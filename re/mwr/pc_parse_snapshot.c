__int64 __fastcall sub_342770(unsigned int a1, _DWORD *a2)
{
  __int64 v4; // rax
  __int64 v5; // rdi
  __int64 v6; // rsi
  __int64 v7; // rbx
  int v8; // r13d
  int v9; // eax
  _OWORD *v10; // rdi
  bool v11; // zf
  int v12; // ebp
  int v13; // eax
  __int64 v14; // r8
  _BYTE *v15; // r15
  _BYTE *v16; // r9
  char *v17; // r8
  _BYTE *v18; // r8
  __int64 v19; // rcx
  __int64 v20; // rcx
  unsigned __int64 v21; // r12
  int v22; // eax
  int v23; // ecx
  int v24; // edx
  int v25; // r8d
  unsigned __int64 v26; // r8
  __int64 v27; // r10
  __int64 v28; // rax
  __int64 v29; // rcx
  __int128 v30; // xmm0
  __int64 v31; // r8
  __int64 v32; // rcx
  __int64 v33; // rax
  __int128 v34; // xmm0
  int v35; // ebx
  int v36; // edi
  __int64 v37; // r11
  int v38; // r9d
  unsigned __int64 v39; // rdx
  __int128 v40; // xmm0
  _BYTE v42[56]; // [rsp+30h] [rbp-38h] BYREF
  __int64 v43; // [rsp+80h] [rbp+18h]

  sub_59D300(v42, 19064); /*0x342796*/
  v4 = sub_59D470(v42); /*0x3427a0*/
  v5 = qword_2EC8510; /*0x3427a5*/
  v6 = qword_2EC84F0; /*0x3427ae*/
  v43 = qword_2EC8510; /*0x3427be*/
  v7 = v4; /*0x3427c6*/
  sub_826080(v4, 0, 19064); /*0x3427c9*/
  *(_DWORD *)(v7 + 19060) = *(_DWORD *)(v5 + 262456); /*0x3427d7*/
  *(_DWORD *)(v7 + 19004) = sub_4EB7D0(a2); /*0x3427e2*/
  *(_DWORD *)(v7 + 19008) = *(_DWORD *)(v5 + 262452); /*0x3427f1*/
  v8 = sub_4EB510(a2); /*0x3427fc*/
  if ( v8 ) /*0x342801*/
    *(_DWORD *)(v7 + 19012) = *(_DWORD *)(v7 + 19008) - v8; /*0x342818*/
  else
    *(_DWORD *)(v7 + 19012) = -1; /*0x342803*/
  v9 = sub_4EB510(a2); /*0x342826*/
  *(_DWORD *)(v7 + 19000) = v9; /*0x34282b*/
  v10 = &unk_2F78770; /*0x342831*/
  v11 = (v9 & 8) == 0; /*0x342838*/
  v12 = 0; /*0x34283a*/
  v13 = dword_2F7D1E8; /*0x34283f*/
  if ( !v11 ) /*0x342845*/
    v13 = 0; /*0x342845*/
  dword_2F7D1E8 = v13; /*0x342848*/
  v14 = *(int *)(v7 + 19012); /*0x34284e*/
  if ( (int)v14 > 0 ) /*0x342858*/
  {
    v15 = (_BYTE *)(*(_QWORD *)(v6 + 36768) + 19064 * (v14 & *(int *)(v6 + 36744))); /*0x342893*/
    if ( !(unsigned __int8)sub_340490(v6, v15) ) /*0x3428a4*/
      goto LABEL_16; /*0x3428a4*/
    *(_DWORD *)(v7 + 18980) = 1; /*0x3428a6*/
  }
  else
  {
    v11 = (*(_BYTE *)(v7 + 19000) & 8) == 0; /*0x34285a*/
    *(_DWORD *)(v7 + 18980) = 1; /*0x342861*/
    if ( v11 ) /*0x34286b*/
    {
      if ( dword_2F7D1E8 ) /*0x342873*/
      {
        v15 = &unk_2F78770; /*0x342875*/
        goto LABEL_13; /*0x342878*/
      }
LABEL_16:
      sub_4EB190(a2); /*0x3428cc*/
      return sub_59D350(v42); /*0x3428d4*/
    }
    v15 = 0; /*0x34287a*/
  }
LABEL_13:
  if ( (int)MSG_ReadShort(a2) <= 0 ) /*0x3428bf*/
  {
    v16 = 0; /*0x3428de*/
  }
  else
  {
    if ( !v15 ) /*0x3428c4*/
    {
      *(_DWORD *)(v7 + 18980) = 0; /*0x3428c6*/
      goto LABEL_16; /*0x3428c6*/
    }
    v16 = v15; /*0x3428d9*/
  }
  sub_4EE4E0(a1, a2, *(unsigned int *)(v7 + 19004), v16, v7, 1); /*0x3428f8*/
  if ( !v15 || (v15[19000] & 8) != 0 ) /*0x34290a*/
    v17 = 0; /*0x342915*/
  else
    v17 = v15 + 18576; /*0x34290c*/
  sub_4EF6C0(a2, *(unsigned int *)(v7 + 19004), v17, v7 + 18576); /*0x342928*/
  v18 = v15; /*0x342930*/
  if ( !v8 ) /*0x342939*/
    v18 = 0; /*0x342939*/
  sub_342240(v6, a2, v18, v7); /*0x342940*/
  sub_4EC1E0(a2); /*0x342948*/
  sub_341D30(v6, (_DWORD)a2, *(_DWORD *)(v7 + 19004), (_DWORD)v15, v7); /*0x342962*/
  sub_4EC1E0(a2); /*0x34296a*/
  v19 = *(_DWORD *)(v7 + 19000) >> 5; /*0x342975*/
  LOBYTE(v19) = (*(_DWORD *)(v7 + 19000) & 0x20) != 0; /*0x342978*/
  sub_7F8F0(v19); /*0x34297b*/
  LOBYTE(v20) = *(_DWORD *)(v7 + 9076) != 0; /*0x342986*/
  sub_7F980(v20); /*0x342989*/
  sub_7E430(); /*0x34298e*/
  LODWORD(v21) = (_DWORD)v15; /*0x342993*/
  if ( !v8 ) /*0x342999*/
  {
    LODWORD(v21) = 0; /*0x34299e*/
    v22 = sub_4EB510(a2); /*0x3429a1*/
    if ( v22 ) /*0x3429a8*/
      v21 = *(_QWORD *)(v6 + 36768) + 19064 * (*(int *)(v6 + 36744) & (unsigned __int64)(*(_DWORD *)(v7 + 19008) - v22)); /*0x3429c6*/
  }
  sub_341960(v6, (_DWORD)a2, *(_DWORD *)(v7 + 19004), v21, v7); /*0x3429e2*/
  sub_4EC1E0(a2); /*0x3429ea*/
  sub_341580(v6, (_DWORD)a2, *(_DWORD *)(v7 + 19004), (_DWORD)v15, v7); /*0x342a04*/
  sub_308550(a2); /*0x342a0c*/
  sub_342300(v6, (_DWORD)a2, *(_DWORD *)(v7 + 19004), (_DWORD)v15, v7); /*0x342a26*/
  if ( *a2 ) /*0x342a2b*/
  {
    *(_DWORD *)(v7 + 18980) = 0; /*0x342a30*/
  }
  else if ( *(_DWORD *)(v7 + 18980) ) /*0x342a3b*/
  {
    v23 = *(_DWORD *)(v7 + 19008); /*0x342a4d*/
    v24 = *(_DWORD *)(v6 + 19016) + 1; /*0x342a53*/
    v25 = *(_DWORD *)(v6 + 36740); /*0x342a55*/
    if ( v23 - v24 >= v25 ) /*0x342a63*/
      v24 = v23 - v25; /*0x342a67*/
    if ( v24 < v23 ) /*0x342a6c*/
    {
      do /*0x342aaf*/
      {
        v26 = *(int *)(v6 + 36744); /*0x342a70*/
        if ( (v24 & (unsigned int)v26) != (*(_DWORD *)(v7 + 19008) & *(_DWORD *)(v6 + 36744)) ) /*0x342a87*/
          *(_DWORD *)(19064 * (v24 & v26) + *(_QWORD *)(v6 + 36768) + 18980) = 0; /*0x342aa0*/
        ++v24; /*0x342aa7*/
      }
      while ( v24 < *(_DWORD *)(v7 + 19008) ); /*0x342aaf*/
    }
    v27 = 148; /*0x342ab8*/
    if ( (*(_BYTE *)(v7 + 19000) & 8) != 0 ) /*0x342abe*/
    {
      v28 = v7; /*0x342ac4*/
      v29 = 148; /*0x342ac7*/
      do /*0x342b21*/
      {
        v10 += 8; /*0x342ad0*/
        v30 = *(_OWORD *)v28; /*0x342ad7*/
        v28 += 128; /*0x342ada*/
        *(v10 - 8) = v30; /*0x342ae1*/
        *(v10 - 7) = *(_OWORD *)(v28 - 112); /*0x342ae9*/
        *(v10 - 6) = *(_OWORD *)(v28 - 96); /*0x342af1*/
        *(v10 - 5) = *(_OWORD *)(v28 - 80); /*0x342af9*/
        *(v10 - 4) = *(_OWORD *)(v28 - 64); /*0x342b01*/
        *(v10 - 3) = *(_OWORD *)(v28 - 48); /*0x342b09*/
        *(v10 - 2) = *(_OWORD *)(v28 - 32); /*0x342b11*/
        *(v10 - 1) = *(_OWORD *)(v28 - 16); /*0x342b19*/
        --v29; /*0x342b1d*/
      }
      while ( v29 ); /*0x342b21*/
      *v10 = *(_OWORD *)v28; /*0x342b26*/
      v10[1] = *(_OWORD *)(v28 + 16); /*0x342b2d*/
      v10[2] = *(_OWORD *)(v28 + 32); /*0x342b35*/
      v10[3] = *(_OWORD *)(v28 + 48); /*0x342b3d*/
      v10[4] = *(_OWORD *)(v28 + 64); /*0x342b45*/
      v10[5] = *(_OWORD *)(v28 + 80); /*0x342b4d*/
      v10[6] = *(_OWORD *)(v28 + 96); /*0x342b55*/
      *((_QWORD *)v10 + 14) = *(_QWORD *)(v28 + 112); /*0x342b5d*/
    }
    v31 = v6 + 8; /*0x342b67*/
    *(_DWORD *)(v6 + 19072) = *(_DWORD *)(v6 + 19012); /*0x342b6b*/
    v32 = v6 + 8; /*0x342b71*/
    v33 = 148; /*0x342b74*/
    do /*0x342bd1*/
    {
      v32 += 128; /*0x342b80*/
      v34 = *(_OWORD *)v7; /*0x342b87*/
      v7 += 128; /*0x342b8a*/
      *(_OWORD *)(v32 - 128) = v34; /*0x342b91*/
      *(_OWORD *)(v32 - 112) = *(_OWORD *)(v7 - 112); /*0x342b99*/
      *(_OWORD *)(v32 - 96) = *(_OWORD *)(v7 - 96); /*0x342ba1*/
      *(_OWORD *)(v32 - 80) = *(_OWORD *)(v7 - 80); /*0x342ba9*/
      *(_OWORD *)(v32 - 64) = *(_OWORD *)(v7 - 64); /*0x342bb1*/
      *(_OWORD *)(v32 - 48) = *(_OWORD *)(v7 - 48); /*0x342bb9*/
      *(_OWORD *)(v32 - 32) = *(_OWORD *)(v7 - 32); /*0x342bc1*/
      *(_OWORD *)(v32 - 16) = *(_OWORD *)(v7 - 16); /*0x342bc9*/
      --v33; /*0x342bcd*/
    }
    while ( v33 ); /*0x342bd1*/
    *(_OWORD *)v32 = *(_OWORD *)v7; /*0x342bd6*/
    *(_OWORD *)(v32 + 16) = *(_OWORD *)(v7 + 16); /*0x342bdd*/
    *(_OWORD *)(v32 + 32) = *(_OWORD *)(v7 + 32); /*0x342be5*/
    *(_OWORD *)(v32 + 48) = *(_OWORD *)(v7 + 48); /*0x342bed*/
    *(_OWORD *)(v32 + 64) = *(_OWORD *)(v7 + 64); /*0x342bf5*/
    *(_OWORD *)(v32 + 80) = *(_OWORD *)(v7 + 80); /*0x342bfd*/
    *(_OWORD *)(v32 + 96) = *(_OWORD *)(v7 + 96); /*0x342c05*/
    *(_QWORD *)(v32 + 112) = *(_QWORD *)(v7 + 112); /*0x342c0d*/
    v35 = *(_DWORD *)(v6 + 36740); /*0x342c11*/
    *(_DWORD *)(v6 + 19024) = 999; /*0x342c17*/
    if ( v35 > 0 ) /*0x342c23*/
    {
      v36 = *(_DWORD *)(v6 + 36744); /*0x342c2d*/
      v37 = *(_QWORD *)(v6 + 36760); /*0x342c33*/
      v38 = *(_DWORD *)(v43 + 524872) - 1; /*0x342c45*/
      while ( *(_DWORD *)(v6 + 84) < *(_DWORD *)(v37 + 12LL * (v36 & v38) + 4) ) /*0x342c61*/
      {
        ++v12; /*0x342c63*/
        --v38; /*0x342c65*/
        if ( v12 >= v35 ) /*0x342c6a*/
          goto LABEL_49; /*0x342c6a*/
      }
      *(_DWORD *)(v6 + 19024) = dword_2ED2080 - *(_DWORD *)(v37 + 12LL * (v36 & v38) + 8); /*0x342c80*/
    }
LABEL_49:
    v39 = *(_QWORD *)(v6 + 36768) + 19064 * (*(int *)(v6 + 19016) & (unsigned __int64)*(int *)(v6 + 36744)); /*0x342c86*/
    do /*0x342cfe*/
    {
      v39 += 128LL; /*0x342ca5*/
      v40 = *(_OWORD *)v31; /*0x342cac*/
      v31 += 128; /*0x342cb0*/
      *(_OWORD *)(v39 - 128) = v40; /*0x342cb7*/
      *(_OWORD *)(v39 - 112) = *(_OWORD *)(v31 - 112); /*0x342cc0*/
      *(_OWORD *)(v39 - 96) = *(_OWORD *)(v31 - 96); /*0x342cc9*/
      *(_OWORD *)(v39 - 80) = *(_OWORD *)(v31 - 80); /*0x342cd2*/
      *(_OWORD *)(v39 - 64) = *(_OWORD *)(v31 - 64); /*0x342cdb*/
      *(_OWORD *)(v39 - 48) = *(_OWORD *)(v31 - 48); /*0x342ce4*/
      *(_OWORD *)(v39 - 32) = *(_OWORD *)(v31 - 32); /*0x342ced*/
      *(_OWORD *)(v39 - 16) = *(_OWORD *)(v31 - 16); /*0x342cf6*/
      --v27; /*0x342cfa*/
    }
    while ( v27 ); /*0x342cfe*/
    *(_OWORD *)v39 = *(_OWORD *)v31; /*0x342d04*/
    *(_OWORD *)(v39 + 16) = *(_OWORD *)(v31 + 16); /*0x342d0c*/
    *(_OWORD *)(v39 + 32) = *(_OWORD *)(v31 + 32); /*0x342d15*/
    *(_OWORD *)(v39 + 48) = *(_OWORD *)(v31 + 48); /*0x342d1e*/
    *(_OWORD *)(v39 + 64) = *(_OWORD *)(v31 + 64); /*0x342d27*/
    *(_OWORD *)(v39 + 80) = *(_OWORD *)(v31 + 80); /*0x342d30*/
    *(_OWORD *)(v39 + 96) = *(_OWORD *)(v31 + 96); /*0x342d39*/
    *(_QWORD *)(v39 + 112) = *(_QWORD *)(v31 + 112); /*0x342d41*/
    *(_DWORD *)(v6 + 19100) = 1; /*0x342d45*/
  }
  return sub_59D350(v42); /*0x342d59*/
}