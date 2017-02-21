#pragma once
#include "stdafx.h"
#include "table.h"

namespace meta {
	using table_iterator = std::vector<std::shared_ptr<table>>::const_iterator;

	// generic collection of tables.  (database schema names are included as part of a table name)
	class schema
	{
		std::wstring schema_name_;
		std::vector<std::shared_ptr<table>> tables_;
	public:
		schema() : tables_{} {}
		schema(std::wstring schema_name, std::vector<std::shared_ptr<table>> tables) : schema_name_(schema_name), tables_(move(tables)) {}
		~schema();
		table_iterator begin() const { return std::begin(tables_); }
		table_iterator end() const { return std::end(tables_); }
		std::wstring schema_name() { return schema_name_; }
		friend std::wostream& operator<< (std::wostream& stream, const meta::schema& schema_);
	};
}