#pragma once
#include <string>
#include <JsonObject.h>

class Settings
{
private:

	static Settings m_instance;

	int m_max_length = 0;
	int m_max_price = 0;
	int m_min_price = 0;
	int m_time_generate = 0;
	int m_max_amount_goods = 0;

	std::string m_path_goods = {};
	std::string m_path_settings = "..\\MyStore\\data\\Settings.json";

protected:

	Settings() { Settings::Instance().LoadFromFile(); };
	Settings(const Settings& obj) = delete;
	Settings(const Settings&& obj) = delete;

public:

	static Settings& Instance();

	bool LoadFromFile();

	inline int GetMaxLength() const { return m_max_length; }
	inline int GetMaxPrice() const { return m_max_price; }
	inline int GetMinPrice() const { return m_min_price; }
	inline int GetTimeGenerate() const { return m_time_generate; }
	inline int GetMaxAmoutGoods() const { return m_max_amount_goods; }
	inline std::string GetPathGoods() const { return m_path_goods; }
};

