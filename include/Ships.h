#ifndef SHIPS_H_
#define SHIPS_H_

#include <stdlib.h>
#include "BattleField.h"
#include "Defines.h"

bool checkShipName(const char* shipType, const char* name);

void initViking(TerranShips *ship);
void initBattleCruser(TerranShips *ship);
void initCarrier(ProtossShips *ship);
void initPhoenix(ProtossShips *ship);

void vikingAttack(TerranShips *attacker, ProtossShips *enemy);
void battleCruserAttack(TerranShips *attacker, ProtossShips *enemy, int turnCount);

void substractShieldDamage(ProtossShips *ship);
void shieldRegen(ProtossShips *ship, int maxShield, int regenRate);
int carrierInterceptorsStatus(ProtossShips* carrier);

void destroyedTerranShip(Vector *vec, TerranShips **enemy, int *enemyId );
void destroyedProtossShip(Vector *vec, ProtossShips **enemy, int *enemyId );

#endif /* SHIPS_H_ */