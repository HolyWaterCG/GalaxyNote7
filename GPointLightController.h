#pragma once

#include "GLEngine/GL/GL.h"

#include "Helpers.h"

class GPointLightController : public GCube
{
public:
	GConstructor(GPointLightController, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
		float constant, float linear, float quadratic)
		: GSuperClassInitializer(GCube)
	{
		this->light = GLCreate<GLPointLight>();

		this->light->SetAmbient(ambient);
		this->light->SetDiffuse(diffuse);
		this->light->SetSpecular(specular);
		this->light->SetConstant(constant);
		this->light->SetLinear(linear);
		this->light->SetQuadratic(quadratic);
	}

	~GPointLightController()
	{
		this->GetScene()->RemoveLight(this->light);
	}

	void Initialize() override
	{
		GCube::Initialize();

		this->GetScene()->AddLight(this->light);
		this->GetTransform()->SetScale(0.00001f, 0.00001f, 0.00001f);
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "w")
		{
			ToggleDirection(this->rotationDirection, 1);
		}
		else if (key == "e")
		{
			ToggleDirection(this->rotationDirection, -1);
		}
		else if (key == "i")
		{
			if (this->moveSpeed.y != 1.0f)
			{
				this->moveSpeed.y = 1.0f;
			}
			else
			{
				this->moveSpeed.y = 0.0f;
			}
		}
		else if (key == "o")
		{
			if (this->moveSpeed.z != -1.0f)
			{
				this->moveSpeed.z = -1.0f;
			}
			else
			{
				this->moveSpeed.z = 0.0f;
			}
		}
		else if (key == "c" || key == "C")
		{
			this->light->SetAmbient(Rand3v(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f));
			this->light->SetDiffuse(Rand3v(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f));
			this->light->SetSpecular(Rand3v(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f));
		}
		else if (key == "-" || key == "_")
		{
			this->light->SetAmbient(this->light->GetAmbient() - 0.1f);
			this->light->SetDiffuse(this->light->GetDiffuse() - 0.1f);
			this->light->SetSpecular(this->light->GetSpecular() - 0.1f);
		}
		else if (key == "+" || key == "=")
		{
			this->light->SetAmbient(this->light->GetAmbient() + 0.1f);
			this->light->SetDiffuse(this->light->GetDiffuse() + 0.1f);
			this->light->SetSpecular(this->light->GetSpecular() + 0.1f);
		}
		else if (key == "m")
		{
			this->light->SetActive(true);
		}
		else if (key == "M")
		{
			this->light->SetActive(false);
		}
	}

	void OnKeyUp(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyUp(key, x, y);
	}

	void Update(float deltaTime) override
	{
		RepeatLight();

		GLGameObject::Update(deltaTime);

		auto transform = this->GetTransform();
		 
		glm::vec3 back = glm::normalize(transform->GetRotation() * glm::vec3(0.0f, 1.0f, 0.0f));

		transform->Translate(this->moveSpeed.y * deltaTime * back);

		if (this->rotationDirection)
		{
			transform->RotateAround(glm::vec3(0.0f), deltaTime * this->rotationDirection, glm::vec3(0.0f, 1.0f, 0.0f));
		}
	}

	void RepeatLight()
	{
		++timeCnt;

		if (timeCnt > 30 && timeCnt <= 60) {
			this->light->SetAmbient(this->light->GetAmbient() + 0.04f);
			this->light->SetDiffuse(this->light->GetDiffuse() + 0.04f);
			this->light->SetSpecular(this->light->GetSpecular() + 0.04f);
		}
		else if (timeCnt > 60) {
			timeCnt = 0;
		}
		else if (timeCnt > 0 && timeCnt <= 30) {
			this->light->SetAmbient(this->light->GetAmbient() - 0.04f);
			this->light->SetDiffuse(this->light->GetDiffuse() - 0.04f);
			this->light->SetSpecular(this->light->GetSpecular() - 0.04f);
		}
	}
	

private:
	GLSharedPtr<GLPointLight> light;
	int timeCnt = 0;
	glm::vec3 moveSpeed = glm::vec3(0.0f);
	int rotationDirection = 0;
	
};