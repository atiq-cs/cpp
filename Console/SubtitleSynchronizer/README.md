### Subtitle Synchronizer
- only supported subtitle format: SubRip (.srt)
 
Input:  
	filename_pre.srt
	
Output:  
	filename.srt

**Build**  
Build instruction at [Console Projects Build - Main ReadMe](https://github.com/atiq-cs/cpp/tree/dev/Console).

I like to rename the binary during linking,

    link /OUT:x64\Release\SubSybc.exe ...


**Platforms**  
*Currently tested on Windows. With some trivial modifications it should work on Linux.*

**Cmd Example**  
Example delay subtitle to 16 seconds and fix sequence number,

    $ SubSync.exe "D:\TEDTalks\Tan Le - My immigration story (no sub)_2011X-480p_pre.srt" '00:00:16,000' 0

It fixes the sequence number when 0 is provided as sequence#.

Providing wrong argument leads to a help output like this below,

    $ SubSync.exe /help
    Subtitle Synchronizer 0.95

    You provided 1 cmd arg(s). They are
    1. /help
    SubMod: incorrect commandline. Number of arguments should be 3. They are:
    1. srt file location
    2. [+/-]H:M:S,M (+ to make delay)
    3. Sequence Offset (put a zero for default): this is sequence number that precedes every caption.