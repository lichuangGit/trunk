#include "StarParticle.h"
#include "Star.h"
#include "Data/Const.h"

void showEffect(int color, Vec2 position, Node* node)
{
	ParticleExplosion *effect = ParticleExplosion::create();
	effect->setTexture(Director::getInstance()->getTextureCache()->addImage(getColorImage(color)));
	effect->setAutoRemoveOnFinish(true);
	effect->setTotalParticles(1300);
	effect->setStartSize(18.0f);
	effect->setGravity(Point(0, -400));
	effect->setLife(0.6f);
	effect->setSpeed(250);
	effect->setSpeedVar(10);
	effect->setPosition(position);
	node->addChild(effect);
}

void showStarParticleEffect(int color, Point position, Node* node) 
{
	ParticleExplosion* effect = ParticleExplosion::create();
	effect->setAutoRemoveOnFinish(true);
	effect->setTexture(((ParticleBatchNode*)node)->getTexture());
	effect->setTotalParticles(1300);
	//effect->setStartColor(getColor4F(color));
	//effect->setEndColor(getColor4F(color));
	effect->setStartSize(18.0f);
	effect->setGravity(Point(0, -400));
	effect->setLife(0.6f);
	effect->setSpeed(250);
	effect->setSpeedVar(10);
	effect->setPosition(position);
	node->addChild(effect);
}

void showCCParticleFireworksEffect(Node* node)
{
	ParticleSystemQuad* effect = ParticleSystemQuad::create("firework_1.plist");
	effect->setAutoRemoveOnFinish(true);
	effect->setTotalParticles(300);
	effect->setPosition(Point(120, VISIBLE_SIZE.height));
	node->addChild(effect);

	ParticleSystemQuad* effect2 = ParticleSystemQuad::create("firework_1.plist");
	effect2->setAutoRemoveOnFinish(true);
	effect2->setTotalParticles(300);
	effect2->setPosition(Point(420, 800));
	node->addChild(effect2);

	ParticleSystemQuad* effect3 = ParticleSystemQuad::create("firework_1.plist");
	effect3->setAutoRemoveOnFinish(true);
	effect3->setTotalParticles(300);
	effect3->setPosition(Point(150, 400));
	node->addChild(effect3);

	ParticleSystemQuad* effect4 = ParticleSystemQuad::create("firework_1.plist");
	effect4->setAutoRemoveOnFinish(true);
	effect4->setTotalParticles(300);
	effect4->setPosition(Point(450, 350));
	node->addChild(effect4);
}

string getColorImage(int color) 
{
	switch (color) 
	{
	case Star::Color::PURPLE:
		return "purple_bum.png";
	case Star::Color::BLUE:
		return "blue_bum.png";
	case Star::Color::RED:
		return "red_bum.png";
	case Star::Color::YELLOW:
		return "orange_bum.png";
	case Star::Color::GREEN:
		return "green_bum.png";
	case  DIAMOND:
		return "zuanshi_bum.png";
	}
	return "red_bum.png";
}

Color4F getColor4F(int color) 
{
	switch (color) 
	{
	case Star::Color::PURPLE:
		return Color4F(0.74f, 0.30f, 0.99f, 1.0f);
	case Star::Color::BLUE:
		return Color4F(84 / 255.0f, 203 / 255.0f, 254 / 255.0f, 1.0f);
	case Star::Color::RED:
		return Color4F(253 / 255.0f, 80 / 255.0f, 126 / 255.0f, 1.0f);
	case Star::Color::YELLOW:
		return Color4F(253 / 255.0f, 234 / 255.0f, 84 / 255.0f, 1.0f);
	case Star::Color::GREEN:
		return Color4F(132 / 255.0f, 226 / 255.0f, 111 / 255.0f, 1.0f);
	}
	return Color4F(1.0f, 1.0f, 1.0f, 0.0f);
}
