#include <Windows.h>
#include "offsets.h"
#include "Hprocess.h"
/* GLOBAL VARIABLES*/

//CSGO PROCESS
CHackProcess fProcess;

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
      (PBYTE*) (localPlayer+Offsets::dwCrossHairId), &crossHairId, sizeof(int), 0);

}

void 
getLocalPlayer() {
  ReadProcessMemory(fProcess.__HandleProcess,
      (PBYTE*) (fProcess.__dwordClient + Offsets::dwLocalPlayer),
      &localPlayer, sizeof(DWORD), 0);
  ReadProcessMemory(fProcess.__HandleProcess, 
      (PBYTE*) (localPlayer + Offsets::dwTeamNum), &localTeamNumber,
      sizeof(int), 0);
}

void 
getCrossHairPlayer() {
  DWORD crossOffset = (crossHairId - 1) * Offsets::dwEntityLoopDist;
  ReadProcessMemory(fProcess.__HandleProcess, 
      (PBYTE*) (fProcess.__dwordClient + Offsets::dwEntityList + crossOffset), 
      &crossHairPlayer, sizeof(DWORD), 0);
  ReadProcessMemory(fProcess.__HandleProcess, 
      (PBYTE*) (crossHairPlayer + Offsets::dwTeamNum), &crossHairPlayerTeam, 
      sizeof(int), 0);
  ReadProcessMemory(fProcess.__HandleProcess, 
      (PBYTE*) (crossHairPlayer + Offsets::dwHealth), &crossHairPlayerHealth,
      sizeof(int), 0);
}

void 
shoot() {
  int attack = 5;
  WriteProcessMemory(fProcess.__HandleProcess, 
      (PBYTE*) (fProcess.__dwordClient + Offsets::dwAttack), &attack, sizeof(int),0);
  attack = 4;
  WriteProcessMemory(fProcess.__HandleProcess, 
      (PBYTE*) (fProcess.__dwordClient + Offsets::dwAttack), &attack, sizeof(int),0);
}

int
main() {
  fProcess.RunProcess();
  
  for(;;) {
    getLocalPlayer();
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
