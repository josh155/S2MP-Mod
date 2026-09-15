// positive sp value has been detected, the output may be wrong!
__int64 __fastcall sub_4EE63E(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, char a6)
{
  _DWORD *v6; // rbp
  __int64 v7; // rsi
  int v8; // r12d
  int v9; // r13d
  __int64 v10; // r14
  __int64 v11; // r15
  int v12; // edi
  __int64 v13; // rsi
  char v14; // al
  _BYTE *v15; // rbx
  bool v16; // al
  bool v17; // al
  int v18; // edi
  char v19; // r12
  __int64 v20; // rbx
  __int64 v21; // rbx
  char *v22; // r15
  int v23; // r8d
  int v24; // ecx
  int v25; // ecx
  unsigned __int8 v26; // dl
  char v27; // bl
  int v28; // r8d
  int v29; // ecx
  int v30; // ecx
  unsigned __int8 v31; // dl
  int v32; // r9d
  __int64 v33; // rdi
  int v34; // ebx
  bool v35; // al
  __int64 v36; // rbx
  _DWORD *v37; // rbx
  __int64 v38; // rdi
  int v39; // r8d
  int v40; // ecx
  int v41; // ecx
  unsigned __int8 v42; // dl
  int v43; // r9d
  int v44; // ecx
  int v45; // ecx
  unsigned __int8 v46; // dl
  int v47; // edi
  __int64 v48; // rsi
  int v49; // r10d
  int v50; // r8d
  int v51; // edx
  int v52; // ecx
  unsigned __int8 v53; // dl
  int v54; // r9d
  int v55; // r9d
  int v56; // edx
  int v57; // r9d
  int v58; // edx
  int v59; // ecx
  unsigned __int8 v60; // dl
  __int64 v61; // rax
  int v62; // ecx
  unsigned __int8 v63; // dl
  int v64; // r8d
  int v65; // ecx
  int v66; // eax
  int v67; // ecx
  unsigned __int8 v68; // dl
  int v69; // r8d
  int v70; // ecx
  int v71; // eax
  int v72; // ecx
  unsigned __int8 v73; // dl
  int v74; // r8d
  int v75; // ecx
  int v76; // eax
  int v77; // ecx
  unsigned __int8 v78; // dl
  int v79; // r8d
  int v80; // ecx
  int v81; // eax
  int v82; // ecx
  unsigned __int8 v83; // dl
  int v84; // r8d
  int v85; // ecx
  int v86; // ecx
  unsigned __int8 v87; // dl
  int v88; // r8d
  int v89; // ecx
  int v90; // eax
  int v91; // ecx
  unsigned __int8 v92; // dl
  int v93; // r9d
  int v94; // ecx
  int v95; // eax
  int v96; // ecx
  unsigned __int8 v97; // dl
  int v98; // r8d
  int v99; // ecx
  int v100; // eax
  int v101; // ecx
  unsigned __int8 v102; // dl
  int v103; // r8d
  int v104; // ecx
  int v105; // eax
  int v106; // ecx
  unsigned __int8 v107; // dl
  int v108; // r9d
  int v109; // edx
  int v110; // ecx
  unsigned __int8 v111; // dl
  int v112; // r8d
  int v113; // ecx
  int v114; // ecx
  unsigned __int8 v115; // dl
  int v116; // r9d
  __int64 v117; // rbx
  int v118; // r8d
  int v119; // ecx
  int v120; // ecx
  unsigned __int8 v121; // dl
  char v122; // al
  int v123; // r10d
  int v124; // r8d
  int v125; // edx
  int v126; // eax
  int v127; // ecx
  unsigned __int8 v128; // dl
  int v129; // r9d
  int v130; // ecx
  int v131; // ecx
  unsigned __int8 v132; // dl
  _DWORD *v133; // rdi
  _DWORD *v134; // rbx
  __int64 v135; // rsi
  char *v136; // r15
  int v137; // r12d
  void *v138; // r13
  int v139; // r8d
  int v140; // ecx
  int v141; // ecx
  unsigned __int8 v142; // dl
  char *v143; // rbx
  __int64 v144; // rsi
  int v145; // edi
  __int64 v146; // rbp
  int v147; // ebx
  int v148; // eax
  float v150; // [rsp-4918h] [rbp-4918h]
  int v151; // [rsp-4910h] [rbp-4910h]
  char v152; // [rsp-4908h] [rbp-4908h]
  unsigned __int8 v153; // [rsp-4907h] [rbp-4907h]
  int v154; // [rsp-4904h] [rbp-4904h]
  char v155; // [rsp-4900h] [rbp-4900h]
  unsigned int v156; // [rsp-48FCh] [rbp-48FCh]
  char *v157; // [rsp-48F8h] [rbp-48F8h]
  int v158; // [rsp-48F0h] [rbp-48F0h]
  int v159; // [rsp-48ECh] [rbp-48ECh]
  __int64 v160; // [rsp-48E8h] [rbp-48E8h]
  _DWORD *v161; // [rsp-48E0h] [rbp-48E0h]

  if ( v8 > -1 ) /*0x4ee64f*/
  {
    while ( 1 ) /*0x4ee663*/
    {
      v12 = v9 + 1; /*0x4ee663*/
      v9 += sub_4F0780(v10, 4, (unsigned int)(v8 - v9)); /*0x4ee677*/
      if ( v12 < v9 ) /*0x4ee67d*/
        break; /*0x4ee67d*/
LABEL_12:
      v16 = !v155 && (*(_BYTE *)(v11 + 8LL * v9 + 6) & 4) != 0; /*0x4ee715*/
      v17 = a6 && v16; /*0x4ee725*/
      LOBYTE(v150) = v17; /*0x4ee732*/
      sub_4ED0E0(v10, v156, v7, (__int64)v6, (unsigned __int16 *)(v11 + 8LL * v9), 0, v150); /*0x4ee749*/
      if ( v9 >= v8 ) /*0x4ee751*/
      {
        v158 = v9; /*0x4ee757*/
        goto LABEL_22; /*0x4ee757*/
      }
    }
    v13 = v11 + 8LL * v12; /*0x4ee68d*/
    v14 = v152; /*0x4ee691*/
    v15 = (_BYTE *)(v13 + 6); /*0x4ee696*/
    while ( v14 || (*(_WORD *)v15 & 0x1F0) == 0 ) /*0x4ee6ac*/
    {
      if ( (*v15 & 2) == 0 ) /*0x4ee6c7*/
      {
        sub_4EC1F0(v11, (__int64)v157, (__int64)v6, v12); /*0x4ee6d5*/
        goto LABEL_9; /*0x4ee6d5*/
      }
LABEL_10:
      ++v12; /*0x4ee6df*/
      v13 += 8; /*0x4ee6e1*/
      v15 += 8; /*0x4ee6e5*/
      if ( v12 >= v9 ) /*0x4ee6ec*/
      {
        v10 = v160; /*0x4ee6ee*/
        v8 = v159; /*0x4ee6f3*/
        v7 = (__int64)v157; /*0x4ee6f8*/
        goto LABEL_12; /*0x4ee6f8*/
      }
    }
    ((void (__fastcall *)(_QWORD, __int64, char *))sub_4F0B90)(v153, v13, (char *)v6 + *((unsigned __int16 *)v15 - 3)); /*0x4ee6bd*/
LABEL_9:
    v14 = v152; /*0x4ee6da*/
    goto LABEL_10; /*0x4ee6da*/
  }
LABEL_22:
  v18 = v9 + 1; /*0x4ee761*/
  v19 = v152; /*0x4ee76a*/
  v20 = v9 + 1; /*0x4ee770*/
  if ( v20 < v154 ) /*0x4ee776*/
  {
    do /*0x4ee7c8*/
    {
      if ( v152 || (*(_WORD *)(v11 + 8 * v20 + 6) & 0x1F0) == 0 ) /*0x4ee78e*/
        sub_4EC1F0(v11, (__int64)v157, (__int64)v6, v18); /*0x4ee7b6*/
      else
        ((void (__fastcall *)(_QWORD, __int64, char *))sub_4F0B90)( /*0x4ee7a3*/
          v153,
          v11 + 8LL * v18,
          (char *)v6 + *(unsigned __int16 *)(v11 + 8 * v20));
      ++v18; /*0x4ee7bb*/
      ++v20; /*0x4ee7bd*/
    }
    while ( v20 < v154 ); /*0x4ee7c8*/
    v10 = v160; /*0x4ee7ca*/
    v9 = v158; /*0x4ee7cf*/
  }
  v21 = v9; /*0x4ee7d4*/
  if ( v9 > 0 ) /*0x4ee7da*/
  {
    do /*0x4ee814*/
    {
      if ( (*(_BYTE *)(v11 + 6) & 2) != 0 ) /*0x4ee7e6*/
      {
        LOBYTE(v150) = 0; /*0x4ee7ef*/
        sub_4ED0E0(v10, v156, (__int64)v157, (__int64)v6, (unsigned __int16 *)v11, 0, v150); /*0x4ee807*/
      }
      v11 += 8; /*0x4ee80c*/
      --v21; /*0x4ee810*/
    }
    while ( v21 ); /*0x4ee814*/
    v19 = v152; /*0x4ee816*/
  }
  if ( v155 ) /*0x4ee821*/
  {
    v22 = v157; /*0x4ee835*/
    if ( !(unsigned int)CL_GetPredictedPlayerInformationForServerTime(qword_2EC84F0, v6[19], v6) ) /*0x4ee830*/
    {
      v6[30] = *((_DWORD *)v157 + 30); /*0x4ee842*/
      v6[31] = *((_DWORD *)v157 + 31); /*0x4ee849*/
      v6[32] = *((_DWORD *)v157 + 32); /*0x4ee853*/
      v6[33] = *((_DWORD *)v157 + 33); /*0x4ee860*/
      v6[34] = *((_DWORD *)v157 + 34); /*0x4ee86d*/
      v6[35] = *((_DWORD *)v157 + 35); /*0x4ee87a*/
      v6[29] = *((_DWORD *)v157 + 29); /*0x4ee884*/
      v6[50] = *((_DWORD *)v157 + 50); /*0x4ee88e*/
    }
  }
  else
  {
    v22 = v157; /*0x4ee896*/
  }
  v23 = *(_DWORD *)(v10 + 40) & 7; /*0x4ee89f*/
  if ( !v23 ) /*0x4ee8a3*/
  {
    v24 = *(_DWORD *)(v10 + 36); /*0x4ee8ad*/
    if ( v24 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) ) /*0x4ee8b3*/
    {
      *(_DWORD *)v10 = 1; /*0x4ee8b5*/
LABEL_46:
      v27 = MSG_ReadBits(v10, 4); /*0x4ee910*/
      if ( (v27 & 1) != 0 ) /*0x4ee921*/
        v6[87] = Com_Printf(v10); /*0x4ee92b*/
      if ( (v27 & 2) != 0 ) /*0x4ee934*/
        v6[88] = Com_Printf(v10); /*0x4ee93e*/
      if ( (v27 & 4) != 0 ) /*0x4ee947*/
        v6[89] = Com_Printf(v10); /*0x4ee951*/
      if ( (v27 & 8) != 0 ) /*0x4ee95a*/
        v6[90] = sub_4EB510(v10); /*0x4ee964*/
      goto LABEL_54; /*0x4ee964*/
    }
    *(_DWORD *)(v10 + 40) = 8 * v24; /*0x4ee8c5*/
    *(_DWORD *)(v10 + 36) = v24 + 1; /*0x4ee8cc*/
  }
  v25 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28); /*0x4ee8dc*/
  if ( v25 < 0 ) /*0x4ee8e0*/
    v26 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4ee8f6*/
  else
    v26 = *(_BYTE *)(v25 + *(_QWORD *)(v10 + 16)); /*0x4ee8e9*/
  ++*(_DWORD *)(v10 + 40); /*0x4ee902*/
  if ( ((v26 >> v23) & 1) != 0 ) /*0x4ee90e*/
    goto LABEL_46; /*0x4ee90e*/
LABEL_54:
  v28 = *(_DWORD *)(v10 + 40) & 7; /*0x4ee970*/
  if ( !v28 ) /*0x4ee978*/
  {
    v29 = *(_DWORD *)(v10 + 36); /*0x4ee982*/
    if ( v29 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) ) /*0x4ee988*/
    {
      *(_DWORD *)v10 = 1; /*0x4ee98a*/
LABEL_62:
      v33 = 3LL * (int)MSG_ReadBits(v10, 4); /*0x4ee9e8*/
      v34 = MSG_ReadBits(v10, 1); /*0x4eea11*/
      v6[2 * v33 + 284] = MSG_ReadBits(v10, 27); /*0x4eea1a*/
      v35 = v34 != 0; /*0x4eea28*/
      v36 = 2 * (v33 + 143); /*0x4eea2b*/
      LOBYTE(v6[v36 - 1]) = v35; /*0x4eea33*/
      v37 = &v6[v36]; /*0x4eea37*/
      v38 = 2; /*0x4eea3a*/
      while ( 1 ) /*0x4eea44*/
      {
        v39 = *(_DWORD *)(v10 + 40) & 7; /*0x4eea44*/
        if ( v39 ) /*0x4eea48*/
          goto LABEL_67; /*0x4eea48*/
        v40 = *(_DWORD *)(v10 + 36); /*0x4eea52*/
        if ( v40 < *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) ) /*0x4eea58*/
          break; /*0x4eea58*/
        *(_DWORD *)v10 = 1; /*0x4eea5a*/
LABEL_71:
        *v37 = MSG_ReadBits(v10, 8); /*0x4eeab5*/
LABEL_72:
        ++v37; /*0x4eeac4*/
        if ( !--v38 ) /*0x4eeacc*/
          goto LABEL_54; /*0x4eeacc*/
      }
      *(_DWORD *)(v10 + 40) = 8 * v40; /*0x4eea6a*/
      *(_DWORD *)(v10 + 36) = v40 + 1; /*0x4eea71*/
LABEL_67:
      v41 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28); /*0x4eea75*/
      if ( v41 < 0 ) /*0x4eea85*/
        v42 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4eea9b*/
      else
        v42 = *(_BYTE *)(v41 + *(_QWORD *)(v10 + 16)); /*0x4eea8e*/
      ++*(_DWORD *)(v10 + 40); /*0x4eeaa7*/
      if ( ((v42 >> v39) & 1) == 0 ) /*0x4eeab3*/
        goto LABEL_72; /*0x4eeab3*/
      goto LABEL_71; /*0x4eeab3*/
    }
    *(_DWORD *)(v10 + 40) = 8 * v29; /*0x4ee99a*/
    *(_DWORD *)(v10 + 36) = v29 + 1; /*0x4ee9a1*/
  }
  v30 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28); /*0x4ee9b1*/
  if ( v30 < 0 ) /*0x4ee9b5*/
    v31 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4ee9cb*/
  else
    v31 = *(_BYTE *)(v30 + *(_QWORD *)(v10 + 16)); /*0x4ee9be*/
  v32 = *(_DWORD *)(v10 + 40) + 1; /*0x4ee9cf*/
  *(_DWORD *)(v10 + 40) = v32; /*0x4ee9d9*/
  if ( ((v31 >> v28) & 1) != 0 ) /*0x4ee9e2*/
    goto LABEL_62; /*0x4ee9e2*/
  v43 = v32 & 7; /*0x4eead7*/
  if ( !v43 ) /*0x4eeadb*/
  {
    v44 = *(_DWORD *)(v10 + 36); /*0x4eeae5*/
    if ( v44 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) ) /*0x4eeaeb*/
    {
      *(_DWORD *)v10 = 1; /*0x4eeaed*/
LABEL_82:
      v47 = 0; /*0x4eeb4c*/
      v48 = 0; /*0x4eeb58*/
      while ( 1 ) /*0x4eeb64*/
      {
        v49 = *(_DWORD *)(v10 + 40) & 7; /*0x4eeb64*/
        if ( !v49 ) /*0x4eeb68*/
        {
          v50 = *(_DWORD *)(v10 + 28); /*0x4eeb6e*/
          v51 = *(_DWORD *)(v10 + 36); /*0x4eeb75*/
          if ( v51 >= v50 + *(_DWORD *)(v10 + 32) ) /*0x4eeb7b*/
          {
            *(_DWORD *)v10 = 1; /*0x4eeb7d*/
LABEL_91:
            if ( v19 ) /*0x4eebe1*/
              goto LABEL_95; /*0x4eebe1*/
            v55 = *(_DWORD *)(v10 + 40) & 7; /*0x4eebe7*/
            if ( !v55 ) /*0x4eebeb*/
            {
              v56 = *(_DWORD *)(v10 + 36); /*0x4eebf1*/
              if ( v56 >= v50 + *(_DWORD *)(v10 + 32) ) /*0x4eebfa*/
              {
                *(_DWORD *)v10 = 1; /*0x4eebfc*/
LABEL_95:
                v57 = *(_DWORD *)(v10 + 40) & 7; /*0x4eec03*/
                if ( !v57 ) /*0x4eec0b*/
                {
                  v58 = *(_DWORD *)(v10 + 36); /*0x4eec15*/
                  if ( v58 >= v50 + *(_DWORD *)(v10 + 32) ) /*0x4eec1e*/
                  {
                    *(_DWORD *)v10 = 1; /*0x4eec24*/
                    goto LABEL_109; /*0x4eec2b*/
                  }
                  *(_DWORD *)(v10 + 40) = 8 * v58; /*0x4eecac*/
                  *(_DWORD *)(v10 + 36) = v58 + 1; /*0x4eecb3*/
                }
                v62 = (*(int *)(v10 + 40) >> 3) - v50; /*0x4eecc3*/
                if ( v62 < 0 ) /*0x4eecc6*/
                  v63 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4eecdc*/
                else
                  v63 = *(_BYTE *)(v62 + *(_QWORD *)(v10 + 16)); /*0x4eeccf*/
                ++*(_DWORD *)(v10 + 40); /*0x4eece8*/
                if ( ((v63 >> v57) & 1) != 0 ) /*0x4eecf4*/
LABEL_109:
                  v6[v48 + 151] = MSG_ReadBits(v10, 27); /*0x4eecf6*/
                v64 = *(_DWORD *)(v10 + 40) & 7; /*0x4eed0e*/
                if ( !v64 ) /*0x4eed12*/
                {
                  v65 = *(_DWORD *)(v10 + 36); /*0x4eed1c*/
                  if ( v65 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) ) /*0x4eed22*/
                  {
                    *(_DWORD *)v10 = 1; /*0x4eed24*/
                    v66 = -1; /*0x4eed2b*/
                    goto LABEL_118; /*0x4eed2e*/
                  }
                  *(_DWORD *)(v10 + 40) = 8 * v65; /*0x4eed37*/
                  *(_DWORD *)(v10 + 36) = v65 + 1; /*0x4eed3e*/
                }
                v67 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28); /*0x4eed4e*/
                if ( v67 < 0 ) /*0x4eed52*/
                  v68 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4eed68*/
                else
                  v68 = *(_BYTE *)(v67 + *(_QWORD *)(v10 + 16)); /*0x4eed5b*/
                ++*(_DWORD *)(v10 + 40); /*0x4eed74*/
                v66 = (v68 >> v64) & 1; /*0x4eed7d*/
LABEL_118:
                LOBYTE(v6[4 * v48 + 166]) = v66 > 0; /*0x4eed80*/
                v69 = *(_DWORD *)(v10 + 40) & 7; /*0x4eed96*/
                if ( !v69 ) /*0x4eed9a*/
                {
                  v70 = *(_DWORD *)(v10 + 36); /*0x4eeda4*/
                  if ( v70 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) ) /*0x4eedaa*/
                  {
                    *(_DWORD *)v10 = 1; /*0x4eedac*/
                    v71 = -1; /*0x4eedb3*/
                    goto LABEL_126; /*0x4eedb6*/
                  }
                  *(_DWORD *)(v10 + 40) = 8 * v70; /*0x4eedbf*/
                  *(_DWORD *)(v10 + 36) = v70 + 1; /*0x4eedc6*/
                }
                v72 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28); /*0x4eedd6*/
                if ( v72 < 0 ) /*0x4eedda*/
                  v73 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4eedf0*/
                else
                  v73 = *(_BYTE *)(v72 + *(_QWORD *)(v10 + 16)); /*0x4eede3*/
                ++*(_DWORD *)(v10 + 40); /*0x4eedfc*/
                v71 = (v73 >> v69) & 1; /*0x4eee05*/
LABEL_126:
                BYTE1(v6[4 * v48 + 166]) = v71 > 0; /*0x4eee08*/
                v74 = *(_DWORD *)(v10 + 40) & 7; /*0x4eee18*/
                if ( !v74 ) /*0x4eee1c*/
                {
                  v75 = *(_DWORD *)(v10 + 36); /*0x4eee26*/
                  if ( v75 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) ) /*0x4eee2c*/
                  {
                    *(_DWORD *)v10 = 1; /*0x4eee2e*/
                    v76 = -1; /*0x4eee35*/
                    goto LABEL_134; /*0x4eee38*/
                  }
                  *(_DWORD *)(v10 + 40) = 8 * v75; /*0x4eee41*/
                  *(_DWORD *)(v10 + 36) = v75 + 1; /*0x4eee48*/
                }
                v77 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28); /*0x4eee58*/
                if ( v77 < 0 ) /*0x4eee5c*/
                  v78 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4eee72*/
                else
                  v78 = *(_BYTE *)(v77 + *(_QWORD *)(v10 + 16)); /*0x4eee65*/
                ++*(_DWORD *)(v10 + 40); /*0x4eee7e*/
                v76 = (v78 >> v74) & 1; /*0x4eee87*/
LABEL_134:
                BYTE2(v6[4 * v48 + 166]) = v76 > 0; /*0x4eee8a*/
                if ( v19 ) /*0x4eee99*/
                {
                  v79 = *(_DWORD *)(v10 + 40) & 7; /*0x4eeea3*/
                  if ( !v79 ) /*0x4eeea7*/
                  {
                    v80 = *(_DWORD *)(v10 + 36); /*0x4eeeb1*/
                    if ( v80 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) ) /*0x4eeeb7*/
                    {
                      *(_DWORD *)v10 = 1; /*0x4eeeb9*/
                      v81 = -1; /*0x4eeec0*/
                      goto LABEL_143; /*0x4eeec3*/
                    }
                    *(_DWORD *)(v10 + 40) = 8 * v80; /*0x4eeecc*/
                    *(_DWORD *)(v10 + 36) = v80 + 1; /*0x4eeed3*/
                  }
                  v82 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28); /*0x4eeee3*/
                  if ( v82 < 0 ) /*0x4eeee7*/
                    v83 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4eeefd*/
                  else
                    v83 = *(_BYTE *)(v82 + *(_QWORD *)(v10 + 16)); /*0x4eeef0*/
                  ++*(_DWORD *)(v10 + 40); /*0x4eef09*/
                  v81 = (v83 >> v79) & 1; /*0x4eef12*/
LABEL_143:
                  HIBYTE(v6[4 * v48 + 166]) = v81 > 0; /*0x4eef15*/
                  v84 = *(_DWORD *)(v10 + 40) & 7; /*0x4eef25*/
                  if ( !v84 ) /*0x4eef29*/
                  {
                    v85 = *(_DWORD *)(v10 + 36); /*0x4eef33*/
                    if ( v85 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) ) /*0x4eef39*/
                    {
                      *(_DWORD *)v10 = 1; /*0x4eef3e*/
                      LOBYTE(v6[4 * v48 + 167]) = 0; /*0x4eef4a*/
                      goto LABEL_152; /*0x4eef51*/
                    }
                    *(_DWORD *)(v10 + 40) = 8 * v85; /*0x4eef5a*/
                    *(_DWORD *)(v10 + 36) = v85 + 1; /*0x4eef61*/
                  }
                  v86 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28); /*0x4eef71*/
                  if ( v86 < 0 ) /*0x4eef75*/
                    v87 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4eef8b*/
                  else
                    v87 = *(_BYTE *)(v86 + *(_QWORD *)(v10 + 16)); /*0x4eef7e*/
                  ++*(_DWORD *)(v10 + 40); /*0x4eef97*/
                  LOBYTE(v6[4 * v48 + 167]) = ((v87 >> v84) & 1) != 0; /*0x4eefa8*/
                }
                else
                {
                  *(_WORD *)((char *)&v6[4 * v48 + 166] + 3) = 0; /*0x4eefb1*/
                }
LABEL_152:
                v88 = *(_DWORD *)(v10 + 40) & 7; /*0x4eefba*/
                if ( !v88 ) /*0x4eefc2*/
                {
                  v89 = *(_DWORD *)(v10 + 36); /*0x4eefcc*/
                  if ( v89 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) ) /*0x4eefd2*/
                  {
                    *(_DWORD *)v10 = 1; /*0x4eefd4*/
                    v90 = -1; /*0x4eefdb*/
                    goto LABEL_160; /*0x4eefde*/
                  }
                  *(_DWORD *)(v10 + 40) = 8 * v89; /*0x4eefe7*/
                  *(_DWORD *)(v10 + 36) = v89 + 1; /*0x4eefee*/
                }
                v91 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28); /*0x4eeffe*/
                if ( v91 < 0 ) /*0x4ef002*/
                  v92 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4ef018*/
                else
                  v92 = *(_BYTE *)(v91 + *(_QWORD *)(v10 + 16)); /*0x4ef00b*/
                ++*(_DWORD *)(v10 + 40); /*0x4ef024*/
                v90 = (v92 >> v88) & 1; /*0x4ef02d*/
LABEL_160:
                BYTE1(v6[4 * v48 + 167]) = v90 > 0; /*0x4ef030*/
                v6[4 * v48 + 168] = MSG_ReadBits(v10, 2); /*0x4ef050*/
                v93 = *(_DWORD *)(v10 + 40) & 7; /*0x4ef058*/
                if ( !v93 ) /*0x4ef05c*/
                {
                  v94 = *(_DWORD *)(v10 + 36); /*0x4ef066*/
                  if ( v94 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) ) /*0x4ef06c*/
                  {
                    *(_DWORD *)v10 = 1; /*0x4ef06e*/
                    v95 = -1; /*0x4ef075*/
                    goto LABEL_168; /*0x4ef078*/
                  }
                  *(_DWORD *)(v10 + 40) = 8 * v94; /*0x4ef081*/
                  *(_DWORD *)(v10 + 36) = v94 + 1; /*0x4ef088*/
                }
                v96 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28); /*0x4ef098*/
                if ( v96 < 0 ) /*0x4ef09c*/
                  v97 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4ef0b2*/
                else
                  v97 = *(_BYTE *)(v96 + *(_QWORD *)(v10 + 16)); /*0x4ef0a5*/
                ++*(_DWORD *)(v10 + 40); /*0x4ef0be*/
                v95 = (v97 >> v93) & 1; /*0x4ef0c7*/
LABEL_168:
                LOBYTE(v6[4 * v48 + 169]) = v95 > 0; /*0x4ef0ca*/
                v98 = *(_DWORD *)(v10 + 40) & 7; /*0x4ef0da*/
                if ( !v98 ) /*0x4ef0de*/
                {
                  v99 = *(_DWORD *)(v10 + 36); /*0x4ef0e8*/
                  if ( v99 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) ) /*0x4ef0ee*/
                  {
                    *(_DWORD *)v10 = 1; /*0x4ef0f0*/
                    v100 = -1; /*0x4ef0f7*/
                    goto LABEL_176; /*0x4ef0fa*/
                  }
                  *(_DWORD *)(v10 + 40) = 8 * v99; /*0x4ef103*/
                  *(_DWORD *)(v10 + 36) = v99 + 1; /*0x4ef10a*/
                }
                v101 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28); /*0x4ef11a*/
                if ( v101 < 0 ) /*0x4ef11e*/
                  v102 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4ef134*/
                else
                  v102 = *(_BYTE *)(v101 + *(_QWORD *)(v10 + 16)); /*0x4ef127*/
                ++*(_DWORD *)(v10 + 40); /*0x4ef140*/
                v100 = (v102 >> v98) & 1; /*0x4ef149*/
LABEL_176:
                BYTE1(v6[4 * v48 + 169]) = v100 > 0; /*0x4ef14c*/
                BYTE2(v6[4 * v48 + 169]) = v153 + 1; /*0x4ef15c*/
                v103 = *(_DWORD *)(v10 + 40) & 7; /*0x4ef167*/
                if ( !v103 ) /*0x4ef16b*/
                {
                  v104 = *(_DWORD *)(v10 + 36); /*0x4ef175*/
                  if ( v104 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) ) /*0x4ef17b*/
                  {
                    *(_DWORD *)v10 = 1; /*0x4ef17d*/
                    v105 = -1; /*0x4ef184*/
                    goto LABEL_184; /*0x4ef187*/
                  }
                  *(_DWORD *)(v10 + 40) = 8 * v104; /*0x4ef190*/
                  *(_DWORD *)(v10 + 36) = v104 + 1; /*0x4ef197*/
                }
                v106 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28); /*0x4ef1a7*/
                if ( v106 < 0 ) /*0x4ef1ab*/
                  v107 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4ef1c1*/
                else
                  v107 = *(_BYTE *)(v106 + *(_QWORD *)(v10 + 16)); /*0x4ef1b4*/
                ++*(_DWORD *)(v10 + 40); /*0x4ef1cd*/
                v105 = (v107 >> v103) & 1; /*0x4ef1d6*/
LABEL_184:
                if ( v19 ) /*0x4ef1dc*/
                {
                  if ( !v105 ) /*0x4ef1e0*/
                    BYTE2(v6[4 * v48 + 169]) = sub_4EB510(v10); /*0x4ef1ee*/
                }
                else if ( !v105 ) /*0x4ef1fc*/
                {
                  BYTE2(v6[4 * v48 + 169]) = 0; /*0x4ef202*/
                }
                goto LABEL_199; /*0x4ef1f5*/
              }
              *(_DWORD *)(v10 + 40) = 8 * v56; /*0x4eec37*/
              *(_DWORD *)(v10 + 36) = v56 + 1; /*0x4eec3e*/
            }
            v59 = (*(int *)(v10 + 40) >> 3) - v50; /*0x4eec4e*/
            if ( v59 < 0 ) /*0x4eec51*/
              v60 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4eec67*/
            else
              v60 = *(_BYTE *)(v59 + *(_QWORD *)(v10 + 16)); /*0x4eec5a*/
            ++*(_DWORD *)(v10 + 40); /*0x4eec73*/
            if ( ((v60 >> v55) & 1) != 0 ) /*0x4eec7f*/
              goto LABEL_95; /*0x4eec7f*/
            v6[v47 + 151] = 0; /*0x4eec86*/
            v61 = 2LL * v47; /*0x4eec8d*/
            *(_QWORD *)&v6[2 * v61 + 166] = 0; /*0x4eec90*/
            *(_QWORD *)&v6[2 * v61 + 168] = 0; /*0x4eec98*/
            goto LABEL_199; /*0x4eeca0*/
          }
          *(_DWORD *)(v10 + 40) = 8 * v51; /*0x4eeb8d*/
          *(_DWORD *)(v10 + 36) = v51 + 1; /*0x4eeb94*/
        }
        v50 = *(_DWORD *)(v10 + 28); /*0x4eeb9f*/
        v52 = (*(int *)(v10 + 40) >> 3) - v50; /*0x4eeba8*/
        if ( v52 < 0 ) /*0x4eebab*/
          v53 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4eebc1*/
        else
          v53 = *(_BYTE *)(v52 + *(_QWORD *)(v10 + 16)); /*0x4eebb4*/
        v54 = *(_DWORD *)(v10 + 40) + 1; /*0x4eebc5*/
        *(_DWORD *)(v10 + 40) = v54; /*0x4eebcf*/
        if ( ((v53 >> v49) & 1) != 0 ) /*0x4eebd8*/
          goto LABEL_91; /*0x4eebd8*/
        if ( v47 <= 0 || (v47 & 3) != 0 ) /*0x4ef214*/
          goto LABEL_199; /*0x4ef214*/
        v108 = v54 & 7; /*0x4ef216*/
        if ( !v108 ) /*0x4ef21a*/
        {
          v109 = *(_DWORD *)(v10 + 36); /*0x4ef220*/
          if ( v109 >= v50 + *(_DWORD *)(v10 + 32) ) /*0x4ef229*/
          {
            *(_DWORD *)v10 = 1; /*0x4ef22b*/
            goto LABEL_199; /*0x4ef232*/
          }
          *(_DWORD *)(v10 + 40) = 8 * v109; /*0x4ef23b*/
          *(_DWORD *)(v10 + 36) = v109 + 1; /*0x4ef242*/
        }
        v110 = (*(int *)(v10 + 40) >> 3) - v50; /*0x4ef252*/
        if ( v110 < 0 ) /*0x4ef255*/
          v111 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4ef26b*/
        else
          v111 = *(_BYTE *)(v110 + *(_QWORD *)(v10 + 16)); /*0x4ef25e*/
        ++*(_DWORD *)(v10 + 40); /*0x4ef277*/
        if ( ((v111 >> v108) & 1) == 0 ) /*0x4ef283*/
        {
LABEL_200:
          v22 = v157; /*0x4ef293*/
          goto LABEL_201; /*0x4ef293*/
        }
LABEL_199:
        ++v47; /*0x4ef285*/
        ++v48; /*0x4ef287*/
        if ( v47 >= 15 ) /*0x4ef28d*/
          goto LABEL_200; /*0x4ef28d*/
      }
    }
    *(_DWORD *)(v10 + 40) = 8 * v44; /*0x4eeafd*/
    *(_DWORD *)(v10 + 36) = v44 + 1; /*0x4eeb04*/
  }
  v45 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28); /*0x4eeb14*/
  if ( v45 < 0 ) /*0x4eeb18*/
    v46 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4eeb2e*/
  else
    v46 = *(_BYTE *)(v45 + *(_QWORD *)(v10 + 16)); /*0x4eeb21*/
  ++*(_DWORD *)(v10 + 40); /*0x4eeb3a*/
  if ( ((v46 >> v43) & 1) != 0 ) /*0x4eeb46*/
    goto LABEL_82; /*0x4eeb46*/
  while ( 1 )
  {
LABEL_201:
    v112 = *(_DWORD *)(v10 + 40) & 7; /*0x4ef2a0*/
    if ( !v112 ) /*0x4ef2a8*/
    {
      v113 = *(_DWORD *)(v10 + 36); /*0x4ef2b2*/
      if ( v113 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) ) /*0x4ef2b8*/
      {
        *(_DWORD *)v10 = 1; /*0x4ef2ba*/
        goto LABEL_209; /*0x4ef2c1*/
      }
      *(_DWORD *)(v10 + 40) = 8 * v113; /*0x4ef2ca*/
      *(_DWORD *)(v10 + 36) = v113 + 1; /*0x4ef2d1*/
    }
    v114 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28); /*0x4ef2e1*/
    v115 = v114 < 0
         ? *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8))
         : *(_BYTE *)(v114 + *(_QWORD *)(v10 + 16));
    v116 = *(_DWORD *)(v10 + 40) + 1; /*0x4ef2ff*/
    *(_DWORD *)(v10 + 40) = v116; /*0x4ef309*/
    if ( ((v115 >> v112) & 1) == 0 ) /*0x4ef312*/
      break; /*0x4ef312*/
LABEL_209:
    v117 = 3LL * (int)MSG_ReadBits(v10, 4); /*0x4ef318*/
    v118 = *(_DWORD *)(v10 + 40) & 7; /*0x4ef330*/
    if ( !v118 ) /*0x4ef334*/
    {
      v119 = *(_DWORD *)(v10 + 36); /*0x4ef33e*/
      if ( v119 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) ) /*0x4ef344*/
      {
        *(_DWORD *)v10 = 1; /*0x4ef346*/
LABEL_217:
        v122 = MSG_ReadBits(v10, 1); /*0x4ef3a1*/
        v6[v117 + 239] = 0; /*0x4ef3b0*/
        LOBYTE(v6[v117 + 240]) = v122 + 1; /*0x4ef3b8*/
        BYTE1(v6[v117 + 240]) = 1; /*0x4ef3bf*/
        goto LABEL_227; /*0x4ef3c7*/
      }
      *(_DWORD *)(v10 + 40) = 8 * v119; /*0x4ef356*/
      *(_DWORD *)(v10 + 36) = v119 + 1; /*0x4ef35d*/
    }
    v120 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28); /*0x4ef36d*/
    if ( v120 < 0 ) /*0x4ef371*/
      v121 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4ef387*/
    else
      v121 = *(_BYTE *)(v120 + *(_QWORD *)(v10 + 16)); /*0x4ef37a*/
    ++*(_DWORD *)(v10 + 40); /*0x4ef393*/
    if ( ((v121 >> v118) & 1) != 0 ) /*0x4ef39f*/
      goto LABEL_217; /*0x4ef39f*/
    v123 = MSG_ReadBits(v10, 27); /*0x4ef3dd*/
    v124 = *(_DWORD *)(v10 + 40) & 7; /*0x4ef3e0*/
    if ( v124 ) /*0x4ef3e4*/
      goto LABEL_222; /*0x4ef3e4*/
    v125 = *(_DWORD *)(v10 + 36); /*0x4ef3ee*/
    if ( v125 < *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) ) /*0x4ef3f4*/
    {
      *(_DWORD *)(v10 + 40) = 8 * v125; /*0x4ef409*/
      *(_DWORD *)(v10 + 36) = v125 + 1; /*0x4ef410*/
LABEL_222:
      v127 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28); /*0x4ef414*/
      if ( v127 < 0 ) /*0x4ef424*/
        v128 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4ef43a*/
      else
        v128 = *(_BYTE *)(v127 + *(_QWORD *)(v10 + 16)); /*0x4ef42d*/
      ++*(_DWORD *)(v10 + 40); /*0x4ef446*/
      v126 = (v128 >> v124) & 1; /*0x4ef44f*/
      goto LABEL_226; /*0x4ef44f*/
    }
    *(_DWORD *)v10 = 1; /*0x4ef3f6*/
    v126 = -1; /*0x4ef3fd*/
LABEL_226:
    v6[v117 + 239] = v123; /*0x4ef452*/
    LOBYTE(v6[v117 + 240]) = 0; /*0x4ef45c*/
    BYTE1(v6[v117 + 240]) = v126 != 0; /*0x4ef467*/
LABEL_227:
    v6[v117 + 241] = MSG_ReadBits(v10, 10); /*0x4ef46e*/
  }
  v129 = v116 & 7; /*0x4ef487*/
  if ( !v129 ) /*0x4ef48b*/
  {
    v130 = *(_DWORD *)(v10 + 36); /*0x4ef495*/
    if ( v130 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) ) /*0x4ef49b*/
    {
      *(_DWORD *)v10 = 1; /*0x4ef49d*/
      goto LABEL_236; /*0x4ef4a4*/
    }
    *(_DWORD *)(v10 + 40) = 8 * v130; /*0x4ef4ad*/
    *(_DWORD *)(v10 + 36) = v130 + 1; /*0x4ef4b4*/
  }
  v131 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28); /*0x4ef4c4*/
  if ( v131 < 0 ) /*0x4ef4c8*/
    v132 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4ef4de*/
  else
    v132 = *(_BYTE *)(v131 + *(_QWORD *)(v10 + 16)); /*0x4ef4d1*/
  ++*(_DWORD *)(v10 + 40); /*0x4ef4ea*/
  if ( ((v132 >> v129) & 1) != 0 ) /*0x4ef4f6*/
  {
LABEL_236:
    v133 = v6 + 1945; /*0x4ef4fc*/
    v134 = v22 + 7780; /*0x4ef50e*/
    v135 = 36; /*0x4ef518*/
    v136 = (char *)((char *)v6 - v22); /*0x4ef51d*/
    v137 = *((_DWORD *)off_12D4BA8 + 18); /*0x4ef520*/
    v138 = off_12D4BA8[8]; /*0x4ef524*/
    do /*0x4ef573*/
    {
      LOBYTE(v151) = 0; /*0x4ef53d*/
      *v133 = MSG_ReadBits(v10, 3); /*0x4ef560*/
      ((void (__fastcall *)(__int64, _QWORD, _DWORD *, char *, int, void *, int, int))sub_4EDAF0)( /*0x4ef562*/
        v10,
        v156,
        v134,
        (char *)v134 + (_QWORD)v136,
        v137,
        v138,
        1,
        v151);
      v134 += 9; /*0x4ef567*/
      v133 += 9; /*0x4ef56b*/
      --v135; /*0x4ef56f*/
    }
    while ( v135 ); /*0x4ef573*/
    v6 = v161; /*0x4ef575*/
  }
  v139 = *(_DWORD *)(v10 + 40) & 7; /*0x4ef57e*/
  if ( !v139 ) /*0x4ef582*/
  {
    v140 = *(_DWORD *)(v10 + 36); /*0x4ef58c*/
    if ( v140 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) ) /*0x4ef592*/
    {
      *(_DWORD *)v10 = 1; /*0x4ef594*/
      goto LABEL_247; /*0x4ef59b*/
    }
    *(_DWORD *)(v10 + 40) = 8 * v140; /*0x4ef5a4*/
    *(_DWORD *)(v10 + 36) = v140 + 1; /*0x4ef5ab*/
  }
  v141 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28); /*0x4ef5bb*/
  if ( v141 < 0 ) /*0x4ef5bf*/
    v142 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8)); /*0x4ef5d5*/
  else
    v142 = *(_BYTE *)(v141 + *(_QWORD *)(v10 + 16)); /*0x4ef5c8*/
  ++*(_DWORD *)(v10 + 40); /*0x4ef5e1*/
  if ( ((v142 >> v139) & 1) != 0 ) /*0x4ef5ed*/
  {
LABEL_247:
    v143 = v157; /*0x4ef5ef*/
    ((void (__fastcall *)(_DWORD, int, int, int, int))sub_4EDD10)(v10, (_DWORD)v157 + 14848, (_DWORD)v6 + 14848, 15, 4); /*0x4ef619*/
    ((void (__fastcall *)(_DWORD, int, int, int, int))sub_4EDD10)(v10, (_DWORD)v157 + 9088, (_DWORD)v6 + 9088, 30, 5); /*0x4ef643*/
  }
  else
  {
    v143 = v157; /*0x4ef64a*/
  }
  v144 = (__int64)(v6 + 4432); /*0x4ef654*/
  v145 = sub_5A47B0(); /*0x4ef65b*/
  v146 = (__int64)(v143 + 17728); /*0x4ef65d*/
  v147 = sub_5A47A0(); /*0x4ef669*/
  v148 = sub_5A4790(); /*0x4ef66b*/
  return ((__int64 (__fastcall *)(_DWORD, int, int, __int64, __int64, int))sub_4EE380)( /*0x4ef6ba*/
           v10,
           v148,
           v147,
           v146,
           v144,
           v145);
}