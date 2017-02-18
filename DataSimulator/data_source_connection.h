#pragma once
#include "stdafx.h"
#include "table.h"

namespace odbc {
	using namespace std;
	class data_source_connection
	{
	public:
		virtual vector<vector<wstring>> execute_sql_query(wstring sql_query) = 0;
		virtual void generate_schema_model(vector<unique_ptr<meta::table>> schema) = 0;
	};
}
