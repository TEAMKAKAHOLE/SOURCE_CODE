#include "stdafx.h"
#include "FieldScene.h"



FieldScene::FieldScene()
{
}


FieldScene::~FieldScene()
{
}

void FieldScene::Start()
{


	m_imgWorldBuffer = g_pImgManager->AddImage("WorldBuffer", 2048, 2048);
	//m_imgTerrainBuffer = g_pImgManager->AddImage("field-map-magenta", 2048, 2048);

	m_imgWorldBuffer = g_pImgManager->FindImage("WorldBuffer");
	m_imgWorldMap = g_pImgManager->FindImage("field-map");
	m_imgTerrainBuffer = g_pImgManager->FindImage("field-map-magenta");

	m_pPlayer = new Player;
	m_pPlayer->SetBodyImg(g_pImgManager->FindImage("player"));
	m_pPlayer->SetBodyPos({ 160,1600 });
	m_pPlayer->SetBodySize({ 128,128 });
	m_pPlayer->SetupForSprites(7, 8);
	m_pPlayer->SetFrameDelay(3);
	m_pPlayer->StartAnimation();
	m_pPlayer->SetTerrainBuffer(m_imgTerrainBuffer);
	


	m_pEnemy = new Enemy;
	m_pEnemy->SetBodyImg(g_pImgManager->FindImage("enemy-knight"));
	m_pEnemy->SetBodyPos({ 1200,1600 });
	m_pEnemy->SetBodySize({ 128,128 });
	m_pEnemy->SetupForSprites(4, 4);
	m_pEnemy->SetFrameDelay(3);
	m_pEnemy->StartAnimation();
	
}

void FieldScene::Update()
{
	m_pPlayer->Update();
	m_pEnemy->Update();

	//¸Ê ¿òÁ÷ÀÌ±â
	g_rtViewPort = g_pDrawHelper->MakeViewPort(m_pPlayer->GetBodyPos(), m_imgWorldBuffer);


}

void FieldScene::Render()
{
	
	m_imgWorldMap->Render(m_imgWorldBuffer->GetMemDC(), 0, 0, 2048, 2048);
	m_pPlayer->Render(m_imgWorldBuffer->GetMemDC());
	m_pEnemy->Render(m_imgWorldBuffer->GetMemDC());
	m_imgWorldBuffer->ViewportRender(g_hDC, g_rtViewPort);
	
}

void FieldScene::Release()
{
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pEnemy);
	
}
