#pragma once

#include "GPhysicsObject.h"

class GBBullet : public GPhysicsObject
{
public:
    GConstructor(GBBullet)
        : GSuperClassInitializer(GPhysicsObject)
    {

    }

    void Initialize() override
    {
        GPhysicsObject::Initialize();

        auto mesh = GLMeshLoader::Load("resources/Sphere.obj");

        auto meshRenderer = this->GetMeshRenderer();

        meshRenderer->SetMesh(mesh);

        this->GetTransform()->SetLocalScale(glm::vec3(0.05f, 0.05f, 0.05f));

        auto scene = this->GetScene();

        if (scene)
        {
            this->SetBody(scene->GetPhysics()->CreateRigidBody(this->GetTransform()));
            this->collisionShape = scene->GetPhysics()->CreateBoxShape(glm::vec3(0.05f, 0.05f, 0.05f));
            this->collider = this->GetBody()->addCollider(this->collisionShape, GLPhysicsTransform());

            this->GetBody()->setType(GLBodyType::KINEMATIC);
            this->collider->setCollisionCategoryBits(0x1);
        }
    }

    void Update(float deltaTime) override
    {
        GPhysicsObject::Update(deltaTime);

        this->GetTransform()->Translate(this->speed * deltaTime);

        this->UpdateBody();
    }

    glm::vec3 GetSpeed()
    {
        return this->speed;
    }

    void SetSpeed(const glm::vec3& speed)
    {
        this->speed = speed;
    }

private:
    glm::vec3 speed = glm::vec3(0.0f);

    GLBoxShape* collisionShape;
    GLCollider* collider;
};