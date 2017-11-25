#include "stdafx.h"
#include "TownScene.h"


TownScene::TownScene()
{
    m_startPos = { 290, 375 };
    m_objExit.SetBodyRect({ 500, 390, 512, 410 });
    m_isBossLevel = false;

    g_pSndManager->AddSoundList(m_szTagName);
    while (g_pSndManager->AddSoundByJson(m_szTagName));
}


TownScene::~TownScene()
{
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

    m_player.SetBodyImg(g_pImgManager->FindImage("player"));
    m_player.SetupForSprites(7, 8);
    m_player.StartAnimation();
    m_player.SetBodySize({ 64, 64 });
    m_player.SetBodyPos(m_startPos);
    m_player.SetFrameDelay(6);
    m_player.SetTerrainBuffer(m_imgTerrainBuffer);
    m_player.SetUiBuffer(m_imgUiBuffer);
    m_player.SetHBoxMargin({ 16, 16, 16, 16 });
    m_player.Update();
    m_player.SetLockArea({ 0, 0, 512, 512 });
    m_player.LockInWnd();
    m_player.Start();

    m_chief.Start();
    m_chief.SetVecBullets(&m_vecBullet);
    m_chief.SetPlayerPos(m_player.GetBodyPosRef());

    m_scnLevel = m_playerData["player"]["scn-level"];
    if (m_scnLevel >= 4)
    {
        m_isBossLevel = true;
        m_objExit.SetDead();
        m_chief.SetHostile();
    }

    g_pSndManager->Play("town");
}

void TownScene::Update()
{
    if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
        PostQuitMessage(1);

    m_player.Update();
    m_player.MakeBullet(m_vecBullet, m_player.GetBodyPos());
    m_viewportPos = m_player.GetBodyPos();

    m_chief.Update();

    if (m_chief.GetLife() <= 0)
    {
        m_vecBullet.clear();
        m_chief.SetDead();
        m_scnLevel = 5;
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
        if (iter->GetDamage() == 5)
        {
            cout << "timebomb" << endl;
        }
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

#ifdef _DEBUG
    string bulletCnt = to_string((int)m_vecBullet.size());
    TextOut(g_hDC, W_WIDTH - 20, 45, bulletCnt.c_str(), (int)strlen(bulletCnt.c_str()));
#endif // _DEBUG
}

void TownScene::Release()
{
    SaveGame();
    g_pSndManager->Stop("town");
}

void TownScene::SaveGame()
{
    m_playerData["player"]["hp"] = m_player.GetLife();
    m_playerData["player"]["potion"] = m_player.GetHealPotion();
    m_playerData["player"]["atk"] = 1;
    m_playerData["player"]["scn-level"] = 0;
    g_pFileManager->JsonSave(PLAYER_DATA_PATH, m_playerData);
}
