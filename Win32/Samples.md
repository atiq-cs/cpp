## Windows SDK and Visual Studio Samples

Most of the old samples are available on
- [GitHub MSFT Archive](https://github.com/microsoftarchive), [GitHub MSFT Archive Samples Search](https://github.com/microsoftarchive?q=sample&type=all&language=&sort=) root archive containing tons of samples, includes
  - [microsoftarchive/msdn-code-gallery-microsoft](https://github.com/microsoftarchive/msdn-code-gallery-microsoft) Windows SDK Samples, Kit Samples, Visual Studio and Office Samples
    - [C# Visual Studio 2010 SDK Samples](https://github.com/microsoftarchive/msdn-code-gallery-microsoft/tree/master/Visual%20Studio%20Product%20Team/Visual%20Studio%202010%20SDK%20Samples/%5BC%23%5D-Visual%20Studio%202010%20SDK%20Samples), ref, 'Visual Studio 2010 SDK Samples All.zip'
    - [C++ Visual Studio 2010 SDK Samples](https://github.com/microsoftarchive/msdn-code-gallery-microsoft/tree/master/Visual%20Studio%20Product%20Team/Visual%20Studio%202010%20SDK%20Samples/%5BC%2B%2B%5D-Visual%20Studio%202010%20SDK%20Samples), ref, 'Visual Studio 2010 SDK Samples  VC++.zip'
    - [Windows 8 desktop samples](https://github.com/microsoftarchive/msdn-code-gallery-microsoft/tree/master/Official%20Windows%20Platform%20Sample/Windows%208%20desktop%20samples)
    - [Windows 8.1 desktop samples](https://github.com/microsoftarchive/msdn-code-gallery-microsoft/tree/master/Official%20Windows%20Platform%20Sample/Windows%208.1%20desktop%20samples)


  - Classic Win Samples Repository: [microsoft/Windows-classic-samples](https://github.com/microsoft/Windows-classic-samples) contains
    - [Win 7 Samples](https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples) which includes,
      - [WinUI Samples](https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/winui) i.e., HotKey registration
    - In addition, includes MFPlayer2 and Transcode as part of Media Foundation samples,  
  
listed from local copy,  

    $ gci 'Windows Desktop App Development\All Samples\New samples'
    Mode                 LastWriteTime         Length Name
    ----                 -------------         ------ ----
    d----          12/13/2017  1:07 PM                TCP  IP Server Client Example
    -a---            6/8/2014  8:14 PM         796572 A basic Windows service in C++ (CppWindowsService)_3.zip
    -a---            6/4/2014  9:05 PM       32219354 Basic thread synchronization in C++.zip
    -a---            6/8/2014  8:02 PM          51529 Build Progress Bar.zip
    -a---            6/4/2014  8:53 PM         252551 C++ app automates PowerPoint (CppAutomatePowerPoint).zip
    -a---            6/4/2014  8:52 PM         154877 C++ app dynamically loads a DLL (CppLoadLibrary).zip
    -a---            6/4/2014  8:52 PM         204989 C++ app hosts CLR 4 and invokes .NET assembly (CppHostCLR).zip
    -a---            6/4/2014  8:52 PM          41799 C++ Dynamic-link Library (CppDynamicLinkLibrary).zip
    -a---            6/4/2014  8:52 PM          36975 C++ UTF-8 Conversion Helpers.zip
    -a---            6/4/2014  8:50 PM          70703 C++ Windows Shell context menu handler (CppShellExtContextMenuHandler).zip
    -a---            6/4/2014  8:50 PM          47001 CaptureEngine video capture sample.zip
    -a---            6/8/2014  8:11 PM          68984 Complete Matching Game tutorial sample.zip
    -a---            6/8/2014  8:01 PM          46426 Data Binding Demo.zip
    -a---            6/4/2014  8:48 PM          72862 Device Console (DevCon) Tool.zip
    -a---            6/4/2014  8:49 PM         363154 Direct3D Tutorial Win32 Sample.zip
    -a---            6/8/2014  7:33 PM         847107 DirectX 3D shooting game sample.zip
    -a---            6/4/2014  8:50 PM          88088 DirectX video rendering sample.zip
    -a---            6/4/2014  8:54 PM        6030895 DirectXTK Simple Win32 Sample.zip
    -a---            6/4/2014  8:46 PM       11485880 Example of math expressions, variables, and if statements_2.zip
    -a---            6/4/2014  8:42 PM         275015 Example of math expressions, variables, and if statements.zip
    -a---            6/4/2014  8:50 PM         111902 HClient sample application.zip
    -a---            6/4/2014 10:25 PM          84540 Header for WRL and C++ for Vector, Map, UnorderedMap, KeyValuePair containers.zip
    -a---            6/4/2014  8:49 PM         819524 Hilo.zip
    -a---            6/8/2014  8:02 PM         369350 How to modify data in DataTable and update to the data source.zip
    -a---            6/4/2014  8:49 PM         864781 Huo Chess (C#, C++, VB micro chess) c++.zip
    -a---            6/4/2014  8:48 PM         370254 Huo Chess (C#, C++, VB micro chess).zip
    -a---            6/8/2014  8:06 PM         214105 Introduction to Building WPF Applications.zip
    -a---            6/8/2014  8:01 PM          64170 Learning C# - List  Collection Code Sample.zip
    -a---            6/8/2014  8:03 PM       13550570 Make a part of your Bitmap transparent c++.zip
    -a---            6/8/2014  8:02 PM         131602 Make a part of your Bitmap transparent.zip
    -a---            6/4/2014 10:25 PM          54216 MediaFoundation transform decoder as hardware MF transcoder sample.zip
    -a---            6/4/2014  8:52 PM         101236 MFC CTaskDialog sample (MFCTaskDialog).zip
    -a---            6/4/2014  8:52 PM         114003 MFC Direct2D Hello World sample.zip
    -a---            6/4/2014  8:52 PM         283494 Modal and modeless dialogs in MFC (MFCDialog)_2.zip
    -a---            6/4/2014  8:52 PM         271453 Modal and modeless dialogs in MFC (MFCDialog).zip
    -a---            6/4/2014  8:48 PM          33724 ODBC database sample.zip
    -a---            6/8/2014  8:01 PM         182473 Pacman Game.zip
    -a---            6/8/2014  7:51 PM         116409 Simple Calculator.zip
    -a---            6/8/2014  8:01 PM        1310874 Single File Generator.zip
    -a---            6/8/2014  8:07 PM        7220139 TCP  IP Server Client Example Part 4 (Chat Application).zip
    -a---            6/8/2014  8:06 PM        2018576 TCP  IP Server Client Example Part 6 (Chat Application).zip
    -a---            6/8/2014  8:06 PM        1413824 TCP  IP Server Client Example Part 7 (Chat Application).zip
    -a---            6/4/2014  8:53 PM         245296 Track the system CPU usage (CppCpuUsage).zip
    -a---            6/4/2014  8:50 PM         119884 UAC self-elevation (CppUACSelfElevation).zip
    -a---            6/4/2014  8:43 PM         300157 USBView sample application.zip
    -a---            6/8/2014  8:01 PM          53851 Virtual hard disk management sample_2.zip
    -a---            6/8/2014  8:01 PM          58898 Virtual hard disk management sample.zip
    -a---            6/4/2014  8:50 PM         540539 Windows common controls demo (CppWindowsCommonControls).zip
    -a---            6/4/2014  9:11 PM      106206722 Windows Driver Kit (WDK) 8.1 Samples.zip


  - Listing resumes for Classic Win Samples Repository: [microsoft/Windows-classic-samples](https://github.com/microsoft/Windows-classic-samples)
    - [WMP Samples C++](https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/multimedia/WMP) as part of multimedia samples.
    - WMP SDK Samples were part of Windows SDK around Windows 7, ref, [MSFT - WMP SDK Samples](https://learn.microsoft.com/en-us/windows/win32/wmp/samples)

- [MSFT Docs - Visual Studio C++ Official Samples Main Page](https://learn.microsoft.com/en-us/cpp/overview/visual-cpp-samples) lists ATL, COM, CLR, MFC Samples

MSFT org page has following repos on GitHub,
- [microsoft/VCSamples](https://github.com/microsoft/VCSamples) contains VS Samples 2008, 2010, 2012, and 2015
  - [VC2012Samples](https://github.com/microsoft/VCSamples/tree/master/VC2012Samples) (also called Windows 8 samples)
  - VC2010SP1Samples C++
  - All [VC 2010 Samples dir](https://github.com/microsoft/VCSamples/tree/master/VC2010Samples) contents

- [Windows App SDK Samples](https://github.com/microsoft/WindowsAppSDK-Samples)
- Raymond Chen archived a bunch of samples in [GH - oldnewthing](https://github.com/oldnewthing)
  - Windows-universal-samples
  - old-Windows8-samples
  - build2018setssample
  - old-Windows-universal-samples


[MSFT - Browse code samples](https://learn.microsoft.com/en-us/samples/browse)
- Processing Command Line Arguments Sample [wpf-samples/processing-command-line-arguments-sample](https://learn.microsoft.com/en-us/samples/microsoft/wpf-samples/processing-command-line-arguments-sample/)


Some of the msdn etc samples are archived archive links at,

    microsoftarchive/msdn-code-gallery-community-a-c-*

links are listed on [MSFT TeamBlog](https://learn.microsoft.com/en-us/teamblog/msdn-code-gallery-retired)


UWP, Games and Graphics, Drivers, tools and packaging and Windows 10 UWP samples are at: https://microsoft.github.io/windows