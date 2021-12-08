#pragma once

#include "GLEngine/GL/GL.h"

class GBox : public GCube
{
public:
	GConstructor(GBox)
		: GSuperClassInitializer(GCube)
	{

	};

	void Initialize() override
	{
		GCube::Initialize();

		auto shape = GCreate(GCube);
		this->AddChild(shape);

		shape->Initialize();

		auto transform = this->GetTransform();
		transform->SetScale(0.1f, 0.1f, 0.1f);

		auto meshRenderer = this->GetMeshRenderer();
		auto material = meshRenderer->GetMaterial();

		auto mesh = GLMeshLoader::Load("resources/Cube.obj");
		auto texture = GLTextureLoader::Load("resources/Dice.png");

		meshRenderer->SetMesh(mesh);
		material->SetDiffuseMap(texture);


	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		auto transform = this->GetTransform();
		transform->Rotate(this->rotating * deltaTime , yrotate);
	}

private:
	glm::vec3 yrotate = glm::vec3(0.0f, 1.0f, 0.0f);

	int rotating = 1;
};

class GBoxItem : public GLGameObject
{
public:
	GConstructor(GBoxItem)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		for (int i = 0; i < 4; i++) {

			auto Cube = GCreate(GBox);

			this->AddChild(Cube);

			Cube->Initialize();

			auto transform = Cube->GetTransform();
			transform->SetPosition(Rand3v(-2.5f, 2.5f, 0.f, 0.f, -2.5f, 2.5f));
			
		}
	}

	void SetItemBox(int ItemBox)
	{
		this->ItemBoxCnt = ItemBox;
	}

	void Update(GLfloat deltaTime) override
	{
		GLGameObject::Update(deltaTime);
	}

private:
	int ItemBoxCnt = 4;

};