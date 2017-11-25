#include "stdafx.h"
#include "EscapeScene.h"
#include "Player.h"
#include "TelePort.h"
#include "Enemy.h"

EscapeScene::EscapeScene()
{
}


EscapeScene::~EscapeScene()
{
}

void EscapeScene::Start()
{
    SetData();

    m_imgWorldBuffer     = g_pImgManager->AddImage("eacape-map-buffer", 512, 512);
    m_imgWorldMap        = g_pImgManager->FindImage("escape-map");
    m_imgTerrainBuffer   = g_pImgManager->FindImage("escape-terrain");
    m_imgUiBuffer = g_pImgManager->FindImage("ui-buffer");

    m_player.SetBodyPos({ 350.0f, 390.0f });
    m_player.SetTerrainBuffer(m_imgTerrainBuffer);
    m_player.SetUiBuffer(m_imgUiBuffer);
    m_player.Start();

    m_teleportA.SetBodyPos({ 385.0f, 300.0f });
    m_teleportA.SetBodySize({ 20, 20 });
    m_teleportB.SetBodyPos({ 418.0f, 190.0f });
    m_teleportB.SetBodySize({ 20, 20 });
    m_teleportC.SetBodyPos({ 255.0f, 250.0f });
    m_teleportC.SetBodySize({ 20, 20 });
    m_teleportD.SetBodyPos({ 95.0f, 285.0f });
    m_teleportD.SetBodySize({ 20, 20 });

    //next Scene 이동위한 Endpoint
    m_EndPoint.SetBodyPos({ 80.0f, 170.0f });
    m_EndPoint.SetBodySize({ 20, 20 });
    m_StartPoint.SetBodyPos({ 350.0f, 390.0f });
    m_StartPoint.SetBodySize({ 20, 20 });

    //Item 초기위치,bool 설정
    m_KeyItem1.SetBodyImg(g_pImgManager->FindImage("keyItem"));
    m_KeyItem1.SetupForSprites(1, 1);
    m_KeyItem1.StartAnimation();
    m_KeyItem1.SetBodySize({ 46, 46 });
    m_KeyItem1.SetBodyPos({ 420.0f, 260.0f });
    m_bKeyItem1 = false;

    m_BackScene.SetBodyImg(g_pImgManager->FindImage("Diration"));
    m_BackScene.SetupForSprites(1, 1);
    m_BackScene.StartAnimation();
    m_BackScene.SetBodySize({ 43, 28 });
    m_BackScene.SetBodyPos({ 150.0f, 415.0f });
    m_HP = 100;
    m_bIsAct = false;   //충돌상태가 아닐때
    m_bIngAct = false;  //충돌상태 판단

    //클리어 상태이므로 적과 키를 보이지 않게 한다.
    if (m_scnLevel >= 4) 
    {
        m_KeyItem1.SetInvisible();
    }
    else
    {
        for (int i = 0; i < 3; ++i) 
        {
            //Enemy 
            m_cEnemy[i].SetBodyImg(g_pImgManager->FindImage("EnemyKnight"));
            m_cEnemy[i].SetupForSprites(4, 4);
            m_cEnemy[i].SetTerrainBuffer(m_imgTerrainBuffer);
            m_cEnemy[i].StartAnimation();
            m_cEnemy[i].SetBodySize({ 64, 64 });
            m_cEnemy[i].SetFrameDelay(6);
            m_cEnemy[i].SetBodyPos({ (int)310,(int)290 });
            m_cEnemy[i].SetHBoxMargin({ 16, 16, 16, 16 });
            m_cEnemy[i].SetLockArea({ 0, 0, 512, 512 });
            m_cEnemy[i].LockInWnd();
        }
    }
}

void EscapeScene::Update()
{
    m_player.Update();
    m_teleportA.Update();
    m_teleportB.Update();
    m_teleportC.Update();
    m_teleportD.Update();
    m_KeyItem1.Update();
    m_BackScene.Update();
    m_StartPoint.Update();
    m_EndPoint.Update();

    RECT rt;
    //탈출시 위치가 또다른 충돌박스에 있지 않게 한다.추가 위치 보정필요
    if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_teleportA.GetBodyRect()))
        m_player.SetBodyPos({ (int)250, (int)250 + 50 });
    else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_teleportB.GetBodyRect()))
        m_player.SetBodyPos({ (int)92, (int)280 + 50 });
    else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_teleportC.GetBodyRect()))
        m_player.SetBodyPos({ (int)80 + 50, (int)170 });
    else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_teleportD.GetBodyRect()))
        m_player.SetBodyPos({ (int)385, (int)300 + 50 });
    else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_EndPoint.GetBodyRect()))
        if (m_bKeyItem1)    //씬 이동을 위한 충돌 판단 부분
            SceneChange();
    else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_BackScene.GetBodyRect()))
        SceneBack();        //씬 이동을 위한 충돌 판단 부분
    else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_KeyItem1.GetBodyRect()))
    {
        //key item
        m_scnLevel = 4;
        m_bKeyItem1 = true;
        m_KeyItem1.SetInvisible();
    }

    if (m_HP <= 0)  //죽었을  경우
    {
        //죽었을 경우 체력5
        m_playerData["player"]["hp"] = 5;
        //클래스 json에 저장
        JsonAdd();
        //씬이동시킨다
        SceneChange();
    }

    g_rtViewPort = g_pDrawHelper->MakeViewPort(m_player.GetBodyPos(), m_imgWorldBuffer);
}

void EscapeScene::Render()
{
    m_imgWorldMap->Render(m_imgWorldBuffer->GetMemDC(), 0, 0);

    m_player.Render(m_imgWorldBuffer->GetMemDC());
    m_teleportA.Render(m_imgWorldBuffer->GetMemDC());
    m_teleportB.Render(m_imgWorldBuffer->GetMemDC());
    m_teleportC.Render(m_imgWorldBuffer->GetMemDC());
    m_teleportD.Render(m_imgWorldBuffer->GetMemDC());
    m_KeyItem1.Render(m_imgWorldBuffer->GetMemDC());
    m_EndPoint.Render(m_imgWorldBuffer->GetMemDC());
    m_StartPoint.Render(m_imgWorldBuffer->GetMemDC());
    m_BackScene.Render(m_imgWorldBuffer->GetMemDC());

    for (int i = 0; i < 3; ++i)
    {
        m_cEnemy[i].Render(m_imgWorldBuffer->GetMemDC());
    }
    
    m_imgWorldBuffer->ViewportRender(g_hDC, g_rtViewPort);

    m_imgUiBuffer->TransRender(g_hDC, 0, 0, W_WIDTH, W_HEIGHT);

#ifdef _DEBUG
    char str[256];
    sprintf_s(str, "player hp : %d", m_HP);
    TextOut(g_hDC, 400, 100, str, strlen(str));
#endif // _DEBUG
}

void EscapeScene::Release()
{
    m_playerData["player"]["hp"] = m_player.GetLife();
    m_playerData["player"]["potion"] = m_player.GetHealPotion();
    m_playerData["player"]["scn-level"] = m_scnLevel;
    g_pFileManager->JsonUpdate("player", m_playerData);
}

void EscapeScene::SceneChange()
{
    //  클리어시 town
    g_pScnManager->SetNextScene("town");
    g_pScnManager->ChangeScene("loading");
}

void EscapeScene::SceneBack()
{
    //  클리어시 field
    g_pScnManager->SetNextScene("field");
    g_pScnManager->ChangeScene("loading");
}

//현재 클래스의 내용을 json에 저장함
void EscapeScene::JsonAdd()
{
    m_playerData["player"]["hp"] = m_player.GetLife(); 
    m_playerData["player"]["scn-level"] = m_scnLevel;
    m_playerData["player"]["potion"] = m_player.GetHealPotion();
    m_playerData["player"]["atk"] = m_player.GetAtkDamage();
    g_pFileManager->JsonUpdate("player", m_playerData);
}

void EscapeScene::SetData()
{
    m_playerData = g_pFileManager->JsonFind("player");
    m_HP = m_playerData["player"]["hp"];
    m_scnLevel = m_playerData["player"]["scn-level"];
    m_potion = m_playerData["player"]["potion"];
    m_atk = m_playerData["player"]["atk"];
}