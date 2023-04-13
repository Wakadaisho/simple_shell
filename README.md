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

## Compilation
Your shell will be compiled this way:<br>
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
