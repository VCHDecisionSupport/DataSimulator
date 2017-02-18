#include "odbc_connection.h"

using namespace std;

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
		cout << "init connection" << endl;
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

odbc_connection::~odbc_connection()
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
}
