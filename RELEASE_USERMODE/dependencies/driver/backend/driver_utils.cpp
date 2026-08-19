#include "driver_utils.h"

void silence(std::string output) {
	if (DBGPRINT == true) {
		std::cout << output;
	}
	else {

	}
}

void dsilence(std::string output) {
	if (SDBGPRINT == true) {
		std::cout << output;
	}
	else {

	}
}

void instrict() {
	std::cout << xorstr_("-- Press Enter To Exit --\n");
	while (true) {
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			exit(1);
			exit(1);
		}
		else {
			Sleep(100);
		}
	}
}