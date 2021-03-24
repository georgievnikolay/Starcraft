#include <stdio.h>
#include <stdlib.h>

#include "BattleField.h"

int main() {
  const int buffSize = 50;
  char terranFleet[50];
  char protossFleet[50];
  scanf("%s %s", terranFleet, protossFleet);

  BattleField battleField;
  generateTerranFleet(&battleField, terranFleet);
  generateProtossFleet(&battleField, protossFleet);
  startBattle(&battleField);
  deinit(&battleField);

  return EXIT_SUCCESS;
}
