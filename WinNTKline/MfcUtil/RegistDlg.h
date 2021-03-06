#pragma once

//#include "html/CWebBrowser2.h"
#include "html/MfcHtmlView.h"
#include "html/cefWebKit.h"
#include "afxdialogex.h"

// CRegist 对话框

class CRegistDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CRegistDlg)

public:
    CRegistDlg(char* IP, CWnd* pParent = NULL);   // 标准构造函数
    virtual BOOL OnInitDialog();
    virtual ~CRegistDlg();
    CRegistDlg();

    // 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_BROWSER };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
public:
    CMfcHtmlView * m_HTMLPage = NULL;
    //CWebBrowser2 m_browser;
    char m_IP[32];
    CStatic m_hint;
    LOGFONT m_lf;
    CFont m_font;
    CToolTipCtrl m_Mytip;
    CefRefPtr<CEFWebKit> m_cWebClient;
private:
    void InitBrs();
    void SetTipLatent();
    void SetCefWeb(RECT rect, CString& url);
    afx_msg BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
    afx_msg void OnStnDblclickCursor();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
};
