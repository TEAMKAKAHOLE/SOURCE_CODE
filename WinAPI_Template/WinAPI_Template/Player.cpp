#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	
}

Player::~Player()
{
}

void Player::Update()
{
	isAnimate = false; // �ƹ� ���۵� ���� ���¿��� �ִϸ��̼��� false
	PlayerController(); // �÷��̾� ��Ʈ�� �Լ� ȣ���ؿ´�
	if (isAnimate == false) // �ִϸ��̼��� false���
		SetFrameX(0);		// �÷��̾��� ������x�� 0���� ����

	SpritesObject::Update();

	
	UnitPos ProbePos = m_dPos;
	//ProbePos.x = m_nSize.w / 4;
	//ProbePos.y = m_nSize.h / 4;

	if (g_pPixelManager->CheckPixelMagenta(m_imgTerrainBuffer, ProbePos)==true)
	{
		int rollbackPosX = 0;
		int rollbackPosY = 0;

		if (g_pPixelManager->CheckPixelMagenta(m_imgTerrainBuffer, ProbePos.x - rollbackPosX - 1, ProbePos.y))
		{
			rollbackPosX++;
			m_dPos.x = m_dPos.x - rollbackPosX;
		}
		if (g_pPixelManager->CheckPixelMagenta(m_imgTerrainBuffer, ProbePos.x + rollbackPosX + 1, ProbePos.y))
		{
			rollbackPosX--;
			m_dPos.x = m_dPos.x + rollbackPosX;
		}

		if (g_pPixelManager->CheckPixelMagenta(m_imgTerrainBuffer, ProbePos.x, ProbePos.y - rollbackPosY - 1))
		{
			rollbackPosY++;
			m_dPos.y = m_dPos.y - rollbackPosY;
		}
		if (g_pPixelManager->CheckPixelMagenta(m_imgTerrainBuffer, ProbePos.x, ProbePos.y + rollbackPosY + 1))
		{
			rollbackPosY--;
			m_dPos.y = m_dPos.y + rollbackPosY;
		}
	}
}

void Player::Render(HDC hdc)
{
	SpritesObject::Render(hdc);
}

void Player::PlayerController()
{
	UnitSpeed  speed = { 0.0f,0.0f }; // ���� x, y  ���ǵ带 �������ش�
	if (g_pKeyManager->isStayKeyDown(VK_LEFT))
	{
		speed.x -= 7.0f;
		SetFrameY(4);
		isAnimate = true;
	}
	else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
	{
		speed.x += 7.0f;
		SetFrameY(2);
		isAnimate = true;
	}

	if (g_pKeyManager->isStayKeyDown(VK_UP))
	{
		speed.y -= 7.0f;
		SetFrameY(6);
		isAnimate = true;
	}

	if (g_pKeyManager->isStayKeyDown(VK_DOWN))
	{
		speed.y += 7.0f;
		SetFrameY(0);
		isAnimate = true;
	}

	m_dSpeed = speed;
}

