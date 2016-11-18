
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

struct PointInfo
{
	int vtValue;			//该点的数值
	bool bInputFlag;		//是输入 为true 
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//add
	afx_msg void OnClickGrid(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickChoice(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void  OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl m_pGrid;
	CGridCtrl m_pChoice;
	


	void Init();											//初始化
	void GridCtrlInit();									//初始化网格
	void ChoiceGridCtrlInit();								//选择框初始化
	void VectorInit();										//数组初始化
	void LoadVectorToGridCtrl();							//加载数组到网格
	void SetDefaultColor();	//设置某个单元的颜色
	void GetTableFromDB();									//从数据库中获取数独表
	void FillGrid();										//把数独中的一部分数填充至表格，并改变填充字符的颜色
	void Timer();											//计算填写数独用时时间
	bool IsFillNumberComformRules(int row, int column, int iValue, int &rtRow, int &rtColumn);//填充的数据符合规则吗
	void FillErrorTip();									//填充错误提示
	void RestoreErrorTip();									//复原提示
	void FinishDisplay();									//完成显示
	bool IsFinish();										//是否无错填充完成
	void StartTimer();
	void StopTimer();
	bool IsColorChanged();//是否改变过颜色


	vector<vector<PointInfo>> m_vtSudoku;					//三维数组，存放所有的数字 
	UINT m_fillValue;										//填充值
	bool m_bChoiceFlag;										//是否选择了字符
	int m_gridRow;
	int m_gridCol;
	int m_choiceRow;
	int m_choiceCol;
	int m_iFillCount;//填入数字计数
	CStatic m_timer;
	
	ULONG m_timeSecond;//记录的秒数
	bool m_bColorChange;//改变颜色标识
};
