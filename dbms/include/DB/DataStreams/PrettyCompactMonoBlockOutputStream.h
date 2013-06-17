#pragma once

#include <DB/DataStreams/PrettyBlockOutputStream.h>


namespace DB
{

/** Тоже самое, что и PrettyCompactBlockOutputStream, но выводит все max_rows (или меньше,
 * 	если результат содержит меньшее число строк) одним блоком с одной шапкой.
  */
class PrettyCompactMonoBlockOutputStream : public PrettyBlockOutputStream
{
public:
	PrettyCompactMonoBlockOutputStream(WriteBuffer & ostr_, bool no_escapes_ = false, size_t max_rows_ = PRETTY_FORMAT_DEFAULT_MAX_ROWS)
		: PrettyBlockOutputStream(ostr_, no_escapes_, max_rows_) {}

	void write(const Block & block);
	void writeSuffix();
	
private:
	typedef std::vector<Block> Blocks_t;
	
	Blocks_t blocks;
};

}
