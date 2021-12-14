#pragma once

#include "GLEngine/GL/GL.h"

class GSpacecraft : public GLGameObject
{
public:
	GConstructor(GSpacecraft)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		auto mesh = GLMeshLoader::Load("resources/Spacecraft.obj");
		auto texture = GLTextureLoader::Load("resources/Spacecraft.png", GL_RGBA);

		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(mesh);
		meshRenderer->GetMaterial()->SetDiffuseMap(texture);
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);
	}
};
