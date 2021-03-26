#include "Ships.h"

bool checkShipName(const char* shipType, const char* name) {
  if(strcmp(shipType, name) == 0)
    return true;
  
  return false;
}

void initViking(TerranShips *ship) {
  ship->damage = VIKING_DAMAGE;
  ship->health = VIKING_HEALTH;
  ship->ability = VIKING_ABILITY_MULTIPLIER;
  strcpy(ship->shipType, "Viking");
}

void initBattleCruser(TerranShips *ship) {
  ship->damage = BATTLE_CRUSER_DAMAGE;
  ship->health = BATTLE_CRUSER_HEALTH;
  ship->ability = BATTLE_CRUSER_ABILITY_MULTIPLIER;
  strcpy(ship->shipType, "BattleCruser");
}

void initCarrier(ProtossShips *ship) {
  ship->damage = CARRIER_DAMAGE;
  ship->health = CARRIER_HEALTH;
  ship->shield = CARRIER_SHIELD;
  ship->shieldRegen = CARRIER_SHIELD_REGENERATE_RATE;
  strcpy(ship->shipType, "Carrier");
}

void initPhoenix(ProtossShips *ship) {
  ship->shield = PHOENIX_SHIELD;
  ship->shieldRegen = PHOENIX_SHIELD_REGENERATE_RATE;
  ship->health = PHOENIX_HEALTH;
  ship->damage = PHOENIX_DAMAGE;
  strcpy(ship->shipType, "Phoenix");
}

void vikingAttack(TerranShips *attacker, ProtossShips *enemy) {
  if(checkShipName(enemy->shipType, "Phoenix")) {
    enemy->shield -= attacker->ability * attacker->damage;
  }
  else {
    enemy->shield -= attacker->damage;
  }
}

void battleCruserAttack(TerranShips *attacker, ProtossShips *enemy, int turnCount) {
  if(turnCount % YAMATO_CANNON_LOADING_TURNS == 0) {
    enemy->shield -= attacker->ability * attacker->damage;
  }
  else {
    enemy->shield -= attacker->damage;
  }
}

void substractShieldDamage(ProtossShips *ship) {
  if(ship->shield < 0) {
    ship->health += ship->shield;
    ship->shield = 0;
  }
}

void shieldRegen(ProtossShips *ship, int maxShield, int regenRate) {
  ship->shield += regenRate;
  if(ship->shield > maxShield)
    ship->shield = maxShield;
}

int carrierInterceptorsStatus(ProtossShips* carrier) {
  if(carrier->health != CARRIER_HEALTH) {
    return DAMAGED_STATUS_INTERCEPTORS;
  }
  else {
    return MAX_INTERCEPTORS;
  }
}