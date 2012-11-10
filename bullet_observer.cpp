#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include  "bullet_observer.h"

BulletObserver::BulletObserver() { 
  this->bullet = NULL;
}

void BulletObserver::addBullet(Bullet* bullet){
  this->bullet = bullet;
}
void BulletObserver::draw(){
  if(this->bullet != NULL){
    this->bullet->draw();
  }
}

void BulletObserver::update(){
  if(this->bullet != NULL)
    this->bullet->translateY(1);
}

