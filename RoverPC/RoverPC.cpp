// RoverPC.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Gamepad.h"

int main(int argc, char* argv[])
{
	using namespace RoverPC;

	Gamepad * g = new Gamepad(0);

	// Test Gamepad
	while (true)
	{
		// Clear stream
		system("cls");

		g->Update();
		std::cout << g->GetState()._RAW;

		if ((g->GetState().B & GAMEPAD_A) == GAMEPAD_A)
			break;

		Sleep(100);
	}

	delete g;

	return 0;
}

