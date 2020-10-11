#ifndef GUIIMAGECOMPONENT_HEADER
#define GUIIMAGECOMPONENT_HEADER
#include <string>
#include "GUIComponent.h"

class SpriteSurface;
class GuiImageComponent : public GUIComponent
{
public:
	GuiImageComponent();
	virtual ~GuiImageComponent();
	virtual void OnCreate(std::string name_,glm::vec2 offset_,float scale_, float angle_,glm::vec4 tint_);
	virtual void Draw();
	virtual bool FindContaintingPoint(glm::vec2 point_);
private:
	SpriteSurface* ptrSurface; // Enable the spriteSurface Member Variables with the OnCreate Function of this class; 
	glm::vec2 offSet;
	std::string tag;
};
#endif //GUIIMAGEcOMPONENT_HEADER
