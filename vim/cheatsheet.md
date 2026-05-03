# Cheatsheet for VIM mode:

## 1. INTRODUCTION
There are 4 main modes:
- Insert: typing. Replace: Overwrites existing characters/words as you type.
- Visual: selecting specific text areas to perform action, e.g copy, delete.
  - Visual_line:
  - Visual_block:
- Normal: default mode for navigation and text manipulate command. All operators happen in here.
- Command: typing : , a specific command bbar opens at tthe top of editor 
At the bottom right corner, you will see the mode, and the row:column.
If you toggle the relative line in the Insert mode, it will show the absolute line, while in the normal mode, it will show the relative line.
----------------------------------------------------------------------------
Syntax of VIM = Verb + Noun, e.g: delete word = d w:              
- Verb= Operators (d= delete, v = visual select, y= copy).
- Noun: 
  - Motion: (h,j,kl, w= move word, b: move back)
  - Text Object: iw= in word, aw=around word, sw=surround word.
- Repeat: (, or ; to repeat motion forward,backward, .: to repeat action.)
----------------------------------------------------------------------------

## 1. MODE switching
	- ESC: go to normal mode.
	- v/V: go to visual mode for selecting char/line.
  - i,a: insert/append at the cursor. 
  - I/A: insert/append at the begining of the line.
  - o/O: insert a new line after/before the current line

## 2. Operators: 
**Actions happen immediately without waiting. Can always combine with {num} in front.**
- x/X: delete/backspace char
- s/S: substitute (delete the char and enter the INSERT mode)/delete entire line.
- r/R: replace 1 char/ replace until you ESC.
- p/P: paste/ Paste before
- u/Ctrl+r: Undo/ Redo
- U: undo every thing you make to the current line.
- J: join the current line and the below line.
- ~: Toggle case uppper/lower of char
- dd or D: delete to the end.
- cc or C: change from the cursor to the end (and enter the INSERT mode). cc is the same with S.
- yy or Y: Copy the whole line.
- >>, <<: Indent the current line.
- ==: fix the indentation of the current line.
- guu/gUU: change lower/UPPER case for the whole line.

**An operator is any command that waits for a NOUN (motion or text object) to complete the action.**
- d: delete + (WHAT).
- v{motion}: select motion or text_objects.
- c: change (delete and enter the INSERT mode)+ (WHAT)
- y: copy + (WHAT)
- gu,gU,g~: lower case/ upper case/ toggle case.
- <, >, =: indent left/right/ auto indent+ (WHAT). Useful for code block indentation.
- gc: comment the code.
- when double the operators, it works for the.
- v{motion}: select motion or text_objects. whole line. E.g dd,cc,yy,<<,>>,==,guu,gUU, gcc
E.g: =i{: fix the indent inside the code block { }.

**Mode change is special type of operators, it enter the mode of the selection motion. You can do . to repeat mode change**
Examples:
- i: change to insert mode, type something, then . it will repeat what you typed at the cursor.
- V: selection line.
- v{motion}: select motion or text_objects.

## 3. Motion:
**Motion defines the range of text or movement. When use alone, they move the cursor. When combine with Operators, they are the range of text to apply.**
- **Alone motion**
	- {num}h,j,k,l (char level): move {num} char (left/down/up/right).
	- {num}w/e/b/ge (word level): move {num} word (next begin of word/ next end of word/ go back begin word/ go back end of word).
	- 0/^/$/g_ (current line level): move to (begining of line/ first char of line/ end of line/ last non-blank char of line).
	- gg/G/{num}G: (go to line) first line/last line/go to line {num}.
	- */#: search forward/backward for the word under cursor.
	- [[ or {/ ]] or }: jump forward/backward to the next empty line (paragraph, block).
	- H/M/L (global leave): Jump to (High/Midle/Low) of the visible screen.
- **Motion with pattern**.
	- fc/Fc: find char c forward/backward.
	- tf/Tc: find untill char c forward/backward.
	- ,/: repeat the motion for fc/Fc,tc/Tc.
	- /{pattern}: search forward pattern. Eg d/hello: mean delete forward until the word hello.
	- ?{pattern}: searach backward pattern. eg: d?777: delete backward until the word 777.
	- %: jump to the matching bracket (),[],{}.
	- n/N: next/previous search result.

## 4. Text Objects:
**Text objects are used only with operators: d,c,y or in visual mode, regardless of where the cursors is inside them**
- i/a/s: Inner/Around/Surround.
- w/s/t/p: word, sentence, tag, paragraph.
- brackets: (,{,[,<, or >,],},).
- quotes: ",',
Examples:
- di(: delete anything inside the bracket.
- ya": copy anything in "..." and include the "".
- cs([: change the surround ( current text) to [current text].
- ysiw*: add surround the current word with *.
- yss": add surround the sentene with ". But it recommend to add i/a, like ysis" or ysa".
- you can use v{motion}/{text_objects}, then apply action, but it is faster than just use the action directly. The good default is `ci(` just to change whatever inside the bracklet.

## 5. NORMAL mode:
  ### 5.1 Move Vertically
  - Move cursor
    - `Ctrl+F/B` move cursor forward, backward fullscreen.
    - `Ctrl+U/D` move cursor up/down half screen.
    - `Ctrl+o/i`: move forward/backward previous cursor.
  - Scrolling (leave cursor in place):
    - z+(t/z/b): scroll to top/middle/bottom.
    - Ctrl+E/Y: scroll 1 line up/down.

  ### 5.2 Fold text:
  - zc/zo: fold/unfold the content of the function
  - zM/zO: fold/unfold all.
  - zj/jk: move down/up to next fold.
  - zd/zE: delete current fold/all folds.
  
## 6. VISUAL (SELECT) mode:
Visual selection is a type of operator, but it does not edit.
  - gl/gL: (look like)add a cursor selecting the next/prev of the current word (at the cursor).
  - gI/gA: add the cursor at the first char/the end of every line of the current selection (and enter the INSERT mode).
  - ga: add a visual selection of every copy of the current word

## 7. Command mode:
  - Explore command:
  - :t: open terminal. Cmd+J: open the bottom pannel
  - :E: open file explore.

## 8. Zed features:
  **Motion**
  - gd/gD/gI/gy: go to definition/declaration/Implementation/type definition. Good when combine with ctrl+i/o: to return previous position.
  - <ctrl+w> g d/g D: go to the definition in the split.
  - gA: go to ALL references to the current word
  - g[, g]: go to nex/prev diagonotis error.
  - gs/gS: Find symbol (function name) in the current file/entire project.
  - g h: show inline error.
  - g .: open code action menu.
  - cd: change definition (the name of the function) in all place
  - [ m, ]m: go to next/prev method.
  - [ M, ]M: go to next/prev end of method
  - [/, ]/: go to next/prev comment.
  **Text Objects: still combine with i/a infront but with extra keywords**
 	- c: class, definition. Eg. ia: inside a class
  - f: function. Eg. daf: delete around the function.
  - a: argument. Eg. aa: an argument of function,
  - I: Indent. Eg: diI: delete all of the current indent.
  **Multi cursors selection**
  - gl/gL: add a cursor selecting the next copy of the current word forward/backward.
  - gI/gA: add a cursor at the first char/end of every line in the current visual selection.
