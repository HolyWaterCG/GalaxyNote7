#pragma once

#include "GLEngine/GL/GL.h"

#include "GGameStage.h"
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

    void Reset()
    {
        this->ClearChildren();

        if (this->stageType == EGameStage::Dodge)
        {
            this->stage = GCreate(GDodgeStage);
        }
        else if (this->stageType == EGameStage::Boss)
        {
            this->stage = GCreate(GBossStage);
        }

        this->AddChild(this->stage);
        this->stage->Initialize();
    }

    void Update(float deltaTime) override
    {
        GLGameObject::Update(deltaTime);

        if (this->stageType == EGameStage::Dodge)
        {
            if (this->stage->IsEnded())
            {
                this->stageType = EGameStage::Boss;
                this->Reset();
            }
        }
        else if (this->stageType == EGameStage::Boss)
        {
            if (this->stage->IsEnded())
            {
                ++round;
                this->stageType = EGameStage::Dodge;
                this->Reset();
            }
        }
    }

private:
    GLSharedPtr<GGameStage> stage;

    int round = 1;
    EGameStage stageType = EGameStage::Dodge;    
};