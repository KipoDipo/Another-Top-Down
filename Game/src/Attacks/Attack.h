#pragma once
#include <SFML/Graphics.hpp>

class Attack : public virtual sf::Drawable
{
public:
	Attack(int speed, float size, float distance, float range, const sf::Texture* texture);
	virtual ~Attack();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	virtual void update(const sf::Vector2f& origin) = 0;
	virtual void attackSequence(const sf::Vector2f& origin) = 0;

	bool getIsAttacking() const;
	int getAttackProgress() const;
	int getAttackSpeed() const;
	float getAttackSize() const;
	float getAttackDistance() const;
	float getAttackRange() const;
	sf::Vector2f getAttackDirection() const;
	const sf::FloatRect& getAttackCollider() const;

protected:
	void setIsAttacking(bool state);
	void setAttackProgress(int progress);
	void addAttackProgress(int plusProgress);
	void setAttackSpeed(int speed);
	void setAttackSize(float size);
	void setAttackDistance(float distance);
	void setAttackRange(float range);
	void setAttackDirection(sf::Vector2f direction);
	void setAttackCollider(const sf::FloatRect& collider);
	void setAttackSpritePosition(sf::Vector2f position);
private:
	bool isAttacking;
	int atkProgress;
	int atkSpeed;
	float atkSize;
	float atkDist;
	float atkRange;
	sf::Vector2f atkDir;
	sf::FloatRect atkCollider;
	sf::Sprite sprite;
};