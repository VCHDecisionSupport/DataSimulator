#pragma once
#include "stdafx.h"
#include "source_system_connection.h"
class ms_source_system :
	public source_system_connection
{
	boost::wformat schema_query_fmt;

public:
	ms_source_system(std::wstring dsn_name);

	// Inherited via source_system_connection
	std::wstring schema_query() override;
	std::wstring schema_query(std::wstring database_name) override;
	std::shared_ptr<meta::database> generate_meta_object(std::wstring database_name) override;
	~ms_source_system();
};
