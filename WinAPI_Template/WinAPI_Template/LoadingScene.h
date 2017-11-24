#pragma once
#include "GameNode.h"
#include "ProgressBarObject.h"
#include "SpritesObject.h"

class LoadingScene : public GameNode
{
private:
    E_RSC_LOAD_TYPE m_loadType;

    ImageObject*    m_prgBarBg;
    ImageObject*    m_prgBarFg;
	ImageObject*    m_loadingBg;
	SpritesObject*  m_sprLinkRun;

    string      m_szDestScene;

    bool        m_isLoadDone;
    LoadResult  m_tagImgLoadResult;
    LoadResult  m_tagSndLoadResult;
    double      m_dPartLoadRatio;

    int         m_nEntireCount;
    int         m_nLoadedCount;
    double      m_dEntireLoadRatio;

    ProgressBarObject   m_entirePrgsBar;
    ProgressBarObject   m_partPrgsBar;

    float       m_fCurrTime;
    float       m_fDestTime;

public:
    LoadingScene();
    ~LoadingScene();

    void LoadingImage();
    void LoadingSound();

#pragma region GET
    string  GetDestScene() { return m_szDestScene; }
#pragma endregion
#pragma region SET
    void SetDestScene(string DestScene) { m_szDestScene = DestScene; }
#pragma endregion

    // GameNode을(를) 통해 상속됨
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};