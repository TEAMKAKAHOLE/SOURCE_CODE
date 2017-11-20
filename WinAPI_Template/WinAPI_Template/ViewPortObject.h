#pragma once
class ViewPortObject
{
private:
    bool        m_bIsArrive;
    double      m_dT;
    UnitPos     m_startPos;
    UnitPos     m_currPos;
    UnitPos     m_destPos;

public:
    ViewPortObject();
    ~ViewPortObject();

#pragma region GET
    UnitPos     GetCurrPos() { return m_currPos; }
    UnitPos     GetDestPos() { return m_destPos; }
#pragma endregion
#pragma region SET
    void    SetCurrPos(UnitPos Pos) { m_currPos = Pos; }
    void    SetDestPos(UnitPos Pos) { m_destPos = Pos; }
#pragma endregion

    void MoveStart(UnitPos Dest);
    void Update();
    RECT MakeViewPort(UnitSize LimitSize);
};