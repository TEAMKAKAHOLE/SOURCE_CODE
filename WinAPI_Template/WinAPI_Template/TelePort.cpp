#include "stdafx.h"
#include "TelePort.h"


TelePort::TelePort()
{
	//���۰� ���ÿ�  ��ġ �̵� ������ �Ѵ�.
	//if out�� ��쿡�� ���Ϳ��� �̰ݰŸ��� �ش�
	//�ȱ׷��� �浹üũ �ٽ� �߻��ؼ� �̻��� ��ġ�� �̵�
	AGateIn.x  = 385*4;
	AGateIn.y  = 300 * 4;

	AGateOut.x = 250 * 4;
	AGateOut.y = 250 * 4;


	BGateIn.x = 418*4;
	BGateIn.y = 208*4;

	BGateOut.x = 92 * 4;
	BGateOut.y = 290 * 4;

	CGateIn.x = 250 * 4;
	CGateIn.y = 250 * 4;

	CGateOut.x = 80*4;
	CGateOut.y = 170*4;

	DGateIn.x = 92 * 4;
	DGateIn.y = 290 * 4;

	DGateOut.x = 385 * 4;
	DGateOut.y = 300 * 4;





	GameObject::GameObject();


}


TelePort::~TelePort()
{

}

void TelePort::Update()
{
	GameObject::Update();
}

void TelePort::Render(HDC hdc)
{
	//�θ������Ʈ��  ������ ����ϰڴ�.
	GameObject::Render(hdc);
}

void TelePort::telePort(int x, int y)
{

}
