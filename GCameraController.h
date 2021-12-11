#pragma once

#include "GLEngine/GL/GL.h"

class GCameraController : public GLGameObject
{
public:
	GConstructor(GCameraController)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override //부모에 있는 클래스가 virtual 이여야함 그냥 오버라이드 무조건 쓰셈
	{
		this->perspectiveCamera = GCreate(GPerspectiveCamera, 90.0f); //원근
		this->orthographicCamera = GCreate(GOrthographicCamera, -2.0f, 2.0f, -2.0f, 2.0f); //직각

		auto scene = this->GetScene(); //root object가 포함되어있는 scene
		scene->AddCamera(this->perspectiveCamera); 
		scene->AddCamera(this->orthographicCamera); 

		this->AddChildren({ this->perspectiveCamera, this->orthographicCamera });

		this->Reset();
	}

	void Update(float deltaTime) override //카메라 srt
	{
		GLGameObject::Update(deltaTime);

		auto transform = this->GetTransform();

		transform->RotateAround( //공전 각도만큼
			glm::vec3(0.0f, 0.0f, 0.0f), deltaTime * this->rotatingAroundCenter, glm::vec3(0.0f, 1.0f, 0.0f));

		transform->Rotate(deltaTime * this->rotating, glm::vec3(0.0f, 1.0f, 0.0f)); // 자전

		transform->Translate(glm::vec3(this->directions) * deltaTime); 
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "p")
		{
			this->perspectiveCamera->SetActive(true);
			this->orthographicCamera->SetActive(false);
		}
		else if (key == "P")
		{
			this->perspectiveCamera->SetActive(false);
			this->orthographicCamera->SetActive(true);
		}
		else if (key == "z")
		{
			ToggleDirection(this->directions.z, 1);
		}
		else if (key == "Z")
		{
			ToggleDirection(this->directions.z, -1);
		}
		else if (key == "x")
		{
			ToggleDirection(this->directions.x, 1);
		}
		else if (key == "X")
		{
			ToggleDirection(this->directions.x, -1);
		}
		else if (key == "r")
		{
			ToggleDirection(this->rotatingAroundCenter, 1);
			std::cout << this->GetTransform()->GetPosition().x << std::endl;

		}
		else if (key == "R")
		{
			ToggleDirection(this->rotatingAroundCenter, -1);
		}
		else if (key == "a")
		{
			this->rotatingAroundCenter = 1; 
		}
		else if (key == "A")
		{
			this->rotatingAroundCenter = 0;
		}

		else if (key == "s" || key == "S")
		{
			this->Stop();
		}
		else if (key == "c" || key == "C")
		{
			this->Stop();
			this->Reset();
		}
	}

	void OnKeyUp(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyUp(key, x, y);
	}

	void Stop()
	{
		this->rotating = 0;
		this->rotatingAroundCenter = 0;
		this->directions = glm::tvec3<int>(0);
	}

	void Reset()
	{
		this->perspectiveCamera->SetActive(true);
		this->orthographicCamera->SetActive(false);

		this->perspectiveCamera->GetTransform()->SetEulerAngles(glm::radians(-90.0f), 0.0f, 0.0f);
		this->orthographicCamera->GetTransform()->SetEulerAngles(glm::radians(-90.0f), 0.0f, 0.0f);
	}

private:
	int rotatingAroundCenter = 0;
	int rotating = 0;

	glm::tvec3<int> directions = glm::tvec3<int>(0);

	GLSharedPtr<GPerspectiveCamera> perspectiveCamera; //동적할당인데 나중에 해제할필요없는 smart
	GLSharedPtr<GOrthographicCamera> orthographicCamera;
};