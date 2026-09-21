__int64 __fastcall MSG_WriteEvent(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, int a6)
{
  __int64 v8; // rbx
  int EventParamBits; // eax
  unsigned int v10; // r14d
  int v11; // r12d
  __int64 v12; // r15
  __int64 result; // rax
  int v14; // edx
  __int64 v15; // rcx
  __int64 v16; // r8
  int v17; // r9d
  int v18; // esi
  __int64 v19; // rax
  unsigned int v20; // ebx
  __int64 v21; // r14
  int v22; // eax
  __int64 v23; // rdx
  __int64 v24; // rcx
  __int64 v25; // r8
  int v26; // r9d
  int v27; // edx
  int v28; // ecx
  int v29; // r8d
  int v30; // r9d
  int v31; // eax
  __int64 v32; // rcx
  __int64 v33; // r8
  int v34; // r9d
  int v35; // ebx
  __int64 v36; // rdi
  __int64 v37; // rdx
  int v38; // ebx
  __int64 v39; // r8
  char v40; // [rsp+Ch] [rbp-54h]
  __int64 v41; // [rsp+10h] [rbp-50h]
  __int64 v42; // [rsp+18h] [rbp-48h]

  if ( *(_DWORD *)(a2 + 4) ) /*0x73b366*/
    MyAssertHandler( /*0x73b38a*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
      920,
      0,
      (unsigned int)"%s",
      (unsigned int)"!msg->readOnly",
      a6);
  v8 = *(unsigned __int16 *)(a5 + 8); /*0x73b38f*/
  EventParamBits = MSG_GetEventParamBits(*(unsigned int *)(a4 + v8)); /*0x73b3a0*/
  if ( a6 != -1 && *(_BYTE *)(a1 + a6 + 46) ) /*0x73b3ae*/
  {
    v42 = v8; /*0x73b3b6*/
    *(_BYTE *)(a1 + a6 + 46) = 0; /*0x73b3ba*/
    v10 = EventParamBits; /*0x73b3c9*/
    v41 = a1; /*0x73b3cc*/
    v11 = -1; /*0x73b3d0*/
    v40 = 1; /*0x73b3e1*/
    if ( EventParamBits < 32 ) /*0x73b3e4*/
      v11 = ~(-1 << EventParamBits); /*0x73b3e4*/
    v12 = a4; /*0x73b3e8*/
LABEL_18:
    MSG_WriteBit1(a2); /*0x73b4d7*/
    MSG_WriteByte(a2, *(_DWORD *)(v12 + v42), v23, v24, v25, v26); /*0x73b4f1*/
    result = *(unsigned int *)(v12 + v42 + 4); /*0x73b4f6*/
    if ( v10 ) /*0x73b4fe*/
    {
      if ( (v11 & (unsigned int)result) != (_DWORD)result ) /*0x73b50b*/
      {
        v31 = va( /*0x73b520*/
                (unsigned int)"Event %d requires %d bit parameter, but has more than %d bits set",
                *(_DWORD *)(v12 + v42),
                v10,
                v10,
                v29,
                v30);
        MyAssertHandler( /*0x73b549*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
          981,
          0,
          (unsigned int)"%s\n\t%s",
          (unsigned int)"(toEvent->eventParm & mask) == toEvent->eventParm",
          v31);
      }
      if ( v40 || (v11 & (*(_DWORD *)(a3 + v42 + 4) ^ *(_DWORD *)(v12 + v42 + 4))) != 0 ) /*0x73b565*/
      {
        MSG_WriteBit1(a2); /*0x73b571*/
        result = MSG_WriteBits(a2, *(_DWORD *)(v12 + v42 + 4), v10, v32, v33, v34); /*0x73b581*/
        if ( !*(_BYTE *)(v41 + 29) && !*(_BYTE *)(v41 + 28) ) /*0x73b595*/
          return SV_TrackEventSend(1, 1, 8, v10, 2); /*0x73b5b8*/
        return result; /*0x73b5b8*/
      }
      result = MSG_WriteBit0(a2); /*0x73b68a*/
      if ( *(_BYTE *)(v41 + 29) || *(_BYTE *)(v41 + 28) ) /*0x73b69a*/
        return result; /*0x73b69f*/
      v36 = 1; /*0x73b6b0*/
      v37 = 8; /*0x73b6b7*/
      v39 = 2; /*0x73b6be*/
      return SV_TrackEventSend(v36, 0, v37, 0, v39); /*0x73b6d2*/
    }
    if ( (_DWORD)result ) /*0x73b5bf*/
    {
      v35 = va( /*0x73b5d3*/
              (unsigned int)"Event %d requires no parameter, but has a parameter set",
              *(_DWORD *)(v12 + v42),
              v27,
              v28,
              v29,
              v30);
      result = MyAssertHandler( /*0x73b5fa*/
                 (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
                 976,
                 0,
                 (unsigned int)"%s\n\t%s",
                 (unsigned int)"toEvent->eventParm == 0",
                 v35);
    }
    if ( !*(_BYTE *)(v41 + 29) && !*(_BYTE *)(v41 + 28) ) /*0x73b60e*/
    {
      v36 = 1; /*0x73b619*/
      v37 = 8; /*0x73b620*/
LABEL_36:
      v39 = 1; /*0x73b67d*/
      return SV_TrackEventSend(v36, 0, v37, 0, v39); /*0x73b685*/
    }
    return result; /*0x73b613*/
  }
  v10 = EventParamBits; /*0x73b3fa*/
  v11 = -1; /*0x73b3fd*/
  if ( EventParamBits < 32 ) /*0x73b410*/
    v11 = ~(-1 << EventParamBits); /*0x73b410*/
  v12 = a4; /*0x73b414*/
  if ( *(_DWORD *)(a3 + v8) != *(_DWORD *)(a4 + v8) ) /*0x73b41f*/
  {
    v42 = v8; /*0x73b4c8*/
    v41 = a1; /*0x73b4cc*/
    v40 = 0; /*0x73b4d0*/
    goto LABEL_18; /*0x73b4d0*/
  }
  result = MSG_WriteBit0(a2); /*0x73b429*/
  v18 = *(_DWORD *)(a4 + v8 + 4); /*0x73b42e*/
  if ( v10 ) /*0x73b436*/
  {
    v19 = v8; /*0x73b43f*/
    v20 = v10; /*0x73b442*/
    if ( (v18 & v11) != v18 ) /*0x73b448*/
    {
      v21 = v19; /*0x73b44a*/
      v22 = va( /*0x73b45e*/
              (unsigned int)"Event %d requires %d bit parameter, but has more than %d bits set",
              *(_DWORD *)(a4 + v19),
              v20,
              v20,
              v16,
              v17);
      MyAssertHandler( /*0x73b487*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
        962,
        0,
        (unsigned int)"%s\n\t%s",
        (unsigned int)"(toEvent->eventParm & mask) == toEvent->eventParm",
        v22);
      v18 = *(_DWORD *)(a4 + v21 + 4); /*0x73b48c*/
    }
    result = MSG_WriteBits(a2, v18, v20, v15, v16, v17); /*0x73b497*/
    if ( !*(_BYTE *)(a1 + 29) && !*(_BYTE *)(a1 + 28) ) /*0x73b4a7*/
      return SV_TrackEventSend(0, 1, 0, v20, 1); /*0x73b4c3*/
  }
  else
  {
    if ( v18 ) /*0x73b629*/
    {
      v38 = va( /*0x73b63d*/
              (unsigned int)"Event %d requires no parameter, but has a parameter set",
              *(_DWORD *)(a4 + v8),
              v14,
              v15,
              v16,
              v17);
      result = MyAssertHandler( /*0x73b664*/
                 (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
                 956,
                 0,
                 (unsigned int)"%s\n\t%s",
                 (unsigned int)"toEvent->eventParm == 0",
                 v38);
    }
    if ( !*(_BYTE *)(a1 + 29) && !*(_BYTE *)(a1 + 28) ) /*0x73b670*/
    {
      v36 = 0; /*0x73b677*/
      v37 = 0; /*0x73b67b*/
      goto LABEL_36; /*0x73b67b*/
    }
  }
  return result; /*0x73b6a1*/
}