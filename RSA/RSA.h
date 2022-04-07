#pragma once
#include <string>
#include <vector>
#include <thread>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/integer/common_factor_ct.hpp>


#define RSA_BITCOUNT 2048

namespace BRSA = boost::multiprecision;
namespace random = boost::random;
typedef BRSA::number<BRSA::cpp_int_backend<RSA_BITCOUNT, RSA_BITCOUNT, BRSA::cpp_integer_type::unsigned_magnitude, BRSA::unchecked, void>> uint2048_t;
typedef BRSA::number<BRSA::cpp_int_backend<RSA_BITCOUNT, RSA_BITCOUNT, BRSA::cpp_integer_type::signed_magnitude, BRSA::unchecked, void>> int2048_t;
//typedef BRSA::number<BRSA::cpp_int_backend<2*RSA_BITCOUNT, 2*RSA_BITCOUNT, BRSA::cpp_integer_type::unsigned_magnitude, BRSA::unchecked, void>> uint2048_t;


namespace RSA {

	struct KeyPair {
		uint2048_t* N;		/* RSA-module         */
		uint2048_t* key2;	/* public/private key */

		/// <summary>
		/// generate a key-pair, wich is needed for the (en/de)cryption
		/// </summary>
		/// <param name="N">The RSA-module N = p * q</param>
		/// <param name="key2">by public keys e (encryption), by private keys d (decrytion)</param>
		KeyPair(uint2048_t* N, uint2048_t* key2);
		char* encrypt(std::string, size_t&);
		std::string decrypt(char*, size_t);
	};

	struct RSAKeys {
		uint2048_t* N; /* RSA-module               */
		uint2048_t* e; /* public key (encryption)  */
		uint2048_t* d; /* private key (decryption) */

		RSAKeys();
	};

	uint2048_t& fromBase64(std::string);

	std::string toBase64(uint2048_t&);

	/// <summary>
	/// generates a 2048-Bit prime
	/// </summary>
	/// <param name="n">must be initialised, is the "return"-value</param>
	void genPrimeNumber(uint2048_t* n);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="RSAKeys&amp;">must be initialised, is the "return"-value</param>
	void genKeys(RSAKeys&);
};


