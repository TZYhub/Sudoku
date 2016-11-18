
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
const CString cStrCancel = _T("取消");
const CString cStrSpace = _T("空格");
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
	,m_iFillCount(0)
	,m_timeSecond(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSudokuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_GridControl(pDX, IDC_GRID, m_pGrid);
	DDX_GridControl(pDX, IDC_CHOICE, m_pChoice);
	DDX_Control(pDX, IDC_TIME, m_timer);
}

BEGIN_MESSAGE_MAP(CSudokuDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_GRID, &CSudokuDlg::OnClickGrid)
	ON_NOTIFY(NM_CLICK, IDC_CHOICE, &CSudokuDlg::OnClickChoice)
	ON_NOTIFY(GVN_BEGINDRAG, IDC_GRID, &CSudokuDlg::OnBeginDrag)
	ON_WM_TIMER()
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
	ChoiceGridCtrlInit();
	VectorInit();
	LoadVectorToGridCtrl();
	
}

//表格初始化，包括颜色，网格大小，等
void CSudokuDlg::GridCtrlInit()
{
	//m_pGrid.SetSingleRowSelection(FALSE);
	//m_pGrid.SetSingleColSelection(FALSE);
	m_pGrid.SetSingleColSelection(FALSE);
	m_pGrid.SetEditable(true);
	m_pGrid.SetRowCount(9);			//初始为9行
	m_pGrid.SetColumnCount(9);		//初始化为9列
	//m_pGrid.EnableDragAndDrop(FALSE);
	

	for (int row=0; row < mc_lineAndColumn; row++)
	{
		for (int column=0; column < mc_lineAndColumn; column++)
		{
			m_pGrid.SetRowHeight(row,25);
			m_pGrid.SetColumnWidth(column,25);
			m_pGrid.SetGridLineColor(BLACK);
			m_pGrid.SetItemFormat(row, column, DT_CENTER | DT_VCENTER);
		}
	}
	SetDefaultColor();
	m_pGrid.SetTrackFocusCell(FALSE);
	m_pGrid.SetFrameFocusCell(FALSE);
	m_pGrid.ExpandColumnsToFit();
}


void CSudokuDlg::ChoiceGridCtrlInit()
{
	CFont* pFont = m_pChoice.GetFont(); 
	LOGFONT lf;  
	pFont->GetLogFont(&lf);  
	memcpy(lf.lfFaceName, _T("Arial"), 6); 
	lf.lfHeight = 5000;
	lf.lfEscapement = 900; 
	lf.lfOrientation = 900;

	m_pChoice.SetEditable(false);
	m_pChoice.InsertRow(_T(""));
	m_pChoice.SetRowCount(1);			//初始为9行
	m_pChoice.SetColumnCount(11);		//初始化为9列

	for (int iCol = 0; iCol < 11; iCol++)
	{
		if (iCol < 9)
		{
			TCHAR a[5];
			_itot_s(iCol+1, a, 5, 10);
			m_pChoice.SetItemText(0, iCol, a);
		}
		else if (9 == iCol)
		{
			m_pChoice.SetItemText(0, iCol, _T("空格"));
		}
		else
		{
			//m_pChoice.InsertColumn(_T("取消"));
			m_pChoice.SetItemText(0, iCol, _T("取消"));
		}
		m_pChoice.SetItemFormat(0, iCol, 37U);
		GV_ITEM Item ; 
		Item.row = 0;
		Item.col = iCol;
		Item.mask = GVIF_BKCLR | GVIF_STATE;
		Item.crBkClr = MGREEN;
		//Item.nState = GVIS_DROPHILITED;
		m_pChoice.SetColumnWidth(iCol, 40);
		m_pChoice.SetItem(&Item);

	}
	m_pChoice.SetRowHeight(0,40);
	

	m_pChoice.ShowWindow(false);
}


void CSudokuDlg::VectorInit()
{
	vector<PointInfo> vt;
	PointInfo point;
	for (int row = 0; row < mc_lineAndColumn; row++)
	{
		vt.clear();
		for (int column = 0; column < mc_lineAndColumn; column++)
		{
			point.vtValue = 0;
			point.bInputFlag = false;
			vt.push_back(point);
		}
		m_vtSudoku.push_back(vt);
	}
	m_vtSudoku.at(0).at(0).vtValue = 3;m_vtSudoku.at(0).at(3).vtValue = 4;m_vtSudoku.at(0).at(7).vtValue = 1;m_vtSudoku.at(0).at(8).vtValue = 6;
	m_vtSudoku.at(1).at(0).vtValue = 7;m_vtSudoku.at(1).at(1).vtValue = 2;m_vtSudoku.at(1).at(2).vtValue = 6;m_vtSudoku.at(1).at(6).vtValue = 4;
	m_vtSudoku.at(2).at(3).vtValue = 3;m_vtSudoku.at(2).at(4).vtValue = 7;m_vtSudoku.at(2).at(7).vtValue = 5;
	m_vtSudoku.at(3).at(1).vtValue = 9;m_vtSudoku.at(3).at(5).vtValue = 5;m_vtSudoku.at(3).at(6).vtValue = 3;
	m_vtSudoku.at(4).at(0).vtValue = 8;m_vtSudoku.at(4).at(2).vtValue = 5;m_vtSudoku.at(4).at(6).vtValue = 6;
	m_vtSudoku.at(5).at(1).vtValue = 4;m_vtSudoku.at(5).at(4).vtValue = 8;m_vtSudoku.at(5).at(5).vtValue = 3;m_vtSudoku.at(5).at(7).vtValue = 2;
	m_vtSudoku.at(6).at(3).vtValue = 5;m_vtSudoku.at(6).at(7).vtValue = 9;m_vtSudoku.at(6).at(8).vtValue = 4;
	m_vtSudoku.at(7).at(2).vtValue = 3;m_vtSudoku.at(7).at(4).vtValue = 9;m_vtSudoku.at(7).at(5).vtValue = 4;
	m_vtSudoku.at(8).at(0).vtValue = 9;m_vtSudoku.at(8).at(3).vtValue = 8;m_vtSudoku.at(8).at(8).vtValue = 7;
}


void CSudokuDlg::LoadVectorToGridCtrl()
{
	GV_ITEM item;
	
	for (int row = 0; row < mc_lineAndColumn; row++)
	{
		for (int column = 0; column < mc_lineAndColumn; column++)
		{
			if (m_vtSudoku.at(row).at(column).vtValue != 0)
			{
				TCHAR ch[3];
				_itot_s(m_vtSudoku.at(row).at(column).vtValue, ch, _countof(ch), 10);
				m_pGrid.SetItemText(row, column, ch);
				//m_pGrid.SetTextColor()
				m_vtSudoku.at(row).at(column).bInputFlag = true;
				m_iFillCount++;
			}
		}
	}
}


void CSudokuDlg::SetDefaultColor()
{

	for (int row=0; row < mc_lineAndColumn; row++)
	{
		for (int column=0; column < mc_lineAndColumn; column++)
		{
			GV_ITEM Item ; 
			Item.row = row;
			Item.col = column;
			Item.mask = GVIF_BKCLR;
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
			m_pGrid.SetItem(&Item);
		}
	}
	m_pGrid.ExpandColumnsToFit();
}


//判断填入的数字是否符合规则
bool CSudokuDlg::IsFillNumberComformRules(int row, int column, int iValue, int &rtRow, int &rtColumn)
{
	//行
	for (int col = 0; col < mc_lineAndColumn; col++)
	{
		if (col != column && m_vtSudoku.at(row).at(col).vtValue == iValue)
		{
			//改变这两个地方的颜色
			rtRow = row;
			rtColumn = col;
			return false;
		}
	}
	//列
	for (int iRow = 0; iRow < mc_lineAndColumn; iRow++)
	{
		if (iRow != row && m_vtSudoku.at(iRow).at(column).vtValue == iValue)
		{
			//改变这两个地方的颜色
			rtRow = iRow;
			rtColumn = column;
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
			if ( (iRow != row || iCol != column) && m_vtSudoku.at(iRow).at(iCol).vtValue == iValue)
			{
				//改变这两个地方的颜色
				rtRow = iRow;
				rtColumn = iCol;
				return false;
			}
		}
	}
	return true;
}


void CSudokuDlg::OnClickGrid(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;
	if (IsColorChanged())
	{
		SetDefaultColor();
		m_bColorChange = false;
	}
	//弹出可选择的数字和取消按钮
	m_gridRow = pItem->iRow;
	m_gridCol = pItem->iColumn;
	if (m_vtSudoku.at(m_gridRow).at(m_gridCol).bInputFlag)
		return;
	m_bChoiceFlag = false;
	m_pChoice.ShowWindow(!m_bChoiceFlag);
	*pResult = 1;
}


void CSudokuDlg::OnClickChoice(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNMHDR;
	m_bChoiceFlag = true;
	CString str = m_pChoice.GetItemText(pItem->iRow, pItem->iColumn);
	if (cStrSpace == str)//如果是空格,则清除上面的字符
	{
		m_vtSudoku.at(m_gridRow).at(m_gridCol).vtValue = 0;
		m_pGrid.SetItemText(m_gridRow, m_gridCol, _T(""));
		m_iFillCount--;
	}
	else if (cStrCancel == str)//如果是取消，则不处理
	{

	}
	else
	{
		int fillNumber = _ttof(str);
		int svRow;		//same value row
		int svColumn;	//same value column
		bool ret = IsFillNumberComformRules(m_gridRow, m_gridCol, fillNumber, svRow, svColumn);//若是数字，则先判断是否正确，再填入表格及数组中
		
		if (ret)//如果是符合规则的，则填充至二维数组中
		{
			if (0 == m_timeSecond)
			{
				StartTimer();
			}
			m_iFillCount++;
			if (IsFinish())//如果填充个数达到了81个，则提示完成
			{
				StopTimer();//停止计时器
				MessageBox(_T("成功！"));//显示成功完成
			}
			m_vtSudoku.at(m_gridRow).at(m_gridCol).vtValue = fillNumber;
			m_pGrid.SetItemText(m_gridRow, m_gridCol, str);
		}
		else
		{
			m_bColorChange = true;
			m_pGrid.SetItemBkColour(svRow, svColumn, RED);
		}
		
	}
	m_pChoice.ShowWindow(!m_bChoiceFlag);//隐藏选择网格
	m_pGrid.SetFocusCell(m_gridRow, m_gridCol);
	m_pGrid.ExpandColumnsToFit();

	*pResult = 1;
}


void CSudokuDlg::StartTimer()
{
	SetTimer(1,1000,NULL);
}


void CSudokuDlg::StopTimer()
{
	KillTimer(1);
}


void CSudokuDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_timeSecond++;
	CString strTime;
	strTime.Format(_T("%02d:%02d:%02d"), m_timeSecond/3600, m_timeSecond/60, m_timeSecond%60);
	m_timer.SetWindowText(strTime);
	CDialogEx::OnTimer(nIDEvent);
}


bool CSudokuDlg::IsFinish()
{
	return mc_lineAndColumn*mc_lineAndColumn == m_iFillCount;
}

bool CSudokuDlg::IsColorChanged()
{
	return m_bColorChange;
}


void CSudokuDlg::OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult)
{

	*pResult = -1;
}