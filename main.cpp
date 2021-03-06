#include <iostream>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>

#include "GLEngine/GL/GL.h"

#include "GBossStage.h"
#include "GDodgeStage.h"

#include "GGameWorld.h"

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	GLSetWindow(GLCreate<GLWindow>(0, 0, 800, 800, "TeamProject"));

	InitializeGLEW();
	glEnable(GL_DEPTH_TEST);

	auto scene = GLCreate<GLScene>("TeamProject");
	GLLoadScene(scene);

	auto world = GCreate(GGameWorld);
	scene->GetRoot()->AddChild(world);

	scene->SetBackgroundColor(GLColor(0.0f, 0.0f, 0.0f));
	world->Initialize();

	glutMainLoop();
}