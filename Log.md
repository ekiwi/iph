# Log

## 2014-06-10 morning
* function generator needs -5V in AM mode in external source input to
  output 0V ampltude (or at least a very small amplitude)
* function generator external input is high impedance, not 50 ohm terminated

## 2014-06-10 14:30
* connected UART dongle to comparator to function generator
* comparator and function generator working good (blue/red line in uart_*)

## 2014-06-10 15:00
* 10Hz function generator bit patten test
* toggle pattern recognizable (10Hz_toggle)
* problems with random patterns (10Hz_random)
* ERROR: channel 2 was AC coupled which caused misleading results

## 2014-06-10 17:40
* connected comparator to receiver output to generate digital signal
* working with 3Hz random patterns (see files in 3Hz_comparator)

## 2014-07-03
* built current source that can be modulated using two transistors
* tested, working fine up to 100kHz
* sending seems to work fine, but receiving poses some problems
  (see measurements)


## 2014-07-10
* tried to improve transmitter with 50 Ohm resistor to ground
  -> reflections gone but still no better transmission
* transmitter with 1MHz of data working well

