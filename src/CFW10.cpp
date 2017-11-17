#include <Arduino.h>

#include "../lib/CFW10.h"

#define CFW10_SS_PIN 29 // Start/Stop Pin
#define CFW10_RL_PIN 30 // Right/Left Pin
#define CFW10_GE_PIN 31 // General Enable Pin
#define CFW10_CKWS_PIN 32 // Clockwise/Counter-Clockwise select pin
#define CFW10_A0_PIN 13

void cfw10_setup(void) {

	pinMode(CFW10_SS_PIN, OUTPUT);
	pinMode(CFW10_RL_PIN, OUTPUT);
	pinMode(CFW10_GE_PIN, OUTPUT);
	pinMode(CFW10_CKWS_PIN, OUTPUT);
	pinMode(CFW10_A0_PIN, OUTPUT);

	digitalWrite(CFW10_GE_PIN, LOW);

}

void cfw10_start(double val) {

	analogWrite(CFW10_A0_PIN, (unsigned int) (val * 255.00) );

	delay(100);

	digitalWrite(CFW10_GE_PIN, LOW);
	digitalWrite(CFW10_RL_PIN, LOW);
	digitalWrite(CFW10_CKWS_PIN, LOW);
	digitalWrite(CFW10_SS_PIN, HIGH);
	digitalWrite(CFW10_GE_PIN, HIGH);

}

void cfw10_stop(void) {

	digitalWrite(CFW10_SS_PIN, LOW);
	digitalWrite(CFW10_GE_PIN, LOW);

}
