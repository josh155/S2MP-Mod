__int64 __fastcall sub_4F0780(__int64 a1, int a2)
{
  unsigned int v2; // edi
  int v5; // r8d
  int v6; // ecx
  int v7; // ecx
  unsigned __int8 v8; // dl
  int v9; // r8d
  int v10; // eax
  int v11; // ecx
  int v13; // ecx
  unsigned __int8 v14; // dl
  int v15; // edi
  int Bits; // eax
  int i; // esi

  v2 = 0; /*0x4f0794*/
  if ( a2 == 1 ) /*0x4f079e*/
  {
    while ( 1 ) /*0x4f07a4*/
    {
      ++v2; /*0x4f07a4*/
      v5 = *(_DWORD *)(a1 + 40) & 7; /*0x4f07a6*/
      if ( !v5 ) /*0x4f07aa*/
      {
        v6 = *(_DWORD *)(a1 + 36); /*0x4f07b2*/
        if ( v6 >= *(_DWORD *)(a1 + 32) + *(_DWORD *)(a1 + 28) ) /*0x4f07b7*/
        {
          *(_DWORD *)a1 = 1; /*0x4f0811*/
          return v2; /*0x4f0813*/
        }
        *(_DWORD *)(a1 + 40) = 8 * v6; /*0x4f07c0*/
        *(_DWORD *)(a1 + 36) = v6 + 1; /*0x4f07c6*/
      }
      v7 = (*(int *)(a1 + 40) >> 3) - *(_DWORD *)(a1 + 28); /*0x4f07d5*/
      if ( v7 < 0 ) /*0x4f07d8*/
        v8 = *(_BYTE *)((*(int *)(a1 + 40) >> 3) + *(_QWORD *)(a1 + 8)); /*0x4f07ee*/
      else
        v8 = *(_BYTE *)(v7 + *(_QWORD *)(a1 + 16)); /*0x4f07e1*/
      ++*(_DWORD *)(a1 + 40); /*0x4f07fa*/
      if ( ((v8 >> v5) & 1) != 0 ) /*0x4f0805*/
        return v2; /*0x4f0805*/
    }
  }
  v9 = *(_DWORD *)(a1 + 40) & 7; /*0x4f0821*/
  if ( !v9 ) /*0x4f0825*/
  {
    v10 = *(_DWORD *)(a1 + 28) + *(_DWORD *)(a1 + 32); /*0x4f082a*/
    v11 = *(_DWORD *)(a1 + 36); /*0x4f082d*/
    if ( v11 >= v10 ) /*0x4f0832*/
    {
      *(_DWORD *)a1 = 1; /*0x4f0834*/
      return 1; /*0x4f0838*/
    }
    *(_DWORD *)(a1 + 40) = 8 * v11; /*0x4f0844*/
    *(_DWORD *)(a1 + 36) = v11 + 1; /*0x4f084a*/
  }
  v13 = (*(int *)(a1 + 40) >> 3) - *(_DWORD *)(a1 + 28); /*0x4f0859*/
  if ( v13 < 0 ) /*0x4f085c*/
    v14 = *(_BYTE *)((*(int *)(a1 + 40) >> 3) + *(_QWORD *)(a1 + 8)); /*0x4f0872*/
  else
    v14 = *(_BYTE *)(v13 + *(_QWORD *)(a1 + 16)); /*0x4f0865*/
  ++*(_DWORD *)(a1 + 40); /*0x4f087e*/
  if ( ((v14 >> v9) & 1) != 0 ) /*0x4f0888*/
    return 1; /*0x4f088a*/
  v15 = 1; /*0x4f0893*/
  Bits = MSG_ReadBits(a1, a2); /*0x4f0895*/
  for ( i = (1 << a2) - 1; Bits == i; Bits = MSG_ReadBits(a1, a2) ) /*0x4f08a2*/
    v15 += i; /*0x4f08a9*/
  return (unsigned int)(Bits + v15); /*0x4f08c7*/
}