int __cdecl MSG_ReadEntityIndex(_DWORD *a1, int a2)
{
  int v2; // ecx
  char v3; // bl
  int v4; // edx
  int v6; // edx
  int v7; // eax
  int v8; // edx
  char v9; // al
  int v10; // ebx
  int v11; // eax
  int v12; // edx
  char v13; // si
  int v14; // edx
  int v15; // edx
  char v16; // bl
  int v17; // edx
  int v18; // edx
  int v19; // eax
  int v20; // edx
  int v21; // esi
  char v22; // bl
  int v23; // edx
  int v24; // edx
  int v25; // eax
  int v26; // ebx
  char v27; // si
  int v28; // edx
  int v29; // edx
  int v30; // eax
  char v31; // si
  int v32; // edx
  int v33; // edx
  int v34; // eax
  int v35; // ebx
  char v36; // si
  int v37; // edx
  int v38; // edx
  int v39; // eax
  int v40; // edx
  int v41; // [esp+1Ch] [ebp-2Ch]
  int v42; // [esp+1Ch] [ebp-2Ch]
  int v43; // [esp+1Ch] [ebp-2Ch]
  int v44; // [esp+1Ch] [ebp-2Ch]
  int v45; // [esp+20h] [ebp-28h]
  int v46; // [esp+20h] [ebp-28h]
  int v47; // [esp+24h] [ebp-24h]
  int v48; // [esp+28h] [ebp-20h]
  int v49; // [esp+2Ch] [ebp-1Ch]

  v2 = a1[8]; /*0x178a2c*/
  v3 = v2 & 7; /*0x178a31*/
  if ( (v2 & 7) != 0 )
  {
    v45 = a1[5]; /*0x178aa3*/
  }
  else
  {
    v4 = a1[7]; /*0x178a36*/
    v45 = a1[5]; /*0x178a3c*/
    if ( v4 >= a1[6] + v45 )
    {
      *a1 = 1; /*0x178a4a*/
LABEL_4:
      if ( *(_BYTE *)(msg_printEntityNums + 12) )
        Com_Printf(16, "Entity num: 1 bit (inc)\n");
      ++a1[9]; /*0x178a62*/
      goto LABEL_7; /*0x178a62*/
    }
    a1[8] = 8 * v4; /*0x178b88*/
    ++a1[7]; /*0x178b8b*/
    v2 = 8 * v4; /*0x178b8e*/
  }
  v6 = v2 >> 3; /*0x178aa8*/
  if ( v2 >> 3 >= v45 ) /*0x178aae*/
  {
    v6 -= v45; /*0x178b72*/
    v7 = a1[3]; /*0x178b75*/
  }
  else
  {
    v7 = a1[2]; /*0x178ab4*/
  }
  v8 = *(unsigned __int8 *)(v7 + v6); /*0x178ab7*/
  v9 = v2 + 1; /*0x178abb*/
  a1[8] = v2 + 1; /*0x178abe*/
  if ( ((v8 >> v3) & 1) != 0 ) /*0x178ac8*/
    goto LABEL_4; /*0x178ac8*/
  if ( a2 == 10 )
  {
    v16 = v9 & 7; /*0x178bc8*/
    if ( (v9 & 7) == 0 ) /*0x178bcb*/
    {
      v17 = a1[7]; /*0x178bcd*/
      if ( v17 >= a1[6] + v45 ) /*0x178bd8*/
      {
        *a1 = 1; /*0x178bda*/
        goto LABEL_15; /*0x178be0*/
      }
      a1[8] = 8 * v17; /*0x178c0f*/
      ++a1[7]; /*0x178c12*/
    }
    v18 = (int)a1[8] >> 3; /*0x178c1a*/
    if ( v18 >= v45 ) /*0x178c20*/
    {
      v18 -= v45; /*0x178db5*/
      v19 = a1[3]; /*0x178db8*/
    }
    else
    {
      v19 = a1[2]; /*0x178c26*/
    }
    v20 = *(unsigned __int8 *)(v19 + v18); /*0x178c29*/
    ++a1[8]; /*0x178c30*/
    if ( ((v20 >> v16) & 1) != 0 ) /*0x178c3a*/
      goto LABEL_15; /*0x178c3a*/
    if ( *(_BYTE *)(msg_printEntityNums + 12) )
    {
      Com_Printf(16, "Entity num: %i bits (delta)\n", 6);
      v45 = a1[5]; /*0x178e19*/
    }
    v49 = a1[9]; /*0x178c55*/
    v21 = a1[8]; /*0x178c58*/
    v22 = v21 & 7; /*0x178c5d*/
    if ( (v21 & 7) == 0 ) /*0x178c60*/
    {
      v23 = a1[7]; /*0x178c62*/
      if ( v23 >= a1[6] + v45 ) /*0x178c6d*/
        goto LABEL_66; /*0x178c6d*/
      a1[8] = 8 * v23; /*0x178c7a*/
      ++a1[7]; /*0x178c7d*/
      v21 = 8 * v23; /*0x178c80*/
    }
    v24 = v21 >> 3; /*0x178c84*/
    if ( v21 >> 3 >= v45 ) /*0x178c8a*/
      v25 = *(unsigned __int8 *)(a1[3] + v24 - v45); /*0x178dca*/
    else
      v25 = *(unsigned __int8 *)(a1[2] + v24); /*0x178c93*/
    v26 = (v25 >> v22) & 1; /*0x178c9d*/
    v42 = v21 + 1; /*0x178ca1*/
    a1[8] = v21 + 1; /*0x178ca4*/
    v27 = (v21 + 1) & 7; /*0x178caa*/
    if ( (v42 & 7) == 0 ) /*0x178cad*/
    {
      v28 = a1[7]; /*0x178caf*/
      if ( v28 >= a1[6] + v45 ) /*0x178cba*/
        goto LABEL_66; /*0x178cba*/
      a1[8] = 8 * v28; /*0x178cc7*/
      ++a1[7]; /*0x178cca*/
      v42 = 8 * v28; /*0x178ccd*/
    }
    v29 = v42 >> 3; /*0x178cd3*/
    if ( v42 >> 3 >= v45 ) /*0x178cd9*/
      v30 = *(unsigned __int8 *)(a1[3] + v29 - v45); /*0x178dd9*/
    else
      v30 = *(unsigned __int8 *)(a1[2] + v29); /*0x178ce2*/
    v48 = 2 * ((v30 >> v27) & 1); /*0x178cef*/
    v43 = v42 + 1; /*0x178cf6*/
    a1[8] = v43; /*0x178cf9*/
    v31 = v43 & 7; /*0x178cfe*/
    if ( (v43 & 7) == 0 ) /*0x178d01*/
    {
      v32 = a1[7]; /*0x178d03*/
      if ( v32 >= a1[6] + v45 ) /*0x178d0e*/
        goto LABEL_66; /*0x178d0e*/
      a1[8] = 8 * v32; /*0x178d1b*/
      ++a1[7]; /*0x178d1e*/
      v43 = 8 * v32; /*0x178d21*/
    }
    v33 = v43 >> 3; /*0x178d27*/
    if ( v43 >> 3 >= v45 ) /*0x178d2d*/
      v34 = *(unsigned __int8 *)(a1[3] + v33 - v45); /*0x178de8*/
    else
      v34 = *(unsigned __int8 *)(a1[2] + v33); /*0x178d36*/
    v35 = (4 * ((v34 >> v31) & 1)) | v48 | v26; /*0x178d47*/
    v44 = v43 + 1; /*0x178d4d*/
    a1[8] = v44; /*0x178d50*/
    v36 = v44 & 7; /*0x178d55*/
    if ( (v44 & 7) != 0 ) /*0x178d58*/
      goto LABEL_57; /*0x178d58*/
    v37 = a1[7]; /*0x178d5a*/
    if ( v37 < a1[6] + v45 ) /*0x178d65*/
    {
      a1[8] = 8 * v37; /*0x178d72*/
      ++a1[7]; /*0x178d75*/
      v44 = 8 * v37; /*0x178d78*/
LABEL_57:
      v38 = v44 >> 3; /*0x178d7b*/
      if ( v44 >> 3 < v45 ) /*0x178d84*/
        v39 = *(unsigned __int8 *)(a1[2] + v38); /*0x178df4*/
      else
        v39 = *(unsigned __int8 *)(a1[3] + v38 - v45); /*0x178d8c*/
      v40 = v35 | (8 * ((v39 >> v36) & 1)); /*0x178d9e*/
      a1[8] = v44 + 1; /*0x178da4*/
      goto LABEL_60; /*0x178da4*/
    }
LABEL_66:
    *a1 = 1; /*0x178e21*/
    v40 = -1; /*0x178e27*/
LABEL_60:
    a1[9] = v40 + v49; /*0x178da7*/
    goto LABEL_7; /*0x178db0*/
  }
LABEL_15:
  if ( *(_BYTE *)(msg_printEntityNums + 12) )
    Com_Printf(16, "Entity num: %i bits (full)\n", a2 + 2);
  v47 = 0; /*0x178ae6*/
  if ( a2 > 0 ) /*0x178af2*/
  {
    v10 = 0; /*0x178af8*/
    v46 = a1[5]; /*0x178afd*/
    do /*0x178b35*/
    {
      v12 = a1[8]; /*0x178b35*/
      v41 = v12; /*0x178b38*/
      v13 = v12 & 7; /*0x178b3d*/
      if ( (v12 & 7) == 0 ) /*0x178b40*/
      {
        v14 = a1[7]; /*0x178b42*/
        if ( v14 >= a1[6] + v46 ) /*0x178b4d*/
        {
          *a1 = 1; /*0x178b95*/
          v47 = -1; /*0x178b9b*/
          break; /*0x178b9b*/
        }
        a1[8] = 8 * v14; /*0x178b56*/
        ++a1[7]; /*0x178b59*/
        v41 = 8 * v14; /*0x178b5c*/
        v12 = 8 * v14; /*0x178b5f*/
      }
      v15 = v12 >> 3; /*0x178b61*/
      if ( v15 >= v46 ) /*0x178b67*/
        v11 = *(unsigned __int8 *)(a1[3] + v15 - v46); /*0x178b16*/
      else
        v11 = *(unsigned __int8 *)(a1[2] + v15); /*0x178b6c*/
      v47 |= ((v11 >> v13) & 1) << v10; /*0x178b25*/
      a1[8] = v41 + 1; /*0x178b2c*/
      ++v10; /*0x178b2f*/
    }
    while ( v10 != a2 ); /*0x178b35*/
  }
  a1[9] = v47; /*0x178ba2*/
LABEL_7:
  if ( *(_BYTE *)(msg_printEntityNums + 12) ) /*0x178a6d*/
    Com_Printf(16, "Read entity num %i\n", a1[9]); /*0x178a89*/
  return a1[9]; /*0x178a91*/
}