void *__usercall CG_DeployServerCommand@<eax>(int a1@<eax>)
{
  int v1; // ecx
  int v2; // edx
  const char *v3; // eax
  const char *v4; // eax
  int v5; // edi
  int j; // ebx
  const char *v7; // edx
  int v9; // edi
  const char *v10; // ebx
  const char *v11; // eax
  const char *v12; // eax
  int v13; // eax
  int v14; // edx
  const char *v15; // edx
  const char *v16; // edx
  const char *v17; // edx
  int *v18; // ebx
  int *v19; // edx
  int *v20; // eax
  int v21; // edx
  const char *v22; // edx
  const char *v23; // ecx
  const char *v24; // ecx
  const char *v25; // ecx
  const char *v26; // ecx
  const char *v27; // ecx
  const char *v28; // ecx
  int v29; // edi
  const char *ConfigString; // eax
  const char *v31; // eax
  unsigned int v32; // eax
  const char *v33; // eax
  int v34; // edi
  const char *v35; // eax
  char v36; // bl
  int v37; // eax
  const char *v38; // eax
  int v39; // eax
  const char *v40; // eax
  int v41; // eax
  const char *v42; // eax
  int v43; // edi
  const char *v44; // eax
  int v45; // eax
  int v46; // esi
  int v47; // ebx
  int *v48; // edx
  int v49; // ecx
  int v50; // eax
  const char *v51; // eax
  const char *v52; // eax
  const char *v53; // eax
  unsigned int v54; // eax
  int v55; // ebx
  const char *v56; // eax
  __int16 v57; // di
  const char *v58; // edx
  int v59; // ebx
  const char *v60; // edx
  const char *v61; // edx
  const char *v62; // edx
  float v63; // xmm0_4
  float v64; // xmm0_4
  float v65; // xmm0_4
  const char *v66; // edx
  const char *v67; // edx
  const char *v68; // eax
  float v69; // xmm0_4
  float v70; // xmm0_4
  float v71; // xmm0_4
  const char *v72; // eax
  const char *v73; // eax
  char v74; // al
  char *v75; // edx
  int v76; // ecx
  const char *v77; // eax
  const char *v78; // eax
  char v79; // al
  int v80; // ecx
  const char *v81; // eax
  const char *v82; // eax
  const char *v83; // edx
  int v84; // ebx
  const char *v85; // eax
  float v86; // xmm0_4
  const char *v87; // eax
  unsigned int v88; // eax
  int v89; // ebx
  const char *v90; // eax
  const char *v91; // eax
  int v92; // eax
  const char *v93; // edx
  int v94; // ebx
  const char *v95; // eax
  int v96; // eax
  int v97; // eax
  int v98; // edx
  int v99; // eax
  int v100; // eax
  int v101; // edx
  int v102; // eax
  const char *v103; // edi
  _BYTE *v104; // eax
  char v105; // al
  const char *v106; // eax
  int *v107; // edi
  int v108; // edx
  int v109; // eax
  int v110; // edx
  int v111; // eax
  int v112; // edx
  int v113; // ecx
  int v114; // ebx
  int *i; // esi
  int v116; // edx
  int v117; // ecx
  int v118; // ebx
  int v119; // eax
  int v120; // edx
  int v121; // ecx
  int v122; // eax
  int v123; // edx
  int v124; // ebx
  const char *v125; // eax
  float v126; // xmm0_4
  int v127; // eax
  int v128; // edx
  int v129; // edi
  const char *v130; // edx
  const char *v131; // edx
  const char *v132; // edx
  const char *v133; // ebx
  float v134; // xmm0_4
  int v135; // eax
  float v136; // xmm0_4
  float v137; // xmm0_4
  const char *v138; // edx
  int v139; // edi
  const char *v140; // eax
  float v141; // xmm0_4
  int ShellshockParms; // eax
  int v143; // edx
  int v144; // ebx
  const char *v145; // eax
  float v146; // xmm0_4
  int v147; // eax
  const char *v148; // eax
  const char *v149; // eax
  const char *v150; // eax
  int v151; // [esp+0h] [ebp-2F8h]
  int v152; // [esp+0h] [ebp-2F8h]
  const char *v153; // [esp+4h] [ebp-2F4h]
  float v154; // [esp+Ch] [ebp-2ECh]
  int v155; // [esp+30h] [ebp-2C8h]
  int v156; // [esp+34h] [ebp-2C4h]
  float v157; // [esp+3Ch] [ebp-2BCh]
  float v158; // [esp+40h] [ebp-2B8h]
  float v159; // [esp+44h] [ebp-2B4h]
  float v160; // [esp+48h] [ebp-2B0h]
  double v162; // [esp+50h] [ebp-2A8h]
  double v163; // [esp+58h] [ebp-2A0h]
  double v164; // [esp+68h] [ebp-290h]
  double v165; // [esp+70h] [ebp-288h]
  int v166; // [esp+88h] [ebp-270h]
  int v167; // [esp+8Ch] [ebp-26Ch]
  double v168; // [esp+90h] [ebp-268h]
  double v169; // [esp+98h] [ebp-260h]
  double v170; // [esp+A0h] [ebp-258h]
  int v171; // [esp+B4h] [ebp-244h]
  bool v172; // [esp+CBh] [ebp-22Dh]
  int v173; // [esp+CCh] [ebp-22Ch]
  int v174; // [esp+D0h] [ebp-228h]
  int v175; // [esp+D4h] [ebp-224h]
  int v176; // [esp+DCh] [ebp-21Ch]
  int v177; // [esp+E0h] [ebp-218h]
  int v178; // [esp+E4h] [ebp-214h]
  int v179; // [esp+ECh] [ebp-20Ch]
  int v180; // [esp+F0h] [ebp-208h]
  int v181; // [esp+F4h] [ebp-204h]
  int v182; // [esp+F8h] [ebp-200h]
  int v183; // [esp+FCh] [ebp-1FCh]
  int v184; // [esp+100h] [ebp-1F8h]
  int v185; // [esp+104h] [ebp-1F4h]
  int v186; // [esp+108h] [ebp-1F0h]
  int v187; // [esp+10Ch] [ebp-1ECh]
  int v188; // [esp+110h] [ebp-1E8h]
  int v189; // [esp+114h] [ebp-1E4h]
  int v190; // [esp+118h] [ebp-1E0h]
  int v191; // [esp+11Ch] [ebp-1DCh]
  _DWORD v192[3]; // [esp+12Ch] [ebp-1CCh] BYREF
  _DWORD v193[3]; // [esp+138h] [ebp-1C0h] BYREF
  char v194[256]; // [esp+146h] [ebp-1B2h] BYREF
  char v195[150]; // [esp+246h] [ebp-B2h] BYREF

  v1 = cmd_args[0]; /*0x9a914*/
  v2 = cmd_args[cmd_args[0] + 17]; /*0x9a916*/
  v3 = ""; /*0x9a91a*/
  if ( v2 > 0 ) /*0x9a921*/
    v3 = *(const char **)cmd_args[cmd_args[0] + 25]; /*0x9a927*/
  if ( *v3 <= 0x76u )
  {
    switch ( (unsigned int)v3 )
    {
      case 0u:
        return &__stack_chk_guard;
      case 0x42u:
        CG_MapRestart(a1, 0); /*0x9b257*/
        return &__stack_chk_guard; /*0x9b25c*/
      case 0x43u:
        v53 = ""; /*0x9b1d6*/
        if ( v2 > 1 ) /*0x9b1dc*/
          v53 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9b1e2*/
        v54 = atoi(v53); /*0x9b1e8*/
        v55 = v54; /*0x9b1ed*/
        if ( !v54 || *(_DWORD *)(BG_GetWeaponDef(v54) + 324) ) /*0x9b1fb*/
          CG_SetEquippedOffHand(a1, v55); /*0x9b216*/
        return &__stack_chk_guard; /*0x9b21b*/
      case 0x44u:
        if ( v2 == 3 )
        {
          v144 = atoi(*(const char **)(cmd_args[cmd_args[0] + 25] + 4)); /*0x9c06b*/
          v145 = ""; /*0x9c06f*/
          if ( cmd_args[cmd_args[0] + 17] > 2 ) /*0x9c079*/
            v145 = *(const char **)(cmd_args[cmd_args[0] + 25] + 8); /*0x9c07f*/
          v146 = atof(v145); /*0x9c090*/
          v159 = floorf((float)(v146 * 1000.0) + 0.5); /*0x9c0b2*/
          v147 = 0; /*0x9c0c0*/
          if ( (int)v159 >= 0 ) /*0x9c0c4*/
            v147 = (int)v159; /*0x9c0c4*/
          SND_DeactivateEnvironmentEffects(v144, v147); /*0x9c0ce*/
        }
        else
        {
          Com_PrintError(
            14,
            "ERROR: CG_DeactivateReverbCmd called with %i args (should be 3)\n",
            cmd_args[cmd_args[0] + 17]);
        }
        return &__stack_chk_guard; /*0x9b241*/
      case 0x45u:
        if ( v2 == 4 )
        {
          v171 = atoi(*(const char **)(cmd_args[cmd_args[0] + 25] + 4)); /*0x9bfb5*/
          v138 = ""; /*0x9bfbd*/
          if ( cmd_args[cmd_args[0] + 17] > 2 ) /*0x9bfc7*/
            v138 = *(const char **)(cmd_args[cmd_args[0] + 25] + 8); /*0x9bfcd*/
          v139 = atoi(v138); /*0x9bfd8*/
          v140 = ""; /*0x9bfdc*/
          if ( cmd_args[cmd_args[0] + 17] > 3 ) /*0x9bfe6*/
            v140 = *(const char **)(cmd_args[cmd_args[0] + 25] + 12); /*0x9bfec*/
          v141 = atof(v140); /*0x9bffd*/
          v158 = floorf((float)(v141 * 1000.0) + 0.5); /*0x9c01f*/
          ShellshockParms = BG_GetShellshockParms(v139); /*0x9c030*/
          v143 = 0; /*0x9c035*/
          if ( (int)v158 >= 0 ) /*0x9c039*/
            v143 = (int)v158; /*0x9c039*/
          SND_SetChannelVolumes(v171, (const float *)(ShellshockParms + 324), v143); /*0x9c052*/
        }
        else
        {
          Com_PrintError(
            9,
            "ERROR: CG_SetChannelVolCmd called with %i args (should be 4)\n",
            cmd_args[cmd_args[0] + 17]);
        }
        return &__stack_chk_guard; /*0x9b1d1*/
      case 0x46u:
        if ( v2 == 3 )
        {
          v124 = atoi(*(const char **)(cmd_args[cmd_args[0] + 25] + 4)); /*0x9bdfe*/
          v125 = ""; /*0x9be02*/
          if ( cmd_args[cmd_args[0] + 17] > 2 ) /*0x9be0c*/
            v125 = *(const char **)(cmd_args[cmd_args[0] + 25] + 8); /*0x9be12*/
          v126 = atof(v125); /*0x9be23*/
          v157 = floorf((float)(v126 * 1000.0) + 0.5); /*0x9be45*/
          v127 = 0; /*0x9be53*/
          if ( (int)v157 >= 0 ) /*0x9be57*/
            v127 = (int)v157; /*0x9be57*/
          SND_DeactivateChannelVolumes(v124, v127); /*0x9be61*/
        }
        else
        {
          Com_PrintError(
            9,
            "ERROR: CG_DeactivateChannelVolCmd called with %i args (should be 3)\n",
            cmd_args[cmd_args[0] + 17]);
        }
        return &__stack_chk_guard; /*0x9b1ab*/
      case 0x47u:
        v52 = ""; /*0x9b162*/
        if ( v2 > 1 ) /*0x9b168*/
          v52 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9b16e*/
        *(_DWORD *)((char *)&loc_4F8B0 + (_DWORD)cgArray) = atoi(v52); /*0x9b17f*/
        return &__stack_chk_guard; /*0x9b185*/
      case 0x48u:
        v51 = ""; /*0x9b13a*/
        if ( v2 > 1 ) /*0x9b140*/
          v51 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9b146*/
        *(_DWORD *)((char *)&loc_4F8B4 + (_DWORD)cgArray) = atoi(v51); /*0x9b157*/
        return &__stack_chk_guard; /*0x9b15d*/
      case 0x49u:
        v42 = ""; /*0x9b08b*/
        if ( v2 > 2 ) /*0x9b093*/
          v42 = *(const char **)(cmd_args[cmd_args[0] + 25] + 8); /*0x9b099*/
        v43 = atoi(v42); /*0x9b0a4*/
        v44 = ""; /*0x9b0a8*/
        if ( cmd_args[cmd_args[0] + 17] > 1 ) /*0x9b0b2*/
          v44 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9b0b8*/
        v45 = atoi(v44); /*0x9b0be*/
        v46 = v45; /*0x9b0c3*/
        v47 = *(_DWORD *)((char *)&loc_4F8A8 + (_DWORD)cgArray); /*0x9b0cb*/
        if ( v47 <= 0 ) /*0x9b0d3*/
          goto LABEL_88; /*0x9b0d3*/
        v48 = cgArray; /*0x9b0d5*/
        v49 = 0; /*0x9b0d7*/
        if ( v45 == *(_DWORD *)&byte_10A1AA1[315] ) /*0x9b0df*/
        {
          *(_DWORD *)&byte_10A1AA1[319] = v43; /*0x9c1a1*/
          v49 = 0; /*0x9c1a7*/
          goto LABEL_216; /*0x9c1a9*/
        }
        do /*0x9b0fb*/
        {
          if ( ++v49 == v47 ) /*0x9b104*/
          {
LABEL_88:
            if ( !*(_DWORD *)&byte_10A1AA1[259] || *(_DWORD *)&byte_10A1AA1[259] + 10000 < dword_1098428 ) /*0x9b121*/
              UpdateScores(a1); /*0x9b130*/
            return &__stack_chk_guard; /*0x9b135*/
          }
          v50 = v48[81473]; /*0x9b0f0*/
          v48 += 10; /*0x9b0f6*/
        }
        while ( v46 != v50 ); /*0x9b0fb*/
        cgArray[10 * v49 + 81464] = v43; /*0x9ba83*/
        v107 = (int *)((char *)&loc_4F8D8 + (_DWORD)&cgArray[10 * v49]); /*0x9ba8a*/
        while ( 2 ) /*0x9baa6*/
        {
          v190 = v49 - 1; /*0x9baa6*/
          v108 = v107[5]; /*0x9baaf*/
          v176 = v108; /*0x9bab2*/
          v109 = *(v107 - 5); /*0x9bab8*/
          v177 = v109; /*0x9babb*/
          if ( v108 == v109 || v108 != 3 && v109 != 3 ) /*0x9bad1*/
          {
            v110 = v107[2]; /*0x9bad7*/
            v178 = v110; /*0x9bada*/
            v111 = *(v107 - 8); /*0x9bae0*/
            if ( v110 > v111 || v110 >= v111 && v107[4] < *(v107 - 6) ) /*0x9baf9*/
            {
              v112 = *v107; /*0x9baff*/
              v113 = *(v107 - 1); /*0x9bb01*/
              v114 = *(v107 - 2); /*0x9bb04*/
              v183 = *(v107 - 3); /*0x9bb0a*/
              v182 = *(v107 - 4); /*0x9bb13*/
              v181 = *(v107 - 6); /*0x9bb1c*/
              v180 = *(v107 - 7); /*0x9bb25*/
              v179 = *(v107 - 9); /*0x9bb2e*/
              *(v107 - 9) = v107[1]; /*0x9bb37*/
              *(v107 - 8) = v178; /*0x9bb40*/
              *(v107 - 7) = v107[3]; /*0x9bb46*/
              *(v107 - 6) = v107[4]; /*0x9bb4c*/
              *(v107 - 5) = v176; /*0x9bb55*/
              *(v107 - 4) = v107[6]; /*0x9bb5b*/
              *(v107 - 3) = v107[7]; /*0x9bb61*/
              *(v107 - 2) = v107[8]; /*0x9bb67*/
              *(v107 - 1) = v107[9]; /*0x9bb6d*/
              *v107 = v107[10]; /*0x9bb73*/
              v107[10] = v112; /*0x9bb75*/
              v107[9] = v113; /*0x9bb78*/
              v107[8] = v114; /*0x9bb7b*/
              v107[7] = v183; /*0x9bb84*/
              v107[6] = v182; /*0x9bb8d*/
              v107[5] = v177; /*0x9bb96*/
              v107[4] = v181; /*0x9bb9f*/
              v107[3] = v180; /*0x9bba8*/
              v107[2] = v111; /*0x9bbb1*/
              v107[1] = v179; /*0x9bbba*/
              v107 -= 10; /*0x9bbbd*/
              if ( v190 ) /*0x9bbc8*/
              {
                v49 = v190; /*0x9baa0*/
                continue; /*0x9baa0*/
              }
              v49 = 0; /*0x9bbce*/
            }
          }
          break;
        }
LABEL_216:
        if ( v49 >= *(_DWORD *)((char *)&loc_4F8A8 + (_DWORD)cgArray) - 1 ) /*0x9bbdf*/
          return &__stack_chk_guard; /*0x9bbdf*/
        v155 = v49 + 1; /*0x9bbe6*/
        for ( i = &cgArray[10 * v49 + 81482]; ; i += 10 ) /*0x9bbf5*/
        {
          v119 = *(i - 5); /*0x9bd06*/
          v173 = v119; /*0x9bd09*/
          v120 = *(i - 15); /*0x9bd0f*/
          v174 = v120; /*0x9bd12*/
          if ( v119 != v120 && (v119 == 3 || v120 == 3) ) /*0x9bd28*/
            break; /*0x9bd28*/
          v121 = *(i - 8); /*0x9bd2e*/
          v175 = v121; /*0x9bd31*/
          v122 = *(i - 18); /*0x9bd37*/
          if ( v121 <= v122 ) /*0x9bd42*/
          {
            if ( v121 < v122 ) /*0x9bc10*/
              return &__stack_chk_guard; /*0x9bc10*/
            v156 = *(i - 6); /*0x9bc19*/
            if ( v156 >= *(i - 16) ) /*0x9bc22*/
              return &__stack_chk_guard; /*0x9bc22*/
          }
          else
          {
            v156 = *(i - 6); /*0x9bd4b*/
          }
          v116 = *i; /*0x9bc28*/
          v117 = *(i - 1); /*0x9bc2a*/
          v118 = *(i - 2); /*0x9bc2d*/
          v191 = *(i - 3); /*0x9bc33*/
          v187 = *(i - 4); /*0x9bc3c*/
          v189 = *(i - 7); /*0x9bc45*/
          v188 = *(i - 9); /*0x9bc4e*/
          *(i - 9) = *(i - 19); /*0x9bc57*/
          *(i - 8) = v122; /*0x9bc60*/
          *(i - 7) = *(i - 17); /*0x9bc66*/
          *(i - 6) = *(i - 16); /*0x9bc6c*/
          *(i - 5) = v174; /*0x9bc75*/
          *(i - 4) = *(i - 14); /*0x9bc7b*/
          *(i - 3) = *(i - 13); /*0x9bc81*/
          *(i - 2) = *(i - 12); /*0x9bc87*/
          *(i - 1) = *(i - 11); /*0x9bc8d*/
          *i = *(i - 10); /*0x9bc93*/
          *(i - 10) = v116; /*0x9bc95*/
          *(i - 11) = v117; /*0x9bc98*/
          *(i - 12) = v118; /*0x9bc9b*/
          *(i - 13) = v191; /*0x9bca4*/
          *(i - 14) = v187; /*0x9bcad*/
          *(i - 15) = v173; /*0x9bcb6*/
          *(i - 16) = v156; /*0x9bcbf*/
          *(i - 17) = v189; /*0x9bcc8*/
          *(i - 18) = v175; /*0x9bcd1*/
          *(i - 19) = v188; /*0x9bcda*/
          if ( *(_DWORD *)((char *)&loc_4F8A8 + (_DWORD)cgArray) - 1 <= v155 ) /*0x9bcf3*/
            return &__stack_chk_guard; /*0x9bcf3*/
          ++v155; /*0x9bd00*/
        }
        return &__stack_chk_guard; /*0x9bd28*/
      case 0x4Au:
        v40 = ""; /*0x9b05d*/
        if ( v2 > 1 ) /*0x9b063*/
          v40 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9b069*/
        v41 = atoi(v40); /*0x9b06f*/
        CG_MenuShowNotify(a1, v41); /*0x9b081*/
        return &__stack_chk_guard; /*0x9b086*/
      case 0x4Bu:
        v38 = ""; /*0x9b039*/
        if ( v2 > 1 ) /*0x9b03f*/
          v38 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9b045*/
        v39 = atoi(v38); /*0x9b04b*/
        CL_ResetPlayerMuting(v39); /*0x9b053*/
        return &__stack_chk_guard; /*0x9b058*/
      case 0x4Cu:
        UI_CloseInGameMenu(a1); /*0x9b02f*/
        return &__stack_chk_guard; /*0x9b034*/
      case 0x4Eu:
        v33 = ""; /*0x9afc9*/
        if ( v2 > 2 ) /*0x9afd1*/
          v33 = *(const char **)(cmd_args[cmd_args[0] + 25] + 8); /*0x9afd7*/
        v34 = atoi(v33); /*0x9afe2*/
        v35 = ""; /*0x9afe6*/
        if ( cmd_args[cmd_args[0] + 17] > 1 ) /*0x9aff0*/
          v35 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9aff6*/
        v36 = atoi(v35); /*0x9b001*/
        v37 = CL_ControllerIndexFromClientNum(a1); /*0x9b00c*/
        LiveStorage_SetStat(v37, v36, v34); /*0x9b01c*/
        return &__stack_chk_guard; /*0x9b021*/
      case 0x61u:
        v31 = ""; /*0x9af9b*/
        if ( v2 > 1 ) /*0x9afa1*/
          v31 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9afa7*/
        v32 = atoi(v31); /*0x9afad*/
        CG_SelectWeaponIndex(a1, v32); /*0x9afbf*/
        return &__stack_chk_guard; /*0x9afc4*/
      case 0x62u:
        if ( *(int *)((char *)&loc_4F8A8 + (_DWORD)cgArray) <= 0 ) /*0x9ab9d*/
        {
          *(_DWORD *)&byte_10A1AA1[2887] = -1; /*0x9c0d8*/
          v1 = cmd_args[0]; /*0x9c0e2*/
          v2 = cmd_args[cmd_args[0] + 17]; /*0x9c0e4*/
        }
        v12 = ""; /*0x9aba3*/
        if ( v2 > 1 ) /*0x9aba9*/
          v12 = *(const char **)(cmd_args[v1 + 25] + 4); /*0x9abaf*/
        v13 = atoi(v12); /*0x9abb5*/
        v14 = 64; /*0x9abba*/
        if ( v13 < 65 ) /*0x9abc2*/
          v14 = v13; /*0x9abc2*/
        *(_DWORD *)((char *)&loc_4F8A8 + (_DWORD)cgArray) = v14; /*0x9abcb*/
        *(_DWORD *)&byte_10A1AA1[267] = 0; /*0x9abd8*/
        *(_DWORD *)&byte_10A1AA1[271] = 0; /*0x9abde*/
        *(_DWORD *)&byte_10A1AA1[275] = 0; /*0x9abe5*/
        *(_DWORD *)&byte_10A1AA1[279] = 0; /*0x9abec*/
        v15 = ""; /*0x9abf5*/
        if ( cmd_args[cmd_args[0] + 17] > 2 ) /*0x9abff*/
          v15 = *(const char **)(cmd_args[cmd_args[0] + 25] + 8); /*0x9ac05*/
        *(_DWORD *)((char *)&loc_4F8B0 + (_DWORD)cgArray) = atoi(v15); /*0x9ac16*/
        v16 = ""; /*0x9ac1e*/
        if ( cmd_args[cmd_args[0] + 17] > 3 ) /*0x9ac28*/
          v16 = *(const char **)(cmd_args[cmd_args[0] + 25] + 12); /*0x9ac2e*/
        *(_DWORD *)((char *)&loc_4F8B4 + (_DWORD)cgArray) = atoi(v16); /*0x9ac3f*/
        v17 = ""; /*0x9ac47*/
        if ( cmd_args[cmd_args[0] + 17] > 4 ) /*0x9ac51*/
          v17 = *(const char **)(cmd_args[cmd_args[0] + 25] + 16); /*0x9ac57*/
        *(_DWORD *)&byte_10A1AA1[2875] = atoi(v17); /*0x9ac68*/
        memset(&byte_10A1AA1[315], 0, 0xA00u); /*0x9ac88*/
        *(_DWORD *)&byte_10A1AA1[283] = 0; /*0x9ac97*/
        *(_DWORD *)&byte_10A1AA1[287] = 0; /*0x9ac9d*/
        *(_DWORD *)&byte_10A1AA1[291] = 0; /*0x9aca4*/
        *(_DWORD *)&byte_10A1AA1[295] = 0; /*0x9acab*/
        *(_DWORD *)&byte_10A1AA1[299] = 0; /*0x9acbc*/
        *(_DWORD *)&byte_10A1AA1[303] = 0; /*0x9acc2*/
        *(_DWORD *)&byte_10A1AA1[307] = 0; /*0x9acc9*/
        *(_DWORD *)&byte_10A1AA1[311] = 0; /*0x9acd0*/
        if ( *(int *)((char *)&loc_4F8A8 + (_DWORD)cgArray) > 0 ) /*0x9ace5*/
        {
          v18 = cgArray; /*0x9aceb*/
          v167 = 0; /*0x9aced*/
          v184 = 5; /*0x9acf7*/
          v185 = 44; /*0x9ad01*/
          do /*0x9adf6*/
          {
            v22 = ""; /*0x9adfe*/
            if ( cmd_args[cmd_args[0] + 17] > v184 ) /*0x9ae0d*/
              v22 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4 * v184); /*0x9ae13*/
            v18[81463] = atoi(v22); /*0x9ae1e*/
            v23 = ""; /*0x9ae2d*/
            if ( cmd_args[cmd_args[0] + 17] > v184 + 1 ) /*0x9ae36*/
              v23 = *(const char **)(cmd_args[cmd_args[0] + 25] + v185 - 20); /*0x9ae42*/
            v18[81464] = atoi(v23); /*0x9ae4e*/
            v24 = ""; /*0x9ae5f*/
            if ( cmd_args[cmd_args[0] + 17] > v184 + 2 ) /*0x9ae68*/
              v24 = *(const char **)(cmd_args[cmd_args[0] + 25] + v185 - 16); /*0x9ae74*/
            v18[81465] = atoi(v24); /*0x9ae80*/
            v25 = ""; /*0x9ae91*/
            if ( cmd_args[cmd_args[0] + 17] > v184 + 3 ) /*0x9ae9a*/
              v25 = *(const char **)(cmd_args[cmd_args[0] + 25] + v185 - 12); /*0x9aea6*/
            v18[81466] = atoi(v25); /*0x9aeb2*/
            v26 = ""; /*0x9aec3*/
            if ( cmd_args[cmd_args[0] + 17] > v184 + 4 ) /*0x9aecc*/
              v26 = *(const char **)(cmd_args[cmd_args[0] + 25] + v185 - 8); /*0x9aed8*/
            v166 = atoi(v26); /*0x9aee4*/
            v27 = ""; /*0x9aef5*/
            if ( cmd_args[cmd_args[0] + 17] > v184 + 5 ) /*0x9aefe*/
              v27 = *(const char **)(cmd_args[cmd_args[0] + 25] + v185 - 4); /*0x9af0a*/
            v18[81468] = atoi(v27); /*0x9af16*/
            v28 = ""; /*0x9af27*/
            if ( cmd_args[cmd_args[0] + 17] > v184 + 6 ) /*0x9af30*/
              v28 = *(const char **)(cmd_args[cmd_args[0] + 25] + v185); /*0x9af3c*/
            v18[81470] = atoi(v28); /*0x9af47*/
            v29 = v18[81463]; /*0x9af4d*/
            if ( (unsigned int)(v166 - 1) <= 7 ) /*0x9af5d*/
            {
              ConfigString = (const char *)CL_GetConfigString(a1, v166 + 2258); /*0x9af7b*/
              v18[81471] = Material_RegisterHandle(ConfigString); /*0x9af90*/
            }
            v19 = &cgArray[307 * v29]; /*0x9ad16*/
            v18[81469] = v19[239574]; /*0x9ad22*/
            CL_GetRankIcon(v19[239574], *(_DWORD *)((char *)&loc_E9F5C + (_DWORD)v19), &cgArray[10 * v167 + 81472]); /*0x9ad55*/
            if ( (unsigned int)v18[81463] > 0x3F ) /*0x9ad61*/
              v18[81463] = 0; /*0x9ad63*/
            cgArray[307 * v18[81463] + 239577] = v18[81464]; /*0x9ad83*/
            v20 = &cgArray[307 * v18[81463]]; /*0x9ad94*/
            v21 = 0; /*0x9ad96*/
            if ( *(_DWORD *)((char *)&loc_E9F34 + (_DWORD)v20) ) /*0x9ad98*/
              v21 = *(_DWORD *)((char *)FX_ConvertElemDef + (_DWORD)v20); /*0x9ada2*/
            v18[81467] = v21; /*0x9adae*/
            ++*(_DWORD *)((char *)&loc_4F8CC + (_DWORD)&cgArray[v21]); /*0x9adb9*/
            *(_DWORD *)((char *)&loc_4F8BC + (_DWORD)&cgArray[v18[81467]]) += v18[81465]; /*0x9adcc*/
            ++v167; /*0x9add3*/
            v184 += 7; /*0x9add9*/
            v18 += 10; /*0x9ade0*/
            v185 += 28; /*0x9ade3*/
          }
          while ( *(_DWORD *)((char *)&loc_4F8A8 + (_DWORD)cgArray) > v167 ); /*0x9adf6*/
        }
        v97 = *(_DWORD *)((char *)&loc_4F8CC + (_DWORD)cgArray); /*0x9b89e*/
        if ( v97 <= 0 || (v98 = *(_DWORD *)((char *)&loc_4F8BC + (_DWORD)cgArray), v98 <= 0) ) /*0x9b8b4*/
          *(_DWORD *)((char *)&loc_4F8BC + (_DWORD)cgArray) = 0; /*0x9bd9c*/
        else
          *(_DWORD *)((char *)&loc_4F8BC + (_DWORD)cgArray) = v98 / v97; /*0x9b8c9*/
        v99 = *(_DWORD *)((char *)&loc_4F8D0 + (_DWORD)cgArray); /*0x9b8d1*/
        if ( v99 <= 0 || *(int *)&byte_10A1AA1[287] <= 0 ) /*0x9b8e7*/
          *(_DWORD *)&byte_10A1AA1[287] = 0; /*0x9bd85*/
        else
          *(int *)&byte_10A1AA1[287] /= v99; /*0x9b8fc*/
        v100 = *(_DWORD *)((char *)&loc_4F8D4 + (_DWORD)cgArray); /*0x9b904*/
        if ( v100 <= 0 || (v101 = *(_DWORD *)((char *)&loc_4F8C4 + (_DWORD)cgArray), v101 <= 0) ) /*0x9b91a*/
          *(_DWORD *)((char *)&loc_4F8C4 + (_DWORD)cgArray) = 0; /*0x9bd6f*/
        else
          *(_DWORD *)((char *)&loc_4F8C4 + (_DWORD)cgArray) = v101 / v100; /*0x9b92f*/
        v102 = *(_DWORD *)((char *)&loc_4F8D8 + (_DWORD)cgArray); /*0x9b937*/
        if ( v102 <= 0 || *(int *)&byte_10A1AA1[295] <= 0 ) /*0x9b94d*/
          *(_DWORD *)&byte_10A1AA1[295] = 0; /*0x9bd5b*/
        else
          *(int *)&byte_10A1AA1[295] /= v102; /*0x9b962*/
        return &__stack_chk_guard; /*0x9b968*/
      case 0x63u:
        v11 = ""; /*0x9ab46*/
        if ( v2 > 1 ) /*0x9ab4c*/
          v11 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9ab52*/
        CG_TranslateHudElemMessage(a1, v11, "announcement message", v194); /*0x9ab74*/
        goto LABEL_28; /*0x9ab74*/
      case 0x64u:
        CG_ConfigStringModified(v151); /*0x9ab3c*/
        return &__stack_chk_guard; /*0x9ab41*/
      case 0x65u:
        v82 = ""; /*0x9b614*/
        if ( v2 > 1 ) /*0x9b61a*/
          v82 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9b620*/
        goto LABEL_153; /*0x9b620*/
      case 0x66u:
        v82 = ""; /*0x9b5ca*/
        if ( v2 > 1 ) /*0x9b5d0*/
          v82 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9b5d6*/
LABEL_153:
        CG_TranslateHudElemMessage(a1, v82, "game message", v194); /*0x9b5d9*/
        CG_GameMessage(a1, v194); /*0x9b60a*/
        return &__stack_chk_guard; /*0x9b60f*/
      case 0x67u:
        v81 = ""; /*0x9b5a4*/
        if ( v2 > 1 ) /*0x9b5aa*/
          v81 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9b5b0*/
        CG_TranslateHudElemMessage(a1, v81, "bold game message", v194); /*0x9b5c5*/
LABEL_28:
        CG_BoldGameMessage(a1, v194); /*0x9ab79*/
        return &__stack_chk_guard; /*0x9ab8b*/
      case 0x68u:
        if ( *(_BYTE *)(cg_teamChatsOnly + 12) ) /*0x9b4eb*/
          return &__stack_chk_guard; /*0x9b4ef*/
        v77 = ""; /*0x9b4f5*/
        if ( v2 > 1 ) /*0x9b4fb*/
          v77 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9b501*/
        v78 = (const char *)SEH_LocalizeTextMessage(v77, "chat message", 0); /*0x9b517*/
        I_strncpyz(v195, v78, 150); /*0x9b531*/
        v79 = v195[0]; /*0x9b536*/
        v75 = v195; /*0x9b53d*/
        if ( v195[0] ) /*0x9b545*/
        {
          v80 = 0; /*0x9b547*/
          do /*0x9b563*/
          {
            if ( v79 != 25 ) /*0x9b552*/
              v195[v80++] = v79; /*0x9b554*/
            v79 = *++v75; /*0x9b55c*/
          }
          while ( v79 ); /*0x9b563*/
          v75 = &v195[v80]; /*0x9b56b*/
        }
LABEL_137:
        *v75 = 0; /*0x9b4ad*/
        CG_AddToTeamChat(v152, v153); /*0x9b4bc*/
        Com_Printf(14, "%s\n", v195); /*0x9b4da*/
        return &__stack_chk_guard; /*0x9b4df*/
      case 0x69u:
        v72 = ""; /*0x9b43a*/
        if ( v2 > 1 ) /*0x9b440*/
          v72 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9b446*/
        v73 = (const char *)SEH_LocalizeTextMessage(v72, "team chat message", 0); /*0x9b45c*/
        I_strncpyz(v195, v73, 150); /*0x9b476*/
        v74 = v195[0]; /*0x9b47b*/
        v75 = v195; /*0x9b482*/
        if ( v195[0] ) /*0x9b48a*/
        {
          v76 = 0; /*0x9b48c*/
          do /*0x9b4a3*/
          {
            if ( v74 != 25 ) /*0x9b492*/
              v195[v76++] = v74; /*0x9b494*/
            v74 = *++v75; /*0x9b49c*/
          }
          while ( v74 ); /*0x9b4a3*/
          v75 = &v195[v76]; /*0x9b4ab*/
        }
        goto LABEL_137; /*0x9b4ab*/
      case 0x6Au:
        v56 = ""; /*0x9b29e*/
        if ( v2 > 1 ) /*0x9b2a4*/
          v56 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9b2aa*/
        v57 = atoi(v56); /*0x9b2b5*/
        v58 = ""; /*0x9b2b9*/
        if ( cmd_args[cmd_args[0] + 17] > 2 ) /*0x9b2c3*/
          v58 = *(const char **)(cmd_args[cmd_args[0] + 25] + 8); /*0x9b2c9*/
        v59 = atoi(v58); /*0x9b2d4*/
        v60 = ""; /*0x9b2d8*/
        if ( cmd_args[cmd_args[0] + 17] > 5 ) /*0x9b2e2*/
          v60 = *(const char **)(cmd_args[cmd_args[0] + 25] + 20); /*0x9b2e8*/
        v162 = atof(v60); /*0x9b2f3*/
        v61 = ""; /*0x9b2fb*/
        if ( cmd_args[cmd_args[0] + 17] > 4 ) /*0x9b305*/
          v61 = *(const char **)(cmd_args[cmd_args[0] + 25] + 16); /*0x9b30b*/
        v163 = atof(v61); /*0x9b316*/
        v62 = ""; /*0x9b31e*/
        if ( cmd_args[cmd_args[0] + 17] > 3 ) /*0x9b328*/
          v62 = *(const char **)(cmd_args[cmd_args[0] + 25] + 12); /*0x9b32e*/
        v63 = atof(v62); /*0x9b33f*/
        *(float *)v193 = v63; /*0x9b347*/
        v64 = v163; /*0x9b34f*/
        *(float *)&v193[1] = v64; /*0x9b357*/
        v65 = v162; /*0x9b35f*/
        *(float *)&v193[2] = v65; /*0x9b367*/
        v66 = ""; /*0x9b371*/
        if ( cmd_args[cmd_args[0] + 17] > 8 ) /*0x9b37b*/
          v66 = *(const char **)(cmd_args[cmd_args[0] + 25] + 32); /*0x9b381*/
        v164 = atof(v66); /*0x9b38c*/
        v67 = ""; /*0x9b394*/
        if ( cmd_args[cmd_args[0] + 17] > 7 ) /*0x9b39e*/
          v67 = *(const char **)(cmd_args[cmd_args[0] + 25] + 28); /*0x9b3a4*/
        v165 = atof(v67); /*0x9b3af*/
        v68 = ""; /*0x9b3b7*/
        if ( cmd_args[cmd_args[0] + 17] > 6 ) /*0x9b3c1*/
          v68 = *(const char **)(cmd_args[cmd_args[0] + 25] + 24); /*0x9b3c7*/
        v69 = atof(v68); /*0x9b3d8*/
        *(float *)v192 = v69; /*0x9b3e0*/
        v70 = v165; /*0x9b3e8*/
        *(float *)&v192[1] = v70; /*0x9b3f0*/
        v71 = v164; /*0x9b3f8*/
        *(float *)&v192[2] = v71; /*0x9b400*/
        DynEntCl_DestroyEvent(a1, v57, v59, v193, v192); /*0x9b430*/
        return &__stack_chk_guard; /*0x9b435*/
      case 0x6Bu:
        if ( v2 == 2 )
        {
          v128 = atoi(*(const char **)(cmd_args[cmd_args[0] + 25] + 4)); /*0x9be7a*/
          if ( (unsigned int)(v128 - 1) <= 0xFF )
          {
            v149 = (const char *)CL_GetConfigString(a1, v128 + 1342); /*0x9c150*/
            CG_StopClientSoundAliasByName(a1, v149); /*0x9c162*/
          }
          else
          {
            Com_PrintError(9, "ERROR: LocalSoundStop() called with index %i (should be in range[1,%i])\n", v128, 256);
          }
        }
        else
        {
          Com_PrintError(9, "ERROR: LocalSoundStop(), should be called with 2 arguments.\n");
        }
        return &__stack_chk_guard; /*0x9b299*/
      case 0x6Eu:
        CG_MapRestart(a1, 1); /*0x9b272*/
        return &__stack_chk_guard; /*0x9b277*/
      case 0x6Fu:
        if ( (unsigned __int8)CL_IsFirstActiveLocalClient(a1) ) /*0x9b7d5*/
        {
          v93 = ""; /*0x9b7e4*/
          if ( cmd_args[cmd_args[0] + 17] > 2 ) /*0x9b7ee*/
            v93 = *(const char **)(cmd_args[cmd_args[0] + 25] + 8); /*0x9b7f4*/
          v94 = atoi(v93); /*0x9b7ff*/
          v95 = ""; /*0x9b803*/
          if ( cmd_args[cmd_args[0] + 17] > 1 ) /*0x9b80d*/
            v95 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9b813*/
          v96 = CL_PickSoundAlias(v95); /*0x9b819*/
          SND_PlayMusicAlias(a1, v96, v94 != 0, 1); /*0x9b83e*/
        }
        return &__stack_chk_guard; /*0x9b843*/
      case 0x70u:
        if ( (unsigned __int8)CL_IsFirstActiveLocalClient(a1) ) /*0x9b795*/
        {
          v91 = ""; /*0x9b7a4*/
          if ( cmd_args[cmd_args[0] + 17] > 1 ) /*0x9b7ae*/
            v91 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9b7b4*/
          v92 = atoi(v91); /*0x9b7ba*/
          SND_StopMusic(v92); /*0x9b7c2*/
        }
        return &__stack_chk_guard; /*0x9b7c7*/
      case 0x71u:
        if ( (unsigned __int8)CL_IsFirstActiveLocalClient(a1) ) /*0x9b68d*/
        {
          v83 = ""; /*0x9b69c*/
          if ( cmd_args[cmd_args[0] + 17] > 2 ) /*0x9b6a6*/
            v83 = *(const char **)(cmd_args[cmd_args[0] + 25] + 8); /*0x9b6ac*/
          v84 = atoi(v83); /*0x9b6b7*/
          v85 = ""; /*0x9b6bb*/
          if ( cmd_args[cmd_args[0] + 17] > 1 ) /*0x9b6c5*/
            v85 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9b6cb*/
          v86 = atof(v85); /*0x9b6e0*/
          SND_FadeAllSounds(v86, v84); /*0x9b6ed*/
        }
        return &__stack_chk_guard; /*0x9b6f2*/
      case 0x72u:
        if ( v2 == 6 )
        {
          v129 = atoi(*(const char **)(cmd_args[cmd_args[0] + 25] + 4)); /*0x9bebe*/
          v130 = ""; /*0x9bec2*/
          if ( cmd_args[cmd_args[0] + 17] > 3 ) /*0x9becc*/
            v130 = *(const char **)(cmd_args[cmd_args[0] + 25] + 12); /*0x9bed2*/
          v170 = atof(v130); /*0x9bedd*/
          v131 = ""; /*0x9bee5*/
          if ( cmd_args[cmd_args[0] + 17] > 4 ) /*0x9beef*/
            v131 = *(const char **)(cmd_args[cmd_args[0] + 25] + 16); /*0x9bef5*/
          v169 = atof(v131); /*0x9bf00*/
          v132 = ""; /*0x9bf08*/
          if ( cmd_args[cmd_args[0] + 17] > 5 ) /*0x9bf12*/
            v132 = *(const char **)(cmd_args[cmd_args[0] + 25] + 20); /*0x9bf18*/
          v168 = atof(v132); /*0x9bf23*/
          v133 = ""; /*0x9bf2b*/
          if ( cmd_args[cmd_args[0] + 17] > 2 ) /*0x9bf35*/
            v133 = *(const char **)(cmd_args[cmd_args[0] + 25] + 8); /*0x9bf3b*/
          v134 = v168; /*0x9bf3e*/
          v160 = floorf((float)(v134 * 1000.0) + 0.5); /*0x9bf60*/
          v135 = 0; /*0x9bf6e*/
          if ( (int)v160 >= 0 ) /*0x9bf72*/
            v135 = (int)v160; /*0x9bf72*/
          v136 = v169; /*0x9bf79*/
          v154 = v136; /*0x9bf81*/
          v137 = v170; /*0x9bf87*/
          SND_SetEnvironmentEffects(v129, v133, v137, v154, v135); /*0x9bf9c*/
        }
        else
        {
          Com_PrintError(14, "ERROR: CG_ReverbCmd called with %i args (should be 6)\n", cmd_args[cmd_args[0] + 17]);
        }
        return &__stack_chk_guard; /*0x9b67f*/
      case 0x73u:
        if ( v2 == 2 )
        {
          v123 = atoi(*(const char **)(cmd_args[cmd_args[0] + 25] + 4)); /*0x9bdba*/
          if ( (unsigned int)(v123 - 1) <= 0xFF ) /*0x9bdc4*/
          {
            v150 = (const char *)CL_GetConfigString(a1, v123 + 1342); /*0x9c17f*/
            CG_PlayClientSoundAliasByName(a1, v150); /*0x9c191*/
            return &__stack_chk_guard; /*0x9c196*/
          }
          Com_PrintError(9, "ERROR: LocalSound() called with index %i (should be in range[1,%i])\n", v123, 256);
        }
        else
        {
          Com_PrintError(9, "ERROR: LocalSound() called with %i args (should be 2)\n", cmd_args[cmd_args[0] + 17]);
        }
        CL_DumpReliableCommands(a1); /*0x9b782*/
        return &__stack_chk_guard; /*0x9b787*/
      case 0x74u:
        v87 = ""; /*0x9b6f7*/
        if ( v2 > 1 ) /*0x9b6fd*/
          v87 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4); /*0x9b703*/
        v88 = atoi(v87); /*0x9b709*/
        v89 = v88; /*0x9b70e*/
        if ( v88 > 0x1F )
        {
          Com_Printf(14, "Server tried to open a bad script menu index: %i\n", v88);
          v90 = (const char *)va("cmd mr %i bad\n", v89); /*0x9b73c*/
          Cbuf_AddText(a1, v90); /*0x9b74e*/
          return &__stack_chk_guard; /*0x9b753*/
        }
        v103 = (const char *)CL_GetConfigString(a1, v88 + 1970); /*0x9b98a*/
        if ( *v103 )
        {
          if ( cmd_args[cmd_args[0] + 17] > 2 && (v104 = *(_BYTE **)(cmd_args[cmd_args[0] + 25] + 8)) != 0 ) /*0x9b9ab*/
          {
            v172 = *v104 == 0; /*0x9b9b4*/
            v105 = v172; /*0x9b9bb*/
          }
          else
          {
            v172 = 1; /*0x9c0ed*/
            v105 = 1; /*0x9c0f4*/
          }
          if ( !UI_PopupScriptMenu(a1, v103, v105) ) /*0x9b9d3*/
          {
            if ( cg_waitingScriptMenu[72 * a1] ) /*0x9b9fc*/
            {
              if ( !I_stricmp(v103, &cg_waitingScriptMenu[72 * a1]) ) /*0x9ba14*/
                return &__stack_chk_guard; /*0x9ba14*/
              v106 = (const char *)va("cmd mr %i noop\n", dword_4461E0[18 * a1]); /*0x9ba2c*/
              Cbuf_AddText(a1, v106); /*0x9ba3e*/
            }
            I_strncpyz(&cg_waitingScriptMenu[72 * a1], v103, 64); /*0x9ba58*/
            dword_4461E0[18 * a1] = v89; /*0x9ba5d*/
            byte_4461E4[72 * a1] = v172; /*0x9ba6b*/
          }
        }
        else
        {
          Com_Printf(14, "Server tried to open a non-loaded script menu index: %i\n", v89);
          v148 = (const char *)va("cmd mr %i bad\n", v89); /*0x9c121*/
          Cbuf_AddText(a1, v148); /*0x9c133*/
        }
        return &__stack_chk_guard; /*0x9ba72*/
      case 0x75u:
        UI_ClosePopupScriptMenu(a1, 1u); /*0x9ab1b*/
        cg_waitingScriptMenu[72 * a1] = 0; /*0x9ab29*/
        return &__stack_chk_guard; /*0x9ab31*/
      case 0x76u:
        if ( v2 > 1 ) /*0x9aa0b*/
        {
          v9 = 1; /*0x9aa0d*/
          v186 = 4; /*0x9aa12*/
          do /*0x9aa6a*/
          {
            I_strncpyz(v195, *(const char **)(v186 + cmd_args[v1 + 25]), 150); /*0x9aa92*/
            v10 = ""; /*0x9aa9c*/
            if ( v9 + 1 < cmd_args[cmd_args[0] + 17] ) /*0x9aaa5*/
              v10 = *(const char **)(cmd_args[cmd_args[0] + 25] + v186 + 4); /*0x9aab1*/
            if ( I_stricmp(v195, "cg_objectiveText") ) /*0x9aac6*/
            {
              if ( I_stricmp(v195, "hud_drawHud") ) /*0x9aae4*/
              {
                if ( I_stricmp(v195, "g_scriptMainMenu") ) /*0x9b859*/
                  Dvar_SetFromStringByName(v195, v10); /*0x9b88e*/
                else
                  I_strncpyz(byte_10A1AA1, v10, 256); /*0x9b877*/
              }
              else
              {
                dword_10A25F4 = atoi(v10); /*0x9aaff*/
              }
            }
            else
            {
              I_strncpyz(&byte_10A16A1, v10, 1024); /*0x9aa55*/
            }
            v9 += 2; /*0x9aa5a*/
            v1 = cmd_args[0]; /*0x9aa5d*/
            v186 += 8; /*0x9aa5f*/
          }
          while ( cmd_args[cmd_args[0] + 17] > v9 ); /*0x9aa6a*/
        }
        return &__stack_chk_guard; /*0x9aa6a*/
      default:
        break;
    }
  }
  v4 = ""; /*0x9a932*/
  if ( v2 > 0 ) /*0x9a939*/
    v4 = *(const char **)cmd_args[cmd_args[0] + 25]; /*0x9a93f*/
  Com_Printf(14, "Unknown client game command: %s\n", v4);
  v5 = cmd_args[cmd_args[0] + 17]; /*0x9a95b*/
  if ( v5 > 1 ) /*0x9a962*/
  {
    Com_Printf(14, "Arguments(%i):", v5 - 1); /*0x9a97a*/
    for ( j = 1; j != v5; ++j ) /*0x9a97f*/
    {
      v7 = ""; /*0x9a992*/
      if ( j < cmd_args[cmd_args[0] + 17] ) /*0x9a99b*/
        v7 = *(const char **)(cmd_args[cmd_args[0] + 25] + 4 * j); /*0x9a9a1*/
      Com_Printf(14, " %s", v7); /*0x9a9b7*/
    }
    Com_Printf(14, "\n"); /*0x9a9d0*/
  }
  return &__stack_chk_guard; /*0x9a9f0*/
}