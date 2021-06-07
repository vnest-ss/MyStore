#include "StorageData.h"
#include <conio.h>
#include <chrono>
#include <windows.h>

const int period_for_element_milliseconds = 1000;
using namespace std::chrono;

int main(int argc, char* argv[])
{
	StorageData storage;

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