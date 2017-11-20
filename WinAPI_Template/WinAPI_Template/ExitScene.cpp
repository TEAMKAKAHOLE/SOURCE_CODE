#include "stdafx.h"
#include "ExitScene.h"


ExitScene::ExitScene()
{
    m_szTagName = "exit";
}

ExitScene::~ExitScene()
{
}

void ExitScene::Start()
{
    m_fCurrTime = g_pTimerManager->GetWorldTime();
}

void ExitScene::Update()
{
    if (m_fCurrTime + 0.5f < g_pTimerManager->GetWorldTime())
    {
        PostQuitMessage(0);
    }
}

void ExitScene::Render()
{
#ifdef _DEBUG
    TextOut(g_hDC, W_WIDTH - 100, 0, m_szTagName.c_str(), (int)strlen(m_szTagName.c_str()));
#endif // _DEBUG
}

void ExitScene::Release()
{
}
