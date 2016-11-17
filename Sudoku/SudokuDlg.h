
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
	//add
	afx_msg void OnDBClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl m_pGrid;
	


	void Init();											//��ʼ��
	void GridCtrlInit();									//��ʼ������
	void VectorInit();										//�����ʼ��
	void SetCellColor(int row, int column, COLORREF color);	//����ĳ����Ԫ����ɫ
	void GetTableFromDB();									//�����ݿ��л�ȡ������
	void FillGrid();										//�������е�һ�������������񣬲��ı�����ַ�����ɫ
	void Timer();											//�������ʱ��
	bool IsFillNumberComformRules(int row, int column, int iValue);//�������ݷ��Ϲ�����
	void FillErrorTip();									//��������ʾ
	void RestoreErrorTip();									//��ԭ��ʾ
	bool IsFinish();										//�Ƿ����
	void FinishDisplay();									//�����ʾ



	vector<vector<int>> m_vtSudoku;					//��ά���飬������е����� 0,0,0 0,0,1 0,0,2  1,0,3 1,0,4 1,0,5  2,0,6 2,0,7 2,0,8
															//                       0,1,0 0,1,1 0,1,2  1,1,3 1,1,4 1,1,5  2,1,6 2,1,7 2,1,8��������
	UINT m_fillValue;										//���ֵ
};
