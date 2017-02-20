#pragma once
#include "SqlTableInfo.h"
#include "odbc_connection.h"


namespace unit_test
{
	using namespace odbc;
	void SqlTableInfo_()
	{
		SqlTableInfo x;
		x.ExecuteCommand();
		x.PopulateColumnInfo();
	}

	void OdbcConnection_()
	{
		odbc_connection conn;
		conn.connect();
		conn.connect();
	}

	void sql_query()
	{
		odbc_connection conn;
		conn.connect();
		vector<vector<wstring>> data = conn.execute_sql_query(wstring(L"SELECT * FROM master.sys.tables;"));
		cout << "rows recieved: " << sizeof(data) << endl;
		wcout << "first data point: " << data.at(0).at(0) << endl;
		for (auto row : data)
		{
			cout << "number of columns : " << sizeof(row) << endl;
			for (auto dpt : row)
			{
				wcout << dpt << endl;
			}
		}

	}
	void meta_data()
	{
		odbc_connection conn;
		conn.connect();
		wstring database_name = L"WideWorldImporterDW";
		//meta::schema schema = conn.get_meta_schema(database_name);

		cout << "complete" << endl;

	}
}