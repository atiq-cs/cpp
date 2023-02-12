### RegisterClass
Latest example based on SDK template is on OOP Template. ref, [MSFT Doc - Using Window Classes](https://learn.microsoft.com/en-us/windows/win32/winmsg/using-window-classes) provides comment for each field of `WNDCLASSEX`.

Various ways of registering class with some customizations,

**v1**  
```cpp
WNDCLASSEX wcex;

// Fill in the window class structure with parameters
// that describe the main window. 
wcex.cbSize = sizeof(wcex);          // size of structure
wcex.style = CS_HREDRAW | 
    CS_VREDRAW;                    // redraw if size changes
wcex.lpfnWndProc = DERIVED_TYPE::WindowProc;     // points to window procedure
wcex.cbClsExtra = 0;                // no extra class memory
wcex.cbWndExtra = 0;                // no extra window memory
wcex.hInstance = GetModuleHandle(nullptr);         // handle to instance
wcex.hIcon = LoadIcon(nullptr, 
    IDI_APPLICATION);              // predefined app. icon
wcex.hCursor = LoadCursor(nullptr, 
    IDC_ARROW);                    // predefined arrow
// Was this to change Window Background to Whitish ?
// wcex.hbrBackground  = (HBRUSH) (COLOR_WINDOW+1);
wcex.hbrBackground = (HBRUSH) GetStockObject( 
    WHITE_BRUSH);                  // white background brush
// Utilize valid menu resource, otherwise Registering Window and ShowWindow won't work
// wcex.lpszMenuName =  L"MainMenu";    // name of menu resource
wcex.lpszClassName = ClassName();  // name of window class
// wcex.hIconSm = LoadImage(wcex.hInstance, // small class icon
//     MAKEINTRESOURCE(5),
//     IMAGE_ICON,
//     GetSystemMetrics(SM_CXSMICON),
//     GetSystemMetrics(SM_CYSMICON),
//     LR_DEFAULTCOLOR);

// Register the window class.
RegisterClassEx(&wcex);
```

**v2**  

`RegisterClass` example, before we replaced our code with `RegisterClassEx`,

```cpp
WNDCLASS wcex = {0};

//wcex.cbSize = sizeof(WNDCLASSEX);
wcex.style          = CS_HREDRAW | CS_VREDRAW;
wcex.lpfnWndProc    = DERIVED_TYPE::WindowProc;
wcex.cbClsExtra     = 0;
wcex.cbWndExtra     = 0;
wcex.hInstance      = GetModuleHandle(NULL);
// Following throws this compile time error:
//   Main.cpp(66,1): warning C4302: 'type cast': truncation from 'LPWSTR' to 'WORD'
// wcex.hIcon          = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
wcex.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
wcex.hbrBackground  = (HBRUSH) (COLOR_WINDOW+1);
wcex.lpszMenuName   = NULL;
wcex.lpszClassName  = ClassName();
//wcex.hIconSm    = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

RegisterClass(&wcex);
```
