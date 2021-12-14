#pragma once

#include "GLEngine/GL/GL.h"

#include "GDodgeStage.h"
#include "GBossStage.h"

enum class EGameStage
{
    Dodge = 1,
    Boss = 2
};

class GGameWorld : public GLGameObject
{
public:
    GConstructor(GGameWorld)
        : GSuperClassInitializer(GLGameObject)
    {

    }

    void Initialize() override
    {
        GLGameObject::Initialize();

        this->Reset();
    }

    void ResetDodge()
    {
        this->ClearChildren();

        this->dodgeStage = GCreate(GDodgeStage);
        this->bossStage = nullptr;

        this->AddChild(this->dodgeStage);

        this->dodgeStage->Initialize();
    }

    void ResetBoss()
    {
        this->ClearChildren();

        this->dodgeStage = nullptr;
        this->bossStage = GCreate(GBossStage);

        this->AddChild(this->bossStage);

        this->bossStage->Initialize();
    }

    void Reset()
    {
        if (this->stageType == EGameStage::Dodge)
        {
            this->ResetDodge();
        }
        else if (this->stageType == EGameStage::Boss)
        {
            this->ResetBoss();
        }
    }

    void Update(float deltaTime) override
    {
        GLGameObject::Update(deltaTime);

        if (this->stageType == EGameStage::Dodge)
        {
            if (this->dodgeStage->IsEnded())
            {
                this->stageType = EGameStage::Boss;
                this->Reset();
            }
        }
        else if (this->stageType == EGameStage::Boss)
        {
            if (this->bossStage->IsEnded())
            {
                ++round;
                this->stageType = EGameStage::Dodge;
                this->Reset();
            }
        }
    }

private:
    GLSharedPtr<GDodgeStage> dodgeStage;
    GLSharedPtr<GBossStage> bossStage;

    int round = 1;
    EGameStage stageType = EGameStage::Dodge;    
};