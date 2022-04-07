#include "RSA.h"
#define max(a, b) (a < b ? b : a)
#define CALC_SIZE(size, divisor) (8 * (size % divisor ? size / divisor + 2 : size / divisor + 1))

RSA::KeyPair::KeyPair(uint2048_t* N, uint2048_t* key2) {
	this->N = N;
	this->key2 = key2;
}

RSA::RSAKeys::RSAKeys() {
	this->N = new uint2048_t(0);
	this->e = new uint2048_t(0);
	this->d = new uint2048_t(0);
}

char* RSA::KeyPair::encrypt(std::string s, size_t& size) {
	size = CALC_SIZE(s.size(), 8); // = 8 * (size / 8 + 1) + 8
	char* cstr = new char[size]('\0');

	for (size_t t = 0; t < s.size(); t++)
		cstr[t] = s[t];
	
	uint2048_t tmp = 0;
	for (uint64_t* num = (uint64_t*)cstr; *num; num++) {
		tmp = BRSA::powm((uint2048_t)*num, *this->key2, *this->N);
		*num = tmp.convert_to<uint64_t>();
	}

	return cstr;
}


std::string RSA::KeyPair::decrypt(char* cstr, size_t size) {
	uint2048_t tmp = 0;
	for (uint64_t* num = (uint64_t*)cstr; *num; num++) {
		tmp = BRSA::powm((uint2048_t)*num, *this->key2, *this->N);
		*num = tmp.convert_to<uint64_t>();
	}

	std::string ret = "";

	for (size_t t = 0; t < size; t++)
		ret += cstr[t];

	return cstr;

	//str[t / 4] = BRSA::powm(uint2048_t(str[t / 4]), this->key2->convert_to<uint2048_t>(), *this->N).convert_to<uint32_t>();
}

// /* this funktion was to slow */
//uint2048_t* RSA::genPrimeNumber() {
//	random::mt11213b base_gen(clock());
//	random::independent_bits_engine<random::mt11213b, RSA_BITCOUNT, uint2048_t> gen(base_gen);
//	//
//	// We must use a different generator for the tests and number generation, otherwise
//	// we get false positives.
//	//
//	random::mt19937 gen2(clock());
//
//	std::cout << "Starting with search... " << std::endl;
//
//	uint2048_t n;
//	for (unsigned t = 0; t < 100000; t++) {
//		n = gen();
//		if (miller_rabin_test(n, 25, gen2)) {
//			std::cout << "[iteration " << std::setw(6) << std::setfill('0') << std::dec << t << "]  found a probable prime with value: " << std::hex << std::showbase << n << std::endl;
//			if (miller_rabin_test((n - 1) / 2, 25, gen2)) {
//				uint2048_t ret = n.convert_to<uint2048_t>();
//				std::cout << "[itertation " << std::setw(6) << std::setfill('0') << std::dec << t << "]  save prime found: " << std::hex << std::showbase << n << std::endl;
//				return &ret;
//			}
//		}
//	}
//
//	std::cout << "No prime number found!" << std::endl;
//	return new uint2048_t(0);
//}

//std::shared_mutex primes_mutex;

// the first 255 primes
uint16_t first_primes[] = {
	   3,    5,    7,   11,   13,   17,   19,   23,   29,   31,   37,   41,   43,   47,   53,   59,
	  61,   67,   71,   73,   79,   83,   89,   97,  101,  103,  107,  109,  113,  127,  131,  137,
	 139,  149,  151,  157,  163,  167,  173,  179,  181,  191,  193,  197,  199,  211,  223,  227,
	 229,  233,  239,  241,  251,  257,  263,  269,  271,  277,  281,  283,  293,  307,  311,  313,
	 317,  331,  337,  347,  349,  353,  359,  367,  373,  379,  383,  389,  397,  401,  409,  419,
	 421,  431,  433,  439,  443,  449,  457,  461,  463,  467,  479,  487,  491,  499,  503,  509,
	 521,  523,  541,  547,  557,  563,  569,  571,  577,  587,  593,  599,  601,  607,  613,  617,
	 619,  631,  641,  643,  647,  653,  659,  661,  673,  677,  683,  691,  701,  709,  719,  727,
	 733,  739,  743,  751,  757,  761,  769,  773,  787,  797,  809,  811,  821,  823,  827,  829,
	 839,  853,  857,  859,  863,  877,  881,  883,  887,  907,  911,  919,  929,  937,  941,  947,
	 953,  967,  971,  977,  983,  991,  997, 1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051,
	1061, 1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171,
	1181, 1187, 1193, 1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289,
	1291, 1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423, 1427,
	1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511, 1523,
	1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619, NULL
};

// if(miller_rabin_test((test--) / 2, 25, *gen2)) return true; // we would lost many primes

__forceinline bool isPrime(uint2048_t* n, uint2048_t* a) {
	// kleiner Satz von Fermat
	// n is a prim
	// for every a from Z is a^(p-1) = 1 mod p if p is not an deivisor of a
	for (uint16_t* t = first_primes; *t; t++)
		if (!(*n % *t)) return false;

	if (powm(*a, *n - 1, *n) == 1) {
		random::mt19937 gen2(std::clock());
		if (miller_rabin_test(*n, 10, gen2))
			return true;
		return false;
	}
	return false;
}

void RSA::genPrimeNumber(uint2048_t* n) {
	size_t tmp = 0;
	random::mt11213b base_gen{  };
	random::independent_bits_engine<random::mt11213b, RSA_BITCOUNT, uint2048_t> gen{ base_gen };
	uint2048_t a;
	for (;;) {
		// We must use a different generator for the tests and number generation, otherwise we get false positives.
		base_gen.seed(std::time(NULL));
		gen.seed(std::time(NULL));

		*n = gen();
		a = gen();
		a %= (*n - 2);	// a < n
		a += 2;			// 1 < a

		if (!((*n) % 2))
			(*n)++;

		for (size_t t = 0; t < 60; t++, (*n) += 2) {
			if (isPrime(n, &a)) {
				std::cout << "iteration: " << t << ", tmp: " << tmp << std::endl;
				std::cout << std::hex << *n << std::endl;
				return;
			}
		}

		tmp++;
	}
}

void ce(RSA::RSAKeys& keys, uint2048_t& phi_N) {
	*keys.e = max(*keys.e, *keys.d);
	//uint2048_t res = 0;

	{	random::mt19937 gen(std::clock());
		*keys.e += uint64_t(gen());
		if (!(*keys.e % 2)) (*keys.e)++;
	}

	
	do (*keys.e) += 2;
	while (	boost::integer::gcd(*keys.e, phi_N) != 1 ||
			boost::integer::gcd(*keys.e, *keys.N) != 1	);
}

// a = phi(N)
// t = d
// b = e
//uint2048_t extended_euclid(uint2048_t a, uint2048_t b, uint2048_t* t)
void extended_euclid(uint2048_t& phi_N, uint2048_t& e, uint2048_t* d)
{
	int2048_t s = 1, u = 0, v = 1, q, b1, v1, u1;
	int2048_t a = phi_N.convert_to<int2048_t>(), b = e.convert_to<int2048_t>(), t = 0;
	while (b != 0) {
		q = a / b;
		b1 = b; // Variable zum Zwischenspeichern
		b = a - q * b;
		a = b1;
		u1 = u; // Variable zum Zwischenspeichern
		u = s - q * u;
		s = u1;
		v1 = v; // Variable zum Zwischenspeichern
		v = t - q * v;
		t = v1;
	}

	*d = t.convert_to<uint2048_t>();
	//return a;
}

void euclid(uint2048_t& a, uint2048_t phi_N)
{
	if (a == 0) {
		a = phi_N;
		return;
	}

	while (phi_N != 0) {
		uint2048_t h = a % phi_N;
		a = phi_N;
		phi_N = h;
	}
}

// a = e, b = phi(N)
uint2048_t cd(uint2048_t& e, uint2048_t& phi_N) {
	/*uint2048_t k = e / phi_N - 1;
	return ((k * phi_N) + 1) / e;*/
	// k * phi(N) + 1 % e = 0
	// k * phi(N) + 1 = e
	// e / phi(N) - 1 = k
	// e * d mod phi(N) = 1

	random::mt19937 gen(std::clock());

	for (uint2048_t d = uint32_t(gen()) * phi_N; ; d += e)
		if (d % phi_N == 1) return d / e;

	/*uint2048_t k = 1;
	while ((k * phi_N + 1) % e != 0) k++;
	return ((k * phi_N) + 1) / e;*/
}

void RSA::genKeys(RSA::RSAKeys& keys)
{
	// generate p and q
	//std::cout << "Calculate primes p and q ...";
	//std::thread t0(&genPrimeNumber, keys.d);						// p
	//std::thread t1(&genPrimeNumber, keys.e);						// q
	//t0.join();
	//t1.join();
	genPrimeNumber(keys.d);
	genPrimeNumber(keys.e);

	if (*keys.d == *keys.e) genPrimeNumber(keys.e);					// p != q	
	
	std::cout << " done!\n";
	std::cout << "Calculate RSA-Module N ...";

	// calc N
	*keys.N = (*keys.d) * (*keys.e);								// N = p * q

	std::cout << " done!\n";
	std::cout << std::hex << *keys.N << std::endl;
	std::cout << "\nCalculate phi(N) ...";
	
	// calc phi(N)
	uint2048_t phi_N = ((*keys.d) - 1) * ((*keys.e) - 1);			// phi(N) = (p - 1) * (q - 1)
	
	std::cout << " done!\n";
	std::cout << std::hex << phi_N << std::endl;
	std::cout << "Calculate e ...";

	// generate e
	ce(keys, phi_N);
	//euclid(*keys.e, phi_N);

	std::cout << " done!\n";
	std::cout << std::hex << *keys.e << std::endl;
	std::cout << "Calculate d ...";

	// (e * d) mod phi(N) = 1
	// e * d = 1 mod phi(N)
	// 1 mod phi(N) / e = d
	//extggt(*keys.e, phi_N); // (1 % phi_N) / *keys.e;
	*keys.d = cd(*keys.e, phi_N);
	extended_euclid(phi_N, *keys.e, keys.d);

	std::cout << " done!\n";
	std::cout << std::hex << *keys.d << std::endl;

	return;
}