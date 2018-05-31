#include <Windows.h>
#include "offsets.h"
#include "Hprocess.h"

/* GLOBAL VARIABLES */
CHackProcess fProcess;

struct glowStruct {
  float r,g,b,a;
  bool rwo, rwuo;
};

//LOCAL PLAYER
DWORD localPlayer;
int localTeamNumber;

//ENTITY
DWORD entity;
int entityTeamNumber;
//bool isDormant; can't find offset

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
getEntity(int i) {
  DWORD entityOffset = (i-1) * Offsets::dwEntityLoopDist;
  ReadProcessMemory(fProcess.__HandleProcess,
      (PBYTE*) (fProcess.__dwordClient + Offsets::dwEntityList + entityOffset),
      &entity, sizeof(DWORD), 0);
  ReadProcessMemory(fProcess.__HandleProcess, 
      (PBYTE*) (entity + Offsets::dwTeamNum), &entityTeamNumber, 
      sizeof(int), 0);
}

void
init_struct(struct glowStruct *s, int r, int g, int b, int a, bool rw, 
    bool rwu) {
  s->r = r;
  s->g = g;
  s->b = b;
  s->a = a;
  s->rwo = rw;
  s->rwuo = rwu;
}

int
main() {
  struct glowStruct enemy;
  struct glowStruct team;
  
  init_struct(&enemy, 1, 0, 0, 1, true, true);
  init_struct(&team, 0, 0, 1, 1, true, true);

  fProcess.RunProcess();
  getLocalPlayer();

  for(;;) {
    int i;
    DWORD glowIndex, glowObject;
    DWORD aux, curr;
    
    for(i = 1; i < 65; i++) {
      getEntity(i);
      ReadProcessMemory(fProcess.__HandleProcess, 
          (PBYTE*) (entity + Offsets::dwGlowIndex), &glowIndex, 
          sizeof(DWORD), 0);
      
      if(localTeamNumber == entityTeamNumber) {
        ReadProcessMemory(fProcess.__HandleProcess,
            (PBYTE*) (fProcess.__dwordClient + Offsets::dwGlowObject),
            &glowObject, sizeof(DWORD), 0);
        
        aux = glowIndex * 0x38 + 0x4;
        curr = glowObject + aux;
        WriteProcessMemory(fProcess.__HandleProcess, 
            (PBYTE*) (curr), &team.r, sizeof(int), 0);
        
        aux = glowIndex * 0x38 + 0x8;
        curr = glowObject + aux;
        WriteProcessMemory(fProcess.__HandleProcess, 
            (PBYTE*) (curr), &team.g, sizeof(int), 0);

        aux = glowIndex * 0x38 + 0xC;
        curr = glowObject + aux;
        WriteProcessMemory(fProcess.__HandleProcess, 
            (PBYTE*) (curr), &team.b, sizeof(int), 0);

        aux = glowIndex * 0x38 + 0x10;
        curr = glowObject + aux;
        WriteProcessMemory(fProcess.__HandleProcess, 
            (PBYTE*) (curr), &team.a, sizeof(int), 0);

        aux = glowIndex * 0x38 + 0x24;
        curr = glowObject + aux;
        WriteProcessMemory(fProcess.__HandleProcess, 
            (PBYTE*) (curr), &team.rwo, sizeof(bool), 0);

        aux = glowIndex * 0x38 + 0x25;
        curr = glowObject + aux;
        WriteProcessMemory(fProcess.__HandleProcess, 
            (PBYTE*) (curr), &team.rwuo, sizeof(bool), 0);

      } else {
        ReadProcessMemory(fProcess.__HandleProcess,
            (PBYTE*) (fProcess.__dwordClient + Offsets::dwGlowObject),
            &glowObject, sizeof(DWORD), 0);
        
        aux = glowIndex * 0x38 + 0x4;
        curr = glowObject + aux;
        WriteProcessMemory(fProcess.__HandleProcess, 
            (PBYTE*) (curr), &enemy.r, sizeof(int), 0);
        
        aux = glowIndex * 0x38 + 0x8;
        curr = glowObject + aux;
        WriteProcessMemory(fProcess.__HandleProcess, 
            (PBYTE*) (curr), &enemy.g, sizeof(int), 0);

        aux = glowIndex * 0x38 + 0xC;
        curr = glowObject + aux;
        WriteProcessMemory(fProcess.__HandleProcess, 
            (PBYTE*) (curr), &enemy.b, sizeof(int), 0);

        aux = glowIndex * 0x38 + 0x10;
        curr = glowObject + aux;
        WriteProcessMemory(fProcess.__HandleProcess, 
            (PBYTE*) (curr), &enemy.a, sizeof(int), 0);

        aux = glowIndex * 0x38 + 0x24;
        curr = glowObject + aux;
        WriteProcessMemory(fProcess.__HandleProcess, 
            (PBYTE*) (curr), &enemy.rwo, sizeof(bool), 0);

        aux = glowIndex * 0x38 + 0x25;
        curr = glowObject + aux;
        WriteProcessMemory(fProcess.__HandleProcess, 
            (PBYTE*) (curr), &enemy.rwuo, sizeof(bool), 0);
      }
    } 
  }
  //Should never reach in a successful run.
  return -1;
}
