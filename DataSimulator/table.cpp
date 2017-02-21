#include "table.h"


meta::table::~table()
{
}

std::wostream & meta::operator<<(std::wostream & stream, const meta::table & table_)
{
	stream
		<< "\t" << table_.table_name_
		<< endl;
	std::for_each(std::begin(table_.columns_), std::end(table_.columns_), [&](auto column_)
	{
		stream << column_;
	});
	return stream;
}
