#!/usr/bin/env python
# -*- coding: utf-8 -*-

import serial,sys,getopt

def usage():
	print "Usage: sentSerial.py [options] COMMAND"
	print " -h --help \t Print help message"
	print " -p --port \t Set the serial port"

if __name__ == "__main__":
	# Strip away last argument
	argArray = sys.argv[1:len(sys.argv)-1]
	command = sys.argv[len(sys.argv)-1]
	
	# Parse command line arguments
        try:                
		opts,args = getopt.getopt(argArray,"h",["help"])
	except getopt.GetoptError as err:
 		sys.exit(-1)
	for o,a in opts:
 		if o in ("-h","--help"):
 			usage()
			sys.exit(-1)
