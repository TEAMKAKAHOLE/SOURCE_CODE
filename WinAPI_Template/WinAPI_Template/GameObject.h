#pragma once

//  Mutual Refernce
class ImageObject;
class GameObject
{
    //  VARS
private:
    bool            m_bIsSetup;
protected:
    int             m_uId;              //  Unique
    string          m_szTagName;        //  TagName

//--------------------------------------------------------------------------
//      BODY
    RECT            m_rtBody;           //  Body rectangle
    ImageObject*    m_imgBody;          //  Image paste on body rect
    UnitPos         m_dPos;             //  Center position of Object
    UnitSpeed       m_dSpeed;           //  Move to XY each Move() function
    UnitSize        m_nSize;            //  Width, Height of body rect
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//      HIT BOX
    RECT            m_rtHitBox;         //  Hit box for calc only
    UnitSize        m_nSizeHBox;        //  Hit box size
    RectMargin      m_nMarginHBox;      //  Hit box margin
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//      SNAP SHOT
    UnitPos         m_startPos;
    UnitPos         m_viaPos;
    UnitPos         m_destPos;
    double          m_dT;
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//      PROBE
    UnitPos         m_probe;
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//      LOCK IN 
    RECT            m_rtLockArea;
    bool            m_isLockInWnd;      //  Never escape window
//--------------------------------------------------------------------------
    bool            m_isImmortal;
    bool            m_isVisible;        //  Render or not
    bool            m_isMovable;        //  Move or not
    bool            m_isRigid;          //  Collide or not
    bool            m_isAlive;
    double          m_dAlpha;
    double          m_dAngle;
    bool            m_isRotate;

    int             m_nLife;

public:

    //  FUNCS
public:
    GameObject();
    GameObject(string szTagName);
    ~GameObject();
    virtual void Setup();

#pragma region GET
    //  Identifier
    int         GetUid()        { return m_uId; }
    string      GetTagName()    { return m_szTagName; }
    //  Body
    RECT            GetBodyRect()   { return m_rtBody; }
    UnitPos         GetBodyPos()        { return m_dPos; }
    UnitPos*        GetBodyPosRef()     { return &m_dPos; }
    UnitSize        GetBodySize()       { return m_nSize; }
    UnitSpeed       GetBodySpeed()      { return m_dSpeed; }
    ImageObject*    GetBodyImg()   { return m_imgBody; }
    double          GetBodySpeedX() { return m_dSpeed.x; }
    double          GetBodySpeedY() { return m_dSpeed.y; }
    //  HitBox
    RECT        GetHBoxRect()   { return m_rtHitBox; }
    UnitSize    GetHBoxSize()   { return m_nSizeHBox; }
    //  Snap shot
    UnitPos     GetStartPos()   { return m_startPos; }
    UnitPos     GetDestPos()    { return m_destPos; }
    UnitPos     GetTrvlPos()    { return m_viaPos;}
    //  Probe
    UnitPos     GetHBoxBotProbe();
    UnitPos     GetHBoxTopProbe();
    UnitPos     GetHBoxRightProbe();
    UnitPos     GetHBoxLeftProbe();

    bool        IsImmortal()    { return m_isImmortal; }
    bool        IsVisible()     { return m_isVisible; }
    bool        IsAlive()       { return m_isAlive; }
    bool        IsLockInWnd()   { return m_isLockInWnd; }
    int         GetLife()       { return m_nLife; }

    double      GetAlpha()      { return m_dAlpha; }
#pragma endregion

#pragma region SET
    //  Identifier
    void SetUid(int Id)             { m_uId = Id; }
    void SetTagName(string TagName) { m_szTagName = TagName; }
    //  Body
    void SetBodyRect();
    void SetBodyRect(RECT Rect);
    void SetBodySize(UnitSize Size)     { m_nSize = Size; }
    void SetBodySpeed(UnitSpeed Speed)  { m_dSpeed = Speed; }
    void SetBodyPos(UnitPos Pos)        { m_dPos = Pos; }
    void SumBodyPosX(double PosX) { m_dPos.x += PosX; }
    void SumBodyPosY(double PosY) { m_dPos.y += PosY; }
    void SetBodySpeedX(double SpeedX) { m_dSpeed.x = SpeedX; }
    void SetBodySpeedY(double SpeedY) { m_dSpeed.y = SpeedY; }
    void SumBodySpeed(UnitSpeed Speed) { m_dSpeed.x += Speed.x; m_dSpeed.y += Speed.y; }
    void SumBodySpeedX(double SpeedX) { m_dSpeed.x += SpeedX; }
    void SumBodySpeedY(double SpeedY) { m_dSpeed.y += SpeedY; }
    //  Body image
    void SetBodyImg(ImageObject* Image) { m_imgBody = Image; }
    void SetBodyImgAuto();
    void SetBodyImgByKey(string Key, bool IsOverwrite = false);
    //  HitBox
    void SetHBoxMargin(RectMargin HBoxMargin) { m_nMarginHBox = HBoxMargin; }
    void SetHBox();
	//	Snap shot
	void SetStartPos(UnitPos Pos) { m_startPos = Pos; }
	void SetViaPos(UnitPos Pos) { m_viaPos = Pos; }
	void SetDestPos(UnitPos Pos) { m_destPos = Pos; }
    //  Lock area
    void SetLockArea(RECT Area) { m_rtLockArea = Area; }
    void LockInWnd()    { m_isLockInWnd = true; }
    void UnlockInWnd()  { m_isLockInWnd = false; }

    //  Exterior
    void SetAlpha(double Alpha) { m_dAlpha = Alpha; }
    void SetImmortal()  { m_isImmortal = true; }
    void SetMortal()    { m_isImmortal = false; }
    void SetVisible()   { m_isVisible = true; }
    void SetInvisible() { m_isVisible = false; }
    void SetAlive()     { m_isAlive = true; }
    void SetDead()      { if (!m_isImmortal) m_isAlive = false; }
    void SetLife(int Life) { m_nLife = Life; }
    void SumLife(int Deal) { m_nLife += Deal; }

#pragma endregion

    //  Update / Render
    virtual void Update();
    virtual void Render(HDC hdc);

    //  Object move
    virtual void Move();

    void Setup(UnitPos Pos, UnitSize Size);

    void WndLocker();
};

