#include "stdafx.h"
#include "GameNode.h"


GameNode::GameNode()
{
    m_pImgBackBuffer = new ImageObject;
    m_pImgBackBuffer->Setup(W_WIDTH, W_HEIGHT);
    m_szTagName = "";
}

GameNode::GameNode(string TagName)
{
    m_szTagName = TagName;
}


GameNode::~GameNode()
{
    SAFE_DELETE(m_pImgBackBuffer);
}

void GameNode::Update()
{
    InvalidateRect(g_hWnd, NULL, false);
}

LRESULT GameNode::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    g_hDC = this->m_pImgBackBuffer->GetMemDC();

    switch (message)
    {
    case WM_CREATE:
        srand((unsigned int)time(NULL));
        break;
    case WM_MOUSEMOVE:
        g_ptMouse.x = LOWORD(lParam);
        g_ptMouse.y = HIWORD(lParam);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}
