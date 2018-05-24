#include <iostream>

#include "Tests.h"
#include "Unit.h"
#include "TestObservers.h"
#include "FairDice.h"
#include "Weapon.h"
#include "Swords.h"

bool test::runUnitTest() {
	DmgObserver o1 = DmgObserver();
	ExpObserver o2 = ExpObserver();
	FairDice<100> d;

	Unit mia("Mia", d, AttributeList({ 5, 0, 8, 10, 19, 4, 6, 1 }));
	Unit ike("Ike", d, AttributeList({ 5, 1, 6, 7, 19, 5, 5, 0 }));
	mia.attach(o1);
	ike.attach(o1);
	mia.attach(o2);
	ike.attach(o2);

	std::unique_ptr<Weapon> mias_sword = std::make_unique<BronzeSword>();
	std::unique_ptr<Weapon> ikes_sword = std::make_unique<BronzeSword>();

	mia.getInventory().equip(ON_HAND, std::move(mias_sword));
	ike.getInventory().add(std::move(ikes_sword));
	ike.getInventory().equip(ON_HAND, 0);

	std::cout << "Ike:" << std::endl << "\tHit: " << ike.getStats().hit() << "\tAvo: " << ike.getStats().avoid() << std::endl;
	std::cout << "Mia:" << std::endl << "\tHit: " << mia.getStats().hit() << "\tAvo: " << mia.getStats().avoid() << std::endl;

	mia.getCombat().combat(ike);
	return true;
}
