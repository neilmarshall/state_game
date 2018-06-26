#include "game.h"

Game::Game() {
    read_state_data("states.txt");
}

void Game::read_state_data(std::string fpath) {

    std::string state;
    std::ifstream ifile(fpath);

    if (ifile.is_open()) {
        while (getline(ifile, state)) {
            this->state_list.push_back(state);
        }
        ifile.close();
    }
    else {
        std::cout << "File could not be opened!\n";
        return;
    }
    
    shuffle_state_data();
    
    return;
}

void Game::shuffle_state_data() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);
    std::shuffle(this->state_list.begin(), this->state_list.end(), engine);
}

void Game::run() {
        
    char play_again_choice;
    do {
        if (state_list.empty()) break;
        std::system("clear");
        play_round();
        std::cout << "Play again? ('Y' / 'y' to continue, any other key to exit)\n";
        std::cin >> play_again_choice;
        std::cin.ignore();
    } while (play_again_choice == 'Y' || play_again_choice == 'y');
    std::cout << "Game Exited!!!" << std::endl;

    return;
}

void Game::play_round() {
    
    int countdown = 0;
    std::string state = this->state_list.front();
    this->state_list.pop_front();
    std::string lowercase_state = state;
    std::transform(state.begin(), state.end(), lowercase_state.begin(), ::tolower);
    std::string guess, lowercase_guess;
    
    do {
        countdown += 1;
        std::cout << "Identify the state: " << state.substr(0, countdown) << "___\n";
        std::getline(std::cin, guess);
        std::system("clear");
        lowercase_guess = guess;
        std::transform(guess.begin(), guess.end(), lowercase_guess.begin(), ::tolower);
        if (lowercase_guess == lowercase_state) break;
        std::cout << "You guessed " << guess << " - that is not correct. ";
        std::cout << "Please guess again" << std::endl;
    } while (countdown < state.size());
    
    if (guess == state) {
        std::cout << "Congratulations - you guessed '" + state + "' correctly!!!\n";
    } else {
        std::cout << "Unlucky - you did not guess '" + state;
        std::cout << "' - better luck next time!!!\n";
    }

    return;
}
