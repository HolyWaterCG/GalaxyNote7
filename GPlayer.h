#pragma once

#include "GLEngine/GL/GL.h"

#include "Helpers.h"
#include "GPhysicsObject.h"

class GPlayer : public GLGameObject
{
public:
	GConstructor(GPlayer)
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
		transform->SetScale(0.2f, 0.2f, 0.2f);

		auto meshRenderer = this->GetMeshRenderer();
		auto material = meshRenderer->GetMaterial();

		auto mesh = GLMeshLoader::Load("resources/Aircraft.obj");
		auto texture = GLTextureLoader::Load("resources/Aircraft.jpg");

		meshRenderer->SetMesh(mesh);
		material->SetDiffuseMap(texture);

	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		auto transform = this->GetTransform();

		if (key == "Up")
		{
			if (this->moveSpeed.z != -1.0f)
			{
				check = 3;
				transform->SetRotation(0.f, 0.f, 0.f, 0.f);
				this->moveSpeed.z = -1.0f;
				this->moveSpeed.x = 0.0f;
			}
			else
			{
				if (check != 3) 
				{
					this->moveSpeed.z = 0.0f;
				}
			}
		}
		else if (key == "Down")
		{
			if (this->moveSpeed.z != 1.0f)
			{
				check = 4;
				transform->SetRotation(0.f, 0.f, 0.f, 0.f);
				this->moveSpeed.z = 1.0f;
				this->moveSpeed.x = 0.0f;
			}
			else
			{
				if (check != 4)
				{
					this->moveSpeed.z = 0.0f;
				}
			}
		}
		else if (key == "Left")
		{
			if (this->moveSpeed.x != -1.0f)
			{
				check = 1;
				transform->SetRotation(0.f, 0.f, 0.f, 0.f);
				this->moveSpeed.x = -1.0f;
				this->moveSpeed.z = 0.0f;
				transform->Rotate(45.f, back);
			}
			else
			{
				if (check != 1) 
				{
					this->moveSpeed.x = 0.0f;
				}
			}
		}
		else if (key == "Right")
		{
			if (this->moveSpeed.x != 1.0f)
			{
				check = 2;
				transform->SetRotation(0.f, 0.f, 0.f, 0.f);
				this->moveSpeed.x = 1.0f;
				this->moveSpeed.z = 0.0f;
				transform->Rotate(-45.f, back);
			}
			else
			{
				if (check != 2)
				{
					this->moveSpeed.x = 0.0f;
				}
			}
		}
	}

	void OnKeyUp(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyUp(key, x, y);


	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		auto transform = this->GetTransform();

		if (transform->GetPosition().z >= 4.9f || transform->GetPosition().z <= -4.9f) 
		{
			Reset();
		}

		else 
		{
			transform->Translate(this->moveSpeed.z * deltaTime * back);
		}
		
		if (transform->GetPosition().x >= 4.9f || transform->GetPosition().x <= -4.9f) 
		{
			Reset();
		}

		else 
		{
			transform->Translate(this->moveSpeed.x * deltaTime * side);
		}
	}

	void Reset()
	{
		auto transform = this->GetTransform();

		transform->SetPosition(0.f,0.f,0.f);
	}

private:
	glm::vec3 moveSpeed = glm::vec3(0.0f);
	glm::vec3 back = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 side = glm::vec3(1.0f, 0.0f, 0.0f);

	int check = 0;
};