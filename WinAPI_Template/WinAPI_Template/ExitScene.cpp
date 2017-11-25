#include "stdafx.h"
#include "ExitScene.h"


ExitScene::ExitScene()
{
    m_szTagName = "exit";
    g_pImgManager->AddImageList(m_szTagName);
    while (g_pImgManager->AddImageByJson(m_szTagName));
}

ExitScene::~ExitScene()
{
}

void ExitScene::Start()
{
    m_fCurrTime = g_pTimerManager->GetWorldTime();

    m_pImgBg = g_pImgManager->FindImage("exit-bg");
    m_pimgGoodBye = g_pImgManager->FindImage("GoodBye");

    m_sprJunimoDance = new SpritesObject;
    m_sprJunimoDance->SetBodyImg(g_pImgManager->FindImage("junimo-dance"));
    m_sprJunimoDance->SetupForSprites(4, 1);
    m_sprJunimoDance->StartAnimation();
    m_sprJunimoDance->SetBodySize({ 50, 50 });
    m_sprJunimoDance->SetFrameDelay(8);
    m_sprJunimoDance->SetBodyPos({W_WIDTH / 2 , W_HEIGHT / 2 + 80});    
}

void ExitScene::Update()
{
    m_sprJunimoDance->Update();

    if (m_fCurrTime + 4.0f < g_pTimerManager->GetWorldTime())
    {
        PostQuitMessage(0);
    }
}

void ExitScene::Render()
{
    m_pImgBg->Render(g_hDC, 0, 0);
    m_pimgGoodBye->Render(g_hDC,W_WIDTH / 2 - 75, W_HEIGHT / 2);
    m_sprJunimoDance->Render(g_hDC);

#ifdef _DEBUG
    TextOut(g_hDC, W_WIDTH - 100, 0, m_szTagName.c_str(), (int)strlen(m_szTagName.c_str()));
#endif // _DEBUG
}

void ExitScene::Release()
{
    
}
