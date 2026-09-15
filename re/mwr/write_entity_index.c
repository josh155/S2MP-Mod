void __fastcall MSG_WriteEntityIndex(const char *a1, signed int a2, unsigned int a3, int a4, int a5, int a6)
{
  const char *v6; // r12
  int v9; // esi
  int v10; // ebx
  int v11; // edx
  int v12; // ecx
  int v13; // r8d
  int v14; // r9d
  __int64 v15; // rcx
  __int64 v16; // r8
  int v17; // r9d
  int v18; // edx
  int v19; // eax
  __int64 v20; // rsi
  __int64 v21; // rdx
  const char *v22; // rdi
  int v23; // r9d

  v6 = a1; /*0x73b13e*/
  if ( *((_DWORD *)a1 + 1) ) /*0x73b147*/
  {
    a1 = "D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp"; /*0x73b14f*/
    MyAssertHandler( /*0x73b16d*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
      735,
      0,
      (unsigned int)"%s",
      (unsigned int)"!msg->readOnly",
      a6);
  }
  if ( *(_BYTE *)(unk_BA57FB8 + 24LL) && (unsigned __int8)SV_IsSnapshotNetworkData(a1) ) /*0x73b183*/
  {
    a1 = (_BYTE *)(&dword_C + 3); /*0x73b198*/
    Com_Printf(15, (unsigned int)"Writing entity num %i (msg->lastEntityRef %d)\n", a2, *((_DWORD *)v6 + 11), a5, a6); /*0x73b1a2*/
  }
  v9 = *((_DWORD *)v6 + 11); /*0x73b1a7*/
  if ( v9 >= a2 ) /*0x73b1af*/
  {
    v10 = va((unsigned int)"lastEntityReferenced is %i, index is %i", v9, a2, a4, a5, a6); /*0x73b1c2*/
    a1 = "D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp"; /*0x73b1c5*/
    MyAssertHandler( /*0x73b1e9*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
      744,
      0,
      (unsigned int)"%s\n\t%s",
      (unsigned int)"index - msg->lastEntityRef > 0",
      v10);
    v9 = *((_DWORD *)v6 + 11); /*0x73b1ee*/
  }
  if ( a2 - v9 == 1 )
  {
    if ( *(_BYTE *)(unk_BA57FB8 + 24LL) && (unsigned __int8)SV_IsSnapshotNetworkData(a1) )
      Com_Printf(16, (unsigned int)"Wrote entity num: 1 bit (inc)\n", v11, v12, v13, v14);
    MSG_WriteBit1(v6); /*0x73b226*/
  }
  else
  {
    MSG_WriteBit0(v6); /*0x73b233*/
    if ( a3 == 11 && a2 - *((_DWORD *)v6 + 11) <= 511 )
    {
      if ( *(_BYTE *)(unk_BA57FB8 + 24LL) && (unsigned __int8)SV_IsSnapshotNetworkData(v6) )
        Com_Printf(16, (unsigned int)"Wrote entity num: %i bits (delta)\n", 11, v15, v16, v17);
      v18 = *((_DWORD *)v6 + 11); /*0x73b280*/
      if ( v18 >= a2 ) /*0x73b288*/
      {
        v19 = va((unsigned int)"index was %i, lastEntityRef is %i", a2, v18, v15, v16, v17); /*0x73b296*/
        MyAssertHandler( /*0x73b2c2*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
          766,
          0,
          (unsigned int)"%s\n\t(va( \"index was %i, lastEntityRef is %i\", index, msg->lastEntityRef )) = %i",
          (unsigned int)"(index - msg->lastEntityRef > 0)",
          v19);
      }
      MSG_WriteBit0(v6); /*0x73b2ca*/
      v20 = (unsigned int)(a2 - *((_DWORD *)v6 + 11)); /*0x73b2d2*/
      v21 = 9; /*0x73b2d7*/
      v22 = v6; /*0x73b2dc*/
    }
    else
    {
      if ( *(_BYTE *)(unk_BA57FB8 + 24LL) && (unsigned __int8)SV_IsSnapshotNetworkData(v6) )
        Com_Printf(16, (unsigned int)"Wrote entity num: %i bits (full)\n", a3 + 2, v15, v16, v23);
      if ( a3 == 11 ) /*0x73b30f*/
        MSG_WriteBit1(v6); /*0x73b314*/
      v22 = v6; /*0x73b319*/
      v20 = (unsigned int)a2; /*0x73b31c*/
      v21 = a3; /*0x73b31f*/
    }
    MSG_WriteBits(v22, v20, v21, v15, v16); /*0x73b322*/
  }
  *((_DWORD *)v6 + 11) = a2; /*0x73b327*/
}