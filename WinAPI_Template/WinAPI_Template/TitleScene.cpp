#include "stdafx.h"
#include "TitleScene.h"


TitleScene::TitleScene()
{
    m_szTagName = "title";
	g_pSndManager->AddSoundList(m_szTagName);
	while (g_pSndManager->AddSoundByJson(m_szTagName));
}


TitleScene::~TitleScene()
{
}

void TitleScene::Start()
{
    m_imgTitleBg = g_pImgManager->FindImage("title-bg");
	g_pSndManager->Play("title");
}

void TitleScene::Update()
{
    InputController();
}

void TitleScene::Render()
{
    m_imgTitleBg->Render(g_hDC, 0, 0, W_WIDTH, W_HEIGHT);
}

void TitleScene::Release()
{
}

void TitleScene::InputController()
{
    if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
    {
        g_pScnManager->SetNextScene("town");
        g_pScnManager->ChangeScene("loading");
    }

    if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
        g_pScnManager->ChangeScene("exit");
}
