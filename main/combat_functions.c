#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include"combat_functions.h"

#define UNIT_SIZE 1000

#define negative_to_zero(i) (i < 0 ? 0 : i)

int dice_roll(int startNum, int endNum) {
	return rand() % (endNum - startNum) + 1;
}

int unit_pips(int roll, int leader, int targetLeader, int attackPips, int targetPips, int terrain) { //fire - shock phase
	return (roll + negative_to_zero(leader - targetLeader) + attackPips - targetPips - terrain);
}

float casualty_multiplier(int strength, float damage, float tactics, float combatAblity, float discipline, int round) {
	return ((strength / UNIT_SIZE) * (damage / tactics) * (1 + combatAblity) * (1 + discipline) * (1 + round / 100));
}

float morale_casualties(int pips, float multiplier, float maxMorale, float reserveDamage) {
	return ((15 + 5 * pips) * multiplier * (maxMorale / 540) + (0.03 * (1 - reserveDamage)));
}

float strength_casualties(int pips, float multiplier, float damageModifier, float damageReceived) {
	return ((15 + 5 * pips) * multiplier * (1 + damageModifier) * (1 + damageReceived));
}