# Mini Kernel
Small Kernel written in C over an emulated hardware module. The Kernel takes care of process scheduling (FIFO and roundrobin modes), synchronization with mutex and IO blocking calls.

## How to run
Several user-space C functions will trigger system calls that test developed functionality on the OS mini kernel
```bash
sh run.sh
```
