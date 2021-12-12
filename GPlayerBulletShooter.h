#pragma once

#include "GLEngine/GL/GL.h"

#include "GBullet.h"
#include "GBulletShooter.h"

class GPlayerShooter : public GBulletShooter
{
public:
    GConstructor(GPlayerShooter)
        : GSuperClassInitializer(GBulletShooter)
    {

    }

    void Initialize() override
    {
        GBulletShooter::Initialize();
    }

    void Shoot(const glm::vec3& position, const glm::vec3& direction)
    {
        auto bullet = this->CreateBullet();

        auto bulletTransform = bullet->GetTransform();
        bulletTransform->SetPosition(position);

        bullet->SetSpeed(direction * this->GetSpeed());
        bullet->UpdateBody();
    }
};