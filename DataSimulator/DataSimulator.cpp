// DataSimulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "unit_tests.h"
#include "table.h"

using namespace std;

void populate_meta_data(OdbcConnection &con, vector<unique_ptr<table>> &tables)
{
	
}

int main()
{
	//unit_test::SqlTableInfo_();
	unit_test::OdbcConnection_();
	cout << " execution complete " << endl;
	getchar();
    return 0;
}

