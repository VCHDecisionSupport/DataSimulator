#include "bc_meta_factory.h"

odbc::bc_meta_factory::bc_meta_factory(std::wstring dsn_name)
{
	odbc_connection_ = odbc::bc_odbc_connection(dsn_name);
	odbc_connection_.connect();
}

odbc::bc_meta_factory::~bc_meta_factory()
{
	odbc_connection_.~bc_odbc_connection();
}
