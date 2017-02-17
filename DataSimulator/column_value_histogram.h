#pragma once
#include "stdafx.h"
using namespace std;

class column;

class column_value_histogram
{
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution;// (0.0, 1.0);
	//auto dice = std::bind(distribution, generator);
	void profile_column()
	{

	}
public:
	column_value_histogram()
	{
		distribution = std::uniform_real_distribution<double>(0.0, 1.0);
	}
	vector<string> get_distinct_values();
	const int distinct_count();
	string rand_column_value()
	{
		double random_real = distribution(generator);
		//TODO: binary search tree; nodes have probability and string column value.
	}
	~column_value_histogram();
};


