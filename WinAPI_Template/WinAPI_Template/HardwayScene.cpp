#include "stdafx.h"
#include "HardwayScene.h"


HardwayScene::HardwayScene()
	: m_isStartGhost(false)
	, m_isEventStart(true)
	, m_isPursuing(false)
	, m_isGoingX(false)
	, m_isDead(false)
	, m_nPusuingDelay(500)
	, m_nRenderShotTime(400)
	, m_nShakePosX(0)
	, m_nShakePosY(0)
	, m_nSoundPlayerCount(1)
{
	m_szTagName = "hardway";
}


HardwayScene::~HardwayScene()
{
}

void HardwayScene::Start()
{
	m_playerData = g_pFileManager->JsonFind("player");

	g_pImgManager->AddImageList(m_szTagName);
	while (g_pImgManager->AddImageByJson(m_szTagName));
	g_pSndManager->AddSoundList(m_szTagName);
	while (g_pSndManager->AddSoundByJson(m_szTagName));
	
	m_imgWorldBuffer = g_pImgManager->AddImage("hardway-map-buffer", 512, 512);
	m_imgWorldMap = g_pImgManager->FindImage("maze");
	m_imgTerrainBuffer = g_pImgManager->FindImage("maze-terrain");
	m_imgGhostShot = g_pImgManager->FindImage("ghost-shot");

	//플레이어 세팅
	m_Player.SetBodyImg(g_pImgManager->FindImage("player"));
	m_Player.SetupForSprites(7, 8);
	m_Player.StartAnimation();
	m_Player.SetBodySize({ 64, 64 });
	m_Player.SetTerrainBuffer(m_imgTerrainBuffer);
	m_Player.SetHBoxMargin({ 16, 16, 16, 16 });
	m_Player.SetBodyPos({ 395, 480 });
	m_Player.Update();
	m_Player.SetLockArea({ 0, 0, 512, 512 });
	m_Player.LockInWnd();
	m_Player.SetFrameDelay(6);

	//고스트 세팅
	m_Ghost.SetBodyImg(g_pImgManager->FindImage("ghost"));
	m_Ghost.SetupForSprites(2, 4);
	m_Ghost.StartAnimation();
	m_Ghost.SetBodySize({ 32, 32 });
	m_Ghost.SetTerrainBuffer(m_imgTerrainBuffer);
	m_Ghost.SetBodyPos({ 269, 335 });
	m_Ghost.Update();
	m_Ghost.SetLockArea({ 0, 0, 512, 512 });
	m_Ghost.LockInWnd();
	m_Ghost.SetFrameDelay(5);

	m_rtExit = new SpritesObject;
	m_rtExit->SetBodySize({ 10, 25 });
	m_rtExit->SetBodyPos({ 513, 223 });
	m_rtExit->SetBodyRect();

	g_pSndManager->Play("ghost-bgm");
}

void HardwayScene::Update()
{
	if (!m_isStartGhost && !m_isDead)
	{
		m_Player.Update();
	}
	
	g_rtViewPort = g_pDrawHelper->MakeViewPort(m_Player.GetBodyPos(), m_imgWorldBuffer);
	//이벤트 시작
	if ((m_Ghost.GetBodyPos().x - m_Player.GetBodyPos().x) * -1 < 100 && m_isEventStart == true)
	{
		m_isStartGhost = true;
		m_isEventStart = false;
	}
	if (m_isStartGhost)
	{
		m_Ghost.Update();
		m_Ghost.CheckCollision();
		m_Ghost.SetDirection(E_BOTTOM);
		m_Ghost.GhostMove();
		if (m_Ghost.GetBodyPos().y > 429)
		{
			m_Ghost.SetDirection(E_LEFT);
			m_Ghost.GhostMove();
		}
		if (m_Ghost.GetBodyPos().x < 40)
		{
			m_Ghost.SetDirection(E_TOP);
			m_Ghost.GhostMove();
		}
		if (m_Ghost.GetBodyPos().y < 290)
		{
			m_Ghost.SetDirection(E_BOTTOM);
			m_isStartGhost = false;
		}
	}

	if (!m_isEventStart && !m_isStartGhost)
	{
		m_nPusuingDelay--;
		if((m_Ghost.GetBodyPos().x - m_Player.GetBodyPos().x) * -1 < 50)
			m_isPursuing = true;
		if(m_nPusuingDelay < 0)
			m_isPursuing = true;
	}
		
	
	if (m_isPursuing == true)
	{
		m_Ghost.Update();
		m_Ghost.GhostMove();

		if (m_Player.GetBodyPos().x + 5 > m_Ghost.GetBodyPos().x &&
			m_Player.GetBodyPos().x - 5 < m_Ghost.GetBodyPos().x)
			m_isGoingX = false;
		else m_isGoingX = true;

		if(m_isGoingX == true && m_Player.GetBodyPos().x > m_Ghost.GetBodyPos().x)
			m_Ghost.SetDirection(E_RIGHT);
		if (m_isGoingX == true && m_Player.GetBodyPos().x < m_Ghost.GetBodyPos().x)
			m_Ghost.SetDirection(E_LEFT);
		if(m_isGoingX == false && m_Player.GetBodyPos().y < m_Ghost.GetBodyPos().y)
			m_Ghost.SetDirection(E_TOP);
		if (m_isGoingX == false && m_Player.GetBodyPos().y > m_Ghost.GetBodyPos().y)
			m_Ghost.SetDirection(E_BOTTOM);
	}

	//죽음
	RECT rt;
	if (IntersectRect(&rt, &m_Ghost.GetBodyRect(), &m_Player.GetHBoxRect()))
	{
		m_isDead = true;
		m_nRenderShotTime--;

		if (m_isDead && m_nSoundPlayerCount > 0)
		{
			g_pSndManager->Play("ghost-sound");
			m_nSoundPlayerCount--;
		}

		if (m_nRenderShotTime < 0)
		{
			int m_PlayerLife = m_playerData["player"]["hp"];
			m_PlayerLife = 0;
			m_playerData["player"]["hp"] = m_PlayerLife;
			g_pSndManager->Stop("ghost-bgm");
			g_pFileManager->JsonUpdate("player", m_playerData);
			g_pScnManager->SetNextScene("town");
			g_pScnManager->ChangeScene("loading");
		}
	}

	RECT rt2;
	if (IntersectRect(&rt2, &m_rtExit->GetBodyRect(), &m_Player.GetHBoxRect()))
	{
		g_pFileManager->JsonUpdate("player", m_playerData);
		g_pScnManager->SetNextScene("field");
		g_pScnManager->ChangeScene("loading");
	}

	m_nShakePosX = rand() % 10 - 5;
	m_nShakePosY = rand() % 10 - 5;
}

void HardwayScene::Render()
{
	m_imgWorldMap->Render(m_imgWorldBuffer->GetMemDC(), 0, 0);
	m_Ghost.Render(m_imgWorldBuffer->GetMemDC());
	m_Player.Render(m_imgWorldBuffer->GetMemDC());
	m_rtExit->Render(m_imgWorldBuffer->GetMemDC());
	//그려준 버퍼를 뷰포트렌더를 이용해 창 사이즈 만큼만 보이게
	m_imgWorldBuffer->ViewportRender(g_hDC, g_rtViewPort);

	if (m_isDead)
	{
		m_imgGhostShot->Render(g_hDC, m_nShakePosX, m_nShakePosY);
	}
}

void HardwayScene::Release()
{
}
