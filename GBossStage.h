#pragma once

#include "GLEngine/GL/GL.h"

#include "Helpers.h"
#include "GSkybox.h"
#include "GPointLight.h"
#include "GDirectionalLight.h"
#include "GBPlayer.h"
#include "GBoss.h"
#include "GPlayerUI.h"

class GBossStage : public GLGameObject
{
public:
	GConstructor(GBossStage)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override
	{
		this->Reset();
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		this->boss->SetPlayerPosition(this->player->GetTransform()->GetPosition());

		auto& playerLeftBullets = this->playerLeftShooter->GetBullets();
		auto& playerRightBullets = this->playerRightShooter->GetBullets();

		auto& bossRandomBullets = this->bossRandomShooter->GetBullets();
		auto& bossBullets = this->bossShooter->GetBullets();

		for (int i = 0; i < playerLeftBullets.size(); ++i)
		{
			auto bullet = playerLeftBullets[i];
			if (bullet->GetBody()->testAABBOverlap(this->boss->GetBody()->getAABB()))
			{
				this->boss->SetHP(this->boss->GetHP() - this->player->GetAtk());
				this->playerLeftShooter->RemoveBullet(i);
				break;
			}
		}

		for (int i = 0; i < playerRightBullets.size(); ++i)
		{
			auto bullet = playerRightBullets[i];
			if (bullet->GetBody()->testAABBOverlap(this->boss->GetBody()->getAABB()))
			{
				this->boss->SetHP(this->boss->GetHP() - this->player->GetAtk());
				this->playerRightShooter->RemoveBullet(i);
				break;
			}
		}

		for (int i = 0; i < bossRandomBullets.size(); ++i)
		{
			auto bullet = bossRandomBullets[i];
			if (bullet->GetBody()->testAABBOverlap(this->player->GetBody()->getAABB()))
			{
				this->player->SetHP(this->player->GetHP() - this->boss->GetAtk());
				this->bossRandomShooter->RemoveBullet(i);
				break;
			}
		}

		for (int i = 0; i < bossBullets.size(); ++i)
		{
			auto bullet = bossBullets[i];
			if (bullet->GetBody()->testAABBOverlap(this->player->GetBody()->getAABB()))
			{
				this->player->SetHP(this->player->GetHP() - this->boss->GetAtk());
				this->bossShooter->RemoveBullet(i);
				break;
			}
		}

		if (this->player->GetHP() <= 0.0f)
		{
			this->Reset();
			return;
		}

		this->playerUI->SetPlayerHPRatio(this->player->GetHP() / this->player->GetMaxHP());
		this->playerUI->SetBossHPRatio(this->boss->GetHP() / this->boss->GetMaxHP());
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "Escape")
		{
			GLMain::GetInstance()->Exit();
		}
	}

	void Reset()
	{
		this->ClearChildren();

		auto directionalLight = GCreate(GDirectionalLight, glm::vec3(0.5f), glm::vec3(0.5f), glm::vec3(0.6f), glm::vec3(-1.0f, -1.0f, -1.0f));
		auto skybox = GCreate(GSkybox);

		auto player = GCreate(GBPlayer);
		auto boss = GCreate(GBoss);

		auto playerUI = GCreate(GPlayerUI);

		this->AddChildren({ skybox, directionalLight, player, boss });

		player->SetWorld(this);
		boss->SetWorld(this);

		skybox->Initialize();
		directionalLight->Initialize();
		player->Initialize();
		boss->Initialize();

		skybox->GetTransform()->SetLocalScale(glm::vec3(50.0f));
		player->GetTransform()->SetPosition(0.0f, 0.0f, 10.0f);
		boss->GetTransform()->SetPosition(0.0f, 0.0f, -15.0f);

		player->UpdateBody();
		boss->UpdateBody();

		player->GetUICamera()->AddChild(playerUI);
		playerUI->Initialize();

		playerUI->GetTransform()->SetLocalPosition(0.0f, 0.0f, -0.5f);

		this->player = player;
		this->playerUI = playerUI;
		this->playerLeftShooter = std::dynamic_pointer_cast<GPlayerShooter>(this->GetChild("PlayerLeftShooter"));
		this->playerRightShooter = std::dynamic_pointer_cast<GPlayerShooter>(this->GetChild("PlayerRightShooter"));

		this->bossRandomShooter = std::dynamic_pointer_cast<GBossRandomShooter>(this->GetChild("BossRandomShooter"));
		this->bossShooter = std::dynamic_pointer_cast<GBossShooter>(this->GetChild("BossShooter"));

		this->boss = boss;
	}

private:
	GLSharedPtr<GBPlayer> player = nullptr;
	GLSharedPtr<GPlayerUI> playerUI = nullptr;
	GLSharedPtr<GPlayerShooter> playerLeftShooter = nullptr;
	GLSharedPtr<GPlayerShooter> playerRightShooter = nullptr;
	
	GLSharedPtr<GBossRandomShooter> bossRandomShooter = nullptr;
	GLSharedPtr<GBossShooter> bossShooter = nullptr;

	GLSharedPtr<GBoss> boss = nullptr;
};