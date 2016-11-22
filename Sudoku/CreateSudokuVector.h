#ifndef __CREATESUDOKUVECTOR_H
#define __CREATESUDOKUVECTOR_H
#include "DancingLinkX.h"

enum LEVEL
{
	Lower = 1, Primary, Intermediate, Senior, Ashes/*�ǻҼ�*/
};

struct PointInfo
{
	int vtValue;			//�õ����ֵ
	bool bInputFlag;		//������ Ϊtrue 
};


class CreateSudoku
{
public:
	CreateSudoku();
	~CreateSudoku();
	vector<vector<PointInfo>> CreateSudokuVector(LEVEL lv);//����һ��������ά����
protected:
	void InitVector();//��ʼ������
	int GetARandValue(int iMin, int iMax);//��ȡiMin-imax��һ�������
	bool CreateFinallSudoku();//��������
	void DigHole(LEVEL lv);//�ڶ�
	void DigHoleLower();//�ͼ�
	void DigHoleSenior();
	bool CanDigHole(int iRow, int iCol);
	bool CrackSuduku(vector<vector<int>> vt2);//�ƽ�����,�ܹ��ƽⷵ��true ���򷵻� false

	//�ƽ�����
	bool StartCrack();
	void DoCrack(int &x,int &y,int value,bool &rt);
	bool Crack(int row, int column, int iValue);
	bool IsTrue(int row, int column, int iValue);

private:
	vector<vector<PointInfo>> m_vtSudoku;//������ɵ�������ά����
	vector<vector<PointInfo>> m_vtTempSudoku;//��ʱ������ά����
	CDancingLinkX m_dancingLinkX;
};

#endif