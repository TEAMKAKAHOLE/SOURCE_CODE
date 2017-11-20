#pragma once
#include "GameNode.h"
#include "SpritesObject.h"

class GameScene : public GameNode
{
private:

public:
    GameScene();
    virtual ~GameScene();

    // GameNode을(를) 통해 상속됨
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;

    void NewGame();
    void SaveGame();
    bool LoadGame();

    void PlayerController();
};