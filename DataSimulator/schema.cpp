#include "schema.h"


meta::schema::~schema()
{
}

std::wostream & meta::operator<<(std::wostream & stream, const meta::schema & schema_)
{
	stream
		<< schema_.schema_name_
		<< endl;
	//std::copy(begin(schema_.tables_), end(schema_.tables_), out_table);
	std::for_each(schema_.begin(), schema_.end(), [&](auto table_)
	{
		stream << *table_;
	});
	return stream;
}
