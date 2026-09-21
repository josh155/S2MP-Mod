__int64 __fastcall sub_4EB7D0(__int64 a1)
{
  __int64 v1; // r8
  __int64 v2; // r9
  __int64 v3; // rdx
  char v4; // r9
  char v5; // r10
  char v6; // r10
  bool v7; // sf
  __int64 v8; // rdx
  __int64 result; // rax
  unsigned int v10; // [rsp+8h] [rbp+8h]

  v1 = *(int *)(a1 + 36); /*0x4eb7d0*/
  v2 = *(int *)(a1 + 28); /*0x4eb7d4*/
  if ( (int)v1 + 4 > (int)v2 + *(_DWORD *)(a1 + 32) ) /*0x4eb7e5*/
  {
    *(_DWORD *)a1 = 1; /*0x4eb884*/
    return 0xFFFFFFFFLL; /*0x4eb88a*/
  }
  else
  {
    v3 = v1 - v2; /*0x4eb7ee*/
    if ( v1 - v2 < 0 ) /*0x4eb7f1*/
      v4 = *(_BYTE *)(*(_QWORD *)(a1 + 8) + v1); /*0x4eb802*/
    else
      v4 = *(_BYTE *)(v3 + *(_QWORD *)(a1 + 16)); /*0x4eb7f7*/
    LOBYTE(v10) = v4; /*0x4eb807*/
    if ( v3 + 1 < 0 ) /*0x4eb813*/
      v5 = *(_BYTE *)(*(_QWORD *)(a1 + 8) + v1 + 1); /*0x4eb824*/
    else
      v5 = *(_BYTE *)(v3 + 1 + *(_QWORD *)(a1 + 16)); /*0x4eb819*/
    BYTE1(v10) = v5; /*0x4eb82e*/
    if ( v3 + 2 < 0 ) /*0x4eb836*/
      v6 = *(_BYTE *)(*(_QWORD *)(a1 + 8) + v1 + 2); /*0x4eb847*/
    else
      v6 = *(_BYTE *)(v3 + 2 + *(_QWORD *)(a1 + 16)); /*0x4eb83c*/
    v7 = v3 + 3 < 0; /*0x4eb84d*/
    v8 = v3 + 3; /*0x4eb84d*/
    BYTE2(v10) = v6; /*0x4eb851*/
    if ( v7 ) /*0x4eb856*/
      HIBYTE(v10) = *(_BYTE *)(*(_QWORD *)(a1 + 8) + v1 + 3); /*0x4eb877*/
    else
      HIBYTE(v10) = *(_BYTE *)(v8 + *(_QWORD *)(a1 + 16)); /*0x4eb860*/
    result = v10; /*0x4eb864*/
    *(_DWORD *)(a1 + 36) = v1 + 4; /*0x4eb868*/
  }
  return result; /*0x4eb86c*/
}