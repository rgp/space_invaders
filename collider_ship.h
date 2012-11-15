class ColliderShip{
  public:
  BulletObserver* bulletObserver;
  Ship* ship;
  ColliderShip(BulletObserver*, Ship*);
  int checkForCollisions();
};
