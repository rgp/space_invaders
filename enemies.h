class Enemies : public Element{
  public:
    Enemies(double xx, double xy, double xwidth, double xheight):Element(xx,xy,xwidth,xheight) {}

    int alive[4][8];
    double direction;
    int padding;
    void generate();
    void draw_one();
    void draw();
    void update();
    int getIndexX(double);
    int getIndexY(double);
    bool collided(double,double);
    Bullet* shoot();
  private:
    Bullet* generateBullet(int,int);
};
