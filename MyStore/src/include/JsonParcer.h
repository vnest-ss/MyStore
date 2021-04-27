#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

class JsonParcer
{
private:

	struct InfoProduct
	{
		std::string m_product_name = {};
		std::string m_product_color = {};
	}Product;

	std::string m_file_path = {};
	std::vector<InfoProduct> m_data;

public:

	JsonParcer() = delete;
	JsonParcer(std::string path) : m_file_path(path) {};
	JsonParcer(const JsonParcer& obj) = delete;
	JsonParcer(const JsonParcer&& obj) = delete;

	bool Deserialization();
	void ShowData();	
};

