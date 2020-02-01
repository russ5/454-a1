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

    const float dimmer = 0.5;
    const float dimmest = 0.25;

    vec3 verts[2] = {
      vec3((pos1.x-pos0.x)*0.5, (pos1.y-pos0.y)*0.5, 0 ),
      vec3( pos1.x, pos1.y, 0 )
    };

    gpuProgram->drawVertices( &verts[0], 2, GL_LINES, dimmest * colour );

    vec3 verts[2] = {
      vec3( (pos1.x-pos0.x)*0.3, (pos1.y-pos0.y)*0.3, 0 ),
      vec3( pos1.x, pos1.y, 0 )
    };

    gpuProgram->drawVertices( &verts[0], 2, GL_LINES, dimmer * colour );

    vec3 verts[2] = {
      vec3( (pos1.x-pos0.x)*0.1, (pos1.y-pos0.y)*0.1, 0 ),
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

  bool hasReachedDestination(bool incoming, bool * buildings) {
    return (pos1.x > 1 || pos1.y > 1 || pos1.x < 0 || pos1.y < 0 ||  // hit edges of world
			(abs(pos1.y - destY) < 0.01) ||  // missile is at destination (within 1%)
			(incoming&&(pos1.y<0.04)&&(
            ((pos1.x>0.075||pos1.x<0.125)&&buildings[0])||
            ((pos1.x>0.175||pos1.x<0.225)&&buildings[1])||
            ((pos1.x>0.275||pos1.x<0.325)&&buildings[2])||
            ((pos1.x>0.375||pos1.x<0.425)&&buildings[3])||
            ((pos1.x>0.475||pos1.x<0.525)&&buildings[4])||
            ((pos1.x>0.575||pos1.x<0.625)&&buildings[5])||
            ((pos1.x>0.675||pos1.x<0.725)&&buildings[6])||
            ((pos1.x>0.775||pos1.x<0.825)&&buildings[7])||
            ((pos1.x>0.875||pos1.x<0.925)&&buildings[8])))  // missile at city or silo
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
