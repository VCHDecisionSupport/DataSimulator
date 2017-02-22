#pragma once
#include"stdafx.h"
#include"table.h"
//#include "column_value_histogram.h"

namespace meta {
	class table;
	class column
	{
		std::wstring column_name_;
		std::weak_ptr<table> table_;
		//std::shared_ptr<column_value_histogram> column_value_histogram_ptr_;
	public:
		column() :column_name_{} {}
		column(std::wstring column_name) :column_name_(column_name) {};
		column(std::wstring column_name, std::weak_ptr<table> table) :column_name_(column_name), table_(table) {};
		~column();
		std::wstring column_name() { return column_name_; }
		friend std::wostream& operator<< (std::wostream& stream, const meta::column& column_);
	};
}