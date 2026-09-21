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

  if ( v8 > -1 )
  {
    while ( 1 )
    {
      v12 = v9 + 1;
      v9 += MSG_ReadNumFieldsSkipped(v10, 4, (unsigned int)(v8 - v9));
      if ( v12 < v9 )
        break;
LABEL_12:
      v16 = !v155 && (*(_BYTE *)(v11 + 8LL * v9 + 6) & 4) != 0;
      v17 = a6 && v16;
      LOBYTE(v150) = v17;
      MSG_ReadDeltaField(v10, v156, v7, (__int64)v6, (unsigned __int16 *)(v11 + 8LL * v9), 0, v150);
      if ( v9 >= v8 )
      {
        v158 = v9;
        goto LABEL_22;
      }
    }
    v13 = v11 + 8LL * v12;
    v14 = v152;
    v15 = (_BYTE *)(v13 + 6);
    while ( v14 || (*(_WORD *)v15 & 0x1F0) == 0 )
    {
      if ( (*v15 & 2) == 0 )
      {
        MSG_CopyFieldOver(v11, (__int64)v157, (__int64)v6, v12);
        goto LABEL_9;
      }
LABEL_10:
      ++v12;
      v13 += 8;
      v15 += 8;
      if ( v12 >= v9 )
      {
        v10 = v160;
        v8 = v159;
        v7 = (__int64)v157;
        goto LABEL_12;
      }
    }
    ((void (__fastcall *)(_QWORD, __int64, char *))sub_4F0B90)(v153, v13, (char *)v6 + *((unsigned __int16 *)v15 - 3));
LABEL_9:
    v14 = v152;
    goto LABEL_10;
  }
LABEL_22:
  v18 = v9 + 1;
  v19 = v152;
  v20 = v9 + 1;
  if ( v20 < v154 )
  {
    do
    {
      if ( v152 || (*(_WORD *)(v11 + 8 * v20 + 6) & 0x1F0) == 0 )
        MSG_CopyFieldOver(v11, (__int64)v157, (__int64)v6, v18);
      else
        ((void (__fastcall *)(_QWORD, __int64, char *))sub_4F0B90)(
          v153,
          v11 + 8LL * v18,
          (char *)v6 + *(unsigned __int16 *)(v11 + 8 * v20));
      ++v18;
      ++v20;
    }
    while ( v20 < v154 );
    v10 = v160;
    v9 = v158;
  }
  v21 = v9;
  if ( v9 > 0 )
  {
    do
    {
      if ( (*(_BYTE *)(v11 + 6) & 2) != 0 )
      {
        LOBYTE(v150) = 0;
        MSG_ReadDeltaField(v10, v156, (__int64)v157, (__int64)v6, (unsigned __int16 *)v11, 0, v150);
      }
      v11 += 8;
      --v21;
    }
    while ( v21 );
    v19 = v152;
  }
  if ( v155 )
  {
    v22 = v157;
    if ( !(unsigned int)CL_GetPredictedPlayerInformationForServerTime(qword_2EC84F0, v6[19], v6) )
    {
      v6[30] = *((_DWORD *)v157 + 30);
      v6[31] = *((_DWORD *)v157 + 31);
      v6[32] = *((_DWORD *)v157 + 32);
      v6[33] = *((_DWORD *)v157 + 33);
      v6[34] = *((_DWORD *)v157 + 34);
      v6[35] = *((_DWORD *)v157 + 35);
      v6[29] = *((_DWORD *)v157 + 29);
      v6[50] = *((_DWORD *)v157 + 50);
    }
  }
  else
  {
    v22 = v157;
  }
  v23 = *(_DWORD *)(v10 + 40) & 7;
  if ( !v23 )
  {
    v24 = *(_DWORD *)(v10 + 36);
    if ( v24 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) )
    {
      *(_DWORD *)v10 = 1;
LABEL_46:
      v27 = MSG_ReadBits(v10, 4);
      if ( (v27 & 1) != 0 )
        v6[87] = MSG_ReadValue32_ByteCursor(v10);
      if ( (v27 & 2) != 0 )
        v6[88] = MSG_ReadValue32_ByteCursor(v10);
      if ( (v27 & 4) != 0 )
        v6[89] = MSG_ReadValue32_ByteCursor(v10);
      if ( (v27 & 8) != 0 )
        v6[90] = MSG_ReadByte(v10);
      goto LABEL_54;
    }
    *(_DWORD *)(v10 + 40) = 8 * v24;
    *(_DWORD *)(v10 + 36) = v24 + 1;
  }
  v25 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
  if ( v25 < 0 )
    v26 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
  else
    v26 = *(_BYTE *)(v25 + *(_QWORD *)(v10 + 16));
  ++*(_DWORD *)(v10 + 40);
  if ( ((v26 >> v23) & 1) != 0 )
    goto LABEL_46;
LABEL_54:
  v28 = *(_DWORD *)(v10 + 40) & 7;
  if ( !v28 )
  {
    v29 = *(_DWORD *)(v10 + 36);
    if ( v29 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) )
    {
      *(_DWORD *)v10 = 1;
LABEL_62:
      v33 = 3LL * (int)MSG_ReadBits(v10, 4);
      v34 = MSG_ReadBits(v10, 1);
      v6[2 * v33 + 284] = MSG_ReadBits(v10, 27);
      v35 = v34 != 0;
      v36 = 2 * (v33 + 143);
      LOBYTE(v6[v36 - 1]) = v35;
      v37 = &v6[v36];
      v38 = 2;
      while ( 1 )
      {
        v39 = *(_DWORD *)(v10 + 40) & 7;
        if ( v39 )
          goto LABEL_67;
        v40 = *(_DWORD *)(v10 + 36);
        if ( v40 < *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) )
          break;
        *(_DWORD *)v10 = 1;
LABEL_71:
        *v37 = MSG_ReadBits(v10, 8);
LABEL_72:
        ++v37;
        if ( !--v38 )
          goto LABEL_54;
      }
      *(_DWORD *)(v10 + 40) = 8 * v40;
      *(_DWORD *)(v10 + 36) = v40 + 1;
LABEL_67:
      v41 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
      if ( v41 < 0 )
        v42 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
      else
        v42 = *(_BYTE *)(v41 + *(_QWORD *)(v10 + 16));
      ++*(_DWORD *)(v10 + 40);
      if ( ((v42 >> v39) & 1) == 0 )
        goto LABEL_72;
      goto LABEL_71;
    }
    *(_DWORD *)(v10 + 40) = 8 * v29;
    *(_DWORD *)(v10 + 36) = v29 + 1;
  }
  v30 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
  if ( v30 < 0 )
    v31 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
  else
    v31 = *(_BYTE *)(v30 + *(_QWORD *)(v10 + 16));
  v32 = *(_DWORD *)(v10 + 40) + 1;
  *(_DWORD *)(v10 + 40) = v32;
  if ( ((v31 >> v28) & 1) != 0 )
    goto LABEL_62;
  v43 = v32 & 7;
  if ( !v43 )
  {
    v44 = *(_DWORD *)(v10 + 36);
    if ( v44 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) )
    {
      *(_DWORD *)v10 = 1;
LABEL_82:
      v47 = 0;
      v48 = 0;
      while ( 1 )
      {
        v49 = *(_DWORD *)(v10 + 40) & 7;
        if ( !v49 )
        {
          v50 = *(_DWORD *)(v10 + 28);
          v51 = *(_DWORD *)(v10 + 36);
          if ( v51 >= v50 + *(_DWORD *)(v10 + 32) )
          {
            *(_DWORD *)v10 = 1;
LABEL_91:
            if ( v19 )
              goto LABEL_95;
            v55 = *(_DWORD *)(v10 + 40) & 7;
            if ( !v55 )
            {
              v56 = *(_DWORD *)(v10 + 36);
              if ( v56 >= v50 + *(_DWORD *)(v10 + 32) )
              {
                *(_DWORD *)v10 = 1;
LABEL_95:
                v57 = *(_DWORD *)(v10 + 40) & 7;
                if ( !v57 )
                {
                  v58 = *(_DWORD *)(v10 + 36);
                  if ( v58 >= v50 + *(_DWORD *)(v10 + 32) )
                  {
                    *(_DWORD *)v10 = 1;
                    goto LABEL_109;
                  }
                  *(_DWORD *)(v10 + 40) = 8 * v58;
                  *(_DWORD *)(v10 + 36) = v58 + 1;
                }
                v62 = (*(int *)(v10 + 40) >> 3) - v50;
                if ( v62 < 0 )
                  v63 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
                else
                  v63 = *(_BYTE *)(v62 + *(_QWORD *)(v10 + 16));
                ++*(_DWORD *)(v10 + 40);
                if ( ((v63 >> v57) & 1) != 0 )
LABEL_109:
                  v6[v48 + 151] = MSG_ReadBits(v10, 27);
                v64 = *(_DWORD *)(v10 + 40) & 7;
                if ( !v64 )
                {
                  v65 = *(_DWORD *)(v10 + 36);
                  if ( v65 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) )
                  {
                    *(_DWORD *)v10 = 1;
                    v66 = -1;
                    goto LABEL_118;
                  }
                  *(_DWORD *)(v10 + 40) = 8 * v65;
                  *(_DWORD *)(v10 + 36) = v65 + 1;
                }
                v67 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
                if ( v67 < 0 )
                  v68 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
                else
                  v68 = *(_BYTE *)(v67 + *(_QWORD *)(v10 + 16));
                ++*(_DWORD *)(v10 + 40);
                v66 = (v68 >> v64) & 1;
LABEL_118:
                LOBYTE(v6[4 * v48 + 166]) = v66 > 0;
                v69 = *(_DWORD *)(v10 + 40) & 7;
                if ( !v69 )
                {
                  v70 = *(_DWORD *)(v10 + 36);
                  if ( v70 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) )
                  {
                    *(_DWORD *)v10 = 1;
                    v71 = -1;
                    goto LABEL_126;
                  }
                  *(_DWORD *)(v10 + 40) = 8 * v70;
                  *(_DWORD *)(v10 + 36) = v70 + 1;
                }
                v72 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
                if ( v72 < 0 )
                  v73 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
                else
                  v73 = *(_BYTE *)(v72 + *(_QWORD *)(v10 + 16));
                ++*(_DWORD *)(v10 + 40);
                v71 = (v73 >> v69) & 1;
LABEL_126:
                BYTE1(v6[4 * v48 + 166]) = v71 > 0;
                v74 = *(_DWORD *)(v10 + 40) & 7;
                if ( !v74 )
                {
                  v75 = *(_DWORD *)(v10 + 36);
                  if ( v75 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) )
                  {
                    *(_DWORD *)v10 = 1;
                    v76 = -1;
                    goto LABEL_134;
                  }
                  *(_DWORD *)(v10 + 40) = 8 * v75;
                  *(_DWORD *)(v10 + 36) = v75 + 1;
                }
                v77 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
                if ( v77 < 0 )
                  v78 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
                else
                  v78 = *(_BYTE *)(v77 + *(_QWORD *)(v10 + 16));
                ++*(_DWORD *)(v10 + 40);
                v76 = (v78 >> v74) & 1;
LABEL_134:
                BYTE2(v6[4 * v48 + 166]) = v76 > 0;
                if ( v19 )
                {
                  v79 = *(_DWORD *)(v10 + 40) & 7;
                  if ( !v79 )
                  {
                    v80 = *(_DWORD *)(v10 + 36);
                    if ( v80 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) )
                    {
                      *(_DWORD *)v10 = 1;
                      v81 = -1;
                      goto LABEL_143;
                    }
                    *(_DWORD *)(v10 + 40) = 8 * v80;
                    *(_DWORD *)(v10 + 36) = v80 + 1;
                  }
                  v82 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
                  if ( v82 < 0 )
                    v83 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
                  else
                    v83 = *(_BYTE *)(v82 + *(_QWORD *)(v10 + 16));
                  ++*(_DWORD *)(v10 + 40);
                  v81 = (v83 >> v79) & 1;
LABEL_143:
                  HIBYTE(v6[4 * v48 + 166]) = v81 > 0;
                  v84 = *(_DWORD *)(v10 + 40) & 7;
                  if ( !v84 )
                  {
                    v85 = *(_DWORD *)(v10 + 36);
                    if ( v85 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) )
                    {
                      *(_DWORD *)v10 = 1;
                      LOBYTE(v6[4 * v48 + 167]) = 0;
                      goto LABEL_152;
                    }
                    *(_DWORD *)(v10 + 40) = 8 * v85;
                    *(_DWORD *)(v10 + 36) = v85 + 1;
                  }
                  v86 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
                  if ( v86 < 0 )
                    v87 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
                  else
                    v87 = *(_BYTE *)(v86 + *(_QWORD *)(v10 + 16));
                  ++*(_DWORD *)(v10 + 40);
                  LOBYTE(v6[4 * v48 + 167]) = ((v87 >> v84) & 1) != 0;
                }
                else
                {
                  *(_WORD *)((char *)&v6[4 * v48 + 166] + 3) = 0;
                }
LABEL_152:
                v88 = *(_DWORD *)(v10 + 40) & 7;
                if ( !v88 )
                {
                  v89 = *(_DWORD *)(v10 + 36);
                  if ( v89 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) )
                  {
                    *(_DWORD *)v10 = 1;
                    v90 = -1;
                    goto LABEL_160;
                  }
                  *(_DWORD *)(v10 + 40) = 8 * v89;
                  *(_DWORD *)(v10 + 36) = v89 + 1;
                }
                v91 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
                if ( v91 < 0 )
                  v92 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
                else
                  v92 = *(_BYTE *)(v91 + *(_QWORD *)(v10 + 16));
                ++*(_DWORD *)(v10 + 40);
                v90 = (v92 >> v88) & 1;
LABEL_160:
                BYTE1(v6[4 * v48 + 167]) = v90 > 0;
                v6[4 * v48 + 168] = MSG_ReadBits(v10, 2);
                v93 = *(_DWORD *)(v10 + 40) & 7;
                if ( !v93 )
                {
                  v94 = *(_DWORD *)(v10 + 36);
                  if ( v94 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) )
                  {
                    *(_DWORD *)v10 = 1;
                    v95 = -1;
                    goto LABEL_168;
                  }
                  *(_DWORD *)(v10 + 40) = 8 * v94;
                  *(_DWORD *)(v10 + 36) = v94 + 1;
                }
                v96 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
                if ( v96 < 0 )
                  v97 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
                else
                  v97 = *(_BYTE *)(v96 + *(_QWORD *)(v10 + 16));
                ++*(_DWORD *)(v10 + 40);
                v95 = (v97 >> v93) & 1;
LABEL_168:
                LOBYTE(v6[4 * v48 + 169]) = v95 > 0;
                v98 = *(_DWORD *)(v10 + 40) & 7;
                if ( !v98 )
                {
                  v99 = *(_DWORD *)(v10 + 36);
                  if ( v99 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) )
                  {
                    *(_DWORD *)v10 = 1;
                    v100 = -1;
                    goto LABEL_176;
                  }
                  *(_DWORD *)(v10 + 40) = 8 * v99;
                  *(_DWORD *)(v10 + 36) = v99 + 1;
                }
                v101 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
                if ( v101 < 0 )
                  v102 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
                else
                  v102 = *(_BYTE *)(v101 + *(_QWORD *)(v10 + 16));
                ++*(_DWORD *)(v10 + 40);
                v100 = (v102 >> v98) & 1;
LABEL_176:
                BYTE1(v6[4 * v48 + 169]) = v100 > 0;
                BYTE2(v6[4 * v48 + 169]) = v153 + 1;
                v103 = *(_DWORD *)(v10 + 40) & 7;
                if ( !v103 )
                {
                  v104 = *(_DWORD *)(v10 + 36);
                  if ( v104 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) )
                  {
                    *(_DWORD *)v10 = 1;
                    v105 = -1;
                    goto LABEL_184;
                  }
                  *(_DWORD *)(v10 + 40) = 8 * v104;
                  *(_DWORD *)(v10 + 36) = v104 + 1;
                }
                v106 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
                if ( v106 < 0 )
                  v107 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
                else
                  v107 = *(_BYTE *)(v106 + *(_QWORD *)(v10 + 16));
                ++*(_DWORD *)(v10 + 40);
                v105 = (v107 >> v103) & 1;
LABEL_184:
                if ( v19 )
                {
                  if ( !v105 )
                    BYTE2(v6[4 * v48 + 169]) = MSG_ReadByte(v10);
                }
                else if ( !v105 )
                {
                  BYTE2(v6[4 * v48 + 169]) = 0;
                }
                goto LABEL_199;
              }
              *(_DWORD *)(v10 + 40) = 8 * v56;
              *(_DWORD *)(v10 + 36) = v56 + 1;
            }
            v59 = (*(int *)(v10 + 40) >> 3) - v50;
            if ( v59 < 0 )
              v60 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
            else
              v60 = *(_BYTE *)(v59 + *(_QWORD *)(v10 + 16));
            ++*(_DWORD *)(v10 + 40);
            if ( ((v60 >> v55) & 1) != 0 )
              goto LABEL_95;
            v6[v47 + 151] = 0;
            v61 = 2LL * v47;
            *(_QWORD *)&v6[2 * v61 + 166] = 0;
            *(_QWORD *)&v6[2 * v61 + 168] = 0;
            goto LABEL_199;
          }
          *(_DWORD *)(v10 + 40) = 8 * v51;
          *(_DWORD *)(v10 + 36) = v51 + 1;
        }
        v50 = *(_DWORD *)(v10 + 28);
        v52 = (*(int *)(v10 + 40) >> 3) - v50;
        if ( v52 < 0 )
          v53 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
        else
          v53 = *(_BYTE *)(v52 + *(_QWORD *)(v10 + 16));
        v54 = *(_DWORD *)(v10 + 40) + 1;
        *(_DWORD *)(v10 + 40) = v54;
        if ( ((v53 >> v49) & 1) != 0 )
          goto LABEL_91;
        if ( v47 <= 0 || (v47 & 3) != 0 )
          goto LABEL_199;
        v108 = v54 & 7;
        if ( !v108 )
        {
          v109 = *(_DWORD *)(v10 + 36);
          if ( v109 >= v50 + *(_DWORD *)(v10 + 32) )
          {
            *(_DWORD *)v10 = 1;
            goto LABEL_199;
          }
          *(_DWORD *)(v10 + 40) = 8 * v109;
          *(_DWORD *)(v10 + 36) = v109 + 1;
        }
        v110 = (*(int *)(v10 + 40) >> 3) - v50;
        if ( v110 < 0 )
          v111 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
        else
          v111 = *(_BYTE *)(v110 + *(_QWORD *)(v10 + 16));
        ++*(_DWORD *)(v10 + 40);
        if ( ((v111 >> v108) & 1) == 0 )
        {
LABEL_200:
          v22 = v157;
          goto LABEL_201;
        }
LABEL_199:
        ++v47;
        ++v48;
        if ( v47 >= 15 )
          goto LABEL_200;
      }
    }
    *(_DWORD *)(v10 + 40) = 8 * v44;
    *(_DWORD *)(v10 + 36) = v44 + 1;
  }
  v45 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
  if ( v45 < 0 )
    v46 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
  else
    v46 = *(_BYTE *)(v45 + *(_QWORD *)(v10 + 16));
  ++*(_DWORD *)(v10 + 40);
  if ( ((v46 >> v43) & 1) != 0 )
    goto LABEL_82;
  while ( 1 )
  {
LABEL_201:
    v112 = *(_DWORD *)(v10 + 40) & 7;
    if ( !v112 )
    {
      v113 = *(_DWORD *)(v10 + 36);
      if ( v113 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) )
      {
        *(_DWORD *)v10 = 1;
        goto LABEL_209;
      }
      *(_DWORD *)(v10 + 40) = 8 * v113;
      *(_DWORD *)(v10 + 36) = v113 + 1;
    }
    v114 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
    v115 = v114 < 0
         ? *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8))
         : *(_BYTE *)(v114 + *(_QWORD *)(v10 + 16));
    v116 = *(_DWORD *)(v10 + 40) + 1;
    *(_DWORD *)(v10 + 40) = v116;
    if ( ((v115 >> v112) & 1) == 0 )
      break;
LABEL_209:
    v117 = 3LL * (int)MSG_ReadBits(v10, 4);
    v118 = *(_DWORD *)(v10 + 40) & 7;
    if ( !v118 )
    {
      v119 = *(_DWORD *)(v10 + 36);
      if ( v119 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) )
      {
        *(_DWORD *)v10 = 1;
LABEL_217:
        v122 = MSG_ReadBits(v10, 1);
        v6[v117 + 239] = 0;
        LOBYTE(v6[v117 + 240]) = v122 + 1;
        BYTE1(v6[v117 + 240]) = 1;
        goto LABEL_227;
      }
      *(_DWORD *)(v10 + 40) = 8 * v119;
      *(_DWORD *)(v10 + 36) = v119 + 1;
    }
    v120 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
    if ( v120 < 0 )
      v121 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
    else
      v121 = *(_BYTE *)(v120 + *(_QWORD *)(v10 + 16));
    ++*(_DWORD *)(v10 + 40);
    if ( ((v121 >> v118) & 1) != 0 )
      goto LABEL_217;
    v123 = MSG_ReadBits(v10, 27);
    v124 = *(_DWORD *)(v10 + 40) & 7;
    if ( v124 )
      goto LABEL_222;
    v125 = *(_DWORD *)(v10 + 36);
    if ( v125 < *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) )
    {
      *(_DWORD *)(v10 + 40) = 8 * v125;
      *(_DWORD *)(v10 + 36) = v125 + 1;
LABEL_222:
      v127 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
      if ( v127 < 0 )
        v128 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
      else
        v128 = *(_BYTE *)(v127 + *(_QWORD *)(v10 + 16));
      ++*(_DWORD *)(v10 + 40);
      v126 = (v128 >> v124) & 1;
      goto LABEL_226;
    }
    *(_DWORD *)v10 = 1;
    v126 = -1;
LABEL_226:
    v6[v117 + 239] = v123;
    LOBYTE(v6[v117 + 240]) = 0;
    BYTE1(v6[v117 + 240]) = v126 != 0;
LABEL_227:
    v6[v117 + 241] = MSG_ReadBits(v10, 10);
  }
  v129 = v116 & 7;
  if ( !v129 )
  {
    v130 = *(_DWORD *)(v10 + 36);
    if ( v130 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) )
    {
      *(_DWORD *)v10 = 1;
      goto LABEL_236;
    }
    *(_DWORD *)(v10 + 40) = 8 * v130;
    *(_DWORD *)(v10 + 36) = v130 + 1;
  }
  v131 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
  if ( v131 < 0 )
    v132 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
  else
    v132 = *(_BYTE *)(v131 + *(_QWORD *)(v10 + 16));
  ++*(_DWORD *)(v10 + 40);
  if ( ((v132 >> v129) & 1) != 0 )
  {
LABEL_236:
    v133 = v6 + 1945;
    v134 = v22 + 7780;
    v135 = 36;
    v136 = (char *)((char *)v6 - v22);
    v137 = *((_DWORD *)off_12D4BA8 + 18);
    v138 = off_12D4BA8[8];
    do
    {
      LOBYTE(v151) = 0;
      *v133 = MSG_ReadBits(v10, 3);
      ((void (__fastcall *)(__int64, _QWORD, _DWORD *, char *, int, void *, int, int))sub_4EDAF0)(
        v10,
        v156,
        v134,
        (char *)v134 + (_QWORD)v136,
        v137,
        v138,
        1,
        v151);
      v134 += 9;
      v133 += 9;
      --v135;
    }
    while ( v135 );
    v6 = v161;
  }
  v139 = *(_DWORD *)(v10 + 40) & 7;
  if ( !v139 )
  {
    v140 = *(_DWORD *)(v10 + 36);
    if ( v140 >= *(_DWORD *)(v10 + 28) + *(_DWORD *)(v10 + 32) )
    {
      *(_DWORD *)v10 = 1;
      goto LABEL_247;
    }
    *(_DWORD *)(v10 + 40) = 8 * v140;
    *(_DWORD *)(v10 + 36) = v140 + 1;
  }
  v141 = (*(int *)(v10 + 40) >> 3) - *(_DWORD *)(v10 + 28);
  if ( v141 < 0 )
    v142 = *(_BYTE *)((*(int *)(v10 + 40) >> 3) + *(_QWORD *)(v10 + 8));
  else
    v142 = *(_BYTE *)(v141 + *(_QWORD *)(v10 + 16));
  ++*(_DWORD *)(v10 + 40);
  if ( ((v142 >> v139) & 1) != 0 )
  {
LABEL_247:
    v143 = v157;
    ((void (__fastcall *)(_DWORD, int, int, int, int))sub_4EDD10)(v10, (_DWORD)v157 + 14848, (_DWORD)v6 + 14848, 15, 4);
    ((void (__fastcall *)(_DWORD, int, int, int, int))sub_4EDD10)(v10, (_DWORD)v157 + 9088, (_DWORD)v6 + 9088, 30, 5);
  }
  else
  {
    v143 = v157;
  }
  v144 = (__int64)(v6 + 4432);
  v145 = sub_5A47B0();
  v146 = (__int64)(v143 + 17728);
  v147 = sub_5A47A0();
  v148 = sub_5A4790();
  return ((__int64 (__fastcall *)(_DWORD, int, int, __int64, __int64, int))sub_4EE380)(
           v10,
           v148,
           v147,
           v146,
           v144,
           v145);
}
