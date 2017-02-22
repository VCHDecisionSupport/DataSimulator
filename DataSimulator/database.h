#pragma once
#include"stdafx.h"
#include"schema.h"
namespace meta {


	class schema;
	using schema_iterator = std::vector<std::shared_ptr<schema>>::const_iterator;
	class database
	{
		std::wstring database_name_;
		std::vector<std::shared_ptr<schema>> schemas_;
	public:
		database(std::wstring database_name) : database_name_(database_name) {}
		database(std::wstring database_name, std::vector<std::shared_ptr<schema>> schemas) : database_name_(database_name), schemas_(schemas) {}
		~database();
		std::wstring database_name() { return database_name_; }
		void set_schemas(std::vector<std::shared_ptr<schema>> schemas) { schemas_ = schemas; }
		void push_back(std::shared_ptr<schema> schema) { schemas_.push_back(schema); }
		schema_iterator begin() const { return std::begin(schemas_); }
		schema_iterator end() const { return std::end(schemas_); }
		friend std::wostream& operator<< (std::wostream& stream, const meta::database& database_);
	};

	//schema_iterator begin(database database_)
	//{
	//	return database_.begin();
	//}
	//schema_iterator end(database database_)
	//{
	//	return database_.end();
	//}
}