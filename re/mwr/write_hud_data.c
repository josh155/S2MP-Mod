void __fastcall MSG_WriteHudData(__int64 a1, _BYTE *a2, _DWORD *a3)
{
  __int64 v4; // rcx
  __int64 v5; // r8
  __int64 v6; // rcx
  __int64 v7; // r8
  __int64 v8; // rcx
  __int64 v9; // r8

  if ( ((*(_BYTE *)a3 ^ *a2) & 0x3F) != 0 ) /*0x73bbea*/
  {
    MSG_WriteBit1(a1); /*0x73bbec*/
    MSG_WriteBits(a1, *a3 & 0xF, 4, v4, v5); /*0x73bbfe*/
    MSG_WriteBits(a1, (*a3 >> 4) & 3, 2, v6, v7); /*0x73bc15*/
  }
  else
  {
    MSG_WriteBit0(a1); /*0x73bc1c*/
  }
  if ( ((*(_WORD *)a3 ^ *(_WORD *)a2) & 0x3C0) != 0 ) /*0x73bc2a*/
  {
    MSG_WriteBit1(a1); /*0x73bc2f*/
    MSG_WriteBits(a1, (*a3 >> 6) & 0xF, 4, v8, v9); /*0x73bc50*/
  }
  else
  {
    MSG_WriteBit0(a1); /*0x73bc62*/
  }
}