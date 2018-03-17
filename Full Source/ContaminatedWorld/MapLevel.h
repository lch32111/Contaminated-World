#pragma once
#ifndef MAPLEVEL_H
#define MAPLEVEL_H

#include <vector>

class MapLevel
{
private:
	int m_MapData[100][100]; // containing the MapObject Id
	int m_row;
	int m_col;
public:
	MapLevel();
	MapLevel(std::vector<std::vector<int>>& data, int row, int col);
	~MapLevel();

	/* ----- get & set ----- */
	int getMapdata(int row, int col);
	unsigned int getMapRow();
	unsigned int getMapCol();
};

#endif