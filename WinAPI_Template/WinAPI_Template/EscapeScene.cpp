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

	m_nSoundPlayCount = 1;
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

    //next Scene �̵����� Endpoint
    m_EndPoint.SetBodyPos({ 80.0f, 170.0f });
    m_EndPoint.SetBodySize({ 20, 20 });
    m_StartPoint.SetBodyPos({ 350.0f, 390.0f });
    m_StartPoint.SetBodySize({ 20, 20 });

    //Item �ʱ���ġ,bool ����
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
    m_bIsAct = false;   //�浹���°� �ƴҶ�
    m_bIngAct = false;  //�浹���� �Ǵ�
    m_bInAt2 = false; //�浹�� ��������Ʈ Ȱ��ȭ

    //Ŭ���� �����̹Ƿ� ���� Ű�� ������ �ʰ� �Ѵ�.
    if (m_scnLevel >= 4) 
    {
        m_KeyItem1.SetInvisible();
        m_bKeyItem1 = true;
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

    m_Trap.SetBodyImg(g_pImgManager->FindImage("Trap"));
    m_Trap.SetBodyPos({ 320,290 });
    m_Trap.SetupForSprites(16, 1);
    m_Trap.StartAnimation();
    m_Trap.SetFrameDelay(3);
    m_Trap.SetBodySize({ 32,44 });
    m_Trap.SetVisible();

    m_Trap2.SetBodyImg(g_pImgManager->FindImage("Trap2"));
    m_Trap2.SetBodyPos({ 170,290 });
    m_Trap2.SetupForSprites(16, 1);
    m_Trap2.StartAnimation();
    m_Trap2.SetFrameDelay(3);
    m_Trap2.SetBodySize({ 32,44 });
    m_Trap2.SetVisible();

    m_Bom.SetBodyImg(g_pImgManager->FindImage("Bom"));
    m_Bom.SetupForSprites(6, 1);
    m_Bom.StartAnimation();
    m_Bom.SetFrameDelay(3);
    m_Bom.SetBodyPos({ 320,290 - 10 });
    m_Bom.SetBodySize({ 117,128 });
    m_Bom.SetInvisible();

	g_pSndManager->Play("escape");
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

    m_Trap.Update();
    m_Trap2.Update();
    m_Bom.Update();

    RECT rt;
    //Ż��� ��ġ�� �Ǵٸ� �浹�ڽ��� ���� �ʰ� �Ѵ�.�߰� ��ġ �����ʿ�
    if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_teleportA.GetBodyRect()))
    {
        m_player.SetBodyPos({ (int)250, (int)250 + 50 });

		if (m_nSoundPlayCount > 0)
		{
			g_pSndManager->Play("potal");
			m_nSoundPlayCount--;
		}
    }
    else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_teleportB.GetBodyRect()))
    {
        m_player.SetBodyPos({ (int)92, (int)280 + 50 });

		if (m_nSoundPlayCount > 0)
		{
			g_pSndManager->Play("potal");
			m_nSoundPlayCount--;
		}
    }
    else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_teleportC.GetBodyRect()))
    {
        m_player.SetBodyPos({ (int)80 + 50, (int)170 });

		if (m_nSoundPlayCount > 0)
		{
			g_pSndManager->Play("potal");
			m_nSoundPlayCount--;
		}
    }
    else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_teleportD.GetBodyRect()))
    {
        m_player.SetBodyPos({ (int)385, (int)300 + 50 });

		if (m_nSoundPlayCount > 0)
		{
			g_pSndManager->Play("potal");
			m_nSoundPlayCount--;
		}
    }
    else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_EndPoint.GetBodyRect()))
    {
        if (m_bKeyItem1)    //�� �̵��� ���� �浹 �Ǵ� �κ�
        {
            SceneChange();
        }
    }
    else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_BackScene.GetBodyRect()))
    {
        SceneBack();        //�� �̵��� ���� �浹 �Ǵ� �κ�
    }
    else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_KeyItem1.GetBodyRect()))
    {
		if (m_bKeyItem1 == false && m_nSoundPlayCount > 0)
		{
			g_pSndManager->Play("key");
			m_nSoundPlayCount--;
		}

        //key item
        m_scnLevel = 4;
        m_bKeyItem1 = true;
        m_KeyItem1.SetInvisible();
    }
    else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_Trap.GetHBoxRect())
        && m_Trap.IsVisible())
    {
		if (m_nSoundPlayCount > 0)
		{
			g_pSndManager->Play("explosion");
			m_nSoundPlayCount--;
		}

        //trap�� �浹�� ��ź ������ �ϱ� 
        m_Trap.SetInvisible();
        m_bInAt2 = true;
        m_idBoom = 1;
    }
    else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_Trap2.GetHBoxRect())
        && m_Trap2.IsVisible())
    {
        m_Trap2.SetInvisible();
        m_bInAt2 = true;
        m_idBoom = 2;
    }

    if (m_bInAt2)
    {
        if (m_idBoom == 1)
        {
            //Trap��ǥ���� ����
            m_Bom.SetBodyPos({ 320, 290 - 20 });
        }

        m_Bom.SetVisible();
        if (m_Bom.GetFrameX() >= 5)
        {
            m_Bom.StopAnimation();
            m_Bom.SetInvisible();
            m_bInAt2 = false;
            PlayerDie();
        }
    }

    if (m_HP <= 0)  //�׾���  ���
    {
        //�׾��� ��� ü��5
        m_playerData["player"]["hp"] = 5;
        //���̵���Ų��
        SceneChange();
    }
	m_nSoundPlayCount = 1;
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
    m_Trap.Render(m_imgWorldBuffer->GetMemDC());
    m_Bom.Render(m_imgWorldBuffer->GetMemDC());

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
    JsonAdd();
	g_pSndManager->Stop("escape");
}

void EscapeScene::SceneChange()
{
    //  Ŭ����� town
    g_pScnManager->SetNextScene("town");
    g_pScnManager->ChangeScene("loading");
}

void EscapeScene::SceneBack()
{
    //  Ŭ����� field
    g_pScnManager->SetNextScene("field");
    g_pScnManager->ChangeScene("loading");
}

//���� Ŭ������ ������ json�� ������
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

void EscapeScene::PlayerDie()
{
	//�׾��� ��� ü��5
	m_playerData["player"]["hp"] = 5;
	//Ŭ���� json�� ����
	JsonAdd();
	//���̵���Ų��
	SceneChange();
}