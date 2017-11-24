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
	m_playerData = g_pFileManager->JsonFind("player");
	m_vecEnemy.clear();
    m_isClear = false;
	m_isBill = false;
	m_isError = false;

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
	m_imgBill = g_pImgManager->FindImage("bill");
	m_imgError = g_pImgManager->FindImage("error");

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
	m_nscnLevel = m_playerData["player"]["scn-level"];

	if (m_nscnLevel == 0)
	{
		for (int i = 0; i <= 3; ++i)
		{
			MakeEnemy(i);
		}
	}
	else
	{
		for (int i = 0; i <= 5; ++i)
		{
			MakeEnemy(i);
		}

	}

	m_imgAutoButton = new SpritesObject;
	m_imgAutoButton->SetBodyImg( g_pImgManager->FindImage("auto-button"));
	m_imgAutoButton->SetupForSprites(1, 1);
	m_imgAutoButton->SetBodyPos({650,600});
	m_imgAutoButton->SetBodySize({ 130,50 });
	m_imgAutoButton->SetAlpha(150);

	m_imgClose = new SpritesObject;
	m_imgClose->SetBodyImg(g_pImgManager->FindImage("close"));
	m_imgClose->SetupForSprites(1, 1);
	m_imgClose->SetBodyPos({ 100,470});
	m_imgClose->SetBodySize({ 30,15 });

	m_imgXbox = new SpritesObject;
	m_imgXbox->SetBodyImg(g_pImgManager->FindImage("Xbox"));
	m_imgXbox->SetupForSprites(1, 1);
	m_imgXbox->SetBodyPos({ 660,110 });
	m_imgXbox->SetBodySize({ 50,50 });
	
	
	
	m_rtTownPortal = g_pDrawHelper->MakeRect({ 0,400 }, { 30,70 });
	m_rtEscapePortal = g_pDrawHelper->MakeRect({ 500,380 }, { 20,130 });


}

void FieldScene::Update()  
{
	m_player.Update();
	m_imgAutoButton->Update();
	m_imgClose->Update();
	m_imgXbox->Update();
    m_player.MakeBullet(m_vecBullets, m_player.GetBodyPos());
	
	for (auto iter = m_vecEnemy.begin(); iter != m_vecEnemy.end(); ++iter)
	{
		iter->Update();
	}
	
    if (m_isClear)
    {      
        RECT rt;
        if (IntersectRect(&rt, &m_rtTownPortal, &m_player.GetHBoxRect()))
        {
            if (m_nscnLevel == 0)
            {
				m_nscnLevel = 1;
                g_pScnManager->SetNextScene("town");
                g_pScnManager->ChangeScene("loading");
                m_playerData["player"]["scn-level"] = m_nscnLevel;
                g_pFileManager->JsonUpdate("player", m_playerData);
            }
            else
            {
                g_pScnManager->SetNextScene("puzzle");
                g_pScnManager->ChangeScene("loading");
            }
        }

        RECT rt2;
        if (IntersectRect(&rt2, &m_rtEscapePortal, &m_player.GetHBoxRect()))
        {
            if (m_nscnLevel != 0)
            {
                g_pScnManager->SetNextScene("escape");
                g_pScnManager->ChangeScene("loading");
            }
        }
    }

    for (auto iterBullet = m_vecBullets.begin(); iterBullet != m_vecBullets.end(); iterBullet++)
    {
        iterBullet->Update();
        RECT rt;
        if (IntersectRect(&rt, &m_player.GetHBoxRect(), &iterBullet->GetHBoxRect()) &&
            iterBullet->IsAlive() &&
            iterBullet->GetTagName() == "enemy")
        {
            iterBullet->SetDead();
            m_player.SumLife(-1);
        }

        for (auto iterEnemy = m_vecEnemy.begin(); iterEnemy != m_vecEnemy.end(); ++iterEnemy)
        {
            RECT rt2;
			double dbAngle = 0.0f;

            if (IntersectRect(&rt2, &iterEnemy->GetHBoxRect(), &iterBullet->GetHBoxRect()) &&
                iterBullet->IsAlive() &&
                iterBullet->GetTagName() == "player")
            {
                iterBullet->SetDead();
                iterEnemy->SumLife(-1);

				dbAngle = g_pGeoHelper->GetAngleFromCoord(iterEnemy->GetBodyPos(), m_player.GetBodyPos());
				iterEnemy->SetBodySpeed(g_pGeoHelper->GetCoordFromAngle(-dbAngle, -7.0f));
            }		
        }
    }

	
	for (auto iterEnemy = m_vecEnemy.begin(); iterEnemy != m_vecEnemy.end(); ++iterEnemy)
	{
		RECT rt3;
		//적이 플레이어를 따라온다
		if (IntersectRect(&rt3, &iterEnemy->GetAwarenessRect(), &m_player.GetHBoxRect()))
		{
			iterEnemy->SetTrackingPlayer(true);

			if (iterEnemy->GetTrackingPlayer() == true)
			{
				m_dbAngle = g_pGeoHelper->GetAngleFromCoord(iterEnemy->GetBodyPos(), m_player.GetBodyPos());
				iterEnemy->SetBodySpeed(g_pGeoHelper->GetCoordFromAngle(-m_dbAngle, 0.5f));			
			}
		}
		else
			iterEnemy->SetTrackingPlayer(false);
	
		/*RECT rt5;
		double dbAngle1 = 0.0f;
		if (IntersectRect(&rt5, &iterEnemy->GetHBoxRect(), &m_player.GetHBoxRect()))
		{
			dbAngle1 = g_pGeoHelper->GetAngleFromCoord(iterEnemy->GetBodyPos(), m_player.GetBodyPos());
			m_player.SetBodySpeed(g_pGeoHelper->GetCoordFromAngle(-dbAngle1, -7.0f));
		}*/
	}

    CheckClear();

    //  적 제거
    for (auto iterEnemy = m_vecEnemy.begin(); iterEnemy != m_vecEnemy.end();)
    {
        if (iterEnemy->IsAlive() == false)
        {
            iterEnemy = m_vecEnemy.erase(iterEnemy);
        }
        else
        {
            ++iterEnemy;
        }
    }

    //  총알 제거
    for (auto iterBullet = m_vecBullets.begin(); iterBullet != m_vecBullets.end();)
    {
        if (iterBullet->IsAlive() == false)
        {
            iterBullet = m_vecBullets.erase(iterBullet);
        }
        else
        {
            ++iterBullet;
        }
    }

	//오토 창 띄우기
	if (PtInRect(&m_imgAutoButton->GetBodyRect(), g_ptMouse))
	{
		if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
		{
			m_isBill = true;
		}
	}

	if (PtInRect(&m_imgClose->GetBodyRect(), g_ptMouse))
	{
		if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
		{
			m_isBill = false;
			m_isError = false;
		}
	}
	if (PtInRect(&m_imgXbox->GetBodyRect(), g_ptMouse))
	{
		if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
		{
			m_isError = true;
		}
	}


	//맵 움직이기
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

    for (auto iter = m_vecBullets.begin(); iter != m_vecBullets.end(); iter++)
    {
        iter->Render(m_imgWorldBuffer->GetMemDC());
    }

	m_player.Render(m_imgWorldBuffer->GetMemDC());
	m_imgWorldBuffer->ViewportRender(g_hDC, g_rtViewPort);
	m_imgAutoButton->Render(g_hDC);
	if (m_isBill == true)
	{
		m_imgBill->AlphaRender(g_hDC, W_WIDTH / 2 - 300, W_HEIGHT / 2 - 250, 600, 400, 255);
		m_imgClose->Render(g_hDC);
		m_imgXbox->Render(g_hDC);
	}
	if (m_isError == true)
	{
		m_imgError->Render(g_hDC, W_WIDTH / 2 - 200, W_HEIGHT / 2 - 150, 360, 140);
	}
}

void FieldScene::Release()
{
}

void FieldScene::MakeEnemy(int count)
{
	if (count)
	{		
        m_enemy.SetBodyPos({ (double)GetRandom(100, 500), (double)m_nEnemyPosY[rand() % 5] });
		
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

void FieldScene::SaveGame()
{
    m_playerData["player"]["hp"] = m_player.GetLife();
    m_playerData["player"]["potion"] = m_player.GetHealPotion();
    g_pFileManager->JsonSave(PLAYER_DATA_PATH, m_playerData);
}

void FieldScene::CheckClear() //적 다 죽으면 클리어
{
    if (m_isClear == false)
    {
        //  enemy count
        int remainEnemies = (int)m_vecEnemy.size();
        if (remainEnemies == 0)
        {
            m_isClear = true;
        }
    }
}
