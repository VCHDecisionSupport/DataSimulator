#pragma once
#include "stdafx.h"
#include "database.h"
#include "table.h"
#include "bc_odbc_connection.h"
#include "column_value_histogram.h"

namespace odbc
{
	// abstract factory for creating meta namespace objects
	class bc_meta_factory
	{
	protected:
		odbc::bc_odbc_connection odbc_connection_;
	public:
		bc_meta_factory(std::wstring dsn_name);
		virtual std::wstring schema_query() = 0;
		virtual std::wstring schema_query(std::wstring database_name) = 0;
		virtual std::shared_ptr<meta::database> generate_meta_object(std::wstring database_name) = 0;

		virtual std::wstring table_row_count_query(meta::table& table_) = 0;
		virtual long long unsigned get_table_row_count(meta::table& table_) = 0;

		virtual std::wstring column_value_histogram_query(meta::column& column_) = 0;
		virtual meta::column_value_histogram generate_column_value_histogram(meta::column& column_) = 0;
		~bc_meta_factory();
	};

}