#pragma once
#include <iostream>

#include "GLEngine/GL/GL.h"

class GBullet : public GPhysicsObject
{
public:
	GConstructor(GBullet)
		: GSuperClassInitializer(GPhysicsObject)
	{

	}

	void Initialize() override
	{
		GPhysicsObject::Initialize();

		auto scene = GLGetCurrentScene();

		this->SetBody(scene->GetPhysics()->CreateRigidBody(this->GetTransform()));
		this->collisionShape = scene->GetPhysics()->CreateBoxShape(glm::vec3(0.2f));

		this->GetBody()->setType(GLBodyType::STATIC);

		auto shape = GCreate(GUVSphere);
		this->AddChild(shape);

		shape->Initialize();

		auto transform = this->GetTransform();
		transform->SetScale(0.1f, 0.1f, 0.1f);

		this->UpdateBody();

		RandMaterial(shape);
	}

	void Update(float deltaTime) override
	{
		GPhysicsObject::Update(deltaTime);

		auto transform = this->GetTransform();

		if (this->IsMoving())
		{

			if (GetTransform()->GetPosition().x >= 5.f || GetTransform()->GetPosition().x <= -5.f) 
			{
				speed.x *= dir;
			}

			//if (GetTransform()->GetPosition().y >= 5.f || GetTransform()->GetPosition().y <= -5.f)
			//{
			//	speed.y *= dir;
			//}

			if (GetTransform()->GetPosition().z >= 5.f || GetTransform()->GetPosition().z <= -5.f)
			{
				speed.z *= dir;
			}

			transform->Translate(this->speed * deltaTime);

		}

		this->UpdateBody();

	}

	bool IsMoving()
	{
		return this->bIsMoving;
	}
	void SetDir(float dir) 
	{
		this->dir = dir;
	}
	void SetMoving(bool moving)
	{
		this->bIsMoving = moving;
	}

	glm::vec3 GetSpeed()
	{
		return this->speed;
	}

	void SetSpeed(glm::vec3 speed)
	{
		this->speed = speed;
	}

private:
	glm::vec3 speed = glm::vec3(Rand3v(0.1f, 1.f, 0.f, 0.f, 0.1f, 1.f)); //1라운드
	//glm::vec3 speed = glm::vec3(Rand3v(0.1f, 1.5f, 0.f, 0.f, 0.1f, 1.5f)); //2라운드
	bool bIsMoving = true;
	float dir = -1.f;

	GLBoxShape* collisionShape;
};

class GBulletCnt : public GLGameObject
{
public:
	GConstructor(GBulletCnt)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override
	{
		for (int i = 0; i < this->BulletCount; i++) {

			auto bullet = GCreate(GBullet);

			this->AddChild(bullet);
		
			bullet->Initialize();

			auto bulletTransform = bullet->GetTransform();
			bulletTransform->SetPosition(Rand3v(-5.f, 5.f, 0.f, 0.f, -5.f, 5.f));
			bullet->UpdateBody();
		}
	}

	void Update(GLfloat deltaTime) override
	{
		GLGameObject::Update(deltaTime);
	}

private:
	int BulletCount = 100; //1라운드
	//int BulletCount = 130; //3라운드
};