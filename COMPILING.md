#QUICK COMPILE GUIDE
(THE REALLY QUICK VERSION)

REQUIREMENTS
------------
YOU NEED QT4. Download it from http://qt.nokia.com

Linux/MacX/Windows
------------------
To compile each program enter the program/src/ path (i.e., lyngo/drillbit/src/)
and execute the following commands from the command line (Linux users can use
xterm, macx users can use Terminal.app, windows users can use the QT Command
Prompt available in the start menu).

	qmake -project -o appname.pro
	qmake
	make

For Mac OS X, the 'makenbake' script is ready to use for a terminal build using
and execution using GNU make.

If you are using XCode on mac after executing qmake the second time, the default
qmake spec will create a .xcode package.

If you are on Mac OS X and do not want to use the XCode spec, check the
makenbake file for an example useage of the -spec argument for qmake,
it should look something like this:

	qmake -spec macx-g++

