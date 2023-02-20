### Timer
*Time a.k.a Delay Timer a.k.a Countdown Timer a.k.a Sleep Timer a.k.a Console Stop Watch*

Console application works as a countdown timer for Windows and Linux. Useful for windows batch scripts, powershell scripts and Linux bash shell scripts.

- On Win, functions as Sleep method in scripts, better of version Start-Sleep cmdlet
- On Unix, it functions as an enhanced version of sleep command.

#### Windows Instructions
Please put the dll file on the same directory where you keep 'Timer.exe'.
Otherwise, we need to install Visual C++ 2022 Redistributable, ref, [MSFT - Redist](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist).

**Usage Example**  
Start Timer for 1 minutes and 5 seconds,

    C:\> Timer 1:05

Start Timer for 30 seconds,

    C:\> Timer 30

Start Timer for 1 hour and 10 seconds,

    C:\> Timer 1:0:10

Start Timer for 25 hours 4 minutes and 4 seconds,

    C:\> Timer 25:04:04

While it's running it updates remaining time on the Console,

    C:\> Timer 1:6
    To elapse: 1m 6s

Once, the entire time has elapsed it says,

     1m 6s elapsed.


##### Linux
`gcc` was used to compile on Unix/Linux.

**Usage Example**  
Start Timer for 1 minutes and 5 seconds,

    $ ./Timer 1:05

Start Timer for 30 seconds,

    $ ./Timer 30

Start Timer for 1 hour and 10 seconds,

    $ ./Timer 1:0:10

Start Timer for 25 hours and 4 minutes and 4 seconds,

    $ ./Timer 25:04:04


**Refs**  
- Sleep function from Windows header [MSFT - nf-synchapi-sleep](https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-sleep) and an example use in code, ref, [MSFT - thread local storage](https://learn.microsoft.com/en-us/windows/win32/procthread/using-thread-local-storage)
- Deprecated link: A powershell script that uses this executable for notifying user after timeout is here: https://gallery.technet.microsoft.com/scriptcenter/Powershell-Delay-Counter-3ade4a08
