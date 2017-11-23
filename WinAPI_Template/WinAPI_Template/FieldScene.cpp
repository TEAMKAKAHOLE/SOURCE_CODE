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
	m_vecEnemy.clear();

	m_nEnemyPosY[0] = 420;
	m_nEnemyPosY[1] = 340;
	m_nEnemyPosY[2] = 350;
	m_nEnemyPosY[3] = 370;
	m_nEnemyPosY[4] = 430;

	m_dbAngle = 0.0f;

	m_dbCoordFromeAngle = 0;

	m_imgWorldBuffer = g_pImgManager->AddImage("WorldBuffer", 512, 512);

	m_imgWorldBuffer = g_pImgManager->FindImage("WorldBuffer");
	m_imgWorldMap = g_pImgManager->FindImage("field-map");
	m_imgTerrainBuffer = g_pImgManager->FindImage("field-map-magenta");

	m_player.SetBodyImg(g_pImgManager->FindImage("player"));
	m_player.SetBodyPos({ 50, 400 });
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
	m_enemy.SetTerrainBuffer(m_imgTerrainBuffer);

	for (int i = 0; i <= 5; ++i)
	{
		MakeEnemy(i);
	}
	
	m_rtTownPortal = g_pDrawHelper->MakeRect({ 0,400 }, { 30,70 });
	m_rtEscapePortal = g_pDrawHelper->MakeRect({ 500,380 }, { 20,130 });

	m_isTutorial = false;
}



void FieldScene::Update()  
{
	RECT rt;

	m_player.Update();

	for (auto iter = m_vecEnemy.begin(); iter != m_vecEnemy.end(); ++iter)
	{
		iter->Update();
		
	}
	
	if (IntersectRect(&rt, &m_rtTownPortal, &m_player.GetBodyRect()))
	{
		g_pScnManager->SetNextScene("town");
		g_pScnManager->ChangeScene("loading");
	}


	if (IntersectRect(&rt, &m_rtEscapePortal, &m_player.GetBodyRect()))
	{
		if (m_isTutorial == false)
		{
			g_pScnManager->SetNextScene("escape");
			g_pScnManager->ChangeScene("loading");
		}
	}


	for (auto iter = m_vecEnemy.begin(); iter != m_vecEnemy.end(); ++iter)
	{

		/*if (IntersectRect(&rt, &iter->GetAwarenessRect(), &m_player.GetBodyRect()))
		{
			m_dbAngle = g_pGeoHelper->GetAngleFromCoord(iter->GetBodyPos(), m_player.GetBodyPos());
			g_pGeoHelper->GetCoordFromAngle(m_dbAngle, 5.0f);
			iter->SetBodySpeed(g_pGeoHelper->GetCoordFromAngle(m_dbAngle, 5.0f));
		}*/

		if (IntersectRect(&rt, &iter->GetBodyRect(), &m_player.GetAtkArea()))
		{
			iter->SumLife(-1);
			if (iter->GetLife() == 0)
			{
				m_vecEnemy.erase(iter);
				break;
			}
		}
	}

	//¸Ê ¿òÁ÷ÀÌ±â
	g_rtViewPort = g_pDrawHelper->MakeViewPort(m_player.GetBodyPos(), m_imgWorldBuffer);
	
}

void FieldScene::Render()
{
	m_imgWorldMap->Render(m_imgWorldBuffer->GetMemDC(), 0, 0);
	g_pDrawHelper->DrawRect(m_imgWorldBuffer->GetMemDC(), m_rtTownPortal);

	g_pDrawHelper->DrawRect(m_imgWorldBuffer->GetMemDC(), m_rtEscapePortal);


	for (auto iter = m_vecEnemy.begin(); iter != m_vecEnemy.end(); ++iter)
	{
		iter->Render(m_imgWorldBuffer->GetMemDC());
		g_pDrawHelper->DrawRect(m_imgWorldBuffer->GetMemDC(), m_rtAwareness);

	}

	m_player.Render(m_imgWorldBuffer->GetMemDC());
	m_imgWorldBuffer->ViewportRender(g_hDC, g_rtViewPort);
}

void FieldScene::Release()
{
}

void FieldScene::MakeEnemy(int count)
{
	if (count)
	{		
		m_enemy.SetBodyPos({ (double)GetRandom(100,500),(double)m_nEnemyPosY[rand() % 5]});
		
		m_enemy.SetBodySize({ 64, 64 });
		m_enemy.SetupForSprites(4, 4);
		m_enemy.SetFrameDelay(3);
		m_enemy.StartAnimation();
		m_enemy.Update();
		m_enemy.SetHBoxMargin({ 16, 16, 16, 16 });
		m_enemy.SetLockArea({ 0, 210, 512, 512 });
		m_enemy.LockInWnd();
			
		m_vecEnemy.push_back(m_enemy);
	}

	
}

int FieldScene::GetRandom(int min, int max)
{
	// 0 ~ 5 : 5 - 0 + 1 => 0 ~ 5
	// 5 ~ 9 : 9 - 5 + 1 => 0 ~ 4 + 5 => 5 ~ 9
	return rand() % (max - min + 1) + min;
}
