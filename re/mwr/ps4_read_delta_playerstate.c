__int64 __fastcall MSG_ReadDeltaPlayerstate(
        unsigned int a1,
        char *a2,
        unsigned int a3,
        _BYTE *a4,
        __int64 a5,
        char a6,
        __m128 _XMM0,
        __m128 _XMM1,
        __m128 a9)
{
  int v13; // ecx
  int v14; // r8d
  int v15; // r9d
  int v16; // eax
  int v18; // r15d
  __int64 v19; // rsi
  int v20; // eax
  __int64 v21; // rcx
  int v22; // r8d
  int v23; // r9d
  int v24; // r14d
  char v25; // al
  __int64 v26; // rdi
  int v27; // r8d
  int v28; // r9d
  char *v30; // rbx
  int v31; // eax
  int v32; // r14d
  __int64 v33; // r12
  int v34; // ecx
  int v35; // r8d
  int v36; // r9d
  unsigned int v37; // r15d
  __int64 *v38; // r13
  int v39; // ebx
  __int16 v40; // ax
  __int64 v41; // r13
  __int16 v42; // ax
  int v43; // r15d
  char v44; // al
  char v45; // al
  int v46; // eax
  __int64 *v47; // r12
  __int64 *v48; // rbx
  __int16 v50; // dx
  int v52; // ecx
  int v53; // edx
  __int16 *v55; // r15
  int v56; // ecx
  int v57; // eax
  int v58; // r8d
  char v59; // r9
  int v60; // ebx
  unsigned int v61; // ebx
  int v62; // r12d
  __int64 *v63; // r14
  int v64; // r14d
  char *v65; // r13
  __int64 *v66; // rbx
  char v67; // r9
  __int64 v68; // rdi
  int v69; // edx
  int v70; // r8d
  char v73; // r9
  __int64 v74; // rdi
  __int64 v75; // rax
  __int64 v76; // r15
  __int64 v77; // r12
  __int64 v78; // rdx
  int v79; // ecx
  int v80; // r8d
  int v81; // r9d
  char v82; // al
  char v83; // bl
  int v84; // eax
  int v85; // eax
  int v86; // eax
  __int64 v87; // r14
  int v88; // eax
  int v89; // ebx
  bool v90; // zf
  __int64 v91; // rbx
  int v92; // eax
  int v93; // eax
  _DWORD *v96; // r12
  int v97; // eax
  char v98; // r9
  bool v99; // al
  int v100; // eax
  __int64 v102; // rdx
  int Long; // eax
  int v104; // eax
  char v105; // al
  __int64 v106; // rdi
  int WeaponName; // eax
  int v108; // edx
  int v109; // r8d
  int v110; // r9d
  char v111; // al
  int v112; // eax
  int v113; // r14d
  int v114; // eax
  int v115; // ebx
  __int64 v116; // rbx
  int v117; // eax
  int v118; // eax
  char *v119; // r14
  __int64 v120; // rbx
  _DWORD *v121; // r13
  __int64 *v122; // r15
  int v123; // eax
  char *v124; // rdi
  __int64 v125; // r12
  int v126; // r14d
  int v127; // r15d
  __int64 v128; // rdx
  __int64 v129; // rcx
  int v130; // eax
  __int64 result; // rax
  _BYTE *v132; // [rsp+0h] [rbp-4C28h]
  __int64 v133; // [rsp+0h] [rbp-4C28h]
  char v134; // [rsp+8h] [rbp-4C20h]
  __int64 v135; // [rsp+30h] [rbp-4BF8h]
  __int16 *v137; // [rsp+40h] [rbp-4BE8h]
  int v138; // [rsp+4Ch] [rbp-4BDCh]
  int v139; // [rsp+50h] [rbp-4BD8h]
  _DWORD *v141; // [rsp+58h] [rbp-4BD0h]
  bool v142; // [rsp+60h] [rbp-4BC8h]
  int Bit; // [rsp+68h] [rbp-4BC0h]
  unsigned int v145; // [rsp+6Ch] [rbp-4BBCh]
  int NumFieldsSkipped; // [rsp+70h] [rbp-4BB8h]
  __int64 v147; // [rsp+70h] [rbp-4BB8h]
  char *v148; // [rsp+78h] [rbp-4BB0h]
  char *v149; // [rsp+78h] [rbp-4BB0h]
  unsigned int v150; // [rsp+80h] [rbp-4BA8h]
  int v151; // [rsp+84h] [rbp-4BA4h]
  int v152; // [rsp+88h] [rbp-4BA0h]
  _BYTE *v153; // [rsp+90h] [rbp-4B98h]
  char v154; // [rsp+9Fh] [rbp-4B89h]
  char v155; // [rsp+9Fh] [rbp-4B89h]
  __int64 *v156; // [rsp+A0h] [rbp-4B88h]
  int v157; // [rsp+A8h] [rbp-4B80h]
  int v158; // [rsp+A8h] [rbp-4B80h]
  __int128 v159; // [rsp+B0h] [rbp-4B78h] BYREF
  _BYTE v160[32]; // [rsp+C0h] [rbp-4B68h] BYREF
  _BYTE v161[32]; // [rsp+E0h] [rbp-4B48h] BYREF
  _BYTE v162[28]; // [rsp+100h] [rbp-4B28h] BYREF
  __int16 v164; // [rsp+12Ch] [rbp-4AFCh]
  __int16 v165; // [rsp+12Eh] [rbp-4AFAh]
  __int16 v166; // [rsp+134h] [rbp-4AF4h]
  __int16 v167; // [rsp+136h] [rbp-4AF2h]
  int v168; // [rsp+168h] [rbp-4AC0h]
  int v169; // [rsp+1A4h] [rbp-4A84h]
  int v170; // [rsp+1A8h] [rbp-4A80h]
  int v171; // [rsp+1ACh] [rbp-4A7Ch]
  int v172; // [rsp+1B4h] [rbp-4A74h]
  int v173; // [rsp+1C8h] [rbp-4A60h]
  __int16 v174; // [rsp+1D8h] [rbp-4A50h]
  int v175; // [rsp+34Ch] [rbp-48DCh]
  int v176; // [rsp+35Ch] [rbp-48CCh]
  int v177; // [rsp+360h] [rbp-48C8h]
  int v178; // [rsp+5E4h] [rbp-4644h]
  int v179; // [rsp+5E8h] [rbp-4640h]
  int v180; // [rsp+5ECh] [rbp-463Ch]
  int v181; // [rsp+2030h] [rbp-2BF8h]
  int v182; // [rsp+2048h] [rbp-2BE0h]
  int v183; // [rsp+204Ch] [rbp-2BDCh]
  int v184; // [rsp+2058h] [rbp-2BD0h]
  __int16 v186; // [rsp+2080h] [rbp-2BA8h]
  __int16 v187; // [rsp+20A4h] [rbp-2B84h]
  __int16 v188; // [rsp+20C8h] [rbp-2B60h]
  __int16 v189; // [rsp+20ECh] [rbp-2B3Ch]
  __int16 v190; // [rsp+2110h] [rbp-2B18h]
  __int16 v191; // [rsp+2134h] [rbp-2AF4h]
  __int16 v192; // [rsp+2158h] [rbp-2AD0h]
  __int16 v193; // [rsp+217Ch] [rbp-2AACh]
  __int16 v194; // [rsp+21A0h] [rbp-2A88h]
  __int16 v195; // [rsp+21C4h] [rbp-2A64h]
  __int16 v196; // [rsp+21E8h] [rbp-2A40h]
  __int16 v197; // [rsp+220Ch] [rbp-2A1Ch]
  __int16 v198; // [rsp+2230h] [rbp-29F8h]
  __int16 v199; // [rsp+2254h] [rbp-29D4h]
  __int16 v200; // [rsp+2278h] [rbp-29B0h]
  __int16 v201; // [rsp+229Ch] [rbp-298Ch]
  __int16 v202; // [rsp+22C0h] [rbp-2968h]
  __int16 v203; // [rsp+22E4h] [rbp-2944h]
  __int16 v204; // [rsp+2308h] [rbp-2920h]
  __int16 v205; // [rsp+232Ch] [rbp-28FCh]
  __int16 v206; // [rsp+2350h] [rbp-28D8h]
  __int16 v207; // [rsp+2374h] [rbp-28B4h]
  __int16 v208; // [rsp+2398h] [rbp-2890h]
  __int16 v209; // [rsp+23BCh] [rbp-286Ch]
  __int16 v210; // [rsp+23E0h] [rbp-2848h]
  __int16 v211; // [rsp+2404h] [rbp-2824h]
  __int16 v212; // [rsp+2428h] [rbp-2800h]
  __int16 v213; // [rsp+244Ch] [rbp-27DCh]
  __int16 v214; // [rsp+2470h] [rbp-27B8h]
  __int16 v215; // [rsp+2494h] [rbp-2794h]
  __int16 v216; // [rsp+24B8h] [rbp-2770h]
  __int16 v217; // [rsp+24DCh] [rbp-274Ch]
  char v218[1024]; // [rsp+47C0h] [rbp-468h] BYREF
  __int64 v219; // [rsp+4BC0h] [rbp-68h]

  v219 = *(_QWORD *)COMMON; /*0x72560f*/
  if ( !unk_337EDC0 ) /*0x72561c*/
    MyAssertHandler( /*0x72563c*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../client_mp/client_mp.h",
      1198,
      0,
      (unsigned int)"%s",
      (unsigned int)"clientConnections",
      a6);
  if ( unk_337EDB0[0] <= a1 ) /*0x72564e*/
    MyAssertHandler( /*0x72566d*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../client_mp/client_mp.h",
      1200,
      0,
      (unsigned int)"localClientNum doesn't index MAX_LOCAL_CLIENTS\n\t%i not in [0, %i)",
      a1,
      LOBYTE(unk_337EDB0[0]));
  v135 = (int)a1; /*0x72567e*/
  v154 = *(_BYTE *)(unk_337EDC0 + 333288LL * (int)a1 + 4); /*0x725691*/
  if ( !a4 ) /*0x725698*/
  {
    a4 = v162; /*0x72569e*/
    PLmemset(v162, 0, 18048); /*0x7256b0*/
    __asm /*0x7256b5*/
    {
      vmovdqa xmm0, cs:xmmword_F9B9A0
      vmovaps ymm1, cs:ymmword_F9B9C0
    }
    v165 = 2047; /*0x7256c5*/
    v162[15] = 15; /*0x7256cf*/
    v166 = 2047; /*0x7256d7*/
    v164 = 2047; /*0x7256e1*/
    v174 = 2047; /*0x7256eb*/
    v170 = 0; /*0x7256f5*/
    __asm { vmovdqu [rsp+4C28h+var_4B0C], xmm0 } /*0x725700*/
    v182 = 1086324736; /*0x725709*/
    v183 = 1072064102; /*0x725714*/
    v184 = 0; /*0x72571f*/
    __asm { vmovups [rsp+4C28h+var_2BCC], ymm1 } /*0x72572a*/
    v186 = 2047; /*0x725733*/
    v187 = 2047; /*0x72573d*/
    v188 = 2047; /*0x725747*/
    v189 = 2047; /*0x725751*/
    v190 = 2047; /*0x72575b*/
    v191 = 2047; /*0x725765*/
    v192 = 2047; /*0x72576f*/
    v193 = 2047; /*0x725779*/
    v194 = 2047; /*0x725783*/
    v195 = 2047; /*0x72578d*/
    v196 = 2047; /*0x725797*/
    v197 = 2047; /*0x7257a1*/
    v198 = 2047; /*0x7257ab*/
    v199 = 2047; /*0x7257b5*/
    v200 = 2047; /*0x7257bf*/
    v201 = 2047; /*0x7257c9*/
    v202 = 2047; /*0x7257d3*/
    v203 = 2047; /*0x7257dd*/
    v204 = 2047; /*0x7257e7*/
    v205 = 2047; /*0x7257f1*/
    v206 = 2047; /*0x7257fb*/
    v207 = 2047; /*0x725805*/
    v208 = 2047; /*0x72580f*/
    v209 = 2047; /*0x725819*/
    v210 = 2047; /*0x725823*/
    v211 = 2047; /*0x72582d*/
    v212 = 2047; /*0x725837*/
    v213 = 2047; /*0x725841*/
    v214 = 2047; /*0x72584b*/
    v215 = 2047; /*0x725855*/
    v216 = 2047; /*0x72585f*/
    v217 = 2047; /*0x725869*/
    v178 = 0; /*0x725873*/
    v179 = 0; /*0x72587e*/
    v180 = 1065353216; /*0x725889*/
    v177 = 1065353216; /*0x725894*/
    v168 = 0; /*0x72589f*/
    v169 = 0; /*0x7258aa*/
    v173 = 0; /*0x7258b5*/
    v181 = 1065353216; /*0x7258c0*/
    v171 = 0; /*0x7258cb*/
    v172 = 0; /*0x7258d6*/
    v175 = 1065353216; /*0x7258e1*/
    v167 = 800; /*0x7258ec*/
    v176 = 1065353216; /*0x7258f6*/
  }
  v153 = a4; /*0x72590e*/
  PLmemcpy(a5, a4, 18048); /*0x725916*/
  v145 = 0; /*0x725922*/
  if ( unk_337E2E0 )
  {
    v16 = *(_DWORD *)(unk_337E2E0 + 24LL); /*0x725932*/
    if ( v16 > 1 || v16 == -2 )
    {
      Com_Printf(25, (unsigned int)"%3i: playerstate\n", *((_DWORD *)a2 + 9), v13, v14, v15);
      v145 = 1; /*0x725956*/
    }
  }
  Bit = MSG_ReadBit(a2); /*0x72596c*/
  v138 = MSG_ReadBit(a2); /*0x725978*/
  v157 = MSG_ReadBit(a2); /*0x725981*/
  v150 = a3; /*0x72598c*/
  if ( v157 ) /*0x72598a*/
    v142 = 0; /*0x725994*/
  else
    v142 = (unsigned int)MSG_ReadBit(a2) != 0; /*0x7259b3*/
  v18 = *((_DWORD *)g_netFieldList + 14); /*0x7259cc*/
  v156 = g_netFieldList[6]; /*0x7259d8*/
  v19 = 32 - __lzcnt(v18 + 1); /*0x7259e7*/
  *(double *)_XMM0.m128_u64 = MSG_ReadBits(a2, v19); /*0x7259e9*/
  v24 = v20; /*0x7259ee*/
  if ( v20 >= v18 + 1 ) /*0x7259f4*/
  {
    v25 = va((unsigned int)"lastChanged was %i, totalFields is %i\n", v20, v18 + 1, v21, v22, v23); /*0x725a05*/
    v19 = 1001; /*0x725a22*/
    MyAssertHandler( /*0x725a31*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
      1001,
      0,
      (unsigned int)"%s\n\t%s",
      (unsigned int)"lastChanged < totalFields",
      v25);
  }
  v151 = v24 - 1; /*0x725a3a*/
  if ( v24 - 1 <= -2 ) /*0x725a44*/
  {
    v19 = 2869; /*0x725a5b*/
    MyAssertHandler( /*0x725a64*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
      2869,
      0,
      (unsigned int)"%s",
      (unsigned int)"lc >= -1",
      (_BYTE)v23);
  }
  if ( v24 > v18 ) /*0x725a6c*/
  {
    MSG_Discard(a2); /*0x725a71*/
    v26 = 25; /*0x725a84*/
    Com_PrintError(25, (unsigned int)"Got lastChanged field of %i, but there are only %i fields\n", v151, v18, v27, v28); /*0x725a8e*/
    goto LABEL_169; /*0x725a93*/
  }
  v139 = v18; /*0x725a98*/
  _R15 = a5; /*0x725a9d*/
  v30 = a2; /*0x725aa2*/
  v31 = -1; /*0x725aa5*/
  v148 = a2; /*0x725aad*/
  if ( v24 > 0 ) /*0x725ab2*/
  {
    v32 = -1; /*0x725abd*/
    while ( 1 ) /*0x725ad3*/
    {
      v33 = _R15; /*0x725ad3*/
      if ( *(_DWORD *)v30 ) /*0x725ad0*/
        MyAssertHandler( /*0x725af6*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
          2882,
          0,
          (unsigned int)"%s",
          (unsigned int)"!msg->overflowed",
          (_BYTE)v23);
      NumFieldsSkipped = MSG_ReadNumFieldsSkipped((__int64)v30, 4u, v151 - v32); /*0x725b12*/
      v37 = v32 + 1; /*0x725b1b*/
      v152 = NumFieldsSkipped + v32; /*0x725b1f*/
      if ( v32 + 1 < NumFieldsSkipped + v32 ) /*0x725b2a*/
      {
        v38 = &v156[2 * v32 + 2]; /*0x725b42*/
        v34 = NumFieldsSkipped; /*0x725b46*/
        v39 = NumFieldsSkipped - 1; /*0x725b4b*/
        do /*0x725bb8*/
        {
          v40 = *((_WORD *)v38 + 7); /*0x725b50*/
          if ( v157 || (v34 = v40 & 0x1F0, !(_WORD)v34) ) /*0x725b6a*/
          {
            if ( (v40 & 2) == 0 ) /*0x725b92*/
              MSG_CopyFieldOver(v156, v153, v33, v37); /*0x725baa*/
          }
          else
          {
            MSG_SetResetOnSpawnField((unsigned int)v154, v38, *((unsigned __int16 *)v38 + 4) + v33); /*0x725b80*/
          }
          ++v37; /*0x725baf*/
          v38 += 2; /*0x725bb2*/
          --v39; /*0x725bb6*/
        }
        while ( v39 ); /*0x725bb8*/
      }
      v41 = 2LL * v152; /*0x725bc5*/
      if ( Bit ) /*0x725bce*/
        break; /*0x725bce*/
      v42 = HIWORD(v156[v41 + 1]); /*0x725bf8*/
      v43 = (unsigned __int8)(v42 & 4) >> 2; /*0x725c05*/
      LOBYTE(v34) = (v138 == 0) | ((unsigned __int8)(v42 & 4) >> 2); /*0x725c0c*/
      if ( !(_BYTE)v34 ) /*0x725c10*/
        goto LABEL_36; /*0x725c10*/
LABEL_38:
      if ( v152 > v151 ) /*0x725c32*/
      {
        v44 = va((unsigned int)"nextChanged == %i, lc == %i", v152, v151, v34, v35, v36); /*0x725c4c*/
        MyAssertHandler( /*0x725c75*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
          2907,
          0,
          (unsigned int)"%s\n\t%s",
          (unsigned int)"nextChanged <= lc",
          v44);
      }
      if ( NumFieldsSkipped <= 0 ) /*0x725c8d*/
      {
        v45 = va((unsigned int)"nextChanged == %i, lastChanged == %i", v152, v32, v34, v35, v36); /*0x725ca3*/
        MyAssertHandler( /*0x725cd2*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
          2908,
          0,
          (unsigned int)"%s\n\t%s",
          (unsigned int)"nextChanged > lastChanged",
          v45);
      }
      v19 = v150; /*0x725ce0*/
      v46 = (unsigned __int8)(a6 & v43); /*0x725cfa*/
      _R15 = v33; /*0x725cfe*/
      v47 = &v156[v41]; /*0x725d01*/
      MSG_ReadDeltaField((__int64)v148, v150, (__int64)v153, _R15, &v156[v41], v145, _XMM0, _XMM1, a9, v46, v134); /*0x725d0a*/
      v48 = v156; /*0x725d13*/
      if ( v142 && (v156[v41 + 1] & 0x1F0000000000000LL) != 0 && (int)MSG_ReadBit(v148) > 0 ) /*0x725d3f*/
      {
        v19 = (__int64)&v156[v41]; /*0x725d55*/
        MSG_SetResetOnSpawnField((unsigned int)v154, v47, &v159); /*0x725d5b*/
        _RAX = LOWORD(v156[v41 + 1]); /*0x725d60*/
        v50 = WORD1(v156[v41 + 1]); /*0x725d66*/
        __asm { vmovdqu xmm0, xmmword ptr [r15+rax] } /*0x725d6e*/
        v52 = -(unsigned __int16)v50; /*0x725d74*/
        if ( v50 >= 0 ) /*0x725d79*/
          LOBYTE(v52) = v50; /*0x725d79*/
        __asm { vpcmpeqb xmm0, xmm0, [rsp+4C28h+var_4B78] } /*0x725d81*/
        v53 = (1 << v52) - 1; /*0x725d8c*/
        __asm { vpmovmskb ecx, xmm0 } /*0x725d8e*/
        v21 = v53 & _ECX; /*0x725d92*/
        if ( (_DWORD)v21 != v53 ) /*0x725d96*/
        {
          v19 = (__int64)&v159; /*0x725da6*/
          v147 = _RAX + _R15; /*0x725da9*/
          if ( !(unsigned __int8)MSG_ValuesAreEqualPost(_RAX + _R15, &v159, (unsigned int)SWORD2(v156[v41 + 1]), v21) ) /*0x725dae*/
          {
            v55 = (__int16 *)&v156[v41 + 1] + 3; /*0x725dc5*/
            v137 = (__int16 *)&v156[v41 + 1] + 1; /*0x725ddd*/
            ((void (__fastcall *)(__int64, __int64 *, _BYTE *, __int64))MSG_PrintNetFieldValue)(v147, v47, v161, 32); /*0x725de2*/
            ((void (__fastcall *)(__int128 *, __int64 *, _BYTE *, __int64))MSG_PrintNetFieldValue)(&v159, v47, v160, 32); /*0x725e00*/
            v132 = v160; /*0x725e29*/
            Com_PrintError( /*0x725e2d*/
              25,
              (unsigned int)"field %s size %d changedhints %d received value %s != resetvalue %s\n",
              *v47,
              *v137,
              *v55,
              (unsigned int)v161);
            v56 = *v55; /*0x725e3b*/
            _R15 = a5; /*0x725e3f*/
            v57 = va( /*0x725e52*/
                    (unsigned int)"field %s size %d changedhints %d received value %s != resetvalue %s\n",
                    *v47,
                    *v137,
                    v56,
                    (unsigned int)v161,
                    (unsigned int)v160);
            v19 = 2936; /*0x725e5a*/
            MyAssertHandler((unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp", 2936, 0, v57, v58, v59); /*0x725e6a*/
            v48 = v156; /*0x725e6f*/
          }
        }
      }
      v156 = v48; /*0x725e80*/
      v30 = v148; /*0x725e88*/
      if ( *(_DWORD *)v148 ) /*0x725e8d*/
      {
        v19 = 2942; /*0x725e92*/
        MyAssertHandler( /*0x725eb0*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
          2942,
          0,
          (unsigned int)"%s",
          (unsigned int)"!msg->overflowed",
          (_BYTE)v23);
      }
      v31 = v152; /*0x725eb5*/
      v32 = v152; /*0x725ec4*/
      if ( v151 <= v152 ) /*0x725ec7*/
        goto LABEL_53; /*0x725ec7*/
    }
    if ( !v138 ) /*0x725bd5*/
    {
      LOBYTE(v43) = 0; /*0x725c20*/
      goto LABEL_38; /*0x725c20*/
    }
    v42 = HIWORD(v156[v41 + 1]); /*0x725bdf*/
LABEL_36:
    LOBYTE(v43) = (unsigned __int8)(v42 & 8) >> 3; /*0x725c12*/
    goto LABEL_38; /*0x725c1b*/
  }
LABEL_53:
  v149 = v30; /*0x725ecd*/
  if ( v151 != v31 ) /*0x725ed9*/
  {
    v60 = v31; /*0x725edb*/
    v19 = 2944; /*0x725ef3*/
    MyAssertHandler( /*0x725efc*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
      2944,
      0,
      (unsigned int)"%s",
      (unsigned int)"nextChanged == lc",
      (_BYTE)v23);
    v31 = v60; /*0x725f01*/
  }
  v61 = v31 + 1; /*0x725f04*/
  v62 = v31; /*0x725f07*/
  if ( v31 + 1 < v139 ) /*0x725f11*/
  {
    v63 = &v156[2 * v31 + 2]; /*0x725f33*/
    do /*0x725f97*/
    {
      if ( v157 || (*((_WORD *)v63 + 7) & 0x1F0) == 0 ) /*0x725f53*/
      {
        v19 = (__int64)v153; /*0x725f78*/
        MSG_CopyFieldOver(v156, v153, _R15, v61); /*0x725f85*/
      }
      else
      {
        v19 = (__int64)v63; /*0x725f5d*/
        MSG_SetResetOnSpawnField((unsigned int)v154, v63, *((unsigned __int16 *)v63 + 4) + _R15); /*0x725f64*/
      }
      ++v61; /*0x725f8f*/
      v63 += 2; /*0x725f91*/
    }
    while ( v139 != v61 ); /*0x725f97*/
  }
  v64 = v62; /*0x725f99*/
  v65 = v149; /*0x725f9c*/
  v66 = v156; /*0x725fa9*/
  if ( v62 > 0 ) /*0x725fb4*/
  {
    do /*0x725ff1*/
    {
      if ( (*((_BYTE *)v66 + 14) & 2) != 0 ) /*0x725fc4*/
      {
        v19 = v150; /*0x725fc6*/
        MSG_ReadDeltaField((__int64)v149, v150, (__int64)v153, _R15, v66, v145, _XMM0, _XMM1, a9, 0, v134); /*0x725fe5*/
      }
      v66 += 2; /*0x725fea*/
      --v64; /*0x725fee*/
    }
    while ( v64 ); /*0x725ff1*/
  }
  if ( Bit ) /*0x725ff8*/
  {
    if ( !unk_337EDB8 ) /*0x726009*/
      MyAssertHandler( /*0x726029*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../client_mp/client_mp.h",
        1184,
        0,
        (unsigned int)"%s",
        (unsigned int)"clients",
        (_BYTE)v23);
    v67 = unk_337EDB0[0]; /*0x72603a*/
    if ( unk_337EDB0[0] <= a1 ) /*0x726040*/
      MyAssertHandler( /*0x72605c*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../client_mp/client_mp.h",
        1186,
        0,
        (unsigned int)"localClientNum doesn't index MAX_LOCAL_CLIENTS\n\t%i not in [0, %i)",
        a1,
        LOBYTE(unk_337EDB0[0]));
    v68 = unk_337EDB8; /*0x72606a*/
    if ( *(_BYTE *)(unk_337EDB8 + 70528 * v135 + 18828) ) /*0x72606d*/
    {
      MyAssertHandler( /*0x726095*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../client_mp/client_mp.h",
        1187,
        0,
        (unsigned int)"%s",
        (unsigned int)"clients[localClientNum].alwaysFalse == false",
        v67);
      v68 = unk_337EDB8; /*0x72609a*/
    }
    v19 = *(unsigned int *)(_R15 + 76); /*0x72609d*/
    if ( !(unsigned int)CL_GetPredictedPlayerInformationForServerTime(70528 * v135 + v68, v19, _R15) ) /*0x7260a7*/
    {
      v19 = (__int64)"Unable to find the origin we sent, delta is not going to work\n"; /*0x7260b4*/
      Com_PrintError( /*0x7260c2*/
        25,
        (unsigned int)"Unable to find the origin we sent, delta is not going to work\n",
        v69,
        v21,
        v70,
        v23);
      *(_DWORD *)(_R15 + 116) = *((_DWORD *)v153 + 29); /*0x7260cc*/
      *(_DWORD *)(_R15 + 120) = *((_DWORD *)v153 + 30); /*0x7260d5*/
      *(_DWORD *)(_R15 + 124) = *((_DWORD *)v153 + 31); /*0x7260de*/
      *(_DWORD *)(_R15 + 128) = *((_DWORD *)v153 + 32); /*0x7260ea*/
      *(_DWORD *)(_R15 + 132) = *((_DWORD *)v153 + 33); /*0x7260f9*/
      *(_DWORD *)(_R15 + 136) = *((_DWORD *)v153 + 34); /*0x726108*/
      *(_BYTE *)(_R15 + 14) = v153[14]; /*0x726114*/
      *(_DWORD *)(_R15 + 196) = *((_DWORD *)v153 + 49); /*0x726120*/
    }
  }
  else
  {
    __asm { vxorps xmm1, xmm1, xmm1 } /*0x726133*/
    _RAX = unk_BA57FD0; /*0x726137*/
    __asm /*0x72613a*/
    {
      vmovss xmm0, dword ptr [rax+18h]
      vucomiss xmm0, xmm1
    }
  }
  if ( !v138 && *(_WORD *)(_R15 + 216) != 2047 ) /*0x7262f5*/
  {
    if ( !unk_337EDB8 ) /*0x726306*/
      MyAssertHandler( /*0x726326*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../client_mp/client_mp.h",
        1184,
        0,
        (unsigned int)"%s",
        (unsigned int)"clients",
        (_BYTE)v23);
    _R14 = v153; /*0x726337*/
    v73 = unk_337EDB0[0]; /*0x72633a*/
    if ( unk_337EDB0[0] <= a1 ) /*0x726340*/
      MyAssertHandler( /*0x72635c*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../client_mp/client_mp.h",
        1186,
        0,
        (unsigned int)"localClientNum doesn't index MAX_LOCAL_CLIENTS\n\t%i not in [0, %i)",
        a1,
        LOBYTE(unk_337EDB0[0]));
    v74 = unk_337EDB8; /*0x726361*/
    v75 = _R15; /*0x72636d*/
    v76 = _R15 + 216; /*0x726370*/
    v77 = v75; /*0x726377*/
    if ( *(_BYTE *)(unk_337EDB8 + 70528 * v135 + 18828) ) /*0x72637a*/
    {
      MyAssertHandler( /*0x7263a2*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../client_mp/client_mp.h",
        1187,
        0,
        (unsigned int)"%s",
        (unsigned int)"clients[localClientNum].alwaysFalse == false",
        v73);
      v74 = unk_337EDB8; /*0x7263ae*/
    }
    v19 = *(unsigned int *)(v77 + 76); /*0x7263b1*/
    v78 = v76; /*0x7263b6*/
    _R15 = v77; /*0x7263bc*/
    if ( !(unsigned int)CL_GetPredictedVehicleForServerTime(70528 * v135 + v74, v19, v78, v21) ) /*0x7263bf*/
    {
      *(_DWORD *)(v77 + 220) = *((_DWORD *)v153 + 55); /*0x7263d3*/
      *(_DWORD *)(v77 + 228) = *((_DWORD *)v153 + 57); /*0x7263e1*/
      *(_DWORD *)(v77 + 232) = *((_DWORD *)v153 + 58); /*0x7263ef*/
      *(_DWORD *)(v77 + 236) = *((_DWORD *)v153 + 59); /*0x7263fd*/
      *(_DWORD *)(v77 + 240) = *((_DWORD *)v153 + 60); /*0x72640b*/
      *(_DWORD *)(v77 + 244) = *((_DWORD *)v153 + 61); /*0x726419*/
      *(_DWORD *)(v77 + 248) = *((_DWORD *)v153 + 62); /*0x726427*/
      *(_DWORD *)(v77 + 252) = *((_DWORD *)v153 + 63); /*0x726435*/
      *(_DWORD *)(v77 + 256) = *((_DWORD *)v153 + 64); /*0x726443*/
      *(_DWORD *)(v77 + 260) = *((_DWORD *)v153 + 65); /*0x726451*/
      *(_DWORD *)(v77 + 264) = *((_DWORD *)v153 + 66); /*0x72645f*/
      *(_DWORD *)(v77 + 268) = *((_DWORD *)v153 + 67); /*0x72646d*/
      *(_DWORD *)(v77 + 272) = *((_DWORD *)v153 + 68); /*0x72647b*/
      *(_DWORD *)(v77 + 276) = *((_DWORD *)v153 + 69); /*0x726489*/
      *(_DWORD *)(v77 + 280) = *((_DWORD *)v153 + 70); /*0x726497*/
      *(_DWORD *)(v77 + 284) = *((_DWORD *)v153 + 71); /*0x7264a5*/
      *(_DWORD *)(v77 + 288) = *((_DWORD *)v153 + 72); /*0x7264b3*/
      *(_DWORD *)(v77 + 292) = *((_DWORD *)v153 + 73); /*0x7264c1*/
      *(_DWORD *)(v77 + 296) = *((_DWORD *)v153 + 74); /*0x7264cf*/
      *(_DWORD *)(v77 + 300) = *((_DWORD *)v153 + 75); /*0x7264dd*/
      *(_DWORD *)(v77 + 304) = *((_DWORD *)v153 + 76); /*0x7264eb*/
      *(_DWORD *)(v77 + 308) = *((_DWORD *)v153 + 77); /*0x7264f9*/
      *(_DWORD *)(v77 + 312) = *((_DWORD *)v153 + 78); /*0x726507*/
      *(_DWORD *)(v77 + 316) = *((_DWORD *)v153 + 79); /*0x726515*/
      *(_WORD *)(v77 + 320) = *((_WORD *)v153 + 160); /*0x726524*/
      *(_WORD *)(v77 + 322) = *((_WORD *)v153 + 161); /*0x726534*/
      *(_WORD *)(v77 + 324) = *((_WORD *)v153 + 162); /*0x726544*/
      *(_WORD *)(v77 + 224) = *((_WORD *)v153 + 112); /*0x726554*/
      __asm /*0x72655c*/
      {
        vmovups xmm0, xmmword ptr [r14+148h]
        vmovups xmmword ptr [r15+148h], xmm0
      }
    }
  }
  if ( (unsigned int)MSG_ReadBit(v149) ) /*0x726571*/
  {
    if ( unk_337E2E0 && *(_DWORD *)(unk_337E2E0 + 24LL) == 5 ) /*0x726591*/
      Com_Printf(25, (unsigned int)"%s ", (unsigned int)"PS_STATS", v79, v80, v81); /*0x7265a8*/
    v19 = 4; /*0x7265ad*/
    *(double *)_XMM0.m128_u64 = MSG_ReadBits(v149, 4); /*0x7265b5*/
    v83 = v82; /*0x7265ba*/
    if ( (v82 & 1) != 0 ) /*0x7265bf*/
      *(_DWORD *)(_R15 + 472) = MSG_ReadShort( /*0x7265c9*/
                                  v149,
                                  4,
                                  *(double *)_XMM0.m128_u64,
                                  *(double *)_XMM1.m128_u64,
                                  *(double *)a9.m128_u64);
    if ( (v83 & 2) != 0 ) /*0x7265d3*/
      *(_DWORD *)(_R15 + 476) = MSG_ReadShort( /*0x7265dd*/
                                  v149,
                                  4,
                                  *(double *)_XMM0.m128_u64,
                                  *(double *)_XMM1.m128_u64,
                                  *(double *)a9.m128_u64);
    if ( (v83 & 4) != 0 ) /*0x7265e7*/
      *(_DWORD *)(_R15 + 480) = MSG_ReadShort( /*0x7265f1*/
                                  v149,
                                  4,
                                  *(double *)_XMM0.m128_u64,
                                  *(double *)_XMM1.m128_u64,
                                  *(double *)a9.m128_u64);
    if ( (v83 & 8) != 0 ) /*0x7265fb*/
    {
      *(double *)_XMM0.m128_u64 = MSG_ReadByte(v149); /*0x726600*/
      *(_DWORD *)(_R15 + 484) = v84; /*0x726605*/
    }
  }
  while ( (unsigned int)MSG_ReadBit(v149) ) /*0x72662f*/
  {
    MSG_ReadBits(v149, 4); /*0x726639*/
    v87 = v86; /*0x726646*/
    MSG_ReadBits(v149, 1); /*0x726649*/
    v19 = 31; /*0x72664e*/
    v89 = v88; /*0x726656*/
    *(double *)_XMM0.m128_u64 = MSG_ReadBits(v149, 31); /*0x726658*/
    v90 = v89 == 0; /*0x72665d*/
    v91 = 3 * v87; /*0x72665f*/
    *(_DWORD *)(_R15 + 8 * v91 + 1448) = v92; /*0x726666*/
    *(_BYTE *)(_R15 + 8 * v91 + 1452) = !v90; /*0x72666e*/
    if ( (unsigned int)MSG_ReadBit(v149) ) /*0x726677*/
    {
      v19 = 8; /*0x726680*/
      *(double *)_XMM0.m128_u64 = MSG_ReadBits(v149, 8); /*0x726688*/
      *(_DWORD *)(_R15 + 24 * v87 + 1456) = v93; /*0x72668d*/
    }
    if ( (unsigned int)MSG_ReadBit(v149) ) /*0x726698*/
    {
      v19 = 8; /*0x726610*/
      *(double *)_XMM0.m128_u64 = MSG_ReadBits(v149, 8); /*0x726618*/
      *(_DWORD *)(_R15 + 24 * v87 + 1460) = v85; /*0x72661d*/
    }
  }
  v141 = (_DWORD *)_R15; /*0x7266ad*/
  if ( (unsigned int)MSG_ReadBit(v149) ) /*0x7266b2*/
  {
    v155 = v154 + 1; /*0x7266c4*/
    _R15 = 0; /*0x7266cb*/
    _RBX = v141 + 198; /*0x7266ce*/
    v96 = v141 + 183; /*0x7266d5*/
    do /*0x726a1f*/
    {
      if ( (unsigned int)MSG_ReadBit(v65) ) /*0x7266e3*/
      {
        if ( v157 || (unsigned int)MSG_ReadBit(v65) ) /*0x7266fd*/
        {
          if ( (unsigned int)MSG_ReadBit(v65) ) /*0x72670d*/
          {
            MSG_ReadBits(v65, 31); /*0x726722*/
            *v96 = v97; /*0x72672e*/
            if ( (!unk_8341190 || !*(_BYTE *)(unk_8341190 + 24LL)) /*0x726825*/
              && v141[183] != v97
              && v141[184] != v97
              && v141[185] != v97
              && v141[186] != v97
              && v141[187] != v97
              && v141[188] != v97
              && v141[189] != v97
              && v141[190] != v97
              && v141[191] != v97
              && v141[192] != v97
              && v141[193] != v97
              && v141[194] != v97
              && v141[195] != v97
              && v141[196] != v97
              && v141[197] != v97 )
            {
              MyAssertHandler( /*0x726845*/
                (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
                3126,
                0,
                (unsigned int)"%s",
                (unsigned int)"equippedWeapon",
                v98);
            }
          }
          LOBYTE(_RBX[_R15]) = (int)MSG_ReadBit(v65) > 0; /*0x72685d*/
          BYTE1(_RBX[_R15]) = (int)MSG_ReadBit(v65) > 0; /*0x72686c*/
          BYTE2(_RBX[_R15]) = (int)MSG_ReadBit(v65) > 0; /*0x72687c*/
          HIBYTE(_RBX[_R15]) = (int)MSG_ReadBit(v65) > 0; /*0x726889*/
          if ( v157 ) /*0x726897*/
          {
            LOBYTE(_RBX[_R15 + 1]) = (int)MSG_ReadBit(v65) > 0; /*0x7268a6*/
            v99 = (int)MSG_ReadBit(v65) > 0; /*0x7268b3*/
          }
          else
          {
            v99 = 0; /*0x7268c0*/
            LOBYTE(_RBX[_R15 + 1]) = 0; /*0x7268c2*/
          }
          BYTE1(_RBX[_R15 + 1]) = v99; /*0x7268cb*/
          v19 = 2; /*0x7268d7*/
          BYTE2(_RBX[_R15 + 1]) = (int)MSG_ReadBit(v65) > 0; /*0x7268df*/
          *(double *)_XMM0.m128_u64 = MSG_ReadBits(v65, 2); /*0x7268e5*/
          _RBX[_R15 + 2] = v100; /*0x7268ed*/
          LOBYTE(_RBX[_R15 + 3]) = (int)MSG_ReadBit(v65) > 0; /*0x7268fc*/
          BYTE1(_RBX[_R15 + 3]) = (int)MSG_ReadBit(v65) > 0; /*0x726909*/
          if ( v157 ) /*0x726917*/
          {
            MSG_ReadShort(v65, 2, *(double *)_XMM0.m128_u64, *(double *)_XMM1.m128_u64, *(double *)a9.m128_u64); /*0x72691c*/
            __asm /*0x726921*/
            {
              vcvtsi2ss xmm0, xmm0, eax
              vmulss xmm0, xmm0, cs:dword_F9B8B8
            }
            __asm { vmovss dword ptr [rbx+r15+10h], xmm0 }
            Long = MSG_ReadLong(v65, 2, v102); /*0x726937*/
          }
          else
          {
            Long = 0; /*0x726940*/
            _RBX[_R15 + 4] = 0; /*0x726942*/
          }
          _RBX[_R15 + 5] = Long; /*0x72694b*/
          LOBYTE(_RBX[_R15 + 6]) = v155; /*0x72695a*/
          v104 = MSG_ReadBit(v65); /*0x72695f*/
          if ( v157 ) /*0x72696c*/
          {
            if ( !v104 ) /*0x726970*/
            {
              *(double *)_XMM0.m128_u64 = MSG_ReadByte(v65); /*0x726979*/
              LOBYTE(_RBX[_R15 + 6]) = v105; /*0x7269a5*/
              v65 = v149; /*0x7269aa*/
              if ( v105 >= 19 ) /*0x7269b2*/
              {
                v19 = 3174; /*0x7269b8*/
                MyAssertHandler( /*0x7269d9*/
                  (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
                  3174,
                  0,
                  (unsigned int)"%s\n\t(to->weapEquippedData[equippedWeaponIndex].ownerOriginal) = %i",
                  (unsigned int)"(to->weapEquippedData[equippedWeaponIndex].ownerOriginal <= 18)",
                  v105);
              }
            }
          }
          else if ( !v104 ) /*0x7269e2*/
          {
            LOBYTE(_RBX[_R15 + 6]) = 0; /*0x7269e4*/
          }
        }
        else
        {
          __asm { vxorps xmm0, xmm0, xmm0 } /*0x7269ec*/
          *v96 = 0; /*0x7269f0*/
          __asm /*0x7269f8*/
          {
            vmovups xmmword ptr [rbx+r15+0Ch], xmm0
            vmovups xmmword ptr [rbx+r15], xmm0
          }
        }
      }
      _R15 += 7; /*0x726a10*/
      ++v96; /*0x726a14*/
    }
    while ( _R15 != 105 ); /*0x726a1f*/
  }
  v106 = (unsigned int)v141[307]; /*0x726a2a*/
  if ( (_BYTE)v106 /*0x726b10*/
    && (!unk_8341190 || !*(_BYTE *)(unk_8341190 + 24LL))
    && v141[183] != (_DWORD)v106
    && v141[184] != (_DWORD)v106
    && v141[185] != (_DWORD)v106
    && v141[186] != (_DWORD)v106
    && v141[187] != (_DWORD)v106
    && v141[188] != (_DWORD)v106
    && v141[189] != (_DWORD)v106
    && v141[190] != (_DWORD)v106
    && v141[191] != (_DWORD)v106
    && v141[192] != (_DWORD)v106
    && v141[193] != (_DWORD)v106
    && v141[194] != (_DWORD)v106
    && v141[195] != (_DWORD)v106
    && v141[196] != (_DWORD)v106
    && v141[197] != (_DWORD)v106 )
  {
    WeaponName = BG_GetWeaponName(v106, v218, 1024); /*0x726b23*/
    v111 = va( /*0x726b37*/
             (unsigned int)"Player thinks their current weapon is %s but we don't have that weapon equipped",
             WeaponName,
             v108,
             WeaponName,
             v109,
             v110);
    v19 = 3193; /*0x726b54*/
    MyAssertHandler( /*0x726b63*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
      3193,
      0,
      (unsigned int)"%s\n\t%s",
      (unsigned int)"to->weapCommon.weapon.weaponIdx == WP_NONE || BG_GetEquippedWeaponState( to, to->weapCommon.weapon )",
      v111);
  }
  while ( (unsigned int)MSG_ReadBit(v65) ) /*0x726bd5*/
  {
    MSG_ReadBits(v65, 4); /*0x726b78*/
    v113 = v112; /*0x726b85*/
    MSG_ReadBits(v65, 1); /*0x726b88*/
    v115 = v114; /*0x726b95*/
    MSG_ReadBits(v65, 31); /*0x726b97*/
    v90 = v115 == 0; /*0x726b9f*/
    v19 = 10; /*0x726ba1*/
    v116 = 3LL * v113; /*0x726ba9*/
    v141[v116 + 317] = v117; /*0x726bad*/
    LOBYTE(v141[v116 + 318]) = !v90; /*0x726bb5*/
    *(double *)_XMM0.m128_u64 = MSG_ReadBits(v65, 10); /*0x726bbe*/
    v141[3 * v113 + 319] = v118; /*0x726bc3*/
  }
  v119 = v65; /*0x726bdf*/
  if ( (unsigned int)MSG_ReadBit(v65) ) /*0x726bda*/
  {
    v120 = 0; /*0x726bf6*/
    v121 = v141 + 2015; /*0x726bfb*/
    v122 = g_netFieldList[8]; /*0x726c05*/
    v158 = *((_DWORD *)g_netFieldList + 18); /*0x726c09*/
    do /*0x726c6f*/
    {
      *(double *)_XMM0.m128_u64 = MSG_ReadBits(v119, 3); /*0x726c28*/
      v19 = v150; /*0x726c2d*/
      v121[v120] = v123; /*0x726c4b*/
      MSG_ReadDeltaFields( /*0x726c5f*/
        (_DWORD)v119,
        v150,
        (_DWORD)v153 + 8060 + v120 * 4,
        (_DWORD)v121 + v120 * 4,
        v158,
        (_DWORD)v122,
        1,
        0);
      v120 += 9; /*0x726c64*/
    }
    while ( v120 != 288 ); /*0x726c6f*/
  }
  v124 = v119; /*0x726c71*/
  v125 = (__int64)v119; /*0x726c86*/
  if ( (unsigned int)MSG_ReadBit(v119) ) /*0x726c74*/
  {
    MSG_ReadDeltaHudElems(v119, v150, v153 + 14504, v141 + 3626, 15, 4, v132); /*0x726ccb*/
    v124 = v119; /*0x726ce4*/
    v19 = v150; /*0x726ce7*/
    *(double *)_XMM0.m128_u64 = MSG_ReadDeltaHudElems(v119, v150, v153 + 9224, v141 + 2306, 30, 5, v133); /*0x726ced*/
  }
  v126 = Omnvar_PerPlayerstateCount(v124); /*0x726d05*/
  v127 = Omnvar_PerPlayerstateMinBitsForIndex( /*0x726d0d*/
           *(double *)_XMM0.m128_u64,
           *(double *)_XMM1.m128_u64,
           *(double *)a9.m128_u64);
  v130 = Omnvar_PerSnapCount(v124, v19, v128, v129); /*0x726d10*/
  v26 = v125; /*0x726d1c*/
  MSG_ReadDeltaOmnvars_Internal(v125, v150, v126, v127, (_DWORD)v153 + 17144, (_DWORD)v141 + 17144, v130); /*0x726d2e*/
LABEL_169:
  result = *(_QWORD *)COMMON; /*0x726d33*/
  if ( *(_QWORD *)COMMON != v219 ) /*0x726d45*/
  {
    PL__stack_chk_fail(*(double *)_XMM0.m128_u64, *(double *)_XMM1.m128_u64, *(double *)a9.m128_u64); /*0x726d56*/
    return MSG_InitBaselinePlayerState(v26); /*0x726d5d*/
  }
  return result; /*0x726d47*/
}