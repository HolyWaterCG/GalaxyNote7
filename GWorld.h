#pragma once

#include "GLEngine/GL/GL.h"

#include "GBoundary.h"
#include "GPlayer.h"
#include "Helpers.h"
#include "GCameraController.h"
#include "GPointLightController.h"
#include "GBullet.h"
#include "GBox.h"
#include "GSolarSystem.h"
#include "GFractalPhyramid.h"
#include "GSnowFallEffect.h"

class GWorld : public GLGameObject
{
public:
	GConstructor(GWorld)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override
	{
		auto cameraController = GCreate(GCameraController);
		auto lightContoller = GCreate(GPointLightController, glm::vec3(1.3f), glm::vec3(1.3f), glm::vec3(1.3f), 1.0f, 0.22f, 0.20f);
		this->bulletCnt = GCreate(GBulletCnt);
		auto Object = GCreate(GBoxItem);
		this->hero = GCreate(GPlayer);
		auto Line = GCreate(GBoundary);

		this->AddChildren({ cameraController, lightContoller, bulletCnt, Object, hero, Line});

		cameraController->Initialize();
		lightContoller->Initialize();
		bulletCnt->Initialize();
		Object->Initialize();
		hero->Initialize();
		Line->Initialize();

		cameraController->GetTransform()->SetPosition(0.f, 5.f, 0.f);
		lightContoller->GetTransform()->SetPosition(0.0f, 5.0f, 0.0f);
		hero->GetTransform()->SetPosition(0.0f, 0.0f, 0.0f);

	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "q" || key == "Q")
		{
			GLMain::GetInstance()->Exit();
		}
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);
	}

	GLSharedPtr<GBulletCnt> bulletCnt;
	GLSharedPtr<GPlayer> hero;
};