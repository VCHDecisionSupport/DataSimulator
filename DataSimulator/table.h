#pragma once
#include"stdafx.h"
#include"column.h"
namespace meta {
	using namespace std;

	class table
	{
		vector<unique_ptr<column>> columns_;
		wstring table_name_;
	public:
		table() {}
		//table(wstring table_name, vector<unique_ptr<column>> columns);
		//void set_columns(vector<unique_ptr<column>> columns);
		~table();
	};
}