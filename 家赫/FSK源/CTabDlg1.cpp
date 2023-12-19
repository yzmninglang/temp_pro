// CTabDlg1.cpp: 实现文件
//
#include "SigTranmit.h"
#include "pch.h"
#include "FSK.h"
#include "CTabDlg1.h"
#include "afxdialogex.h"
#include "FSKDlg.h"


extern SigTranmit Signal;

// CTabDlg1 对话框

IMPLEMENT_DYNAMIC(CTabDlg1, CDialogEx)

CTabDlg1::CTabDlg1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, my_ID(Signal.GetmyID())
	, nFs(Signal.GetFs())
	//, nFc(0)
	, snr(Signal.GetmyIntensity())
	, nLpfc(Signal.GetnLpfc())
	, nBpfc1(Signal.GetnBpfc1())
	, nBpfc2(Signal.GetnBpfc2())
	, nBpfc3(Signal.GetnBpfc3())
	, nBpfc4(Signal.GetnBpfc4())
	, Fc1(Signal.GetFc1())
	, Fc2(Signal.GetFc2())
	, nDesign(_T(""))
{

}

CTabDlg1::~CTabDlg1()
{
}

void CTabDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_ID, my_ID);
	DDX_Text(pDX, IDC_Fs, nFs);
	//DDX_Text(pDX, IDC_Fc, nFc);
	//DDX_Text(pDX, IDC_SNR, snr);
	DDX_Text(pDX, IDC_LPF, nLpfc);
	DDX_Text(pDX, IDC_BPF1, nBpfc1);
	DDX_Text(pDX, IDC_BPF2, nBpfc2);
	//DDX_Text(pDX, IDC_BPF3, nBpfc3);
	//DDX_Text(pDX, IDC_BPF4, nBpfc4);
	DDX_Text(pDX, IDC_Fc1, Fc1);
	//DDX_Text(pDX, IDC_Fc2, Fc2);
	DDX_Text(pDX, IDC_myID, my_ID);
	//DDX_CBString(pDX, IDC_Design, nDesign);
	Signal.SetDesign(FILTER_WIN);
	//窗
	Signal.SetWin(WIN_JXC);
	//DDX_Control(pDX, IDC_WinFunc, my_Winfunc);
}


BEGIN_MESSAGE_MAP(CTabDlg1, CDialogEx)
	//ON_EN_CHANGE(IDC_EDIT3, &CTabDlg1::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON_LPF, &CTabDlg1::OnBnClickedButtonLpf)
//	ON_BN_CLICKED(IDC_BUTTON_BPF, &CTabDlg1::OnBnClickedButtonBpf)
//	ON_EN_CHANGE(IDC_ID, &CTabDlg1::OnEnChangeId)
	ON_EN_CHANGE(IDC_Fs, &CTabDlg1::OnEnChangeFs)
	//ON_EN_CHANGE(IDC_Fc, &CTabDlg1::OnEnChangeFc)
	ON_EN_CHANGE(IDC_SNR, &CTabDlg1::OnEnChangeSnr)
	ON_EN_CHANGE(IDC_Fc1, &CTabDlg1::OnEnChangeFc1)
	ON_EN_CHANGE(IDC_Fc2, &CTabDlg1::OnEnChangeFc2)
	ON_EN_CHANGE(IDC_LPF, &CTabDlg1::OnEnChangeLpf)
	ON_EN_CHANGE(IDC_BPF1, &CTabDlg1::OnEnChangeBpf1)
	ON_EN_CHANGE(IDC_BPF2, &CTabDlg1::OnEnChangeBpf2)
	ON_EN_CHANGE(IDC_BPF3, &CTabDlg1::OnEnChangeBpf3)
	ON_EN_CHANGE(IDC_BPF4, &CTabDlg1::OnEnChangeBpf4)
//	ON_BN_CLICKED(IDC_BUTTON_BPF1, &CTabDlg1::OnBnClickedButtonBpf1)
	ON_BN_CLICKED(IDC_BUTTON_BPF2, &CTabDlg1::OnBnClickedButtonBpf2)
	ON_BN_CLICKED(IDC_BUTTON_BPF1, &CTabDlg1::OnBnClickedButtonBpf1)
	ON_EN_CHANGE(IDC_myID, &CTabDlg1::OnEnChangemyid)
	ON_CBN_SELCHANGE(IDC_Design, &CTabDlg1::OnCbnSelchangeDesign)
	ON_CBN_SELCHANGE(IDC_WinFunc, &CTabDlg1::OnCbnSelchangeWinfunc)
END_MESSAGE_MAP()


// CTabDlg1 消息处理程序


void CTabDlg1::OnBnClickedButtonLpf()
{
	// TODO: 在此添加控件通知处理程序代码
	Signal.Lpf();
	Signal.Dft(Signal.GetHl(),N);
	CFSKDlg* parent = (CFSKDlg*)GetParent()->GetParent();//CSensorSysDlg是主对话框对应的类
	parent->Draw_graph_filter(Signal.GetHl(), Signal.GetA());
}


void CTabDlg1::OnEnChangeFs()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);
	Signal.SetFs(nFs);
	// TODO:  在此添加控件通知处理程序代码
}


//void CTabDlg1::OnEnChangeFc()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//	UpdateData(TRUE);
//	// TODO:  在此添加控件通知处理程序代码
//}


void CTabDlg1::OnEnChangeSnr()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);
	Signal.SetIntensity(snr);
	// TODO:  在此添加控件通知处理程序代码
}


void CTabDlg1::OnEnChangeFc1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);
	Signal.SetFc1(Fc1);
	// TODO:  在此添加控件通知处理程序代码
}


void CTabDlg1::OnEnChangeFc2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);
	Signal.SetFc2(Fc2);
	// TODO:  在此添加控件通知处理程序代码
}


void CTabDlg1::OnEnChangeLpf()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);
	Signal.SetLFc(nLpfc);
	// TODO:  在此添加控件通知处理程序代码
}


void CTabDlg1::OnEnChangeBpf1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);
	Signal.SetBFc1(nBpfc1);
	// TODO:  在此添加控件通知处理程序代码
}


void CTabDlg1::OnEnChangeBpf2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);
	Signal.SetBFc2(nBpfc2);
	// TODO:  在此添加控件通知处理程序代码
}


void CTabDlg1::OnEnChangeBpf3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);
	Signal.SetBFc3(nBpfc3);
	// TODO:  在此添加控件通知处理程序代码
}


void CTabDlg1::OnEnChangeBpf4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);
	Signal.SetBFc4(nBpfc4);
	// TODO:  在此添加控件通知处理程序代码
}


void CTabDlg1::OnBnClickedButtonBpf1()
{
	// TODO: 在此添加控件通知处理程序代码
	Signal.Bpf(1);
	Signal.Dft(Signal.GetH2(), N);
	CFSKDlg* parent = (CFSKDlg*)GetParent()->GetParent();//CSensorSysDlg是主对话框对应的类
	parent->Draw_graph_filter(Signal.GetH2(), Signal.GetA());
}


void CTabDlg1::OnBnClickedButtonBpf2()
{
	// TODO: 在此添加控件通知处理程序代码
	Signal.Bpf(2);
	Signal.Dft(Signal.GetH2(), N);
	CFSKDlg* parent = (CFSKDlg*)GetParent()->GetParent();//CSensorSysDlg是主对话框对应的类
	parent->Draw_graph_filter(Signal.GetH2(), Signal.GetA());
}





void CTabDlg1::OnEnChangemyid()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);
	Signal.SetID(my_ID);
	// TODO:  在此添加控件通知处理程序代码
}


void CTabDlg1::OnCbnSelchangeDesign()
{
	// TODO: 在此添加控件通知处理程序代码
	int iPos = ((CComboBox*)GetDlgItem(IDC_Design))->GetCurSel();
	if (iPos == 1)
		my_Winfunc.EnableWindow(FALSE);
	else
		my_Winfunc.EnableWindow(TRUE);
	switch (iPos)
	{
		case 0:Signal.SetDesign(FILTER_WIN); break;
		case 1:Signal.SetDesign(FILTER_SAMPLE); break;
	}
}


void CTabDlg1::OnCbnSelchangeWinfunc()
{
	// TODO: 在此添加控件通知处理程序代码
	int iPos = ((CComboBox*)GetDlgItem(IDC_WinFunc))->GetCurSel();
	switch (iPos)
	{
	case 0:Signal.SetWin(WIN_JXC); break;//JXC
	case 1:Signal.SetWin(WIN_HNC); break;//HNC
	case 2:Signal.SetWin(WIN_HMC); break;//HMC
	case 3:Signal.SetWin(WIN_BLKMC); break;//BLKMC
	}
}
