// Basis: PS4 twin 0x7273A0
void __fastcall sub_4ED0E0(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        unsigned __int16 *a5,
        unsigned int a6,
        int a7)
{
  char v7; // bl
  unsigned int v8; // r12d
  unsigned __int16 *v9; // r15
  __int64 v11; // rdi
  int *v12; // r14
  __int64 v13; // r8
  __int64 v14; // rsi
  int v16; // r8d
  int v17; // r8d
  int v18; // ebx
  int v19; // eax
  int v20; // ecx
  unsigned int v21; // eax
  int v22; // eax
  int v23; // ebx
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // ebx
  int v29; // ebx
  int v30; // ebx
  unsigned int v31; // eax
  int v32; // eax
  __int64 v33; // rcx
  int v34; // eax
  char v35; // al
  int v36; // eax
  int v37; // eax
  unsigned int v38; // edi
  int v39; // ebx
  int v40; // eax
  int v41; // eax
  int v42; // [rsp+88h] [rbp+48h] BYREF

  v7 = a7;
  v8 = 0;
  v9 = a5;
  v42 = 0;
  v11 = a1;
  if ( (_BYTE)a7 )
    v12 = &v42;
  else
    v12 = (int *)(a3 + *a5);
  v13 = (unsigned int)(__int16)a5[2];
  v14 = a4 + *a5;
  switch ( a5[2] )
  {
    case 0xFF90:
    case 0xFFC0:
      a7 = *v12;
      if ( !v7 )
        sub_5B0C40(v12, &a7);
      *(_DWORD *)v14 = sub_4F0520(v11, &a7, v9, a6);
      sub_5B0CE0(v14, v14);
      return;
    case 0xFF91:
    case 0xFFBF:
      a7 = *v12;
      if ( !v7 )
        sub_5B0C30(v12, &a7);
      *(_DWORD *)v14 = sub_4F0520(v11, &a7, v9, a6);
      sub_5B0CD0(v14, v14);
      return;
    case 0xFF92:
      *(_DWORD *)v14 = sub_4F05C0(a1, v12);
      return;
    case 0xFF94:
    case 0xFFBE:
      a7 = *v12;
      if ( !v7 )
        sub_5B0C20(v12, &a7);
      *(_DWORD *)v14 = sub_4F0520(v11, &a7, v9, a6);
      sub_5B0CC0(v14, v14);
      return;
    case 0xFF95:
      *(_DWORD *)v14 = sub_4EC610(a1, v12, a5, a6);
      return;
    case 0xFF96:
      a7 = *v12;
      if ( !v7 )
        sub_5B0C20(v12, &a7);
      *(_DWORD *)v14 = sub_4F0650(v11, &a7, v9, a6);
      sub_5B0CC0(v14, v14);
      return;
    case 0xFF97:
      a7 = *v12;
      if ( !v7 )
        sub_5B0C30(v12, &a7);
      *(_DWORD *)v14 = sub_4F0650(v11, &a7, v9, a6);
      sub_5B0CD0(v14, v14);
      return;
    case 0xFF98:
      a7 = *v12;
      if ( !v7 )
        sub_5B0C40(v12, &a7);
      *(_DWORD *)v14 = sub_4F0650(v11, &a7, v9, a6);
      sub_5B0CE0(v14, v14);
      return;
    case 0xFF99:
      v34 = MSG_ReadBit(a1);
      v33 = v11;
      if ( v34 )
        goto LABEL_83;
      *(_DWORD *)v14 = 50 * MSG_ReadBits(v11, 4);
      return;
    case 0xFF9A:
      v32 = MSG_ReadBit(a1);
      v33 = v11;
      if ( v32 )
LABEL_83:
        *(_DWORD *)v14 = MSG_ReadBits(v33, 16);
      else
        *(_DWORD *)v14 = 250 * MSG_ReadBits(v11, 4);
      return;
    case 0xFF9B:
      if ( !(unsigned int)MSG_ReadBit(a1) )
        goto LABEL_100;
      *(_DWORD *)v14 = MSG_ReadValue32_ByteCursor(v11);
      return;
    case 0xFF9C:
      *(float *)v14 = sub_4EC8A0(a1);
      return;
    case 0xFF9D:
      if ( (unsigned int)MSG_ReadBit(a1) )
      {
        if ( (unsigned int)MSG_ReadBit(v11) )
        {
          *(_DWORD *)v14 = MSG_ReadLong(v11) ^ *v12;
        }
        else
        {
          v28 = MSG_ReadBits(v11, 4);
          *(float *)v14 = (float)(int)(((16 * MSG_ReadByte(v11) + v28) ^ ((int)*(float *)v12 + 2048)) - 2048);
        }
      }
      else
      {
LABEL_100:
        *(_DWORD *)v14 = 0;
      }
      return;
    case 0xFF9E:
      v29 = *v12;
      if ( (unsigned int)MSG_ReadBit(a1) == 1 )
        *(_DWORD *)v14 = MSG_ReadBits(v11, 29);
      else
        *(_DWORD *)v14 = v29 ^ (1 << MSG_ReadBits(v11, 5));
      return;
    case 0xFF9F:
    case 0xFFB6:
    case 0xFFB8:
    case 0xFFBA:
      *(_DWORD *)v14 = sub_4EFFE0(a1);
      return;
    case 0xFFA0:
      if ( (unsigned int)MSG_ReadBit(a1) == 1 )
      {
        v8 = 2046;
      }
      else if ( (unsigned int)MSG_ReadBit(v11) != 1 )
      {
        v30 = MSG_ReadBits(v11, 3);
        v8 = v30 | (8 * MSG_ReadByte(v11));
      }
      sub_4F1740(v14, (unsigned int)(__int16)v9[1], v8);
      return;
    case 0xFFA1:
      *(_DWORD *)v14 = 100 * MSG_ReadBits(a1, 7);
      return;
    case 0xFFA2:
      sub_4ED000(a1, a3, a4, a5);
      return;
    case 0xFFA3:
      v31 = MSG_ReadBits(a1, 27);
      goto LABEL_64;
    case 0xFFA4:
    case 0xFFA5:
      *(float *)v14 = sub_4F08D0((unsigned int)v13, a1);
      return;
    case 0xFFA6:
      *(float *)v14 = sub_4F09B0(a1);
      return;
    case 0xFFA7:
      v22 = MSG_ReadBit(a1);
      a1 = v11;
      if ( v22 )
        goto LABEL_47;
      v23 = MSG_ReadBits(v11, 5);
      *(float *)v14 = (float)(int)(((32 * MSG_ReadByte(v11) + v23) ^ ((int)*(float *)v12 + 4096)) - 4096);
      return;
    case 0xFFA8:
LABEL_47:
      v27 = MSG_ReadLong(a1);
      *(_DWORD *)v14 = v27;
      *(_DWORD *)v14 = *v12 ^ v27;
      return;
    case 0xFFA9:
      *(float *)v14 = sub_4EB250(a1);
      return;
    case 0xFFAA:
      *(float *)v14 = (float)((float)(int)MSG_ReadBits(a1, 6) / 10.0) + 0.0;
      return;
    case 0xFFAB:
      if ( (unsigned int)MSG_ReadBit(a1) )
      {
        *(_DWORD *)v14 = *v12;
        if ( !*((_BYTE *)v12 + 3) )
          LOBYTE(v8) = -1;
        *(_BYTE *)(v14 + 3) = v8;
      }
      else
      {
        if ( (unsigned int)MSG_ReadBit(v11) )
        {
          *(_BYTE *)v14 = *(_BYTE *)v12;
          *(_BYTE *)(v14 + 1) = *((_BYTE *)v12 + 1);
          v35 = *((_BYTE *)v12 + 2);
        }
        else
        {
          *(_BYTE *)v14 = MSG_ReadByte(v11);
          *(_BYTE *)(v14 + 1) = MSG_ReadByte(v11);
          v35 = MSG_ReadByte(v11);
        }
        *(_BYTE *)(v14 + 2) = v35;
        *(_BYTE *)(v14 + 3) = 8 * MSG_ReadBits(v11, 5);
      }
      return;
    case 0xFFAC:
      *(_DWORD *)v14 = MSG_ReadBits(a1, 9);
      return;
    case 0xFFAD:
      a7 = *v12;
      if ( !v7 )
        sub_5B0C20(v12, &a7);
      *(float *)v14 = sub_4F08D0((unsigned int)(__int16)v9[2], v11);
      sub_5B0CC0(v14, v14);
      return;
    case 0xFFAE:
      a7 = *v12;
      if ( !v7 )
        sub_5B0C30(v12, &a7);
      *(float *)v14 = sub_4F08D0((unsigned int)(__int16)v9[2], v11);
      sub_5B0CD0(v14, v14);
      return;
    case 0xFFAF:
      a7 = *v12;
      if ( !v7 )
        sub_5B0C40(v12, &a7);
      *(float *)v14 = sub_4F09B0(v11);
      sub_5B0CE0(v14, v14);
      return;
    case 0xFFB0:
    case 0xFFB2:
    case 0xFFB7:
    case 0xFFB9:
    case 0xFFBB:
    case 0xFFBC:
      *(_DWORD *)v14 = MSG_ReadLong(a1);
      return;
    case 0xFFB1:
      sub_8295A0(a1, a2, v13, a4);
      *(float *)v14 = sub_4EC9C0(v11);
      return;
    case 0xFFB3:
      v31 = MSG_ReadByte(a1);
LABEL_64:
      sub_4F1740(v14, (unsigned int)(__int16)v9[1], v31);
      return;
    case 0xFFB4:
      v36 = MSG_ReadBit(a1);
      v20 = v11;
      if ( v36 != 1 )
        goto LABEL_35;
      v37 = MSG_ReadBits(v11, 4);
      v38 = (__int16)v9[1];
      v39 = v37;
      v40 = sub_4EC3F0(v12, v38);
      sub_4F1740(v14, v38, (unsigned int)(v40 + v39 - 8));
      break;
    case 0xFFB5:
      if ( (unsigned int)MSG_ReadBit(a1) == 1 )
      {
        if ( !_BitScanReverse((unsigned int *)&v16, 0x10u) )
          v17 = 32;
        else
          v17 = v16 ^ 0x1F;
        v18 = MSG_ReadBits(v11, (unsigned int)(32 - v17));
        v19 = sub_4EC3F0(v12, (unsigned int)(__int16)v9[1]);
        sub_4F1740(v14, (unsigned int)(__int16)v9[1], (unsigned int)(v18 + v19 + 1));
      }
      else
      {
        v20 = v11;
LABEL_35:
        v21 = sub_4F0A70(v20, (_DWORD)v12, v14, 8, (__int16)v9[1]);
        sub_4F1740(v14, (unsigned int)(__int16)v9[1], v21);
      }
      break;
    case 0xFFBD:
      *(_DWORD *)v14 = MSG_ReadBits(a1, 5) - 10;
      return;
    case 0xFFC1:
      *(_DWORD *)v14 = MSG_ReadLong(a1);
      v24 = *v12;
      a7 = *v12;
      if ( !v7 )
      {
        sub_5B0C20(v12, &a7);
        v24 = a7;
      }
      *(_DWORD *)v14 ^= v24;
      sub_5B0CC0(v14, v14);
      return;
    case 0xFFC2:
      *(_DWORD *)v14 = MSG_ReadLong(a1);
      v25 = *v12;
      a7 = *v12;
      if ( !v7 )
      {
        sub_5B0C30(v12, &a7);
        v25 = a7;
      }
      *(_DWORD *)v14 ^= v25;
      sub_5B0CD0(v14, v14);
      return;
    case 0xFFC3:
      *(_DWORD *)v14 = MSG_ReadLong(a1);
      v26 = *v12;
      a7 = *v12;
      if ( !v7 )
      {
        sub_5B0C40(v12, &a7);
        v26 = a7;
      }
      *(_DWORD *)v14 ^= v26;
      sub_5B0CE0(v14, v14);
      return;
    case 0u:
      *(_DWORD *)v14 = sub_4F0520(a1, v12, a5, a6);
      return;
    default:
      if ( (unsigned int)MSG_ReadBit(a1) )
      {
        v41 = sub_4F0A70(v11, (_DWORD)v12, v14, (__int16)v9[2], (__int16)v9[1]);
        switch ( v9[1] )
        {
          case 0xFFFC:
          case 4u:
            *(_DWORD *)v14 = v41;
            break;
          case 0xFFFE:
          case 2u:
            *(_WORD *)v14 = v41;
            break;
          case 0xFFFF:
          case 1u:
            *(_BYTE *)v14 = v41;
            break;
          default:
            return;
        }
      }
      else
      {
        switch ( v9[1] )
        {
          case 0xFFFC:
          case 4u:
            goto LABEL_100;
          case 0xFFFE:
          case 2u:
            *(_WORD *)v14 = 0;
            break;
          case 0xFFFF:
          case 1u:
            *(_BYTE *)v14 = 0;
            break;
          default:
            return;
        }
      }
      return;
  }
}
