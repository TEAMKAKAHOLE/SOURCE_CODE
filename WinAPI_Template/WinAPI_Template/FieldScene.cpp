#include "stdafx.h"
#include "FieldScene.h"

FieldScene::FieldScene()
{
}


FieldScene::~FieldScene()
{
}

void FieldScene::Start()
{
	m_imgWorldBuffer = g_pImgManager->AddImage("WorldBuffer", 512, 512);

	m_imgWorldBuffer = g_pImgManager->FindImage("WorldBuffer");
	m_imgWorldMap = g_pImgManager->FindImage("field-map");
	m_imgTerrainBuffer = g_pImgManager->FindImage("field-map-magenta");

	m_player.SetBodyImg(g_pImgManager->FindImage("player"));
	m_player.SetBodyPos({ 210, 400 });
	m_player.SetBodySize({ 64, 64 });
	m_player.SetupForSprites(7, 8);
	m_player.SetFrameDelay(3);
	m_player.StartAnimation();
	m_player.SetTerrainBuffer(m_imgTerrainBuffer);
    m_player.SetHBoxMargin({ 16, 16, 16, 16 });
    m_player.Update();
    m_player.SetLockArea({ 0, 0, 512, 512 });
    m_player.LockInWnd();

	m_enemy.SetBodyImg(g_pImgManager->FindImage("enemy-knight"));
	m_enemy.SetBodyPos({ 300, 400 });
	m_enemy.SetBodySize({ 64, 64 });
	m_enemy.SetupForSprites(4, 4);
	m_enemy.SetFrameDelay(3);
	m_enemy.StartAnimation();
    m_enemy.SetHBoxMargin({ 16, 16, 16, 16 });
    m_enemy.Update();
    m_enemy.SetLockArea({ 0, 0, 512, 512 });
    m_enemy.LockInWnd();
}

void FieldScene::Update()
{
    if (g_pKeyManager->isOnceKeyDown(VK_F1))
    {
        g_pScnManager->SetNextScene("town");
        g_pScnManager->ChangeScene("loading");
    }
    else if (g_pKeyManager->isOnceKeyDown(VK_F2))
    {
        g_pScnManager->SetNextScene("field");
        g_pScnManager->ChangeScene("loading");
    }
    else if (g_pKeyManager->isOnceKeyDown(VK_F3))
    {
        g_pScnManager->SetNextScene("escape");
        g_pScnManager->ChangeScene("loading");
    }
    else if (g_pKeyManager->isOnceKeyDown(VK_F4))
    {
        g_pScnManager->SetNextScene("puzzle");
        g_pScnManager->ChangeScene("loading");
    }

	m_player.Update();
	m_enemy.Update();

	//¸Ê ¿òÁ÷ÀÌ±â
	g_rtViewPort = g_pDrawHelper->MakeViewPort(m_player.GetBodyPos(), m_imgWorldBuffer);
}

void FieldScene::Render()
{
	m_imgWorldMap->Render(m_imgWorldBuffer->GetMemDC(), 0, 0);
	m_player.Render(m_imgWorldBuffer->GetMemDC());
	m_enemy.Render(m_imgWorldBuffer->GetMemDC());
	m_imgWorldBuffer->ViewportRender(g_hDC, g_rtViewPort);
}

void FieldScene::Release()
{
}
