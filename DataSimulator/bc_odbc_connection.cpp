#include "bc_odbc_connection.h"

inline void odbc::bc_odbc_connection::PopulateColumnInfo()
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

inline void odbc::bc_odbc_connection::InitializeResults(SqlDataPoint ** this_data_row)
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

inline void odbc::bc_odbc_connection::ProcessResults()
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
			//std::cout << "data_returned = false" << std::endl;
		}
		else
		{
			std::vector<std::wstring> columns_;
			data_returned = true;
			//std::cout << "data_returned = true" << std::endl;
			for (this_data_point = first_data_point; this_data_point; this_data_point = this_data_point->sNext)
			{
				//std::wcout << this->_column_infos->at(this_data_point->column_index - 1).column_name << ": ";
				if (this_data_point->wcSize == SQL_NULL_DATA)
				{
					columns_.push_back(L"SQL_NULL_DATA");
				}
				else
				{
					columns_.push_back(std::wstring(this_data_point->wcData));
					//std::wcout << this_data_point->wcData << std::endl;
					//std::wcout << *(end(columns_) - 1) << std::endl;
				}
			}
			rows_of_columns_of_data_.push_back(columns_);
			//std::cout << "row complete" << std::endl;
		}
		//break;
	} while (data_returned && this_row_number < 10000);

	while (first_data_point)
	{
		this_data_point = first_data_point->sNext;
		free(first_data_point->wcData);
		free(first_data_point);
		first_data_point = this_data_point;
	}

}

odbc::bc_odbc_connection::bc_odbc_connection()
{
	dsn_name_in_ = std::wstring(L"DSN=DevOdbcSqlServer;UID=vch\\gcrowell;Trusted_Connection=Yes;");
	dsn_name_in_ = std::wstring(L"DSN=SysDsnWwi;UID=user;Trusted_Connection=Yes;");
	dsn_name_in_ = std::wstring(L"DSN=DevOdbcSqlServer;");
	dsn_name_in_ = std::wstring(L"DSN=DenodoODBC;");
}

odbc::bc_odbc_connection::bc_odbc_connection(std::wstring dsn_name_in) : dsn_name_in_(dsn_name_in) {}

inline std::vector<std::vector<std::wstring>> odbc::bc_odbc_connection::execute_sql_query(std::wstring stmt)
{
	execute_sql(stmt);
	ProcessResults();
	return rows_of_columns_of_data_;
}

bool odbc::bc_odbc_connection::connect()
{
	// mutex within function
	std::mutex conn_mutex;
	// lock mutex before accessing shared resource
	std::lock_guard<std::mutex> lock(conn_mutex);
	if (this->_input_handle == nullptr)
	{
		std::cout << "init ODBC connection" << std::endl;
		
		SQLWCHAR dsn_connection_string_out[DSN_STRING_MAX_LENGTH];
		SQLSMALLINT* dsn_string_length = nullptr;

		SQLRETURN retcode;
		if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_environment_handle) == SQL_ERROR)
		{
			std::cout << "error connecting" << std::endl;
			//exit(-1);
			throw std::exception("ODBC error: cannot connect");
		}
		else
		{
			std::cout << "enviroment created" << std::endl;
		}
		// Register this as an application that expects 3.x behavior,
		// you must register something if you use AllocHandle
		SQLSetEnvAttr(_environment_handle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
		// Allocate a connection handle
		SQLAllocHandle(SQL_HANDLE_DBC, _environment_handle, &_input_handle);
		// connect to ODBC driver using dsn_name_in_
		retcode = SQLDriverConnect(_input_handle, GetDesktopWindow(), (SQLWCHAR*)dsn_name_in_.c_str(), SQL_NTS, dsn_connection_string_out, DSN_STRING_MAX_LENGTH, dsn_string_length, SQL_DRIVER_COMPLETE);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			std::wcout << L"connection established:\n\tinstring:  " << dsn_name_in_ << std::endl;
			dsn_name_out_ = std::wstring(dsn_connection_string_out);
			std::wcout << L"\toutstring: " << dsn_name_out_ << std::endl;
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
			throw std::exception("ODBC error: cannot connect");
			return false;
		}
		return true;
	}
}

void odbc::bc_odbc_connection::execute_sql(const std::wstring stmt)
{
	std::wcout << "executing sql: " << std::endl << stmt << std::endl;
	if (stmt.length() >= 2000)
	{
		throw std::exception("sql query too long");
	}
	//if (sql_statement_str)
	//{
	//	// TODO this might delete prev allocated/still used sql
	//	delete[] sql_statement_str;
	//}
	//sql_statement_str = new wchar_t[stmt.length() + 1];
	wchar_t sql_statement_str[2000];
	wcscpy(sql_statement_str, stmt.c_str());


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
			PopulateColumnInfo();
		}
		else
		{
			std::cout << "no columns returned from query" << std::endl;
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
			std::cout << "no rows affected by statement" << std::endl;
		}
		break;
	}
	case SQL_ERROR:
	{
		std::cout << "SQL_ERROR" << std::endl;
		throw std::exception("ODBC error: cannot execute SQL");
		//HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, RetCode);
		break;
	}
	default:
		fwprintf(stderr, L"Unexpected return code %hd!\n", RetCode);
	}
}

// TODO not working.  issue with unique pointer
meta::schema odbc::bc_odbc_connection::get_meta_schema(std::wstring database_name)
{
	std::wstring sql_fmt = L"\n\
SELECT\n\
	QUOTENAME(sch.name) + '.' + QUOTENAME(tab.name) AS table_name\n\
	,col.name AS column_name\n\
FROM [%s].sys.schemas AS sch\n\
JOIN [%s].sys.tables AS tab\n\
ON sch.schema_id = tab.schema_id\n\
JOIN [%s].sys.columns as col\n\
ON tab.object_id = col.object_id;";

	wchar_t sql_arr[2000];
	swprintf(sql_arr, sql_fmt.c_str(), database_name.c_str(), database_name.c_str(), database_name.c_str());
	std::wstring sql(sql_arr);
	execute_sql_query(sql);
	return meta::schema_builder::build_schema(database_name, rows_of_columns_of_data_);
}

odbc::bc_odbc_connection::~bc_odbc_connection()
{
	std::cout << "cleaning up ODBC connection" << std::endl;
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
	//if (sql_statement_str)
	//{
	//	delete[] sql_statement_str;
	//}
}
