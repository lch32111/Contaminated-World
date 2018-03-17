#pragma once
#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <vector>

class FileParser
{
private:
	char* m_buf; // buffer - this is where the data goes
	int m_cursor; // point where we are in the file
	unsigned int m_size;

	bool atEOF(); // check for end of file
	bool atEOL(); // check for end of line

	void skipWhiteSpace();
	void skipWhiteSpaceNoNewLine();
	bool isWhiteSpace();
	void reset();
	bool nextLine();

	bool getInt(int* _int);
	bool getChar(char* _char);
	bool getWord(char* _word);

	bool compareString(const char* a, const char* b);
public:
	FileParser();
	~FileParser();

	int OpenFile(const char* _filename);

	bool get_Numb_MabObject_Fromcwmo(int* size);
	bool get_OneMapObject_Info_Fromcwmo(int* index, char* address, int* type);
	bool get_SlopeInfo_Fromcwmo(int* dy1, int* dy2);

	bool getRowFromcwm(int* row);
	bool getColFromcwm(int* col);
	bool getVecFromcwm(std::vector<std::vector<int>>& vec);
	bool getVecFromcwm(std::vector<std::vector<int>>& vec, int& row, int& col);

	bool get_Numb_RankTable_Fromcwrt(int* size);
	bool get_Rank_Number_Fromcwrt(int* number);
	bool get_Rank_Name_Fromcwrt(std::string* name);
	bool get_Rank_Score_Fromcwrt(int* score);
	bool get_Rank_Thought_Fromcwrt(std::string* thought);
};
#endif
