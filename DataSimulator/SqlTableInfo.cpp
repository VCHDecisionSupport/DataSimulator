#include "stdafx.h"
#include "SqlTableInfo.h"

SqlTableInfo::SqlTableInfo()
{
	/* this matches a preexisting 64 bit System DSN */
	std::wstring conn_str(L"DSN=DevOdbcSqlServer;UID=vch\\gcrowell;Trusted_Connection=Yes;"); /* dsn connection string (pop window magically happens) */
	const size_t DSN_STRING_MAX_LENGTH = 1000; /* max characters to store the DSN connection string */
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
		std::wcout << "connection established:\n\tinstring:  " << conn_str << std::endl;
		std::wcout << "\toutstring: " << std::wstring(dsn_connection_string_out) << std::endl;
	}
	else
	{
		std::cout << "connection failed" << std::endl;
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
}

void SqlTableInfo::ExecuteCommand()
{
	wchar_t* sql_statement_str = L"SELECT * FROM DSDW.Dim.ReferralReason;"; /* sql statement string */
	SQLSMALLINT result_column_count; /* number of columns returned from execution of sql statement */

	SQLAllocHandle(SQL_HANDLE_STMT, _input_handle, &_statement_handle);
	SQLRETURN RetCode = SQLExecDirect(_statement_handle, sql_statement_str, SQL_NTS);

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
		std::cout << "result_column_count: " << result_column_count << std::endl;
		if (result_column_count > 0)
		{
			//_statement_handle = _statement_handle;
			_result_column_count = result_column_count;
			PopulateColumnInfo();
		}
		else
		{
			SQLLEN cRowCount;
			SQLRowCount(_statement_handle, &cRowCount);
			std::cout << "cRowCount: " << cRowCount << std::endl;

			if (cRowCount >= 0)
			{
				wprintf(L"%Id %s affected\n",
					cRowCount,
					cRowCount == 1 ? L"row" : L"rows");
			}
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

void SqlTableInfo::PopulateColumnInfo()
{
	std::cout << "PopulateColumnInfo (" << _result_column_count << " columns)" << std::endl;

	WCHAR wcColumnName[100];
	WCHAR wcColumnType[100];
	SQLLEN uiOctetLength;
	SQLLEN uiPrecision;
	SQLLEN uiScale;
	SQLLEN uiDisplayWidth;
	//SQLSMALLINT nullable;           // whether column can have NULL value
	this->_column_infos = new std::vector<ColumnInfo>(_result_column_count);
	for (SQLSMALLINT column_index = 1; column_index <= _result_column_count; ++column_index)
	{
		ColumnInfo column_info = ColumnInfo();
		column_info.column_number = column_index;

		SQLColAttribute(_statement_handle, column_index, SQL_DESC_NAME, wcColumnName, sizeof(wcColumnName), nullptr, nullptr);
		std::wstring column_name(wcColumnName);
		//std::cout << L"column_name: " << column_name.c_str() << " (" << column_index << ")" << std::endl;
		column_info.column_name = column_name;

		SQLColAttribute(_statement_handle, column_index, SQL_DESC_TYPE_NAME, wcColumnType, sizeof(wcColumnType), nullptr, nullptr);
		std::wstring column_type(wcColumnType);
		//std::cout << L"\tcolumn_type: " << column_type.c_str() << std::endl;
		column_info.column_type = column_type;

		SQLColAttribute(_statement_handle, column_index, SQL_DESC_OCTET_LENGTH, nullptr, NULL, nullptr, &uiOctetLength);
		signed long long column_octet_length(uiOctetLength);
		//std::cout << L"\tcolumn_octet_length: " << uiOctetLength << std::endl;
		column_info.column_octet_length = column_octet_length;

		SQLColAttribute(_statement_handle, column_index, SQL_DESC_PRECISION, nullptr, NULL, nullptr, &uiPrecision);
		signed long long column_precision(uiPrecision);
		//std::cout << L"\tcolumn_precision: " << uiPrecision << std::endl;
		column_info.column_precision = column_precision;

		SQLColAttribute(_statement_handle, column_index, SQL_DESC_SCALE, nullptr, NULL, nullptr, &uiScale);
		signed long long column_scale(uiScale);
		//std::cout << L"\tcolumn_scale: " << uiScale << std::endl;
		column_info.column_scale = column_scale;

		SQLColAttribute(_statement_handle, column_index, SQL_DESC_DISPLAY_SIZE, nullptr, NULL, nullptr, &uiDisplayWidth);
		signed long long column_display_width(uiDisplayWidth);
		//std::cout << L"\tcolumn_scale: " << uiScale << std::endl;
		column_info.column_display_width = column_display_width;

		this->_column_infos->at(column_index - 1) = column_info;
	}
}

void SqlTableInfo::InitializeResults(SqlDataPoint** this_data_row)
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

void SqlTableInfo::ProcessResults()
{
	SqlDataPoint* this_data_point = nullptr;
	SqlDataPoint* first_data_point = nullptr;
	SQLRETURN sql_return = 0;
	bool data_returned = true;
	uint32_t this_row_number = 0;
	InitializeResults(&first_data_point);

	do {

		sql_return = SQLFetch(_statement_handle);
		this_row_number++;
		//std::cout << this_row_number << std::endl;
		if (sql_return == SQL_NO_DATA_FOUND)
		{
			data_returned = false;
			std::cout << "data_returned = false" << std::endl;
		}
		else
		{
			data_returned = true;
			//std::cout << "data_returned = true" << std::endl;
			for (this_data_point = first_data_point; this_data_point; this_data_point = this_data_point->sNext)
			{
				//std::cout << this->_column_infos->at(this_data_point->column_index - 1).column_name << ": ";
				if (this_data_point->wcSize != SQL_NULL_DATA)
				{
					//std::cout << this_data_point->wcData << std::endl;
				}
			}

		}
	} while (!data_returned && this_row_number < 10000);

	while (first_data_point)
	{
		this_data_point = first_data_point->sNext;
		free(first_data_point->wcData);
		free(first_data_point);
		first_data_point = this_data_point;
	}

}

std::wostream& operator<<(std::wostream& os, const SqlTableInfo& obj)
{
	for (auto column_info : *obj._column_infos)
	{
		os << column_info << std::endl;
	}
	return os;
}

SqlTableInfo::~SqlTableInfo()
{
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
	delete[] _column_infos;
}


