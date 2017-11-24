#!/usr/bin/python
import smtplib
from os.path import basename
from email.mime.application import MIMEApplication
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.utils import COMMASPACE, formatdate

class Server(object):
	def __init__(self, url, port):
		self.url=url
		self.port=port
class EmailId(object):
	def __init__(self, mailid=None, password=None):
		self.mailid=mailid
		self.password=password
class MailSender(object):
	def __init__(self, send_from, send_to, subject, text, files=None,server=None):
		self.send_to=send_to
	    	assert isinstance(send_to, list)
		self.send_from=send_from
		self.files=files
		self.server=server
		self.subject=subject
		self.text=text
	def send_mail(self):

	    msg = MIMEMultipart()
	    msg['From'] = self.send_from.mailid
	    msg['To'] = COMMASPACE.join(self.send_to)
	    msg['Date'] = formatdate(localtime=True)
	    msg['Subject'] = self.subject
	    msg.attach(MIMEText(self.text))

	    for f in self.files or []:
	        with open(f, "rb") as fil:
	            part = MIMEApplication(fil.read(), Name=basename(f))
           	    part['Content-Disposition'] = 'attachment; filename="%s"' % basename(f)
	            msg.attach(part)
		
	    try:
		    smtp = smtplib.SMTP_SSL(self.server.url, self.server.port)
		    smtp.ehlo()
		    smtp.login(self.send_from.mailid, self.send_from.password)	
		    smtp.sendmail(self.send_from.mailid, self.send_to, msg.as_string())
		    smtp.close()
		    print "Mail Sent"
	    except:
		    print "while sending mail Something went wrong"

if __name__ == "__main__":
	send_from=EmailId('somnathbghule@gmail.com','Srm@9767');
	send_to=['somnathbghule@gmail.com']
	subject="test mail"
	text="Mail sended implemented"
	server=Server('smtp.gmail.com', 587);
	files=['test.spec']
	sender=MailSender(send_from,send_to, subject, text,files, server)
	sender.send_mail();
