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

	

	m_teleportA.SetBodyPos({ (int)385, (int)300 });
	m_teleportA.SetBodySize({ (int)20, (int)20 });

	
	m_teleportB.SetBodyPos({ (int)418, (int)190 });
	m_teleportB.SetBodySize({ (int)20, (int)20 });

	
	m_teleportC.SetBodyPos({ (int)255, (int)250 });
	m_teleportC.SetBodySize({ (int)20, (int)20 });

	
	m_teleportD.SetBodyPos({ (int)95, (int)285 });
	m_teleportD.SetBodySize({ (int)20, (int)20 });

	//next Scene 이동위한 Endpoint
	m_EndPoint.SetBodyPos({ 80 ,170 });
	m_EndPoint.SetBodySize({ 20,20 });
	m_StartPoint.SetBodyPos({ 350 ,390 });
	m_StartPoint.SetBodySize({ 20,20 });


	//Item 초기위치,bool 설정
	m_KeyItem1.SetBodyImg(g_pImgManager->FindImage("keyItem"));
	m_KeyItem1.SetupForSprites(1,1);
	m_KeyItem1.StartAnimation();
	m_KeyItem1.SetBodySize({ 46,46 });
	m_KeyItem1.SetBodyPos({ 420,260 });
	m_bKeyItem1 = false;
	

}

void EscapeScene::Update()
{
	m_player.Update();
	m_teleportA.Update();
	m_teleportB.Update();
	m_teleportC.Update();
	m_teleportD.Update();
	m_KeyItem1.Update();
	m_EndPoint.Update();
	m_StartPoint.Update();

	int distance = 10;

	g_rtViewPort = g_pDrawHelper->MakeViewPort(m_player.GetBodyPos(), m_imgWorldBuffer);
	RECT rt;
	//탈출시 위치가 또다른 충돌박스에 있지 않게 한다.추가 위치 보정필요
	if (IntersectRect(&rt, &m_player.GetBodyRect(), &m_teleportA.GetBodyRect()))
	{
		m_player.SetBodyPos({ (int)250, (int)250 + 50});
	}
	else if (IntersectRect(&rt, &m_player.GetBodyRect(), &m_teleportB.GetBodyRect()))
	{
		m_player.SetBodyPos({ (int)92, (int)280 + 50});
	}
	else if (IntersectRect(&rt, &m_player.GetBodyRect(), &m_teleportC.GetBodyRect()))
	{
		m_player.SetBodyPos({ (int)80 + 50, (int)170 });
	}
	else if (IntersectRect(&rt, &m_player.GetBodyRect(), &m_teleportD.GetBodyRect()))
	{
		m_player.SetBodyPos({ (int)385, (int)300 + 50 });
	}
	else if (IntersectRect(&rt, &m_player.GetBodyRect(), &m_EndPoint.GetBodyRect()))
	{  //씬 이동을 위한 충돌 판단 부분
		if(m_bKeyItem1)
		{
		  SceneChange();
		}
	}
	else if (IntersectRect(&rt, &m_player.GetBodyRect(), &m_KeyItem1.GetBodyRect()))
	{
		m_bKeyItem1 = true;
		m_KeyItem1.SetInvisible();
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
	m_KeyItem1.Render(m_imgWorldBuffer->GetMemDC());
	m_EndPoint.Render(m_imgWorldBuffer->GetMemDC());
	m_StartPoint.Render(m_imgWorldBuffer->GetMemDC());

	m_imgWorldBuffer->ViewportRender(g_hDC, g_rtViewPort);
}

void EscapeScene::Release()
{
}

void EscapeScene::SceneChange()
{
	g_pScnManager->SetNextScene("puzzle");
	g_pScnManager->ChangeScene("loading");
}
