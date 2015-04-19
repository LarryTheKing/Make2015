#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace RoverPC
{
	class Input
	{
	private:
		unsigned __int32 sampleRate;


	public:
		Input();
		~Input();

		void Run();
	};
}