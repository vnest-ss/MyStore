#include "Settings.h"

Settings& Settings::Instance()
{
	return m_instance;
}

bool Settings::LoadFromFile()
{
	JsonObject loader;
	bool b = loader.LoadFromFile("..\\MyStore\\data\\Settings.json");

	if (b)
	{
		JsonObject json = loader["settings"];

		m_max_length = json["max_length"].AsInt();
		m_max_price = json["max_price"].AsInt();
		m_min_price = json["min_price"].AsInt();
		m_time_generate = json["time_generate"].AsInt();
		m_max_amount_goods = json["max_amount_goods"].AsInt();
		m_path_goods = json["path_goods"].AsString();

		return true;
	}
	else
		return false;
}

Settings Settings::m_instance;