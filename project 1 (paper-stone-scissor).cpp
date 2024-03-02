
#include <iostream>
# include <cstdlib>

using namespace std;
enum enwinner{computer =1 , user =2 , tie =0};
enum enchoices {stone =1 , paper =2 , scissor =3};
struct stgamechoices
{
    short game_rounds;
    short computer_win = 0;
    short user_win = 0;
    short ties = 0;
    enwinner winner;
    string winner_name;

};
struct stround_info {
    short round_number;
    enchoices player_choice;
    enchoices computer_choice;
    enwinner winner;
    string winner_name;

};
string choice_write_on_screen(enchoices choice) {
    switch (choice)
    {
        case enchoices::stone:
            return "stone";
        case enchoices::paper:
            return "paper";


        case enchoices::scissor:
            return "scissor";

        default:
            break;
    }
}
int computer_choice_randomly(int from =1 , int to=3) {

    int comp_choice = rand() % (to - from + 1) + from;
    return comp_choice;

}
enchoices computer_choice_enum (){
    return (enchoices) computer_choice_randomly(1,3);
}
short read_how_many_rounds() {
    short game_rounds;
    do{
        cout << "how many rounds 1 to 10 ?";
        cin >> game_rounds;

    } while (game_rounds < 1 || game_rounds >10);

    return game_rounds;
}
enwinner choices_possibleties(int user_choice , int comp_choice) {
    if (user_choice == comp_choice) {
        return enwinner::tie;
    }
    switch (user_choice) {
        case enchoices::stone:
            if (comp_choice == enchoices::paper) {
                return enwinner::computer;
            }
            break;
        case enchoices ::paper:
            if (comp_choice == enchoices::scissor) {
                return enwinner::computer;
            }
            break;
        case enchoices::scissor:
            if (comp_choice == enchoices::stone) {
                return enwinner::computer;
            }
            break;
    }
    return enwinner::user;

}
string winner_string(enwinner winner) {
    switch (winner)
    {

        case enwinner::computer:
            return "computer";
        case enwinner::user:
            return"user";
        case enwinner::tie:
            return "[no winner]";
        default:
            break;
    }
}

enchoices player_choice() {
    short player_choice;
    do {
        cout << " your choice :  " << " [1]:" << "stone, " << " [2]:" << "paper, " << " [3]:" << "scissor ?";
        cin >> player_choice;


    } while (player_choice < 1 || player_choice >3);
    return enchoices(player_choice);
}
enwinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes) {
    if (Player1WinTimes > ComputerWinTimes)
        return enwinner::user;
    else if(ComputerWinTimes > Player1WinTimes)
        return enwinner::computer;
    else
        return enwinner::tie;
}

stgamechoices fillgame_res(short game_rounds , short player_win_times , short computer_win_times , short draw_times) {
    stgamechoices game_results;
    game_results.game_rounds = game_rounds;
    game_results.user_win = player_win_times;
    game_results.computer_win = computer_win_times;
    game_results.ties = draw_times;
    game_results.winner = WhoWonTheGame(player_win_times, computer_win_times);
    game_results.winner_name = winner_string(game_results.winner);

    return game_results;

}
void print_round_info(stround_info roundinfo) {
    // round construction fonts
    cout << "--------------------------- round [" << roundinfo.round_number << "]" << "---------------------------" << endl;

    cout << "player1 choice : " << choice_write_on_screen(roundinfo.player_choice) << endl;
    cout << "computer choice : " << choice_write_on_screen(roundinfo.computer_choice) << endl;
    cout << " round winner:  " << roundinfo.winner_name << endl;
    cout << "-------------------------------------------------------------------------------" << endl;



}

stgamechoices play_rounds(short rounds) {

    stround_info round;
    short player_win_times=0;
    short computer_win_times=0;
    short ties=0;


    for (int i = 1; i <= rounds; i++)
    {
        cout << "\n Round [" << i << "] begins: \n";
        round.round_number = i;
        round.player_choice = player_choice();
        round.computer_choice = computer_choice_enum();
        round.winner = choices_possibleties(round.player_choice, round.computer_choice);
        round.winner_name = winner_string(round.winner);

        if (round.winner == enwinner::user)player_win_times++;
        if (round.winner == enwinner::computer)computer_win_times++;
        if (round.winner == enwinner::tie)ties++;
        print_round_info(round);

    }
    return fillgame_res(rounds, player_win_times, computer_win_times, ties);

}
void show_game_result(stgamechoices final) {

    cout << "\t\tgame rounds              :" << final.game_rounds << endl;
    cout << "\t\tplayer 1 won times       :" << final.user_win << endl;
    cout << "\t\tcomputer won times       :" << final.computer_win << endl;
    cout << "\t\tdraw times               :" << final.ties << endl;
    cout << "\t\tfinal winner             :" << final.winner_name << endl;

    cout << " \t \t---------------------------------------------------------------------------------- \t \t" << endl << endl;
}

void show_game_over_screen() {

    cout << " \t \t---------------------------------------------------------------------------------- \t \t" << endl << endl;

    cout << "\t \t \t \t \t +++ G A M E O V E R !!!!!! +++ \t \t" << endl << endl;
    cout << " \t \t---------------------------------------------------------------------------------- \t \t" << endl << endl;
    cout << " \t \t--------------------------------[ GAME RESULTS]----------------------------------- \t \t" << endl;
}
void round_choice_detailes() {
    char wanna_continue = 'Y';
    do
    {
        stgamechoices game = play_rounds(read_how_many_rounds()); // we have here all rounds res in game struct
        show_game_over_screen();
        show_game_result(game);
        cout << "\t\t do you want to play again y/n?";
        cin >> wanna_continue;
    }
    while (wanna_continue == 'y'||wanna_continue=='Y');
}
int main()
{
    srand((unsigned)time(NULL));

    round_choice_detailes();
}

