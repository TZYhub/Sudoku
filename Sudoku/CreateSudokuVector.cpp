#include "stdafx.h"
#include "CreateSudokuVector.h"

const int mc_nine = 9;

CreateSudoku::CreateSudoku()
{
	InitVector();
}

CreateSudoku::~CreateSudoku()
{

}


void CreateSudoku::InitVector()
{
	PointInfo pt;
	vector<PointInfo> vt;
	m_vtSudoku.clear();
	for (int iRow =0; iRow < mc_nine; iRow++)
	{
		vt.clear();
		for (int iCol =0; iCol <mc_nine; iCol++)
		{
			pt.vtValue = 0;
			pt.bInputFlag = false;
			vt.push_back(pt);
		}
		m_vtSudoku.push_back(vt);
	}
}

vector<vector<PointInfo>> CreateSudoku::CreateSudokuVector(LEVEL lv)
{
	vector<vector<int>> vt2;
	vector<int> vt;
	m_dancingLinkX.Solution(vt2, vt);
	while(!CreateFinallSudoku());//1.生成终盘  修改成使用舞蹈链求解

	DigHole(lv);//2.根据难度等级挖洞，生成符合要求的数独

	//3.可做变换
	return m_vtSudoku;
}


int CreateSudoku::GetARandValue(int iMin, int iMax)
{
	if (iMin > iMax)
	{
		int it = iMax;
		iMax = iMin;
		iMin = it;
	}
	srand(time(0));
	return (rand()%(iMax-iMin)+iMin);//对iMax求余
}

bool CreateSudoku::CreateFinallSudoku()
{
	InitVector();
	//1.随机选取9个格子，随机填入1-9的数字，利用破解数独函数，得出终盘
	//从0到80选9不重复的数，放入数组中
	bool flag = false;
	vector<int> vtChoiceNumber;
	vector<int> vtAllNumber;
	for (int i = 0; i < 81; i++)
	{
		vtAllNumber.push_back(i);//填充0-80
	}

	for (int i = 0; i < mc_nine; i++)
	{
		int iValue = GetARandValue(0,80-i);
		vtChoiceNumber.push_back(vtAllNumber.at(iValue));
		vtAllNumber.erase(vtAllNumber.begin()+iValue);//删除已选的元素
	}
	//寻找序号对应的二维坐标，然后填入数字
	for (int i = 0; i < mc_nine; i++)
	{
		int iRow = vtChoiceNumber.at(i)/mc_nine;
		int iCol = vtChoiceNumber.at(i)%mc_nine;
		//看看fillValue是否需要判断条件
		m_vtSudoku.at(iRow).at(iCol).vtValue = i + 1;
		m_vtSudoku.at(iRow).at(iCol).bInputFlag = true;
	}

	//根据填充的这11个格子是否可以生成终盘
	if(StartCrack())
	{
		for (int iRow = 0; iRow < mc_nine; iRow++)
		{
			for (int iCol = 0; iCol < mc_nine; iCol++)
			{
				m_vtSudoku.at(iRow).at(iCol).bInputFlag = true;
			}
		}
		return true;
	}
		
	return false;
}

void CreateSudoku::DigHole(LEVEL lv)
{
	//1.根据难度选择挖洞规则，及挖洞下限
	switch (lv)
	{
	case Lower:
		DigHoleLower();
		break;
	case Primary:
		break;
	case Intermediate:
		break;
	case Senior:
		//DigHoleSenior();
		break;
	case Ashes:
		break;
	default:
		break;
	}
}

void CreateSudoku::DigHoleLower()
{
	//生成一个下限值
	int minValue = 31;
	int needDigNumber = 81 - 31;
	
	vector<int> vtAllNumber;
	for (int i = 0; i < 81; i++)
	{
		vtAllNumber.push_back(i);//填充0-80
	}
	int iIndex = -1;
	int iGetValue = 0;
	//判断是否达到了挖洞的下限值
	while (needDigNumber > 0)
	{
		//1.随机挖洞
		iIndex = GetARandValue(0, vtAllNumber.size()-1);
		iGetValue = vtAllNumber.at(iIndex);
		//2.检验是否可以挖洞
		if (CanDigHole(iGetValue/9, iGetValue%9))
		{
			m_vtSudoku.at(iGetValue/9).at(iGetValue%9).vtValue = 0;
			m_vtSudoku.at(iGetValue/9).at(iGetValue%9).bInputFlag = false;
			vtAllNumber.erase(vtAllNumber.begin()+iIndex);
			needDigNumber--;
		}
	}
	for (int iRow = 0; iRow < mc_nine; iRow++)
	{
		for (int iCol = 0; iCol < mc_nine; iCol++)
		{
			if (!m_vtSudoku.at(iRow).at(iCol).bInputFlag)
			{
				m_vtSudoku.at(iRow).at(iCol).vtValue = 0;
			}
		}
	}
}

bool CreateSudoku::CanDigHole(int iRow, int iCol)
{
	//1.挖去的一行大于下限，挖去的一列大于下限?
	//行
	int compareValue = 0;
	for (int col = 0; col < mc_nine; col++)
	{
		if (m_vtSudoku.at(iRow).at(col).bInputFlag)
		{
			compareValue++;
		}
	}
	if (compareValue < 3)
	{
		return false;
	}

	compareValue = 0;
	//列
	for (int row = 0; row < mc_nine; row++)
	{
		if (m_vtSudoku.at(row).at(iCol).bInputFlag)
		{
			compareValue++;
		}
	}
	if (compareValue < 3)
	{
		return false;
	}
	//2.挖去的数形成唯一解
	int iValue = m_vtSudoku.at(iRow).at(iCol).vtValue;
	for (int i = 0; i < mc_nine; i++)
	{
		if (i+1 != iValue)
		{
			if (IsTrue(iRow, iCol, i+1))
			{
				m_vtSudoku.at(iRow).at(iCol).vtValue = i + 1;
				if (StartCrack())
				{
					return false;
				}
			}
		}		
	}
	return true;
}


//破解数独函数
bool CreateSudoku::StartCrack()
{
	//1.先确定第一个不为输入的位置
	int firstRow = -1;
	int firstCol = -1;
	bool findFlag = false;
	for (int i = 0; i < mc_nine; i++)
	{
		for (int j = 0; j < mc_nine; j++)
		{
			if (!m_vtSudoku.at(i).at(j).bInputFlag)
			{
				firstRow = i;
				firstCol = j;
				findFlag = true;
				break;
			}
		}
		if (findFlag)
		{
			break;
		}
	}
	//2.破解数独
	bool m_bRecall = false;
	for (int i = 0; i < mc_nine; i++)
	{
		for (int j = 0; j < mc_nine; j++)
		{
			if (!m_bRecall)//如果不是回溯
			{
				if (!m_vtSudoku.at(i).at(j).bInputFlag)//如果不是输入，则执行
				{
					int value = 1;
					DoCrack(i, j, 1, m_bRecall);//开始破解
				}
			}
			else//是回溯
			{
				m_bRecall = false;//改变标志
				if (i == firstRow && j == firstCol)//如果回溯找到了最开始的一个还需要回溯，则表示找不到解
				{
					if (m_vtSudoku.at(i).at(j).vtValue < 9)//如果1-8
					{
						DoCrack(i, j, m_vtSudoku.at(i).at(j).vtValue + 1, m_bRecall);
						if (m_bRecall)//如果破解还需回溯，则证明无解
						{
							return false;
						}
					}
					else//如果是9了还需要回溯，则证明无解
					{
						return false;
					}
				}
				else
				{
					//获取i，j的值 
					if (m_vtSudoku.at(i).at(j).bInputFlag)//如果回溯的是一开始输入的值，则继续回溯
					{
						if (0 == j)
						{
							i--;
							if (i < 0)
							{
								return false;
							}
							j = mc_nine - 2;
						}
						else
						{
							j -= 2;
						}
						m_bRecall = true;//下一次是回溯
					}
					else
					{
						if (m_vtSudoku.at(i).at(j).vtValue < 9)//如果1-8
						{
							DoCrack(i, j, m_vtSudoku.at(i).at(j).vtValue + 1, m_bRecall);
						}
						else//等于9
						{
							m_vtSudoku.at(i).at(j).vtValue = 0;
							if (0 == j)
							{
								i--;
								if (i < 0)
								{
									return false;
								}
								j = mc_nine - 2;
							}
							else
							{
								j -= 2;
							}
							m_bRecall = true;
						}
					}
				}
			}
		}
	}
	return true;

}

void CreateSudoku::DoCrack(int &x, int &y, int value, bool &rt)
{
	if(!Crack(x, y, value))//如果填入的数不可以，则值+1继续
	{
		m_vtSudoku.at(x).at(y).vtValue = 0;
		value++;
		if (value > 9)//如果已经加到9了还是不可以，那么回溯
		{
			if (0 == y)
			{
				x--;
				y = mc_nine - 2;
			}
			else
			{
				y -= 2;
			}
			rt = true;
		}
		else
		{
			DoCrack(x, y, value, rt);
		}
	}
}

bool CreateSudoku::Crack(int row, int column, int iValue)
{
	//判断填入的这个数是否可以，可以则返回真，否则返回假
	//先把值推入栈和二维数组中
	//m_vtPoint.at(row).at(column).value = iValue;
	m_vtSudoku.at(row).at(column).vtValue = iValue;
	//然后判断是否可以填入
	return IsTrue(row, column, iValue);//如果可以填入，则返回true

}


bool CreateSudoku::IsTrue(int row, int column, int iValue)
{
	//行
	for (int col = 0; col < mc_nine; col++)
	{
		if (col != column && m_vtSudoku.at(row).at(col).vtValue == iValue)
		{
			return false;
		}
	}
	//列
	for (int iRow = 0; iRow < mc_nine; iRow++)
	{
		if (iRow != row && m_vtSudoku.at(iRow).at(column).vtValue == iValue)
		{
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
				return false;
			}
		}
	}
	return true;
}
