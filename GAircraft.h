#pragma once

#include "GLEngine/GL/GL.h"

class GAircraft : public GLGameObject
{
public:
	GConstructor(GAircraft)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		auto mesh = GLMeshLoader::Load("resources/Aircraft.obj");
		auto texture = GLTextureLoader::Load("resources/Aircraft.jpg");

		auto meshRenderer = this->GetMeshRenderer();

		meshRenderer->SetMesh(mesh);
		meshRenderer->GetMaterial()->SetDiffuseMap(texture);
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);
	}

	int orbitDirection = 1;
	float orbitSpeed = 1.0f;
};