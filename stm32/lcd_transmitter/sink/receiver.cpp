#include "receiver.hpp"
#include "../settings.hpp"
#include "../hamming.hpp"

#include <xpcc/architecture/platform.hpp>
#include <xpcc/debug/logger.hpp>

using namespace xpcc::stm32;

typedef GpioInputA5 ReceivePin;


Receiver::Receiver()
: delay(0)
{
	this->stop();
}

void
Receiver::initialize()
{
	ReceivePin::setInput();
}


bool
Receiver::run()
{
	static bool bit;
	static int ii;

	PT_BEGIN();

	// wait for falling edge
	PT_WAIT_UNTIL(ReceivePin::read());
	PT_WAIT_UNTIL(!ReceivePin::read());
	XPCC_LOG_DEBUG << "[";

	// wait for startbit + 1.bit to get transmitted
	delay.restart(Settings::ReceiveStartDelay);
	PT_WAIT_UNTIL(delay.isExpired());

	// receive bits
	ii = 0;
	while(ii < 7) {
		bit = ReceivePin::read();
		if(bit) XPCC_LOG_DEBUG << "1";
		else XPCC_LOG_DEBUG << "0";
		data = (data << 1) | (bit? 1 : 0);

		delay.restart(Settings::BitPeriod);
		PT_WAIT_UNTIL(delay.isExpired());
	}

	// sample stopbit
	bit = ReceivePin::read();
	if(bit) {
		XPCC_LOG_DEBUG << "]";
	} else {
		XPCC_LOG_DEBUG << "*E*";
	}

	// done
	PT_END();
}




void
Receiver::startReceive() {
	if(this->isRunning()) {
		XPCC_LOG_ERROR << "Cannot receive Data. Not finished!" << xpcc::endl;
		return;
	}

	XPCC_LOG_DEBUG << xpcc::endl << "Start receiving"<< xpcc::endl;
	this->data = 0;
	this->restart();
}

uint8_t
Receiver::getResult() {
	if(this->isRunning()) {
		XPCC_LOG_ERROR << "No result. Not finished!" << xpcc::endl;
		return 0;
	}

	return Hamming::decode(data);
}
