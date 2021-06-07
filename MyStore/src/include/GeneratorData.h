#pragma once

#include <vector>
#include <iostream>
#include "InfoProduct.h"

class GeneratorData
{
private:

	const int m_max_amount_data = 0;
	std::vector<InfoProduct> m_data;
	std::vector<std::string> m_colors = { "green", "blue", "yellow", "orange", "pink", "black", "white", "red"};
	std::vector<std::string> m_names = { "apple", "banana", "orange", "pineapple", "cherry", "pomegranate", "watermelon", "kiwi"};

public:

	GeneratorData() {};
	GeneratorData(const int& max_amount_data) : m_max_amount_data(max_amount_data) {};

	InfoProduct GeneratedProduct();
};

