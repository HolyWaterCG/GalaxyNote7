#pragma once

#include "GLEngine/GL/GL.h"

class GHPBar : public GLGameObject
{
public:
    GConstructor(GHPBar)
        : GSuperClassInitializer(GLGameObject) { }

    ~GHPBar()
    {

    }

    void Initialize() override
    {
        GLGameObject::Initialize();

        auto hpBar = GCreate(GRectangle, GLColor(0.8f, 0.8f, 0.8f));
        auto currentHP = GCreate(GRectangle, GLColor(1.0f, 0.0f, 0.0f));

        this->AddChildren({ currentHP, hpBar });

        hpBar->Initialize();
        currentHP->Initialize();

        hpBar->GetMeshRenderer()->GetMaterial()->SetShader(GLCreate<GLBasicShader>());
        currentHP->GetMeshRenderer()->GetMaterial()->SetShader(GLCreate<GLBasicShader>());

        hpBar->SetLayer("UI");
        currentHP->SetLayer("UI");

        auto hpBarTransform = hpBar->GetTransform();
        hpBarTransform->SetLocalScale(1.0f, 0.025f, 0.0f);

        auto currentHPTransform = currentHP->GetTransform();
        currentHPTransform->SetLocalScale(1.0f, 0.025f, 0.0f);

        this->hpBar = hpBar;
        this->currentHP = currentHP;
    }

    float GetHPRatio()
    {
        return this->hpRatio;
    }

    void SetHPRatio(float hpRatio)
    {
        this->hpRatio = hpRatio;
    }

    void Update(float deltaTime) override
    {
        GLGameObject::Update(deltaTime);

        auto currentHPTransform = this->currentHP->GetTransform();

        currentHPTransform->LocalPosition.x = (this->hpRatio - 1.0f) / 2.0f;
        currentHPTransform->SetLocalScale(this->hpRatio, 0.025f, 0.0f);
    }

private:
    float hpRatio = 1.0f;

    GLSharedPtr<GLGameObject> hpBar;
    GLSharedPtr<GLGameObject> currentHP;
};

class GPlayerUI : public GLGameObject
{
public:
    GConstructor(GPlayerUI)
        : GSuperClassInitializer(GLGameObject) { }

    ~GPlayerUI()
    {

    }

    void Initialize() override
    {
        GLGameObject::Initialize();

        auto playerHPBar = GCreate(GHPBar);
        auto bossHPBar = GCreate(GHPBar);

        this->AddChildren({ playerHPBar, bossHPBar });

        playerHPBar->Initialize();
        bossHPBar->Initialize();

        auto playerHPBarTransform = playerHPBar->GetTransform();
        auto bossHPBarTransform = bossHPBar->GetTransform();

        playerHPBarTransform->SetLocalScale(0.25f, 1.0f, 0.0f);
        playerHPBarTransform->SetLocalPosition(0.35f, -0.42f, 0.0f);

        bossHPBarTransform->SetLocalScale(0.9f, 1.2f, 0.0f);
        bossHPBarTransform->SetLocalPosition(0.0f, 0.42f, 0.0f);

        this->playerHPBar = playerHPBar;
        this->bossHPBar = bossHPBar;
    }

    void Update(float deltaTime) override
    {
        GLGameObject::Update(deltaTime);
    }

    float GetPlayerHPRatio()
    {
        return this->playerHPBar->GetHPRatio();
    }

    float GetBossHPRatio()
    {
        return this->bossHPBar->GetHPRatio();
    }

    void SetPlayerHPRatio(float hpRatio)
    {
        this->playerHPBar->SetHPRatio(hpRatio);
    }

    void SetBossHPRatio(float hpRatio)
    {
        this->bossHPBar->SetHPRatio(hpRatio);
    }

private:
    GLSharedPtr<GHPBar> playerHPBar;
    GLSharedPtr<GHPBar> bossHPBar;
};