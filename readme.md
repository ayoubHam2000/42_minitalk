# Minitalk

The purpose of this project is to code a small data exchange program using UNIX signals between processes. 

<p align="center">
  <img src="./static/1.jpg">
</p>

## Key concepts

- Bit manipulation
- Bitwise operators
- Unix signals

## Unix signals

1. Sending a Signal:


    - When a process wants to send a signal to another process, it typically calls a system call like `kill()`. Despite its name, `kill()` is not just for terminating processes; it can send any signal.
    The `kill()` system call requires two arguments: the process ID (`PID`) of the target process and the signal number (e.g., `SIGINT`, `SIGTERM`).


    - The kernel first checks if the sending process has permission to send the signal. Generally, a process can send a signal to another process if they share the same user ID, or if the sending process is the superuser (root).


    - Once validated, the kernel queues the signal in the target process's signal descriptor. Each process has a data structure (typically part of the task structure in the kernel) that maintains a list of pending signals. The signal is marked as pending but not yet delivered.

2. Delivering the Signal:


    - The kernel doesn’t immediately deliver the signal. Instead, it marks the signal as pending and waits for the target process to enter a state where it can handle the signal (e.g., when it returns from a system call, when it is about to be scheduled, or when it checks for signals explicitly).


3. Handling the Signal:


    - The process can handle the signal in one of three ways:
      - **Default Action:** If no custom handler is defined, the process will perform the default action associated with the signal. This could be termination, ignoring the signal, or stopping/continuing execution.
      - **Custom Signal Handler:** If the process has registered a signal handler using functions like `signal()` or `sigaction()`, the kernel will execute this handler instead.
      - **Ignore the Signal:** The process can also choose to ignore the signal (except for signals like `SIGKILL` and `SIGSTOP`, which cannot be caught or ignored).


    - Before invoking the signal handler, the kernel saves the current execution context of the process (registers, program counter, stack pointer, etc.) so that the process can resume correctly after the handler finishes.
    The kernel then switches the process's execution context to run the signal handler. This involves setting the instruction pointer to the handler's address and switching to the handler’s stack frame.

4. Executing the Signal Handler:

    - The signal handler executes like a normal function but runs in a special context set up by the kernel.
    During the handler execution, some signals may be blocked (i.e., the process will not handle any new signals until the handler finishes).


    - After the handler completes, it typically returns using the `sigreturn()` system call (implicitly). This system call restores the process's previous execution context (saved before the handler was invoked).


6. Signal Queuing in Linux

    In Linux, signals are either standard signals or real-time signals, and they are treated differently with respect to queuing.

    - **Standard Signals:**
      Most signals in Linux are standard signals (e.g., `SIGINT`, `SIGTERM`, `SIGKILL`, etc.).
      Single Pending Signal: For standard signals, *the kernel does not queue multiple instances of the same signal*. If multiple signals of the same type are sent to a process while it’s still handling the first one, only one instance of that signal is recorded as pending.
      

    - **Real-Time Signals:**
      Real-time signals (which are a part of the `POSIX` real-time extensions) behave differently.
      Queued Signals: Real-time signals are queued, meaning if multiple real-time signals of the same type are sent to a process, each one is queued individually and will be delivered to the process in the order they were sent.
   
## Usage

- Compile
```
make
```
- Run the the server
```
./server
```
- Run the client to send message to the server process
```
./client <server pid> <message>
```

## Resources
- [Subject](./static/minitalk.pdf)
- [man7](https://man7.org/linux/man-pages/index.html)
- [Sending and Handling Signals in C](https://www.youtube.com/watch?v=83M5-NPDeWs&t=68s)
- [Extreme C (book)](https://www.dropbox.com/scl/fi/jspczpgumsd2ct7sluvox/Extreme_C_Taking_You_To_The_Limit_In_Concurrency_OOP_And_The_Most_Advanced_Capabilities_Of_C_Kamran_Amini_z-lib.org.pdf?rlkey=ffpu0qmift02gzo79vx36xe8j&e=1&dl=0)
