# pipex
> This project is about implementing the same behaviors as pipes.

To understands the project in details read the subject. (look for it between repository files).

```
$> ./pipex infile "ls -l" "wc -l" outfile
```
Should behave as :
```
< infile ls -l | wc -l > outfile
```

### Example:

```
$> ./pipex infile "grep a1" "wc -w" outfile
```

Should behave as :
```
< infile grep a1 | wc -w > outfile
```

To run the program:

1. Clone the repository
2. Into the directory of the repository run:
```
make
```
3. Finally, run the program using the below command:
```
$> ./pipex infile "grep a1" "wc -w" outfile
```
> ps: you can change in the commands so the program should behave as normal pipes.






# Resources I relied on while working on the project:
- [Operating System Concepts 10th Edition by Abraham Silberschatz (Author), Greg Gagne (Author), Peter B. Galvin (Author)](https://www.amazon.com/Operating-System-Concepts-Abraham-Silberschatz/dp/1119800366/ref=d_pd_vtp_vft_none_sccl_2_2/141-3930655-7318351?pd_rd_w=sZCQl&content-id=amzn1.sym.8e065679-52e9-4d16-ae63-fa3d08b93cef&pf_rd_p=8e065679-52e9-4d16-ae63-fa3d08b93cef&pf_rd_r=5B0V0AZZBFM0Y2SD7ARN&pd_rd_wg=n8K4t&pd_rd_r=50865642-40fa-4059-8eb4-092f0bd31f89&pd_rd_i=1119800366&psc=1).
- [Linux Command Line and Shell Scripting Bible 4th Edition by Richard Blum (Author), Christine Bresnahan (Author)](https://www.amazon.com/Linux-Command-Shell-Scripting-Bible/dp/1119700914).

- dup() && dup2():
[Handling a File by its Descriptor in C](https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/).

- [Pipe: an Inter-Process Communication Method](https://www.codequoi.com/en/pipe-an-inter-process-communication-method/).

# A brief summary about pipes and processes:

__1. Environment variables:__
linux environment variables help define your linux shell experience. Many programs and scripts use environment variables to obtain system information and store temporary data and configuration information.


__2. Setting the PATH environment variable__

When you enter an external command in the shell command line interface (CLI), the shell must search the system to find the program. The PATH environment variable defines the directories it searches looking for commands and programs.

To see the env PATH use the command below:
```
$ echo $PATH
```
This will show you all the directories where the shell looks for commands and programs. The directories in the PATH are separated by colons.

- If you need to a add directory to the PATH run the command below:
```
$ PATH=$PATH:/path/to/directory
```
- If you need to add the current directory run:
```
$ PATH=$PATH:.
```
__3. Redirecting Input and Output__

Sometimes, you want to save the output from a command instead of just having it displayed on the monitor. The bash shell provides a few different operators that allow you to redirect the output of a command to an alternative location (such as a file). Redirection can be used for input as well as output, redirecting a file to a command for input. This section describes what you need to do to use redirection in your shell scripts.

*Output redirection*

The most basic type of redirection is sending output from a command to a file. The bash
shell uses the greater-than symbol (>) for this: command > outputfile    

- to overwrite: >>

*Input redirection*

Input redirection is the opposite of output redirection. Instead of taking the output of a
command and redirecting it to a file, input redirection takes the content of a file and
redirects it to a command.
The input redirection symbol is the less-than symbol (<):
command < inputfile

## PIPES

Instead of redirecting the output of a command to a file, you can redirect the output to another command. This process is called piping.

__1. Process management in OS__

A process is a program in execution. A process will need certain resources—such as CPU time, 
memory, files, and I/O devices— to accomplish its task. These resources are typically allocated 
to the process while it is executing.

To see running processes run the command bellow:
```
$ ps
```
>We emphasize that a program by itself is not a process. A program is a
passive entity, such as a file containing a list of instructions stored on disk
(often called an executable file ). In contrast, a process is an active entity,
with a program counter specifying the next instruction to execute and a set
of associated resources. A program becomes a process when an executable file
is loaded into memory. 

----> Process creation

During the course of execution, a process may create several new processes. The creating process is called a parent process, and the new processes are called the children of that process. Each of these new processes may in turn create other processes, forming a tree of processes.

Most operating systems (including UNIX, Linux, and Windows) identify processes according to a unique process identifier (or pid), which is typically an integer number. The pid provides a unique value for each process in the system, and it can be used as an index to access various attributes of a process within the kernel.

----> Child process

In general, when a process creates a child process, that child process will need certain resources (CPU time, memory, files, I/O devices) to accomplish its task. A child process may be able to obtain its resources directly from the operating system, or it may be constrained to a subset of the resources of the parent process. The parent may have to partition its resources among its children, or it may be able to share some resources (such as memory or files) among several of its children. Restricting a child process to a subset of the parent’s resources prevents any process from overloading the system by creating too many child processes.

— When a process creates a new process, two possibilities for execution exist:

1. The parent continues to execute concurrently with its children.
2. The parent waits until some or all of its children have terminated.

— There are also two address-space possibilities for the new process:

1. The child process is a duplicate of the parent process (it has the same program and data as the parent).
2. The child process has a new program loaded into it.


----- In UNIX, as we’ve seen, each process is identified by its process identifier, which is a unique integer. A new process is created by the fork() system call. The new process consists of a copy of the address space of the original process. This mechanism allows the parent process to communicate easily with its child process. Both processes (the parent and the child) continue execution at the instruction after the fork(), with one difference: the return code for the fork() is zero for the new (child) process, whereas the (nonzero) process identifier of the child is returned to the parent.

----- After a fork() system call, one of the two processes typically uses the exec() system call to replace the process’s memory space with a new program. The exec() system call loads a binary file into memory (destroying the memory image of the program containing the exec() system call) and starts  its execution. In this manner, the two processes are able to communicate and then go their separate ways. The parent can then create more children; or, if it has nothing else to do while the child runs, it can issue a wait() system call to move itself off the ready queue until the termination of the child. Because the call to exec() overlays the process’s address space with a new program, exec() does not return control unless an error occurs.

```
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
  pid t pid;
  /* fork a child process */
  pid = fork();
  if (pid < 0) { /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  }
  else if (pid == 0) { /* child process */
    execlp("/bin/ls","ls",NULL);
  }
  else { /* parent process */
  /* parent will wait for the child to complete */
    wait(NULL);
    printf("Child Complete");
  }
  return 0;
}
```

|

|
 -----> The C program shown in the top illustrates the UNIX system calls previously described. We now have two different processes running copies of the same program. The only difference is that the value of the variable pid for the child process is zero, while that for the parent is an integer value greater than zero (in fact, it is the actual pid of the child process). The child process inherits privileges and scheduling attributes from the parent, as well certain resources, such as open files. The child process then overlays its address space with the UNIX command /bin/ls (used to get a directory listing) using the execlp() system call (execlp() is a version of the exec() system call). The parent waits for the child process to complete with the wait() system call. When the child process completes (by either implicitly or explicitly invoking exit()), the parent process resumes from the call to wait(), where it completes using the exit() system call.
 
 *Process creation illustrated using fork():
 ```
 parent ----> pid = fork() ----> parent (pid > 0) ----------------------->wait() ---->parent resumes
 
                            ----> child (pid = 0) --> exec() -------->exit() ^
 ```
 
__2. Networking and Inter-Process Communication__

Processes run individually and work independently in their respective address spaces. 
However, they sometimes need to communicate with each other to pass on information. 
For processes to cooperate, they need to be able to communicate with each other as 
well as synchronize their actions.

These communications can be unidirectional or bidirectional. To enable any form of
communication between processes, the following popular interprocess communication 
(IPC) mechanisms are used: pipes, FIFOs (named pipes), sockets, message queues, 
and shared memory. Pipes and FIFO enable unidirectional communication, whereas 
sockets, message queues, and shared memory enable bidirectional communication.

__2. Ordinary pipes:__

Ordinary pipes allow two processes to communicate in standard producer consumer fashion: the producer writes to one end of the pipe (the write end) and the consumer reads from the other end (the read end). As a result, ordinary pipes are unidirectional, allowing only one-way communication. If two-way communication is required, two pipes must be used, with each pipe sending data in a different direction. We next illustrate constructing ordinary pipes on both UNIX and Windows systems. In both program examples, one process writes the message Greetings to the pipe, while the other process reads this message from the pipe.

On UNIX systems, ordinary pipes are constructed using the function

`pipe(int fd[])`

*file descriptors for an ordinary pipe*
```
Parent                 pipe                    Child
fd[0]      -------------------------------      fd[0] 
fd[1]      -------------------------------      fd[1] 
```
__pipe() system call__

A pipe is used for connecting two processes. The output from one process can be sent
as an input to another process. The flow is unidirectional, that is, one process can
write to the pipe and another process can read from the pipe. Writing and reading are
done in an area of main memory, which is also known as a virtual file. Pipes have a
First in First out (FIFO) or a queue structure, that is, what is written first will be read
first.

The index location, pp[0], will get the file descriptor for the reading end of the pipe 
and pp[1] will get the file descriptor for the write end of the pipe.

ps: A process should not try to read from the pipe before something is
written into it, otherwise it will suspend until something is written
into the pipe.

Syntax: 
```
int pipe(int arr[2]);
```
The function returns 0 on success and -1 on error.

__perror() function__

This displays an error message indicating the error that might have occurred while
invoking a function or system call. The error message is displayed to stderr, that is,
the standard error output stream. This is basically the console.

Syntax:
```
void perror ( const char * str );
```

__fork() system call__

Both processes start their execution right after the system call fork()
. Since both processes have identical but separate address spaces, those variables initialized before
 the fork()
 call have the same values in both address spaces. Since every process has its own address space, any modifications will be independent of the others. In other words, if the parent changes the value of its variable, the modification will only affect the variable in the parent process's address space. Other address spaces created by fork()
 calls will not be affected even though they have identical variable names.
 
 __execve() system call__
 
 The exec system call family replaces the currently running process with a new process. But the original process identifier remains the same, and all the internal details, such as stack, data, and instructions. The new process replaces the executables. This function call family runs binary executables and shell scripts.
 
 ## Example of a pipe creation:
 
 ```
 #include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BUFFER SIZE 25
#define READ END 0
#define WRITE END 1
int main(void)
{
  char write msg[BUFFER SIZE] = "Greetings";
  char read msg[BUFFER SIZE];
  int fd[2];
  pid t pid;

  /* create the pipe */
  if (pipe(fd) == -1) {
    fprintf(stderr,"Pipe failed");
    return 1;
  }
  /* fork a child process */
  pid = fork();
  if (pid < 0) { /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  }
  if (pid > 0) { /* parent process */
  /* close the unused end of the pipe */
    close(fd[READ END]);
    /* write to the pipe */
    write(fd[WRITE END], write msg, strlen(write msg)+1);
    /* close the write end of the pipe */
    close(fd[WRITE END]);
  }
  else { /* child process */
    /* close the unused end of the pipe */
    close(fd[WRITE END]);
    /* read from the pipe */
    read(fd[READ END], read msg, BUFFER SIZE);
    printf("read %s",read msg);
    /* close the read end of the pipe */
    close(fd[READ END]);
  }
  return 0;
}
```

*Hope this is going to help you to finish the project with a good understanding of its general aspects!*
