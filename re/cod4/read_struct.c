int __usercall MSG_ReadDeltaStruct@<eax>(
        _DWORD *a1@<eax>,
        int a2@<edx>,
        char *a3@<ecx>,
        char *a4,
        int a5,
        int a6,
        int a7,
        const char **a8,
        int a9)
{
  int v10; // edx
  int v11; // ecx
  char v12; // bl
  int v13; // ecx
  char v14; // bl
  int v15; // ecx
  int v16; // eax
  int v17; // eax
  int v18; // esi
  int v19; // ebx
  int v20; // ebx
  int v21; // eax
  int v22; // eax
  char v23; // si
  int v24; // edx
  int v25; // edx
  int v26; // edx
  int v27; // edx
  int v28; // eax
  int v29; // edx
  int v30; // eax
  int v31; // eax
  int v33; // eax
  const char **v34; // ebx
  int i; // esi
  const char **v36; // ebx
  int v37; // ecx
  int v38; // eax
  int v39; // [esp+2Ch] [ebp-4Ch]
  int v40; // [esp+3Ch] [ebp-3Ch]
  int v41; // [esp+3Ch] [ebp-3Ch]
  int v42; // [esp+3Ch] [ebp-3Ch]
  int v43; // [esp+48h] [ebp-30h]
  int v46; // [esp+54h] [ebp-24h]
  int v47; // [esp+58h] [ebp-20h]
  int v48; // [esp+5Ch] [ebp-1Ch]

  v10 = a1[8]; /*0x17c874*/
  v11 = v10; /*0x17c877*/
  v12 = v10 & 7; /*0x17c87b*/
  if ( (v10 & 7) != 0 ) /*0x17c87e*/
  {
    v43 = a1[5]; /*0x17c9e7*/
    goto LABEL_16; /*0x17c9e7*/
  }
  v13 = a1[7]; /*0x17c884*/
  v43 = a1[5]; /*0x17c88a*/
  if ( v13 < a1[6] + v43 )
  {
    a1[8] = 8 * v13; /*0x17ca93*/
    ++a1[7]; /*0x17ca96*/
    v11 = 8 * v13; /*0x17ca99*/
LABEL_16:
    v27 = v11 >> 3; /*0x17c9ea*/
    if ( v11 >> 3 >= v43 ) /*0x17c9f2*/
    {
      v30 = *(unsigned __int8 *)(a1[3] + v27 - v43); /*0x17ca36*/
      v10 = v11 + 1; /*0x17ca3a*/
      a1[8] = v11 + 1; /*0x17ca3d*/
      if ( ((v30 >> v12) & 1) == 0 ) /*0x17ca46*/
      {
LABEL_18:
        v14 = v10 & 7; /*0x17ca09*/
        if ( (v10 & 7) != 0 ) /*0x17ca0e*/
          goto LABEL_4; /*0x17ca0e*/
        goto LABEL_19; /*0x17ca0e*/
      }
    }
    else
    {
      v28 = *(unsigned __int8 *)(a1[2] + v27); /*0x17c9f7*/
      v10 = v11 + 1; /*0x17c9fb*/
      a1[8] = v11 + 1; /*0x17c9fe*/
      if ( ((v28 >> v12) & 1) == 0 ) /*0x17ca07*/
        goto LABEL_18; /*0x17ca07*/
    }
    if ( !cl_shownet ) /*0x17ca51*/
      return 1; /*0x17ca51*/
    v31 = *(_DWORD *)(cl_shownet + 12); /*0x17ca57*/
    if ( v31 <= 1 && v31 != -1 ) /*0x17cbfe*/
      return 1; /*0x17cc04*/
    Com_Printf(16, "%3i: #%-3i remove\n", a1[7], a5);
    return 1; /*0x17cc04*/
  }
  *a1 = 1; /*0x17c898*/
  v14 = v10 & 7; /*0x17c8a0*/
  if ( (v10 & 7) != 0 ) /*0x17c8a3*/
    goto LABEL_4; /*0x17c8a3*/
LABEL_19:
  v29 = a1[7]; /*0x17ca14*/
  if ( v29 >= a1[6] + v43 ) /*0x17ca1f*/
  {
    *a1 = 1; /*0x17ca25*/
    goto LABEL_6; /*0x17ca2b*/
  }
  v10 = 8 * v29; /*0x17cbe3*/
  a1[8] = v10; /*0x17cbe6*/
  ++a1[7]; /*0x17cbe9*/
LABEL_4:
  v15 = v10 >> 3; /*0x17c8a9*/
  if ( v10 >> 3 < v43 ) /*0x17c8b1*/
  {
    v38 = *(unsigned __int8 *)(a1[2] + v15); /*0x17cba5*/
    a1[8] = v10 + 1; /*0x17cbaa*/
    if ( ((v38 >> v14) & 1) != 0 ) /*0x17cbb3*/
      goto LABEL_6; /*0x17cbb3*/
LABEL_40:
    memcpy(a4, a3, 4 * a6 + 4); /*0x17cbb9*/
    return 0; /*0x17cbe2*/
  }
  v16 = *(unsigned __int8 *)(a1[3] + v15 - v43); /*0x17c8bd*/
  a1[8] = v10 + 1; /*0x17c8c2*/
  if ( ((v16 >> v14) & 1) == 0 ) /*0x17c8cb*/
    goto LABEL_40; /*0x17c8cb*/
LABEL_6:
  HIWORD(v17) = HIWORD(a9); /*0x17c8d1*/
  LOWORD(v17) = 0; /*0x17c8d3*/
  v18 = ((a9 << (v17 == 0 ? 0x10 : 0)) & 0xFF000000) == 0 ? 8 : 0;
  v40 = a9 << (v17 == 0 ? 0x10 : 0) << v18;
  v19 = (v40 & 0xF0000000) == 0 ? 4 : 0;
  v41 = v40 << v19; /*0x17c922*/
  v39 = -((v41 & 0xC0000000) == 0); /*0x17c930*/
  v48 = (v17 == 0 ? 16 : 32)
      - v18
      - v19
      - (v39 & 2)
      - (v41 << (v39 & 2) >= 0)
      - (v41 << (v39 & 2) << (v41 << (v39 & 2) >= 0) >= 0);
  v46 = 0; /*0x17c961*/
  if ( v48 > 0 ) /*0x17c96d*/
  {
    v20 = 0; /*0x17c973*/
    v21 = a1[8]; /*0x17c975*/
    do /*0x17c9a9*/
    {
      v42 = v21; /*0x17c9a9*/
      v23 = v21 & 7; /*0x17c9ae*/
      if ( (v21 & 7) == 0 ) /*0x17c9b1*/
      {
        v24 = a1[7]; /*0x17c9b3*/
        if ( v24 >= a1[6] + v43 ) /*0x17c9be*/
        {
          *a1 = 1; /*0x17caa0*/
          v46 = -1; /*0x17caa6*/
          break; /*0x17caa6*/
        }
        v25 = 8 * v24; /*0x17c9c4*/
        a1[8] = v25; /*0x17c9c7*/
        ++a1[7]; /*0x17c9ca*/
        v42 = v25; /*0x17c9cd*/
      }
      v26 = v42 >> 3; /*0x17c9d3*/
      if ( v42 >> 3 >= v43 ) /*0x17c9d9*/
        v22 = *(unsigned __int8 *)(a1[3] + v26 - v43); /*0x17c986*/
      else
        v22 = *(unsigned __int8 *)(a1[2] + v26); /*0x17c9de*/
      v46 |= ((v22 >> v23) & 1) << v20; /*0x17c995*/
      v21 = v42 + 1; /*0x17c99b*/
      a1[8] = v42 + 1; /*0x17c99c*/
      ++v20; /*0x17c99f*/
    }
    while ( v48 != v20 ); /*0x17c9a9*/
  }
  if ( v46 <= a6 )
  {
    v47 = 0; /*0x17cacc*/
    if ( cl_shownet )
    {
      v33 = *(_DWORD *)(cl_shownet + 12); /*0x17cad7*/
      if ( v33 > 1 || v33 == -1 )
      {
        Com_Printf(16, "%3i: #%-3i ", a1[7], *(_DWORD *)a4);
        v47 = 1; /*0x17cb07*/
      }
    }
    *(_DWORD *)a4 = a5; /*0x17cb14*/
    if ( v46 > 0 ) /*0x17cb1b*/
    {
      v34 = a8; /*0x17cb1d*/
      for ( i = 0; i != v46; ++i ) /*0x17cb20*/
      {
        MSG_ReadDeltaField(a1, a2, (int)a3, (int)a4, v34, v47, 0); /*0x17cb5b*/
        v34 += 4; /*0x17cb61*/
      }
    }
    if ( v46 < a6 ) /*0x17cb6f*/
    {
      v36 = &a8[4 * v46]; /*0x17cb7a*/
      v37 = v46; /*0x17cb7d*/
      do /*0x17cb96*/
      {
        *(_DWORD *)&a4[(_DWORD)v36[1]] = *(_DWORD *)&a3[(_DWORD)v36[1]]; /*0x17cb8c*/
        ++v37; /*0x17cb8f*/
        v36 += 4; /*0x17cb90*/
      }
      while ( v37 != a6 ); /*0x17cb96*/
    }
    return 0; /*0x17cb98*/
  }
  else
  {
    *a1 = 1; /*0x17cab5*/
    return 0; /*0x17cabb*/
  }
}