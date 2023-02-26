### ICMP Network Programming Demo with Minimal MFC GUI
*As part of drafts from Ping GUI iniital attempts.*

### Network Programming
This section also serves as Win32 / Network Programming reference.

For sending ICMP requests latest API is, `IcmpSendEcho2` (ref below). The ref contains an example in cpp.

Earlier function is named `IcmpSendEcho` which is used in the demo program here.

**Ping App Output**  
An app screenshot of the ping demo app as it receives ICMP reply from server is showed in screenshot below,  
  
![ICMP Reply](https://user-images.githubusercontent.com/7858031/221376351-0443c9b1-bc08-4bdf-9702-31d8e5b11e1b.png)

Demo runs for 20 seconds, then it shows a Message Box for closing it,

![Timer up, close app](https://user-images.githubusercontent.com/7858031/221376353-fc26017e-c209-4c92-af6d-7961baea29d5.png)


**Refs**  
- [MSFT - IcmpSendEcho2](https://learn.microsoft.com/en-us/windows/win32/api/icmpapi/nf-icmpapi-icmpsendecho2)
- [MSFT - IcmpSendEcho](https://learn.microsoft.com/en-us/windows/win32/api/icmpapi/nf-icmpapi-icmpsendecho)
- [MSFT - Win32 - Retrieving HTTP Headers](https://learn.microsoft.com/en-us/windows/win32/WinInet/retrieving-http-headers)
- [MSFT - Win32 Internet - Asynchronous Example Application](https://learn.microsoft.com/en-us/windows/win32/wininet/asynchronous-example-application)