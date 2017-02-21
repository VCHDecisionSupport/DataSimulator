#pragma once
#include"stdafx.h"
//#include "column_value_histogram.h"

namespace meta {
	class column
	{
		std::wstring column_name_;
		//std::shared_ptr<column_value_histogram> column_value_histogram_ptr_;
	public:
		column() :column_name_{} {}
		column(std::wstring column_name) :column_name_(column_name) {};
		~column();
		std::wstring column_name() { return column_name_; }
		friend std::wostream& operator<< (std::wostream& stream, const meta::column& column_);
	};
}