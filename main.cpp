#include <iostream>

int main() {

    std::string menu_choice;
    do {
        std::cout << "Hit any key to continue, or 'q' to quit:\n";
        std::getline(std::cin, menu_choice);
    } while (menu_choice != "q");

    std::cout << "Game exited!!!";

    return 0;
}
