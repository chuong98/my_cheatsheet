# VIM Cheatsheet

## Introduction

VIM has 4 main modes:
- **Insert**: Typing mode. Replace mode overwrites existing characters/words.
- **Visual**: Select specific text areas to perform actions (copy, delete, etc.)
- **Normal**: Default mode for navigation and text manipulation. All operators happen here.
- **Command**: Type `:` to open a command bar at the top of the editor.

**UI Info**: Mode and row:column position shown at bottom right. Relative line numbers toggle between Insert and Normal modes.

**VIM Syntax = Verb + Noun** (e.g., `d2w` = delete 2 words)
- **Verb**: Operators (`d`=delete, `v`=visual select, `y`=copy)
- **Noun**: Motion or Text Object
  - Motion: `h,j,k,l` (move), `w` (word), `b` (back)
  - Text Object: `iw` (inner word), `aw` (around word)
- **Repeat**: `,` or `;` to repeat motion forward/backward, `.` to repeat action

---

## 1. Mode Switching

| Command | Description |
|---------|-------------|
| `ESC` | Go to Normal mode |
| `v/V` | Go to Visual mode (select char/line) |
| `i/a` | Insert/append at cursor |
| `I/A` | Insert/append at beginning/end of line |
| `o/O` | Insert new line after/before current line |

## 2. Operators

### Immediate Actions (no motion needed)

| Command | Description |
|---------|-------------|
| `x/X` | Delete/backspace character |
| `s` | Substitute (delete char, enter Insert mode) |
| `r/R` | Replace 1 char / replace mode until ESC |
| `p/P` | Paste after/before cursor |
| `u/Ctrl+r` | Undo/Redo |
| `U` | Undo all changes to current line |
| `J` | Join current line with line below |
| `~` | Toggle case (upper/lower) of character |

### Motion/Text Object Operators (wait for noun)

| Command | Description |
|---------|-------------|
| `v` | Select motion or text objects (visual) |
| `d/c/y` | Delete/change/copy + motion/text object |
| `gu/gU/g~` | Lowercase/uppercase/toggle case + motion/text object |
| `</>/=` | Indent left/right/auto-indent + motion/text object |
| `gc` | Comment/uncomment code + motion/text object |
| `cx` | Swap lines (type on line 1, then `.` on target line) |

**Note**:
- Double operators work on whole line**: `dd`, `cc`, `yy`, `<<`, `>>`, `==`, `guu`, `gUU`, `gcc`
- Mode change is special type of operators, it enter the mode of the selection motion. You can do . to repeat what you edit in the Insert mode.

## 3. Motion

**Motion defines cursor movement when use alone or text range when combined with operators.**

### Character/Word/Line Level

| Command | Description |
|---------|-------------|
| `{num}h/j/k/l` | Move {num} char left/down/up/right |
| `{num}w/e/b/ge` | Move {num} words (begin/end/back begin/back end) |
| `0/^/$/ g_` | Move to begin/first char/end/last non-blank of line |
| `gg/G/{num}G` | Go to first/last/line {num} |
| `H/M/L` | Jump to top/middle/bottom of visible screen |

### Search-Based Motion

| Command | Description |
|---------|-------------|
| `*/#` | Search forward/backward for word under cursor |
| `f{c}/F{c}` | Find char {c} forward/backward on line |
| `t{c}/T{c}` | Find until char {c} forward/backward |
| `;/,` | Repeat last f/F/t/T motion forward/backward |
| `/{pat}/?{pat}` | Search forward/backward for pattern |
| `n/N` | Go to next/previous search result |

### Paragraph/Bracket Motion

| Command | Description |
|---------|-------------|
| `[[/]]` | Jump backward/forward to next empty line/block |
| `{/}` | Jump backward/forward to empty line |
| `%` | Jump to matching bracket: `()`, `[]`, `{}` |

## 4. Text Objects

**Text objects work with operators (d, c, y) or in Visual mode.**

**Format**: `{modifier}{target}` where modifier is `i` (inner), `a` (around), `s` (surround)

| Command | Description |
|---------|-------------|
| `iw/aw` | Inner/around word |
| `is/as` | Inner/around sentence |
| `it/at` | Inner/around tag |
| `ip/ap` | Inner/around paragraph |
| `i(/)` / `a(/)` | Inside/around parentheses |
| `i{/}` / `a{/}` | Inside/around braces |
| `i[/]` / `a[/]` | Inside/around brackets |
| `i</>`  / `a</>` | Inside/around angle brackets |
| `i"/'` / `a"/'` | Inside/around double/single quotes |

### Text Object Examples

| Command | Description |
|---------|-------------|
| `di("` | Delete inside parens |
| `ya"` |  Copy around quotes |
| `cs([` | Change surrounding `(` to `[` |
| `ys{motion}*` | Surround motion/selection with `*` |
| `ci(` | Change (delete & insert) inside parentheses |

## 5. Normal Mode

### 5.1 Move Vertically

| Command | Description |
|---------|-------------|
| `Ctrl+f/b` | Move cursor forward/backward full screen |
| `Ctrl+u/d` | Move cursor up/down half screen |
| `Ctrl+o/i` | Move to previous/next cursor position (history) |

### 5.2 Scrolling (leave cursor in place)

| Command | Description |
|---------|-------------|
| `z t/z/b` | Scroll to top/middle/bottom |
| `Ctrl+e/y` | Scroll up/down 1 line |

### 5.3 Folding Text

| Command | Description |
|---------|-------------|
| `zc/zo` | Fold/unfold content |
| `zM/zO` | Fold/unfold all |
| `zj/zk` | Move down/up to next fold |
| `zd/zE` | Delete current/all folds |

### 5.4 Search Text

| Command | Description |
|---------|-------------|
| `*/#` | Search forward/backward for word under cursor |
| `//? ` | Search forward/backward for pattern |
| `g/` | Search pattern for whole project |
| `gs/gS` | Search symbols in current file/entire project |
| `n/N` | Go to next/previous search result |

### 5.5 Bookmarks

| Command | Description |
|---------|-------------|
| `m{letter}` | Bookmark current line (e.g., `ma`) |
| `'{letter}` | Jump to bookmarked line (e.g., `'a`) |
| `` `{letter} `` | Jump to exact bookmark position (e.g., `` `a ``) |
| `gi/go` | Jump to previous/next cursor position (history) |

## 6. Visual (Select) Mode

**Used for multi-cursor editing or multi-line operations.**

| Command | Description |
|---------|-------------|
| `ga` | Add cursor at every occurrency of current word |
| `gl/gL` | Add cursor at next/previous occurrency with current word |
| `gI/gA` | Add cursor at first/end char of every line in selection |

## 7. Command Mode

**Type `:` to open command bar at top of editor**

| Command | Description |
|---------|-------------|
| `:t` | Open terminal |
| `Cmd+J` | Open/close bottom panel |
| `:E` | Open file explorer |

## 8. Zed Features

**Editor-specific commands**

### Code Navigation

| Command | Description |
|---------|-------------|
| `gd/gD/gI/gy` | Go to definition/declaration/implementation/type |
| `Ctrl+w gd/gD` | Go to definition/declaration in split view |
| `Ctrl+i/o` | Jump to next/previous position in history |

### Diagnostics & Code Actions

| Command | Description |
|---------|-------------|
| `g[/g]` | Go to next/previous diagnostic error |
| `gh` | Show inline error |
| `g.` | Open code action menu |
| `cd` | Rename definition (changes name in all places) |

### Method & Comment Navigation

| Command | Description |
|---------|-------------|
| `[m/]m` | Go to next/previous method |
| `[M/]M` | Go to next/previous end of method |
| `[//]/` | Go to next/previous comment |

### Extended Text Objects (Zed-specific)

**Combine with i/a modifiers (e.g., `dic` = delete inside class)**

| Command | Description |
|---------|-------------|
| `c` | Class or definition |
| `f` | Function |
| `a` | Argument |
| `I` | Indent level |
