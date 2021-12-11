#pragma once

#include "GLEngine/GL/GL.h"

#include "GBoundary.h" 
#include "GPlayer.h"
#include "Helpers.h"
#include "GCameraController.h"
#include "GPointLightController.h"
#include "GBullet.h"
#include "GBox.h"
#include "GPhysicsObject.h"

class GWorld : public GLGameObject
{

private:

	std::shared_ptr<GCameraController> cameraController;
	std::shared_ptr<GPointLightController> lightContoller;
	std::shared_ptr<GBulletCnt> bullet;
	std::shared_ptr<GPlayer> hero;
	std::shared_ptr<GBoxItem> itemBox;
	std::shared_ptr<GBoundary> Line;
	std::shared_ptr<GBullet> ballSpeed;

public:
	GConstructor(GWorld)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override
	{
		cameraController = GCreate(GCameraController); //ī�޶�
		lightContoller = GCreate(GPointLightController, glm::vec3(2.5f), glm::vec3(2.5f), glm::vec3(2.5f), 1.0f, 0.22f, 0.20f); //����
		bullet = GCreate(GBulletCnt); //�� ����
		hero = GCreate(GPlayer); // �÷��̾�
		itemBox = GCreate(GBoxItem); //�ڽ�
		Line = GCreate(GBoundary); // ��輱 + �� ����

		this->AddChildren({ cameraController, lightContoller, bullet, itemBox, hero, Line });

		cameraController->Initialize();
		lightContoller->Initialize();
		bullet->Initialize();
		itemBox->Initialize();
		hero->Initialize();
		Line->Initialize();

		cameraController->GetTransform()->SetPosition(0.f, 5.f, 0.f);
		lightContoller->GetTransform()->SetPosition(0.0f, 10.0f, 0.0f);
		hero->GetTransform()->SetPosition(0.0f, 0.0f, 0.0f);
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "q" || key == "Q")
		{
			GLMain::GetInstance()->Exit();
		}

		if (key == "2") // 2���嶧 �߰��Ǵ¿�� 
		{

			bullet->ChageStage();
			itemBox->SetItemBox(3);
			itemBox->Initialize();

		}
	}



	void Update(float deltaTime) override
	{

		GLGameObject::Update(deltaTime);

	}
};