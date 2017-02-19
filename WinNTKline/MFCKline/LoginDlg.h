#pragma once
#include "stdafx.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "afxmt.h"
#include "afxdialogex.h"
#include "Index/Indexes.inl"
// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	HICON m_hIcon;
	DECLARE_MESSAGE_MAP()
private:
	CHAR m_IP[16];
	char m_acnt[32];
	char m_pswd[32];
	Indexes netmsg; 
	CFont m_font;
	CEdit m_logport;
	CEdit m_editPsw;
	CStatic m_regist;
	CComboBox m_combo;
	CIPAddressCtrl m_ipCtrl;
public:
	afx_msg void SetCombo();
	afx_msg void GetiniIPs(char* IPs[]);
	afx_msg void OnCbnSelchangeIp();
	afx_msg void OnBnClickedDft80();
	afx_msg void OnStnClickedRegi();
	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void fill_edit(CEdit& edit, const char tmp[], int hexlen);
};
