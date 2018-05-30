#include <Windows.h>
#include "Hprocess.h"
/* GLOBAL VARIABLES*/

//CSGO PROCESS
CHackProcess fProcess;

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
int crossHairId;
int localTeamNumber;

//CROSSHAIR ENTITY
DWORD crossHairPlayer;
int crossHairPlayerTeam;
int crossHairPlayerHealth;

/* MEMORY FUNCTIONS */
void 
getCrossHairId() {
  ReadProcessMemory(fProcess.__HandleProcess,
      (PBYTE*) (localPlayer+dwCrossHairId), &crossHairId, sizeof(int), 0);

}

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
getCrossHairPlayer() {
  DWORD crossOffset = (crossHairId - 1) * dwEntityLoopDist;
  ReadProcessMemory(fProcess.__HandleProcess, 
      (PBYTE*) (fProcess.__dwordClient + dwEntityList + crossOffset), 
      &crossHairPlayer, sizeof(DWORD), 0);
  ReadProcessMemory(fProcess.__HandleProcess, 
      (PBYTE*) (crossHairPlayer + dwTeamNum), &crossHairPlayerTeam, 
      sizeof(int), 0);
  ReadProcessMemory(fProcess.__HandleProcess, 
      (PBYTE*) (crossHairPlayer + dwHealth), &crossHairPlayerHealth,
      sizeof(int), 0);
}

void 
shoot() {
  int attack = 5;
  WriteProcessMemory(fProcess.__HandleProcess, 
      (PBYTE*) (fProcess.__dwordClient + dwAttack), &attack, sizeof(int),0);
  attack = 4;
  WriteProcessMemory(fProcess.__HandleProcess, 
      (PBYTE*) (fProcess.__dwordClient + dwAttack), &attack, sizeof(int),0);
}

int
main() {
  fProcess.RunProcess();
  getLocalPlayer();

  for(;;) {
    getCrossHairId();
    if (crossHairId > 0 && crossHairId < 65) {
      getCrossHairPlayer();
      if ((crossHairPlayerTeam != localTeamNumber) &&
          (crossHairPlayerTeam > 1) && (crossHairPlayerHealth > 0))
        shoot();
    }
  }
  //Should never reach in a successful run.
  return -1;
}
