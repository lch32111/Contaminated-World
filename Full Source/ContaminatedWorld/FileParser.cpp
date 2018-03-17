	#include "FileParser.h"

FileParser::FileParser()
{
	this->m_buf = NULL;
	this->m_cursor = 0;
	this->m_size = 0;
}

FileParser::~FileParser()
{
	free(m_buf);
	m_buf = NULL;
}

// return positive if the file is opened
// return negative if the file is not opened
int FileParser::OpenFile(const char* _filename)
{
	void* l_pointer;
	size_t l_bytesRead, l_totalBytesRead = 0;
	
	// get a File pointer
	FILE* cwb;
	int l_error = fopen_s(&cwb, _filename, "rb");
	if (l_error != 0) { printf("unable to open the map file %s\n", _filename); return -1; }

	// check if empty file 
	if (fseek(cwb, 0, SEEK_END)) { printf("This map file is empty %s\n", _filename); return -1; }

	// find size of file -> because file indicator on end of file
	m_size = ftell(cwb);

	// allocate memory
	l_pointer = (char*)malloc(sizeof(char) * m_size);
	if (!l_pointer) { printf("Unable to allocate memory for file reading %s\n", _filename); m_size = 0; return -1; }
	
	// file indicator on the beginning
	rewind(cwb);

	// read in data
	while (l_totalBytesRead < m_size)
	{
		l_bytesRead = fread(l_pointer, 1, m_size - l_totalBytesRead, cwb);
		if (!l_bytesRead)
		{
			printf("Error reading file %s\n", _filename);
			free(l_pointer);
			m_size = 0;
			return -1;
		}
		l_totalBytesRead += l_bytesRead;
	}
	// tidy up
	m_buf = (char*)l_pointer;
	fclose(cwb);
	return 1;
}

bool FileParser::atEOF() // check for end of file
{
	bool l_result = true;
	if (m_cursor < m_size) l_result = false;
	return l_result;
}

bool FileParser::atEOL()
{
	bool l_result = false;
	if (m_buf[m_cursor] == '\n') l_result = true;
	if (m_buf[m_cursor] == '\r') l_result = true;
	return l_result;
}

void FileParser::skipWhiteSpace() // skip white space
{
	bool l_whiteSpace = true;
	while (l_whiteSpace && !atEOF())
	{
		l_whiteSpace = isWhiteSpace();
		if (l_whiteSpace) ++m_cursor;
	}
}

void FileParser::skipWhiteSpaceNoNewLine() // skip white spaces, but don't go past a new line
{
	bool l_whiteSpace = true;
	while (!atEOL() && l_whiteSpace && !atEOF())
	{
		l_whiteSpace = isWhiteSpace();
		if (l_whiteSpace) ++m_cursor;
	}
}

bool FileParser::isWhiteSpace()
{
	bool l_result = false;
	if (m_buf[m_cursor] == ' ') l_result = true;
	if (m_buf[m_cursor] == '\n') l_result = true;
	if (m_buf[m_cursor] == '\r') l_result = true;
	if (m_buf[m_cursor] == '\0') l_result = true;
	if (m_buf[m_cursor] == '\t') l_result = true;
	if (m_buf[m_cursor] == 13) l_result = true;
	return l_result;
}

void FileParser::reset() // reset cursor to allow another file seek
{
	m_cursor = 0;
}

bool FileParser::nextLine() // jump to the start of the next line
{
	bool l_foundEnd = false;
	while (!l_foundEnd && !atEOF())
	{
		if (atEOL())
		{
			l_foundEnd = true;
			++m_cursor;
			if (atEOL()) ++m_cursor; // second check to deal with /r/n
		}
		else ++m_cursor;
	}
	return l_foundEnd;
}

bool FileParser::getInt(int* _int) // extract an integer from the file. Returns false if something goes wrong
{
	bool l_success = true;
	bool l_atEnd = false;
	int l_total = 0;
	if (!atEOF()) skipWhiteSpace(); // finds the next set of non-whitespace characters

	while (!l_atEnd && l_success)
	{
		if (!isWhiteSpace() && !atEOF())
		{
			if ((m_buf[m_cursor] >= 48) && (m_buf[m_cursor] <= 57))
			{
				l_total *= 10;
				l_total += m_buf[m_cursor] - 48;
				m_cursor++;
			}
			else if (m_buf[m_cursor] == 45) { printf("Map Data should not be negative\n"); l_success = false; }
			else if (m_buf[m_cursor] == 43) m_cursor++;  // plus sign - do nothing
			else  l_success = false;
		}
		else l_atEnd = true;
	}
	
	*_int = l_total;

	return l_success;
}

bool FileParser::getChar(char* _char)
{
	bool l_success = true;
	if (!atEOF()) skipWhiteSpace();
	if (!atEOF()) *_char = m_buf[m_cursor];
	else l_success = false;
	m_cursor++;
	return l_success;
}

bool FileParser::getWord(char* _word)
{
	bool l_success = false;
	int l_counter = 0;
	if (!atEOF()) skipWhiteSpace();
	while (!isWhiteSpace() && !atEOF())
	{
		l_success = true;
		_word[l_counter] = m_buf[m_cursor];
		m_cursor++;
		l_counter++;
	}
	_word[l_counter] = '\0';
	return l_success;
}

bool FileParser::compareString(const char* a, const char* b)
{
	bool l_success = true;
	int l_counter = 0;

	while ((a[l_counter] != '\0') && (b[l_counter] != '\0'))
	{
		if (a[l_counter] != b[l_counter]) l_success = false;
		++l_counter;
	}

	if ((a[l_counter] != '\0') || (b[l_counter] != '\0')) l_success = false;
	return l_success;
}

bool FileParser::get_Numb_MabObject_Fromcwmo(int* size)
{
	reset(); // First line is just a commnet
	bool l_success = false;

	// the next line after the first line is for the MabObject number
	if (!nextLine()) { printf("Can't move onto the next line // getNumbMabObject\n"); return l_success; }

	char l_line[50];
	l_success = getWord(l_line);
	if (!l_success) { printf("Can't get the word from cwom // getNumbMabObject\n"); return l_success; }

	if (compareString(l_line, "NUMBER"))
	{
		l_success = getInt(size);

		if(!l_success) { printf("Can't get the integer from cwom // getNumbMabObject\n"); return l_success; }
	}

	return l_success;
}

bool FileParser::get_OneMapObject_Info_Fromcwmo(int* index, char* address, int* type)
{
	bool l_success = false;
	if(!nextLine()) { printf("Can't move onto the next line // getonMapObjectInfo\n"); return l_success; }

	l_success = getInt(index);
	if (!l_success) { printf("Can't get the integer from cwom // getNumbMabObject\n"); return l_success; }

	char token = ' ';
	l_success = getChar(&token);
	if (!l_success) { printf("Can't get the character from cwom // getNumbMabObject\n"); return l_success; }

	if (token == 'A')
	{
		l_success = getWord(address);
		if (!l_success) { printf("Can't get the word from cwom // getNumbMabObject\n"); return l_success; }
	}

	l_success = getInt(type);
	if (!l_success) { printf("Can't get the integer from cwom // getNumbMabObject\n"); return l_success; }

	return l_success;
}

bool FileParser::get_SlopeInfo_Fromcwmo(int* dy1, int* dy2)
{
	bool l_success = false;
	
	l_success = getInt(dy1);
	if (!l_success) { printf("Can't get the integer from cwom // getSlopeCoord\n"); return l_success; }

	l_success = getInt(dy2);
	if (!l_success) { printf("Can't get the integer from cwom // getSlopeCoord\n"); return l_success; }

	return l_success;
}

bool FileParser::getRowFromcwm(int* row) // extract a row from the file. return -1 if something goes wrong
{
	reset(); // first character is row

	bool l_success = false;
	
	l_success = getInt(row);

	if (!l_success) { printf("Cannot get integer from cwb file\n"); return l_success; }

	return l_success;
} 

bool FileParser::getColFromcwm(int* col) // extract a col from the file. return -1 if something goes wrong
{
	reset(); // first character is row
	bool l_success = false;

	// the next line after the first line is for the column number
	if (!nextLine()) { printf("Can't move onto the next line // getCol\n"); return l_success; }

	l_success = getInt(col);

	if (!l_success) { printf("Cannot get integer from cwb file\n"); return l_success; }

	return l_success;
}

bool FileParser::getVecFromcwm(std::vector<std::vector<int>>& vec)
{
	int row{ 0 }, col{ 0 };
	bool l_success = true;

	l_success = getRowFromcwm(&row);
	if (!l_success) { printf("Cannot get integer from cwb file\n"); return l_success; }

	l_success = getColFromcwm(&col);
	if (!l_success) { printf("Cannot get integer from cwb file\n"); return l_success; }

	// after getting col, we can go to the vector data with nextline
	if (!nextLine()) { printf("Can't move onto the next line // getVec\n"); return l_success; }

	std::vector<std::vector<int>> temp(row, std::vector<int>(col));

	for(unsigned int i = 0; i < row; ++i)
		for (unsigned int j = 0; j < col; ++j)
		{
			l_success = getInt(&temp[i][j]);
			if (!l_success) { printf("Cannot get integer from cwb file\n"); return l_success; }
		}

	vec = temp;

	return l_success;
}

bool FileParser::getVecFromcwm(std::vector<std::vector<int>>& vec, int& row, int& col)
{
	reset();
	bool l_success = false;

	// after goint to next line twice, you can meet vector data
	if (!nextLine()) { printf("Can't move onto the next line // getVec\n"); return l_success; }
	if (!nextLine()) { printf("Can't move onto the next line // getVec\n"); return l_success; }

	std::vector<std::vector<int>> temp(row, std::vector<int>(col));

	for (unsigned int i = 0; i < row; ++i)
		for (unsigned int j = 0; j < col; ++j)
		{
			l_success = getInt(&temp[i][j]);
			if (!l_success) { printf("Cannot get integer from cwb file // getVec\n"); return l_success; }
		}

	vec = temp;

	return l_success;
}

bool FileParser::get_Numb_RankTable_Fromcwrt(int* size)
{
	reset();
	bool l_success = false;

	// after goint to next line twice, you can meet the number data
	if (!nextLine()) { printf("Can't move onto the next line // get_Numb_RankTable_Fromcwrt\n"); return l_success; }
	if (!nextLine()) { printf("Can't move onto the next line // get_Numb_RankTable_Fromcwrt\n"); return l_success; }

	char l_line[50];
	l_success = getWord(l_line);
	if (!l_success) { printf("Can't get the word from cwom // get_Numb_RankTable_Fromcwrt\n"); return l_success; }

	if (compareString(l_line, "NUMBER"))
	{
		l_success = getInt(size);

		if (!l_success) { printf("Can't get the integer from cwom // get_Numb_RankTable_Fromcwrt\n"); return l_success; }
	}
	else
	{
		l_success = false;
		printf("The cwrt file doesn't have a right format // NUMBER part // get_Numb_RankTable_Fromcwrt\n");
		return l_success;
	}

	return l_success;
}

bool FileParser::get_Rank_Number_Fromcwrt(int* number)
{
	bool l_success = false;

	// When you try to get the number of rank, you should go to the nextline
	if (!nextLine()) { printf("Can't move onto the next line // get_Rank_Number_Fromcwrt\n"); return l_success; }

	l_success = getInt(number);

	if (!l_success) { printf("Cannot get integer from cwrt file\n"); return l_success; }

	return l_success;
}

bool FileParser::get_Rank_Name_Fromcwrt(std::string* name)
{
	bool l_success = false;

	char l_line[50];
	l_success = getWord(l_line);
	if (!l_success) { printf("Can't get the word from cwrt // get_Rank_Name_Fromcwrt\n"); return l_success; }

	char* cursor = l_line;

	while (*cursor != '\0')
	{
		// Space Character Translation
		if (*cursor == '|')
			*cursor = ' ';

		++cursor;
	}

	*name = std::string(l_line);

	return l_success;
}

bool FileParser::get_Rank_Score_Fromcwrt(int* score)
{
	bool l_success = false;

	l_success = getInt(score);

	if (!l_success) { printf("Cannot get integer from cwrt file\n"); return l_success; }

	return l_success;
}

bool FileParser::get_Rank_Thought_Fromcwrt(std::string* thought)
{
	bool l_success = false;

	char l_line[200];
	l_success = getWord(l_line);
	if (!l_success) { printf("Can't get the word from cwrt // get_Rank_Thought_Fromcwrt\n"); return l_success; }

	char* cursor = l_line;

	while (*cursor != '\0')
	{
		// Space Character Translation
		if (*cursor == '|')
			*cursor = ' ';

		++cursor;
	}

	*thought = std::string(l_line);

	return l_success;
}