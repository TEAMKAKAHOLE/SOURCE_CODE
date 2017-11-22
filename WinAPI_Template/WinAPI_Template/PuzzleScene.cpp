#include "stdafx.h"
#include "PuzzleScene.h"


PuzzleScene::PuzzleScene()
: m_isStageClear(false)
, m_isPuzzleClear(false)
, m_isHint1On(false)
, m_isHint2On(false)
, m_isHint3On(false)
, m_isSignUp(false)
, m_isExitMessage1(false)
, m_isExitMessage2(false)
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
	m_Player.SetBodyPos({ 272, 85 });
	m_Player.Update();
	m_Player.SetLockArea({ 0, 0, 512, 512 });
	m_Player.LockInWnd();
	//애니메이션 딜레이
	m_Player.SetFrameDelay(6);

	//오브젝트 세팅
	m_Object.SetBodyImg(g_pImgManager->FindImage("hint"));
	m_Object.SetupForSprites(1, 1);
	m_Object.SetBodySize({ 15, 10 });
	m_Object.SetBodyPos({ 270, 200 });
	m_Object.Update();

	m_imgHintLetter1.SetBodyImg(g_pImgManager->FindImage("hint-letter-1"));
	m_imgHintLetter1.SetupForSprites(1, 1);
	m_imgHintLetter1.SetBodySize({ 459, 647 });
	m_imgHintLetter1.SetBodyPos({ W_WIDTH / 2, W_HEIGHT / 2 });
	m_imgHintLetter1.Update();

	//시작 위치
	m_StartLocation.SetBodySize({ 20, 20 });
	m_StartLocation.SetBodyPos({ 272, 35 });
	m_StartLocation.SetBodyRect();

	//게임 시작 위치
	m_GameStartLocation.SetBodySize({ 15, 20 });
	m_GameStartLocation.SetBodyPos({ 275, 355 });
	m_GameStartLocation.SetBodyRect();

	//하드 코스
	m_Exit1.SetBodySize({ 15, 10 });
	m_Exit1.SetBodyPos({ 130, 150 });
	m_Exit1.SetBodyRect();

	m_imgHardway.SetBodyImg(g_pImgManager->FindImage("hardway"));
	m_imgHardway.SetupForSprites(1, 1);
	m_imgHardway.SetBodySize({ 390, 282 });
	m_imgHardway.SetBodyPos({ W_WIDTH / 2, W_HEIGHT / 2 });
	m_imgHardway.Update();

	//노말 코스
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
	//플레이어 기준으로 뷰포트 사이즈 만큼만 그려줌
	g_rtViewPort = g_pDrawHelper->MakeViewPort(m_Player.GetBodyPos(), m_imgWorldBuffer);

	if (g_pKeyManager->isOnceKeyDown('1'))
	{
		m_isPuzzleClear = true;
	}

	//퍼즐 게임 씬 전환 충돌
	RECT rt2;
	if (IntersectRect(&rt2, &m_Player.GetHBoxRect(), &m_GameStartLocation.GetBodyRect()) &&
		g_pKeyManager->isOnceKeyDown(VK_SPACE))
	{
		g_pScnManager->ChangeScene("puzzle-game");
	}

	//힌트 충돌
	RECT rt;
	if (IntersectRect(&rt, &m_Player.GetHBoxRect(), &m_Object.GetBodyRect()) && g_pKeyManager->isToggleKy(VK_SPACE))
	{
		m_isHint1On = true;
		//오브젝트에 막히는 부분 설정 해야함.
	}
	else
	{
		m_isHint1On = false;
	}

	//출구 충돌
	RECT rt3;
	if (IntersectRect(&rt3, &m_Player.GetHBoxRect(), &m_StartLocation.GetBodyRect()) && m_isStageClear)
	{
		g_pScnManager->SetNextScene("town");
		g_pScnManager->ChangeScene("loading");
	}
	
	if (IntersectRect(&rt3, &m_Player.GetHBoxRect(), &m_Exit1.GetBodyRect()) && m_isStageClear)
	{
		g_pScnManager->SetNextScene("field");
		g_pScnManager->ChangeScene("loading");
	}
	else if (IntersectRect(&rt3, &m_Player.GetHBoxRect(), &m_Exit1.GetBodyRect()) && g_pKeyManager->isToggleKy(VK_SPACE))
	{
		m_isExitMessage1 = true;
	}
	else
		m_isExitMessage1 = false;

	if (IntersectRect(&rt3, &m_Player.GetHBoxRect(), &m_Exit2.GetBodyRect()) && m_isStageClear)
	{
		g_pScnManager->SetNextScene("field");
		g_pScnManager->ChangeScene("loading");
	}
	else if (IntersectRect(&rt3, &m_Player.GetHBoxRect(), &m_Exit2.GetBodyRect()) && g_pKeyManager->isToggleKy(VK_SPACE))
	{
		m_isExitMessage2 = true;
	}
	else
	{
		m_isExitMessage2 = false;
	}
		
}

void PuzzleScene::Render()
{
	//맵과 플레이어 맵버퍼에 그려줌.
	m_imgWorldMap->Render(m_imgWorldBuffer->GetMemDC(), 0, 0);
	m_Player.Render(m_imgWorldBuffer->GetMemDC());

	m_StartLocation.Render(m_imgWorldBuffer->GetMemDC());
	m_GameStartLocation.Render(m_imgWorldBuffer->GetMemDC());
	m_Exit1.Render(m_imgWorldBuffer->GetMemDC());
	m_Exit2.Render(m_imgWorldBuffer->GetMemDC());

	//퍼즐클리어시 힌트 생성
	if(m_isPuzzleClear)
		m_Object.Render(m_imgWorldBuffer->GetMemDC());

	//그려준 버퍼를 뷰포트렌더를 이용해 창 사이즈 만큼만 보이게
	m_imgWorldBuffer->ViewportRender(g_hDC, g_rtViewPort);

	//힌트메세지
	if (m_isHint1On)
	{	
		m_imgHintLetter1.Render(g_hDC);
	}
	if (m_isExitMessage1)
		m_imgHardway.Render(g_hDC);
	else if (m_isExitMessage2)
		m_imgNormalway.Render(g_hDC);
}

void PuzzleScene::Release()
{
}
