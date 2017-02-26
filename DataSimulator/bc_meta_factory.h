#pragma once
#include "stdafx.h"
#include "database.h"
#include "bc_odbc_connection.h"

namespace odbc
{
	// abstract factory for creating meta namespace objects
	class bc_meta_factory
	{
	protected:
		odbc::bc_odbc_connection odbc_connection_;
	public:
		bc_meta_factory(std::wstring dsn_name);
		virtual std::wstring schema_query() = 0;
		virtual std::wstring schema_query(std::wstring database_name) = 0;
		virtual std::shared_ptr<meta::database> generate_meta_object(std::wstring database_name) = 0;
		~bc_meta_factory();
	};

}