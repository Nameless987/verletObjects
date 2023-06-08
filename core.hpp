void animation(vector<point> player, VertexArray &circles, int i){
    circles[i*6+0].position = Vector2f(player[i].pos_current.x-player[i].r, player[i].pos_current.y-player[i].r);
    circles[i*6+1].position = Vector2f(player[i].pos_current.x+player[i].r, player[i].pos_current.y-player[i].r);
    circles[i*6+2].position = Vector2f(player[i].pos_current.x+player[i].r, player[i].pos_current.y+player[i].r);
    circles[i*6+3].position = Vector2f(player[i].pos_current.x-player[i].r, player[i].pos_current.y-player[i].r);
    circles[i*6+4].position = Vector2f(player[i].pos_current.x-player[i].r, player[i].pos_current.y+player[i].r);
    circles[i*6+5].position = Vector2f(player[i].pos_current.x+player[i].r, player[i].pos_current.y+player[i].r);
}