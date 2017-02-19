//#include "schema_builder.h"

//inline meta::schema_builder::schema_builder(wstring schema_name) : schema_name_(schema_name) {}
//
//inline meta::schema_builder::schema_builder(vector<vector<wstring>> table_column_names)
//{
//	vector<unique_ptr<column>> columns;
//	wstring prev_table_name;
//	wstring this_table_name;
//	for (auto table_column_name : table_column_names)
//	{
//		this_table_name = table_column_name.at(0);
//		if (this_table_name != prev_table_name && prev_table_name != L"")
//		{
//			tables_.push_back(make_unique<table>(prev_table_name, columns));
//			columns = vector<unique_ptr<column>>();
//		}
//		columns.push_back(make_unique<column>(table_column_name.at(1)));
//		prev_table_name = this_table_name;
//	}
//}
//
//inline meta::schema meta::schema_builder::get_schema()
//{
//	return schema(schema_name_, tables_);
//}
