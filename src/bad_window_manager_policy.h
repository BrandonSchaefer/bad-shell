// -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
/*
 * Copyright (C) 2016 Brandon Schaefer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Brandon Schaefer <brandontschaefer@gmail.com>
 */

#include <miral/canonical_window_manager.h>
#include <miral/window_manager_tools.h>

namespace bad
{

class WindowManagerPolicy : public miral::CanonicalWindowManagerPolicy
{
public:
    using miral::CanonicalWindowManagerPolicy::CanonicalWindowManagerPolicy;

    bool handle_keyboard_event(MirKeyboardEvent const* kev) override;
    bool handle_pointer_event(MirPointerEvent const* pev) override;
    bool handle_touch_event(MirTouchEvent const* tev) override;

private:
    int current_scan_code{0};

};

}
