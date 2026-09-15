void __fastcall MSG_WriteAnimData(__int64 a1, _DWORD *a2, _DWORD *a3, __int64 a4, __int64 a5, int a6)
{
  __int64 v7; // rcx
  __int64 v8; // r8
  __int64 v9; // rcx
  __int64 v10; // r8
  __int64 v11; // rcx
  __int64 v12; // r8
  __int64 v13; // rdx
  __int64 v14; // rsi
  __int64 v15; // rcx
  unsigned int MinBitCountForNum; // r12d
  __int64 v17; // rcx
  __int64 v18; // r8
  unsigned int v19; // r15d

  if ( (*(_BYTE *)a3 & 1) == 0 ) /*0x73ba27*/
  {
    MSG_WriteBit0(a1); /*0x73ba2c*/
    if ( ((*a3 ^ *a2) & 0x7FF800) != 0 ) /*0x73ba3e*/
    {
      MSG_WriteBit1(a1); /*0x73ba44*/
      MSG_WriteBits(a1, (*a3 >> 11) & 0xFFF, 12, v7, v8); /*0x73ba5b*/
    }
    else
    {
      MSG_WriteBit0(a1); /*0x73bac6*/
    }
    if ( ((*(_WORD *)a3 ^ *(_WORD *)a2) & 0x7FE) != 0 ) /*0x73bad4*/
    {
      MSG_WriteBit1(a1); /*0x73badd*/
      v13 = 10; /*0x73bae7*/
      v14 = (*a3 >> 1) & 0x3FF; /*0x73baef*/
LABEL_19:
      MSG_WriteBits(a1, v14, v13, v11, v12); /*0x73bbaf*/
      return; /*0x73bbb7*/
    }
LABEL_20:
    MSG_WriteBit0(a1); /*0x73bbbc*/
    return; /*0x73bbc7*/
  }
  if ( !dword_D178D80[0] ) /*0x73ba6c*/
    MyAssertHandler( /*0x73ba8c*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
      1756,
      0,
      (unsigned int)"%s",
      (unsigned int)"svsHeaderValid",
      a6);
  MSG_WriteBit1(a1); /*0x73ba94*/
  if ( ((*a2 ^ *a3) & 0x1E000) != 0 ) /*0x73baa6*/
  {
    MSG_WriteBit1(a1); /*0x73baa8*/
    MSG_WriteBits(a1, (*a3 >> 13) & 0xF, 4, v9, v10); /*0x73babf*/
  }
  else
  {
    MSG_WriteBit0(a1); /*0x73baf9*/
  }
  v15 = (*a3 >> 13) & 0xF; /*0x73bb0c*/
  if ( *((_BYTE *)&word_D178E00 + v15 + 320) ) /*0x73bb11*/
  {
    if ( ((*(_BYTE *)a2 ^ (unsigned __int8)*a3) & 0xFE) != 0 ) /*0x73bb22*/
    {
      MinBitCountForNum = GetMinBitCountForNum(*((unsigned __int8 *)&word_D178E00 + v15 + 320)); /*0x73bb2c*/
      MSG_WriteBit1(a1); /*0x73bb2f*/
      MSG_WriteBits(a1, (*a3 >> 1) & 0x7F, MinBitCountForNum, v17, v18); /*0x73bb44*/
    }
    else
    {
      MSG_WriteBit0(a1); /*0x73bb57*/
    }
    if ( ((*(_WORD *)a3 ^ *(_WORD *)a2) & 0x1F00) != 0 ) /*0x73bb66*/
    {
      v19 = GetMinBitCountForNum(*(unsigned __int8 *)(((unsigned __int8)*a3 >> 1) /*0x73bb97*/
                                                    + GOT__svsHeader
                                                    + ((unsigned __int64)((*a3 >> 13) & 0xF) << 7)
                                                    + 336));
      MSG_WriteBit1(a1); /*0x73bb9a*/
      v13 = v19; /*0x73bba7*/
      v14 = (*a3 >> 8) & 0x1F; /*0x73bbaa*/
      goto LABEL_19; /*0x73bbaa*/
    }
    goto LABEL_20; /*0x73bb66*/
  }
}