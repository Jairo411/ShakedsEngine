#ifndef GAME1_H
#define GAME1_H

#include "../Engine/Core/CoreEngine.h"
#include "Scenes/StartScene.h"
#include "Scenes/GameScene.h"

class Game1 : public GameInterface{
public:
	Game1();
	virtual ~Game1();
	
	// if the parent has virutal .... () = 0, the child must be included in the child and defined (even if it's empty)
	virtual bool OnCreate();
	virtual void Draw();
	virtual void Update(const float deltaTime_);
	virtual void Render();

private:
	Scene* currentScene;
	int currentSceneNum;
	void BuildScene();
};
#endif