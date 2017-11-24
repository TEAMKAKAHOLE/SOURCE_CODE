#include "stdafx.h"
#include "TownScene.h"


TownScene::TownScene()
{
    m_startPos = { 290, 375 };
    m_objExit.SetBodyRect({ 500, 390, 512, 410 });
    m_isBossLevel = false;
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

    m_scnLevel = m_playerData["player"]["scn-level"];
    if (m_scnLevel >= 4)
    {
        m_isBossLevel = true;
        m_objExit.SetDead();
        m_chief.SetHostile();
    }
}

void TownScene::Update()
{
    if (g_pKeyManager->isOnceKeyDown('1'))
    {
        Item genItem;
        genItem.Start();
        genItem.SetBodyPos(m_player.GetBodyPos());
        genItem.SetActiveTime(g_pTimerManager->GetWorldTime() + 3.0f);
        m_vecItems.push_back(genItem);
    }

    if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
        PostQuitMessage(1);

    m_player.Update();
    m_player.MakeBullet(m_vecBullet, m_player.GetBodyPos());

    m_chief.Update();
    m_chief.MakeBullet(m_vecBullet, m_player.GetBodyPos());

    if (m_chief.GetLife() <= 0)
    {
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
        RECT rt;
        if (IntersectRect(&rt, &m_player.GetHBoxRect(), &iter->GetHBoxRect()) &&
            iter->IsAlive() &&
            iter->GetTagName() == "enemy")
        {
            iter->SetDead();
            m_player.SumLife(-1);
        }

        RECT rt2;
        if (IntersectRect(&rt2, &m_chief.GetHBoxRect(), &iter->GetHBoxRect()) &&
            iter->IsAlive() &&
            iter->GetTagName() == "player")
        {
            if (m_chief.IsAlive() &&
                m_chief.IsHostile())
            {
                iter->SetDead();
                m_chief.SumLife(-1);
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
    
    g_rtViewPort = g_pDrawHelper->MakeViewPort(m_player.GetBodyPos(), m_imgWorldBuffer);
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
}

void TownScene::SaveGame()
{
    m_playerData["player"]["hp"] = m_player.GetLife();
    m_playerData["player"]["potion"] = m_player.GetHealPotion();
    m_playerData["player"]["atk"] = 1;
    m_playerData["player"]["scn-level"] = 0;
    g_pFileManager->JsonSave(PLAYER_DATA_PATH, m_playerData);
}
