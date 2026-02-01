/*
 * LockShift
 * Copyright (C) 2026  bo7dan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <iostream>
#include <atomic>

std::atomic<bool> is_blocked(true);

Display* dpy;
Window root;
KeyCode grave_key;

void block_input() {
    XGrabKeyboard(dpy, root, False,
                  GrabModeAsync, GrabModeAsync, CurrentTime);
    XGrabPointer(dpy, root, True,
                 ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
                 GrabModeAsync, GrabModeAsync,
                 None, None, CurrentTime);
    XFlush(dpy);
}

void unblock_input() {
    XUngrabKeyboard(dpy, CurrentTime);
    XUngrabPointer(dpy, CurrentTime);
    XFlush(dpy);
}

int main() {
    dpy = XOpenDisplay(nullptr);
    if (!dpy) {
        std::cerr << "X11 not available\n";
        return 1;
    }

    root = DefaultRootWindow(dpy);
    grave_key = XKeysymToKeycode(dpy, XK_grave);

    // Passive grab for `~`
    XGrabKey(dpy, grave_key, AnyModifier, root,
             True, GrabModeAsync, GrabModeAsync);

    block_input();

    std::cout << "Blocked. Press `~` to toggle\n";

    XEvent ev;
    while (true) {
        XNextEvent(dpy, &ev);

        if (ev.type == KeyPress && ev.xkey.keycode == grave_key) {
            is_blocked = !is_blocked;

            if (is_blocked) {
                block_input();
                std::cout << "Blocked\n";
            } else {
                unblock_input();
                std::cout << "Unlocked\n";
            }
        }
    }
}
