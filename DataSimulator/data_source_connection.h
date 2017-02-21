#pragma once
#include "stdafx.h"
#include "schema.h"
#include "table.h"
#include "column.h"

namespace odbc {
	class data_source_connection
	{
	public:
		virtual std::vector<std::vector<std::wstring>> execute_sql_query(std::wstring sql_query) = 0;
		//virtual meta::schema get_meta_schema(std::wstring database_name) = 0;
	};
}
