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
	while(!CreateFinallSudoku());//1.��������  �޸ĳ�ʹ���赸�����

	DigHole(lv);//2.�����Ѷȵȼ��ڶ������ɷ���Ҫ�������

	//3.�����任
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
	return (rand()%(iMax-iMin)+iMin);//��iMax����
}

bool CreateSudoku::CreateFinallSudoku()
{
	InitVector();
	//1.���ѡȡ9�����ӣ��������1-9�����֣������ƽ������������ó�����
	//��0��80ѡ9���ظ�����������������
	bool flag = false;
	vector<int> vtChoiceNumber;
	vector<int> vtAllNumber;
	for (int i = 0; i < 81; i++)
	{
		vtAllNumber.push_back(i);//���0-80
	}

	for (int i = 0; i < mc_nine; i++)
	{
		int iValue = GetARandValue(0,80-i);
		vtChoiceNumber.push_back(vtAllNumber.at(iValue));
		vtAllNumber.erase(vtAllNumber.begin()+iValue);//ɾ����ѡ��Ԫ��
	}
	//Ѱ����Ŷ�Ӧ�Ķ�ά���꣬Ȼ����������
	for (int i = 0; i < mc_nine; i++)
	{
		int iRow = vtChoiceNumber.at(i)/mc_nine;
		int iCol = vtChoiceNumber.at(i)%mc_nine;
		//����fillValue�Ƿ���Ҫ�ж�����
		m_vtSudoku.at(iRow).at(iCol).vtValue = i + 1;
		m_vtSudoku.at(iRow).at(iCol).bInputFlag = true;
	}

	//����������11�������Ƿ������������
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
	//1.�����Ѷ�ѡ���ڶ����򣬼��ڶ�����
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
	//����һ������ֵ
	int minValue = 31;
	int needDigNumber = 81 - 31;
	
	vector<int> vtAllNumber;
	for (int i = 0; i < 81; i++)
	{
		vtAllNumber.push_back(i);//���0-80
	}
	int iIndex = -1;
	int iGetValue = 0;
	//�ж��Ƿ�ﵽ���ڶ�������ֵ
	while (needDigNumber > 0)
	{
		//1.����ڶ�
		iIndex = GetARandValue(0, vtAllNumber.size()-1);
		iGetValue = vtAllNumber.at(iIndex);
		//2.�����Ƿ�����ڶ�
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
	//1.��ȥ��һ�д������ޣ���ȥ��һ�д�������?
	//��
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
	//��
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
	//2.��ȥ�����γ�Ψһ��
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


//�ƽ���������
bool CreateSudoku::StartCrack()
{
	//1.��ȷ����һ����Ϊ�����λ��
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
	//2.�ƽ�����
	bool m_bRecall = false;
	for (int i = 0; i < mc_nine; i++)
	{
		for (int j = 0; j < mc_nine; j++)
		{
			if (!m_bRecall)//������ǻ���
			{
				if (!m_vtSudoku.at(i).at(j).bInputFlag)//����������룬��ִ��
				{
					int value = 1;
					DoCrack(i, j, 1, m_bRecall);//��ʼ�ƽ�
				}
			}
			else//�ǻ���
			{
				m_bRecall = false;//�ı��־
				if (i == firstRow && j == firstCol)//��������ҵ����ʼ��һ������Ҫ���ݣ����ʾ�Ҳ�����
				{
					if (m_vtSudoku.at(i).at(j).vtValue < 9)//���1-8
					{
						DoCrack(i, j, m_vtSudoku.at(i).at(j).vtValue + 1, m_bRecall);
						if (m_bRecall)//����ƽ⻹����ݣ���֤���޽�
						{
							return false;
						}
					}
					else//�����9�˻���Ҫ���ݣ���֤���޽�
					{
						return false;
					}
				}
				else
				{
					//��ȡi��j��ֵ 
					if (m_vtSudoku.at(i).at(j).bInputFlag)//������ݵ���һ��ʼ�����ֵ�����������
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
						m_bRecall = true;//��һ���ǻ���
					}
					else
					{
						if (m_vtSudoku.at(i).at(j).vtValue < 9)//���1-8
						{
							DoCrack(i, j, m_vtSudoku.at(i).at(j).vtValue + 1, m_bRecall);
						}
						else//����9
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
	if(!Crack(x, y, value))//���������������ԣ���ֵ+1����
	{
		m_vtSudoku.at(x).at(y).vtValue = 0;
		value++;
		if (value > 9)//����Ѿ��ӵ�9�˻��ǲ����ԣ���ô����
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
	//�ж������������Ƿ���ԣ������򷵻��棬���򷵻ؼ�
	//�Ȱ�ֵ����ջ�Ͷ�ά������
	//m_vtPoint.at(row).at(column).value = iValue;
	m_vtSudoku.at(row).at(column).vtValue = iValue;
	//Ȼ���ж��Ƿ��������
	return IsTrue(row, column, iValue);//����������룬�򷵻�true

}


bool CreateSudoku::IsTrue(int row, int column, int iValue)
{
	//��
	for (int col = 0; col < mc_nine; col++)
	{
		if (col != column && m_vtSudoku.at(row).at(col).vtValue == iValue)
		{
			return false;
		}
	}
	//��
	for (int iRow = 0; iRow < mc_nine; iRow++)
	{
		if (iRow != row && m_vtSudoku.at(iRow).at(column).vtValue == iValue)
		{
			return false;
		}
	}
	//����
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
