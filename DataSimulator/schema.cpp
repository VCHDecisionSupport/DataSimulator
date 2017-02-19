#include "schema.h"

inline meta::schema::schema(wstring schema_name, vector<unique_ptr<table>> tables) : schema_name_(schema_name), tables_(move(tables)) {}

meta::schema::~schema()
{
}
