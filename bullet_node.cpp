#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include  "bullet_node.h"

BulletNode::BulletNode() { 
  this->bullet = NULL;
  this->next = NULL;
}

BulletNode::BulletNode(Bullet* bullet) { 
  this->bullet = bullet;
  this->next = NULL;
}

void BulletNode::add(Bullet* bullet){
  if(this->bullet == NULL)
    this->bullet = bullet;
  else{
    BulletNode *node = this;
    while(node->next != NULL) node = node->next;
    node->next = new BulletNode(bullet);
  }
}
