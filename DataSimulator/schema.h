#pragma once
#include "stdafx.h"
#include "table.h"
#include "odbc_connection.h"

namespace meta {
	using namespace std;

	// generic collection of tables.  (database schema names are included as part of a table name)
	class schema
	{
		wstring schema_name_;
		odbc_connection odbc_connection_;
		vector<unique_ptr<table>> tables_;
	public:
		schema();
		~schema();
	};

}