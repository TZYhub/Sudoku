
// SudokuDlg.h : 头文件
//

#pragma once
#include "GridCtrl.h"

enum COLOR
{
	/*红色*/
	RED = RGB(0xFF, 0x00, 0x00),	
	/*米绿色*/
	MGREEN = RGB(0x9A, 0xFF, 0x9A),
	/*白色*/
	WHITE = RGB(0xFF, 0xFF, 0xFF),
	/*黑色*/
	BLACK = RGB(0x00, 0x00, 0x00),
	/*蓝色*/
	BLUE = RGB(0x00, 0x00, 0xFF)
};

// CSudokuDlg 对话框
class CSudokuDlg : public CDialogEx
{
// 构造
public:
	CSudokuDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SUDOKU_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	


	void Init();											//初始化
	void GridCtrlInit();									//初始化网格
	void VectorInit();										//数组初始化
	void SetCellColor(int row, int column, COLORREF color);	//设置某个单元的颜色
	void GetTableFromDB();									//从数据库中获取数独表
	void FillGrid();										//把数独中的一部分数填充至表格，并改变填充字符的颜色
	void Timer();											//计算填充时间
	bool IsFillNumberComformRules(int row, int column, int iValue);//填充的数据符合规则吗
	void FillErrorTip();									//填充错误提示
	void RestoreErrorTip();									//复原提示
	bool IsFinish();										//是否完成
	void FinishDisplay();									//完成显示



	vector<vector<int>> m_vtSudoku;					//三维数组，存放所有的数字 0,0,0 0,0,1 0,0,2  1,0,3 1,0,4 1,0,5  2,0,6 2,0,7 2,0,8
															//                       0,1,0 0,1,1 0,1,2  1,1,3 1,1,4 1,1,5  2,1,6 2,1,7 2,1,8依此类推
	UINT m_fillValue;										//填充值
};
