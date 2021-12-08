#pragma once

#include "GLEngine/GL/GL.h"

class GBoundary : public GLGameObject
{
public:
	GConstructor(GBoundary)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		auto shape = GCreate(GLGameObject);
		this->AddChild(shape);

		shape->Initialize();

		auto transform = this->GetTransform();
		transform->SetScale(3.f, 3.f, 3.f);

		auto meshRenderer = this->GetMeshRenderer();
		auto material = meshRenderer->GetMaterial();

		auto mesh = GLMeshLoader::Load("resources/Sphere.obj");
		auto texture = GLTextureLoader::Load("resources/TranslucentBlue.png", GL_RGBA);

		meshRenderer->SetMesh(mesh);
		material->SetDiffuseMap(texture);
		material->SetShininess(120.f);

		meshRenderer->SetBlend(true);
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);
	}

private:
	glm::vec3 Xrotate = glm::vec3(1.f, 0.f, 0.f);
};