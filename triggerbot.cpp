#include <Windows.h>
#include <iostream>
#include "Hprocess.h"
/* GLOBAL VARIABLES*/
//CSGO PROCESS
CHackProcess fProcess;
//OFFSETS
DWORD dwLocalPlayer = 0xAA9AB4;
DWORD dwCrossHairId = 0xB2A4;
DWORD dwAttack = 0x2EC6AC8;
DWORD localPlayer;

int id;
int attack;

/* MEMORY FUNCTIONS */
void ReadMemory() {

  ReadProcessMemory(fProcess.__HandleProcess, 
      (PBYTE*) (fProcess.__dwordClient + dwLocalPlayer),
      &localPlayer, sizeof(DWORD),0);
  ReadProcessMemory(fProcess.__HandleProcess,
      (PBYTE*) (localPlayer+dwCrossHairId), &id, sizeof(int), 0);

}

void WriteMemory() {
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

  while(1) {
    ReadMemory();
    //Debug
    std::cout << id << std::endl;

    if(id > 0 && id < 32) {
      WriteMemory();
    }
  }
}
