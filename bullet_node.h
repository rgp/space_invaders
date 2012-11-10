class BulletNode{
  public:
  Bullet* bullet;
  BulletNode* next;

  BulletNode(Bullet*);
  BulletNode();
  void add(Bullet*);
};
