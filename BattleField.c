#include <stdlib.h>
#include "BattleField.h"
#include "Defines.h"

TerranShips viking = {.health = VIKING_HEALTH, .damage = VIKING_DAMAGE};
TerranShips cruser = {.health = BATTLE_CRUSER_HEALTH, .damage = BATTLE_CRUSER_DAMAGE};
ProtosShips phoenix = {.health = PHOENIX_HEALTH, .damage = PHOENIX_DAMAGE, .shield = PHOENIX_SHIELD};
ProtosShips carrier = {.health = CARRIER_HEALTH, .damage = CARRIER_DAMAGE, .shield = CARRIER_SHIELD};
void generateTerranFleet(BattleField *battleField, const char *terranFleetStr)
{
  int i;
  TerranShips *temp;
  vectorInit(&battleField->terranFleet, 50, sizeof(TerranShips));

  for (i = 0; i < strlen(terranFleetStr); i++)
  {
    if (terranFleetStr[i] == 'v')
    {
      vectorPush(&battleField->terranFleet, &viking);
    }
    else if (terranFleetStr[i] == 'b')
    {
      vectorPush(&battleField->terranFleet, &cruser);
    }
  }

  for (i = 0; i < vectorGetSize(&battleField->terranFleet); i++)
  {
    temp = vectorGet(&battleField->terranFleet, i);
    printf("%d %d\n", temp->damage, temp->health);
  }
}

void generateProtossFleet(BattleField *battleField, const char *protossFleetStr)
{
  int i;
  ProtosShips *temp;
  vectorInit(&battleField->protossFleet, 50, sizeof(ProtosShips));
  for (i = 0; i < strlen(protossFleetStr); i++)
  {
    if (protossFleetStr[i] == 'p')
    {
      vectorPush(&battleField->protossFleet, &phoenix);
    }
    else if (protossFleetStr[i] == 'c')
    {
      vectorPush(&battleField->protossFleet, &carrier);
    }
  }
  for (i = 0; i < vectorGetSize(&battleField->protossFleet); i++)
  {
    temp = vectorGet(&battleField->protossFleet, i);
    printf("%d %d %d\n", temp->damage, temp->health, temp->shield);
  }
}

void startBattle(BattleField *battleField)
{
  while (true)
  {
    if (processTerranTurn(battleField))
    {
      printf("TERRAN has won!\n");
      break;
    }

    if (processProtossTurn(battleField))
    {
      printf("PROTOSS has won!\n");
      break;
    }
  }
}

void deinit(BattleField *battleField)
{
}

bool processTerranTurn(BattleField *battleField)
{
  return false;
}

bool processProtossTurn(BattleField *battleField)
{
  return false;
}
