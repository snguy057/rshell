UCR CS100 rshell Assignment/Project
===

Authors
--------
Steven Nguyen - snguy057@ucr.edu

Ethan Valdez - evald011@ucr.edu

Repository
--------
https://github.com/snguy057/rshell.git

Licensing Information
--------
GNU General Public License
Version 3, 29 June 2007

Summary
--------
***rshell*** is a command shell program, created with the intent of having the 
ability to implement BASH commands. Our rshell prints a command prompt (i.e. $) 
then reads in a command on one line. Commands have the following form:
'''
executable [ argumentList ] [ connector cmd ]
'''
Valid connectors include:
'''
&& , || , ;
'''

It is currently a work in progress and lacking some BASH functionality. As of 
2/16/2017, the first portion of this project has been implemented but not all 
bugs have been resolved. See below for Known Bugs.


Running rshell
--------
To run rshell, enter these commands in the following order:
'''
1. git clone https://github.com/snguy057/rshell.git
2. cd rshell
3. make
4. ./bin/rshell
'''
You will now be able to run BASH commands using ***rshell***


