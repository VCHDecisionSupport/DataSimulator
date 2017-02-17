#pragma once
#include "SqlTableInfo.h"
#include "OdbcConnection.h"


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
		OdbcConnection conn;
		conn.just_do_it();
		conn.just_do_it();
	}
}