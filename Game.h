#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Field.h"
#include "Shooting.h"
#include "AI.h"


class Game
{
private:
protected:

    enum GameMode
    {
        SinglePlayer,
        Coop
    };

    enum GameStage
    {
        MENU,
        SHIP_PLACING_AI,
        SHIP_PLACING_PLAYER1,
        SHIP_PLACING_PLAYER2,
        GAME_TURN_AI,
        GAME_TURN_PLAYER,
        GAME_OVER
    };

    ///******
    ///переставить в field
    enum ShipsForm
    {
        ShipsLinnear,
        ShipsAny
    };
    enum ShipsSpacing
    {
        SpacingBox,
        SpacingOff
    };
    ///********

public:
    field F1;
    field F2;
    GameMode GMode;
    GameStage GStage;
    ShipsForm GSForm;
    ShipsSpacing GSSpacing;

    //Game()
    //{
        //F1();
      //  F2();
    //}

    void Run()
    {
        GStage = MENU;
        int i_buff = 0;

        std::cout << "Enter Game Mode 1 - Single Player, 2 - Coop: ";
            std::cin >> i_buff;
            if(i_buff == 1)
                GMode = SinglePlayer;
            if(i_buff == 2)
                GMode = Coop;
            else
                GMode = GameMode::SinglePlayer;

        std::cout << "Enter Ship Form 1 - Linnear, 2 - Any: ";
            std::cin >> i_buff;
            if(i_buff == 1)
                GSForm = ShipsLinnear;
            if(i_buff == 2)
                GSForm = ShipsAny;
            else
                GSForm = ShipsLinnear;

        std::cout << "Enter Spacing Mode 1 - BoxLike, 2 - None: ";
            std::cin >> i_buff;
            if(i_buff == 1)
                GSSpacing = SpacingBox;
            if(i_buff == 2)
                GSSpacing = SpacingOff;
            else
                GSSpacing = SpacingBox;

        GStage = SHIP_PLACING_PLAYER1;
        this->F1.Placing_Cycle_Player();

        if(GMode == Coop){std::cout << "COOP!\n";
            GStage = SHIP_PLACING_PLAYER2;
            this->F2.Placing_Cycle_Player();
        }else{std::cout << "SINGLE!\n";
            Game_BS_AI ai;//(Game_BS_AI::AI_Placing_Mode::random);
            GStage = SHIP_PLACING_AI;
            ai.AI_placing(this->F2);
        }

        this->GameLoop();
        GStage = GAME_OVER;
    }


    void GameLoop()
    {
        GStage = GameStage::GAME_TURN_PLAYER;
        srand(time(0));rand();

        bool flag_game_over = false, flag_repeat = false;
        int X = 0, Y = 0;

        std::cout << "READY TO START?\n";
        std::string buff;
            std::cin >> buff;
        system("cls");

        //cout << "GAME STARTED\n";
        int turn_counter = 0;
        while(!flag_game_over && turn_counter < 80)
        {
            turn_counter++;
            std::cout << "\t\tTURN " << turn_counter << " STARTED!\n";
            std::cout << "******************************************************\n";
           //     cin >> buff;
           // system("cls");
            do{
                F1.show();
                std::cout << "******************************************************\n";
                if(flag_repeat)
                    std::cout << "Another shoot! ";
                std::cout << "Enter coordinates X, Y:\n";

                std::cin >> X >> Y;
             //   shot(P1, P2, X, Y, flag_repeat, flag_game_over);
                system("cls");
            }while(flag_repeat);
        }
    }

    void info_game_stage()
    {
        std::cout << "info_game_stage\n";
    }

    void info_game_mode()
    {
        if(GMode == GameMode::Coop)
            std::cout << "GameMode: Coop\n";
        else
            if(GMode == GameMode::SinglePlayer)
                std::cout << "GameMode: SinglePlayer\n";
            else
                std::cout << "GameMode: indefined\n";
    }
};

#endif // GAME_H_INCLUDED
