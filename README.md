# Kernel-Hacking

## System Calls

**Trace** system call have the following return codes and parameters: 

```c
int trace(const char *pathname)
int getcount(void)
```

The first
system call is `trace()` and the second is `getcount()`.<br><br>
The first simply tells the OS to track how many times a particular file,
specified by the name `pathname`, has been opened.<br><br>
The second, `getcount()`, returns the value of a counter (perhaps called `trace_counter`
or something like that). This counter should be incremented every time any process calls the
`open()` system call if the pathname passed to open matches the pathname being traced.

**getreadcount** system call have the following return codes and
parameters: 

```c
int getreadcount(void)
```

It returns the value of a counter which is incremented every time any process calls the
**read()** system call.

## Lottery Scheduler

### Details

Two new system calls needed to implement this scheduler. The first is `int settickets(int number)`, which sets the number of tickets of the calling process. By default, each process gets one ticket, calling this routine makes it such that a process can raise the number of tickets it receives, and thus receive a higher proportion of CPU cycles.

The second is `int getpinfo(struct pstat *)`. This routine returns information about all running processes as shown in the structure pstat is given below.

Tickets are assigned to a process when it is created. Specfically, child process inherits the same number of tickets as its parents.

The structure called `pstat.h`:

```c
#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"

struct pstat {
  int inuse[NPROC];   // whether this slot of the process table is in use (1 or 0)
  int tickets[NPROC]; // the number of tickets this process has
  int pid[NPROC];     // the PID of each process 
  int ticks[NPROC];   // the number of ticks each process has accumulated 
};

#endif // _PSTAT_H_
```




