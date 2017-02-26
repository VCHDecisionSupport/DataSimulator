#pragma once
#include "stdafx.h"
#include "database.h"
#include "odbc_connection.h"
// 
class source_system_connection
{
protected:
	odbc::odbc_connection odbc_connection_;
public:
	source_system_connection(std::wstring dsn_name);
	virtual std::wstring schema_query() = 0;
	virtual std::wstring schema_query(std::wstring database_name) = 0;
	virtual std::shared_ptr<meta::database> generate_meta_object(std::wstring database_name) = 0;
	~source_system_connection();
};

