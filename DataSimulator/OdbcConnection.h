#pragma once
#include"stdafx.h"
const size_t DSN_STRING_MAX_LENGTH = 1000; /* max characters to store the DSN connection string */

class OdbcConnection
{
	//L"DSN=DevOdbcSqlServer;UID=vch\\gcrowell;Trusted_Connection=Yes;"
	SQLWCHAR* dsnName = (SQLWCHAR*)"SysDsnWwi";
	SQLWCHAR* userID = (SQLWCHAR*)"SysDsnWwi";
	SQLWCHAR* passwd = (SQLWCHAR*)"SysDsnWwi";
	SQLSMALLINT _result_column_count = 0; /* number of columns returned by sql statement */
	SQLHENV _environment_handle = nullptr; /* SQLHANDLE SQLHENV sql handle enviroment */
	SQLHDBC _input_handle = nullptr; /* SQLHANDLE SQLHDBC sql handle database connection */
	SQLHSTMT _statement_handle = nullptr; /* SQLHANDLE SQLHSTMT sql handle statement */
	bool connect();

public:
	OdbcConnection();



	void just_do_it()
	{
		connect();
	}
	~OdbcConnection();
};
