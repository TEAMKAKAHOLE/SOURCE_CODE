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
    m_imgWorldBuffer = g_pImgManager->AddImage("town-map-buffer", 512, 512);
    m_imgWorldMap = g_pImgManager->FindImage("town-map");
    m_imgTerrainBuffer = g_pImgManager->FindImage("town-terrain");
    m_player.SetBodyImg(g_pImgManager->FindImage("player"));
    m_player.SetupForSprites(7, 8);
    m_player.StartAnimation();
    m_player.SetBodySize({ 64, 64 });
    m_player.SetBodyPos({ 300.0f, 350.0f });
    m_player.SetFrameDelay(6);
    m_player.SetTerrainBuffer(m_imgTerrainBuffer);
}

void TownScene::Update()
{
    m_player.Update();
    g_rtViewPort = g_pDrawHelper->MakeViewPort(m_player.GetBodyPos(), m_imgWorldBuffer);
}

void TownScene::Render()
{
    m_imgWorldMap->Render(m_imgWorldBuffer->GetMemDC(), 0, 0);
    m_player.Render(m_imgWorldBuffer->GetMemDC());

    m_imgWorldBuffer->ViewportRender(g_hDC, g_rtViewPort);
}

void TownScene::Release()
{
}
