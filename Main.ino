#include <Arduino.h>
#include "PhotoResistor.h"
#include "Bluetooth.h"
#include "Toggler.h"
#include "LED.h"
#include "Button.h"

//Pin definitions
#define LED_PIN 2
#define LDR_PIN A0
#define SERVO_PIN 11
#define BUTTON_PIN 13

//LDR constants
#define VIN 5
#define R 10000
#define MAX_LUMEN 300
#define MIN_LUMEN 35
#define TAP_INTERVAL 100

//Servo constants
#define OFF_ANGLE 175
#define ON_ANGLE 40
#define SPEED_DELAY 10

//SoftwarSerial constants
#define TX_PIN 5
#define RX_PIN 6 
#define SIZE 2

enum Mode {BT, AUTO, INF, MAN};

Mode lastMode = 0;
byte data[SIZE] = {1, 0};

LED led = LED(LED_PIN);
Bluetooth bt = Bluetooth(RX_PIN, TX_PIN, SIZE);
Toggler toggler = Toggler(SERVO_PIN, OFF_ANGLE, ON_ANGLE, SPEED_DELAY);
PhotoResistor ldr = PhotoResistor(LDR_PIN, VIN, R, MAX_LUMEN, MIN_LUMEN, TAP_INTERVAL);
Button button = Button(BUTTON_PIN);

void setup() {
	Serial.begin(9600);
	led.init();
	toggler.init();
	bt.init();
	ldr.init();
	button.init();
}

void loop() {
  run();
}

void run() {
	static int newToggleState = 0;
	int lumen = ldr.read();

	bt.getData(data, led);
	Mode mode = data[0] == 0 ? BT : data[0] == 1 ? AUTO : INF;

	switch (mode) {
		case BT:
			newToggleState = data[1];
			break;
		case AUTO:
			newToggleState = lumen < MIN_LUMEN ? 1 : lumen > MAX_LUMEN ? 0 : toggler.getCurrentState();
			break;
		case INF:
			bt.sendData(lumen, lastMode, toggler.getCurrentState());
      		data[0] = lastMode; 
			break;
	}

	toggler.setToggleState(newToggleState);
	toggler.toggle(led);

	led.changeState(LOW);
	toggler.update();
	lastMode = mode;
}
