#pragma once

#include "GLEngine/GL/GL.h"

class GBullet : public GLGameObject
{
public:
	GConstructor(GBullet)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		auto transform = this->GetTransform();
		transform->SetScale(0.05f, 0.05f, 0.05f);

		auto mesh = GLMeshLoader::Load("resources/Sphere.obj");

		auto meshRenderer = this->GetMeshRenderer();
		meshRenderer->SetMesh(mesh);

		RandMaterial(this);
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

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

private:
	glm::vec3 speed = glm::vec3(Rand3v(-0.1f, 1.2f, 0.f, 0.f, -0.1f, 1.2f)); //1¶ó¿îµå
	bool bIsMoving = true;
	float dir = -1.f;

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

			auto bullet = GCreate(GBullet);

			this->AddChild(bullet);
			this->bullets.push_back(bullet);

			bullet->Initialize();

			auto bulletTransform = bullet->GetTransform();
			bulletTransform->SetPosition(Rand3v(-4.5f, 4.5f, 0.f, 0.f, -4.5f, 4.5f));
		}
	}

	void BulletInit(int size)
	{
		for (int i = BulletCount; i < this->BulletCount + size; i++)
		{
		    auto bullet = GCreate(GBullet);

			this->AddChild(bullet);
			this->bullets.push_back(bullet);

			bullet->Initialize();

			auto bulletTransform = bullet->GetTransform();
			bulletTransform->SetPosition(Rand3v(-4.5f, 4.5f, 0.f, 0.f, -4.5f, 4.5f));
		}
	}

	void ChangeStage()
	{
		BulletCnt(20);
		SetSpeed(glm::vec3(0.3f, 0.f, 0.3f));
	}

	void BulletCnt(int BulletCnt)
	{
		BulletInit(BulletCnt);
		this->BulletCount = BulletCnt;
		this->MaxBulletCount += BulletCnt;
	}

	void SetSpeed(glm::vec3 speed)
	{
		for (int i = 0; i < MaxBulletCount; ++i)
		{
			bullets[i]->SetSpeed(speed);
		}
	}

	void Update(GLfloat deltaTime) override
	{
		GLGameObject::Update(deltaTime);
	}

	std::vector<GLSharedPtr<GBullet>>& GetBullets()
	{
		return this->bullets;
	}

private:
	int BulletCount = 50;
	int MaxBulletCount = BulletCount;
	std::vector<GLSharedPtr<GBullet>> bullets;
};