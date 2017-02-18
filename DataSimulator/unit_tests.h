#pragma once
#include "SqlTableInfo.h"
#include "odbc_connection.h"


namespace unit_test
{
	void SqlTableInfo_()
	{
		SqlTableInfo x;
		x.ExecuteCommand();
		x.PopulateColumnInfo();
	}

	void OdbcConnection_()
	{
		odbc_connection conn;
		conn.just_do_it();
		conn.just_do_it();
	}

	void sql_query()
	{
		odbc_connection conn;
		conn.just_do_it();
		conn.execute_sql(wstring(L"SELECT * FROM master.sys.tables;"));
		
	}
}