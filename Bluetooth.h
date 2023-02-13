#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <SoftwareSerial.h>
#include "LED.h"

class Bluetooth : private SoftwareSerial {
	private: 	
		byte rxPin; 
		byte txPin;
		byte size;

	public:
		Bluetooth(byte rxPin, byte txPin, byte size) : SoftwareSerial(rxPin, txPin) {
			this->rxPin = rxPin;
			this->txPin = txPin;
			this->size = size;
		}

		void init() {
			begin(9600);
		}

		void getData(byte data[], LED led) {
			byte index = 0;
			char startMarker = '<';
			char endMarker = '>';
			bool isRecieving = false;
      		unsigned long readStartTime = 0;

			while (available() > 0) {
        		if (index == 0) 
          			led.wait(HIGH, 500);

        		char incomingChar = read();

				if (incomingChar == startMarker) {
				    incomingChar = read();
				    isRecieving = true;
		    	}      

				if (isRecieving) {
					if (incomingChar != endMarker)
						data[index] = incomingChar - '0';
					else 
						isRecieving = false;
				} 

				index++;
			}
		}

		void sendData(int lumen, byte mode, byte toggleState) {
		  	String brightness = String(lumen);
		  	String modeStr = mode == 0 ? "BT" : "AUTO";
		  	String state = toggleState == 1 ? "HIGH" : "LOW"; 
		  	String out = "\nBRIGHTNESS: " + brightness + " lm\n" + "MODE: " + modeStr + "\n" + "STATE: " + state + "\n\n";

			for (byte i = 0; i < out.length(); i++)
				write(out.charAt(i));

			delay(500);
		}
};

#endif