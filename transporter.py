#!/usr/bin/env python
import cgi, cgitb
import csv
import webbrowser
cgitb.enable()
form = cgi.FieldStorage()

inventory = form.getvalue('inventory')
URL = form.getvalue('URL')

inFile = open("test.csv")
reader = csv.reader(inFile)
data = list(reader)
isOccupied = data[2]
print(data[2])
if isOccupied == ['1']:
    print "occupied"
    print "<hmtl>"
    print "<body>"
    print "<h2> Refreshing...</h2>"
    print "<form action=\"%s/cgi-bin/room.cgi\">" %(URL)
    print "<input type=\"submit\" value=\"Go Back\">"
    print "</form>"
    print "</body>"
    print "</html>"
else:
    print "not occupied"
    print "<html>"
    print "<h1> Looks like the room isn't occupied... Wanna transport into it? </h1>"
    print "<body>"
    print "<form action=\"cgi-bin/room.cgi\">"
    print "<input type=\"submit\" value=\"Transport\">"
    print "</form>"
    print "<object type=\"text/html\" width=\"0\" height=\"0\" data=\"%s/cgi-bin/success.py\" >" %(URL)
    print "</object>"
    print "</body>"
    print "</html>"
