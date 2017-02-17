#pragma once
#include"stdafx.h"
#include "column_value_histogram.h"
using namespace std;

class column
{
	string column_name_;
	unique_ptr<column_value_histogram> column_value_histogram_ptr_;
public:

	column(string column_name) :column_name_(column_name) {};
	string rand_column_value()
	{
		return column_value_histogram_ptr_->rand_column_value();
	}
	~column();
};

