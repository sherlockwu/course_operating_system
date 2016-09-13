# Process
Running Program; For Time-sharing of the CPU, we need more techs(context switch) and polocies(schedule)  
## A Process 
* Machine state of a process: address space, registers; special registers(PC, stack pointer, frame pointer); I/O info.(file descriptors) 

## Process API
* Create, Destroy, Wait, Control(suspend, resume), Status(get information) 

## Process Creation
* Load excutable format of an app into mem; (maybe lazily loaded, using paging and swapping)
* allocate run-time stack
* allocate heap
* initialize I/O (three basic ones: standard input, output, error)
* At last, jump to the main()

## Process States
* running, ready, blocked(waiting for I/O)
* states switch (time-out interrrupt)  

## Data Structures in OS for process control
* process list (store ready processes)
* actually more state of process (like zombie state for parent process's usage)
* PCB (process control block)


## How to use process creation interface in UNIX
More like different parallel model
* fork()
	* create a new process: running the same code just after fork() in parent process
	* return: <0 fail; 0 to child process and child PID to parent process;
		* We can use different return to program the actions those two processes to continue 
	* the CPU can schedule any of these two processes to run 
* wait()
	* a function won't return until the child has run and exited 
	* can be used with fork, to together get a determined schedule of the processes
* exec()
	* have many versions eg. execvp
	* input: name of an executable and its arguments
		* after exec, just transform the current process into the new executable with re-initializing its mem space(of course, code)
* Motivating the API? 
	* these APIs are designed for shell, at first
		* shell process fork to exec a command, and wait
		* Eg. can close standard output and open a output file, `after fork, before exec` for redirect the output
* Other  

## Limited Direct Execution (Control process running)
Processes, tim-sharing, keep process running efficiently while maintaining control
* Intro: cannot just let process run; and os should regain control of the system
* Restricted Operations
	* Need I/O or more, you need use trap assembly instruction
	* User mode -trap(system call)-> kernel mode
	* trap table(initialized when boot, store in hardware); user call trap system-call number
* Switching between Processes
	* need regain control sometime (system call, error, timer interrupt)
	* when switch process: context switch 
* Concurrency
	* disable interrupts while in kernel mode
	* how about multiprocessors? 
* Summary
Keep the process running safely & OS can gain control to CPU

## Homework: 

## Ref 