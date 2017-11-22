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

	//버퍼는 애드 이미지로 추가
	m_imgWorldBuffer = g_pImgManager->AddImage("puzzle-map-buffer", 512, 512);
	m_imgWorldMap = g_pImgManager->FindImage("puzzle-map");
	m_imgTerrainBuffer = g_pImgManager->FindImage("puzzle-terrain");

	//플레이어 세팅
	m_Player.SetBodyImg(g_pImgManager->FindImage("player"));
	//스프라이트 이미지 x, y축 프레임 갯수 세팅
	m_Player.SetupForSprites(7, 8);
	//애니메이션 키기
	m_Player.StartAnimation();
	m_Player.SetBodySize({ 64, 64 });
	m_Player.SetTerrainBuffer(m_imgTerrainBuffer);
	m_Player.SetHBoxMargin({ 16, 16, 16, 16 });
	m_Player.Update();
	m_Player.SetLockArea({ 0, 0, 512, 512 });
	m_Player.LockInWnd();
	//애니메이션 딜레이
	m_Player.SetFrameDelay(6);
}

void PuzzleScene::Update()
{
	m_Player.Update();
	//플레이어 기준으로 뷰포트 사이즈 만큼만 그려줌
	g_rtViewPort = g_pDrawHelper->MakeViewPort(m_Player.GetBodyPos(), m_imgWorldBuffer);

	if (g_pKeyManager->isOnceKeyDown('1') || g_pKeyManager->isOnceKeyDown('2'))
	{
		//로딩없이 바로 씬 전환
		g_pScnManager->ChangeScene("puzzle-game");
	}
}

void PuzzleScene::Render()
{
	//맵과 플레이어 맵버퍼에 그려줌.
	m_imgWorldMap->Render(m_imgWorldBuffer->GetMemDC(), 0, 0);
	m_Player.Render(m_imgWorldBuffer->GetMemDC());

	//그려준 버퍼를 뷰포트렌더를 이용해 창 사이즈 만큼만 보이게
	m_imgWorldBuffer->ViewportRender(g_hDC, g_rtViewPort);
}

void PuzzleScene::Release()
{
}