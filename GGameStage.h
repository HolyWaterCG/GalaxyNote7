#pragma once

#include "GLEngine/GL/GL.h"

class GGameStage : public GLGameObject
{
public:
    GConstructor(GGameStage)
        : GSuperClassInitializer(GLGameObject)
    {

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
};