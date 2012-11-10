class BulletObserver{

  public:
  BulletNode* bulletList;

  BulletObserver();
  void update();
  void addBullet(Bullet*);
  void draw();
};
