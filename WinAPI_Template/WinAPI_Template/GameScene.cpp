#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene()
{
    m_currPlace = STORE_END;
    m_szTagName = "rpg";
    g_pImgManager->AddImage("rpg-ui-buffer", 200, W_HEIGHT);
    g_pImgManager->AddImage("rpg-world-buffer", 1500, 1500);
}

GameScene::~GameScene()
{
}

void GameScene::Start()
{
    g_pSndManager->Play("rpg-bgm");
    m_uiBuffer = g_pImgManager->FindImage("rpg-ui-buffer");
    m_gameBoardBuffer = g_pImgManager->FindImage("rpg-world-buffer");

    g_pDrawHelper->m_textBoxInfo = { true, {0, 0, 0, 0}, {255, 255, 255, 255}, "Consolas" };

    //  map setup
    m_map.SetBodyImg(g_pImgManager->FindImage("rpg-map-texture"));

    //  player setup
    m_player.Start();

    //  store setup
    m_storeEntrance.Setup({ 100.0f, 100.0f }, { 200, 200 });
    m_storeEntrance.SetBodyImg(g_pImgManager->FindImage("rpg-store"));
    m_storeEntrance.SetupForSprites(1, 1);
    m_store.Start();

    //  armory setup
    m_armoryEntrance.Setup({ 100.0f, 800.0f }, { 200, 200 });
    m_armoryEntrance.SetBodyImg(g_pImgManager->FindImage("rpg-armory"));
    m_armoryEntrance.SetupForSprites(1, 1);

    //  dungeon 1 setup
    m_dungeon1.Setup({ 500.0f, 100.0f }, { 200, 200 });
    m_dungeon1.SetBodyImg(g_pImgManager->FindImage("rpg-dungeon-1"));
    m_dungeon1.SetupForSprites(1, 1);

    //  dungeon 2 setup
    m_dungeon2.Setup({ 500.0f, 800.0f }, { 200, 200 });
    m_dungeon2.SetBodyImg(g_pImgManager->FindImage("rpg-dungeon-2"));
    m_dungeon2.SetupForSprites(1, 1);

    NewGame();
}

void GameScene::Update()
{
    m_currPlace = STORE_END;

    //  player collision
    RECT rt;
    if (IntersectRect(&rt, &m_player.GetBodyRect(), &m_storeEntrance.GetBodyRect()))
    {
        m_currPlace = STORE;
        m_store.SetStore();
        m_store.SetupData();
    }
    else if (IntersectRect(&rt, &m_player.GetBodyRect(), &m_armoryEntrance.GetBodyRect()))
    {
        m_currPlace = ARMORY;
        m_store.SetArmory();
        m_store.SetupData();
    }
    else if (IntersectRect(&rt, &m_player.GetBodyRect(), &m_dungeon1.GetBodyRect()))
    {
        json playerData = g_pFileManager->JsonFind("player-data");
        playerData["dungeon"]["level"] = 1;
        g_pFileManager->JsonUpdate("player-data", playerData);
        g_pScnManager->SetNextScene("dungeon");
        g_pScnManager->ChangeScene("loading");
    }
    else if (IntersectRect(&rt, &m_player.GetBodyRect(), &m_dungeon2.GetBodyRect()))
    {
        json playerData = g_pFileManager->JsonFind("player-data");
        playerData["dungeon"]["level"] = 2;
        g_pFileManager->JsonUpdate("player-data", playerData);
        g_pScnManager->SetNextScene("dungeon");
        g_pScnManager->ChangeScene("loading");
    }

    //  player update
    PlayerController();
    m_player.Update();

    if (m_currPlace != ITEM_END)
        m_store.Update();

    //  viewport update
    g_rtViewPort = g_pDrawHelper->MakeViewPort(m_player.GetBodyPos(), { 0, 0, 200, 0 }, m_gameBoardBuffer);
}

void GameScene::Render()
{
    PatBlt(m_uiBuffer->GetMemDC(), 0, 0, 200, W_HEIGHT, WHITENESS);
    m_map.GetBodyImg()->TransRender(m_gameBoardBuffer->GetMemDC()
        , 0, 0
        , m_gameBoardBuffer->GetWidth(), m_gameBoardBuffer->GetHeight());

    m_storeEntrance.Render(m_gameBoardBuffer->GetMemDC());
    m_armoryEntrance.Render(m_gameBoardBuffer->GetMemDC());
    m_dungeon1.Render(m_gameBoardBuffer->GetMemDC());
    m_dungeon2.Render(m_gameBoardBuffer->GetMemDC());

    m_player.Render(m_gameBoardBuffer->GetMemDC());

    m_gameBoardBuffer->ViewportRender(g_hDC, g_rtViewPort);
    m_uiBuffer->TransRender(g_hDC, W_WIDTH - 200, 0);

    if (m_currPlace != ITEM_END)
        StoreRender();

#ifdef _DEBUG
    TextOut(g_hDC, W_WIDTH - 100, 0, m_szTagName.c_str(), (int)strlen(m_szTagName.c_str()));
#endif // _DEBUG
}

void GameScene::Release()
{
    json playerData = g_pFileManager->JsonFind("player-data");
    if (playerData != nullptr)
        g_pFileManager->JsonSave("data/data-player.json", playerData);
}

void GameScene::NewGame()
{
}

void GameScene::SaveGame()
{
    //  empty json instance
    json saveDatas;

    g_pFileManager->JsonSave("data\\savedata.json", saveDatas);
}

bool GameScene::LoadGame()
{
    NewGame();

    return true;
}

void GameScene::PlayerController()
{
    if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
    {
        g_pScnManager->ChangeScene("title");
    }

    if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
    {
        int itemId = m_store.GetClickedItem();
    }

    if (g_pKeyManager->isOnceKeyDown('P'))
    {
        g_pSndManager->PlayAndPause("bgm");
    }
}

void GameScene::StoreRender()
{
    m_store.Render(g_hDC);
}