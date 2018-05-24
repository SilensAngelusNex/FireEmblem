#include "WeaponList.h"

#include <iostream>

namespace Weapon_Advantages {
	enum matchup { adv = 1, neu = 0, dis = -1 };
	//				 SWD, AXE, LNC, KNF, BOW, ETH, AIR, FIR, WTR, LGT, DRK
	WeaponList swd({ neu, adv, dis, adv, dis, neu, neu, neu, neu, neu, neu });
	WeaponList axe({ dis, neu, adv, neu, adv, dis, dis, dis, dis, dis, dis });
	WeaponList lnc({ adv, dis, neu, dis, neu, adv, adv, adv, adv, adv, adv });
	WeaponList knf({ dis, neu, adv, neu, dis, adv, adv, adv, adv, adv, adv });
	WeaponList bow({ adv, dis, neu, adv, neu, dis, dis, dis, dis, dis, dis });
	WeaponList eth({ neu, adv, dis, dis, adv, neu, dis, neu, adv, adv, dis });
	WeaponList air({ neu, adv, dis, dis, adv, adv, neu, dis, neu, adv, dis });
	WeaponList fir({ neu, adv, dis, dis, adv, neu, adv, neu, dis, adv, dis });
	WeaponList wtr({ neu, adv, dis, dis, adv, dis, neu, adv, neu, adv, dis });
	WeaponList lgt({ neu, adv, dis, dis, adv, dis, dis, dis, dis, neu, adv });
	WeaponList drk({ neu, adv, dis, dis, adv, adv, adv, adv, adv, dis, neu });

	std::array<WeaponList, WeaponType::size> matchups = { swd, axe, lnc, knf, bow, eth, air, fir, wtr, lgt, drk };
}

int compare(WeaponType lhs, WeaponType rhs) {
	return Weapon_Advantages::matchups[lhs.pos()][rhs];
}

bool operator<(WeaponType lhs, WeaponType rhs) {
	return compare(lhs, rhs) < 0;
}

bool operator>(WeaponType lhs, WeaponType rhs) {
	return compare(lhs, rhs) > 0;
}


bool runWeaponListTests() {
	bool result = true;
	for (WeaponType lhs : WeaponType::list) {
		for (WeaponType rhs : WeaponType::list) {
			bool test = compare(lhs, rhs) == -compare(rhs, lhs);
			result &= test;
		}
	}
	return result;
}