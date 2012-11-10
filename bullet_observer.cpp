#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include  "bullet_observer.h"

BulletObserver::BulletObserver() { 
  this->bulletList = NULL;
}

void BulletObserver::addBullet(Bullet* bullet){
  if(this->bulletList == NULL)
    this->bulletList = new BulletNode();
  this->bulletList->add(bullet);
}

void BulletObserver::draw(){
  BulletNode *node = this->bulletList;
  while(node != NULL){
    node->bullet->draw();
    node = node->next;
  }
}

void BulletObserver::update(){
  BulletNode *node = this->bulletList;
  while(node != NULL){
    node->bullet->translateY(1);
    node = node->next;
  }
}

