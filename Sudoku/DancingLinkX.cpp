#include "stdafx.h"
#include "DancingLinkX.h"

CDancingLinkX::CDancingLinkX()
{

}


bool CDancingLinkX::Solution(vector<vector<int>> vtInput, vector<int> &vtResult)
{
	vector<int> vt;
	for (int iRow = 0; iRow < 6; iRow++)
	{
		vt.clear();
		for (int iCol = 0; iCol < 7; iCol++)
		{
			vt.push_back(0);
		}
		vtInput.push_back(vt);
	}
	vtInput.at(0).at(2) = 1;vtInput.at(0).at(4) = 1;vtInput.at(0).at(5) = 1;
	vtInput.at(1).at(0) = 1;vtInput.at(1).at(3) = 1;vtInput.at(1).at(6) = 1;
	vtInput.at(2).at(1) = 1;vtInput.at(2).at(2) = 1;vtInput.at(2).at(5) = 1;
	vtInput.at(3).at(0) = 1;vtInput.at(3).at(3) = 1;
	vtInput.at(4).at(1) = 1;vtInput.at(4).at(6) = 1;
	vtInput.at(5).at(3) = 1;vtInput.at(5).at(4) = 1;vtInput.at(5).at(6) = 1;

	NodeInfo *head = new NodeInfo;
	head->_row = 0;
	vector<NodeInfo *> vtFuzhu;
	vtFuzhu.push_back(head);
	for (int iCol = 1; iCol < 8; iCol++)
	{
		NodeInfo *C = new NodeInfo;
		C->col = C;
		C->_row = 0;
		vtFuzhu.push_back(C);
	}

	for (int i = 1; i < 7; i++)
	{
		vtFuzhu.at(i)->left = vtFuzhu.at(i - 1);
		vtFuzhu.at(i)->right =vtFuzhu.at(i + 1);
	}
	//head
	vtFuzhu.at(0)->left = vtFuzhu.at(7);
	vtFuzhu.at(0)->right = vtFuzhu.at(1);
	//最后一个
	vtFuzhu.at(7)->left = vtFuzhu.at(6);
	vtFuzhu.at(7)->right =vtFuzhu.at(0);

	vector<NodeInfo *> vtElem;
	for (int iRow = 0; iRow < 6; iRow++)
	{
		for (int iCol = 0; iCol < 7; iCol++)
		{
			if (1 == vtInput.at(iRow).at(iCol))
			{
				NodeInfo *elem = new NodeInfo;
				elem->_row = iRow + 1;
				elem->col = vtFuzhu.at(iCol + 1);
				vtElem.push_back(elem);
			}
		}
	}


	return true;
}