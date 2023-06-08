using namespace std;
using namespace sf;

class point{
public:
    Vector2f pos_current;
    Vector2f pos_old;
    Vector2f velocity = {0, 1};
    Vector2f acc;

    float r;

    bool follow = false;

    //integration de Verlet

    void move(float dt){
        velocity = pos_current-pos_old;
        pos_old=pos_current;

        pos_current = pos_current+velocity+acc*dt*dt;

        acc = {0, 0};

    }

    void accelerate(Vector2f a){
        acc = acc+a;
    }
    
    ////

    void applyConstraints(Vector2f p, float R){
        float d = dist(p.x, p.y, pos_current.x, pos_current.y);
        if(d>(R-r)){
            Vector2f n = (pos_current-p)/d;
            pos_current = p+n*(R-r);
        }
    }

    void collide(point &obj, float d){
        Vector2f n = (pos_current-obj.pos_current)/d;
        float delta = (r+obj.r)-d;
        pos_current += 0.5f*delta*n;
        obj.pos_current -= 0.5f*delta*n;
    }
};