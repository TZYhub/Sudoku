#ifndef __CREATESUDOKUVECTOR_H
#define __CREATESUDOKUVECTOR_H


class CreateSudoku
{
public:
	CreateSudoku();
	~CreateSudoku();
	vector<vector<int>> CreateSudokuVector();//产生一个数独二维数组
protected:
	void CreateFinallSudoku();//生成终盘
	void DigHole();//挖洞
	bool CrackSuduku(vector<vector<int>> vt2);//破解数独,能够破解返回true 否则返回 false

private:
	vector<vector<int>> m_vtSuduko;//最后生成的数独二维数组
};

#endif