#pragma once
#include <string>
#include <iostream>

struct InfoProduct
{
	std::string m_product_name = {};
	std::string m_product_color = {};
};

std::ostream& operator << (std::ostream& out, const InfoProduct& data);

