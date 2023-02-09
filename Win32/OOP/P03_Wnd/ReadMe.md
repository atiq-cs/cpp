## P03 Window Based Template
\*\* *Note this is an outdated template compared to VS 2022. TODO: update it based on P04_VS2022*  

This is an OOP Skeleton with an actual Window as Base.

Previous two projects,
- P01_Modeless, and,
- P02_Modeless_KB

founded the OOP code based on a Modeless Dialog. However, this one is founded on a Wnd.

**Backup of previous versions**  
`RegisterClass` example, before we replaced our code with `RegisterClassEx`,

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

*Screenshot*  

![P03 Window Based OOP Template](https://user-images.githubusercontent.com/7858031/217655906-7cf6ee2d-20cc-4cf1-b6dd-64dd60d8c8e8.png)
