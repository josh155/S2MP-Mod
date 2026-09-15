__int64 __fastcall sub_3411A0(unsigned int a1, __int64 a2, double a3, double a4)
{
  __int64 v6; // rbp
  __int64 v7; // rbx
  int v8; // ebx
  int v9; // eax
  _BYTE *v10; // rax
  unsigned __int8 v11; // al
  __int64 v12; // rbx
  _BYTE *v13; // rax
  _BYTE v15[32]; // [rsp+30h] [rbp-68h] BYREF
  _BYTE v16[32]; // [rsp+50h] [rbp-48h] BYREF

  sub_33DE40(); /*0x3411c3*/
  v6 = qword_2EC8510; /*0x3411c8*/
  *(_DWORD *)(qword_2EC8510 + 32) = 0; /*0x3411d1*/
  sub_12DC80(a1); /*0x3411d8*/
  MSG_ClearLastReferencedEntity(a2); /*0x3411e0*/
  v7 = qword_2EC84F0; /*0x3411e5*/
  qword_2ED20A8 = 0; /*0x3411f1*/
  dword_2ED20B0 = 0; /*0x3411f8*/
  *(_DWORD *)(v6 + 262456) = MSG_ReadLong(a2); /*0x341209*/
  sub_4EB910(a2, v16, 32); /*0x341217*/
  *(_DWORD *)(v7 + 19172) = MSG_ReadLong(a2); /*0x34122a*/
  sub_4EB910(a2, v15, 32); /*0x341238*/
  v8 = MSG_ReadLong(a2); /*0x341245*/
  if ( !(unsigned int)sub_2B0CD0() ) /*0x341247*/
  {
    sub_2B0D80(); /*0x341250*/
    sub_5A4530(); /*0x341255*/
  }
  if ( (unsigned int)sub_2B18E0() != v8 ) /*0x341261*/
    sub_159860(1, "XBOXLIVE_CANTJOINSESSION"); /*0x34126f*/
  v9 = MSG_ReadBits(a2, 3); /*0x34127c*/
  if ( v9 != 7 ) /*0x341284*/
  {
    while ( v9 == 1 ) /*0x341293*/
    {
      CL_ParseConfigStrings(a1, a2); /*0x34129e*/
      v10 = CL_GetConfigString(8u); /*0x3412a8*/
      PLsscanf(v10, "%f %f %f", a3, a4, COERCE_DOUBLE(&dword_2ED20B0)); /*0x3412ca*/
      v9 = MSG_ReadBits(a2, 3); /*0x3412d7*/
      if ( v9 == 7 ) /*0x3412df*/
        goto LABEL_8; /*0x3412df*/
    }
    return MSG_Discard(a2); /*0x341293*/
  }
LABEL_8:
  v11 = MSG_ReadLong(a2); /*0x3412e1*/
  *(_BYTE *)(v6 + 4) = v11; /*0x3412e9*/
  if ( v11 > 0x11u ) /*0x3412ee*/
  {
    *(_BYTE *)(v6 + 4) = 0; /*0x3413a7*/
    return MSG_Discard(a2); /*0x3413ae*/
  }
  *(_DWORD *)(v6 + 296) = MSG_ReadLong(a2); /*0x341301*/
  *(_BYTE *)(v6 + 524864) = MSG_ReadBits(a2, 1); /*0x34130f*/
  sub_399DE0(); /*0x341315*/
  v12 = qword_2EC84F0; /*0x34131a*/
  v13 = CL_GetConfigString(3u); /*0x341326*/
  dword_2F52FA4 = sub_830F80(v13); /*0x341333*/
  *(_DWORD *)(v12 + 19104) = dword_2F52FA4; /*0x34133b*/
  sub_342ED0(a1); /*0x341341*/
  dword_2ED21C8 |= *((unsigned __int8 *)off_2EC86B8 + 9); /*0x341351*/
  if ( (unsigned int)sub_188FD0(*(unsigned int *)(v6 + 296)) ) /*0x34135d*/
    sub_189320(a1, *(unsigned int *)(v6 + 296)); /*0x34136e*/
  sub_12FDF0(a1, v16, v15); /*0x34137f*/
  sub_4F2C50(); /*0x341384*/
  sub_12BA00(a1); /*0x34138b*/
  sub_137AE0(a1); /*0x341392*/
  return sub_185D10(off_2E6EE10, 0); /*0x3413b3*/
}