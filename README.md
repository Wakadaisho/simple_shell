# 0x16. C - Simple Shell
## Background Context
### Write a simple UNIX command interpreter.

## Output
*    Unless specified otherwise, your program __must have the exact same output__ as `sh` (`/bin/sh`) as well as the exact same error output.<br>
*    The only difference is when you print an error, the name of the program must be equivalent to your `argv[0]` (See below)<br>
Example of error with `sh`:<br>
```bash
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
```
Same error with your program `hsh`:<br>
```bash
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
```
## List of allowed functions and system calls
* access (man 2 access)<br>
* chdir (man 2 chdir)<br>
* close (man 2 close)<br>
* closedir (man 3 closedir)<br>
* execve (man 2 execve)<br>
* exit (man 3 exit)<br>
* _exit (man 2 _exit)<br>
* fflush (man 3 fflush)<br>
* fork (man 2 fork)<br>
* free (man 3 free)<br>
* getcwd (man 3 getcwd)<br>
* getline (man 3 getline)<br>
* getpid (man 2 getpid)<br>
* isatty (man 3 isatty)<br>
* kill (man 2 kill)<br>
* malloc (man 3 malloc)<br>
* open (man 2 open)<br>
* opendir (man 3 opendir)<br>
* perror (man 3 perror)V
* read (man 2 read)<br>
* readdir (man 3 readdir)<br>
* signal (man 2 signal)<br>
* stat (__xstat) (man 2 stat)<br>
* lstat (__lxstat) (man 2 lstat)<br>
* fstat (__fxstat) (man 2 fstat)<br>
* strtok (man 3 strtok)<br>
* wait (man 2 wait)<br>
* waitpid (man 2 waitpid)<br>
* wait3 (man 2 wait3)<br>
* wait4 (man 2 wait4)<br>
* write (man 2 write)<br>

## Compilation
Your shell will be compiled this way:<br>
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Testing 
Your shell should work like this in interactive mode:<br>
```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```
But also in non-interactive mode:<br>
```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```
