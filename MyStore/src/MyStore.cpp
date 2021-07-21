#include "StorageData.h"
#include <conio.h>
#include <chrono>
#include <windows.h>
#include <filesystem>
#include <thread>
#include <mutex>
#include <atomic>

using namespace std::chrono;

// This variable is needed to avoid confusion with relative paths in different modules
// Example of usage:
// std::string filePath = gProjectPath + "\\data\\Data.json"

const std::string gProjectPath = std::filesystem::current_path().generic_string();


void GenerateProducts(StorageData& stor, const int& period, std::atomic<bool>& flag)
{
	auto last_time = system_clock::now();

	while (true)
	{
		if (flag)
			break;
		if ((duration_cast<milliseconds>(system_clock::now() - last_time).count()) > period)
		{
			std::cout << stor.m_Generator.GeneratedProduct();
			last_time = system_clock::now();
		}
	}
}
void ExitCondition(std::atomic<bool>& flag)
{
	while (true)
	{
		if (GetKeyState(VK_SPACE) & 0x8000)
			break;
	}
	flag = true;
}

int main(int argc, char* argv[])
{
	StorageData storage;
	std::atomic<bool> flag_thread = false;
	const int period_for_element_milliseconds = Settings::Instance().GetTimeGenerate();

	storage.m_Parcer.Deserialization();
	storage.m_Parcer.ShowData();

	std::thread T1(&GenerateProducts, std::ref(storage), std::ref(period_for_element_milliseconds), std::ref(flag_thread));
	std::thread T2(ExitCondition, std::ref(flag_thread));
	T1.join();
	T2.join();

	return 0;
}
