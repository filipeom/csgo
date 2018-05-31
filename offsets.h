#ifndef OFFSETS_H
#define OFFSETS_H

typedef unsigned long DWORD;

class Offsets {
  public:
    static const DWORD dwLocalPlayer    = 0xAA9AB4;
    static const DWORD dwCrossHairId    = 0xB2A4;
    static const DWORD dwAttack         = 0x2EC6AC8;
    static const DWORD dwEntityList     = 0x4A8473C;
    static const DWORD dwTeamNum        = 0xF0;
    static const DWORD dwHealth         = 0xFC;
    static const DWORD dwEntityLoopDist = 0x10;
    static const DWORD dwGlowIndex      = 0xA310;
    static const DWORD dwGlowObject     = 0x4FB14E8; 
};
#endif
