#pragma once
#include "stdafx.h"
//#include "schema.h"
//#include "table.h"
//#include "column.h"

namespace odbc {
	using namespace std;
	class data_source_connection
	{
	public:
		virtual vector<vector<wstring>> execute_sql_query(wstring sql_query) = 0;
	};
}
