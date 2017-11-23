#include "stdafx.h"
#include "PuzzleScene.h"


PuzzleScene::PuzzleScene()
: m_isStageClear(false)
, m_isPuzzleClear(false)
, m_isHint1On(false)
, m_isSignUp(false)
, m_isExitMessage1(false)
, m_isExitMessage2(false)
, m_isHintCheck(false)
{
	m_szTagName = "puzzle";

	//���̽㿡 ������ �ʱ�ȭ
	

	//�ƿ�ǲ ��Ʈ�� ���� ����Ÿ �ֱ� 

}


PuzzleScene::~PuzzleScene()
{
}

void PuzzleScene::Start()
{
	//���̽� ���ϵ���Ÿ ��������
	m_playerData = g_pFileManager->JsonFind("player");
	m_nScnLevel = m_playerData["player"]["scn-level"];

	g_pImgManager->AddImageList(m_szTagName);
	while (g_pImgManager->AddImageByJson(m_szTagName));

	//���۴� �ֵ� �̹����� �߰�
	m_imgWorldBuffer = g_pImgManager->AddImage("puzzle-map-buffer", 512, 512);
	m_imgWorldMap = g_pImgManager->FindImage("puzzle-map");
	m_imgTerrainBuffer = g_pImgManager->FindImage("puzzle-terrain");

	//�÷��̾� ����
	m_Player.SetBodyImg(g_pImgManager->FindImage("player"));
	//��������Ʈ �̹��� x, y�� ������ ���� ����
	m_Player.SetupForSprites(7, 8);
	//�ִϸ��̼� Ű��
	m_Player.StartAnimation();
	m_Player.SetBodySize({ 64, 64 });
	m_Player.SetTerrainBuffer(m_imgTerrainBuffer);
	m_Player.SetHBoxMargin({ 16, 16, 16, 16 });
	m_Player.SetBodyPos({ 272, 85 });
	m_Player.Update();
	m_Player.SetLockArea({ 0, 0, 512, 512 });
	m_Player.LockInWnd();
	//�ִϸ��̼� ������
	m_Player.SetFrameDelay(6);

	//������Ʈ ����
	m_Object.SetBodyImg(g_pImgManager->FindImage("hint"));
	m_Object.SetupForSprites(1, 1);
	m_Object.SetBodySize({ 15, 10 });
	m_Object.SetBodyPos({ 280, 185 });
	m_Object.Update();
	
	m_imgHintLetter1.SetBodyImg(g_pImgManager->FindImage("hint-letter-1"));
	m_imgHintLetter1.SetupForSprites(1, 1);
	m_imgHintLetter1.SetBodySize({ 459, 647 });
	m_imgHintLetter1.SetBodyPos({ W_WIDTH / 2, W_HEIGHT / 2 });
	m_imgHintLetter1.Update();

	//���� ��ġ
	m_StartLocation.SetBodySize({ 20, 20 });
	m_StartLocation.SetBodyPos({ 272, 35 });
	m_StartLocation.SetBodyRect();

	//���� ���� ��ġ
	m_GameStartLocation.SetBodySize({ 15, 20 });
	m_GameStartLocation.SetBodyPos({ 275, 355 });
	m_GameStartLocation.SetBodyRect();

	//�ϵ� �ڽ�
	m_Exit1.SetBodySize({ 15, 10 });
	m_Exit1.SetBodyPos({ 130, 150 });
	m_Exit1.SetBodyRect();

	m_imgHardway.SetBodyImg(g_pImgManager->FindImage("hardway"));
	m_imgHardway.SetupForSprites(1, 1);
	m_imgHardway.SetBodySize({ 390, 282 });
	m_imgHardway.SetBodyPos({ W_WIDTH / 2, W_HEIGHT / 2 });
	m_imgHardway.Update();

	//�븻 �ڽ�
	m_Exit2.SetBodySize({ 15, 10 });
	m_Exit2.SetBodyPos({ 420, 150 });
	m_Exit2.SetBodyRect();

	m_imgNormalway.SetBodyImg(g_pImgManager->FindImage("normalway"));
	m_imgNormalway.SetupForSprites(1, 1);
	m_imgNormalway.SetBodySize({ 390, 282 });
	m_imgNormalway.SetBodyPos({ W_WIDTH / 2, W_HEIGHT / 2 });
	m_imgNormalway.Update();
}

void PuzzleScene::Update()
{
	m_Player.Update();
	//�÷��̾� �������� ����Ʈ ������ ��ŭ�� �׷���
	g_rtViewPort = g_pDrawHelper->MakeViewPort(m_Player.GetBodyPos(), m_imgWorldBuffer);

	//���� ���� �� ��ȯ �浹
	RECT rt2;
	if (IntersectRect(&rt2, &m_Player.GetHBoxRect(), &m_GameStartLocation.GetBodyRect()) &&
		g_pKeyManager->isOnceKeyDown(VK_SPACE))
	{
		g_pScnManager->ChangeScene("puzzle-game");
	}

	//��Ʈ �浹
	RECT rt;
	if (IntersectRect(&rt, &m_Player.GetHBoxRect(), &m_Object.GetBodyRect()))
	{
		if (g_pKeyManager->isOnceKeyDown(VK_SPACE) && m_isPuzzleClear == true)
		    m_isHint1On = true;
	}
	else
		m_isHint1On = false;

	//�ⱸ �浹
	RECT rt3;
	if (IntersectRect(&rt3, &m_Player.GetHBoxRect(), &m_StartLocation.GetBodyRect()) && m_isStageClear)
	{
		g_pScnManager->SetNextScene("town");
		g_pScnManager->ChangeScene("loading");
	}
	
	//���� ��
	if (IntersectRect(&rt3, &m_Player.GetHBoxRect(), &m_Exit1.GetBodyRect()) && m_isStageClear)
	{
		g_pScnManager->SetNextScene("field");
		g_pScnManager->ChangeScene("loading");
	}
	else if (IntersectRect(&rt3, &m_Player.GetHBoxRect(), &m_Exit1.GetBodyRect()))
	{
		if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
			m_isExitMessage1 = true;
	}
	else
		m_isExitMessage1 = false;

	//���� �� (���ݷ� ���ʽ� �߰�)
	if (IntersectRect(&rt3, &m_Player.GetHBoxRect(), &m_Exit2.GetBodyRect()) && m_isStageClear)
	{
		//���ݷ� +3 ���ʽ�
		int playerAtk;
		playerAtk = m_playerData["player"]["atk"];
		playerAtk = 8;
		m_playerData["player"]["atk"] = playerAtk;
		g_pScnManager->SetNextScene("field");
		g_pScnManager->ChangeScene("loading");
	}
	else if (IntersectRect(&rt3, &m_Player.GetHBoxRect(), &m_Exit2.GetBodyRect()))
	{
		if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
			m_isExitMessage2 = true;
	}
	else
		m_isExitMessage2 = false;

	//�������� Ŭ���� 
	if (m_isPuzzleClear == true && m_isHint1On == true)
		m_isStageClear = true;
	
	//���̽� ����Ÿ
    if (m_nScnLevel == 2)
    {
        m_nScnLevel = 3;
		m_isPuzzleClear = true;
    }
	else if(m_nScnLevel == 1)
		m_isPuzzleClear = false;
}

void PuzzleScene::Render()
{
	//�ʰ� �÷��̾� �ʹ��ۿ� �׷���.
	m_imgWorldMap->Render(m_imgWorldBuffer->GetMemDC(), 0, 0);
	m_Player.Render(m_imgWorldBuffer->GetMemDC());

	m_StartLocation.Render(m_imgWorldBuffer->GetMemDC());
	m_GameStartLocation.Render(m_imgWorldBuffer->GetMemDC());
	m_Exit1.Render(m_imgWorldBuffer->GetMemDC());
	m_Exit2.Render(m_imgWorldBuffer->GetMemDC());

	//���� Ŭ����� ��Ʈ ����
	if(m_isPuzzleClear == true)
		m_Object.Render(m_imgWorldBuffer->GetMemDC());

	//�׷��� ���۸� ����Ʈ������ �̿��� â ������ ��ŭ�� ���̰�
	m_imgWorldBuffer->ViewportRender(g_hDC, g_rtViewPort);

	//��Ʈ�޼���
	if (m_isHint1On)
		m_imgHintLetter1.Render(g_hDC);
	
	//�ⱸ �޼���
	if (m_isExitMessage1)
		m_imgHardway.Render(g_hDC);
	else if (m_isExitMessage2)
		m_imgNormalway.Render(g_hDC);
}

void PuzzleScene::Release()
{
    m_playerData["player"]["scn-level"] = m_nScnLevel;
    g_pFileManager->JsonUpdate("player", m_playerData);
}