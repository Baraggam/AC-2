// C++ code
//

String memoria[100]; // String com todos os dados inseridos com tamanho máximo 100 dados
char entrada = '*';
int X = 0,
	Y = 0,
	OP = 0,
	saida = 0,
	PC = 4,
	tam = 0; // Quantidade de comandos inseridos

void setup()
{
	Serial.begin(9600);
	pinMode(10, OUTPUT); // Azul
	pinMode(11, OUTPUT); // Verde
	pinMode(12, OUTPUT); // Amarelo
	pinMode(13, OUTPUT); // Vermelho
	digitalWrite(10, LOW);
	digitalWrite(11, LOW);
	digitalWrite(12, LOW);
	digitalWrite(13, LOW);
}

void loop()
{
	if (Serial.available() > 0)
	{
		entrada = toupper(Serial.read());
		if (entrada == 'S') // Verifica se a pessoa digitou "S"
		{
			tam /= 3;
			fill();
			mostrar();
			resetar();
		}
		else if ((entrada >= '0' && entrada <= '9') || (entrada >= 'A' && entrada <= 'F'))
		{
			if (tam % 3 == 0)
			{
				memoria[(tam / 3) + 4] = entrada;
			}
			else
			{
				memoria[(tam / 3) + 4] += entrada;
			}
			tam++;
		}
	}
}

// Preence os primeiros valores da memoria com os dados certos
void fill()
{
	memoria[0] = '4';
	memoria[1] = '*';
	memoria[2] = '*';
	memoria[3] = '*';
}

// Retorna para os valores iniciais para nova execução
void resetar()
{
	Serial.println("=====");
	PC = 4;
	tam = 0;
}

void mostrar()
{
	String tela = "->| " + memoria[0];
	for (int i = 1; i < tam + 4; i++)
	{
		tela += " | " + memoria[i];
	}
	Serial.println(tela);
	for (int i = 4; i < tam + 4; i++)
	{
		delay(2000);
		decoder(memoria[i]);
		calculadora();
		memoria[0] = String(PC++, HEX);
		memoria[1] = String(saida, HEX);
		memoria[2] = String(X, HEX);
		memoria[3] = String(Y, HEX);
		maiuscula();
		digitalWrite(10, primeiroBit(saida, 0));
		digitalWrite(11, primeiroBit(saida, 1));
		digitalWrite(12, primeiroBit(saida, 2));
		digitalWrite(13, primeiroBit(saida, 3));
		tela = "->| " + memoria[0];
		for (int j = 1; j < tam + 4; j++)
		{
			tela += " | " + memoria[j];
		}
		Serial.println(tela);
	}
}

// Separa os valores para o cálculo
void decoder(String dados)
{
	X = charToInt(dados.charAt(0));
	Y = charToInt(dados.charAt(1));
	OP = charToInt(dados.charAt(2));
}

// Converte a letra em hexadecimal em um número inteiro
int charToInt(char c)
{
	int resp = 0;
	if (c >= '0' && c <= '9')
	{
		resp = c - '0';
	}
	else
	{
		resp = c - 'A' + 10;
	}
	return resp;
}

// Coloca as letras do arranjo de mémoria em maiúsculas
void maiuscula()
{
	for (int i = 0; i < 4; i++)
	{
		memoria[i].toUpperCase();
	}
}

// Retorna apenas o valor do primeiro bit do número
int primeiroBit(int i, int n)
{
	return i >> n & 0x1;
}

// O comando "& 0xf" é uma maneira de analisar os 4 bits relevantes e retornar o valor negado
int negate(int i)
{
	return ~i & 0xf;
}

// Envia os valores para o cálculo desejado
void calculadora()
{
	switch (OP)
	{
	case 0x0:
		porta0();
		break;
	case 0x1:
		porta1();
		break;
	case 0x2:
		porta2();
		break;
	case 0x3:
		porta3();
		break;
	case 0x4:
		porta4();
		break;
	case 0x5:
		porta5();
		break;
	case 0x6:
		porta6();
		break;
	case 0x7:
		porta7();
		break;
	case 0x8:
		porta8();
		break;
	case 0x9:
		porta9();
		break;
	case 0xA:
		portaA();
		break;
	case 0xB:
		portaB();
		break;
	case 0xC:
		portaC();
		break;
	case 0xD:
		portaD();
		break;
	case 0xE:
		portaE();
		break;
	case 0xF:
		portaF();
		break;
	default:
		break;
	}
}

void porta0()
{
	saida = negate(X);
}

void porta1()
{
	saida = negate(X | Y);
}

void porta2()
{
	saida = negate(X) & Y;
}

void porta3()
{
	saida = 0x0;
}

void porta4()
{
	saida = negate(X & Y);
}

void porta5()
{
	saida = negate(Y);
}

void porta6()
{
	saida = X ^ Y;
}

void porta7()
{
	saida = X & negate(Y);
}

void porta8()
{
	saida = negate(X) | Y;
}

void porta9()
{
	saida = negate(X ^ Y);
}

void portaA()
{
	saida = Y;
}

void portaB()
{
	saida = X & Y;
}

void portaC()
{
	saida = 0Xf;
}

void portaD()
{
	saida = X | negate(Y);
}

void portaE()
{
	saida = X | Y;
}

void portaF()
{
	saida = X;
}