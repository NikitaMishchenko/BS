#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include <iostream>

#include <ctime>
#include <random>

#include "Field.h"

class Game_BS_AI
{
private:
protected:
public:
    enum AI_Placing_Mode
    {
        random,
        stupid,
        advanced, ///снижение вероятности попадания
        from_file
    };

    AI_Placing_Mode AI_pm;

    //AI(AI_Placing_Mode p)
    //{AI_pm = p;}

    void AI_placing(field &F)
    {
        ///random
        int is_vertical,x,y;
            is_vertical = x = y = 0;
        std::string sbuff;
        //if( AI_Placing_Mode::stupid)
        std::cout << "Stupid Placing\n";
            for(int deck_number = 4; deck_number > 0; --deck_number)
                {for(int i = 0; i < 5-deck_number;)
                {
                    get_total_random_coordinates(deck_number, is_vertical, x, y);

                    std::cout << "\tdeck_number\tvert\tx\t\y\n";
                    std::cout << "\tR_param " << deck_number << "\t" << is_vertical << "\t"
                        << x << "\t" << y << std::endl;

                    if(F.Place_Linnear_Ship(F, deck_number, is_vertical, x,y))
                    {std::cout << "SUCESS\n\n";
                        i++;
                    }else{
                        //repeat_placing_occur = true;
                        get_total_random_coordinates(deck_number, is_vertical, x, y);
                    }
                    F.show();
                    //std::cin >> sbuff;
                }}
    }

    void get_total_random_coordinates(int deck_number, int& is_vertical, int& x, int& y)
    {
        is_vertical = get_rand_int(0,1);
        if(!is_vertical)
        {
            x = get_rand_int(1,10-deck_number);
            y = get_rand_int(1,10);
        }else{
            x = get_rand_int(1,10);
            y = get_rand_int(1,10-deck_number);
        }
    }

    void smart_place(field& F, int decl_number)
    {
        ///не ясно
    };


    int get_rand_int(int min_, int max_)
    {
        static double fraction = 1.0/(static_cast<double>(RAND_MAX + 1.0));
        return static_cast<int>( rand()*fraction*(max_-min_+1)+min_);
    }
};



#endif // AI_H_INCLUDED
