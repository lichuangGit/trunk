#ifndef _STAR_PARTICLE_H_
#define _STAR_PARTICLE_H_

#include "cocos2d.h"
#include <string>

using namespace std;
USING_NS_CC;

void showEffect(int color, Point position, Node* node);
void showStarParticleEffect(int color,Point position,Node* node);
Color4F getColor4F(int color);
string getColorImage(int color);
void showCCParticleFireworksEffect(Node* node);

#endif
