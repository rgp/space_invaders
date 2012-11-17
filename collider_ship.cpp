#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "collider_ship.h"

ColliderShip::ColliderShip(BulletObserver* bulletObserver, Ship* ship){
  this->bulletObserver = bulletObserver;
  this->ship = ship;
}

int ColliderShip::checkForCollisions(){
  int score = 0;
  BulletNode* previous = NULL;
  BulletNode* current = this->bulletObserver->bulletList;

  while(current != NULL){
    if(ship->collided(current->bullet->x, current->bullet->y)){
      score += 10;
      if( previous == NULL)
       this->bulletObserver->bulletList = current->next;
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

