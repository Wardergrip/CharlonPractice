#include "pch.h"
#include "JsonFilehelper.h"

#include <fstream>

using json = nlohmann::json;

int JsonFilehelper::SaveJSON(const std::string& jsonDump, const std::string& filePath)
{
	if (filePath.empty())
	{
		return 1;
	}
	if (jsonDump.empty())
	{
		return 2;
	}
	std::ofstream outputFile{ filePath };
	outputFile.write(jsonDump.c_str(), jsonDump.length());

	return 0;
}
