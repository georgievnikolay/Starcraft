// #include <stdlib.h>
// #include "BattleField.h"
// #include "Defines.h"
#include "Ships.h"

void generateTerranFleet(BattleField *battleField, const char *terranFleetStr)
{
  vectorInit(&battleField->terranFleet, strlen(terranFleetStr));

  TerranShips *terranFleet = malloc(strlen(terranFleetStr) * sizeof(TerranShips));

  size_t i;
  for (i = 0; i < strlen(terranFleetStr); i++) {
    if (terranFleetStr[i] == BATTLE_CRUSER) {
      initBattleCruser(&terranFleet[i]);
    }
    if (terranFleetStr[i] == VIKING) {
      initViking(&terranFleet[i]);
    }

    vectorPush(&battleField->terranFleet, &(terranFleet[i]));
  }
}

void generateProtossFleet(BattleField *battleField, const char *protossFleetStr)
{
  vectorInit(&battleField->protossFleet, strlen(protossFleetStr));

  ProtossShips *protossFleet = malloc(strlen(protossFleetStr) * sizeof(ProtossShips));

  size_t i;
  for (i = 0; i < strlen(protossFleetStr); i++) {
    if (protossFleetStr[i] == CARRIER) {
      initCarrier(&protossFleet[i]);
    }
    if (protossFleetStr[i] == PHOENIX) {
      initPhoenix(&protossFleet[i]);
    }

    vectorPush(&battleField->protossFleet, &(protossFleet[i]));
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
  free(&battleField->protossFleet);
  free(&battleField->terranFleet);
  vectorFree(&battleField->protossFleet);
  vectorFree(&battleField->terranFleet);
}

bool processTerranTurn(BattleField *battleField)
{
  /*from global to static*/
  static int numberOfTurns = 1;

  int lastProtosShipIndx;
  ProtossShips *currentProtossShip;
  TerranShips *currentTerranShip;

  size_t i;
  for (i = 0; i < vectorGetSize(&battleField->terranFleet); i++)
  {
    lastProtosShipIndx = vectorGetSize(&battleField->protossFleet) - 1;

    currentTerranShip = vectorGet(&battleField->terranFleet, i);
    currentProtossShip = vectorBack(&battleField->protossFleet);
    
    /*go into functions*/
    if (checkShipName(currentTerranShip->shipType, "Viking")) {
      vikingAttack(currentTerranShip, currentProtossShip);
    }
    if (checkShipName(currentTerranShip->shipType, "BattleCruser")) {
      battleCruserAttack(currentTerranShip, currentProtossShip, numberOfTurns);
    }

    substractShieldDamage(currentProtossShip);

    if (currentProtossShip->health <= 0) {
      printf("%s with ID: %d killed enemy airship with ID: %d\n", currentTerranShip->shipType, i, lastProtosShipIndx);
      /*destry ship function ii*/
      vectorPop(&battleField->protossFleet);
      lastProtosShipIndx = vectorGetSize(&battleField->protossFleet) - 1;
      currentProtossShip = vectorBack(&battleField->protossFleet);
    }
    
    if (vectorIsEmpty(&battleField->protossFleet)) {
      return true;
    }
  }

  numberOfTurns++;
  printf("Last Protoss AirShip with ID: %d has %d health and %d shield left\n", lastProtosShipIndx, currentProtossShip->health, currentProtossShip->shield);

  return false;
}

bool processProtossTurn(BattleField *battleField)
{
  int LastTerranShipIndx;
  ProtossShips *currentProtossShip;
  TerranShips *currentTerranShip;

  size_t i;
  for (i = 0; i < vectorGetSize(&battleField->protossFleet); i++)
  {
    LastTerranShipIndx = vectorGetSize(&battleField->terranFleet) - 1;

    currentProtossShip = vectorGet(&battleField->protossFleet, i);
    currentTerranShip = vectorBack(&battleField->terranFleet);
    
    if (checkShipName(currentProtossShip->shipType, "Carrier"))
    {
      int j;
      for (j = 0; j < carrierInterceptorsStatus(currentProtossShip); j++)
      {
        /*function i*/
        currentTerranShip->health -= currentProtossShip->damage;

        if (currentTerranShip->health <= 0)
        {
          printf("%s with ID: %d killed enemy airship with ID: %d\n", currentProtossShip->shipType, i, LastTerranShipIndx);
          /*destry ship function ii*/
          vectorPop(&battleField->terranFleet);
          LastTerranShipIndx = vectorGetSize(&battleField->terranFleet) - 1;
          currentTerranShip = vectorBack(&battleField->terranFleet);
          
          if(vectorIsEmpty(&battleField->terranFleet)){
            return true;
          }
        }
      }
    } 
    if(checkShipName(currentProtossShip->shipType, "Phoenix")) {
      currentTerranShip->health -= currentProtossShip->damage;

      if(currentTerranShip->health <= 0) {
        /*destry ship function ii*/
        vectorPop(&battleField->terranFleet);
        printf("%s with ID: %d killed enemy airship with ID: %d\n", currentProtossShip->shipType, i, LastTerranShipIndx);
        LastTerranShipIndx = vectorGetSize(&battleField->terranFleet) - 1;
        currentTerranShip = vectorBack(&battleField->terranFleet);
      }   
    }

    if(vectorIsEmpty(&battleField->terranFleet)){
      return true;
    }
  }

  if (checkShipName(currentProtossShip->shipType, "Carrier")) {
    shieldRegen(currentProtossShip, CARRIER_SHIELD, CARRIER_SHIELD_REGENERATE_RATE);
  }
  if (checkShipName(currentProtossShip->shipType, "Phoenix")) {
    shieldRegen(currentProtossShip, PHOENIX_SHIELD, PHOENIX_SHIELD_REGENERATE_RATE);
  }

  printf("Last Terran AirShip with ID: %d has %d health left\n", LastTerranShipIndx, currentTerranShip->health);
  return false;
}
