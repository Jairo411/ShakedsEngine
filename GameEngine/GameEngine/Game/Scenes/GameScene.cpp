#include "GameScene.h"

GameScene::GameScene() : Scene() {

}

GameScene::~GameScene() {

	
}

bool GameScene::OnCreate() {
	Debug::Info("Creating Game Scene", "GameScene.cpp", __LINE__);
	
	CoreEngine::GetInstance()->SetCamera(new Camera);
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 2.5f, 0.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, 3.0f, 2.0f), 0.7f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));	

	CollisionHandler::GetInstance()->OnCreate(100.0f);

	GUIObj* gui0 = new GUIObj(glm::vec3(CoreEngine::GetInstance()->GetWindowSize().x/2,CoreEngine::GetInstance()->GetWindowSize().y,0.0f));
	gui0->AddComponent<GuiImageComponent>();
	gui0->GetComponent<GuiImageComponent>()->OnCreate("sun",glm::vec2(1.0,1.0),1.0f,0.5f,glm::vec4(1.0,1.0,1.0,1.0));
	SceneGraph::GetInstance()->AddGUIObject(gui0, "gui0");
	/*Model* model1 = new Model("./Resources/Models/Dice.obj", "./Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(model1);

	Model* model2 = new Model("./Resources/Models/Apple.obj", "./Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(model2);

	GameObject* dice = new GameObject(model1, glm::vec3(0.0f, 1.0f, -3.0f));
	dice->SetRotation(glm::vec3(0.0f, 0.0, 1.0f));
	SceneGraph::GetInstance()->AddGameObject(dice, "dice");
	
	
	GameObject* apple = new GameObject(model2, glm::vec3(2.0f, 1.0f, -3.0f));
	apple->AddComponent<ComponentA>();
	dice->AddComponent<ComponentA>();
	dice->RemoveComponent<ComponentA>();
	
	apple->SetScale(glm::vec3(0.5f));
	SceneGraph::GetInstance()->AddGameObject(apple, "apple");*/

	// Testing Planes
	//std::cout << "planes: " << std::endl;
	//CoreEngine::GetInstance()->GetCamera()->GetFrustum().PrintAllPlanes();

	return true;
}

void GameScene::Draw()
{
	SceneGraph::GetInstance()->Draw();
}

void GameScene::Update(const float deltaTime_) {
	SceneGraph::GetInstance()->Update(deltaTime_);
}

void GameScene::Render() {
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}