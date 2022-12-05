#pragma once
#include <iostream>
#include <fstream>

void WriteText(const char* filename, const char* text) 
{
	std::ofstream str;
	str.open(filename);
	str << text << std::endl;
	str.close(); //Writing Text and Then Close :D
}
