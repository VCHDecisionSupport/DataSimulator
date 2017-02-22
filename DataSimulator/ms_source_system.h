#pragma once
#include "source_system.h"
class ms_source_system :
	public source_system
{
public:
	ms_source_system(std::wstring dsn_name);



	// Inherited via source_system
	std::wstring schema_query() override;
	std::wstring schema_query(std::wstring database_name) override;
	meta::database generate_meta_object(std::wstring database_name) override;
	~ms_source_system();
};
