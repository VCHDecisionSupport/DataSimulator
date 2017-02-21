#pragma once
#include "stdafx.h"
#include "table.h"

namespace meta {

	//template<T>
	//using vector_iter = boost::indirect_iterator<std::vector<T>>;

	//using table_iterator = boost::indirect_iterator<std::vector<unique_ptr<table>>::const_iterator, const table>;

	using namespace std;

	// generic collection of tables.  (database schema names are included as part of a table name)
	class schema
	{
		wstring schema_name_;
		vector<unique_ptr<table>> tables_;
	public:
		schema() : tables_{} {}
		schema(wstring schema_name, vector<unique_ptr<table>> tables) : schema_name_(schema_name), tables_(move(tables)) {}
		~schema();
		//table_iterator begin() const { return std::begin(tables_); }
		//table_iterator end() const { return std::end(tables_); }
		wstring schema_name() { return schema_name_; }
		//friend std::wostream& operator<< (std::wostream& stream, const meta::schema& schema_);
	};
}