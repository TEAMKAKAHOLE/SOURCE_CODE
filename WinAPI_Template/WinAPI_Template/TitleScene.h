﻿#pragma once
#include "GameNode.h"
#include "SpritesObject.h"

class TitleScene : public GameNode
{
private:
    SpritesObject       m_btnGoRungame;
    SpritesObject       m_btnGoDodonpachi;
    SpritesObject       m_btnGoFortress;
    SpritesObject       m_btnGoRpg;

public:
    TitleScene();
    ~TitleScene();

    // GameNode을(를) 통해 상속됨
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;

    void InputController();
    void GoSelectedScene(string Scene);
};