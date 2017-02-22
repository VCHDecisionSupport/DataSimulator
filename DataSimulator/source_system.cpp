#include "source_system.h"

source_system::source_system(std::wstring dsn_name)
{
	odbc_connection_ = odbc::odbc_connection(dsn_name);
	odbc_connection_.connect();
}

source_system::~source_system()
{
	odbc_connection_.~odbc_connection();
}
