#ifndef SHOOTING_H_INCLUDED
#define SHOOTING_H_INCLUDED

#include <iostream>
#include "matrix.h"


void shot(field& F_player, field& F_enemy, int j, int i, bool& flag_repeat, bool& flag_game_over)
{
     --i; --j;///MATRIX COORDINATE
    if(i>=0 && i<=9 && j>=0 && j<=9)
    {
        ///проверяем куда попали
        ///попадение по кораблю
        if(F_enemy.ship_places.get_data(i,j) == 4 ||F_enemy.ship_places.get_data(i,j) == 3
           || F_enemy.ship_places.get_data(i,j) == 2 || F_enemy.ship_places.get_data(i,j) == 1)
        {///попадание
            F_enemy.ship_places.set_data(i,j, 9);
            F_player.shoots.set_data(i,j, 9);
            ///при поподании можно стрелять еще раз
            //cout << F_enemy.ship_places << endl;
            std::cout << "Succes! Bonus shooting!\n";
            flag_repeat = true;
        }else{
            if (F_enemy.ship_places.get_data(i,j) == 8)
            {///уже стреляли - повтор выстрела
                std::cout << "Already shot! Enter other coordinates!\n";
                flag_repeat = true;
            }else{///отмечается выстрел по полю
                F_enemy.ship_places.set_data(i,j,8);
                F_player.shoots.set_data(i,j,8);
                flag_repeat = false;
            }
        }}else{
            std::cout << "Incorrect coordinates! Enter other coordinates!\n";
            flag_repeat = true;
    }
}


#endif // SHOOTING_H_INCLUDED
