#pragma once
#include "stdafx.h"
#include "database.h"
#include "schema.h"
#include "table.h"
#include "column.h"
//
namespace meta {
	class schema_builder
	{
	public:

		static schema build_schema(std::wstring schema_name, std::vector<std::vector<std::wstring>> table_column_names)
		{
			std::vector<std::shared_ptr<table>> tables;
			std::vector<std::shared_ptr<column>> columns;
			std::wstring prev_table_name;
			std::wstring this_table_name;
			std::wstring this_column_name;
			for (std::vector<std::wstring> table_column_name : table_column_names)
			{
				this_table_name = table_column_name.at(0);
				this_column_name = table_column_name.at(1);
				if (this_table_name != prev_table_name && prev_table_name != L"")
				{
					tables.push_back(std::make_shared<table>(prev_table_name, move(columns)));
					columns = std::vector<std::shared_ptr<column>>();
				}
				columns.push_back(std::make_shared<column>(this_column_name));
				prev_table_name = this_table_name;
			}
			tables.push_back(std::make_shared<table>(prev_table_name, move(columns)));
			return schema(schema_name, move(tables));
		}
	};
}