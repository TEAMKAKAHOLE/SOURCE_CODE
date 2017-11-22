#pragma once
#include "GameNode.h"
#include "Player.h"
#include "SpritesObject.h"

class PuzzleScene : public GameNode
{
private:
	//플레이어와 월드맵이 들어갈 버퍼
	ImageObject*	m_imgWorldBuffer;
	//마젠타 처리가 안된 월드맵 사이즈는 512 * 512
	ImageObject*	m_imgWorldMap;
	//충돌 처리할떄만 그리는
	ImageObject*	m_imgTerrainBuffer;
	
	SpritesObject	m_Object;
	SpritesObject	m_imgHintLetter1;
	SpritesObject	m_StartLocation;
	SpritesObject	m_Exit1;
	SpritesObject	m_Exit2;
	SpritesObject	m_imgHardway;
	SpritesObject	m_imgNormalway;
	SpritesObject	m_GameStartLocation;

	Player		m_Player;

	bool		m_isStageClear;
	bool		m_isPuzzleClear;
	bool		m_isExitMessage1;
	bool		m_isExitMessage2;
	bool		m_isHint1On;
	bool		m_isHint2On;
	bool		m_isHint3On;
	bool		m_isSignUp;

public:
	PuzzleScene();
	virtual ~PuzzleScene();

	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

