#pragma once
#include"stdafx.h"
#include"column.h"

namespace meta {
	using namespace std;

	class table
	{
		wstring table_name_;
		vector<unique_ptr<column>> columns_;
	public:
		table(wstring table_name, vector<unique_ptr<column>> columns) : table_name_(table_name), columns_(move(columns)) {}
		~table();
	};
}