// A Silo


#ifndef SILO_H
#define SILO_H

#include "headers.h"
#include "gpuProgram.h"
#include "buildings.h"


class Silo : public Building {
 public:

  // Constructors 

  Silo() {}

  Silo( vec3 pos ) : Building( pos ) {

    roundsLeft = 15;
    intact = true;
  }

  bool canShoot() {
    return (roundsLeft > 0 && intact);
  }

  bool isIntact() {
    return intact;
  }

  void destroy() {
    intact = false;
  }

  void decrMissiles() {
    roundsLeft--;
  }

  vec3 position() {
    return pos;
  }

  int rounds() {
    return roundsLeft;
  }


  // Draw the silo

  void draw( GPUProgram *gpuProgram ) {
    if (!intact) return;
    const int NUM_SEGMENTS = 45; // number of pieces of hemisphere perimeter

    vec3 *verts = new vec3[NUM_SEGMENTS+1];

    verts[0] = pos;
    
    for (int i=0; i<NUM_SEGMENTS; i++) {
      float theta = (i/(float)(NUM_SEGMENTS-1)) * M_PI;
      verts[i+1] = vec3( pos.x + 0.04 * cos(theta), pos.y + 0.04 * sin(theta), 0 );
    }

    gpuProgram->drawVertices( verts, NUM_SEGMENTS+1, GL_TRIANGLE_FAN, vec3(1,1,1) );

    delete [] verts;
  }

  bool isHit( vec3 explosionPos ) {
    return explosionPos.y<0.05 && (explosionPos.x > (pos.x - 0.025) && explosionPos.x < (pos.x + 0.025));
  }

 private:

  int roundsLeft;
  bool intact;
};
  

#endif
