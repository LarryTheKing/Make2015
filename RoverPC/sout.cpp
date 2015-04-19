#include "sout.h"

namespace RoverPC
{
	sout::sout(const unsigned __int32 rate)
		:sampleRate(rate)
	{
		pBuffer = new sf::SoundBuffer();
		pSound = new sf::Sound();

		// Generate wave shapes
		pWavs = new __int16[2 * SAMPLES_BIT];

		// Zero Bit Wave
		for (int i = 0; i < PEAKS_BIT; i++){
			pWavs[i] = _I16_MAX; }

		for (int i = PEAKS_BIT; i < 2 * PEAKS_BIT; i++){
			pWavs[i] = _I16_MIN; }

		// One Bit Wave
		for (int i = SAMPLES_BIT; i < 2 * SAMPLES_BIT; i++){
			pWavs[i++] = _I16_MAX;
			pWavs[i] = _I16_MIN;
		}
		
	}


	sout::~sout()
	{
		if (pBuffer)
			delete pBuffer;
		pBuffer = nullptr;

		if (pSound)
			delete pSound;
		pSound = nullptr;

		if (pWavs)
			delete pWavs;
		pWavs = nullptr;
		
	}

#define NSAMPLES_BIT

	void sout::AddByteToSignal(const unsigned __int8 b, __int16 * pData)
	{
		memcpy(pData, (b & 0x01) ? pWavs + SAMPLES_BIT : pWavs, SAMPLES_BIT * sizeof(__int16));
		pData += SAMPLES_BIT;
		memcpy(pData, (b & 0x02) ? pWavs + SAMPLES_BIT : pWavs, SAMPLES_BIT * sizeof(__int16));
		pData += SAMPLES_BIT;
		memcpy(pData, (b & 0x04) ? pWavs + SAMPLES_BIT : pWavs, SAMPLES_BIT * sizeof(__int16));
		pData += SAMPLES_BIT;
		memcpy(pData, (b & 0x08) ? pWavs + SAMPLES_BIT : pWavs, SAMPLES_BIT * sizeof(__int16));
		pData += SAMPLES_BIT;
		memcpy(pData, (b & 0x10) ? pWavs + SAMPLES_BIT : pWavs, SAMPLES_BIT * sizeof(__int16));
		pData += SAMPLES_BIT;
		memcpy(pData, (b & 0x20) ? pWavs + SAMPLES_BIT : pWavs, SAMPLES_BIT * sizeof(__int16));
		pData += SAMPLES_BIT;
		memcpy(pData, (b & 0x40) ? pWavs + SAMPLES_BIT : pWavs, SAMPLES_BIT * sizeof(__int16));
		pData += SAMPLES_BIT;
		memcpy(pData, (b & 0x80) ? pWavs + SAMPLES_BIT : pWavs, SAMPLES_BIT * sizeof(__int16));
		pData += SAMPLES_BIT;
	}

	void sout::SetSignal(const char * pData, const size_t byteSize)
	{
		const size_t sample_count = (byteSize * SAMPLES_BYTE) + SAMPLES_HANDSHAKE;
		__int16 * pSamples = new __int16[sample_count];
		
		// Make the handshake
		for (int i = 0; i < SAMPLES_HANDSHAKE; i++)
			pSamples[i] = 0;
			
		// Add each byte
		__int16 * pCurrent = pSamples + SAMPLES_HANDSHAKE;
		for (int i = 0; i < byteSize; i++){
			AddByteToSignal(pData[i], pCurrent);
			pCurrent += SAMPLES_BYTE;
		}

		// Generate audio buffer
		pBuffer->loadFromSamples(pSamples, sample_count, 1, sampleRate);

		pSound->stop();
		pSound->setBuffer(*pBuffer);
		pSound->setLoop(true);
		pSound->play();
	}
}