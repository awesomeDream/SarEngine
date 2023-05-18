#include "Renderer.h"

#include "Matrix.h"
#include "Camera.h"
#include "Object.h"

#define EPSILON 1e-5f
#define CLIP_MAX 50

Matrix4x4 Renderer::modelMatrix(const Object& object)
{
	Matrix4x4 t = Matrix4x4::translate(object.getPosition());
	Matrix4x4 rx = Matrix4x4::rotateX(object.getRotation().x);
	Matrix4x4 ry = Matrix4x4::rotateY(object.getRotation().y);
	Matrix4x4 rz = Matrix4x4::rotateZ(object.getRotation().z);
	Matrix4x4 s = Matrix4x4::scale(object.getScale());

	return t * rx * ry * rz * s;
}
Matrix4x4 Renderer::viewMatrix()
{
	Camera& camera = *this->camera;
	Matrix4x4 ir;
	ir.mat[0] = camera.GetAxis().x.x; ir.mat[1] = camera.GetAxis().y.x; ir.mat[2] = camera.GetAxis().z.x;
	ir.mat[4] = camera.GetAxis().x.y; ir.mat[5] = camera.GetAxis().y.y; ir.mat[6] = camera.GetAxis().z.y;
	ir.mat[8] = camera.GetAxis().x.z; ir.mat[9] = camera.GetAxis().y.z; ir.mat[10] = camera.GetAxis().z.z;

	Matrix4x4 t = Matrix4x4::translate(camera.GetPosition() * -1.f);

	return ir * t;
}
Matrix4x4 Renderer::projectionMatrix(void)
{
	return this->camera->getProjectionMatrix();
}
Matrix4x4 Renderer::screenSpace(void) {
	Camera& camera = *this->camera;
	Matrix4x4 s = Matrix4x4::scale({ camera.getWidth() / 2, camera.getHeight() / 2, 0.5f });
	Matrix4x4 t = Matrix4x4::translate({ camera.getWidth() / 2, camera.getHeight() / 2, 1.f });

	return t * s;
}

typedef enum {
    POSITIVE_W,
    POSITIVE_X,
    NEGATIVE_X,
    POSITIVE_Y,
    NEGATIVE_Y,
    POSITIVE_Z,
    NEGATIVE_Z
} PLANE;

bool is_inside_plane(Vector4 vec, PLANE plane)
{
    switch (plane) {
    case POSITIVE_W: return vec.w >= EPSILON;
    case POSITIVE_X: return vec.x <= +vec.w;
    case NEGATIVE_X: return vec.x >= -vec.w;
    case POSITIVE_Y: return vec.y <= +vec.w;
    case NEGATIVE_Y: return vec.y >= -vec.w;
    case POSITIVE_Z: return vec.z <= +vec.w;
    case NEGATIVE_Z: return vec.z >= -vec.w;
    default: return false;
    }
}

static float get_intersect_ratio(Vector4 prev, Vector4 curr, PLANE plane) {
    switch (plane) {
    case POSITIVE_W: return (prev.w - EPSILON) / (prev.w - curr.w);
    case POSITIVE_X: return (prev.w - prev.x) / ((prev.w - prev.x) - (curr.w - curr.x));
    case NEGATIVE_X: return (prev.w + prev.x) / ((prev.w + prev.x) - (curr.w + curr.x));
    case POSITIVE_Y: return (prev.w - prev.y) / ((prev.w - prev.y) - (curr.w - curr.y));
    case NEGATIVE_Y: return (prev.w + prev.y) / ((prev.w + prev.y) - (curr.w + curr.y));
    case POSITIVE_Z: return (prev.w - prev.z) / ((prev.w - prev.z) - (curr.w - curr.z));
    case NEGATIVE_Z: return (prev.w + prev.z) / ((prev.w + prev.z) - (curr.w + curr.z));
    default: return 0;
    }
}

static int clip_against_plane(PLANE plane, Vector4 in[CLIP_MAX], int in_size, Vector4 out[CLIP_MAX]) {
    int ret = 0; // out num vertices;

    for (int i = 0; i < in_size; i++) {
        int prev_idx = (i == 0) ? in_size - 1 : i - 1;
        int curr_idx = i;

        Vector4 prev = in[prev_idx];
        Vector4 curr = in[curr_idx];
        
        bool prev_inside = is_inside_plane(prev, plane);
        bool curr_inside = is_inside_plane(curr, plane);

        if (prev_inside != curr_inside) {
            float ratio = get_intersect_ratio(prev, curr, plane);
            out[ret++] = Vector4::lerp(prev, curr, ratio);
        }

        if (curr_inside) {
            out[ret++] = curr;
        }
    }

    return ret;
}

#define CLIP_IN2OUT(plane)                                                  \
    do {                                                                    \
        num_vertices = clip_against_plane(plane, in, num_vertices, out);    \
        if (num_vertices < 3) {                                             \
            return 0;                                                       \
        }                                                                   \
    } while (0)

#define CLIP_OUT2IN(plane)                                                  \
    do {                                                                    \
        num_vertices = clip_against_plane(plane, out, num_vertices, in);    \
        if (num_vertices < 3) {                                             \
            return 0;                                                       \
        }                                                                   \
    } while (0)

#define IS_VERTEX_VISIBLE(v)                                                \
  ( ((v.x > 0 ? v.x : -v.x) <= v.w) &&                                      \
    ((v.y > 0 ? v.y : -v.y) <= v.w) &&                                      \
    ((v.z > 0 ? v.z : -v.z) <= v.w) )

int clipping(Vector4 in[CLIP_MAX], Vector4 out[CLIP_MAX]) {
    if (
        IS_VERTEX_VISIBLE(in[0]) && 
        IS_VERTEX_VISIBLE(in[1]) && 
        IS_VERTEX_VISIBLE(in[2])
    ) {
        out[0] = in[0];
        out[1] = in[1];
        out[2] = in[2];
        
        return 3;
    }

    int num_vertices = 3;
    CLIP_IN2OUT(POSITIVE_W);
    CLIP_OUT2IN(POSITIVE_X);
    CLIP_IN2OUT(NEGATIVE_X);
    CLIP_OUT2IN(POSITIVE_Y);
    CLIP_IN2OUT(NEGATIVE_Y);
    CLIP_OUT2IN(POSITIVE_Z);
    CLIP_IN2OUT(NEGATIVE_Z);
    return num_vertices;
}


void Renderer::renderObject(Object& object, Application& app)
{
    Vector4 in[CLIP_MAX], out[CLIP_MAX];

	Matrix4x4 model = this->modelMatrix(object);
	Matrix4x4 view = this->viewMatrix();
    Matrix4x4 projection = this->projectionMatrix();
	Matrix4x4 mvp = projection * view * model;
	Matrix4x4 screenSpace = this->screenSpace();

    Mesh* mesh = object.getMesh();
    const float* vArray = mesh->getVertexArray()->array;
    const size_t vArray_size = mesh->getVertexArray()->size;
    const int* iArray = mesh->getIndexArray()->array;
    const size_t iArray_size = mesh->getIndexArray()->size;
    
    int k = 0;
    for (size_t i = 0; i < iArray_size; i++) {
        int idx_0 = iArray[k] * 3;
        int idx_1 = iArray[k + 1] * 3;
        int idx_2 = iArray[k + 2] * 3;

        k += 3;

        Vector4 p0 = { vArray[idx_0], vArray[idx_0 + 1], vArray[idx_0 + 2], 1 };
        Vector4 p1 = { vArray[idx_1], vArray[idx_1 + 1], vArray[idx_1 + 2], 1 };
        Vector4 p2 = { vArray[idx_2], vArray[idx_2 + 1], vArray[idx_2 + 2], 1 };

        in[0] = mvp * p0;
        in[1] = mvp * p1;
        in[2] = mvp * p2;
        
        int cnt = clipping(in, out);

        for (int j = 0; j < cnt - 2; j++)
        {
            Vector4 v0 = screenSpace * out[0].perspectiveDivision();
            Vector4 v1 = screenSpace * out[1 + j].perspectiveDivision();
            Vector4 v2 = screenSpace * out[2 + j].perspectiveDivision();

            // triangle[0] = { v0.x, v0.y };
            // triangle[1] = { v0.x, v0.y };
            // triangle[2] = { v0.x, v0.y };

            // draw triangle

            app.drawLine(v0.x, v0.y, v1.x, v1.y);
            app.drawLine(v1.x, v1.y, v2.x, v2.y);
            app.drawLine(v2.x, v2.y, v0.x, v0.y);
        }

        /*
        Vector4 v0 = screenSpace * in[0].perspectiveDivision();
        Vector4 v1 = screenSpace * in[1].perspectiveDivision();
        Vector4 v2 = screenSpace * in[2].perspectiveDivision();

        app.drawLine(v0.x, v0.y, v1.x, v1.y);
        app.drawLine(v1.x, v1.y, v2.x, v2.y);
        app.drawLine(v2.x, v2.y, v0.x, v0.y);
        */
	}
}