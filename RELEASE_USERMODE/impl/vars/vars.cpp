#ifndef VARS_CPP
#define VARS_CPP

#include <impl/includes.hpp>

void vars_interface::c_vars::load( )
{
    this->hotbar.position = ImVec2( render->game_width / 2.00, 200 );
    this->misc.indicator_position = ImVec2( render->game_width / 2.00, render->game_height / 2.00 + 30 );

    this->misc.aspect_ratio = render->game_width / render->game_height;

    this->ui.framerate = { .state = true };
    this->ui.menu = { .state = true, .keybind = {.key = VK_INSERT, .mode = c_keybind_mode::hold } };
}

#endif // !VARS_CPP