class Bullet : public Element{
  public:
  Bullet(double xx, double xy, double xwidth, double xheight):Element(xx,xy,xwidth,xheight) {}
  Bullet(double xx, double xy):Element(xx,xy,0.01,0.1) {}
};
