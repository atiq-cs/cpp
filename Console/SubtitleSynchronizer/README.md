### Subtitle Synchronizer
- only supported subtitle format: SubRip (.srt)
 
Input:  
	filename_pre.srt
	
Output:  
	filename.srt

**Platforms**  
Currently tested on Windows. With some trivial modifications it should work on Linux.

**Cmd Example**  
Example delay subtitle to 16 seconds and fix sequence number

    $ SubSync.exe "D:\TEDTalks\Tan Le - My immigration story (no sub)_2011X-480p_pre.srt" '00:00:16,000' 0
