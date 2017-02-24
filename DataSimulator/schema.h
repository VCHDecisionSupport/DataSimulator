#pragma once
#include "stdafx.h"
#include "database.h"
#include "table.h"

namespace meta {
	
	class database;
	class table;
	using table_iterator = std::vector<std::shared_ptr<table>>::const_iterator;
	class schema
	{
		std::wstring schema_name_;
		std::vector<std::shared_ptr<table>> tables_;
		std::weak_ptr<database> database_;
	public:
		schema(std::wstring schema_name, std::weak_ptr<database> database) : schema_name_(schema_name), database_(database), tables_{} {}
		schema(std::wstring schema_name, std::vector<std::shared_ptr<table>> tables) : schema_name_(schema_name), tables_(move(tables)) {}
		~schema();
		table_iterator begin() const { return std::begin(tables_); }
		table_iterator end() const { return std::end(tables_); }
		std::weak_ptr<database> get_parent() { return database_; }
		void set_tables(std::vector<std::shared_ptr<table>> tables) { tables_ = tables; }
		void push_back(std::shared_ptr<table> table) { tables_.push_back(table); }
		std::wstring schema_name() { return schema_name_; }
		friend std::wostream& operator<< (std::wostream& stream, const meta::schema& schema_);
	};

	//table_iterator begin(schema schema_)
	//{
	//	return schema_.begin();
	//}
	//table_iterator end(schema schema_)
	//{
	//	return schema_.end();
	//}
}