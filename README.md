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

UPDATE2: **rshell** now supports IO redirection and limited piping. Mulitple
pipes is broken.

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
Redirection
--------
The redirection operators '<', '>', and '<<' are now supported in rshell. 
These operators allow for the contents of files or outputs of commands to be 
redirected into other commands as inputted by the user.

For example, the following command:
```
echo My text > newFile
```
prints the text "My text" into the file named "newFile". If "newFile" does not
exist, a file of the name "newFile" will be created and the text "My text" will
be written into it. If "newFile" does exist, then its contents will be 
overwritten by the new output being redirected into it.

The '>>' operator functions in a similar manner to the '>' operator, with the
exception that if the file already exists, the '>>' operator only appends the
output to the file instead of overwrites it.

The command:
```
cat < existingInputFile
```
allows the command on the left to accept input from "existingInputFile" 
instead of user input from the command line. This can be useful in scripts that
require arguments, as the command:
```
test.sh < test.txt
```
would pass in the contents of "test.txt" as input to the test.sh script without
the user being required to type in the content of test.txt by hand.

The pipe operator, '|', is also supported, passing in the output of the previous
command as input to the next command. For example
```
cat existingInputFile | tr A-Z a-z
```
takes the output of cat (which is the contents of existingInputFile) and passes
it to "tr A-Z a-z", a translate command with will turn all capital letters into
lowercase then output the translated output to the command prompt.

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
4. [ [ \<directory/file\> ] ] returns (FALSE) rather than pushing an error.
5. Multiple flags passed into the test command returns (FALSE) rather than
   throwing an error.
6. Multiple pipes in a command line is broken and prevented. When trying to
   when implementing multiple pipes, the parent process would be indefinitly
   waiting for the child to terminate.
