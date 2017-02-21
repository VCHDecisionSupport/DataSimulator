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
		std::vector<std::vector<std::wstring>> data = conn.execute_sql_query(std::wstring(L"SELECT * FROM CommunityMart.sys.tables;"));
		std::cout << "rows recieved: " << sizeof(data) << std::endl;
		std::wcout << "first data point: " << data.at(0).at(0) << std::endl;
		for (auto row : data)
		{
			std::cout << "number of columns : " << sizeof(row) << std::endl;
			for (auto dpt : row)
			{
				std::wcout << dpt << std::endl;
			}
		}
	}

	struct col
	{
		std::wstring col_name;
		col(std::wstring col_name) : col_name(col_name) {}
		~col() {}
	};

	struct tab
	{
		std::wstring tab_name;
		std::vector<std::shared_ptr<col>> cols;
		tab(std::wstring tab_name, std::vector<std::shared_ptr<col>> &cols) : tab_name(tab_name), cols(std::move(cols)) {}
		~tab() {}
	};

	struct sch
	{
		std::wstring sch_name;
		std::vector<std::shared_ptr<tab>> tabs;
		sch(std::wstring sch_name, std::vector<std::shared_ptr<tab>> tabs) : sch_name(sch_name), tabs(std::move(tabs)) {}
		~sch() {}
	};

	//void schema_class_builder()
	//{
	//	col cObj(L"column_name");
	//	std::shared_ptr<col> cPtr = std::make_shared<col>(L"col1_ptr");
	//	std::vector<std::shared_ptr<col>> cPtrVec;
	//	cPtrVec.push_back(move(cPtr));

	//std::wstring tab_name(L"table_name");
	//	tab tObj(tab_name, std::move(cPtrVec));
	//	tab tObj2(tab_name, cPtrVec);
	//	std::shared_ptr<tab> tPtr = std::make_shared<tab>(tab_name, cPtrVec);
	//	std::vector<std::shared_ptr<tab>> tPtrVec;
	//	tPtrVec.push_back(move(tPtr));

	//std::wstring sch_name = L"schema_name";
	//	sch sObj(sch_name, move(tPtrVec));
	//}
	void meta_data()
	{
		odbc_connection conn;
		conn.connect();
		//std::wstring database_name = L"WideWorldImportersDW";
		std::wstring database_name = L"CommunityMart";
		conn.get_meta_schema(database_name);
		std::cout << "complete" << std::endl;
	}

	void meta_output()
	{
		odbc_connection conn;
		conn.connect();
		//std::wstring database_name = L"WideWorldImportersDW";
		std::wstring database_name = L"CommunityMart";
		meta::schema schema_ = conn.get_meta_schema(database_name);
		std::wcout << schema_ << std::endl;
	}

}