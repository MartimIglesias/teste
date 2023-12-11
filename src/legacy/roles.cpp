#include "roles.hpp"
#include <cstdlib>  // Para rand()

// Escolhe um jogador aleatoriamente que ainda esteja vivo
Player& escolhe_player(std::vector<Player>& players) 
{
    Player* chosen = nullptr;
    while (!chosen) 
    {
        int index = rand() % players.size();
        if (players[index].isAlive()) 
        {
            chosen = &players[index];
        }
    }
    return *chosen;
}

std::string Investigador::classifyRole(const std::string& roleName) 
{
    if (roleName == "Salazar" || roleName == "PIDE") 
    {
        return "Mau";
    }
    // No caso de adicionar mais roles neutras no futuro, como "Bruxa":
    // else if (roleName == "Bruxa") {
    //     return "Neutro";
    // }
    else 
    {
        return "Bom";
    }
}

void SK::acao_noite(std::vector<Player>& players) 
{
    Player& target = escolhe_player(players);
    target.kill();  // Supondo que haja um método "kill" na classe Player
}

void Mafia::acao_noite(std::vector<Player>& players) 
{
    Player& target = escolhe_player(players);
    target.kill();
}

void Doutor::acao_noite(std::vector<Player>& players) 
{
    Player& target = escolhe_player(players);
    target.save();  // Supondo que haja um método "save" na classe Player
}

void Investigador::acao_noite(std::vector<Player>& players) 
{
    Player& target = escolhe_player(players);
    
    std::string roleClassification = classifyRole(target.getRoleName());
    
    std::cout << "Descobriste que " << target.getName() << " é " << roleClassification << ".\n";
}

void Aldeao::acao_noite(std::vector<Player>& players) {
    // Os aldeões podem não ter ação à noite, mas se você quiser, pode adicionar algo específico aqui.
}

