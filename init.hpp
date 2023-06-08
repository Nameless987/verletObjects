#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <math.h>

using namespace sf;
using namespace std;

const char* nameProject = "Projet cpp";

bool fullscreen = true;
bool pause;

RenderWindow window(VideoMode(1920, 1080), nameProject, (fullscreen ? Style::Fullscreen : Style::Resize|Style::Close));

float dist(float a, float b, float c, float d){
    return sqrt(pow((c-a), 2) + pow((d-b), 2));
}

float gauss(float x){
    return (255/(1+exp(-0.07*(x-100))));
}

#include "structures.hpp"
#include "core.hpp"

Font font;
Text text;
Event event;
Mouse mouse;
Clock gameClock;
Clock timer;
Texture texture;

vector<point> player;
point newPlayer;
VertexArray circles(PrimitiveType::Triangles);


VertexArray backCircle(PrimitiveType::Triangles);

void newCircle(point nP, vector<point> &p, VertexArray &c, int i){
    p.push_back(nP);
    
    
    c.append(Vector2f(p[i].pos_current.x-p[i].r, p[i].pos_current.y-p[i].r));
    c.append(Vector2f(p[i].pos_current.x+p[i].r, p[i].pos_current.y-p[i].r));
    c.append(Vector2f(p[i].pos_current.x+p[i].r, p[i].pos_current.y+p[i].r));
    c.append(Vector2f(p[i].pos_current.x-p[i].r, p[i].pos_current.y-p[i].r));
    c.append(Vector2f(p[i].pos_current.x-p[i].r, p[i].pos_current.y+p[i].r));
    c.append(Vector2f(p[i].pos_current.x+p[i].r, p[i].pos_current.y+p[i].r));
    
    c[i*6+0].texCoords = Vector2f(0, 0);
    c[i*6+1].texCoords = Vector2f(1000, 0);
    c[i*6+2].texCoords = Vector2f(1000, 1000);

    c[i*6+3].texCoords = Vector2f(0, 0);
    c[i*6+4].texCoords = Vector2f(0, 1000);
    c[i*6+5].texCoords = Vector2f(1000, 1000);
    
    c[i*6+0].color = Color(224, 191, 184);
    c[i*6+1].color = Color(224, 191, 184);
    c[i*6+2].color = Color(224, 191, 184);

    c[i*6+3].color = Color(224, 191, 184);
    c[i*6+4].color = Color(224, 191, 184);
    c[i*6+5].color = Color(224, 191, 184);
}

void init_circles(point nP, vector<point> &p, VertexArray &c, int n){
    
    if (!texture.loadFromFile("images/circle.png")){
        cout<<"Erreur lors de la récupération de la texture"<<endl;
    }
    
    for(int i=0; i<n; i++){
        newCircle(nP, p, c, i);
        float d = rand()%400;
        float teta = rand()%314/100;
        p[i].pos_current = {960+d*cos(teta), 540+d*sin(teta)};
        p[i].pos_old = p[i].pos_current;
        p[i].r = 10;
    }

}

void init_text(Text &text){
    
    font.loadFromFile("fonts/arial.ttf");

    text.setFont(font); // font is a sf::Font
    text.setString("Hello world");
    text.setCharacterSize(100); // in pixels, not points!
    text.setFillColor(sf::Color::White);
    text.setPosition(Vector2f(200, 100));
}

void input(vector<point> &player, double dt){
    while(window.pollEvent(event)){
        if((event.key.code == Keyboard::Escape && fullscreen)) {
            window.close();
		}
        if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Space)) {
            pause = !pause;
		}
        //for(int i=0; i<player.size(); i++){
        //    player[i].follow = false;
        //    if(Mouse::isButtonPressed(Mouse::Left)){
        //        if(dist(player[i].x, player[i].y, mouse.getPosition().x, mouse.getPosition().y) < player[i].r){
        //            player[i].follow = true;
        //            player[i].x = mouse.getPosition().x;
        //            player[i].y = mouse.getPosition().y;
        //            player[i].vx = (player[i].x-player[i].pre[0])/dt;
        //            player[i].vy = (player[i].y-player[i].pre[1])/dt;
        //            player[i].v = sqrt(player[i].vx*player[i].vx+player[i].vy*player[i].vy);
        //            player[i].theta = atan2(player[i].vy, player[i].vx);
        //            player[i].pre[0] = player[i].x;
        //            player[i].pre[1] = player[i].y;
        //        }
        //    }
        //}
        if( event.type == Event::MouseButtonReleased){
            int i=player.size()-1;
            newCircle(newPlayer, player, circles, i);
            float d = rand()%400;
            float teta = rand()%314/100;
            player[i].pos_current = {960+d*cos(teta), 540+d*sin(teta)};
            player[i].pos_old = player[i].pos_current;
            player[i].r = 10;
        }
        if(event.type == Event::Closed){
            window.close();
        }
    }

    window.clear(Color(100, 100, 100, 255));
}