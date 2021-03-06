#pragma once

#include <vector>

#include "GLMemoryHelpers.h"
#include "GLShader.h"
#include "GLTransform.h"
#include "GLMesh.h"
#include "GLMeshRenderer.h"
#include "GLComponent.h"

class GLScene;

class GLGameObject
{
public:
	GLGameObject()
	{
		this->transform = GLCreate<GLTransform>(this);
		this->meshRenderer = GLCreate<GLMeshRenderer>();

		this->SetParent(nullptr);
	}

	GLGameObject(const GLSharedPtr<GLTransform>& parent)
	{
		this->transform = GLCreate<GLTransform>(this);
		this->meshRenderer = GLCreate<GLMeshRenderer>();

		this->SetParent(parent);
	}
	
	virtual ~GLGameObject()
	{
		this->scene = nullptr;
		this->transform = nullptr;
		this->meshRenderer = nullptr;
	}

	virtual void Initialize()
	{
		assert(this->bInitialized == false);

		this->bInitialized = true;
	}

	virtual void OnKeyDown(const std::string& key, int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnKeyDown(key, x, y);
		}
	}

	virtual void OnKeyUp(const std::string& key, int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnKeyUp(key, x, y);
		}
	}

	virtual void OnMouseDown(int button,int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnMouseDown(button, x, y);
		}
	}

	virtual void OnMouseUp(int button, int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnMouseUp(button, x, y);
		}
	}

	virtual void OnMouseWheel(int wheel, int direction, int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnMouseWheel(wheel, direction, x, y);
		}
	}

	virtual void OnMouseMove(int button, int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnMouseMove(button, x, y);
		}
	}

	virtual void OnMouseLeave()
	{
		for (auto& child : this->children)
		{
			child->OnMouseLeave();
		}
	}

	virtual void OnMouseEnter()
	{
		for (auto& child : this->children)
		{
			child->OnMouseEnter();
		}
	}

	virtual void Update(GLfloat deltaTime)
	{
		this->transform->Update();

		for (auto& child : this->children)
		{
			child->Update(deltaTime);
		}
	};

	virtual void Render(const std::string& layer, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition,
		        const std::vector<GLSharedPtr<GLLight>>& lights)
	{
		if (this->transform == nullptr)
		{
			return;
		}

		this->transform->Update();

		if (!this->bVisible)
		{
			return;
		}

		for (auto& child : this->children)
		{
			child->Render(layer, viewMatrix, projectionMatrix, cameraPosition, lights);
		}

		if (layer == this->layer && this->meshRenderer != nullptr)
		{
			this->meshRenderer->Render(this->transform->LocalToWorldMatrix, viewMatrix, projectionMatrix, cameraPosition, lights);
		}
	}

	GLSharedPtr<GLTransform> GetParent()
	{
		return this->transform->Parent;
	}

	void SetParent(const GLSharedPtr<GLTransform>& parent)
	{
		if (this->transform != nullptr)
		{
			this->transform->SetParent(parent);
		}

		if (parent != nullptr)
		{
			this->scene = parent->GameObject->scene;
		}
	}

	GLSharedPtr<GLGameObject> GetChild(int i)
	{
		assert(i >= 0 && i < this->children.size());

		return this->children.at(i);
	}

	GLSharedPtr<GLGameObject> GetChild(const std::string& name)
	{
		for (auto& child : this->children)
		{
			if (name == child->GetName())
			{
				return child;
			}
		}
		return nullptr;
	}

	void AddChild(const GLSharedPtr<GLGameObject>& child)
	{
		assert(child != nullptr);

		child->SetParent(this->transform);

		this->children.push_back(child);
	}

	void AddChildren(const std::initializer_list<GLSharedPtr<GLGameObject>>& children)
	{
		for (const auto& child : children)
		{
			this->AddChild(child);
		}
	}

	void RemoveChild(const GLSharedPtr<GLGameObject>& child)
	{
		assert(child != nullptr);

		child->SetParent(nullptr);

		auto position = std::find(this->children.begin(), this->children.end(), child);
		
		if (position != this->children.end())
		{
			this->children.erase(position);
		}
	}

	void RemoveChildren(const std::initializer_list<GLSharedPtr<GLGameObject>>& children)
	{
		for (const auto& child : children)
		{
			this->RemoveChild(child);
		}
	}

	void ClearChildren()
	{
		this->children.clear();
	}

	std::string GetName()
	{
		return this->name;
	}

	void SetName(const std::string& name)
	{
		this->name = name;
	}
	
	std::string GetLayer()
	{
		return this->layer;
	}

	void SetLayer(const std::string& layer)
	{
		this->layer = layer;
	}

	bool IsVisible()
	{
		return this->bVisible;
	}

	void SetVisible(bool bVisible)
	{
		this->bVisible = bVisible;
	}

	GLSharedPtr<GLScene> GetScene()
	{
		return this->scene;
	}

	GLSharedPtr<GLMeshRenderer> GetMeshRenderer()
	{
		return this->meshRenderer;
	}

	GLSharedPtr<GLTransform> GetTransform()
	{
		return this->transform;
	}

	void SetScene(const GLSharedPtr<GLScene>& scene)
	{
		this->scene = scene;
	}

	void SetMeshRenderer(const GLSharedPtr<GLMeshRenderer>& meshRenderer)
	{
		this->meshRenderer = meshRenderer;
	}

	void SetTransform(const GLSharedPtr<GLTransform>& transform)
	{
		this->transform = transform;
	}

private:
	GLSharedPtr<GLScene> scene = nullptr;
	GLSharedPtr<GLTransform> transform = nullptr;
	GLSharedPtr<GLMeshRenderer> meshRenderer = nullptr;

	std::vector<GLSharedPtr<GLComponent>> components;
	std::vector<GLSharedPtr<GLGameObject>> children;

	bool bVisible = true;

	std::string name = "";
	std::string layer = "Default";

	bool bInitialized = false;
};

#define GConstructor(CLASSNAME, ...) \
CLASSNAME(const GLSharedPtr<GLTransform>& parent, ## __VA_ARGS__)

#define GSuperClassInitializer(SUPERCLASSNAME, ...) \
SUPERCLASSNAME(parent, ## __VA_ARGS__)

#define GCreate(CLASSNAME, ...) \
GLCreate<CLASSNAME>(nullptr, ## __VA_ARGS__)

#define GCreateChild(CLASSNAME, ...) \
GLCreate<CLASSNAME>(this->Transform, ## __VA_ARGS__)

#define GCreateAndAddChild(CLASSNAME, ...) \
this->AddChild(GCreate(CLASSNAME, ## __VA_ARGS__)) \

#define GCreateChildFor(PARENTGAMEOBJECT, CLASSNAME, ...) \
GLCreate<CLASSNAME>(((PARENTGAMEOBJECT))->Transform, ## __VA_ARGS__)

#define GCreateAndAddChildFor(PARENTGAMEOBJECT, CLASSNAME, ...) \
((PARENTGAMEOBJECT))->AddChild(GCreateChildFor(PARENTGAMEOBJECT, CLASSNAME), ## __VA_ARGS__) \

#define GAddChild(CHILDGAMEOBJECT) \
this->AddChild(((CHILDGAMEOBJECT)))

#define GAddChildren(...) \
this->AddChildren(__VA_ARGS__)

#define GAddChildTo(PARENTGAMEOBJECT, CHILDGAMEOBJECT) \
((PARENTGAMEOBJECT))->AddChild(((CHILDGAMEOBJECT)))

#define GAddChildrenTo(PARENTGAMEOBJECT, ...) \
((PARENTGAMEOBJECT))->AddChildren(__VA_ARGS__)

