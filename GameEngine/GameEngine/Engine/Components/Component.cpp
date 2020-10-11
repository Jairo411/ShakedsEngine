#include "Component.h"
#include "../Rendering/3D/GameObject.h"
Component::Component()
{
	gameobject = nullptr;
}

Component::~Component()
{
	gameobject = nullptr;
	delete gameobject;
}
