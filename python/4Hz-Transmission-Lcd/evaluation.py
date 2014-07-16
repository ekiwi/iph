#!/usr/bin/env python3

import matplotlib
matplotlib.use('Qt4Agg')
import scipy
import pylab
import scipy.fftpack
import sys


import csv


data = []

with open('../../measurements/20140611/4Hz-Transmission-Lcd/receiver.log', newline='') as csvfile:
	spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
	for row in spamreader:
		data.append([int(row[0]), int(row[1]), 0])

value = 10

type_count = [0,0,0]

for ii in range(0, len(data)):
	if value != data[ii][1]:
		data[ii][2] = 3		# Type3: incorrect value
	elif data[ii][0] == 1:
		data[ii][2] = 2		# Type2: one error corrected
	else:
		data[ii][2] = 1		# Type1 correct
	type_count[data[ii][2]-1] = type_count[data[ii][2]-1] + 1
	value = value + 1
	if value == 16:
		value = 0

print(type_count)
print(data)
