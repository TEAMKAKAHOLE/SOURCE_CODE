#pragma once
#include "ImageObject.h"

class GameNode
{
protected:
    string          m_szTagName;
    ImageObject*    m_pImgBackBuffer;

public:
    void            SetTagName(string TagName) { m_szTagName = TagName; }
    const string    GetTagName() { return m_szTagName; }

    GameNode();
    GameNode(string TagName);
    virtual ~GameNode();

    virtual void Start() PURE;
    virtual void Update();
    virtual void Render() PURE;
    virtual void Release() PURE;

    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};