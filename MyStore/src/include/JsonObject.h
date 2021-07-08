#pragma once

#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>
#include <any>

// JsonObject class
// usage example:
// 
// JsonObject json;
// bool b = json.LoadFromFile("..\\MyStore\\data\\Data.json");
// 
// int count = json["products"].GetArraySize();
// for (int i = 0; i < count; ++i)
// {
// 	JsonObject child = json["products"][i];
// 	std::cout << child["name"].AsString() << ", " << child["color"].AsString() << ", " << child["price"].AsInt() << std::endl;
// }

class BadType_Exception {};
class BadIndex_Exception {};
class BadKey_Exception {};

class JsonObject
{
public:
	enum class ObjectType { Object, Array, Value };

	JsonObject(const ObjectType& type = ObjectType::Value);
	bool LoadFromFile(const std::string& path);

	JsonObject& operator[](const std::string& key);
	JsonObject& operator[](const int index);

	size_t GetArraySize();

	bool IsObject() const { return m_type == ObjectType::Object; };
	bool IsArray() const { return m_type == ObjectType::Array; };
	bool IsValue() const { return m_type == ObjectType::Value; };

	std::string AsString();
	int AsInt();
	float AsFloat();
private:
	bool LoadFromParser(std::ifstream& fstream);

private:
	ObjectType m_type = ObjectType::Value;
	std::unordered_map<std::string, JsonObject> m_children;
	std::vector<JsonObject> m_array;
	std::any m_value;
};