#ifndef __CREATESUDOKUVECTOR_H
#define __CREATESUDOKUVECTOR_H


class CreateSudoku
{
public:
	CreateSudoku();
	~CreateSudoku();
	vector<vector<int>> CreateSudokuVector();//����һ��������ά����
protected:
	void CreateFinallSudoku();//��������
	void DigHole();//�ڶ�
	bool CrackSuduku(vector<vector<int>> vt2);//�ƽ�����,�ܹ��ƽⷵ��true ���򷵻� false

private:
	vector<vector<int>> m_vtSuduko;//������ɵ�������ά����
};

#endif