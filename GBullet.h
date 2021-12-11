#pragma once

#include "GLEngine/GL/GL.h"

class GBullet : public GUVSphere
{
public:
	GConstructor(GBullet)
		: GSuperClassInitializer(GUVSphere)
	{

	}

	void Initialize() override
	{
		GUVSphere::Initialize();

		/*auto scene = GLGetCurrentScene();

		this->SetBody(scene->GetPhysics()->CreateRigidBody(this->GetTransform()));
		this->collisionShape = scene->GetPhysics()->CreateBoxShape(glm::vec3(0.2f));

		this->GetBody()->setType(GLBodyType::STATIC);*/

		auto shape = GCreate(GUVSphere);
		this->AddChild(shape);

		shape->Initialize();

		auto transform = this->GetTransform();
		transform->SetScale(0.1f, 0.1f, 0.1f);

		/*this->UpdateBody();*/

		RandMaterial(shape);

	}

	void Update(float deltaTime) override
	{
		//GPhysicsObject::Update(deltaTime);

		auto transform = this->GetTransform();

		if (this->IsMoving())
		{

			if (GetTransform()->GetPosition().x >= 5.f || GetTransform()->GetPosition().x <= -5.f) 
			{
				speed.x *= dir;
			}

			if (GetTransform()->GetPosition().z >= 5.f || GetTransform()->GetPosition().z <= -5.f)
			{
				speed.z *= dir;
			}

			transform->Translate(this->speed * deltaTime);

		}

		//this->UpdateBody();

		//if (//플레이어와의 충돌이 일어났다.) {
		//	iscollison = true;
		//}
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
		this->speed += speed;
	}

	void Reset()
	{
		this->speed = glm::vec3(0.f, 0.f, 0.f);
	}

private:
	//glm::vec3 speed = glm::vec3(Rand3v(-0.1f, 1.2f, 0.f, 0.f, -0.1f, 1.2f)); //1라운드
	glm::vec3 speed = glm::vec3(Rand3v(-0.1f, 1.35f, 0.f, 0.f, -0.1f, 1.35f)); //2라운드
	bool bIsMoving = true;
	float dir = -1.f;

	//GLBoxShape* collisionShape;
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
		GLGameObject::Initialize();

		for (int i = 0; i < this->BulletCount; i++) {

			bullet[i] = GCreate(GBullet);

			this->AddChild(bullet[i]);

			bullet[i]->Initialize();

			auto bulletTransform = bullet[i]->GetTransform();
			bulletTransform->SetPosition(Rand3v(-4.5f, 4.5f, 0.f, 0.f, -4.5f, 4.5f));
			//bullet->UpdateBody();
		}
	}

	void BulletInit(int size)
	{
		for (int i = BulletCount; i < this->BulletCount + size; i++) {

			bullet[i] = GCreate(GBullet);

			this->AddChild(bullet[i]);

			bullet[i]->Initialize();

			auto bulletTransform = bullet[i]->GetTransform();
			bulletTransform->SetPosition(Rand3v(-4.5f, 4.5f, 0.f, 0.f, -4.5f, 4.5f));
		}
	}

	void ChageStage()
	{
		BulletCnt(20);
		SetSpeed(glm::vec3(0.3f, 0.f, 0.3f));
	}

	void Update(GLfloat deltaTime) override
	{
		GLGameObject::Update(deltaTime);
	}

	void BulletCnt(int BulletCnt)
	{
		BulletInit(BulletCnt);
		this->BulletCount = BulletCnt;
		this->MaxBulletCount += BulletCnt;
	}

	void Reset()
	{
		this->BulletCount = 0;
	}

	void SetSpeed(glm::vec3 speed)
	{
		for (int i = 0; i < MaxBulletCount; ++i)
		{
			bullet[i]->SetSpeed(speed);
		}
	}

private:
	int BulletCount = 100; //1라운드
	int MaxBulletCount = BulletCount;
	std::shared_ptr<GBullet> bullet[120];
};