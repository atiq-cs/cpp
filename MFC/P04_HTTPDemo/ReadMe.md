### HTTP Request / Download Demo
*As part of drafts from Networking Programming prjects with Win32.*  

This is a demo that was prepared aiming to build a software similar to or better than IDM (Internet Download Manger). ref, *P4_http1*

Demonstrates following,
- Shell Browe, `SHBrowse`

Name in manifest, might be useful to create an installer,

    name="FFTSys.Internet.Software"
    // ...
    <description>Internet Download Manager</description>

Some URL etc. resources are hardcoded though.

**Interesting Demos**  
This app is loaded with interesting applications.

File attribute check example,
- GetValidFolder

File / Folder Browse,
- SHBrowseForFolder

Control related demos,
- Enable/disable control
- Combo edit file browser (with selection pop up)
- Control color modified using `OnCtlColor`

NP demos,
- GetHttpConnection, OpenRequest, Read (download by chunk)

**Input URL List File**  
Example input URL is pretty straight forward. URLs delimetered by newline. Example, URL list file looks like this,

    https://github.com/openssh/openssh-portable/archive/refs/tags/V_9_1_P1.zip


ref, *Input_DN_URLs.txt*

**Downloader Demo App Output**  

An app screenshot of the ping demo app as it receives ICMP reply from server is showed in screenshot below,  
  
![HTTP App Screenshot](https://user-images.githubusercontent.com/7858031/221424213-50503470-8e0a-499c-b359-394f5dcdf16b.png)


**Refs**  
- [MSFT - CInternetSession::GetHttpConnection](https://learn.microsoft.com/en-us/cpp/mfc/reference/cinternetsession-class?#gethttpconnection)
