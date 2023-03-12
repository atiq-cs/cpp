### Emot Icon Control Project
**Index**  
- [C++ Database Demos](../../../Console/DB/)  
- Earlier [Drafts](https://github.com/atiq-cs/cpp/blob/dev/MFC/CustomControl/P05_EmotIconChat/Drafts.md) / Code Revisions
  
*A C++ Parser that uses MFC for the GUI, writtein around 12-2013*  

Documentation is in comments,
- ChatControl.cpp
- ChatControl.h

Demos,  
- SQLite Example

However, the database loading part is commented out in `MainDlg` for now.

Some methods/code are duplicate in `CChatUIPainter.cpp`. However, instantiation of 'CChatUIPainter' class  in `CChatControl::OnPaint()` is commented out.


**App Screenshot**  
An app screenshot of the chat box is showed in screenshot below,  
  
![All Emot Icons in Pop Up Dlg](https://user-images.githubusercontent.com/7858031/224502994-a9ad7ab2-12a2-4700-9e68-c299cd8d8d24.png)
  
  
![Edit Control for Chat with Emot Icons](https://user-images.githubusercontent.com/7858031/224503006-e385e308-fb0a-4090-ad8b-27c8fec4695c.png)

  
![Just the emot icons](https://user-images.githubusercontent.com/7858031/224509640-2fe8337a-7672-401e-9faf-0eba254fe8cd.png)


**Emot Icon Indices**  

Index mapping of emot icons, ref, *06-14-2014*,  

| 0     | 26    |
| ----- | ----- |
| 1,2,3 | 0,1,2 |
| 4     | 28    |
| 5     | 3     |
| 6     | 4     |
| …     | …     |
| 27    | 25    |
| 28    | 27    |
| 29    | 29    |
| 30    | 30    |
| …     | …     |
| 33    | 33    |
| 34    | 42    |
| 35    | 43    |
| 36    | 34    |
| 37    | 45    |
| 38    | 35    |
| 39    | 36    |
| ….    | …..   |
| 44    | 41    |
| 45    | 44    |
| 46    | …     |



### TODO
ref, *08-03-2014*  
- Function `createIMChatWindow` failing
- Integrate availability pic
- Handle offline messages / load from db.
- Later, fix Custom Chat Control Issues

**Custom Control Issues**  
When a different user name sends a message it doesn't add the username for display before current message.
Crashes sometimes on `GetoutputExtent` which call is inside `ChatControl::AddPaintElement`


