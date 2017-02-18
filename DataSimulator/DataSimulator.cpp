// DataSimulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "unit_tests.h"
#include "table.h"
#include "schema.h"

using namespace std;

void populate_meta_data(odbc_connection &con, vector<unique_ptr<table>> &tables)
{
	
}

void user_exit()
{
	cout << endl << endl << "execution complete" << endl << "press enter to exit" << endl;
	getchar();
}

int main()
{
	//unit_test::SqlTableInfo_();
	//unit_test::OdbcConnection_();
	unit_test::sql_query();
	
	user_exit();
    return 0;
}

