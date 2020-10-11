#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H
#include <iostream>
#include "../Camera/Camera.h"
class GUIComponent
{
public:
	GUIComponent();
	virtual ~GUIComponent();
	virtual void Draw(Camera* cam_, glm::vec3 postion_) = 0;
	virtual bool FindContainingPoint() = 0;
private:
		glm::vec3 postion;
};
#endif //COMPONENTA_H
