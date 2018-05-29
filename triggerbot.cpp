#include <Windows.h>
#include <iostream>
#include "Hprocess.h"

CHackProcess fProcess;

DWORD dwLocalPlayer = 0xAA9AB4;
DWORD dwCrossHairId = 0xB2A4;
int id;

struct triggerBot {
  void ReadMemory() {
    DWORD localPlayer;

    ReadProcessMemory(fProcess.__HandleProcess, 
        (PBYTE*) (fProcess.__dwordClient + dwLocalPlayer),
        &localPlayer, sizeof(DWORD),0);
    ReadProcessMemory(fProcess.__HandleProcess,
        (PBYTE*) (localPlayer+dwCrossHairId), &id, sizeof(int), 0);
  
  }
}

int
main() {
  fProcess.RunProcess();
  while(1) {
    struct triggerBot bot;
    bot.ReadMemory();
    std::cout << id << std::endl;
    Sleep(1);
  }
}
