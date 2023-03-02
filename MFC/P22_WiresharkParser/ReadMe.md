### Wireshark Parser
*A C++ Parser that uses MFC for the GUI.*  

This MFC App parses UDP packets stored by wireshark; provides following info,
- Timestamp
- Source IP
- Destination IP
- Packet Length
- And data (optional)
- Decrypted header for signaling


Earlier version of this project did not use StunKeys. However, latest revision did include that to decrypt packets.

However, following two source files are missing from last svn commit,  
- StunKeySettings.h
- StunKeySettings.cpp

For now, StunKeys related code blocks are disabled compile time using Macro `STUN_KEYS_ENABLED`.

![Running version of the parser app](https://user-images.githubusercontent.com/7858031/222569177-a9351568-602c-493b-b4e8-df822a1d4630.png)

**Some old Refs**  
Probably considered this for Edit Browse Control,

```cpp
BOOL MainFrame::GetValidFolder(CString &buffer) {
  int pos = -1;

  do
  {
    DWORD attrib = GetFileAttributes(buffer);
    if (attrib != 0xffffffff && (attrib & FILE_ATTRIBUTE_DIRECTORY))
    {
      // The path is a valid folder
      if (buffer[buffer.GetLength() - 1] != '\\')
        buffer += "\\";

      return TRUE;
    }

    pos = buffer.ReverseFind('\\');

    if (pos > 0)
    {
      int len = buffer.GetLength();
      buffer.Delete(pos, len - pos);
    }
  } while (pos > 0);

  return FALSE;
}
```

Wireshark filters from draft,

    udp.dstport==101
    udp.srcport==100 || udp.srcport==101



**Refs**  
- [MSFT - MFC - Accessing File Status](https://learn.microsoft.com/en-us/cpp/mfc/accessing-file-status)
