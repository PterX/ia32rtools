int sub_test()
{
  u32 eax;
  u32 ebx;
  u32 ecx;
  u32 edx;
  u32 esi;
  u32 edi;
  u32 cond_z;

  ebx = 0x10000;
  esi = 0x20000;
  edi = 0x30000;
  ecx = 0x0a;

loop:
  LOBYTE(eax) = *(u8 *)esi; esi += 1;  // lods
  LOBYTE(eax) = *(u8 *)(ebx + LOBYTE(eax));  // xlat
  *(u8 *)edi = eax; edi += 1;  // stos
  LOWORD(eax) = *(u16 *)esi; esi += 2;  // lods
  LOWORD(eax) = -(s16)(u16)eax;
  *(u16 *)edi = eax; edi += 2;  // stos
  eax = *(u32 *)esi; esi += 4;  // lods
  *(u32 *)edi = eax; edi += 4;  // stos
  *(u8 *)edi = *(u8 *)esi; edi += 1; esi += 1;  // movs
  cond_z = (*(u16 *)esi == *(u16 *)edi); esi += 2; edi += 2;  // cmps
  cond_z = ((u8)eax == *(u8 *)edi); edi += 1;  // scas
  if (--ecx != 0)
    goto loop;  // loop
  *(u8 *)edi = eax; edi -= 1;  // stos
  *(u16 *)edi = eax; edi -= 2;  // stos
  *(u32 *)edi = eax; edi -= 4;  // stos
  edx = (s32)eax >> 31;  // cdq
  eax = ecx ? __builtin_ffs(ecx) - 1 : 0;  // bsf
  eax = 1;
  return eax;
}

