class Collider{
  public:
  BulletObserver* bulletObserver;
  Enemies* enemies;
  Collider(BulletObserver*, Enemies*);
  int checkForCollisions();
};
