#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <iostream>
using std::string;
using std::endl;
using std::cout;
class logger
{
	public:
		static void log(string text);
};

#endif // LOGGER_H
