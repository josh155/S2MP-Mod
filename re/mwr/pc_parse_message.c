// CL_ParseMessage
// BASIS: string-anchor port from MWR-PS4 (2-h1_mp.elf, port 9999) - SAME GAME, real symbols.
// 1 anchor(s), each referenced by exactly ONE function on BOTH sides, all implying PS4 0x39bda0.
// anchors: 'matchdatadone'
// tier: single_weak
// call-graph corroboration (independent of strings): CONFIRMED - shared callees 0, shared callers 1
// NOTE: cross-binary port - only the NAME transfers, addresses differ.
__int64 __fastcall sub_341420(unsigned int a1, _DWORD *a2, __int64 a3, double a4)
{
  double v4; // xmm2_8
  __int64 result; // rax
  int v9; // eax

  if ( *a2 ) /*0x341434*/
    return sub_4EB190(a3); /*0x341434*/
  while ( 1 ) /*0x341458*/
  {
    result = MSG_ReadBits((__int64)a2, 3); /*0x341458*/
    if ( (_DWORD)result == 7 ) /*0x341460*/
      break; /*0x341460*/
    if ( !*a2 ) /*0x341466*/
    {
      switch ( (int)result ) /*0x341484*/
      {
        case 0: /*0x341484*/
          sub_1CCD40(); /*0x3414b8*/
          sub_59DCE0(); /*0x3414bd*/
          sub_3411A0(a1, (__int64)a2, v4, a4); /*0x3414c7*/
          sub_59DCE0(); /*0x3414cc*/
          break; /*0x3414d1*/
        case 2: /*0x341484*/
          sub_342470(a1, a2, 1); /*0x341491*/
          break; /*0x341496*/
        case 3: /*0x341484*/
          v9 = MSG_ReadBits((__int64)a2, 8); /*0x3414a3*/
          sub_342470(a1, a2, (unsigned int)(v9 + 1)); /*0x3414b1*/
          break; /*0x3414b6*/
        case 4: /*0x341484*/
          sub_3423D0(a1, a2); /*0x341527*/
          break; /*0x341527*/
        case 5: /*0x341484*/
          sub_4EB910((__int64)a2, (__int64)&byte_2ED25CC, 0x40u); /*0x3414f8*/
          sub_4EB570(a2, &unk_2ED260C, 1744); /*0x34150d*/
          CL_AddReliableCommand(a1, "matchdatadone"); /*0x34151b*/
          break; /*0x341520*/
        case 6: /*0x341484*/
          if ( SHIDWORD(qword_2EC82C4[0]) < 9 ) /*0x3414da*/
            return sub_4EB190(a3); /*0x3414da*/
          sub_342770(a1, a2); /*0x3414e1*/
          break; /*0x3414e6*/
        default:
          return sub_4EB190(a3);
      }
      if ( !*a2 ) /*0x34152c*/
        continue; /*0x34152c*/
    }
    return sub_4EB190(a3); /*0x34152f*/
  }
  if ( *a2 ) /*0x341537*/
    return sub_4EB190(a3); /*0x34153c*/
  return result; /*0x341544*/
}