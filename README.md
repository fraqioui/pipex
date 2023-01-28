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





