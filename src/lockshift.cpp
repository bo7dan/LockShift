#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <atomic>
#include <string>

// --- Глобальні змінні ---
// Використовуємо atomic для безпечного доступу з різних потоків
std::atomic<bool> is_blocked = true; 

HHOOK hHook_Keyboard = NULL;
HHOOK hHook_Mouse = NULL;

const DWORD VK_TILDE = 0xC0; // VK_OEM_3 (~)

// --- Прототипи функцій-обробників ---
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam);

// --- 1. Обробник клавіатури ---
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode < 0) {
        return CallNextHookEx(hHook_Keyboard, nCode, wParam, lParam);
    }

    if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        KBDLLHOOKSTRUCT* pkb = (KBDLLHOOKSTRUCT*)lParam;
        
        // Клавіша '~'
        if (pkb->vkCode == VK_TILDE) {
            is_blocked = !is_blocked;
            std::cout << (is_blocked ? "Blocked" : "Unlocked") << std::endl;
            // Передаємо далі, щоб дозволити самій клавіші працювати
            return CallNextHookEx(hHook_Keyboard, nCode, wParam, lParam);
        }

        // Блокуємо, якщо is_blocked == true
        if (is_blocked.load()) {
            return 1; // Повернення 1 блокує подію
        }
    }

    // Передаємо інші події далі
    return CallNextHookEx(hHook_Keyboard, nCode, wParam, lParam);
}

// --- 2. Обробник миші ---
LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode < 0) {
        return CallNextHookEx(hHook_Mouse, nCode, wParam, lParam);
    }

    // Блокування всіх подій миші
    if (is_blocked.load()) {
        return 1; // Повернення 1 блокує подію
    }

    return CallNextHookEx(hHook_Mouse, nCode, wParam, lParam);
}

// --- 3. Встановлення хуків ---
bool InstallHooks() {
    std::cout << "Attempt to install hooks..." << std::endl;

    HINSTANCE hInstance = GetModuleHandle(NULL);

    hHook_Keyboard = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInstance, 0);
    if (!hHook_Keyboard) {
        std::cerr << "Error: Failed to set keyboard hook. Administrator rights required." << std::endl;
        return false;
    }

    hHook_Mouse = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, hInstance, 0);
    if (!hHook_Mouse) {
        std::cerr << "Error: Failed to set mouse hook. Removing keyboard hook..." << std::endl;
        UnhookWindowsHookEx(hHook_Keyboard);
        return false;
    }

    std::cout << "Hooks installed. Keyboard and mouse locked.." << std::endl;
    std::cout << "Press ~/` to unlock/lock (English layout)." << std::endl;
    return true;
}

// --- 4. Видалення хуків ---
void UninstallHooks() {
    if (hHook_Keyboard) {
        UnhookWindowsHookEx(hHook_Keyboard);
        hHook_Keyboard = NULL;
    }
    if (hHook_Mouse) {
        UnhookWindowsHookEx(hHook_Mouse);
        hHook_Mouse = NULL;
    }
}

// --- 5. Цикл повідомлень ---
void MessageLoop() {
    MSG msg;
    // Це забезпечує роботу хуків
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// --- 6. Основна функція ---
int main() {
    // Встановлення хуків
    if (!InstallHooks()) {
        return 1;
    }

    // Запуск циклу, який чекає на події
    MessageLoop();

    // Видалення хуків при завершенні програми
    UninstallHooks();
    std::cout << "Hooks removed. Exit........." << std::endl;

    return 0;
}