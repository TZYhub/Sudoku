
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
	ON_NOTIFY(NM_DBLCLK, IDC_GRID, &CSudokuDlg::OnDBClick)
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_GRID, OnGridStartEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit)
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
	Init();
	
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

void CSudokuDlg::Init()
{
	GridCtrlInit();//表格初始化
	VectorInit();
	
}

//表格初始化，包括颜色，网格大小，等
void CSudokuDlg::GridCtrlInit()
{
	m_pGrid.SetEditable(true);
	m_pGrid.SetRowCount(9);			//初始为9行
	m_pGrid.SetColumnCount(9);		//初始化为9列

	for (int row=0; row < mc_lineAndColumn; row++)
	{
		for (int column=0; column < mc_lineAndColumn; column++)
		{
			GV_ITEM Item ; 
			Item.row = row;
			Item.col = column;
			Item.mask = GVIF_BKCLR;
			Item.crFgClr = BLACK;

			if ((row < 3) && (column > 2 && column < 6))
			{
				Item.crBkClr = MGREEN;
			}
			else if ((3 == row || 4 == row || 5 == row) && (column < 3 || column > 5))
			{
				Item.crBkClr = MGREEN;
			}
			else if ( (row > 5) && ( column > 2 && column < 6))
			{
				Item.crBkClr = MGREEN;
			}
			else
			{
				Item.crBkClr = WHITE;
			}
			
			m_pGrid.SetRowHeight(row,25);
			m_pGrid.SetColumnWidth(column,25);
			m_pGrid.SetItem(&Item);
			m_pGrid.SetGridLineColor(BLACK);
		}
	}
}


void CSudokuDlg::VectorInit()
{
	vector<int> vt;
	for (int index = 0; index < mc_lineAndColumn; index++)
	{
		for (int row = 0; row < mc_lineAndColumn; row++)
		{
			vt.clear();
			for (int column = 0; column < mc_lineAndColumn; column++)
			{
				vt.push_back(0);
			}
			m_vtSudoku.push_back(vt);
		}
	}
}

void CSudokuDlg::SetCellColor(int row, int column, COLORREF color)
{
	GV_ITEM item;
	item.row = row;
	item.col = column;
	item.mask = GVIF_BKCLR;
	item.crBkClr = color;
	m_pGrid.SetItem(&item);
}


//判断填入的数字是否符合规则
bool CSudokuDlg::IsFillNumberComformRules(int row, int column, int iValue)
{
	//行
	for (int col = 0; col < mc_lineAndColumn; col++)
	{
		if (col != column && m_vtSudoku.at(row).at(col) == iValue)
		{
			//改变这两个地方的颜色
			return false;
		}
	}
	//列
	for (int iRow = 0; iRow < mc_lineAndColumn; iRow++)
	{
		if (iRow != row && m_vtSudoku.at(iRow).at(column) == iValue)
		{
			//改变这两个地方的颜色
			return false;
		}
	}
	//格子
	int iRowMin = row/3*3;
	int iRowMax = row/3*3+3;
	int iColMin = column/3*3;
	int iColMax = column/3*3+3;
	for (int iRow = iRowMin; iRow < iRowMax; iRow++)
	{
		for (int iCol = iColMin; iCol < iColMax; iCol++)
		{
			if ( (iRow != row || iCol != column) && m_vtSudoku.at(iRow).at(iCol) == iValue)
			{
				//改变这两个地方的颜色
				return false;
			}
		}
	}
	return true;
}

void CSudokuDlg::OnDBClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	MessageBox(_T("hahaha"));
}

void CSudokuDlg::OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	
	*pResult = 1;
	
}

void CSudokuDlg::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	m_fillValue = 1;
	bool ret = IsFillNumberComformRules(pItem->iRow, pItem->iColumn, m_fillValue);
	//如果是符合规则的，则填充至二维数组中
	if (ret)
	{
		m_vtSudoku.at(pItem->iRow).at(pItem->iColumn) = m_fillValue;
		//如果填充个数达到了81个，则提示完成
	}
	*pResult = ret ? 1 : -1;
}