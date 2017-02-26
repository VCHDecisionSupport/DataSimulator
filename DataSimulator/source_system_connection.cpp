#include "source_system_connection.h"

source_system_connection::source_system_connection(std::wstring dsn_name)
{
	odbc_connection_ = odbc::odbc_connection(dsn_name);
	odbc_connection_.connect();
}

source_system_connection::~source_system_connection()
{
	odbc_connection_.~odbc_connection();
}
