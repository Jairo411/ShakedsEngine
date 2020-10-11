#ifndef COMPONENT_H
#define COMPONENT_H
class GameObject;
class Component 
{
public:
	Component();
	virtual ~Component();
	virtual void OnCreate(GameObject* temp_) = 0;
	virtual void Update(float deltaTime_)=0 ;

protected:
	GameObject* gameobject;
};


#endif