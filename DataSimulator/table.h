#pragma once
#include"stdafx.h"
#include"column.h"

namespace meta {
	//using column_iterator = boost::indirect_iterator<std::vector<std::shared_ptr<column>>::const_iterator, const column>;
	class schema;
	class column;
	using column_iterator = std::vector<std::shared_ptr<column>>::const_iterator;
	class table
	{
		std::wstring table_name_;
		std::vector<std::shared_ptr<column>> columns_;
		std::weak_ptr<schema> schema_;
		boost::wformat fully_qualified_table_name_fmt_;// (std::wstring(L"asdf"));
	public:
		table() : columns_{} {}
		table(std::wstring table_name, std::vector<std::shared_ptr<column>> columns) : table_name_(table_name), columns_(move(columns)), fully_qualified_table_name_fmt_(L"[%s].[%s].[%s]") {}
		table(std::wstring table_name, std::weak_ptr<schema> schema) : table_name_(table_name), schema_(schema) {}
		~table();
		column_iterator begin() const { return std::begin(columns_); }
		column_iterator end() const { return std::end(columns_); }
		std::wstring table_name() { return table_name_; }
		//std::wstring fully_qualified_table_name() { return (fully_qualified_table_name_fmt_ % (schema_.lock().get())->get_parent().lock().get()->database_name() % schema_.lock().get()->schema_name() % table_name_).str(); }
		std::weak_ptr<schema> get_parent() { return schema_; }
		void push_back(std::shared_ptr<column> column_) { columns_.push_back(column_); }
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