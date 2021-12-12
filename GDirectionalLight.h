#pragma once

#include "GLEngine/GL/GL.h"

#include "Helpers.h"

class GDirectionalLight : public GLGameObject
{
public:
	GConstructor(GDirectionalLight, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& direction)
		: GSuperClassInitializer(GLGameObject)
	{
		this->light = GLCreate<GLDirectionalLight>();

		this->light->SetAmbient(ambient);
		this->light->SetDiffuse(diffuse);
		this->light->SetSpecular(specular);
		this->light->SetDirection(direction);
	}

	~GDirectionalLight()
	{
		this->GetScene()->RemoveLight(this->light);
	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		this->GetScene()->AddLight(this->light);
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
	}

private:
	GLSharedPtr<GLDirectionalLight> light;
};