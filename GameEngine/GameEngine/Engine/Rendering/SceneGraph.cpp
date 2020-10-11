#include "SceneGraph.h"


std::unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;

std::map<GLuint, std::vector<Model*>> SceneGraph::sceneModels = std::map<GLuint, std::vector<Model*>>();
std::map<std::string, GameObject*> SceneGraph::sceneGameObjects = std::map<std::string, GameObject*>();
std::map<std::string, GUIObj*> SceneGraph::sceneGUIObjects = std::map<std::string, GUIObj*>();

SceneGraph::SceneGraph() {
	
}

SceneGraph::~SceneGraph() {
	OnDestroy();
}

SceneGraph* SceneGraph::GetInstance() {
	if (sceneGraphInstance.get() == nullptr) {
		sceneGraphInstance.reset(new SceneGraph);
	}
	return sceneGraphInstance.get();
}

void SceneGraph::AddModel(Model* model_) {
	// if find is equal to the end, it means it hasn't found it
	if (sceneModels.find(model_->GetShaderProgram()) == sceneModels.end()) {
		std::vector<Model*> tmp = std::vector<Model*>();
		tmp.reserve(10);
		tmp.push_back(model_);
		sceneModels.insert(std::pair<GLuint, std::vector<Model*>>(model_->GetShaderProgram(), tmp));
	}
	else {
		sceneModels[model_->GetShaderProgram()].push_back(model_);
	}
}

void SceneGraph::AddGameObject(GameObject* go_, std::string tag_) {
	// doesn't work for removing game objects
	if (tag_ == "") {
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		go_->SetTag(newTag);
		sceneGameObjects[newTag] = go_;
	}
	// if we haven't found the tag
	else if (sceneGameObjects.find(tag_) == sceneGameObjects.end()) {
		go_->SetTag(tag_);
		sceneGameObjects[tag_] = go_;
	}
	else {
		Debug::Warning("Trying to add a GameObject with a tag " + tag_ + " that already exists", "SceneGraph.cpp", __LINE__);
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		go_->SetTag(newTag);
		sceneGameObjects[newTag] = go_;
	}
	CollisionHandler::GetInstance()->AddObject(go_);
}

void SceneGraph::AddGUIObject(GUIObj* obj_, std::string tag_)
{
	if (tag_=="")
	{
		std::string newTag = "GUI:" + std::to_string(sceneGUIObjects.size()+1);
		sceneGUIObjects[tag_] = obj_;
	}

	else if (sceneGUIObjects.find(tag_)== sceneGUIObjects.end())
	{
		obj_->setTag(tag_);
		sceneGUIObjects[tag_] = obj_;
	}
	else {
		Debug::Warning("Trying to add a GameObject with a tag" + tag_ + "that already exists", "SceneGraph.cpp",__LINE__);
		std::string newTag = "GameObject" + std::to_string(sceneGUIObjects.size() + 1);
		obj_->setTag(tag_);
		sceneGUIObjects[tag_] = obj_;
	}
}

GUIObj* SceneGraph::GetGUIObj(std::string tag_)
{
	if (sceneGUIObjects.find(tag_) != sceneGUIObjects.end())
	{
		return sceneGUIObjects[tag_];
	}
	return nullptr;
}

GameObject* SceneGraph::GetGameObject(std::string tag_) {
	if (sceneGameObjects.find(tag_) != sceneGameObjects.end()) {
		return sceneGameObjects[tag_];
	}
	// make sure to use try and catch when dealing with game objects
	return nullptr;
}

void SceneGraph::Update(const float deltaTime_) {
	for (auto go : sceneGameObjects) {
		go.second->Update(deltaTime_);
	}
}

void SceneGraph::Draw()
{

	glDisable(GL_DEPTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (auto gui: sceneGUIObjects)
	{
		glUseProgram(ShaderHandler::GetInstance()->GetShader("SpriteShader"));
		gui.second->Draw();
	}
	glEnable(GL_DEPTH);
	glDisable(GL_BLEND);
	

}

void SceneGraph::Render(Camera* camera_) {
	// check to see if they are in the frustum first
	for (auto entry : sceneModels) {
		glUseProgram(entry.first);
		for (auto m : entry.second) {
			m->Render(camera_);
		}
	}
	//std::cout << "pos: " << camera_->GetPosition().x << " " << camera_->GetPosition().y << " " << camera_->GetPosition().z << std::endl;
	//camera_->GetFrustum().PrintAllPlanes();
	for (auto entry : sceneGameObjects) {
		//std::cout << entry.second->GetTag() << " obb:    minVert: " << entry.second->GetBoundingBox().minVert.x << " " << entry.second->GetBoundingBox().minVert.y << " " << entry.second->GetBoundingBox().minVert.z << std::endl;
		//std::cout << entry.second->GetTag() << " obb:    maxVert: " << entry.second->GetBoundingBox().maxVert.x << " " << entry.second->GetBoundingBox().maxVert.y << " " << entry.second->GetBoundingBox().maxVert.z << std::endl;
		// Testing of frustums
		// Frustum is kind of working except the values do not seem correct
		//std::cout << entry.second->GetTag() << " is at: " << entry.second->GetPosition().x << "   " << entry.second->GetPosition().y << "   " << entry.second->GetPosition().z << std::endl;
		entry.second->Render(camera_);
		if (camera_->GetFrustum().IsPointInsideFrustum(entry.second->GetPosition())) {
			std::cout << entry.second->GetTag() << " is inside the frustum!" << std::endl;
			//entry.second->Render(camera_);
		}
		else {
			//std::cout << entry.second->GetTag() << " is outside the frustum!" << std::endl;
		}
	}
}

void SceneGraph::OnDestroy() {
	if (sceneGameObjects.size() > 0) {
		for (auto go : sceneGameObjects) {
			delete go.second;
			go.second = nullptr;
		}
		sceneGameObjects.clear();
	}

	if (sceneModels.size() > 0) {
		for (auto entry : sceneModels) {
			if (entry.second.size() > 0) {
				for (auto m : entry.second) {
					delete m;
					m = nullptr;
				}
				entry.second.clear();
			}
		}
		sceneModels.clear();
		if (sceneGUIObjects.size()>0)
		{
			for (auto gui:sceneGUIObjects)
			{
				delete gui.second;
				gui.second = nullptr;
			}
			sceneGUIObjects.clear();
		}
	}
}