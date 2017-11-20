#pragma once
#include "GameObject.h"
#include "SpritesObject.h"

class MapObject : public GameObject
{
private:
    ImageObject*        m_imgMapBuffer;
    vector<GameObject>  m_vecObjs;
    double              m_dGravity;

public:
    MapObject();
    ~MapObject();

#pragma region GET
#pragma endregion
#pragma region SET
    void    SetGravity(double Gravity) { m_dGravity = Gravity; }
#pragma endregion


    void Start();
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void AddObject(GameObject GameObj);
    void ApplyGravity(GameObject* GameObj);
};

