#include "Model.h"

std::list<Model*> Model::Models;

using namespace std;


FbxAMatrix* before;
Model::Model(char* name)
{
	FbxManager* lSdkManager = FbxManager::Create();
	FbxIOSettings * ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	this->modelName = name;
	lSdkManager->SetIOSettings(ios);
	FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");
	std::string path = MODELS_SUBDIR + std::string(name);
	if (!lImporter->Initialize(path.c_str(), -1, lSdkManager->GetIOSettings()))
		TriggerCrash("Nie mo¿na znaleœæ modelu!");
	FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");
	lImporter->Import(lScene);
	for (int i = 0; i < lScene->GetRootNode()->GetChildCount(); i++){
		FbxNode* node = lScene->GetRootNode()->GetChild(i);
		char* texBaseName = (char*) node->GetName();
		this->objects.push_back(new ModelObject(node));
	}
	Models.push_back(this);
}


Model::~Model()
{
}

Model* Model::GetModel(char* name, char* localization){
	char* name2 = (char*) malloc(strlen(name) + strlen(localization) + 1);
	strcpy(name2, localization);
	if (!(localization[strlen(localization) - 1] == '/' || localization[strlen(localization) - 1] == '\\'))
		strcat(name2, "/");
	strcat(name2, name);
	for (std::list<Model*>::iterator it = Models.begin(); it != Models.end(); it++){
		if (strcmp((*it)->modelName, name2) == 0)
			return *it;
	}
	return new Model(name2);
}
