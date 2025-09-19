#include <iostream>   // Libreria per input/output standard (cout, cin)
#include <stdlib.h>   // Libreria C (serve per rand, srand, system)
#include <ctime>      // Libreria per funzioni di tempo (time)
using namespace std;  // Usa lo spazio dei nomi standard (evita std::)

int main() {  
    srand((unsigned)time(NULL)); // Inizializza il generatore casuale con l'orario corrente

    int mode = 0;                        // Variabile per la modalità di gioco
    cout << "=== TRIS (Tic-Tac-Toe) ===\n";    // Titolo del gioco
    cout << "Scegli modalita:\n";             // Stampa menu scelta modalità
    cout << "  1) Due persone\n";             // Opzione: due giocatori
    cout << "  2) Contro CPU (tu = X, CPU = O)\n"; // Opzione: contro CPU
    cout << "Scelta: ";                        // Richiesta input scelta
    cin >> mode;                               // Legge la scelta dell’utente
    if (mode != 1 && mode != 2) {              // Controlla se scelta non è valida
        cout << "Scelta non valida. Esco.\n";  // Messaggio errore
        return 0;                              // Termina programma
    }

    char board[9];                             // Array di 9 celle per la griglia
    for (int i = 0; i < 9; i++) board[i] = '1' + i; // Inizializza la griglia con numeri '1'..'9'
    char player = 'X';                         // Primo giocatore = X

    int win[8][3] = {                          // Combinazioni vincenti
        {0,1,2},{3,4,5},{6,7,8},               // Righe
        {0,3,6},{1,4,7},{2,5,8},               // Colonne
        {0,4,8},{2,4,6}                        // Diagonali
    };

    auto printBoard = [&]() {                  // Funzione lambda per stampare la griglia
        cout << "\n";                          
        for (int r = 0; r < 3; r++) {          // Ciclo per 3 righe
            int i = r * 3;                     // Calcola indice di partenza riga
            cout << " " << board[i] << " | " << board[i+1] << " | " << board[i+2] << "\n"; // Stampa riga
            if (r < 2) cout << "---+---+---\n"; // Linea divisoria tra righe
        }
        cout << "\n";                          
    };

    system("clear"); // Pulisce lo schermo (su Windows sarebbe "cls")
    printBoard();    // Stampa griglia iniziale

    while (true) {   // Ciclo infinito finché la partita non termina
        int pos = -1; // Variabile per posizione scelta

        if (mode == 2 && player == 'O') {  // Se è turno della CPU
            do {
                pos = rand() % 9;          // Genera numero casuale tra 0 e 8
            } while (board[pos] == 'X' || board[pos] == 'O'); // Ripete finché la cella non è libera
            cout << "CPU (O) sceglie la casella " << (pos + 1) << " ...\n"; // Mostra scelta CPU
        } else {                           // Altrimenti turno di un giocatore umano
            cout << "Giocatore " << player << ", scegli una casella (1-9): "; // Richiesta input
            cin >> pos;                    // Legge posizione scelta
            pos--;                         // Conversione da 1..9 a 0..8

            if (cin.fail() || pos < 0 || pos > 8) { // Se input non valido
                cin.clear();               // Ripristina lo stato di cin
                cin.ignore(10000, '\n');   // Scarta input errato
                cout << "Input non valido. Riprova.\n"; // Avvisa l'utente
                continue;                  // Torna all’inizio del ciclo
            }
            if (board[pos] == 'X' || board[pos] == 'O') { // Se casella occupata
                cout << "Casella occupata! Riprova.\n";   // Messaggio di errore
                continue;                  // Torna all’inizio del ciclo
            }
        }

        board[pos] = player;   // Applica la mossa sulla griglia
        system("clear");       // Pulisce schermo
        printBoard();          // Stampa nuova griglia aggiornata

        bool winFound = false; // Flag vittoria
        for (auto &line : win) { // Controlla tutte le combinazioni vincenti
            if (board[line[0]] == player && 
                board[line[1]] == player && 
                board[line[2]] == player) { // Se 3 in fila dello stesso giocatore
                winFound = true; 
                break;            // Vittoria trovata
            }
        }

        if (winFound) {          // Se un giocatore ha vinto
            if (mode == 2 && player == 'O') // Se è CPU
                cout << "Ha vinto la CPU!\n"; 
            else                            // Se è umano
                cout << "Ha vinto il giocatore " << player << "!\n";
            break;              // Fine partita
        }

        bool draw = true;       // Flag pareggio
        for (int i = 0; i < 9; i++) { // Controlla se ci sono caselle libere
            if (board[i] != 'X' && board[i] != 'O') { // Se trova casella libera
                draw = false; 
                break;
            }
        }
        if (draw) {             // Se nessuna casella libera → pareggio
            cout << "Pareggio!\n";
            break;              // Fine partita
        }

        player = (player == 'X') ? 'O' : 'X'; // Alterna turno tra X e O
    }

    cout << "Fine partita\n";   // Messaggio finale
    return 0;                   // Termina programma
}