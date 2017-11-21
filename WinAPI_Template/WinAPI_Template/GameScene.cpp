#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene()
{
    
}

GameScene::~GameScene()
{
}

void GameScene::Start()
{
    
}

void GameScene::Update()
{
   
}

void GameScene::Render()
{
    
#ifdef _DEBUG
    TextOut(g_hDC, W_WIDTH - 100, 0, m_szTagName.c_str(), (int)strlen(m_szTagName.c_str()));
#endif // _DEBUG
}

void GameScene::Release()
{
    
}

void GameScene::NewGame()
{
}

void GameScene::SaveGame()
{
    
}

bool GameScene::LoadGame()
{
    
    return true;
}

void GameScene::PlayerController()
{
}