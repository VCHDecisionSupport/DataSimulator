#pragma once
#include"stdafx.h"
//#include "column_value_histogram.h"

namespace meta {
	using namespace std;
	class column
	{
		wstring column_name_;
		//unique_ptr<column_value_histogram> column_value_histogram_ptr_;
	public:
		column() :column_name_{} {}
		column(wstring column_name) :column_name_(column_name) {};
		~column();
	};
}