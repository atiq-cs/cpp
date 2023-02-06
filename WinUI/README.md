## Win Apps with C++

### Win UI
Win UI is the future direction for now for developing Apps in C++ for Windows.

Apps on Arm64
https://learn.microsoft.com/en-us/windows/arm/arm64ec


**Installation**  
VS requires following on Windows 10 Device,
- Latest Win 10 SDK (Win 11 SDK doesn't enable Win UI Templates on Win 10)

For creating and running an application: ref, [MSFT Docs - Create your first WinUI 3 (Windows App SDK) project](https://learn.microsoft.com/en-us/windows/apps/winui/winui3/create-your-first-winui3-app) is dated!

We create packaged applications to make it work. And we do not set `AppxPackage` to `false`. Instead we leave it to default,

    <AppxPackage>true</AppxPackage>


Otherwise, application cannot run. An error pops up complaining about wrong deployment config.


**Refs**  
- [WinUI 3 Demos](https://github.com/microsoft/WinUI-3-Demos)
- [GitHub C++ `.gitignore`](https://github.com/github/gitignore/blob/main/C%2B%2B.gitignore)