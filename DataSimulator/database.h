#pragma once
#include"stdafx.h"
#include"schema.h"
namespace meta {
	using schema_iterator = std::vector<std::shared_ptr<schema>>::const_iterator;



	class database
	{
		std::wstring database_name_;
		std::vector<std::shared_ptr<schema>> schemas_;
	public:
		database(std::wstring database_name, std::vector<std::shared_ptr<schema>> schemas) : database_name_(database_name), schemas_(schemas) {}
		~database();
		std::wstring schema_name() { return database_name_; }
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