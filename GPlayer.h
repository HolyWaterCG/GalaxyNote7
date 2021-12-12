#pragma once

#include "GLEngine/GL/GL.h"

#include "GPhysicsObject.h"
#include "GAircraft.h"
#include "GPointLight.h"
#include "GAircraftController.h"
#include "GPlayerCameraController.h"
#include "GPlayerBulletShooter.h"
#include "GPlayerUI.h"

class GPlayer : public GPhysicsObject
{
public:
	GConstructor(GPlayer)
		: GSuperClassInitializer(GPhysicsObject)
	{

	}

	~GPlayer()
	{
		auto scene = this->GetScene();

		if (scene)
		{
			if (this->camera)
			{
				scene->RemoveCamera(this->camera);
				scene->RemoveCamera(this->uiCamera);
			}
		}
	}

	void Initialize() override
	{
		GPhysicsObject::Initialize();
	   
		auto camera = GCreate(GPerspectiveCamera, 90.0f);
		auto uiCamera = GCreate(GPerspectiveCamera, 90.0f);
		auto light = GCreate(GPointLight, glm::vec3(0.7f), glm::vec3(0.8f), glm::vec3(0.8f), 0.22f, 0.2f, 1.0f);
		auto aircraft = GCreate(GAircraft);
		auto aircraftController = GCreate(GAircraftController);
		auto cameraController = GCreate(GPlayerCameraController);
		auto leftBulletShooter = GCreate(GPlayerShooter);
		auto rightBulletShooter = GCreate(GPlayerShooter);
		
		this->AddChildren({ camera, light, aircraft, aircraftController, cameraController });
		this->world->AddChildren({ uiCamera, leftBulletShooter, rightBulletShooter });

		camera->Initialize();
		uiCamera->Initialize();
		light->Initialize();
		aircraft->Initialize();
		aircraftController->Initialize();
		cameraController->Initialize();
		leftBulletShooter->Initialize();
		rightBulletShooter->Initialize();

		light->GetTransform()->Translate(0.0f, 0.0f, 2.0f);

		auto cameraTransform = camera->GetTransform();
		cameraTransform->Translate(0.0f, 0.75f, 0.0f);

		aircraftController->SetAircraft(aircraft);
		cameraController->SetCamera(camera);

		uiCamera->SetLayer("UI");

		camera->SetOrder(1);
		uiCamera->SetOrder(2);

		leftBulletShooter->SetName("PlayerLeftShooter");
		rightBulletShooter->SetName("PlayerRightShooter");

		this->camera = camera;
		this->uiCamera = uiCamera;
		this->light = light;
		this->aircraftController = aircraftController;
		this->cameraController = cameraController;
		this->leftShooter = leftBulletShooter;
		this->rightShooter = rightBulletShooter;

		auto scene = this->GetScene();

		if (scene)
		{
			scene->AddCamera(this->camera);
			scene->AddCamera(this->uiCamera);

			this->SetBody(scene->GetPhysics()->CreateRigidBody(this->GetTransform()));
			this->collisionShape = scene->GetPhysics()->CreateBoxShape(glm::vec3(0.8f, 0.2f, 0.8f));
			this->collider = this->GetBody()->addCollider(this->collisionShape, GLPhysicsTransform());

			this->GetBody()->setType(GLBodyType::KINEMATIC);
		}
	}

	void Update(float deltaTime) override
	{
		GPhysicsObject::Update(deltaTime);

		auto transform = this->GetTransform();

		auto currentSpeed = this->currentSpeed * deltaTime;
		transform->Translate(currentSpeed);

		this->UpdateBody();
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GPhysicsObject::OnKeyDown(key, x, y);

		if (key == "w")
		{
			this->currentSpeed.z = -this->speed.z;
		}
		else if (key == "s")
		{
			this->currentSpeed.z = this->speed.z;
		}
		else if (key == "a")
		{
			this->currentSpeed.x = -this->speed.x;
		}
		else if (key == "d")
		{
			this->currentSpeed.x = this->speed.x;
		}
		else if (key == "LCtrl")
		{
			this->currentSpeed.y = -this->speed.y;
		}
		else if (key == "Space")
		{
			this->currentSpeed.y = this->speed.y;
		}
	}

	void OnKeyUp(const std::string& key, int x, int y) override
	{
		GPhysicsObject::OnKeyUp(key, x, y);

		if (key == "w" && this->currentSpeed.z == -this->speed.z)
		{
			this->currentSpeed.z = 0;
		}
		else if (key == "s" && this->currentSpeed.z == this->speed.z)
		{
			this->currentSpeed.z = 0;
		}
		else if (key == "a" && this->currentSpeed.x == -this->speed.x)
		{
			this->currentSpeed.x = 0;
		}
		else if (key == "d" && this->currentSpeed.x == this->speed.x)
		{
			this->currentSpeed.x = 0;
		}
		else if (key == "LCtrl" && this->currentSpeed.y == -this->speed.y)
		{
			this->currentSpeed.y = 0;
		}
		else if (key == "Space" && this->currentSpeed.y == this->speed.y)
		{
			this->currentSpeed.y = 0;
		}
	}

	void OnMouseDown(int button, int x, int y) override
	{
		GPhysicsObject::OnMouseDown(button, x, y);

		if (button == 0)
		{
			auto euler = this->cameraController->GetEulerAngles();
			auto rotation = glm::quat(euler);
			auto direction = glm::normalize(rotation * glm::vec3(0.0f, 0.0f, -1.0f));

			this->leftShooter->Shoot(this->GetTransform()->GetPosition() + glm::vec3(-0.4f, 0.0f, -0.5f), direction);
			this->rightShooter->Shoot(this->GetTransform()->GetPosition() + glm::vec3(0.4f, 0.0f, -0.5f), direction);
		}
	}

	GLGameObject* GetWorld()
	{
		return this->world;
	}

	void SetWorld(GLGameObject* world)
	{
		this->world = world;
	}

	GLSharedPtr<GCamera> GetCamera()
	{
		return this->camera;
	}

	GLSharedPtr<GCamera> GetUICamera()
	{
		return this->uiCamera;
	}

	float GetHP()
	{
		return this->hp;
	}

	float GetMaxHP()
	{
		return this->maxHP;
	}

	float GetAtk()
	{
		return this->atk;
	}

	void SetHP(float hp)
	{
		this->hp = hp;
	}

	void SetMaxHP(float maxHP)
	{
		this->maxHP = maxHP;
	}

	void SetAtk(float atk)
	{
		this->atk = atk;
	}

private:
	GLGameObject* world = nullptr;
	GLSharedPtr<GPerspectiveCamera> camera = nullptr;
	GLSharedPtr<GPerspectiveCamera> uiCamera = nullptr;
	GLSharedPtr<GPointLight> light = nullptr;
	GLSharedPtr<GAircraftController> aircraftController = nullptr;
	GLSharedPtr<GPlayerCameraController> cameraController = nullptr;
	GLSharedPtr<GPlayerShooter> leftShooter = nullptr;
	GLSharedPtr<GPlayerShooter> rightShooter = nullptr;

	glm::vec3 speed = glm::vec3(4.0f, 1.5f, 2.0f);
	glm::vec3 currentSpeed = glm::vec3(0.0f);

	float hp = 100.0f;
	float maxHP = 100.0f;

	float stamina = 100.0f;
	float maxStamina = 100.0f;

	float atk = 50.0f;

	GLBoxShape* collisionShape;
	GLCollider* collider;
};