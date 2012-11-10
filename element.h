class Element{

  public:
  double x;
  double y;
  double width;
  double height;
  Element(double, double, double, double);
  bool collided(double, double);
  void translateX(double);
  void translateY(double);
  double getVector();
  void draw();
};

//class Enemy : public Element{
//boolean alive;
//int points;

//public:
//int getPoints();
//boolean isAlive();
//void die();
//}


//class Ship : public Element{
//int lives;
//int points;

//public:
//int getPoints();
//void addPoints(int);
//void removeLife();
//void addLife();
//}

//class Laser : public Element{
//}
