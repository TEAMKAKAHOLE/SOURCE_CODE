#include "stdafx.h"
#include "TownScene.h"


TownScene::TownScene()
{
}


TownScene::~TownScene()
{
}

void TownScene::Start()
{
    //  world map
    m_imgWorldBuffer = g_pImgManager->AddImage("town-map-buffer", 512, 512);
    m_imgWorldMap = g_pImgManager->FindImage("town-map");
    m_imgTerrainBuffer = g_pImgManager->FindImage("town-terrain");

    //  ui
    m_imgUiBuffer = g_pImgManager->FindImage("ui-buffer");
    m_imgHud = g_pImgManager->FindImage("hud");
    m_sprHudNumber = new SpritesObject;
    m_sprHudNumber->SetBodyImg(g_pImgManager->FindImage("hud-number"));
    m_sprHudNumber->SetupForSprites(10, 1);
    m_sprHudLife = new SpritesObject;
    m_sprHudLife->SetBodyImg(g_pImgManager->FindImage("hud-life"));
    m_sprHudLife->SetupForSprites(3, 1);

    m_player.SetBodyImg(g_pImgManager->FindImage("player"));
    m_player.SetupForSprites(7, 8);
    m_player.StartAnimation();
    m_player.SetBodySize({ 64, 64 });
    m_player.SetBodyPos({ 300.0f, 350.0f });
    m_player.SetFrameDelay(6);
    m_player.SetTerrainBuffer(m_imgTerrainBuffer);
    m_player.SetHBoxMargin({ 16, 16, 16, 16 });
    m_player.Update();
    m_player.SetLockArea({ 0, 0, 512, 512 });
    m_player.LockInWnd();
}

void TownScene::Update()
{
    if (g_pKeyManager->isOnceKeyDown(VK_F2))
    {
        g_pScnManager->SetNextScene("field");
        g_pScnManager->ChangeScene("loading");
    }
    else if (g_pKeyManager->isOnceKeyDown(VK_F3))
    {
        g_pScnManager->SetNextScene("puzzle");
        g_pScnManager->ChangeScene("loading");
    }

    m_player.Update();
    g_rtViewPort = g_pDrawHelper->MakeViewPort(m_player.GetBodyPos(), m_imgWorldBuffer);
}

void TownScene::Render()
{
    m_imgWorldMap->Render(m_imgWorldBuffer->GetMemDC(), 0, 0);
    m_player.Render(m_imgWorldBuffer->GetMemDC());

    //  world render
    m_imgWorldBuffer->ViewportRender(g_hDC, g_rtViewPort);

    //  ui render
    m_imgHud->FastRender(m_imgUiBuffer->GetMemDC(), 0, 0);
    //  180, 25
    //  life
    int marginX = 180;
    int marginY = 25;
    for (int i = 0; i < m_player.GetLife(); i++)
    {
        m_sprHudLife->GetBodyImg()->SpritesRender(m_imgUiBuffer->GetMemDC()
            , marginX + i * 10, marginY
            , 7, 7
            , 0, 0
            , 255.0f);
    }

    //  65, 24
    //  number
    m_sprHudNumber->GetBodyImg()->SpritesRender(m_imgUiBuffer->GetMemDC()
        , { 85, 28 }
        , { 7, 7 }
        , m_player.GetHealPotion()
        , 255.0f);

    m_imgUiBuffer->TransRender(g_hDC, 0, 0, W_WIDTH, W_HEIGHT);
}

void TownScene::Release()
{
}
