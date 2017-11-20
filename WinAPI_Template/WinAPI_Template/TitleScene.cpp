#include "stdafx.h"
#include "TitleScene.h"


TitleScene::TitleScene()
{
    m_szTagName = "title";
}


TitleScene::~TitleScene()
{
}

void TitleScene::Start()
{
    g_pImgManager->AddImageList(m_szTagName);
    g_pSndManager->AddSoundList(m_szTagName);
    while (g_pImgManager->AddImageByJson(m_szTagName));
    while (g_pSndManager->AddSoundByJson(m_szTagName));

    m_btnGoRungame.SetTagName("rungame");
    m_btnGoDodonpachi.SetTagName("dodonpachi");
    m_btnGoFortress.SetTagName("fortress");
    m_btnGoRpg.SetTagName("rpg");

    UnitPos btnPos = GLOBAL_CENTER_POS;
    btnPos.y -= 200.0f;
    m_btnGoRungame.SetBodyPos(btnPos);
    btnPos.y += 100.0f;
    m_btnGoDodonpachi.SetBodyPos(btnPos);
    btnPos.y += 100.0f;
    m_btnGoFortress.SetBodyPos(btnPos);
    btnPos.y += 100.0f;
    m_btnGoRpg.SetBodyPos(btnPos);

    UnitSize btnSize = { 300, 80 };
    m_btnGoRungame.SetBodySize(btnSize);
    m_btnGoDodonpachi.SetBodySize(btnSize);
    m_btnGoFortress.SetBodySize(btnSize);
    m_btnGoRpg.SetBodySize(btnSize);

    m_btnGoRungame.SetBodyImg(g_pImgManager->FindImage("btn-rungame"));
    m_btnGoRungame.SetupForSprites();
    m_btnGoDodonpachi.SetBodyImg(g_pImgManager->FindImage("btn-dodonpachi"));
    m_btnGoDodonpachi.SetupForSprites();
    m_btnGoFortress.SetBodyImg(g_pImgManager->FindImage("btn-fortress"));
    m_btnGoFortress.SetupForSprites();
    m_btnGoRpg.SetBodyImg(g_pImgManager->FindImage("btn-rpg"));
    m_btnGoRpg.SetupForSprites();
}

void TitleScene::Update()
{
    m_btnGoRungame.Update();
    m_btnGoDodonpachi.Update();
    m_btnGoFortress.Update();
    m_btnGoRpg.Update();

    InputController();
}

void TitleScene::Render()
{
    m_btnGoRungame.Render(g_hDC);
    m_btnGoDodonpachi.Render(g_hDC);
    m_btnGoFortress.Render(g_hDC);
    m_btnGoRpg.Render(g_hDC);
}

void TitleScene::Release()
{
}

void TitleScene::InputController()
{
    if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
    {
        if (PtInRect(&m_btnGoRungame.GetBodyRect(), g_ptMouse))
            GoSelectedScene(m_btnGoRungame.GetTagName());
        else if (PtInRect(&m_btnGoDodonpachi.GetBodyRect(), g_ptMouse))
            GoSelectedScene(m_btnGoDodonpachi.GetTagName());
        else if (PtInRect(&m_btnGoFortress.GetBodyRect(), g_ptMouse))
            GoSelectedScene(m_btnGoFortress.GetTagName());
        else if (PtInRect(&m_btnGoRpg.GetBodyRect(), g_ptMouse))
            GoSelectedScene(m_btnGoRpg.GetTagName());
    }

    if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
        g_pScnManager->ChangeScene("exit");
}

void TitleScene::GoSelectedScene(string Scene)
{
    g_pScnManager->SetNextScene(Scene);
    g_pScnManager->ChangeScene("loading");
}
