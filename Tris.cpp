#include <iostream>  
#include <stdlib.h>   
#include <ctime>     
using namespace std;

int main() {
    srand((unsigned)time(NULL));

    //Scelta modalità
    int mode = 0;                       
    cout << "=== TRIS (Tic-Tac-Toe) ===\n";
    cout << "Scegli modalita:\n";
    cout << "  1) Due persone\n";
    cout << "  2) Contro CPU (tu = X, CPU = O)\n";
    cout << "Scelta: ";
    cin >> mode;
    if (mode != 1 && mode != 2) {
        cout << "Scelta non valida. Esco.\n";
        return 0;
    }

    //Inizializzazione griglia
    char board[9];
    for (int i = 0; i < 9; i++) board[i] = '1' + i; // '1'..'9'
    char player = 'X';

    //Combinazioni vincenti
    int win[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}          
    };

    //Stampa griglia
    auto printBoard = [&]() {
        cout << "\n";
        for (int r = 0; r < 3; r++) {
            int i = r * 3;
            cout << " " << board[i] << " | " << board[i+1] << " | " << board[i+2] << "\n";
            if (r < 2) cout << "---+---+---\n";
        }
        cout << "\n";
    };

    system("clear"); 
    printBoard();

    //Loop partita
    while (true) {
        int pos = -1;

        if (mode == 2 && player == 'O') {
            //Turno CPU
            do {
                pos = rand() % 9; // 0..8
            } while (board[pos] == 'X' || board[pos] == 'O');

            cout << "CPU (O) sceglie la casella " << (pos + 1) << " ...\n";
        } else {
            //Turno 2 giocatore
            cout << "Giocatore " << player << ", scegli una casella (1-9): ";
            cin >> pos;
            pos--;

            if (cin.fail() || pos < 0 || pos > 8) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Input non valido. Riprova.\n";
                continue;
            }
            if (board[pos] == 'X' || board[pos] == 'O') {
                cout << "Casella occupata! Riprova.\n";
                continue;
            }
        }

        //Applica mossa
        board[pos] = player;

        system("clear");
        printBoard();

        //Controllo vittoria
        bool winFound = false;
        for (auto &line : win) {
            if (board[line[0]] == player &&
                board[line[1]] == player &&
                board[line[2]] == player) {
                winFound = true;
                break;
            }
        }
        if (winFound) {
            if (mode == 2 && player == 'O')
                cout << "Ha vinto la CPU!\n";
            else
                cout << "Ha vinto il giocatore " << player << "!\n";
            break;
        }

        //Controllo pareggio
        bool draw = true;
        for (int i = 0; i < 9; i++) {
            if (board[i] != 'X' && board[i] != 'O') { draw = false; break; }
        }
        if (draw) {
            cout << "Pareggio!\n";
            break;
        }

        //Cambio turno
        player = (player == 'X') ? 'O' : 'X';
    }

    cout << "Fine partita\n";
    return 0;
}