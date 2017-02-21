#pragma once
#include "stdafx.h"

// meta data of column contained in/returned by query 
// member fields populated by calling PopulateColumnInfo which assumes _statement_handle has been executed
struct ColumnInfo
{
	std::uint32_t column_number = 0;
	std::wstring column_name = L"";
	std::wstring column_type = L"";
	std::uint32_t column_octet_length = 0;
	std::uint32_t column_precision = 0;
	std::uint32_t column_scale = 0;
	std::uint32_t column_display_width = 0;

	friend std::wostream& operator<<(std::wostream& os, const ColumnInfo& obj)
	{
		return os
			<< "column_name: " << obj.column_name << std::endl
			<< "\t" << "column_number: " << obj.column_number << std::endl
			<< "\t" << "column_type: " << obj.column_type << std::endl
			<< "\t" << "column_octet_length: " << obj.column_octet_length << std::endl
			<< "\t" << "column_precision: " << obj.column_precision << std::endl
			<< "\t" << "column_scale: " << obj.column_scale << std::endl
			<< "\t" << "column_display_width: " << obj.column_display_width << std::endl
			;
	}
};
typedef struct STR_BINDING {
	SQLSMALLINT         cDisplaySize;           /* size to display  */
	WCHAR               *wszBuffer;             /* display buffer   */
	SQLLEN              indPtr;                 /* size or null     */
	BOOL                fChar;                  /* character col?   */
	struct STR_BINDING  *sNext;                 /* linked list      */
} BINDING;

struct SqlDataPoint
{
	SQLSMALLINT column_index;
	WCHAR *wcData;             /* display buffer   */
	SQLLEN wcSize;                 /* size or null     */
	struct SqlDataPoint  *sNext;                 /* linked list      */
	friend std::wostream& operator<<(std::wostream& os, const SqlDataPoint& obj)
	{
		return os
			<< L"Column Index:\n\t"
			<< obj.column_index << std::endl
			<< L"Size:\n\t"
			<< obj.wcSize << std::endl
			<< L"Data:\n\t"
			<< obj.wcData << std::endl;
	}
};

