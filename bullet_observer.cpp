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
  if(bullet != NULL){
    if(this->bulletList == NULL)
      this->setBullet(bullet);
    else
      this->bulletList->add(bullet);
  }
}

void BulletObserver::setBullet(Bullet* bullet){
  if(bullet != NULL)
    this->bulletList = new BulletNode(bullet);
}

void BulletObserver::draw(){
  BulletNode *node = this->bulletList;
  while(node != NULL){
    if(node->bullet->y > 25)
      this->bulletList = NULL;
    else
      node->bullet->draw();
    node = node->next;
  }
}

void BulletObserver::update(int n){
  BulletNode *node = this->bulletList;
  while(node != NULL){
    node->bullet->translateY(n);
    node = node->next;
  }
}

bool BulletObserver::isEmpty(){
  return (this->bulletList == NULL);
}
