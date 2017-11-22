#pragma once
#include "GameNode.h"
#include "Player.h"

class PuzzleScene : public GameNode
{
private:
	//플레이어와 월드맵이 들어갈 버퍼
	ImageObject*	m_imgWorldBuffer;
	//마젠타 처리가 안된 월드맵 사이즈는 2048 * 2048
	ImageObject*	m_imgWorldMap;
	//충돌 처리할떄만 그리는
	ImageObject*	m_imgTerrainBuffer;

	Player		m_Player;

public:
	PuzzleScene();
	virtual ~PuzzleScene();

	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

