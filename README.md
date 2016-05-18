# sspn_06_lets_boost

This is sample code for the 6th SSPN meetup:
http://www.meetup.com/sspn16/events/231003288/

This is just demo code showing how to use some of the boost libraries. 

#Notice
 * This is currently work in progress
 * It still misses a lot of thing I would like to talk about
 * But maybe it is already too much for the first time and we have to split it up into more sessions...
 
#Build
 * clone the repro
 * open a console and create a sub directory 'build' and switch to that directory
 * Run the command 'cmake .. -G "Visual Studio 14 2015"' and open the solution in VS2015 on Windows and 'cmake .. -G "Unix Makefiles" && make' on Linux
 
#Source
 * I added a bunch of comments to the source code, but I'm not sure if it understandable without hearing the explaination
 * I tried to introduce new concepts step by step, so we will not through in all 'new' features at once

#Tests
 * Tested most of the time with MSVC 14 - the whole code is written as feature test, if it compiles we are good. Running the executeable in debug modde just prooves some concepts.
