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
		std::cout << "rows recieved: " << sizeof(data) << endl;
		std::wcout << "first data point: " << data.at(0).at(0) << endl;
		for (auto row : data)
		{
			cout << "number of columns : " << sizeof(row) << endl;
			for (auto dpt : row)
			{
				wcout << dpt << endl;
			}
		}

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
		vector<shared_ptr<col>> cols;
		tab(wstring tab_name, vector<shared_ptr<col>> &cols) : tab_name(tab_name), cols(std::move(cols)) {}
		~tab() {}
	};

	struct sch
	{
		wstring sch_name;
		vector<shared_ptr<tab>> tabs;
		sch(wstring sch_name, vector<shared_ptr<tab>> tabs) : sch_name(sch_name), tabs(std::move(tabs)) {}
		~sch() {}
	};

	//void schema_class_builder()
	//{
	//	col cObj(L"column_name");
	//	std::shared_ptr<col> cPtr = std::make_shared<col>(L"col1_ptr");
	//	std::vector<std::shared_ptr<col>> cPtrVec;
	//	cPtrVec.push_back(move(cPtr));

	//	wstring tab_name(L"table_name");
	//	tab tObj(tab_name, std::move(cPtrVec));
	//	tab tObj2(tab_name, cPtrVec);
	//	std::shared_ptr<tab> tPtr = make_shared<tab>(tab_name, cPtrVec);
	//	std::vector<std::shared_ptr<tab>> tPtrVec;
	//	tPtrVec.push_back(move(tPtr));

	//	wstring sch_name = L"schema_name";
	//	sch sObj(sch_name, move(tPtrVec));
	//}
	void meta_data()
	{
		odbc_connection conn;
		conn.connect();
		wstring database_name = L"WideWorldImportersDW";
		//wstring database_name = L"CommunityMart";
		conn.get_meta_schema(database_name);
		std::cout << "complete" << endl;
	}

	void meta_output()
	{
		odbc_connection conn;
		conn.connect();
		wstring database_name = L"WideWorldImportersDW";
		//wstring database_name = L"CommunityMart";
		meta::schema schema_ = conn.get_meta_schema(database_name);
		wcout << schema_ << endl;

	}
	
}