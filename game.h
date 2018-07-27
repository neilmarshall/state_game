#include <algorithm>
#include <chrono>
#include <deque>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

class Game {
    public:
        Game();
        ~Game();
        void run();
    private:
        std::deque<std::string> state_list;
        void read_state_data(std::string);
        void shuffle_state_data();
        void play_round();
};
