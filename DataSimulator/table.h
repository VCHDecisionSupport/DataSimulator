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
		table() : columns_{} {}
		table(wstring table_name, vector<unique_ptr<column>> columns) : table_name_(table_name), columns_(move(columns)) {}
		~table();
		friend std::wostream& operator<< (std::wostream& stream, const meta::table& table_);
	};
}