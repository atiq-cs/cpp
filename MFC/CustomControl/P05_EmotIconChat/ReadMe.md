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


**Emot Icon Indices Continues..**  
Original list, 11-04-2013,

```
:)
:(
:D
:P
:S
:O
:@
:-[
:-]
:|
:'(
:>
:3
:*
:V
:/
;)
>:(
>:O
8)
8|
O.o
O:)
3:)
L(\
L3
:))
:Z
:POOP
:$
:0
::3
:4
:-h
:6
:8
:9
:12
:-?
(Y)
:54
:56
:60
:67
:72
:88
=((
```

rearranged version, same date,

```
:))
:)
:(
:D
:POOP
:P
:S
:O
:@
:-[
:-]
:|
:'(
:>
:3
:*
:V
:/
;)
>:(
>:O
8)
8|
O.o
O:)
3:)
L(\
L3
:Z
:$
:0
::3
:4
:-h
:60
:67
:6
:88
:8
:9
:12
:-?
(Y)
:54
:56
:72
=((
```

And, icons mapping, 09-01-2013,

```
":-)" = "smile"
":)" = "smile"
":]" = "smile"
"=)" = "smile"
":@" = "angry"
":-(" = "frown"
":(" = "frown"
":[" = "frown"
"=(" = "frown"
":-O" = "gasp"
":O" = "gasp"
":-o" = "gasp"
":o" = "gasp"
":-D" = "grin1"
":D" = "grin1"
"=D" = "grin1"
":))" = "lough"
":-))" = "lough"
":-P" = "tongue"
":P" = "tongue"
":-p" = "tongue"
":p" = "tongue"
"=P" = "tongue"
";-)" = "wink1"
";)" = "wink1"
":3" = "curly_lips"
":-*" = "kiss"
":*" = "kiss"
":Z" = "sleepy"
":z" = "sleepy"
"8-)" = "glasses"
"8)" = "glasses"
"B-)" = "glasses"
"B)" = "glasses"
"8-|" = "sunglasses"
"8|" = "sunglasses"
"B-|" = "sunglasses"
"B|" = "sunglasses"
">:O" = "upset1"
">:-O" = "upset1"
">:o " = "upset1"
">:-o" = "upset1"
"o.O" = "confused"
"O.o" = "confused"
":?" = "confused"
"O:)" = "angel"
"O:-)" = "angel"
"o:-)" = "angel"
"o:-)" = "angel"
"3:)" = "devil"
"3:-)" = "devil"
":X" = "devil"
":x" = "devil"
":/" = "unsure1"
":-/" = "unsure1"
":\" = "unsure1"
":-\" = "unsure1"
":'(" = "cry"
"<3" = "heart"
"<(“)" = "penguin"
":poop:" = "poop1"
">:(" = "worried"
">:-(" = "worried"
":oops:" = "emabarassed"
":-$" = "emabarassed"
":$" = "emabarassed"
":0" = "0"
"::3" = "3"
":4" = "4"
":-h" = "wave"
":6" = "6"
":8" = "8"
":9" = "9"
":12" = "12"
":-?" = "thinking"
"(Y)" = "Thumbs_up"
"(y)" = "Thumbs_up"
":54" = "54"
":56" = "56"
":60" = "60"
":67" = "67"
":72" = "72"
"=((" = "broken_heart"
":88" = "88"
```

### Testing
Input examples, ref, *im_input02.txt*, 11-06-2013,

```
 this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that??
 
This is a distinguished text. It can be very easily recognized regardless the positions of words. However, there are certain situations.
 
averyverylongstringherehowisitgoinghoneyIthinkwearegoingtogetbustedwhatdoyouthinkIthinkprettysameDon'tyou?However,thingswillchange

averyverylongstringherehowisitgoinghoneyIthinkwearegoingtogetbustedwhatdoyouthinkIthinkprettysameDon'tyouHowever,thingswillchangetewstfurthertehstasweriotuwoperiuwpeoiru

:):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):) hi hello who is this???? how is going?

bug for input fixed:
:):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):)

test:):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):)test:):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):)tst:):)tst:):)tst

this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test.test:):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):)test:):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):):)tst:):)tst:):)tst Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that??:):):) this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that??

averyverylongstringherehowisitgoinghoneyIthinkwearegoingtogetbustedwhatdoyouthinkIthinkprettysameDon'tyouHowever,thingswillchangetewstfurthertehstasweriotuwoperiuwpeoiru:):):)

this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that:):):):):)testtestthis is a test. Nicolaus Copernicus!!!! hello who is that??:):):)

gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM


1. this is a test.

2. Atique!!!!

3. hello who is that??

4. this is a test.

5. Atique!!!!

6. who is doing wht?

7. this is a test.

8. Atique!!!!

9. hello who is that??

10. this is a test.

11. Atique!!!!

12. who is doing wht?


:):):):):):):):):):)
:(:(:(:(:(:(:(:(:(:(:(:(:(:(:(
:D:D:D:D:D:D:D:D:D:D:D:D:D:D:D:D:D:D:D:D:D
:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P:P
:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S:S
:O
:@
:-[
:-]
:|
:'(
:>
:3
:*
:V
:/
;)
>:(
>:O
8)
8|
O.o
```


Input examples, ref, *im_input02.txt*, 08-31-2013,

```
It formats text by expanding tabs into appropriate spaces, aligning text to the left, right, or center of the given rectangle, and breaking text into lines that fit within the given rectangle. The type of formatting is specified by nFormat. 

This member function uses the device context's selected font, text color, and background color to draw the text. Unless the DT_NOCLIP format is used, DrawText clips the text so that the text does not appear outside the given rectangle. All formatting is assumed to have multiple lines unless the DT_SINGLELINE format is given. 

If the selected font is too large for the specified rectangle, the DrawText member function does not attempt to substitute a smaller font.

If the DT_CALCRECT flag is specified, the rectangle specified by lpRect will be updated to reflect the width and height needed to draw the text.

If the TA_UPDATECP text-alignment flag has been set (see CDC::SetTextAlign), DrawText will display text starting at the current position, rather than at the left of the given rectangle. DrawText will not wrap text when the TA_UPDATECP flag has been set (that is, the DT_WORDBREAK flag will have no effect).

The text color may be set by CDC::SetTextColor.
```


Input examples, ref, *im_input03.txt*, 09-01-2013,

```
 this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that?? this is a test. Nicolaus Copernicus!!!! hello who is that??  :) :)
 ```