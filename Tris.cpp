#include <iostream>      // serve per usare cout e cin (input/output su console)
using namespace std;     // evita di scrivere ogni volta std:: davanti a cout/cin

int main() {
    // Creiamo il "campo da gioco": 9 caselle numerate da 1 a 9
    char board[9];                       // array di 9 char, ogni char è una casella
    for (int i = 0; i < 9; i++)          // ciclo da 0 a 8
        board[i] = '1' + i;              // inizializza con caratteri '1','2',...'9'

    char player = 'X';                   // il primo giocatore è sempre 'X'

    // Tutte le possibili combinazioni vincenti (8 terne)
    int win[8][3] = { {0,1,2},{3,4,5},{6,7,8},   // righe
                      {0,3,6},{1,4,7},{2,5,8},   // colonne
                      {0,4,8},{2,4,6} };         // diagonali

    // Funzione "lambda" per stampare la griglia
    auto printBoard = [&]() {             // lambda che "vede" board dall'esterno
        cout << "\n";                     // riga vuota per separare
        for (int r = 0; r < 3; r++) {     // per ogni riga della griglia (0..2)
            int i = r * 3;                // indice iniziale della riga
            cout << " " << board[i]       // stampa 1° colonna
                 << " | " << board[i+1]   // stampa 2° colonna
                 << " | " << board[i+2]   // stampa 3° colonna
                 << "\n";                 // a capo
            if (r < 2)                    // se non è l'ultima riga
                cout << "---+---+---\n";  // stampa linea di separazione
        }
        cout << "\n";                     // riga vuota finale
    };

    printBoard();                         // stampa la board iniziale (1..9)

    while (true) {                        // loop infinito fino a vittoria o pareggio
        int pos;                          // variabile per la scelta dell’utente
        cout << "Giocatore " << player
             << ", scegli una casella (1-9): ";
        cin >> pos;                       // legge numero da tastiera
        pos--;                            // trasformo da 1–9 a indice 0–8

        // Controllo validità della mossa
        if (pos < 0 || pos > 8 ||         // se fuori range
            board[pos] == 'X' || board[pos] == 'O') { // o casella già occupata
            cout << "Mossa non valida, riprova.\n";
            continue;                     // torna all’inizio del ciclo
        }

        board[pos] = player;              // segna la mossa del giocatore
        printBoard();                     // ristampa la griglia aggiornata

        // Controllo se il giocatore ha vinto
        bool winFound = false;            // flag che diventa true se trovo vittoria
        for (auto &line : win) {          // scorro tutte le terne vincenti
            if (board[line[0]] == player &&
                board[line[1]] == player &&
                board[line[2]] == player) {
                winFound = true;          // se trovo una terna uguale -> vittoria
                break;                    // esco dal ciclo
            }
        }
        if (winFound) {                   // se c’è un vincitore
            cout << "Ha vinto il giocatore " << player << "!\n";
            break;                        // fine del gioco
        }

        // Controllo se la partita è finita in pareggio (tutte le caselle piene)
        bool draw = true;                 // ipotizzo che sia pareggio
        for (int i = 0; i < 9; i++)       // scorro tutte le caselle
            if (board[i] != 'X' && board[i] != 'O')
                draw = false;             // se trovo una casella libera non è pareggio
        if (draw) {                       // se è davvero pareggio
            cout << "Pareggio!\n";
            break;                        // fine del gioco
        }

        // Cambio turno: se era 'X' diventa 'O', se era 'O' diventa 'X'
        player = (player == 'X') ? 'O' : 'X';
    }

    cout << "Ciao!\n";                    // messaggio di chiusura
    return 0;                             // fine del programma con successo
}