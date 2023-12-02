#include "lib/gpio.h"

void setup() {
	pinMode(BUILTIN_LED, OUTPUT);
}

void loop() {
	digitalWrite(BUILTIN_LED, HIGH);
	sleep_ms(1000);
	digitalWrite(BUILTIN_LED, LOW);
	sleep_ms(1000);
}

int main(){setup();for(;;)loop();return 0;};
