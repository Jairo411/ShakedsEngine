#ifndef GUIOBJ_HEADER
#define GUIOBJ_HEADER
#include"../Components/GUIComponent.h"
class EngineCore;
class GUIObj
{
public:	
	GUIObj(glm::vec3 position_);
	void Draw();
	bool FindContainingPoint();
	void setTag(std::string tag_);
	std::string getTag()const;

	template <typename T>
	void AddComponent()
	{
		T* temp_T = new T();
		//first time I wrote C++11 code 2020-09-28 4:48 PM
		if (dynamic_cast<GUIComponent*>(temp_T) == nullptr) {
			//delete temp_G;
			std::string message;
			std::string fileName;

			message = "Dynmaic Cast failed";
			fileName = "GameObject.h";

		//	Debug::Error(message, fileName, __LINE__);

			delete temp_T;
			temp_T = nullptr;

			return;
		}

		if (GetComponent<T>() != nullptr)
		{
			std::string message;
			std::string fileName;

			message = "GameObject already has a Component";
			fileName = "GameObject.h";
		//	Debug::Error(message, fileName, __LINE__);

			delete temp_T;
			temp_T = nullptr;

			return;
		}
		//temp_T->OnCreate(NULL);
		container.push_back(temp_T);

	}

	template <typename T>
	T* GetComponent()
	{
		T* temp_T = new T();
		if (container.size() != 0)
		{
			for (std::size_t t = 0; t < container.size(); t++)
			{
				if (dynamic_cast<GUIComponent*>(container.at(t)) == temp_T)
				{
					return temp_T;
				}
			}
		}
		else
		{
			return NULL;
		}
	}

	template <typename T>
	void RemoveComponent()
	{
		T* temp_T = new T();
		int i = 0;
		bool flag = false;
		while (flag != true)
		{
			if (container.size() != 0)
			{
				if (dynamic_cast<GUIComponent*>(container.at(i)) != temp_T)
				{
					delete temp_T;
					temp_T = nullptr;
					//i = container.begin();
					container.clear();
					i++;
				}
			}
			else
			{
				flag = true;
			}
		}
	}
	
private:
	glm::vec3 position;
	std::string tag;
	std::vector<GUIComponent> container;
};
#endif
