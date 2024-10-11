#include "eogll/transforms.h"

#include "eogll/logging.h"

EogllProjection eogllPerspectiveProjection(float fov, float near, float far) {
    EogllProjection projection;
    projection.fov = glm_rad(fov);
    projection.near = near;
    projection.far = far;
    projection.isOrtho = false;
    projection.lastWidth = -1;
    projection.lastHeight = -1;
    return projection;
}

EogllProjection eogllOrthographicProjection(float near, float far) {
    EogllProjection projection;
    projection.lastTop = -1.0f;
    projection.lastBottom = 1.0f;
    projection.lastLeft = -1.0f;
    projection.lastRight = 1.0f;

    projection.near = near;
    projection.far = far;
    projection.isOrtho = true;
    return projection;
}

void eogllUpdateProjectionMatrix(EogllProjection* projection, EogllShaderProgram* shader, const char* name, uint32_t width, uint32_t height) {
    if (!projection->isOrtho) {
        if (width != projection->lastWidth || height != projection->lastHeight) {
            glm_perspective(projection->fov, (float)width / (float)height, projection->near, projection->far, projection->projection);
            projection->lastWidth = width;
            projection->lastHeight = height;
        }
    } else {
        if (width != projection->lastRight || height != projection->lastBottom || 0 != projection->lastTop || 0 != projection->lastLeft) {
            glm_ortho(0.0f, (float)width, (float)height, 0.0f, projection->near, projection->far, projection->projection);
            projection->lastTop = 0.0f;
            projection->lastBottom = height;
            projection->lastLeft = 0.0f;
            projection->lastRight = width;
        }
        EOGLL_LOG_WARN(stderr, "Orthographic projection calling perspective projection update function");
    }
    eogllSetUniformMatrix4fv(shader, name, projection->projection);
}

void eogllUpdateProjectionMatrixOrtho(EogllProjection* projection, EogllShaderProgram* shader, const char* name, float top, float bottom, float left, float right) {
    if (!projection->isOrtho) {
        float width = right - left;
        float height = top - bottom;
        width = fabs(width);
        height = fabs(height);
        if (width != projection->lastWidth || height != projection->lastHeight) {
            glm_perspective(projection->fov, width / height, projection->near, projection->far, projection->projection);
            projection->lastWidth = width;
            projection->lastHeight = height;
        }
        EOGLL_LOG_WARN(stderr, "Perspective projection calling orthographic projection update function");
    } else {
        if (top != projection->lastTop || bottom != projection->lastBottom || left != projection->lastLeft || right != projection->lastRight) {
            glm_ortho(left, right, bottom, top, projection->near, projection->far, projection->projection);
            projection->lastTop = top;
            projection->lastBottom = bottom;
            projection->lastLeft = left;
            projection->lastRight = right;
        }
    }
    eogllSetUniformMatrix4fv(shader, name, projection->projection);
}

EogllModel eogllCreateModel() {
    EogllModel model;
    glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, model.pos);
    glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, model.rot);
    glm_vec3_copy((vec3){1.0f, 1.0f, 1.0f}, model.scale);
    return model;
}

void eogllRotateModel3f(EogllModel *model, float angle, float x, float y, float z) {
    float r = glm_rad(angle);
    glm_vec3_add(model->rot, (vec3){r*x, r*y, r*z}, model->rot);
}

void eogllRotateModel(EogllModel *model, float angle, vec3 axis) {
    vec3 res;
    glm_vec3_scale(axis, glm_rad(angle), res);
    glm_vec3_add(model->rot, res, model->rot);
}

void eogllTranslateModel3f(EogllModel *model, float x, float y, float z) {
    glm_vec3_add(model->pos, (vec3){x, y, z}, model->pos);
}

void eogllTranslateModel(EogllModel *model, vec3 translation) {
    glm_vec3_add(model->pos, translation, model->pos);
}

void eogllScaleModel3f(EogllModel *model, float x, float y, float z) {
    glm_vec3_add(model->scale, (vec3){x, y, z}, model->scale);
}

void eogllScaleModel(EogllModel *model, vec3 scale) {
    glm_vec3_add(model->scale, scale, model->scale);
}

void eogllUpdateModelMatrix(const EogllModel* model, EogllShaderProgram* shader, const char* name) {
    mat4 modelMatrix;
    EogllModel copy = *model;
    glm_mat4_identity(modelMatrix);
    glm_translate(modelMatrix, copy.pos);
    glm_rotate(modelMatrix, glm_rad(model->rot[0]), (vec3){1.0f, 0.0f, 0.0f});
    glm_rotate(modelMatrix, glm_rad(model->rot[1]), (vec3){0.0f, 1.0f, 0.0f});
    glm_rotate(modelMatrix, glm_rad(model->rot[2]), (vec3){0.0f, 0.0f, 1.0f});
    glm_scale(modelMatrix, copy.scale);
    eogllSetUniformMatrix4fv(shader, name, modelMatrix);
}