#include <stdint.h>
#include <iostream>
#include "../hamming.hpp"

int main(int argc, char* argv[])
{
	uint8_t encoded[16];
	srand(time(0));
	
	for(int ii = 0; ii < 16; ++ii) {
		encoded[ii] = Hamming::encode(ii);
	}
	
	for(int ii = 0; ii < 16; ++ii) {
		uint8_t toggle = 0x1;
		int rand_int = rand();
		double rand_double = static_cast<double>(rand_int);
		rand_double /= RAND_MAX / 8;
		rand_double -= 0.5;
		toggle <<= static_cast<int>(rand_double);
		
		rand_int = rand();
		if(rand_int > RAND_MAX / 2) {
			encoded[ii] = encoded[ii] & ~toggle;
		} else {
			encoded[ii] = encoded[ii] | toggle;
		}
	}
	
	for(int ii = 0; ii < 16; ++ii) {
		std::cout << Hamming::decode(encoded[ii]) << std::endl;
	}
	
	return 0;
}
