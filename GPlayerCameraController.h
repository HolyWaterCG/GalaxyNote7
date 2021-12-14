#pragma once

#include "GLEngine/GL/GL.h"

class GPlayerCameraController : public GLGameObject
{
public:
    GConstructor(GPlayerCameraController)
        : GSuperClassInitializer(GLGameObject)
    {

    }

    void Initialize() override
    {
        GLGameObject::Initialize();
    }

    void Update(float deltaTime) override
    {
        GLGameObject::Update(deltaTime);

        auto cameraTransform = this->camera->GetTransform();
        cameraTransform->SetEulerAngles(this->euler);
    }


    void OnKeyDown(const std::string& key, int x, int y) override
    {
        GLGameObject::OnKeyDown(key, x, y);

        if (key == "c")
        {
            this->euler = glm::vec3(0.0f);            
        }
    }

    void OnMouseDown(int button, int x, int y) override
    {
        GLGameObject::OnMouseDown(button, x, y);

        if (button == 2)
        {
            this->mouseLock = !this->mouseLock;
        }

        if (this->mouseLock)
        {
            glutSetCursor(GLUT_CURSOR_CROSSHAIR);
        }
        else
        {
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        }
    }

    void OnMouseMove(int button, int x, int y) override
    {
        GLGameObject::OnMouseMove(button, x, y);

        if (!this->mouseLock)
        {
            return;
        }

        auto window = GLGetCurrentWindow();
        auto windowSize = window->GetSize();

        auto center = windowSize / 2;

        auto euler = glm::vec3(center.y - y, center.x - x, 0.0f) * this->mouseSensitivity;
        this->euler += euler;

        glutWarpPointer(center.x, center.y);
    }

    GLSharedPtr<GCamera> GetCamera()
    {
        return this->camera;
    }

    void SetCamera(const GLSharedPtr<GCamera>& camera)
    {
        this->camera = camera;
    }

    glm::vec3 GetEulerAngles()
    {
        return this->euler;
    }

    void SetEulerAngles(float x, float y, float z)
    {
        this->euler.x = x;
        this->euler.y = y;
        this->euler.z = z;
    }

    void SetEulerAngles(const glm::vec3& euler)
    {
        this->euler = euler;
    }

    float GetMouseSensitivity()
    {
        return this->mouseSensitivity;
    }

    void SetMouseSensitivity(float mouseSensitivity)
    {
        this->mouseSensitivity = mouseSensitivity;
    }

private:
    glm::vec3 euler = glm::vec3(0.0f);
    float mouseSensitivity = 0.005f;

    GLSharedPtr<GCamera> camera;

    bool mouseLock = false;
};