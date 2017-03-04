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

UPDATE: ***rshell*** now supports precedence operators '(' and ')', as well as
implements a specialized operation of the test command, printing the result of
the test (either (TRUE) or (FALSE)) to the terminal.

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

Precedence
--------
The precedence operators '(' and ')' allow the encapsulation of combinations of
commands to run in specific orders. For example:
```
echo 1 && echo 2 || echo 3 && echo 4
```
Prints 
```
1
2
4
```
to the screen. However, with precedence operators:
```
(echo 1 && echo 2) || (echo 3 && echo 4)
```
Prints
```
1
2
```
to the screen, not executing the commands for echo 3 and echo 4.

Nested precedence is also supported:
```
(echo Prints || (echo Does not run echo or ls && ls)) && (echo Runs pwd && pwd)
```
The above command will print:
```
Prints
Runs pwd
.../<currentDir>
```

Test Scripts
--------
Our project includes a series of test scripts designed to ensure proper 
functionality of our program. In order to run any of these scripts, first 
navigate to the tests/ directory, then enter the following command:
```
./<name_of_script>
```
where <name_of_script> can be replaced by any of the scripts listed below:
```
single_command.sh      #tests single commands
multi_command.sh       #tests commands with connectors (&&, ||, and/or ;)
commented_command.sh   #tests commands containing comments
exit.sh                #tests exit and commands with exit
```

Known Bugs
--------
1. If echo is passed an argument containing quotes, echo does not remove the 
   quote characters when printing the argument to the console
2. The echo command does not support escape characters (e.g. '\n', '\t')
3. If a command contains an odd amount of quotes (single or double), an error 
   is printed and no commands are executed.
4. Piping and redirection is not supported.
5. [ [ \<directory/file\> ] ] returns (FALSE) rather than pushing an error.
6. Multiple flags passed into the test command returns (FALSE) rather than
   throwing an error.
