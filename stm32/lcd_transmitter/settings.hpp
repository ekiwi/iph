#ifndef SETTINGS_HPP
#define SETTINGS_HPP


namespace Settings
{
	static constexpr int   BitPeriod   = 250;
	static constexpr int   ReceiveStartDelay = BitPeriod + (BitPeriod * 2 / 3);


	static constexpr int SendValuesDelay = 2000;
}

#endif // SETTINGS_HPP
