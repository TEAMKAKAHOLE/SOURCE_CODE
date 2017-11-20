#include "stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

GameNode* SceneManager::m_pCurrScene = NULL;

GameNode* SceneManager::AddScene(string ScnName, GameNode * Scene)
{
    if (Scene) 
        m_scnList.insert(make_pair(ScnName, Scene));
    return Scene;
}

GameNode * SceneManager::FindScene(string ScnName)
{
    return m_scnList.find(ScnName)->second;
}

void SceneManager::NextScene()
{
    if (m_szNextScene != "")
    {
        ChangeScene(m_szNextScene);
        m_szNextScene = "";
    }
}

void SceneManager::ChangeScene(string ScnName)
{
    m_scnIter = m_scnList.find(ScnName);

    if (m_scnIter == m_scnList.end())
        g_pLogManager->WriteLog(EL_WARNING, "Scene change failed : Not found");

    if (m_scnIter->second == m_pCurrScene)
        g_pLogManager->WriteLog(EL_WARNING, "Scene change failed : Target is current scene");

    if (m_pCurrScene != NULL)
    {
        g_pImgManager->ReleaseByScene(m_pCurrScene->GetTagName());
        g_pSndManager->ReleaseByScene(m_pCurrScene->GetTagName());
        g_pLogManager->WriteLog(EL_INFO, "Scene release : " + m_pCurrScene->GetTagName());
        m_pCurrScene->Release();
    }

    m_pCurrScene = m_scnIter->second;
    m_pCurrScene->Start();
}

void SceneManager::Update()
{
    if (m_pCurrScene != NULL)
    {
        m_pCurrScene->Update();
    }
}

void SceneManager::Render()
{
    if (m_pCurrScene != NULL)
    {
        m_pCurrScene->Render();
    }
}

void SceneManager::ReleaseAll()
{
    m_scnIter = m_scnList.begin();
    for (; m_scnIter != m_scnList.end();)
    {
        // 삭제
        if (m_scnIter->second != NULL)
        {
            m_scnIter->second->Release();
            SAFE_DELETE(m_scnIter->second);
            m_scnIter = m_scnList.erase(m_scnIter);
        }
        else
        {
            ++m_scnIter;
        }
    }

    m_scnList.clear();
}
