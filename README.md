## lockshift – Keyboard & Mouse Lock Utility

A small Windows utility that blocks all keyboard and mouse input until the user toggles the lock with the `~` (tilde) key.  
The program uses low‑level hooks (`WH_KEYBOARD_LL`, `WH_MOUSE_LL`) and an `std::atomic<bool>` flag to safely enable/disable the block from any thread.

---  

### Features
- Global input lock – prevents any keypresses or mouse actions while active.  
- Toggle with `~` – press the tilde/back‑quote key (English layout) to unlock/lock again.  
- Thread‑safe flag – uses `std::atomic<bool>` for lock state.  
- Console feedback – prints “Blocked” or “Unlocked” each time the state changes.  

---  

### Prerequisites
 Requirement | Version / Note 

 Windows OS  10 or later (64‑bit recommended) 
 Visual Studio  2022 or newer, with C++ Desktop Development workload 
 Windows SDK | Included with Visual Studio 

---  

### Build Instructions
1. Create a new Win32 Console project in Visual Studio.  
2. Add the source file (`lockshift.cpp`) containing the code above.  
3. Ensure the project links against `User32.lib` (default for console apps).  
4. Set C++ Language Standard to C++20 or later.  
5. Build the solution (`Ctrl+Shift+B`).  

The resulting executable (`lockshift.exe`) can be run directly from a console.

---  

### Usage
```text
> lockshift.exe
Attempt to install hooks...
Hooks installed. Keyboard and mouse locked..
Press ~/` to unlock/lock (English layout).
```

- While locked, all keyboard and mouse input is ignored.  
- Press the tilde (`~`) key to toggle the lock. The console will display `Blocked` or `Unlocked`.  
- Close the console window or press "Ctrl+C" to terminate; the hooks are automatically removed.

---  

### Safety & Permissions
- The program requires administrator rights to install low‑level hooks.  
- If the hooks cannot be set, an error message is printed and the program exits.  

---  

### License
This code is provided "as‑is: under the MIT License. Feel free to modify, redistribute, or integrate it into other projects.  
<img width="677" height="1173" alt="image" src="https://github.com/user-attachments/assets/8b71f23d-7552-4938-8a69-4d76a85e4401" />
