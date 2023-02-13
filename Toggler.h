#ifndef TOGGLER_H
#define TOGGLER_H

#include <Servo.h>
#include "LED.h"

class Toggler : private Servo {
	private: 
		byte servoPin;
		byte offAngle;
		byte onAngle;
		byte speedDelay;

		byte toggleState = 0;
		byte lastToggleState = 0;
		bool hasToggled = false;

	public:
		Toggler(byte servoPin, byte offAngle, byte onAngle, byte speedDelay) {
			this->servoPin = servoPin;
			this->offAngle = offAngle;
			this->onAngle = onAngle;
			this->speedDelay = speedDelay;
		}

		void init() {
			attach(servoPin);
		}

		void toggle(LED led) {
		  	if (toggleState == 1 && !hasToggled) {
		    	for (byte i = offAngle; i > onAngle; i--) {
		      		write(i);
		      		led.wait(HIGH, speedDelay);
		    	}
		  	}
			else if (toggleState == 0 && !hasToggled) {
		    	for (byte i = onAngle; i < offAngle; i++) {
		      		write(i);
		      		led.wait(HIGH, speedDelay);
		    	}
		  	}
		}

		void update() {
			hasToggled = toggleState != lastToggleState && toggleState != 2 ? false : true;
			lastToggleState = toggleState;
		}

		byte getCurrentState() {
			return read() > (offAngle - 5) ? LOW : HIGH;
		}

		void setToggleState(byte toggleState) {
			this->toggleState = toggleState;
		}
};

#endif