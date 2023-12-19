
// FSKDlg.h: 头文件
//
#include "CTabDlg1.h"
#include "CTabDlg2.h"
#include "SigTranmit.h"

#if !defined(AFX_FSKDLG_H)
#define AFX_FSKDLG_H

#if _MSC_VER > 1600
#pragma once
#endif // _MSC_VER > 1600


// CFSKDlg 对话框
class CFSKDlg : public CDialogEx
{
// 构造
public:
	CFSKDlg(CWnd* pParent = nullptr);	// 标准构造函数	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FSK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabDlg1 CTabDlg1;
	CTabDlg2 CTabDlg2;
	CDialog* pDialog[2];
	int m_CurSelTab;
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	CTabCtrl r_tab1;
	afx_msg void OnStnClickedT();
	afx_msg void OnStnClickedF();
	void Draw_graph(float S[], float Fre[]);
	void Draw_graph_filter(float S[], float Fre[]);
	float findmax(float x[], int m);
};
#endif 