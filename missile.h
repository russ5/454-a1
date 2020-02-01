// Missile class


#ifndef MISSILE_H
#define MISSILE_H


#include "headers.h"
#include "gpuProgram.h"


class Missile {
 public:

  // Constructors

  Missile() {}

  Missile( vec3 p, vec3 v, float y, vec3 c ) {
    pos0 = p;
    pos1 = p;
    velocity = v;
    colour = c;
    destY = y;
  }

  // Draw the missile and its trail

  void draw( GPUProgram *gpuProgram) {

    vec3 verts[2] = {
      vec3( pos0.x, pos0.y, 0 ),
      vec3( pos1.x, pos1.y, 0 )
    };

    gpuProgram->drawVertices( &verts[0], 2, GL_LINES, colour );
  }

  // Move the missile over a time interval, deltaT

  void move( float deltaT ) {
    pos1 = pos1 + deltaT * velocity;
  }

  // Return the current position 

  vec3 position() {
    return pos1;
  }

  // Has the missile reached its destination?

  bool hasReachedDestination(bool incoming) {
    return (pos1.x > 1 || pos1.y > 1 || pos1.x < 0 || pos1.y < 0 ||  // hit edges of world
			(abs(pos1.y - destY) < 0.01) ||  // missile is at destination (within 1%)
			(incoming&&(pos1.y<0.04)&&(
            ((pos1.x>0.075||pos1.x<0.125)&&silos[0].intact())||
            ((pos1.x>0.175||pos1.x<0.225)&&cities[0].intact())||
            ((pos1.x>0.275||pos1.x<0.325)&&cities[1].intact())||
            ((pos1.x>0.375||pos1.x<0.425)&&cities[2].intact())||
            ((pos1.x>0.475||pos1.x<0.525)&&silos[1].intact())||
            ((pos1.x>0.575||pos1.x<0.625)&&cities[3].intact())||
            ((pos1.x>0.675||pos1.x<0.725)&&cities[4].intact())||
            ((pos1.x>0.775||pos1.x<0.825)&&cities[5].intact())||
            ((pos1.x>0.875||pos1.x<0.925)&&silos[2].intact())))  // missile at city or silo
    );
  }

 private:

  vec3  pos0;			// start position
  vec3  pos1;			// current position
  vec3  velocity;		// velocity
  vec3  colour;			// colour of missile trail
  float destY;			// y position at destination
};


#endif
