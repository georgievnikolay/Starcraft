#include "Ships.h"

ProtossShips *ptrToProtossFleet;
TerranShips *ptrToTerranFleet;

void generateTerranFleet(BattleField *battleField, const char *terranFleetStr)
{
  vectorInit(&battleField->terranFleet, strlen(terranFleetStr));

  TerranShips *terranFleet = malloc(strlen(terranFleetStr) * sizeof(TerranShips));
  ptrToTerranFleet = terranFleet;

  size_t i;
  for (i = 0; i < strlen(terranFleetStr); i++) {
    switch(terranFleetStr[i]){
      case BATTLE_CRUSER:
        initBattleCruser(&terranFleet[i]);
        break;
      case VIKING:
        initViking(&terranFleet[i]);
        break;
    }

    vectorPush(&battleField->terranFleet, &(terranFleet[i]));
  }
}

void generateProtossFleet(BattleField *battleField, const char *protossFleetStr)
{
  vectorInit(&battleField->protossFleet, strlen(protossFleetStr));

  ProtossShips *protossFleet = malloc(strlen(protossFleetStr) * sizeof(ProtossShips));
  ptrToProtossFleet = protossFleet;

  size_t i;
  for (i = 0; i < strlen(protossFleetStr); i++) {
    switch(protossFleetStr[i]){
      case CARRIER:
        initCarrier(&protossFleet[i]);
        break;
      case PHOENIX:
        initPhoenix(&protossFleet[i]);
        break;
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
  free(ptrToProtossFleet);
  free(ptrToTerranFleet);
  vectorFree(&battleField->protossFleet);
  vectorFree(&battleField->terranFleet);
}

bool processTerranTurn(BattleField *battleField)
{
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
    
    if (checkShipName(currentTerranShip->shipType, "Viking")) {
      vikingAttack(currentTerranShip, currentProtossShip);
    }
    if (checkShipName(currentTerranShip->shipType, "BattleCruser")) {
      battleCruserAttack(currentTerranShip, currentProtossShip, numberOfTurns);
    }

    substractShieldDamage(currentProtossShip);

    if (currentProtossShip->health <= 0) {
      printf("%s with ID: %ld killed enemy airship with ID: %d\n", currentTerranShip->shipType, i, lastProtosShipIndx);
      destroyedProtossShip(&battleField->protossFleet,&currentProtossShip,&lastProtosShipIndx);
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
        currentTerranShip->health -= currentProtossShip->damage;

        if (currentTerranShip->health <= 0)
        {
          printf("%s with ID: %ld killed enemy airship with ID: %d\n", currentProtossShip->shipType, i, LastTerranShipIndx);
          destroyedTerranShip(&battleField->terranFleet,&currentTerranShip,&LastTerranShipIndx);
          
          if(vectorIsEmpty(&battleField->terranFleet)){
            return true;
          }
        }
      }
    } 
    if(checkShipName(currentProtossShip->shipType, "Phoenix")) {
      currentTerranShip->health -= currentProtossShip->damage;

      if(currentTerranShip->health <= 0) {
        printf("%s with ID: %ld killed enemy airship with ID: %d\n", currentProtossShip->shipType, i, LastTerranShipIndx);
        destroyedTerranShip(&battleField->terranFleet,&currentTerranShip,&LastTerranShipIndx);
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
