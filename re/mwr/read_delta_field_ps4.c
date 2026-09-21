__int64 __fastcall MSG_ReadDeltaField(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        __int64 *a5,
        unsigned int a6,
        __m128 _XMM0,
        __m128 _XMM1,
        __m128 _XMM2,
        int a10,
        char a11)
{
  __int64 v14; // r13
  __int16 *v15; // rcx
  int v16; // ecx
  int v17; // r8d
  int v18; // eax
  __int64 *v19; // rbx
  __int64 v20; // rdi
  int v22; // r8d
  int v23; // r9d
  int v24; // r15d
  int v25; // ebx
  int v26; // r13d
  int v27; // eax
  char v28; // cl
  int v29; // r14d
  int v30; // r12d
  int Short; // eax
  unsigned int v32; // r12d
  __int64 *v33; // r12
  __int64 v34; // r14
  unsigned int v35; // ebx
  __int64 v36; // rdx
  int v37; // ecx
  int v40; // r8d
  int v41; // r9d
  int v55; // eax
  int v62; // r8d
  int v63; // r9d
  _QWORD *v68; // r15
  char v69; // al
  int v70; // r14d
  char v71; // al
  int v72; // ebx
  int Bit; // ebx
  int v74; // eax
  int v75; // eax
  int v76; // ebx
  int v77; // eax
  int v79; // ebx
  int v80; // eax
  unsigned int v81; // eax
  int v82; // r9d
  signed int v83; // ebx
  __int64 v91; // rdx
  int v93; // r8d
  int v94; // r9d
  int v97; // r14d
  unsigned int v98; // ebx
  int v99; // eax
  __int64 v100; // rdx
  int v101; // eax
  int v102; // eax
  int v103; // eax
  __int64 v104; // r14
  unsigned int v105; // eax
  signed int v106; // ebx
  unsigned int v107; // r13d
  unsigned int v108; // ebx
  unsigned int v109; // eax
  unsigned int Long; // eax
  int v123; // r15d
  int v124; // edx
  int v125; // ecx
  int v126; // r8d
  int v127; // r9d
  __int16 v129; // ax
  __int16 v130; // r14
  char v131; // cf
  bool v132; // zf
  int v137; // eax
  int v139; // edx
  int v140; // ecx
  int v141; // r8d
  int v142; // r9d
  int v143; // eax
  int v145; // r15d
  int v149; // r15d
  int v150; // eax
  int v151; // eax
  __int16 v152; // bx
  int v153; // ecx
  unsigned __int16 v154; // bx
  int v155; // eax
  int v156; // r8d
  int v157; // r9d
  unsigned int v158; // r15d
  int v159; // edx
  int v160; // r14d
  int v161; // eax
  int v162; // r8d
  int v163; // r9d
  unsigned int v164; // ebx
  int v165; // r14d
  int v166; // eax
  int v172; // ecx
  int v173; // r8d
  int v174; // r9d
  char v175; // al
  int v176; // eax
  int v177; // eax
  int v178; // ebx
  int v179; // r9d
  __int16 v180; // ax
  unsigned int v188; // eax
  char v189; // bl
  int v190; // r8d
  int v191; // r9d
  int v192; // r14d
  int v193; // ebx
  int v194; // r8d
  int v195; // r9d
  int v196; // r14d
  int v197; // r15d
  unsigned int v198; // ebx
  int v199; // eax
  unsigned __int64 v200; // rbx
  int v201; // eax
  int v202; // eax
  int v203; // ebx
  int v205; // eax
  char v206; // al
  unsigned __int16 v207; // ax
  int v208; // edx
  int v209; // ecx
  int v210; // r8d
  int v211; // r9d
  bool v212; // cf
  bool v213; // zf
  int v214; // eax
  int v217; // ebx
  int v218; // ebx
  __int64 v219; // rdx
  int v220; // eax
  unsigned int v221; // ebx
  int v222; // r9d
  __int64 ClassByIndex; // r14
  __int64 v224; // rax
  int v225; // ebx
  int v226; // eax
  unsigned int v227; // r13d
  unsigned int v228; // ebx
  __int16 v229; // ax
  int v230; // r9d
  unsigned int v231; // r9d
  int v232; // r9d
  int v233; // ecx
  int v234; // r8d
  __int64 v235; // rdx
  int v236; // eax
  int v237; // r14d
  int v238; // r8d
  int v239; // r9d
  int v241; // eax
  int v242; // ecx
  bool v247; // cf
  bool v248; // zf
  int v249; // eax
  int v255; // edx
  char v256; // al
  char v257; // al
  char v258; // al
  unsigned int v259; // r13d
  unsigned int v260; // r15d
  unsigned int v261; // r9d
  int v262; // r13d
  __int16 v263; // ax
  int v264; // ebx
  unsigned int v265; // ebx
  unsigned int v266; // ebx
  unsigned int v267; // r9d
  __int64 result; // rax
  int v269; // edx
  int v270; // ecx
  int v271; // r8d
  int v272; // r9d
  __int16 v273; // [rsp+8h] [rbp-78h]
  __int64 *v274; // [rsp+10h] [rbp-70h]
  __int64 *v275; // [rsp+10h] [rbp-70h]
  __int64 *v276; // [rsp+10h] [rbp-70h]
  int v277; // [rsp+18h] [rbp-68h]
  unsigned int *v278; // [rsp+18h] [rbp-68h]
  unsigned int *v279; // [rsp+18h] [rbp-68h]
  __int16 *v280; // [rsp+20h] [rbp-60h]
  __int64 v284; // [rsp+30h] [rbp-50h]
  unsigned __int8 v291; // [rsp+30h] [rbp-50h]
  int v292; // [rsp+48h] [rbp-38h] BYREF
  int v293; // [rsp+4Ch] [rbp-34h] BYREF
  __int64 v294; // [rsp+50h] [rbp-30h]

  v277 = a2; /*0x7273cc*/
  v294 = *(_QWORD *)COMMON; /*0x7273d5*/
  v292 = 0; /*0x7273d9*/
  if ( !a3 ) /*0x7273e0*/
  {
    a2 = 1480; /*0x7273f7*/
    MyAssertHandler( /*0x727400*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
      1480,
      0,
      (unsigned int)"%s",
      (unsigned int)"from",
      a6);
  }
  v14 = *((unsigned __int16 *)a5 + 4); /*0x727405*/
  v15 = (__int16 *)&v292; /*0x72740a*/
  if ( !(_BYTE)a10 ) /*0x727414*/
    v15 = (__int16 *)(a3 + v14); /*0x727414*/
  v280 = v15; /*0x72741d*/
  if ( *(_DWORD *)a1 ) /*0x727418*/
  {
    a2 = 1488; /*0x727438*/
    MyAssertHandler( /*0x727441*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
      1488,
      0,
      (unsigned int)"%s",
      (unsigned int)"!msg->overflowed",
      a6);
    if ( *(_DWORD *)a1 ) /*0x727446*/
    {
      v18 = va( /*0x727460*/
              (unsigned int)"msg overflowed after reading %i out of %i bytes",
              *(_DWORD *)(a1 + 36),
              *(_DWORD *)(a1 + 28),
              v16,
              v17,
              a6);
      a2 = 1493; /*0x72747d*/
      MyAssertHandler( /*0x72748c*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
        1493,
        0,
        (unsigned int)"%s\n\t%s",
        (unsigned int)"!msg->overflowed",
        v18);
    }
  }
  v19 = a5; /*0x727491*/
  v20 = (unsigned int)*((__int16 *)a5 + 6); /*0x727498*/
  _R13 = (unsigned int *)(v14 + a4); /*0x72749c*/
  switch ( *((_WORD *)a5 + 6) )
  {
    case 0xFF92:
      v68 = a5; /*0x7278de*/
      if ( (unsigned int)MSG_ReadBit(a1) == 1 ) /*0x7278e9*/
      {
        MSG_ReadBits(a1, 4); /*0x7278f7*/
        LODWORD(a2) = 2; /*0x7278ff*/
        v70 = v69 & 0xF; /*0x727907*/
        *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, 2); /*0x72790b*/
        v72 = v70 | (16 * v71) & 0x30; /*0x727918*/
      }
      else
      {
        v72 = *(_DWORD *)v280 & 0x3F; /*0x728070*/
      }
      LODWORD(v20) = a1; /*0x728073*/
      if ( (unsigned int)MSG_ReadBit(a1) == 1 ) /*0x72807e*/
      {
        LODWORD(a2) = 4; /*0x728084*/
        LODWORD(v20) = a1; /*0x728089*/
        *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, 4); /*0x72808c*/
        v176 = (v175 & 0xF) << 6; /*0x728094*/
      }
      else
      {
        v176 = *(_DWORD *)v280 & 0x3C0; /*0x72822a*/
      }
      v33 = (__int64 *)COMMON; /*0x72822f*/
      v198 = v176 | v72 & 0xFFFFFC3F; /*0x72823c*/
      if ( a6 ) /*0x728240*/
      {
        a2 = (__int64)"%s:%d,%d,%d "; /*0x72824c*/
        LODWORD(v20) = 25; /*0x728253*/
        Com_Printf(25, (unsigned int)"%s:%d,%d,%d ", *v68, v198 & 0xF, (v198 >> 4) & 3, (v198 >> 6) & 0xF); /*0x72826c*/
      }
      *_R13 = v198; /*0x728271*/
      goto LABEL_234; /*0x728275*/
    case 0xFF93:
      goto LABEL_10;
    case 0xFF94:
      goto LABEL_47;
    case 0xFF95:
      v275 = a5; /*0x727923*/
      Bit = MSG_ReadBit(a1); /*0x72792f*/
      v74 = MSG_ReadBit(a1); /*0x727931*/
      if ( Bit == 1 ) /*0x727939*/
      {
        if ( v74 == 1 ) /*0x727942*/
        {
          LODWORD(a2) = 4; /*0x727948*/
          *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, 4); /*0x727950*/
          v76 = v75 << 13; /*0x727957*/
        }
        else
        {
          v76 = *(_DWORD *)v280; /*0x7285a8*/
        }
        v221 = v76 & 0x1E000; /*0x7285aa*/
        v20 = v221 >> 13; /*0x7285b2*/
        ClassByIndex = BG_AnimationState_GetClassByIndex(v20); /*0x7285ba*/
        if ( !ClassByIndex ) /*0x7285c0*/
        {
          v20 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp"; /*0x7285c2*/
          LODWORD(a2) = 1320; /*0x7285d7*/
          MyAssertHandler( /*0x7285e0*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
            1320,
            0,
            (unsigned int)"%s",
            (unsigned int)"animClass",
            v222);
        }
        v224 = *(_QWORD *)(ClassByIndex + 8); /*0x7285e5*/
        v225 = v221 | 1; /*0x7285e9*/
        if ( v224 && *(_WORD *)(v224 + 4) ) /*0x7285f1*/
        {
          v279 = _R13; /*0x728615*/
          if ( (unsigned int)MSG_ReadBit(a1) == 1 ) /*0x728603*/
          {
            a2 = 32 - __lzcnt(*(unsigned __int16 *)(*(_QWORD *)(ClassByIndex + 8) + 4LL)); /*0x728621*/
            *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, a2); /*0x728623*/
            LOBYTE(v226) = 2 * v226; /*0x728628*/
          }
          else
          {
            v226 = *(_DWORD *)v280; /*0x72891d*/
          }
          v291 = v226; /*0x728926*/
          v259 = v226 & 0xFE; /*0x728929*/
          v260 = v259 >> 1; /*0x728933*/
          v261 = *(unsigned __int16 *)(*(_QWORD *)(ClassByIndex + 8) + 4LL); /*0x728936*/
          if ( v259 >> 1 >= v261 ) /*0x72893e*/
          {
            LODWORD(a2) = 1334; /*0x72894e*/
            MyAssertHandler( /*0x72895d*/
              (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
              1334,
              0,
              (unsigned int)"toValue->animState doesn't index animClass->stateMachine->stateCount\n\t%i not in [0, %i)",
              v260,
              v261);
          }
          LODWORD(v20) = a1; /*0x728962*/
          v262 = v225 | v259; /*0x728965*/
          if ( (unsigned int)MSG_ReadBit(a1) == 1 ) /*0x728970*/
          {
            LODWORD(v20) = a1; /*0x72897e*/
            a2 = 32 - __lzcnt(*(unsigned __int8 *)(*(_QWORD *)(*(_QWORD *)(ClassByIndex + 8) + 8LL) + 40LL * v260 + 13)); /*0x728992*/
            *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, a2); /*0x728994*/
            LOWORD(v264) = v263 << 8; /*0x72899b*/
          }
          else
          {
            v264 = *(_DWORD *)v280; /*0x7289a4*/
          }
          v33 = (__int64 *)COMMON; /*0x7289af*/
          v265 = v264 & 0x1F00; /*0x7289b6*/
          v227 = v265 | v262; /*0x7289c2*/
          v266 = v265 >> 8; /*0x7289c5*/
          v267 = *(unsigned __int8 *)(*(_QWORD *)(*(_QWORD *)(ClassByIndex + 8) + 8LL) + 40LL * (v291 >> 1) + 13); /*0x7289d0*/
          if ( v266 >= v267 ) /*0x7289d9*/
          {
            v20 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp"; /*0x7289db*/
            LODWORD(a2) = 1346; /*0x7289e9*/
            MyAssertHandler( /*0x7289f8*/
              (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
              1346,
              0,
              (unsigned int)"toValue->animEntry doesn't index animClass->stateMachine->states[toValue->animState].entryCo"
                            "unt\n"
                            "\t%i not in [0, %i)",
              v266,
              v267);
          }
        }
        else
        {
          v33 = (__int64 *)COMMON; /*0x72862f*/
          v279 = _R13; /*0x728636*/
          v227 = v225; /*0x72863a*/
        }
        if ( a6 ) /*0x728a06*/
        {
          v235 = *v275; /*0x728a08*/
          a2 = (__int64)"%s:%d,%d,%d,%d "; /*0x728a13*/
          LODWORD(v20) = 25; /*0x728a1a*/
          v234 = (v227 >> 13) & 0xF; /*0x728a1f*/
          v233 = v227 & 1; /*0x728a29*/
          v232 = (unsigned __int8)v227 >> 1; /*0x728a2c*/
          goto LABEL_232; /*0x728a2c*/
        }
      }
      else
      {
        if ( v74 == 1 ) /*0x72809f*/
        {
          LODWORD(a2) = 12; /*0x7280a5*/
          *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, 12); /*0x7280ad*/
          v178 = v177 << 11; /*0x7280b4*/
        }
        else
        {
          v178 = *(_DWORD *)v280; /*0x728646*/
        }
        LODWORD(v20) = a1; /*0x728648*/
        v228 = v178 & 0x7FF800; /*0x72864b*/
        if ( (unsigned int)MSG_ReadBit(a1) == 1 ) /*0x728659*/
        {
          LODWORD(a2) = 10; /*0x72865b*/
          LODWORD(v20) = a1; /*0x728660*/
          v279 = _R13; /*0x728663*/
          *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, 10); /*0x728667*/
          LOWORD(v230) = 2 * v229; /*0x72866f*/
        }
        else
        {
          v279 = _R13; /*0x728678*/
          v230 = *(_DWORD *)v280; /*0x72867c*/
        }
        v231 = v230 & 0x7FE; /*0x72867f*/
        v33 = (__int64 *)COMMON; /*0x728686*/
        v227 = v228 | v231; /*0x728690*/
        if ( a6 ) /*0x728697*/
        {
          v232 = v231 >> 1; /*0x7286a4*/
          a2 = (__int64)"%s:%d,%d,%d "; /*0x7286a7*/
          LODWORD(v20) = 25; /*0x7286ae*/
          v233 = 0; /*0x7286b3*/
          v234 = v228 >> 11; /*0x7286b5*/
          v235 = *a5; /*0x7286b8*/
LABEL_232:
          Com_Printf(25, a2, v235, v233, v234, v232); /*0x728a40*/
        }
      }
      *v279 = v227; /*0x728a45*/
      goto LABEL_234; /*0x728a49*/
    case 0xFF96:
    case 0xFF97:
    case 0xFF98:
      if ( (unsigned int)MSG_ReadBit(a1) ) /*0x7276fc*/
      {
        _RAX = v280; /*0x727709*/
        a2 = (__int64)&v293; /*0x727710*/
        LODWORD(v20) = a1; /*0x727714*/
        __asm /*0x72771a*/
        {
          vmovss xmm0, dword ptr [rax]
          vaddss xmm0, xmm0, cs:dword_F9B8D0
          vroundss xmm0, xmm0, xmm0, 1
          vcvttss2si eax, xmm0
        }
        v293 = (int)_RAX; /*0x727730*/
        _EBX = MSG_ReadFloatCase(a1, &v293, a5, a6); /*0x727738*/
LABEL_43:
        v33 = (__int64 *)COMMON; /*0x72773a*/
LABEL_44:
        *_R13 = _EBX; /*0x727741*/
        goto LABEL_234; /*0x727745*/
      }
      v20 = (unsigned int)*((__int16 *)a5 + 6); /*0x727863*/
      if ( (_DWORD)v20 != -104 ) /*0x72786d*/
      {
        _RAX = v280; /*0x72802d*/
        LODWORD(a2) = a1; /*0x728031*/
        __asm { vmovss xmm0, dword ptr [rax] } /*0x728034*/
        *(double *)_XMM0.m128_u64 = MSG_ReadOriginFloat(v20, a1, *(double *)_XMM0.m128_u64); /*0x728038*/
        __asm { vmovd ebx, xmm0 } /*0x728041*/
        if ( a6 ) /*0x728045*/
        {
          __asm { vcvtss2sd xmm0, xmm0, xmm0 } /*0x72804e*/
          a2 = (__int64)"%s:%f "; /*0x728052*/
          LODWORD(v20) = 25; /*0x728059*/
          Com_Printf(25, (unsigned int)"%s:%f ", *a5, v172, v173, v174); /*0x728060*/
        }
        goto LABEL_43; /*0x728065*/
      }
      _RAX = v280; /*0x727873*/
      __asm /*0x72787a*/
      {
        vmovss xmm0, dword ptr [rax]
        vmovss dword ptr [rbp+var_50], xmm0
      }
      if ( (unsigned int)MSG_ReadBit(a1) ) /*0x727883*/
      {
        _RAX = &unk_337EE80; /*0x727890*/
        LODWORD(a2) = 16; /*0x727897*/
        LODWORD(v20) = a1; /*0x72789c*/
        __asm /*0x72789f*/
        {
          vmovss xmm0, dword ptr [rax+158h]
          vroundss xmm0, xmm0, xmm0, 1
          vcvttss2si ebx, xmm0
        }
        *(double *)&_XMM0 = MSG_ReadBits(a1, 16); /*0x7278b1*/
        __asm /*0x7278b6*/
        {
          vxorps xmm0, xmm0, xmm0
          vroundss xmm0, xmm0, dword ptr [rbp+var_50], 1
        }
        __asm { vcvttss2si ecx, xmm0 }
        __asm
        {
          vxorps xmm0, xmm0, xmm0
          vcvtsi2ss xmm0, xmm0, eax
        }
      }
      else
      {
        LODWORD(a2) = 7; /*0x728836*/
        LODWORD(v20) = a1; /*0x72883b*/
        *(double *)&_XMM0 = MSG_ReadBits(a1, 7); /*0x72883e*/
        __asm /*0x728843*/
        {
          vxorps xmm0, xmm0, xmm0
          vroundss xmm0, xmm0, dword ptr [rbp+var_50], 1
        }
        __asm
        {
          vcvttss2si ecx, xmm0
          vxorps xmm0, xmm0, xmm0
          vcvtsi2ss xmm0, xmm0, eax
          vcvtsi2ss xmm1, xmm0, ecx
          vaddss xmm0, xmm0, xmm1
        }
      }
      v33 = (__int64 *)COMMON; /*0x728865*/
      __asm { vmovd ebx, xmm0 } /*0x728870*/
      if ( !a6 ) /*0x728874*/
        goto LABEL_44; /*0x728874*/
      __asm { vcvtss2sd xmm0, xmm0, xmm0 } /*0x72887d*/
      a2 = (__int64)"%s:%f "; /*0x728881*/
      LODWORD(v20) = 25; /*0x728888*/
      Com_Printf(25, (unsigned int)"%s:%f ", *a5, _ECX, v62, v63); /*0x72888f*/
      *_R13 = _EBX; /*0x728894*/
      goto LABEL_234; /*0x728898*/
    case 0xFF99:
      if ( (unsigned int)MSG_ReadBit(a1) ) /*0x727962*/
        goto LABEL_70; /*0x727969*/
      LODWORD(a2) = 4; /*0x72796b*/
      LODWORD(v20) = a1; /*0x727970*/
      *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, 4); /*0x727973*/
      Short = 50 * v77; /*0x727978*/
      goto LABEL_158; /*0x72797b*/
    case 0xFF9A:
      if ( (unsigned int)MSG_ReadBit(a1) ) /*0x727983*/
      {
LABEL_70:
        a2 = 16; /*0x727990*/
        goto LABEL_106; /*0x727995*/
      }
      LODWORD(a2) = 4; /*0x72827a*/
      LODWORD(v20) = a1; /*0x72827f*/
      *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, 4); /*0x728282*/
      Short = 250 * v199; /*0x728287*/
      goto LABEL_158; /*0x728287*/
    case 0xFF9B:
      LODWORD(v20) = a1; /*0x72799a*/
      if ( (unsigned int)MSG_ReadBit(a1) ) /*0x72799d*/
      {
        LODWORD(v20) = a1; /*0x7279aa*/
        Short = MSG_ReadShort( /*0x7279ad*/
                  (char *)a1,
                  a2,
                  *(double *)_XMM0.m128_u64,
                  *(double *)_XMM1.m128_u64,
                  *(double *)_XMM2.m128_u64);
        goto LABEL_158; /*0x7279b2*/
      }
      v33 = (__int64 *)COMMON; /*0x72829d*/
      *_R13 = 0; /*0x7282a4*/
      goto LABEL_234; /*0x7282ac*/
    case 0xFF9C:
      _RAX = v280; /*0x7279b7*/
      __asm /*0x7279be*/
      {
        vmovss xmm0, dword ptr [rax]
        vmovss dword ptr [rbp+var_50], xmm0
      }
      v79 = MSG_ReadBit(a1); /*0x7279cf*/
      v80 = MSG_ReadBit(a1); /*0x7279d1*/
      if ( v79 == 1 ) /*0x7279d9*/
      {
        LODWORD(v20) = a1; /*0x7279ec*/
        a2 = 32 - __lzcnt(7u); /*0x7279f6*/
        MSG_ReadBits(a1, a2); /*0x7279fb*/
        v83 = v81; /*0x727a00*/
        if ( v81 >= 7 ) /*0x727a05*/
        {
          v20 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp"; /*0x727a07*/
          LODWORD(a2) = 1078; /*0x727a15*/
          MyAssertHandler( /*0x727a2a*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
            1078,
            0,
            (unsigned int)"index doesn't index COMMON_ANGLE_DELTA_ARRAYCOUNT\n\t%i not in [0, %i)",
            v81,
            7);
        }
        v33 = (__int64 *)COMMON; /*0x727a39*/
        if ( !g_commonAngleDeltas[v83] ) /*0x727a44*/
        {
          v20 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp"; /*0x727a4c*/
          LODWORD(a2) = 1080; /*0x727a61*/
          MyAssertHandler( /*0x727a6a*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
            1080,
            0,
            (unsigned int)"%s",
            (unsigned int)"delta",
            v82);
        }
        __asm { vmovss xmm0, dword ptr [rbp+var_50] } /*0x727a6f*/
        __asm
        {
          vmulss xmm0, xmm0, cs:dword_F9B8D8
          vaddss xmm0, xmm0, cs:dword_F9B8D0
          vroundss xmm0, xmm0, xmm0, 1
          vcvttss2si eax, xmm0
        }
        __asm
        {
          vxorps xmm0, xmm0, xmm0
          vcvtsi2ss xmm0, xmm0, eax
          vmulss xmm0, xmm0, cs:dword_F9B8DC
          vmovss dword ptr [r13+0], xmm0
        }
      }
      else
      {
        if ( v80 ) /*0x7280be*/
        {
          LODWORD(a2) = 12; /*0x7280cf*/
          LODWORD(v20) = a1; /*0x7280d4*/
          MSG_ReadBit(a1); /*0x7280c7*/
          MSG_ReadBits(a1, 12); /*0x7280e1*/
          if ( !v180 ) /*0x7280eb*/
          {
            v20 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp"; /*0x7280ed*/
            LODWORD(a2) = 1100; /*0x728102*/
            MyAssertHandler( /*0x72810b*/
              (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
              1100,
              0,
              (unsigned int)"%s",
              (unsigned int)"delta",
              v179);
          }
          __asm { vmovss xmm0, dword ptr [rbp+var_50] } /*0x728110*/
          __asm
          {
            vmulss xmm0, xmm0, cs:dword_F9B8D8
            vaddss xmm0, xmm0, cs:dword_F9B8D0
            vroundss xmm0, xmm0, xmm0, 1
            vcvttss2si eax, xmm0
          }
          __asm
          {
            vxorps xmm0, xmm0, xmm0
            vcvtsi2ss xmm0, xmm0, eax
            vmulss xmm0, xmm0, cs:dword_F9B8DC
          }
        }
        else
        {
LABEL_144:
          LODWORD(v20) = a1; /*0x72814a*/
          _XMM0 = (__m128)MSG_ReadAngle16(a1, _XMM0); /*0x72814d*/
        }
LABEL_145:
        v33 = (__int64 *)COMMON; /*0x728152*/
        __asm { vmovss dword ptr [r13+0], xmm0 } /*0x728159*/
      }
      goto LABEL_234; /*0x727aad*/
    case 0xFF9D:
      LODWORD(v20) = a1; /*0x727ab2*/
      if ( (unsigned int)MSG_ReadBit(a1) ) /*0x727ab5*/
      {
        if ( (unsigned int)MSG_ReadBit(a1) ) /*0x727ac5*/
        {
          LODWORD(v20) = a1; /*0x727ad2*/
          _EAX = *(_DWORD *)v280 ^ MSG_ReadLong(a1, a2, v91); /*0x727ade*/
          *_R13 = _EAX; /*0x727ae4*/
          if ( a6 ) /*0x727ae8*/
          {
            __asm { vmovd xmm0, eax } /*0x727af1*/
            a2 = (__int64)"%s:%f\n"; /*0x727af5*/
            LODWORD(v20) = 25; /*0x727afc*/
            __asm { vcvtss2sd xmm0, xmm0, xmm0 } /*0x727b03*/
            Com_Printf(25, (unsigned int)"%s:%f\n", *a5, (_DWORD)v280, v93, v94); /*0x727b07*/
          }
        }
        else
        {
          LODWORD(a2) = 4; /*0x7286c2*/
          MSG_ReadBits(a1, 4); /*0x7286ca*/
          LODWORD(v20) = a1; /*0x7286cf*/
          v237 = v236; /*0x7286d2*/
          *(double *)_XMM0.m128_u64 = MSG_ReadByte(a1); /*0x7286d5*/
          _RCX = v280; /*0x7286da*/
          __asm { vcvttss2si ecx, dword ptr [rcx] } /*0x7286e4*/
          v242 = ((v237 + 16 * v241) ^ ((_DWORD)_RCX + 2048)) - 2048; /*0x7286f0*/
          __asm /*0x7286fa*/
          {
            vcvtsi2ss xmm0, xmm0, ecx
            vmovss dword ptr [r13+0], xmm0
          }
          if ( a6 ) /*0x728704*/
          {
            a2 = (__int64)"%s:%i\n"; /*0x728709*/
            LODWORD(v20) = 25; /*0x728710*/
            Com_Printf(25, (unsigned int)"%s:%i\n", *v19, v242, v238, v239); /*0x728717*/
          }
        }
      }
      else
      {
        *_R13 = 0; /*0x7282b1*/
      }
      __asm { vmovss xmm0, dword ptr [r13+0] } /*0x72871c*/
      v33 = (__int64 *)COMMON; /*0x728722*/
      __asm /*0x728729*/
      {
        vaddss xmm0, xmm0, cs:dword_F9B8E0
        vcvttss2si rax, xmm0
      }
      if ( (unsigned int)_RAX >= 0x1000 ) /*0x72873b*/
      {
        __asm { vcvttss2si r8d, xmm0 } /*0x728741*/
        v20 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp"; /*0x728745*/
        LODWORD(a2) = 1664; /*0x728753*/
        MyAssertHandler( /*0x728765*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
          1664,
          0,
          (unsigned int)"*(float *)toF + HUDELEM_COORD_BIAS doesn't index 1 << HUDELEM_COORD_BITS\n\t%i not in [0, %i)",
          _R8D,
          4096);
      }
      goto LABEL_234; /*0x72876a*/
    case 0xFF9E:
      v97 = *(_DWORD *)v280; /*0x727b1a*/
      if ( *(_DWORD *)a1 ) /*0x727b15*/
        MyAssertHandler( /*0x727b3d*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
          799,
          0,
          (unsigned int)"%s",
          (unsigned int)"!msg->overflowed",
          a6);
      if ( (unsigned int)MSG_ReadBit(a1) == 1 ) /*0x727b4d*/
      {
        a2 = 29; /*0x727b53*/
LABEL_106:
        LODWORD(v20) = a1; /*0x727cfb*/
        *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, a2); /*0x727cfe*/
      }
      else
      {
        LODWORD(a2) = 5; /*0x728164*/
        LODWORD(v20) = a1; /*0x728169*/
        *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, 5); /*0x72816c*/
        v189 = v188; /*0x728171*/
        if ( v188 >= 0x1D ) /*0x728176*/
        {
          v20 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp"; /*0x728178*/
          LODWORD(a2) = 810; /*0x72818d*/
          MyAssertHandler( /*0x72819c*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
            810,
            0,
            (unsigned int)"%s\n\t(bitChanged) = %i",
            (unsigned int)"(bitChanged >= 0 && bitChanged < 29)",
            v188);
        }
        Short = v97 ^ (1 << v189); /*0x7281aa*/
      }
      goto LABEL_158; /*0x727d03*/
    case 0xFF9F:
    case 0xFFB6:
    case 0xFFB8:
    case 0xFFBA:
      if ( (unsigned int)MSG_ReadBit(a1) ) /*0x7275dd*/
        goto LABEL_25; /*0x7275e4*/
      LODWORD(a2) = 8; /*0x727841*/
      LODWORD(v20) = a1; /*0x727846*/
      *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, 8); /*0x727849*/
      v33 = (__int64 *)COMMON; /*0x727851*/
      *_R13 = v277 - v55; /*0x72785a*/
      goto LABEL_234; /*0x72785e*/
    case 0xFFA0:
      v98 = *((__int16 *)a5 + 5); /*0x727b5d*/
      v99 = MSG_ReadBit(a1); /*0x727b64*/
      v100 = 2046; /*0x727b69*/
      if ( v99 != 1 ) /*0x727b71*/
      {
        v101 = MSG_ReadBit(a1); /*0x727b76*/
        v100 = 0; /*0x727b7b*/
        if ( v101 != 1 ) /*0x727b80*/
        {
          *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, 3); /*0x727b8a*/
          v100 = v102 | (8 * (unsigned int)((__int64 (__fastcall *)(__int64))MSG_ReadByte)(a1)); /*0x727b9f*/
        }
      }
      v20 = (__int64)_R13; /*0x727ba2*/
      a2 = v98; /*0x727ba5*/
      goto LABEL_180; /*0x727ba7*/
    case 0xFFA1:
      LODWORD(a2) = 7; /*0x727bac*/
      LODWORD(v20) = a1; /*0x727bb1*/
      *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, 7); /*0x727bb4*/
      Short = 100 * v103; /*0x727bb9*/
      goto LABEL_158; /*0x727bbc*/
    case 0xFFA2:
      v104 = *((unsigned __int16 *)a5 + 4); /*0x727bc1*/
      LODWORD(v20) = a1; /*0x727bc6*/
      if ( !(unsigned int)MSG_ReadBit(a1) ) /*0x727bd0*/
      {
        v200 = *(int *)(a3 + v104); /*0x7282c2*/
        *(_DWORD *)(a4 + v104) = v200; /*0x7282cd*/
        if ( v200 >= 0xBA ) /*0x7282d1*/
        {
          v20 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp"; /*0x7282d3*/
          MyAssertHandler( /*0x7282f6*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
            175,
            0,
            (unsigned int)"eventType doesn't index EV_MAX_EVENTS\n\t%i not in [0, %i)",
            v200,
            186);
        }
        a2 = *((unsigned int *)&qword_F9BA00 + v200); /*0x728302*/
        if ( (_DWORD)a2 ) /*0x728307*/
        {
          v20 = a1; /*0x72830d*/
          goto LABEL_165; /*0x72830d*/
        }
        goto LABEL_175; /*0x728307*/
      }
      LODWORD(v20) = a1; /*0x727bd6*/
      v105 = ((__int64 (__fastcall *)(__int64))MSG_ReadByte)(a1); /*0x727bd9*/
      v106 = v105; /*0x727be2*/
      *(_DWORD *)(a4 + v104) = v105; /*0x727bea*/
      if ( v105 >= 0xBA ) /*0x727bee*/
      {
        v20 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp"; /*0x727bf0*/
        LODWORD(a2) = 175; /*0x727bfe*/
        MyAssertHandler( /*0x727c13*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
          175,
          0,
          (unsigned int)"eventType doesn't index EV_MAX_EVENTS\n\t%i not in [0, %i)",
          v105,
          186);
      }
      v107 = *((_DWORD *)&qword_F9BA00 + v106); /*0x727c22*/
      if ( !v107 ) /*0x727c29*/
      {
LABEL_175:
        v33 = (__int64 *)COMMON; /*0x72846c*/
        *(_DWORD *)(a4 + v104 + 4) = 0; /*0x728477*/
        goto LABEL_234; /*0x728480*/
      }
      LODWORD(v20) = a1; /*0x727c2f*/
      if ( (unsigned int)MSG_ReadBit(a1) ) /*0x727c32*/
      {
        v20 = a1; /*0x727c3f*/
        a2 = v107; /*0x727c42*/
LABEL_165:
        *(double *)_XMM0.m128_u64 = MSG_ReadBits(v20, a2); /*0x728310*/
        v33 = (__int64 *)COMMON; /*0x728319*/
        *(_DWORD *)(a4 + v104 + 4) = v201; /*0x728320*/
        goto LABEL_234; /*0x728325*/
      }
      v33 = (__int64 *)COMMON; /*0x7288aa*/
      v255 = ~(-1 << v107); /*0x7288bd*/
      if ( v106 == 183 ) /*0x7288bf*/
        v255 = -1; /*0x7288bf*/
      *(_DWORD *)(a4 + v104 + 4) = *(_DWORD *)(a3 + v104 + 4) & v255; /*0x7288c7*/
LABEL_234:
      result = *v33; /*0x728a4c*/
      if ( *v33 != v294 ) /*0x728a54*/
      {
        PL__stack_chk_fail(*(double *)_XMM0.m128_u64, *(double *)_XMM1.m128_u64, *(double *)_XMM2.m128_u64); /*0x728b35*/
        return MSG_ReadDeltaFields(v20, a2, v269, v270, v271, v272, a10, a11); /*0x728b3c*/
      }
      return result;
    case 0xFFA3:
      v108 = *((__int16 *)a5 + 5); /*0x727c4a*/
      *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, 31); /*0x727c56*/
      goto LABEL_122; /*0x727c5b*/
    case 0xFFA4:
    case 0xFFA5:
    case 0xFFAD:
    case 0xFFAE:
      _RAX = v280; /*0x7276e4*/
      LODWORD(a2) = a1; /*0x7276e8*/
      __asm { vmovss xmm0, dword ptr [rax] } /*0x7276eb*/
      *(double *)_XMM0.m128_u64 = MSG_ReadOriginFloat(v20, a1, *(double *)_XMM0.m128_u64); /*0x7276ef*/
      goto LABEL_131; /*0x7276f4*/
    case 0xFFA6:
    case 0xFFAF:
      _RAX = v280; /*0x727777*/
      __asm /*0x72777e*/
      {
        vmovss xmm0, dword ptr [rax]
        vmovss dword ptr [rbp+var_50], xmm0
      }
      if ( (unsigned int)MSG_ReadBit(a1) ) /*0x727787*/
      {
        _RAX = &unk_337EE80; /*0x727794*/
        LODWORD(a2) = 16; /*0x72779b*/
        LODWORD(v20) = a1; /*0x7277a0*/
        __asm /*0x7277a6*/
        {
          vmovss xmm0, dword ptr [rax+158h]
          vroundss xmm0, xmm0, xmm0, 1
          vcvttss2si ebx, xmm0
        }
        *(double *)&_XMM0 = MSG_ReadBits(a1, 16); /*0x7277b8*/
        __asm /*0x7277bd*/
        {
          vxorps xmm0, xmm0, xmm0
          vroundss xmm0, xmm0, dword ptr [rbp+var_50], 1
        }
        v19 = a5; /*0x7277ca*/
        __asm { vcvttss2si ecx, xmm0 } /*0x7277cd*/
        __asm
        {
          vxorps xmm0, xmm0, xmm0
          vcvtsi2ss xmm0, xmm0, eax
        }
      }
      else
      {
        LODWORD(a2) = 7; /*0x727fc8*/
        LODWORD(v20) = a1; /*0x727fcd*/
        *(double *)&_XMM0 = MSG_ReadBits(a1, 7); /*0x727fd0*/
        __asm /*0x727fd5*/
        {
          vxorps xmm0, xmm0, xmm0
          vroundss xmm0, xmm0, dword ptr [rbp+var_50], 1
        }
        __asm
        {
          vcvttss2si ecx, xmm0
          vxorps xmm0, xmm0, xmm0
          vcvtsi2ss xmm0, xmm0, eax
          vcvtsi2ss xmm1, xmm0, ecx
          vaddss xmm0, xmm0, xmm1
        }
      }
LABEL_131:
      v33 = (__int64 *)COMMON; /*0x727ff7*/
      __asm { vmovss dword ptr [r13+0], xmm0 } /*0x727ffe*/
      if ( a6 ) /*0x728008*/
        goto LABEL_132; /*0x728008*/
      goto LABEL_234; /*0x728008*/
    case 0xFFA7:
      if ( (unsigned int)MSG_ReadBit(a1) ) /*0x727c63*/
        goto LABEL_100; /*0x727c6a*/
      LODWORD(a2) = 5; /*0x72832a*/
      MSG_ReadBits(a1, 5); /*0x728332*/
      LODWORD(v20) = a1; /*0x728337*/
      v203 = v202; /*0x72833d*/
      *(double *)_XMM0.m128_u64 = MSG_ReadByte(a1); /*0x72833f*/
      _RCX = v280; /*0x728344*/
      v33 = (__int64 *)COMMON; /*0x72834b*/
      __asm { vcvttss2si ecx, dword ptr [rcx] } /*0x728357*/
      v37 = ((v203 + 32 * v205) ^ ((_DWORD)_RCX + 4096)) - 4096; /*0x728363*/
      __asm /*0x72836d*/
      {
        vcvtsi2ss xmm0, xmm0, ecx
        vmovss dword ptr [r13+0], xmm0
      }
      if ( !a6 ) /*0x728377*/
        goto LABEL_234; /*0x728377*/
      v36 = *a5; /*0x72837d*/
      goto LABEL_185; /*0x728380*/
    case 0xFFA8:
LABEL_100:
      LODWORD(v20) = a1; /*0x727c70*/
      Long = MSG_ReadLong(a1, a2, a3); /*0x727c73*/
      *_R13 = Long; /*0x727c78*/
      v33 = (__int64 *)COMMON; /*0x727c7c*/
      _ECX = (int)v280; /*0x727c83*/
      _EAX = *(_DWORD *)v280 ^ Long; /*0x727c87*/
      *_R13 = _EAX; /*0x727c89*/
      if ( a6 ) /*0x727c91*/
      {
        __asm { vmovd xmm0, eax } /*0x727c97*/
LABEL_132:
        __asm { vcvtss2sd xmm0, xmm0, xmm0 } /*0x72800e*/
        a2 = (__int64)"%s:%f\n"; /*0x728015*/
        LODWORD(v20) = 25; /*0x72801c*/
        Com_Printf(25, (unsigned int)"%s:%f\n", *v19, _ECX, v40, v41); /*0x728023*/
      }
      goto LABEL_234; /*0x728028*/
    case 0xFFA9:
      goto LABEL_144;
    case 0xFFAA:
      LODWORD(a2) = 6; /*0x727ca0*/
      LODWORD(v20) = a1; /*0x727ca5*/
      *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, 6); /*0x727ca8*/
      __asm /*0x727cad*/
      {
        vcvtsi2ss xmm0, xmm0, eax
        vdivss xmm0, xmm0, cs:dword_F9B8BC
        vxorps xmm1, xmm1, xmm1
        vaddss xmm0, xmm0, xmm1
      }
      goto LABEL_145; /*0x727cc1*/
    case 0xFFAB:
      LODWORD(v20) = a1; /*0x727cc6*/
      if ( (unsigned int)MSG_ReadBit(a1) ) /*0x727cc9*/
      {
        v33 = (__int64 *)COMMON; /*0x727cda*/
        *_R13 = *(_DWORD *)v280; /*0x727ce3*/
        *((_BYTE *)_R13 + 3) = -(*((_BYTE *)v280 + 3) == 0); /*0x727ced*/
      }
      else
      {
        if ( (unsigned int)MSG_ReadBit(a1) ) /*0x728388*/
        {
          *(_BYTE *)_R13 = *(_BYTE *)v280; /*0x72839b*/
          *((_BYTE *)_R13 + 1) = *((_BYTE *)v280 + 1); /*0x7283a2*/
          v206 = *((_BYTE *)v280 + 2); /*0x7283a6*/
        }
        else
        {
          MSG_ReadByte(a1); /*0x7288d4*/
          *(_BYTE *)_R13 = v256; /*0x7288dc*/
          MSG_ReadByte(a1); /*0x7288e0*/
          *((_BYTE *)_R13 + 1) = v257; /*0x7288e8*/
          MSG_ReadByte(a1); /*0x7288ec*/
        }
        LODWORD(a2) = 5; /*0x7288f1*/
        LODWORD(v20) = a1; /*0x7288f6*/
        *((_BYTE *)_R13 + 2) = v206; /*0x7288f9*/
        *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, 5); /*0x7288fd*/
        v33 = (__int64 *)COMMON; /*0x728902*/
        *((_BYTE *)_R13 + 3) = 8 * v258; /*0x72890c*/
      }
      goto LABEL_234; /*0x727cf1*/
    case 0xFFAC:
      a2 = 13; /*0x727cf6*/
      goto LABEL_106; /*0x727cf6*/
    case 0xFFB0:
    case 0xFFB2:
    case 0xFFB7:
    case 0xFFB9:
    case 0xFFBB:
    case 0xFFBC:
LABEL_25:
      LODWORD(v20) = a1; /*0x7275ea*/
      Short = MSG_ReadLong(a1, a2, a3); /*0x7275ed*/
      goto LABEL_158; /*0x7275f2*/
    case 0xFFB1:
      _RAX = v280; /*0x727d08*/
      __asm /*0x727d0f*/
      {
        vmovss xmm0, dword ptr [rax]
        vmovss dword ptr [rbp+var_50], xmm0
      }
      if ( (unsigned int)MSG_ReadBit(a1) )
      {
        __asm /*0x727d25*/
        {
          vmovss xmm0, dword ptr [rbp+var_50]
          vxorps xmm2, xmm2, xmm2
        }
        __asm
        {
          vmulss xmm0, xmm0, cs:dword_F9B8C0
          vroundss xmm1, xmm0, xmm0, 1
          vsubss xmm0, xmm0, xmm1
          vmulss xmm0, xmm0, cs:dword_F9B8C4
          vaddss xmm1, xmm0, cs:dword_F9B8C8
          vcmpless xmm2, xmm2, xmm1
          vblendvps xmm0, xmm0, xmm1, xmm2
          vmovaps xmmword ptr [rbp+var_50], xmm0
        }
        LODWORD(a2) = 12; /*0x727d6b*/
        LODWORD(v20) = a1; /*0x727d70*/
        v123 = -((unsigned int)MSG_ReadBit(a1) == 0); /*0x727d73*/
        *(double *)&_XMM0 = MSG_ReadBits(a1, 12); /*0x727d76*/
        v130 = v129; /*0x727d7b*/
        v131 = 0; /*0x727d7e*/
        v132 = v129 == 0; /*0x727d7e*/
        if ( !v129 ) /*0x727d82*/
        {
          v20 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp"; /*0x727d84*/
          LODWORD(a2) = 1149; /*0x727d99*/
          MyAssertHandler( /*0x727da2*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
            1149,
            0,
            (unsigned int)"%s",
            (unsigned int)"delta",
            v127);
        }
        __asm /*0x727da7*/
        {
          vmovaps xmm1, xmmword ptr [rbp+var_50]
          vxorps xmm0, xmm0, xmm0
          vucomiss xmm0, xmm1
          vmovaps xmm0, xmm1
        }
        if ( v131 | v132 )
        {
          __asm { vucomiss xmm0, cs:dword_F9B8C4 } /*0x727dba*/
        }
        else
        {
          __asm { vcvtss2sd xmm0, xmm0, xmm0 } /*0x727dc8*/
          __asm { vmovsd [rbp+var_58], xmm0 }
          v137 = va((unsigned int)"oldFloat %f isn't normalized\n", a2, v124, v125, v126, v127); /*0x727dda*/
          MyAssertHandler( /*0x727e09*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
            1151,
            0,
            (unsigned int)"%s\n\t%s",
            (unsigned int)"IsAngleNormalized360(oldFloat)",
            v137);
          __asm { vmovsd xmm0, [rbp+var_58] } /*0x727e0e*/
          v143 = va(
                   (unsigned int)"AngleToCompressed called with a non normalized angle: x = %f\n",
                   1151,
                   v139,
                   v140,
                   v141,
                   v142);
          v20 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h"; /*0x727e24*/
          LODWORD(a2) = 1360; /*0x727e32*/
          MyAssertHandler( /*0x727e44*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h",
            1360,
            0,
            (unsigned int)"%s\n\t%s",
            (unsigned int)"IsAngleNormalized360(x)",
            v143);
          __asm { vmovaps xmm0, xmmword ptr [rbp+var_50] } /*0x727e49*/
        }
        __asm { vmulss xmm0, xmm0, cs:dword_F9B8CC } /*0x727e4e*/
        v145 = ~v123; /*0x727e56*/
        __asm /*0x727e59*/
        {
          vaddss xmm0, xmm0, cs:dword_F9B8D0
          vroundss xmm0, xmm0, xmm0, 1
          vcvttss2si r12d, xmm0
        }
        if ( _R12D != (__int64)(__int16)_R12D ) /*0x727e75*/
        {
          a2 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h"; /*0x727e77*/
          LODWORD(v20) = _R12D; /*0x727e83*/
          *(double *)&_XMM0 = truncate_cast_assert_with_info( /*0x727e86*/
                                _R12D,
                                "D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h",
                                1362);
        }
        v149 = v145 | 1; /*0x727e8b*/
        if ( (unsigned __int16)_R12D >= 0x1000u ) /*0x727e97*/
        {
          v150 = va((unsigned int)"compressedAngle %d not within 0-%d range\n", (__int16)_R12D, 4095, v125, v126, v127); /*0x727eab*/
          v20 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h"; /*0x727eb3*/
          LODWORD(a2) = 1366; /*0x727ec8*/
          MyAssertHandler( /*0x727ed7*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h",
            1366,
            0,
            (unsigned int)"%s\n\t%s",
            (unsigned int)"(compressedAngle >= 0.f) && (compressedAngle<=COMPRESSED_ANGLE_RANGE)",
            v150);
        }
        v151 = (unsigned __int16)_R12D + v149 * v130; /*0x727ee8*/
        v152 = _R12D + v149 * v130; /*0x727eec*/
        v153 = v151 << 16; /*0x727eef*/
        if ( (v151 & 0x8000) != 0 ) /*0x727ef2*/
        {
          v154 = v152 + 4095; /*0x72876f*/
        }
        else
        {
          v154 = v152 - 4095; /*0x727ef8*/
          if ( v153 <= (int)&unk_FFF0000 ) /*0x727f04*/
            v154 = _R12D + v149 * v130; /*0x727f04*/
        }
        v33 = (__int64 *)COMMON; /*0x728775*/
        v247 = v154 < 0x1000u; /*0x72877f*/
        v248 = v154 == 4096; /*0x72877f*/
        if ( v154 >= 0x1000u )
        {
          v249 = va(
                   (unsigned int)"CompressedToAngle called with out of band value: x = %d\n",
                   (__int16)v154,
                   v124,
                   v153,
                   v126,
                   v127);
          v20 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h"; /*0x72879a*/
          LODWORD(a2) = 1373; /*0x7287af*/
          MyAssertHandler( /*0x7287bb*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h",
            1373,
            0,
            (unsigned int)"%s\n\t%s",
            (unsigned int)"(x >= 0) && (x <= COMPRESSED_ANGLE_RANGE)",
            v249);
        }
        __asm /*0x7287c3*/
        {
          vcvtsi2ss xmm0, xmm0, eax
          vmulss xmm1, xmm0, cs:dword_F9B8D4
          vxorps xmm0, xmm0, xmm0
          vucomiss xmm0, xmm1
        }
        if ( v247 || v248 ) /*0x7287d7*/
        {
          __asm { vucomiss xmm1, cs:dword_F9B8C4 } /*0x7287d9*/
          goto LABEL_213; /*0x7287e1*/
        }
        __asm { vcvtss2sd xmm0, xmm1, xmm1 } /*0x7287e3*/
        __asm { vmovss dword ptr [rbp+var_50], xmm1 }
        v217 = va((unsigned int)"newFloat %f isn't normalized ! (from CompressedToAngle)", a2, v124, v153, v126, v127); /*0x7287fa*/
        v20 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp"; /*0x7287fd*/
        LODWORD(a2) = 1164; /*0x728812*/
      }
      else
      {
        LODWORD(a2) = 12; /*0x7283ae*/
        LODWORD(v20) = a1; /*0x7283b3*/
        *(double *)&_XMM0 = MSG_ReadBits(a1, 12); /*0x7283b6*/
        v212 = v207 < 0x1000u; /*0x7283c0*/
        v213 = v207 == 4096; /*0x7283c0*/
        if ( v207 >= 0x1000u )
        {
          v214 = va(
                   (unsigned int)"CompressedToAngle called with out of band value: x = %d\n",
                   (__int16)v207,
                   v208,
                   v209,
                   v210,
                   v211);
          v20 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h"; /*0x7283db*/
          LODWORD(a2) = 1373; /*0x7283f0*/
          MyAssertHandler( /*0x7283fc*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/com_math.h",
            1373,
            0,
            (unsigned int)"%s\n\t%s",
            (unsigned int)"(x >= 0) && (x <= COMPRESSED_ANGLE_RANGE)",
            v214);
        }
        v33 = (__int64 *)COMMON; /*0x728404*/
        __asm /*0x72840b*/
        {
          vxorps xmm0, xmm0, xmm0
          vcvtsi2ss xmm0, xmm0, eax
          vmulss xmm1, xmm0, cs:dword_F9B8D4
          vxorps xmm0, xmm0, xmm0
          vucomiss xmm0, xmm1
        }
        if ( v212 || v213 ) /*0x728423*/
        {
          __asm { vucomiss xmm1, cs:dword_F9B8C4 } /*0x728425*/
          goto LABEL_213; /*0x72842d*/
        }
        __asm { vcvtss2sd xmm0, xmm1, xmm1 } /*0x728433*/
        __asm { vmovss dword ptr [rbp+var_50], xmm1 }
        v217 = va((unsigned int)"newFloat %f isn't normalized ! (from MSG_ReadAngle16)", a2, v208, v209, v210, v211); /*0x72844a*/
        v20 = (__int64)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp"; /*0x72844d*/
        LODWORD(a2) = 1133; /*0x728462*/
      }
      MyAssertHandler( /*0x728821*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
        a2,
        0,
        (unsigned int)"%s\n\t%s",
        (unsigned int)"IsAngleNormalized360(newFloat)",
        v217);
      __asm { vmovss xmm1, dword ptr [rbp+var_50] } /*0x728826*/
LABEL_213:
      __asm { vmovss dword ptr [r13+0], xmm1 } /*0x72882b*/
      goto LABEL_234; /*0x728831*/
    case 0xFFB3:
      v108 = *((__int16 *)a5 + 5); /*0x727f0c*/
      v109 = ((__int64 (__fastcall *)(__int64))MSG_ReadByte)(a1); /*0x727f13*/
LABEL_122:
      v20 = (__int64)_R13; /*0x727f18*/
      a2 = v108; /*0x727f1b*/
      v100 = v109; /*0x727f1d*/
      goto LABEL_180; /*0x727f1f*/
    case 0xFFB4:
      if ( (unsigned int)MSG_ReadBit(a1) == 1 ) /*0x727f2f*/
      {
        *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, 4); /*0x727f3d*/
        v158 = *((__int16 *)a5 + 5); /*0x727f42*/
        v159 = v155; /*0x727f47*/
        v276 = a5; /*0x727f49*/
        switch ( *((_WORD *)a5 + 5) ) /*0x727f68*/
        {
          case 0xFFFC: /*0x727f68*/
          case 4: /*0x727f68*/
            v160 = *(_DWORD *)v280; /*0x727f6e*/
            break; /*0x727f71*/
          case 0xFFFE: /*0x727f68*/
            v160 = *v280; /*0x728a6d*/
            break; /*0x728a71*/
          case 0xFFFF: /*0x727f68*/
            v160 = *(char *)v280; /*0x728a7a*/
            break; /*0x728a7e*/
          case 1: /*0x727f68*/
            v160 = *(unsigned __int8 *)v280; /*0x728a87*/
            break; /*0x728a8b*/
          case 2: /*0x727f68*/
            v160 = (unsigned __int16)*v280; /*0x728a94*/
            break; /*0x728a98*/
          default:
            v218 = v155; /*0x728485*/
            v160 = 0; /*0x72849f*/
            MyAssertHandler( /*0x7284a2*/
              (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/../qcommon/msg.h",
              521,
              0,
              (unsigned int)"unknown field size",
              v156,
              v157);
            v159 = v218; /*0x7284a7*/
            break; /*0x7284a7*/
        }
        v33 = (__int64 *)COMMON; /*0x7284aa*/
        v219 = (unsigned int)(v159 + v160 - 8); /*0x7284b1*/
      }
      else
      {
        v158 = *((__int16 *)a5 + 5); /*0x7281b2*/
        v276 = a5; /*0x7281ba*/
        v192 = ((__int64 (__fastcall *)(__int64))MSG_ReadByte)(a1); /*0x7281c3*/
        switch ( v158 ) /*0x7281e1*/
        {
          case 0xFFFFFFFC: /*0x7281e1*/
          case 4u: /*0x7281e1*/
            v193 = *(_DWORD *)v280; /*0x7281e7*/
            break; /*0x7281e9*/
          case 0xFFFFFFFE: /*0x7281e1*/
            LOWORD(v193) = *v280; /*0x728ad5*/
            break; /*0x728ad8*/
          case 0xFFFFFFFF: /*0x7281e1*/
            LOBYTE(v193) = *(_BYTE *)v280; /*0x728ae1*/
            break; /*0x728ae4*/
          case 1u: /*0x7281e1*/
            LOBYTE(v193) = *(_BYTE *)v280; /*0x728aed*/
            break; /*0x728af0*/
          case 2u: /*0x7281e1*/
            LOWORD(v193) = *v280; /*0x728af9*/
            break; /*0x728afc*/
          default:
            LOBYTE(v193) = 0; /*0x728521*/
            MyAssertHandler( /*0x728523*/
              (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/../qcommon/msg.h",
              521,
              0,
              (unsigned int)"unknown field size",
              v190,
              v191);
            break; /*0x728523*/
        }
        v33 = (__int64 *)COMMON; /*0x728528*/
        v219 = v192 ^ (unsigned int)(unsigned __int8)v193; /*0x728532*/
      }
      LODWORD(v20) = (_DWORD)_R13; /*0x728535*/
      LODWORD(a2) = v158; /*0x728538*/
      SetField(_R13, v158, v219); /*0x72853b*/
      if ( !a6 ) /*0x728548*/
        goto LABEL_234; /*0x728548*/
      v36 = *v276; /*0x72854e*/
      v37 = *_R13; /*0x728551*/
LABEL_185:
      a2 = (__int64)"%s:%i\n"; /*0x728555*/
      LODWORD(v20) = 25; /*0x72855c*/
      goto LABEL_39; /*0x728563*/
    case 0xFFB5:
      v161 = MSG_ReadBit(a1); /*0x727f79*/
      v164 = *((__int16 *)a5 + 5); /*0x727f7e*/
      if ( v161 == 1 ) /*0x727f85*/
      {
        switch ( *((_WORD *)a5 + 5) ) /*0x727fa5*/
        {
          case 0xFFFC: /*0x727fa5*/
          case 4: /*0x727fa5*/
            v165 = *(_DWORD *)v280; /*0x727fab*/
            break; /*0x727fae*/
          case 0xFFFE: /*0x727fa5*/
            v165 = *v280; /*0x728aa1*/
            break; /*0x728aa5*/
          case 0xFFFF: /*0x727fa5*/
            v165 = *(char *)v280; /*0x728aae*/
            break; /*0x728ab2*/
          case 1: /*0x727fa5*/
            v165 = *(unsigned __int8 *)v280; /*0x728abb*/
            break; /*0x728abf*/
          case 2: /*0x727fa5*/
            v165 = (unsigned __int16)*v280; /*0x728ac8*/
            break; /*0x728acc*/
          default:
            v165 = 0; /*0x7284cf*/
            MyAssertHandler( /*0x7284d2*/
              (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/../qcommon/msg.h",
              521,
              0,
              (unsigned int)"unknown field size",
              v162,
              v163);
            break; /*0x7284d2*/
        }
        *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, 32 - __lzcnt(0x10u)); /*0x7284ea*/
        v100 = (unsigned int)(v165 + v220 + 1); /*0x7284ef*/
        v20 = (__int64)_R13; /*0x7284f4*/
        a2 = v164; /*0x7284f7*/
LABEL_180:
        SetField(v20, a2, v100); /*0x7284f9*/
        v33 = (__int64 *)COMMON; /*0x7284fe*/
      }
      else
      {
        v196 = ((__int64 (__fastcall *)(__int64))MSG_ReadByte)(a1); /*0x7281f6*/
        switch ( v164 ) /*0x728213*/
        {
          case 0xFFFFFFFC: /*0x728213*/
          case 4u: /*0x728213*/
            v197 = *(_DWORD *)v280; /*0x728219*/
            break; /*0x72821c*/
          case 0xFFFFFFFE: /*0x728213*/
            LOWORD(v197) = *v280; /*0x728b05*/
            break; /*0x728b09*/
          case 0xFFFFFFFF: /*0x728213*/
            LOBYTE(v197) = *(_BYTE *)v280; /*0x728b12*/
            break; /*0x728b16*/
          case 1u: /*0x728213*/
            LOBYTE(v197) = *(_BYTE *)v280; /*0x728b1f*/
            break; /*0x728b23*/
          case 2u: /*0x728213*/
            LOWORD(v197) = *v280; /*0x728b2c*/
            break; /*0x728b30*/
          default:
            LOBYTE(v197) = 0; /*0x72857f*/
            MyAssertHandler( /*0x728582*/
              (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/../qcommon/msg.h",
              521,
              0,
              (unsigned int)"unknown field size",
              v194,
              v195);
            break; /*0x728582*/
        }
        v33 = (__int64 *)COMMON; /*0x728587*/
        LODWORD(v20) = (_DWORD)_R13; /*0x728592*/
        LODWORD(a2) = v164; /*0x728595*/
        SetField(_R13, v164, v196 ^ (unsigned int)(unsigned __int8)v197); /*0x72859a*/
      }
      goto LABEL_234; /*0x728505*/
    case 0xFFBD:
      LODWORD(a2) = 5; /*0x727fb3*/
      LODWORD(v20) = a1; /*0x727fb8*/
      *(double *)_XMM0.m128_u64 = MSG_ReadBits(a1, 5); /*0x727fbb*/
      Short = v166 - 10; /*0x727fc0*/
      goto LABEL_158; /*0x727fc3*/
    default:
      if ( *((_WORD *)a5 + 6) )
      {
LABEL_10:
        LODWORD(v20) = a1; /*0x7274b5*/
        if ( (unsigned int)MSG_ReadBit(a1) ) /*0x7274b8*/
        {
          v284 = (unsigned int)*((__int16 *)a5 + 5); /*0x7274c9*/
          v278 = _R13; /*0x7274d1*/
          v274 = a5; /*0x7274d5*/
          v273 = *((_WORD *)a5 + 6); /*0x7274de*/
          v24 = (v273 >> 31) ^ (v273 + (v273 >> 31)); /*0x7274e6*/
          if ( v24 < 0 ) /*0x7274e9*/
            MyAssertHandler( /*0x727509*/
              (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
              1012,
              0,
              (unsigned int)"%s",
              (unsigned int)"bits >= 0",
              v23);
          v25 = 0; /*0x727511*/
          v26 = 0; /*0x727513*/
          if ( (v24 & 7) != 0 ) /*0x72751d*/
          {
            v25 = ((__int64 (__fastcall *)(__int64, _QWORD))MSG_ReadBits)(a1, v24 & 7); /*0x72752a*/
            v26 = v24 & 7; /*0x72752c*/
          }
          while ( v26 < v24 ) /*0x727556*/
          {
            v27 = ((__int64 (__fastcall *)(__int64))MSG_ReadByte)(a1); /*0x727543*/
            v28 = v26; /*0x727548*/
            v26 += 8; /*0x72754b*/
            v25 |= v27 << v28; /*0x727551*/
          }
          if ( v24 >= 33 ) /*0x72755c*/
            MyAssertHandler( /*0x727582*/
              (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
              1046,
              0,
              (unsigned int)"%s\n\t(absbits) = %i",
              (unsigned int)"(absbits <= 32)",
              v24);
          _R13 = v278; /*0x72758f*/
          v29 = -1; /*0x727593*/
          if ( v24 != 32 ) /*0x7275a5*/
            v29 = (1 << v24) - 1; /*0x7275a5*/
          switch ( (int)v284 ) /*0x7275bf*/
          {
            case -4: /*0x7275bf*/
            case 4: /*0x7275bf*/
              v30 = *(_DWORD *)v280; /*0x7275c5*/
              break; /*0x7275c8*/
            case -2: /*0x7275bf*/
              v30 = *v280; /*0x7277e9*/
              break; /*0x7277ed*/
            case -1: /*0x7275bf*/
              v30 = *(char *)v280; /*0x7277f6*/
              break; /*0x7277fa*/
            case 1: /*0x7275bf*/
              v30 = *(unsigned __int8 *)v280; /*0x727803*/
              break; /*0x727807*/
            case 2: /*0x7275bf*/
              v30 = (unsigned __int16)*v280; /*0x727810*/
              break; /*0x727814*/
            default:
              v30 = 0; /*0x727630*/
              MyAssertHandler( /*0x727633*/
                (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/../qcommon/msg.h",
                521,
                0,
                (unsigned int)"unknown field size",
                v22,
                v23);
              break; /*0x727633*/
          }
          v32 = v25 ^ v29 & v30; /*0x72763f*/
          if ( v273 < 0 ) /*0x727645*/
          {
            v19 = v274; /*0x727651*/
            a2 = v284; /*0x727655*/
            if ( _bittest((const int *)&v32, v24 - 1) ) /*0x72765c*/
              v32 |= ~v29; /*0x727665*/
          }
          else
          {
            v19 = v274; /*0x727647*/
            a2 = v284; /*0x72764b*/
          }
          LODWORD(v20) = (_DWORD)v278; /*0x727668*/
          SetField(v278, a2, v32); /*0x72766e*/
        }
        else
        {
          switch ( *((_WORD *)a5 + 5) ) /*0x72760d*/
          {
            case 0xFFFC: /*0x72760d*/
            case 4: /*0x72760d*/
              *_R13 = 0; /*0x72760f*/
              break; /*0x727617*/
            case 0xFFFE: /*0x72760d*/
            case 2: /*0x72760d*/
              *(_WORD *)_R13 = 0; /*0x72774a*/
              break; /*0x727751*/
            case 0xFFFF: /*0x72760d*/
            case 1: /*0x72760d*/
              *(_BYTE *)_R13 = 0; /*0x727756*/
              break; /*0x72775b*/
            default:
              break;
          }
        }
        v33 = (__int64 *)COMMON; /*0x727673*/
        if ( a6 )
        {
          v34 = *v19; /*0x727688*/
          switch ( *((_WORD *)v19 + 5) ) /*0x7276a1*/
          {
            case 0xFFFC: /*0x7276a1*/
            case 4: /*0x7276a1*/
              v35 = *_R13; /*0x7276a3*/
              break; /*0x7276a7*/
            case 0xFFFE: /*0x7276a1*/
              v35 = *(__int16 *)_R13; /*0x727819*/
              break; /*0x72781e*/
            case 0xFFFF: /*0x7276a1*/
              v35 = *(char *)_R13; /*0x727823*/
              break; /*0x727828*/
            case 1: /*0x7276a1*/
              v35 = *(unsigned __int8 *)_R13; /*0x72782d*/
              break; /*0x727832*/
            case 2: /*0x7276a1*/
              v35 = *(unsigned __int16 *)_R13; /*0x727837*/
              break; /*0x72783c*/
            default:
              v35 = 0; /*0x7276c0*/
              MyAssertHandler( /*0x7276c2*/
                (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/../qcommon/msg.h",
                521,
                0,
                (unsigned int)"unknown field size",
                v22,
                v23);
              break; /*0x7276c2*/
          }
          a2 = (__int64)"default field value: %s:%i\n";
          LODWORD(v20) = 25; /*0x7276ce*/
          LODWORD(v36) = v34; /*0x7276d5*/
          v37 = v35; /*0x7276d8*/
LABEL_39:
          Com_Printf(25, a2, v36, v37, v22, v23); /*0x7276da*/
        }
      }
      else
      {
LABEL_47:
        LODWORD(a2) = (_DWORD)v280; /*0x727760*/
        LODWORD(v20) = a1; /*0x727767*/
        Short = MSG_ReadFloatCase(a1, v280, a5, a6); /*0x72776d*/
LABEL_158:
        v33 = (__int64 *)COMMON; /*0x72828d*/
        *_R13 = Short; /*0x728294*/
      }
      goto LABEL_234; /*0x7276df*/
  }
}