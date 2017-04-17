#include "MyOglDrawDlg.h"
// MyOglDrawDlg.cpp : 
#include <iostream>
#include <string>

using namespace std;
bool net_exit = false;

IMPLEMENT_DYNAMIC(MyOglDrawDlg, CDialog)

MyOglDrawDlg::MyOglDrawDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OGLIMG, pParent)
{
	net_exit = false;
	//m_hIcon = LoadIcon((HINSTANCE)IDR_ICON, "");
}

void MyOglDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GLTAB, m_tab);
}

BEGIN_MESSAGE_MAP(MyOglDrawDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	//ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_SYSCOMMAND()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONDOWN()
	ON_MESSAGE(WM_MSG_OGL, GetOglCmd)
	ON_MESSAGE(WM_MSG_BOX, ShowMsgOnly)
	ON_MESSAGE(WM_MSG_SHOW, OnTaskShow)
	ON_MESSAGE(WM_MSG_TITL, SetDlgTitle)
	ON_COMMAND(WM_MSG_DEP, &MyOglDrawDlg::SetDeepDeg)
	ON_COMMAND(WM_MSG_BKG, &MyOglDrawDlg::SetDlgBkg)
	ON_COMMAND(WM_MSG_QUIT, &MyOglDrawDlg::PostNcDestroy)
	ON_WM_DROPFILES()
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_COMMAND(ID_SETBKG, &MyOglDrawDlg::OnSetbkg)
END_MESSAGE_MAP()

///*******************定义本文件内的全局变量*******************///
OGLKview Ogl;		//FillChart
MyOglDrawDlg* Mod;	//Notify
NOTIFYICONDATA icon;//OnTaskShow
					///**************************END**************************///

namespace MarkData
{
	int		idx = 0;
	int		ipt = 0;
	int		line = 0;
	int		failmsg = 0;
	char*	cot = NULL;
	char*	buff = NULL;
	char*	token = NULL;
	bool	isnext = false;
	char*	div_stock[3] = { NULL };
	char	code[64] = { NULL };
	char	exeFullPath[256] = { NULL };
	CString csDirPath;
	std::string tmp = " ";
	std::string sSystemFullPath;
	std::string sWritePath;
	std::ifstream Readfile;
	vector<char*> tradedata;
	OGLKview::Market ststock;
	WIN32_FIND_DATA fileData;
	OGLKview::Point Pter = { 0 }, Pt[4] = { 0 };
	OGLKview::Point pt_code = { 0.8f,1.189f };
}

using namespace MarkData;

char* MyOglDrawDlg::GetFirstData()
{
	//使用相对路径读取:
	//F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\Debug\data\SH600747.DAT
	GetModuleFileName(NULL, exeFullPath, sizeof(exeFullPath));
	//CString csDirPath((LPCSTR)exeFullPath);
	csDirPath.Format("%s", exeFullPath);
	csDirPath = csDirPath.Left(csDirPath.ReverseFind(_T('\\'))) + "\\data";
	std::string sSystemPath = csDirPath.GetBuffer(csDirPath.GetLength());
	csDirPath += "\\*.DAT";
	FindFirstFile(csDirPath.GetBuffer(), &fileData);
	sSystemFullPath = sSystemPath + (std::string)_T("\\") + fileData.cFileName;
	return (char*)(Ogl.file = sSystemFullPath.c_str());
}

int MyOglDrawDlg::GetMarkDatatoDraw()
{
	Readfile.open(Ogl.file, std::ios::in);
	if (Readfile.fail())
	{
		if (failmsg < 1)
			::PostMessage(m_hWnd, WM_MSG_OGL, 0, (LPARAM)Ogl.index.AllocBuffer("Reading failure!"));
		failmsg++;
		return false;
	}
	else {
		while (getline(Readfile, tmp))
		{
			buff = (char*)tmp.c_str();
			token = strtok_s(buff, "/,\t", &cot);
			while (token != NULL)
			{
				tradedata.push_back(token);
				token = strtok_s(NULL, "/,\t", &cot);
			}
			token = NULL;
			if ((tradedata.size() <= 7) && (tradedata.size()>0))
			{
				if (tradedata.size() < 3)
				{
					Ogl.coding = true;
					buff = tradedata[0];
					title.Format("%s", buff);
					SetWindowText(title);
					idx = 0;
					token = strtok_s(buff, " ", &cot);
					while (token != NULL)
					{
						div_stock[idx] = token;
						token = strtok_s(NULL, " ", &cot);
						idx++;
					}
					Ogl.SwitchViewport(0);
					sprintf(code, "%s(%s)", div_stock[1], div_stock[0]);
					Ogl.DrawKtext(code, pt_code, 20, { 1,1,0 }, "Terminal", false);
					sprintf(code, _T("%s(%s)<%s>"), div_stock[1], div_stock[0], div_stock[2]);
					pt_code = { -1.22f,pt_code.y };
					Ogl.DrawKtext(code, pt_code, 12, { 1,1,0 }, "宋体");
					pt_code = { 0.8f,1.189f };
					*div_stock = NULL;
				}
				tradedata.clear();
			}
			else if (tradedata.size() > 8)
			{
				Ogl.lastmarket = ststock;
				ststock.time.tm_year = atoi(tradedata[0]);
				ststock.time.tm_mon = atoi(tradedata[1]);
				ststock.time.tm_mday = atoi(tradedata[2]);
				ststock.open = (float)atof(tradedata[3]);
				ststock.high = (float)atof(tradedata[4]);
				ststock.low = (float)atof(tradedata[5]);
				ststock.close = (float)atof(tradedata[6]);
				ststock.amount = atoi(tradedata[7]);
				ststock.price = (float)atof(tradedata[8]);
				if (line < Ogl.tinkep.move + Ogl.dlginfo.cycle / Ogl.tinkep.ratio)
				{
					if (line > 0)
						if (ipt > 3)
						{
							ipt = 0;
							isnext = true;
						}
					if (line <= 3)
					{
						Ogl.dlginfo.line = 1;
					}
					else
						Ogl.dlginfo.line = line - 2;
					if (Ogl.tinkep.ratio == 0)
					{
						Pt[ipt].x += 6.5f;
						Pt[ipt].y /= 2;
					}
					Pt[ipt].x = Ogl.Pxtinker(Ogl.tinkep);
					Pt[ipt].y = (float)atof(tradedata[6]);
					ASSERT(_CrtCheckMemory());
					Ogl.dlginfo.line <= 1 ? Pter = Pt[0] : Pt[0];
					if (line >= Ogl.tinkep.move)
						Ogl.DrawKline(ststock, Ogl.tinkep);
					Ogl.DrawPoly(Pter, Pt[ipt], { 0.f,1.f,0.f });
					Pter = Pt[ipt];
					ipt++;
				}
				tradedata.clear();
			}
			else return false;
			line++;
		}
		Ogl.dlginfo.line = line = 0;
	}
	Readfile.close();
	return true;
}

BOOL MyOglDrawDlg::OnInitDialog()
{
	HWND m_hWnd = this->GetSafeHwnd();
	m_hDC = ::GetDC(m_hWnd/*m_tab.GetSafeHwnd()*/);
	CTPdev* m_ctp = new CTPdev();
	Ogl.SetWindowPixelFormat(m_hDC, m_hWnd);
	OnPaint();
	//SetCtrl();
	Ogl.AdjustDraw(W, H);
	GetFirstData();
#ifdef GLTEST
	test.LoadGLTexture();
	//test.Load__QDU(W, H);
#else
	SetTimer(1, 30, NULL);
#endif
	SetWindowPos(FromHandle(GetSafeHwnd()), 0, 0, GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN), SWP_NOZORDER);
	m_hAcc = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(ID_ACCLER));
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, m_ctp->SimpleClient, (void*)this, 0, NULL));
	delete m_ctp;
	return CDialog::OnInitDialog();
}

void MyOglDrawDlg::OnPaint()
{
	CRect Recto;
	CPaintDC dc(this);
	GetClientRect(&Recto);
	dc.SetViewportOrg(W = Recto.Width(), H = Recto.Height());
}

HCURSOR MyOglDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
#ifdef _UNICODE
void MyOglDrawDlg::OnTimer(UINT_PTR nIDEvent)
#else
void MyOglDrawDlg::OnTimer(UINT nIDEvent)
#endif
{
	switch (nIDEvent)
	{
	case 1://调用绘图函数
		DrawFunc(m_hDC);
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

NOTIFYICONDATA MyOglDrawDlg::GetNotiIcon(HWND O_hWnd)
{
	icon.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	icon.hWnd = O_hWnd;
	icon.uID = IDR_MAINFRAME;
	icon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
	icon.uCallbackMessage = WM_MSG_SHOW;
	icon.uTimeout = 3000;
	icon.dwInfoFlags = NIIF_INFO;
	_tcscpy(icon.szTip, "隐藏的对话框");
	_tcscpy(icon.szInfoTitle, "已最小化到托盘区");
	_tcscpy(icon.szInfo, "点击图标恢复，右键弹出菜单。");
	icon.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	return icon;
}

void MyOglDrawDlg::FloatDrift(char* text)
{
	CFont font;
	CWindowDC wdc(Mod->FromHandle(::GetDesktopWindow()));
	wdc.SetBkMode(BKMODE_LAST);
	wdc.SetTextColor(RGB(20, 20, 20));
	//wdc.BitBlt(0,0,
	wdc.LineTo(0, 0);
	font.CreateFont(20, 0, 0, 0,
		FW_MEDIUM,
		false/*斜体*/, false, false,
		OEM_CHARSET/*ANSI_CHARSET*/, OUT_CHARACTER_PRECIS,
		CLIP_STROKE_PRECIS, PROOF_QUALITY,
		FF_SCRIPT, " ");
	wdc.SelectObject(&font);
	wdc.TextOut(400, 400, text, strlen(text));
	::Sleep(300);
	if (text)
		text = NULL;
}

void _stdcall MyOglDrawDlg::DrawFunc(HDC m_hDC)
{
	Ogl.InitGraph();
	Ogl.DrawCoord(Ogl.dlginfo.mouX, Ogl.dlginfo.mouY);
#if !defined(GLTEST)
	Ogl.GetMarkDatatoDraw();
	depth->FillChart(Ogl.unfurl);
	depth->DrawItem(depth->item, false);
#else
	//test.Load__QDU(W, H);
	test.Model(Ogl.dlginfo.width, Ogl.dlginfo.height, dX, dY);
	test.House(Ogl.dlginfo.width, Ogl.dlginfo.height);
	//test.glTEST(true);
#endif
	Ogl.AdjustDraw(Ogl.dlginfo.width, Ogl.dlginfo.height, Ogl.dlginfo.bkg);
	SwapBuffers(m_hDC);
}

void MyOglDrawDlg::OnGetMinMaxInfo(MINMAXINFO * lpMMI)
{
}
// MyOglDrawDlg 

void MyOglDrawDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	Ogl.dlginfo.mouX = point.x;
	Ogl.dlginfo.mouY = point.y;
	if (point.x > 980 || point.y < 22)
		Ogl.dlginfo.drawstaff = 0;
	if ((Ogl.dlginfo.leftdown) && (point.x < Ogl.dlginfo.width) && (point.y < Ogl.dlginfo.height))
	{
		Ogl.dlginfo.drawstaff = 0;
		dX = point.x - oldX;
		dY = point.y - oldY;
		float Delta = sqrt(dX*dX + dY*dY);
		SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		if (Delta >= 6)
		{
			if (oldX < point.x)
			{
				Ogl.tinkep.move--;
			}
			else if (oldX > point.x)
				Ogl.tinkep.move++;
			else 1;
			oldX = (float)point.x;
			oldY = (float)point.y;
		}
	}
	else if ((point.x >= Ogl.dlginfo.width) || (point.y >= Ogl.dlginfo.height))
		Ogl.dlginfo.leftdown = false;
}

BOOL MyOglDrawDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta == WHEEL_DELTA)
		Ogl.tinkep.ratio *= 2;
	if (zDelta == -WHEEL_DELTA)
	{
		Ogl.tinkep.ratio /= 2;
		if (Ogl.tinkep.ratio < (1.0f / 32))
			Ogl.tinkep.ratio = (1.0f / 32);
	}
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void MyOglDrawDlg::OnSysCommand(UINT nID, LPARAM lparam)
{
	if (SC_MINIMIZE == nID)
	{
#ifndef _WIN64
		NOTIFYICONDATA noti = GetNotiIcon(m_hWnd);
		Shell_NotifyIcon(NIM_ADD, &noti);
		ShowWindow(SW_HIDE);
#endif
	}
	else
		CDialog::OnSysCommand(nID, lparam);
}

LRESULT MyOglDrawDlg::GetOglCmd(WPARAM wparam, LPARAM lparam)
{
	CString cmd;
	char* pMsg = (char*)lparam;
	cmd.Format(_T("%s"), pMsg);
	if (MessageBox(cmd) == IDOK)
		OnClose();
	if (pMsg)
		pMsg = NULL;
	return LRESULT();
}

LRESULT MyOglDrawDlg::ShowMsgOnly(WPARAM wparam, LPARAM lparam)
{
	CString cmd;
	char* pMsg = (char*)lparam;
	if (pMsg != NULL)
	{
		cmd.Format(_T("%s"), pMsg);
		AfxMessageBox(cmd);
		pMsg = NULL;
	}
	return LRESULT();
}

BOOL MyOglDrawDlg::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT message)
{
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	if (nHitTest != HTCAPTION)
	{
		if (Ogl.dlginfo.drawstaff)
		{
			if ((Ogl.dlginfo.mouY >= 20) && (Ogl.dlginfo.mouX < 950) && (Ogl.dlginfo.mouY < 380))
				SetCursor(NULL);
		}
		else if ((Ogl.dlginfo.mouY == 380) && (Ogl.dlginfo.mouX<950))
			SetCursor(LoadCursor(NULL, IDC_SIZENS));
	}
	return 0;
}

void MyOglDrawDlg::OnSize(UINT nType, int cx, int cy)
{
	Ogl.dlginfo.width = cx;
	Ogl.dlginfo.height = cy;
	CDialog::OnSize(nType, cx, cy);
}

LRESULT MyOglDrawDlg::OnTaskShow(WPARAM wparam, LPARAM lparam)
{
	CMenu cmenu;
	HMENU hmenu;
	CBitmap bitmap;
	if (lparam != IDR_MAINFRAME)
		switch (lparam)
		{
		case WM_RBUTTONUP:
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);
			cmenu.CreatePopupMenu();
			cmenu.AppendMenu(MF_STRING, /*ID_APP_EXIT*/WM_MSG_QUIT, _T("Exit"));
			SetForegroundWindow();
			bitmap.LoadBitmap(IDB_BITMAP);
			cmenu.SetMenuItemBitmaps(0, MF_BYPOSITION, &bitmap, &bitmap);
			cmenu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
			hmenu = cmenu.Detach();
			cmenu.DestroyMenu();
			delete lpoint;
		}
		break;
		case WM_LBUTTONDOWN:
			if (IsWindowVisible())
				ShowWindow(SW_HIDE);
			else
			{
				ShowWindow(SW_SHOW);
				Shell_NotifyIcon(NIM_DELETE, &icon);
			}
			break;
		default:
			break;
		}
	return LRESULT();
}

LRESULT CALLBACK MyOglDrawDlg::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY)
		OnDestroy();
	return CDialog::WindowProc(uMsg, wParam, lParam);
}

BOOL MyOglDrawDlg::PreTranslateMessage(tagMSG * pMsg)
{
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
	{
		if (m_hAcc && ::TranslateAccelerator(m_hWnd, m_hAcc, pMsg))
		{
			Dos.RedirectConsole();
			break;
		}
		else switch (pMsg->wParam)
		{
		case 'F':
		case 'f':
		{
			SetDeepDeg();
		}
		break;
		case 'M':
		{
			depth->item.time.hour = depth->item.time.min = 9;
			depth->item.pc_ = 99;
			depth->item.mode = 1;
		}
		break;
		default:
			break;
		}
	};
	case WM_DROPFILES:
		//OnDropFiles();
		break;
	};
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL MyOglDrawDlg::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
#ifdef _DEBUG
	if (nCode < 0 && nCode != (int)0x8000)
		TRACE1("Implementation Warning: control notification = $%X.\n", nCode);
#endif
	if (nCode == CN_COMMAND)
	{
		//for (UINT i = IDR_BKG + 1; i <= IDR_BKG + 5; i++)
		//	if (nID == i)
		//	{
		//		itoa(i - IDR_BKG, buffer, 10);
		//	}
		switch (nID)
		{
		case ID_BKG:
			SetDlgBkg();
			break;
		case ID_DEEP:
			SetDeepDeg();
			break;
		default:
			break;
		}
	}
	else
	{
		//if (_afxThreadState->m_hLockoutNotifyWindow == m_hWnd)
		//	return TRUE;        // locked out - ignore control notification
		// zero IDs for normal commands are not allowed
		if (nID == 0)
			return FALSE;
	}
	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void MyOglDrawDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	{
		HINSTANCE hInstance = (HINSTANCE)GetWindowLong(pWnd->m_hWnd, GWL_HINSTANCE);
		HMENU hMenuTray = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU));
		HMENU hPopupMenu = GetSubMenu(hMenuTray, 0);
		TrackPopupMenu(hPopupMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, 0, pWnd->m_hWnd, NULL);
	}
	{
		CMenu* p_mPop = new CMenu;
		p_mPop->LoadMenu(IDR_MENU);
		p_mPop->GetSubMenu(0);
		ClientToScreen(&point);
		p_mPop->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x - 8, point.y - 60, pWnd);
		p_mPop->Detach();
		delete p_mPop;
	}
}

void MyOglDrawDlg::SetDlgBkg()
{
	if (Ogl.dlginfo.bkg)
		Ogl.dlginfo.bkg = false;
	else
		Ogl.dlginfo.bkg = true;
}

void MyOglDrawDlg::SetDeepDeg()
{
	if (Ogl.unfurl)
		Ogl.unfurl = false;
	else
		Ogl.unfurl = true;
}

LRESULT MyOglDrawDlg::SetDlgTitle(WPARAM wparam, LPARAM lparam)
{
	SetWindowText((char*)lparam);
	return LRESULT();
}

void MyOglDrawDlg::OnClose()
{
	net_exit = true;
	KillTimer(1);
	//DestroyMenu(m_hTop);
	CWnd::OnClose();
	return PostNcDestroy();
}

void MyOglDrawDlg::PostNcDestroy()
{
	delete this;
}

void MyOglDrawDlg::SetCtrl()
{
#ifdef OWNCTL_H
	CMyMenu
#else
	CMenu
#endif
	 m_uTop;
	m_uTop.LoadMenu(IDR_TOP);// AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_TOP));
	ASSERT(this);
	CBrush m_brBkgd;
	m_brBkgd.DeleteObject();
	m_brBkgd.CreateSolidBrush(RGB(0, 0, 0));
	MENUINFO m_info = { 0 };
	m_info.cbSize = sizeof(MENUINFO);
	m_info.fMask = /*MIM_APPLYTOSUBMENUS |*/ MIM_BACKGROUND;
	//m_info.dwStyle = MNS_AUTODISMISS;
	m_info.hbrBack = m_brBkgd;
	try {
		if (IsMenu(m_uTop.m_hMenu))
			//::SetMenuInfo(m_uTop.m_hMenu, &m_info);
			Invalidate();
	}
	catch (...) { return; }
	for (int i = 0; i < m_uTop.GetMenuItemCount(); i++)
	{
		BOOL bModi = m_uTop.ModifyMenu(ID_BUTTON800 + i, MF_BYCOMMAND | MF_OWNERDRAW, ID_BUTTON800 + i);
		if (!bModi)
		{
			//TRACK("ModifyMenu fail!");
		}
	}
	SetMenu(/*GetSafeHwnd(),*/ &m_uTop);
	if (m_tool.Create(this) && m_tool.LoadToolBar(IDR_TOOL))
	{
		//m_tool.EnableDocking(CBRS_ALIGN_ANY);
		m_tool.ModifyStyle(0, TBSTYLE_FLAT);
		CRect rcItem;
		//RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, reposQuery, rcNew);	
		CPoint ptOffset(0, 0);
		CWnd* pwndChild = GetWindow(GW_CHILD);
		while (pwndChild)
		{
			pwndChild->GetWindowRect(rcItem);
			ScreenToClient(rcItem);
			rcItem.OffsetRect(ptOffset);
			pwndChild->MoveWindow(rcItem, FALSE);
			pwndChild = pwndChild->GetNextWindow();
		}
		RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	}
}

MyOglDrawDlg::~MyOglDrawDlg()
{
	Shell_NotifyIcon(NIM_DELETE, &icon);
}

void MyOglDrawDlg::OnDropFiles(HDROP hDropInfo)
{
	//char lpszFileName[MAX_PATH + 1] = { 0 };
	//char g____lpstrFilename[2048];
	//memset(g____lpstrFilename, 0, 512 * sizeof(TCHAR));
	if (DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0) == 1)
	{
		//DragQueryFile(hDropInfo, 0, g____lpstrFilename, 512);
		//myopenfile( g____lpstrFilename, 1 );
		DragQueryFile(hDropInfo, 0, (LPTSTR)Ogl.file, _MAX_PATH);
		//m_edit.SetWindowText(g____lpstrFilename);
		//::DragFinish(hDropInfo); //释放内存 i="0;" delete []lpszFileName; //
	};
	CDialog::OnDropFiles(hDropInfo);
}

int MyOglDrawDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	DragAcceptFiles(TRUE);
	return 0;
}

auto MyOglDrawDlg::GetPrivMem()
{
	auto f = *((bool*)&Ogl);
	if (!f)
		MessageBox(_T("私有成员"));
	return f;
}

HBRUSH MyOglDrawDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CreateSolidBrush(RGB(0, 0, 0));
	if (pWnd->GetDlgCtrlID() == IDR_TOP)
	{
		pDC->SetTextColor(RGB(20, 20, 20));
		pDC->SetBkMode(TRANSPARENT);
	}
	return hbr;
}

void MyOglDrawDlg::CallShellScript(CString Path, CString fbat, CString param)
{
	USES_CONVERSION;
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = fbat;
	ShExecInfo.lpParameters = param;
	ShExecInfo.lpDirectory = Path;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
}

void MyOglDrawDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	Ogl.dlginfo.drawstaff++;
	if (Ogl.dlginfo.drawstaff == 2)
		Ogl.dlginfo.drawstaff = 0;
	Ogl.dlginfo.leftdown = true;
	return CDialog::OnLButtonDown(nFlags, point);
}

void MyOglDrawDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
}

void MyOglDrawDlg::OnRButtonDown(UINT nFlags, CPoint point)
{

}

void MyOglDrawDlg::OnSetbkg()
{
	SetDlgBkg();
}
