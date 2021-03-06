#include "game.h"

//******************************************************************************
//    Class constructor - reads states into a deque
//******************************************************************************

Game::Game() {
    read_state_data("states.txt");
}

//******************************************************************************
//    Function to reads states into a deque (and then shuffle them)
//******************************************************************************

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
    
    this->shuffle_state_data();
}

//******************************************************************************
//    Function to shuffle states deque
//******************************************************************************

void Game::shuffle_state_data() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);
    std::shuffle(this->state_list.begin(), this->state_list.end(), engine);
}

//******************************************************************************
//    Function to control running the game - launches once (if states deque not
//    empty) and subsequently loops as long as user indicates they want to
//    continue
//******************************************************************************

void Game::run() {
        
    char play_again_choice;
    do {
        if (state_list.empty()) break;
        std::system("clear");
        this->play_round();
        std::cout << "Play again? ('Y' / 'y' to continue, any other key to exit)\n";
        std::cin >> play_again_choice;
        std::cin.ignore();
    } while (play_again_choice == 'Y' || play_again_choice == 'y');
    std::cout << "Game Exited!!!" << std::endl;
}

//******************************************************************************
//    Function to play an individual round - called by 'run' repeatedly; reads
//    a state and prompts user to guess the state (compares guess again state
//    on a case-less basis for simplicity)
//******************************************************************************

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
    
    if (lowercase_guess == lowercase_state) {
        std::cout << "Congratulations - you guessed '" + state + "' correctly!!!\n";
    } else {
        std::cout << "Unlucky - you did not guess '" + state;
        std::cout << "' - better luck next time!!!\n";
    }
}
