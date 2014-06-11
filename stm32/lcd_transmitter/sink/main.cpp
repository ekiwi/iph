#include <xpcc/architecture/platform.hpp>
#include "../../../../xpcc/examples/stm32f4_discovery/stm32f4_discovery.hpp"
#include <xpcc/debug/logger.hpp>
#include "../settings.hpp"
#include "receiver.hpp"

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


Receiver rx;

// ----------------------------------------------------------------------------
MAIN_FUNCTION
{
	defaultSystemClock::enable();

	xpcc::cortex::SysTickTimer::enable();

	LedRed::setOutput(xpcc::Gpio::High);


	// initialize Uart2 for XPCC_LOG_
	GpioOutputA2::connect(Usart2::Tx);
	GpioInputA3::connect(Usart2::Rx, Gpio::InputType::PullUp);
	Usart2::initialize<defaultSystemClock, 115200>(12);


	rx.initialize();

	while (1)
	{
		rx.startReceive();
		while(rx.run());
		uint8_t data = rx.getResult();
		LedRed::toggle();
		XPCC_LOG_INFO << xpcc::endl << "Received: " << data << xpcc::endl;
	}

	return 0;
}

