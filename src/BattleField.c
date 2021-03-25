#include <stdlib.h>
#include "BattleField.h"
#include "Defines.h"

void generateTerranFleet(BattleField *battleField, const char *terranFleetStr)
{
  vectorInit(&battleField->terranFleet, strlen(terranFleetStr));

  /*Allocating memory for terrans fleet so we can initialize it and push it in the vector since it holds a pointer to a pointer*/
  /*To free the memory*/
  TerranShips *terranFleet = malloc(strlen(terranFleetStr) * sizeof(TerranShips));
  TerranShips *temp;

  size_t i;
  for (i = 0; i < strlen(terranFleetStr); i++)
  {
    if (terranFleetStr[i] == VIKING)
    {
      terranFleet[i].damage = VIKING_DAMAGE;
      terranFleet[i].health = VIKING_HEALTH;
      vectorPush(&battleField->terranFleet, &(terranFleet[i]));
    }
    else if (terranFleetStr[i] == BATTLE_CRUSER)
    {
      terranFleet[i].damage = BATTLE_CRUSER_DAMAGE;
      terranFleet[i].health = BATTLE_CRUSER_HEALTH;
      vectorPush(&battleField->terranFleet, &(terranFleet[i]));
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
  vectorInit(&battleField->protossFleet, strlen(protossFleetStr));

  ProtossShips *protossFleet = malloc(strlen(protossFleetStr) * sizeof(ProtossShips));
  ProtossShips *temp;

  size_t i;
  for (i = 0; i < strlen(protossFleetStr); i++)
  {
    if (protossFleetStr[i] == PHOENIX)
    {
      protossFleet[i].shield = PHOENIX_SHIELD;
      protossFleet[i].shieldRegen = PHOENIX_SHIELD_REGENERATE_RATE;
      protossFleet[i].health = PHOENIX_HEALTH;
      protossFleet[i].damage = PHOENIX_DAMAGE;
      vectorPush(&battleField->protossFleet, &(protossFleet[i]));
    } 
    else if (protossFleetStr[i] == CARRIER)
    {
      protossFleet[i].damage = CARRIER_DAMAGE;
      protossFleet[i].health = CARRIER_HEALTH;
      protossFleet[i].shield = CARRIER_SHIELD;
      protossFleet[i].shieldRegen = CARRIER_SHIELD_REGENERATE_RATE;
      vectorPush(&battleField->protossFleet, &(protossFleet[i]));
    }
  }

  for (i = 0; i < vectorGetSize(&battleField->protossFleet); i++)
  {
    temp = vectorGet(&battleField->protossFleet, i);
    printf("%d %d %d %d\n", temp->damage, temp->health, temp->shield, temp->shieldRegen);
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
