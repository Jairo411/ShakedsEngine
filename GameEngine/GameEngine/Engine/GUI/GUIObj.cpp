#include "GUIObj.h"
#include "../Core/CoreEngine.h"
GUIObj::GUIObj(glm::vec3 position_)
{
	position = position_;
}

void GUIObj::Draw()
{
	for (int i = 0; i < container.size(); i++)
	{
		container[i].Draw(CoreEngine::GetInstance()->GetCamera(), glm::vec3());
	}
}

bool GUIObj::FindContainingPoint()
{
	for (int i = 0; i < container.size(); i++)
	{
		if (container[i].FindContainingPoint()) {
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void GUIObj::setTag(std::string tag_)
{
	tag = tag_;
}

std::string GUIObj::getTag() const
{
	return tag;
}
