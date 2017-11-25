#include "stdafx.h"
#include "EndingCreditScene.h"


EndingCreditScene::EndingCreditScene()
{
    m_szTagName = "ending-credit";
    g_pImgManager->AddImageList(m_szTagName);
    while (g_pImgManager->AddImageByJson(m_szTagName));
}


EndingCreditScene::~EndingCreditScene()
{
    if (m_sprEndingCredit != NULL)
    {
        SAFE_DELETE(m_sprEndingCredit);
    }
}

void EndingCreditScene::Start()
{
    m_sprEndingCredit = new SpritesObject;
    m_sprEndingCredit->SetBodyImg(g_pImgManager->FindImage("ending-credit"));
    m_sprEndingCredit->SetBodyPos({ (double)W_WIDTH * 0.5f
        , (double)W_HEIGHT * 0.5f + (double)m_sprEndingCredit->GetBodyImg()->GetHeight() * 0.5f });
    m_sprEndingCredit->SetBodySpeed({ 0.0f, -1.0f });
    m_sprEndingCredit->SetBodySize({ 768, 8200 });
    m_sprEndingCredit->SetupForSprites(1, 1);
}

void EndingCreditScene::Update()
{
    m_sprEndingCredit->Update();
    if (m_sprEndingCredit->GetBodyRect().bottom <= W_HEIGHT)
    {
        g_pScnManager->ChangeScene("exit");
    }
}

void EndingCreditScene::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, BLACKNESS);
    m_sprEndingCredit->GetBodyImg()->FastRender(g_hDC
        , m_sprEndingCredit->GetBodyRect().left, m_sprEndingCredit->GetBodyRect().top);

#ifdef _DEBUG
    string szPosY = to_string(m_sprEndingCredit->GetBodyPos().y);
    TextOut(g_hDC, 0, 100, szPosY.c_str(), (int)strlen(szPosY.c_str()));
#endif // _DEBUG
}

void EndingCreditScene::Release()
{
}