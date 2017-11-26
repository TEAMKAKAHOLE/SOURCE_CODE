#include "stdafx.h"
#include "TownScene.h"


TownScene::TownScene()
{
    m_sprFadeout = new SpritesObject;
    m_sprFadeout->SetBodyImg(g_pImgManager->FindImage("fade-out"));
    m_sprFadeout->SetAlpha(0.0f);
    m_dFadeoutAlpha = 0.0f;

    m_startPos = { 290, 375 };
    m_objExit.SetBodyRect({ 500, 390, 512, 410 });
    m_isBossLevel = false;
    m_isGameClear = false;

    g_pSndManager->AddSoundList(m_szTagName);
    while (g_pSndManager->AddSoundByJson(m_szTagName));

	m_nSoundPlayCount = 1;
}


TownScene::~TownScene()
{
    if (m_sprFadeout != NULL)
        SAFE_DELETE(m_sprFadeout);
}

void TownScene::Start()
{
    //  json load
    m_playerData = g_pFileManager->JsonFind("player");

    //  clear
    m_vecBullet.clear();
    m_vecItems.clear();

    //  world map
    m_imgWorldBuffer = g_pImgManager->AddImage("town-map-buffer", 512, 512);
    m_imgWorldMap = g_pImgManager->FindImage("town-map");
    m_imgTerrainBuffer = g_pImgManager->FindImage("town-terrain");

    //  ui
    m_imgUiBuffer = g_pImgManager->FindImage("ui-buffer");

    m_player.SetBodyPos(m_startPos);
    m_player.SetTerrainBuffer(m_imgTerrainBuffer);
    m_player.SetUiBuffer(m_imgUiBuffer);
    m_player.Start();

    m_chief.Start();
    m_chief.SetVecBullets(&m_vecBullet);
    m_chief.SetPlayerPos(m_player.GetBodyPosRef());

    m_player.SetLife(m_playerData["player"]["hp"]);
    m_player.SetAtkDamage(m_playerData["player"]["atk"]);
    m_player.SetHealPotion(m_playerData["player"]["potion"]);
    m_scnLevel = m_playerData["player"]["scn-level"];


    if (m_scnLevel >= 4)
    {
        m_isBossLevel = true;
        m_objExit.SetDead();
        m_chief.SetHostile();
		g_pSndManager->Play("boss");
    }
	else
		g_pSndManager->Play("town");
}

void TownScene::Update()
{
    if (m_isGameClear)
    {
        m_dFadeoutAlpha += 1.0f;
        if (m_dFadeoutAlpha >= 255.0f)
        {
            g_pSndManager->Stop("boss");
            g_pScnManager->ChangeScene("ending-credit");
            m_dFadeoutAlpha = 255.0f;
        }

        m_sprFadeout->SetAlpha(m_dFadeoutAlpha);
    }

    if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
        PostQuitMessage(1);

    if (m_chief.IsHostile())
    {
        if (m_player.IsAlive() == false)
        {
            g_pScnManager->SetNextScene("escape");
            g_pScnManager->ChangeScene("loading");
        }
    }

    m_player.Update();
    m_player.MakeBullet(m_vecBullet, m_player.GetBodyPos());
    m_viewportPos = m_player.GetBodyPos();

    m_chief.Update();

    if (m_chief.GetLife() <= 0)
    {
        m_vecBullet.clear();
        m_chief.SetDead();
        m_scnLevel = 5;
        m_isGameClear = true;
    }

    if (m_objExit.IsAlive())
    {
        int scnLevel = m_playerData["player"]["scn-level"];

        RECT rt;
        if (IntersectRect(&rt, &m_objExit.GetBodyRect(), &m_player.GetBodyRect()))
        {
            if (scnLevel == 0)
                g_pScnManager->SetNextScene("field");
            else
                g_pScnManager->SetNextScene("puzzle");

            g_pScnManager->ChangeScene("loading");
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

    for (auto itemIter = m_vecItems.begin(); itemIter != m_vecItems.end();)
    {
        if (itemIter->IsAlive() == false)
        {
            itemIter = m_vecItems.erase(itemIter);
        }
        else
        {
            ++itemIter;
        }
    }

    for (auto iter = m_vecBullet.begin(); iter != m_vecBullet.end(); iter++)
    {
        iter->Update();

        RECT rt;
        if (IntersectRect(&rt, &m_player.GetHBoxRect(), &iter->GetHBoxRect()) &&
            iter->IsAlive() &&
            iter->IsActivate() && 
            iter->GetTagName() == "enemy")
        {
            iter->SetDead();
            if (m_player.IsImmortal())
                iter->SetDamage(0);
            m_player.SumLife(-iter->GetDamage());
        }

        RECT rt2;
        if (IntersectRect(&rt2, &m_chief.GetHBoxRect(), &iter->GetHBoxRect()) &&
            iter->IsAlive() &&
            iter->IsActivate() &&
            iter->GetTagName() == "player")
        {
			if (m_chief.IsAlive() &&
				m_chief.IsHostile())
			{
				m_chief.SumLife(-iter->GetDamage());
				if (iter->GetDamage() > 0)
				{
					if (m_nSoundPlayCount > 0)
					{
						g_pSndManager->Play("hit");
						m_nSoundPlayCount--;
					}
					
					iter->SetDamage(0);
					iter->SetBodySpeed({ 0.0f, 0.0f });
					iter->SetBodySize({ 32, 32 });
					iter->SetHBoxMargin({ 0, 0, 0, 0 });
					iter->SetBodyImg(g_pImgManager->FindImage("moon-slash-particle"));
					iter->SetupForSprites(2, 1);
					iter->StartAnimation();
					iter->SetFrameDelay(6);
					iter->SetGenTime(g_pTimerManager->GetWorldTime());
					iter->SetExistTime(0.2f);
				}
			}
        }
    }

    for (auto iter = m_vecBullet.begin(); iter != m_vecBullet.end();)
    {
        if (iter->IsAlive() == false)
            iter = m_vecBullet.erase(iter);
        else
            ++iter;
    }
    
    if (m_scnLevel == 5)
    {
        m_viewportPos.x += rand() % 10 - 5;
        m_viewportPos.y += rand() % 10 - 5;
        if (m_fEndTimer < g_pTimerManager->GetWorldTime())
            g_pScnManager->ChangeScene("exit");
    }
    else
    {
        m_fEndTimer = g_pTimerManager->GetWorldTime() + 5.0f;
    }

	m_nSoundPlayCount = 1;
    g_rtViewPort = g_pDrawHelper->MakeViewPort(m_viewportPos, m_imgWorldBuffer);
}

void TownScene::Render()
{
    m_imgWorldMap->Render(m_imgWorldBuffer->GetMemDC(), 0, 0);
    m_player.Render(m_imgWorldBuffer->GetMemDC());
    m_chief.Render(m_imgWorldBuffer->GetMemDC());

    for (auto itemIter = m_vecItems.begin(); itemIter != m_vecItems.end(); itemIter++)
    {
        itemIter->Render(m_imgWorldBuffer->GetMemDC());
    }

    for (auto iter = m_vecBullet.begin(); iter != m_vecBullet.end(); iter++)
    {
        iter->Render(m_imgWorldBuffer->GetMemDC());
    }

    //  world render
    m_imgWorldBuffer->ViewportRender(g_hDC, g_rtViewPort);
    
    m_imgUiBuffer->TransRender(g_hDC, 0, 0, W_WIDTH, W_HEIGHT);

    if (m_isGameClear)
    {
        m_sprFadeout->GetBodyImg()->AlphaRender(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, (BYTE)m_sprFadeout->GetAlpha());
        return;
    }
#ifdef _DEBUG
    string bulletCnt = to_string((int)m_vecBullet.size());
    TextOut(g_hDC, W_WIDTH - 20, 45, bulletCnt.c_str(), (int)strlen(bulletCnt.c_str()));
#endif // _DEBUG
}

void TownScene::Release()
{
    SaveGame();
    g_pSndManager->Stop("town");
	g_pSndManager->Stop("boss");
}

void TownScene::SaveGame()
{
    m_playerData["player"]["hp"] = m_player.GetLife();
    m_playerData["player"]["potion"] = m_player.GetHealPotion();
    m_playerData["player"]["atk"] = 1;
    m_playerData["player"]["scn-level"] = 0;
    g_pFileManager->JsonSave(PLAYER_DATA_PATH, m_playerData);
}
