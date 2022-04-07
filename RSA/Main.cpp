#include <iostream>
#include <fstream>
#include <chrono>
#include "RSA.h"

// TODO: Ver-/Entschlüsselung
// TODO: Einlesen der Schlüssel
// TODO: Interface UI <-> RSA-Tool
// TODO: UI
// TODO: Komprimierung
// TODO: Doku

int main(int argc, char* argv[]) {
	/*auto startpoint = std::chrono::high_resolution_clock::now();
	uint2048_t* prime = new uint2048_t();
	RSA::genPrimeNumber(prime);
	auto endpoint = std::chrono::high_resolution_clock::now();
	auto time = endpoint - startpoint;
	std::cout << "done!" << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::seconds>(time) << " needed!\n";
	std::cout << std::hex << *prime << "\n\n" << std::dec << *prime << std::endl;

	delete prime;*/

	std::cout << "Calculating..." << std::endl;
	auto startpoint = std::chrono::high_resolution_clock::now();
	RSA::RSAKeys keys{};
	RSA::genKeys(keys);
	auto endpoint = std::chrono::high_resolution_clock::now();
	auto time = endpoint - startpoint;
	std::cout << "done!" << std::endl;
	std::cout << std::dec << std::chrono::duration_cast<std::chrono::seconds>(time) << " needed!\n";
	RSA::KeyPair publ(keys.N, keys.e);

	//RSA::KeyPair publ(nullptr, nullptr);
	size_t size;
	char* cstr = publ.encrypt("123456789", size);
	std::cout << cstr << std::endl;
	publ.key2 = keys.d;
	std::cout << publ.decrypt(cstr, size) << std::endl;

	return 0;
}