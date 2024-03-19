#include "eogll/transforms.h"

EogllProjection eogllPerspectiveProjection(float fov, float near, float far) {
    EogllProjection projection;
    projection.fov = glm_rad(fov);
    projection.near = near;
    projection.far = far;
    return projection;
}

void eogllUpdateProjectionMatrix(const EogllProjection* projection, EogllShaderProgram* shader, const char* name, uint32_t width, uint32_t height) {
    if (width == projection->lastWidth && height == projection->lastHeight) {
        eogllSetUniformMatrix4fv(shader, name, projection->projection);
    } else {
        glm_perspective(projection->fov, (float)width / (float)height, projection->near, projection->far, projection->projection);
        eogllSetUniformMatrix4fv(shader, name, projection->projection);
        projection->lastWidth = width;
        projection->lastHeight = height;
    }
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
    glm_mat4_identity(modelMatrix);
    glm_translate(modelMatrix, model->pos);
    glm_rotate(modelMatrix, glm_rad(model->rot[0]), (vec3){1.0f, 0.0f, 0.0f});
    glm_rotate(modelMatrix, glm_rad(model->rot[1]), (vec3){0.0f, 1.0f, 0.0f});
    glm_rotate(modelMatrix, glm_rad(model->rot[2]), (vec3){0.0f, 0.0f, 1.0f});
    glm_scale(modelMatrix, model->scale);
    eogllSetUniformMatrix4fv(shader, name, modelMatrix);
}