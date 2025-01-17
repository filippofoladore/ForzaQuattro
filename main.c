//FORZA QUATTRO - FILIPPO FOLADORE - 894669
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#define righe 6
#define colonne 7
#define file_r "risultati.txt"

    // DEFINZIONE PROTOTIPI
    void creaCampo(char matrice[righe][colonne]);
    void stampaCampo(char matrice[righe][colonne]);
    void pulisci();
    void intro();
    void impostaNome(char nome1[30], char nome2[30]);
    void impostaDataOra(char g[12], char o[12]);
    void inserisciGettone(char matrice[righe][colonne], int turno_giocatore, char *simbolo);
    bool orizzontale(char matrice[righe][colonne], char *simbolo, int turno_giocatore, int rig, int col);
    bool verticale(char matrice[righe][colonne], char *simbolo, int turno_giocatore, int rig, int col);
    bool diagonaleAvanti(char matrice[righe][colonne], char *simbolo, int turno_giocatore, int rig, int col);
    bool diagonaleIndietro(char matrice[righe][colonne], char *simbolo, int turno_giocatore, int rig, int col);
    int vittoria (char matrice[righe][colonne], int turno_giocatore, char *simbolo);
    void scriviFile(FILE *fileris, char n1[30], char n2[30], char v[30], char gg[12], char hm[12], int mosse);


int main()
{
    char campo[righe][colonne]; //campo di gioco
    char *simboli = "XO";       //simboli dei due gettoni
    int mossa = 0;              //contatore per decidere quale giocatore deve fare la mossa
    int limite = righe*colonne; //limite di turni (tutte le caselle)
    bool esci; bool v1; bool v2;//operatori per definire la fine della partita e l'utente che ha vinto
    int esitoMain;              //riceve il valore della funzione vittoria
    char gioc1[30]; char gioc2[30]; char vincitore[30]; //nome dei due giocatori e del vincitore al termine
    FILE *file_risultati;   //puntatore al file
    char giorno[12]; char ora[12]; //giorno e ora della partita

    intro();
    creaCampo(campo);
    impostaNome(gioc1, gioc2);
    impostaDataOra(giorno, ora);
        do{
        stampaCampo(campo);
        esci = false;
        inserisciGettone(campo, mossa % 2, simboli);
        stampaCampo(campo);
        esitoMain = vittoria(campo, mossa % 2, simboli);
        if (esitoMain == 0){
            v1 = true;   esci = true;
        }else if (esitoMain == 1){
            v2 = true;  esci = true;
        }
        mossa++;
        pulisci();
        }while (mossa < limite && esci != true);

        if (v1){
                stampaCampo(campo);
                printf("%s (%c) ha vinto!\n", gioc1, simboli[0]);
                strcpy(vincitore, gioc1);
        } else if (v2){
                stampaCampo(campo);
                printf("%s (%c) ha vinto!\n", gioc2, simboli[1]);
                strcpy(vincitore, gioc2);
        }

            scriviFile(file_risultati, gioc1, gioc2, vincitore, giorno, ora, mossa);
            printf("\nPartita finita! Premi un tasto per uscire. ");
            getchar();
            return 0;
}

    void creaCampo(char matrice[righe][colonne]){
        //funzione che crea il campo di gioco
        int i, j;
        for (i = 0; i < righe; i++){
            for (j = 0; j < colonne; j++){
                matrice[i][j] = ' ';
            }
        }
    }

    void stampaCampo(char matrice[righe][colonne]){
        //funzione che stampa il campo di gioco
        int i, j;
        printf("\n");
        printf("\t-----------------------------\n");
        for (i = 0; i < righe; i++){
            printf("\t");
        for (j = 0; j < colonne; j++){
            printf("| %c ", matrice[i][j]);
        }
        printf("|");
        printf("\n");
    }
    printf("\t*****************************\n");
    printf("Input:    0   1   2   3   4   5   6\n");
    }

     void pulisci(){
        //funzione che pulisce lo schermo
        system("@cls||clear");
}

    void intro(){
        //funzione che stampa le regole del gioco
        printf("\t F O R Z A   Q U A T T R O \n");
        printf("Il famoso gioco da tavolo in cui due giocatori si sfidano ad allineare dei gettoni su una griglia.\n");
        printf("Il gioco si svolge su una griglia 6x7 e l'obiettivo e' allineare quattro gettoni \ndel proprio simbolo in maniera orizzontale, verticale o diagonale.\n");
        printf("L'elemento fondamentale del gioco e' la forza di gravita' perche' \ninserendo in input una colonna si andra' ad occupare la riga libera piu' in basso.\n");
        printf("Il giocatore 1 giochera' con il simbolo X, il giocatore 2 giochera' con il simbolo O.\n");
        printf("\n\t I N I Z I A M O !\n\n");
    }

    void inserisciGettone(char matrice[righe][colonne], int turno_giocatore, char *simbolo){
        //funzione che avendo in input il giocatore che sta effettuando la mossa
        //e chiedendo una colonna in input inserisce il gettone all'interno della matrice
        int x,y;
        int contMeno = 1;
        printf("\nTurno del giocatore %d (%c). Inserisci una colonna compresa tra 0 e %d --> ", turno_giocatore+1, simbolo[turno_giocatore], colonne-1);
        do
        {
            scanf("%d", &y);
        } while (y < 0 || y > 6);

        printf("Inserisco il gettone nella colonna %d\n", y);
        for (x = righe-1; x >= 0; x--){
            if (matrice[x][y] == ' '){
                matrice[x][y] = simbolo[turno_giocatore];
                break;
            }
            else if (matrice[x-contMeno][y] != ' '){
                    contMeno++;
            }
        if (contMeno == righe) {
                printf("La colonna e' piena! Mossa sprecata!\n");
                Sleep(3000);
                break; return;
        }
    }
}

    bool orizzontale(char matrice[righe][colonne], char *simbolo, int turno_giocatore, int rig, int col){
        //controlla se 4 gettoni dello stesso segno sono allineati
        bool risultato = false;
        if (matrice[rig][col] == simbolo[turno_giocatore] && matrice[rig][col+1] == simbolo[turno_giocatore]
            && matrice[rig][col+2] == simbolo[turno_giocatore] && matrice[rig][col+3] == simbolo[turno_giocatore])
        {
            risultato = true;
        }
        return risultato;
    }

    bool verticale(char matrice[righe][colonne], char *simbolo, int turno_giocatore, int rig, int col){
        //controlla se 4 gettoni dello stesso segno sono allineati
        bool risultato = false;
        if (matrice[rig-1][col] == simbolo[turno_giocatore] && matrice[rig][col] == simbolo[turno_giocatore]
            && matrice[rig+1][col] == simbolo[turno_giocatore] && matrice[rig+2][col] == simbolo[turno_giocatore])
        {
            risultato = true;
        }
        return risultato;
    }

    bool diagonaleAvanti(char matrice[righe][colonne], char *simbolo, int turno_giocatore, int rig, int col){
        //controlla se 4 gettoni dello stesso segno sono allineati
        bool risultato = false;
        if (matrice[rig][col] == simbolo[turno_giocatore] && matrice[rig-1][col+1] == simbolo[turno_giocatore]
            && matrice[rig-2][col+2] == simbolo[turno_giocatore] && matrice[rig-3][col+3] == simbolo[turno_giocatore])
        {
            risultato = true;
        }
        return risultato;
    }

    bool diagonaleIndietro(char matrice[righe][colonne], char *simbolo, int turno_giocatore, int rig, int col){
        //controlla se 4 gettoni dello stesso segno sono allineati
        bool risultato = false;
        if (matrice[rig][col] == simbolo[turno_giocatore] && matrice[rig-1][col-1] == simbolo[turno_giocatore]
            && matrice[rig-2][col-2] == simbolo[turno_giocatore] && matrice[rig-3][col-3] == simbolo[turno_giocatore])
        {
            risultato = true;
        }
        return risultato;
    }

    int vittoria (char matrice[righe][colonne], int turno_giocatore, char *simbolo){
        //funzione che scannerizza la matrice chiamando le 4 funzioni di controllo e restituisce l'esito della partita
        int rig,col;
        int esito;
         for(rig = 0; rig < righe; rig++){
            for(col = 0; col < colonne; col++){
            if(matrice[rig][col] == simbolo[turno_giocatore]){
                if (orizzontale(matrice, simbolo, turno_giocatore, rig, col) || verticale(matrice, simbolo, turno_giocatore,rig, col)
                    || diagonaleAvanti(matrice, simbolo, turno_giocatore, rig, col) || diagonaleIndietro(matrice, simbolo, turno_giocatore, rig, col))
                {
                    esito = turno_giocatore;
                    break;
                }
            }
        }
    }
         return esito;
}

    void impostaNome(char nome1[30], char nome2[30]){
        printf("\nBenvenuti giocatori!\n");
        printf("Giocatore 1, inserisci il tuo nome --> ");
        scanf("%s", nome1);
        printf("Giocatore 2, inserisci il tuo nome --> ");
        scanf("%s", nome2);
        printf("\nGiocatore 1: %s\tGiocatore 2: %s\n", nome1, nome2);
    }

    void impostaDataOra(char g[12], char o[12]){
        time_t giorno;
        time(&giorno);
        struct tm* gioOut;
        gioOut = localtime(&giorno);
        //char giornoMeseAnno[12];
        strftime(g,12,"%d-%m-%Y",gioOut);
        time_t ora;
        time(&ora);
        struct tm* oraOut;
        oraOut = localtime(&ora);
        //char oraMinSec[12];
        strftime(o, 12, "%H:%M:%S", oraOut);

    }

    void scriviFile(FILE *fileris, char n1[30], char n2[30], char v[30], char gg[12], char hm[12], int mosse){
        fileris = fopen(file_r, "a+");
        if (fileris == NULL){
            printf("Impossibile aprire il file!\n");
            exit(1);
        } else {
            fprintf(fileris, "Data e ora partita: %s %s Giocatore 1: %s Giocatore 2: %s Esito: vittoria di %s dopo %d mosse\n", gg, hm, n1, n2, v, mosse);
        }
        fclose(fileris);
    }

