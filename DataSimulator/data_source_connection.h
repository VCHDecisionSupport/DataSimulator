#pragma once
#include "stdafx.h"
#include "table.h"
namespace {
	using namespace std;
	class data_source_connection
	{
	public:
		virtual void generate_schema_model(vector<unique_ptr<table>> schema) = 0;
	};
}
