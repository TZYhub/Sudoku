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
	CreateFinallSudoku();//1.��������

	DigHole();//2.�����Ѷȵȼ��ڶ������ɷ���Ҫ�������

	//3.�����任
	return m_vtSuduko;
}


void CreateSudoku::CreateFinallSudoku()
{
	//1.���ѡȡ11�����ӣ��������1-9�����֣������ƽ������������ó�����
}

void CreateSudoku::DigHole()
{

}