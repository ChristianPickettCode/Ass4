#!/usr/bin/env python

import cgi, cgitb
import csv
import webbrowser
cgitb.enable()
form = cgi.FieldStorage()

inventory = form.getvalue('inventory')
URL = form.getvalue('URL')

def readv():
	data=""
	with open("resources.csv") as f:
		data = f.read()
	x = data.split(',')
	return x

isOccupied = readv()

if isOccupied[2] =='1':
		print("Content-Type: text/html\n\n")
    #print "occupied"
    print "<hmtl>"
    print "<body>"
    print "<h2> Refreshing...</h2>"
    print "<form action=\"%s\" method=\"POST\">" %(URL)
		print "<input type=\"hidden\" name=\"command\" value\"REFRESH\">"
		print "<input type=\"hidden\" name=\"inventory\" value=\"%s\">" %(inv)
    print "<input type=\"submit\" value=\"Go Back\">"
    print "</form>"
    print "</body>"
    print "</html>"
else:
		print("Content-Type: text/html\n\n")
    #print "not occupied"
    print "<html>"
    print "<h1> Looks like the room isn't occupied... Wanna transport into it? </h1>"
    print "<body>"
    print "<form action=\"http://cgi64.cs.mcgill.ca/~cpicke5/test.cgi\" method=\"POST\">"
		print "<input type=\"hidden\" name=\"command\" value=\"REFRESH\">"
		print "<input type=\"hidden\" name=\"inventory\" value=\"%s\">" %(inv)
    print "<input type=\"submit\" value=\"Transport\">"
    print "</form>"
    print "<object type=\"text/html\" width=\"0\" height=\"0\" data=\"%s/cgi-bin/success.py\" >" %(URL)
    print "</object>"
    print "</body>"
    print "</html>"


