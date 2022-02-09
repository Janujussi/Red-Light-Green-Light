// FILE: SegmentDisplay.h
// 	This class creates an object of 7 segment display and provides
// 	methods to change displayed number for Arduino.
//
// Author: Jan Morrison

#ifndef SEGMENTDISPLAY_H
#define SEGMENTDISPLAY_H

#include "Arduino.h"

class SegmentDisplay
{
	public:
		// Default Constructor
		SegmentDisplay();

		// Constructor
		SegmentDisplay(int pinA, int pinB, int pinC, int pinD, int pinE, int pinF, int pinG);

		// Destructor
		~SegmentDisplay();

		// Methods //
		// Display shows 0
		void zero();
		// Display shows 1
		void one();
		// Display shows 2
		void two();
		// Display shows 3
		void three();
		// Display shows 4
		void four();
		// Display shows 5
		void five();
		// Display shows 6
		void six();
		// Display shows 7
		void seven();
		// Display shows 8
		void eight();
		// Display shows 9
		void nine();
		// Gets current number shown on display
		int getNumber();

	private:
		int a, b, c, d, e, f, g;	// LEDs on the display
		int currentState;			// Current number shown on display
};

#endif