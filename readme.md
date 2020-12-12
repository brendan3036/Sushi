# CMPE320 Project - Sush
**Created by: Kamrin Langan, Brendan Karper. Joshua Kellogg**

*This project was done for an Operating Systems course in the Spring semester of 2020.

*The following are requirements for sush*

## Internal commands
1. setenv
2. unsetenv
3. cd dir
4. pwd
5. exit
6. accnt


### Thinks that Sush must be able to handle
1. Redirection (I.E ">", ">>", "<", "|")
2. Signal Handling
3. Execution


#### Redirection
1. ">" - will redirect standard output to a file
2. ">>" - will concatenate standard output to a file
3. "<" - will redirect standard input from a file
4. "|" - will run two processes and connect the output of one to the input of the other


##### Process Accounting
1. The UNIX kernel tracks many different aspects of the resources used by a process.  For the current process, these can be read using the “getrusage” system call
2. Since this information is available, sush will keep track of it
3. When the user types the “accnt” internal command, or when sush receives the SIGUSR1, it will display this information to STDOUT.
4. When a process terminates, this information is also available from the kernel by using the “wait3” system call
5. So, sush will read this information and display it whenever a process terminates.
6. Sush will also keep a grand total of all of these and then print them when sush exits


###### Signal Handling
1. During execution, when a “ctrl-c” is detected by the terminal driver, a SIGINT is sent to the cur-rent process.  Sush must not terminate when a SIGINT is received; but the child process must.  Sush must also handle the death of a child, SIGCHLD
2. One of “sush’s” design goal is to track the system resources used by it and its programs.  If an-other process sends “sush” a SIGUSR1 it will handle this signal and display the current processes system resources, and a SIGUSR2 will display the current running total + the current process totals

