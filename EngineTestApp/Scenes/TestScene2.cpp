#include "stdafx.h"
//#include "TestScene2.h"
//#include <GameObject.h>
//#include <Components.h>
//#include <InputManager.h>
//#include <SoundManager.h>
//#include <BinaryContainer.h>
//#include <SceneManager.h>
//
//TestScene2::~TestScene2()
//{
//}
//
//void TestScene2::Initialize(const Spartan::GameContext &gameContext)
//{
//	UNREFERENCED_PARAMETER(gameContext);
//	//m_pObject = new GameObject();
//	//m_pObject->GetTransform()->Translate(BaseGame::GetGame()->GetGameSettings().Window.Width / 2.0f, BaseGame::GetGame()->GetGameSettings().Window.Height / 2.0f);
//	//m_pObject->AddComponent(new UIComponent());
//
//	//auto pSound = ContentManager::GetInstance()->Load<AudioData>("./Resources/Audio/airplane-fly-over.wav");
//	//auto pSound1 = ContentManager::GetInstance()->Load<AudioData>("./Resources/Audio/other_user_joined.wav");
//	//auto pSound2 = ContentManager::GetInstance()->Load<AudioData>("./Resources/Audio/br_crossing_bell_dop.r.wav");
//	//auto pSound3 = ContentManager::GetInstance()->Load<AudioData>("./Resources/Audio/other_user_leaves.wav");
//	//auto pMusic = ContentManager::GetInstance()->Load<AudioData>("./Resources/Audio/Ali Gosun ft. Kurt Cobain - Smells like teen spirit.mp3");
//
//	//m_pImage = new GameObject();
//	//m_pImage->GetTransform()->Translate(100.0f, 0.0f);
//	//m_pImage->GetTransform()->SetScale(Vector2(0.1f, 0.1f));
//	//m_pImage->AddComponent(new ImageRenderComponent("./Resources/test.bmp"));
//	//m_pImage->AddComponent(new AudioSourceComponent(pSound2));
//	//m_pImage->GetComponent<AudioSourceComponent>()->SetSettings(AudioSourceSettings(500.0f, 1000.0f, Linear));
//	//m_pImage->GetComponent<AudioSourceComponent>()->GetSettings().IsConstant = true;
//
//	//m_pObject->AddChild(m_pImage);
//
//	/*auto pObject = new GameObject();
//	pObject->AddComponent(new ImageRenderComponent("./Resources/arty.webp"));
//	pObject->GetTransform()->Translate(50.0f, 50.0f);
//	AddChild(pObject);*/
//
//	//auto pObject = new GameObject();
//	//pObject->AddComponent(new ImageRenderComponent("./Resources/TwitchAvatar.png"));
//	//pObject->AddComponent(new UIComponent());
//	//pObject->GetTransform()->Translate(50.0f, 50.0f);
//	//AddChild(pObject);
//
//	//pObject->GetTransform()->Translate(-50.0f, -50.0f);
//
//	//AddChild(m_pObject);
//
//	//m_pAudioSource = new GameObject();
//	//auto pAudio = new AudioSourceComponent("./Resources/Audio/gun-shot.wav");
//	//pAudio->SetSettings(AudioSourceSettings(500.0f, 5000.0f, Exponential, 25.0f));
//	//pAudio->GetSettings().Exponent = 2;
//	//m_pAudioSource->AddComponent(pAudio);
//	//AddChild(m_pAudioSource);
//
//	Spartan::Utilities::BinaryContainer::OpenWrite("./Resources/Spritesheets/mario.bin");
//	Spartan::Utilities::BinaryContainer::Write<int>(0);
//	Spartan::Utilities::BinaryContainer::Write<int>(1);
//
//	// 1: General information about the spritesheet
//	Spartan::Utilities::BinaryContainer::Write<BYTE>(1);
//	Spartan::Utilities::BinaryContainer::WriteString("mario.png");
//	Spartan::Utilities::BinaryContainer::Write<int>(2);
//
//	// 2: Animation Clips
//	Spartan::Utilities::BinaryContainer::Write<BYTE>(2);
//	Spartan::Utilities::BinaryContainer::Write<int>(0);
//	Spartan::Utilities::BinaryContainer::WriteString("idle");
//	Spartan::Utilities::BinaryContainer::Write<int>(1);
//	Spartan::Utilities::BinaryContainer::Write<int>(0);
//
//	Spartan::Utilities::BinaryContainer::Write<int>(1);
//	Spartan::Utilities::BinaryContainer::WriteString("walk");
//	Spartan::Utilities::BinaryContainer::Write<int>(3);
//	Spartan::Utilities::BinaryContainer::Write<int>(15);
//
//	// 3: Frames
//	Spartan::Utilities::BinaryContainer::Write<BYTE>(3);
//
//	Spartan::Utilities::BinaryContainer::Write<int>(4);
//	// Idle has only 1 frame
//	SDL_Rect r{ 211, 0, 13, 16 };
//	Spartan::Utilities::BinaryContainer::Write<int>(0);
//	Spartan::Utilities::BinaryContainer::Write<SDL_Rect>(r);
//	
//	// Walk has 4 frames
//	r = { 241, 0, 14, 15 };
//	Spartan::Utilities::BinaryContainer::Write<int>(1);
//	Spartan::Utilities::BinaryContainer::Write<SDL_Rect>(r);
//
//	r = { 272, 0, 12, 16 };
//	Spartan::Utilities::BinaryContainer::Write<int>(1);
//	Spartan::Utilities::BinaryContainer::Write<SDL_Rect>(r);
//
//	r = { 300, 0, 16, 16 };
//	Spartan::Utilities::BinaryContainer::Write<int>(1);
//	Spartan::Utilities::BinaryContainer::Write<SDL_Rect>(r);
//
//	Spartan::Utilities::BinaryContainer::Write<BYTE>(0);
//	Spartan::Utilities::BinaryContainer::Close();
//
//	m_pGroundBox = Instantiate<Spartan::GameObject>();
//	m_pGroundBox->CreateRuntimeComponent<Spartan::RigidBodyComponent>()->m_BodyType = b2_staticBody;
//	m_pGroundBox->CreateRuntimeComponent<Spartan::ColliderComponent>()->SetCollider(new Spartan::Box(500.0f, 50.0f));
//
//	m_pSpriteSheetTest = Instantiate<Spartan::GameObject>();
//	m_pSpriteSheetTest->CreateRuntimeComponent<Spartan::RigidBodyComponent>();
//	m_pSpriteSheetTest->CreateRuntimeComponent<Spartan::ColliderComponent>()->SetCollider(new Spartan::Circle(8.0f));
//
//	Spartan::SpriteSheetData *pSpriteSheet = Spartan::ContentManager::GetInstance()->Load<Spartan::SpriteSheetData>("./Resources/Spritesheets/mario.bin");
//	m_pSpriteSheetTest->CreateRuntimeComponent<Spartan::SpriteSheetComponent>()->SetSpriteSheet(pSpriteSheet);
//
//	Spartan::Utilities::Debug::EnablePhysicsDebugRendering(true);
//}
//
//void TestScene2::PostInitialize(const Spartan::GameContext &gameContext)
//{
//	UNREFERENCED_PARAMETER(gameContext);
//	// Since its rigidbody isnt initialized during scene Initialize yet, we translate it in the PostInitialize
//	// Of the scene, when we are here, all objects will have initialized
//	// NEVER create a new object in PostInitialize!
//	m_pGroundBox->GetTransform()->Translate(0.0f, -100.0f);
//}
//
//void TestScene2::Update(const Spartan::GameContext &gameContext)
//{
//	/*m_pObject->GetTransform()->Rotate(Vector3(0, 0, 0.001f) * *gameContext.pTime->GetDeltaTime());
//	m_pImage->GetTransform()->Rotate(Vector3(0, 0, 0.001f) * *gameContext.pTime->GetDeltaTime());*/
//
//	//GetActiveCamera()->GetGameObject()->GetTransform()->Rotate(Vector3(0, 0, 0.001f) * *gameContext.pTime->GetDeltaTime());
//
//	if (gameContext.pInput->IsActionTriggered("Forward"))
//	{
//		GetActiveCamera()->GetGameObject()->GetTransform()->Translate(Spartan::Vector2(0.0f, 1.0f) * gameContext.pTime->GetDeltaTime());
//	}
//	if (gameContext.pInput->IsActionTriggered("Backward"))
//	{
//		GetActiveCamera()->GetGameObject()->GetTransform()->Translate(Spartan::Vector2(0.0f, -1.0f) * gameContext.pTime->GetDeltaTime());
//	}
//	if (gameContext.pInput->IsActionTriggered("Left"))
//	{
//		GetActiveCamera()->GetGameObject()->GetTransform()->Translate(Spartan::Vector2(-1.0f, 0.0f) * gameContext.pTime->GetDeltaTime());
//	}
//	if (gameContext.pInput->IsActionTriggered("Right"))
//	{
//		GetActiveCamera()->GetGameObject()->GetTransform()->Translate(Spartan::Vector2(1.0f, 0.0f) * gameContext.pTime->GetDeltaTime());
//	}
//	if (gameContext.pInput->IsActionTriggered("ZoomOut"))
//	{
//		GetActiveCamera()->Zoom(2.0f);
//	}
//	if (gameContext.pInput->IsActionTriggered("ZoomIn"))
//	{
//		GetActiveCamera()->Zoom(0.5f);
//	}
//	if (gameContext.pInput->IsActionTriggered("ChangeScene"))
//	{
//		Spartan::SceneManager::GetInstance()->LoadScene(0);
//	}
//	/*if (gameContext.pInput->IsActionTriggered("Shoot"))
//	{
//		m_pAudioSource->GetComponent<AudioSourceComponent>()->Play(gameContext);
//	}*/
//
//	//m_pSpriteSheetTest->GetComponent<SpriteSheetComponent>()->Play(string("walk"));
//}
//
//void TestScene2::Draw(const Spartan::GameContext &gameContext)
//{
//	UNREFERENCED_PARAMETER(gameContext);
//}
