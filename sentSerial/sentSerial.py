#!/bin/env python
# -*- coding: utf-8 -*-

from Tkinter import *
import serial,sys

master = Tk()
port='/dev/cu.usbmodem1411'
ser = serial.Serial(port,9600)

def shutter():
	print "Shutter now"
	ser.write('t')
def shutterDelayed():
	print "Shutter delayed"
	ser.write('d')
master.config(width=250)

title = Label(master,text="aeAuslöser")
title.pack()

b1 = Button(master,text="Shutter",command=shutter)
b1.pack(side=LEFT,fill=X)

b2 = Button(master,text="Delayed",command=shutterDelayed)
b2.pack(side=LEFT,fill=X)

port = Label(master,text="On: " + port)
port.pack(side=BOTTOM)

mainloop()
