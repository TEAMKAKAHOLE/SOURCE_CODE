#pragma once
#include "SpritesObject.h"

class Item : public SpritesObject
{
private:
    bool    m_isActive;
    int     m_nCount;
    bool    m_onField;
    float   m_fActiveTime;
    float   m_fExpireTime;

public:
    Item();
    ~Item();

    int GetCount() { return m_nCount; }
    void SumCount(int Count = 1) { m_nCount += Count; }
    
    void SetOnField(bool OnField) { m_onField; }
    
    void SetActiveTime(float ActTime) { m_fActiveTime = ActTime; }
    void SetExpireTime(float ExpTime) { m_fExpireTime = ExpTime; }
    
    bool IsActive() { return m_isActive; }
    void Activate() { m_isActive = true; }
    void Deactivate() { m_isActive = false; }

    void Start();
    virtual void Update() override;
    virtual void Render(HDC hdc) override;
};