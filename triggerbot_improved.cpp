#include <Windows.h>
#include "Hprocess.h"
/* GLOBAL VARIABLES*/

//CSGO PROCESS
CHackProcess fProcess;

//OFFSETS
DWORD dwLocalPlayer = 0xAA9AB4;
DWORD dwCrossHairId = 0xB2A4;
DWORD dwAttack = 0x2EC6AC8;
DWORD dwEntityList = 0x4A8473C;
DWORD dwTeamNum = 0xF0;
DWORD dwHealth = 0xFC;
DWORD dwEntityLoopDist = 0x10;

DWORD localPlayer;
int crossHairId;
int localTeamNumber;

/* MEMORY FUNCTIONS */
void getCrossHairId() {
  ReadProcessMemory(fProcess.__HandleProcess,
      (PBYTE*) (localPlayer+dwCrossHairId), &crossHairId, sizeof(int), 0);

}

void shoot() {
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
  
  ReadProcessMemory(fProcess.__HandleProcess,
      (PBYTE*) (fProcess.__dwordClient + dwLocalPlayer),
      &localPlayer, sizeof(DWORD), 0);
  ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*) localPlayer,
      &localTeamNumber, sizeof(int), 0);

  for(;;) {
    getCrossHairId();
    if(crossHairId > 0 && crossHairId < 32) {
      shoot();
    }
  }
}
