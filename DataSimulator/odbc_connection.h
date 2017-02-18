#pragma once
#include"stdafx.h"
#include"data_source_connection.h"
#include "ColumnInfo.h"

namespace odbc {
	using namespace std;


	//#include"data_source_connection.h"
	const size_t DSN_STRING_MAX_LENGTH = 1000; /* max characters to store the DSN connection string */

	//struct SqlDataPoint
	//{
	//	SQLSMALLINT column_index;
	//	WCHAR *wcData;             /* display buffer   */
	//	SQLLEN wcSize;                 /* size or null     */
	//	struct SqlDataPoint  *sNext;                 /* linked list      */
	//};


	// rejigged version of SqlTableInfo ODBC database sample 
	class odbc_connection : public data_source_connection
	{
		//L"DSN=DevOdbcSqlServer;UID=vch\\gcrowell;Trusted_Connection=Yes;"
		SQLWCHAR* dsnName = (SQLWCHAR*)"SysDsnWwi";
		SQLWCHAR* userID = (SQLWCHAR*)"SysDsnWwi";
		SQLWCHAR* passwd = (SQLWCHAR*)"SysDsnWwi";
		SQLSMALLINT _result_column_count = 0; /* number of columns returned by sql statement */
		SQLHENV _environment_handle = nullptr; /* SQLHANDLE SQLHENV sql handle enviroment */
		SQLHDBC _input_handle = nullptr; /* SQLHANDLE SQLHDBC sql handle database connection */
		SQLHSTMT _statement_handle = nullptr; /* SQLHANDLE SQLHSTMT sql handle statement */

		std::vector<ColumnInfo> *_column_infos = nullptr;


		void PopulateColumnInfo();
		void InitializeResults(SqlDataPoint** this_data_row);

	public:
		odbc_connection();
		vector<vector<wstring>> execute_sql_query(wstring sql_query) override;
		
		bool connect();
		void execute_sql(wstring stmt);
		~odbc_connection();
	};


	// references
	// ODBC database sample https://code.msdn.microsoft.com/ODBC-sample-191624ae
}