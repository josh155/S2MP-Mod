__int64 __fastcall MSG_WriteValue(__int64 a1, __int16 *a2, unsigned __int16 *a3, int a4, int a5, __int64 a6)
{
  int v9; // ebx
  int v10; // r15d
  int v11; // ebx
  int v12; // r8d
  int v13; // r9d
  int v14; // eax
  int v15; // r8d
  int v16; // r9d
  unsigned int v17; // ebx
  __int64 v19; // [rsp+0h] [rbp-30h]

  v9 = a5 + 4; /*0x74417a*/
  switch ( a5 ) /*0x744190*/
  {
    case -4: /*0x744190*/
    case 4: /*0x744190*/
      v19 = a1; /*0x744192*/
      v10 = *(_DWORD *)a2; /*0x744196*/
      goto LABEL_4; /*0x744199*/
    case -2: /*0x744190*/
      v19 = a1; /*0x7441f9*/
      v10 = *a2; /*0x7441fd*/
LABEL_8:
      v11 = (__int16)*a3; /*0x744201*/
      break; /*0x744206*/
    case -1: /*0x744190*/
      v19 = a1; /*0x744208*/
      v10 = *(char *)a2; /*0x74420c*/
LABEL_10:
      v11 = *(char *)a3; /*0x744210*/
      break; /*0x744215*/
    case 1: /*0x744190*/
      v19 = a1; /*0x744217*/
      v10 = *(unsigned __int8 *)a2; /*0x74421b*/
LABEL_12:
      v11 = *(unsigned __int8 *)a3; /*0x74421f*/
      break; /*0x744224*/
    case 2: /*0x744190*/
      v19 = a1; /*0x744226*/
      v10 = (unsigned __int16)*a2; /*0x74422a*/
LABEL_14:
      v11 = *a3; /*0x74422e*/
      break; /*0x74422e*/
    default:
      v19 = a1; /*0x74419b*/
      v10 = 0; /*0x7441b6*/
      MyAssertHandler( /*0x7441b9*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/../qcommon/msg.h",
        521,
        0,
        (unsigned int)"unknown field size",
        a5,
        a6);
LABEL_4:
      switch ( v9 ) /*0x7441d1*/
      {
        case 0: /*0x7441d1*/
        case 8: /*0x7441d1*/
          v11 = *(_DWORD *)a3; /*0x7441d3*/
          break; /*0x7441d7*/
        case 2: /*0x7441d1*/
          goto LABEL_8;
        case 3: /*0x7441d1*/
          goto LABEL_10;
        case 5: /*0x7441d1*/
          goto LABEL_12;
        case 6: /*0x7441d1*/
          goto LABEL_14;
        default:
          v11 = 0; /*0x7441f0*/
          MyAssertHandler( /*0x7441f2*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/../qcommon/msg.h",
            521,
            0,
            (unsigned int)"unknown field size",
            a5,
            a6);
          break; /*0x7441f7*/
      }
      break; /*0x7441f7*/
  }
  if ( 32 - __lzcnt(v11 ^ (v11 >> 31)) > a4 + (v11 >> 31) )
  {
    Com_PrintError(1, (unsigned int)"Not enough bits written: %d for %s (%d)\n", v11, a6, a4, a6);
    v14 = va((unsigned int)"Not enough bits written: %d for %s (%d)\n", v11, a6, a4, v12, v13);
    MyAssertHandler((unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp", 1536, 0, v14, v15, v16); /*0x744291*/
  }
  v17 = v10 ^ v11; /*0x744296*/
  if ( a4 != 32 && a4 >= 0 ) /*0x7442a2*/
    v17 &= (1 << a4) - 1; /*0x7442b0*/
  return MSG_WriteValueNoXor(v19, v17, (unsigned int)a4, a6); /*0x7442c2*/
}