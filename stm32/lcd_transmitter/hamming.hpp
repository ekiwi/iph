#ifndef HAMMING_HPP
#define HAMMING_HPP

namespace Hamming
{

static constexpr uint8_t
hammingLut[16] = {
0b00000000,	// 0
0b00001011,	// 1
0b00010110,	// 2
0b00100111,	// 3
0b00101100,	// 4
0b00101100,	// 5
0b00110001,	// 6
0b00111010,	// 7
0b01000101,	// 8
0b01001110,	// 9
0b01010011,	// 10
0b01011000,	// 11
0b01100010,	// 12
0b01101001,	// 13
0b01110100,	// 14
0b01111111,	// 15
};

// encodes least significant 4 bits
static uint8_t
encode(uint8_t data) {
	return(hammingLut[data & 0xf]);
}



}


#endif // HAMMING_HPP
