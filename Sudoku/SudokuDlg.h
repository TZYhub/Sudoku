
// SudokuDlg.h : ͷ�ļ�
//

#pragma once
#include "GridCtrl.h"

enum COLOR
{
	/*��ɫ*/
	RED = RGB(0xFF, 0x00, 0x00),	
	/*����ɫ*/
	MGREEN = RGB(0x9A, 0xFF, 0x9A),
	/*��ɫ*/
	WHITE = RGB(0xFF, 0xFF, 0xFF),
	/*��ɫ*/
	BLACK = RGB(0x00, 0x00, 0x00),
	/*��ɫ*/
	BLUE = RGB(0x00, 0x00, 0xFF)
};

struct PointInfo
{
	int vtValue;			//�õ����ֵ
	bool bInputFlag;		//������ Ϊtrue 
};


// CSudokuDlg �Ի���
class CSudokuDlg : public CDialogEx
{
// ����
public:
	CSudokuDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SUDOKU_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//add
	afx_msg void OnClickGrid(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickChoice(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void  OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl m_pGrid;
	CGridCtrl m_pChoice;
	


	void Init();											//��ʼ��
	void GridCtrlInit();									//��ʼ������
	void ChoiceGridCtrlInit();								//ѡ����ʼ��
	void VectorInit();										//�����ʼ��
	void LoadVectorToGridCtrl();							//�������鵽����
	void SetDefaultColor();	//����ĳ����Ԫ����ɫ
	void GetTableFromDB();									//�����ݿ��л�ȡ������
	void FillGrid();										//�������е�һ�������������񣬲��ı�����ַ�����ɫ
	void Timer();											//������д������ʱʱ��
	bool IsFillNumberComformRules(int row, int column, int iValue, int &rtRow, int &rtColumn);//�������ݷ��Ϲ�����
	void FillErrorTip();									//��������ʾ
	void RestoreErrorTip();									//��ԭ��ʾ
	void FinishDisplay();									//�����ʾ
	bool IsFinish();										//�Ƿ��޴�������
	void StartTimer();
	void StopTimer();
	bool IsColorChanged();//�Ƿ�ı����ɫ


	vector<vector<PointInfo>> m_vtSudoku;					//��ά���飬������е����� 
	UINT m_fillValue;										//���ֵ
	bool m_bChoiceFlag;										//�Ƿ�ѡ�����ַ�
	int m_gridRow;
	int m_gridCol;
	int m_choiceRow;
	int m_choiceCol;
	int m_iFillCount;//�������ּ���
	CStatic m_timer;
	
	ULONG m_timeSecond;//��¼������
	bool m_bColorChange;//�ı���ɫ��ʶ
};
