.set noreorder
.align 2
.global LoadExec
.type LoadExec, @function

LoadExec:
    li    $t2, 0xA0
    jr    $t2
    li    $t1, 0x51

.set noreorder
.align 2
.global InitHeap
.type InitHeap, @function

InitHeap:
    li    $t2, 0xA0
    jr    $t2
    li    $t1, 0x39

.set noreorder
.align 2
.global setExceptionJmpBuf
.type setExceptionJmpBuf, @function

setExceptionJmpBuf:
    li    $t2, 0xB0
    jr    $t2
    li    $t1, 0x19

.set noreorder
.align 2
.global ExitCriticalSection
.type ExitCriticalSection, @function

ExitCriticalSection:
    li    $a0, 0x02
    syscall
    jr $ra
    nop

.set noreorder
.align 2
.global ReturnFromException
.type ReturnFromException, @function

ReturnFromException:
    li    $t2, 0xB0
    jr    $t2
    li    $t1, 0x17

.set noreorder
.align 2
.global ChangeClearPAD
.type ChangeClearPAD, @function

ChangeClearPAD:
    li    $t2, 0xB0
    jr    $t2
    li    $t1, 0x5B

.set noreorder
.align 2
.global ChangeClearRCnt
.type ChangeClearRCnt, @function

ChangeClearRCnt:
    li    $t2, 0xC0
    jr    $t2
    li    $t1, 0x0A

.set noreorder
.align 2
.global EnterCriticalSection
.type EnterCriticalSection, @function

EnterCriticalSection:
    li    $a0, 0x01
    syscall
    jr $ra
    nop

.set noreorder
.align 2
.global ResetEntryInt
.type ResetEntryInt, @function

ResetEntryInt:
    li    $t2, 0xB0
    jr    $t2
    li    $t1, 0x18

.set noreorder
.align 2
.global GPU_cw
.type GPU_cw, @function

GPU_cw:
    li    $t2, 0xA0
    jr    $t2
    li    $t1, 0x49

.set noreorder
.align 2
.global DeliverEvent
.type DeliverEvent, @function

DeliverEvent:
    li    $t2, 0xB0
    jr    $t2
    li    $t1, 0x07

.set noreorder
.align 2
.global open
.type open, @function

open:
    li    $t2, 0xB0
    jr    $t2
    li    $t1, 0x32

.set noreorder
.align 2
.global close
.type close, @function

close:
    li    $t2, 0xB0
    jr    $t2
    li    $t1, 0x36

.set noreorder
.align 2
.global lseek
.type lseek, @function

lseek:
    li    $t2, 0xB0
    jr    $t2
    li    $t1, 0x33

.set noreorder
.align 2
.global read
.type read, @function

read:
    li    $t2, 0xB0
    jr    $t2
    li    $t1, 0x34

.set noreorder
.align 2
.global write
.type write, @function

write:
    li    $t2, 0xB0
    jr    $t2
    li    $t1, 0x35

.set noreorder
.align 2
.global sysDeqIntRP
.type sysDeqIntRP, @function

sysDeqIntRP:
    li    $t2, 0xC0
    jr    $t2
    li    $t1, 0x03

.set noreorder
.align 2
.global sysEnqIntRP
.type sysEnqIntRP, @function

sysEnqIntRP:
    li    $t2, 0xC0
    jr    $t2
    li    $t1, 0x02

.set noreorder
.align 2
.global TestEvent
.type TestEvent, @function

TestEvent:
    li    $t2, 0xB0
    jr    $t2
    li    $t1, 0x0B

.set noreorder
.align 2
.global OpenEvent
.type OpenEvent, @function

OpenEvent:
    li    $t2, 0xB0
    jr    $t2
    li    $t1, 0x08

.set noreorder
.align 2
.global EnableEvent
.type EnableEvent, @function

EnableEvent:
    li    $t2, 0xB0
    jr    $t2
    li    $t1, 0x0C

.set noreorder
.align 2
.global CloseEvent
.type CloseEvent, @function

CloseEvent:
    li    $t2, 0xB0
    jr    $t2
    li    $t1, 0x09
