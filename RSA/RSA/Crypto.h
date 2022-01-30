#pragma once


/*
* Problem:
* Zahl N, hat mehrere hunderte dezimalstellen
* p & q sind Primzahlen (auch verdammt groß)
* N = p * q
* 
*/

/*
* RSA Schlüssel:
* 1) Nimm zwei (sehr, sehr große) Primzahlen p und q
* 2) Bilde das RSA_Modul N = p * q
* 3) Bestimme phi(N) = phi(p * q) = phi(p) * phi(q) = (p-1) * (q-1)
* 4) Wähle eine Zahl e mit 1 < e < phi(N) mit ggT(e, phi(N)) = 1
*    -> Jetzt bilden (e, N) den öffentlichen Schlüssel
* 5) Bestimme d mit e * d ist kongurent 1 mod phi(N)
*    => e * d + K * phi(N) = 1 -> erweiterte euglidische Algorithmus
*    -> Jetzt bilden (d, N) den privaten Schlüssel
*/

/*
* G = T^e mod N
* T = G^e mod N
*/

typedef struct Keys
{
	int N;

	typedef struct Public {
		int e;
	};

	typedef struct Private {
		int d;
		// not important
		//int p, q, phi_of_n;
	};
};

Keys* gen_RSAKeys(int p, int q);

void RSA(int p, int q);