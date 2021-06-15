#include <stdexcept>
#include "JsonObject.h"


namespace
{
	const std::string cWhitespaces = " \n\r\t\f\v";

	std::string GetQuoteString(const std::string& inStr)
	{
		size_t leftQuote = inStr.find('"');
		size_t rightQuote = inStr.find('"', leftQuote + 1);
		if (leftQuote == std::string::npos || rightQuote == std::string::npos || leftQuote == rightQuote)
			return "";

		return inStr.substr(leftQuote + 1, rightQuote - leftQuote - 1);
	}

	std::string TrimWhitespaces(const std::string& inStr)
	{
		size_t start = inStr.find_first_not_of(cWhitespaces);
		if (start == std::string::npos)
			return "";

		size_t end = inStr.find_last_not_of(cWhitespaces);
		return inStr.substr(start, end - start + 1);
	}
}

JsonObject::JsonObject(const ObjectType& type)
	:m_type(type)
{
}

bool JsonObject::LoadFromFile(const std::string& path)
{
	std::ifstream fstream(path);

	if (path.empty() || !fstream)
		return false;

	bool bRet = true;

	std::string text = {};

	while (!fstream.eof())
	{
		getline(fstream, text);
		if (text == "{")
		{
			m_type = ObjectType::Object;
			bRet &= LoadFromParser(fstream);
		}
	}

	return bRet;
}

bool JsonObject::LoadFromParser(std::ifstream& fstream)
{
	bool res = true;

	while (!fstream.eof())
	{
		std::string str;
		getline(fstream, str);
		str = TrimWhitespaces(str);

		if (m_type == ObjectType::Array && str == "]")
			break;
		else if (m_type == ObjectType::Object && (str == "}") || (str == "},"))
			break;

		size_t nPos = str.find(':');
		if (nPos == std::string::npos)
		{
			if (m_type == ObjectType::Array && str == "{")
			{
				m_array.emplace_back(ObjectType::Object);
				res &= m_array.back().LoadFromParser(fstream);

				continue;
			}
			else
			{
				return false;
			}
		}

		std::string strLeft = str.substr(0, nPos);
		std::string key = GetQuoteString(strLeft);
		if (key.empty())
			return false;

		m_children.insert({ key, {} });

		std::string strRight = str.substr(nPos + 1);
		strRight = TrimWhitespaces(strRight);
		if (strRight.back() == ',')
			strRight = strRight.substr(0, strRight.size() - 1);

		if (strRight == "{")
		{
			// we deal with object
			m_children[key].m_type = ObjectType::Object;
			res &= m_children[key].LoadFromParser(fstream);
		}
		else if (strRight == "[")
		{
			// we deal with array
			m_children[key].m_type = ObjectType::Array;
			res &= m_children[key].LoadFromParser(fstream);
		}
		else
		{
			// determine true value type
			std::string val = GetQuoteString(strRight);
			if (!val.empty())
				// it's string
				m_children[key].m_value = val;
			else
			{
				if (strRight.find('.') != std::string::npos)
				{
					// it's float
					try
					{
						double dVal = std::atof(strRight.c_str());
						m_children[key].m_value = dVal;
					}
					catch (const std::invalid_argument&)
					{
						m_children[key].m_value = 0.0;
					}
				}
				else
				{
					// otherwise int
					try
					{
						int val = std::stoi(strRight);
						m_children[key].m_value = val;
					}
					catch (const std::invalid_argument&)
					{
						m_children[key].m_value = 0;
					}
				}
			}
		}
	}

	return res;
}

JsonObject& JsonObject::operator[](const std::string& key)
{
	if (m_type != ObjectType::Object)
		throw BadType_Exception{};

	if (m_children.find(key) == m_children.end())
		throw BadKey_Exception{};

	return m_children[key];
}

JsonObject& JsonObject::operator[](const int index)
{
	if (m_type != ObjectType::Array)
		throw BadType_Exception{};

	if (index < 0 || index >= m_array.size())
		throw BadIndex_Exception{};

	return m_array[index];
}

size_t JsonObject::GetArraySize()
{
	if (m_type != ObjectType::Array)
		return 0;
	else
		return m_array.size();
}

std::string JsonObject::AsString()
{
	if (m_type != ObjectType::Value)
		return "";

	if (m_value.type() != typeid(std::string))
		return "";

	return std::any_cast<std::string>(m_value);
}

int JsonObject::AsInt()
{
	if (m_type != ObjectType::Value)
		return 0;

	if (m_value.type() != typeid(int))
		return 0;

	return std::any_cast<int>(m_value);
}

float JsonObject::AsFloat()
{
	if (m_type != ObjectType::Value)
		return 0.0;

	if (m_value.type() != typeid(float))
		return 0.0;

	return std::any_cast<float>(m_value);
}
