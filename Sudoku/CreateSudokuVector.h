#ifndef __CREATESUDOKUVECTOR_H
#define __CREATESUDOKUVECTOR_H
#include "DancingLinkX.h"

enum LEVEL
{
	Lower = 1, Primary, Intermediate, Senior, Ashes/*骨灰级*/
};

struct PointInfo
{
	int vtValue;			//该点的数值
	bool bInputFlag;		//是输入 为true 
};


class CreateSudoku
{
public:
	CreateSudoku();
	~CreateSudoku();
	vector<vector<PointInfo>> CreateSudokuVector(LEVEL lv);//产生一个数独二维数组
protected:
	void InitVector();//初始化数独
	int GetARandValue(int iMin, int iMax);//获取iMin-imax的一个随机数
	bool CreateFinallSudoku();//生成终盘
	void DigHole(LEVEL lv);//挖洞
	void DigHoleLower();//低级
	void DigHoleSenior();
	bool CanDigHole(int iRow, int iCol);
	bool CrackSuduku(vector<vector<int>> vt2);//破解数独,能够破解返回true 否则返回 false

	//破解数独
	bool StartCrack();
	void DoCrack(int &x,int &y,int value,bool &rt);
	bool Crack(int row, int column, int iValue);
	bool IsTrue(int row, int column, int iValue);

private:
	vector<vector<PointInfo>> m_vtSudoku;//最后生成的数独二维数组
	vector<vector<PointInfo>> m_vtTempSudoku;//临时数独二维数组
	CDancingLinkX m_dancingLinkX;
};

#endif