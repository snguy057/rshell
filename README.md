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
```
executable [ argumentList ] [ connector cmd ]
```
Valid connectors include:
```
&& , || , ;
```
If a command includes a # symbol, then everything occuring after the # is 
regarded as a comment and not executed.

It is currently a work in progress and lacking some BASH functionality. As of 
2/16/2017, the first portion of this project has been implemented but not all 
bugs have been resolved. See below for Known Bugs.


Running rshell
--------
To run rshell, enter these commands in the following order:
```
1. git clone https://github.com/snguy057/rshell.git
2. cd rshell
3. make
4. ./bin/rshell
```
You will now be able to run BASH commands using ***rshell***

Connector Descriptions
--------
&& Connector: if a command is followed by this connector, then the next command 
   executes only if the first one succeeds.
|| Connector: if a command is followed by this connector, then the next command 
   executes only if the first one fails.
; Connector: if a command is followed by this connector, then the next command 
   is always executed.

Test Scripts
--------
Our project includes a series of test scripts designed to ensure proper 
functionality of our program. In order to run any of these scripts, first 
navigate to the tests/ director, then enter the following command:
```
./script
```
where script can be replaced by any of the scripts listed below:
```
single_command.sh      #tests single commands
multi_command.sh       #tests commands with connectors (&&, ||, and/or ;)
commented_command.sh   #tests commands containing comments
exit.sh                #tests exit and commands with exit
```

Known Bugs
--------
1. rshell does not support the cd command
2. If echo is passed an argument containing quotes, echo does not remove the 
   quote characters when printing the argument to the console
3. The echo command does not support escape characters (e.g. '\n', '\t')
4. If a command contains an odd amount of quotes (single or double), an error 
   is printed and no commands are executed.
5. Piping and redirection is not supported.
6. Precedence (using parentheses) is not supported.
