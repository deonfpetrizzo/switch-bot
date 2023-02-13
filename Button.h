#ifndef BUTTON_H
#define BUTTON_H

class Button {
	private:
		byte buttonPin;

	public:
		Button(byte buttonPin) {
			this->buttonPin = buttonPin;
		}

		void init() {
			pinMode(buttonPin, INPUT);
		}

		bool isPressed() {
			return digitalRead(buttonPin);
		}
};

#endif