#include <iostream>

#include <ctime>
#include <random>
#include <windows.h>

#include <string>
#include <queue>

//#include "matrix.h"
#include "Game.h"
#include "Field.h"




/*struct ship_struct
{
    int deck_initial;
    int deck_current;
};*/


/*
int get_rand_int(int min_, int max_)
{
    static double fraction = 1.0/(static_cast<double>(RAND_MAX + 1.0));
    return static_cast<int>( rand()*fraction*(max_-min_+1)+min_);
}*/

/*
void act_auto_place_ship(field& F,ship_struct s)
{
    int i = 0, ///height
        j = 0; ///width
    ///10^2 empty
    if(s.deck_current == 4)///в начале не важно куда поставить, можно регулировать поворотом/отражением поля
    {
        i = get_rand_int (0, (F.ship_places).get_height());
        j = get_rand_int (0, (F.ship_places).get_width()-s.deck_current-1);

        for(int k = j; k < j+4; k++)
            F.ship_places.set_data(i,k,s.deck_current);

        if( get_rand_int(1,2) == 1){std::cout << "transpose!\n";
            F.ship_places.transpose(F.ship_places);}

    }
    ///10^2-4=96 empty
    ///random coordinate
    if(true)
    {
        ///i = rand (0, field.ship_places.get_height());
        ///j =
        ///if (field.ship_places.get_data(i,j) == 0)
    }
};



void procedure_auto_place_ships(field &F)
{
    std::queue <ship_struct> ship_list;
    ship_struct s;
    for(int i = 4; i > 0; --i)
    {
        s.deck_initial = i;
        for(int j = i; j <= 4; ++j)
        {
            s.deck_current = s.deck_initial;
            ship_list.push(s);
        }
    }

    ///print_list
    while(ship_list.size())
    {
       cout << ship_list.front().deck_initial << "/" << ship_list.front().deck_current << endl;
       ship_list.pop();
    }

    ///SHIP_FORM_MODE : narrow, any
    ///SHIP PLACING_MODE : distance, corner_anable, any

    ///placing
    ///narrow, distance
    while(ship_list.size())
    {
        act_auto_place_ship(F,ship_list.front());
        ship_list.pop();
    }
}
*/

int main()
{
    //srand(time(0));rand();
    //field P1;

    //P1.Placing_Cycle();

    Game NewGame;
    //NewGame.Run();
    NewGame.F1.Placing_Cycle_Player();

    //GameLoop();

    //P1.ship_places.Save_matrix("shipepta.txt");

}
