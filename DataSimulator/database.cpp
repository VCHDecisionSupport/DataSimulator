#include "database.h"
meta::database::~database()
{
}

std::wostream & meta::operator<<(std::wostream & stream, const meta::database & database_)
{
	stream
		<< database_.database_name_
		<< std::endl;
	std::for_each(database_.begin(), database_.end(), [&](auto schema_)
	{
		stream << *schema_;
	});
	return stream;
}
