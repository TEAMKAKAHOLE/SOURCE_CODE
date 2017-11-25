#include "stdafx.h"
#include "EndingCreditScene.h"


EndingCreditScene::EndingCreditScene()
{
    m_szTagName = "ending-credit";
    g_pImgManager->AddImageList(m_szTagName);
    while (g_pImgManager->AddImageByJson(m_szTagName));
    g_pSndManager->AddSoundList(m_szTagName);
    while (g_pSndManager->AddSoundByJson(m_szTagName));
    m_imgEndingCreditBuffer = g_pImgManager->AddImage("ending-credit-buffer", CREDIT_WIDTH, CREDIT_HEIGHT);
    m_sprEndingCredit = NULL;
    m_dViewPortPos = GLOBAL_CENTER_POS;
}


EndingCreditScene::~EndingCreditScene()
{
    if (m_sprEndingCredit != NULL)
        SAFE_DELETE(m_sprEndingCredit);
}

void EndingCreditScene::Start()
{
    g_pSndManager->Play("ending-credit-bgm");

    m_sprEndingCredit = new SpritesObject;
    m_sprEndingCredit->SetBodyImg(g_pImgManager->FindImage("ending-credit"));
    m_sprEndingCredit->SetBodyPos({ (double)W_WIDTH * 0.5f
        , (double)W_HEIGHT * 0.5f + (double)m_sprEndingCredit->GetBodyImg()->GetHeight() * 0.5f });
    m_sprEndingCredit->SetBodySpeed({ 0.0f, -1.0f });
    m_sprEndingCredit->SetBodySize({ CREDIT_WIDTH, CREDIT_HEIGHT });
    m_sprEndingCredit->SetupForSprites(1, 1);

    m_sprEndingCredit->GetBodyImg()->FastRender(m_imgEndingCreditBuffer->GetMemDC(), 0, 0);

    m_nVpMargin.left = -(W_WIDTH - VIEWPORT_WIDTH) / 2;
    m_nVpMargin.right = m_nVpMargin.left;
    m_nVpMargin.top = -(W_HEIGHT - VIEWPORT_HEIGHT) / 2;
    m_nVpMargin.bottom = m_nVpMargin.top;
}

void EndingCreditScene::Update()
{
    m_dViewPortPos.y += CREDIT_SCROLL_SPEED;
    if (m_dViewPortPos.y >= CREDIT_HEIGHT)
    {
        g_pSndManager->Stop("ending-credit-bgm");
        g_pScnManager->ChangeScene("cookie");
    }

    g_rtViewPort = g_pDrawHelper->MakeViewPort(m_dViewPortPos, m_nVpMargin, m_imgEndingCreditBuffer);
}

void EndingCreditScene::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, BLACKNESS);
    m_imgEndingCreditBuffer->ViewportRender(g_hDC, g_rtViewPort);
#ifdef _DEBUG
    string szPosY = to_string(m_dViewPortPos.y);
    TextOut(g_hDC, 0, 100, szPosY.c_str(), (int)strlen(szPosY.c_str())); 
    szPosY = to_string(g_rtViewPort.top);
    TextOut(g_hDC, 0, 115, szPosY.c_str(), (int)strlen(szPosY.c_str()));
#endif // _DEBUG
}

void EndingCreditScene::Release()
{
}