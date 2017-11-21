#include "stdafx.h"
#include "PuzzleScene.h"


PuzzleScene::PuzzleScene()
{
	m_szTagName = "puzzle";
}


PuzzleScene::~PuzzleScene()
{
}

void PuzzleScene::Start()
{
	g_pImgManager->AddImageList(m_szTagName);
	while (g_pImgManager->AddImageByJson(m_szTagName));

	//���۴� �ֵ� �̹����� �߰�
	m_imgWorldBuffer = g_pImgManager->AddImage("puzzle-map-buffer", 2048, 2048);
	m_imgWorldMap = g_pImgManager->FindImage("puzzle-map");
	m_imgTerrainBuffer = g_pImgManager->FindImage("puzzle-terrain");

	//�÷��̾� ����
	m_Player.SetBodyImg(g_pImgManager->FindImage("Player"));
	//��������Ʈ �̹��� x, y�� ������ ���� ����
	m_Player.SetupForSprites(7, 8);
	//�ִϸ��̼� Ű��
	m_Player.StartAnimation();
	m_Player.SetBodySize({ 128, 128 });
	//�ִϸ��̼� ������
	m_Player.SetFrameDelay(6);
}

void PuzzleScene::Update()
{
	m_Player.Update();
	//�÷��̾� �������� ����Ʈ ������ ��ŭ�� �׷���
	g_rtViewPort = g_pDrawHelper->MakeViewPort(m_Player.GetBodyPos(), m_imgWorldBuffer);

	if (g_pKeyManager->isOnceKeyDown('1'))
	{
		//�ε����� �ٷ� �� ��ȯ
		g_pScnManager->ChangeScene("puzzleGame");
	}
}

void PuzzleScene::Render()
{
	//�ʰ� �÷��̾� �ʹ��ۿ� �׷���.
	m_imgWorldMap->Render(m_imgWorldBuffer->GetMemDC(), 0, 0, 2048, 2048);
	m_Player.Render(m_imgWorldBuffer->GetMemDC());

	//�׷��� ���۸� ����Ʈ������ �̿��� â ������ ��ŭ�� ���̰�
	m_imgWorldBuffer->ViewportRender(g_hDC, g_rtViewPort);
}

void PuzzleScene::Release()
{
}
