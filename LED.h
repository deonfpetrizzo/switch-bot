#ifndef LED_H
#define LED_H

class LED {
	public:
		byte ledPin;

	public:
		LED(byte ledPin) {
			this->ledPin = ledPin;
		}
		
		void init() {
			pinMode(ledPin, OUTPUT);
		}

		void changeState(byte state) {
			digitalWrite(ledPin, state);
		}
		
		void wait(byte state, byte t) {
		    changeState(state);
		    delay(t);
		}
};

#endif