class Enemies : public Element{
  public:
    Enemies(double xx, double xy, double xwidth, double xheight):Element(xx,xy,xwidth,xheight) {}

    int alive[8][4];
    int direction;
    void generate();
    void draw_one();
    void draw();
    void update();
    bool collided(double,double);
};
