#include <xpcc/architecture/platform.hpp>
#include "../../../../xpcc/examples/stm32f3_discovery/stm32f3_discovery.hpp"
#include <xpcc/debug/logger.hpp>
#include "../settings.hpp"
#include "transmitter.hpp"

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


Transmitter tx;

// ----------------------------------------------------------------------------
MAIN_FUNCTION
{
	defaultSystemClock::enable();

	xpcc::cortex::SysTickTimer::enable();

	LedNorth::setOutput(xpcc::Gpio::High);


	// initialize Uart2 for XPCC_LOG_
	GpioOutputA2::connect(Usart2::Tx);
	GpioInputA3::connect(Usart2::Rx, Gpio::InputType::PullUp);
	Usart2::initialize<defaultSystemClock, 115200>(12);


	tx.initialize();

	while (1)
	{
		tx.sendPrefix();
		while(tx.run());
		for(int ii = 0; ii < 16; ++ii) {
			tx.sendData(ii);
			while(tx.run());
			LedNorth::toggle();
		}
		xpcc::delay_ms(Settings::SendValuesDelay);
	}

	return 0;
}

