#pragma once

#include <SDL2/SDL.h>

namespace Combo {

    
    class InputManager
    {
        public:

        private:
        

    };
    
    
    
    enum class KeyboardKey
    {
        KEY_UNKNOWN      = SDLK_UNKNOWN, //0
        KEY_RETURN       = SDLK_RETURN, //'\r'
        KEY_ESCAPE       = SDLK_ESCAPE, //'\033'
        KEY_BACKSPACE    = SDLK_BACKSPACE, //'\b'
        KEY_TAB          = SDLK_TAB, //'\t'
        KEY_SPACE        = SDLK_SPACE, //' '
        KEY_EXCLAIM      = SDLK_EXCLAIM, //'!'
        KEY_QUOTEDBL     = SDLK_QUOTEDBL, //'"'
        KEY_HASH         = SDLK_HASH, //'#'
        KEY_PERCENT      = SDLK_PERCENT, //'%'
        KEY_DOLLAR       = SDLK_DOLLAR, //'$'
        KEY_AMPERSAND    = SDLK_AMPERSAND, //'&'
        KEY_QUOTE        = SDLK_QUOTE, //'\''
        KEY_LEFTPAREN    = SDLK_LEFTPAREN, //'('
        KEY_RIGHTPAREN   = SDLK_RIGHTPAREN, //')'
        KEY_ASTERISK     = SDLK_ASTERISK, //'*'
        KEY_PLUS         = SDLK_PLUS, //'+'
        KEY_COMMA        = SDLK_COMMA, //','
        KEY_MINUS        = SDLK_MINUS, //'-'
        KEY_PERIOD       = SDLK_PERIOD, //'.'
        KEY_SLASH        = SDLK_SLASH, //'/'
        KEY_0            = SDLK_0, //'0'
        KEY_1            = SDLK_1, //'1'
        KEY_2            = SDLK_2, //'2'
        KEY_3            = SDLK_3, //'3'
        KEY_4            = SDLK_4, //'4'
        KEY_5            = SDLK_5, //'5'
        KEY_6            = SDLK_6, //'6'
        KEY_7            = SDLK_7, //'7'
        KEY_8            = SDLK_8, //'8'
        KEY_9            = SDLK_9, //'9'
        KEY_COLON        = SDLK_COLON, //':'
        KEY_SEMICOLON    = SDLK_SEMICOLON, //';'
        KEY_LESS         = SDLK_LESS, //'<'
        KEY_EQUALS       = SDLK_EQUALS, //'='
        KEY_GREATER      = SDLK_GREATER, //'>'
        KEY_QUESTION     = SDLK_QUESTION, //'?'
        KEY_AT           = SDLK_AT, //'@'
        KEY_LEFTBRACKET  = SDLK_LEFTBRACKET, //'['
        KEY_BACKSLASH    = SDLK_BACKSLASH, //'\\'
        KEY_RIGHTBRACKET = SDLK_RIGHTBRACKET, //']'
        KEY_CARET        = SDLK_CARET, //'^'
        KEY_UNDERSCORE   = SDLK_UNDERSCORE, //'_'
        KEY_BACKQUOTE    = SDLK_BACKQUOTE, //'`'
        KEY_A            = SDLK_a, //'a'
        KEY_B            = SDLK_b, //'b'
        KEY_C            = SDLK_c, //'c'
        KEY_D            = SDLK_d, //'d'
        KEY_E            = SDLK_e, //'e'
        KEY_F            = SDLK_f, //'f'
        KEY_G            = SDLK_g, //'g'
        KEY_H            = SDLK_h, //'h'
        KEY_I            = SDLK_i, //'i'
        KEY_J            = SDLK_j, //'j'
        KEY_K            = SDLK_k, //'k'
        KEY_L            = SDLK_l, //'l'
        KEY_M            = SDLK_m, //'m'
        KEY_N            = SDLK_n, //'n'
        KEY_O            = SDLK_o, //'o'
        KEY_P            = SDLK_p, //'p'
        KEY_Q            = SDLK_q, //'q'
        KEY_R            = SDLK_r, //'r'
        KEY_S            = SDLK_s, //'s'
        KEY_T            = SDLK_t, //'t'
        KEY_U            = SDLK_u, //'u'
        KEY_V            = SDLK_v, //'v'
        KEY_W            = SDLK_w, //'w'
        KEY_X            = SDLK_x, //'x'
        KEY_Y            = SDLK_y, //'y'
        KEY_Z            = SDLK_z, //'z'
        KEY_CAPSLOCK     = SDLK_CAPSLOCK,
        KEY_F1           = SDLK_F1, 
        KEY_F2           = SDLK_F2, 
        KEY_F3           = SDLK_F3, 
        KEY_F4           = SDLK_F4, 
        KEY_F5           = SDLK_F5, 
        KEY_F6           = SDLK_F6, 
        KEY_F7           = SDLK_F7, 
        KEY_F8           = SDLK_F8, 
        KEY_F9           = SDLK_F9, 
        KEY_F10          = SDLK_F10,
        KEY_F11          = SDLK_F11,
        KEY_F12          = SDLK_F12,
        KEY_PRINTSCREEN  = SDLK_PRINTSCREEN,
        KEY_SCROLLLOCK   = SDLK_SCROLLLOCK,
        KEY_PAUSE        = SDLK_PAUSE,
        KEY_INSERT       = SDLK_INSERT,
        KEY_HOME         = SDLK_HOME, 
        KEY_PAGEUP       = SDLK_PAGEUP,
        KEY_DELETE       = SDLK_DELETE,
        KEY_END          = SDLK_END,
        KEY_PAGEDOWN     = SDLK_PAGEDOWN, 
        KEY_RIGHT        = SDLK_RIGHT,
        KEY_LEFT         = SDLK_LEFT,
        KEY_DOWN         = SDLK_DOWN,
        KEY_UP           = SDLK_UP,
        KEY_NUMLOCKCLEAR = SDLK_NUMLOCKCLEAR,
        KEY_KP_DIVIDE    = SDLK_KP_DIVIDE, 
        KEY_KP_MULTIPLY  = SDLK_KP_MULTIPLY, 
        KEY_KP_MINUS     = SDLK_KP_MINUS,
        KEY_KP_PLUS      = SDLK_KP_PLUS, 
        KEY_KP_ENTER     = SDLK_KP_ENTER,
        KEY_KP_1         = SDLK_KP_1,
        KEY_KP_2         = SDLK_KP_2,
        KEY_KP_3         = SDLK_KP_3,
        KEY_KP_4         = SDLK_KP_4,
        KEY_KP_5         = SDLK_KP_5,
        KEY_KP_6         = SDLK_KP_6,
        KEY_KP_7         = SDLK_KP_7,
        KEY_KP_8         = SDLK_KP_8,
        KEY_KP_9         = SDLK_KP_9,
        KEY_KP_0         = SDLK_KP_0,
        KEY_KP_PERIOD    = SDLK_KP_PERIOD
    //to be modified if needed
    };
    enum class MouseButton
    {
        MouseButton_LEFT = SDL_BUTTON_LEFT,
        MouseButton_RIGHT = SDL_BUTTON_MIDDLE,
        MouseButton_MIDDLE = SDL_BUTTON_RIGHT,
        MouseButton_4 = SDL_BUTTON_X1,
        MouseButton_5 = SDL_BUTTON_X2
    };   
}