#!/usr/bin/env python3

import matplotlib
matplotlib.use('Qt4Agg')
import scipy
import pylab
import scipy.fftpack
import sys


import csv


out = []
inp = []

with open('../../../measurements/20140610/10Hz_random/scope_5.csv', newline='') as csvfile:
	spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
	ii = 0
	for row in spamreader:
		ii = ii+1
		if ii > 3:
			out.append(float(row[1]))
			inp.append(float(row[2]))


# Filter
filtered_out = pylab.convolve([-1,1], out)

# Sort
high = False

digital_out = []

for o in out:
	if o > 0.05:
		high = False
	elif o < -0.12:
		high = True
	if high:
		digital_out.append(1)
	else:
		digital_out.append(0)


pylab.figure(1)
pylab.subplot(311)
pylab.plot(out, 'r')
pylab.twinx()
pylab.plot(inp, 'g')
pylab.ylabel('Voltage (V)')
pylab.xlabel('Something (us)')

pylab.subplot(312)
pylab.plot(inp, 'g')
pylab.twinx()
pylab.plot(filtered_out, 'b')
pylab.ylabel('Voltage (V)')
pylab.xlabel('Something (us)')

pylab.subplot(313)
pylab.plot(inp, 'g')
#pylab.twinx()
pylab.plot(digital_out, 'r')
pylab.ylabel('Voltage (V)')
pylab.xlabel('Something (us)')

pylab.show()
