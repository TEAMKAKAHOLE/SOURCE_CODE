#include "stdafx.h"
#include "EscapeScene.h"
#include "Player.h"
#include "TelePort.h"
#include "Enemy.h"

//������ GameObject�� ��ӹް� �Ѵ�.
EscapeScene::EscapeScene()
{
	
}


EscapeScene::~EscapeScene()
{
}

void EscapeScene::Start()
{
	m_imgWorldBuffer = g_pImgManager->AddImage("eacape-map-buffer", 512, 512);
	m_imgWorldMap = g_pImgManager->FindImage("escape-map");
	m_imgTerrainBuffer = g_pImgManager->FindImage("escape-terrain");


	m_player.SetBodyImg(g_pImgManager->FindImage("player"));
	m_player.SetupForSprites(7, 8);
	m_player.StartAnimation();
	m_player.SetBodySize({ 64, 64 });
	m_player.SetFrameDelay(6);
	m_player.SetBodyPos({ (int)350,(int)390 });
	m_player.SetHBoxMargin({ 16, 16, 16, 16 });
	m_player.SetTerrainBuffer(m_imgTerrainBuffer);
	m_player.Update();
	m_player.SetLockArea({ 0, 0, 512, 512 });
	m_player.LockInWnd();

	m_teleportA.SetBodyPos({ (int)385, (int)300 });
	m_teleportA.SetBodySize({ (int)20, (int)20 });
	m_teleportB.SetBodyPos({ (int)418, (int)190 });
	m_teleportB.SetBodySize({ (int)20, (int)20 });
	m_teleportC.SetBodyPos({ (int)255, (int)250 });
	m_teleportC.SetBodySize({ (int)20, (int)20 });
	m_teleportD.SetBodyPos({ (int)95, (int)285 });
	m_teleportD.SetBodySize({ (int)20, (int)20 });

	//next Scene �̵����� Endpoint
	m_EndPoint.SetBodyPos({ 80 ,170 });
	m_EndPoint.SetBodySize({ 20,20 });
	m_StartPoint.SetBodyPos({ 350 ,390 });
	m_StartPoint.SetBodySize({ 20,20 });

	//Item �ʱ���ġ,bool ����
	m_KeyItem1.SetBodyImg(g_pImgManager->FindImage("keyItem"));
	m_KeyItem1.SetupForSprites(1, 1);
	m_KeyItem1.StartAnimation();
	m_KeyItem1.SetBodySize({ 46,46 });
	m_KeyItem1.SetBodyPos({ 420,260 });
	m_bKeyItem1 = false;

	m_BackScene.SetBodyImg(g_pImgManager->FindImage("Diration"));
	m_BackScene.SetupForSprites(1, 1);
	m_BackScene.StartAnimation();
	m_BackScene.SetBodySize({ 43,28 });
	m_BackScene.SetBodyPos({ 150,415 });
	m_HP = 100;
	m_bIsAct = false; //�浹���°� �ƴҶ�
	m_bIngAct = false;//�浹���� �Ǵ�

	//ó�����۰� ���ÿ�json�� ������Ŭ Ŭ���� ������ ��´�
	SetData();
	//�ӽ÷� �׽�Ʈ ���ؼ� 100�Է�
	m_playerData["player"]["hp"] = 100;

	//Ŭ���� �����̹Ƿ� ���� Ű�� ������ �ʰ� �Ѵ�.
	if (m_Level > 4) {
		m_KeyItem1.SetInvisible();
	}
	else {
		for (int i = 0; i < 3; ++i) {

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
	m_EndPoint.Update();
	m_BackScene.Update();


	m_StartPoint.Update();

	//���� ����
	/*for (int i = 0; i < 3; ++i)
	{
		m_cEnemy[i].Update();
	}*/

	int distance = 10;

	g_rtViewPort = g_pDrawHelper->MakeViewPort(m_player.GetBodyPos(), m_imgWorldBuffer);
	RECT rt;
	//Ż��� ��ġ�� �Ǵٸ� �浹�ڽ��� ���� �ʰ� �Ѵ�.�߰� ��ġ �����ʿ�
	if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_teleportA.GetBodyRect()))
	{
		m_player.SetBodyPos({ (int)250, (int)250 + 50 });
	}
	else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_teleportB.GetBodyRect()))
	{
		m_player.SetBodyPos({ (int)92, (int)280 + 50 });
	}
	else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_teleportC.GetBodyRect()))
	{
		m_player.SetBodyPos({ (int)80 + 50, (int)170 });
	}
	else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_teleportD.GetBodyRect()))
	{
		m_player.SetBodyPos({ (int)385, (int)300 + 50 });
	}
	else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_EndPoint.GetBodyRect()))
	{  //�� �̵��� ���� �浹 �Ǵ� �κ�
		if (m_bKeyItem1)
		{
			SceneChange();
		}
	}
	else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_BackScene.GetBodyRect()))
	{  //�� �̵��� ���� �浹 �Ǵ� �κ�
		SceneBack();
	}
	    //key item
	else if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_KeyItem1.GetBodyRect()))
	{
		m_bKeyItem1 = true;
		m_KeyItem1.SetInvisible();
	}

	//�׾���  ��� 
	if (m_HP <= 0)
	{
	   //�׾��� ��� ü��5
		m_playerData["player"]["hp"] = 5;
		//Ŭ���� json�� ����
		JsonAdd();
		//���̵���Ų��
		SceneChange();

	}

#pragma region oneTest

	//�浹ó�� �κ� �ѹ��� �浹�ϰ� �Ұ� �ε�ģ ���¿����� 
	//���� ������ �������� �������Ͼ�� �ʰ� �Ѵ�.
	/*for (int i = 0; i < 3; i++)
	{
		if (IntersectRect(&rt, &m_player.GetHBoxRect(), &m_cEnemy[i].GetHBoxRect()))
		{
			if (!m_bIsAct && !m_bIngAct)
			{
				m_bIsAct = true;
				m_HP -= 10;
			}

		  if ( IsRectEmpty(&m_cEnemy[i].GetBodyRect()))
			{
				m_bIsAct = false;
			}
		}
	}*/

#pragma endregion DEBUGInput

	if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
	{
		JsonView();
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_TAB))
	{
		JsonAdd();
	}

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


	char str[256];
	sprintf_s(str, "player hp : %d", m_HP);
	TextOut(g_hDC, 400, 100, str, strlen(str));

}

void EscapeScene::Release()
{
}

void EscapeScene::SceneChange()
{
	//Ŭ����� town
	g_pScnManager->SetNextScene("town");
	g_pScnManager->ChangeScene("loading");


}

void EscapeScene::SceneBack()
{
	//Ŭ����� town
	g_pScnManager->SetNextScene("field");
	g_pScnManager->ChangeScene("loading");
}


//���� Ŭ������ ������ json�� ������
void EscapeScene::JsonAdd()
{
	//m_playerData = g_pFileManager->JsonFind("player");
	m_playerData["player"]["hp"] = m_HP; 
	m_playerData["player"]["scn-level"] = m_Level;
	m_playerData["player"]["potion"] = m_potion;
	m_playerData["player"]["atk"] = m_atk;
	g_pFileManager->JsonUpdate("player", m_playerData);
}

#pragma region Jsonview

void EscapeScene::JsonView()
{
	json jDataRead;
	ifstream i;


	i.open("data/player.json", ios_base::in);
	i >> jDataRead;
	i.close();

	cout << "hp          :" << jDataRead["player"]["hp"] << endl;
	cout << "atk         :" << jDataRead["player"]["atk"] << endl;
	cout << "Level       :" << jDataRead["player"]["scn-level"] << endl;

	cout << "hp 1         :" << m_playerData["player"]["hp"] << endl;
	cout << "atk  1       :" << m_playerData["player"]["atk"] << endl;
	cout << "Level  1     :" << m_playerData["player"]["scn-level"] << endl;
}
#pragma endregion


void EscapeScene::SetData()
{
	m_playerData = g_pFileManager->JsonFind("player");
	m_HP = m_playerData["player"]["hp"];
	m_Level = m_playerData["player"]["scn-level"];
	m_potion = m_playerData["player"]["potion"];
	m_atk = m_playerData["player"]["atk"];
}

