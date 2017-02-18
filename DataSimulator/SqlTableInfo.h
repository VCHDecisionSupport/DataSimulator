#pragma once
#include"stdafx.h"
// https://code.msdn.microsoft.com/ODBC-sample-191624ae
using namespace std;

#include "ColumnInfo.h"
//struct ColumnInfo
//{
//	std::uint32_t column_number = 0;
//	std::wstring column_name = L"";
//	std::wstring column_type = L"";
//	std::uint32_t column_octet_length = 0;
//	std::uint32_t column_precision = 0;
//	std::uint32_t column_scale = 0;
//	std::uint32_t column_display_width = 0;
//
//	friend std::wostream& operator<<(std::wostream& os, const ColumnInfo& obj)
//	{
//		return os
//			<< "column_name: " << obj.column_name << endl
//			<< "\t" << "column_number: " << obj.column_number << endl
//			<< "\t" << "column_type: " << obj.column_type << endl
//			<< "\t" << "column_octet_length: " << obj.column_octet_length << endl
//			<< "\t" << "column_precision: " << obj.column_precision << endl
//			<< "\t" << "column_scale: " << obj.column_scale << endl
//			<< "\t" << "column_display_width: " << obj.column_display_width << endl
//			;
//	}
//};
//typedef struct STR_BINDING {
//	SQLSMALLINT         cDisplaySize;           /* size to display  */
//	WCHAR               *wszBuffer;             /* display buffer   */
//	SQLLEN              indPtr;                 /* size or null     */
//	BOOL                fChar;                  /* character col?   */
//	struct STR_BINDING  *sNext;                 /* linked list      */
//} BINDING;
//
//struct SqlDataPoint
//{
//	SQLSMALLINT column_index;
//	WCHAR *wcData;             /* display buffer   */
//	SQLLEN wcSize;                 /* size or null     */
//	struct SqlDataPoint  *sNext;                 /* linked list      */
//};

class SqlTableInfo
{
	SQLWCHAR* dsnName = (SQLWCHAR*)"SysDsnWwi";
	SQLWCHAR* userID = (SQLWCHAR*)"SysDsnWwi";
	SQLWCHAR* passwd = (SQLWCHAR*)"SysDsnWwi";
	SQLSMALLINT _result_column_count = 0; /* number of columns returned by sql statement */
	SQLHENV _environment_handle = nullptr; /* SQLHANDLE SQLHENV sql handle enviroment */
	SQLHDBC _input_handle = nullptr; /* SQLHANDLE SQLHDBC sql handle database connection */
	SQLHSTMT _statement_handle = nullptr; /* SQLHANDLE SQLHSTMT sql handle statement */
	std::vector<ColumnInfo> *_column_infos = nullptr;

	void InitializeResults(SqlDataPoint** dptr);

	friend std::wostream& operator<<(std::wostream& os, const SqlTableInfo& obj);
public:
	SqlTableInfo();
	void error_out();
	void test();
	bool SqlConnect();
	void ExecuteCommand();
	void PopulateColumnInfo();
	void ProcessResults();
	~SqlTableInfo();
};



