#pragma once

#include <string>
#include <unordered_map>

#include <gl/glm/glm.hpp>

#include "GLMemoryHelpers.h"
#include "GLColor.h"
#include "GLShader.h"
#include "GLBasicShader.h"



class GLMaterial
{
public:
	GLMaterial()
	{
		this->shader = GLCreate<GLBasicMaterialShader>();

		this->vectors["ambient"] = glm::vec3(1.0f);
		this->vectors["diffuse"] = glm::vec3(1.0f);
		this->vectors["specular"] = glm::vec3(1.0f);
		this->floats["shininess"] = 1.0f;
	}

	GLMaterial(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess)
	{
		this->shader = GLCreate<GLBasicMaterialShader>();

		this->vectors["ambient"] = ambient;
		this->vectors["diffuse"] = diffuse;
		this->vectors["specular"] = specular;
		this->floats["shininess"] = shininess;
	}

	virtual ~GLMaterial()
	{

	}

	GLSharedPtr<GLShader> GetShader()
	{
		return this->shader;
	}

	void SetShader(const GLSharedPtr<GLShader>& shader)
	{
		this->shader = shader;
	}

	void Use()
	{
		this->shader->Use();

		for (const auto& item : this->ints)
		{
			std::string name = "material." + item.first;
			if (this->shader->GetUniformLocation(name) > 0)
			{
				this->shader->SetUniform(name, item.second);
			}
		}

		for (const auto& item : this->floats)
		{
			std::string name = "material." + item.first;
			if (this->shader->GetUniformLocation(name) > 0)
			{
				this->shader->SetUniform(name, item.second);
			}
		}

		for (const auto& item : this->vectors)
		{
			std::string name = "material." + item.first;
			if (this->shader->GetUniformLocation(name) > 0)
			{
				this->shader->SetUniform(name, item.second);
			}
		}

		for (const auto& item : this->matrices)
		{
			std::string name = "material." + item.first;
			if (this->shader->GetUniformLocation(name) > 0)
			{
				this->shader->SetUniform(name, item.second);
			}
		}
	}

	int GetInt(const std::string& name)
	{
		assert(this->ints.find(name) != this->ints.end());

		return this->ints[name];
	}
	
	void SetInt(const std::string& name, int value)
	{
		this->ints[name] = value;
	}

	float GetFloat(const std::string& name)
	{
		assert(this->floats.find(name) != this->floats.end());

		return this->floats[name];
	}

	void SetFloat(const std::string& name, float value)
	{
		this->floats[name] = value;
	}

	glm::vec3 GetVector(const std::string& name)
	{
		assert(this->vectors.find(name) != this->vectors.end());

		return this->vectors[name];
	}

	void SetVector(const std::string& name, const glm::vec3& value)
	{
		this->vectors[name] = value;
	}

	glm::mat4 GetMatrix(const std::string& name)
	{
		assert(this->matrices.find(name) != this->matrices.end());

		return this->matrices[name];
	}

	void SetMatrix(const std::string & name, const glm::mat4& matrix)
	{
		this->matrices[name] = matrix;
	}

private:
	std::unordered_map<std::string, int> ints;
	std::unordered_map<std::string, float> floats;
	std::unordered_map<std::string, glm::vec3> vectors;
	std::unordered_map<std::string, glm::mat4> matrices;

	GLSharedPtr<GLShader> shader;
};

std::unordered_map<std::string, GLSharedPtr<GLMaterial>> __GLPredefinedMaterials;

GLSharedPtr<GLMaterial> GLGetPreDefinedMaterial(const std::string& materialType)
{
	if (__GLPredefinedMaterials.size() == 0)
	{
		__GLPredefinedMaterials["Emerald"] = GLCreate<GLMaterial>(glm::vec3(0.0215f, 0.1745f, 0.0215f), glm::vec3(0.07568f, 0.61424f, 0.07568f), glm::vec3(0.633f, 0.727811f, 0.633f), 0.6f);
		__GLPredefinedMaterials["Jade"] = GLCreate<GLMaterial>(glm::vec3(0.135f, 0.2225f, 0.1575f), glm::vec3(0.54f, 0.89f, 0.63f), glm::vec3(0.316228f, 0.316228f, 0.316228f), 0.1f);
		__GLPredefinedMaterials["Obsidian"] = GLCreate<GLMaterial>(glm::vec3(0.05375f, 0.05f, 0.06625f), glm::vec3(0.18275f, 0.17f, 0.22525f), glm::vec3(0.332741f, 0.328634f, 0.346435f), 0.3f);
		__GLPredefinedMaterials["Pearl"] = GLCreate<GLMaterial>(glm::vec3(0.25f, 0.20725f, 0.20725f), glm::vec3(1.0f, 0.829f, 0.829f), glm::vec3(0.296648f, 0.296648f, 0.296648f), 0.088f);
		__GLPredefinedMaterials["Ruby"] = GLCreate<GLMaterial>(glm::vec3(0.1745f, 0.01175f, 0.01175f), glm::vec3(0.61424f, 0.04136f, 0.04136f), glm::vec3(0.727811f, 0.626959f, 0.626959f), 0.6f);
		__GLPredefinedMaterials["Turquoise"] = GLCreate<GLMaterial>(glm::vec3(0.1f, 0.18725f, 0.1745f), glm::vec3(0.396f, 0.74151f, 0.69102f), glm::vec3(0.297254f, 0.30829f, 0.306678f), 0.1f);
		__GLPredefinedMaterials["Brass"] = GLCreate<GLMaterial>(glm::vec3(0.329412f, 0.223529f, 0.027451f), glm::vec3(0.780392f, 0.568627f, 0.113725f), glm::vec3(0.992157f, 0.941176f, 0.807843f), 0.21794872f);
		__GLPredefinedMaterials["Bronze"] = GLCreate<GLMaterial>(glm::vec3(0.2125f, 0.1275f, 0.054f), glm::vec3(0.714f, 0.4284f, 0.18144f), glm::vec3(0.393548f, 0.271906f, 0.166721f), 0.2f);
		__GLPredefinedMaterials["Chrome"] = GLCreate<GLMaterial>(glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.774597f, 0.774597f, 0.774597f), 0.6f);
		__GLPredefinedMaterials["Copper"] = GLCreate<GLMaterial>(glm::vec3(0.19125f, 0.0735f, 0.0225f), glm::vec3(0.7038f, 0.27048f, 0.0828f), glm::vec3(0.256777f, 0.137622f, 0.086014f), 0.1f);
		__GLPredefinedMaterials["Gold"] = GLCreate<GLMaterial>(glm::vec3(0.24725f, 0.1995f, 0.0745f), glm::vec3(0.75164f, 0.60648f, 0.22648f), glm::vec3(0.628281f, 0.555802f, 0.366065f), 0.4f);
		__GLPredefinedMaterials["Silver"] = GLCreate<GLMaterial>(glm::vec3(0.19225f, 0.19225f, 0.19225f), glm::vec3(0.50754f, 0.50754f, 0.50754f), glm::vec3(0.508273f, 0.508273f, 0.508273f), 0.4f);
		__GLPredefinedMaterials["BlackPlastic"] = GLCreate<GLMaterial>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.50f, 0.50f, 0.50f), 0.25f);
		__GLPredefinedMaterials["CyanPlastic"] = GLCreate<GLMaterial>(glm::vec3(0.0f, 0.1f, 0.06f), glm::vec3(0.0f, 0.50980392f, 0.50980392f), glm::vec3(0.50196078f, 0.50196078f, 0.50196078f), 0.25f);
		__GLPredefinedMaterials["GreenPlastic"] = GLCreate<GLMaterial>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.35f, 0.1f), glm::vec3(0.45f, 0.55f, 0.45f), 0.25f);
		__GLPredefinedMaterials["RedPlastic"] = GLCreate<GLMaterial>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.7f, 0.6f, 0.6f), 0.25f);
		__GLPredefinedMaterials["WhitePlastic"] = GLCreate<GLMaterial>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.55f, 0.55f, 0.55f), glm::vec3(0.70f, 0.70f, 0.70f), 0.25f);
		__GLPredefinedMaterials["YellowPlastic"] = GLCreate<GLMaterial>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.60f, 0.60f, 0.50f), 0.25f);
		__GLPredefinedMaterials["BlackRubber"] = GLCreate<GLMaterial>(glm::vec3(0.02f, 0.02f, 0.02f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.4f, 0.4f, 0.4f), 0.078125f);
		__GLPredefinedMaterials["CyanRubber"] = GLCreate<GLMaterial>(glm::vec3(0.0f, 0.05f, 0.05f), glm::vec3(0.4f, 0.5f, 0.5f), glm::vec3(0.04f, 0.7f, 0.7f), 0.078125f);
		__GLPredefinedMaterials["GreenRubber"] = GLCreate<GLMaterial>(glm::vec3(0.0f, 0.05f, 0.0f), glm::vec3(0.4f, 0.5f, 0.4f), glm::vec3(0.04f, 0.7f, 0.04f), 0.078125f);
		__GLPredefinedMaterials["RedRubber"] = GLCreate<GLMaterial>(glm::vec3(0.05f, 0.0f, 0.0f), glm::vec3(0.5f, 0.4f, 0.4f), glm::vec3(0.7f, 0.04f, 0.04f), 0.078125f);
		__GLPredefinedMaterials["WhiteRubber"] = GLCreate<GLMaterial>(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.7f, 0.7f, 0.7f), 0.078125f);
		__GLPredefinedMaterials["YellowRubber"] = GLCreate<GLMaterial>(glm::vec3(0.05f, 0.05f, 0.0f), glm::vec3(0.5f, 0.5f, 0.4f), glm::vec3(0.7f, 0.7f, 0.04f), 0.078125f);
	}

	return __GLPredefinedMaterials[materialType];
}