#pragma once
#include "MyCtrl.h"

class Administrator
{
private:
	MyCtrl ctrl;
public:
	Administrator();
	Administrator(const Administrator& admin);
	~Administrator() = default;
	const Administrator& operator=(const Administrator& admin);
	void open_log();
	void read_command(char* command);
};
