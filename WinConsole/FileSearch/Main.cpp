//
// PURPOSE: File searching API `FindFirstFile`, wild card search for files
//
// Author : Atiq Rahman
// Date   : 10-23-2009
// Status : Good
// Remarks: Demos,
//        - Unicode Console project due to the use of TCHAR
//        - conversion from C++ string to LPTSTR
// Output :
//        Provided file: D:\Docs\TODO\Code\*.txt
//        The first file found is stdt codeplex.txt
//

#include <windows.h>
#include <iostream>


//
// PURPOSE: Probably wanted to replicate Unix `ls` tool
//
void ls(std::wstring csFilePath) {
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;

    std::wcout << "Provided file: " << csFilePath << std::endl;

    LPCTSTR filePath = csFilePath.c_str();

    hFind = FindFirstFile(filePath, &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        std::cout << "FindFirstFile failed " << GetLastError();
        return ;
    }
    else
    {
        std::wcout << "The first file found is " << FindFileData.cFileName << std::endl;
        FindClose(hFind);
    }
}


int main()
{
    // std::wstring filePath = L"D:\\Docs\\TODO\\Code\\*.txt";
    std::wstring filePath = L"D:\\Docs\\*.txt";
    ls(filePath);
}
