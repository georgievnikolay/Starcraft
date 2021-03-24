#ifndef BATTLEFIELD_H_
#define BATTLEFIELD_H_

#include <stdbool.h>
#include <stdio.h>
#include "Vector.h"
#include <string.h>
typedef struct {
  Vector terranFleet;
  Vector protossFleet;
} BattleField;

typedef struct
{
  int health; 
  int ability;
  int damage;
} TerranShips;

typedef struct
{

  int health;
  int shield;
  int ability;
  int ability2;
  int damage;

} ProtosShips;
void generateTerranFleet(BattleField *battleField, const char *terranFleetStr);
void generateProtossFleet(BattleField *battleField, const char *protossFleetStr);

void startBattle(BattleField *battleField);

void deinit(BattleField *battleField);

bool processTerranTurn(BattleField *battleField);
bool processProtossTurn(BattleField *battleField);

#endif /* BATTLEFIELD_H_ */
