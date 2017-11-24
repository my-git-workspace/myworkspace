#!/usr/bin/python
import sqlite3 
import sys
import os
import time
import csv
from Emailer import MailSender
from Emailer import EmailId
from Emailer import Server


class DBBackup(object):
	def __init__(self, dbname,query):
		self.dbname=dbname
		timestr=time.strftime("%H-%M-%S")
		self.cmd="sqlite3 -line " + self.dbname + " '.backup " + self.dbname +"_"+timestr +"'"
		self.query=query

	def getBackup(self):
	    #print self.cmd
            try:
		    os.system(self.cmd)
	    except OSError:
		    print "database backup failed: something went wrong"	
	def getDataInCSV(self):
		timestr=time.strftime("%H-%M-%S")
		csvfile="data-table"+timestr+".csv"
		conn = sqlite3.connect(self.dbname)
		print "Opened database successfully";
		cursor = conn.execute(self.query)
		writer = csv.writer(open(csvfile, 'w'))
		for row in cursor:
			print "ID = ", row[0]
			print "NAME = ", row[1]
			writer.writerow(row)

		print "Operation done successfully";
		conn.close()
		return csvfile		
backup=DBBackup('container.db', 'select id, name from data');
backup.getBackup()
attachmentfile=backup.getDataInCSV();
send_from=EmailId('somnathbghule@gmail.com','Srm@9767');
send_to=['spsalunke.ss@gmail.com']
subject="please find current update.."
text="Bhai DB backup POC is completed.:(y)"
server=Server('smtp.gmail.com', 465);
files=[attachmentfile]
sender=MailSender(send_from,send_to, subject, text,files, server)
sender.send_mail();
