__int64 __fastcall MSG_ReadNumFieldsSkipped(__int64 a1, unsigned int a2, int a3)
{
  int v4; // ecx
  int v5; // ebx
  int Bit; // eax
  int v7; // r9d
  unsigned int v8; // ebx
  int v9; // r9d
  int Bits; // r12d
  int v11; // r13d
  int v12; // ebx
  int v13; // ebx
  int v14; // r9d

  if ( a2 == 1 ) /*0x726f7b*/
  {
    v4 = -1; /*0x726f7d*/
    do /*0x726f9f*/
    {
      v5 = v4; /*0x726f93*/
      Bit = MSG_ReadBit(a1); /*0x726f95*/
      v4 = v5 + 1; /*0x726f9a*/
    }
    while ( !Bit ); /*0x726f9f*/
    v8 = v5 + 2; /*0x726fa1*/
    if ( v4 >= a3 ) /*0x726fa7*/
      MyAssertHandler( /*0x726fcb*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
        1886,
        0,
        (unsigned int)"%s",
        (unsigned int)"maxVal >= numSkipped",
        v7);
  }
  else
  {
    v8 = 1; /*0x726fdd*/
    if ( !(unsigned int)MSG_ReadBit(a1) ) /*0x726fd8*/
    {
      Bits = MSG_ReadBits(a1, a2); /*0x726ffd*/
      v11 = 1; /*0x727000*/
      v12 = (1 << a2) - 1; /*0x727008*/
      if ( Bits > v12 ) /*0x72700d*/
        MyAssertHandler( /*0x72702d*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
          1910,
          0,
          (unsigned int)"%s",
          (unsigned int)"bits <= ( 1 << skippedFieldBits ) - 1",
          v9);
      if ( Bits == v12 ) /*0x727035*/
      {
        do /*0x72707b*/
        {
          v13 = MSG_ReadBits(a1, a2); /*0x72704b*/
          if ( v13 > Bits ) /*0x727050*/
            MyAssertHandler( /*0x727070*/
              (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
              1918,
              0,
              (unsigned int)"%s",
              (unsigned int)"bits <= ( 1 << skippedFieldBits ) - 1",
              v14);
          v11 += Bits; /*0x727075*/
        }
        while ( v13 == Bits ); /*0x72707b*/
      }
      else
      {
        v13 = Bits; /*0x72707f*/
      }
      return (unsigned int)(v11 + v13); /*0x727082*/
    }
  }
  return v8; /*0x72708b*/
}