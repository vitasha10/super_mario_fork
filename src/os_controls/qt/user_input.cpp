#include "user_input.hpp"

#include <atomic>

using biv::os::UserInput;

namespace {
        std::atomic<bool> left_pressed{false};
        std::atomic<bool> right_pressed{false};
        std::atomic<bool> jump_pressed{false};
        std::atomic<bool> exit_pressed{false};
}

UserInput biv::os::get_user_input() {
        if (exit_pressed.load()) {
                return UserInput::EXIT;
        } else if (left_pressed.load()) {
                return UserInput::MAP_LEFT;
        } else if (right_pressed.load()) {
                return UserInput::MAP_RIGHT;
        } else if (jump_pressed.load()) {
                return UserInput::MARIO_JUMP;
        }

        return UserInput::NO_INPUT;
}

void biv::os::set_input_state(UserInput input, bool pressed) {
        switch (input) {
                case UserInput::MAP_LEFT:
                        left_pressed.store(pressed);
                        break;
                case UserInput::MAP_RIGHT:
                        right_pressed.store(pressed);
                        break;
                case UserInput::MARIO_JUMP:
                        jump_pressed.store(pressed);
                        break;
                case UserInput::EXIT:
                        exit_pressed.store(pressed);
                        break;
                case UserInput::NO_INPUT:
                        break;
        }
}
