#include "MapLevel.h"
#include <stdlib.h>

MapLevel::MapLevel()
{

}

MapLevel::MapLevel(std::vector<std::vector<int>>& data, int row, int col)
{
	// Data copy
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			m_MapData[i][j] = data[i][j];

	m_row = row;
	m_col = col;
}

MapLevel::~MapLevel()
{
}

int MapLevel::getMapdata(int row, int col)
{
	return m_MapData[row][col];
}

unsigned int MapLevel::getMapRow()
{
	return m_row;
}

unsigned int MapLevel::getMapCol()
{
	return m_col;
}

