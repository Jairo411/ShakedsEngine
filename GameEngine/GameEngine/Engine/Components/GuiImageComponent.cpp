#include "GuiImageComponent.h"
#include "../GUI/SpriteSurface.h"

GuiImageComponent::GuiImageComponent(): offSet(glm::vec2()), ptrSurface(nullptr)
{	
}

GuiImageComponent::~GuiImageComponent()
{
	ptrSurface = NULL;
	delete ptrSurface;
}

void GuiImageComponent::OnCreate(std::string name_, glm::vec2 offset_, float scale_, float angle_, glm::vec4 tint_)
{
	offSet = offset_;
	ptrSurface = new SpriteSurface("UI", scale_, angle_, tint_);
}

void GuiImageComponent::Draw()
{

}

bool GuiImageComponent::FindContaintingPoint(glm::vec2 point_)
{
	glm::vec2 minVert;
	minVert = ptrSurface->minVert();
	int width = ptrSurface->getWidth();
	int height = ptrSurface->getHeight();

	if (point_.x>=minVert.x&&point_.x<=minVert.x+width
		&&point_.y >= minVert.y && point_.y<=minVert.y+height)
	{
		std::cout << "UI CollisonDetection Hit" << std::endl;
		return true;
	}
	
	

	return false;
}
