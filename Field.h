#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include <iostream>

#include "matrix.h"


class field
{
private:
protected:
public:
    enum Err_Placing
    {
        COORD_OUT_OF_RANGE,
        COORD_ENGAGED
    };

    matrix ship_places;///deck num
    matrix shoots;///bool
    Err_Placing ErrP;

    field()
    {
        matrix n_m(10,10);
            n_m.set_out_separator(' ');
                ship_places = n_m;
                shoots = n_m;
    }

    char show_texture(int i)
    {
        if ( i == 0)
            return '.';
        if (i == 4 || i == 3 || i == 2 || i == 1)
            return '#';
        if ( i == 5)
            return '*';
        if ( i == 8)
            return '+';
        if (i == 9)
            return '?';
        return ' ';
    }

    void show()///отрисовка основного игрового блока
    {
        std::cout << "          BATTLEMAP\t\t    FLEETMAP\n";
        std::cout << "*****************************************************\n";
        std::cout << "\n    1 2 3 4 5 6 7 8 9 10     1 2 3 4 5 6 7 8 9 10\n";
        for (int i = 0; i < shoots.get_height(); i++)
        {
            ///COORDBOX
            if(i == 9)
                std::cout << i+1 << "| ";
            else
                std::cout << " " << i+1 << "| ";

            for (int j = 0; j < shoots.get_width(); j++)
                std::cout << show_texture(shoots.get_data(i,j)) << " ";

            ///COORDBOX
            if(i == 9)
                std::cout << "|" << i+1 << "| ";
            else
                std::cout << "| " << i+1 << "| ";

            for (int k = 0 ; k < ship_places.get_width(); k++)
                std::cout << show_texture(ship_places.get_data(i,k)) << " ";

            ///COORDBOX
            if(i == 9)
                std::cout<< "|" << i+1 ;
            else
                std::cout << "|"<< i+1 ;

            std::cout << std::endl;
        }
    }

    bool check_coordinates(field& F, int x_coordinate, int y_coordinate)
    {
        if(x_coordinate < F.ship_places.get_width() && x_coordinate >= 0
            && y_coordinate < F.ship_places.get_height() && x_coordinate >= 0)
                return true;
        ErrP = Err_Placing::COORD_OUT_OF_RANGE;
        return false;
    }

    bool check_place_for_linnear_ship(field& F, int ship_size, int is_vertical, int x_coordinate, int y_coordinate)
    {std::cout << "check_place_for_linnear_ship\t";

        if(!is_vertical)
        {std::cout << "is horizontal\t";
            if(check_coordinates(F,x_coordinate, y_coordinate)
               && check_coordinates(F,x_coordinate+ship_size-1, y_coordinate))
            {std::cout << "coordinates in range\t";
                if( (F.ship_places.get_data(x_coordinate, y_coordinate) == 0 &&
                   F.ship_places.get_data(x_coordinate+ship_size-1, y_coordinate) == 0)
                  )///||(F.ship_places.get_data(x_coordinate, y_coordinate) == 5 && F.ship_places.get_data(x_coordinate+ship_size-1, y_coordinate) == 5)
                {std::cout << "can be placed\n";
                    return true;
                }else{std::cout << "can not be placed coordinate has value\n";
                    ErrP = Err_Placing::COORD_ENGAGED;
                    return false;
                }
            }else{std::cout << "coordinates out of range 1..10!\n";
                return false;
            }
        }else
            if(check_coordinates(F,x_coordinate, y_coordinate)
               && check_coordinates(F,x_coordinate, y_coordinate+ship_size-1))
            {std::cout << "coordinates in range\t";
                if(F.ship_places.get_data(x_coordinate, y_coordinate) == 0 &&
                   F.ship_places.get_data(x_coordinate, y_coordinate+ship_size-1) == 0)
                   {std::cout << "can be placed\n";
                       return true;
                }else{std::cout << "can not be placed coordinate has value\n";
                    return false;
                }
            }else{std::cout << "coordinates out of range 1..10!\n";
                return false;
            }

    };

    void place_ship(field& F, int ship_size, int is_vertical, int x_coordinate, int y_coordinate)
    {std::cout << "place_ship() " << x_coordinate << " " << y_coordinate << " " << x_coordinate+ship_size << std::endl;
        if(!is_vertical)
        {std::cout<< "not vertical\n";
            for(int i = 0; i < ship_size; i++)
            {
                //std::cout << "placing " << i << std::endl;
                //std::cout << "horiz place coord:" << x_coordinate << " " << y_coordinate << std::endl;
                F.ship_places.set_data( y_coordinate,x_coordinate, ship_size);
                x_coordinate++;
            }
        }else{
            for(int i = 0; i < ship_size; i++)
            {
                std::cout << "vert place coord:" << x_coordinate << " " << y_coordinate << std::endl;
                F.ship_places.set_data( y_coordinate, x_coordinate, ship_size);
                y_coordinate++;
            }
        }
    }

    void ship_spacing(field& F, int ship_size, int is_vertical, int x_coordinate, int y_coordinate)
    {///COORDINATES 0..9
        if(!is_vertical)///HORIZONTAL
        {
            if(x_coordinate > 0)///mark left border
            {
                if(y_coordinate>0)///top left corner
                    F.ship_places.set_data( y_coordinate-1,x_coordinate-1, 5);
                F.ship_places.set_data( y_coordinate,x_coordinate-1, 5);///left border
                if(y_coordinate<F.ship_places.get_height()-1)///bot left corner
                    F.ship_places.set_data( y_coordinate+1,x_coordinate-1, 5);
            }std::cout << "lb_marked\n";

            if(x_coordinate+ship_size < F.ship_places.get_width()-1)///mark right border
            {
                if(y_coordinate>0)
                    F.ship_places.set_data( y_coordinate-1,x_coordinate+ship_size, 5);
                F.ship_places.set_data( y_coordinate,x_coordinate+ship_size, 5);
                if(y_coordinate<F.ship_places.get_height()-1)
                    F.ship_places.set_data( y_coordinate+1,x_coordinate+ship_size, 5);
            }std::cout << "rb_marked\n";

            for(int i = 0; i < ship_size; i++)
            {
                if(y_coordinate>0)///mark top
                    F.ship_places.set_data( y_coordinate-1,x_coordinate, 5);
                if(y_coordinate<F.ship_places.get_width()-1)///mark bot
                    F.ship_places.set_data( y_coordinate+1,x_coordinate, 5);
                x_coordinate++;
            }std::cout << "tb_marked\n";
        }else{///VERTICAL
            if(y_coordinate > 0)///mark top border
            {
                if(x_coordinate>0)///top left corner
                    F.ship_places.set_data( y_coordinate-1,x_coordinate-1, 5);
                F.ship_places.set_data( y_coordinate-1,x_coordinate, 5);///top border
                if(x_coordinate<F.ship_places.get_width()-1)///top right corner
                    F.ship_places.set_data( y_coordinate-1,x_coordinate+1, 5);
            }std::cout << "tb_marked\n";

            if(y_coordinate+ship_size < F.ship_places.get_height()-1)///mark bot border
            {
                if(x_coordinate>0)
                    F.ship_places.set_data( y_coordinate + ship_size,x_coordinate-1, 5);
                F.ship_places.set_data( y_coordinate + ship_size,x_coordinate, 5);
                if(y_coordinate<F.ship_places.get_height()-1)
                    F.ship_places.set_data( y_coordinate + ship_size,x_coordinate+1, 5);
            }std::cout << "rb_marked\n";

            for(int i = 0; i < ship_size; i++)
            {
                if(x_coordinate>0)///mark left
                    F.ship_places.set_data( y_coordinate,x_coordinate-1, 5);
                if(y_coordinate<F.ship_places.get_height()-1)///mark right
                    F.ship_places.set_data( y_coordinate,x_coordinate+1, 5);
                y_coordinate++;
            }std::cout << "tb_marked\n";
        }
    }

    bool Place_Linnear_Ship(field& F, int ship_size, int is_vertical, int x_coordinate, int y_coordinate)///first_left or first_top deck coordinates
    {
        x_coordinate--;y_coordinate--;///НУМЕРАЦИЯ МАТРИЧНАЯ
        ///check for place
        if (check_place_for_linnear_ship(F, ship_size, is_vertical, x_coordinate, y_coordinate))
        {
            place_ship(F, ship_size, is_vertical, x_coordinate, y_coordinate);///place
            ship_spacing(F, ship_size, is_vertical, x_coordinate, y_coordinate);
        }else{
            this->info_err_placing();
            return false;
        }
        return true;
    }

    void Placing_Cycle_Player()
    {
        int is_vertical, x,y;
        bool repeat_placing_occur = false;
        for(int deck_number = 4; deck_number > 0; --deck_number)
            for(int i = 0; i < 5-deck_number;)
            {
                system("cls");
                this->show();
                std::cout << "*****************************************************\n\n";
                    if(repeat_placing_occur)
                        std::cout << "Placing err. Repeat!\n";
                    std::cout << "Placing ship deck number is " << deck_number <<
                            "is placed  " << i << "/" <<  5-deck_number<< std::endl;
                    std::cout << "\nEter 0 for horizontal 1 for vertical placing ";
                    std::cin >> is_vertical;
                    if (is_vertical)
                        std::cout << "\tVertical placing.";
                    else
                        std::cout << "\tHorizontal placing.";
                    std::cout << "Enter X and Y coordinate \n";
                    std::cin >> x >> y;

                if(Place_Linnear_Ship(*this, deck_number, is_vertical, x,y))
                    i++;
                else
                {
                    repeat_placing_occur = true;
                    std::cin >> x;
                }
            }
    }


    /*void Placing_Cycle_AI()
    {
        int is_vertical, x,y;
        bool repeat_placing_occur = false;
        for(int deck_number = 4; deck_number > 0; --deck_number)
            for(int i = 0; i < 5-deck_number;)
            {
                system("cls");
                this->show();
                std::cout << "*****************************************************\n\n";
                    if(repeat_placing_occur)
                        std::cout << "Placing err. Repeat!\n";

                    is_vertical = rand

                    if (is_vertical)
                        std::cout << "\tVertical placing.";
                    else
                        std::cout << "\tHorizontal placing.";
                    std::cout << "Enter X and Y coordinate \n";
                    std::cin >> x >> y;

                if(Place_Linnear_Ship(*this, deck_number, is_vertical, x,y))
                    i++;
                else
                {
                    repeat_placing_occur = true;
                    std::cin >> x;
                }
            }
    }*/

    void info_err_placing()
    {
        if(this->ErrP == Err_Placing::COORD_ENGAGED)
            std::cout << "PLACING_ERR: coordinate engaged!\n";
        if(this->ErrP == Err_Placing::COORD_OUT_OF_RANGE)
            std::cout << "PLACING_ERR: coordinate out of range!\n";

        std::cout << this->ship_places << std::endl;
    }
};

#endif // FIELD_H_INCLUDED
