#pragma once

#include "GLEngine/GL/GL.h"

#include "GBoundary.h" 
#include "GPlayer.h"
#include "Helpers.h"
#include "GCameraController.h"
#include "GPointLightController.h"
#include "GBullet.h"
#include "GBox.h"

class GDodgeStage : public GLGameObject
{

private:

	std::shared_ptr<GCameraController> cameraController;
	std::shared_ptr<GPointLightController> lightContoller;
	std::shared_ptr<GBulletCnt> bulletCnt;
	std::shared_ptr<GPlayer> hero;
	std::shared_ptr<GBoxItem> itemBox;
	std::shared_ptr<GBoundary> Line;
	std::shared_ptr<GBullet> ballSpeed;

public:
	GConstructor(GDodgeStage)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override
	{
		this->Reset();
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "q" || key == "Q")
		{
			GLMain::GetInstance()->Exit();
		}
    	else if (key == "Enter")
		{
			this->SetStarted(true);
		}
	}

	void ChangeStage(int round)
	{

	}
	
	void Reset()
	{
		this->ClearChildren();

		cameraController = GCreate(GCameraController); //카메라
		lightContoller = GCreate(GPointLightController, glm::vec3(2.5f), glm::vec3(2.5f), glm::vec3(2.5f), 1.0f, 0.22f, 0.20f); //조명
		bulletCnt = GCreate(GBulletCnt); //공 갯수
		hero = GCreate(GPlayer); // 플레이어
		itemBox = GCreate(GBoxItem); //박스
		Line = GCreate(GBoundary); // 경계선 + 뒷 매핑

		this->AddChildren({ cameraController, lightContoller, bulletCnt, itemBox, hero, Line });

		cameraController->Initialize();
		lightContoller->Initialize();
		bulletCnt->Initialize();
		itemBox->Initialize();
		hero->Initialize();
		Line->Initialize();

		cameraController->GetTransform()->SetPosition(0.f, 5.f, 0.f);
		lightContoller->GetTransform()->SetPosition(0.0f, 10.0f, 0.0f);
		hero->GetTransform()->SetPosition(0.0f, 0.0f, 0.0f);

		this->itemBoxCount = 0;
		this->SetStarted(false);
		this->SetEnded(false);
	}

	void Reset(int round)
	{
		this->Reset();

		if (round == 2)
		{
			bulletCnt->ChangeStage();
			itemBox->SetItemBox(3);
			itemBox->Initialize();
		}
	}

	void Update(float deltaTime) override
	{
		if (!this->IsStarted())
		{
			return;
		}

		GLGameObject::Update(deltaTime);

		if (this->itemBoxCount >= 3)
		{
			this->SetEnded(true);
		}

		if (this->IsEnded())
		{
			return;
		}

		auto playerPosition = this->hero->GetTransform()->GetPosition();

		auto& bullets = this->bulletCnt->GetBullets();
		for (auto bullet : bullets)
		{
			auto bulletPosition = bullet->GetTransform()->GetPosition();

			auto distance = glm::length2(bulletPosition - playerPosition);

			if (distance <= 0.02f)
			{
				this->Reset();
				return;
			}
		}

		for (int i = 0; i < 3 - itemBoxCount; ++i)
		{
			auto box = this->itemBox->GetChild(i);
			auto boxPosition = box->GetTransform()->GetPosition();

			auto distance = glm::length2(boxPosition - playerPosition);

			if (distance <= 0.05f)
			{
				++this->itemBoxCount;
				this->itemBox->RemoveChild(box);
				break;
			}
		}
	}

	bool IsStarted()
	{
		return this->bIsStarted;
	}

	void SetStarted(bool isStarted)
	{
		this->bIsStarted = isStarted;
	}

	bool IsEnded()
	{
		return this->bIsEnded;
	}

	void SetEnded(bool isEnded)
	{
		this->bIsEnded = isEnded;
	}

private:

	bool bIsStarted = false;
	bool bIsEnded = false;

	int itemBoxCount = 0;
};