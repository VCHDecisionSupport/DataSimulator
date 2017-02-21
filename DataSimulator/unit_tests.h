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
		vector<vector<wstring>> data = conn.execute_sql_query(wstring(L"SELECT * FROM CommunityMart.sys.tables;"));
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
	void schema_builder()
	{
		meta::column c1(L"col1");
		meta::column c2(L"col2");

		std::unique_ptr<meta::column> cPtr = std::make_unique<meta::column>(L"col1_ptr");
		std::vector<std::unique_ptr<meta::column>> table_;
		table_.push_back(std::move(cPtr));
		std::vector<std::vector<std::unique_ptr<meta::column>>> tables_;
		tables_.push_back(std::move(table_));
	}

	struct col
	{
		wstring col_name;
		col(wstring col_name) : col_name(col_name) {}
		~col() {}
	};

	struct tab
	{
		wstring tab_name;
		vector<unique_ptr<col>> cols;
		tab(wstring tab_name, vector<unique_ptr<col>> &cols) : tab_name(tab_name), cols(std::move(cols)) {}
		~tab() {}
	};

	struct sch
	{
		wstring sch_name;
		vector<unique_ptr<tab>> tabs;
		sch(wstring sch_name, vector<unique_ptr<tab>> tabs) : sch_name(sch_name), tabs(std::move(tabs)) {}
		~sch() {}
	};

	void schema_class_builder()
	{
		col cObj(L"column_name");
		std::unique_ptr<col> cPtr = std::make_unique<col>(L"col1_ptr");
		std::vector<std::unique_ptr<col>> cPtrVec;
		cPtrVec.push_back(move(cPtr));

		wstring tab_name(L"table_name");
		tab tObj(tab_name, std::move(cPtrVec));
		tab tObj2(tab_name, cPtrVec);
		std::unique_ptr<tab> tPtr = make_unique<tab>(tab_name, cPtrVec);
		std::vector<std::unique_ptr<tab>> tPtrVec;
		tPtrVec.push_back(move(tPtr));

		wstring sch_name = L"schema_name";
		sch sObj(sch_name, move(tPtrVec));
	}
	void meta_data()
	{
		odbc_connection conn;
		conn.connect();
		//wstring database_name = L"WideWorldImporterDW";
		//vector<vector<wstring>> data = conn.execute_sql_query(wstring(L"SELECT * FROM CommunityMart.sys.tables;"));
		wstring database_name = L"CommunityMart";
		conn.get_meta_schema(database_name);

		cout << "complete" << endl;

	}

}