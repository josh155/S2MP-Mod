int __cdecl CL_ParseServerMessage(int a1, _DWORD *a2)
{
  int v2; // ecx
  int v3; // edx
  int Byte; // ebx
  int result; // eax
  int Long; // ebx
  const char *String; // eax
  int v8; // eax
  unsigned int EntityIndex; // eax
  int v10; // ebx
  int v11; // esi
  int *v12; // edi
  const char *v13; // ebx
  size_t v14; // eax
  size_t v15; // esi
  const char *BigString; // esi
  size_t v17; // ebx
  int v18; // esi
  int *v19; // edi
  const char *v20; // ebx
  size_t v21; // eax
  size_t v22; // esi
  const char *ConfigString; // eax
  char v24; // [esp+8h] [ebp-180h]
  char v25; // [esp+8h] [ebp-180h]
  signed int Bits; // [esp+44h] [ebp-144h]
  int v27; // [esp+48h] [ebp-140h]
  int Short; // [esp+4Ch] [ebp-13Ch]
  char v29[244]; // [esp+54h] [ebp-134h] BYREF
  int v30[7]; // [esp+148h] [ebp-40h] BYREF
  int v31; // [esp+164h] [ebp-24h]

  if ( *(_DWORD *)(cl_shownet + 12) == 1 ) /*0xc5d28*/
  {
    Com_Printf(14, "%i ", a2[5]); /*0xc644a*/
  }
  else if ( *(int *)(cl_shownet + 12) > 1 ) /*0xc5d2e*/
  {
    Com_Printf(14, "------------------\n"); /*0xc5d3f*/
  }
  MSG_Init(v30, (int)&CL_ParseServerMessage(int,msg_t *)::msgCompressed_buf, (int)&loc_20000); /*0xc5d5a*/
  v2 = a2[7]; /*0xc5d62*/
  v3 = a2[5]; /*0xc5d65*/
  if ( v3 - v2 > (unsigned int)&loc_20000 ) /*0xc5d71*/
  {
    Com_Error(2, "Compressed msg overflow in CL_ParseServerMessage", v24); /*0xc641e*/
    v3 = a2[5]; /*0xc6426*/
    v2 = a2[7]; /*0xc6429*/
  }
  v30[5] = MSG_ReadBitsCompress( /*0xc5d93*/
             (const unsigned __int8 *)(a2[2] + v2),
             &CL_ParseServerMessage(int,msg_t *)::msgCompressed_buf,
             v3 - v2);
  while ( 1 )
  {
LABEL_7:
    if ( v30[0] ) /*0xc5de5*/
      return MSG_Discard(a2); /*0xc5de5*/
LABEL_8:
    Byte = MSG_ReadByte(v30); /*0xc5df6*/
    if ( Byte == 7 ) /*0xc5dfb*/
      break; /*0xc5dfb*/
    if ( *(int *)(cl_shownet + 12) > 1 ) /*0xc5e0d*/
    {
      if ( svc_strings[Byte] ) /*0xc5e0f*/
        Com_Printf(14, "%3i:%s\n", v31 - 1, svc_strings[Byte]); /*0xc5e39*/
      else
        Com_Printf(14, "%3i:BAD CMD %i\n", v31 - 1, Byte); /*0xc63dd*/
    }
    switch ( Byte )
    {
      case 0:
        continue;
      case 1:
        Con_Close(a1); /*0xc5f1e*/
        dword_13856A0 = 0; /*0xc5f28*/
        CL_ClearState(a1); /*0xc5f35*/
        MSG_ClearLastReferencedEntity(v30); /*0xc5f40*/
        dword_13E77F8 = 0; /*0xc5f4b*/
        dword_13E77FC = 0; /*0xc5f51*/
        dword_13E7800 = 0; /*0xc5f58*/
        dword_13A57B8 = MSG_ReadLong(v30); /*0xc5f70*/
        unk_11F9084 = 1; /*0xc5f7b*/
        break; /*0xc5f7b*/
      case 4:
        Long = MSG_ReadLong(v30); /*0xc5ecd*/
        String = (const char *)MSG_ReadString(v30); /*0xc5ed5*/
        if ( Long > dword_13A57B8 ) /*0xc5ee6*/
        {
          dword_13A57B8 = Long; /*0xc5eec*/
          I_strncpyz((char *)&clientConnections[256 * (Long & 0x7F) + 32848], String, 1024); /*0xc5f0e*/
        }
        continue; /*0xc5f13*/
      case 5:
        CL_ParseDownload(a1, (int)v30, v25); /*0xc5eb8*/
        continue; /*0xc5ebd*/
      case 6:
        CL_ParseSnapshot(a1, v30); /*0xc5e85*/
        if ( v30[0] ) /*0xc5e8f*/
          return MSG_Discard(a2); /*0xc5e8f*/
        goto LABEL_8; /*0xc5e8f*/
      default:
        Com_PrintError(1, "CL_ParseServerMessage: Illegible server message %d\n", Byte);
        return MSG_Discard(a2); /*0xc5e61*/
    }
    while ( 1 )
    {
      v8 = MSG_ReadByte(v30); /*0xc5f97*/
      if ( v8 == 7 ) /*0xc5f9f*/
        break; /*0xc5f9f*/
      while ( v8 != 2 )
      {
        if ( v8 != 3 )
        {
          Com_PrintError(1, "CL_ParseGamestate: bad command byte %d\n", v8);
          MSG_Discard(v30); /*0xc6405*/
          goto LABEL_7; /*0xc640a*/
        }
        EntityIndex = MSG_ReadEntityIndex(v30, 10); /*0xc5fc5*/
        v10 = EntityIndex; /*0xc5fca*/
        if ( EntityIndex > 0x3FF )
          Com_Error(2, "\x15Baseline number out of range: %i", EntityIndex);
        memset(v29, 0, sizeof(v29)); /*0xc5ff0*/
        MSG_ReadDeltaEntity(v30, 0, v29, (char *)&loc_C8AD0 + (_DWORD)&clients + 244 * v10, v10); /*0xc6028*/
        v8 = MSG_ReadByte(v30); /*0xc6033*/
        if ( v8 == 7 ) /*0xc603b*/
          goto LABEL_28; /*0xc603b*/
      }
      Short = MSG_ReadShort(v30); /*0xc6145*/
      v27 = 0; /*0xc614b*/
      if ( Short ) /*0xc6163*/
      {
        Bits = -1; /*0xc6169*/
        do /*0xc62b9*/
        {
          if ( MSG_ReadBit(v30) ) /*0xc6185*/
            ++Bits; /*0xc6192*/
          else
            Bits = MSG_ReadBits(v30, 12); /*0xc639e*/
          if ( (unsigned int)Bits > 0x989 ) /*0xc61a2*/
            Com_Error(2, "\x15configstring > MAX_CONFIGSTRINGS", v25); /*0xc6381*/
          v11 = constantConfigStrings[4 * v27]; /*0xc61b7*/
          if ( v11 && Bits > v11 ) /*0xc61c4*/
          {
            v12 = &constantConfigStrings[4 * v27 + 1]; /*0xc61c6*/
            do /*0xc61d9*/
            {
              v13 = (const char *)*v12; /*0xc61db*/
              v14 = strlen((const char *)*v12); /*0xc61e0*/
              *((_DWORD *)&clients + v11 + 3055) = unk_11F9084; /*0xc61f3*/
              v15 = v14 + 1; /*0xc61fa*/
              memcpy((char *)&unk_11D9084 + unk_11F9084, v13, v14 + 1); /*0xc6214*/
              unk_11F9084 += v15; /*0xc621e*/
              ++v27; /*0xc6224*/
              v11 = v12[3]; /*0xc622a*/
              if ( !v11 ) /*0xc622f*/
                break; /*0xc622f*/
              v12 += 4; /*0xc61d0*/
            }
            while ( Bits > v11 ); /*0xc61d9*/
          }
          v27 += Bits == v11; /*0xc623c*/
          BigString = (const char *)MSG_ReadBigString(v30); /*0xc624d*/
          v17 = strlen(BigString) + 1; /*0xc6257*/
          if ( (int)(unk_11F9084 + v17) > (int)&loc_20000 ) /*0xc626d*/
            Com_Error(2, "\x15MAX_GAMESTATE_CHARS exceeded", v25); /*0xc63b8*/
          *((_DWORD *)&clients + Bits + 3055) = unk_11F9084; /*0xc6285*/
          memcpy((char *)&unk_11D9084 + unk_11F9084, BigString, v17); /*0xc62a3*/
          unk_11F9084 += v17; /*0xc62ad*/
          --Short; /*0xc62b3*/
        }
        while ( Short ); /*0xc62b9*/
      }
      v18 = constantConfigStrings[4 * v27]; /*0xc62ce*/
      if ( v18 ) /*0xc62d3*/
      {
        v19 = &constantConfigStrings[4 * v27 + 1]; /*0xc62d5*/
        do /*0xc632a*/
        {
          v20 = (const char *)*v19; /*0xc62d9*/
          v21 = strlen((const char *)*v19); /*0xc62de*/
          *((_DWORD *)&clients + v18 + 3055) = unk_11F9084; /*0xc62f1*/
          v22 = v21 + 1; /*0xc62f8*/
          memcpy((char *)&unk_11D9084 + unk_11F9084, v20, v21 + 1); /*0xc6312*/
          unk_11F9084 += v22; /*0xc631c*/
          v18 = v19[3]; /*0xc6322*/
          v19 += 4; /*0xc6325*/
        }
        while ( v18 ); /*0xc632a*/
      }
      ConfigString = (const char *)CL_GetConfigString(a1, 12); /*0xc633a*/
      sscanf(ConfigString, "%f %f %f", &dword_13E77F8, &dword_13E77FC, &dword_13E7800); /*0xc6368*/
    }
LABEL_28:
    dword_1385684 = MSG_ReadLong(v30); /*0xc6041*/
    dword_13857A8 = MSG_ReadLong(v30); /*0xc6066*/
    if ( *(_BYTE *)(useFastFile + 12) ) /*0xc6073*/
      DB_SyncXAssets(); /*0xc64c1*/
    CL_SystemInfoChanged(a1); /*0xc6083*/
    dword_16C3D6C |= *(unsigned __int8 *)(fs_gameDirVar + 11); /*0xc6099*/
    if ( FS_NeedRestart(dword_13857A8) ) /*0xc60ae*/
      FS_Restart(a1, dword_13857A8); /*0xc64b7*/
    if ( *(_BYTE *)(net_lanauthorize + 12) || !Sys_IsLANAddress(dword_1385690, dword_1385694, *(_DWORD *)&dword_1385698) ) /*0xc60e2*/
      CL_RequestAuthorization(a1); /*0xc60f1*/
    CL_InitDownloads(a1); /*0xc60fc*/
    Dvar_SetInt(cl_paused, 0); /*0xc6113*/
  }
  if ( *(int *)(cl_shownet + 12) > 1 ) /*0xc6460*/
    Com_Printf(14, "%3i:%s\n", v31 - 1, "END OF MESSAGE"); /*0xc6481*/
  result = v30[0]; /*0xc6486*/
  if ( v30[0] ) /*0xc648b*/
    return MSG_Discard(a2); /*0xc6491*/
  return result; /*0xc5e66*/
}