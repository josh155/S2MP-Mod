int __cdecl SV_SendClientGameState(int a1)
{
  int result; // eax
  int v2; // esi
  int v3; // edi
  int v4; // ebx
  int v5; // edi
  int v6; // ebx
  unsigned __int16 v7; // ax
  char *v8; // ebx
  int v9; // edi
  _DWORD *v10; // esi
  int i; // ebx
  int *v12; // ebx
  const char *v13; // eax
  int v14; // [esp+24h] [ebp-154h]
  char *v15; // [esp+28h] [ebp-150h]
  int v16; // [esp+2Ch] [ebp-14Ch]
  _BYTE v17[244]; // [esp+34h] [ebp-144h] BYREF
  int v18[10]; // [esp+128h] [ebp-50h] BYREF
  _DWORD v19[3]; // [esp+150h] [ebp-28h] BYREF
  char v20; // [esp+15Ch] [ebp-1Ch]

  while ( *(_DWORD *)a1 && *(_DWORD *)(a1 + 64) ) /*0x1bd225*/
    SV_Netchan_TransmitNextFragment(a1, a1 + 16); /*0x1bd251*/
  if ( *(_DWORD *)(a1 + 658716) ) /*0x1bd262*/
  {
    memset((void *)(a1 + 669233), 0, 0x2000u); /*0x1bd2a4*/
    *(_BYTE *)(a1 + 677425) = 127; /*0x1bd2ac*/
  }
  else
  {
    result = *(unsigned __int8 *)(a1 + 677425); /*0x1bd26e*/
    if ( (_BYTE)result != 127 ) /*0x1bd277*/
    {
      if ( !(_BYTE)result ) /*0x1bd27b*/
        return NET_OutOfBandPrint(1, *(_DWORD *)(a1 + 32), *(_DWORD *)(a1 + 36), *(_DWORD *)(a1 + 40), "requeststats\n"); /*0x1bd7d8*/
      return result; /*0x1bd7d8*/
    }
  }
  SV_SetServerStaticHeader(); /*0x1bd2b3*/
  Com_DPrintf(15, "SV_SendClientGameState() for %s\n", (const char *)(a1 + 135816)); /*0x1bd2d4*/
  Com_DPrintf(15, "Going from CS_CONNECTED to CS_CLIENTLOADING for %s\n", (const char *)(a1 + 135816)); /*0x1bd2ec*/
  *(_DWORD *)a1 = 3; /*0x1bd2f4*/
  *(_DWORD *)(a1 + 525556) = 0; /*0x1bd2fa*/
  *(_DWORD *)(a1 + 134744) = *(_DWORD *)(a1 + 16); /*0x1bd30a*/
  MSG_Init(v18, (int)&SV_SendClientGameState(client_t *)::msgBuffer, (int)&loc_20000); /*0x1bd326*/
  MSG_ClearLastReferencedEntity((int)v18); /*0x1bd331*/
  MSG_WriteLong(v18, *(_DWORD *)(a1 + 134784)); /*0x1bd349*/
  SV_UpdateServerCommandsToClient(a1, v18); /*0x1bd35b*/
  MSG_WriteByte(v18, 1); /*0x1bd36e*/
  MSG_WriteLong(v18, *(_DWORD *)(a1 + 134728)); /*0x1bd386*/
  MSG_WriteByte(v18, 2); /*0x1bd399*/
  v2 = 0; /*0x1bd39e*/
  v14 = 0; /*0x1bd3a0*/
  v3 = 0; /*0x1bd3aa*/
  do /*0x1bd450*/
  {
    while ( 1 ) /*0x1bd3dc*/
    {
      v4 = 4 * v14; /*0x1bd3dc*/
      if ( constantConfigStrings[4 * v14] == v2 ) /*0x1bd3e8*/
        break; /*0x1bd3e8*/
      v3 += *((_WORD *)&sv + v2++ + 1037) != unk_CCAE798; /*0x1bd3cb*/
      if ( v2 == 2442 ) /*0x1bd3d4*/
        goto LABEL_17; /*0x1bd3d4*/
    }
    v15 = (char *)SL_ConvertToString(*((unsigned __int16 *)&sv + v2 + 1037)); /*0x1bd400*/
    if ( constantConfigStrings[v4] <= 820 ) /*0x1bd412*/
    {
LABEL_15:
      v3 -= (strcmp((const char *)constantConfigStrings[4 * v14 + 1], v15) == 0) - 1; /*0x1bd418*/
      goto LABEL_16; /*0x1bd440*/
    }
    v12 = &constantConfigStrings[v4]; /*0x1bd690*/
    if ( I_stricmp((const char *)v12[1], v15) ) /*0x1bd698*/
    {
      ++v3; /*0x1bd6a1*/
    }
    else if ( *v12 <= 820 ) /*0x1bd6ad*/
    {
      goto LABEL_15; /*0x1bd6ad*/
    }
LABEL_16:
    ++v14; /*0x1bd443*/
    ++v2; /*0x1bd449*/
  }
  while ( v2 != 2442 ); /*0x1bd450*/
LABEL_17:
  MSG_WriteShort(v18, v3); /*0x1bd452*/
  LOWORD(v2) = 0; /*0x1bd461*/
  v16 = 0; /*0x1bd464*/
  v5 = -1; /*0x1bd46e*/
  do /*0x1bd510*/
  {
    while ( 1 ) /*0x1bd49c*/
    {
      v6 = constantConfigStrings[4 * v16]; /*0x1bd49c*/
      if ( v6 != v2 ) /*0x1bd4a1*/
        goto LABEL_20; /*0x1bd4a1*/
      ++v16; /*0x1bd6c0*/
      v13 = (const char *)SL_ConvertToString(*((unsigned __int16 *)&sv + v6 + 1037)); /*0x1bd6d7*/
      if ( v6 <= 820 ) /*0x1bd6e4*/
      {
        if ( !strcmp((const char *)constantConfigStrings[4 * v16 - 3], v13) ) /*0x1bd76a*/
          goto LABEL_18; /*0x1bd771*/
      }
      else if ( !I_stricmp((const char *)constantConfigStrings[4 * v16 - 3], v13) ) /*0x1bd707*/
      {
        goto LABEL_18; /*0x1bd707*/
      }
      if ( *((_WORD *)&sv + v6 + 1037) != unk_CCAE798 ) /*0x1bd722*/
        break; /*0x1bd722*/
      MSG_WriteBit0(v18); /*0x1bd77e*/
      MSG_WriteBits(v18, v6, 12); /*0x1bd795*/
      MSG_WriteBigString((int)v18, ""); /*0x1bd7a8*/
      v5 = v6; /*0x1bd7ad*/
LABEL_20:
      v7 = *((_WORD *)&sv + v2 + 1037); /*0x1bd4a7*/
      if ( v7 != unk_CCAE798 ) /*0x1bd4bc*/
        goto LABEL_21; /*0x1bd4bc*/
LABEL_18:
      if ( ++v2 == 2442 ) /*0x1bd487*/
        goto LABEL_24; /*0x1bd487*/
    }
    v7 = *((_WORD *)&sv + v6 + 1037); /*0x1bd724*/
LABEL_21:
    v8 = (char *)SL_ConvertToString(v7); /*0x1bd4be*/
    if ( v5 + 1 == v2 ) /*0x1bd4d0*/
    {
      MSG_WriteBit1(v18); /*0x1bd746*/
    }
    else
    {
      MSG_WriteBit0(v18); /*0x1bd4dc*/
      MSG_WriteBits(v18, v2, 12); /*0x1bd4f3*/
    }
    MSG_WriteBigString((int)v18, v8); /*0x1bd502*/
    v5 = v2++; /*0x1bd507*/
  }
  while ( v2 != 2442 ); /*0x1bd510*/
LABEL_24:
  v9 = 1125496133 * ((a1 - (int)&dword_1EEC48C) >> 2); /*0x1bd516*/
  memset(v17, 0, sizeof(v17)); /*0x1bd549*/
  v10 = &sv; /*0x1bd54e*/
  for ( i = 0; i != 1024; ++i ) /*0x1bd554*/
  {
    while ( !v10[1741] ) /*0x1bd57b*/
    {
      ++i; /*0x1bd560*/
      v10 += 94; /*0x1bd561*/
      if ( i == 1024 ) /*0x1bd56d*/
        goto LABEL_28; /*0x1bd56d*/
    }
    MSG_WriteByte(v18, 3); /*0x1bd58b*/
    v19[0] = 1125496133 * ((a1 - (int)&dword_1EEC48C) >> 2); /*0x1bd590*/
    v19[2] = -1; /*0x1bd593*/
    v20 = 1; /*0x1bd59a*/
    MSG_WriteEntity(v19, v18, 0, v17, (char *)&sv + 376 * i + 6964, 1); /*0x1bd5dc*/
    v20 = 0; /*0x1bd5e1*/
    v10 += 94; /*0x1bd5e6*/
  }
LABEL_28:
  MSG_WriteByte(v18, 7); /*0x1bd5f8*/
  MSG_WriteLong(v18, v9); /*0x1bd615*/
  MSG_WriteLong(v18, unk_CCADF94); /*0x1bd62d*/
  MSG_WriteByte(v18, 7); /*0x1bd640*/
  Com_DPrintf(15, "Sending %i bytes in gamestate to client: %i\n", v18[5], v9);
  SV_SendMessageToClient(v18, a1); /*0x1bd671*/
  return SV_GetServerStaticHeader(); /*0x1bd281*/
}