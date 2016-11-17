
// SudokuDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sudoku.h"
#include "SudokuDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int mc_lineAndColumn=9;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSudokuDlg �Ի���




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


// CSudokuDlg ��Ϣ�������

BOOL CSudokuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	Init();
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSudokuDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSudokuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSudokuDlg::Init()
{
	GridCtrlInit();//����ʼ��
	VectorInit();
	
}

//����ʼ����������ɫ�������С����
void CSudokuDlg::GridCtrlInit()
{
	m_pGrid.SetEditable(true);
	m_pGrid.SetRowCount(9);			//��ʼΪ9��
	m_pGrid.SetColumnCount(9);		//��ʼ��Ϊ9��

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


//�ж�����������Ƿ���Ϲ���
bool CSudokuDlg::IsFillNumberComformRules(int row, int column, int iValue)
{
	//��
	for (int col = 0; col < mc_lineAndColumn; col++)
	{
		if (col != column && m_vtSudoku.at(row).at(col) == iValue)
		{
			//�ı��������ط�����ɫ
			return false;
		}
	}
	//��
	for (int iRow = 0; iRow < mc_lineAndColumn; iRow++)
	{
		if (iRow != row && m_vtSudoku.at(iRow).at(column) == iValue)
		{
			//�ı��������ط�����ɫ
			return false;
		}
	}
	//����
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
				//�ı��������ط�����ɫ
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
	//����Ƿ��Ϲ���ģ����������ά������
	if (ret)
	{
		m_vtSudoku.at(pItem->iRow).at(pItem->iColumn) = m_fillValue;
		//����������ﵽ��81��������ʾ���
	}
	*pResult = ret ? 1 : -1;
}