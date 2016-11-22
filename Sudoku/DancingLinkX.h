/**************************************************************************
功能：使用舞蹈链对输入的精确覆盖问题（二维数组）进行求解


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

	bool Solution(vector<vector<int>> vtInput, vector<int> &vtResult);//输入二维数组，求出解，存入一位数组中

};

#endif