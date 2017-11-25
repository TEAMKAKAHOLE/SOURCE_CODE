#include "stdafx.h"
#include "SplashScene.h"


SplashScene::SplashScene()
{
    m_szTagName = "splash";
    g_pImgManager->AddImageList(m_szTagName);
    while (g_pImgManager->AddImageByJson(m_szTagName));
    g_pSndManager->AddSoundList(m_szTagName);
    while (g_pSndManager->AddSoundByJson(m_szTagName));
}

SplashScene::~SplashScene()
{
}

void SplashScene::Start()
{
    m_isStart = true;
    m_nAlpha = 0;
    m_nAlphaPlus = 2;
    m_imgLogo = g_pImgManager->FindImage("logo");
    g_pSndManager->Play("splash");
}

void SplashScene::Update()
{
    if (m_isStart)
    {
        m_fDestTime = g_pTimerManager->GetWorldTime() + 4.0f;        
        m_isStart = false;
    }
    else if (m_fDestTime < g_pTimerManager->GetWorldTime())
    {
        g_pScnManager->ChangeScene("title");
    }

    m_nAlpha += m_nAlphaPlus;
    if (m_nAlpha >= 255)
    {
        m_nAlphaPlus = 0;
        m_nAlpha = 255;
    }
}

void SplashScene::Render()
{
    m_imgLogo->AlphaRender(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, m_nAlpha);
#ifdef _DEBUG
    TextOut(g_hDC, W_WIDTH - 100, 0, m_szTagName.c_str(), (int)strlen(m_szTagName.c_str()));
#endif // _DEBUG
}

void SplashScene::Release()
{
}