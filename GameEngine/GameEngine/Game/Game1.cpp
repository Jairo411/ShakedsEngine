#include "Game1.h"

Game1::Game1() : GameInterface(), currentScene(nullptr), currentSceneNum(0) {

}

Game1::~Game1() {
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::OnCreate() {
	if (CoreEngine::GetInstance()->GetCurrentScene() == 0) {
		currentScene = new StartScene();
		if (!currentScene->OnCreate()) {
			Debug::FatalError("Game was not created", "Game1.cpp", __LINE__);
			return false;
		}
		return true;
	}

	Debug::FatalError("Engine scene number is not zero", "Game1.cpp", __LINE__);
	return false;
}

void Game1::Draw()
{
	currentScene->Draw();
}

void Game1::Update(const float deltaTime_) {
	if (currentSceneNum != CoreEngine::GetInstance()->GetCurrentScene()) {
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}

void Game1::Render() {
	currentScene->Render();
}

void Game1::BuildScene() {
	delete currentScene;
	currentScene = nullptr;

	switch (CoreEngine::GetInstance()->GetCurrentScene()) {
	case 1:
		currentScene = new GameScene();
		break;
	default:
		currentScene = new StartScene();
		break;
	}

	if (!currentScene->OnCreate()) {
		Debug::Error("Scene failed to load!", "Game1.cpp", __LINE__);
		CoreEngine::GetInstance()->Exit();
	}

	currentSceneNum = CoreEngine::GetInstance()->GetCurrentScene();
}