#include "sql_server_meta_factory.h"

odbc::sql_server_meta_factory::sql_server_meta_factory(std::wstring dsn_name) : bc_meta_factory(dsn_name)
{
}


//std::wstring odbc::sql_server_meta_factory::table_row_count_query(meta::table & table_)
//{
//	std::wstring query((table_row_count_query_fmt % table_.fully_qualified_table_name()).str());
//	std::wcout << query << std::endl;
//	return query;
//}
//
//long long unsigned  odbc::sql_server_meta_factory::get_table_row_count(meta::table & table_)
//{
//	return 0;
//}
//
//std::wstring odbc::sql_server_meta_factory::column_value_histogram_query(meta::column & column_)
//{
//	
//	table_row_count_query_fmt = boost::wformat(
//		L"SELECT COUNT(*) FROM %s"
//	);
//	return std::wstring();
//}

//meta::column_value_histogram odbc::sql_server_meta_factory::generate_column_value_histogram(meta::column & column_)
//{
//	return meta::column_value_histogram();
//}

odbc::sql_server_meta_factory::~sql_server_meta_factory()
{
}

std::wstring odbc::sql_server_meta_factory::schema_query()
{
	std::wstring sql(
		L"SELECT\n\
	DB_NAME() AS database_name\n\
	,sch.name AS schema_name\n\
	,tab.name AS table_name\n\
	,col.name AS column_name\n\
FROM sys.schemas AS sch\n\
JOIN sys.tables AS tab\n\
ON sch.schema_id = tab.schema_id\n\
JOIN sys.columns as col\n\
ON tab.object_id = col.object_id;\n");
	return sql;
}

std::wstring odbc::sql_server_meta_factory::schema_query(std::wstring database_name)
{
	boost::wformat fmt(
		L"SELECT\n\
	'%s' AS database_name\n\
	,sch.name AS schema_name\n\
	,tab.name AS table_name\n\
	,col.name AS column_name\n\
FROM [%s].sys.schemas AS sch\n\
JOIN [%s].sys.tables AS tab\n\
ON sch.schema_id = tab.schema_id\n\
JOIN [%s].sys.columns as col\n\
ON tab.object_id = col.object_id;\n");
	fmt % database_name % database_name % database_name % database_name;
	return fmt.str();
}

std::shared_ptr<meta::database> odbc::sql_server_meta_factory::generate_meta_object(std::wstring database_name)
{
	std::vector<std::vector<std::wstring>> data = odbc_connection_.execute_sql_query(schema_query(database_name));
	std::wstring this_database_name;
	std::wstring this_schema_name;
	std::wstring this_table_name;
	std::wstring this_column_name;
	std::wstring prev_database_name;
	std::wstring prev_schema_name;
	std::wstring prev_table_name;
	std::wstring prev_column_name;
	std::shared_ptr<meta::database> database_ptr = nullptr;
	std::shared_ptr<meta::schema> schema_ptr = nullptr;
	std::shared_ptr<meta::table> table_ptr = nullptr;
	std::shared_ptr<meta::column> column_ptr = nullptr;
	for (auto row : data)
	{
		this_database_name = row.at(0);
		this_schema_name = row.at(1);
		this_table_name = row.at(2);
		this_column_name = row.at(3);
		//std::wcout << this_database_name << "." << this_schema_name << "." << this_table_name << "." << this_column_name << std::endl;
		if (this_database_name != prev_database_name)
		{
			std::wcout << "new database" << std::endl;
			database_ptr = std::make_shared<meta::database>(this_database_name);
		}
		if (this_schema_name != prev_schema_name)
		{
			
			if (std::find_if(database_ptr->begin(), database_ptr->end(), [&](auto schema_)
			{
				return schema_->schema_name() == this_schema_name;
			}) == database_ptr->end())
			{
				std::wcout << "new schema" << std::endl;

				schema_ptr = std::make_shared<meta::schema>(this_schema_name, database_ptr);
				database_ptr->push_back(schema_ptr);
			}
		}
		if (this_table_name != prev_table_name)
		{
			table_ptr = std::make_shared<meta::table>(this_table_name, schema_ptr);
			if (std::find(schema_ptr->begin(), schema_ptr->end(), table_ptr) == schema_ptr->end())
			{
				schema_ptr->push_back(table_ptr);
			}
		}
		column_ptr = std::make_shared<meta::column>(this_column_name, table_ptr);
		table_ptr->push_back(column_ptr);
		prev_database_name = this_database_name;
		prev_schema_name = this_schema_name;
		prev_table_name = this_table_name;
		prev_column_name = this_column_name;
	}
	std::wcout << *database_ptr << std::endl;
	return database_ptr;
	//return meta::database(L"not a real database");
}

