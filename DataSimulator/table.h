#pragma once
#include"stdafx.h"
#include"column.h"

namespace meta {
	using namespace std;

	//using column_iterator = boost::indirect_iterator<std::vector<std::unique_ptr<column>>::const_iterator, const column>;

	class table
	{
		wstring table_name_;
		vector<unique_ptr<column>> columns_;
	public:
		table() : columns_{} {}
		table(wstring table_name, vector<unique_ptr<column>> columns) : table_name_(table_name), columns_(move(columns)) {}
		~table();
		//column_iterator begin() const { return std::begin(columns_); }
		//column_iterator end() const { return std::end(columns_); }
		wstring table_name() { return table_name_; }
		//friend std::wostream& operator<< (std::wostream& stream, const meta::table& table_);
	};
}