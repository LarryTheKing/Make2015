#include "Output.h"

namespace RoverPC
{
	Output::Output()
	{
		pSignal = new sout(SAMPLE_RATE);
		pGamepad = new Gamepad(0);
	}


	Output::~Output()
	{
		if (pSignal)
			delete pSignal;
		pSignal = nullptr;

		if (pGamepad)
			delete pGamepad;
		pGamepad= nullptr;

		Stop();	
	}

	void Output::Update()
	{
		pGamepad->Update();
		if (pGamepad->GetState()._RAW == oldState._RAW)
			return;

		oldState._RAW = pGamepad->GetState()._RAW;

		pSignal->SetSignal(reinterpret_cast<const char *>(&oldState), sizeof(GamepadState));
	}

	void OutputLoop(Output * pOut)
	{
		// Update Gamepad
		while (true)
		{
			pOut->Update();
			Sleep(GAMEPAD_SLEEP);
		}
	}

	void Output::Run()
	{
		pThread = new std::thread(&OutputLoop, this);
	}

	void Output::Stop()
	{
		if (pThread){
			pThread->join();
			delete pThread;
			pThread = nullptr;
		}
	}
}