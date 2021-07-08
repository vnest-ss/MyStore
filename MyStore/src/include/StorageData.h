#pragma once
#include "GeneratorData.h"
#include "JsonParcer.h"
#include "Settings.h"

class StorageData
{
public:
	std::vector<InfoProduct> m_data;
	const int m_max_size_data = Settings::Instance().GetMaxAmoutGoods();

	JsonParcer m_Parcer = (Settings::Instance().GetPathGoods());
	GeneratorData m_Generator;
};

