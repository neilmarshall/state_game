#include "game.h"

Game::Game() {
    read_state_data("states.csv");
    shuffle_state_data();
}

void Game::read_state_data(std::string fpath) {
    std::string state;
    std::ifstream ifile(fpath);
    if (ifile.is_open()) {
        while (getline(ifile, state)) {
            state_list.push_back(state);
        }
        ifile.close();
    }
    else {
        std::cout << "File could not be opened!\n";
    }
}

void Game::shuffle_state_data() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);
    std::shuffle(state_list.begin(), state_list.end(), engine);
}

void Game::run() {
    char menu_choice;
    do {
        std::cout << "Please hit any key to play a round or 'q' to quit:\n";
        std::getline(std::cin, menu_choice);
        // std::cin >> menu_choice;
        if (menu_choice == "q") break;
        // if (menu_choice == 'q') break;
        // std::cin.clear();
        std::cin.ignore();
        play_round();
    } while (true);
    std::cout << "Game Exited!!!" << std::endl;
}

void Game::play_round() {
    
    int countdown = 1;
    std::string state = state_list.front();
    state_list.pop_front();
    std::string guess;
    
    do {
        std::cout << "Identify the state: " << state.substr(0, countdown) << "___\n";
        countdown += 1;
        std::getline(std::cin, guess);
        std::cout << "you guessed " << guess << std::endl;
    } while (guess != state || countdown < state.size());
    
    if (guess == state) {
        std::cout << "Congratulations - you guessed '" + state + "' correctly!!!\n";
    } else {
        std::cout << "Unlucky - you did not guess '" + state + "' - better luckt next time!!!\n";
    }
}