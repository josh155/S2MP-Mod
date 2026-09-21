__int64 __fastcall MSG_ReadEntityIndex(_DWORD *a1, unsigned int a2)
{
  int v2; // edx
  int v3; // ecx
  int v4; // r8d
  int v5; // r9d
  int v6; // ebx
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int Bits; // r15d
  int v11; // r9d

  if ( (unsigned int)MSG_ReadBit(a1) )
  {
    if ( *(_BYTE *)(unk_BA57FB8 + 24LL) )
      Com_Printf(25, (unsigned int)"Entity num: 1 bit (inc)\n", v2, v3, v4, v5);
    v6 = a1[11] + 1; /*0x72457f*/
  }
  else if ( a2 == 11 && !(unsigned int)MSG_ReadBit(a1) )
  {
    if ( *(_BYTE *)(unk_BA57FB8 + 24LL) )
      Com_Printf(25, (unsigned int)"Entity num: %i bits (delta)\n", 11, v3, v4, v5);
    Bits = MSG_ReadBits(a1, 9); /*0x724645*/
    if ( Bits <= 0 ) /*0x72464b*/
      MyAssertHandler( /*0x724671*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
        958,
        0,
        (unsigned int)"%s\n\t(delta) = %i",
        (unsigned int)"(delta > 0)",
        Bits);
    v6 = Bits + a1[11]; /*0x72467a*/
  }
  else
  {
    if ( *(_BYTE *)(unk_BA57FB8 + 24LL) )
      Com_Printf(25, (unsigned int)"Entity num: %i bits (full)\n", a2 + 2, v3, v4, v5);
    v7 = MSG_ReadBits(a1, a2); /*0x7245c2*/
    v8 = a1[11]; /*0x7245c7*/
    v6 = v7; /*0x7245cb*/
    if ( v7 <= v8 ) /*0x7245cf*/
    {
      v9 = va((unsigned int)"%i <= %i", v7, v8, v3, v4, v5); /*0x7245e0*/
      MyAssertHandler( /*0x724609*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
        969,
        0,
        (unsigned int)"%s\n\t%s",
        (unsigned int)"delta > msg->lastEntityRef",
        v9);
    }
  }
  a1[11] = v6; /*0x724684*/
  if ( *(_BYTE *)(unk_BA57FB8 + 24LL) ) /*0x72468b*/
    Com_Printf(25, (unsigned int)"Read entity num %i\n", v6, v3, v4, v5); /*0x7246a1*/
  if ( !*a1 ) /*0x7246a6*/
  {
    v11 = a1[11]; /*0x7246ac*/
    if ( v11 < 0 ) /*0x7246b3*/
      MyAssertHandler( /*0x7246d6*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
        976,
        0,
        (unsigned int)"%s\n\t(msg->lastEntityRef) = %i",
        (unsigned int)"(msg->overflowed || msg->lastEntityRef >= 0)",
        v11);
  }
  return (unsigned int)a1[11]; /*0x7246e3*/
}