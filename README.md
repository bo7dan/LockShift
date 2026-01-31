[![License: GPL v3](https://img.shields.io)](https://www.gnu.org)

# LockShift – Keyboard & Mouse Lock Utility

A small Windows utility that blocks all keyboard and mouse input until the user toggles the lock with the `~` (tilde) key.  
The program uses low‑level hooks (`WH_KEYBOARD_LL`, `WH_MOUSE_LL`) and an `std::atomic<bool>` flag to safely enable/disable the block from any thread.

---  

### 🚀 Features
- **Global input lock** – prevents any keypresses or mouse actions while active.  
- **Toggle with `~`** – press the tilde/back‑quote key (English layout) to unlock/lock again.  
- **Thread‑safe flag** – uses `std::atomic<bool>` for lock state.  
- **Console feedback** – prints “Blocked” or “Unlocked” each time the state changes.  

---  

### 📋 Prerequisites
| Requirement | Version / Note |
| :--- | :--- |
| **Windows OS** | 10 or later (64‑bit recommended) |
| **Visual Studio** | 2022 or newer, with C++ Desktop Development workload |
| **Windows SDK** | Included with Visual Studio |

---  

### 🛠 Build Instructions
1. Create a new Win32 Console project in Visual Studio.  
2. Add the source file (`lockshift.cpp`) containing the code.  
3. Ensure the project links against `User32.lib` (default for console apps).  
4. Set C++ Language Standard to **C++20** or later.  
5. Build the solution (`Ctrl+Shift+B`).  

The resulting executable (`lockshift.exe`) can be run directly from a console.

---  

### ⌨️ Usage
```text
> lockshift.exe
Attempt to install hooks...
Hooks installed. Keyboard and mouse locked.
Press ~/` to unlock/lock (English layout).
```
## ⚖️ License

This project is licensed under the **GNU General Public License v3.0**.

- You are free to copy, modify, and distribute this software.
- Any modifications or derivative works **must also be licensed under GPLv3**.
- For more details, see the [LICENSE](LICENSE) file in this repository.

---
*This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY.*


