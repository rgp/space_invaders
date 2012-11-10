class BulletObserver{

  public:
  Bullet* bullet;

  BulletObserver();
  void update();
  void addBullet(Bullet*);
  void draw();
};
