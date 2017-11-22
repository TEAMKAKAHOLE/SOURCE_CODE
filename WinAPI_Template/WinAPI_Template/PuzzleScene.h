#pragma once
#include "GameNode.h"
#include "Player.h"

class PuzzleScene : public GameNode
{
private:
	//�÷��̾�� ������� �� ����
	ImageObject*	m_imgWorldBuffer;
	//����Ÿ ó���� �ȵ� ����� ������� 2048 * 2048
	ImageObject*	m_imgWorldMap;
	//�浹 ó���ҋ��� �׸���
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

