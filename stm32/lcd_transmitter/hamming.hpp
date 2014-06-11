#ifndef HAMMING_HPP
#define HAMMING_HPP

namespace Hamming
{

static constexpr uint8_t
hammingLut[16] = {
0b00000000,	// 0
0b00001011,	// 1
0b00010110,	// 2
0b00011101,	// 3
0b00100111,	// 4
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

static int
decode(uint8_t data) {
	int cur_distance, min_distance = 8;
	uint8_t data_copy, hamming_word;
	int index = 0;
	
	for(int ii = 0; ii < 16; ++ii) {
		cur_distance = 0;
		data_copy = data;
		hamming_word = hammingLut[ii];
		for(int jj = 0; jj < 8; ++jj) {
			cur_distance += (static_cast<bool>(data_copy & 0x1) !=
				static_cast<bool>(hamming_word & 0x1));
			data_copy = data_copy >> 1;
			hamming_word = hamming_word >> 1;
		}
		
		if(cur_distance < min_distance) {
			min_distance = cur_distance;
			index = ii;
		}
	}
	return index;
}

}


#endif // HAMMING_HPP
