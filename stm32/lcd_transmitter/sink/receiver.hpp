#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include <xpcc/processing/protothread.hpp>
#include <xpcc/processing/periodic_timer.hpp>

class Receiver : private xpcc::pt::Protothread
{
public:
	Receiver();

	void
	initialize();

	bool
	run();

	void
	startReceive();

	uint8_t
	getResult();

private:

	uint8_t
	data;	// raw data that was received

	xpcc::Timeout<>
	delay;

};

#endif // RECEIVER_HPP
