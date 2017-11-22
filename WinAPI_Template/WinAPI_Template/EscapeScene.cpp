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
	m_imgWorldBuffer     = g_pImgManager->AddImage("eacape-map-buffer",2048,2048);
	m_imgWorldMap        = g_pImgManager->FindImage("escape_bg");
	m_imgTerrainBuffer   = g_pImgManager->FindImage("escape_bgmaginta-bg");
	m_player.SetBodyImg(g_pImgManager->FindImage("Player"));
	m_player.SetupForSprites(7,8);
	m_player.StartAnimation();
	m_player.SetBodySize({ 128,128 });
	m_player.SetFrameDelay(6);

	//Player스타트 위치 세팅 512사이즈위치 *4 
	m_player.SetBodyPos({(int) 350 *4,(int) 390*4});
	m_player.SetHBoxMargin({10,10,10,10 });

	//for (int i = 0; i < 4; ++i)
	//{
	//	TelePort m_teleport;

	//}  일단 하드코딩

	m_teleportA.SetBodyPos({ (int)385 * 4 ,(int)300 * 4 });
	m_teleportA.SetBodySize({ (int)100,(int)100 });

	
	m_teleportB.SetBodyPos({ (int)418 * 4 ,(int)190* 4 });
	m_teleportB.SetBodySize({ (int)100,(int)100 });

	
	m_teleportC.SetBodyPos({ (int)255 * 4 ,(int)250 * 4 });
	m_teleportC.SetBodySize({ (int)100,(int)100 });

	
	m_teleportD.SetBodyPos({ (int)95 * 4 ,(int)285 * 4 });
	m_teleportD.SetBodySize({ (int)100,(int)100 });

	
	

	
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
		
		m_player.SetBodyPos({ (int)250 * 4,(int)250 * 4 + 180});
	}
	else if (IntersectRect(&rt, &m_player.GetBodyRect(), &m_teleportB.GetBodyRect()))
	{
		m_player.SetBodyPos({ (int)92 * 4,(int)280 * 4 + 180});
	}

	else if (IntersectRect(&rt, &m_player.GetBodyRect(), &m_teleportC.GetBodyRect()))
	{
		m_player.SetBodyPos({ (int)80* 4+200,(int)170 * 4  });
	}
	else if (IntersectRect(&rt, &m_player.GetBodyRect(), &m_teleportD.GetBodyRect()))
	{
		m_player.SetBodyPos({ (int)385 * 4,(int)300 * 4 +180 });
	}
		


}

void EscapeScene::Render()
{
	m_imgWorldMap->Render(m_imgWorldBuffer->GetMemDC(), 0, 0, 2048, 2048);
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
