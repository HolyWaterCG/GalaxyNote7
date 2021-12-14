#pragma once

#include "GLEngine/GL/GL.h"

#include "GPhysicsObject.h"
#include "GSpacecraft.h"
#include "GBossRandomShooter.h"
#include "GBossShooter.h"

class GBoss : public GPhysicsObject
{
public:
	GConstructor(GBoss)
		: GSuperClassInitializer(GPhysicsObject)
	{

	}

	~GBoss()
	{

	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		auto spacecraft = GCreate(GSpacecraft);
		auto randomShooter = GCreate(GBossRandomShooter);
		auto shooter = GCreate(GBossShooter);

		this->AddChild(spacecraft);
		this->world->AddChildren({ randomShooter, shooter });

		spacecraft->Initialize();
		randomShooter->Initialize();
		shooter->Initialize();

		randomShooter->SetName("BossRandomShooter");
		shooter->SetName("BossShooter");

		randomShooter->SetSpeed(5.0f);
		shooter->SetSpeed(15.0f);

		randomShooter->SetMaterialType("Emerald");
		shooter->SetMaterialType("Pearl");

		this->spacecraft = spacecraft;
		this->randomShooter = randomShooter;
		this->shooter = shooter;

		auto scene = this->GetScene();

		if (scene)
		{
			this->SetBody(scene->GetPhysics()->CreateRigidBody(this->GetTransform()));
			this->collisionShape = scene->GetPhysics()->CreateBoxShape(glm::vec3(3.0f, 0.4f, 4.0f));
			this->collider = this->GetBody()->addCollider(this->collisionShape, GLPhysicsTransform());

			this->GetBody()->setType(GLBodyType::KINEMATIC);
		}
	}

	void Update(float deltaTime) override
	{
		GPhysicsObject::Update(deltaTime);

		auto transform = this->GetTransform();

		this->currentRandomShootCooldown -= deltaTime;
		this->currentShotCooldown -= deltaTime;

		auto position = transform->GetPosition();
		auto playerDirection = glm::normalize(this->playerPosition - position);

		if (this->currentRandomShootCooldown < 0.0f)
		{
			this->currentRandomShootCooldown = this->randomShootCooldown;

			this->randomShooter->Shoot(position, playerDirection);
		}

		if (this->currentShotCooldown < 0.0f)
		{
			this->currentShotCooldown = this->shootCooldown;

			this->shooter->Shoot(position, playerDirection);
		}

		this->UpdateBody();
	}

	GLGameObject* GetWorld()
	{
		return this->world;
	}

	void SetWorld(GLGameObject* world)
	{
		this->world = world;
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

	glm::vec3 GetPlayerPosition()
	{
		return this->playerPosition;
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

	void SetPlayerPosition(const glm::vec3& playerPosition)
	{
		this->playerPosition = playerPosition;
	}

private:

	float hp = 10000.0f;
	float maxHP = 10000.0f;

	float atk = 25.0f;

	float currentRandomShootCooldown = 0.1f;
	float currentShotCooldown = 0.8f;
	float randomShootCooldown = 0.1f;
	float shootCooldown = 0.8f;

	glm::vec3 playerPosition = glm::vec3(0.0f);

	GLGameObject* world = nullptr;
	GLSharedPtr<GSpacecraft> spacecraft = nullptr;
	GLSharedPtr<GBossRandomShooter> randomShooter = nullptr;
	GLSharedPtr<GBossShooter> shooter = nullptr;

	GLBoxShape* collisionShape;
	GLCollider* collider;
};