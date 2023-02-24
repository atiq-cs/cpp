### Bitmap Viwer Control
*Emot icon related custom control project.*

`BitmapViewer` implementation might be based on the codeproject article (linked in Refs below).

In `OnInitDialog`,
```cpp
m_Viewer.SetBitmap(IDB_BITMAP_IMAGE);
```

Also, has data exchange bound in `DoDataExchange`,
```cpp
DDX_Control(pDX, IDC_BMP, m_Viewer);
```

**App Output**  
An app screenshot of the bitmap is showed in the control is showed in screenshot,  
  
![Bitmap Viewer CC Screenshot](https://user-images.githubusercontent.com/7858031/221285585-4821cce0-729a-44b6-a10e-46b9594ea4ce.png)
  

**Refs**  
- [Chris Maunder - Creating Custom Controls, codeproject](https://www.codeproject.com/articles/521/creating-custom-controls)
- [MSFT Docs - CBitmap](https://learn.microsoft.com/en-us/cpp/mfc/reference/cbitmap-class)