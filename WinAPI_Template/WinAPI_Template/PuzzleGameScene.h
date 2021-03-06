#pragma once
#include "GameNode.h"

struct tagBlock
{
    POINT ptDest;
    POINT ptSour;
};
class PuzzleGameScene : public GameNode
{
private:
    json                m_playerData;
    ImageObject*        m_imgPuzzle;
    ImageObject*        m_imgBg;
    tagBlock            m_stBlock[9];
    int                    m_nLastBlock;
    int                    m_nChageSceneDelay;
	int					m_nSoundPlayCount;
    bool                m_isPlaying;
    bool                m_isPuzzleClear;
    int m_nAlpha;

public:
    PuzzleGameScene();
    virtual ~PuzzleGameScene();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;

    void Suffle();
    void Swap(int dest, int sour);
};