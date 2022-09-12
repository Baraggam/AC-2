// C++ code
//

int entrada = 0,
	A = 0,
	B = 0,
	OP = 0,
	saida = 0,
	vai1 = 0;

void setup()
{
	Serial.begin(9600);
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);
	digitalWrite(10, LOW);
	digitalWrite(11, LOW);
	digitalWrite(12, LOW);
	digitalWrite(13, LOW);
}

void loop()
{
	if (Serial.available() > 0)
	{
		entrada = Serial.parseInt();
		A = (entrada / 100) % 10; // Centena
		B = (entrada / 10) % 10;  // Dezena
		OP = entrada % 10;		  // Unidade
		vai1 = 0;
		switch (OP)
		{
		case 0:
			saida = portaand();
			break;
		case 1:
			saida = portaor();
			break;
		case 2:
			saida = portanot();
			break;
		case 3:
			saida = portasoma();
			break;
		default:
			break;
		}
		mostrar();
	}
}

void mostrar()
{
	apagar();
	digitalWrite(10, vai1);
	digitalWrite(11, saida);
	digitalWrite(12, B);
	digitalWrite(13, A);
}

int portaand()
{
	return (A & B);
}

int portaor()
{
	return (A | B);
}

/*
** O comando "& 0x1" é uma maneira de analisar
** o 1 bit relevante e retornar o valor negado
*/
int portanot()
{
	return ~A & 0x1;
}

int portasoma()
{
	vai1 = (A + B) / 2;
	return ((A + B) % 2);
}

void apagar()
{
	digitalWrite(10, LOW);
	digitalWrite(11, LOW);
	digitalWrite(12, LOW);
	digitalWrite(13, LOW);
}