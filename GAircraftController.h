#pragma once

#include "GLEngine/GL/GL.h"

#include "GAircraft.h"

class GAircraftController : public GLGameObject
{
public:
	GConstructor(GAircraftController)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	virtual ~GAircraftController()
	{

	}

	void Initialize() override
	{
		GLGameObject::Initialize();
	}

	GLSharedPtr<GAircraft> GetAircraft()
	{
		return this->aircraft;
	}

	void SetAircraft(const GLSharedPtr<GAircraft>& aircraft)
	{
		this->aircraft = aircraft;
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "a")
		{
			this->currentRotationSpeed = this->rotationSpeed;
		}
		else if (key == "d")
		{
			this->currentRotationSpeed = -this->rotationSpeed;
		}
	}

	void OnKeyUp(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyUp(key, x, y);

		if (key == "a" && this->currentRotationSpeed == this->rotationSpeed)
		{
			this->currentRotationSpeed = 0;
		}
		else if (key == "d" && this->currentRotationSpeed == -this->rotationSpeed)
		{
			this->currentRotationSpeed = 0;
		}
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		auto transform = this->GetTransform();

		this->rotation += this->currentRotationSpeed * deltaTime;
		this->rotation = glm::clamp(this->rotation, glm::radians(-30.0f), glm::radians(30.0f));

		if (this->currentRotationSpeed == 0.0f && glm::abs(this->rotation) > 0.01f)
		{
			this->rotation -= glm::sign(this->rotation) * this->rotationSpeed * deltaTime;
		}
		else if (this->currentRotationSpeed == 0.0f && glm::abs(this->rotation) < 0.01f)
		{
			this->rotation = 0.0f;
		}

		this->aircraft->GetTransform()->SetEulerAngles(0.0f, 0.0f, this->rotation);
	}

private:
	GLSharedPtr<GAircraft> aircraft;

	float rotation = 0.0f;
	float currentRotationSpeed = 0.0f;
	float rotationSpeed = 0.5f;
};
