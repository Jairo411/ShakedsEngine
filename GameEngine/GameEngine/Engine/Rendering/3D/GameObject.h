#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include "../../Components/Component.h"


class GameObject {
public:
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3());
	GameObject(glm::vec3 position_); // for an object with no model
	~GameObject();
	void Render(Camera* camera_);
	void Update(const float deltaTime_);

	glm::vec3 GetPosition() const;
	float GetAngle() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	BoundingBox GetBoundingBox() const;
	std::string GetTag() const;
	bool GetHit() const;

	void SetPosition(glm::vec3 position_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetTag(std::string tag_);
	void SetHit(bool hit_, int buttonType_);


	template <typename T>
	void AddComponent()
	{
		T* temp_T = new T();
		 //first time I wrote C++11 code 2020-09-28 4:48 PM
		if (dynamic_cast<Component*>(temp_T)==nullptr) {
			//delete temp_G;
			std::string message;
			std::string fileName;

			message = "Dynmaic Cast failed";
			fileName = "GameObject.h";

			Debug::Error(message, fileName, __LINE__);

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
			Debug::Error(message, fileName, __LINE__);

			delete temp_T;
			temp_T=nullptr;

			return;
		}
		temp_T->OnCreate(this);
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
				if (dynamic_cast<Component*>(container.at(t)) == temp_T)
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
		bool flag= false;
		while (flag!=true)
		{
			if (container.size()!=0)
			{
				if (dynamic_cast<Component*>(container.at(i)) != temp_T)
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
	Model* model;
	int modelInstance;

	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;
	BoundingBox box;

	std::string tag;

	bool hit;

	std::vector<Component*> container;
};


#endif