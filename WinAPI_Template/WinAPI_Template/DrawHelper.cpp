#include "stdafx.h"
#include "DrawHelper.h"

DrawHelper::DrawHelper()
{
    m_pBrushRed = new HBRUSH;
    m_pBrushGreen = new HBRUSH;
    m_pBrushBlue = new HBRUSH;

    *m_pBrushRed = CreateSolidBrush(RGB(255, 0, 0));
    *m_pBrushGreen = CreateSolidBrush(RGB(0, 255, 0));
    *m_pBrushBlue = CreateSolidBrush(RGB(0, 0, 255));
}

DrawHelper::~DrawHelper()
{
    SAFE_DELETE(m_pBrushRed);
    SAFE_DELETE(m_pBrushGreen);
    SAFE_DELETE(m_pBrushBlue);
}

bool DrawHelper::DrawLine2D(HDC hdc, UnitPos Pos1, UnitPos Pos2, int PenWidth, int ColorCode)
{
    HPEN* hPen = new HPEN; 
    switch (ColorCode)
    {
    case 1:
        *hPen = CreatePen(PS_SOLID, PenWidth, RGB(255, 0, 0));
        break;
    case 2:
        *hPen = CreatePen(PS_SOLID, PenWidth, RGB(0, 255, 0));
        break;
    case 3:
        *hPen = CreatePen(PS_SOLID, PenWidth, RGB(0, 0, 255));
        break;
    default:
        *hPen = CreatePen(PS_SOLID, PenWidth, RGB(0, 0, 0));
        break;
    }
    SelectObject(hdc, *hPen);
    MoveToEx(hdc, (int)Pos1.x, (int)Pos1.y, NULL);
    LineTo(hdc, (int)Pos2.x, (int)Pos2.y);
    DeleteObject(*hPen);
    SAFE_DELETE(hPen);

    return true;
}

void DrawHelper::DrawBoxLine2D(HDC hdc, RECT rt, int LineWidth, int ColorCode)
{
    UnitPos lt = { (double)rt.left, (double)rt.top };
    UnitPos rb = { (double)rt.right, (double)rt.bottom };

    DrawLine2D(hdc, lt, UnitPos{ rb.x, lt.y }, LineWidth, ColorCode);
    DrawLine2D(hdc, lt, UnitPos{ lt.x, rb.y }, LineWidth, ColorCode);
    DrawLine2D(hdc, rb, UnitPos{ rb.x, lt.y }, LineWidth, ColorCode);
    DrawLine2D(hdc, rb, UnitPos{ lt.x, rb.y }, LineWidth, ColorCode);
}

RECT DrawHelper::MakeRect(UnitPos Pos, UnitSize Size)
{
    RECT rt;
    rt.left = (int)(Pos.x - Size.w * 0.5f);
    rt.top  = (int)(Pos.y - Size.h * 0.5f);
    rt.right = rt.left + Size.w;
    rt.bottom = rt.top + Size.h;

    return rt;
}

void DrawHelper::DrawRect(HDC hdc, RECT Rect)
{
    Rectangle(hdc, Rect.left, Rect.top, Rect.right, Rect.bottom);
}

void DrawHelper::DrawRect(HDC hdc, RECT Rect, HBRUSH Brush)
{
    FillRect(hdc, &Rect, Brush);
}

void DrawHelper::DrawEllipse(HDC hdc, RECT Rect)
{
    Ellipse(hdc, Rect.left, Rect.top, Rect.right, Rect.bottom);
}

RECT DrawHelper::MakeViewPort(UnitPos Pos, ImageObject* WorldMap)
{
    RectMargin margin = { 0, 0, 0, 0 };
    return MakeViewPort(Pos, margin, WorldMap);
}

RECT DrawHelper::MakeViewPort(UnitPos Pos, RectMargin Margin, ImageObject * WorldMap)
{
    int w = W_WIDTH - Margin.left - Margin.right;
    int h = W_HEIGHT - Margin.top - Margin.bottom;
    RECT rtViewPort = MakeRect(Pos, { w, h });
    if (rtViewPort.left < 0)
    {
        rtViewPort.left = 0;
        rtViewPort.right = rtViewPort.left + w;
    }
    else if (rtViewPort.right > WorldMap->GetWidth())
    {
        rtViewPort.right = WorldMap->GetWidth();
        rtViewPort.left = rtViewPort.right - w;
    }

    if (rtViewPort.top < 0)
    {
        rtViewPort.top = 0;
        rtViewPort.bottom = rtViewPort.top + h;
    }
    else if (rtViewPort.bottom > WorldMap->GetHeight())
    {
        rtViewPort.bottom = WorldMap->GetHeight();
        rtViewPort.top = rtViewPort.bottom - h;
    }

    return rtViewPort;
}

void DrawHelper::DrawTextBox(HDC hdc, RECT TxtBox, string TextString)
{
    HFONT hFont, hTmp;
    int FontSize = TxtBox.bottom - TxtBox.top;
    SetTextColor(hdc, RGB(m_textBoxInfo.FontColor.R
                            , m_textBoxInfo.FontColor.G
                            , m_textBoxInfo.FontColor.B));
    hFont = CreateFont(FontSize, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 2, 0, m_textBoxInfo.FontName.data());
    hTmp = (HFONT)SelectObject(hdc, hFont);
    SetBkMode(hdc, TRANSPARENT);
    if (m_textBoxInfo.IsVisibleBox)
    {
        HBRUSH* pBrush = new HBRUSH;
        *pBrush = CreateSolidBrush(RGB(m_textBoxInfo.BoxColor.R, m_textBoxInfo.BoxColor.G, m_textBoxInfo.BoxColor.B));
        FillRect(hdc, &TxtBox, *pBrush);
        SAFE_DELETE(pBrush);
    }
    DrawText(hdc, TextString.data(), -1, &TxtBox, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    DeleteObject(SelectObject(hdc, hTmp));
    SetBkMode(hdc, BKMODE_LAST);
}

void DrawHelper::DrawTextBox(HDC hdc, RECT TxtBox, int FontSize, string TextString)
{
    HFONT hFont, hTmp;
    SetTextColor(hdc, RGB(m_textBoxInfo.FontColor.R
        , m_textBoxInfo.FontColor.G
        , m_textBoxInfo.FontColor.B));
    hFont = CreateFont(FontSize, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 2, 0, m_textBoxInfo.FontName.data());
    hTmp = (HFONT)SelectObject(hdc, hFont);
    SetBkMode(hdc, TRANSPARENT);
    if (m_textBoxInfo.IsVisibleBox)
    {
        HBRUSH* pBrush = new HBRUSH;
        *pBrush = CreateSolidBrush(RGB(m_textBoxInfo.BoxColor.R, m_textBoxInfo.BoxColor.G, m_textBoxInfo.BoxColor.B));
        FillRect(hdc, &TxtBox, *pBrush);
        SAFE_DELETE(pBrush);
    }
    DrawText(hdc, TextString.data(), -1, &TxtBox, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    DeleteObject(SelectObject(hdc, hTmp));
    SetBkMode(hdc, BKMODE_LAST);
}

UnitSize DrawHelper::GetSizeFromRect(RECT Rect)
{
    return UnitSize{ Rect.right - Rect.left, Rect.bottom - Rect.top };
}

UnitPos DrawHelper::GetPosFromRect(RECT Rect)
{
    UnitSize nSize = GetSizeFromRect(Rect);
    return UnitPos{ (double)(Rect.left + (nSize.w * 0.5f))
                  , (double)(Rect.top  + (nSize.h * 0.5f)) };
}
