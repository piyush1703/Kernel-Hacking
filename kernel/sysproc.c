#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "pstat.h"
#include "spinlock.h"

struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

int
sys_settickets(void)
{
  int n;
  if(argint(0, &n) < 0)
  {
	myproc()->tickets = 1;
	return -1;
  }

   myproc()->tickets = n;
   return 0;
}

int
sys_getpinfo(void)
{
  acquire(&ptable.lock);
  struct pstat* procstat;
  struct proc* p;
  if(argint(0, (int*)(&procstat)) < 0) {
    return -1;
  }

  for(p = ptable.proc; p != &(ptable.proc[NPROC]); p++) {
    int index = p - ptable.proc;
    if(p->state != UNUSED) {
	procstat->pid[index] = p->pid;
        procstat->ticks[index] = p->ticks;
	procstat->tickets[index] = p->tickets;
	procstat->inuse[index] = p->inuse;
    }
  }
  release(&ptable.lock);
  return 0;
}

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_getreadcount(void)
{
	return read_count;
}

int
sys_trace(void)
{
    char *pathname;
    if (argstr(0, &pathname) < 0)
        return -1;

    if (pathname == 0)
        return -1;

    acquire(&tickslock);
    safestrcpy(trace_pathname, pathname, sizeof(trace_pathname));
    trace_counter = 0;
    trace_enabled = 1;
    release(&tickslock);

    return 0;
}

int
sys_getcount(void)
{
    if (!trace_enabled)
        return 0;
    return trace_counter;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
