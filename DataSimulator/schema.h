#pragma once
#include "stdafx.h"
#include "table.h"

namespace meta {
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
	};
}