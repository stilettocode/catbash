#include <iostream>
#include "greetings.h"

void greeting(int& savedInt, std::string& savedString) {
    if (savedInt == 0) {
        std::cout <<
            "\033[33m      _\n"
            "       l`*-.\n"
            "        )  _`-.\n"
            "       .  : `. .\n"
            "       : _   '  l\n"
            "       ; *` _.   `*-._\n"
            "       `-.-'          `-.\n"
            "         ;       `       `.\n"
            "         :.       .        l\n"
            "         . l  .   :   .-'   .\n"
            "         '  `+.;  ;  '      :\n"
            "         :  '  |    ;       ;-.\n"
            "         ; '   : :`-:     _.`* ;\n"
            "cat    .*' /  .*' ; .*`- +'  `*'\n"
            "bash   `*-*   `*-*  `*-*'\033[0m\n\n"
            "\033[36mgit commands work with git replaced with cat. make sure you have git installed.\n\n"
            "catbash adopt <name> to adopt your first cat, or adopt a new one.\n"
            "catbash feed to feed your cat.\n"
            "yo <prompt> for command help.\n\n"
            "feed your cat every day to watch it grow!\033[0m\n\n";
    }
    else if (savedInt > 0 && savedInt < 4) {
        std::cout <<
            "\033[33m      |l     _,,,---,,_\n"
            "ZZZzz /,'.-'''    -.  ;-;;,_\n"
            "     |,4-  ) )-,_. ,l (  ''-'\n"
            "    '---''(_/--'  '-'l_)\033[0m\n\n";
        std::cout << "Your kitten " << savedString << " looks happy! You've fed it " << savedInt << " times.\n\n"
            "\033[36mgit commands work with git replaced with cat. make sure you have git installed.\n"
            "catbash adopt <name> to adopt your first cat, or adopt a new one.\n"
            "catbash feed to feed your cat.\n"
            "yo <prompt> for command help.\n\n"
            "feed your cat every day to watch it grow!\033[0m\n\n";
    }
    else if (savedInt > 3 && savedInt < 11) {
        std::cout <<
            "\033[33m                ,\n"
            "              _/((\n"
            "     _.---. .'   '\\\n"
            "   .'      '     ^ T=\n"
            "  /     \\       .--'\n"
            " |      /       )'-.\n"
            "  \\ \\-.__)    ''--.)\n"
            "   '.'-.__.-.\n"
            "     '-...-'\033[0m\n\n";
        std::cout << "Your kitten " << savedString << " looks happy! You've fed it " << savedInt << " times.\n\n"
            "\033[36mgit commands work with git replaced with cat. make sure you have git installed.\n"
            "catbash adopt <name> to adopt your first cat, or adopt a new one.\n"
            "catbash feed to feed your cat.\n"
            "yo <prompt> for command help.\n\n"
            "feed your cat every day to watch it grow!\033[0m\n\n";
    }
    else if (savedInt > 10 && savedInt < 26) {
        std::cout <<
            "\033[33m_                ___       _.--.\n"
            "\\’.|\\..----...-’’   ‘-._.-'_.-’’\n"
            "/  ‘ ‘         ,       __.--’\n"
            ")/’ _/     \\   ‘-_,   /\n"
            "‘-’’ ‘’\\_  ,_.-;_.-\\_ ‘,\n"
            "    _.-’_./   {_.’   ; /\n"
            "   {_.-’’-         {_/\033[0m\n\n";
        std::cout << "Your cat " << savedString << " looks happy! You've fed it " << savedInt << " times.\n\n"
            "\033[36mgit commands work with git replaced with cat. make sure you have git installed.\n"
            "catbash adopt <name> to adopt your first cat, or adopt a new one.\n"
            "catbash feed to feed your cat.\n"
            "yo <prompt> for command help.\n\n"
            "feed your cat every day to watch it grow!\033[0m\n\n";
    }
    else if (savedInt > 25 && savedInt < 76) {
        std::cout <<
            "\033[33m                         ,\n"
            "  ,-.       _,---._ __  / \\\n"
            " /  )    .-'       './ /   \\\n"
            "(  (   ,'            '/    /|\n"
            " \\  '_'             \\'\\   / |\n"
            "  '.              ,  \\ \\ /  |\n"
            "   /'.          ,'-'----Y   |\n"
            "  (            ;        |   '\n"
            "  |  ,-.    ,-'         |  /\n"
            "  |  | (   |            | /\n"
            "  )  |  \\  '.___________|/\n"
            "  '--'   '--'\033[0m\n\n";
        std::cout << "Your cat " << savedString << " looks happy! You've fed it " << savedInt << " times.\n\n"
            "\033[36mgit commands work with git replaced with cat. make sure you have git installed.\n"
            "catbash adopt <name> to adopt your first cat, or adopt a new one.\n"
            "catbash feed to feed your cat.\n"
            "yo <prompt> for command help.\n\n"
            "feed your cat every day to watch it grow!\033[0m\n\n";
    }
}