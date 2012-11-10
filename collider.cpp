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

void Collider::checkForCollisions(){
  BulletNode* previous = NULL;
  BulletNode* current = bulletObserver->bulletList;
  while(current != NULL){
    if(enemies->collided(current->bullet->x, current->bullet->y)){
      printf("TRUE\n");
      if( previous == NULL)
       bulletObserver->bulletList = current->next;
      else{
        current = current -> next;
        previous->next = current;
      }
    }
    previous = current;
    current = current -> next;
  }

}

