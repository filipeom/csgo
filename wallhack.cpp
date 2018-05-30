#include <Windows.h>
#include "Hprocess.h"

/* GLOBAL VARIABLES */
CHackProcess fProcess;

struct glowStruct {
  float r,g,b,a;
  bool rwo, rwuo;
}

//OFFSETS
const DWORD dwLocalPlayer = 0xAA9AB4;
const DWORD dwCrossHairId = 0xB2A4;
const DWORD dwAttack = 0x2EC6AC8;
const DWORD dwEntityList = 0x4A8473C;
const DWORD dwTeamNum = 0xF0;
const DWORD dwHealth = 0xFC;
const DWORD dwEntityLoopDist = 0x10;

//LOCAL PLAYER
DWORD localPlayer;
int localTeamNumber;

//ENTITY
DWORD entity;
int entityTeamNumber;
bool isDormant;

void
getLocalPlayer() {
  ReadProcessMemory(fProcess.__HandleProcess, 
      (PBYTE*) (fProcess.__dwordClient + dwLocalPlayer),
      &localPlayer, sizeof(DWORD), 0);
  ReadProcessMemory(fProcess.__HandleProcess, 
      (PBYTE*) (localPlayer + dwTeamNum), &localTeamNumber,
      sizeof(int), 0);
}

void
getEntity(int i) {
  DWORD entityOffset = (i-1) * dwEntityLoopDist;
  ReadProcessMemory(fProcess.__HandleProcess,
      (PBYTE*) (fProcess.__dwordClient + dwEntityList + entityOffset),
      &entity, sizeof(DWORD), 0);
  ReadProcessMemory(fProcess.__HandleProcess, 
      (PBYTE*) (entity + dwTeamNum), &entityTeamNumber, 
      sizeof(int), 0);
}

int
main() {
  struct glowStruct enemy;
  enemy.r = 1;
  enemy.g = 0;
  enemy.b = 0;
  enemy.a = 1;
  enemy.rwo = true;
  enemy.rwuo = true;
  struct glowStruct team;
  team.r = 0;
  team.g = 0;
  team.b = 1;
  team.a = 1;
  team.rwo = true;
  team.rwuo = true;

  for(;;) {
  

  }
  //Should never reach in a successful run.
  return -1;
}
