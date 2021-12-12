#pragma once

#include "GLEngine/GL/GL.h"

#include "GBullet.h"

class GBulletShooter : public GLGameObject
{
public:
    GConstructor(GBulletShooter)
        : GSuperClassInitializer(GLGameObject)
    {

    }

    virtual void Initialize() override
    {
        GLGameObject::Initialize();
    }

    virtual void Update(float deltaTime) override
    {
        GLGameObject::Update(deltaTime);

        for (auto itr = this->bullets.begin(); itr != this->bullets.end(); ++itr)
        {
            auto bullet = *itr;
            auto bulletTransform = bullet->GetTransform();
            auto bulletPosition = bulletTransform->GetPosition();

            if (bulletPosition.x > 50.0f || bulletPosition.x < -50.0f)
            {
                this->RemoveChild(bullet);
                this->bullets.erase(itr);
                break;
            }

            if (bulletPosition.y > 50.0f || bulletPosition.y < -50.0f)
            {
                this->RemoveChild(bullet);
                this->bullets.erase(itr);
                break;
            }

            if (bulletPosition.z > 50.0f || bulletPosition.z < -50.0f)
            {
                this->RemoveChild(bullet);
                this->bullets.erase(itr);
                break;
            }
        }
    }

    virtual void Shoot(const glm::vec3& position) { };

    float GetSpeed()
    {
        return this->speed;
    }

    void SetSpeed(float speed)
    {
        this->speed = speed;
    }

    GLSharedPtr<GBullet> CreateBullet()
    {
        auto bullet = GCreate(GBullet);
        this->AddChild(bullet);
        this->bullets.push_back(bullet);

        bullet->Initialize();

        auto bulletMeshRenderer = bullet->GetMeshRenderer();
        bulletMeshRenderer->SetMaterial(GLGetPreDefinedMaterial(this->materialType));
        
        return bullet;
    }

    std::vector<GLSharedPtr<GBullet>>& GetBullets()
    {
        return this->bullets;
    }

    void RemoveBullet(int i)
    {
        assert(i >= 0 && i < this->bullets.size());

        this->RemoveChild(this->bullets[i]);
        this->bullets.erase(this->bullets.begin() + i);
    }

    std::string GetMaterialType()
    {
        return this->materialType;
    }

    void SetMaterialType(const std::string& materialType)
    {
        this->materialType = materialType;
    }

private:
    float speed = 10.0f;

    std::string materialType = "Ruby";

    std::vector<GLSharedPtr<GBullet>> bullets;
};