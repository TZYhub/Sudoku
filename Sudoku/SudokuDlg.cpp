
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
	GridCtrlInit();
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

void CSudokuDlg::GridCtrlInit()
{
	m_pGrid.SetEditable(true);
	//m_pGrid.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));//��ɫ����
	m_pGrid.SetRowCount(9); //��ʼΪ9��
	m_pGrid.SetColumnCount(9); //��ʼ��Ϊ9��

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
	//		//���ñ����ʾ����
	//		GV_ITEM Item; 
	//		Item.mask = GVIF_TEXT|GVIF_FORMAT;
	//		Item.row = row;
	//		Item.col = col;
	//		Item.crBkClr=(RGB(0xFF, 0xFF, 0x00));
	//		m_pGrid.SetItem(&Item);
	//		m_pGrid.SetRowHeight(row,25); //���ø��и�          
	//		m_pGrid.SetColumnWidth(col,25); //���ø��п�
	//		if(row==0&&col==0) //��(0��0)��
	//		{
	//			Item.nFormat = DT_CENTER|DT_WORDBREAK;
	//			Item.strText.Format(_T(""),col);
	//		}
	//		else if (row < 1) //����0�б�ͷ��ʾ
	//		{        
	//			Item.nFormat = DT_CENTER|DT_WORDBREAK;
	//			Item.strText.Format(_T(""));
	//		}
	//		else if (col < 1) //����0�б�ͷ��ʾ
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