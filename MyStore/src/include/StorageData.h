#pragma once
#include "GeneratorData.h"
#include "JsonParcer.h"

class StorageData
{
public:
	std::vector<InfoProduct> m_data;
	const int m_max_size_data = 5000;

	JsonParcer m_Parcer = ("..\\MyStore\\data\\Data.json");
	GeneratorData m_Generator;
};

