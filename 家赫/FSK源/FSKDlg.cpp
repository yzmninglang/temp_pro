
// FSKDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "FSK.h"
#include "FSKDlg.h"
#include "afxdialogex.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
SigTranmit Signal;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFSKDlg 对话框



CFSKDlg::CFSKDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FSK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFSKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, r_tab1);
}

BEGIN_MESSAGE_MAP(CFSKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CFSKDlg::OnTcnSelchangeTab1)
	ON_STN_CLICKED(IDC_T, &CFSKDlg::OnStnClickedT)
	ON_STN_CLICKED(IDC_F, &CFSKDlg::OnStnClickedF)
END_MESSAGE_MAP()


// CFSKDlg 消息处理程序

BOOL CFSKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	r_tab1.InsertItem(0, _T("参数设置")); //修改分页名称	
	r_tab1.InsertItem(1, _T("数字通信系统模拟仿真"));
	//******将子窗口嵌到主窗口中，并且修改下大小******//
	CTabDlg1.Create(IDD_DIALOG1, &r_tab1);
	CTabDlg2.Create(IDD_DIALOG2, &r_tab1);

	CRect rc;
	r_tab1.GetClientRect(&rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	CTabDlg1.MoveWindow(&rc);
	CTabDlg2.MoveWindow(&rc);

	//把对话框对象指针保存起来
	pDialog[0] = &CTabDlg1;
	pDialog[1] = &CTabDlg2;
	//显示初始页面
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	//保存当前选择
	m_CurSelTab = 0;

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFSKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFSKDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFSKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFSKDlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//把当前的页面隐藏起来
	pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	//得到新的页面索引
	m_CurSelTab = r_tab1.GetCurSel();
	//把新的页面显示出来
	pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);
	*pResult = 0;
}


void CFSKDlg::OnStnClickedT()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CFSKDlg::OnStnClickedF()
{
	// TODO: 在此添加控件通知处理程序代码
}

float CFSKDlg::findmax(float x[], int m)
{
	int i;
	float t = x[0];
	for (i = 0; i < m; i++)
	{
		if (x[i] >= t)
			t = x[i];
	}
	return t;
}

void CFSKDlg::Draw_graph(float S[], float Fre[])
{
	CWnd* pWnd = GetDlgItem(IDC_T);
	CDC* pDC = pWnd->GetDC();
	CRect rect;
	pWnd->GetClientRect(rect);
	int W = rect.Width(); //画图区域宽度
	int H = rect.Height(); //画图区域高度
	//设置背景色
	RedrawWindow();
	CBrush newbrush;
	newbrush.CreateSolidBrush(RGB(255, 255, 255));
	pDC->Rectangle(rect);
	//pDC->FillRect(rect,&newbrush);
	int StepX = int((W - 1) / (16 * M));
	double maxt = findmax(S, (16 * M));
	double StepY = (H / 2 - 10) / (fabs(maxt));
	//确定画图起始位置
	int ox = int((W - (16 * M) * StepX) / 2);
	int oyt = rect.bottom - int(H / 2);
	//画坐标
	CPen CoordinatePen, pen;
	CoordinatePen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	pDC->SelectObject(&CoordinatePen);
	pDC->MoveTo(rect.left, oyt);
	pDC->LineTo(rect.left + W, oyt);

	CPen pen2;
	pen2.CreatePen(PS_DOT, 1, RGB(150, 150, 150));
	pDC->SelectObject(&pen2);
	for (int i1 = 0; i1 < H; i1 += 20)
	{
		pDC->MoveTo(0, i1);
		pDC->LineTo(W, i1);

	}
	for (int j1 = 0; j1 < W; j1 += 20)
	{

		pDC->MoveTo(j1, 0);
		pDC->LineTo(j1, H);
	}
	pDC->SelectObject(&pen);
	pDC->MoveTo(ox, oyt);
	for (int i = 0; i < (16 * M); i++)
	{
		pDC->LineTo(ox + i * StepX, int(oyt - StepY * S[i]));
	}
	//频谱图
	CWnd* pWnd1 = GetDlgItem(IDC_F);
	CDC* pDC1 = pWnd1->GetDC();
	CRect rect1;
	pWnd1->GetClientRect(rect1);
	int W1 = rect1.Width(); //画图区域宽度
	int H1 = rect1.Height(); //画图区域高度
	CBrush newbrush1;
	newbrush1.CreateSolidBrush(RGB(255, 255, 255));
	pDC1->Rectangle(rect1);
	//坐标定位
	int StepX1 = int(2 * (W1 - 1) / (16 * M));
	float maxt1 = findmax(Fre, int((16 * M) / 2));
	float StepY1 = (4 * H1 / 5 - 10) / ((float)fabs(maxt1));
	//确定画图起始位置
	int oxf = int((W1 - (16 * M) * StepX1 / 2) / 2);
	int oyf = rect1.bottom - int(H1 / 5);
	CPen CoordinatePen1, pen1;
	CoordinatePen1.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	pen1.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	pDC1->SelectObject(&CoordinatePen1);
	//画坐标
	pDC1->MoveTo(rect1.left, oyf);
	pDC1->LineTo(rect1.left + W1, oyf);
	//pDC1->BeginPath();
	pDC1->TextOut(oxf, oyf + 5, L"0");
	pDC1->TextOut(oxf + StepX1 * 16 * M / 2 - StepX1 * 3, oyf + 5, L"π");
	//pDC1->EndPath();
	//pDC1->SelectClipPath(RGN_DIFF);
	CPen pen4;
	pen4.CreatePen(PS_DOT, 1, RGB(150, 150, 150));
	pDC1->SelectObject(&pen4);
	for (int i2 = 0; i2 < H1; i2 += 20)
	{
		pDC1->MoveTo(0, i2);
		pDC1->LineTo(W, i2);

	}
	for (int j2 = 0; j2 < W1; j2 += 20)
	{

		pDC1->MoveTo(j2, 0);
		pDC1->LineTo(j2, H);
	}

	pDC1->SelectObject(&pen1);
	pDC1->MoveTo(oxf, oyf);
	for (int i = 0; i < (16 * M) / 2; i++)
	{
		pDC1->MoveTo(oxf + StepX1 * i, oyf);
		pDC1->LineTo(oxf + StepX1 * i, int(oyf - StepY1 * Fre[i]));
	}
}


void CFSKDlg::Draw_graph_filter(float S[], float Fre[])
{
	CWnd* pWnd = GetDlgItem(IDC_T);
	CDC* pDC = pWnd->GetDC();
	CRect rect;
	pWnd->GetClientRect(rect);
	int W = rect.Width(); //画图区域宽度
	int H = rect.Height(); //画图区域高度
	//设置背景色
	RedrawWindow();
	CBrush newbrush;
	newbrush.CreateSolidBrush(RGB(255, 255, 255));
	pDC->Rectangle(rect);

	int StepX = int((W - 1) / N);
	double maxt = findmax(S, N);
	double StepY = (H / 2 - 10) / (fabs(maxt));
	//确定画图起始位置
	int ox = int((W - N * StepX) / 2);
	int oyt = rect.bottom - int(H / 2);
	//画坐标
	CPen CoordinatePen, pen;
	CoordinatePen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	pDC->SelectObject(&CoordinatePen);
	pDC->MoveTo(rect.left, oyt);
	pDC->LineTo(rect.left + W, oyt);

	CPen pen2;
	pen2.CreatePen(PS_DOT, 1, RGB(150, 150, 150));
	pDC->SelectObject(&pen2);
	for (int i1 = 0; i1 < H; i1 += 20)
	{
		pDC->MoveTo(0, i1);
		pDC->LineTo(W, i1);

	}
	for (int j1 = 0; j1 < W; j1 += 20)
	{

		pDC->MoveTo(j1, 0);
		pDC->LineTo(j1, H);
	}
	pDC->SelectObject(&pen);
	pDC->MoveTo(ox, oyt);
	for (int i = 0; i < N; i++)
	{
		pDC->LineTo(ox + i * StepX, int(oyt - StepY * S[i]));
	}
	//频谱图
	CWnd* pWnd1 = GetDlgItem(IDC_F);
	CDC* pDC1 = pWnd1->GetDC();
	CRect rect1;
	pWnd1->GetClientRect(rect1);
	int W1 = rect1.Width(); //画图区域宽度
	int H1 = rect1.Height(); //画图区域高度
	CBrush newbrush1;
	newbrush1.CreateSolidBrush(RGB(255, 255, 255));
	pDC1->Rectangle(rect1);
	//坐标定位
	int StepX1 = int(2 * (W1 - 1) / N);
	float maxt1 = findmax(Fre, int(N / 2));
	float StepY1 = (4 * H1 / 5 - 10) / ((float)fabs(maxt1));
	//确定画图起始位置
	int oxf = int((W1 - N * StepX1 / 2) / 2);
	int oyf = rect1.bottom - int(H1 / 5);
	CPen CoordinatePen1, pen1;
	CoordinatePen1.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	pen1.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	pDC1->SelectObject(&CoordinatePen1);
	//画坐标
	pDC1->MoveTo(rect1.left, oyf);
	pDC1->LineTo(rect1.left + W1, oyf);
	pDC1->TextOut(oxf, oyf + 5, L"0");
	pDC1->TextOut(oxf + StepX1 * N / 2 - StepX1 * 3, oyf + 5, L"π");

	CPen pen4;
	pen4.CreatePen(PS_DOT, 1, RGB(150, 150, 150));
	pDC1->SelectObject(&pen4);
	for (int i2 = 0; i2 < H1; i2 += 20)
	{
		pDC1->MoveTo(0, i2);
		pDC1->LineTo(W1, i2);

	}
	for (int j2 = 0; j2 < W1; j2 += 20)
	{

		pDC1->MoveTo(j2, 0);
		pDC1->LineTo(j2, H1);
	}

	pDC1->SelectObject(&pen1);
	pDC1->MoveTo(oxf, oyf);
	for (int i = 0; i < N / 2; i++)
	{
		pDC1->MoveTo(oxf + StepX1 * i, oyf);
		pDC1->LineTo(oxf + StepX1 * i, int(oyf - StepY1 * Fre[i]));
	}
}
