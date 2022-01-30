#pragma once
#include <cstdint>
#include <exception>

#define BIGINT_SIGNET			0b0000'0001
#define BIGINT_FORCED_UNSIGNED	0b0000'0010
#define BIGINT_BLOCK_MAX		0xFFFF'FFFF

struct BigInt {
	BigInt(bool is_signed = true);
	BigInt(BigInt* copy);
	~BigInt() = default;

	
	void set(BigInt* num);
	void inc();
	void dec();
	void add(BigInt* num);
	void sub(BigInt* num);
	void mul(BigInt* num);
	void div(BigInt* num);
	BigInt* mod(BigInt* num);

	bool equals(BigInt* num);
	bool greater(BigInt* num);
	bool less(BigInt* num);

protected:
	uint32_t elements[32];	// = 1024 Bit = 1,8 * 10^308
	uint8_t flags;
};

BigInt *add(BigInt *num0, BigInt *num1);
BigInt *sub(BigInt *minuend, BigInt *num1);
BigInt *mul(BigInt *num0, BigInt *num1);
BigInt *div(BigInt *quotient, BigInt *divisor);
BigInt *mod(BigInt *quotient, BigInt *divisor);

BigInt *pow(BigInt *base, BigInt *exponent);