# Cheatsheet for VIM mode:
There are 4 main modes:
- Normal: default mode for navigation and text manipulate command.
- Insert: typing. Replace: Overwrites existing characters/words as you type.
- Visual: selecting specific text areas to perform action, e.g copy, delete.
  - Visual_line:
  - Visual_bblock:
- Command: typing : , a specific command bbar opens at tthe top of editor 
At the bottom right corner, you will see the mode, and the row:column.


## 1. Enter INSERT/REPLACE mode from NORMAL mode:
  - i,a to insert/append at the cursor. I/A to insert/append at the begining of the line.
  - o/O append a new line after/before the current line
  - cc/C: (change) entire line/ from the current cursor to the end of line. 
  - r/R: replace 1 char (still in NORMAL)/ Replace until ESC to go back .
  - s/S: delete char/line (stay in INSERT mode). S is the same with cc.

## 2. NORMAL mode:
  ### 2.1 Move Vertically
  - Move cursor
    - `h,j,k,l`: move cursor left/down/up/right. `4j,4k` move cursor 4 lines down/up.
    - `H/M/L`: move cursor to the top/middle/bottom of screen
    - `gg/G`: go to the first line/last line of document. `5G` or `5gg`: go to line 5.
    - `Ctrl+F/B` move cursor forward, backward fullscreen.
    - `Ctrl+U/D` move cursor up/down half screen.
  - Scrolling (leave cursor in place):
    - z+(t/z/b): scroll to top/middle/bottom.
    - Ctrl+E/Y: scroll 1 line up/down.

  ### 2.2 Move Horizontally
  - Move within line:
    - `0/^/$` jump to the start/first char/end of line (still in Normal mode, different with I/A)
    - `f{char}/ t{char}` jump to the next {char}/before the next {char}.
    - `F{char},T{char}` jump backward.
    - `;/,` repeat the motion of f,t,T,F forward/backward.
  - Move between words:
    - `w,e`: move to the beginning/end of the next word. `b` go back.
    - `W/E`: move to the beggning/end of composed word (word with -,/_ in between). B go backward.
    - `%` move cursor to the matching character for {asdfs}, [dfsdfsd],(fdsfds)
    - `u/Ctrl+r`: undo/redo. `U` Undo line(only for the current line). 
  - Move between brackets:
    - `[ / ] + {Bracket type: {/}, (),[]},` go to previous/next unmatch brackets.
  - Move between sentence/paragraph:
    - ( / ) move between sentences.
    - { / } move between paragraphs (seperate by empty line)
  - Move between Search:
    - */#: search for the next/previous word in front or under the cursor.
    - /,? + pattern: search forward/backward for a pattern.
    - n/N: (next) repeat last search in the forward/backward in the same direction.
    - Ctrl +o/i: move forward/backward previous cursor.
  
  ### 2.3 Concept that used in the 2.4 Edit sesstion:
  - {motion}: is the VIM command that moves the cursor, as shown in 2.1 and 2.2. 
  - {Text Obbject}: is a combination of i/a (inside/arround) and Open-Close pair characters ("",(),{},[],< >)
    - i( or i): a block inside the ( ).
    - a( or a): a block inside and include ( ).
    - iw/aw: a word inside/include the white space.
    - it/at: a block inside/include the xml/html tags.
    - ip/ap: a paragraph inside/include the whitespace.

  ### 2.4 Edit:
  - Deletion:
    - d{motion} (dw,de,db,dW,dE,dB): delete(cut) motion (word) under the cursor and copy to reggister. d2W delete 2 words.
    - c{motion}: same with d{motion} but change into INSERT mode.
    - x: delete the current char and copy to register.
    - dd/D: Delete (cut) the line/from the cursor to the end of line. 2dd: cut 2 line.
    
  - Copy/Paste:
    - y{motion}: copy motion.
    - yy/Y: copy(yank) current line/from cursor to end of line. 2yy: copy 2 lines
    - p/P: paste after/before cursor.

  - Change Lower/UPPER case:
    - ~: switch case for char under the cursor.
    - ~{motion} (~w,~W,~b,~B,~e,~E): change case for the {motion}
    - gu{motion}, gU{motion}: change lower/UPPER case for the {motion}
    - guu/gUU: change lower/UPPER case for the whole line.

  - . : repeat last change.
  - d{text_object} (di", da{}, diw) delete object at the current cursor surrounded by the parathesis. Same for `c,y,v`.

  ### 2.5 Fold text:
  - zc/zo: fold/unfold the content of the function
  - zM/zO: fold/unfold all.
  - zj/jk: move down/up to next fold.
  - zd/zE: delete current fold/all folds.
  
## 3. VISUAL (SELECT) mode:
  - V: to select line, then 4j/4k to select 4 next/4 previous lines
  - v: select char, then 4w/4b to select 4 next/ 4 previous words.
  - v{text_object} (vi",vi{, vi[, etc): select everything inside the "",{}, ().
  - gl/gL: (look like)add a cursor selecting the next/prev of the current word (at the cursor).
  - gI/gA: add the cursor at the first char/the end of every line of the current selection (and enter the INSERT mode).
  - ga: add a visual selection of every copy of the current word

## 4. Command mode:
  - Jump:
    - :<number> jump to line <number>
    - :$: jump to end of gile
    - :/foo and :?/foo jump to the next/prev line matching foo.
  - Explore command:
  - :t: open terminal. Cmd+J: open the bottom pannel
    - :E: open file explore.

## 5. Zed features:
  - Language server (like Python, C++)
    - gd/gD/gI/gy: go to definition/declaration/Implementation/type definition.
    - gs/gS: Find symbol (function name) in the current file/entire project.
    - gA: go to ALL references to the current word
    - g[, g]: go to nex/prev diagonotis error.
    - g h: show inline error.
    - g .: open code action menu.
    - cd: change definition (the name of the function) in all place
  - Tree Sitter:
    - [ m/ ]m: go to next/prev method.
    - [ M/ ]M: go the next/prev end of method
      
    - g c: add coment

  - Multicursors:
    - gl/gL: select all words
