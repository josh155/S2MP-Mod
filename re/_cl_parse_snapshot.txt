void *__cdecl CL_ParseSnapshot(int a1, _DWORD *a2)
{
  int Byte; // edx
  int v3; // ebx
  _DWORD *v4; // ecx
  void *result; // eax
  void *v6; // ebx
  int v7; // edi
  _DWORD *v8; // eax
  int EntityIndex; // esi
  const char *EntityTypeName; // eax
  void **v11; // edi
  void *v12; // ebx
  _DWORD *v13; // eax
  int v14; // esi
  int v15; // ebx
  int v16; // edx
  char *v17; // ecx
  int v18; // eax
  char v19; // [esp+8h] [ebp-F0h]
  int *v20; // [esp+40h] [ebp-B8h]
  void **v21; // [esp+44h] [ebp-B4h]
  double v22; // [esp+48h] [ebp-B0h]
  double v23; // [esp+50h] [ebp-A8h]
  double v24; // [esp+58h] [ebp-A0h]
  int v25; // [esp+64h] [ebp-94h]
  int v26; // [esp+68h] [ebp-90h]
  int v27; // [esp+6Ch] [ebp-8Ch]
  int v28[25]; // [esp+78h] [ebp-80h] BYREF

  memset(&CL_ParseSnapshot(int,msg_t *)::newSnap, 0, 0x2F94u); /*0xc4e89*/
  dword_4943F0 = dword_13A57B8; /*0xc4e9a*/
  dword_491468 = MSG_ReadLong(a2); /*0xc4ead*/
  dword_49146C = *(_DWORD *)((char *)&loc_20134 + (_DWORD)&clientConnections); /*0xc4eb8*/
  Byte = MSG_ReadByte(a2); /*0xc4ecb*/
  if ( Byte ) /*0xc4ecf*/
    dword_491470 = dword_49146C - Byte; /*0xc4f6e*/
  else
    dword_491470 = -1; /*0xc4ed5*/
  dword_491464 = MSG_ReadByte(a2); /*0xc4eed*/
  if ( dword_491470 <= 0 ) /*0xc4efa*/
  {
    CL_ParseSnapshot(int,msg_t *)::newSnap = 1; /*0xc4fec*/
    dword_13C5818 = 0; /*0xc4ffc*/
    v20 = 0; /*0xc5006*/
  }
  else
  {
    v3 = 12180 * (dword_491470 & 0x1F); /*0xc4f05*/
    v4 = (_DWORD *)((char *)&clients + v3); /*0xc4f10*/
    if ( !*(_DWORD *)((char *)&clients + v3 + 432208) ) /*0xc4f1b*/
    {
      Com_PrintError(14, "Delta from invalid frame (not supposed to happen!).\n"); /*0xc4fd4*/
      return (void *)MSG_Discard(a2); /*0xc4fe7*/
    }
    if ( dword_491470 != v4[108055] ) /*0xc4f27*/
    {
      Com_DPrintf(14, "Delta frame too old.\n"); /*0xc4f38*/
      return (void *)MSG_Discard(a2); /*0xc4f46*/
    }
    if ( *(_DWORD *)&word_11F90C8 - v4[111094] > 1920 ) /*0xc4f8f*/
    {
      Com_DPrintf(14, "Delta parseEntitiesNum too old.\n"); /*0xc5bd8*/
      return (void *)MSG_Discard(a2); /*0xc5beb*/
    }
    if ( *(_DWORD *)&word_11F90CC - v4[111095] > 1920 ) /*0xc4fa6*/
    {
      Com_DPrintf(14, "Delta parseClientsNum too old.\n"); /*0xc5cc9*/
      return (void *)MSG_Discard(a2); /*0xc5cc9*/
    }
    v20 = (int *)((char *)&clients + v3 + 432208); /*0xc4fb3*/
    CL_ParseSnapshot(int,msg_t *)::newSnap = 1; /*0xc4fb9*/
  }
  if ( *(int *)(cl_shownet + 12) > 1 ) /*0xc501c*/
    Com_Printf(14, "%3i:%s\n", a2[7] - 1, "playerstate"); /*0xc5043*/
  if ( v20 ) /*0xc5050*/
    MSG_ReadDeltaPlayerstate(a1, (int)a2, dword_491468, v20 + 7, &unk_49147C, 1); /*0xc508c*/
  else
    MSG_ReadDeltaPlayerstate(a1, (int)a2, dword_491468, 0, &unk_49147C, 1); /*0xc5cb7*/
  MSG_ClearLastReferencedEntity(a2); /*0xc509a*/
  if ( *(int *)(cl_shownet + 12) > 1 ) /*0xc50ab*/
    Com_Printf(14, "%3i:%s\n", a2[7] - 1, "packet entities"); /*0xc50cc*/
  v25 = dword_491468; /*0xc50d7*/
  dword_4943E8 = *(_DWORD *)&word_11F90C8; /*0xc50e9*/
  dword_4943E0 = 0; /*0xc50ee*/
  if ( v20 && v20[3040] > 0 ) /*0xc5114*/
  {
    v21 = (void **)((char *)&clients + 244 * (v20[3042] & 0x7FF) + 1071824); /*0xc5132*/
    v6 = *v21; /*0xc5138*/
  }
  else
  {
    v21 = 0; /*0xc5c50*/
    v6 = &loc_1869F; /*0xc5c5a*/
  }
  v7 = 0; /*0xc513f*/
LABEL_25:
  v8 = a2; /*0xc5141*/
  while ( !*a2 )
  {
    EntityIndex = MSG_ReadEntityIndex(v8, 10); /*0xc5161*/
    if ( EntityIndex == 1023 ) /*0xc5168*/
      break; /*0xc5168*/
    if ( a2[7] > a2[5] )
      Com_Error(2, "\x15CL_ParsePacketEntities: end of message", v19);
LABEL_29:
    if ( (int)v6 < EntityIndex )
    {
      while ( !*a2 )
      {
        if ( *(_DWORD *)(cl_shownet + 12) == 3 )
          Com_Printf(14, "%3i:  unchanged: %i\n", a2[7], v6);
        memcpy((char *)&clients + 244 * (word_11F90C8 & 0x7FF) + 1071824, v21, 0xF4u); /*0xc51dd*/
        ++*(_DWORD *)&word_11F90C8; /*0xc51e7*/
        ++dword_4943E0; /*0xc51ed*/
        ++v7; /*0xc51f3*/
        v6 = &loc_1869F; /*0xc51f4*/
        if ( v7 >= v20[3040] ) /*0xc5205*/
          goto LABEL_29; /*0xc5205*/
        v21 = (void **)((char *)&clients + 244 * ((v20[3042] + v7) & 0x7FF) + 1071824); /*0xc5227*/
        v6 = *v21; /*0xc5233*/
        if ( (int)*v21 >= EntityIndex ) /*0xc523c*/
          break; /*0xc523c*/
      }
    }
    if ( v6 == (void *)EntityIndex )
    {
      if ( *(_DWORD *)(cl_shownet + 12) == 3 )
        Com_Printf(14, "%3i:  delta: %i\n", a2[7], v6);
      if ( !MSG_ReadDeltaEntity((int)a2, v25, v21, (char *)&clients + 244 * (word_11F90C8 & 0x7FF) + 1071824, (int)v6) ) /*0xc5928*/
      {
        ++*(_DWORD *)&word_11F90C8; /*0xc5937*/
        ++dword_4943E0; /*0xc593d*/
      }
      ++v7; /*0xc5943*/
      v6 = &loc_1869F; /*0xc5944*/
      if ( v7 < v20[3040] ) /*0xc5955*/
      {
        v21 = (void **)((char *)&clients + 244 * ((v20[3042] + v7) & 0x7FF) + 1071824); /*0xc597d*/
        v6 = *v21; /*0xc5989*/
      }
      goto LABEL_25; /*0xc5990*/
    }
    if ( *(_DWORD *)(cl_shownet + 12) == 3 )
      Com_Printf(14, "%3i:  baseline: %i\n", a2[7], EntityIndex);
    if ( MSG_ReadDeltaEntity( /*0xc52a6*/
           (int)a2,
           v25,
           (char *)&loc_C8AD0 + (_DWORD)&clients + 244 * EntityIndex,
           (char *)&clients + 244 * (word_11F90C8 & 0x7FF) + 1071824,
           EntityIndex) )
    {
      goto LABEL_25; /*0xc52ad*/
    }
    ++*(_DWORD *)&word_11F90C8; /*0xc52b9*/
    ++dword_4943E0; /*0xc52bf*/
    v8 = a2; /*0xc52c5*/
  }
  if ( v6 != &loc_1869F && !*a2 )
  {
    do
    {
      if ( *(_DWORD *)(cl_shownet + 12) == 3 )
        Com_Printf(14, "%3i:  unchanged: %i\n", a2[7], v6);
      memcpy((char *)&clients + 244 * (word_11F90C8 & 0x7FF) + 1071824, v21, 0xF4u); /*0xc535a*/
      ++*(_DWORD *)&word_11F90C8; /*0xc5365*/
      ++dword_4943E0; /*0xc536b*/
      ++v7; /*0xc5371*/
      v6 = &loc_1869F; /*0xc5372*/
      if ( v7 < v20[3040] ) /*0xc5383*/
      {
        v21 = (void **)((char *)&clients + 244 * ((v20[3042] + v7) & 0x7FF) + 1071824); /*0xc53a1*/
        v6 = *v21; /*0xc53ad*/
      }
      if ( *(_BYTE *)(msg_dumpEnts + 12) )
      {
        v24 = *((float *)v21 + 8); /*0xc53cb*/
        v23 = *((float *)v21 + 7); /*0xc53d8*/
        v22 = *((float *)v21 + 6); /*0xc53e5*/
        EntityTypeName = (const char *)BG_GetEntityTypeName((int)v21[1]); /*0xc53f3*/
        Com_Printf(14, "%3i: unchanged ent, eType %s at %f, %f, %f\n", v6, EntityTypeName, v22, v23, v24);
        if ( v6 == &loc_1869F ) /*0xc5444*/
          break; /*0xc5444*/
      }
      else if ( v6 == &loc_1869F ) /*0xc52ff*/
      {
        break; /*0xc52ff*/
      }
    }
    while ( !*a2 );
  }
  if ( *(_BYTE *)(cl_shownuments + 12) || *(_BYTE *)(msg_dumpEnts + 12) )
    Com_Printf(14, "Entities in packet: %i\n", dword_4943E0);
  MSG_ClearLastReferencedEntity(a2); /*0xc5476*/
  if ( *(int *)(cl_shownet + 12) > 1 ) /*0xc5487*/
    Com_Printf(14, "%3i:%s\n", a2[7] - 1, "packet clients"); /*0xc54ae*/
  v27 = dword_491468; /*0xc54b9*/
  dword_4943EC = *(_DWORD *)&word_11F90CC; /*0xc54cb*/
  dword_4943E4 = 0; /*0xc54d0*/
  if ( v20 && v20[3041] > 0 ) /*0xc54f6*/
  {
    v11 = (void **)((char *)&clients + 100 * (v20[3043] & 0x7FF) + 1571536); /*0xc550c*/
    v12 = *v11; /*0xc5513*/
  }
  else
  {
    v11 = 0; /*0xc5c44*/
    v12 = &loc_1869F; /*0xc5c46*/
  }
  v26 = 0; /*0xc551a*/
LABEL_59:
  v13 = a2; /*0xc5524*/
  if ( !*a2 )
  {
    while ( MSG_ReadBit(v13) )
    {
      v14 = MSG_ReadEntityIndex(a2, 6); /*0xc555a*/
      if ( a2[7] > a2[5] )
        Com_Error(2, "\x15CL_ParsePacketClients: end of message", v19);
      while ( (int)v12 < v14 )
      {
        while ( 1 )
        {
          if ( *(_DWORD *)(cl_shownet + 12) == 3 )
            Com_Printf(14, "%3i:  unchanged: %i\n", a2[7], v12);
          memcpy((char *)&clients + 100 * (word_11F90CC & 0x7FF) + 1571536, v11, 0x64u); /*0xc55b4*/
          ++*(_DWORD *)&word_11F90CC; /*0xc55bf*/
          ++dword_4943E4; /*0xc55c5*/
          ++v26; /*0xc55cb*/
          v12 = &loc_1869F; /*0xc55d1*/
          if ( v26 >= v20[3041] ) /*0xc55e8*/
            break; /*0xc55e8*/
          v11 = (void **)((char *)&clients + 100 * ((v20[3043] + v26) & 0x7FF) + 1571536); /*0xc5602*/
          v12 = *v11; /*0xc5609*/
          if ( (int)*v11 >= v14 ) /*0xc5612*/
            goto LABEL_68; /*0xc5612*/
        }
      }
LABEL_68:
      if ( v12 == (void *)v14 )
      {
        if ( *(_DWORD *)(cl_shownet + 12) == 3 )
          Com_Printf(14, "%3i:  delta: %i\n", a2[7], v12);
        if ( !MSG_ReadDeltaClient( /*0xc5a7f*/
                (int)a2,
                v27,
                (int)v11,
                (char *)&clients + 100 * (word_11F90CC & 0x7FF) + 1571536,
                (int)v12) )
        {
          ++*(_DWORD *)&word_11F90CC; /*0xc5a8e*/
          ++dword_4943E4; /*0xc5a94*/
        }
        ++v26; /*0xc5a9a*/
        v12 = &loc_1869F; /*0xc5aa0*/
        if ( v26 < v20[3041] ) /*0xc5ab7*/
        {
          v11 = (void **)((char *)&clients + 100 * ((v20[3043] + v26) & 0x7FF) + 1571536); /*0xc5ad5*/
          v12 = *v11; /*0xc5adc*/
        }
        goto LABEL_59; /*0xc5ae3*/
      }
      if ( *(_DWORD *)(cl_shownet + 12) == 3 )
        Com_Printf(14, "%3i:  baseline: %i\n", a2[7], v14);
      memset(v28, 0, sizeof(v28)); /*0xc5648*/
      if ( MSG_ReadDeltaClient((int)a2, v27, (int)v28, (char *)&clients + 100 * (word_11F90CC & 0x7FF) + 1571536, v14) ) /*0xc568a*/
        goto LABEL_59; /*0xc5691*/
      ++*(_DWORD *)&word_11F90CC; /*0xc569d*/
      ++dword_4943E4; /*0xc56a3*/
      v13 = a2; /*0xc56a9*/
      if ( *a2 ) /*0xc56af*/
        break; /*0xc56b3*/
    }
  }
  if ( v12 != &loc_1869F && !*a2 )
  {
    if ( *(_DWORD *)(cl_shownet + 12) == 3 ) /*0xc56d9*/
      goto LABEL_108; /*0xc56d9*/
    while ( 1 )
    {
      memcpy((char *)&clients + 100 * (word_11F90CC & 0x7FF) + 1571536, v11, 0x64u); /*0xc5709*/
      ++*(_DWORD *)&word_11F90CC; /*0xc5714*/
      ++dword_4943E4; /*0xc571a*/
      if ( ++v26 >= v20[3041] ) /*0xc5738*/
        break; /*0xc5738*/
      v18 = 100 * ((v20[3043] + v26) & 0x7FF); /*0xc5af7*/
      v12 = *(void **)((char *)&clients + v18 + 1571536); /*0xc5afa*/
      if ( v12 == &loc_1869F || *a2 ) /*0xc5b13*/
        break; /*0xc5b13*/
      v11 = (void **)((char *)&clients + v18 + 1571536); /*0xc5b23*/
      if ( *(_DWORD *)(cl_shownet + 12) == 3 )
LABEL_108:
        Com_Printf(14, "%3i:  unchanged: %i\n", a2[7], v12);
    }
  }
  result = (void *)cl_shownuments; /*0xc5744*/
  if ( *(_BYTE *)(cl_shownuments + 12) )
    result = (void *)Com_Printf(14, "Clients in packet: %i\n", dword_4943E4);
  if ( *a2 ) /*0xc5756*/
  {
    CL_ParseSnapshot(int,msg_t *)::newSnap = 0; /*0xc5bba*/
  }
  else if ( CL_ParseSnapshot(int,msg_t *)::newSnap ) /*0xc5768*/
  {
    v15 = dword_11D3AB4[0] + 1; /*0xc5776*/
    if ( dword_49146C - (dword_11D3AB4[0] + 1) >= 32 ) /*0xc5786*/
      v15 = dword_49146C - 31; /*0xc5786*/
    for ( ; dword_49146C > v15; ++v15 ) /*0xc578b*/
      *((_DWORD *)&clients + 3045 * (v15 & 0x1F) + 108052) = 0; /*0xc579e*/
    dword_11D6A40[4] = unk_11D3AB0; /*0xc57bb*/
    memcpy(&unk_11D3AA8, &CL_ParseSnapshot(int,msg_t *)::newSnap, 0x2F94u); /*0xc57d9*/
    dword_11D3AB4[2] = 999; /*0xc57e4*/
    v16 = 1; /*0xc57f9*/
    while ( 1 ) /*0xc5816*/
    {
      v17 = (char *)&clients + 12 * ((unk_13C5838 - (_BYTE)v16) & 0x1F); /*0xc5816*/
      if ( dword_11D3AB4[4] >= *((_DWORD *)v17 + 107957) ) /*0xc581f*/
        break; /*0xc581f*/
      if ( ++v16 == 33 ) /*0xc5804*/
        goto LABEL_89; /*0xc5804*/
    }
    dword_11D3AB4[2] = dword_13E77D8 - *(_DWORD *)((char *)&loc_696D8 + (_DWORD)v17); /*0xc5832*/
LABEL_89:
    memcpy((char *)&clients + 12180 * (dword_11D3AB4[0] & 0x1F) + 432208, &unk_11D3AA8, 0x2F94u); /*0xc5835*/
    if ( *(_DWORD *)(cl_shownet + 12) == 3 ) /*0xc5871*/
      Com_Printf(14, "   snapshot:%i  delta:%i  ping:%i\n", dword_11D3AB4[0], dword_11D3AB4[1], dword_11D3AB4[2]); /*0xc5cf8*/
    result = &clients; /*0xc5877*/
    dword_11D6A40[6] = 1; /*0xc587c*/
  }
  return result; /*0xc4f5c*/
}