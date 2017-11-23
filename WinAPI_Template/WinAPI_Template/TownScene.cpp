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

    //  world map
    m_imgWorldBuffer = g_pImgManager->AddImage("town-map-buffer", 512, 512);
    m_imgWorldMap = g_pImgManager->FindImage("town-map");
    m_imgTerrainBuffer = g_pImgManager->FindImage("town-terrain");

    //  ui
    m_imgUiBuffer = g_pImgManager->FindImage("ui-buffer");
    m_imgHud = g_pImgManager->FindImage("hud");
    m_sprHudNumber = new SpritesObject;
    m_sprHudNumber->SetBodyImg(g_pImgManager->FindImage("hud-number"));
    m_sprHudNumber->SetupForSprites(10, 1);
    m_sprHudLife = new SpritesObject;
    m_sprHudLife->SetBodyImg(g_pImgManager->FindImage("hud-life"));
    m_sprHudLife->SetupForSprites(3, 1);

    m_player.SetBodyImg(g_pImgManager->FindImage("player"));
    m_player.SetupForSprites(7, 8);
    m_player.StartAnimation();
    m_player.SetBodySize({ 64, 64 });
    m_player.SetBodyPos(m_startPos);
    m_player.SetFrameDelay(6);
    m_player.SetTerrainBuffer(m_imgTerrainBuffer);
    m_player.SetHBoxMargin({ 16, 16, 16, 16 });
    m_player.Update();
    m_player.SetLockArea({ 0, 0, 512, 512 });
    m_player.LockInWnd();

    m_chief.Start();

    int scnLevel = m_playerData["player"]["scn-level"];
    if (scnLevel >= 4)
    {
        m_isBossLevel = true;
        m_objExit.SetDead();
        m_chief.SetHostile();
    }
}

void TownScene::Update()
{
    if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
        PostQuitMessage(1);

    m_player.Update();
    m_chief.Update();
    m_chief.MakeBullet(m_vecBullet, m_player.GetBodyPos());

    if (m_objExit.IsAlive())
    {
        int scnLevel = m_playerData["player"]["scn-level"];

        RECT rt;
        if (IntersectRect(&rt, &m_objExit.GetBodyRect(), &m_player.GetBodyRect()))
        {
            if (scnLevel == 0)
            {
                g_pScnManager->SetNextScene("field");
            }
            else
            {
                g_pScnManager->SetNextScene("puzzle");
            }
            g_pScnManager->ChangeScene("loading");
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
            iter->SetDead();
            m_chief.SumLife(-1);
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

    for (auto iter = m_vecBullet.begin(); iter != m_vecBullet.end(); iter++)
    {
        iter->Render(m_imgWorldBuffer->GetMemDC());
    }

    //  world render
    m_imgWorldBuffer->ViewportRender(g_hDC, g_rtViewPort);

    //  ui render
    m_imgHud->FastRender(m_imgUiBuffer->GetMemDC(), 0, 0);
    //  180, 25
    //  life
    int marginX = 180;
    int marginY = 25;
    for (int i = 0; i < m_player.GetLife(); i++)
    {
        m_sprHudLife->GetBodyImg()->SpritesRender(m_imgUiBuffer->GetMemDC()
            , marginX + i * 10, marginY
            , 7, 7
            , 0, 0
            , 255.0f);
    }

    //  65, 24
    //  number
    m_sprHudNumber->GetBodyImg()->SpritesRender(m_imgUiBuffer->GetMemDC()
        , { 85, 28 }
        , { 7, 7 }
        , m_player.GetHealPotion()
        , 255.0f);

    m_imgUiBuffer->TransRender(g_hDC, 0, 0, W_WIDTH, W_HEIGHT);

    string bulletCnt = to_string((int)m_vecBullet.size());
    TextOut(g_hDC, W_WIDTH - 20, 45, bulletCnt.c_str(), (int)strlen(bulletCnt.c_str()));
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
