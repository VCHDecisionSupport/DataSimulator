#pragma once
#include "stdafx.h"
class source_system
{
public:
	virtual std::wstring schema_query(std::wstring database_name) = 0;
};

