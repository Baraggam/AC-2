import java.io.*;

/*
 * RandomAccessFile é usado para abrir e percorrer o arquivo de entrada linha por linha;
 * FileWriter é usado para criar (ou substituir) e acrescentar ao arquivo de saída;
 */

public class TP3 {

	/*
	 * Abre o arquivo de entrada e cria o arquivo de saída;
	 * Lê as linhas e converte os caracteres em hexadecimal para seu valor em inteiro
	 * Une os dados e joga para o arquivo de saída no formato hexadecimal
	 */
	public static void main(String args[]) {
		try {
			RandomAccessFile entrada = new RandomAccessFile(
				"testeula.ula",
				"r"
			);
			FileWriter saida = new FileWriter("testeula.hex");
			saida.write("");
			int X = 0, Y = 0, W = 0;
			String palavra = entrada.readLine();
			while (!palavra.equals("inicio:")) { // Caso o arquivo contenha linhas desnecessárias antes dos valores úteis
				palavra = entrada.readLine();
			}
			palavra = entrada.readLine();
			while (!palavra.equals("fim.")) { // Lendo todas as linhas antes do comando "fim."
				String dados[] = palavra.split("=");
				if (dados[0].equals("X")) {
					X = charToInt(dados[1].charAt(0));
				} else if (dados[0].equals("Y")) {
					Y = charToInt(dados[1].charAt(0));
				} else {
					W = analisador(dados[1].replaceAll(";", ""));
					saida.append(String.format("%X%X%X\n", X, Y, W));
				}
				palavra = entrada.readLine();
			}
			entrada.close();
			saida.close();
		} catch (Exception e) {
			System.out.println(e);
			System.out.println("O arquivo não possui dados válidos");
		}
	}

	// Converte a letra em hexadecimal para um número inteiro
	public static int charToInt(char c) {
		int resp = 0;
		if (c >= '0' && c <= '9') {
			resp = c - '0';
		} else {
			resp = c - 'A' + 10;
		}
		return resp;
	}

	// Converte o mnemônico em um número hexadecimal
	public static int analisador(String s) {
		int resp = 0x0;
		switch (s) {
			case "An":
				resp = 0x0;
				break;
			case "nAoB":
				resp = 0x1;
				break;
			case "AnB":
				resp = 0x2;
				break;
			case "zeroL":
				resp = 0x3;
				break;
			case "nAeB":
				resp = 0x4;
				break;
			case "Bn":
				resp = 0x5;
				break;
			case "AxB":
				resp = 0x6;
				break;
			case "ABn":
				resp = 0x7;
				break;
			case "AnoB":
				resp = 0x8;
				break;
			case "nAxB":
				resp = 0x9;
				break;
			case "copiaB":
				resp = 0xa;
				break;
			case "AB":
				resp = 0xb;
				break;
			case "umL":
				resp = 0xc;
				break;
			case "AoBn":
				resp = 0xd;
				break;
			case "AoB":
				resp = 0xe;
				break;
			case "copiaA":
				resp = 0xf;
				break;
			default:
				break;
		}
		return resp;
	}
}
