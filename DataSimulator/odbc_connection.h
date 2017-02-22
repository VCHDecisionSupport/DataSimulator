#pragma once
#include"stdafx.h"
#include"data_source_connection.h"
#include "schema_builder.h"
#include "ColumnInfo.h"

namespace odbc {
	const size_t DSN_STRING_MAX_LENGTH = 1000; /* max characters to store the DSN connection string */

	// rejigged version of SqlTableInfo ODBC database sample 
	class odbc_connection : public data_source_connection
	{
		// ODBC data source name passed into SQLDriverConnect
		std::wstring dsn_name_in_;
		// ODBC data source name returned from SQLDriverConnect
		std::wstring dsn_name_out_;
		
		SQLSMALLINT _result_column_count = 0; /* number of columns returned by sql statement */
		SQLHENV _environment_handle = nullptr; /* SQLHANDLE SQLHENV sql handle enviroment */
		SQLHDBC _input_handle = nullptr; /* SQLHANDLE SQLHDBC sql handle database connection */
		SQLHSTMT _statement_handle = nullptr; /* SQLHANDLE SQLHSTMT sql handle statement */
		wchar_t* sql_statement_str = nullptr;

		std::vector<ColumnInfo> *_column_infos = nullptr;
		std::vector<std::vector<std::wstring>> rows_of_columns_of_data_;

		void PopulateColumnInfo();
		void ProcessResults();
		void InitializeResults(SqlDataPoint** this_data_row);

	public:
		odbc_connection();
		odbc_connection(std::wstring dsn_name_in);
		std::vector<std::vector<std::wstring>> execute_sql_query(std::wstring sql_query) override;
		meta::schema get_meta_schema(std::wstring database_name);
		bool connect();
		void execute_sql(std::wstring stmt);
		~odbc_connection();
	};


	// references
	// ODBC database sample https://code.msdn.microsoft.com/ODBC-sample-191624ae
}