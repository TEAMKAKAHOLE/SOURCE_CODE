#pragma once
#include "GameNode.h"

class EndingCreditScene : public GameNode
{
public:
    EndingCreditScene();
    ~EndingCreditScene();

    // GameNode��(��) ���� ��ӵ�
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};