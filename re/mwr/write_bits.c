__int64 __fastcall MSG_WriteBits(__int64 a1, int a2, int a3, __int64 a4, __int64 a5, int a6)
{
  int v7; // r15d
  const char *v8; // r8
  int v9; // esi
  __int64 v10; // r13
  __int64 v11; // rbx
  __int64 result; // rax
  int v13; // r8d
  __int64 v14; // rsi
  unsigned int v15; // edx
  int v16; // ecx
  char v17; // cc
  int v18; // [rsp+0h] [rbp-2Ch]

  v7 = *(_DWORD *)(a1 + 4); /*0x720d46*/
  if ( v7 ) /*0x720d4d*/
    MyAssertHandler( /*0x720d6d*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg.cpp",
      287,
      0,
      (unsigned int)"%s",
      (unsigned int)"!msg->readOnly",
      a6);
  if ( (unsigned int)a3 >= 0x21 ) /*0x720d76*/
  {
    v18 = a2; /*0x720d9c*/
    v8 = "(unsigned)bits <= 32"; /*0x720dad*/
    v9 = 289; /*0x720db4*/
  }
  else
  {
    v18 = a2; /*0x720d78*/
    if ( a3 ) /*0x720d7e*/
      goto LABEL_8; /*0x720d7e*/
    v8 = "bits"; /*0x720d8e*/
    v9 = 290; /*0x720d95*/
  }
  MyAssertHandler( /*0x720dbd*/
    (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg.cpp",
    v9,
    0,
    (unsigned int)"%s",
    (_DWORD)v8,
    a6);
LABEL_8:
  v10 = *(int *)(a1 + 24); /*0x720dc2*/
  v11 = *(int *)(a1 + 28); /*0x720dc6*/
  result = (unsigned int)(*(_DWORD *)(a1 + 24) - v11); /*0x720dcd*/
  if ( (int)result <= 3 ) /*0x720dd2*/
  {
    *(_DWORD *)a1 = 1; /*0x720dd4*/
    return result; /*0x720ddb*/
  }
  if ( a3 == 32 ) /*0x720de4*/
  {
    if ( v7 ) /*0x720de9*/
      MyAssertHandler( /*0x720e09*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg.cpp",
        477,
        0,
        (unsigned int)"%s",
        (unsigned int)"!msg->readOnly",
        a6);
    result = (unsigned int)(v11 + 4); /*0x720e10*/
    if ( (int)result <= (int)v10 ) /*0x720e16*/
    {
      *(_DWORD *)(*(_QWORD *)(a1 + 8) + v11) = v18; /*0x720ed4*/
      *(_DWORD *)(a1 + 28) = result; /*0x720ed7*/
    }
    else
    {
      *(_DWORD *)a1 = 1; /*0x720e1c*/
    }
  }
  else
  {
    if ( a3 >= 32 ) /*0x720e28*/
      MyAssertHandler( /*0x720e48*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg.cpp",
        305,
        0,
        (unsigned int)"%s",
        (unsigned int)"bits < 32",
        a6);
    v13 = *(_DWORD *)(a1 + 40); /*0x720e4d*/
    v14 = *(_QWORD *)(a1 + 8); /*0x720e59*/
    v15 = v18 & ~(-1 << a3); /*0x720e5f*/
    v16 = v13 & 7; /*0x720e68*/
    if ( (v13 & 7) != 0 ) /*0x720e6b*/
    {
      result = (unsigned int)(8 - v16); /*0x720e86*/
      *(_BYTE *)(v14 + (v13 >> 3)) |= (_BYTE)v15 << v16; /*0x720e88*/
      if ( (int)result >= a3 ) /*0x720e8f*/
      {
        *(_DWORD *)(a1 + 40) = a3 + v13; /*0x720ee0*/
        return result; /*0x720ee4*/
      }
      a3 -= result; /*0x720e93*/
      v15 >>= 8 - v16; /*0x720e96*/
    }
    result = (unsigned int)(a3 + 8 * v11); /*0x720e98*/
    *(_DWORD *)(a1 + 40) = result; /*0x720e9f*/
    if ( (int)v10 <= (int)v11 ) /*0x720ea3*/
    {
LABEL_23:
      *(_DWORD *)a1 = 1; /*0x720ec4*/
    }
    else
    {
      while ( 1 ) /*0x720eb0*/
      {
        *(_BYTE *)(v14 + v11++) = v15; /*0x720eb0*/
        v17 = (a3 - 8 < 0) ^ __OFADD__(-8, a3) | (a3 == 8); /*0x720eb6*/
        a3 -= 8; /*0x720eb6*/
        if ( v17 ) /*0x720eba*/
          break; /*0x720eba*/
        v15 >>= 8; /*0x720ebc*/
        if ( v11 >= v10 ) /*0x720ec2*/
          goto LABEL_23; /*0x720ec2*/
      }
      *(_DWORD *)(a1 + 28) = v11; /*0x720ee6*/
    }
  }
  return result; /*0x720eee*/
}