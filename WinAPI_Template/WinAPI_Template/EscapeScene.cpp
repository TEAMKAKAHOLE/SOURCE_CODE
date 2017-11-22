#include "stdafx.h"
#include "EscapeScene.h"
#include "Player.h"
#include "TelePort.h"

//생성시 GameObject를 상속받게 한다.
EscapeScene::EscapeScene()
{
	
}


EscapeScene::~EscapeScene()
{
}

void EscapeScene::Start()
{
	m_imgWorldBuffer     = g_pImgManager->AddImage("eacape-map-buffer", 512, 512);
	m_imgWorldMap        = g_pImgManager->FindImage("escape-map");
	m_imgTerrainBuffer   = g_pImgManager->FindImage("escape-terrain");
	m_player.SetBodyImg(g_pImgManager->FindImage("player"));
	m_player.SetupForSprites(7,8);
	m_player.StartAnimation();
    m_player.SetBodySize({ 64, 64 });
	m_player.SetFrameDelay(6);
    m_player.SetBodyPos({ (int)350,(int)390 });
    m_player.SetHBoxMargin({ 16, 16, 16, 16 });
    m_player.SetTerrainBuffer(m_imgTerrainBuffer);
    m_player.Update();
    m_player.SetLockArea({ 0, 0, 512, 512 });
    m_player.LockInWnd();

	//Player스타트 위치 세팅 512사이즈위치 *4 

	//for (int i = 0; i < 4; ++i)
	//{
	//	TelePort m_teleport;

	//}  일단 하드코딩

	m_teleportA.SetBodyPos({ (int)385, (int)300 });
	m_teleportA.SetBodySize({ (int)100, (int)100 });

	
	m_teleportB.SetBodyPos({ (int)418, (int)190 });
	m_teleportB.SetBodySize({ (int)100, (int)100 });

	
	m_teleportC.SetBodyPos({ (int)255, (int)250 });
	m_teleportC.SetBodySize({ (int)100, (int)100 });

	
	m_teleportD.SetBodyPos({ (int)95, (int)285 });
	m_teleportD.SetBodySize({ (int)100, (int)100 });
}

void EscapeScene::Update()
{
	m_player.Update();
	m_teleportA.Update();
	m_teleportB.Update();
	m_teleportC.Update();
	m_teleportD.Update();

	int distance = 10;

	g_rtViewPort = g_pDrawHelper->MakeViewPort(m_player.GetBodyPos(), m_imgWorldBuffer);
	RECT rt;
	//탈출시 위치가 또다른 충돌박스에 있지 않게 한다.추가 위치 보정필요
	if (IntersectRect(&rt, &m_player.GetBodyRect(), &m_teleportA.GetBodyRect()))
	{
		m_player.SetBodyPos({ (int)250, (int)250 + 180});
	}
	else if (IntersectRect(&rt, &m_player.GetBodyRect(), &m_teleportB.GetBodyRect()))
	{
		m_player.SetBodyPos({ (int)92, (int)280 + 180});
	}
	else if (IntersectRect(&rt, &m_player.GetBodyRect(), &m_teleportC.GetBodyRect()))
	{
		m_player.SetBodyPos({ (int)80 + 200, (int)170 });
	}
	else if (IntersectRect(&rt, &m_player.GetBodyRect(), &m_teleportD.GetBodyRect()))
	{
		m_player.SetBodyPos({ (int)385, (int)300 + 180 });
	}
}

void EscapeScene::Render()
{
	m_imgWorldMap->Render(m_imgWorldBuffer->GetMemDC(), 0, 0);

	m_player.Render(m_imgWorldBuffer->GetMemDC());

	m_teleportA.Render(m_imgWorldBuffer->GetMemDC());
	m_teleportB.Render(m_imgWorldBuffer->GetMemDC());
	m_teleportC.Render(m_imgWorldBuffer->GetMemDC());
	m_teleportD.Render(m_imgWorldBuffer->GetMemDC());

	m_imgWorldBuffer->ViewportRender(g_hDC, g_rtViewPort);
}

void EscapeScene::Release()
{
}
