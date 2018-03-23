#include "csvReader.h"
#include <fstream>
#include <sstream>
#ifdef DEBUG
#include <iostream>

#endif // DEBUG


csvReader::csvReader()
{
}

void csvReader::Load(std::string fileName)
{
#ifdef DEBUG
	std::cout << "csv読み込み" << fileName << std::endl;

#endif // DEBUG

	std::ifstream l_File(fileName);
	if (!l_File)throw std::runtime_error("csvファイルが開けませんでした");


	std::string l_Line;
	Matrix l_Matrix;

	while (std::getline(l_File, l_Line))
	{
		std::stringstream l_SStream(l_Line);
		std::string l_Value;
		Row l_Row;
		while (std::getline(l_SStream, l_Value, ','))
		{
			l_Row.push_back(l_Value);
		}
		l_Matrix.push_back(l_Row);
	}
	m_Matrix = l_Matrix;
}

int csvReader::GetI(int line, int row)
{
	return std::stoi(GetS(line, row));
}

float csvReader::GetF(int line, int row)
{
	return std::stof(m_Matrix[line][row]);
}

const std::string& csvReader::GetS(int line, int row)
{
	return m_Matrix[line][row];
}

int csvReader::GetRowSize(int line)
{
	return m_Matrix[line].size();
}

int csvReader::GetLineSize()
{
	return m_Matrix.size();
}
