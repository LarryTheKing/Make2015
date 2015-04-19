// RoverPC.cpp : Defines the entry point for the console application.
//

#include <thread>
#include <iostream>
#include "Gamepad.h"
#include "Input.h"
#include "Output.h"

#include <SFML/Audio.hpp>

int main(int argc, char* argv[])
{
	using namespace RoverPC;


	Gamepad * g = new Gamepad(0);

	Input * pIn = new Input();
	Output * pOut = new Output();

	std::thread iThread(&Input::Run, pIn);
	//iThread.join();

	// Test Gamepad
	while (true)
	{
		// Clear stream
		system("cls");

		g->Update();
		std::cout << g->GetState()._RAW;
		pOut->SetSignal(g->GetState());

		Sleep(100);
	}

	delete g;

	return 0;
}

