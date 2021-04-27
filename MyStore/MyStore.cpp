#include "JsonParcer.h"


int main(int argc, char *argv[])
{

	JsonParcer obj("..\\MyStore\\data\\Data.json");
	obj.Deserialization();
	obj.ShowData();

	return 0;
}