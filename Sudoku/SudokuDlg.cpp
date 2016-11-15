
// SudokuDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Sudoku.h"
#include "SudokuDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int mc_lineAndColumn=9;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSudokuDlg 对话框




CSudokuDlg::CSudokuDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSudokuDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSudokuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_GridControl(pDX, IDC_GRID, m_pGrid);
}

BEGIN_MESSAGE_MAP(CSudokuDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CSudokuDlg 消息处理程序

BOOL CSudokuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GridCtrlInit();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSudokuDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSudokuDlg::OnPaint()
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
HCURSOR CSudokuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSudokuDlg::GridCtrlInit()
{
	m_pGrid.SetEditable(true);
	//m_pGrid.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));//黄色背景
	m_pGrid.SetRowCount(9); //初始为9行
	m_pGrid.SetColumnCount(9); //初始化为9列

	for (int row=0; row < mc_lineAndColumn; row++)
	{
		for (int column=0; column < mc_lineAndColumn; column++)
		{
			GV_ITEM Item; 
			Item.crBkClr=(DWORD)2;
			m_pGrid.SetRowHeight(row,25);
			m_pGrid.SetColumnWidth(column,25);
			m_pGrid.SetItem(&Item); 
		}
	}









	//for (int row = 0; row < m_pGrid.GetRowCount(); row++)
	//	for (int col = 0; col < m_pGrid.GetColumnCount(); col++)
	//	{ 
	//		//设置表格显示属性
	//		GV_ITEM Item; 
	//		Item.mask = GVIF_TEXT|GVIF_FORMAT;
	//		Item.row = row;
	//		Item.col = col;
	//		Item.crBkClr=(RGB(0xFF, 0xFF, 0x00));
	//		m_pGrid.SetItem(&Item);
	//		m_pGrid.SetRowHeight(row,25); //设置各行高          
	//		m_pGrid.SetColumnWidth(col,25); //设置各列宽
	//		if(row==0&&col==0) //第(0，0)格
	//		{
	//			Item.nFormat = DT_CENTER|DT_WORDBREAK;
	//			Item.strText.Format(_T(""),col);
	//		}
	//		else if (row < 1) //设置0行表头显示
	//		{        
	//			Item.nFormat = DT_CENTER|DT_WORDBREAK;
	//			Item.strText.Format(_T(""));
	//		}
	//		else if (col < 1) //设置0列表头显示
	//		{
	//			if(row< m_pGrid.GetRowCount())
	//			{
	//				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	//				Item.strText.Format(_T(""));
	//			}
	//		}
	//		else
	//		{
	//			Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	//			Item.strText.Format(_T(""),2);
	//		}
	//		m_pGrid.SetItem(&Item); 
	//	}
}