class BulletObserver{

  public:
  BulletNode* bulletList;

  BulletObserver();
  void update(int);
  void addBullet(Bullet*);
  void setBullet(Bullet*);
  void draw();
  bool isEmpty();
};
