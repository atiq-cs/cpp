### P19 Media Player
*This project was deprecated by new Movies & TV App by Microsoft (project discontinued).*  

*Minor modification on [MFPlayer2](https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/multimedia/mediafoundation/MFPlayer2).*  
MFPlayer2 itself is a deprecated or obsolete Sample, ref, [MSFT medfound - medfound](https://learn.microsoft.com/en-us/windows/win32/medfound/media-foundation-sdk-samples)!


All files including 'images' dir are same except some modifications around 11-2013,
- ThemedButton.cpp: Successful linking required changing this file, more details on next section!
- MPlayer.rc: looks like co-ordinates are updated. Added this file here in this repo.
  
For ease of viewing the diff,

![Change on the resource file](https://user-images.githubusercontent.com/7858031/219880720-9a194038-e4de-4402-811f-6c13c94b5404.png)


**Code**  
`ZeroMemory` on 'ThemedButton.cpp(310)' throw this 'warning C4789' on x64,

    buffer 'BlendFn' of size 4 bytes will be overrun; 8 bytes will be written starting at offset 0
    LINK : fatal error LNK1257: code generation failed

Initialize struct to zero, ref, ThemedButton.cpp line 310,

```cpp
BLENDFUNCTION BlendFn = {0};
// ZeroMemory(&BlendFn, sizeof(BLENDFUNCTION));

```

**Build Instruction**  
Link against following additional libs (add to linker cmd),

    mf.lib mfplat.lib mfuuid.lib mfplay.lib comctl32.lib uxtheme.lib msimg32.lib shlwapi.lib


Otherwise we get,

    AudioSessionVolume.obj : error LNK2001: unresolved external symbol QISearch
    Player2.obj : error LNK2001: unresolved external symbol MFPCreateMediaPlayer
    x64\Release\Main.exe : fatal error LNK1120: 2 unresolved externals

from the linker!

**Notes on the Sample: MFPlayer2**  
- Main Video player app dialog looks like this,

![MFPlayer2 App Main Dialog](https://user-images.githubusercontent.com/7858031/219879973-218316a6-96df-4ac8-a7ed-c153e0a3e0e6.png)

- Open File shows how to implement a standard open file dialog.
- Open URL box looks like this,  

![MFPlayer2 App Open URL Tiny Dialog Box](https://user-images.githubusercontent.com/7858031/219879980-cba24031-39ee-4b99-8d73-02a12a78a3f4.png)

- In addition, Options has "Video Effect" which is a tick box.


**Refs**  
- Win Classic Media Foundation Sample [MSFT on Github  - MFPlayer2](https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/multimedia/mediafoundation/MFPlayer2), [MSFT Docs - medfound](https://learn.microsoft.com/en-us/windows/win32/medfound/mfplayer2-sample)
