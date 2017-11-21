#pragma once
#include "GameNode.h"

#pragma region SCENE
#include "SplashScene.h"
#include "TitleScene.h"
#include "LoadingScene.h"
#include "TownScene.h"
#include "ExitScene.h"
#pragma endregion

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    string      m_szVerInfo;
//=======================================================
//  FUNCTIONS
private:
public:
    MainGame();
    ~MainGame();

    // GameNode을(를) 통해 상속됨
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;

#pragma region CONTROLLER
    void    SystemController();
    void    MouseLock();
    void    MouseUnlock();
#pragma endregion

    void    VerInfoStamp();
};