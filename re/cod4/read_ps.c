int __cdecl MSG_ReadDeltaPlayerstate(int a1, _DWORD *a2, int a3, _BYTE *a4, _DWORD *a5, char a6)
{
  _BYTE *v6; // eax
  void *v7; // edx
  int v8; // eax
  int v9; // ecx
  char v10; // bl
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  int v14; // eax
  int i; // ebx
  int v16; // eax
  char v17; // si
  int v18; // ecx
  int v19; // edx
  int v20; // ecx
  char *v21; // ebx
  int v22; // ecx
  char v23; // bl
  int v24; // ecx
  int v25; // esi
  char v26; // bl
  int v27; // ecx
  int v28; // edx
  int v29; // eax
  int v30; // ebx
  int v31; // esi
  int v32; // edx
  int v33; // eax
  char v34; // si
  int v35; // edx
  int v36; // eax
  char v37; // si
  int v38; // edx
  int v39; // eax
  int v40; // ebx
  char v41; // si
  int v42; // edx
  int v43; // eax
  int v44; // esi
  char v45; // al
  int v46; // edx
  char v47; // al
  int v48; // eax
  const char **v49; // esi
  int v50; // ebx
  int v51; // ecx
  char v52; // al
  int v53; // edx
  char v54; // al
  int v55; // eax
  int v56; // ecx
  char v57; // al
  int v58; // edx
  char v59; // al
  int v60; // eax
  int v61; // edx
  char v62; // bl
  int v63; // edx
  int v64; // edx
  int v65; // eax
  char v66; // bl
  int v67; // edx
  int v68; // edx
  int v69; // edx
  int v70; // eax
  char v71; // bl
  int v72; // edx
  int v73; // edx
  int v74; // edx
  int v75; // eax
  char v76; // bl
  int v77; // edx
  int v78; // edx
  int v79; // edx
  int v80; // eax
  int v81; // ebx
  int v82; // edx
  int v83; // edx
  int v84; // edx
  int v85; // eax
  int v86; // ebx
  int v87; // edx
  int v88; // edx
  int v89; // edx
  int v90; // eax
  int v91; // eax
  int v92; // ecx
  int v93; // edx
  int v94; // edx
  int v95; // ecx
  char v96; // bl
  int v97; // ecx
  char v98; // bl
  int v99; // edx
  int v100; // ecx
  char v101; // al
  int v102; // edx
  char v103; // al
  int *v104; // ebx
  int j; // esi
  char v106; // al
  int v107; // edx
  char v108; // al
  int v109; // eax
  int v110; // ecx
  int v111; // ecx
  int v112; // eax
  int v113; // edx
  int v114; // eax
  int v115; // edx
  char v116; // bl
  int v117; // edx
  int v118; // ecx
  char v119; // al
  int v120; // edx
  char v121; // al
  int *v122; // ebx
  int m; // esi
  char v124; // al
  int v125; // edx
  char v126; // al
  int v127; // eax
  int v128; // ecx
  int v129; // ecx
  int v130; // eax
  int v131; // edx
  int v132; // ecx
  char v133; // bl
  int v134; // ecx
  int v135; // esi
  char v136; // bl
  int v137; // edx
  int v138; // edx
  int v139; // edx
  int v140; // eax
  int v141; // ebx
  int v142; // esi
  int v143; // edx
  int v144; // edx
  int v145; // edx
  int v146; // eax
  int v147; // esi
  int v148; // ecx
  int v149; // edx
  int v150; // edx
  int v151; // edx
  int v152; // eax
  int v153; // eax
  int v154; // eax
  int v155; // ecx
  char v156; // bl
  int v157; // ecx
  const char **v158; // esi
  int v159; // ebx
  int v160; // edx
  int v161; // eax
  int v162; // ecx
  int v163; // edx
  int v164; // eax
  int v165; // edx
  char v166; // bl
  int v167; // edx
  int v168; // edx
  char v169; // bl
  int v170; // ecx
  int v171; // ebx
  int n; // eax
  int v173; // edx
  int result; // eax
  int v175; // ecx
  int v176; // eax
  int v177; // ecx
  int v178; // eax
  int v179; // edx
  int v180; // eax
  int v181; // ebx
  int v182; // [esp+2Ch] [ebp-301Ch]
  int v183; // [esp+3Ch] [ebp-300Ch]
  int v184; // [esp+3Ch] [ebp-300Ch]
  int v185; // [esp+3Ch] [ebp-300Ch]
  int v186; // [esp+3Ch] [ebp-300Ch]
  int v187; // [esp+3Ch] [ebp-300Ch]
  int v188; // [esp+3Ch] [ebp-300Ch]
  int v189; // [esp+3Ch] [ebp-300Ch]
  int v190; // [esp+3Ch] [ebp-300Ch]
  int v191; // [esp+3Ch] [ebp-300Ch]
  int v192; // [esp+3Ch] [ebp-300Ch]
  int v193; // [esp+3Ch] [ebp-300Ch]
  int v194; // [esp+3Ch] [ebp-300Ch]
  int v195; // [esp+4Ch] [ebp-2FFCh]
  int v196; // [esp+4Ch] [ebp-2FFCh]
  _DWORD *v197; // [esp+58h] [ebp-2FF0h]
  int v198; // [esp+5Ch] [ebp-2FECh]
  int v199; // [esp+60h] [ebp-2FE8h]
  int v200; // [esp+68h] [ebp-2FE0h]
  int v201; // [esp+6Ch] [ebp-2FDCh]
  char v202; // [esp+70h] [ebp-2FD8h]
  char *v203; // [esp+80h] [ebp-2FC8h]
  int v204; // [esp+84h] [ebp-2FC4h]
  char v205; // [esp+8Bh] [ebp-2FBDh]
  _DWORD *v206; // [esp+8Ch] [ebp-2FBCh]
  int k; // [esp+90h] [ebp-2FB8h]
  int v208; // [esp+94h] [ebp-2FB4h]
  int v209; // [esp+98h] [ebp-2FB0h]
  int v210; // [esp+9Ch] [ebp-2FACh]
  int v211; // [esp+A0h] [ebp-2FA8h]
  int v212; // [esp+A4h] [ebp-2FA4h]
  int v213; // [esp+ACh] [ebp-2F9Ch]
  int v214; // [esp+B0h] [ebp-2F98h]
  int v215; // [esp+B4h] [ebp-2F94h]
  int v216; // [esp+B8h] [ebp-2F90h]
  int v217; // [esp+BCh] [ebp-2F8Ch]
  __int16 v218; // [esp+C6h] [ebp-2F82h]
  __int16 v219; // [esp+C6h] [ebp-2F82h]
  __int16 v220; // [esp+C6h] [ebp-2F82h]
  __int16 v221; // [esp+C6h] [ebp-2F82h]
  __int16 v222; // [esp+C6h] [ebp-2F82h]
  __int16 v223; // [esp+C6h] [ebp-2F82h]
  __int16 v224; // [esp+C6h] [ebp-2F82h]
  _BYTE v225[12132]; // [esp+C8h] [ebp-2F80h] BYREF

  v6 = a4; /*0x17d2ef*/
  v197 = a4; /*0x17d2f2*/
  v7 = a5; /*0x17d2f8*/
  if ( !a4 ) /*0x17d31a*/
  {
    memset(v225, 0, sizeof(v225)); /*0x17e9c5*/
    v197 = v225; /*0x17e9ca*/
    v6 = v225; /*0x17e9d0*/
    v7 = a5; /*0x17e9d2*/
  }
  memcpy(v7, v6, 0x2F64u); /*0x17d32f*/
  if ( cl_shownet && ((v8 = *(_DWORD *)(cl_shownet + 12), v8 > 1) || v8 == -2) )
  {
    Com_Printf(16, "%3i: playerstate ", a2[7]);
    v200 = 1; /*0x17d363*/
    v9 = a2[8]; /*0x17d36d*/
    v10 = v9 & 7; /*0x17d372*/
    if ( (v9 & 7) != 0 ) /*0x17d375*/
    {
LABEL_10:
      v195 = a2[5]; /*0x17d3b8*/
      goto LABEL_11; /*0x17d3bb*/
    }
  }
  else
  {
    v200 = 0; /*0x17d3a4*/
    v9 = a2[8]; /*0x17d3ae*/
    v10 = v9 & 7; /*0x17d3b3*/
    if ( (v9 & 7) != 0 ) /*0x17d3b6*/
      goto LABEL_10; /*0x17d3b6*/
  }
  v11 = a2[7]; /*0x17d377*/
  v195 = a2[5]; /*0x17d37d*/
  if ( v11 >= a2[6] + v195 ) /*0x17d38a*/
  {
    *a2 = 1; /*0x17d390*/
    v205 = 0; /*0x17d396*/
    goto LABEL_14; /*0x17d39d*/
  }
  a2[8] = 8 * v11; /*0x17d57a*/
  ++a2[7]; /*0x17d57d*/
  v9 = 8 * v11; /*0x17d580*/
LABEL_11:
  v12 = v9 >> 3; /*0x17d3c1*/
  if ( v9 >> 3 >= v195 ) /*0x17d3cc*/
    v13 = *(unsigned __int8 *)(a2[3] + v12 - v195); /*0x17d56a*/
  else
    v13 = *(unsigned __int8 *)(a2[2] + v12); /*0x17d3d5*/
  a2[8] = v9 + 1; /*0x17d3dc*/
  v205 = (v13 >> v10) & 1; /*0x17d3e6*/
LABEL_14:
  HIWORD(v14) = HIWORD(numPlayerStateFields); /*0x17d3ec*/
  LOWORD(v14) = 0; /*0x17d3f9*/
  v182 = -(((numPlayerStateFields << (v14 == 0 ? 0x10 : 0) << (((numPlayerStateFields << (v14 == 0 ? 0x10 : 0))
                                                              & 0xFF000000) == 0
                                                             ? 8
                                                             : 0) << (((numPlayerStateFields << (v14 == 0 ? 0x10 : 0) << (((numPlayerStateFields << (v14 == 0 ? 0x10 : 0)) & 0xFF000000) == 0 ? 8 : 0))
                                                                     & 0xF0000000) == 0
                                                                    ? 4
                                                                    : 0))
          & 0xC0000000) == 0);
  v183 = numPlayerStateFields << (v14 == 0 ? 0x10 : 0) << (((numPlayerStateFields << (v14 == 0 ? 0x10 : 0)) & 0xFF000000) == 0
                                                         ? 8
                                                         : 0) << (((numPlayerStateFields << (v14 == 0 ? 0x10 : 0) << (((numPlayerStateFields << (v14 == 0 ? 0x10 : 0)) & 0xFF000000) == 0 ? 8 : 0))
                                                                 & 0xF0000000) == 0
                                                                ? 4
                                                                : 0) << (v182 & 2);
  v201 = (v14 == 0 ? 16 : 32)
       - (((numPlayerStateFields << (v14 == 0 ? 0x10 : 0)) & 0xFF000000) == 0 ? 8 : 0)
       - (((numPlayerStateFields << (v14 == 0 ? 0x10 : 0) << (((numPlayerStateFields << (v14 == 0 ? 0x10 : 0))
                                                             & 0xFF000000) == 0
                                                            ? 8
                                                            : 0))
         & 0xF0000000) == 0
        ? 4
        : 0)
       - (v182 & 2)
       - (v183 >= 0)
       - (v183 << (v183 >= 0) >= 0);
  v198 = 0; /*0x17d4bb*/
  if ( v201 > 0 ) /*0x17d4cd*/
  {
    v217 = 0; /*0x17d4d3*/
    for ( i = 0; i != v201; ++i ) /*0x17d4dd*/
    {
      v184 = a2[8]; /*0x17d519*/
      v17 = v184 & 7; /*0x17d51f*/
      if ( (v184 & 7) == 0 ) /*0x17d522*/
      {
        v18 = a2[7]; /*0x17d524*/
        if ( v18 >= a2[6] + v195 ) /*0x17d532*/
        {
          *a2 = 1; /*0x17d587*/
          v198 = -1; /*0x17d58d*/
          goto LABEL_26; /*0x17d58d*/
        }
        a2[8] = 8 * v18; /*0x17d53b*/
        ++a2[7]; /*0x17d53e*/
        v184 = 8 * v18; /*0x17d541*/
      }
      v19 = v184 >> 3; /*0x17d54d*/
      if ( v184 >> 3 >= v195 ) /*0x17d556*/
        v16 = *(unsigned __int8 *)(a2[3] + v19 - v195); /*0x17d4ea*/
      else
        v16 = *(unsigned __int8 *)(a2[2] + v19); /*0x17d55b*/
      v217 |= ((v16 >> v17) & 1) << i; /*0x17d4f9*/
      a2[8] = v184 + 1; /*0x17d506*/
    }
    v198 = v217; /*0x17d882*/
    if ( v217 > 0 ) /*0x17d88a*/
    {
      v49 = (const char **)&playerStateFields; /*0x17d890*/
      if ( a6 && v205 ) /*0x17e765*/
      {
        v181 = 0; /*0x17e76b*/
        while ( 1 ) /*0x17e7ac*/
        {
          MSG_ReadDeltaField(a2, a3, (int)v197, (int)a5, v49, v200, *((_BYTE *)v49 + 12) == 3); /*0x17e7ac*/
          if ( ++v181 == v217 ) /*0x17e7b8*/
            break; /*0x17e7b8*/
          v49 += 4; /*0x17e770*/
        }
      }
      else
      {
        v50 = 0; /*0x17d8a3*/
        while ( 1 ) /*0x17d8d9*/
        {
          MSG_ReadDeltaField(a2, a3, (int)v197, (int)a5, v49, v200, 0); /*0x17d8d9*/
          if ( ++v50 == v217 ) /*0x17d8e5*/
            break; /*0x17d8e5*/
          v49 += 4; /*0x17d8eb*/
        }
      }
    }
  }
LABEL_26:
  v20 = v198; /*0x17d597*/
  if ( numPlayerStateFields > v198 ) /*0x17d5a3*/
  {
    v21 = (char *)&playerStateFields + 16 * v198; /*0x17d5aa*/
    do /*0x17d5cf*/
    {
      *(_DWORD *)((char *)a5 + *((_DWORD *)v21 + 1)) = *(_DWORD *)((char *)v197 + *((_DWORD *)v21 + 1)); /*0x17d5c2*/
      ++v20; /*0x17d5c5*/
      v21 += 16; /*0x17d5c6*/
    }
    while ( v20 != numPlayerStateFields ); /*0x17d5cf*/
  }
  if ( !v205 /*0x17e82a*/
    && !(unsigned __int8)CL_GetPredictedOriginForServerTime(&clients, *a5, a5 + 7, a5 + 10, a5 + 66, a5 + 2, a5 + 43) )
  {
    Com_PrintError(14, "Unable to find the origin we sent, delta is not going to work"); /*0x17e846*/
    a5[7] = v197[7]; /*0x17e85a*/
    a5[8] = v197[8]; /*0x17e860*/
    a5[9] = v197[9]; /*0x17e866*/
    a5[10] = v197[10]; /*0x17e86c*/
    a5[11] = v197[11]; /*0x17e872*/
    a5[12] = v197[12]; /*0x17e878*/
    a5[2] = v197[2]; /*0x17e87e*/
    a5[43] = v197[43]; /*0x17e887*/
    a5[66] = v197[66]; /*0x17e893*/
    a5[67] = v197[67]; /*0x17e89f*/
    a5[68] = v197[68]; /*0x17e8ab*/
  }
  v22 = a2[8]; /*0x17d5de*/
  v23 = v22 & 7; /*0x17d5e3*/
  if ( (v22 & 7) != 0 ) /*0x17d5e6*/
  {
    v196 = a2[5]; /*0x17e6ce*/
  }
  else
  {
    v24 = a2[7]; /*0x17d5ec*/
    v196 = a2[5]; /*0x17d5f2*/
    if ( v24 >= a2[6] + v196 ) /*0x17d5ff*/
    {
      *a2 = 1; /*0x17d605*/
      goto LABEL_33; /*0x17d605*/
    }
    a2[8] = 8 * v24; /*0x17e8ff*/
    ++a2[7]; /*0x17e902*/
    v22 = 8 * v24; /*0x17e905*/
  }
  v179 = v22 >> 3; /*0x17e6d6*/
  if ( v22 >> 3 < v196 ) /*0x17e6df*/
    v180 = *(unsigned __int8 *)(a2[2] + v179); /*0x17e728*/
  else
    v180 = *(unsigned __int8 *)(a2[3] + v179 - v196); /*0x17e6ea*/
  a2[8] = v22 + 1; /*0x17e6f1*/
  if ( ((v180 >> v23) & 1) != 0 ) /*0x17e6fa*/
  {
LABEL_33:
    if ( cl_shownet && *(_DWORD *)(cl_shownet + 12) == 4 ) /*0x17d61b*/
    {
      Com_Printf(16, "%s ", "PS_STATS"); /*0x17ea60*/
      v196 = a2[5]; /*0x17ea68*/
    }
    v25 = a2[8]; /*0x17d621*/
    v26 = v25 & 7; /*0x17d626*/
    if ( (v25 & 7) == 0 ) /*0x17d629*/
    {
      v27 = a2[7]; /*0x17d62b*/
      if ( a2[5] + a2[6] <= v27 ) /*0x17d636*/
        goto LABEL_321; /*0x17d636*/
      a2[8] = 8 * v27; /*0x17d643*/
      ++a2[7]; /*0x17d646*/
      v25 = 8 * v27; /*0x17d649*/
    }
    v28 = v25 >> 3; /*0x17d64d*/
    if ( v196 <= v25 >> 3 ) /*0x17d656*/
      v29 = *(unsigned __int8 *)(a2[3] + v28 - v196); /*0x17e7c8*/
    else
      v29 = *(unsigned __int8 *)(a2[2] + v28); /*0x17d65f*/
    v30 = (v29 >> v26) & 1; /*0x17d669*/
    v185 = v25 + 1; /*0x17d66d*/
    a2[8] = v25 + 1; /*0x17d673*/
    v31 = (v25 + 1) & 7; /*0x17d676*/
    if ( !v31 ) /*0x17d679*/
    {
      v27 = a2[7]; /*0x17d67b*/
      if ( a2[5] + a2[6] <= v27 ) /*0x17d686*/
        goto LABEL_321; /*0x17d686*/
      a2[8] = 8 * v27; /*0x17d693*/
      ++a2[7]; /*0x17d696*/
      v185 = 8 * v27; /*0x17d699*/
    }
    v32 = v185 >> 3; /*0x17d6a5*/
    if ( v196 <= v185 >> 3 ) /*0x17d6ae*/
      v33 = *(unsigned __int8 *)(a2[3] + v32 - v196); /*0x17e8bf*/
    else
      v33 = *(unsigned __int8 *)(a2[2] + v32); /*0x17d6b7*/
    v215 = 2 * ((v33 >> v31) & 1); /*0x17d6c4*/
    v186 = v185 + 1; /*0x17d6d1*/
    a2[8] = v186; /*0x17d6d7*/
    v34 = v186 & 7; /*0x17d6da*/
    if ( (v186 & 7) == 0 ) /*0x17d6dd*/
    {
      v27 = a2[7]; /*0x17d6df*/
      if ( a2[5] + a2[6] <= v27 ) /*0x17d6ea*/
        goto LABEL_321; /*0x17d6ea*/
      a2[8] = 8 * v27; /*0x17d6f7*/
      ++a2[7]; /*0x17d6fa*/
      v186 = 8 * v27; /*0x17d6fd*/
    }
    v35 = v186 >> 3; /*0x17d709*/
    if ( v196 <= v186 >> 3 ) /*0x17d712*/
      v36 = *(unsigned __int8 *)(a2[3] + v35 - v196); /*0x17e8d1*/
    else
      v36 = *(unsigned __int8 *)(a2[2] + v35); /*0x17d71b*/
    v214 = 4 * ((v36 >> v34) & 1); /*0x17d729*/
    v187 = v186 + 1; /*0x17d736*/
    a2[8] = v187; /*0x17d73c*/
    v37 = v187 & 7; /*0x17d73f*/
    if ( (v187 & 7) == 0 ) /*0x17d742*/
    {
      v27 = a2[7]; /*0x17d744*/
      if ( a2[5] + a2[6] <= v27 ) /*0x17d74f*/
        goto LABEL_321; /*0x17d74f*/
      a2[8] = 8 * v27; /*0x17d75c*/
      ++a2[7]; /*0x17d75f*/
      v187 = 8 * v27; /*0x17d762*/
    }
    v38 = v187 >> 3; /*0x17d76e*/
    if ( v196 <= v187 >> 3 ) /*0x17d777*/
      v39 = *(unsigned __int8 *)(a2[3] + v38 - v196); /*0x17e8e3*/
    else
      v39 = *(unsigned __int8 *)(a2[2] + v38); /*0x17d780*/
    v40 = (8 * ((v39 >> v37) & 1)) | v214 | v215 | v30; /*0x17d79a*/
    v188 = v187 + 1; /*0x17d7a3*/
    a2[8] = v188; /*0x17d7a9*/
    v41 = v188 & 7; /*0x17d7ac*/
    if ( (v188 & 7) != 0 ) /*0x17d7af*/
      goto LABEL_59; /*0x17d7af*/
    v27 = a2[7]; /*0x17d7b1*/
    if ( v27 < a2[6] + v196 ) /*0x17d7bf*/
    {
      a2[8] = 8 * v27; /*0x17d7cc*/
      ++a2[7]; /*0x17d7cf*/
      v188 = 8 * v27; /*0x17d7d2*/
LABEL_59:
      v42 = v188 >> 3; /*0x17d7d8*/
      if ( v188 >> 3 < v196 ) /*0x17d7e7*/
        v43 = *(unsigned __int8 *)(a2[2] + v42); /*0x17e8ef*/
      else
        v43 = *(unsigned __int8 *)(a2[3] + v42 - v196); /*0x17d7f6*/
      v44 = v40 | (16 * ((v43 >> v41) & 1)); /*0x17d806*/
      a2[8] = v188 + 1; /*0x17d80f*/
      if ( (v40 & 1) == 0 ) /*0x17d818*/
        goto LABEL_76; /*0x17d818*/
      v27 = a2[7]; /*0x17d81e*/
LABEL_63:
      if ( v27 + 2 > a2[6] + v196 ) /*0x17d82f*/
      {
        *a2 = 1; /*0x17d8f0*/
        v48 = -1; /*0x17d8f6*/
      }
      else
      {
        if ( v27 >= v196 ) /*0x17d83b*/
          v45 = *(_BYTE *)(a2[3] + v27 - v196); /*0x17e9f4*/
        else
          v45 = *(_BYTE *)(a2[2] + v27); /*0x17d844*/
        LOBYTE(v218) = v45; /*0x17d848*/
        v46 = v27 + 1; /*0x17d84e*/
        if ( v196 > v27 + 1 ) /*0x17d857*/
          v47 = *(_BYTE *)(a2[2] + v46); /*0x17e9e0*/
        else
          v47 = *(_BYTE *)(a2[3] + v46 - v196); /*0x17d866*/
        HIBYTE(v218) = v47; /*0x17d86a*/
        v48 = v218; /*0x17d870*/
        a2[7] = v27 + 2; /*0x17d877*/
      }
      a5[82] = v48; /*0x17d901*/
      v196 = a2[5]; /*0x17d90a*/
LABEL_76:
      if ( (v44 & 2) != 0 ) /*0x17d916*/
      {
        v51 = a2[7]; /*0x17d918*/
        if ( v51 + 2 > a2[6] + v196 ) /*0x17d929*/
        {
          *a2 = 1; /*0x17d972*/
          v55 = -1; /*0x17d978*/
        }
        else
        {
          if ( v51 >= v196 ) /*0x17d931*/
            v52 = *(_BYTE *)(a2[3] + v51 - v196); /*0x17ea40*/
          else
            v52 = *(_BYTE *)(a2[2] + v51); /*0x17d93a*/
          LOBYTE(v219) = v52; /*0x17d93e*/
          v53 = v51 + 1; /*0x17d944*/
          if ( v51 + 1 < v196 ) /*0x17d94d*/
            v54 = *(_BYTE *)(a2[2] + v53); /*0x17ea2c*/
          else
            v54 = *(_BYTE *)(a2[3] + v53 - v196); /*0x17d95c*/
          HIBYTE(v219) = v54; /*0x17d960*/
          v55 = v219; /*0x17d966*/
          a2[7] = v51 + 2; /*0x17d96d*/
        }
        a5[83] = v55; /*0x17d983*/
        v196 = a2[5]; /*0x17d98c*/
      }
      if ( (v44 & 4) != 0 ) /*0x17d998*/
      {
        v56 = a2[7]; /*0x17d99a*/
        if ( v56 + 2 > a2[6] + v196 ) /*0x17d9ab*/
        {
          *a2 = 1; /*0x17e90c*/
          v60 = -1; /*0x17e912*/
        }
        else
        {
          if ( v56 >= v196 ) /*0x17d9b7*/
            v57 = *(_BYTE *)(a2[3] + v56 - v196); /*0x17ea14*/
          else
            v57 = *(_BYTE *)(a2[2] + v56); /*0x17d9c0*/
          LOBYTE(v220) = v57; /*0x17d9c4*/
          v58 = v56 + 1; /*0x17d9ca*/
          if ( v56 + 1 < v196 ) /*0x17d9d3*/
            v59 = *(_BYTE *)(a2[2] + v58); /*0x17ea00*/
          else
            v59 = *(_BYTE *)(a2[3] + v58 - v196); /*0x17d9e2*/
          HIBYTE(v220) = v59; /*0x17d9e6*/
          v60 = v220; /*0x17d9ec*/
          a2[7] = v56 + 2; /*0x17d9f3*/
        }
        a5[84] = v60; /*0x17d9fc*/
        v196 = a2[5]; /*0x17da05*/
      }
      if ( (v44 & 8) == 0 ) /*0x17da11*/
        goto LABEL_126; /*0x17da11*/
      v61 = a2[8]; /*0x17da17*/
      v189 = v61; /*0x17da1a*/
      v62 = v61 & 7; /*0x17da22*/
      if ( (v61 & 7) == 0 ) /*0x17da25*/
      {
        v63 = a2[7]; /*0x17da27*/
        if ( v63 >= a2[6] + v196 ) /*0x17da35*/
          goto LABEL_322; /*0x17da35*/
        v61 = 8 * v63; /*0x17da3b*/
        a2[8] = v61; /*0x17da3e*/
        ++a2[7]; /*0x17da41*/
        v189 = v61; /*0x17da44*/
      }
      v64 = v61 >> 3; /*0x17da4a*/
      if ( v64 >= v196 ) /*0x17da53*/
        v65 = *(unsigned __int8 *)(a2[3] + v64 - v196); /*0x17e925*/
      else
        v65 = *(unsigned __int8 *)(a2[2] + v64); /*0x17da5c*/
      v212 = (v65 >> v62) & 1; /*0x17da67*/
      v190 = v189 + 1; /*0x17da74*/
      a2[8] = v190; /*0x17da7a*/
      v66 = v190 & 7; /*0x17da7d*/
      if ( (v190 & 7) == 0 ) /*0x17da80*/
      {
        v67 = a2[7]; /*0x17da82*/
        if ( v67 >= a2[6] + v196 ) /*0x17da90*/
          goto LABEL_322; /*0x17da90*/
        v68 = 8 * v67; /*0x17da96*/
        a2[8] = v68; /*0x17da99*/
        ++a2[7]; /*0x17da9c*/
        v190 = v68; /*0x17da9f*/
      }
      v69 = v190 >> 3; /*0x17daab*/
      if ( v190 >> 3 >= v196 ) /*0x17dab4*/
        v70 = *(unsigned __int8 *)(a2[3] + v69 - v196); /*0x17e961*/
      else
        v70 = *(unsigned __int8 *)(a2[2] + v69); /*0x17dabd*/
      v209 = 2 * ((v70 >> v66) & 1); /*0x17daca*/
      v191 = v190 + 1; /*0x17dad7*/
      a2[8] = v191; /*0x17dadd*/
      v71 = v191 & 7; /*0x17dae0*/
      if ( (v191 & 7) == 0 ) /*0x17dae3*/
      {
        v72 = a2[7]; /*0x17dae5*/
        if ( v72 >= a2[6] + v196 ) /*0x17daf3*/
          goto LABEL_322; /*0x17daf3*/
        v73 = 8 * v72; /*0x17daf9*/
        a2[8] = v73; /*0x17dafc*/
        ++a2[7]; /*0x17daff*/
        v191 = v73; /*0x17db02*/
      }
      v74 = v191 >> 3; /*0x17db0e*/
      if ( v191 >> 3 >= v196 ) /*0x17db17*/
        v75 = *(unsigned __int8 *)(a2[3] + v74 - v196); /*0x17e973*/
      else
        v75 = *(unsigned __int8 *)(a2[2] + v74); /*0x17db20*/
      v210 = 4 * ((v75 >> v71) & 1); /*0x17db2e*/
      v192 = v191 + 1; /*0x17db3b*/
      a2[8] = v192; /*0x17db41*/
      v76 = v192 & 7; /*0x17db44*/
      if ( (v192 & 7) == 0 ) /*0x17db47*/
      {
        v77 = a2[7]; /*0x17db49*/
        if ( v77 >= a2[6] + v196 ) /*0x17db57*/
          goto LABEL_322; /*0x17db57*/
        v78 = 8 * v77; /*0x17db5d*/
        a2[8] = v78; /*0x17db60*/
        ++a2[7]; /*0x17db63*/
        v192 = v78; /*0x17db66*/
      }
      v79 = v192 >> 3; /*0x17db72*/
      if ( v192 >> 3 >= v196 ) /*0x17db7b*/
        v80 = *(unsigned __int8 *)(a2[3] + v79 - v196); /*0x17e985*/
      else
        v80 = *(unsigned __int8 *)(a2[2] + v79); /*0x17db84*/
      v211 = 8 * ((v80 >> v76) & 1); /*0x17db92*/
      v81 = v192 + 1; /*0x17db9e*/
      a2[8] = v192 + 1; /*0x17dba1*/
      if ( (((_BYTE)v192 + 1) & 7) == 0 ) /*0x17dbad*/
      {
        v82 = a2[7]; /*0x17dbaf*/
        if ( v82 >= a2[6] + v196 ) /*0x17dbbd*/
          goto LABEL_322; /*0x17dbbd*/
        v83 = 8 * v82; /*0x17dbc3*/
        a2[8] = v83; /*0x17dbc6*/
        ++a2[7]; /*0x17dbc9*/
        v81 = v83; /*0x17dbcc*/
      }
      v84 = v81 >> 3; /*0x17dbd0*/
      if ( v81 >> 3 >= v196 ) /*0x17dbd9*/
        v85 = *(unsigned __int8 *)(a2[3] + v84 - v196); /*0x17e997*/
      else
        v85 = *(unsigned __int8 *)(a2[2] + v84); /*0x17dbe2*/
      v193 = (16 * ((v85 >> ((v192 + 1) & 7)) & 1)) | v211 | v210 | v209 | v212; /*0x17dc13*/
      v86 = v81 + 1; /*0x17dc19*/
      a2[8] = v86; /*0x17dc1c*/
      v202 = v86 & 7; /*0x17dc22*/
      if ( (v86 & 7) != 0 ) /*0x17dc28*/
        goto LABEL_122; /*0x17dc28*/
      v87 = a2[7]; /*0x17dc2a*/
      if ( v87 < a2[6] + v196 ) /*0x17dc38*/
      {
        v88 = 8 * v87; /*0x17dc3e*/
        a2[8] = v88; /*0x17dc41*/
        ++a2[7]; /*0x17dc44*/
        v86 = v88; /*0x17dc47*/
LABEL_122:
        v89 = v86 >> 3; /*0x17dc49*/
        if ( v86 >> 3 < v196 ) /*0x17dc54*/
          v90 = *(unsigned __int8 *)(a2[2] + v89); /*0x17e9a3*/
        else
          v90 = *(unsigned __int8 *)(a2[3] + v89 - v196); /*0x17dc63*/
        v91 = v193 | (32 * ((v90 >> v202) & 1)); /*0x17dc76*/
        a2[8] = v86 + 1; /*0x17dc7f*/
        goto LABEL_125; /*0x17dc7f*/
      }
LABEL_322:
      *a2 = 1; /*0x17ea83*/
      v91 = -1; /*0x17ea89*/
LABEL_125:
      a5[85] = v91; /*0x17dc82*/
      v196 = a2[5]; /*0x17dc91*/
LABEL_126:
      if ( (v44 & 0x10) != 0 ) /*0x17dc9a*/
      {
        v92 = a2[7]; /*0x17dc9c*/
        if ( v92 >= a2[6] + v196 ) /*0x17dcaa*/
        {
          *a2 = 1; /*0x17dccf*/
          v93 = -1; /*0x17dcd5*/
        }
        else
        {
          if ( v92 < v196 ) /*0x17dcb2*/
            v93 = *(unsigned __int8 *)(a2[2] + v92); /*0x17ea20*/
          else
            v93 = *(unsigned __int8 *)(a2[3] + v92 - v196); /*0x17dcc3*/
          a2[7] = v92 + 1; /*0x17dcca*/
        }
        a5[86] = v93; /*0x17dce0*/
        v196 = a2[5]; /*0x17dce9*/
      }
      goto LABEL_133; /*0x17dce9*/
    }
LABEL_321:
    *a2 = 1; /*0x17ea73*/
    LOBYTE(v44) = -1; /*0x17ea79*/
    goto LABEL_63; /*0x17ea7e*/
  }
LABEL_133:
  v94 = a2[8]; /*0x17dcef*/
  v95 = v94; /*0x17dcf2*/
  v96 = v94 & 7; /*0x17dcf6*/
  if ( (v94 & 7) == 0 ) /*0x17dcf9*/
  {
    v97 = a2[7]; /*0x17dcff*/
    if ( v97 >= a2[6] + v196 ) /*0x17dd0d*/
    {
      *a2 = 1; /*0x17dd13*/
LABEL_136:
      v208 = 0; /*0x17dd19*/
      while ( 1 ) /*0x17dd25*/
      {
        v98 = v94 & 7; /*0x17dd25*/
        if ( (v94 & 7) != 0 ) /*0x17dd28*/
          goto LABEL_163; /*0x17dd28*/
        v99 = a2[7]; /*0x17dd2e*/
        if ( v99 < a2[6] + v196 ) /*0x17dd3c*/
          break; /*0x17dd3c*/
        *a2 = 1; /*0x17dd42*/
LABEL_140:
        if ( cl_shownet && *(_DWORD *)(cl_shownet + 12) == 4 ) /*0x17dd58*/
        {
          Com_Printf(16, "%s ", "PS_AMMO"); /*0x17e945*/
          v196 = a2[5]; /*0x17e94d*/
        }
        v100 = a2[7]; /*0x17dd5e*/
        if ( v100 + 2 > a2[6] + v196 ) /*0x17dd6f*/
        {
          *a2 = 1; /*0x17e601*/
          v199 = -1; /*0x17e607*/
        }
        else
        {
          if ( v100 >= v196 ) /*0x17dd7b*/
            v101 = *(_BYTE *)(a2[3] + v100 - v196); /*0x17e71c*/
          else
            v101 = *(_BYTE *)(a2[2] + v100); /*0x17dd84*/
          LOBYTE(v221) = v101; /*0x17dd88*/
          v102 = v100 + 1; /*0x17dd8e*/
          if ( v100 + 1 < v196 ) /*0x17dd97*/
            v103 = *(_BYTE *)(a2[2] + v102); /*0x17e708*/
          else
            v103 = *(_BYTE *)(a2[3] + v102 - v196); /*0x17dda6*/
          HIBYTE(v221) = v103; /*0x17ddaa*/
          v199 = v221; /*0x17ddb7*/
          a2[7] = v100 + 2; /*0x17ddbd*/
        }
        v104 = &a5[v208 + 87]; /*0x17ddcc*/
        for ( j = 0; j != 16; ++j ) /*0x17ddd3*/
        {
          if ( ((v199 >> j) & 1) != 0 ) /*0x17de42*/
          {
            v110 = a2[7]; /*0x17de44*/
            if ( v110 + 2 <= a2[6] + v196 ) /*0x17de5f*/
            {
              if ( v110 >= v196 ) /*0x17dddd*/
                v106 = *(_BYTE *)(a2[3] + v110 - v196); /*0x17de86*/
              else
                v106 = *(_BYTE *)(a2[2] + v110); /*0x17dde6*/
              LOBYTE(v222) = v106; /*0x17ddea*/
              v107 = v110 + 1; /*0x17ddf0*/
              if ( v110 + 1 < v196 ) /*0x17ddf9*/
                v108 = *(_BYTE *)(a2[2] + v107); /*0x17de75*/
              else
                v108 = *(_BYTE *)(a2[3] + v107 - v196); /*0x17de04*/
              HIBYTE(v222) = v108; /*0x17de08*/
              v109 = v222; /*0x17de0e*/
              a2[7] = v110 + 2; /*0x17de1b*/
            }
            else
            {
              *a2 = 1; /*0x17de65*/
              v109 = -1; /*0x17de6b*/
            }
            *v104 = v109; /*0x17de1e*/
            v196 = a2[5]; /*0x17de23*/
          }
          ++v104; /*0x17de2a*/
        }
LABEL_166:
        v208 += 16; /*0x17dec6*/
        if ( v208 == 64 ) /*0x17ded4*/
          goto LABEL_172; /*0x17ded4*/
        v94 = a2[8]; /*0x17ded6*/
      }
      v94 = 8 * v99; /*0x17de8f*/
      a2[8] = v94; /*0x17de92*/
      ++a2[7]; /*0x17de95*/
LABEL_163:
      v111 = v94 >> 3; /*0x17de98*/
      if ( v94 >> 3 < v196 ) /*0x17dea3*/
        v112 = *(unsigned __int8 *)(a2[2] + v111); /*0x17e5f8*/
      else
        v112 = *(unsigned __int8 *)(a2[3] + v111 - v196); /*0x17deb2*/
      a2[8] = v94 + 1; /*0x17deb7*/
      if ( ((v112 >> v98) & 1) == 0 ) /*0x17dec0*/
        goto LABEL_166; /*0x17dec0*/
      goto LABEL_140; /*0x17dec0*/
    }
    a2[8] = 8 * v97; /*0x17dee5*/
    ++a2[7]; /*0x17dee8*/
    v95 = 8 * v97; /*0x17deeb*/
  }
  v113 = v95 >> 3; /*0x17deef*/
  if ( v95 >> 3 < v196 ) /*0x17def8*/
    v114 = *(unsigned __int8 *)(a2[2] + v113); /*0x17e749*/
  else
    v114 = *(unsigned __int8 *)(a2[3] + v113 - v196); /*0x17df07*/
  v94 = v95 + 1; /*0x17df0b*/
  a2[8] = v95 + 1; /*0x17df0e*/
  if ( ((v114 >> v96) & 1) != 0 ) /*0x17df17*/
    goto LABEL_136; /*0x17df17*/
LABEL_172:
  for ( k = 0; k != 128; k += 16 ) /*0x17df1d*/
  {
    v115 = a2[8]; /*0x17df27*/
    v116 = v115 & 7; /*0x17df2c*/
    if ( (v115 & 7) != 0 ) /*0x17df2f*/
      goto LABEL_199; /*0x17df2f*/
    v117 = a2[7]; /*0x17df35*/
    if ( v117 < a2[6] + v196 ) /*0x17df43*/
    {
      v115 = 8 * v117; /*0x17e0a4*/
      a2[8] = v115; /*0x17e0a7*/
      ++a2[7]; /*0x17e0aa*/
LABEL_199:
      v129 = v115 >> 3; /*0x17e0ad*/
      if ( v115 >> 3 < v196 ) /*0x17e0b8*/
        v130 = *(unsigned __int8 *)(a2[2] + v129); /*0x17e417*/
      else
        v130 = *(unsigned __int8 *)(a2[3] + v129 - v196); /*0x17e0c7*/
      a2[8] = v115 + 1; /*0x17e0cc*/
      if ( ((v130 >> v116) & 1) == 0 ) /*0x17e0d5*/
        continue; /*0x17e0d5*/
      goto LABEL_176; /*0x17e0d5*/
    }
    *a2 = 1; /*0x17df49*/
LABEL_176:
    if ( cl_shownet && *(_DWORD *)(cl_shownet + 12) == 4 ) /*0x17df5f*/
    {
      Com_Printf(16, "%s ", "PS_AMMOCLIP"); /*0x17e6b8*/
      v196 = a2[5]; /*0x17e6c0*/
    }
    v118 = a2[7]; /*0x17df65*/
    if ( v118 + 2 > a2[6] + v196 ) /*0x17df76*/
    {
      *a2 = 1; /*0x17e420*/
      v216 = -1; /*0x17e426*/
    }
    else
    {
      if ( v118 >= v196 ) /*0x17df82*/
        v119 = *(_BYTE *)(a2[3] + v118 - v196); /*0x17e460*/
      else
        v119 = *(_BYTE *)(a2[2] + v118); /*0x17df8b*/
      LOBYTE(v223) = v119; /*0x17df8f*/
      v120 = v118 + 1; /*0x17df95*/
      if ( v118 + 1 < v196 ) /*0x17df9e*/
        v121 = *(_BYTE *)(a2[2] + v120); /*0x17e44c*/
      else
        v121 = *(_BYTE *)(a2[3] + v120 - v196); /*0x17dfad*/
      HIBYTE(v223) = v121; /*0x17dfb1*/
      v216 = v223; /*0x17dfbe*/
      a2[7] = v118 + 2; /*0x17dfc4*/
    }
    v122 = &a5[k + 215]; /*0x17dfd3*/
    for ( m = 0; m != 16; ++m ) /*0x17dfda*/
    {
      if ( ((v216 >> m) & 1) != 0 ) /*0x17e04b*/
      {
        v128 = a2[7]; /*0x17e04d*/
        if ( v128 + 2 <= a2[6] + v196 ) /*0x17e068*/
        {
          if ( v128 >= v196 ) /*0x17dfe6*/
            v124 = *(_BYTE *)(a2[3] + v128 - v196); /*0x17e09b*/
          else
            v124 = *(_BYTE *)(a2[2] + v128); /*0x17dfef*/
          LOBYTE(v224) = v124; /*0x17dff3*/
          v125 = v128 + 1; /*0x17dff9*/
          if ( v128 + 1 < v196 ) /*0x17e002*/
            v126 = *(_BYTE *)(a2[2] + v125); /*0x17e083*/
          else
            v126 = *(_BYTE *)(a2[3] + v125 - v196); /*0x17e00d*/
          HIBYTE(v224) = v126; /*0x17e011*/
          v127 = v224; /*0x17e017*/
          a2[7] = v128 + 2; /*0x17e024*/
        }
        else
        {
          *a2 = 1; /*0x17e06e*/
          v127 = -1; /*0x17e074*/
        }
        *v122 = v127; /*0x17e027*/
        v196 = a2[5]; /*0x17e02c*/
      }
      ++v122; /*0x17e033*/
    }
  }
  v131 = a2[8]; /*0x17e0f2*/
  v132 = v131; /*0x17e0f5*/
  v133 = v131 & 7; /*0x17e0f9*/
  if ( (v131 & 7) == 0 ) /*0x17e0fc*/
  {
    v134 = a2[7]; /*0x17e102*/
    if ( v134 >= a2[6] + v196 ) /*0x17e110*/
    {
      *a2 = 1; /*0x17e116*/
      goto LABEL_206; /*0x17e116*/
    }
    a2[8] = 8 * v134; /*0x17e470*/
    ++a2[7]; /*0x17e473*/
    v132 = 8 * v134; /*0x17e476*/
  }
  v163 = v132 >> 3; /*0x17e47a*/
  if ( v132 >> 3 < v196 ) /*0x17e483*/
    v164 = *(unsigned __int8 *)(a2[2] + v163); /*0x17e731*/
  else
    v164 = *(unsigned __int8 *)(a2[3] + v163 - v196); /*0x17e492*/
  v131 = v132 + 1; /*0x17e496*/
  a2[8] = v132 + 1; /*0x17e499*/
  if ( ((v164 >> v133) & 1) != 0 ) /*0x17e4a2*/
  {
LABEL_206:
    v206 = a5; /*0x17e11c*/
    v213 = 0; /*0x17e135*/
    while ( 1 ) /*0x17e160*/
    {
      v135 = v131; /*0x17e160*/
      v136 = v131 & 7; /*0x17e164*/
      if ( (v131 & 7) == 0 ) /*0x17e167*/
      {
        v137 = a2[7]; /*0x17e169*/
        if ( v137 >= a2[6] + v196 ) /*0x17e177*/
          goto LABEL_281; /*0x17e177*/
        v138 = 8 * v137; /*0x17e17d*/
        a2[8] = v138; /*0x17e180*/
        ++a2[7]; /*0x17e183*/
        v135 = v138; /*0x17e186*/
      }
      v139 = v135 >> 3; /*0x17e18a*/
      if ( v135 >> 3 >= v196 ) /*0x17e193*/
        v140 = *(unsigned __int8 *)(a2[3] + v139 - v196); /*0x17e3e1*/
      else
        v140 = *(unsigned __int8 *)(a2[2] + v139); /*0x17e19c*/
      v141 = (v140 >> v136) & 1; /*0x17e1a6*/
      v194 = v135 + 1; /*0x17e1aa*/
      a2[8] = v135 + 1; /*0x17e1b0*/
      v142 = (v135 + 1) & 7; /*0x17e1b3*/
      if ( !v142 ) /*0x17e1b6*/
      {
        v143 = a2[7]; /*0x17e1b8*/
        if ( v143 >= a2[6] + v196 ) /*0x17e1c6*/
          goto LABEL_281; /*0x17e1c6*/
        v144 = 8 * v143; /*0x17e1cc*/
        a2[8] = v144; /*0x17e1cf*/
        ++a2[7]; /*0x17e1d2*/
        v194 = v144; /*0x17e1d5*/
      }
      v145 = v194 >> 3; /*0x17e1e1*/
      if ( v194 >> 3 >= v196 ) /*0x17e1ea*/
        v146 = *(unsigned __int8 *)(a2[3] + v145 - v196); /*0x17e3f3*/
      else
        v146 = *(unsigned __int8 *)(a2[2] + v145); /*0x17e1f3*/
      v147 = v141 | (2 * ((v146 >> v142) & 1)); /*0x17e201*/
      v148 = v194 + 1; /*0x17e209*/
      a2[8] = v194 + 1; /*0x17e20a*/
      if ( (((_BYTE)v194 + 1) & 7) == 0 ) /*0x17e212*/
      {
        v149 = a2[7]; /*0x17e214*/
        if ( v149 >= a2[6] + v196 ) /*0x17e222*/
        {
LABEL_281:
          *a2 = 1; /*0x17e691*/
          v153 = -1; /*0x17e697*/
          goto LABEL_223; /*0x17e69c*/
        }
        v150 = 8 * v149; /*0x17e228*/
        a2[8] = v150; /*0x17e22b*/
        ++a2[7]; /*0x17e22e*/
        v148 = v150; /*0x17e231*/
      }
      v151 = v148 >> 3; /*0x17e235*/
      if ( v148 >> 3 < v196 ) /*0x17e23e*/
        v152 = *(unsigned __int8 *)(a2[2] + v151); /*0x17e3ff*/
      else
        v152 = *(unsigned __int8 *)(a2[3] + v151 - v196); /*0x17e24d*/
      a2[8] = v148 + 1; /*0x17e254*/
      v153 = v147 | (4 * ((v152 >> ((v194 + 1) & 7)) & 1)); /*0x17e261*/
LABEL_223:
      v206[407] = v153; /*0x17e263*/
      v154 = 28 * v213 + 1616; /*0x17e276*/
      v204 = (int)v197 + v154 + 12; /*0x17e285*/
      v203 = (char *)a5 + v154 + 12; /*0x17e295*/
      v155 = a2[8]; /*0x17e29e*/
      v156 = v155 & 7; /*0x17e2a2*/
      if ( (v155 & 7) != 0 ) /*0x17e2a5*/
      {
        v196 = a2[5]; /*0x17e351*/
      }
      else
      {
        v157 = a2[7]; /*0x17e2ab*/
        v196 = a2[5]; /*0x17e2b1*/
        if ( v157 >= a2[6] + v196 ) /*0x17e2be*/
        {
          *a2 = 1; /*0x17e2c4*/
LABEL_226:
          if ( numObjectiveFields > 0 ) /*0x17e2d2*/
          {
            v158 = (const char **)&objectiveFields; /*0x17e2d4*/
            v159 = 0; /*0x17e2da*/
            do /*0x17e321*/
            {
              MSG_ReadDeltaField(a2, a3, v204, (int)v203, v158, 0, 0); /*0x17e312*/
              ++v159; /*0x17e317*/
              v158 += 4; /*0x17e318*/
            }
            while ( v159 != numObjectiveFields ); /*0x17e321*/
            v196 = a2[5]; /*0x17e326*/
          }
          goto LABEL_230; /*0x17e326*/
        }
        a2[8] = 8 * v157; /*0x17e43c*/
        ++a2[7]; /*0x17e43f*/
        v155 = 8 * v157; /*0x17e442*/
      }
      v160 = v155 >> 3; /*0x17e359*/
      if ( v155 >> 3 < v196 ) /*0x17e362*/
        v161 = *(unsigned __int8 *)(a2[2] + v160); /*0x17e40b*/
      else
        v161 = *(unsigned __int8 *)(a2[3] + v160 - v196); /*0x17e371*/
      a2[8] = v155 + 1; /*0x17e378*/
      if ( ((v161 >> v156) & 1) != 0 ) /*0x17e381*/
        goto LABEL_226; /*0x17e381*/
      v162 = 0; /*0x17e387*/
      if ( numObjectiveFields > 0 ) /*0x17e391*/
      {
        do /*0x17e3c8*/
        {
          *(_DWORD *)&v203[*((_DWORD *)&objectiveFields + 4 * v162 + 1)] = *(_DWORD *)(*((_DWORD *)&objectiveFields /*0x17e3be*/
                                                                                       + 4 * v162
                                                                                       + 1)
                                                                                     + v204);
          ++v162; /*0x17e3c1*/
        }
        while ( v162 != numObjectiveFields ); /*0x17e3c8*/
        v196 = a2[5]; /*0x17e3cd*/
      }
LABEL_230:
      ++v213; /*0x17e32c*/
      v206 += 7; /*0x17e332*/
      if ( v213 == 16 ) /*0x17e340*/
        break; /*0x17e340*/
      v131 = a2[8]; /*0x17e346*/
    }
  }
  v165 = a2[8]; /*0x17e4a8*/
  v166 = v165 & 7; /*0x17e4ad*/
  if ( (v165 & 7) == 0 ) /*0x17e4b0*/
  {
    v167 = a2[7]; /*0x17e4b6*/
    if ( v167 >= a2[6] + v196 ) /*0x17e4c4*/
    {
      *a2 = 1; /*0x17e4ca*/
      goto LABEL_255; /*0x17e4ca*/
    }
    v165 = 8 * v167; /*0x17e655*/
    a2[8] = v165; /*0x17e658*/
    ++a2[7]; /*0x17e65b*/
  }
  v177 = v165 >> 3; /*0x17e660*/
  if ( v165 >> 3 < v196 ) /*0x17e669*/
    v178 = *(unsigned __int8 *)(a2[2] + v177); /*0x17e755*/
  else
    v178 = *(unsigned __int8 *)(a2[3] + v177 - v196); /*0x17e678*/
  v168 = v165 + 1; /*0x17e67c*/
  a2[8] = v168; /*0x17e67d*/
  if ( ((v178 >> v166) & 1) != 0 ) /*0x17e686*/
  {
LABEL_255:
    MSG_ReadDeltaHudElems(a2, a3, (int)(v197 + 1793), (int)(a5 + 1793), 31); /*0x17e4d0*/
    MSG_ReadDeltaHudElems(a2, a3, (int)(v197 + 553), (int)(a5 + 553), 31); /*0x17e523*/
    v196 = a2[5]; /*0x17e52b*/
    v168 = a2[8]; /*0x17e531*/
  }
  v169 = v168 & 7; /*0x17e536*/
  if ( (v168 & 7) == 0 )
  {
    v170 = a2[7]; /*0x17e53f*/
    if ( v170 >= a2[6] + v196 )
    {
      *a2 = 1; /*0x17e553*/
LABEL_259:
      v171 = 0; /*0x17e559*/
      for ( n = v196; ; n = v196 )
      {
        if ( v170 < a2[6] + n )
        {
          v173 = v170 < v196 ? *(unsigned __int8 *)(a2[2] + v170) : *(unsigned __int8 *)(a2[3] + v170 - v196);
          a2[7] = v170 + 1; /*0x17e58a*/
          result = v173; /*0x17e58d*/
        }
        else
        {
          *a2 = 1; /*0x17e5ba*/
          result = -1; /*0x17e5c0*/
        }
        *((_BYTE *)a5 + v171 + 2076) = result; /*0x17e595*/
        if ( ++v171 == 128 ) /*0x17e5a3*/
          break; /*0x17e5a3*/
        v170 = a2[7]; /*0x17e5a5*/
        v196 = a2[5]; /*0x17e5ab*/
      }
      return result; /*0x17e5a3*/
    }
    v168 = 8 * v170; /*0x17e616*/
    a2[8] = 8 * v170; /*0x17e61d*/
    ++a2[7]; /*0x17e620*/
  }
  v175 = v168 >> 3; /*0x17e625*/
  if ( v168 >> 3 < v196 ) /*0x17e62e*/
    v176 = *(unsigned __int8 *)(a2[2] + v175); /*0x17e73d*/
  else
    v176 = *(unsigned __int8 *)(a2[3] + v175 - v196); /*0x17e63d*/
  a2[8] = v168 + 1; /*0x17e642*/
  result = v176 >> v169; /*0x17e647*/
  if ( (result & 1) != 0 ) /*0x17e64b*/
  {
    v170 = a2[7]; /*0x17e64d*/
    goto LABEL_259; /*0x17e650*/
  }
  return result; /*0x17e5ea*/
}