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
    this->bulletList = new BulletNode(bullet);
}

void BulletObserver::draw(){
  BulletNode *node = this->bulletList;
  while(node != NULL){
    if(node->bullet->y > 100)
      this->bulletList =NULL;
    else
    node->bullet->draw();
    node = node->next;
  }
}

void BulletObserver::update(){
  BulletNode *node = this->bulletList;
  while(node != NULL){
    node->bullet->translateY(5);
    node = node->next;
  }
}

