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
