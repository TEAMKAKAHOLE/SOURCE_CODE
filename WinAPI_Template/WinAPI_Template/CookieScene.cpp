#include "stdafx.h"
#include "CookieScene.h"


CookieScene::CookieScene()
{
    m_sprFadeout = NULL;
    m_sprHotsLogo = NULL;
    m_sprHotsSpinner = NULL;

    m_szTagName = "cookie";
    g_pImgManager->AddImageList(m_szTagName);
    while (g_pImgManager->AddImageByJson(m_szTagName));
    m_dFadeoutAlpha = 255.0f;
    m_dSpinnerAngle = 0.0f;

    m_isFadeout = true;
}


CookieScene::~CookieScene()
{
    if (m_sprFadeout != NULL)
        SAFE_DELETE(m_sprFadeout);

    if (m_sprHotsLogo != NULL)
        SAFE_DELETE(m_sprHotsLogo);

    if (m_sprHotsSpinner != NULL)
        SAFE_DELETE(m_sprHotsSpinner);
}

void CookieScene::Start()
{
    m_imgBuffer = g_pImgManager->AddImage("hots-buffer", W_WIDTH, W_HEIGHT);

    m_sprFadeout = new SpritesObject;
    m_sprFadeout->SetBodyImg(g_pImgManager->FindImage("fade-out"));

    m_sprHotsLogo = new SpritesObject;
    m_sprHotsLogo->SetBodyImg(g_pImgManager->FindImage("hots-logo"));
    m_sprHotsLogo->SetBodyPos(GLOBAL_CENTER_POS);
    m_sprHotsLogo->SetBodySize({ 768, 240 });
    m_sprHotsLogo->SetupForSprites(1, 1);
    m_sprHotsLogo->Update();

    m_sprHotsSpinner = new SpritesObject;
    m_sprHotsSpinner->SetBodyImg(g_pImgManager->FindImage("hots-spinner"));
    UnitPos pos = GLOBAL_CENTER_POS;
    pos.x += 65.0f;
    pos.y -= 35.0f;
    m_sprHotsSpinner->SetBodyPos(pos);
    m_sprHotsSpinner->SetBodySize({ 133, 133 });
    m_sprHotsSpinner->SetupForSprites(1, 1);
    m_sprHotsSpinner->Update();

    g_pTimerManager->AddOnOffTimer("cookie");
}

void CookieScene::Update()
{
    m_dSpinnerAngle -= 5.0f;

    if (m_isFadeout)
    {
        m_dFadeoutAlpha -= COOKIE_FADE_OUT_STEP * 0.25f;
        m_showingTime = g_pTimerManager->GetWorldTime(); 

        if (m_dFadeoutAlpha <= 0.0f)
        {
            m_dFadeoutAlpha = 0.0f;
            m_isFadeout = false;
        }
    }
    else
    {
        if (m_showingTime + 2.0f > g_pTimerManager->GetWorldTime())
        {
        }
        else
        {
            m_dFadeoutAlpha += COOKIE_FADE_OUT_STEP;
            if (m_dFadeoutAlpha >= 255.0f)
            {
                m_dFadeoutAlpha = 255.0f;
                g_pScnManager->ChangeScene("exit");
            }
        }
    }

    m_sprFadeout->SetAlpha(m_dFadeoutAlpha);
}

void CookieScene::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, BLACKNESS);

    m_sprHotsLogo->Render(g_hDC);
    m_sprHotsSpinner->GetBodyImg()->RotateRender(g_hDC, m_sprHotsSpinner->GetBodyPos(), m_dSpinnerAngle);

    m_sprFadeout->GetBodyImg()->AlphaRender(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, (BYTE)m_sprFadeout->GetAlpha());
}

void CookieScene::Release()
{
}
