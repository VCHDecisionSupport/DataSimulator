#pragma once
#include "stdafx.h"
#include "schema.h"
#include "table.h"
#include "column.h"
//
namespace meta {
	using namespace std;
	class schema_builder
	{
	public:
		static schema build_schema(wstring schema_name, vector<vector<wstring>> table_column_names)
		{
			vector<unique_ptr<table>> tables;
			vector<unique_ptr<column>> columns;
			wstring prev_table_name;
			wstring this_table_name;
			wstring this_column_name;
			for (vector<wstring> table_column_name : table_column_names)
			{
				this_table_name = table_column_name.at(0);
				this_column_name = table_column_name.at(1);
				if (this_table_name != prev_table_name && prev_table_name != L"")
				{
					tables.push_back(make_unique<table>(prev_table_name, move(columns)));
					columns = vector<unique_ptr<column>>();
				}
				columns.push_back(make_unique<column>(this_column_name));
				prev_table_name = this_table_name;
			}
			tables.push_back(make_unique<table>(prev_table_name, move(columns)));
			return schema(schema_name, move(tables));
		}
	};
}