int __cdecl MSG_ReadDeltaEntity(_DWORD *a1, int a2, char *a3, char *a4, int a5)
{
  int v5; // edx
  int v6; // ecx
  char v7; // bl
  int v8; // ecx
  int v9; // esi
  int v10; // ecx
  char v11; // bl
  int v12; // edx
  int v13; // eax
  char v14; // bl
  int v15; // edx
  int v16; // edx
  _DWORD *v17; // edi
  int v18; // eax
  char v19; // bl
  int v20; // edx
  int v21; // edx
  int v22; // edx
  int v23; // eax
  _DWORD *v24; // edi
  char v25; // bl
  int v26; // edx
  int v27; // edx
  int v28; // edx
  int v29; // eax
  _DWORD *v30; // edi
  char v31; // bl
  int v32; // edx
  int v33; // edx
  int v34; // edx
  int v35; // eax
  _DWORD *v36; // edi
  int v37; // ebx
  int v38; // edx
  int v39; // edx
  int v40; // edx
  int v41; // eax
  int v42; // ebx
  char v43; // di
  int v44; // edx
  int v45; // edx
  int v46; // edx
  int v47; // eax
  int v48; // edx
  unsigned int v49; // edi
  int v50; // eax
  int v52; // edx
  int v53; // eax
  int v54; // ecx
  const char **v55; // ebx
  int i; // esi
  int v57; // ecx
  int v58; // eax
  const char *EntityTypeName; // eax
  int v60; // [esp+2Ch] [ebp-3Ch]
  int v61; // [esp+2Ch] [ebp-3Ch]
  int v62; // [esp+2Ch] [ebp-3Ch]
  int v63; // [esp+2Ch] [ebp-3Ch]
  int v64; // [esp+2Ch] [ebp-3Ch]
  int v65; // [esp+34h] [ebp-34h]
  int v66; // [esp+38h] [ebp-30h]
  int *StateFieldListForEntityType; // [esp+3Ch] [ebp-2Ch]
  int v68; // [esp+40h] [ebp-28h]
  int v69; // [esp+44h] [ebp-24h]
  int v70; // [esp+48h] [ebp-20h]
  int v71; // [esp+4Ch] [ebp-1Ch]

  v5 = a1[8]; /*0x17cd2c*/
  v6 = v5; /*0x17cd2f*/
  v7 = v5 & 7; /*0x17cd33*/
  if ( (v5 & 7) != 0 ) /*0x17cd36*/
  {
    v9 = a1[5]; /*0x17d060*/
  }
  else
  {
    v8 = a1[7]; /*0x17cd3c*/
    v9 = a1[5]; /*0x17cd3f*/
    if ( v8 >= v9 + a1[6] ) /*0x17cd4b*/
    {
      *a1 = 1; /*0x17cd51*/
      v10 = v5; /*0x17cd57*/
      v11 = v5 & 7; /*0x17cd5b*/
      if ( (v5 & 7) != 0 ) /*0x17cd5e*/
        goto LABEL_4; /*0x17cd5e*/
      goto LABEL_48; /*0x17cd5e*/
    }
    a1[8] = 8 * v8; /*0x17d0d8*/
    ++a1[7]; /*0x17d0db*/
    v6 = 8 * v8; /*0x17d0de*/
  }
  v52 = v6 >> 3; /*0x17d065*/
  if ( v6 >> 3 >= v9 ) /*0x17d06a*/
    v53 = *(unsigned __int8 *)(a1[3] + v52 - v9); /*0x17d0c8*/
  else
    v53 = *(unsigned __int8 *)(a1[2] + v52); /*0x17d072*/
  v5 = v6 + 1; /*0x17d076*/
  a1[8] = v6 + 1; /*0x17d07c*/
  if ( ((v53 >> v7) & 1) != 0 )
  {
    if ( !cl_shownet ) /*0x17d203*/
      return 1; /*0x17d203*/
    v58 = *(_DWORD *)(cl_shownet + 12); /*0x17d205*/
    if ( v58 <= 1 && v58 != -1 ) /*0x17d254*/
      return 1; /*0x17d256*/
    Com_Printf(16, "%3i: #%-3i remove\n", a1[7], a5);
    return 1; /*0x17d262*/
  }
  v10 = v6 + 1; /*0x17d08b*/
  v11 = v5 & 7; /*0x17d08f*/
  if ( (v5 & 7) != 0 ) /*0x17d092*/
    goto LABEL_4; /*0x17d092*/
LABEL_48:
  v54 = a1[7]; /*0x17d098*/
  if ( v54 >= v9 + a1[6] ) /*0x17d0a7*/
  {
    *a1 = 1; /*0x17d0ad*/
    goto LABEL_7; /*0x17d0b3*/
  }
  a1[8] = 8 * v54; /*0x17d246*/
  ++a1[7]; /*0x17d249*/
  v10 = 8 * v54; /*0x17d24c*/
LABEL_4:
  v12 = v10 >> 3; /*0x17cd70*/
  if ( v10 >> 3 < v9 ) /*0x17cd77*/
    v13 = *(unsigned __int8 *)(a1[2] + v12); /*0x17d19e*/
  else
    v13 = *(unsigned __int8 *)(a1[3] + v12 - v9); /*0x17cd85*/
  v5 = v10 + 1; /*0x17cd89*/
  a1[8] = v10 + 1; /*0x17cd8f*/
  if ( ((v13 >> v11) & 1) == 0 ) /*0x17cd98*/
  {
    memcpy(a4, a3, 0xF4u); /*0x17d278*/
    return 0; /*0x17d286*/
  }
LABEL_7:
  v60 = v5; /*0x17cd9e*/
  v14 = v5 & 7; /*0x17cda3*/
  if ( (v5 & 7) == 0 ) /*0x17cda6*/
  {
    v15 = a1[7]; /*0x17cdab*/
    if ( v15 >= v9 + a1[6] ) /*0x17cdb7*/
      goto LABEL_77; /*0x17cdb7*/
    v5 = 8 * v15; /*0x17cdbd*/
    a1[8] = v5; /*0x17cdc0*/
    ++a1[7]; /*0x17cdc3*/
    v60 = v5; /*0x17cdc6*/
  }
  v16 = v5 >> 3; /*0x17cdc9*/
  if ( v16 >= v9 ) /*0x17cdce*/
  {
    v18 = *(unsigned __int8 *)(a1[3] + v16 - v9); /*0x17d18d*/
    v17 = a1; /*0x17d191*/
  }
  else
  {
    v17 = a1; /*0x17cdd4*/
    v18 = *(unsigned __int8 *)(a1[2] + v16); /*0x17cdda*/
  }
  v71 = (v18 >> v14) & 1; /*0x17cde5*/
  v61 = v60 + 1; /*0x17cdec*/
  v17[8] = v61; /*0x17cdef*/
  v19 = v61 & 7; /*0x17cdf2*/
  if ( (v61 & 7) == 0 ) /*0x17cdf5*/
  {
    v20 = v17[7]; /*0x17cdf7*/
    if ( v20 >= v9 + v17[6] ) /*0x17ce01*/
      goto LABEL_77; /*0x17ce01*/
    v21 = 8 * v20; /*0x17ce07*/
    v17[8] = v21; /*0x17ce0a*/
    ++v17[7]; /*0x17ce0d*/
    v61 = v21; /*0x17ce10*/
  }
  v22 = v61 >> 3; /*0x17ce16*/
  if ( v61 >> 3 >= v9 ) /*0x17ce1b*/
  {
    v24 = a1; /*0x17d1a9*/
    v23 = *(unsigned __int8 *)(a1[3] + v22 - v9); /*0x17d1af*/
  }
  else
  {
    v23 = *(unsigned __int8 *)(a1[2] + v22); /*0x17ce27*/
    v24 = a1; /*0x17ce2b*/
  }
  v68 = 2 * ((v23 >> v19) & 1); /*0x17ce36*/
  v62 = v61 + 1; /*0x17ce3d*/
  v24[8] = v62; /*0x17ce40*/
  v25 = v62 & 7; /*0x17ce43*/
  if ( (v62 & 7) == 0 ) /*0x17ce46*/
  {
    v26 = v24[7]; /*0x17ce48*/
    if ( v26 >= v9 + v24[6] ) /*0x17ce52*/
      goto LABEL_77; /*0x17ce52*/
    v27 = 8 * v26; /*0x17ce58*/
    v24[8] = v27; /*0x17ce5b*/
    ++v24[7]; /*0x17ce5e*/
    v62 = v27; /*0x17ce61*/
  }
  v28 = v62 >> 3; /*0x17ce67*/
  if ( v62 >> 3 >= v9 ) /*0x17ce6c*/
  {
    v30 = a1; /*0x17d1ba*/
    v29 = *(unsigned __int8 *)(a1[3] + v28 - v9); /*0x17d1c0*/
  }
  else
  {
    v29 = *(unsigned __int8 *)(a1[2] + v28); /*0x17ce78*/
    v30 = a1; /*0x17ce7c*/
  }
  v69 = 4 * ((v29 >> v25) & 1); /*0x17ce88*/
  v63 = v62 + 1; /*0x17ce8f*/
  v30[8] = v63; /*0x17ce92*/
  v31 = v63 & 7; /*0x17ce95*/
  if ( (v63 & 7) == 0 ) /*0x17ce98*/
  {
    v32 = v30[7]; /*0x17ce9a*/
    if ( v32 >= v9 + v30[6] ) /*0x17cea4*/
      goto LABEL_77; /*0x17cea4*/
    v33 = 8 * v32; /*0x17ceaa*/
    v30[8] = v33; /*0x17cead*/
    ++v30[7]; /*0x17ceb0*/
    v63 = v33; /*0x17ceb3*/
  }
  v34 = v63 >> 3; /*0x17ceb9*/
  if ( v63 >> 3 >= v9 ) /*0x17cebe*/
  {
    v36 = a1; /*0x17d1cb*/
    v35 = *(unsigned __int8 *)(a1[3] + v34 - v9); /*0x17d1d1*/
  }
  else
  {
    v35 = *(unsigned __int8 *)(a1[2] + v34); /*0x17ceca*/
    v36 = a1; /*0x17cece*/
  }
  v70 = 8 * ((v35 >> v31) & 1); /*0x17ceda*/
  v37 = v63 + 1; /*0x17cee0*/
  v36[8] = v63 + 1; /*0x17cee1*/
  if ( (((_BYTE)v63 + 1) & 7) == 0 ) /*0x17cee9*/
  {
    v38 = a1[7]; /*0x17ceee*/
    if ( v38 >= v9 + a1[6] ) /*0x17cefa*/
      goto LABEL_77; /*0x17cefa*/
    v39 = 8 * v38; /*0x17cf00*/
    a1[8] = v39; /*0x17cf03*/
    ++a1[7]; /*0x17cf06*/
    v37 = v39; /*0x17cf09*/
  }
  v40 = v37 >> 3; /*0x17cf0d*/
  if ( v37 >> 3 >= v9 ) /*0x17cf12*/
    v41 = *(unsigned __int8 *)(a1[3] + v40 - v9); /*0x17d1e2*/
  else
    v41 = *(unsigned __int8 *)(a1[2] + v40); /*0x17cf1e*/
  v64 = (16 * ((v41 >> ((v63 + 1) & 7)) & 1)) | v70 | v69 | v68 | v71; /*0x17cf3e*/
  v42 = v37 + 1; /*0x17cf41*/
  a1[8] = v42; /*0x17cf45*/
  v43 = v42 & 7; /*0x17cf4a*/
  if ( (v42 & 7) != 0 ) /*0x17cf4d*/
    goto LABEL_35; /*0x17cf4d*/
  v44 = a1[7]; /*0x17cf52*/
  if ( v44 < v9 + a1[6] ) /*0x17cf5c*/
  {
    v45 = 8 * v44; /*0x17cf62*/
    a1[8] = v45; /*0x17cf68*/
    ++a1[7]; /*0x17cf6b*/
    v42 = v45; /*0x17cf6e*/
LABEL_35:
    v46 = v42 >> 3; /*0x17cf70*/
    if ( v42 >> 3 < v9 ) /*0x17cf77*/
    {
      v47 = a1[2]; /*0x17d1ee*/
    }
    else
    {
      v46 -= v9; /*0x17cf7d*/
      v47 = a1[3]; /*0x17cf82*/
    }
    v48 = *(unsigned __int8 *)(v47 + v46); /*0x17cf85*/
    a1[8] = v42 + 1; /*0x17cf8f*/
    v49 = v64 | (32 * ((v48 >> v43) & 1)); /*0x17cf9e*/
    goto LABEL_38; /*0x17cf9e*/
  }
LABEL_77:
  *a1 = 1; /*0x17d2c8*/
  v49 = -1; /*0x17d2d1*/
LABEL_38:
  v65 = 0; /*0x17cfa1*/
  if ( cl_shownet )
  {
    v50 = *(_DWORD *)(cl_shownet + 12); /*0x17cfb3*/
    if ( v50 > 1 || v50 == -1 )
    {
      Com_Printf(16, "%3i: #%-3i ", a1[7], *(_DWORD *)a4);
      v65 = 1; /*0x17cfe6*/
    }
  }
  *(_DWORD *)a4 = a5; /*0x17cff3*/
  MSG_ReadDeltaField(a1, a2, (int)a3, (int)a4, (const char **)&entityStateFields, v65, 0); /*0x17d026*/
  StateFieldListForEntityType = (int *)MSG_GetStateFieldListForEntityType(*(_DWORD *)&a4[unk_40C924]); /*0x17d03c*/
  v66 = *StateFieldListForEntityType; /*0x17d041*/
  if ( StateFieldListForEntityType[1] >= v49 )
  {
    if ( *(_BYTE *)(msg_dumpEnts + 12) )
    {
      EntityTypeName = (const char *)BG_GetEntityTypeName(*(_DWORD *)&a4[unk_40C924]); /*0x17d29f*/
      Com_Printf(14, "%3i: changed ent, eType %s\n", a5, EntityTypeName);
    }
    if ( v49 > 1 ) /*0x17d0f6*/
    {
      v55 = (const char **)(v66 + 16); /*0x17d0fb*/
      for ( i = 1; i != v49; ++i ) /*0x17d0fe*/
      {
        MSG_ReadDeltaField(a1, a2, (int)a3, (int)a4, v55, v65, 0); /*0x17d13e*/
        v55 += 4; /*0x17d144*/
      }
    }
    if ( StateFieldListForEntityType[1] > v49 ) /*0x17d151*/
    {
      v57 = 16 * v49 + v66; /*0x17d15b*/
      do /*0x17d179*/
      {
        *(_DWORD *)&a4[*(_DWORD *)(v57 + 4)] = *(_DWORD *)&a3[*(_DWORD *)(v57 + 4)]; /*0x17d16c*/
        ++v49; /*0x17d16f*/
        v57 += 16; /*0x17d170*/
      }
      while ( StateFieldListForEntityType[1] > v49 ); /*0x17d179*/
    }
    return 0; /*0x17d17b*/
  }
  else
  {
    *a1 = 1; /*0x17d050*/
    return 0; /*0x17d056*/
  }
}