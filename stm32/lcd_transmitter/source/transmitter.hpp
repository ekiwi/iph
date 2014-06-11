#ifndef TRANSMITTER_HPP
#define TRANSMITTER_HPP

#include <xpcc/processing/protothread.hpp>
#include <xpcc/processing/periodic_timer.hpp>

class Transmitter : private xpcc::pt::Protothread
{
public:
	Transmitter();

	void
	initialize();

	bool
	run();

	void
	sendPrefix();

	void
	sendData(uint8_t);

private:

	uint8_t
	data;	// raw data to be sent

	xpcc::PeriodicTimer<>
	delay;

};

#endif // TRANSMITTER_HPP
