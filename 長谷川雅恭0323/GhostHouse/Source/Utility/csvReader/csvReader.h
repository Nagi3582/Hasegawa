#ifndef _CSV_READER_H_
#define _CSV_READER_H_
#include <string>
#include <vector>
#include <gslib.h>

const int STAGE_ID = 1;
const int RESOURCE_ID = 2;
const int RESOURCE_NAME = 3;
const int OCTREE_NAME = 4;
const int SKELETON_ID = 4;
const int ANIMATION_ID = 5;

class csvReader
{
public:
	csvReader();

	void Load(std::string fileName);

	//”’l‚ğæ“¾(int)
	int GetI(int line, int row);

	//”’l‚ğæ“¾(float)
	float GetF(int line, int row);

	//•¶š—ñ‚ğæ“¾
	const std::string& GetS(int line, int row);

	int GetRowSize(int line);
	int GetLineSize();

private:
	using Row = std::vector<std::string>;
	using Matrix = std::vector<Row>;

private:
	Matrix m_Matrix;


};

#endif // !_CSV_READER_H_
