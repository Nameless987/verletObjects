#include "init.hpp"

using namespace sf;
using namespace std;

int main(){
    window.setFramerateLimit(144);

    srand(time(NULL));

    init_circles(newPlayer, player, circles, 1);
    init_text(text);

    
    backCircle.append(Vector2f(960-500, 540-500));
    backCircle.append(Vector2f(960+500, 540-500));
    backCircle.append(Vector2f(960+500, 540+500));
    backCircle.append(Vector2f(960-500, 540-500));
    backCircle.append(Vector2f(960-500, 540+500));
    backCircle.append(Vector2f(960+500, 540+500));
    
    backCircle[0].texCoords = Vector2f(0, 0);
    backCircle[1].texCoords = Vector2f(1000, 0);
    backCircle[2].texCoords = Vector2f(1000, 1000);

    backCircle[3].texCoords = Vector2f(0, 0);
    backCircle[4].texCoords = Vector2f(0, 1000);
    backCircle[5].texCoords = Vector2f(1000, 1000);

    backCircle[0].color = Color(0, 0, 0);
    backCircle[1].color = Color(0, 0, 0);
    backCircle[2].color = Color(0, 0, 0);

    backCircle[3].color = Color(0, 0, 0);
    backCircle[4].color = Color(0, 0, 0);
    backCircle[5].color = Color(0, 0, 0);


    const Vector2f posLimit = {960.0f, 540.0f};
    const float radius = 500.0f;

    //cout<<"player 1 : "<<atan2(player[0].y-player[1].y, player[1].x-player[0].x)/3.1415926535*180<<endl;
    //cout<<"player 2 : "<<atan2(player[1].y-player[0].y, player[0].x-player[1].x)/3.1415926535*180<<endl;

    while(window.isOpen()){

        float dt = gameClock.getElapsedTime().asSeconds();

        float deltaT = timer.getElapsedTime().asMilliseconds();

        input(player, dt);

        if(dt >= 0 && !pause){

            gameClock.restart();

            if(player.size()<500 && deltaT>50){
                int i = player.size()-1;
                newCircle(newPlayer, player, circles, i);
                player[i].pos_current = {960, 100};
                player[i].pos_old = {959, 99};
                player[i].r = 10;
                timer.restart();
            }

            for(int32_t k=0; k<8; k++){
                float sub_dt = dt/8.0f;

                for(int i=0; i<player.size(); i++){
                    player[i].accelerate({0, 100});
                    player[i].move(sub_dt);
                    player[i].applyConstraints(posLimit, radius);
                    for(int j=0; j<player.size(); j++){
                        float d = dist(player[i].pos_current.x, player[i].pos_current.y, player[j].pos_current.x, player[j].pos_current.y);
                        if(d<player[i].r+player[j].r && i!=j){
                            player[i].collide(player[j], d);
                        }
                    }
                }
            }
            for(int i=0; i<player.size(); i++){
                animation(player, circles, i);
            }
        }

        //window.draw(text);

        //window.draw(cases);
        window.draw(backCircle, &texture);

        window.draw(circles, &texture);

        window.display();
    }

    return 0;
}