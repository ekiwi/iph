#include <xpcc/architecture/platform.hpp>
#include "../../../../rca/software/xpcc/examples/stm32f4_discovery/stm32f4_discovery.hpp"



#include <xpcc/debug/logger.hpp>

// ----------------------------------------------------------------------------
// Set the log level
#undef	XPCC_LOG_LEVEL
#define	XPCC_LOG_LEVEL xpcc::log::DEBUG


// Create an IODeviceWrapper around the Uart Peripheral we want to use
xpcc::IODeviceWrapper< Usart2 > loggerDevice;

// Set all four logger streams to use the UART
xpcc::log::Logger xpcc::log::debug(loggerDevice);
xpcc::log::Logger xpcc::log::info(loggerDevice);
xpcc::log::Logger xpcc::log::warning(loggerDevice);
xpcc::log::Logger xpcc::log::error(loggerDevice);


typedef GpioOutputA5 SendPin;

static constexpr int BitDelay = 500;
static constexpr int PrefixDelay = 1000;
static constexpr int SendValuesDelay = 10000;

static void
sendBit(bool bit) {
	SendPin::set(bit);
	if(bit) XPCC_LOG_DEBUG << "1";
	else XPCC_LOG_DEBUG << "0";
	xpcc::delay_ms(BitDelay);
}

static void
send(uint8_t data) {
	for(int ii = 0; ii < 7; ++ii) {
		sendBit(static_cast<bool>(data & 0x1));
		data = data >> 1;
	}
}

static void
sendPrefix() {
	XPCC_LOG_DEBUG << "[p";
	send(0b1010101);
	SendPin::reset();
	XPCC_LOG_DEBUG << "p]";
	xpcc::delay_ms(PrefixDelay);
}



static void
sendData(uint8_t data) {
	XPCC_LOG_DEBUG << xpcc::endl << "Send: " << data << xpcc::endl;
	send(encode(data));
}


// ----------------------------------------------------------------------------
MAIN_FUNCTION
{
	defaultSystemClock::enable();

	LedOrange::setOutput(xpcc::Gpio::High);
	LedGreen::setOutput(xpcc::Gpio::Low);
	LedRed::setOutput(xpcc::Gpio::High);
	LedBlue::setOutput(xpcc::Gpio::High);


	// initialize Uart2 for XPCC_LOG_
	GpioOutputA2::connect(Usart2::Tx);
	GpioInputA3::connect(Usart2::Rx, Gpio::InputType::PullUp);
	Usart2::initialize<defaultSystemClock, 115200>(12);


	SendPin::setOutput();

	while (1)
	{
		sendPrefix();
		for(int ii = 0; ii < 16; ++ii) {
			sendData(ii);
		}
		xpcc::delay_ms(SendValuesDelay);
	}

	return 0;
}

