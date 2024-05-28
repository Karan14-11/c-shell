# Description
This is a simple representation of the Bash shell coded in the C Programming language as a part of the Operating Systems and Networks course at IIIT-Hyderabad Monsoon 2023 semester. This branch is for the Mid-Submission of the project.It supports basic bash functionalities like cd , ls , history and more. 
# How to Run
Go to directory in which you save the file 
Run make in terminal 
Then run ./a.out
# Assumptions
Assumed that bash-oriented commands and shell specific commands won't be given as a single multi-command thread
The size of relevant commands are constrained to size of MACROS defined to store them.
Since the shell is under construction , it may throw some bugs at the user but that's what I'll be doing!Fixing them.
Excessive care has been taken to handle all sorts of edge-cases but any if any such ambiguity still remains
In terminal if background process ends it ended part prints immediately but in our shell it prints before new prompt comes 
iMan works but smetimes it does not give whole output
the redirection will only happen for input in the first command and output in the last command
while storing pastevents execute if it is at end with delimiter(;) it will work but if it is in middle it will not store
Multiple Text files are allowed to use in code.(in pastevents)
For getting pastevents for ur use only initialise pas.txt to empty and nos.txt to "0000" or use pastevents purge as first command
The flags in seek only work when seperated by space and each has a '-' symbol not like in peek where they can be run as in bash terminal ie combining all
# NOTE
an official extension of 3 days was provided due to medical issues by VJS PRANAVASRI sir, Kindly donot include this into late days ; Thank you
