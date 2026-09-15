unsigned int __usercall MSG_WriteDeltaField@<eax>(
        int *a1@<eax>,
        int a2@<edx>,
        int a3@<ecx>,
        int a4,
        int a5,
        int a6,
        int a7,
        char a8)
{
  int v8; // eax
  BOOL v9; // eax
  int v10; // edx
  unsigned int result; // eax
  int v12; // ebx
  float v13; // xmm1_4
  int v14; // eax
  int v15; // ebx
  int v16; // ebx
  int v17; // ebx
  int v18; // ebx
  int v19; // ebx
  int v20; // esi
  unsigned int v21; // ebx
  char v22; // al
  int v23; // ebx
  int v24; // edx
  int v25; // ebx
  int v26; // ebx
  unsigned int v27; // ecx
  int v28; // ebx
  int v29; // esi
  int v30; // ebx
  int *v31; // [esp+28h] [ebp-80h]
  _DWORD *v32; // [esp+2Ch] [ebp-7Ch]
  float v33; // [esp+50h] [ebp-58h]
  int v34; // [esp+54h] [ebp-54h]
  int v35; // [esp+58h] [ebp-50h]
  float v39; // [esp+6Ch] [ebp-3Ch]
  float v40; // [esp+70h] [ebp-38h]
  unsigned int v41; // [esp+74h] [ebp-34h]
  float v42; // [esp+78h] [ebp-30h]
  float v43; // [esp+7Ch] [ebp-2Ch]
  int v44; // [esp+8Ch] [ebp-1Ch] BYREF

  v8 = *(_DWORD *)(a6 + 4); /*0x171f0c*/
  v32 = (_DWORD *)(v8 + a5); /*0x171f14*/
  if ( a8 ) /*0x171f19*/
  {
    v44 = 0; /*0x172080*/
    v31 = &v44; /*0x17208a*/
  }
  else
  {
    v31 = (int *)(a4 + v8); /*0x171f22*/
  }
  if ( *(_BYTE *)(a6 + 12) != 2 ) /*0x171f2c*/
  {
    if ( !a8 ) /*0x171f34*/
    {
      if ( *v31 == *v32 ) /*0x171f49*/
        return MSG_WriteBit0(a2); /*0x171f49*/
      switch ( *(_DWORD *)(a6 + 8) ) /*0x171f57*/
      {
        case 0xFFFFFF9C: /*0x171f57*/
        case 0xFFFFFFA9: /*0x171f57*/
          v9 = (unsigned __int16)(int)(float)((float)(182.04445 * *(float *)v32) + 0.5) == (unsigned __int16)(int)(float)((float)(*(float *)v31 * 182.04445) + 0.5); /*0x172245*/
          break; /*0x172248*/
        case 0xFFFFFFA1: /*0x171f57*/
          v9 = *v31 / 100 == *v32 / 100; /*0x172205*/
          break; /*0x172208*/
        case 0xFFFFFFA4: /*0x171f57*/
        case 0xFFFFFFA5: /*0x171f57*/
        case 0xFFFFFFA6: /*0x171f57*/
          *(float *)&v35 = floorf(*(float *)v31 + 0.5); /*0x171f80*/
          *(float *)&v34 = floorf(*(float *)v32 + 0.5); /*0x171f9e*/
          v9 = v35 == v34; /*0x171fab*/
          break; /*0x171fab*/
        default:
          goto LABEL_9;
      }
      if ( v9 ) /*0x171fb0*/
        return MSG_WriteBit0(a2); /*0x171fb0*/
    }
LABEL_9:
    MSG_WriteBit1(a2); /*0x171fc0*/
  }
  v10 = *(_DWORD *)(a6 + 8); /*0x171fce*/
  switch ( v10 ) /*0x171fd3*/
  {
    case 0: /*0x171fd3*/
      v40 = *(float *)v32; /*0x1720a7*/
      v39 = *(float *)v31; /*0x1720b3*/
      if ( *(float *)v32 != 0.0 ) /*0x1720c4*/
      {
        MSG_WriteBit1(a2); /*0x1720d0*/
        if ( LODWORD(v40) != 0x80000000 ) /*0x1720df*/
        {
          v12 = (int)v40; /*0x1720e8*/
          if ( (float)(int)v40 == v40 && v12 >= -4096 ) /*0x1720fe*/
          {
            v14 = (int)v39; /*0x17224d*/
            if ( v12 <= 4095 && v14 >= -4096 && v14 <= 4095 ) /*0x172271*/
            {
              MSG_WriteBit0(a2); /*0x17227d*/
              v15 = (v12 + 4096) ^ ((int)v39 + 4096); /*0x172291*/
              MSG_WriteBits(a2, v15, 5); /*0x1722a5*/
              return MSG_WriteByte(a2, v15 >> 5); /*0x1722bc*/
            }
          }
        }
        goto LABEL_33; /*0x172271*/
      }
      MSG_WriteBit0(a2); /*0x17216c*/
      if ( LODWORD(v40) == 0x80000000 ) /*0x17217b*/
        return MSG_WriteBit1(a2); /*0x172182*/
      return MSG_WriteBit0(a2); /*0x172146*/
    case -89: /*0x171fd3*/
      v18 = (int)*(float *)v32; /*0x172377*/
      v42 = *(float *)v31; /*0x172382*/
      if ( (float)v18 == *(float *)v32 && *v32 != 0x80000000 && v18 >= -4096 && v18 <= 4095 ) /*0x1723da*/
      {
        MSG_WriteBit0(a2); /*0x1723e2*/
        v19 = (v18 + 4096) ^ ((int)v42 + 4096); /*0x1723f8*/
        MSG_WriteBits(a2, v19, 5); /*0x17240c*/
        return MSG_WriteByte(a2, v19 >> 5); /*0x172423*/
      }
LABEL_33:
      MSG_WriteBit1(a2); /*0x172110*/
      return MSG_WriteLong(a2, *v31 ^ *v32); /*0x17213b*/
    case -88: /*0x171fd3*/
      return MSG_WriteLong(a2, *v31 ^ *v32); /*0x1724b6*/
    case -99: /*0x171fd3*/
      v13 = *(float *)v32; /*0x172194*/
      v43 = *(float *)v31; /*0x17219f*/
      if ( *(float *)v32 == 0.0 && LODWORD(v13) != 0x80000000 ) /*0x1721bc*/
        return MSG_WriteBit0(a2); /*0x1721c3*/
      MSG_WriteBit1(a2); /*0x1722cc*/
      if ( LODWORD(v13) != 0x80000000 ) /*0x1722db*/
      {
        v16 = (int)v13; /*0x1722e8*/
        if ( (float)(int)v13 == v13 && v16 >= -2048 && v16 <= 2047 ) /*0x172311*/
        {
          MSG_WriteBit0(a2); /*0x17231d*/
          v17 = (v16 + 2048) ^ ((int)v43 + 2048); /*0x172333*/
          MSG_WriteBits(a2, v17, 4); /*0x172347*/
          return MSG_WriteByte(a2, v17 >> 4); /*0x17235e*/
        }
      }
      goto LABEL_33; /*0x172311*/
    case -100: /*0x171fd3*/
      if ( !*v32 ) /*0x172473*/
        return MSG_WriteBit0(a2); /*0x172473*/
      MSG_WriteBit1(a2); /*0x17247f*/
      return MSG_WriteAngle16(a2, *v32); /*0x172498*/
    case -87: /*0x171fd3*/
      return MSG_WriteAngle16(a2, *v32); /*0x172586*/
    case -86: /*0x171fd3*/
      v33 = floorf((float)((float)(*(float *)v32 - 1.4) * 10.0) + 0.5); /*0x1725b4*/
      return MSG_WriteBits(a2, (int)v33, 5); /*0x1725d3*/
    case -85: /*0x171fd3*/
      v22 = *((_BYTE *)v31 + 3); /*0x1724be*/
      if ( v22 == -1 ) /*0x1724c4*/
      {
        if ( *((_BYTE *)v32 + 3) ) /*0x17267a*/
          goto LABEL_66; /*0x17267e*/
      }
      else if ( v22 || *((_BYTE *)v32 + 3) != 0xFF ) /*0x1724d5*/
      {
        goto LABEL_66; /*0x1724d5*/
      }
      if ( !memcmp((const char *)v31, (const char *)v32, 3) ) /*0x172690*/
        return MSG_WriteBit1(a2); /*0x1726a5*/
LABEL_66:
      MSG_WriteBit0(a2); /*0x1724db*/
      if ( (*v31 & 0xFFFFFF) == (*v32 & 0xFFFFFF) ) /*0x1724fd*/
      {
        MSG_WriteBit1(a2); /*0x1726b6*/
      }
      else
      {
        MSG_WriteBit0(a2); /*0x172509*/
        MSG_WriteByte(a2, *(_BYTE *)v32); /*0x17251e*/
        MSG_WriteByte(a2, *((_BYTE *)v32 + 1)); /*0x172534*/
        MSG_WriteByte(a2, *((_BYTE *)v32 + 2)); /*0x172544*/
      }
      return MSG_WriteBits(a2, *((_BYTE *)v32 + 3) >> 3, 5); /*0x17256d*/
    case -97: /*0x171fd3*/
      v20 = *v32; /*0x17242b*/
      v21 = *v32 - a3; /*0x17242f*/
      if ( v21 >= 0xFFFFFF01 || v21 == 0 ) /*0x172438*/
      {
        MSG_WriteBit0(a2); /*0x172449*/
        return MSG_WriteBits(a2, -v21, 8); /*0x172462*/
      }
      else
      {
        MSG_WriteBit1(a2); /*0x17265e*/
        return MSG_WriteLong(a2, v20); /*0x17266d*/
      }
    case -98: /*0x171fd3*/
      v23 = *v32; /*0x1725db*/
      v24 = *v31 ^ *v32; /*0x1725e2*/
      if ( ((v24 - 1) & v24) != 0 ) /*0x1725e9*/
      {
        MSG_WriteBit1(a2); /*0x172721*/
        MSG_WriteByte(a2, v23); /*0x172730*/
        v30 = v23 >> 8; /*0x172735*/
        MSG_WriteByte(a2, v30); /*0x172742*/
        return MSG_WriteByte(a2, SBYTE1(v30)); /*0x172751*/
      }
      else
      {
        v25 = 0; /*0x1725ef*/
        if ( (v24 & 1) == 0 ) /*0x1725f4*/
        {
          v25 = 0; /*0x1725f6*/
          do /*0x1725fe*/
          {
            ++v25; /*0x1725f8*/
            v24 >>= 1; /*0x1725f9*/
          }
          while ( (v24 & 1) == 0 ); /*0x1725fe*/
        }
        MSG_WriteBit0(a2); /*0x172606*/
        return MSG_WriteBits(a2, v25, 5); /*0x17261a*/
      }
    case -96: /*0x171fd3*/
      v26 = *v32; /*0x172627*/
      if ( *v32 != 1022 ) /*0x17262f*/
      {
        MSG_WriteBit0(a2); /*0x17263b*/
        if ( v26 ) /*0x172642*/
        {
          MSG_WriteBit0(a2); /*0x17277a*/
          MSG_WriteBits(a2, v26, 2); /*0x17278e*/
          return MSG_WriteByte(a2, v26 >> 2); /*0x1727a2*/
        }
      }
      return MSG_WriteBit1(a2); /*0x17218f*/
    case -94: /*0x171fd3*/
    case -93: /*0x171fd3*/
      return MSG_WriteByte(a2, *v32); /*0x17276a*/
  }
  if ( (unsigned int)(v10 + 92) <= 1 ) /*0x17204b*/
    return MSG_WriteOriginFloat(*a1, a2, v10, *(float *)v32, *(float *)v31); /*0x172852*/
  if ( v10 == -90 ) /*0x172054*/
    return MSG_WriteOriginZFloat(*a1, a2, *(float *)v32, *(float *)v31); /*0x1727f1*/
  if ( v10 == -95 ) /*0x17205d*/
    return MSG_WriteBits(a2, *v32 / 100, 7); /*0x172823*/
  if ( !*v32 ) /*0x172066*/
    return MSG_WriteBit0(a2); /*0x17207b*/
  MSG_WriteBit1(a2); /*0x1726c6*/
  v27 = abs32(*(_DWORD *)(a6 + 8)); /*0x1726d9*/
  v41 = v27; /*0x1726db*/
  v28 = *v31 ^ *v32; /*0x1726e6*/
  v29 = v27 & 7; /*0x1726ea*/
  if ( (v27 & 7) != 0 ) /*0x1726ed*/
  {
    MSG_WriteBits(a2, v28, v27 & 7); /*0x17286a*/
    v41 -= v29; /*0x17286f*/
    v28 >>= v29; /*0x172874*/
  }
  for ( result = v41; v41; v41 -= 8 ) /*0x1726f8*/
  {
    result = MSG_WriteByte(a2, v28); /*0x172708*/
    v28 >>= 8; /*0x17270d*/
  }
  return result; /*0x172131*/
}