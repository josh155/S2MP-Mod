char __fastcall MSG_WriteDeltaField(
        int *a1,
        __int64 a2,
        unsigned int a3,
        __int64 a4,
        __int64 a5,
        __int64 *a6,
        __m128 _XMM0,
        __m128 _XMM1,
        __m128 _XMM2,
        double a10,
        double a11,
        double a12,
        __m128 _XMM6,
        int a14,
        char a15,
        char a16,
        int a17,
        unsigned int a18,
        char a19,
        char a20)
{
  __int64 v20; // r15
  __int64 *v21; // r10
  __int64 v23; // r12
  char v25; // dl
  __int64 v26; // r12
  __int64 v27; // r13
  __int64 *v28; // rbx
  unsigned __int8 *v30; // rcx
  __int64 v31; // rdx
  int v32; // ebx
  int v34; // eax
  int v36; // ecx
  int v37; // edx
  char v39; // bl
  __int64 *v40; // rbx
  char v41; // al
  unsigned __int8 v42; // al
  int v43; // r14d
  __int64 v44; // rbx
  int *v45; // r13
  int EntityTypeString; // eax
  int v47; // edx
  int v48; // r9d
  bool v49; // cc
  int v50; // ebx
  int *v51; // r15
  __int64 *v52; // r14
  int *v53; // r13
  __int64 v54; // r8
  __int64 v55; // rcx
  unsigned int v56; // r15d
  const char *v57; // rbx
  int v58; // r14d
  char v59; // r15
  bool v60; // zf
  bool v61; // pf
  unsigned int v62; // r13d
  int *v63; // rbx
  int *v64; // r14
  __int64 *v65; // rbx
  int v66; // eax
  int v67; // r8d
  int v68; // r9d
  unsigned int v69; // ebx
  int v70; // eax
  __int64 *v71; // r14
  int *v73; // r12
  __int64 v74; // r9
  int *v75; // rdx
  __int64 v76; // rcx
  __int64 v77; // r8
  __int64 v79; // rax
  unsigned int v80; // ebx
  int v81; // ecx
  __int64 v82; // rcx
  __int64 v83; // r8
  unsigned int *v84; // r15
  int v94; // r14d
  int v95; // r13d
  unsigned int v96; // r12d
  unsigned int v102; // r14d
  int v103; // ebx
  int v104; // ebx
  unsigned int v105; // r15d
  __int64 v106; // rcx
  __int64 v107; // r8
  __int64 v108; // rdx
  int v109; // r15d
  int v110; // r12d
  __int64 v111; // rdx
  __int64 v112; // r9
  __int64 *v113; // r15
  unsigned __int64 v114; // r12
  const char *v115; // r8
  int v116; // esi
  unsigned int v117; // r15d
  __int64 v123; // rcx
  unsigned __int8 v125; // al
  const char *v126; // r12
  char v143; // cf
  bool v144; // zf
  bool v145; // r14
  int v147; // eax
  int *v149; // r13
  int v152; // eax
  int v154; // eax
  int v159; // eax
  int v162; // eax
  const char *v167; // r14
  int v168; // eax
  int v169; // eax
  int v170; // r12d
  int v171; // ebx
  int v172; // eax
  __int64 v173; // rcx
  __int64 v174; // r8
  int v175; // ebx
  __int64 *v176; // r13
  unsigned int v177; // r12d
  int v178; // eax
  __int64 v179; // rcx
  __int64 v180; // r8
  __int64 v181; // rdx
  int v182; // r12d
  int v183; // r13d
  unsigned int *v184; // r15
  __int64 v185; // rcx
  __int64 v186; // r8
  _DWORD *v187; // r15
  __int64 v188; // rcx
  __int64 v189; // r8
  __int64 *v190; // r14
  int *v191; // r14
  int v192; // r12d
  bool v193; // zf
  bool v194; // pf
  unsigned int v197; // ebx
  int v198; // r14d
  __int64 v199; // rcx
  __int64 v200; // r8
  int *v201; // rbx
  int v202; // eax
  unsigned __int8 *v203; // rbx
  __int64 v204; // rcx
  __int64 v205; // r8
  int *v206; // r14
  __int64 v207; // rcx
  __int64 v208; // r8
  unsigned int MinBitCountForNum; // eax
  __int64 v213; // rcx
  __int64 v214; // r8
  int v215; // edx
  int v216; // ecx
  int v217; // r8d
  int v218; // r9d
  int v219; // eax
  int v221; // eax
  bool v224; // pf
  int v225; // eax
  int v226; // edx
  int v227; // ecx
  int v228; // r8d
  int v229; // r9d
  int v230; // eax
  int v231; // eax
  int v234; // eax
  int v236; // eax
  int v237; // edx
  int v238; // ecx
  int v239; // r8d
  int v240; // r9d
  int v241; // eax
  int v242; // r9d
  const char *v243; // r8
  unsigned int v244; // r13d
  int *v245; // r12
  int v246; // r12d
  __int64 v247; // rcx
  __int64 v248; // r8
  __int64 v249; // rdx
  __int64 v250; // rcx
  __int64 v251; // r8
  int v252; // r9d
  int v253; // edx
  int v254; // ecx
  int v255; // r8d
  int v256; // r9d
  __int64 v258; // rdx
  int v259; // [rsp+8h] [rbp-88h]
  int *v260; // [rsp+8h] [rbp-88h]
  int *v261; // [rsp+8h] [rbp-88h]
  int *v262; // [rsp+10h] [rbp-80h]
  int *v263; // [rsp+10h] [rbp-80h]
  __int64 *v264; // [rsp+18h] [rbp-78h]
  __int64 *v265; // [rsp+18h] [rbp-78h]
  __int64 *v266; // [rsp+18h] [rbp-78h]
  __int64 v268; // [rsp+20h] [rbp-70h]
  __int64 v269; // [rsp+28h] [rbp-68h]
  char v270; // [rsp+28h] [rbp-68h]
  unsigned __int8 *v271; // [rsp+30h] [rbp-60h]
  unsigned int v275; // [rsp+30h] [rbp-60h]
  __int64 v279; // [rsp+40h] [rbp-50h]
  const char *v281; // [rsp+50h] [rbp-40h]
  __int64 v282; // [rsp+50h] [rbp-40h]
  int v287; // [rsp+5Ch] [rbp-34h] BYREF
  __int64 v288; // [rsp+60h] [rbp-30h]

  v20 = a2; /*0x73fbbf*/
  v21 = a6; /*0x73fbc2*/
  v288 = *(_QWORD *)COMMON; /*0x73fbcb*/
  if ( *(_DWORD *)(a2 + 4) ) /*0x73fbcf*/
  {
    v23 = a4; /*0x73fbd6*/
    a2 = 1931; /*0x73fbee*/
    MyAssertHandler( /*0x73fbfa*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
      1931,
      0,
      (unsigned int)"%s",
      (unsigned int)"!msg->readOnly",
      (_DWORD)a6);
    a4 = v23; /*0x73fbff*/
    v21 = a6; /*0x73fc02*/
  }
  v25 = a16; /*0x73fc05*/
  v26 = *((unsigned __int16 *)v21 + 4); /*0x73fc08*/
  if ( !a4 ) /*0x73fc10*/
  {
    v27 = *((unsigned __int16 *)v21 + 4); /*0x73fc12*/
    a2 = 1935; /*0x73fc2d*/
    v28 = v21; /*0x73fc36*/
    MyAssertHandler( /*0x73fc39*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
      1935,
      0,
      (unsigned int)"%s",
      (unsigned int)"from",
      (_DWORD)a6);
    v25 = a16; /*0x73fc3e*/
    a4 = 0; /*0x73fc41*/
    v26 = v27; /*0x73fc44*/
    v21 = v28; /*0x73fc47*/
  }
  _RDI = a4 + v26; /*0x73fc4d*/
  v269 = a4; /*0x73fc51*/
  v30 = (unsigned __int8 *)(a4 + v26); /*0x73fc57*/
  if ( !v25 ) /*0x73fc5a*/
  {
    v30 = (unsigned __int8 *)&v287; /*0x73fc5c*/
    v287 = 0; /*0x73fc60*/
  }
  v31 = a5; /*0x73fc67*/
  v32 = a14; /*0x73fc6b*/
  v271 = v30; /*0x73fc6e*/
  _R8 = (int *)(a5 + v26); /*0x73fc74*/
  if ( a19 ) /*0x73fc78*/
  {
    if ( !a15 ) /*0x73fc83*/
    {
      v34 = *((__int16 *)v21 + 5); /*0x73fc85*/
      __asm { vmovdqu xmm0, xmmword ptr [rdi] } /*0x73fc8a*/
      __asm { vpcmpeqb xmm0, xmm0, xmmword ptr [r8] }
      v36 = -v34; /*0x73fc9a*/
      if ( v34 >= 0 ) /*0x73fc9e*/
        LOBYTE(v36) = v34; /*0x73fc9e*/
      v37 = (1 << v36) - 1; /*0x73fca3*/
      __asm { vpmovmskb ecx, xmm0 } /*0x73fca5*/
      if ( (v37 & _ECX) == v37 ) /*0x73fcad*/
      {
        v39 = 0; /*0x73fcaf*/
        goto LABEL_73; /*0x73fcb1*/
      }
      a2 = a5 + v26; /*0x73fcbb*/
      v40 = v21; /*0x73fcc3*/
      v41 = MSG_ValuesAreEqualPost(_RDI, a5 + v26, (unsigned int)*((__int16 *)v21 + 6), (unsigned int)v34); /*0x73fcc6*/
      v21 = v40; /*0x73fccb*/
      v32 = a14; /*0x73fcce*/
      _R8 = (int *)(a5 + v26); /*0x73fcd1*/
      if ( v41 ) /*0x73fcd6*/
      {
        v39 = 0; /*0x73fcd8*/
        goto LABEL_73; /*0x73fcda*/
      }
    }
    v281 = (const char *)v20; /*0x73fcdf*/
    if ( (*((_BYTE *)v21 + 14) & 1) != 0 && (a1[30] > 20 || *(_DWORD *)(v269 + 4) == *(_DWORD *)(a5 + 4)) ) /*0x73fd05*/
    {
      v42 = *((_BYTE *)a1 + 28); /*0x73fd07*/
      if ( v32 || !v42 ) /*0x73fd11*/
      {
        v262 = a1; /*0x73fd13*/
        v43 = v32; /*0x73fd17*/
        v44 = *v21; /*0x73fd1a*/
        v45 = _R8; /*0x73fd20*/
        v264 = v21; /*0x73fd23*/
        v259 = v42; /*0x73fd27*/
        EntityTypeString = SV_GetEntityTypeString(); /*0x73fd2d*/
        v47 = v44; /*0x73fd39*/
        v32 = v43; /*0x73fd3c*/
        a1 = v262; /*0x73fd3f*/
        a2 = (__int64)"Field %s changed for eType %s when we thought it never would (baseline = %d)\n"; /*0x73fd46*/
        Com_PrintError( /*0x73fd54*/
          15,
          (unsigned int)"Field %s changed for eType %s when we thought it never would (baseline = %d)\n",
          v47,
          EntityTypeString,
          v259,
          v48);
        v21 = v264; /*0x73fd59*/
        _R8 = v45; /*0x73fd5d*/
      }
    }
    v49 = v32 <= a17; /*0x73fd64*/
    v50 = v32 - a17; /*0x73fd64*/
    v263 = a1; /*0x73fd67*/
    if ( v49 ) /*0x73fd6b*/
    {
      v51 = _R8; /*0x73fd6d*/
      a2 = 1431; /*0x73fd85*/
      v52 = v21; /*0x73fd94*/
      MyAssertHandler( /*0x73fd97*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
        1431,
        0,
        (unsigned int)"%s\n\t(numFieldsSkipped) = %i",
        (unsigned int)"(numFieldsSkipped > 0)",
        v50);
      v21 = v52; /*0x73fd9c*/
      _R8 = v51; /*0x73fd9f*/
    }
    if ( a18 == 1 ) /*0x73fda6*/
    {
      v20 = (__int64)v281; /*0x73fda8*/
      v53 = _R8; /*0x73fdac*/
      v265 = v21; /*0x73fdaf*/
      if ( v50 >= 2 ) /*0x73fdb6*/
      {
        do /*0x73fdcd*/
        {
          MSG_WriteBit0(v281); /*0x73fdc3*/
          --v50; /*0x73fdc8*/
        }
        while ( v50 > 1 ); /*0x73fdcd*/
      }
      _RDI = (__int64)v281; /*0x73fdcf*/
      MSG_WriteBit1(v281); /*0x73fdd2*/
      a1 = v263; /*0x73fdd7*/
      _R8 = v53; /*0x73fddb*/
    }
    else
    {
      v265 = v21; /*0x73fde3*/
      v260 = _R8; /*0x73fde7*/
      if ( v50 == 1 ) /*0x73fdf1*/
      {
        v20 = (__int64)v281; /*0x73fdf3*/
        _RDI = (__int64)v281; /*0x73fdf7*/
        MSG_WriteBit1(v281); /*0x73fdfa*/
      }
      else
      {
        MSG_WriteBit0(v281); /*0x73fe05*/
        LOBYTE(v55) = a18; /*0x73fe10*/
        v56 = v50 - 1; /*0x73fe13*/
        if ( 1 << a18 <= v50 ) /*0x73fe1d*/
        {
          v57 = v281; /*0x73fe25*/
          v58 = (1 << a18) - 1; /*0x73fe29*/
          do /*0x73fe46*/
          {
            MSG_WriteBits(v281, 0xFFFFFFFFLL, a18, v55, v54); /*0x73fe3b*/
            v56 -= v58; /*0x73fe40*/
          }
          while ( (int)v56 >= v58 ); /*0x73fe46*/
        }
        else
        {
          v57 = v281; /*0x73fe1f*/
        }
        _RDI = (__int64)v57; /*0x73fe48*/
        a2 = v56; /*0x73fe4b*/
        MSG_WriteBits(v57, v56, a18, v55, v54); /*0x73fe51*/
        v20 = (__int64)v57; /*0x73fe56*/
      }
      a1 = v263; /*0x73fe59*/
      _R8 = v260; /*0x73fe5d*/
    }
    v21 = v265; /*0x73fe64*/
    v32 = a14; /*0x73fe68*/
  }
  v282 = v20; /*0x73fe6b*/
  v59 = *((_BYTE *)a1 + 29); /*0x73fe6f*/
  v60 = v59 == 0; /*0x73fe73*/
  v61 = __SETP__(v59, 0); /*0x73fe73*/
  if ( !v59 ) /*0x73fe76*/
  {
    v60 = *((_BYTE *)a1 + 28) == 0; /*0x73fe78*/
    v61 = __SETP__(*((_BYTE *)a1 + 28), 0); /*0x73fe78*/
    if ( !*((_BYTE *)a1 + 28) ) /*0x73fe78*/
    {
      v30 = (unsigned __int8 *)*((_QWORD *)a1 + 4); /*0x73fe7f*/
      v60 = *(_DWORD *)&v30[4 * v32] == -1; /*0x73fe86*/
      v61 = __SETP__(++*(_DWORD *)&v30[4 * v32], 0); /*0x73fe86*/
    }
  }
  v62 = *((__int16 *)v21 + 6); /*0x73fe89*/
  v63 = a1; /*0x73fe8e*/
  switch ( *((_WORD *)v21 + 6) )
  {
    case 0xFF92:
      _RDI = v282; /*0x740026*/
      a2 = (__int64)v271; /*0x74002a*/
      MSG_WriteHudData(v282, v271, _R8); /*0x740031*/
      break; /*0x740036*/
    case 0xFF93:
      goto LABEL_41;
    case 0xFF94:
      goto LABEL_59;
    case 0xFF95:
      _RDI = v282; /*0x74003b*/
      a2 = (__int64)v271; /*0x74003f*/
      MSG_WriteAnimData(v282, v271, _R8); /*0x740046*/
      break; /*0x74004b*/
    case 0xFF96:
    case 0xFF97:
    case 0xFF98:
      a2 = v282; /*0x73ffd7*/
      _RDI = (__int64)a1; /*0x73ffdf*/
      MSG_WriteMovingPlatformValidOrigin(a1, v282, v62, v271, _R8); /*0x73ffe5*/
      break; /*0x73ffea*/
    case 0xFF99:
      v79 = *_R8; /*0x740050*/
      if ( v79 > 799 ) /*0x740059*/
        goto LABEL_158; /*0x740059*/
      v80 = (int)v79 / 50; /*0x740071*/
      v81 = 50 * ((int)v79 / 50); /*0x740073*/
      goto LABEL_67; /*0x740076*/
    case 0xFF9A:
      v79 = *_R8; /*0x740078*/
      if ( v79 > 3999 ) /*0x740081*/
        goto LABEL_158; /*0x740081*/
      v80 = (int)v79 / 250; /*0x740099*/
      v81 = 250 * ((int)v79 / 250); /*0x74009b*/
LABEL_67:
      if ( (_DWORD)v79 == v81 ) /*0x7400a3*/
      {
        MSG_WriteBit0(v282); /*0x7400b0*/
        _RDI = v282; /*0x7400ba*/
        a2 = v80; /*0x7400bd*/
        MSG_WriteBits(v282, v80, 4, v82, v83); /*0x7400bf*/
      }
      else
      {
LABEL_158:
        v184 = (unsigned int *)_R8; /*0x74094d*/
        MSG_WriteBit1(v282); /*0x740957*/
        a2 = *v184; /*0x74095c*/
        _RDI = v282; /*0x740964*/
        MSG_WriteBits(v282, a2, 16, v185, v186); /*0x740967*/
      }
      break; /*0x7400c4*/
    case 0xFF9B:
      if ( !*(_WORD *)_R8 ) /*0x7400cb*/
        goto LABEL_71; /*0x7400cb*/
      v84 = (unsigned int *)_R8; /*0x7400d1*/
      MSG_WriteBit1(v282); /*0x7400d7*/
      a2 = *v84; /*0x7400dc*/
      _RDI = v282; /*0x7400df*/
      MSG_WriteShort(v282, a2); /*0x7400e2*/
      break; /*0x7400e7*/
    case 0xFF9C:
      __asm /*0x74011d*/
      {
        vmovss xmm0, cs:dword_FA0C44
        vmovss xmm2, cs:dword_FA0C2C
        vmovss xmm3, dword ptr [r8]
        vmulss xmm1, xmm0, dword ptr [rax]
        vaddss xmm1, xmm1, xmm2
        vroundss xmm1, xmm0, xmm1, 1
        vmulss xmm0, xmm3, xmm0
        vaddss xmm0, xmm0, xmm2
        vcvttss2si eax, xmm1
        vroundss xmm0, xmm0, xmm0, 1
      }
      a2 = (unsigned int)(__int16)_EAX; /*0x740152*/
      __asm { vcvttss2si ecx, xmm0 } /*0x74015c*/
      v94 = (__int16)_ECX - (_DWORD)a2; /*0x740169*/
      v95 = a2 - (__int16)_ECX; /*0x74016f*/
      if ( v95 < 1 ) /*0x740172*/
        v95 = (__int16)_ECX - (_DWORD)a2; /*0x740172*/
      v96 = 0; /*0x740176*/
      if ( g_commonAngleDeltas[0] == v95 /*0x7401d6*/
        || (v96 = 1, (__int16)g_commonAngleDeltas[1] == v95)
        || (v96 = 2, (__int16)g_commonAngleDeltas[2] == v95)
        || (v96 = 3, (__int16)g_commonAngleDeltas[3] == v95)
        || (v96 = 4, (__int16)g_commonAngleDeltas[4] == v95)
        || (v96 = 5, (__int16)g_commonAngleDeltas[5] == v95)
        || (v96 = 6, (__int16)g_commonAngleDeltas[6] == v95) )
      {
        MSG_WriteBit1(v282); /*0x7401e3*/
        if ( v94 < 0 ) /*0x7401ee*/
          MSG_WriteBit1(v282); /*0x740d7d*/
        else
          MSG_WriteBit0(v282); /*0x7401f4*/
        MinBitCountForNum = GetMinBitCountForNum(7); /*0x740d87*/
        _RDI = v282; /*0x740d8c*/
        goto LABEL_259; /*0x740d8f*/
      }
      __asm { vmovss dword ptr [rbp+var_60], xmm3 } /*0x7412ca*/
      v246 = (__int16)_ECX; /*0x7412cf*/
      MSG_WriteBit0(v282); /*0x7412d5*/
      if ( v246 == (_DWORD)a2 || v95 >= 4096 ) /*0x7412e7*/
      {
        if ( !v59 && !*((_BYTE *)v63 + 28) ) /*0x74131a*/
          SV_TrackAngleFullSend(); /*0x741320*/
        MSG_WriteBit0(v282); /*0x74132c*/
        __asm { vmovss xmm0, dword ptr [rbp+var_60] } /*0x741331*/
        _RDI = v282; /*0x741336*/
        MSG_WriteAngle16(v282, _XMM0, a2, v249, v250, v251, v252); /*0x741339*/
        break; /*0x74133e*/
      }
      if ( !v59 && !*((_BYTE *)v63 + 28) ) /*0x7412ee*/
        SV_TrackAngleDeltaBits((unsigned int)v94); /*0x7412f7*/
      MSG_WriteBit1(v282); /*0x741300*/
      if ( v94 < 0 ) /*0x741308*/
        MSG_WriteBit1(v282); /*0x741347*/
      else
        MSG_WriteBit0(v282); /*0x74130e*/
      _RDI = v282; /*0x74134c*/
      a2 = (unsigned int)v95; /*0x741355*/
      *(double *)_XMM0.m128_u64 = MSG_WriteBits(v282, (unsigned int)v95, 12, v247, v248); /*0x741358*/
      __asm /*0x74135d*/
      {
        vcvtsi2ss xmm0, xmm0, r12d
        vmulss xmm0, xmm0, cs:dword_FA0C48
      }
      v39 = 1; /*0x74136a*/
      __asm { vucomiss xmm0, xmm0 } /*0x74136c*/
      if ( v61 ) /*0x741370*/
      {
        __asm { vcvtss2sd xmm0, xmm0, xmm0 } /*0x741376*/
        __asm { vmovapd xmm1, xmm0 }
        v242 = va((unsigned int)"%f != %f", v95, v253, v254, v255, v256); /*0x74138c*/
        _RDI = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp"; /*0x74138f*/
        v243 = "SHORT2ANGLE( newValAsShort ) == SHORT2ANGLE( static_cast<short>( ANGLE2SHORT( fullFloat ) ) )"; /*0x74139d*/
        a2 = 1611; /*0x7413a4*/
        goto LABEL_228; /*0x7413a9*/
      }
      goto LABEL_73; /*0x741370*/
    case 0xFF9D:
      _RAX = v271; /*0x7401fe*/
      __asm /*0x740202*/
      {
        vmovss xmm1, dword ptr [r8]
        vpxor xmm0, xmm0, xmm0
      }
      _R13 = _R8; /*0x74020b*/
      __asm /*0x74020e*/
      {
        vcvttss2si r14d, dword ptr [rax]
        vmovd ebx, xmm1
        vucomiss xmm1, xmm0
      }
      if ( !v60 || v61 || _EBX == 0x80000000 ) /*0x740226*/
      {
        __asm { vmovss dword ptr [rbp+var_50], xmm1 } /*0x740b55*/
        MSG_WriteBit1(v282); /*0x740b60*/
        v193 = _EBX == 0x80000000; /*0x740b65*/
        v194 = __SETP__(_EBX + 0x80000000, 0); /*0x740b65*/
        if ( _EBX == 0x80000000 ) /*0x740b65*/
          goto LABEL_198; /*0x740b65*/
        __asm /*0x740b71*/
        {
          vmovss xmm1, dword ptr [rbp+var_50]
          vcvttss2si ebx, xmm1
          vcvtsi2ss xmm0, xmm0, ebx
          vucomiss xmm0, xmm1
        }
        if ( !v193 || v194 || (v197 = _EBX + 2048, v197 > 0xFFF) ) /*0x740b9a*/
        {
LABEL_198:
          MSG_WriteBit1(v282); /*0x740d1b*/
          _RDI = v282; /*0x740d23*/
          a2 = (unsigned int)(*_R13 ^ *(_DWORD *)v271); /*0x740d26*/
          MSG_WriteLong(v282, a2); /*0x740d2a*/
        }
        else
        {
          MSG_WriteBit0(v282); /*0x740ba3*/
          v198 = v197 ^ (_R14D + 2048); /*0x740bb7*/
          MSG_WriteBits(v282, (unsigned int)v198, 4, v199, v200); /*0x740bbd*/
          _RDI = v282; /*0x740bc6*/
          a2 = (unsigned int)(v198 >> 4); /*0x740bc9*/
          MSG_WriteByte(v282, a2); /*0x740bcc*/
        }
      }
      else
      {
        _RDI = v282; /*0x740232*/
        MSG_WriteBit0(v282); /*0x740236*/
      }
      __asm { vmovss xmm0, dword ptr [r13+0] } /*0x740d2f*/
      v39 = 1; /*0x740d35*/
      __asm /*0x740d37*/
      {
        vaddss xmm0, xmm0, cs:dword_FA0C4C
        vcvttss2si rax, xmm0
      }
      if ( (unsigned int)_RAX >= 0x1000 ) /*0x740d49*/
      {
        __asm { vcvttss2si r8d, xmm0 } /*0x740d4f*/
        _RDI = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp"; /*0x740d53*/
        a2 = 2138; /*0x740d61*/
        MyAssertHandler( /*0x740d73*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
          2138,
          0,
          (unsigned int)"*(float *)toF + HUDELEM_COORD_BIAS doesn't index 1 << HUDELEM_COORD_BITS\n\t%i not in [0, %i)",
          _R8D,
          4096);
      }
      goto LABEL_73; /*0x740d78*/
    case 0xFF9E:
      v102 = *_R8; /*0x740248*/
      v103 = *(_DWORD *)v271; /*0x74024b*/
      if ( *(_DWORD *)(v282 + 4) ) /*0x74024d*/
        MyAssertHandler( /*0x740272*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
          841,
          0,
          (unsigned int)"%s",
          (unsigned int)"!msg->readOnly",
          (_DWORD)a6);
      v104 = v102 ^ v103; /*0x740277*/
      v105 = v104 & 0x1FFFFFFF; /*0x74027d*/
      if ( (v104 & 0x1FFFFFFF) != 0 && (v105 & (v104 + 0x1FFFFFFF)) == 0 ) /*0x74028f*/
      {
        v102 = 31 - __lzcnt(v105); /*0x740da1*/
        if ( v102 >= 0x1D ) /*0x740da8*/
          MyAssertHandler( /*0x740dce*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
            857,
            0,
            (unsigned int)"%s\n\t(changedBitIndex) = %i",
            (unsigned int)"(changedBitIndex >= 0 && changedBitIndex < 29)",
            v102);
        if ( v105 != 1 << v102 ) /*0x740de0*/
          MyAssertHandler( /*0x740e00*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
            858,
            0,
            (unsigned int)"%s",
            (unsigned int)"( ((oldFlags ^ newFlags) & MASK_EFLAGS) ^ (1 << changedBitIndex)) == 0",
            (_DWORD)a6);
        MSG_WriteBit0(v282); /*0x740e08*/
        v108 = 5; /*0x740e0d*/
      }
      else
      {
        MSG_WriteBit1(v282); /*0x740298*/
        v108 = 29; /*0x74029d*/
      }
      _RDI = v282; /*0x740e12*/
      a2 = v102; /*0x740e15*/
      MSG_WriteBits(v282, v102, v108, v106, v107); /*0x740e18*/
      break; /*0x740e1d*/
    case 0xFF9F:
    case 0xFFB6:
    case 0xFFB8:
    case 0xFFBA:
      _RDI = v282; /*0x73ff4b*/
      a2 = a3; /*0x73ff4f*/
      MSG_WriteDeltaTime(v282, a3, (unsigned int)*_R8); /*0x73ff52*/
      break; /*0x73ff57*/
    case 0xFFA0:
      switch ( *((_WORD *)v21 + 5) ) /*0x7402c6*/
      {
        case 0xFFFC: /*0x7402c6*/
        case 4: /*0x7402c6*/
          v109 = *_R8; /*0x7402c8*/
          break; /*0x7402cb*/
        case 0xFFFE: /*0x7402c6*/
          v109 = *(__int16 *)_R8; /*0x74118b*/
          break; /*0x74118f*/
        case 0xFFFF: /*0x7402c6*/
          v109 = *(char *)_R8; /*0x741194*/
          break; /*0x741198*/
        case 1: /*0x7402c6*/
          v109 = *(unsigned __int8 *)_R8; /*0x74119d*/
          break; /*0x7411a1*/
        case 2: /*0x7402c6*/
          v109 = *(unsigned __int16 *)_R8; /*0x7411a6*/
          break; /*0x7411aa*/
        default:
          a2 = 521; /*0x7409a4*/
          v109 = 0; /*0x7409ad*/
          MyAssertHandler( /*0x7409b0*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/../qcommon/msg.h",
            521,
            0,
            (unsigned int)"unknown field size",
            (_DWORD)_R8,
            (_DWORD)a6);
          break; /*0x7409b0*/
      }
      if ( *(_DWORD *)(v282 + 4) ) /*0x7409b9*/
      {
        a2 = 874; /*0x7409d4*/
        MyAssertHandler( /*0x7409dd*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
          874,
          0,
          (unsigned int)"%s",
          (unsigned int)"!msg->readOnly",
          (_DWORD)a6);
      }
      if ( v109 == 2046 || (MSG_WriteBit0(v282), !v109) ) /*0x7409f6*/
      {
        _RDI = v282; /*0x740a24*/
        MSG_WriteBit1(v282); /*0x740a27*/
      }
      else
      {
        MSG_WriteBit0(v282); /*0x7409fb*/
        MSG_WriteBits(v282, (unsigned int)v109, 3, v188, v189); /*0x740a0b*/
        _RDI = v282; /*0x740a14*/
        a2 = (unsigned int)(v109 >> 3); /*0x740a17*/
        MSG_WriteByte(v282, a2); /*0x740a1a*/
      }
      break; /*0x740a1f*/
    case 0xFFA1:
      v110 = *_R8; /*0x7402d0*/
      if ( !v59 ) /*0x7402d6*/
        SV_LogSnapshotContent( /*0x7402ec*/
          *(char *)a1,
          (unsigned int)"Sending %i as playerstate timer value (%ims granularity)\n",
          v110,
          100,
          (_DWORD)_R8,
          (_DWORD)a6);
      v111 = 7; /*0x7402f4*/
      a2 = (unsigned int)(v110 / 100); /*0x74030b*/
      goto LABEL_157; /*0x74030d*/
    case 0xFFA2:
      v112 = 0xFFFFFFFFLL; /*0x740315*/
      if ( !a20 ) /*0x74031d*/
        goto LABEL_232; /*0x74031d*/
      v113 = v21; /*0x740327*/
      if ( *(char *)(a5 + 14) >= 18 ) /*0x740331*/
        MyAssertHandler( /*0x740351*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
          2293,
          0,
          (unsigned int)"%s",
          (unsigned int)"((entityState_t*)to)->clientNum < MAX_CLIENTS",
          -1);
      v114 = (unsigned __int64)(v26 + 0x7FFFFFFD4LL) >> 3; /*0x740363*/
      if ( (v114 & 0x80000000) != 0LL ) /*0x74036a*/
      {
        v115 = "netfieldIndex >= 0"; /*0x74113e*/
        v116 = 2298; /*0x741145*/
      }
      else
      {
        if ( (int)v114 < 4 ) /*0x740374*/
          goto LABEL_231; /*0x740374*/
        v115 = "netfieldIndex < MAX_EVENTS"; /*0x740388*/
        v116 = 2299; /*0x74038f*/
      }
      MyAssertHandler( /*0x74114e*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
        v116,
        0,
        (unsigned int)"%s",
        (_DWORD)v115,
        v112);
LABEL_231:
      v21 = v113; /*0x741153*/
      v112 = (unsigned int)(v114 + 4 * *(char *)(a5 + 14)); /*0x74115e*/
LABEL_232:
      a2 = v282; /*0x741162*/
      _RDI = (__int64)a1; /*0x74116e*/
      MSG_WriteEvent(a1, v282, v269, a5, v21, v112); /*0x741174*/
      break; /*0x741179*/
    case 0xFFA3:
      switch ( *((_WORD *)v21 + 5) ) /*0x7403b8*/
      {
        case 0xFFFC: /*0x7403b8*/
        case 4: /*0x7403b8*/
          v117 = *_R8; /*0x7403ba*/
          break; /*0x7403bd*/
        case 0xFFFE: /*0x7403b8*/
          v117 = *(__int16 *)_R8; /*0x7411af*/
          break; /*0x7411b3*/
        case 0xFFFF: /*0x7403b8*/
          v117 = *(char *)_R8; /*0x7411b8*/
          break; /*0x7411bc*/
        case 1: /*0x7403b8*/
          v117 = *(unsigned __int8 *)_R8; /*0x7411c1*/
          break; /*0x7411c5*/
        case 2: /*0x7403b8*/
          v117 = *(unsigned __int16 *)_R8; /*0x7411ca*/
          break; /*0x7411ce*/
        default:
          v117 = 0; /*0x740a48*/
          MyAssertHandler( /*0x740a4b*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/../qcommon/msg.h",
            521,
            0,
            (unsigned int)"unknown field size",
            (_DWORD)_R8,
            (_DWORD)a6);
          break; /*0x740a4b*/
      }
      if ( *(_DWORD *)(v282 + 4) ) /*0x740a54*/
        MyAssertHandler( /*0x740a78*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
          1003,
          0,
          (unsigned int)"%s",
          (unsigned int)"!msg->readOnly",
          (_DWORD)a6);
      _RDI = v282; /*0x740a82*/
      a2 = v117; /*0x740a85*/
      MSG_WriteBits(v282, v117, 31, v30, _R8); /*0x740a88*/
      break; /*0x740a8d*/
    case 0xFFA4:
    case 0xFFA5:
    case 0xFFAD:
    case 0xFFAE:
      _RAX = v271; /*0x73ff5c*/
      __asm { vmovss xmm0, dword ptr [r8] } /*0x73ff60*/
      _RDI = (__int64)a1; /*0x73ff6d*/
      __asm { vmovss xmm1, dword ptr [rax] } /*0x73ff73*/
      MSG_WriteOriginFloat(a1, a2, a1 + 1, v282, v62, *(double *)_XMM0.m128_u64, *(double *)_XMM1.m128_u64); /*0x73ff77*/
      break; /*0x73ff7c*/
    case 0xFFA6:
    case 0xFFAF:
      _RAX = v271; /*0x740004*/
      __asm { vmovss xmm0, dword ptr [r8] } /*0x740008*/
      a2 = (__int64)(a1 + 1); /*0x740011*/
      _RDI = (__int64)a1; /*0x740015*/
      __asm { vmovss xmm1, dword ptr [rax] } /*0x740018*/
      MSG_WriteOriginZFloat(a1, a1 + 1, v282, *(double *)_XMM0.m128_u64, *(double *)_XMM1.m128_u64); /*0x74001c*/
      break; /*0x740021*/
    case 0xFFA7:
      __asm /*0x7403c2*/
      {
        vmovss xmm0, dword ptr [r8]; jumptable 000000000073FF14 case -89
        vmovd eax, xmm0
      }
      if ( _EAX != 0x80000000 ) /*0x7403cb*/
      {
        __asm /*0x7403d6*/
        {
          vcvttss2si ebx, xmm0
          vcvtsi2ss xmm1, xmm0, ebx
          vucomiss xmm1, xmm0
        }
      }
      v187 = _R8; /*0x740975*/
      MSG_WriteBit1(v282); /*0x74097b*/
      _RDI = v282; /*0x740984*/
      a2 = (unsigned int)(*v187 ^ *(_DWORD *)v271); /*0x740989*/
      MSG_WriteLong(v282, a2); /*0x74098c*/
      break; /*0x740991*/
    case 0xFFA8:
      a2 = (unsigned int)*_R8 ^ *(_DWORD *)v271; /*0x740448*/
      goto LABEL_47; /*0x74044b*/
    case 0xFFA9:
      __asm { vmovss xmm0, dword ptr [r8]; jumptable 000000000073FF14 case -87 } /*0x740450*/
      _RDI = v282; /*0x740455*/
      MSG_WriteAngle16(v282, _XMM0, a2, v31, (__int64)v30, (__int64)_R8, (int)a6); /*0x740459*/
      break; /*0x74045e*/
    case 0xFFAA:
      __asm { vmovss xmm0, dword ptr [r8]; jumptable 000000000073FF14 case -86 } /*0x740463*/
      __asm
      {
        vmulss xmm1, xmm0, cs:dword_FA0C28
        vaddss xmm1, xmm1, cs:dword_FA0C2C
        vroundss xmm1, xmm0, xmm1, 1
        vcvttss2si ebx, xmm1
      }
      v123 = __lzcnt(_EBX ^ (_EBX >> 31)); /*0x740493*/
      if ( 32 - (int)v123 > (unsigned int)((_EBX >> 31) + 6) ) /*0x74049b*/
      {
        __asm { vmovd edx, xmm0 } /*0x74049d*/
        Com_PrintError( /*0x7404af*/
          15,
          (unsigned int)"Not enough bits written for fontScale %f\n",
          _EDX,
          v123,
          (_DWORD)_R8,
          (_DWORD)a6);
      }
      _RDI = v282; /*0x7404b4*/
      a2 = (unsigned int)_EBX; /*0x7404bd*/
      MSG_WriteBits(v282, (unsigned int)_EBX, 6, v123, _R8); /*0x7404bf*/
      break; /*0x7404c4*/
    case 0xFFAB:
      v125 = v271[3]; /*0x7404cd*/
      if ( v125 ) /*0x7404d2*/
      {
        v126 = (const char *)v282; /*0x740bd6*/
        if ( v125 != 255 || *((_BYTE *)_R8 + 3) ) /*0x740be4*/
          goto LABEL_186; /*0x740be9*/
      }
      else
      {
        v126 = (const char *)v282; /*0x7404d8*/
        if ( *((unsigned __int8 *)_R8 + 3) != 255 ) /*0x7404e6*/
          goto LABEL_186; /*0x7404e6*/
      }
      a2 = (__int64)_R8; /*0x740bf4*/
      v201 = _R8; /*0x740bf7*/
      v202 = PLmemcmp(v271, _R8, 3); /*0x740bfa*/
      _R8 = v201; /*0x740bff*/
      if ( !v202 ) /*0x740c04*/
      {
        _RDI = (__int64)v126; /*0x74117e*/
        MSG_WriteBit1(v126); /*0x741181*/
        break; /*0x741186*/
      }
LABEL_186:
      v203 = (unsigned __int8 *)_R8; /*0x740c0a*/
      MSG_WriteBit0(v126); /*0x740c10*/
      if ( *v271 == *v203 && v271[1] == v203[1] && v271[2] == v203[2] ) /*0x740c43*/
      {
        MSG_WriteBit1(v126); /*0x740c48*/
      }
      else
      {
        MSG_WriteBit0(v126); /*0x740c55*/
        MSG_WriteByte(v126, *v203); /*0x740c60*/
        MSG_WriteByte(v126, v203[1]); /*0x740c6c*/
        MSG_WriteByte(v126, v203[2]); /*0x740c78*/
      }
      _RDI = (__int64)v126; /*0x740c86*/
      a2 = v203[3] >> 3; /*0x740c89*/
      MSG_WriteBits(v126, a2, 5, v204, v205); /*0x740c8c*/
      break; /*0x740c91*/
    case 0xFFAC:
      a2 = (unsigned int)*_R8; /*0x7404f1*/
      v111 = 13; /*0x7404f4*/
      goto LABEL_157; /*0x7404f9*/
    case 0xFFB0:
    case 0xFFB2:
    case 0xFFB7:
    case 0xFFB9:
    case 0xFFBB:
    case 0xFFBC:
      a2 = (unsigned int)*_R8; /*0x73ff16*/
LABEL_47:
      _RDI = v282; /*0x73ff19*/
      MSG_WriteLong(v282, a2); /*0x73ff1d*/
      break; /*0x73ff22*/
    case 0xFFB1:
      __asm /*0x7404fe*/
      {
        vmovss xmm0, cs:dword_FA0C30; jumptable 000000000073FF14 case -79
        vmovss xmm7, cs:dword_FA0C34
        vmovss xmm3, cs:dword_FA0C38
      }
      __asm
      {
        vxorps xmm6, xmm6, xmm6
        vmulss xmm1, xmm0, dword ptr [r8]
        vroundss xmm2, xmm0, xmm1, 1
        vmulss xmm0, xmm0, dword ptr [rax]
        vsubss xmm1, xmm1, xmm2
        vmulss xmm1, xmm1, xmm7
        vaddss xmm4, xmm1, xmm3
        vcmpless xmm5, xmm6, xmm4
        vblendvps xmm1, xmm1, xmm4, xmm5
        vmovaps [rbp+var_50], xmm1
        vroundss xmm1, xmm0, xmm0, 1
        vsubss xmm0, xmm0, xmm1
        vmulss xmm0, xmm0, xmm7
        vaddss xmm1, xmm0, xmm3
        vcmpless xmm3, xmm6, xmm1
        vblendvps xmm1, xmm0, xmm1, xmm3
        vucomiss xmm1, xmm7
      }
      __asm { vucomiss xmm6, xmm1 }
      v145 = v60; /*0x740575*/
      v143 = 0; /*0x740575*/
      v144 = !v60; /*0x740575*/
      if ( !v145 ) /*0x740578*/
      {
        __asm { vcvtss2sd xmm0, xmm1, xmm1 } /*0x74057a*/
        __asm { vmovaps [rbp+var_60], xmm1 }
        v147 = va((unsigned int)"oldFloat %f isn't normalized\n", a2, v31, (_DWORD)v30, (_DWORD)_R8, (_DWORD)a6); /*0x74058c*/
        _RDI = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp"; /*0x740594*/
        a2 = 1643; /*0x7405a9*/
        MyAssertHandler( /*0x7405b5*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
          1643,
          0,
          (unsigned int)"%s\n\t%s",
          (unsigned int)"IsAngleNormalized360( oldFloat )",
          v147);
        __asm /*0x7405ba*/
        {
          vmovaps xmm1, [rbp+var_60]
          vxorps xmm6, xmm6, xmm6
        }
      }
      __asm { vmovaps xmm0, [rbp+var_50] } /*0x7405c3*/
      v149 = v63; /*0x7405c8*/
      __asm { vucomiss xmm0, cs:dword_FA0C34 } /*0x7405cb*/
      __asm { vucomiss xmm6, xmm0 }
      LOBYTE(v30) = v143 | v144; /*0x7405dd*/
      v270 = v143 | v144; /*0x7405df*/
      if ( !(v143 | v144) ) /*0x7405dd*/
      {
        __asm { vmovaps xmm0, [rbp+var_50] } /*0x7405e4*/
        __asm
        {
          vmovaps [rbp+var_60], xmm1
          vcvtss2sd xmm0, xmm0, xmm0
        }
        v152 = va((unsigned int)"fullFloat %f isn't normalized\n", a2, v31, (_DWORD)v30, (_DWORD)_R8, (_DWORD)a6); /*0x7405fb*/
        _RDI = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp"; /*0x740603*/
        a2 = 1644; /*0x740618*/
        MyAssertHandler( /*0x740624*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
          1644,
          0,
          (unsigned int)"%s\n\t%s",
          (unsigned int)"IsAngleNormalized360( fullFloat )",
          v152);
        __asm { vmovaps xmm1, [rbp+var_60] } /*0x740629*/
      }
      if ( !v145 )
      {
        __asm { vcvtss2sd xmm0, xmm1, xmm1 } /*0x740634*/
        __asm { vmovaps [rbp+var_60], xmm1 }
        v154 = va(
                 (unsigned int)"AngleToCompressed called with a non normalized angle: x = %f\n",
                 a2,
                 v31,
                 (_DWORD)v30,
                 (_DWORD)_R8,
                 (_DWORD)a6);
        _RDI = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h"; /*0x74064e*/
        a2 = 1360; /*0x740663*/
        MyAssertHandler( /*0x740672*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h",
          1360,
          0,
          (unsigned int)"%s\n\t%s",
          (unsigned int)"IsAngleNormalized360(x)",
          v154);
        __asm { vmovaps xmm1, [rbp+var_60] } /*0x740677*/
      }
      __asm /*0x74067c*/
      {
        vmulss xmm0, xmm1, cs:dword_FA0C3C
        vaddss xmm0, xmm0, cs:dword_FA0C2C
        vroundss xmm0, xmm0, xmm0, 1
        vcvttss2si r12d, xmm0
      }
      if ( _R12D != (__int64)(__int16)_R12D ) /*0x7406a0*/
      {
        a2 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h"; /*0x7406a2*/
        _RDI = _R12D; /*0x7406ae*/
        truncate_cast_assert_with_info(_R12D, "D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h", 1362); /*0x7406b1*/
      }
      if ( (unsigned __int16)_R12D >= 0x1000u ) /*0x7406be*/
      {
        v159 = va( /*0x7406d2*/
                 (unsigned int)"compressedAngle %d not within 0-%d range\n",
                 (__int16)_R12D,
                 4095,
                 (_DWORD)v30,
                 (_DWORD)_R8,
                 (_DWORD)a6);
        _RDI = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h"; /*0x7406da*/
        a2 = 1366; /*0x7406ef*/
        MyAssertHandler( /*0x7406fe*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h",
          1366,
          0,
          (unsigned int)"%s\n\t%s",
          (unsigned int)"(compressedAngle >= 0.f) && (compressedAngle<=COMPRESSED_ANGLE_RANGE)",
          v159);
      }
      if ( (v270 & 1) == 0 )
      {
        __asm { vmovaps xmm0, [rbp+var_50] } /*0x740709*/
        __asm { vcvtss2sd xmm0, xmm0, xmm0 }
        v162 = va(
                 (unsigned int)"AngleToCompressed called with a non normalized angle: x = %f\n",
                 a2,
                 v31,
                 (_DWORD)v30,
                 (_DWORD)_R8,
                 (_DWORD)a6);
        _RDI = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h"; /*0x740723*/
        a2 = 1360; /*0x740738*/
        MyAssertHandler( /*0x740747*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h",
          1360,
          0,
          (unsigned int)"%s\n\t%s",
          (unsigned int)"IsAngleNormalized360(x)",
          v162);
      }
      __asm /*0x74074c*/
      {
        vmovaps xmm0, [rbp+var_50]
        vmulss xmm0, xmm0, cs:dword_FA0C3C
        vaddss xmm0, xmm0, cs:dword_FA0C2C
        vroundss xmm0, xmm0, xmm0, 1
        vcvttss2si ebx, xmm0
      }
      v167 = (const char *)(__int16)_EBX; /*0x74076e*/
      v268 = _EBX; /*0x740772*/
      if ( _EBX != (__int64)(__int16)_EBX ) /*0x740779*/
      {
        _RDI = _EBX; /*0x74077b*/
        a2 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h"; /*0x74077f*/
        *(double *)_XMM0.m128_u64 = truncate_cast_assert_with_info( /*0x74078b*/
                                      _EBX,
                                      "D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h",
                                      1362);
      }
      if ( (unsigned __int16)_EBX >= 0x1000u ) /*0x74079c*/
      {
        v168 = va( /*0x7407ae*/
                 (unsigned int)"compressedAngle %d not within 0-%d range\n",
                 (__int16)_EBX,
                 4095,
                 (_DWORD)v30,
                 (_DWORD)_R8,
                 (_DWORD)a6);
        _RDI = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h"; /*0x7407b9*/
        a2 = 1366; /*0x7407ce*/
        MyAssertHandler( /*0x7407e0*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h",
          1366,
          0,
          (unsigned int)"%s\n\t%s",
          (unsigned int)"(compressedAngle >= 0.f) && (compressedAngle<=COMPRESSED_ANGLE_RANGE)",
          v168);
      }
      v169 = (__int16)_R12D; /*0x7407e5*/
      v275 = (__int16)_EBX; /*0x7407ec*/
      v170 = (__int16)_EBX - (__int16)_R12D; /*0x7407ef*/
      v171 = v169 - (__int16)_EBX; /*0x7407f5*/
      if ( v171 < 1 ) /*0x7407f7*/
        v171 = v170; /*0x7407f7*/
      if ( v171 <= 0 ) /*0x7407fd*/
      {
        if ( !v59 && !*((_BYTE *)v149 + 28) ) /*0x740ceb*/
          SV_TrackAngleNormalizedFullSend(_RDI, a2, v31, v30, _R8, *(double *)_XMM0.m128_u64); /*0x740cf2*/
        MSG_WriteBit0(v282); /*0x740cfe*/
        a2 = v275; /*0x740d03*/
        _RDI = v282; /*0x740d0b*/
        MSG_WriteBits(v282, v275, 12, v207, v208); /*0x740d0e*/
        break; /*0x740d13*/
      }
      if ( v171 >= 4096 )
      {
        v172 = va((unsigned int)"absdiff: %d\n", v171, v31, (_DWORD)v30, (_DWORD)_R8, (_DWORD)a6);
        a2 = 1661; /*0x740833*/
        MyAssertHandler( /*0x74083f*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
          1661,
          0,
          (unsigned int)"%s\n\t%s",
          (unsigned int)"absdiff < ANGLE_DELTA_MAXSIZE",
          v172);
      }
      if ( !v59 && !*((_BYTE *)v149 + 28) ) /*0x740849*/
        SV_TrackNormalizedAngleDeltaBits((unsigned int)v170, a2, v31, v30, _R8, *(double *)_XMM0.m128_u64); /*0x740853*/
      MSG_WriteBit1(v282); /*0x74085f*/
      if ( v170 < 0 ) /*0x74086a*/
        MSG_WriteBit1(v282); /*0x740e22*/
      else
        MSG_WriteBit0(v282); /*0x740870*/
      _RDI = v282; /*0x740e2c*/
      a2 = (unsigned int)v171; /*0x740e2f*/
      MSG_WriteBits(v282, (unsigned int)v171, 12, v173, v174); /*0x740e35*/
      if ( (unsigned __int16)v167 >= 0x1000u )
      {
        v219 = va(
                 (unsigned int)"CompressedToAngle called with out of band value: x = %d\n",
                 v275,
                 v215,
                 v216,
                 v217,
                 v218);
        _RDI = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h"; /*0x740e57*/
        a2 = 1373; /*0x740e6c*/
        MyAssertHandler( /*0x740e7b*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h",
          1373,
          0,
          (unsigned int)"%s\n\t%s",
          (unsigned int)"(x >= 0) && (x <= COMPRESSED_ANGLE_RANGE)",
          v219);
      }
      if ( (v270 & 1) == 0 )
      {
        __asm { vmovaps xmm0, [rbp+var_50] } /*0x740e8a*/
        __asm { vcvtss2sd xmm0, xmm0, xmm0 }
        v221 = va(
                 (unsigned int)"AngleToCompressed called with a non normalized angle: x = %f\n",
                 a2,
                 v215,
                 v216,
                 v217,
                 v218);
        _RDI = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h"; /*0x740ea4*/
        a2 = 1360; /*0x740eb9*/
        MyAssertHandler( /*0x740ec8*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h",
          1360,
          0,
          (unsigned int)"%s\n\t%s",
          (unsigned int)"IsAngleNormalized360(x)",
          v221);
      }
      __asm /*0x740ecd*/
      {
        vxorps xmm0, xmm0, xmm0
        vcvtsi2ss xmm0, xmm0, r14d
      }
      if ( (const char *)v268 != v167 ) /*0x740ed9*/
      {
        a2 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h"; /*0x740edb*/
        _RDI = v268; /*0x740ee7*/
        __asm { vmovss dword ptr [rbp+var_40], xmm0 } /*0x740eea*/
        truncate_cast_assert_with_info(v268, "D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h", 1362); /*0x740eef*/
        __asm { vmovss xmm0, dword ptr [rbp+var_40] } /*0x740ef4*/
      }
      __asm { vmulss xmm0, xmm0, cs:dword_FA0C40 } /*0x740ef9*/
      v224 = __SETP__((unsigned __int16)v167, 4096); /*0x740f05*/
      if ( (unsigned __int16)v167 >= 0x1000u )
      {
        __asm { vmovss dword ptr [rbp+var_40], xmm0 } /*0x740f21*/
        v225 = va((unsigned int)"compressedAngle %d not within 0-%d range\n", v275, 4095, v216, v217, v218); /*0x740f28*/
        MyAssertHandler( /*0x740f5a*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h",
          1366,
          0,
          (unsigned int)"%s\n\t%s",
          (unsigned int)"(compressedAngle >= 0.f) && (compressedAngle<=COMPRESSED_ANGLE_RANGE)",
          v225);
        v230 = va(
                 (unsigned int)"CompressedToAngle called with out of band value: x = %d\n",
                 v275,
                 v226,
                 v227,
                 v228,
                 v229);
        a2 = 1373; /*0x740f79*/
        _RDI = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h"; /*0x740f85*/
        MyAssertHandler( /*0x740f8e*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h",
          1373,
          0,
          (unsigned int)"%s\n\t%s",
          (unsigned int)"(x >= 0) && (x <= COMPRESSED_ANGLE_RANGE)",
          v230);
        __asm { vmovss xmm0, dword ptr [rbp+var_40] } /*0x740f93*/
      }
      v39 = 1; /*0x740f98*/
      __asm { vucomiss xmm0, xmm0 } /*0x740f9a*/
      if ( v224 )
      {
        __asm { vmovss dword ptr [rbp+var_40], xmm0 } /*0x740fa8*/
        if ( (unsigned __int16)v167 >= 0x1000u )
        {
          v231 = va(
                   (unsigned int)"CompressedToAngle called with out of band value: x = %d\n",
                   v275,
                   v215,
                   v216,
                   v217,
                   v218);
          LODWORD(a2) = 1373; /*0x740fdd*/
          MyAssertHandler( /*0x740fe9*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h",
            1373,
            0,
            (unsigned int)"%s\n\t%s",
            (unsigned int)"(x >= 0) && (x <= COMPRESSED_ANGLE_RANGE)",
            v231);
        }
        if ( (v270 & 1) == 0 )
        {
          __asm { vmovaps xmm0, [rbp+var_50] } /*0x740ff4*/
          __asm { vcvtss2sd xmm0, xmm0, xmm0 }
          v234 = va(
                   (unsigned int)"AngleToCompressed called with a non normalized angle: x = %f\n",
                   a2,
                   v215,
                   v216,
                   v217,
                   v218);
          LODWORD(a2) = 1360; /*0x741023*/
          MyAssertHandler( /*0x74102f*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h",
            1360,
            0,
            (unsigned int)"%s\n\t%s",
            (unsigned int)"IsAngleNormalized360(x)",
            v234);
        }
        if ( (const char *)v268 != v167 ) /*0x741037*/
        {
          a2 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h"; /*0x741039*/
          truncate_cast_assert_with_info(v268, "D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h", 1362); /*0x741048*/
        }
        __asm { vmovss xmm0, dword ptr [rbp+var_40] } /*0x74104d*/
        __asm { vcvtss2sd xmm0, xmm0, xmm0 }
        if ( (unsigned __int16)v167 >= 0x1000u )
        {
          __asm { vmovsd [rbp+var_40], xmm0 } /*0x741077*/
          v236 = va((unsigned int)"compressedAngle %d not within 0-%d range\n", v275, 4095, v216, v217, v218); /*0x74107f*/
          MyAssertHandler( /*0x7410b1*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h",
            1366,
            0,
            (unsigned int)"%s\n\t%s",
            (unsigned int)"(compressedAngle >= 0.f) && (compressedAngle<=COMPRESSED_ANGLE_RANGE)",
            v236);
          v241 = va(
                   (unsigned int)"CompressedToAngle called with out of band value: x = %d\n",
                   v275,
                   v237,
                   v238,
                   v239,
                   v240);
          LODWORD(a2) = 1373; /*0x7410d1*/
          MyAssertHandler( /*0x7410e6*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h",
            1373,
            0,
            (unsigned int)"%s\n\t%s",
            (unsigned int)"(x >= 0) && (x <= COMPRESSED_ANGLE_RANGE)",
            v241);
          __asm { vmovsd xmm0, [rbp+var_40] } /*0x7410eb*/
        }
        __asm { vmovapd xmm1, xmm0 } /*0x7410f9*/
        v242 = va((unsigned int)"%f != %f", a2, v215, v216, v217, v218); /*0x741102*/
        _RDI = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp"; /*0x741105*/
        v243 = "CompressedToAngle( newValAsShort ) == CompressedToAngle( AngleToCompressed( fullFloat ) )"; /*0x741113*/
        a2 = 1680; /*0x74111a*/
LABEL_228:
        MyAssertHandler( /*0x74111f*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
          a2,
          0,
          (unsigned int)"%s\n\t%s",
          (_DWORD)v243,
          v242);
      }
      goto LABEL_73; /*0x74112b*/
    case 0xFFB3:
      switch ( *((_WORD *)v21 + 5) ) /*0x740899*/
      {
        case 0xFFFC: /*0x740899*/
        case 4: /*0x740899*/
          v175 = *_R8; /*0x74089b*/
          break; /*0x74089e*/
        case 0xFFFE: /*0x740899*/
          v175 = *(__int16 *)_R8; /*0x7411d3*/
          break; /*0x7411d7*/
        case 0xFFFF: /*0x740899*/
          v175 = *(char *)_R8; /*0x7411dc*/
          break; /*0x7411e0*/
        case 1: /*0x740899*/
          v175 = *(unsigned __int8 *)_R8; /*0x7411e5*/
          break; /*0x7411e9*/
        case 2: /*0x740899*/
          v175 = *(unsigned __int16 *)_R8; /*0x7411ee*/
          break; /*0x7411f2*/
        default:
          v175 = 0; /*0x740aa9*/
          v190 = v21; /*0x740aab*/
          MyAssertHandler( /*0x740aae*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/../qcommon/msg.h",
            521,
            0,
            (unsigned int)"unknown field size",
            (_DWORD)_R8,
            (_DWORD)a6);
          v21 = v190; /*0x740ab3*/
          break; /*0x740ab3*/
      }
      if ( 32 - __lzcnt(v175 ^ (v175 >> 31)) > (v175 >> 31) + 8 )
        Com_PrintError(1, (unsigned int)"Not enough bits written: %d for %s (%d)\n", v175, *v21, 8, (_DWORD)a6);
      _RDI = v282; /*0x740af3*/
      a2 = (unsigned int)v175; /*0x740af6*/
      MSG_WriteByte(v282, (unsigned int)v175); /*0x740af8*/
      break; /*0x740afd*/
    case 0xFFB4:
      v176 = v21; /*0x7408aa*/
      v261 = _R8; /*0x7408ad*/
      v177 = *_R8 - *(_DWORD *)v271; /*0x7408b4*/
      if ( !v59 && !*((_BYTE *)a1 + 28) ) /*0x7408bc*/
        SV_TrackMovementDirDelta(v177); /*0x7408c5*/
      v178 = -v177; /*0x7408d1*/
      if ( (signed int)-v177 < 1 ) /*0x7408d3*/
        v178 = v177; /*0x7408d3*/
      if ( v178 <= 7 ) /*0x7408dd*/
      {
        MSG_WriteBit1(v282); /*0x7408e3*/
        _RDI = v282; /*0x7408f1*/
        a2 = v177 + 8; /*0x7408f4*/
        MSG_WriteBits(v282, a2, 4, v179, v180); /*0x7408f7*/
        break; /*0x7408fc*/
      }
      MSG_WriteBit0(v282); /*0x740c96*/
      v74 = *v176; /*0x740c9b*/
      a2 = (__int64)v271; /*0x740c9f*/
      v75 = v261; /*0x740ca3*/
      v77 = (unsigned int)*((__int16 *)v176 + 5); /*0x740caa*/
      v76 = 8; /*0x740caf*/
      _RDI = v282; /*0x740cb4*/
      goto LABEL_57; /*0x740cb7*/
    case 0xFFB5:
      v181 = (unsigned int)*((__int16 *)v21 + 5); /*0x740901*/
      v266 = v21; /*0x740906*/
      v182 = v181 + 4; /*0x74090a*/
      switch ( *((_WORD *)v21 + 5) ) /*0x740926*/
      {
        case 0xFFFC: /*0x740926*/
        case 4: /*0x740926*/
          v183 = *_R8; /*0x740928*/
          v279 = (unsigned int)*((__int16 *)v21 + 5); /*0x74092b*/
          goto LABEL_176; /*0x74092f*/
        case 0xFFFE: /*0x740926*/
          v183 = *(__int16 *)_R8; /*0x7411f7*/
          v279 = (unsigned int)*((__int16 *)v21 + 5); /*0x7411fb*/
LABEL_247:
          v192 = *(__int16 *)v271; /*0x7411ff*/
          break; /*0x741207*/
        case 0xFFFF: /*0x740926*/
          v183 = *(char *)_R8; /*0x741209*/
          v279 = (unsigned int)*((__int16 *)v21 + 5); /*0x74120d*/
LABEL_249:
          v192 = (char)*v271; /*0x741211*/
          break; /*0x741219*/
        case 1: /*0x740926*/
          v183 = *(unsigned __int8 *)_R8; /*0x74121b*/
          v279 = (unsigned int)*((__int16 *)v21 + 5); /*0x74121f*/
LABEL_251:
          v192 = *v271; /*0x741223*/
          break; /*0x74122b*/
        case 2: /*0x740926*/
          v183 = *(unsigned __int16 *)_R8; /*0x74122d*/
          v279 = (unsigned int)*((__int16 *)v21 + 5); /*0x741231*/
LABEL_253:
          v192 = *(unsigned __int16 *)v271; /*0x741235*/
          break; /*0x741239*/
        default:
          v279 = (unsigned int)*((__int16 *)v21 + 5); /*0x740b02*/
          a2 = 521; /*0x740b14*/
          v183 = 0; /*0x740b1d*/
          v191 = _R8; /*0x740b20*/
          MyAssertHandler( /*0x740b23*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/../qcommon/msg.h",
            521,
            0,
            (unsigned int)"unknown field size",
            (_DWORD)_R8,
            (_DWORD)a6);
          _R8 = v191; /*0x740b28*/
LABEL_176:
          switch ( v182 ) /*0x740b43*/
          {
            case 0: /*0x740b43*/
            case 8: /*0x740b43*/
              v192 = *(_DWORD *)v271; /*0x740b49*/
              break; /*0x740b4c*/
            case 2: /*0x740b43*/
              goto LABEL_247;
            case 3: /*0x740b43*/
              goto LABEL_249;
            case 5: /*0x740b43*/
              goto LABEL_251;
            case 6: /*0x740b43*/
              goto LABEL_253;
            default:
              a2 = 521; /*0x740cca*/
              v192 = 0; /*0x740cd3*/
              v206 = _R8; /*0x740cd6*/
              MyAssertHandler( /*0x740cd9*/
                (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/../qcommon/msg.h",
                521,
                0,
                (unsigned int)"unknown field size",
                (_DWORD)_R8,
                (_DWORD)a6);
              _R8 = v206; /*0x740cde*/
              break; /*0x740ce1*/
          }
          break; /*0x740ce1*/
      }
      v244 = v183 - v192; /*0x74123d*/
      v96 = v244 - 1; /*0x741240*/
      if ( v244 - 1 > 0xF ) /*0x741248*/
      {
        v245 = _R8; /*0x741285*/
        if ( !v59 && !*((_BYTE *)v63 + 28) ) /*0x74128d*/
          SV_TrackEventSeqFullSend(v244); /*0x741296*/
        MSG_WriteBit0(v282); /*0x7412a2*/
        a2 = (__int64)v271; /*0x7412ab*/
        v77 = v279; /*0x7412af*/
        v76 = 8; /*0x7412b3*/
        _RDI = v282; /*0x7412b8*/
        v75 = v245; /*0x7412bb*/
        v74 = *v266; /*0x7412be*/
        goto LABEL_57; /*0x7412c1*/
      }
      if ( !v59 && !*((_BYTE *)v63 + 28) ) /*0x74124f*/
        SV_TrackEventSeqDeltaSend(v244, a2, v181, v30, _R8); /*0x741258*/
      MSG_WriteBit1(v282); /*0x741264*/
      MinBitCountForNum = GetMinBitCountForNum(16); /*0x74126e*/
      _RDI = v282; /*0x741273*/
LABEL_259:
      a2 = v96; /*0x741276*/
      MSG_WriteBits(_RDI, v96, MinBitCountForNum, v213, v214); /*0x74127b*/
      break; /*0x741280*/
    case 0xFFBD:
      v111 = 5; /*0x740937*/
      a2 = (unsigned int)(*_R8 + 10); /*0x74093c*/
LABEL_157:
      _RDI = v282; /*0x74093f*/
      MSG_WriteBits(v282, a2, v111, v30, _R8); /*0x740943*/
      break; /*0x740948*/
    default:
      if ( *((_WORD *)v21 + 6) ) /*0x73fe89*/
      {
LABEL_41:
        if ( (int)v62 <= -51 ) /*0x73fea7*/
        {
          v64 = _R8; /*0x73feb5*/
          v65 = v21; /*0x73feb8*/
          v66 = va( /*0x73febb*/
                  (unsigned int)"Missed a MSG_ case in MSG_WriteDeltaField - value is %i",
                  v62,
                  v31,
                  (_DWORD)v30,
                  (_DWORD)_R8,
                  (_DWORD)a6);
          a2 = 2386; /*0x73feca*/
          MyAssertHandler( /*0x73fed3*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
            2386,
            0,
            v66,
            v67,
            v68);
          v21 = v65; /*0x73fed8*/
          _R8 = v64; /*0x73fedb*/
        }
        v69 = *((__int16 *)v21 + 5); /*0x73fede*/
        switch ( *((_WORD *)v21 + 5) ) /*0x73fef9*/
        {
          case 0xFFFC: /*0x73fef9*/
          case 4: /*0x73fef9*/
            v70 = *_R8; /*0x73fefb*/
            v71 = v21; /*0x73fefe*/
            break; /*0x73ff01*/
          case 0xFFFE: /*0x73fef9*/
            v70 = *(__int16 *)_R8; /*0x73ff81*/
            v71 = v21; /*0x73ff85*/
            break; /*0x73ff88*/
          case 0xFFFF: /*0x73fef9*/
            v70 = *(char *)_R8; /*0x73ff8a*/
            v71 = v21; /*0x73ff8e*/
            break; /*0x73ff91*/
          case 1: /*0x73fef9*/
            v70 = *(unsigned __int8 *)_R8; /*0x73ff93*/
            v71 = v21; /*0x73ff97*/
            break; /*0x73ff9a*/
          case 2: /*0x73fef9*/
            v70 = *(unsigned __int16 *)_R8; /*0x73ff9c*/
            v71 = v21; /*0x73ffa0*/
            break; /*0x73ffa0*/
          default:
            a2 = 521; /*0x73ff35*/
            MyAssertHandler( /*0x73ff3e*/
              (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/../qcommon/msg.h",
              521,
              0,
              (unsigned int)"unknown field size",
              (_DWORD)_R8,
              (_DWORD)a6);
            goto LABEL_71; /*0x73ff43*/
        }
        v73 = _R8; /*0x73ffa3*/
        if ( v70 ) /*0x73ffa8*/
        {
          MSG_WriteBit1(v282); /*0x73ffb5*/
          v74 = *v71; /*0x73ffba*/
          a2 = (__int64)v271; /*0x73ffbd*/
          _RDI = v282; /*0x73ffc1*/
          v75 = v73; /*0x73ffc4*/
          v76 = v62; /*0x73ffc7*/
          v77 = v69; /*0x73ffca*/
LABEL_57:
          MSG_WriteValue(_RDI, a2, v75, v76, v77, v74); /*0x73ffcd*/
        }
        else
        {
LABEL_71:
          _RDI = v282; /*0x7400e9*/
          MSG_WriteBit0(v282); /*0x7400ed*/
        }
      }
      else
      {
LABEL_59:
        _RDI = v282; /*0x73ffef*/
        a2 = (__int64)v271; /*0x73fff3*/
        MSG_WriteFloatCase(v282, v271, _R8); /*0x73fffa*/
      }
      break; /*0x73ffd2*/
  }
  v39 = 1; /*0x7400f2*/
LABEL_73:
  if ( *(_QWORD *)COMMON == v288 ) /*0x740102*/
    return v39; /*0x740108*/
  PL__stack_chk_fail(*(double *)_XMM0.m128_u64, *(double *)_XMM1.m128_u64, *(double *)_XMM2.m128_u64); /*0x7413ae*/
  return CheckFieldValueMatchesResetOnSpawnValue(_RDI, a2, v258); /*0x74010a*/
}