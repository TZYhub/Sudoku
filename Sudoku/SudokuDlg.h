
// SudokuDlg.h : ͷ�ļ�
//

#pragma once
#include "GridCtrl.h"


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
	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl m_pGrid;
	void GridCtrlInit();
};
