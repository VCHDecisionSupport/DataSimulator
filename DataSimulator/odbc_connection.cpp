#include "odbc_connection.h"

using namespace std;

inline void odbc_connection::PopulateColumnInfo()
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

inline void odbc_connection::InitializeResults(SqlDataPoint ** this_data_row)
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

odbc_connection::odbc_connection()
{
	/* this matches a preexisting 64 bit System DSN */
	//conn_str = wstring(L"DSN=DevOdbcSqlServer;UID=vch\\gcrowell;Trusted_Connection=Yes;"); /* dsn connection string (pop window magically happens) */

	//conn_str = L"DSN=DevOdbcSqlServer;UID=vch\\gcrowell;Trusted_Connection=Yes;";
}


bool odbc_connection::connect()
{
	// mutex with function
	std::mutex conn_mutex;
	// lock mutex before accessing shared resource
	std::lock_guard<std::mutex> lock(conn_mutex);
	if (this->_input_handle == nullptr)
	{
		cout << "init ODBC connection" << endl;
		//wstring conn_str = L"DSN=DevOdbcSqlServer;UID=vch\\gcrowell;Trusted_Connection=Yes;";
		wstring conn_str = L"DSN=SysDsnWwi;UID=user;Trusted_Connection=Yes;";
		SQLWCHAR    dsn_connection_string_out[DSN_STRING_MAX_LENGTH];
		SQLSMALLINT* dsn_string_length = nullptr;
		std::wstring dsn_connection_string(dsn_connection_string_out);



		SQLRETURN retcode;
		if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_environment_handle) == SQL_ERROR)
		{
			std::cout << "error connecting" << std::endl;
			exit(-1);
		}
		else
		{
			std::cout << "enviroment created" << std::endl;
		}
		// Register this as an application that expects 3.x behavior,
		// you must register something if you use AllocHandle
		SQLSetEnvAttr(_environment_handle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
		// Allocate a connection
		SQLAllocHandle(SQL_HANDLE_DBC, _environment_handle, &_input_handle);
		retcode = SQLDriverConnect(_input_handle, GetDesktopWindow(), (SQLWCHAR*)conn_str.c_str(), SQL_NTS, dsn_connection_string_out, DSN_STRING_MAX_LENGTH, dsn_string_length, SQL_DRIVER_COMPLETE);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			wcout << "connection established:\n\tinstring:  " << conn_str << endl;
			wcout << "\toutstring: " << wstring(dsn_connection_string_out) << endl;
		}
		else
		{
			cout << "connection failed" << endl;
			if (_input_handle)
			{
				SQLDisconnect(_input_handle);
				SQLFreeHandle(SQL_HANDLE_DBC, _input_handle);
			}

			if (_environment_handle)
			{
				SQLFreeHandle(SQL_HANDLE_ENV, _environment_handle);
			}
			return false;
		}
		return true;
	}
}

void odbc_connection::execute_sql(wstring stmt)
{
	wcout << "executing sql: " << endl << stmt << endl;
	wchar_t sql_statement_str[sizeof(stmt) + 1];
	lstrcpy(sql_statement_str, stmt.c_str());

	SQLAllocHandle(SQL_HANDLE_STMT, _input_handle, &_statement_handle);
	SQLRETURN RetCode = SQLExecDirect(_statement_handle, sql_statement_str, SQL_NTS);

	SQLSMALLINT result_column_count; /* number of columns returned from execution of sql statement */
	SQLLEN affected_row_count;

	switch (RetCode)
	{
	case SQL_SUCCESS_WITH_INFO:
	{
		std::cout << "HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, RetCode);" << std::endl;
		// fall through
	}
	case SQL_SUCCESS:
	{
		std::cout << "SQL_SUCCESS" << std::endl;
		SQLNumResultCols(_statement_handle, &result_column_count);
		if (result_column_count > 0)
		{
			_result_column_count = result_column_count;
			std::cout << "result_column_count: " << result_column_count << std::endl;
			//PopulateColumnInfo();
		}
		else
		{
			cout << "no columns returned from query" << endl;
		}
		SQLRowCount(_statement_handle, &affected_row_count);
		if (affected_row_count > 0)
		{
			std::cout << "affected_row_count: " << affected_row_count << std::endl;

			if (affected_row_count >= 0)
			{
				wprintf(L"%Id %s affected\n",
					affected_row_count,
					affected_row_count == 1 ? L"row" : L"rows");
			}
		}
		else
		{
			cout << "no rows affected by statement" << endl;
		}
		break;
	}
	case SQL_ERROR:
	{
		std::cout << "SQL_ERROR" << std::endl;
		//HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, RetCode);
		break;
	}
	default:
		fwprintf(stderr, L"Unexpected return code %hd!\n", RetCode);
	}
	//TODO: clean up memory allocations
}

odbc_connection::~odbc_connection()
{
	cout << "cleaning up ODBC connection" << endl;
	if (_statement_handle)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, _statement_handle);
	}

	if (_input_handle)
	{
		SQLDisconnect(_input_handle);
		SQLFreeHandle(SQL_HANDLE_DBC, _input_handle);
	}

	if (_environment_handle)
	{
		SQLFreeHandle(SQL_HANDLE_ENV, _environment_handle);
	}
}