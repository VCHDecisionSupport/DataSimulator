#pragma once
#include "SqlTableInfo.h"
#include "bc_odbc_connection.h"
#include "sql_server_meta_factory.h"
#include "column_value_histogram.h"
#include "abc_odbc_object.h"

namespace unit_test
{
	//const std::wstring database_name = L"CommunityMart";
	const std::wstring database_name = L"WideWorldImportersDW";
	//const std::wstring dsn_name_in(L"DSN=DenodoODBC;");
	//const std::wstring dsn_name_in(L"DSN=DevOdbcSqlServer;");
	const std::wstring dsn_name_in(L"DSN=SysDsnWwi;");

	using namespace odbc;
	void SqlTableInfo_()
	{
		SqlTableInfo x;
		x.ExecuteCommand();
		x.PopulateColumnInfo();
	}

	void OdbcConnection_()
	{
		bc_odbc_connection conn(dsn_name_in);
		conn.connect();
		conn.connect();
	}

	void sql_query()
	{
		bc_odbc_connection conn(dsn_name_in);
		conn.connect();
		std::vector<std::vector<std::wstring>> data = conn.execute_sql_query(std::wstring(L"SELECT * FROM sys.tables;"));
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
		bc_odbc_connection conn(dsn_name_in);
		conn.connect();
		////std::wstring database_name = L"WideWorldImportersDW";
		//std::wstring database_name = L"CommunityMart";
		conn.get_meta_schema(database_name);
		std::cout << "complete" << std::endl;
	}

	void meta_output()
	{
		//std::wstring dsn_name_in(L"DSN=DevOdbcSqlServer;");
		bc_odbc_connection conn(dsn_name_in);
		conn.connect();
		//std::wstring database_name = L"WideWorldImportersDW";
		//std::wstring database_name = L"CommunityMart";
		meta::schema schema_ = conn.get_meta_schema(database_name);
		std::wcout << schema_ << std::endl;
	}
	void denodo_connect_query()
	{
		std::wstring dsn_name_in(L"DSN=DenodoODBC;");
		bc_odbc_connection conn(dsn_name_in);
		conn.connect();
		conn.execute_sql_query(L"SELECT * FROM adtcmart_admission_discharge_fact;");
	}
	void ms_source()
	{
		//std::wstring dsn_name_in(L"DSN=DevOdbcSqlServer;");
		//std::wstring dsn_name_in(L"DSN=SysDsnWwi;");
		sql_server_meta_factory ms(dsn_name_in);
		//ms.generate_meta_object(L"CommunityMart");
		std::shared_ptr<meta::database> database_ = ms.generate_meta_object(database_name);
		std::wcout << "database shared_ptr use_count: " << database_.use_count() << std::endl;
		std::for_each(database_->begin(), database_->end(), [&](std::shared_ptr<meta::schema> schema_ptr)
		{
			std::wcout << L"schema_name: " << schema_ptr->schema_name() << std::endl;
			std::wcout << L"database_name: " << schema_ptr->get_parent().lock()->database_name() << std::endl;
		});
	}
	void value_histogram()
	{
		meta::histogram test_hist;
		test_hist.push_back(std::make_unique<meta::histogram_entry>(std::wstring(L"most frequent"), 100, 0.5, 0.5));
		test_hist.push_back(std::make_unique<meta::histogram_entry>(std::wstring(L"2nd most frequent"), 100, 0.3, 0.8));
		test_hist.push_back(std::make_unique<meta::histogram_entry>(std::wstring(L"least most frequent"), 100, 0.2, 1.0));
		meta::column_value_histogram value_histogram(std::move(test_hist));
		std::wstring col_value = value_histogram.rand_column_value();
		std::wcout << "returned from histogram object: " << col_value << std::endl;
	}
	void meta_base_class()
	{
		meta::db db_;
	}
	void uinit_weak_ptr()
	{
		std::weak_ptr<std::wstring> wPtr;
		
		std::wcout << "expired " << wPtr.expired() << std::endl; // 1 OK
		std::wcout << "use count " << wPtr.use_count() << std::endl; // 0 OK
		//wPtr.lock(); // OK
		//std::wcout << *wPtr.lock().get() << std::endl; // ERROR.
	}
	//void signals()
	//{
	//	boost::signals2::signal<void()> s;
	//	s.connect([]() {std::cout << "signal fired" << std::endl; });
	//	s();
	//}
}