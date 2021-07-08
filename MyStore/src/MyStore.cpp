#include "StorageData.h"
#include <conio.h>
#include <chrono>
#include <windows.h>
#include <filesystem>

using namespace std::chrono;

// This variable is needed to avoid confusion with relative paths in different modules
// Example of usage:
// std::string filePath = gProjectPath + "\\data\\Data.json"
const std::string gProjectPath = std::filesystem::current_path().generic_string();

int main(int argc, char* argv[])
{
	StorageData storage;
	const int period_for_element_milliseconds = Settings::Instance().GetTimeGenerate();

	storage.m_Parcer.Deserialization();
	storage.m_Parcer.ShowData();

	auto last_time = system_clock::now();

	while (true)
	{
		if ((duration_cast<milliseconds>(system_clock::now() - last_time).count()) > period_for_element_milliseconds)
		{
			std::cout << storage.m_Generator.GeneratedProduct();
			last_time = system_clock::now();
		}

		if (GetKeyState(VK_SPACE) & 0x8000)
			break;
	}

	return 0;
}