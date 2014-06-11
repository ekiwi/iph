#include "transmitter.hpp"
#include "../settings.hpp"
#include "../hamming.hpp"

#include <xpcc/architecture/platform.hpp>
#include <xpcc/debug/logger.hpp>

using namespace xpcc::stm32;

typedef GpioOutputA5 SendPin;


Transmitter::Transmitter()
: delay(0)
{
	this->stop();
}

void
Transmitter::initialize()
{
	SendPin::setOutput(xpcc::Gpio::High);
}


bool
Transmitter::run()
{
	static bool bit;
	static int ii;

	PT_BEGIN();

	delay.restart(Settings::BitPeriod);

	// send startbit
	SendPin::reset();
	PT_WAIT_UNTIL(delay.isExpired());

	// send 7 databits
	ii = 0;
	while(ii < 7) {
		++ii;

		bit = static_cast<bool>(data & (1<<6));
		// Send single bit
		SendPin::set(bit);
		if(bit) XPCC_LOG_DEBUG << "1";
		else XPCC_LOG_DEBUG << "0";

		PT_WAIT_UNTIL(delay.isExpired());

		data = data << 1;
	}

	// send stopbit
	SendPin::set();
	PT_WAIT_UNTIL(delay.isExpired());

	delay.restart(0);	// stop delay
	PT_END();
}


void
Transmitter::send(uint8_t data) {
	if(this->isRunning()) {
		XPCC_LOG_ERROR << "Cannot send Data. Not finished!" << xpcc::endl;
		return;
	}

	XPCC_LOG_DEBUG << xpcc::endl << "Send: " << data << xpcc::endl;
	this->data =  Hamming::encode(data);
	this->restart();
}

