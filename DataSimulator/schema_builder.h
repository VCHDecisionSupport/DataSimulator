#pragma once
#include "stdafx.h"
#include "schema.h"
#include "table.h"
#include "column.h"
//
//namespace meta {
//	using namespace std;
//	class schema_builder
//	{
//	public:
//		static void build_schema(wstring schema_name, vector<vector<wstring>> table_column_names)
//		{
//			vector<unique_ptr<table>> tables;
//			vector<unique_ptr<column>> columns;
//			wstring prev_table_name;
//			wstring this_table_name;
//			for (vector<wstring> table_column_name : table_column_names)
//			{
//				this_table_name = table_column_name.at(0);
//				if (this_table_name != prev_table_name && prev_table_name != L"")
//				{
//					tables.push_back(make_unique<table>(prev_table_name, columns));
//					columns = vector<unique_ptr<column>>();
//				}
//				columns.push_back(make_unique<column>(table_column_name.at(1)));
//				prev_table_name = this_table_name;
//			}
//			//return schema(schema_name, move(tables));
//		}
//	};
//}