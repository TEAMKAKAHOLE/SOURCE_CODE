#include "stdafx.h"
#include "SplashScene.h"


SplashScene::SplashScene()
{
    m_isStart = true;
    m_szTagName = "splash";
    g_pImgManager->AddImageList(m_szTagName);
    while (g_pImgManager->AddImageByJson(m_szTagName));
}

SplashScene::~SplashScene()
{
}

void SplashScene::Start()
{
}

void SplashScene::Update()
{
    if (m_isStart)
    {
        m_fDestTime = g_pTimerManager->GetWorldTime() + 1.0f;
        m_isStart = false;
    }
    else if (m_fDestTime < g_pTimerManager->GetWorldTime())
    {
        g_pScnManager->SetNextScene("title");
        g_pScnManager->ChangeScene("loading");
    }
}

void SplashScene::Render()
{
    g_pImgManager->Render("logo", g_hDC);
#ifdef _DEBUG
    TextOut(g_hDC, W_WIDTH - 100, 0, m_szTagName.c_str(), (int)strlen(m_szTagName.c_str()));
#endif // _DEBUG
}

void SplashScene::Release()
{
}