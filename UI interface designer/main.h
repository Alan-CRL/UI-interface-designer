#include <bits/stdc++.h>
#include "resource.h"
#include <windows.h>
#include "HiEasyX.h"
#include <thread>
#include <io.h>

#pragma comment(lib, "MSIMG32.LIB")

using namespace std;

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#define BeginDraw BEGIN_TASK()
#define EndDraw END_TASK(); REDRAW_WINDOW()
#define Sleep(int) this_thread::sleep_for(chrono::milliseconds(int))
#define Test() MessageBox(NULL, L"��Ǵ�", L"���", MB_OK)

LOGFONT font;//ͳһ������ʽ
RECT words_rect;

//���ڿ��Ƽ�

struct
{
	int x, y;
	int height, width;
	int frame_hight, frame_width;
	int translucent;
	bool move;
} windows;

//---
//�ַ�����
string global_path;//ȫ��·��

//---
//ͼƬ����
IMAGE Logo;

//����͸��������
void setWindowTransparent(HWND HWnd, bool enable, int alpha = 0xFF)
{
	LONG nRet = ::GetWindowLong(HWnd, GWL_EXSTYLE);
	nRet |= WS_EX_LAYERED;
	::SetWindowLong(HWnd, GWL_EXSTYLE, nRet);
	if (!enable) alpha = 0xFF;
	SetLayeredWindowAttributes(HWnd, 0, alpha, LWA_ALPHA);
}
//string ת wstring
wstring convert_to_wstring(const string& s)
{
	LPCSTR pszSrc = s.c_str();
	int nLen = s.size();

	int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszSrc, nLen, 0, 0);
	if (nSize <= 0)
		return NULL;
	WCHAR* pwszDst = new WCHAR[nSize + 1];
	if (NULL == pwszDst)
		return NULL;
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszSrc, nLen, pwszDst, nSize);
	pwszDst[nSize] = 0;
	if (pwszDst[0] == 0xFEFF) // skip Oxfeff
		for (int i = 0; i < nSize; i++)
			pwszDst[i] = pwszDst[i + 1];
	wstring wcharString(pwszDst);
	delete pwszDst;
	return wcharString;
}
//png ����
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// �ṹ��ĵ�������Ա��ʾ�����͸���ȣ�0 ��ʾȫ͸����255 ��ʾ��͸����
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// ʹ�� Windows GDI ����ʵ�ְ�͸��λͼ
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

//͸��Բ�Ǿ��λ���
void solidroundrect_alpha(int left, int top, int right, int bottom, int ellipsewidth, int ellipseheight, int alpha, COLORREF color = WHITE)
{
	DRAW_TNS_INIT_GRAPHICS(right - left + 1, bottom - top + 1);
	{
		graphics.SolidRoundRect(0, 0, right - left, bottom - top, ellipsewidth, ellipseheight, true, color);
	}
	DRAW_TNS_RENDER_TO(left, top, hiex::GetWindowImage(), alpha);
}