#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Store.h"
#include "SpritesObject.h"

class GameScene : public GameNode
{
private:
    ImageObject*        m_magentaBuffer;
    ImageObject*        m_gameBoardBuffer;
    ImageObject*        m_uiBuffer;

    SpritesObject       m_map;
    Player              m_player;
    SpritesObject       m_storeEntrance;
    SpritesObject       m_armoryEntrance;
    SpritesObject       m_dungeon1;
    SpritesObject       m_dungeon2;

    E_STORE             m_currPlace;
    Store               m_store;

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

    void StoreRender();
};