#ifndef KERNEL_H
#define KERNEL_H

/*
    Structs
*/

typedef struct {
    uint32_t ra, sp, s8, s0, s1, s2, s3, s4, s5, s6, s7, gp;
} JmpBuf;

typedef struct {
    HandlerInfo * next;
    void (*handler)(int);
    int (*verifier)();
    uint32_t padding;
} HandlerInfo;

/*
    Functions here are direct calls to the PSX kernel functions
    https://psx-spx.consoledev.net/kernelbios/#bios-function-summary
*/

void LoadExec(char * name, unsigned int stackAddr, unsigned int stackSize);
void InitHeap(unsigned int * head, unsigned int size);
void setExceptionJmpBuf(JmpBuf * jmpBup);

void ExitCriticalSection();
void ReturnFromException();
void ChangeClearPAD(int val);
int ChangeClearRCnt(int timer, int flag);
void EnterCriticalSection();
void ResetEntryInt();

int GPU_cw(unsigned int cmd);
void DeliverEvent(unsigned int class, unsigned int spec);

int open(char * devname, int flag);
int close(int fd);
unsigned int lseek(int fd, unsigned int offset, int flag);
int read(int fd, char * buf, int n);
int write(int fd, char * buf, int n);

HandlerInfo * sysDeqIntRP(int priority, HandlerInfo * handler);
int sysEnqIntRP(int priority, HandlerInfo * handler);

int TestEvent(unsigned int event);
unsigned int OpenEvent(unsigned int class, unsigned int spec, unsigned int mode, void (*handler)());
int EnableEvent(unsigned int event);
int CloseEvent(unsigned int event);

#endif