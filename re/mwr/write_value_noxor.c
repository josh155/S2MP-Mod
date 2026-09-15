void __fastcall MSG_WriteValueNoXor(__int64 a1, int a2, int a3, __int64 a4, __int64 a5, int a6)
{
  int v6; // ebx
  int v7; // r15d
  int v8; // r12d

  v6 = a2; /*0x74437e*/
  v7 = -a3; /*0x744383*/
  if ( -a3 < 1 ) /*0x744386*/
    v7 = a3; /*0x744386*/
  if ( a3 >= 0 && 32 - __lzcnt(a2 ^ (a2 >> 31)) > v7 + (a2 >> 31) )
    Com_PrintError(1, (unsigned int)"Not enough bits written: %d for %s (%d)\n", a2, a4, v7, a6);
  v8 = v7 & 7; /*0x7443c3*/
  if ( (v7 & 7) != 0 ) /*0x7443c7*/
  {
    MSG_WriteBits(a1, (unsigned int)a2, v7 & 7, a4, a5); /*0x7443d1*/
    v7 -= v8; /*0x7443d9*/
    v6 = a2 >> v8; /*0x7443dc*/
  }
  for ( ; v7; v7 -= 8 ) /*0x7443e1*/
  {
    MSG_WriteByte(a1, (unsigned int)v6); /*0x7443f5*/
    v6 >>= 8; /*0x7443fa*/
  }
}