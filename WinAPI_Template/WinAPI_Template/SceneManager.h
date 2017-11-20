#pragma once
#include "SingletonBase.h"

#define g_pScnManager SceneManager::GetInstance()

class GameNode;
class SceneManager : public SingletonBase<SceneManager>
{
private:
    map<string, GameNode*>                   m_scnList;
    map<string, GameNode*>::iterator         m_scnIter;

    static GameNode*        m_pCurrScene;
    string                  m_szNextScene = "";

public:
#pragma region CRUD
    //  CREATE
    GameNode* AddScene(string ScnName, GameNode* Scene);
    //  READ
    GameNode* FindScene(string ScnName);
    //  UPDATE
    void NextScene();
    void ChangeScene(string ScnName);
    void Update();
    void Render();
    //  DELETE
    void ReleaseAll();
#pragma endregion

    void SetNextScene(string Scene) { m_szNextScene = Scene; }
    string GetNextScene() { return m_szNextScene; }
};