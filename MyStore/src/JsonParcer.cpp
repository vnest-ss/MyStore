#include "JsonParcer.h"
#include <fstream>
#include <iostream>
#include <Settings.h>


bool JsonParcer::Deserialization()
{
	std::ifstream file(m_file_path);

	if (m_file_path.empty() || !file)
		return false;

	std::string text = {};
	InfoProduct store;
	const int maximum_lengthe_of_word = Settings::Instance().GetMaxLength();
	const int maximum_amounut_of_data = Settings::Instance().GetMaxAmoutGoods();

	while (!file.eof())
	{
		if (this->m_data.size() == maximum_amounut_of_data)
			return false;

		getline(file, text);

		if (text.find("name") != std::string::npos)
		{
			for (int i = 0; i < text.size(); i++)
			{
				if (text[i] == ':')
				{
					int index = text.find(':');
					int left_index = text.find('"', index);
					int right_index = text.find('"', left_index + 1);
					store.m_product_name = text.substr(left_index + 1, right_index - left_index - 1);
				}
			}
		}
		if (text.find("color") != std::string::npos)
		{
			for (int i = 0; i < text.size(); i++)
			{
				if (text[i] == ':')
				{
					int index = text.find(':');
					int left_index = text.find('"', index);
					int right_index = text.find('"', left_index + 1);
					store.m_product_color = text.substr(left_index + 1, right_index - left_index - 1);
				}
			}
		}
		if (text.find("price") != std::string::npos)
		{
			for (int i = 0; i < text.size(); i++)
			{
				if (text[i] == ':')
				{
					int index = text.find(':');
					int left_index = text.find('"', index);
					int right_index = text.find('"', left_index + 1);
					store.m_price = std::stoi(text.substr(left_index + 1, right_index - left_index - 1));

					if (store.m_product_color.size() > maximum_lengthe_of_word || store.m_product_name.size() > maximum_lengthe_of_word)
						break;

					m_data.push_back(store);
				}
			}
		}
	}
	file.close();
	return true;
}

void JsonParcer::ShowData()
{
	if (m_data.size() == 0)
	{
		std::cout << "0 products" << '\n';
		return;
	}

	std::cout << "-----------------LIST OF PRODUCTS-----------------" << '\n';

	for (const auto& it : m_data)
	{
		std::cout << it;
	}
}