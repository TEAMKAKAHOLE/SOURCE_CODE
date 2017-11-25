#include "stdafx.h"
#include "PuzzleGameScene.h"


PuzzleGameScene::PuzzleGameScene()
    : m_isPlaying(true)
    , m_isPuzzleClear(false)
    , m_nAlpha(0)
    , m_nChageSceneDelay(300)
{
    //로딩없이 퍼즐게임으로 전환
    m_szTagName = "puzzle-game";
    g_pImgManager->AddImageList(m_szTagName);
    while (g_pImgManager->AddImageByJson(m_szTagName));
    g_pSndManager->AddSoundList(m_szTagName);
    while (g_pSndManager->AddSoundByJson(m_szTagName));
}


PuzzleGameScene::~PuzzleGameScene()
{
}

void PuzzleGameScene::Start()
{
    m_playerData = g_pFileManager->JsonFind("player");
    g_pImgManager->AddImageList(m_szTagName);
    while (g_pImgManager->AddImageByJson(m_szTagName));

    m_imgPuzzle = g_pImgManager->FindImage("puzzle-img");
    m_imgBg = g_pImgManager->FindImage("puzzle-bg");

    for (int i = 0; i < 3 * 3; i++)
    {
        //이미지 사이즈를 쪼갤 수로 나눈 후 곱해준다. 500 / 3 , 503 / 3
        m_stBlock[i].ptDest.x = i % 3 * 500 / 3 + 150;
        m_stBlock[i].ptDest.y = i / 3 * 503 / 3 + 100;
        m_stBlock[i].ptSour.x = i % 3 * 500 / 3;
        m_stBlock[i].ptSour.y = i / 3 * 503 / 3;
    }

    Suffle();

    if (!m_isPlaying)
        m_nChageSceneDelay = 4500;

    g_pSndManager->Play("puzzle-game");
}

void PuzzleGameScene::Update()
{
    if (m_isPlaying)
    {
        if (g_pKeyManager->isOnceKeyDown(VK_LEFT) && m_nLastBlock % 3 > 0)
        {
            Swap(m_nLastBlock, m_nLastBlock - 1);
            // 스왑 후 마지막칸 위치 변경
            m_nLastBlock -= 1;
        }
        else if (g_pKeyManager->isOnceKeyDown(VK_RIGHT) && m_nLastBlock % 3 < 2)
        {
            Swap(m_nLastBlock, m_nLastBlock + 1);
            m_nLastBlock += 1;
        }
        else if (g_pKeyManager->isOnceKeyDown(VK_UP) && m_nLastBlock / 3 > 0)
        {
            Swap(m_nLastBlock, m_nLastBlock - 3);
            m_nLastBlock -= 3;
        }
        else if (g_pKeyManager->isOnceKeyDown(VK_DOWN) && m_nLastBlock / 3 < 2)
        {
            Swap(m_nLastBlock, m_nLastBlock + 3);
            m_nLastBlock += 3;
        }

        //완성 검사. 포문이 다 돌게 되면 완성, 중단 되면 완성 x
        for (int i = 0; i < 8; i++)
        {
            if (m_stBlock[i].ptDest.x - 150 != m_stBlock[i].ptSour.x ||
                m_stBlock[i].ptDest.y - 100 != m_stBlock[i].ptSour.y)
                break;

            if (i == 7)
            {
                m_isPlaying = false;
            }
        }
#ifdef _DEBUG
        if (g_pKeyManager->isOnceKeyDown(VK_RBUTTON))
        {
            m_isPlaying = false;
        }
#endif // _DEBUG
    }
    else if (!m_isPlaying)
    {
        //제이썬에 데이터 넣기
        int m_nScnLevel;
        m_nScnLevel = 2;
        m_playerData["player"]["scn-level"] = m_nScnLevel;
        //아웃풋 스트림 열고 데이타 넣기 
        //ofstream outClearData;
        //outClearData.open("data/player.json", ios_base::out);
        //outClearData << m_playerData;
        //outClearData.close();

        //클리어 효과
        if (m_nAlpha < 255)
            m_nAlpha += 3;

        //클리어 후 씬 자동전환
        m_nChageSceneDelay--;
    }

    if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE) ||
        !m_isPlaying && m_nChageSceneDelay < 0)
    {
        g_pFileManager->JsonUpdate("player", m_playerData);
        g_pScnManager->ChangeScene("puzzle");
    }
}

void PuzzleGameScene::Render()
{
    //그림뒤에 검은 배경
    m_imgBg->Render(g_hDC, 0, 0, 768, 672);

    if (m_isPlaying)
    {
        //알파처리된 이미지를 밑에 깐다.
        m_imgPuzzle->AlphaRender(g_hDC, 150, 100, 128);

        for (int i = 0; i < 3 * 3; i++)
        {
            if (i == m_nLastBlock) continue;

            m_imgPuzzle->Render(g_hDC, m_stBlock[i].ptDest.x, m_stBlock[i].ptDest.y,
                m_stBlock[i].ptSour.x, m_stBlock[i].ptSour.y, 500 / 3, 503 / 3);
        }
    }
    else if (!m_isPlaying)
        m_imgPuzzle->AlphaRender(g_hDC, 150, 100, m_nAlpha);
    
}

void PuzzleGameScene::Release()
{
    g_pSndManager->Stop("puzzle-game");
}

void PuzzleGameScene::Suffle()
{
    for (int i = 0; i < 100; i++)
    {
        int sour = rand() % 8;
        int dest = rand() % 8;

        //짝수 횟수 아닐경우 예외
        if (sour == dest)
        {
            --i;
            continue;
        }
        Swap(dest, sour);
    }

    //마지막 블럭 설정
    m_nLastBlock = 8;
}

void PuzzleGameScene::Swap(int dest, int sour)
{
    POINT ptTemp = m_stBlock[dest].ptSour;
    m_stBlock[dest].ptSour = m_stBlock[sour].ptSour;
    m_stBlock[sour].ptSour = ptTemp;
}