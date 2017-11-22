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
	ImageObject*		m_imgPuzzle;
	ImageObject*		m_imgBg;
	tagBlock			m_stBlock[9];
	int					m_nLastBlock;
	bool				m_isPlaying;
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