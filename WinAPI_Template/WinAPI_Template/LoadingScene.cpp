#include "stdafx.h"
#include "LoadingScene.h"


LoadingScene::LoadingScene()
    : m_szDestScene("")
    , m_dPartLoadRatio(0.0f)
    , m_nEntireCount(0)
    , m_nLoadedCount(0)
    , m_dEntireLoadRatio(0.0f)
    , m_isLoadDone(false)
    , m_loadType(LOAD_EMPTY)
{
    m_szTagName = "loading";
}

LoadingScene::~LoadingScene()
{
}

void LoadingScene::LoadingImage()
{
    //  image load
    if (g_pImgManager->AddImageByJson(m_szDestScene))
    {
        ++m_tagImgLoadResult.nHead;
        ++m_nLoadedCount;
        string log = "load image : ";
        log += to_string(m_tagImgLoadResult.nHead) + "/" + to_string(m_tagImgLoadResult.nMax);
        g_pLogManager->WriteLog(EL_INFO, log);

        //  image load count increase
        m_dPartLoadRatio = (double)m_tagImgLoadResult.nHead / (double)m_tagImgLoadResult.nMax;
    }
    else
    {
        m_dPartLoadRatio = 0.0f;
        m_loadType = LOAD_SND_FILE;
    }
}

void LoadingScene::LoadingSound()
{
    //  sound load
    if (g_pSndManager->AddSoundByJson(m_szDestScene))
    {
        ++m_tagSndLoadResult.nHead;
        ++m_nLoadedCount;
        string log = "load sound : ";
        log += to_string(m_tagSndLoadResult.nHead) + "/" + to_string(m_tagSndLoadResult.nMax);
        g_pLogManager->WriteLog(EL_INFO, log);
        //  sound load count increase
        m_dPartLoadRatio = (double)m_tagSndLoadResult.nHead / (double)m_tagSndLoadResult.nMax;
    }
    else
    {
        m_loadType = LOAD_END;
    }
}

void LoadingScene::Start()
{
    m_loadType = LOAD_IMG_FILE;
    m_isLoadDone = false;
    m_nEntireCount = 0;
    m_nLoadedCount = 0;
    m_dEntireLoadRatio = 0.0f;
    m_dPartLoadRatio = 0.0f;
    m_szDestScene = g_pScnManager->GetNextScene();

    //  loading scene resource
    g_pImgManager->AddImageList(m_szTagName);
    g_pSndManager->AddSoundList(m_szTagName);
    while (g_pImgManager->AddImageByJson(m_szTagName));
    while (g_pSndManager->AddSoundByJson(m_szTagName));

    //  dest scene resource
    g_pImgManager->AddImageList(m_szDestScene);
    g_pSndManager->AddSoundList(m_szDestScene);
    m_tagImgLoadResult = g_pImgManager->GetLoadResult();
    m_tagSndLoadResult = g_pSndManager->GetLoadResult();

    //  entire count setup
    m_nEntireCount = m_tagImgLoadResult.nMax + m_tagSndLoadResult.nMax;

    //  entire progress bar
    m_entirePrgsBar.SetGaugeRatioX(0.0f);
    m_entirePrgsBar.SetBgBar(g_pImgManager->FindImage("bg-gauge"));
    m_entirePrgsBar.SetBodyImg(g_pImgManager->FindImage("fg-gauge"));
	m_entirePrgsBar.SetBodyPos({W_WIDTH * 0.5f, W_HEIGHT - 60});
    m_entirePrgsBar.SetBodySize({ 1200, 20 });
    m_entirePrgsBar.Update();


    //  part progress bar
    m_partPrgsBar.SetGaugeRatioX(0.0f);
    m_partPrgsBar.SetBgBar(g_pImgManager->FindImage("bg-gauge"));
    m_partPrgsBar.SetBodyImg(g_pImgManager->FindImage("fg-gauge"));
    m_partPrgsBar.SetBodyPos({ W_WIDTH * 0.5f, W_HEIGHT - 55 });
    m_partPrgsBar.SumBodyPosY(25);
    m_partPrgsBar.SetBodySize({ 1200, 20 });
    m_partPrgsBar.Update();


	m_loadingBg = g_pImgManager->FindImage("Zelda-bg");
}

void LoadingScene::Update()
{
    m_dEntireLoadRatio = (double)m_nLoadedCount / (double)m_nEntireCount;
    m_entirePrgsBar.SetGaugeRatioX(m_dEntireLoadRatio);
    m_partPrgsBar.SetGaugeRatioX(m_dPartLoadRatio);

    switch (m_loadType)
    {
    case LOAD_IMG_FILE:
    {
        LoadingImage();
        break;
    }
    case LOAD_SND_FILE:
    {
        LoadingSound();
        break;
    }
    case LOAD_END:
        break;
    }

    if (m_nEntireCount == m_nLoadedCount)
        m_isLoadDone = true;

    if (m_isLoadDone)
    {
        m_fCurrTime = g_pTimerManager->GetWorldTime();
        if (m_fCurrTime > m_fDestTime)
            g_pScnManager->NextScene();
    }
    else
    {
        m_fDestTime = g_pTimerManager->GetWorldTime() + 1.0f;
    }
}

void LoadingScene::Render()
{
	m_loadingBg->Render(g_hDC, 0, 0, W_WIDTH, W_HEIGHT);
    m_entirePrgsBar.Render(g_hDC);
    m_partPrgsBar.Render(g_hDC);
	


#ifdef _DEBUG
    TextOut(g_hDC, W_WIDTH - 100, 0, m_szTagName.c_str(), (int)strlen(m_szTagName.c_str()));
#endif // _DEBUG
}

void LoadingScene::Release()
{
}
