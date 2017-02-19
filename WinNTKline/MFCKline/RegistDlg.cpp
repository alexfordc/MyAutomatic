// Regist.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCKline.h"
#include "RegistDlg.h"
#include "HOOK/injectDLL.h"


// CRegist 对话框

IMPLEMENT_DYNAMIC(CRegistDlg, CDialogEx)

CRegistDlg::CRegistDlg(char* ip, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BROWSER, pParent)
	, m_browser()
{
	if (ip == nullptr)
		return;
	memcpy(&this->ip, ip, sizeof(ip) * sizeof(char*) + 1);
}

CRegistDlg::~CRegistDlg()
{
}

CRegistDlg::CRegistDlg()
{
}

void CRegistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRegistDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_STN_DBLCLK(ID_STATIC, &CRegistDlg::OnStnDblclickCursor)
END_MESSAGE_MAP()

int ShowBox(HWND hWndParent)
{
	HMODULE g_hmodu = LoadLibrary(_T("HOOK/hook.dll"));
	typedef int(*ADDROC) ();
	ADDROC ExitWindow = (ADDROC)GetProcAddress(g_hmodu, "ExitWindow");

	if (!ExitWindow)
	{
		MessageBox(hWndParent, _T("获取函数地址失败。"), _T("Error"), MB_OK);
		return -1;
	}
	ExitWindow();
	return 0;
}

BOOL CRegistDlg::OnInitDialog()
{
	if(MessageBox("即将弹出的对话框，请点击“是”。", "提示"))
		Init();	
	//ShowBox(this->m_hWnd);
	return \
		CDialogEx::OnInitDialog();
}

void CRegistDlg::Init()
{
	CRect cet;
	CFont font;
	CString url;
	int reg_port = 443;
	COleVariant noAg;
	GetClientRect(&cet);
	int ect = cet.right / 3;
	m_hint.Create("鼠标双击可退出本对话框", WS_VISIBLE|SS_NOTIFY, \
	{ ect, cet.bottom - 40, ect + 170, cet.bottom - 20}, this, ID_STATIC);
	if (!m_browser.Create(NULL, NULL, WS_VISIBLE, \
		cet, this, ID_BROSR))return;
	if (this->ip[0] == '\0')return;
	url.Format("https://%s:%d/Regist", this->ip, reg_port);
	m_browser.Navigate(url, &noAg, &noAg, &noAg, &noAg);
}

void CRegistDlg::OnStnDblclickCursor()
{
	OnOK();
}
