/// Gra karciana 

#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct card //struktura karty
{
    
    int pwr;
    char type;
    bool spell;
    bool table;
};
struct hero //struktura postaci
{
    
    int pwr;
    char type;
};

//PROTOTYPY
int fight (hero PC, hero AI, int tab[4][4]); // fukcja walki między postaciami
void play (hero& QQ, card& WW); // funkcja zagrania karty
void discard (card& WW); // funkcja odrzucenia karty (na stol)
void draw (card& WW, card DD, int& counter); // funkcja doboru karty
void rrand (card& DD); //funkcja zapełniania talii

//M A I N
int main ()
{
    srand( time(NULL) );
    int element_chart[4][4]; // dwuwymiarowa tablica okresla modyfikatory od typow postaci
    element_chart[0][0] = 0;
    element_chart[0][1] = -1;
    element_chart[0][2] = +2;
    element_chart[0][3] = -1;
    element_chart[1][0] = 1;
    element_chart[1][1] = 0;
    element_chart[1][2] = -2;
    element_chart[1][3] = 1;
    element_chart[2][0] = 0;
    element_chart[2][1] = 2;
    element_chart[2][2] = 0;
    element_chart[2][3] = -2;
    element_chart[3][0] = 0;
    element_chart[3][1] = -2;
    element_chart[3][2] = 2;
    element_chart[3][3] = 0;
    
    int balans =0; // zmienna śledzaca wynik gry
    int counter = 60;// licznik śledzący pozycje karty w talii
    card PChand[4]; // tablica przechowujaca reke gracza
    card AIhand[4];// tablica przechowujaca reke komputera
    card deck[60]; // tablica przechowujaca talie
    hero PC; // postac gracza
    hero AI; // postac komputera
    
    for(int i = 0; i < 60; i++) // zapelnianie talii
    {
        
        rrand(deck[i]);
        
    }
    int turn = 1;
    for (int i = 0; i < 4; i++) PChand[i].table = true; // zapelnienie reki gracza
    for (int i = 0; i < 4; i++) AIhand[i].table = true; // zapelnianie reki komputera
    while (counter != 0) //poczatek gry
    {
        //dobieranie kart
        for (int i = 0; i < 4; i++) draw(PChand[i], deck[counter-1], counter);
        for (int i = 0; i < 4; i++) draw(AIhand[i], deck[counter-1], counter);
        cout << "-Tura " << turn << '-' << endl <<"RĘKA: |"<< PChand[0].type << PChand[0].pwr << "| |" << PChand[1].type << PChand[1].pwr << "| |" << PChand[2].type << PChand[2].pwr << "| |" << PChand[3].type << PChand[3].pwr << "|" << endl;
        int wybor = 10;
        
        while (wybor > 5 || wybor < 1 || PChand[wybor-1].spell == true || PChand[wybor-1].table == true)// petla powtarza sie dopoki gracz wybierze karte bohatera
        {
            cout << "Wybierz karte bohatera: ";
            cin >> wybor;
            if (wybor > 5 || wybor < 1 || PChand[wybor-1].spell == true || PChand[wybor-1].table == true) cout << "\nZla karta!\n";// jesli gracz nie wybierze postaci lub nie wybierze z reki
            
        }
        play (PC, PChand[wybor-1]);
        discard (PChand[wybor-1]);
        
        int randomwybor = 10;
        while (AIhand[randomwybor].spell == true || AIhand[randomwybor].table == true)//upewniamy sie, ze komputer wybiera bohatera
        {
            randomwybor = rand()%4;
        }
        play (AI, AIhand[randomwybor]);
        discard (AIhand[randomwybor]);
        
        cout <<endl<< PC.type << PC.pwr << " VS " << AI.type << AI.pwr;
        // Tura rzucania czaraów
        int xx = -1; // zmienna sprawdzajaca czy gracz rzucil czar
        int yy = -1; // zmienna sprawdzajaca i decydujaca czy komputer rzuil czar
        int zz = 0; // znacznik
        while (zz == 2);
        {
            //gracz rzuca czar
            cout << "\nCzy chcesz rzucic czar ?\n->TAK(0)\n->NIE(1)";
            while (xx > 1 || xx < 0)
            {
                cin >> xx;
                if (xx > 1 || xx < 0) cout << "\nWybierz TAK lub NIE! ";
            }
            if (xx == 0)
            {
                wybor = 10;
                while (wybor > 5 || wybor < 0 || PChand[wybor-1].spell == false || PChand[wybor-1].table == true)//petla powtarza sie dopoki gracz wybierze karte czaru
                {
                    cout << "Wybierz karte czaru: ";
                    cin >> wybor;
                    if (wybor > 5 || wybor < 0 || PChand[wybor-1].spell == false || PChand[wybor-1].table == true) cout << "\nZla karta! ";
                }
                play (PC, PChand[wybor-1]);
                discard (PChand[wybor-1]);
            }
            //komputer rzuca czar
            yy = rand()%1;
            if (yy == 0)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (AIhand[i].spell == true)//jezeli ktoras karta z reki komputera jest czarem
                        
                    {
                        play (AI, AIhand[i]);
                        discard (AIhand[i]);
                    }
                }
            }
            zz = xx + yy;
        };
        
        cout <<endl<< PC.type << PC.pwr << " VS " << AI.type << AI.pwr;
        balans = balans + fight(PC, AI, element_chart);
        cout << "\nKoniec tury\n\n\n\n"<< "Wynik rozgrywki ("<<PC.type << PC.pwr << " VS " << AI.type << AI.pwr<<")"<<fight(PC, AI, element_chart)<<"pkt"<<endl;
        turn++;
        
    }
    
    
    if(balans > 0) cout << "ZWYCIĘSTWO\n\n";
    else if (balans == 0) cout << "REMIS\n\n";
    else cout << "PORAŻKA\n\n";
    
    system ("pause");
    return 0;
}

//DEFINICJE
int fight (hero PC, hero AI, int tab[4][4])
{
    int pts;
    int x;
    int y;
    //element chart
    if (PC.type == 'O') x = 0;
    if (PC.type == 'W') x = 1;
    if (PC.type == 'Z') x = 2;
    if (PC.type == 'E') x = 3;
    
    if (AI.type == 'O') y = 0;
    if (AI.type == 'W') y = 1;
    if (AI.type == 'Z') y = 2;
    if (AI.type == 'E') y = 3;
    
    PC.pwr = PC.pwr + tab[x][y];
    AI.pwr = AI.pwr + tab[y][x];
    pts = PC.pwr - AI.pwr;
    return pts;
}
void play (hero& QQ, card& WW)
{
    if (WW.spell == false) // gdy karta z reki nie jest czarem
    {
        
        QQ.pwr = WW.pwr;
        QQ.type = WW.type;
    }
    else if (WW.pwr != 0) QQ.pwr = QQ.pwr + WW.pwr; //karta zwieksza sile
    else QQ.type = WW.type; // karta jest czarem zmiany typu
    
}
void discard (card& WW)
{
    WW.table = true;
    WW.pwr = 0;
    WW.type = 'X';
}
void draw (card& WW, card DD, int& counter)
{
    if(WW.table == true)
    {
        
        WW.pwr = DD.pwr;
        WW.type = DD.type;
        WW.spell = DD.spell;
        WW.table = false;
        counter--;
    }
}
void rrand (card& DD)
{
    int base = rand()%99; // baza 100 randomowych liczb
    if(base < 15) DD.spell = true; // prawdopodobientwo wylosowania czaru nie wieksze niz 15%
    else DD.spell = false;
    if (DD.spell == true) DD.pwr = rand()%2;
    else DD.pwr = rand()%5 + 1;
    {
        switch (base%4)
        {
            case 0:
                DD.type = 'O';
                break;
            case 1:
                DD.type = 'W';
                break;
            case 2:
                DD.type = 'Z';
                break;
            case 3:
                DD.type = 'E';
                break;
            default:
                cout << "BLAD!!!";
                system("pause");
                break;
        }
        if (DD.spell == true && DD.pwr != 0) DD.type = '+';
    }
}
