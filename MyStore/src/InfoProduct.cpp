#include "InfoProduct.h"

std::ostream& operator << (std::ostream& out, const InfoProduct& data)
{
	out << "Name:" << data.m_product_color << '\n'
		<< "Color:" << data.m_product_name << '\n'
		<< "Price:" << data.m_price << "\n\n";
	return out;
}