﻿#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    g_pLogManager->Setup("\\Log\\");
    g_pLogManager->WriteLog(EL_INFO, "MainGame constructor");
    g_pKeyManager->Setup();
    g_pFileManager->JsonLoad(RSC_LIST_KEY, RSC_LIST_PATH);
    g_pImgManager->AddImageList("global");
    while (g_pImgManager->AddImageByJson("global"));

    VerInfoStamp();
    MouseLock();
    Start();

    //  json file load
    InitPlayerData();
}


MainGame::~MainGame()
{
    //  json file save
    g_pLogManager->WriteLog(EL_INFO, "MainGame destructor");
    g_pFileManager->JsonSave("data/player.json", g_pFileManager->JsonFind("player"));
    
    Release();
}

void MainGame::Start()
{
    g_pImgManager->AddImage("ui-buffer", VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    
    g_pScnManager->AddScene("splash", new SplashScene());
    g_pScnManager->AddScene("title", new TitleScene());
    g_pScnManager->AddScene("loading", new LoadingScene());
    g_pScnManager->AddScene("town", new TownScene());
    g_pScnManager->AddScene("field", new FieldScene());
    g_pScnManager->AddScene("escape", new EscapeScene());
    g_pScnManager->AddScene("hardway", new HardwayScene());
    g_pScnManager->AddScene("puzzle", new PuzzleScene());
    g_pScnManager->AddScene("puzzle-game", new PuzzleGameScene());
    g_pScnManager->AddScene("ending-credit", new EndingCreditScene());
    g_pScnManager->AddScene("cookie", new CookieScene());
    g_pScnManager->AddScene("exit", new ExitScene());
    
#ifdef _DEBUG
    g_pScnManager->ChangeScene("splash");
#else
    g_pScnManager->ChangeScene("splash");
#endif // _DEBUG
}

void MainGame::Update()
{
    SystemController();
    
    g_pScnManager->Update();

    GameNode::Update();
}

void MainGame::Render()
{
    PAINTSTRUCT ps;
    HDC hdc;
    hdc = BeginPaint(g_hWnd, &ps);

    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);

    g_pScnManager->Render();
    g_pTimerManager->Render();
    TextOut(g_hDC, 0, W_HEIGHT - 15, m_szVerInfo.c_str(), (int)strlen(m_szVerInfo.c_str()));
    m_pImgBackBuffer->FastRender(hdc);
    
    EndPaint(g_hWnd, &ps);
}

void MainGame::SystemController()
{
}

void MainGame::MouseLock()
{
    RECT Rt;
    GetWindowRect(g_hWnd, &Rt);
    if (PtInRect(&Rt, g_ptMouse))
        ClipCursor(&Rt);
}

void MainGame::MouseUnlock()
{
    ClipCursor(NULL);
}

void MainGame::VerInfoStamp()
{
    json verInfo = g_pFileManager->JsonLoad("data/ver-info.json");
    int majorVer = verInfo["ver"]["major"];
    int minorVer = verInfo["ver"]["minor"];
    int hotfixVer = verInfo["ver"]["hotfix"];
    int buildVer = verInfo["ver"]["build"];
    m_szVerInfo = to_string(majorVer) + "." + to_string(minorVer) + "." + to_string(hotfixVer);
    m_szVerInfo += "-" + to_string(buildVer);
}

void MainGame::Release()
{
    //  KeyManager release
    g_pKeyManager->ReleaseInstance();
    //  LogManager release
    g_pLogManager->ReleaseInstance();
    //  ImageManager release
    g_pImgManager->ReleaseAll();
    g_pImgManager->ReleaseInstance();
    //  SoundManager release
    g_pSndManager->ReleaseAll();
    g_pSndManager->ReleaseInstance();
    //  DrawHelper release
    g_pDrawHelper->ReleaseInstance();
    //  GeometryHelper release
    g_pGeoHelper->ReleaseInstance();
    //  TimerManager release
    g_pTimerManager->DeleteTimerAll();
    g_pTimerManager->ReleaseInstance();
    //  DbManager release
    g_pDbManager->ReleaseInstance();
    //  SceneManager release
    g_pScnManager->ReleaseAll();
}

void MainGame::InitPlayerData()
{
    fstream playerData;
    playerData.open(PLAYER_DATA_PATH, ios_base::in | ios_base::out);
    if (playerData.is_open())
    {
        playerData.close();
        g_pFileManager->JsonLoad("player", PLAYER_DATA_PATH);
    }
    else
    {
        json initPlayerData;
        initPlayerData["player"]["scn-level"] = 0;
        initPlayerData["player"]["hp"] = 5;
        initPlayerData["player"]["atk"] = 1;
        initPlayerData["player"]["potion"] = 5;

        g_pFileManager->JsonSave(PLAYER_DATA_PATH, initPlayerData);
        g_pFileManager->JsonLoad("player", PLAYER_DATA_PATH);
    }
}
