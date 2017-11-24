#!/usr/bin/python
import smtplib
server = smtplib.SMTP('smtp.gmail.com', 587)

#Next, log in to the server
server.login("somnathbghule@gmail.com" "Srm@9767")

#Send the mail
msg = "Hello!" # The /n separates the message from the headers
server.sendmail("somnathbghule@gmail.com", "somnathbghule@gmail.com", msg)
