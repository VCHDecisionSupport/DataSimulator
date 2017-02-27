#pragma once
#include "stdafx.h"
namespace meta {
	class abc_odbc_object
	{
	protected:
		std::wstring odbc_object_name_;
		std::weak_ptr<abc_odbc_object> odbc_object_parent_;
		std::vector<std::shared_ptr<abc_odbc_object>> odbc_object_children_;
		size_t tab_offset_ = 0;
	public:
		abc_odbc_object() { std::wcout << "abc_odbc_object()" << std::endl; }
		abc_odbc_object(std::wstring odbc_object_name) : odbc_object_name_(odbc_object_name) { std::wcout << (boost::wformat(L"abc_odbc_object(%s)") % odbc_object_name).str() << std::endl; }
		abc_odbc_object(std::wstring odbc_object_name, std::vector<std::shared_ptr<abc_odbc_object>> odbc_object_children) : odbc_object_name_(odbc_object_name), odbc_object_children_(odbc_object_children) { std::wcout << (boost::wformat(L"abc_odbc_object(%s,std::vector<std::shared_ptr<abc_odbc_object>>)") % odbc_object_name).str() << std::endl; }

		virtual std::wstring get_name() { return odbc_object_name_; }
		virtual std::weak_ptr<abc_odbc_object> get_parent() { return odbc_object_parent_; }
		virtual std::vector<std::shared_ptr<abc_odbc_object>> get_children() { return odbc_object_children_; }
		virtual std::vector<std::shared_ptr<abc_odbc_object>>::const_iterator begin() { return std::begin(odbc_object_children_); }
		virtual std::vector<std::shared_ptr<abc_odbc_object>>::const_iterator end() { return std::end(odbc_object_children_); }
		virtual void push_back(std::shared_ptr<abc_odbc_object> child_odbc_object) { odbc_object_children_.push_back(child_odbc_object); }
		friend std::wostream& operator<< (std::wostream& stream, const abc_odbc_object& abc_odbc_object_);
		virtual ~abc_odbc_object() {}
	};

	//class db : public abc_odbc_object
	//{
	//public:
	//	db() : abc_odbc_object() { std::wcout << "db()" << std::endl; tab_offset_ = 0; }
	//	db(std::wstring odbc_object_name) : abc_odbc_object(odbc_object_name) { std::wcout << (boost::wformat(L"abc_odbc_object(%s)") % odbc_object_name).str() << std::endl; tab_offset_ = 0; }
	//	db(std::wstring odbc_object_name, std::vector<std::shared_ptr<abc_odbc_object>> odbc_object_children) : abc_odbc_object(odbc_object_name, odbc_object_children) { std::wcout << (boost::wformat(L"db(%s,std::vector<std::shared_ptr<abc_odbc_object>>)") % odbc_object_name).str() << std::endl; tab_offset_ = 0; }
	//	std::weak_ptr<abc_odbc_object> get_parent() override { throw std::exception("ERROR db.get_parent(): db objects do not have parents."); }
	//};
	//class schema : public abc_odbc_object
	//{
	//public:
	//	schema() : abc_odbc_object() { std::wcout << "schema()" << std::endl; tab_offset_ = 0; }
	//	schema(std::wstring odbc_object_name) : abc_odbc_object(odbc_object_name) { std::wcout << (boost::wformat(L"abc_odbc_object(%s)") % odbc_object_name).str() << std::endl; tab_offset_ = 0; }
	//	schema(std::wstring odbc_object_name, std::vector<std::shared_ptr<abc_odbc_object>> odbc_object_children) : abc_odbc_object(odbc_object_name, odbc_object_children) { std::wcout << (boost::wformat(L"schema(%s,std::vector<std::shared_ptr<abc_odbc_object>>)") % odbc_object_name).str() << std::endl; tab_offset_ = 0; }
	//};
	//class tab : public abc_odbc_object
	//{
	//public:
	//	tab() : abc_odbc_object() { std::wcout << "tab()" << std::endl; tab_offset_ = 0; }
	//	tab(std::wstring odbc_object_name) : abc_odbc_object(odbc_object_name) { std::wcout << (boost::wformat(L"abc_odbc_object(%s)") % odbc_object_name).str() << std::endl; tab_offset_ = 0; }
	//	tab(std::wstring odbc_object_name, std::vector<std::shared_ptr<abc_odbc_object>> odbc_object_children) : abc_odbc_object(odbc_object_name, odbc_object_children) { std::wcout << (boost::wformat(L"tab(%s,std::vector<std::shared_ptr<abc_odbc_object>>)") % odbc_object_name).str() << std::endl; tab_offset_ = 0; }
	//};

}
std::wostream & meta::operator<<(std::wostream & stream, const meta::abc_odbc_object & abc_odbc_object_)
{
	stream
		<< std::wstring(L"\t", abc_odbc_object_.tab_offset_) << abc_odbc_object_.odbc_object_name_
		<< std::endl;
	std::for_each(std::begin(abc_odbc_object_.odbc_object_children_), std::end(abc_odbc_object_.odbc_object_children_), [&](auto odbc_object_child)
	{
		stream << *odbc_object_child;
	});
	return stream;
}
