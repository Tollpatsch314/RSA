#include "BigInt.h"

uint32_t* gp_tmp;
const uint32_t null32 = 0;

BigInt::BigInt(bool is_signed) {
	this->flags = NULL;
	if (!is_signed) this->flags = BIGINT_FORCED_UNSIGNED;
	for (uint8_t t = 0; t < 32; t++) {
		this->elements[t] = null32;
		this->elements[(t++)] = null32;
		this->elements[(t++)] = null32;
		this->elements[(t++)] = null32;
	}
}

BigInt::BigInt(BigInt* copy) {
	this->flags = copy->flags;
	for (uint8_t t = 0; t < 32; t++) {
		this->elements[t] = copy->elements[t];
		this->elements[(t++)] = copy->elements[(t++)];
		this->elements[(t++)] = copy->elements[(t++)];
		this->elements[(t++)] = copy->elements[(t++)];
	}
}

void BigInt::set(BigInt* num) {
	*this = BigInt(num);
}

void BigInt::inc() {
	for (uint8_t t = 0; t < 32; t++) {
		if (this->elements[t] != BIGINT_BLOCK_MAX && !(this->flags & BIGINT_SIGNET)) {
			this->elements[t]++;
			return;
		}
		else if (this->elements[t] != null32 && this->flags & BIGINT_SIGNET) {
			this->elements[t]--;
			if (t == 31 && this->elements == 0) this->flags &= ~BIGINT_SIGNET;
			return;
		}
		else this->elements[t] = null32;
	}
}

void BigInt::dec() {
	for (uint8_t t = 0; t < 32; t++) {
		if (this->elements[t] != null32 && !(this->flags & BIGINT_SIGNET)) {
			this->elements[t]--;
			return;
		}
		else if (this->elements[t] != BIGINT_BLOCK_MAX && this->flags & BIGINT_SIGNET) {
			this->elements[t]++;
			if (t == 31 && this->elements[t] == BIGINT_BLOCK_MAX); // TODO: Overflow ?
			return;
		}
		else this->elements[t] = null32;
	}
}

void BigInt::add(BigInt* num) {

}

void BigInt::sub(BigInt* num) {

}

void BigInt::mul(BigInt* num) {

}

void BigInt::div(BigInt* num) {

}

BigInt* BigInt::mod(BigInt* num) {

}

bool BigInt::equals(BigInt* num) {

}

bool BigInt::greater(BigInt* num) {

}

bool BigInt::less(BigInt* num) {

}


