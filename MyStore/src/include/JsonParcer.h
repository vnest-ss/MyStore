#pragma once

#include <vector>
#include "InfoProduct.h"

class JsonParcer
{
private:

	std::string m_file_path = {};
	std::vector<InfoProduct> m_data;

public:

	JsonParcer() = delete;
	JsonParcer(const std::string& obj) : m_file_path(obj) {};
	JsonParcer(const JsonParcer& obj) = delete;
	JsonParcer(const JsonParcer&& obj) = delete;

	bool Deserialization();
	void ShowData();
};

