#pragma once
#include "GameNode.h"
#include "Player.h"
#include "SpritesObject.h"

class PuzzleScene : public GameNode
{
private:
	json			m_playerData;
	//플레이어와 월드맵이 들어갈 버퍼
	ImageObject*	m_imgWorldBuffer;
	//
	ImageObject*	m_imgWorldMap;
	//
	ImageObject*	m_imgTerrainBuffer;
    ImageObject*    m_imgUiBuffer;
	
	SpritesObject	m_Object;
	SpritesObject	m_imgHintLetter1;
	SpritesObject	m_StartLocation;
	SpritesObject	m_Exit1;
	SpritesObject	m_Exit2;
	SpritesObject	m_imgHardway;
	SpritesObject	m_imgNormalway;
	SpritesObject	m_GameStartLocation;

	Player		m_Player;

	int			m_nScnLevel;
	bool		m_isStageClear;
	bool		m_isPuzzleClear;
	bool		m_isExitMessage1;
	bool		m_isExitMessage2;
	bool		m_isHint1On;
	bool		m_isHintCheck;
	bool		m_isSignUp;

public:
	PuzzleScene();
	virtual ~PuzzleScene();

	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};
