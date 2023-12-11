#include "..\..\headers\chatnetwork.hpp"

int main(int argc, char * argv[]){
    AANetwork::Chat chat;
    chat.Connect("localHost", 2525);
    chat.Run();

    return 0;
}