#pragma once

#include "GLEngine/GL/GL.h"

class GPhysicsObject : public GLGameObject
{
public:
	GConstructor(GPhysicsObject)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	virtual ~GPhysicsObject()
	{
		auto scene = GLGetCurrentScene();

		if (this->rigidBody != nullptr)
		{
			scene->GetPhysics()->DestroyRigidBody(this->rigidBody);
			this->rigidBody = nullptr;
		}
	}

	void Initialize() override
	{
		GLGameObject::Initialize();
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		this->UpdateTransform();
	}

	void UpdateTransform()
	{
		auto scene = GLGetCurrentScene();

		if (scene)
		{
			scene->GetPhysics()->UpdateTransformFromRigidBody(this->GetTransform(), this->rigidBody);
		}
	}

	void UpdateBody()
	{
		auto scene = GLGetCurrentScene();

		if (scene)
		{
			scene->GetPhysics()->UpdateRigidBody(this->rigidBody, this->GetTransform());
		}
	}

	reactphysics3d::RigidBody* GetBody()
	{
		return this->rigidBody;
	}

	void SetBody(reactphysics3d::RigidBody* rigidBody)
	{
		this->rigidBody = rigidBody;
	}

private:
	reactphysics3d::RigidBody* rigidBody = nullptr;
};