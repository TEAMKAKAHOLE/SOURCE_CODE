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
	m_player.Update();
    m_player.MakeBullet(m_vecBullets, m_player.GetBodyPos());

	for (auto iter = m_vecEnemy.begin(); iter != m_vecEnemy.end(); ++iter)
	{
		iter->Update();
	}

    if (m_isClear)
    {
        int scnLevel = m_playerData["player"]["scn-level"];

        RECT rt;
        if (IntersectRect(&rt, &m_rtTownPortal, &m_player.GetHBoxRect()))
        {
            if (scnLevel == 0)
            {
                scnLevel = 1;
                g_pScnManager->SetNextScene("town");
                g_pScnManager->ChangeScene("loading");
                m_playerData["player"]["scn-level"] = scnLevel;
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
            if (scnLevel != 0)
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
            if (IntersectRect(&rt2, &iterEnemy->GetHBoxRect(), &iterBullet->GetHBoxRect()) &&
                iterBullet->IsAlive() &&
                iterBullet->GetTagName() == "player")
            {
                iterBullet->SetDead();
                iterEnemy->SumLife(-1);
            }
        }
    }

    for (auto itemIter = m_vecItems.begin(); itemIter != m_vecItems.end(); itemIter++)
    {
        itemIter->Update();

        RECT rt;
        if (IntersectRect(&rt, &m_player.GetHBoxRect(), &itemIter->GetHBoxRect()))
        {
            if (itemIter->IsActive())
            {
                itemIter->SetDead();
                itemIter->Deactivate();
            }
        }
    }

    CheckClear();

    //  적 제거
    for (auto iterEnemy = m_vecEnemy.begin(); iterEnemy != m_vecEnemy.end();)
    {
        if (iterEnemy->IsAlive() == false)
        {
            Item genItem;
            genItem.Start();
            genItem.SetBodyPos(iterEnemy->GetBodyPos());
            genItem.Activate();
            m_vecItems.push_back(genItem);
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

    for (auto itemIter = m_vecItems.begin(); itemIter != m_vecItems.end();)
    {
        if (itemIter->IsAlive() == false)
        {
            itemIter = m_vecItems.erase(itemIter);
            m_player.SumHealPotion(1);
        }
        else
        {
            ++itemIter;
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
	}

    for (auto iter = m_vecBullets.begin(); iter != m_vecBullets.end(); iter++)
    {
        iter->Render(m_imgWorldBuffer->GetMemDC());
    }

    for (auto itemIter = m_vecItems.begin(); itemIter != m_vecItems.end(); itemIter++)
    {
        itemIter->Render(m_imgWorldBuffer->GetMemDC());
    }

	m_player.Render(m_imgWorldBuffer->GetMemDC());
	m_imgWorldBuffer->ViewportRender(g_hDC, g_rtViewPort);
}

void FieldScene::Release()
{
    m_playerData["player"]["potion"] = m_player.GetHealPotion();
    g_pFileManager->JsonUpdate("player", m_playerData);
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

void FieldScene::CheckClear()
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
