#ifndef COREENGINE_H
#define COREENGINE_H

#include <memory>
#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"

#include "../Components/Component.h"
#include "../Components/GUIComponent.h"
#include"../Components/guiImageComponent.h"
#include "../GUI/GUIObj.h"
#include "../Rendering/3D/GameObject.h"
#include "../Rendering/SceneGraph.h"

#include "../Graphics/ShaderHandler.h"
#include "../Graphics/TextureHandler.h"

#include "../Camera/Camera.h"
#include "../Events//EventListener.h"



class CoreEngine {
public:
	// disabling the function of the copy and move constructor
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator = (const CoreEngine&) = delete;
	CoreEngine& operator = (CoreEngine&&) = delete;
	
	bool OnCreate(std::string name_, int width_, int height_);
	void Run();

	static CoreEngine* GetInstance();

	bool GetIsRunning() const;
	int GetCurrentScene();
	glm::vec2 GetWindowSize() const;
	Camera* GetCamera() const;

	void SetGameInterface(GameInterface* gameInterface_);
	void SetCurrentScene(int sceneNum_);
	void SetCamera(Camera* camera_);

	void Exit();

	// Listeners - Mouse
	void NotifyOfMousePressed(glm::vec2 mouse_, int buttonType_);
	void NotifyOfMouseReleased(glm::vec2 mouse_, int buttonType_);
	void NotifyOfMouseMove(glm::vec2 mouse_);
	void NotifyOfMouseScroll(int y_);

private:
	CoreEngine();
	~CoreEngine();

	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;

	void OnDestroy();
	void Update(const float deltaTime_);
	void Render();

	Window* window;
	bool isRunning;

	Timer timer;
	unsigned int fps;

	GameInterface* gameInterface;

	int currentSceneNum;

	Camera* camera;
};
#endif