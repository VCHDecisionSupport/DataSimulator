#pragma once
#include"stdafx.h"
using namespace std;
class column;
namespace meta {
	class table
	{
		/*vector<unique_ptr<column>> columns_;*/
		wstring table_name_;
	public:
		table();
		void set_columns(vector<unique_ptr<column>> columns);
		~table();
	};
}