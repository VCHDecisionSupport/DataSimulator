#pragma once
#include"stdafx.h"
#include"column.h"

namespace meta {
	//using column_iterator = boost::indirect_iterator<std::vector<std::shared_ptr<column>>::const_iterator, const column>;
	using column_iterator = std::vector<std::shared_ptr<column>>::const_iterator;



	class table
	{
		std::wstring table_name_;
		std::vector<std::shared_ptr<column>> columns_;
	public:
		table() : columns_{} {}
		table(std::wstring table_name, std::vector<std::shared_ptr<column>> columns) : table_name_(table_name), columns_(move(columns)) {}
		~table();
		column_iterator begin() const { return std::begin(columns_); }
		column_iterator end() const { return std::end(columns_); }
		std::wstring table_name() { return table_name_; }
		friend std::wostream& operator<< (std::wostream& stream, const meta::table& table_);
	};

	//column_iterator begin(table table_)
	//{
	//	return table_.begin();
	//}
	//column_iterator end(table table_)
	//{
	//	return table_.end();
	//}
}