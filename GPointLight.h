#pragma once

#include "GLEngine/GL/GL.h"

#include "Helpers.h"

class GPointLight : public GLGameObject
{
public:
	GConstructor(GPointLight, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
		float constant, float linear, float quadratic)
		: GSuperClassInitializer(GLGameObject)
	{
		this->light = GLCreate<GLPointLight>();

		this->light->SetAmbient(ambient);
		this->light->SetDiffuse(diffuse);
		this->light->SetSpecular(specular);
		this->light->SetConstant(constant);
		this->light->SetLinear(linear);
		this->light->SetQuadratic(quadratic);
	}

	~GPointLight()
	{
		this->GetScene()->RemoveLight(this->light);
	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		this->GetScene()->AddLight(this->light);
		this->GetTransform()->SetScale(0.1f, 0.1f, 0.1f);
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "m")
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
		GLGameObject::Update(deltaTime);

		auto transform = this->GetTransform();
		this->light->SetPosition(transform->GetPosition());
	}

private:
	GLSharedPtr<GLPointLight> light;

	glm::vec3 moveSpeed = glm::vec3(0.0f);
	int rotationDirection = 0;
};