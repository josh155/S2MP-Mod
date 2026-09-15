__int64 __fastcall MSG_ReadDeltaEntity(
        char *a1,
        const char *a2,
        __m256 *a3,
        char *a4,
        unsigned int a5,
        int a6,
        double a7,
        double a8,
        double a9,
        int a10)
{
  _QWORD *v10; // r14
  char *v13; // r12
  int v14; // r8d
  int v15; // r9d
  int v16; // eax
  unsigned int v17; // ebx
  int v18; // r9d
  __int64 **v19; // rax
  __int64 *v20; // r15
  int Bits; // eax
  int v22; // r8d
  int v23; // r9d
  int v24; // ecx
  int v25; // eax
  int v26; // eax
  int v27; // r9d
  int NumFieldsSkipped; // ebx
  int v29; // ebx
  int v30; // r8d
  int v31; // r9d
  char *v32; // r15
  int v33; // r15d
  int v34; // eax
  int v35; // r8d
  int v36; // r9d
  char *v37; // rbx
  int v38; // r13d
  unsigned __int8 v39; // r14
  __int64 **StateFieldListForEntityType; // rax
  int v41; // r8d
  __int64 *v42; // r12
  int v43; // edx
  int v45; // r9d
  int v46; // r10d
  __m256 *v47; // r15
  int v56; // ebx
  int v57; // ebx
  int v58; // ebx
  int v59; // ebx
  int v60; // ebx
  __int64 v61; // rcx
  int v62; // r8d
  unsigned __int64 v63; // rax
  unsigned int v64; // ecx
  int v65; // eax
  int v66; // ecx
  int v67; // r8d
  int v68; // r9d
  int v69; // edx
  int v70; // ebx
  int v71; // eax
  int v72; // eax
  int v74; // ebx
  __int64 *v75; // rbx
  int v76; // r14d
  int v77; // r13d
  unsigned __int64 v78; // rax
  unsigned int v79; // ecx
  int v80; // ebx
  int v81; // r10d
  int v82; // ebx
  __int64 v83; // rax
  unsigned int v84; // ebx
  int EntityTypeName; // eax
  int v86; // r8d
  int v87; // r9d
  int v88; // r9d
  __int64 v89; // rdx
  unsigned int v90; // r8d
  int v91; // ebx
  __int64 v92; // rcx
  __int64 v93; // r15
  int v94; // r14d
  __int64 v95; // r12
  unsigned int v96; // r13d
  unsigned int DeltaStruct; // ebx
  int v98; // [rsp+74h] [rbp-184h]
  unsigned int v99; // [rsp+78h] [rbp-180h]
  __int64 *v100; // [rsp+88h] [rbp-170h]
  int Bit; // [rsp+9Ch] [rbp-15Ch]
  __m256 *v102; // [rsp+A0h] [rbp-158h]
  int v103; // [rsp+B0h] [rbp-148h]
  int v104; // [rsp+B0h] [rbp-148h]
  int v105; // [rsp+B0h] [rbp-148h]
  int v106; // [rsp+B4h] [rbp-144h]
  int v107; // [rsp+B8h] [rbp-140h]
  char *v109; // [rsp+C0h] [rbp-138h]
  __m256 v110; // [rsp+C8h] [rbp-130h] BYREF
  __m256 v112; // [rsp+108h] [rbp-F0h]
  __m256 v114; // [rsp+148h] [rbp-B0h]
  __m256 v115; // [rsp+168h] [rbp-90h]
  __m256 v117; // [rsp+1A8h] [rbp-50h]
  __int64 v118; // [rsp+1C8h] [rbp-30h]

  v10 = (_QWORD *)COMMON; /*0x724704*/
  v13 = a1; /*0x724711*/
  v106 = (int)a2; /*0x72471b*/
  v118 = *(_QWORD *)COMMON; /*0x724727*/
  if ( a3 && !a6 ) /*0x724730*/
  {
    LODWORD(a2) = 0; /*0x724732*/
    SV_ValidateEntityState(a3, 0); /*0x724737*/
  }
  if ( a5 >= 0x800 ) /*0x724743*/
  {
    LODWORD(a2) = 2165; /*0x72475a*/
    MyAssertHandler( /*0x724763*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
      2165,
      0,
      (unsigned int)"%s",
      (unsigned int)"number < (1u << GENTITYNUM_BITS)",
      a6);
  }
  if ( (unsigned int)MSG_ReadBit(a1) != 1 )
  {
    if ( (unsigned int)MSG_ReadBit(a1) )
    {
      v19 = g_netFieldList; /*0x7247cd*/
      if ( *((_DWORD *)g_netFieldList + 26) >= 0x49u ) /*0x7247d4*/
      {
        MyAssertHandler( /*0x7247f4*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
          2198,
          0,
          (unsigned int)"%s",
          (unsigned int)"g_netFieldList[NET_FIELD_TYPE_ENTITY_STATE].count <= maxNumFields",
          v18);
        v19 = g_netFieldList; /*0x7247f9*/
      }
      v20 = v19[12]; /*0x7247fc*/
      Bit = MSG_ReadBit(a1); /*0x724808*/
      Bits = MSG_ReadBits(a1, 32 - __lzcnt(0x48u)); /*0x724821*/
      v24 = Bits; /*0x724826*/
      if ( Bits >= 72 )
      {
        v33 = Bits; /*0x7249d5*/
        v34 = va((unsigned int)"lastChanged was %i, totalFields is %i\n", Bits, 72, Bits, v22, v23); /*0x7249d8*/
        MyAssertHandler( /*0x724a01*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
          1001,
          0,
          (unsigned int)"%s\n\t%s",
          (unsigned int)"lastChanged < totalFields",
          v34);
        MSG_Discard(a1); /*0x724a09*/
        a2 = "Got lastChanged field of %i, but there are only %i fields\n"; /*0x724a0e*/
        a1 = (_BYTE *)(&start__Zdynstr + 1); /*0x724a15*/
        Com_PrintError( /*0x724a24*/
          25,
          (unsigned int)"Got lastChanged field of %i, but there are only %i fields\n",
          v33,
          72,
          v35,
          v36);
        v32 = a4; /*0x724a29*/
      }
      else
      {
        v107 = Bits; /*0x724838*/
        if ( unk_337E2E0 )
        {
          v25 = *(_DWORD *)(unk_337E2E0 + 24LL); /*0x724847*/
          if ( v25 > 1 || v25 == -1 )
            Com_Printf(25, (unsigned int)"%3i: lc %d\n", *((_DWORD *)a1 + 9), v107, v22, v23);
        }
        *(_WORD *)a4 = a5; /*0x724881*/
        if ( (unsigned __int16)a5 != a5 ) /*0x724885*/
        {
          v26 = va((unsigned int)"value %d != *(unsigned short*)i %d", a5, (unsigned __int16)a5, v24, v22, v23); /*0x724893*/
          MyAssertHandler( /*0x7248bc*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/../qcommon/msg.h",
            553,
            0,
            (unsigned int)"%s\n\t%s",
            (unsigned int)"value == *(unsigned short*)i",
            v26);
        }
        if ( (unsigned int)PLstrcmp(*v20, "eType") ) /*0x7248cb*/
          MyAssertHandler( /*0x7248f2*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
            2224,
            0,
            (unsigned int)"%s",
            (unsigned int)"strcmp( esField[0].name, \"eType\" ) == 0",
            v27);
        v102 = a3; /*0x7248fc*/
        if ( *((unsigned __int16 *)v20 + 6) != 65459 ) /*0x724908*/
          MyAssertHandler( /*0x724928*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
            2226,
            0,
            (unsigned int)"%s",
            (unsigned int)"esField[0].bits == MSG_FIELD_ETYPE",
            v27);
        NumFieldsSkipped = MSG_ReadNumFieldsSkipped((__int64)a1, 3u, v107 + 1); /*0x724944*/
        if ( NumFieldsSkipped <= 0 ) /*0x724948*/
          MyAssertHandler( /*0x72496e*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
            2236,
            0,
            (unsigned int)"%s\n\t(nextChanged) = %i",
            (unsigned int)"(nextChanged > 0)",
            NumFieldsSkipped);
        v29 = NumFieldsSkipped - 1; /*0x724973*/
        if ( v29 >= 72 ) /*0x724978*/
        {
          MSG_Discard(a1); /*0x724981*/
          Com_PrintError( /*0x72499b*/
            25,
            (unsigned int)"Got nextChanged field of %i, but there are only %i fields\n",
            v29,
            72,
            v30,
            v31);
          v32 = a4; /*0x7249a0*/
          goto LABEL_69; /*0x7249a7*/
        }
        v100 = v20; /*0x724a40*/
        v99 = a5; /*0x724a52*/
        if ( v29 ) /*0x724a5b*/
        {
          v103 = v29; /*0x724a5d*/
          v37 = a4; /*0x724a63*/
          MSG_CopyFieldOver(v20, v102, a4, 0); /*0x724a7d*/
          v38 = -1; /*0x724a82*/
        }
        else
        {
          v37 = a4; /*0x724a91*/
          v38 = 0; /*0x724ab6*/
          MSG_ReadDeltaField((_DWORD)a1, v106, (_DWORD)v102, (_DWORD)a4, (_DWORD)v20, 0, 0); /*0x724abf*/
          if ( v107 <= 0 ) /*0x724acd*/
            v103 = 0; /*0x724ae4*/
          else
            v103 = MSG_ReadNumFieldsSkipped((__int64)a1, 3u, v107); /*0x724adc*/
        }
        v39 = v37[12]; /*0x724aee*/
        v109 = v37; /*0x724af2*/
        StateFieldListForEntityType = MSG_GetStateFieldListForEntityType(v39); /*0x724aff*/
        v42 = *StateFieldListForEntityType; /*0x724b04*/
        v43 = *((_DWORD *)StateFieldListForEntityType + 2); /*0x724b07*/
        if ( a10 ) /*0x724b0d*/
        {
          _RAX = v102; /*0x724b13*/
          v45 = v107; /*0x724b1a*/
          v46 = v103; /*0x724b21*/
          v47 = &v110; /*0x724b2b*/
          __asm /*0x724b32*/
          {
            vmovups ymm0, ymmword ptr [rax+0E0h]
            vmovups [rbp+var_50], ymm0
            vmovups ymm0, ymmword ptr [rax+0C0h]
            vmovups [rbp+var_70], ymm0
            vmovups ymm0, ymmword ptr [rax+0A0h]
            vmovups [rbp+var_90], ymm0
            vmovups ymm0, ymmword ptr [rax+80h]
            vmovups [rbp+var_B0], ymm0
            vmovups ymm0, ymmword ptr [rax]
            vmovups ymm1, ymmword ptr [rax+20h]
            vmovups ymm2, ymmword ptr [rax+40h]
            vmovups ymm3, ymmword ptr [rax+60h]
          }
          __asm
          {
            vmovups [rbp+var_D0], ymm3
            vmovups [rbp+var_F0], ymm2
            vmovups [rbp+var_110], ymm1
            vmovups [rbp+var_130], ymm0
          }
          v56 = v43; /*0x724bdb*/
          switch ( v39 ) /*0x724be4*/
          {
            case 1u: /*0x724be4*/
              if ( v99 != (__int64)(char)v99 ) /*0x724bf6*/
              {
                a7 = truncate_cast_assert_with_info(v99, "D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp", 2285); /*0x724c0a*/
                v46 = v103; /*0x724c0f*/
                v45 = v107; /*0x724c12*/
              }
              HIWORD(v110.m256_f32[1]) = 2046; /*0x724c1c*/
              BYTE1(v110.m256_f32[3]) = 7; /*0x724c25*/
              LODWORD(v112.m256_f32[7]) = 3; /*0x724c2c*/
              LODWORD(v114.m256_f32[0]) = 1; /*0x724c36*/
              v47 = &v110; /*0x724c40*/
              BYTE2(v110.m256_f32[3]) = v99; /*0x724c47*/
              break; /*0x724c4d*/
            case 2u: /*0x724be4*/
              goto LABEL_48;
            case 3u: /*0x724be4*/
              HIWORD(v110.m256_f32[1]) = 2046; /*0x724c68*/
              v47 = &v110; /*0x724c71*/
              BYTE2(v110.m256_f32[3]) = 42; /*0x724c78*/
              break; /*0x724c7f*/
            case 4u: /*0x724be4*/
            case 5u: /*0x724be4*/
              break;
            case 6u: /*0x724be4*/
              v47 = &v110; /*0x724c81*/
              LODWORD(v115.m256_f32[1]) = 2047; /*0x724c88*/
              break; /*0x724c88*/
            default:
              v56 = v43; /*0x724bab*/
              if ( v39 == 18 ) /*0x724bad*/
              {
LABEL_48:
                HIWORD(v110.m256_f32[1]) = 2046; /*0x724c4f*/
                v47 = &v110; /*0x724c58*/
                BYTE1(v110.m256_f32[3]) = 7; /*0x724c5f*/
              }
              break; /*0x724c66*/
          }
        }
        else
        {
          v47 = v102; /*0x724bb8*/
          v45 = v107; /*0x724bbf*/
          v46 = v103; /*0x724bc6*/
          v56 = *((_DWORD *)StateFieldListForEntityType + 2); /*0x724bcd*/
        }
        if ( v45 >= v56 ) /*0x724c95*/
        {
          Com_Printf(14, (unsigned int)"Last changed field was %i, but there are only %i fields\n", v45, v56, v41, v45); /*0x724ed2*/
          v10 = (_QWORD *)COMMON; /*0x724ede*/
          v32 = v109; /*0x724ee5*/
          *(_DWORD *)a1 = 1; /*0x724eec*/
          goto LABEL_69; /*0x724eec*/
        }
        v98 = v56; /*0x724cac*/
        if ( v45 ) /*0x724cbc*/
        {
          if ( v38 == v45 ) /*0x724cc5*/
          {
            v57 = v46; /*0x724ce4*/
            MyAssertHandler( /*0x724ce7*/
              (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
              2315,
              0,
              (unsigned int)"lastChanged != lc\n\t%i, %i",
              v45,
              v45);
            v46 = v57; /*0x724cec*/
          }
          while ( 1 ) /*0x724d4f*/
          {
            v59 = v38; /*0x724d4f*/
            v38 = v46; /*0x724d52*/
            v60 = v59 + 1; /*0x724d55*/
            if ( v60 < v46 ) /*0x724d5a*/
            {
              do /*0x724d75*/
                MSG_CopyFieldOver(v42, v47, v109, (unsigned int)v60++); /*0x724d6b*/
              while ( v38 != v60 ); /*0x724d75*/
            }
            v61 = 2LL * v38; /*0x724d84*/
            v62 = (_DWORD)v42 + v61 * 8; /*0x724d88*/
            LOBYTE(v63) = LOBYTE(v47->m256_f32[3]) != (unsigned __int8)v109[12]; /*0x724d8e*/
            if ( !((Bit == 0) | (unsigned __int8)v63) ) /*0x724d93*/
            {
              v64 = SWORD2(v42[v61 + 1]) + 108; /*0x724da1*/
              if ( v64 > 0x28 ) /*0x724da7*/
                LOBYTE(v63) = 0; /*0x724db8*/
              else
                v63 = (0x1807E000001uLL >> v64) & 1; /*0x724db3*/
            }
            MSG_ReadDeltaField((_DWORD)a1, v106, (_DWORD)v47, (_DWORD)v109, v62, 0, v63); /*0x724dd9*/
            v45 = v107; /*0x724dde*/
            if ( v107 <= v38 ) /*0x724deb*/
              break; /*0x724deb*/
            v65 = MSG_ReadNumFieldsSkipped((__int64)a1, 3u, v107 - v38); /*0x724dfc*/
            v69 = v107; /*0x724e01*/
            v70 = v65; /*0x724e04*/
            v46 = v65 + v38; /*0x724e06*/
            if ( v107 < v65 + v38 ) /*0x724e0d*/
            {
              v104 = v65 + v38; /*0x724e1b*/
              v71 = va((unsigned int)"nextChanged is %i, lc is %i", v46, v107, v66, v67, v68); /*0x724e22*/
              MyAssertHandler( /*0x724e48*/
                (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
                2338,
                0,
                (unsigned int)"%s\n\t%s",
                (unsigned int)"lc >= nextChanged",
                v71);
              v46 = v104; /*0x724e4d*/
              v69 = v107; /*0x724e54*/
            }
            if ( v70 <= 0 ) /*0x724e5d*/
            {
              v105 = v46; /*0x724e6e*/
              v72 = va((unsigned int)"nextChanged is %i, lastChanged is %i", v46, v38, v66, v67, v68); /*0x724e75*/
              MyAssertHandler( /*0x724e9e*/
                (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
                2339,
                0,
                (unsigned int)"%s\n\t%s",
                (unsigned int)"nextChanged > lastChanged",
                v72);
              v46 = v105; /*0x724ea3*/
              v69 = v107; /*0x724eaa*/
            }
            if ( v69 < v46 ) /*0x724eb4*/
            {
              v58 = v46; /*0x724d44*/
              MyAssertHandler( /*0x724d47*/
                (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
                2340,
                0,
                (unsigned int)"nextChanged <= lc\n\t%i, %i",
                v46,
                v107);
              v46 = v58; /*0x724d4c*/
            }
          }
          v46 = v38; /*0x724f1f*/
        }
        if ( v46 != v45 ) /*0x724f25*/
        {
          v74 = v46; /*0x724f44*/
          MyAssertHandler( /*0x724f47*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
            2344,
            0,
            (unsigned int)"nextChanged == lc\n\t%i, %i",
            v46,
            v45);
          v46 = v74; /*0x724f4c*/
        }
        if ( v46 > 0 ) /*0x724f52*/
        {
          v75 = v42; /*0x724f69*/
          v76 = v46; /*0x724f6c*/
          do /*0x724ff7*/
          {
            if ( (*((_BYTE *)v75 + 14) & 2) != 0 ) /*0x724f84*/
            {
              v77 = v46; /*0x724f92*/
              LOBYTE(v78) = LOBYTE(v47->m256_f32[3]) != (unsigned __int8)v109[12]; /*0x724f9b*/
              if ( !((Bit == 0) | (unsigned __int8)v78) ) /*0x724fa0*/
              {
                v79 = *((__int16 *)v75 + 6) + 108; /*0x724fac*/
                if ( v79 > 0x28 ) /*0x724fb2*/
                  LOBYTE(v78) = 0; /*0x724fc3*/
                else
                  v78 = (0x1807E000001uLL >> v79) & 1; /*0x724fbe*/
              }
              MSG_ReadDeltaField((_DWORD)a1, v106, (_DWORD)v47, (_DWORD)v109, (_DWORD)v75, 0, v78); /*0x724fe8*/
              v46 = v77; /*0x724fed*/
            }
            v75 += 2; /*0x724ff0*/
            --v76; /*0x724ff4*/
          }
          while ( v76 ); /*0x724ff7*/
        }
        if ( v46 < 0 ) /*0x724ffc*/
        {
          v80 = v46; /*0x72501c*/
          MyAssertHandler( /*0x72501f*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
            2367,
            0,
            (unsigned int)"%s",
            (unsigned int)"nextChanged >= 0",
            v45);
          v46 = v80; /*0x725024*/
        }
        v81 = v46 + 1; /*0x725035*/
        if ( v81 < v98 ) /*0x72503b*/
        {
          do /*0x72505d*/
          {
            v82 = v81; /*0x72504c*/
            MSG_CopyFieldOver(v42, v47, v109, (unsigned int)v81); /*0x72504f*/
            v81 = v82 + 1; /*0x725057*/
          }
          while ( v98 != v82 + 1 ); /*0x72505d*/
        }
        v10 = (_QWORD *)COMMON; /*0x725066*/
        v32 = v109; /*0x72506d*/
        if ( *(_BYTE *)(unk_BA57FC0 + 24LL) )
        {
          v83 = *((unsigned __int16 *)v100 + 4); /*0x725080*/
          switch ( *((_WORD *)v100 + 5) ) /*0x72509e*/
          {
            case 0xFFFC: /*0x72509e*/
            case 4: /*0x72509e*/
              v84 = *(_DWORD *)&v109[v83]; /*0x7250a0*/
              break; /*0x7250a4*/
            case 0xFFFE: /*0x72509e*/
              v84 = *(__int16 *)&v109[v83]; /*0x725158*/
              break; /*0x72515d*/
            case 0xFFFF: /*0x72509e*/
              v84 = v109[v83]; /*0x725162*/
              break; /*0x725167*/
            case 1: /*0x72509e*/
              v84 = (unsigned __int8)v109[v83]; /*0x72516c*/
              break; /*0x725171*/
            case 2: /*0x72509e*/
              v84 = *(unsigned __int16 *)&v109[v83]; /*0x725176*/
              break; /*0x72517b*/
            default:
              v84 = 0; /*0x7250bd*/
              MyAssertHandler( /*0x7250bf*/
                (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon/../universal/../qcommon/msg.h",
                521,
                0,
                (unsigned int)"unknown field size",
                v41,
                v45);
              break; /*0x7250bf*/
          }
          EntityTypeName = BG_GetEntityTypeName(v84, a7); /*0x7250c6*/
          Com_Printf(25, (unsigned int)"%3i: changed ent, eType %s\n", v99, EntityTypeName, v86, v87);
        }
        a1 = (char *)*v42; /*0x7250e8*/
        a2 = "eType"; /*0x7250ec*/
        if ( (unsigned int)PLstrcmp(*v42, "eType") ) /*0x7250f3*/
        {
          a1 = "D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp"; /*0x7250fc*/
          LODWORD(a2) = 2383; /*0x725111*/
          MyAssertHandler( /*0x72511a*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
            2383,
            0,
            (unsigned int)"%s",
            (unsigned int)"strcmp( stateFields[0].name, \"eType\" ) == 0",
            v88);
        }
        if ( *((unsigned __int16 *)v42 + 6) != 65459 ) /*0x72512a*/
        {
          a1 = "D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp"; /*0x725130*/
          LODWORD(a2) = 2385; /*0x725145*/
          MyAssertHandler( /*0x72514e*/
            (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
            2385,
            0,
            (unsigned int)"%s",
            (unsigned int)"stateFields[0].bits == MSG_FIELD_ETYPE",
            v88);
        }
      }
    }
    else
    {
      v32 = a4; /*0x7249ac*/
      LODWORD(a2) = (_DWORD)a3; /*0x7249b8*/
      a1 = a4; /*0x7249bb*/
      Com_Memcpy(a4, a3, 256); /*0x7249be*/
    }
    v17 = 0; /*0x724a30*/
    if ( !v32 ) /*0x724a35*/
      goto LABEL_70; /*0x724a35*/
LABEL_69:
    LODWORD(a2) = 0; /*0x724ef2*/
    a1 = v32; /*0x724ef4*/
    v17 = 0; /*0x724ef7*/
    SV_ValidateEntityState(v32, 0); /*0x724ef9*/
    goto LABEL_70; /*0x724ef9*/
  }
  if ( unk_337E2E0 )
  {
    v16 = *(_DWORD *)(unk_337E2E0 + 24LL); /*0x724784*/
    if ( v16 > 1 || v16 == -1 )
    {
      a2 = "%3i: #%-3i remove\n";
      a1 = (_BYTE *)(&start__Zdynstr + 1); /*0x72479d*/
      Com_Printf(25, (unsigned int)"%3i: #%-3i remove\n", *((_DWORD *)v13 + 9), a5, v14, v15);
    }
  }
  v17 = 1; /*0x7247ac*/
LABEL_70:
  if ( *v10 == v118 ) /*0x724f05*/
    return v17; /*0x724f0b*/
  PL__stack_chk_fail(a7, a8, a9); /*0x725180*/
  v91 = v89; /*0x7251a8*/
  v93 = v92; /*0x7251ab*/
  v94 = *((_DWORD *)g_netFieldList + 2); /*0x7251b4*/
  v95 = (__int64)*g_netFieldList; /*0x7251b8*/
  if ( v89 ) /*0x7251bb*/
  {
    HIDWORD(v118) = (_DWORD)a2; /*0x7251bd*/
    *(_QWORD *)&v117.m256_f32[6] = a1; /*0x7251c0*/
    v96 = v90; /*0x7251c9*/
    SV_ValidateEntityState(v89, 0); /*0x7251cc*/
    a1 = *(char **)&v117.m256_f32[6]; /*0x7251d1*/
    LODWORD(a2) = HIDWORD(v118); /*0x7251d5*/
    v90 = v96; /*0x7251d8*/
  }
  DeltaStruct = MSG_ReadDeltaStruct((__int64)a1, (int)a2, v91, v93, v90, v94, 11, 2u, v95, 3, 1); /*0x72520d*/
  if ( v93 ) /*0x725212*/
  {
    if ( !DeltaStruct ) /*0x725216*/
      SV_ValidateEntityState(v93, 0); /*0x72521d*/
  }
  return DeltaStruct; /*0x724f0d*/
}