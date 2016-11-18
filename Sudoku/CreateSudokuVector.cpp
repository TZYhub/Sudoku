#include "stdafx.h"
#include "CreateSudokuVector.h"

const int mc_nine = 9;

CreateSudoku::CreateSudoku()
{
	vector<int> vt;
	for (int iRow =0; iRow < mc_nine; iRow++)
	{
		vt.clear();
		for (int iCol =0; iCol <mc_nine; iCol++)
		{
			vt.push_back(0);
		}
		m_vtSuduko.push_back(vt);
	}
}

CreateSudoku::~CreateSudoku()
{

}

vector<vector<int>> CreateSudoku::CreateSudokuVector()
{
	CreateFinallSudoku();//1.生成终盘

	DigHole();//2.根据难度等级挖洞，生成符合要求的数独

	//3.可做变换
	return m_vtSuduko;
}


void CreateSudoku::CreateFinallSudoku()
{
	//1.随机选取11个格子，随机填入1-9的数字，利用破解数独函数，得出终盘
}

void CreateSudoku::DigHole()
{

}