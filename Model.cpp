#include "Model.h"

std::list<Model*> Model::Models;

using namespace std;

Model::Model(char* name)
{
	FbxManager* lSdkManager = FbxManager::Create();
	FbxIOSettings * ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	this->modelName = name;
	lSdkManager->SetIOSettings(ios);
	FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");
	std::string path = MODELS_SUBDIR + std::string(name);
	if (!lImporter->Initialize(path.c_str(), -1, lSdkManager->GetIOSettings()))
		TriggerCrash("Nie można znaleźć modelu!");
	FbxScene* lLevel = FbxScene::Create(lSdkManager, "myLevel");
	lImporter->Import(lLevel);
	for (int i = 0; i < lLevel->GetRootNode()->GetChildCount(); i++){
		FbxNode* node = lLevel->GetRootNode()->GetChild(i);
		char* texBaseName = (char*)node->GetName();
		this->objects.push_back(new ModelObject(node)); // ładowanie modeli z pliku fbx
	}
	Models.push_back(this);
}


Model::~Model()
{
}