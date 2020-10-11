#include "CoreEngine.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() : window(nullptr), isRunning(false), fps(120), gameInterface(nullptr), currentSceneNum(0), camera(nullptr) {

}

CoreEngine::~CoreEngine() {
	OnDestroy();
}

CoreEngine* CoreEngine::GetInstance() {
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new CoreEngine);
	}
	return engineInstance.get();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_) {
	Debug::DebugInit();
	Debug::SetSeverity(MessageType::TYPE_INFO);

	window = new Window();
	// if window fails to create
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::FatalError("Window failed to initialize!", "Window.cpp", __LINE__);
		return isRunning = false;
		// ^^ same as isRunning = false; return isRunning;
	}

	// Sets the mouse position to the middle of the screen - could also be implemented in the window class
	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);

	MouseEventListener::RegisterEngineObject(this);

	// the path to pass in is the relative path (find by looking at file's properties)
	// also only forward slashes '/' (because it's a string)  - example "\n" <- that's a newline character
	ShaderHandler::GetInstance()->CreateProgram("colourShader", "Engine/Shaders/ColourVertexShader.glsl", "Engine/Shaders/ColourFragmentShader.glsl");


	ShaderHandler::GetInstance()->CreateProgram("basicShader", "Engine/Shaders/VertexShader.glsl", "Engine/Shaders/FragmentShader.glsl");

	ShaderHandler::GetInstance()->CreateProgram("SpriteShader", "Engine/Shader/SpriteVertShader.glsl", "Engine/Shader/SpriteFragShader.glsl");

	if (gameInterface) { // if gameInterface is not null
		if (!gameInterface->OnCreate()) {
			Debug::FatalError("Game Interface was not able to load!", "CoreEngine.cpp", __LINE__);
			return isRunning = false;
		}
	}

	timer.Start();

	Debug::Info("Everything was created okay! :)", "CoreEngine.cpp", __LINE__);

	return isRunning = true;
}

void CoreEngine::Run() {
	while (isRunning) {
		timer.UpdateFrameTicks();
		EventListener::Update();
		Update(timer.GetDeltaTime()); // 0.016f will make it 60fps
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
		
	}

	// vv this if statemennt is redundant, just makes it very clear
	if (!isRunning) {
		OnDestroy();
	}
}

bool CoreEngine::GetIsRunning() const {
	return isRunning;
}

void CoreEngine::OnDestroy() {
	// call OnDestroy for singletons
	ShaderHandler::GetInstance()->OnDestroy();
	TextureHandler::GetInstance()->OnDestroy();
	SceneGraph::GetInstance()->OnDestroy();

	delete gameInterface;
	gameInterface = nullptr;

	delete window;
	window = nullptr;

	delete camera;
	camera = nullptr;	

	SDL_Quit();
	exit(0);
}

void CoreEngine::Update(const float deltaTime_) {
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
	}
}

void CoreEngine::Render() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// gets rid of anything in the depth or buffer bit
	
	// GAME'S RENDER
	if (gameInterface) {
		gameInterface->Render();
		gameInterface->Draw();
	}
	
	SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::SetGameInterface(GameInterface* gameInterface_) {
	gameInterface = gameInterface_;
}

int CoreEngine::GetCurrentScene() {
	return currentSceneNum;
}

void CoreEngine::SetCurrentScene(int sceneNum_) {
	currentSceneNum = sceneNum_;
}

void CoreEngine::Exit() {
	isRunning = false;
}

glm::vec2 CoreEngine::GetWindowSize() const {
	return glm::vec2(window->GetWidth(), window->GetHeight());
}

Camera* CoreEngine::GetCamera() const {
	return camera;
}

void CoreEngine::SetCamera(Camera* camera_) {
	camera = camera_;
}

// Listeners - Mouse

void CoreEngine::NotifyOfMousePressed(glm::vec2 mouse_, int buttonType_) {

}

void CoreEngine::NotifyOfMouseReleased(glm::vec2 mouse_, int buttonType_) {
	CollisionHandler::GetInstance()->MouseUpdate(mouse_, buttonType_);
}

void CoreEngine::NotifyOfMouseMove(glm::vec2 mouse_) {
	if (camera) {
		camera->ProcessMouseMovement(MouseEventListener::GetMouseOffset());
	}
}

void CoreEngine::NotifyOfMouseScroll(int y_) {
	if (camera) {
		camera->ProcessMouseScroll(y_);
	}
}