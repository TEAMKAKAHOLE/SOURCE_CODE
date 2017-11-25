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
    m_playerData = g_pFileManager->JsonFind("player");
    m_imgTitleBg = g_pImgManager->FindImage("title-bg");

    m_imgSword.SetBodyImg(g_pImgManager->FindImage("sword"));
    m_imgSword.SetupForSprites(26, 1);
    m_imgSword.StartAnimation();
    m_imgSword.SetBodySize({ 100, 400 });
    m_imgSword.SetBodyPos({ 55, 300 });
    m_imgSword.SetFrameDelay(1);

    for (int i = 0; i < 5; i++)
    {
        m_imgStar[i] = new SpritesObject;
        m_imgStar[i]->SetBodyImg(g_pImgManager->FindImage("star"));
        m_imgStar[i]->SetupForSprites(4, 2);
        m_imgStar[i]->StartAnimation();
    }
    m_imgStar[0]->SetBodySize({ 65, 65 });
    m_imgStar[0]->SetBodyPos({ 140, 150 });
    m_imgStar[0]->SetFrameDelay(2);

    m_imgStar[1]->SetBodySize({ 50, 50 });
    m_imgStar[1]->SetBodyPos({ 340, 350 });
    m_imgStar[1]->SetFrameDelay(2);

    m_imgStar[2]->SetBodySize({ 35, 35 });
    m_imgStar[2]->SetBodyPos({ 430, 170 });
    m_imgStar[2]->SetFrameDelay(2);

    m_imgStar[3]->SetBodySize({ 70, 70 });
    m_imgStar[3]->SetBodyPos({ 510, 255 });
    m_imgStar[3]->SetFrameDelay(2);

    m_imgStar[4]->SetBodySize({ 90, 90 });
    m_imgStar[4]->SetBodyPos({ 170, 400 });
    m_imgStar[4]->SetFrameDelay(2);

    m_nOnStar = rand() % 50;
    m_nRanIndex = rand() % 5;
    m_nRanIndex2 = rand() % 5;

    m_imgTitleBg = g_pImgManager->FindImage("title-bg");
    g_pSndManager->Play("title");
}

void TitleScene::Update()
{
    m_nOnStar--;
    if (m_nOnStar < 0)
    {
        m_nOnStar = rand() % 80;
        m_nRanIndex = rand() % 5;
        m_nRanIndex2 = rand() % 5;
    }
        
    m_imgSword.Update();

    for (int i = 0; i < 5; i++)
    {
        if (m_imgStar[i]->GetFrameX() == 3 &&
            m_imgStar[i]->GetFrameY() == 0)
        {
            m_imgStar[i]->SetFrameY(1);
        }
        else if (m_imgStar[i]->GetFrameX() == 3 &&
                m_imgStar[i]->GetFrameY() == 1)
        {
            m_imgStar[i]->SetFrameY(0);
        }

        m_imgStar[i]->Update();    
    }

    InputController();
}

void TitleScene::Render()
{
    m_imgTitleBg->Render(g_hDC, 0, 0, W_WIDTH, W_HEIGHT);
    m_imgSword.Render(g_hDC);

    m_imgStar[m_nRanIndex]->Render(g_hDC);
    m_imgStar[m_nRanIndex2]->Render(g_hDC);
}

void TitleScene::Release()
{
    g_pFileManager->JsonUpdate("player", m_playerData);
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
