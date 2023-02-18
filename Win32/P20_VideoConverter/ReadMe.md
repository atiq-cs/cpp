### P20 Video Converter
*This project hasn't been published/released before.*  
Video conversion is probably tested. However, how many options/capabilities are supported needs to be checked!



**Notes** 
- Manifest statement is at 'MFConverter.h'.
- 'Main.ico' seems not linked to the application binary!
- Following files comes from MFPlayer2 sample, link here
  - MainDialog.* (adapted and heavily modified)
  - MFConverter.h


- Following files comes from Transcode sample, link here
  - Transcode.*


**Build instructions**  
- Similar to previous project (Shutdown Timer), link against comctl32.lib (add this lib to linker cmd).


**App Screenshots**  

![VC App Main Dialog](https://user-images.githubusercontent.com/7858031/219830020-c1d33eb9-d097-4c86-9af3-6a06f3bf9496.png)


**Refs**  
- Win Classic Media Foundation Sample [MSFT on Github  - MFPlayer2](https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/multimedia/mediafoundation/MFPlayer2)
- Win Classic Media Foundation Sample [MSFT on Github  - Transcode](https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/multimedia/mediafoundation/Transcode)


**07-2013 plans**  
- First thing I tried was to create is the main dialog.
- Then, planned Keep all core functions of MFPlayer and,

Planned Video conversion with options to customize following,
- Video height
- Video width
- Frame rate
- Bit Rate


TODOs planned,
- Multi-threading Support
- Use aac as audio encoder
- Rename fps as 1000 seconds
- Keep previous settings using registry, retrived media info for dropped file
- Cropping video
- Better UI (later)


```cpp
// place holder
```


**Common-Controls Version**  
Changing the Common-Controls version from

    6.0.0.0

to,

    6.10.0.0

for example, to following,

    Microsoft.Windows.Common-Controls,language="&#x2a;",processorArchitecture="&#x2a;",publicKeyToken="6595b64144ccf1df",type="Win32",version="6.10.0.0" 

causes side by side app configuration error,

> SideBySide: ref, binary: x64\Debug\VConv.exe
> Activation context generation failed for "D:\Code\cpp\Win32\VConv_07-26-2013\x64\Debug\VConv.exe". Dependent Assembly Microsoft.Windows.Common-Controls,language="&#x2a;",processorArchitecture="&#x2a;",publicKeyToken="6595b64144ccf1df",type="Win32",version="6.10.0.0" could not be found. Please use sxstrace.exe for detailed diagnosis.

