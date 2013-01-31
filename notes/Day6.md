Title: Day 6
Date: 1/31/13
Published: true

## RegularExpressions and Python

System calls in the kernel are wrapped with a macro
usleep  
nanosleep  
sys_nanosleep //Can't find with grep  
SYSCALL_DEFINE[1-7]()() //number for number of passed args  

$ egrep -sr '^SYSCALL_DEFINE.*\(nanosleep' *
//ending * is actually a glob

GLOB 								RE
*.c 								^.*\.c$
*.*									^.*\..*$
hw?0[1-5].[ch]			hw.0[1-5]\.[ch]$
0-100								0|100|[1-9][0-9]?
NON-Negative				[^-](0|100|[1-9][0-9]?)

## Python Scripting
@note Perl is good for text processing
@note In Python everything is an object

@note scripting `#!/usr/bin/env /usr/bin/python`
`#!` //tell kernel that its a shell executeable

``` python
	#!/usr/bin/env /usr/bin/python
	import smtplib #simple mail transport protocol
		from urllib import urlopen
	import re #regular expression module

	fromaddr = 'bill@microsoft.com'
	toaddrs  = 'steve@apple.com'

	# Add the From: and To: headers at the start!
	msg = ("From: %s\r\nTo: %s\r\nSubject: Home Temp Status\r\n\r\n"
	       % (fromaddr, toaddrs))

	temp 	= urlopen("http://www.eece.maine.edu/cgi-bin/test-cgi").read()
	pat		= re.compile(r'^REMOTE_HOST = (.*)$',re.MULTILINE) #`r` indicates raw string
	match	= re.search(pat,temp) # pattern & cearhcon
	host 	= match.group(1)
	host 	= 'Link to automation system status\r\nhttp://' + host + '/cgi-bin/temp.pl'
	msg 	= msg+host
	server = smtplib.SMTP('outgoing.gwi.net')
	server.login('Username','Password')
	#server.set_debuglevel(1)
	server.sendmail(fromaddr, toaddrs, msg)
	server.quit()(
	```
	
	## Timing on mset
	usleep();
	
	### Python quirks
	Using an undefined variables. Throws errors
	
		import subprocess
		from numpy import *
		import matplotlib.pyplot as pyplot
	
		data = dict()

		for x in range(8): 
			print x

			for y in range(4):
				e=subprocess.check_output(["sudo","tusleep", str(x)])
				try:
					data[x].append(int(e))
				except:
					data[x] = [int(e)];

		print data
		for k in sorted(data.iterkeys()):
			try:
				l.append(k)
			except:
				l = [k]
			l.extend(data[k])

		a=array(l)
		a=a.reshape(8, 5)
		aveTime=(a.sim(1)-a[:,0])/4

		plt.plot(a[:,0], avetime)
		plt.grid();

		plt.show()

