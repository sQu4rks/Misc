#!/bin/env python
# -*- coding: utf-8 -*-
import serial,sys

ser = serial.Serial(sys.argv[1],9600)

def shutter():
	print "Shutter now"
	ser.write('t')
def shutterDelayed():
	print "Shutter delayed"
	ser.write('d')

shutter()
