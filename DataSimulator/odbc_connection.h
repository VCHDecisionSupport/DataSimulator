#pragma once
#include"stdafx.h"
#include "ColumnInfo.h"
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
class odbc_connection //: public data_source_connection
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


	void PopulateColumnInfo()
	{
		using namespace std;
		std::cout << "PopulateColumnInfo (" << _result_column_count << " columns)" << std::endl;

		WCHAR wcColumnName[100];
		WCHAR wcColumnType[100];
		SQLLEN uiOctetLength;
		SQLLEN uiPrecision;
		SQLLEN uiScale;
		SQLLEN uiDisplayWidth;
		SQLSMALLINT nullable;           // whether column can have NULL value
		this->_column_infos = new std::vector<ColumnInfo>(_result_column_count);
		for (SQLSMALLINT column_index = 1; column_index <= _result_column_count; ++column_index)
		{
			ColumnInfo column_info = ColumnInfo();
			column_info.column_number = column_index;

			SQLColAttribute(_statement_handle, column_index, SQL_DESC_NAME, wcColumnName, sizeof(wcColumnName), nullptr, nullptr);
			std::wstring column_name(wcColumnName);
			//std::wcout << L"column_name: " << column_name.c_str() << " (" << column_index << ")" << std::endl;
			column_info.column_name = column_name;

			SQLColAttribute(_statement_handle, column_index, SQL_DESC_TYPE_NAME, wcColumnType, sizeof(wcColumnType), nullptr, nullptr);
			std::wstring column_type(wcColumnType);
			//std::wcout << L"\tcolumn_type: " << column_type.c_str() << std::endl;
			column_info.column_type = column_type;

			SQLColAttribute(_statement_handle, column_index, SQL_DESC_OCTET_LENGTH, nullptr, NULL, nullptr, &uiOctetLength);
			std::int32_t column_octet_length(uiOctetLength);
			//std::wcout << L"\tcolumn_octet_length: " << uiOctetLength << std::endl;
			column_info.column_octet_length = column_octet_length;

			SQLColAttribute(_statement_handle, column_index, SQL_DESC_PRECISION, nullptr, NULL, nullptr, &uiPrecision);
			std::int32_t column_precision(uiPrecision);
			//std::wcout << L"\tcolumn_precision: " << uiPrecision << std::endl;
			column_info.column_precision = column_precision;

			SQLColAttribute(_statement_handle, column_index, SQL_DESC_SCALE, nullptr, NULL, nullptr, &uiScale);
			std::int32_t column_scale(uiScale);
			//std::wcout << L"\tcolumn_scale: " << uiScale << std::endl;
			column_info.column_scale = column_scale;

			SQLColAttribute(_statement_handle, column_index, SQL_DESC_DISPLAY_SIZE, nullptr, NULL, nullptr, &uiDisplayWidth);
			std::int32_t column_display_width(uiDisplayWidth);
			//std::wcout << L"\tcolumn_scale: " << uiScale << std::endl;
			column_info.column_display_width = column_display_width;

			this->_column_infos->at(column_index - 1) = column_info;
		}
	}
	void InitializeResults(SqlDataPoint** this_data_row)
	{
		SqlDataPoint* this_data_point = nullptr;
		SqlDataPoint* prev_data_point = nullptr;
		for (SQLSMALLINT column_index = 1; column_index <= _result_column_count; ++column_index)
		{
			uint32_t display_width = this->_column_infos->at(column_index - 1).column_display_width;
			this_data_point = static_cast<SqlDataPoint*>(malloc(sizeof(SqlDataPoint)));
			this_data_point->column_index = column_index;
			this_data_point->wcData = static_cast<WCHAR*>(malloc((display_width + 1) * sizeof(WCHAR)));
			if (!(this_data_point->wcData))
			{
				fwprintf(stderr, L"Out of memory!\n");
				exit(-100);
			}

			if (column_index == 1)
				*this_data_row = this_data_point;
			else
				prev_data_point->sNext = this_data_point;
			prev_data_point = this_data_point;

			SQLBindCol(_statement_handle,
				column_index,
				SQL_C_TCHAR,
				(SQLPOINTER)this_data_point->wcData,
				(display_width + 1) * sizeof(WCHAR),
				&this_data_point->wcSize);

			this_data_point->sNext = nullptr;
		}

	}
	
public:
	odbc_connection();
	//void execute_odbc_statement(string stmt)
	//{

	//}
	

	//void generate_schema_model(vector<unique_ptr<table>> schema)
	//{

	//}
	bool connect();
	void execute_sql(wstring stmt);
	~odbc_connection();
};


// references
// ODBC database sample https://code.msdn.microsoft.com/ODBC-sample-191624ae
