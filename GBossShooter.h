#pragma once

#include "GLEngine/GL/GL.h"

#include "GBBullet.h"
#include "GBulletShooter.h"

class GBossShooter : public GBulletShooter
{
public:
    GConstructor(GBossShooter)
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