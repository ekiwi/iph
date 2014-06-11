#ifndef SETTINGS_HPP
#define SETTINGS_HPP


namespace Settings
{
	static constexpr int   BitPeriod   = 500;
	static constexpr float SampleTime = 0.5f;	// as a percentage of one bit period
	static constexpr int   ReceiveStartDelay = BitPeriod + static_cast<int>(SampleTime * BitPeriod);


	static constexpr int SendValuesDelay = 10000;
}

#endif // SETTINGS_HPP
