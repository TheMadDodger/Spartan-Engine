#include "stdafx.h"
#include "GameApp.h"
#include <ContentManager.h>
#include <SceneManager.h>
#include "Scenes/TestScene.h"
#include "Scenes/BehaviourTreeTestScene.h"
#include "Scenes/GUIDTestScene.h"
#include "GridTestScene.h"
#include "RenderTestScene.h"
#include <MaterialManager.h>
#include <InputManager.h>
#include "BufferTest.h"

#include "TestAsset.h"
#include "AssetManager.h"

GameApp::GameApp(const Spartan::GameSettings &settings) : Spartan::BaseGame(settings)
{
}

GameApp::~GameApp()
{
}

void GameApp::Initialize(const Spartan::GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	//Spartan::SceneManager::GetInstance()->AddScene(new BufferTest());

	//m_ProgramID = LoadShaders("./Resources/Shaders/triangle.vs", "./Resources/Shaders/triangle.fs");

	//size_t id = MaterialManager::CreateMaterial<Material>("./Resources/Shaders/triangle");
	//m_Material = MaterialManager::GetMaterial(id);

	//m_Projection = glm::perspective<float>(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

	//m_View = glm::lookAt(
	//	glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
	//	glm::vec3(0, 0, 0), // and looks at the origin
	//	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	//);

	//gameContext.pInput->AddInputAction(InputAction("UseGLMToggle", InputType::Pressed, 'f'));

	//auto pAsset = Spartan::AssetManager::CreateInstance<TestAsset>();
	//Spartan::AssetDatabase::CreateAsset(pAsset, "test.sasset");
}

void GameApp::GameUpdate(const Spartan::GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	/*if (gameContext.pInput->IsActionTriggered("UseGLMToggle"))
	{
		m_UseGLM = !m_UseGLM;
	}*/
}

void GameApp::GamePaint(const Spartan::GameContext &gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	//// An array of 3 vectors which represents 3 vertices
	//static const GLfloat g_vertex_buffer_data[] = {
	//   -1.0f, -1.0f, 0.0f,
	//   1.0f, -1.0f, 0.0f,
	//   0.0f,  1.0f, 0.0f,
	//};

	//// This will identify our vertex buffer
	//GLuint vertexbuffer;
	//// Generate 1 buffer, put the resulting identifier in vertexbuffer
	//glGenBuffers(1, &vertexbuffer);
	//// The following commands will talk about our 'vertexbuffer' buffer
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//// Give our vertices to OpenGL.
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	//Utilities::Debug::LogGLError(glGetError());

	//// 1st attribute buffer : vertices
	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glVertexAttribPointer(
	//	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	//	3,                  // size
	//	GL_FLOAT,           // type
	//	GL_FALSE,           // normalized?
	//	0,                  // stride
	//	(void*)0            // array buffer offset
	//);

	//Utilities::Debug::LogGLError(glGetError());

	//glm::mat4 model = glm::mat4(1.0f);

	//auto rot = glm::rotate(glm::mat4(1.0f), glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//auto trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.5f));
	//auto view = trans * rot;

	//glm::mat4 mvp = m_Projection * view * model;

	//Matrix4X4 model2 = Matrix4X4::CreateIdentityMatrix();
	////Matrix4X4 rot2 = Matrix4X4::CreateRotationMatrix(Vector3(0.0f, 0.0f, 60.0f));
	//Matrix4X4 view2 = Matrix4X4::CreateTranslationMatrix(Vector3(0.0f, 0.0f, -2.5f));
	//Matrix4X4 projection2 = Matrix4X4::CreatePerspectiveProjectionMatrix(glm::radians(45.0f), 1280.0f, 720.0f, 0.1f, 100.0f);

	//Matrix4X4 mvp2 = model2 * view2 * projection2;

	//m_Material->Use();

	//// REMEMBER THIS FOR THE MODEL RENDERER!!!
	////glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

	//m_Material->SetMatrix("MVP", m_UseGLM ? &mvp[0][0] : &mvp2.m[0][0]);

	//// Draw the triangle !
	//glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	//glDisableVertexAttribArray(0);

	//Utilities::Debug::LogGLError(glGetError());
}

void GameApp::RegisterUserClasses()
{
	REGISTER_CLASS(TestAsset);
}
