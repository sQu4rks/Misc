#!/usr/bin/env python
# -*- coding: utf8 -*-
"""
 This script checks a supplied email for new Mails and forwards theme to all listed people in mail_list.txt

 Copyright (c) Marcel Neidinger - Students Research Center phaenovum - www.phaenovum.eu

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
  
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
  
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
"""
#Imports
import time
import smtplib

# Variable defintions, set theme as you need theme
# Your smtp server to send the mails to
SMTPAdr="mail.sfz-bw.de"
# Your imap server to get the mails from
IMAPAdr="mail.sfz-bw.de"
# The mail adresse you wish to use
MAILAdr="marcel.neidinger@sfz-bw.de"
# The coressponding password for the mail adress
PASS="Blub'
# The name of your mail list file
LFILE="mail_list.txt"

# Methode to write a log message into our mail.log file
def log(message):
	# Get timestamp and then print the message
	timestamp = time.ctime()
	print(timestamp+" - "+message)
	
	# And now write that string to log
	fobj = open("email.log","a")
	fobj.write(timestamp+" - "+message+"\n")
	fobj.close
	
# Methode to check if there is a new mail
#def mailCheck():

# Methode to forward the Mail to all listed mail adresses
def sendMail(sender,reason,mail):
	# Liste mit Mails aus dem File auslesen
	mailList = list()
	fobj = open(LFILE,"r")
	for line in fobj:
		mailList.append(line)
	log("Liste ausgelesen")
	fobj.close()
	
	# Verbindung zum SMTP Server aufbauen
	server = smtplib.SMTP(SMTPAdr)
	server.login(MAILAdr, PASS)
	
	log("Mit SMTP Server verbunden")
	
	# Header konstruieren
	header = 'To:' + "someone@someone.de" + '\n' + 'From: nicole-neuser@web.de' + '\n' + 'Subject:'+ reason + ' \n'
	
	# Nachricht zusammensetzen
	msg = header + mail
	
	# Nachricht senden
	server.sendmail("from@somebody.de",mailList,msg)
	server.close()	
	log("Nachricht erfolgreich gesendet")
		
# Main Funktion to start everything
if __name__ == "__main__":
	# Funktionen von hier aufrufen
