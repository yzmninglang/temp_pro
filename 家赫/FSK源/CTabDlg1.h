#pragma once

// CTabDlg1 对话框

class CTabDlg1 : public CDialogEx
{
	DECLARE_DYNAMIC(CTabDlg1)

public:
	CTabDlg1(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTabDlg1();
	//friend class SigTranmit;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedButtonLpf();
//	afx_msg void OnEnChangeId();
	afx_msg void OnEnChangeFs();
//	afx_msg void OnEnChangeFc();
	afx_msg void OnEnChangeSnr();
	int my_ID;
	int nFs;
//	int nFc;
	float snr;
	float nLpfc;
	float nBpfc1;
	float nBpfc2;
	float nBpfc3;
	float nBpfc4;
	afx_msg void OnEnChangeFc1();
	afx_msg void OnEnChangeFc2();
	int Fc1;
	int Fc2;
	afx_msg void OnEnChangeLpf();
	afx_msg void OnEnChangeBpf1();
	afx_msg void OnEnChangeBpf2();
	afx_msg void OnEnChangeBpf3();
	afx_msg void OnEnChangeBpf4();
//	afx_msg void OnBnClickedButtonBpf1();
	afx_msg void OnBnClickedButtonBpf2();
	afx_msg void OnBnClickedButtonBpf1();
	afx_msg void OnEnChangemyid();
	// 滤波器设计方法初始化
	CString nDesign;
	CComboBox my_Winfunc;
	afx_msg void OnCbnSelchangeDesign();
	afx_msg void OnCbnSelchangeWinfunc();
};
