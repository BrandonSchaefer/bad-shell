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

#include <miral/window_manager_tools.h>
#include <linux/input.h>

#include "bad_window_manager_policy.h"

namespace bad
{
namespace
{
int const shift_states =
    mir_input_event_modifier_alt |
    mir_input_event_modifier_shift |
    mir_input_event_modifier_sym |
    mir_input_event_modifier_ctrl |
    mir_input_event_modifier_meta;
}

bool WindowManagerPolicy::handle_keyboard_event(MirKeyboardEvent const* kev)
{
    auto action       = mir_keyboard_event_action(kev);
    auto shift_state  = mir_keyboard_event_modifiers(kev) & shift_states;
    auto scan_code    = mir_keyboard_event_scan_code(kev);
    current_scan_code = scan_code;

    if (action == mir_keyboard_action_down &&
        shift_state == mir_input_event_modifier_alt)
    {
        switch (scan_code)
        {
            case KEY_F4:
                tools.ask_client_to_close(tools.active_window());
                return true;
            case KEY_TAB:
                tools.focus_next_application();
                return true;
            case KEY_GRAVE:
                tools.focus_next_within_application();
                return true;
        }
    }
    else if (action == mir_keyboard_action_up)
    {
        current_scan_code = 0;
    }

    return false;
}

bool WindowManagerPolicy::handle_pointer_event(MirPointerEvent const* pev)
{
    if (tools.active_window())
    {
        miral::Point const cursor{
            mir_pointer_event_axis_value(pev, mir_pointer_axis_x),
            mir_pointer_event_axis_value(pev, mir_pointer_axis_y)
        };

        miral::Point const rel_cursor{
            mir_pointer_event_axis_value(pev, mir_pointer_axis_relative_x),
            mir_pointer_event_axis_value(pev, mir_pointer_axis_relative_y)
        };

        auto window = tools.active_window();
        auto& info  = tools.info_for(window);

        miral::WindowSpecification mod;
        mod.top_left() = {cursor.x, cursor.y};
        mod.size()     = window.size();
        if (current_scan_code == KEY_SPACE)
        {
            mod.top_left() = {window.top_left().x, window.top_left().y};
            mod.size()     = {window.size().width.as_int() + rel_cursor.x.as_int(),
                              window.size().height.as_int() + rel_cursor.y.as_int()};
        }
        tools.modify_window(info, mod);
    }

    return false;
}

bool WindowManagerPolicy::handle_touch_event(MirTouchEvent const* tev)
{
    return false;
}

}
