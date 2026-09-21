__int64 __fastcall sub_4F52E0(char *a1, __int64 a2, int a3, __int64 a4, char *a5)
{
  signed __int64 v5; // rax
  void *v6; // rsp
  char *v7; // r15
  _BYTE *v8; // rbx
  __int64 v9; // rdi
  unsigned int v11; // eax
  float v12; // xmm6_4
  __int64 v13; // rcx
  float v14; // xmm1_4
  float v15; // xmm0_4
  float v16; // xmm2_4
  bool v17; // bl
  int v18; // edx
  int v19; // r9d
  __int64 v20; // rdx
  int v21; // r12d
  int v22; // ebx
  int v23; // r13d
  int v24; // r14d
  __int64 v25; // rbp
  unsigned __int8 v26; // di
  __int64 v27; // rsi
  unsigned __int8 v28; // r12
  unsigned int v29; // eax
  int v30; // ebx
  int v31; // edx
  int v32; // r8d
  int v33; // r12d
  _WORD *v34; // r14
  int v35; // esi
  __int64 v36; // rbp
  bool v37; // cl
  int v38; // ebx
  _WORD *v39; // rsi
  bool v40; // cl
  char v41; // al
  __int64 v42; // r12
  unsigned int v43; // ebx
  unsigned int *v44; // rbp
  int v45; // r13d
  _QWORD *v46; // r14
  char *v47; // rcx
  __int64 v48; // r12
  _DWORD *v49; // rbx
  __int64 v50; // rsi
  __int64 v51; // rdx
  void **v52; // r8
  int v53; // ebp
  __int64 v54; // rcx
  __int64 v55; // r9
  _DWORD *v56; // rdx
  int v57; // esi
  void **v58; // r13
  __int64 v59; // r12
  unsigned __int8 *v60; // rbx
  _DWORD *v61; // r14
  int v62; // r12d
  __int64 v63; // rdx
  __int64 v64; // rdx
  int v65; // ebp
  char *v66; // rsi
  unsigned __int8 *v67; // rbx
  __int64 v68; // rdx
  unsigned int *v69; // r14
  __int64 v70; // rsi
  int v71; // r13d
  __int64 v72; // r15
  int v73; // ebp
  char *v74; // r12
  int v75; // eax
  int v76; // ebp
  int v77; // r14d
  _DWORD v79[12]; // [rsp+0h] [rbp-49D8h] BYREF
  __int64 v80; // [rsp+40h] [rbp-4998h]
  int v81; // [rsp+58h] [rbp-4980h]
  bool v82; // [rsp+70h] [rbp-4968h]
  char v83; // [rsp+71h] [rbp-4967h]
  char v84; // [rsp+72h] [rbp-4966h]
  int v85; // [rsp+74h] [rbp-4964h]
  __int64 v86; // [rsp+78h] [rbp-4960h]
  _DWORD *v87; // [rsp+80h] [rbp-4958h]
  char *v88; // [rsp+88h] [rbp-4950h]
  char *v89; // [rsp+90h] [rbp-4948h]
  _BYTE v90[18576]; // [rsp+A0h] [rbp-4938h] BYREF
  _QWORD v91[6]; // [rsp+4930h] [rbp-A8h] BYREF
  char *v92; // [rsp+4960h] [rbp-78h] BYREF
  int v93; // [rsp+4968h] [rbp-70h]
  __int16 v94; // [rsp+496Ch] [rbp-6Ch]
  char v95; // [rsp+496Eh] [rbp-6Ah]
  unsigned __int64 v96; // [rsp+4970h] [rbp-68h]

  v6 = alloca(v5);
  v96 = (unsigned __int64)v79 ^ qword_12F8CB0;
  v7 = a5;
  memset(v91, 0, sizeof(v91));
  v8 = (_BYTE *)a4;
  v9 = a2;
  v11 = *((__int16 *)a5 + 21) - 58;
  v87 = (_DWORD *)a4;
  v85 = a3;
  v86 = a2;
  v88 = a1;
  v89 = a5;
  if ( v11 > 0x7C3 )
    v12 = 0.0099999998;
  else
    v12 = 0.000099999997;
  a1[34] = 1;
  if ( !a4 )
  {
    v8 = v90;
    v87 = v90;
    sub_59F7E0(v90, 0, 18576);
    sub_4EC4C0(v90);
  }
  if ( a1[29] || a1[31] )
  {
    v83 = 0;
    v84 = 1;
    v82 = 1;
    MSG_WriteBit(v9, 0);
    LOBYTE(v20) = 1;
    MSG_WriteBit(v9, v20);
  }
  else
  {
    v13 = *((_QWORD *)a1 + 2);
    if ( v8
      && (*((_DWORD *)v8 + 23) & 0x4000) == 0
      && dword_B7F9C50
      && (v15 = *((float *)a5 + 31) - *(float *)(v13 + 1628),
          v14 = *((float *)a5 + 30) - *(float *)(v13 + 1624),
          v16 = *((float *)a5 + 32) - *(float *)(v13 + 1632),
          v12 >= (float)((float)((float)(v15 * v15) + (float)(v14 * v14)) + (float)(v16 * v16)))
      && *(_DWORD *)(v13 + 1636) == *((_DWORD *)a5 + 19) )
    {
      v83 = 1;
      LOBYTE(a2) = 1;
    }
    else
    {
      v83 = 0;
      a2 = 0;
    }
    MSG_WriteBit(v9, a2);
    v84 = 0;
    v17 = dword_B7F9C54 == 0;
    v82 = dword_B7F9C54 == 0;
    if ( dword_B7F9C54 )
    {
      if ( !qword_B7F9C58
        || (v18 = *a5, dword_B7F9C48 <= v18)
        || (v19 = *((_DWORD *)a5 + 19)) == 0
        || v19 != *(_DWORD *)(736LL * (char)v18 + qword_B7F9C58 + 196)
        || (_BYTE)v18 != *a1 )
      {
        v17 = 1;
      }
      v82 = v17;
    }
    MSG_WriteBit(v9, v17);
    if ( !v17 )
      a1[34] = 0;
  }
  v21 = -1;
  v22 = 0;
  v23 = -1;
  v24 = *((_DWORD *)off_12D4BA8 + 14);
  v92 = (char *)off_12D4BA8[6];
  v25 = (__int64)v92;
  if ( v24 > 0 )
  {
    v26 = v83;
    v27 = 0;
    v28 = v84;
    do
    {
      if ( (unsigned __int8)sub_4F2FE0((_DWORD)v88, v26, v28, (_DWORD)a5, (__int64)v87, v25) )
      {
        v23 = v22;
        *((_DWORD *)v91 + (v27 >> 5)) |= 1 << (v22 & 0x1F);
      }
      ++v22;
      ++v27;
      v25 += 8;
    }
    while ( v22 < v24 );
    v9 = v86;
    v21 = -1;
  }
  v29 = sub_4EC190((unsigned int)(v24 + 1));
  MSG_WriteBits(v9, (unsigned int)(v23 + 1), v29);
  v30 = 0;
  v31 = -1;
  LODWORD(v86) = -1;
  v32 = -1;
  if ( v23 >= 0 )
  {
    v33 = (int)v87;
    v34 = v92 + 6;
    v35 = 1;
    v36 = 0;
    do
    {
      if ( (*v34 & 2) == 0 || v30 == v23 )
      {
        if ( (v35 & *((_DWORD *)v91 + (v36 >> 5))) != 0 )
        {
          v37 = v88[29] || (*v34 & 4) == 0;
          LOBYTE(v81) = 1;
          LOBYTE(v80) = v37;
          Menu_IsMenuOpenAndVisible(
            (_DWORD)v88,
            v9,
            v85,
            v33,
            (__int64)a5,
            (__int64)(v34 - 3),
            v30,
            1,
            v80,
            v32,
            4,
            v81,
            0);
          v32 = v30;
        }
        v31 = v86;
      }
      else
      {
        v31 = v30;
        LODWORD(v86) = v30;
      }
      ++v30;
      v35 = __ROL4__(v35, 1);
      ++v36;
      v34 += 4;
    }
    while ( v30 <= v23 );
    v21 = -1;
  }
  v38 = 0;
  if ( v31 >= 0 )
  {
    v39 = v92 + 6;
    do
    {
      if ( (*v39 & 2) != 0 )
      {
        v40 = v88[29] || (*v39 & 4) == 0;
        LOBYTE(v81) = 0;
        LOBYTE(v80) = v40;
        v41 = Menu_IsMenuOpenAndVisible(
                (_DWORD)v88,
                v9,
                v85,
                (_DWORD)v87,
                (__int64)a5,
                (__int64)(v39 - 3),
                v38,
                1,
                v80,
                v21,
                4,
                v81,
                0);
        v31 = v86;
        if ( v41 )
          v21 = v38;
      }
      ++v38;
      v39 += 4;
    }
    while ( v38 <= v31 );
  }
  v42 = (__int64)v87;
  v43 = *((_DWORD *)a5 + 87) != v87[87];
  if ( *((_DWORD *)a5 + 88) != v87[88] )
    v43 |= 2u;
  if ( *((_DWORD *)a5 + 89) != v87[89] )
    v43 |= 4u;
  if ( *((_DWORD *)a5 + 90) != v87[90] )
    v43 |= 8u;
  if ( v43 )
  {
    MSG_WriteBitOne(v9);
    MSG_WriteBits(v9, v43, 4);
    if ( (v43 & 1) != 0 )
      sub_4EC020(v9, *((unsigned int *)a5 + 87));
    if ( (v43 & 2) != 0 )
      sub_4EC020(v9, *((unsigned int *)a5 + 88));
    if ( (v43 & 4) != 0 )
      sub_4EC020(v9, *((unsigned int *)a5 + 89));
    if ( (v43 & 8) != 0 )
      sub_4EBF30(v9, *((unsigned int *)a5 + 90));
  }
  else
  {
    MSG_WriteBitZero(v9);
  }
  v44 = (unsigned int *)(a5 + 1136);
  v45 = 0;
  v46 = a5 + 1136;
  v47 = (char *)(v42 - (_QWORD)(a5 + 1136));
  v92 = v47;
  do
  {
    if ( *v46 != *(_QWORD *)((char *)v46 + (_QWORD)v47 + 1136)
      || v46[1] != *(_QWORD *)((char *)v46 + (_QWORD)v47 + 1144)
      || v46[2] != *(_QWORD *)((char *)v46 + (_QWORD)v47 + 1152) )
    {
      MSG_WriteBitOne(v9);
      MSG_WriteBits(v9, (unsigned int)v45, 4);
      MSG_WriteBit(v9, *((unsigned __int8 *)v44 + 4));
      MSG_WriteBits(v9, *v44, 27);
      v48 = v42 - (_QWORD)v7;
      v49 = v44 + 2;
      v50 = 2;
      do
      {
        if ( *v49 == *(_DWORD *)((char *)v49 + v48) )
        {
          MSG_WriteBitZero(v9);
        }
        else
        {
          MSG_WriteBitOne(v9);
          v51 = (unsigned int)*v49;
          if ( (int)v51 >= 256 )
            v51 = 255;
          MSG_WriteBits(v9, v51, 8);
        }
        ++v49;
        --v50;
      }
      while ( v50 );
      v7 = v89;
      v47 = v92;
      v42 = (__int64)v87;
    }
    ++v45;
    v46 += 3;
    v44 += 6;
  }
  while ( v45 < 15 );
  MSG_WriteBitZero(v9);
  v52 = (void **)&v92;
  v53 = 0;
  v92 = 0;
  v54 = 0;
  v93 = 0;
  v94 = 0;
  v55 = 15;
  v95 = 0;
  v56 = (_DWORD *)(v42 + 604);
  do
  {
    if ( *(_DWORD *)&v7[(_QWORD)v56 - v42] != *v56
      || *(_QWORD *)&v7[v54 + 664] != *(_QWORD *)(v42 + v54 + 664)
      || *(_QWORD *)&v7[v54 + 672] != *(_QWORD *)(v42 + v54 + 672) )
    {
      *(_BYTE *)v52 = 1;
      ++v53;
    }
    v54 += 16;
    ++v56;
    v52 = (void **)((char *)v52 + 1);
    --v55;
  }
  while ( v55 );
  if ( v53 <= 0 )
  {
    MSG_WriteBitZero(v9);
    goto LABEL_118;
  }
  MSG_WriteBitOne(v9);
  v57 = 0;
  v58 = (void **)&v92;
  v59 = v42 - (_QWORD)v7;
  v60 = (unsigned __int8 *)(v7 + 665);
  v86 = v59;
  v61 = v7 + 604;
  while ( *(_BYTE *)v58 )
  {
    MSG_WriteBitOne(v9);
    --v53;
    if ( v82 )
      goto LABEL_104;
    if ( *(_DWORD *)&v7[4 * v57 + 604] || *(_QWORD *)&v7[16 * v57 + 664] || *(_QWORD *)&v7[16 * v57 + 672] )
    {
      MSG_WriteBitOne(v9);
LABEL_104:
      if ( *v61 == *(_DWORD *)((char *)v61 + v59) )
      {
        MSG_WriteBitZero(v9);
      }
      else
      {
        MSG_WriteBitOne(v9);
        MSG_WriteBits(v9, (unsigned int)*v61, 27);
      }
      MSG_WriteBit(v9, *(v60 - 1));
      MSG_WriteBit(v9, *v60);
      MSG_WriteBit(v9, v60[1]);
      if ( v82 )
      {
        MSG_WriteBit(v9, v60[2]);
        MSG_WriteBit(v9, v60[3]);
      }
      MSG_WriteBit(v9, v60[4]);
      MSG_WriteBits(v9, *(unsigned int *)(v60 + 7), 2);
      MSG_WriteBit(v9, v60[11]);
      MSG_WriteBit(v9, v60[12]);
      v62 = *v88 + 1;
      LOBYTE(v63) = (char)v60[13] == v62;
      MSG_WriteBit(v9, v63);
      if ( v82 || *(_DWORD *)(1011960LL * *v7 + qword_B7F9B80 + 663276) )
      {
        v64 = (unsigned int)(char)v60[13];
        if ( (_DWORD)v64 != v62 )
          sub_4EBF30(v9, v64);
      }
      v59 = v86;
      goto LABEL_114;
    }
    MSG_WriteBitZero(v9);
LABEL_114:
    ++v57;
    ++v61;
    v58 = (void **)((char *)v58 + 1);
    v60 += 16;
    if ( v57 >= 15 )
    {
      v42 = (__int64)v87;
      goto LABEL_118;
    }
  }
  MSG_WriteBitZero(v9);
  if ( v57 <= 0 || (v57 & 3) != 0 )
    goto LABEL_114;
  if ( v53 )
  {
    MSG_WriteBitOne(v9);
    goto LABEL_114;
  }
  MSG_WriteBitZero(v9);
  v42 = (__int64)v87;
LABEL_118:
  v65 = 0;
  v66 = v7 + 956;
  v67 = (unsigned __int8 *)(v7 + 960);
  do
  {
    if ( *(_QWORD *)v66 != *(_QWORD *)&v66[v42 - (_QWORD)v7]
      || *((_DWORD *)v66 + 2) != *(_DWORD *)&v66[v42 - (_QWORD)(v7 + 956) + 964] )
    {
      MSG_WriteBitOne(v9);
      MSG_WriteBits(v9, (unsigned int)v65, 4);
      if ( *((_DWORD *)v67 - 1) || !*v67 )
      {
        MSG_WriteBitZero(v9);
        MSG_WriteBits(v9, *((unsigned int *)v67 - 1), 27);
        MSG_WriteBit(v9, v67[1]);
      }
      else
      {
        MSG_WriteBitOne(v9);
        MSG_WriteBits(v9, (unsigned int)*v67 - 1, 1);
      }
      v68 = *((unsigned int *)v67 + 1);
      if ( (int)v68 >= 1024 )
        v68 = 1023;
      MSG_WriteBits(v9, v68, 10);
    }
    ++v65;
    v66 += 12;
    v67 += 12;
  }
  while ( v65 < 15 );
  MSG_WriteBitZero(v9);
  v69 = (unsigned int *)(v7 + 7780);
  v70 = v42 + 7780;
  if ( (unsigned int)sub_826230(v42 + 7780, v7 + 7780, 1296) )
  {
    v71 = *((_DWORD *)off_12D4BA8 + 18);
    v92 = (char *)off_12D4BA8[8];
    MSG_WriteBitOne(v9);
    v72 = (__int64)v92;
    v73 = 0;
    v74 = (char *)v69 - v70;
    do
    {
      MSG_WriteBits(v9, *v69, 3);
      v79[10] = v73;
      v75 = sub_4F2B30((_DWORD)v88, v70, (int)v74 + (int)v70, v71, v72);
      sub_4F47F0((_DWORD)v88, v9, v85, v70, (__int64)&v74[v70], 0, v75 - 1, v71, v72, 1, 0, 0);
      ++v73;
      v69 += 9;
      v70 += 36;
    }
    while ( v73 < 36 );
    v7 = v89;
    v42 = (__int64)v87;
  }
  else
  {
    MSG_WriteBitZero(v9);
  }
  if ( (unsigned int)sub_826230(v42 + 9088, v7 + 9088, 8640) )
  {
    MSG_WriteBitOne(v9);
    v76 = (int)v88;
    v77 = v85;
    sub_4F4B90((_DWORD)v88, v9, v85, v42 + 14848, (__int64)(v7 + 14848), 15, 4);
    sub_4F4B90(v76, v9, v77, v42 + 9088, (__int64)(v7 + 9088), 30, 5);
  }
  else
  {
    MSG_WriteBitZero(v9);
    v76 = (int)v88;
    v77 = v85;
  }
  return sub_4F5090(v76, v9, v77, dword_B7F9BF0, dword_B7F9BF8, v42 + 17728, (__int64)(v7 + 17728), dword_B7F9BF4);
}
