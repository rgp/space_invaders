#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "collider.h"

Collider::Collider(BulletObserver* bulletObserver, Enemies* enemies){
  this->bulletObserver = bulletObserver;
  this->enemies = enemies;
}

int Collider::checkForCollisions(){
  int score = 0;
  BulletNode* previous = NULL;
  BulletNode* current = bulletObserver->bulletList;

  while(current != NULL){
    if(enemies->collided(current->bullet->x, current->bullet->y)){
      score += 10;
      if( previous == NULL)
       bulletObserver->bulletList = current->next;
      else{
        current = current -> next;
        previous->next = current;
      }
    }
    previous = current;
    if(current != NULL)
      current = current -> next;
  }

  return score;
}

