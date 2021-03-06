#include "table.h"


meta::table::~table()
{
}

std::wostream & meta::operator<<(std::wostream & stream, const meta::table & table_)
{
	stream
		<< "\t" << table_.table_name_
		<< std::endl;
	//std::copy(begin(table_.columns_), end(table_.columns_), out_column);

	std::for_each(table_.begin(), table_.end(), [&](auto column_)
	{
		stream << *column_;
	});
	return stream;
}
