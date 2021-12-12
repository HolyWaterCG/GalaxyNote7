#pragma once

#include "GLEngine/GL/GL.h"

class GSkybox : public GLGameObject
{
public:
    GConstructor(GSkybox)
        : GSuperClassInitializer(GLGameObject)
    {

    }

    void Initialize() override
    {
        auto mesh = GLMeshLoader::Load("resources/Sphere.obj");
        auto texture = GLTextureLoader::Load("resources/Skybox.png", GL_RGBA);

        auto meshRenderer = this->GetMeshRenderer();
        auto material = meshRenderer->GetMaterial();

        meshRenderer->SetMesh(mesh);
        material->SetDiffuseMap(texture);

        meshRenderer->SetCullFace(false);
        material->SetShader(GLCreate<GLBasicTextureShader>());
    }
private:
};