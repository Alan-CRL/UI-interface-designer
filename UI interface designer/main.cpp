#include "main.h"

wstring bkdraw_state;
map<pair<wstring, int>, int> bkdraw_state_each;
void bkdraw()
{
	while (1)
	{
		Sleep(10);
		if (bkdraw_state == L"尺寸设定")
		{
			BeginDraw;
			cleardevice();

			wcscpy(font.lfFaceName, L"DOUYU Font");
			font.lfHeight = 40;
			settextstyle(&font);
			settextcolor(RGB(0, 0, 0));
			outtextxy(325 - textwidth(L"请设定新建场景的尺寸") / 2, 30, L"请设定新建场景的尺寸");

			wcscpy(font.lfFaceName, L"HarmonyOS Sans SC");
			font.lfHeight = 20;
			settextstyle(&font);
			outtextxy(325 - textwidth(L"如 640 × 480") / 2, 80, L"如 640 × 480");

			wcscpy(font.lfFaceName, L"HarmonyOS Sans SC");
			font.lfHeight = 30;
			settextstyle(&font);
			outtextxy(325 - textwidth(L"Tips：输入宽高的单位为像素(px)") / 2, 310, L"Tips：输入宽高的单位为像素(px)");

			wcscpy(font.lfFaceName, L"HarmonyOS Sans SC");
			font.lfHeight = 25;
			settextstyle(&font);
			outtextxy(110, 155, L"场景宽度(x)");
			outtextxy(360, 155, L"场景高度(y)");

			setfillcolor(bkdraw_state_each[make_pair(L"尺寸设定", 2)] == 0 ? RGB(0, 0, 0) : RGB(255, 0, 0));
			solidrectangle(228, 148, 306, 186);
			setfillcolor(bkdraw_state_each[make_pair(L"尺寸设定", 3)] == 0 ? RGB(0, 0, 0) : RGB(255, 0, 0));
			solidrectangle(478, 148, 556, 186);

			solidroundrect_alpha(400, 250, 600, 290, 15, 15, 255, bkdraw_state_each[make_pair(L"尺寸设定", 1)] == 0 ? RGB(32, 148, 243) : (bkdraw_state_each[make_pair(L"尺寸设定", 1)] == 1 ? RGB(12, 128, 223) : RGB(0, 108, 203)));
			settextcolor(RGB(255, 255, 255));
			{
				words_rect.left = 400;
				words_rect.top = 250 + 4;
				words_rect.right = 600;
				words_rect.bottom = 290;
			}
			drawtext(L"确定", &words_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			if (bkdraw_state_each[make_pair(L"尺寸设定", 4)] == 1)
			{
				font.lfHeight = 25;
				settextstyle(&font);
				settextcolor(RGB(255, 0, 0));
				wstring tip = L"场景宽度应在范围 1 - " + to_wstring(GetSystemMetrics(SM_CXSCREEN) - 220) + L" 内";
				{
					words_rect.left = 0;
					words_rect.top = 200;
					words_rect.right = 650;
					words_rect.bottom = 230;
				}
				drawtext(tip.c_str(), &words_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			else if (bkdraw_state_each[make_pair(L"尺寸设定", 4)] == 2)
			{
				font.lfHeight = 25;
				settextstyle(&font);
				settextcolor(RGB(255, 0, 0));
				wstring tip = L"场景高度应在范围 1 - " + to_wstring(GetSystemMetrics(SM_CYSCREEN) - 120) + L" 内";
				{
					words_rect.left = 0;
					words_rect.top = 200;
					words_rect.right = 650;
					words_rect.bottom = 230;
				}
				drawtext(tip.c_str(), &words_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}

			EndDraw;
		}
	}
}
void model(wstring s)
{
	if (s == L"尺寸设定")
	{
		bkdraw_state = s;

		int state;

		hiex::SysEdit edit_width;
		edit_width.PreSetStyle({ false,true,false,false,false,false });    // 预设样式可以不用创建结构体，直接简写成这样
		edit_width.Create(GetHWnd(), 230, 150, 75, 35, L"");
		edit_width.SetFont(30, 0, L"HarmonyOS Sans SC");

		hiex::SysEdit edit_hight;
		edit_hight.PreSetStyle({ false,true,false,false,false,false });    // 预设样式可以不用创建结构体，直接简写成这样
		edit_hight.Create(GetHWnd(), 480, 150, 75, 35, L"");
		edit_hight.SetFont(30, 0, L"HarmonyOS Sans SC");

		ExMessage m;
		while (1)
		{
			getmessage(&m, EM_MOUSE);

			//确定:1
			if (m.x >= 400 && m.y >= 250 && m.x <= 600 && m.y <= 290)
			{
				state = 1;
				int ux = 400, uy = 250, dx = 600, dy = 290, r = 15;

				bkdraw_state_each[make_pair(L"尺寸设定", state)] = 1;

				if (m.lbutton)
				{
					bkdraw_state_each[make_pair(L"尺寸设定", state)] = 2;

					bool willin = false;

					while (1)
					{
						m = getmessage(EM_MOUSE);
						if (m.x >= ux && m.y >= uy && m.x <= dx && m.y <= dy)
						{
							bkdraw_state_each[make_pair(L"尺寸设定", state)] = 2;

							if (!m.lbutton)
							{
								bkdraw_state_each[make_pair(L"尺寸设定", state)] = 0;

								willin = true;
								break;
							}
						}
						else
						{
							bkdraw_state_each[make_pair(L"尺寸设定", state)] = 0;

							if (!m.lbutton) break;
						}
					}

					if (willin)
					{
						//内容部分

						bkdraw_state_each[make_pair(L"尺寸设定", 2)] = bkdraw_state_each[make_pair(L"尺寸设定", 3)] = bkdraw_state_each[make_pair(L"尺寸设定", 4)] = 0;

						//框1 验证
						if (edit_width.GetText() == L"") bkdraw_state_each[make_pair(L"尺寸设定", 2)] = 1;
						else if (to_wstring(_wtoi(edit_width.GetText().c_str())) != edit_width.GetText()) bkdraw_state_each[make_pair(L"尺寸设定", 2)] = 1;
						else if (_wtoi(edit_width.GetText().c_str()) <= 0 || _wtoi(edit_width.GetText().c_str()) > GetSystemMetrics(SM_CXSCREEN) - 220) bkdraw_state_each[make_pair(L"尺寸设定", 2)] = 1, bkdraw_state_each[make_pair(L"尺寸设定", 4)] = 1;

						//框2 验证
						if (edit_hight.GetText() == L"") bkdraw_state_each[make_pair(L"尺寸设定", 3)] = 1;
						else if (to_wstring(_wtoi(edit_hight.GetText().c_str())) != edit_hight.GetText()) bkdraw_state_each[make_pair(L"尺寸设定", 3)] = 1;
						else if ((_wtoi(edit_hight.GetText().c_str()) <= 0 || _wtoi(edit_hight.GetText().c_str()) > GetSystemMetrics(SM_CYSCREEN) - 120) && !bkdraw_state_each[make_pair(L"尺寸设定", 4)]) bkdraw_state_each[make_pair(L"尺寸设定", 3)] = 1, bkdraw_state_each[make_pair(L"尺寸设定", 4)] = 2;

						if (bkdraw_state_each[make_pair(L"尺寸设定", 2)] == 0 && bkdraw_state_each[make_pair(L"尺寸设定", 3)] == 0 && bkdraw_state_each[make_pair(L"尺寸设定", 4)] == 0)
						{
							windows.width = _wtoi(edit_width.GetText().c_str()) + 220;
							windows.height = _wtoi(edit_hight.GetText().c_str()) + 120;
							edit_width.Remove();
							edit_hight.Remove();

							return;
						}
					}
				}
			}
			//框1:2
			//框2:3

			else
			{
				if (state == 1) bkdraw_state_each[make_pair(L"尺寸设定", state)] = 0;
			}
		}
	}
}

int main()
{
	//程序初始化部分
	{
		//全局路径预处理
		{
			global_path = _pgmptr;
			for (int i = int(global_path.length() - 1); i >= 0; i--)
			{
				if (global_path[i] == '\\')
				{
					global_path = global_path.substr(0, i + 1);
					break;
				}
			}
		}
		//多线程并发
		{
			thread bkdraw_thread(bkdraw);
			bkdraw_thread.detach();

			//ModifyRegedit(true);
		}
		//媒体资源读取
		{
			loadimage(&Logo, L"PNG", MAKEINTRESOURCE(IDB_PNG1));
		}

		//程序初始化
		{
			//DPI 初始化
			{
				HINSTANCE hUser32 = LoadLibrary(L"User32.dll");
				if (hUser32)
				{
					typedef BOOL(WINAPI* LPSetProcessDPIAware)(void);
					LPSetProcessDPIAware pSetProcessDPIAware = (LPSetProcessDPIAware)GetProcAddress(hUser32, "SetProcessDPIAware");
					if (pSetProcessDPIAware)
					{
						pSetProcessDPIAware();
					}
					FreeLibrary(hUser32);
				}
			}

			initgraph(650, 350);
			SetWindowTextW(GetHWnd(), L"EasyX UI设计器");

			setbkmode(TRANSPARENT);
			setbkcolor(RGB(240, 240, 240));

			BeginDraw;
			cleardevice();
			EndDraw;

			Sleep(100);

			RECT rcClient, rcWind;
			GetClientRect(GetHWnd(), &rcClient);
			GetWindowRect(GetHWnd(), &rcWind);
			windows.frame_hight = (rcWind.bottom - rcWind.top) - (rcClient.bottom - rcClient.top);
			windows.frame_width = (rcWind.right - rcWind.left) - (rcClient.right - rcClient.left);

			DisableResizing(GetHWnd(), true);//禁止窗口拉伸
			SetWindowPos(GetHWnd(), NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_DRAWFRAME);//窗口置顶
			SetWindowPos(GetHWnd(), NULL, windows.x = GetSystemMetrics(SM_CXSCREEN) / 2 - 325 - windows.frame_width / 2, windows.y = GetSystemMetrics(SM_CYSCREEN) / 2 - 175 - windows.frame_hight / 2, 0, 0, SWP_NOSIZE);

			setWindowTransparent(GetHWnd(), true, windows.translucent = 245);

			BeginDraw;
			putimage(0, 0, &Logo);
			EndDraw;
			Sleep(3000);

			hiex::Canvas canvas(650, 350);
			canvas.SolidRectangle(0, 0, 650, 350, true, 0xe4e7ec);

			for (int i = 0; i <= 255; i += 5)
			{
				BeginDraw;

				putimage(0, 0, &Logo);
				canvas.RenderTo(0, 0, GetWorkingImage(), { 0 }, i, false, false);

				EndDraw;

				Sleep(5);
			}
		}

		//字体初始化部分
		{
			gettextstyle(&font);
			font.lfOutPrecision = OUT_TT_ONLY_PRECIS;
			font.lfQuality = ANTIALIASED_QUALITY | PROOF_QUALITY;

			AddFontResourceEx((convert_to_wstring(global_path) + L"ttf\\HarmonyOS_Sans_SC_Regular.ttf").c_str(), FR_PRIVATE, NULL);
			AddFontResourceEx((convert_to_wstring(global_path) + L"ttf\\Douyu_Font.otf").c_str(), FR_PRIVATE, NULL);
			AddFontResourceEx((convert_to_wstring(global_path) + L"ttf\\SmileySans-Oblique.ttf").c_str(), FR_PRIVATE, NULL);

			//wcscpy(font.lfFaceName, L"HarmonyOS Sans SC");
			//wcscpy(font.lfFaceName, L"DOUYU Font");
			//wcscpy(font.lfFaceName, L"得意黑");
		}
	}

	SetWindowPos(GetHWnd(), NULL, windows.x = GetSystemMetrics(SM_CXSCREEN) / 2 - 325 - windows.frame_width / 2, windows.y = GetSystemMetrics(SM_CYSCREEN) / 2 - 175 - windows.frame_hight / 2, (windows.width = 650) + windows.frame_width, (windows.height = 350) + windows.frame_hight, NULL);
	model(L"尺寸设定");

	SetWindowPos(GetHWnd(), NULL, windows.x = GetSystemMetrics(SM_CXSCREEN) / 2 - windows.width / 2 - windows.frame_width / 2, windows.y = GetSystemMetrics(SM_CYSCREEN) / 2 - windows.height / 2 - windows.frame_hight / 2, windows.width + windows.frame_width, windows.height + windows.frame_hight, NULL);
	model(L"主界面");

	while (1);
}