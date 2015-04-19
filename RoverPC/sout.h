#pragma once

#include <SFML/Audio.hpp>

#define PEAKS_BIT 4
#define SAMPLES_BIT  (2 * PEAKS_BIT)
#define SAMPLES_BYTE (8 * SAMPLES_BIT)

#define SAMPLES_HANDSHAKE (36 * SAMPLES_BIT)

namespace RoverPC
{
	class sout
	{
	private:
		const unsigned __int32 sampleRate;
		sf::SoundBuffer * pBuffer;
		sf::Sound		* pSound;
		__int16			* pWavs;

		void AddByteToSignal(const unsigned __int8, __int16 *);
	public:
		sout(const unsigned __int32);
		~sout();

		void SetSignal(const char * , const size_t);
	};
}
