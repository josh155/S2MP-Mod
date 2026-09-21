char __fastcall sub_4F3B40(
        char *a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        unsigned __int16 *a6,
        int a7,
        char a8,
        float a9,
        int a10,
        unsigned int a11,
        __int32 a12,
        char a13)
{
  unsigned __int16 *v13; // r12
  int v14; // r11d
  char v16; // bl
  __int64 v18; // rax
  const __m128i *v19; // r14
  const __m128i *v20; // r10
  unsigned __int16 **v21; // r15
  int v22; // edx
  __int64 v24; // r9
  int v25; // ebx
  int v26; // eax
  int v27; // edi
  int v28; // ebx
  __int64 v29; // rcx
  float v30; // edx
  float v31; // xmm6_4
  int v32; // r13d
  int v33; // ebx
  int v34; // edi
  __int64 v35; // rdx
  __int64 v36; // rcx
  __int64 v37; // r8
  __int64 v38; // r9
  double v39; // xmm0_8
  __int32 v40; // ecx
  unsigned int v41; // ebx
  int v42; // eax
  char v43; // al
  __int64 v44; // rcx
  unsigned int v45; // ebx
  int v46; // edi
  int v47; // eax
  __int64 v48; // rcx
  unsigned int v49; // ebx
  unsigned int v50; // eax
  unsigned __int32 v51; // ebx
  unsigned int v52; // ecx
  int v54; // ebx
  int v55; // ebx
  int v56; // ebx
  int v57; // ecx
  unsigned int v58; // eax
  unsigned int v59; // eax
  float v60; // xmm0_4
  __int32 v61; // xmm1_4
  int v62; // ebx
  __int32 v63; // eax
  unsigned int v64; // [rsp+E0h] [rbp+57h]
  int v65; // [rsp+E8h] [rbp+5Fh]

  v65 = a4; /*0x4f3b45*/
  v64 = a3; /*0x4f3b4a*/
  v13 = a6; /*0x4f3b66*/
  v14 = a4; /*0x4f3b6a*/
  v16 = LOBYTE(a9); /*0x4f3b74*/
  v18 = *a6; /*0x4f3b7e*/
  v19 = (const __m128i *)(v18 + a5); /*0x4f3b83*/
  v20 = (const __m128i *)(v18 + a4); /*0x4f3b87*/
  if ( LOBYTE(a9) ) /*0x4f3b8d*/
  {
    v21 = (unsigned __int16 **)(v18 + a4); /*0x4f3b9c*/
  }
  else
  {
    LODWORD(a6) = 0; /*0x4f3b8f*/
    v21 = &a6; /*0x4f3b96*/
  }
  if ( (_BYTE)a12 ) /*0x4f3ba6*/
  {
    if ( !a8 ) /*0x4f3bac*/
    {
      v22 = (1 << abs16(v13[1])) - 1; /*0x4f3bd4*/
      if ( (v22 & _mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128(v20), _mm_loadu_si128(v19)))) == v22 /*0x4f3bec*/
        || (unsigned __int8)sub_4F0CE0(v20, v19, (unsigned int)(__int16)v13[2]) )
      {
        return 0; /*0x4f3bf7*/
      }
    }
    sub_4F2A70(a2, (unsigned int)(a7 - a10), a11); /*0x4f3c0f*/
    v14 = v65; /*0x4f3c14*/
  }
  v24 = (unsigned int)(__int16)v13[2]; /*0x4f3c18*/
  switch ( v13[2] ) /*0x4f3c4e*/
  {
    case 0xFF90: /*0x4f3c4e*/
    case 0xFFC0: /*0x4f3c4e*/
      sub_5B0C40(v19, &a12); /*0x4f3da4*/
      a9 = *(float *)v21; /*0x4f3dac*/
      if ( v16 ) /*0x4f3db4*/
        sub_5B0C40(v21, &a9); /*0x4f3dc0*/
      goto LABEL_22; /*0x4f3dc5*/
    case 0xFF91: /*0x4f3c4e*/
    case 0xFFBF: /*0x4f3c4e*/
      sub_5B0C30(v19, &a12); /*0x4f3d77*/
      a9 = *(float *)v21; /*0x4f3d7f*/
      if ( v16 ) /*0x4f3d87*/
        sub_5B0C30(v21, &a9); /*0x4f3d93*/
      goto LABEL_22; /*0x4f3d98*/
    case 0xFF92: /*0x4f3c4e*/
      sub_4F6EB0(a2, v21, v19); /*0x4f3c6c*/
      return 1; /*0x4f3c71*/
    case 0xFF94: /*0x4f3c4e*/
    case 0xFFBE: /*0x4f3c4e*/
      sub_5B0C20(v19, &a12); /*0x4f3d31*/
      a9 = *(float *)v21; /*0x4f3d39*/
      if ( v16 ) /*0x4f3d41*/
        sub_5B0C20(v21, &a9); /*0x4f3d4d*/
LABEL_22:
      sub_4F6DA0(a2, &a9, &a12); /*0x4f3d52*/
      return 1; /*0x4f3d68*/
    case 0xFF95: /*0x4f3c4e*/
      sub_4F3170(a2, v21, v19); /*0x4f3c59*/
      return 1; /*0x4f3c5e*/
    case 0xFF96: /*0x4f3c4e*/
      sub_5B0C20(v19, &a12); /*0x4f3c80*/
      a9 = *(float *)v21; /*0x4f3c88*/
      if ( v16 ) /*0x4f3c90*/
        sub_5B0C20(v21, &a9); /*0x4f3c9c*/
      goto LABEL_15; /*0x4f3c9c*/
    case 0xFF97: /*0x4f3c4e*/
      sub_5B0C30(v19, &a12); /*0x4f3cd4*/
      a9 = *(float *)v21; /*0x4f3cdc*/
      if ( v16 ) /*0x4f3ce4*/
        sub_5B0C30(v21, &a9); /*0x4f3cf0*/
      goto LABEL_15; /*0x4f3cf5*/
    case 0xFF98: /*0x4f3c4e*/
      sub_5B0C40(v19, &a12); /*0x4f3d01*/
      a9 = *(float *)v21; /*0x4f3d09*/
      if ( v16 ) /*0x4f3d11*/
        sub_5B0C40(v21, &a9); /*0x4f3d1d*/
LABEL_15:
      sub_4F6F70((_DWORD)a1, a2, (__int16)v13[2], (unsigned int)&a9, (__int64)&a12); /*0x4f3ca1*/
      return 1; /*0x4f3cc5*/
    case 0xFF99: /*0x4f3c4e*/
      v40 = v19->m128i_i32[0]; /*0x4f417d*/
      v41 = v19->m128i_i32[0] / 50; /*0x4f4191*/
      if ( v19->m128i_i32[0] >= 800 ) /*0x4f4199*/
        goto LABEL_60; /*0x4f4199*/
      v42 = 50 * v41; /*0x4f419b*/
      goto LABEL_58; /*0x4f419e*/
    case 0xFF9A: /*0x4f3c4e*/
      v40 = v19->m128i_i32[0]; /*0x4f411a*/
      v41 = v19->m128i_i32[0] / 250; /*0x4f412e*/
      if ( v19->m128i_i32[0] >= 4000 ) /*0x4f4136*/
        goto LABEL_60; /*0x4f4136*/
      v42 = 250 * v41; /*0x4f4138*/
LABEL_58:
      if ( v40 == v42 ) /*0x4f4140*/
      {
        MSG_WriteBitZero(a2); /*0x4f4145*/
        MSG_WriteBits(a2, v41, 4); /*0x4f4155*/
      }
      else
      {
LABEL_60:
        MSG_WriteBitOne(a2); /*0x4f415f*/
        MSG_WriteBits(a2, v19->m128i_u32[0], 16); /*0x4f4173*/
      }
      return 1; /*0x4f415a*/
    case 0xFF9B: /*0x4f3c4e*/
      v29 = a2; /*0x4f3e74*/
      if ( !v19->m128i_i16[0] ) /*0x4f3e77*/
        goto LABEL_122; /*0x4f3e77*/
      MSG_WriteBitOne(a2); /*0x4f3e7d*/
      sub_4EC020(a2, v19->m128i_u32[0]); /*0x4f3e88*/
      return 1; /*0x4f3e8d*/
    case 0xFF9C: /*0x4f3c4e*/
      sub_4F3550(a1, a2); /*0x4f400d*/
      return 1; /*0x4f4012*/
    case 0xFF9D: /*0x4f3c4e*/
      v31 = *(float *)v19->m128i_i32; /*0x4f3f5e*/
      v32 = (int)*(float *)v21; /*0x4f3f69*/
      v33 = (int)*(float *)v19->m128i_i32; /*0x4f3f6e*/
      if ( *(float *)v19->m128i_i32 == 0.0 && LODWORD(v31) != 0x80000000 ) /*0x4f3f7b*/
        goto LABEL_121; /*0x4f3f82*/
      MSG_WriteBitOne(a2); /*0x4f3f8b*/
      if ( LODWORD(v31) == 0x80000000 || (float)v33 != v31 || (v34 = v33 + 2048, (unsigned int)(v33 + 2048) > 0xFFF) ) /*0x4f3fc4*/
      {
LABEL_32:
        MSG_WriteBitOne(a2); /*0x4f3e44*/
LABEL_33:
        sub_4EBFF0(a2, (unsigned int)(*(_DWORD *)v21 ^ v19->m128i_i32[0])); /*0x4f3e4c*/
      }
      else
      {
        MSG_WriteBitZero(a2); /*0x4f3fcd*/
        MSG_WriteBits(a2, v34 ^ (unsigned int)(v32 + 2048), 4); /*0x4f3fe6*/
        sub_4EBF30(a2, (unsigned int)((v34 ^ (v32 + 2048)) >> 4)); /*0x4f3ff3*/
      }
      return 1; /*0x4f3ff8*/
    case 0xFF9E: /*0x4f3c4e*/
      v51 = v19->m128i_i32[0]; /*0x4f4310*/
      v52 = (*(_DWORD *)v21 ^ v19->m128i_i32[0]) & 0x1FFFFFFF; /*0x4f4318*/
      if ( !v52 || ((v52 - 1) & v52) != 0 ) /*0x4f4325*/
      {
        MSG_WriteBitOne(a2); /*0x4f4360*/
        MSG_WriteBits(a2, v51, 29); /*0x4f4370*/
      }
      else
      {
        if ( !_BitScanReverse((unsigned int *)&v54, v52) ) /*0x4f4327*/
          v55 = 32; /*0x4f4336*/
        else
          v55 = v54 ^ 0x1F; /*0x4f4331*/
        MSG_WriteBitZero(a2); /*0x4f433e*/
        MSG_WriteBits(a2, (unsigned int)(31 - v55), 5); /*0x4f4353*/
      }
      return 1; /*0x4f4358*/
    case 0xFF9F: /*0x4f3c4e*/
    case 0xFFB6: /*0x4f3c4e*/
    case 0xFFB8: /*0x4f3c4e*/
    case 0xFFBA: /*0x4f3c4e*/
      sub_4F6340(a2, v64, v19->m128i_u32[0]); /*0x4f42ed*/
      return 1; /*0x4f42f2*/
    case 0xFFA0: /*0x4f3c4e*/
      v56 = sub_4EC3F0(v19, (unsigned int)(__int16)v13[1]); /*0x4f4388*/
      v44 = a2; /*0x4f438a*/
      if ( v56 == 2046 ) /*0x4f4392*/
        goto LABEL_70; /*0x4f4392*/
      MSG_WriteBitZero(a2); /*0x4f4398*/
      v44 = a2; /*0x4f439d*/
      if ( !v56 ) /*0x4f43a2*/
        goto LABEL_70; /*0x4f43a2*/
      MSG_WriteBitZero(a2); /*0x4f43a8*/
      MSG_WriteBits(a2, (unsigned int)v56, 3); /*0x4f43b8*/
      sub_4EBF30(a2, (unsigned int)(v56 >> 3)); /*0x4f43c5*/
      return 1; /*0x4f43ca*/
    case 0xFFA1: /*0x4f3c4e*/
      MSG_WriteBits(a2, (unsigned int)(v19->m128i_i32[0] / 100), 7); /*0x4f45eb*/
      return 1; /*0x4f45f0*/
    case 0xFFA2: /*0x4f3c4e*/
      v57 = -1; /*0x4f43cf*/
      if ( a13 ) /*0x4f43d9*/
        v57 = 4 * *(char *)(a5 + 12) + ((unsigned __int64)(*v13 - 44) >> 3); /*0x4f43f1*/
      sub_4F6CA0((_DWORD)a1, a2, v14, a5, (__int64)v13, v57); /*0x4f4408*/
      return 1; /*0x4f440d*/
    case 0xFFA3: /*0x4f3c4e*/
      v58 = sub_4EC3F0(v19, (unsigned int)(__int16)v13[1]); /*0x4f441b*/
      MSG_WriteBits(a2, v58, 27); /*0x4f442b*/
      return 1; /*0x4f4430*/
    case 0xFFA4: /*0x4f3c4e*/
    case 0xFFA5: /*0x4f3c4e*/
      sub_4F7040((_DWORD)a1, *a1, (_DWORD)a1 + 4, a2, v24, v19->m128i_i32[0], *(_DWORD *)v21); /*0x4f45ba*/
      return 1; /*0x4f45bf*/
    case 0xFFA6: /*0x4f3c4e*/
      v60 = *(float *)v21; /*0x4f45c4*/
      v61 = v19->m128i_i32[0]; /*0x4f45c9*/
      goto LABEL_107; /*0x4f45ce*/
    case 0xFFA7: /*0x4f3c4e*/
      v25 = (int)*(float *)v21; /*0x4f3ddf*/
      v26 = (int)*(float *)v19->m128i_i32; /*0x4f3de4*/
      if ( (float)v26 != *(float *)v19->m128i_i32 ) /*0x4f3df4*/
        goto LABEL_32; /*0x4f3df4*/
      if ( v19->m128i_i32[0] == 0x80000000 ) /*0x4f3dfb*/
        goto LABEL_32; /*0x4f3dfb*/
      v27 = v26 + 4096; /*0x4f3e04*/
      if ( (unsigned int)(v26 + 4096) > 0x1FFF ) /*0x4f3e10*/
        goto LABEL_32; /*0x4f3e10*/
      MSG_WriteBitZero(a2); /*0x4f3e15*/
      v28 = v27 ^ (v25 + 4096); /*0x4f3e26*/
      MSG_WriteBits(a2, (unsigned int)v28, 5); /*0x4f3e2d*/
      sub_4EBF30(a2, (unsigned int)(v28 >> 5)); /*0x4f3e3a*/
      return 1; /*0x4f3e3f*/
    case 0xFFA8: /*0x4f3c4e*/
      goto LABEL_33;
    case 0xFFA9: /*0x4f3c4e*/
      sub_4EBBE0(a2, 0); /*0x4f40dc*/
      return 1; /*0x4f40e1*/
    case 0xFFAA: /*0x4f3c4e*/
      v39 = sub_8295A0(a1, 0, a3, v24); /*0x4f40fe*/
      MSG_WriteBits(a2, (unsigned int)(int)v39, 6); /*0x4f4110*/
      return 1; /*0x4f4115*/
    case 0xFFAB: /*0x4f3c4e*/
      v43 = *((_BYTE *)v21 + 3); /*0x4f41a0*/
      if ( (v43 == -1 && !v19->m128i_i8[3] || !v43 && v19->m128i_i8[3] == -1) /*0x4f41ce*/
        && *(_WORD *)v21 == v19->m128i_i16[0]
        && *((_BYTE *)v21 + 2) == v19->m128i_i8[2] )
      {
        v44 = a2; /*0x4f41d0*/
LABEL_70:
        MSG_WriteBitOne(v44); /*0x4f41d3*/
      }
      else
      {
        MSG_WriteBitZero(a2); /*0x4f41e0*/
        if ( *(_BYTE *)v21 == v19->m128i_i8[0] /*0x4f4202*/
          && *((_BYTE *)v21 + 1) == v19->m128i_i8[1]
          && *((_BYTE *)v21 + 2) == v19->m128i_i8[2] )
        {
          MSG_WriteBitOne(a2); /*0x4f4207*/
        }
        else
        {
          MSG_WriteBitZero(a2); /*0x4f4211*/
          sub_4EBF30(a2, v19->m128i_u8[0]); /*0x4f421d*/
          sub_4EBF30(a2, v19->m128i_u8[1]); /*0x4f422a*/
          sub_4EBF30(a2, v19->m128i_u8[2]); /*0x4f4237*/
        }
        MSG_WriteBits(a2, v19->m128i_u8[3] >> 3, 5); /*0x4f424d*/
      }
      return 1; /*0x4f41d8*/
    case 0xFFAC: /*0x4f3c4e*/
      MSG_WriteBits(a2, v19->m128i_u32[0], 9); /*0x4f42da*/
      return 1; /*0x4f42df*/
    case 0xFFAD: /*0x4f3c4e*/
      sub_5B0C20(v19, &a12); /*0x4f4466*/
      a9 = *(float *)v21; /*0x4f446e*/
      if ( v16 ) /*0x4f4476*/
        sub_5B0C20(v21, &a9); /*0x4f4482*/
      goto LABEL_100; /*0x4f4482*/
    case 0xFFAE: /*0x4f3c4e*/
      sub_5B0C30(v19, &a12); /*0x4f44d0*/
      a9 = *(float *)v21; /*0x4f44d8*/
      if ( v16 ) /*0x4f44e0*/
        sub_5B0C30(v21, &a9); /*0x4f44ec*/
LABEL_100:
      sub_4F7040((_DWORD)a1, *a1, (_DWORD)a1 + 4, a2, (__int16)v13[2], a12, LODWORD(a9)); /*0x4f4487*/
      return 1; /*0x4f44c1*/
    case 0xFFAF: /*0x4f3c4e*/
      sub_5B0C40(v19, &a12); /*0x4f453a*/
      a9 = *(float *)v21; /*0x4f4542*/
      if ( v16 ) /*0x4f454a*/
        sub_5B0C40(v21, &a9); /*0x4f4556*/
      v60 = a9; /*0x4f455b*/
      v61 = a12; /*0x4f4563*/
LABEL_107:
      sub_4F7100((_DWORD)a1, *a1, (_DWORD)a1 + 4, a2, v61, LODWORD(v60)); /*0x4f456b*/
      return 1; /*0x4f458b*/
    case 0xFFB0: /*0x4f3c4e*/
    case 0xFFB2: /*0x4f3c4e*/
    case 0xFFB7: /*0x4f3c4e*/
    case 0xFFB9: /*0x4f3c4e*/
    case 0xFFBB: /*0x4f3c4e*/
    case 0xFFBC: /*0x4f3c4e*/
      sub_4EBFF0(a2, v19->m128i_u32[0]); /*0x4f3e65*/
      return 1; /*0x4f3e6a*/
    case 0xFFB1: /*0x4f3c4e*/
      sub_8295A0(a1, 0, a3, v24); /*0x4f4043*/
      sub_8295A0(v36, v35, v37, v38); /*0x4f4083*/
      sub_4F3690(a1, a2); /*0x4f40c4*/
      return 1; /*0x4f40cf*/
    case 0xFFB3: /*0x4f3c4e*/
      v59 = sub_4EC3F0(v19, (unsigned int)(__int16)v13[1]); /*0x4f443e*/
      sub_4F7270(a1, a2, v59, 8); /*0x4f4452*/
      return 1; /*0x4f4457*/
    case 0xFFB4: /*0x4f3c4e*/
      v48 = a2; /*0x4f45f8*/
      v62 = v19->m128i_i32[0] - *(_DWORD *)v21; /*0x4f45fb*/
      if ( (int)abs32(v62) >= 8 ) /*0x4f4608*/
        goto LABEL_79; /*0x4f4608*/
      MSG_WriteBitOne(a2); /*0x4f460e*/
      MSG_WriteBits(a2, (unsigned int)(v62 + 8), 4); /*0x4f461f*/
      return 1; /*0x4f4624*/
    case 0xFFB5: /*0x4f3c4e*/
      v45 = (__int16)v13[1]; /*0x4f4257*/
      v46 = sub_4EC3F0(v21, v45); /*0x4f426c*/
      v47 = sub_4EC3F0(v19, v45); /*0x4f426e*/
      v48 = a2; /*0x4f4275*/
      v49 = v47 - v46 - 1; /*0x4f4278*/
      if ( v49 > 0xF ) /*0x4f427e*/
      {
LABEL_79:
        MSG_WriteBitZero(v48); /*0x4f42a1*/
        sub_4F72E0((_DWORD)a1, a2, (_DWORD)v21, (_DWORD)v19, (__int16)v13[1], 8); /*0x4f42c4*/
      }
      else
      {
        MSG_WriteBitOne(a2); /*0x4f4280*/
        v50 = sub_4EC190(16); /*0x4f428a*/
        MSG_WriteBits(a2, v49, v50); /*0x4f4297*/
      }
      return 1; /*0x4f429c*/
    case 0xFFBD: /*0x4f3c4e*/
      MSG_WriteBits(a2, (unsigned int)(v19->m128i_i32[0] + 10), 5); /*0x4f4306*/
      return 1; /*0x4f430b*/
    case 0xFFC1: /*0x4f3c4e*/
      sub_5B0C20(v19, &a12); /*0x4f3e9c*/
      v30 = *(float *)v21; /*0x4f3ea1*/
      a9 = *(float *)v21; /*0x4f3ea4*/
      if ( v16 ) /*0x4f3eac*/
      {
        sub_5B0C20(v21, &a9); /*0x4f3eb8*/
        v30 = a9; /*0x4f3ebd*/
      }
      goto LABEL_45; /*0x4f3ebd*/
    case 0xFFC2: /*0x4f3c4e*/
      sub_5B0C30(v19, &a12); /*0x4f3ee0*/
      v30 = *(float *)v21; /*0x4f3ee5*/
      a9 = *(float *)v21; /*0x4f3ee8*/
      if ( v16 ) /*0x4f3ef0*/
      {
        sub_5B0C30(v21, &a9); /*0x4f3efc*/
        v30 = a9; /*0x4f3f01*/
      }
      goto LABEL_45; /*0x4f3f01*/
    case 0xFFC3: /*0x4f3c4e*/
      sub_5B0C40(v19, &a12); /*0x4f3f24*/
      v30 = *(float *)v21; /*0x4f3f29*/
      a9 = *(float *)v21; /*0x4f3f2c*/
      if ( v16 ) /*0x4f3f34*/
      {
        sub_5B0C40(v21, &a9); /*0x4f3f40*/
        v30 = a9; /*0x4f3f45*/
      }
LABEL_45:
      sub_4EBFF0(a2, (unsigned int)a12 ^ LODWORD(v30)); /*0x4f3f4b*/
      break; /*0x4f3f59*/
    case 0u: /*0x4f3c4e*/
      sub_4F6DA0(a2, v21, v19); /*0x4f3dd0*/
      break; /*0x4f3dd5*/
    default:
      switch ( v13[1] ) /*0x4f4640*/
      {
        case 0xFFFC: /*0x4f4640*/
        case 4u: /*0x4f4640*/
          v63 = v19->m128i_i32[0]; /*0x4f4642*/
          break; /*0x4f4645*/
        case 0xFFFE: /*0x4f4640*/
          v63 = v19->m128i_i16[0]; /*0x4f464d*/
          break; /*0x4f4651*/
        case 0xFFFF: /*0x4f4640*/
          v63 = v19->m128i_i8[0]; /*0x4f4659*/
          break; /*0x4f4659*/
        case 1u: /*0x4f4640*/
          v63 = v19->m128i_u8[0]; /*0x4f4653*/
          break; /*0x4f4657*/
        case 2u: /*0x4f4640*/
          v63 = v19->m128i_u16[0]; /*0x4f4647*/
          break; /*0x4f464b*/
        default:
          goto LABEL_121;
      }
      if ( v63 ) /*0x4f465f*/
      {
        MSG_WriteBitOne(a2); /*0x4f4664*/
        sub_4F72E0((_DWORD)a1, a2, (_DWORD)v21, (_DWORD)v19, (__int16)v13[1], (__int16)v13[2]); /*0x4f467d*/
      }
      else
      {
LABEL_121:
        v29 = a2; /*0x4f4682*/
LABEL_122:
        MSG_WriteBitZero(v29); /*0x4f4685*/
      }
      break; /*0x4f467d*/
  }
  return 1; /*0x4f469c*/
}