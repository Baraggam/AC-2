// C++ code
//

int pulse, led;

void setup()
{
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);
	digitalWrite(10, LOW);
	digitalWrite(11, LOW);
	digitalWrite(12, LOW);
	digitalWrite(13, HIGH);
	pulse = 0;
	led = 0;
	delay(200); // 0,2 segundo
}

void loop()
{
	// Pulso do led azul
	pulse = ((pulse + 1) % 9);
	delay(800); // 0,8 segundo
	digitalWrite(10, HIGH);
	// Controle dos pulsos
	if (pulse < 3) // 3 segundos (3 pulsos)
	{
		led = 0;
	}
	else if (pulse < 7) // 4 segundos (4 pulsos)
	{
		led = 1;
	}
	else // 2 segundos (2 pulsos)
	{
		led = 2;
	}
	// Controle dos leds
	if (led == 0)
	{
		digitalWrite(11, LOW);
		digitalWrite(12, LOW);
		digitalWrite(13, HIGH);
	}
	else if (led == 1)
	{
		digitalWrite(11, HIGH);
		digitalWrite(12, LOW);
		digitalWrite(13, LOW);
	}
	else
	{
		digitalWrite(11, LOW);
		digitalWrite(12, HIGH);
		digitalWrite(13, LOW);
	}
	delay(200); // 0,2 segundo
	digitalWrite(10, LOW);
}