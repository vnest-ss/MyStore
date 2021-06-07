#include "GeneratorData.h"

InfoProduct GeneratorData::GeneratedProduct()
{
	InfoProduct data;

	int max_index_colors = m_colors.size() - 1;
	int max_index_names = m_names.size() - 1;

	int index_color = rand() * ((max_index_colors - 0 + 0.999) / RAND_MAX) + 0;
	int index_name = rand() * ((max_index_names - 0 + 0.999) / RAND_MAX) + 0;

	data.m_product_color = m_colors[index_color];
	data.m_product_name = m_names[index_name];
	m_data.push_back(data);

	return data;
}
