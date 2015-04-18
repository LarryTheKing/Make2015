#pragma once

#define GAMEPAD_A 0x01
#define GAMEPAD_B 0x02
#define GAMEPAD_X 0x04
#define GAMEPAD_Y 0x08
#define GAMEPAD_DPAD_UP		0x10
#define GAMEPAD_DPAD_DOWN	0x20
#define GAMEPAD_DPAD_LEFT	0x40
#define GAMEPAD_DPAD_RIGHT	0x80

#define GAMEPAD_BYTES 8


namespace RoverPC
{
	struct GamepadState
	{
		union
		{
			//unsigned __int64	_RAW;	// RAW data
			unsigned char		_ARRAY[8];	// Data as array of uint8
			struct{
				char LX;				// Left Thumstick X
				char LY;				// Left Thumstick Y
				char RX;				// Right Thumstick X
				char RY;				// Right Thumstick Y
				unsigned char LT;		// Left Trigger
				unsigned char RT;		// Right Trigger
				unsigned char B;		// Buttons
				unsigned char CS;		// Checksum
			};
		};
	};

}
