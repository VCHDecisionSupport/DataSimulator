#pragma once
#include "stdafx.h"
#include "bc_meta_factory.h"
namespace odbc {
	// factory method for creating meta namespace objects from Microsoft Sql Server
	class sql_server_meta_factory :
		public bc_meta_factory
	{
		boost::wformat schema_query_fmt;
		boost::wformat table_row_count_query_fmt = boost::wformat(
			L"SELECT COUNT(*) FROM [%s].[%s].[%s]"
		);

	public:
		sql_server_meta_factory(std::wstring dsn_name);

		// Inherited via bc_meta_factory
		std::wstring schema_query() override;
		std::wstring schema_query(std::wstring database_name) override;
		std::shared_ptr<meta::database> generate_meta_object(std::wstring database_name) override;

		//std::wstring table_row_count_query(meta::table& table_);
		//long long unsigned get_table_row_count(meta::table& table_);

		//std::wstring column_value_histogram_query(meta::column& column_);
		//meta::column_value_histogram generate_column_value_histogram(meta::column& column_);


		~sql_server_meta_factory();
	};
}