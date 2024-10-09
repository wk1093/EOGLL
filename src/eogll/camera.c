#include "eogll/camera.h"

EogllCamera eogllCreateCamera() {
    EogllCamera camera = {
            .pos = {0.0f, 0.0f, 0.0f},
            .up = {0.0f, 1.0f, 0.0f},
            .yaw = -90.0f,
            .pitch = 0.0f,
            .front = {0.0f, 0.0f, -1.0f},
            .worldUp = {0.0f, 1.0f, 0.0f}
    };
    return camera;
}

EogllCameraMatrix eogllCameraMatrix(EogllCamera *camera) {
    EogllCameraMatrix view;
    vec3 res;
    glm_vec3_add(camera->pos, camera->front, res);
    glm_lookat(camera->pos, res, camera->up, view.view);
    return view;
}

void eogllTranslateCamera3f(EogllCamera *camera, float x, float y, float z) {
    vec3 res;
    glm_vec3_add(camera->pos, (vec3) {x, y, z}, res);
    glm_vec3_copy(res, camera->pos);
}

void eogllTranslateCamera(EogllCamera *camera, vec3 translation) {
    vec3 res;
    glm_vec3_add(camera->pos, translation, res);
    glm_vec3_copy(res, camera->pos);
}

void eogllUpdateCameraVectors(EogllCamera *camera) {
    camera->front[0] = cosf(glm_rad(camera->yaw)) * cosf(glm_rad(camera->pitch));
    camera->front[1] = sinf(glm_rad(camera->pitch));
    camera->front[2] = sinf(glm_rad(camera->yaw)) * cosf(glm_rad(camera->pitch));
    glm_vec3_normalize(camera->front);
    glm_vec3_cross(camera->front, camera->worldUp, camera->right);
    glm_vec3_normalize(camera->right);
    glm_vec3_cross(camera->right, camera->front, camera->up);
    glm_vec3_normalize(camera->up);
}

void eogllYawCamera(EogllCamera *camera, float amount) {
    camera->yaw += amount;
    if (camera->yaw > 360.0f) {
        camera->yaw -= 360.0f;
    } else if (camera->yaw < 0.0f) {
        camera->yaw += 360.0f;
    }
    eogllUpdateCameraVectors(camera);
}

void eogllPitchCamera(EogllCamera *camera, float amount) {
    camera->pitch += amount;
    if (camera->pitch > 89.0f) {
        camera->pitch = 89.0f;
    } else if (camera->pitch < -89.0f) {
        camera->pitch = -89.0f;
    }
    eogllUpdateCameraVectors(camera);
}

void eogllMoveCamera(EogllCamera *cam, EogllCameraDirection dir, float amount) {
    switch (dir) {
        case EOGLL_FORWARD: {
            vec3 res = {0.0f, 0.0f, 0.0f};
            glm_vec3_scale(cam->front, amount, res);
            glm_vec3_add(cam->pos, res, cam->pos);
        }
            break;
        case EOGLL_BACKWARD: {
            vec3 res = {0.0f, 0.0f, 0.0f};
            glm_vec3_scale(cam->front, amount, res);
            glm_vec3_sub(cam->pos, res, cam->pos);
        }
            break;
        case EOGLL_RIGHT: {
            vec3 res = {0.0f, 0.0f, 0.0f};
            glm_vec3_cross(cam->front, cam->up, res);
            glm_vec3_normalize(res);
            glm_vec3_scale(res, amount, res);
            glm_vec3_add(cam->pos, res, cam->pos);
        }
            break;
        case EOGLL_LEFT: {
            vec3 res = {0.0f, 0.0f, 0.0f};
            glm_vec3_cross(cam->front, cam->up, res);
            glm_vec3_normalize(res);
            glm_vec3_scale(res, amount, res);
            glm_vec3_sub(cam->pos, res, cam->pos);
        }
            break;
        case EOGLL_UP: {
            vec3 res = {0.0f, 0.0f, 0.0f};
            glm_vec3_scale(cam->up, amount, res);
            glm_vec3_add(cam->pos, res, cam->pos);
        }
            break;
        case EOGLL_DOWN: {
            vec3 res = {0.0f, 0.0f, 0.0f};
            glm_vec3_scale(cam->up, amount, res);
            glm_vec3_sub(cam->pos, res, cam->pos);
        }
            break;
    }

}

void eogllUpdateCameraMatrix(EogllCamera *camera, EogllShaderProgram *program, const char *name) {
    EogllCameraMatrix view = eogllCameraMatrix(camera);
    eogllSetUniformMatrix4fv(program, name, view.view);
}