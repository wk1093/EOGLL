#include "hogll/transforms.hpp"

namespace ogl {
    Model::Model() {
        model = eogllCreateModel();
    }

    Model::Model(glm::vec3 pos) {
        model = eogllCreateModel();
        this->pos() = pos;
    }

    glm::vec3* Model::posptr() {
        return (glm::vec3*)&model.pos;
    }

    glm::vec3& Model::pos() {
        return *(glm::vec3*)&model.pos;
    }

    glm::vec3* Model::rotptr() {
        return (glm::vec3*)&model.rot;
    }

    glm::vec3& Model::rot() {
        return *(glm::vec3*)&model.rot;
    }

    glm::vec3* Model::scaleptr() {
        return (glm::vec3*)&model.scale;
    }

    glm::vec3& Model::scale() {
        return *(glm::vec3*)&model.scale;
    }

    void Model::update(EogllShaderProgram* shader, const char* name) {
        eogllUpdateModelMatrix(&model, shader, name);
    }

    EogllModel* Model::getModel() {
        return &model;
    }

    Camera::Camera() {
        camera = eogllCreateCamera();
    }

    Camera::Camera(glm::vec3 pos) {
        camera = eogllCreateCamera();
        this->pos() = pos;
    }

    glm::vec3* Camera::posptr() {
        return (glm::vec3*)&camera.pos;
    }
    glm::vec3& Camera::pos() {
        return *(glm::vec3*)&camera.pos;
    }

    void Camera::yaw(float amount) {
        eogllYawCamera(&camera, amount);
    }

    void Camera::pitch(float amount) {
        eogllPitchCamera(&camera, amount);
    }

    void Camera::move(EogllCameraDirection dir, float amount) {
        eogllMoveCamera(&camera, dir, amount);
    }

    void Camera::update(EogllShaderProgram* shader, const char* name) {
        eogllUpdateCameraMatrix(&camera, shader, name);
    }

    Projection::Projection(float fov, float near, float far) {
        proj = eogllPerspectiveProjection(fov, near, far);
    }

    void Projection::update(EogllShaderProgram* shader, const char* name, const ogl::Window& window) {
        eogllUpdateProjectionMatrix(&proj, shader, name, window.getWidth(), window.getHeight());
    }
}