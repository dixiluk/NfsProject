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
	FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");	//pobranie calego fbx'a
	lImporter->Import(lScene);
	for (int i = 0; i < lScene->GetRootNode()->GetChildCount(); i++){	//leci po wszystkich modelach w fbx
		FbxNode* node = lScene->GetRootNode()->GetChild(i);
		char* texBaseName = (char*) node->GetName();
		this->objects.push_back(new ModelObject(node));
	}
	Models.push_back(this);
}


Model::~Model()
{
}

