/**************************************************************************
���ܣ�ʹ���赸��������ľ�ȷ�������⣨��ά���飩�������


**************************************************************************/
#ifndef __DANCINGLINKX_H
#define __DANCINGLINKX_H

struct NodeInfo
{
	NodeInfo *left;
	NodeInfo *right;
	NodeInfo *up;
	NodeInfo *down;
	int _row;
	NodeInfo *col;
};


class CDancingLinkX
{
public:
	CDancingLinkX();

	bool Solution(vector<vector<int>> vtInput, vector<int> &vtResult);//�����ά���飬����⣬����һλ������

};

#endif