#include <stdlib.h>
#include "BattleField.h"
#include "Defines.h"
int numberOfTurns = 1;
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
    if (terranFleetStr[i] == 'b')
    {
      terranFleet[i].damage = BATTLE_CRUSER_DAMAGE;
      terranFleet[i].health = BATTLE_CRUSER_HEALTH;
      strcpy(terranFleet[i].shipType, "BattleCruser");
    }
    if (terranFleetStr[i] == 'v')
    {
      terranFleet[i].damage = VIKING_DAMAGE;
      terranFleet[i].health = VIKING_HEALTH;
      strcpy(terranFleet[i].shipType, "Viking");
    }

    vectorPush(&battleField->terranFleet, &(terranFleet[i]));
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

    if (protossFleetStr[i] == 'c')
    {
      protossFleet[i].damage = CARRIER_DAMAGE;
      protossFleet[i].health = CARRIER_HEALTH;
      protossFleet[i].shield = CARRIER_SHIELD;
      protossFleet[i].shieldRegen = CARRIER_SHIELD_REGENERATE_RATE;
      strcpy(protossFleet[i].shipType, "Carrier");
    }
    if (protossFleetStr[i] == 'p')
    {
      protossFleet[i].shield = PHOENIX_SHIELD;
      protossFleet[i].shieldRegen = PHOENIX_SHIELD_REGENERATE_RATE;
      protossFleet[i].health = PHOENIX_HEALTH;
      protossFleet[i].damage = PHOENIX_DAMAGE;
      strcpy(protossFleet[i].shipType, "Phoenix");
    }

    vectorPush(&battleField->protossFleet, &(protossFleet[i]));
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
  size_t i;
  int lastProtosShip;
  ProtossShips *currentProtossShip;
  TerranShips *currentTerranShip;
  for (i = 0; i < vectorGetSize(&battleField->terranFleet); i++)
  {
    lastProtosShip = vectorGetSize(&battleField->protossFleet) - 1;
    currentTerranShip = vectorGet(&battleField->terranFleet, i);
    currentProtossShip = vectorGet(&battleField->protossFleet, lastProtosShip);
    if (currentTerranShip->shipType[0] == 'V' && currentProtossShip->shipType[0] == 'P')
    {
      currentProtossShip->shield -= 2 * currentTerranShip->damage;
    }
    else if (currentTerranShip->shipType[0] == 'B' && numberOfTurns % YAMATO_CANNON_LOADING_TURNS == 0)
    {
      currentProtossShip->shield -= 5 * currentTerranShip->damage;
    }
    else
    {
      currentProtossShip->shield -= currentTerranShip->damage;
    }
    if (currentProtossShip->shield < 0)
    {
      currentProtossShip->health += currentProtossShip->shield;
      currentProtossShip->shield = 0;
      if (currentProtossShip->health <= 0)
      {
        printf("%s with ID: %d killed enemy airship with ID: %d\n", currentTerranShip->shipType, i, lastProtosShip);
        vectorPop(&battleField->protossFleet);
      }
    }
    if (vectorGetSize(&battleField->protossFleet) == 0)
    {
      return true; //Terran win
    }
  }
  numberOfTurns++;
  printf("Last Protoss airship with ID: %d has %d health and %d shield left\n", lastProtosShip, currentProtossShip->health, currentProtossShip->shield);
  return false;
}

bool processProtossTurn(BattleField *battleField)
{
  size_t i;
  int LastTerranShip;
  ProtossShips *currentProtossShip;
  TerranShips *currentTerranShip;
  for (i = 0; vectorGetSize(&battleField->protossFleet); i++)
  {
    LastTerranShip = vectorGetSize(&battleField->terranFleet) - 1;
    currentTerranShip = vectorGet(&battleField->terranFleet, LastTerranShip);
    currentProtossShip = vectorGet(&battleField->protossFleet, i);
    if (currentProtossShip->shipType[0] == 'C')
    {
      int interceptorsCount = MAX_INTERCEPTORS;
      if (currentProtossShip->health != CARRIER_HEALTH)
      {
        interceptorsCount = DAMAGED_STATUS_INTERCEPTORS;
      }
      int j;
      for (j = 0; j < interceptorsCount; j++)
      {
        currentTerranShip->health -= currentProtossShip->damage;
        if (currentTerranShip->health <= 0)
        {
          printf("%s with ID: %d killed enemy airship with ID: %d\n", currentProtossShip->shipType, i, LastTerranShip);
          vectorPop(&battleField->terranFleet);
          LastTerranShip = vectorGetSize(&battleField->terranFleet) - 1;
          currentTerranShip = vectorGet(&battleField->terranFleet, LastTerranShip);
        }
      }
    }
    else
    {
      currentTerranShip->health -= currentProtossShip->damage;
      printf("%s with ID: %d killed enemy airship with ID: %d\n", currentProtossShip->shipType, i, LastTerranShip);
      vectorPop(&battleField->terranFleet);
    }
    if (vectorGetSize(&battleField->terranFleet) == 0)
      return true;
  }

  if (currentProtossShip->shipType[0] == 'C')
  {
    currentProtossShip->shield += CARRIER_SHIELD_REGENERATE_RATE;
    if (currentProtossShip->shield > CARRIER_SHIELD)
      currentProtossShip->shield = CARRIER_SHIELD;
  }
  else
  {
    currentProtossShip->shield += PHOENIX_SHIELD_REGENERATE_RATE;
    if (currentProtossShip->shield > PHOENIX_SHIELD)
      currentProtossShip->shield = PHOENIX_SHIELD;
  }

  printf("Last Terran airship with ID: %d has %d health left\n", LastTerranShip, currentTerranShip->health);
  return false;
}
