#pragma once

#include "GLEngine/GL/GL.h"

#include "GBullet.h"
#include "GBulletShooter.h"

class GBossRandomShooter : public GBulletShooter
{
public:
    GConstructor(GBossRandomShooter)
        : GSuperClassInitializer(GBulletShooter)
    {

    }

    void Initialize() override
    {
        GBulletShooter::Initialize();
    }

    void Shoot(const glm::vec3& position, const glm::vec3& direction)
    {
        auto randomDirection = glm::normalize(direction) + Rand3v(-0.1f, 0.1f, -0.1f, 0.1f, -0.1f, 0.1f);

        auto bullet = this->CreateBullet();

        auto bulletTransform = bullet->GetTransform();
        bulletTransform->SetPosition(position);

        bullet->SetSpeed(randomDirection * this->GetSpeed());
        bullet->UpdateBody();
    }
};