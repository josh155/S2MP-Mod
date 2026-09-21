__int64 __fastcall sub_4EF6C0(__int64 a1, __int64 a2, _BYTE *a3, __int64 a4)
{
  int *v4; // r12
  _BYTE *v5; // r13
  __int64 v7; // rax
  __int128 v8; // xmm0
  __int64 result; // rax
  int *v10; // r14
  __int64 v11; // r15
  _BYTE *v12; // r12
  int v13; // ebp
  int v14; // esi
  int i; // edi
  int v16; // eax
  char v17; // cl
  __int64 v18; // rax
  __int64 v19; // rax
  _BYTE *v20; // r14
  __int64 v21; // r15
  int v22; // r9d
  int v23; // r8d
  int v24; // edx
  char v25; // di
  int v26; // r9d
  int v27; // edx
  int v28; // ecx
  unsigned __int8 v29; // dl
  int v30; // ecx
  unsigned __int8 v31; // dl
  __int16 v32; // si
  int v33; // r8d
  int v34; // ecx
  int v35; // ecx
  unsigned __int8 v36; // dl
  __int16 v37; // di
  __int16 v38; // bp
  int v39; // r8d
  int v40; // ecx
  int v41; // ecx
  unsigned __int8 v42; // dl
  int v43; // esi
  int j; // edi
  int v45; // eax
  char v46; // cl
  __int16 v47; // bp
  int v48; // r8d
  int v49; // ecx
  int v50; // ecx
  unsigned __int8 v51; // dl
  int v52; // esi
  int k; // edi
  int v54; // eax
  char v55; // cl
  __int16 v56; // si
  int v57; // r8d
  int v58; // ecx
  int v59; // ecx
  unsigned __int8 v60; // dl
  __int16 v61; // di
  __int16 v62; // bp
  int v63; // r8d
  int v64; // ecx
  int v65; // ecx
  unsigned __int8 v66; // dl
  int v67; // esi
  int m; // edi
  int v69; // eax
  char v70; // cl
  __int16 v71; // si
  int v72; // r8d
  int v73; // ecx
  int v74; // ecx
  unsigned __int8 v75; // dl
  __int16 v76; // di
  __int16 v77; // di
  int v78; // r8d
  int v79; // ecx
  int v80; // ecx
  unsigned __int8 v81; // dl
  __int16 v82; // di
  int v83; // r8d
  int v84; // ecx
  int v85; // ecx
  unsigned __int8 v86; // dl
  int v87; // r8d
  int v88; // ecx
  int v89; // ecx
  unsigned __int8 v90; // dl
  _DWORD *v91; // rsi
  __int64 v92; // rbp
  int v93; // edi
  int v94; // r8d
  int v95; // ecx
  int v96; // ecx
  unsigned __int8 v97; // dl
  __int64 v99; // [rsp+28h] [rbp-200h]
  _BYTE *v100; // [rsp+30h] [rbp-1F8h]
  _BYTE v101[416]; // [rsp+40h] [rbp-1E8h] BYREF

  v4 = (int *)a4; /*0x4ef6e4*/
  v5 = a3; /*0x4ef6e7*/
  if ( !a3 ) /*0x4ef6f0*/
  {
    v5 = v101; /*0x4ef6ff*/
    sub_59F7E0(v101, 0, 404); /*0x4ef704*/
  }
  if ( (unsigned int)MSG_ReadShort(a1) ) /*0x4ef70c*/
  {
    v10 = v4; /*0x4ef7c5*/
    v100 = (_BYTE *)(v5 - (_BYTE *)v4); /*0x4ef7d6*/
    v11 = 2; /*0x4ef7db*/
    v12 = (_BYTE *)(v5 - (_BYTE *)v4); /*0x4ef7e1*/
    do /*0x4ef82a*/
    {
      v13 = *(int *)((char *)v10 + (_QWORD)v12); /*0x4ef7f0*/
      if ( (unsigned int)MSG_ReadShort(a1) ) /*0x4ef7f7*/
      {
        v14 = 0; /*0x4ef800*/
        for ( i = 0; i < 16; i += 8 ) /*0x4ef802*/
        {
          v16 = sub_4EB510(a1); /*0x4ef807*/
          v17 = i; /*0x4ef80c*/
          v14 |= v16 << v17; /*0x4ef813*/
        }
        v13 = v14 ^ (unsigned __int16)v13; /*0x4ef81d*/
      }
      *v10++ = v13; /*0x4ef81f*/
      --v11; /*0x4ef826*/
    }
    while ( v11 ); /*0x4ef82a*/
    v18 = 0; /*0x4ef831*/
    v99 = 0; /*0x4ef833*/
    while ( 1 ) /*0x4ef844*/
    {
      v19 = 9 * v18; /*0x4ef844*/
      v20 = &v5[2 * v19]; /*0x4ef850*/
      v21 = a4 + 2 * v19; /*0x4ef853*/
      v22 = *(_DWORD *)(a1 + 40) & 7; /*0x4ef857*/
      if ( !v22 ) /*0x4ef85b*/
      {
        v23 = *(_DWORD *)(a1 + 28); /*0x4ef860*/
        v24 = *(_DWORD *)(a1 + 36); /*0x4ef867*/
        if ( v24 >= v23 + *(_DWORD *)(a1 + 32) ) /*0x4ef86c*/
        {
          *(_DWORD *)a1 = 1; /*0x4ef86e*/
LABEL_17:
          v25 = v20[8]; /*0x4ef874*/
          v26 = *(_DWORD *)(a1 + 40) & 7; /*0x4ef87d*/
          if ( !v26 ) /*0x4ef881*/
          {
            v27 = *(_DWORD *)(a1 + 36); /*0x4ef88a*/
            if ( v27 >= v23 + *(_DWORD *)(a1 + 32) ) /*0x4ef892*/
            {
              *(_DWORD *)a1 = 1; /*0x4ef894*/
              goto LABEL_31; /*0x4ef89a*/
            }
            *(_DWORD *)(a1 + 40) = 8 * v27; /*0x4ef911*/
            *(_DWORD *)(a1 + 36) = v27 + 1; /*0x4ef917*/
          }
          v30 = (*(int *)(a1 + 40) >> 3) - v23; /*0x4ef926*/
          if ( v30 < 0 ) /*0x4ef929*/
            v31 = *(_BYTE *)((*(int *)(a1 + 40) >> 3) + *(_QWORD *)(a1 + 8)); /*0x4ef93f*/
          else
            v31 = *(_BYTE *)(v30 + *(_QWORD *)(a1 + 16)); /*0x4ef932*/
          ++*(_DWORD *)(a1 + 40); /*0x4ef94b*/
          if ( ((v31 >> v26) & 1) != 0 ) /*0x4ef956*/
LABEL_31:
            v25 = MSG_ReadBits(a1, 5) ^ v25 & 0x1F; /*0x4ef958*/
          *(_BYTE *)(v21 + 8) = v25; /*0x4ef96a*/
          v32 = *((_WORD *)v20 + 7); /*0x4ef972*/
          v33 = *(_DWORD *)(a1 + 40) & 7; /*0x4ef977*/
          if ( !v33 ) /*0x4ef97b*/
          {
            v34 = *(_DWORD *)(a1 + 36); /*0x4ef983*/
            if ( v34 >= *(_DWORD *)(a1 + 28) + *(_DWORD *)(a1 + 32) ) /*0x4ef988*/
            {
              *(_DWORD *)a1 = 1; /*0x4ef98a*/
              goto LABEL_40; /*0x4ef990*/
            }
            *(_DWORD *)(a1 + 40) = 8 * v34; /*0x4ef999*/
            *(_DWORD *)(a1 + 36) = v34 + 1; /*0x4ef99f*/
          }
          v35 = (*(int *)(a1 + 40) >> 3) - *(_DWORD *)(a1 + 28); /*0x4ef9ae*/
          if ( v35 < 0 ) /*0x4ef9b1*/
            v36 = *(_BYTE *)((*(int *)(a1 + 40) >> 3) + *(_QWORD *)(a1 + 8)); /*0x4ef9c7*/
          else
            v36 = *(_BYTE *)(v35 + *(_QWORD *)(a1 + 16)); /*0x4ef9ba*/
          ++*(_DWORD *)(a1 + 40); /*0x4ef9d3*/
          if ( ((v36 >> v33) & 1) != 0 ) /*0x4ef9de*/
          {
LABEL_40:
            v37 = MSG_ReadBits(a1, 2); /*0x4ef9e0*/
            v32 = ((4 * sub_4EB510(a1)) | v37) ^ v32 & 0x3FF; /*0x4efa02*/
          }
          *(_WORD *)(v21 + 14) = v32; /*0x4efa04*/
          v38 = *((_WORD *)v20 + 5); /*0x4efa0d*/
          v39 = *(_DWORD *)(a1 + 40) & 7; /*0x4efa12*/
          if ( !v39 ) /*0x4efa16*/
          {
            v40 = *(_DWORD *)(a1 + 36); /*0x4efa1e*/
            if ( v40 >= *(_DWORD *)(a1 + 28) + *(_DWORD *)(a1 + 32) ) /*0x4efa23*/
            {
              *(_DWORD *)a1 = 1; /*0x4efa25*/
              goto LABEL_49; /*0x4efa2b*/
            }
            *(_DWORD *)(a1 + 40) = 8 * v40; /*0x4efa34*/
            *(_DWORD *)(a1 + 36) = v40 + 1; /*0x4efa3a*/
          }
          v41 = (*(int *)(a1 + 40) >> 3) - *(_DWORD *)(a1 + 28); /*0x4efa49*/
          if ( v41 < 0 ) /*0x4efa4c*/
            v42 = *(_BYTE *)((*(int *)(a1 + 40) >> 3) + *(_QWORD *)(a1 + 8)); /*0x4efa62*/
          else
            v42 = *(_BYTE *)(v41 + *(_QWORD *)(a1 + 16)); /*0x4efa55*/
          ++*(_DWORD *)(a1 + 40); /*0x4efa6e*/
          if ( ((v42 >> v39) & 1) != 0 ) /*0x4efa79*/
          {
LABEL_49:
            v43 = 0; /*0x4efa7b*/
            for ( j = 0; j < 16; j += 8 ) /*0x4efa7d*/
            {
              v45 = sub_4EB510(a1); /*0x4efa83*/
              v46 = j; /*0x4efa88*/
              v43 |= v45 << v46; /*0x4efa8f*/
            }
            v38 ^= v43; /*0x4efa96*/
          }
          *(_WORD *)(v21 + 10) = v38; /*0x4efa98*/
          v47 = *((_WORD *)v20 + 6); /*0x4efaa1*/
          v48 = *(_DWORD *)(a1 + 40) & 7; /*0x4efaa6*/
          if ( !v48 ) /*0x4efaaa*/
          {
            v49 = *(_DWORD *)(a1 + 36); /*0x4efab2*/
            if ( v49 >= *(_DWORD *)(a1 + 28) + *(_DWORD *)(a1 + 32) ) /*0x4efab7*/
            {
              *(_DWORD *)a1 = 1; /*0x4efab9*/
              goto LABEL_60; /*0x4efabf*/
            }
            *(_DWORD *)(a1 + 40) = 8 * v49; /*0x4efac8*/
            *(_DWORD *)(a1 + 36) = v49 + 1; /*0x4eface*/
          }
          v50 = (*(int *)(a1 + 40) >> 3) - *(_DWORD *)(a1 + 28); /*0x4efadd*/
          if ( v50 < 0 ) /*0x4efae0*/
            v51 = *(_BYTE *)((*(int *)(a1 + 40) >> 3) + *(_QWORD *)(a1 + 8)); /*0x4efaf6*/
          else
            v51 = *(_BYTE *)(v50 + *(_QWORD *)(a1 + 16)); /*0x4efae9*/
          ++*(_DWORD *)(a1 + 40); /*0x4efb02*/
          if ( ((v51 >> v48) & 1) != 0 ) /*0x4efb0d*/
          {
LABEL_60:
            v52 = 0; /*0x4efb0f*/
            for ( k = 0; k < 16; k += 8 ) /*0x4efb11*/
            {
              v54 = sub_4EB510(a1); /*0x4efb16*/
              v55 = k; /*0x4efb1b*/
              v52 |= v54 << v55; /*0x4efb22*/
            }
            v47 ^= v52; /*0x4efb29*/
          }
          *(_WORD *)(v21 + 12) = v47; /*0x4efb2b*/
          v56 = *((_WORD *)v20 + 8); /*0x4efb34*/
          v57 = *(_DWORD *)(a1 + 40) & 7; /*0x4efb39*/
          if ( !v57 ) /*0x4efb3d*/
          {
            v58 = *(_DWORD *)(a1 + 36); /*0x4efb45*/
            if ( v58 >= *(_DWORD *)(a1 + 28) + *(_DWORD *)(a1 + 32) ) /*0x4efb4a*/
            {
              *(_DWORD *)a1 = 1; /*0x4efb4c*/
              goto LABEL_71; /*0x4efb52*/
            }
            *(_DWORD *)(a1 + 40) = 8 * v58; /*0x4efb5b*/
            *(_DWORD *)(a1 + 36) = v58 + 1; /*0x4efb61*/
          }
          v59 = (*(int *)(a1 + 40) >> 3) - *(_DWORD *)(a1 + 28); /*0x4efb70*/
          if ( v59 < 0 ) /*0x4efb73*/
            v60 = *(_BYTE *)((*(int *)(a1 + 40) >> 3) + *(_QWORD *)(a1 + 8)); /*0x4efb89*/
          else
            v60 = *(_BYTE *)(v59 + *(_QWORD *)(a1 + 16)); /*0x4efb7c*/
          ++*(_DWORD *)(a1 + 40); /*0x4efb95*/
          if ( ((v60 >> v57) & 1) != 0 ) /*0x4efba0*/
          {
LABEL_71:
            v61 = MSG_ReadBits(a1, 2); /*0x4efba2*/
            v56 = ((4 * sub_4EB510(a1)) | v61) ^ v56 & 0x3FF; /*0x4efbc4*/
          }
          *(_WORD *)(v21 + 16) = v56; /*0x4efbc6*/
          v62 = *((_WORD *)v20 + 9); /*0x4efbcf*/
          v63 = *(_DWORD *)(a1 + 40) & 7; /*0x4efbd4*/
          if ( !v63 ) /*0x4efbd8*/
          {
            v64 = *(_DWORD *)(a1 + 36); /*0x4efbe0*/
            if ( v64 >= *(_DWORD *)(a1 + 28) + *(_DWORD *)(a1 + 32) ) /*0x4efbe5*/
            {
              *(_DWORD *)a1 = 1; /*0x4efbe7*/
              goto LABEL_80; /*0x4efbed*/
            }
            *(_DWORD *)(a1 + 40) = 8 * v64; /*0x4efbf6*/
            *(_DWORD *)(a1 + 36) = v64 + 1; /*0x4efbfc*/
          }
          v65 = (*(int *)(a1 + 40) >> 3) - *(_DWORD *)(a1 + 28); /*0x4efc0b*/
          if ( v65 < 0 ) /*0x4efc0e*/
            v66 = *(_BYTE *)((*(int *)(a1 + 40) >> 3) + *(_QWORD *)(a1 + 8)); /*0x4efc24*/
          else
            v66 = *(_BYTE *)(v65 + *(_QWORD *)(a1 + 16)); /*0x4efc17*/
          ++*(_DWORD *)(a1 + 40); /*0x4efc30*/
          if ( ((v66 >> v63) & 1) != 0 ) /*0x4efc3b*/
          {
LABEL_80:
            v67 = 0; /*0x4efc3d*/
            for ( m = 0; m < 16; m += 8 ) /*0x4efc3f*/
            {
              v69 = sub_4EB510(a1); /*0x4efc44*/
              v70 = m; /*0x4efc49*/
              v67 |= v69 << v70; /*0x4efc50*/
            }
            v62 ^= v67; /*0x4efc57*/
          }
          *(_WORD *)(v21 + 18) = v62; /*0x4efc59*/
          v71 = *((_WORD *)v20 + 10); /*0x4efc62*/
          v72 = *(_DWORD *)(a1 + 40) & 7; /*0x4efc67*/
          if ( !v72 ) /*0x4efc6b*/
          {
            v73 = *(_DWORD *)(a1 + 36); /*0x4efc73*/
            if ( v73 >= *(_DWORD *)(a1 + 28) + *(_DWORD *)(a1 + 32) ) /*0x4efc78*/
            {
              *(_DWORD *)a1 = 1; /*0x4efc7a*/
              goto LABEL_91; /*0x4efc80*/
            }
            *(_DWORD *)(a1 + 40) = 8 * v73; /*0x4efc89*/
            *(_DWORD *)(a1 + 36) = v73 + 1; /*0x4efc8f*/
          }
          v74 = (*(int *)(a1 + 40) >> 3) - *(_DWORD *)(a1 + 28); /*0x4efc9e*/
          if ( v74 < 0 ) /*0x4efca1*/
            v75 = *(_BYTE *)((*(int *)(a1 + 40) >> 3) + *(_QWORD *)(a1 + 8)); /*0x4efcb7*/
          else
            v75 = *(_BYTE *)(v74 + *(_QWORD *)(a1 + 16)); /*0x4efcaa*/
          ++*(_DWORD *)(a1 + 40); /*0x4efcc3*/
          if ( ((v75 >> v72) & 1) != 0 ) /*0x4efcce*/
          {
LABEL_91:
            v76 = MSG_ReadBits(a1, 2); /*0x4efcd0*/
            v71 = ((4 * sub_4EB510(a1)) | v76) ^ v71 & 0x3FF; /*0x4efcf2*/
          }
          *(_WORD *)(v21 + 20) = v71; /*0x4efcf4*/
          v77 = *((_WORD *)v20 + 11); /*0x4efcfd*/
          v78 = *(_DWORD *)(a1 + 40) & 7; /*0x4efd02*/
          if ( !v78 ) /*0x4efd06*/
          {
            v79 = *(_DWORD *)(a1 + 36); /*0x4efd0e*/
            if ( v79 >= *(_DWORD *)(a1 + 28) + *(_DWORD *)(a1 + 32) ) /*0x4efd13*/
            {
              *(_DWORD *)a1 = 1; /*0x4efd15*/
              goto LABEL_100; /*0x4efd1b*/
            }
            *(_DWORD *)(a1 + 40) = 8 * v79; /*0x4efd24*/
            *(_DWORD *)(a1 + 36) = v79 + 1; /*0x4efd2a*/
          }
          v80 = (*(int *)(a1 + 40) >> 3) - *(_DWORD *)(a1 + 28); /*0x4efd39*/
          if ( v80 < 0 ) /*0x4efd3c*/
            v81 = *(_BYTE *)((*(int *)(a1 + 40) >> 3) + *(_QWORD *)(a1 + 8)); /*0x4efd52*/
          else
            v81 = *(_BYTE *)(v80 + *(_QWORD *)(a1 + 16)); /*0x4efd45*/
          ++*(_DWORD *)(a1 + 40); /*0x4efd5e*/
          if ( ((v81 >> v78) & 1) != 0 ) /*0x4efd69*/
LABEL_100:
            v77 = MSG_ReadBits(a1, 6) ^ v77 & 0x3F; /*0x4efd6b*/
          *(_WORD *)(v21 + 22) = v77; /*0x4efd7d*/
          v82 = *((_WORD *)v20 + 12); /*0x4efd86*/
          v83 = *(_DWORD *)(a1 + 40) & 7; /*0x4efd8b*/
          if ( !v83 ) /*0x4efd8f*/
          {
            v84 = *(_DWORD *)(a1 + 36); /*0x4efd97*/
            if ( v84 >= *(_DWORD *)(a1 + 28) + *(_DWORD *)(a1 + 32) ) /*0x4efd9c*/
            {
              *(_DWORD *)a1 = 1; /*0x4efd9e*/
              goto LABEL_109; /*0x4efda4*/
            }
            *(_DWORD *)(a1 + 40) = 8 * v84; /*0x4efdad*/
            *(_DWORD *)(a1 + 36) = v84 + 1; /*0x4efdb3*/
          }
          v85 = (*(int *)(a1 + 40) >> 3) - *(_DWORD *)(a1 + 28); /*0x4efdc2*/
          if ( v85 < 0 ) /*0x4efdc5*/
            v86 = *(_BYTE *)((*(int *)(a1 + 40) >> 3) + *(_QWORD *)(a1 + 8)); /*0x4efddb*/
          else
            v86 = *(_BYTE *)(v85 + *(_QWORD *)(a1 + 16)); /*0x4efdce*/
          ++*(_DWORD *)(a1 + 40); /*0x4efde7*/
          if ( ((v86 >> v83) & 1) != 0 ) /*0x4efdf2*/
LABEL_109:
            v82 = MSG_ReadBits(a1, 5) ^ v82 & 0x1F; /*0x4efdf4*/
          *(_WORD *)(v21 + 24) = v82; /*0x4efe06*/
          goto LABEL_111; /*0x4efe06*/
        }
        *(_DWORD *)(a1 + 40) = 8 * v24; /*0x4ef8a6*/
        *(_DWORD *)(a1 + 36) = v24 + 1; /*0x4ef8ac*/
      }
      v23 = *(_DWORD *)(a1 + 28); /*0x4ef8b6*/
      v28 = (*(int *)(a1 + 40) >> 3) - v23; /*0x4ef8bf*/
      if ( v28 < 0 ) /*0x4ef8c2*/
        v29 = *(_BYTE *)((*(int *)(a1 + 40) >> 3) + *(_QWORD *)(a1 + 8)); /*0x4ef8d8*/
      else
        v29 = *(_BYTE *)(v28 + *(_QWORD *)(a1 + 16)); /*0x4ef8cb*/
      ++*(_DWORD *)(a1 + 40); /*0x4ef8e4*/
      if ( ((v29 >> v22) & 1) != 0 ) /*0x4ef8ef*/
        goto LABEL_17; /*0x4ef8ef*/
      *(_OWORD *)(v21 + 8) = *(_OWORD *)(v20 + 8); /*0x4ef8f6*/
      *(_WORD *)(v21 + 24) = *((_WORD *)v20 + 12); /*0x4ef900*/
LABEL_111:
      v18 = v99 + 1; /*0x4efe0b*/
      v99 = v18; /*0x4efe13*/
      if ( v18 >= 18 ) /*0x4efe1c*/
      {
        v87 = *(_DWORD *)(a1 + 40) & 7; /*0x4efe2e*/
        if ( !v87 ) /*0x4efe32*/
        {
          v88 = *(_DWORD *)(a1 + 36); /*0x4efe3a*/
          if ( v88 >= *(_DWORD *)(a1 + 28) + *(_DWORD *)(a1 + 32) ) /*0x4efe3f*/
          {
            *(_DWORD *)a1 = 1; /*0x4efe41*/
            goto LABEL_120; /*0x4efe47*/
          }
          *(_DWORD *)(a1 + 40) = 8 * v88; /*0x4efe50*/
          *(_DWORD *)(a1 + 36) = v88 + 1; /*0x4efe56*/
        }
        v89 = (*(int *)(a1 + 40) >> 3) - *(_DWORD *)(a1 + 28); /*0x4efe65*/
        if ( v89 < 0 ) /*0x4efe68*/
          v90 = *(_BYTE *)((*(int *)(a1 + 40) >> 3) + *(_QWORD *)(a1 + 8)); /*0x4efe7e*/
        else
          v90 = *(_BYTE *)(v89 + *(_QWORD *)(a1 + 16)); /*0x4efe71*/
        ++*(_DWORD *)(a1 + 40); /*0x4efe8a*/
        result = (v90 >> v87) & 1; /*0x4efe92*/
        if ( ((v90 >> v87) & 1) == 0 ) /*0x4efe95*/
        {
          *(_OWORD *)(a4 + 332) = *(_OWORD *)(v5 + 332); /*0x4eff4d*/
          *(_OWORD *)(a4 + 348) = *(_OWORD *)(v5 + 348); /*0x4eff5e*/
          *(_OWORD *)(a4 + 364) = *(_OWORD *)(v5 + 364); /*0x4eff6f*/
          *(_OWORD *)(a4 + 380) = *(_OWORD *)(v5 + 380); /*0x4eff80*/
          *(_QWORD *)(a4 + 396) = *(_QWORD *)(v5 + 396); /*0x4eff92*/
          return result; /*0x4eff92*/
        }
LABEL_120:
        v91 = (_DWORD *)(a4 + 332); /*0x4efe9b*/
        v92 = 18; /*0x4efea8*/
        while ( 2 ) /*0x4efeb0*/
        {
          v93 = *(_DWORD *)&v100[(_QWORD)v91]; /*0x4efeb0*/
          v94 = *(_DWORD *)(a1 + 40) & 7; /*0x4efeb8*/
          if ( !v94 ) /*0x4efebc*/
          {
            v95 = *(_DWORD *)(a1 + 36); /*0x4efec4*/
            if ( v95 >= *(_DWORD *)(a1 + 28) + *(_DWORD *)(a1 + 32) ) /*0x4efec9*/
            {
              *(_DWORD *)a1 = 1; /*0x4efecb*/
              goto LABEL_129; /*0x4efed1*/
            }
            *(_DWORD *)(a1 + 40) = 8 * v95; /*0x4efeda*/
            *(_DWORD *)(a1 + 36) = v95 + 1; /*0x4efee0*/
          }
          v96 = (*(int *)(a1 + 40) >> 3) - *(_DWORD *)(a1 + 28); /*0x4efeef*/
          if ( v96 < 0 ) /*0x4efef2*/
            v97 = *(_BYTE *)((*(int *)(a1 + 40) >> 3) + *(_QWORD *)(a1 + 8)); /*0x4eff08*/
          else
            v97 = *(_BYTE *)(v96 + *(_QWORD *)(a1 + 16)); /*0x4efefb*/
          ++*(_DWORD *)(a1 + 40); /*0x4eff14*/
          result = (v97 >> v94) & 1; /*0x4eff1c*/
          if ( ((v97 >> v94) & 1) != 0 ) /*0x4eff1f*/
          {
LABEL_129:
            result = MSG_ReadBits(a1, 2); /*0x4eff21*/
            v93 = result ^ v93 & 3; /*0x4eff31*/
          }
          *v91++ = v93; /*0x4eff33*/
          if ( !--v92 ) /*0x4eff3d*/
            return result; /*0x4eff3d*/
          continue; /*0x4eff3d*/
        }
      }
    }
  }
  v7 = 3; /*0x4ef719*/
  do /*0x4ef78b*/
  {
    v4 += 32; /*0x4ef720*/
    v8 = *(_OWORD *)v5; /*0x4ef728*/
    v5 += 128; /*0x4ef72d*/
    *((_OWORD *)v4 - 8) = v8; /*0x4ef734*/
    *((_OWORD *)v4 - 7) = *((_OWORD *)v5 - 7); /*0x4ef73f*/
    *((_OWORD *)v4 - 6) = *((_OWORD *)v5 - 6); /*0x4ef74a*/
    *((_OWORD *)v4 - 5) = *((_OWORD *)v5 - 5); /*0x4ef755*/
    *((_OWORD *)v4 - 4) = *((_OWORD *)v5 - 4); /*0x4ef760*/
    *((_OWORD *)v4 - 3) = *((_OWORD *)v5 - 3); /*0x4ef76b*/
    *((_OWORD *)v4 - 2) = *((_OWORD *)v5 - 2); /*0x4ef776*/
    *((_OWORD *)v4 - 1) = *((_OWORD *)v5 - 1); /*0x4ef781*/
    --v7; /*0x4ef787*/
  }
  while ( v7 ); /*0x4ef78b*/
  *(_OWORD *)v4 = *(_OWORD *)v5; /*0x4ef792*/
  result = *((unsigned int *)v5 + 4); /*0x4ef797*/
  v4[4] = result; /*0x4ef79b*/
  return result; /*0x4effbc*/
}