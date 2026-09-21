__int64 __fastcall sub_341580(__int64 a1, __int64 a2, int a3, __int64 a4, __int64 a5)
{
  int v5; // ebp
  __int64 result; // rax
  _OWORD *v10; // rbx
  int v11; // esi
  int v12; // r8d
  int v13; // ecx
  int v14; // ecx
  unsigned __int8 v15; // dl
  int v16; // r15d
  bool i; // zf
  __int64 v18; // rax
  __int64 v19; // rcx
  __int64 v20; // rcx
  _BYTE v22[128]; // [rsp+40h] [rbp-D8h] BYREF

  v5 = 0; /*0x3415ab*/
  result = *(unsigned int *)(a1 + 36804); /*0x3415ad*/
  *(_DWORD *)(a5 + 19048) = result; /*0x3415c9*/
  v10 = 0; /*0x3415d1*/
  *(_DWORD *)(a5 + 19044) = 0; /*0x3415d3*/
  if ( a4 ) /*0x3415de*/
  {
    if ( *(int *)(a4 + 19044) > 0 ) /*0x3415ee*/
    {
      result = (unsigned int)(*(_DWORD *)(a4 + 19048) / *(_DWORD *)(a1 + 36800)); /*0x3415ff*/
      v10 = (_OWORD *)(*(_QWORD *)(a1 + 36808) + ((__int64)(*(_DWORD *)(a4 + 19048) % *(_DWORD *)(a1 + 36800)) << 7)); /*0x34160c*/
      v11 = *(__int16 *)v10; /*0x341613*/
    }
    else
    {
      v11 = 99999; /*0x3415f0*/
    }
  }
  else
  {
    v11 = 99999; /*0x3415e0*/
  }
  if ( !*(_DWORD *)a2 ) /*0x341616*/
  {
    while ( 1 ) /*0x341634*/
    {
      v12 = *(_DWORD *)(a2 + 40) & 7; /*0x341634*/
      if ( v12 ) /*0x341638*/
        goto LABEL_11; /*0x341638*/
      v13 = *(_DWORD *)(a2 + 36); /*0x341642*/
      if ( v13 < *(_DWORD *)(a2 + 28) + *(_DWORD *)(a2 + 32) ) /*0x341648*/
        break; /*0x341648*/
      *(_DWORD *)a2 = 1; /*0x34164a*/
LABEL_15:
      v16 = (__int16)sub_4F04B0(a2, 6); /*0x3416a9*/
      if ( *(_DWORD *)(a2 + 36) > *(_DWORD *)(a2 + 28) ) /*0x3416c2*/
        sub_159860(1, &unk_8FE5F8); /*0x3416d0*/
      for ( i = v11 == v16; v11 < v16; i = v11 == v16 ) /*0x3416d8*/
      {
        ++v5; /*0x3416e6*/
        v18 = *(_QWORD *)(a1 + 36808); /*0x3416f2*/
        v19 = (__int64)(*(_DWORD *)(a1 + 36804) % *(_DWORD *)(a1 + 36800)) << 7; /*0x3416fc*/
        *(_OWORD *)(v19 + v18) = *v10; /*0x341700*/
        *(_OWORD *)(v19 + v18 + 16) = v10[1]; /*0x341708*/
        *(_OWORD *)(v19 + v18 + 32) = v10[2]; /*0x341711*/
        *(_OWORD *)(v19 + v18 + 48) = v10[3]; /*0x34171a*/
        *(_OWORD *)(v19 + v18 + 64) = v10[4]; /*0x341723*/
        *(_OWORD *)(v19 + v18 + 80) = v10[5]; /*0x34172c*/
        *(_OWORD *)(v19 + v18 + 96) = v10[6]; /*0x341735*/
        *(_OWORD *)(v19 + v18 + 112) = v10[7]; /*0x34173e*/
        ++*(_DWORD *)(a1 + 36804); /*0x341743*/
        ++*(_DWORD *)(a5 + 19044); /*0x341749*/
        if ( v5 < *(_DWORD *)(a4 + 19044) ) /*0x341758*/
        {
          v10 = (_OWORD *)(*(_QWORD *)(a1 + 36808) /*0x341778*/
                         + ((__int64)((v5 + *(_DWORD *)(a4 + 19048)) % *(_DWORD *)(a1 + 36800)) << 7));
          v11 = *(__int16 *)v10; /*0x34177f*/
        }
        else
        {
          v11 = 99999; /*0x34175a*/
        }
      }
      if ( i ) /*0x34178b*/
      {
        result = sub_4EC7D0( /*0x3417b7*/
                   a2,
                   a3,
                   (_DWORD)v10,
                   *(_DWORD *)(a1 + 36808) + ((*(_DWORD *)(a1 + 36804) % *(_DWORD *)(a1 + 36800)) << 7),
                   v16);
        if ( !(_DWORD)result ) /*0x3417be*/
        {
          ++*(_DWORD *)(a1 + 36804); /*0x3417c0*/
          ++*(_DWORD *)(a5 + 19044); /*0x3417c6*/
        }
        if ( ++v5 < *(_DWORD *)(a4 + 19044) ) /*0x3417d7*/
        {
          result = (unsigned int)((v5 + *(_DWORD *)(a4 + 19048)) / *(_DWORD *)(a1 + 36800)); /*0x3417ea*/
          v10 = (_OWORD *)(*(_QWORD *)(a1 + 36808) /*0x3417f7*/
                         + ((__int64)((v5 + *(_DWORD *)(a4 + 19048)) % *(_DWORD *)(a1 + 36800)) << 7));
          v11 = *(__int16 *)v10; /*0x3417fe*/
        }
        else
        {
          v11 = 99999; /*0x3417d9*/
        }
      }
      else
      {
        sub_826080(v22, 0, 128); /*0x341810*/
        result = sub_4EC7D0( /*0x341841*/
                   a2,
                   a3,
                   (unsigned int)v22,
                   *(_DWORD *)(a1 + 36808) + ((*(_DWORD *)(a1 + 36804) % *(_DWORD *)(a1 + 36800)) << 7),
                   v16);
        if ( !(_DWORD)result ) /*0x341848*/
        {
          ++*(_DWORD *)(a1 + 36804); /*0x34184a*/
          ++*(_DWORD *)(a5 + 19044); /*0x341850*/
        }
      }
      if ( *(_DWORD *)a2 ) /*0x341858*/
        goto LABEL_31; /*0x34185c*/
    }
    *(_DWORD *)(a2 + 40) = 8 * v13; /*0x34165a*/
    *(_DWORD *)(a2 + 36) = v13 + 1; /*0x341661*/
LABEL_11:
    v14 = (*(int *)(a2 + 40) >> 3) - *(_DWORD *)(a2 + 28); /*0x341665*/
    if ( v14 < 0 ) /*0x341675*/
      v15 = *(_BYTE *)((*(int *)(a2 + 40) >> 3) + *(_QWORD *)(a2 + 8)); /*0x34168b*/
    else
      v15 = *(_BYTE *)(v14 + *(_QWORD *)(a2 + 16)); /*0x34167e*/
    ++*(_DWORD *)(a2 + 40); /*0x341697*/
    result = (v15 >> v12) & 1; /*0x3416a0*/
    if ( ((v15 >> v12) & 1) == 0 ) /*0x3416a3*/
      goto LABEL_31; /*0x3416a3*/
    goto LABEL_15; /*0x3416a3*/
  }
LABEL_31:
  if ( v11 != 99999 ) /*0x341878*/
  {
    do /*0x34192a*/
    {
      if ( *(_DWORD *)a2 ) /*0x341880*/
        break; /*0x341884*/
      ++v5; /*0x341890*/
      result = *(_QWORD *)(a1 + 36808); /*0x34189c*/
      v20 = (__int64)(*(_DWORD *)(a1 + 36804) % *(_DWORD *)(a1 + 36800)) << 7; /*0x3418a6*/
      *(_OWORD *)(v20 + result) = *v10; /*0x3418aa*/
      *(_OWORD *)(v20 + result + 16) = v10[1]; /*0x3418b2*/
      *(_OWORD *)(v20 + result + 32) = v10[2]; /*0x3418bb*/
      *(_OWORD *)(v20 + result + 48) = v10[3]; /*0x3418c4*/
      *(_OWORD *)(v20 + result + 64) = v10[4]; /*0x3418cd*/
      *(_OWORD *)(v20 + result + 80) = v10[5]; /*0x3418d6*/
      *(_OWORD *)(v20 + result + 96) = v10[6]; /*0x3418df*/
      *(_OWORD *)(v20 + result + 112) = v10[7]; /*0x3418e8*/
      ++*(_DWORD *)(a1 + 36804); /*0x3418ed*/
      ++*(_DWORD *)(a5 + 19044); /*0x3418f3*/
      if ( v5 >= *(_DWORD *)(a4 + 19044) ) /*0x341902*/
        break; /*0x341902*/
      v10 = (_OWORD *)(*(_QWORD *)(a1 + 36808) /*0x34191b*/
                     + ((__int64)((v5 + *(_DWORD *)(a4 + 19048)) % *(_DWORD *)(a1 + 36800)) << 7));
      result = (unsigned int)*(__int16 *)v10; /*0x341922*/
    }
    while ( (_DWORD)result != 99999 ); /*0x34192a*/
  }
  return result; /*0x341930*/
}