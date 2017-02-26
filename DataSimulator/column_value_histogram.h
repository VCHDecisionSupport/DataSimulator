#pragma once
#include "stdafx.h"

namespace meta {
	class column;

	using column_value = std::wstring;
	using value_frequency = long long unsigned;
	using value_proportion = long double;
	using cumalative_proportion = long double;
	using histogram_entry = std::tuple<column_value, value_frequency, value_proportion, cumalative_proportion>;
	using histogram = std::vector<std::unique_ptr<histogram_entry>>;

	enum class HISTOGRAM_ENTRY
	{
		COLUMN_VALUE = 0
		, VALUE_FREQUENCY
		, VALUE_PROPORTION
		, CUMALATIVE_PROPORTION
	};

	class column_value_histogram
	{
		std::default_random_engine generator;
		std::uniform_real_distribution<double> distribution;// (0.0, 1.0);
		histogram histogram_;
		//auto dice = std::bind(distribution, generator);
	public:
		column_value_histogram(histogram histogram)
		{
			histogram_ = std::move(histogram);
			distribution = std::uniform_real_distribution<double>(0.0, 1.0);
		}
		std::wstring rand_column_value()
		{
			long double random_real = distribution(generator);
			std::wcout << random_real << std::endl;
			auto itr = std::find_if(std::begin(histogram_), std::end(histogram_), [&](const std::unique_ptr<histogram_entry>& histogram_entry_)
			{
				std::wcout << std::get<0>(*histogram_entry_.get()) << L"\t" << std::get<3>(*histogram_entry_.get()) << std::endl;
				//std::wcout << std::get<HISTOGRAM_ENTRY::COLUMN_VALUE>(histogram_entry_->get()) << std::endl;
				if (std::get<3>(*histogram_entry_.get()) > random_real)
				{
					std::wcout << "found" << std::endl;
					std::wcout << std::get<0>(*histogram_entry_.get()) << std::endl;
					return true;
				}
				return false;
			});
			std::wcout << std::get<0>(*itr->get()) << std::endl;
			return std::get<0>(*itr->get());
		}
		~column_value_histogram();
	};


}