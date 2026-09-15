__int64 __fastcall sub_341960(__int64 a1, __int64 a2, int a3, __int64 a4, __int64 a5)
{
  int v5; // r14d
  __int64 result; // rax
  char *v7; // rbx
  int v11; // ebp
  int v12; // r8d
  int v13; // ecx
  int v14; // ecx
  unsigned __int8 v15; // dl
  int v16; // r15d
  bool i; // zf
  _OWORD *v18; // rdx
  _OWORD *v19; // rdx
  __int128 v20; // xmm1
  char *v21; // rbx

  v5 = 0; /*0x34197e*/
  result = *(unsigned int *)(a1 + 19180); /*0x341981*/
  v7 = 0; /*0x341987*/
  *(_DWORD *)(a5 + 19036) = result; /*0x341997*/
  *(_DWORD *)(a5 + 19028) = 0; /*0x34199f*/
  if ( a4 ) /*0x3419ae*/
  {
    if ( *(int *)(a4 + 19028) > 0 ) /*0x3419be*/
    {
      result = *(_DWORD *)(a4 + 19036) % *(_DWORD *)(a1 + 36752); /*0x3419d5*/
      v7 = (char *)(*(_QWORD *)(a1 + 36784) + 212 * result); /*0x3419df*/
      v11 = *v7; /*0x3419e6*/
    }
    else
    {
      v11 = 99999; /*0x3419c0*/
    }
  }
  else
  {
    v11 = 99999; /*0x3419b0*/
  }
  if ( !*(_DWORD *)a2 ) /*0x3419e9*/
  {
    while ( 1 ) /*0x341a04*/
    {
      v12 = *(_DWORD *)(a2 + 40) & 7; /*0x341a04*/
      if ( v12 ) /*0x341a08*/
        goto LABEL_11; /*0x341a08*/
      v13 = *(_DWORD *)(a2 + 36); /*0x341a10*/
      if ( v13 < *(_DWORD *)(a2 + 28) + *(_DWORD *)(a2 + 32) ) /*0x341a15*/
        break; /*0x341a15*/
      *(_DWORD *)a2 = 1; /*0x341a17*/
LABEL_15:
      v16 = (char)sub_4F04B0(a2, 5); /*0x341a71*/
      if ( *(_DWORD *)(a2 + 36) > *(_DWORD *)(a2 + 28) ) /*0x341a88*/
        sub_159860(1, &unk_8FE5D0); /*0x341a96*/
      for ( i = v11 == v16; v11 < v16; i = v11 == v16 ) /*0x341a9e*/
      {
        ++v5; /*0x341ab6*/
        v18 = (_OWORD *)(*(_QWORD *)(a1 + 36784) + 212LL * (*(_DWORD *)(a1 + 19180) % *(_DWORD *)(a1 + 36752))); /*0x341ad4*/
        *v18 = *(_OWORD *)v7; /*0x341adb*/
        v18[1] = *((_OWORD *)v7 + 1); /*0x341ae2*/
        v18[2] = *((_OWORD *)v7 + 2); /*0x341aea*/
        v18[3] = *((_OWORD *)v7 + 3); /*0x341af2*/
        v18[4] = *((_OWORD *)v7 + 4); /*0x341afa*/
        v18[5] = *((_OWORD *)v7 + 5); /*0x341b02*/
        v18[6] = *((_OWORD *)v7 + 6); /*0x341b0a*/
        v18 += 8; /*0x341b0e*/
        *(v18 - 1) = *((_OWORD *)v7 + 7); /*0x341b16*/
        *v18 = *((_OWORD *)v7 + 8); /*0x341b1d*/
        v18[1] = *((_OWORD *)v7 + 9); /*0x341b24*/
        v18[2] = *((_OWORD *)v7 + 10); /*0x341b2c*/
        v18[3] = *((_OWORD *)v7 + 11); /*0x341b34*/
        v18[4] = *((_OWORD *)v7 + 12); /*0x341b3c*/
        *((_DWORD *)v18 + 20) = *((_DWORD *)v7 + 52); /*0x341b43*/
        ++*(_DWORD *)(a1 + 19180); /*0x341b46*/
        ++*(_DWORD *)(a5 + 19028); /*0x341b4c*/
        if ( v5 < *(_DWORD *)(a4 + 19028) ) /*0x341b5b*/
        {
          v7 = (char *)(*(_QWORD *)(a1 + 36784) + 212LL * ((v5 + *(_DWORD *)(a4 + 19036)) % *(_DWORD *)(a1 + 36752))); /*0x341b7f*/
          v11 = *v7; /*0x341b86*/
        }
        else
        {
          v11 = 99999; /*0x341b5d*/
        }
      }
      if ( i ) /*0x341ba3*/
      {
        result = sub_340560(a1, a2, a3, a5, v16, (__int64)v7, 0); /*0x341bb7*/
        if ( ++v5 < *(_DWORD *)(a4 + 19028) ) /*0x341bc6*/
        {
          result = (v5 + *(_DWORD *)(a4 + 19036)) % *(_DWORD *)(a1 + 36752); /*0x341be0*/
          v7 = (char *)(*(_QWORD *)(a1 + 36784) + 212 * result); /*0x341bea*/
          v11 = *v7; /*0x341bf1*/
        }
        else
        {
          v11 = 99999; /*0x341bc8*/
        }
      }
      else
      {
        result = sub_340560(a1, a2, a3, a5, v16, 0, 0); /*0x341c06*/
      }
      if ( *(_DWORD *)a2 ) /*0x341c0b*/
        goto LABEL_28; /*0x341c0e*/
    }
    *(_DWORD *)(a2 + 40) = 8 * v13; /*0x341a26*/
    *(_DWORD *)(a2 + 36) = v13 + 1; /*0x341a2c*/
LABEL_11:
    v14 = (*(int *)(a2 + 40) >> 3) - *(_DWORD *)(a2 + 28); /*0x341a2f*/
    if ( v14 < 0 ) /*0x341a3e*/
      v15 = *(_BYTE *)((*(int *)(a2 + 40) >> 3) + *(_QWORD *)(a2 + 8)); /*0x341a54*/
    else
      v15 = *(_BYTE *)(v14 + *(_QWORD *)(a2 + 16)); /*0x341a47*/
    ++*(_DWORD *)(a2 + 40); /*0x341a60*/
    result = (v15 >> v12) & 1; /*0x341a68*/
    if ( ((v15 >> v12) & 1) == 0 ) /*0x341a6b*/
      goto LABEL_28; /*0x341a6b*/
    goto LABEL_15; /*0x341a6b*/
  }
LABEL_28:
  if ( v11 != 99999 ) /*0x341c24*/
  {
    do /*0x341d0d*/
    {
      if ( *(_DWORD *)a2 ) /*0x341c30*/
        break; /*0x341c33*/
      ++v5; /*0x341c3f*/
      v19 = (_OWORD *)(*(_QWORD *)(a1 + 36784) + 212LL * (*(_DWORD *)(a1 + 19180) % *(_DWORD *)(a1 + 36752))); /*0x341c56*/
      *v19 = *(_OWORD *)v7; /*0x341c5d*/
      v19[1] = *((_OWORD *)v7 + 1); /*0x341c64*/
      v19[2] = *((_OWORD *)v7 + 2); /*0x341c6c*/
      v19[3] = *((_OWORD *)v7 + 3); /*0x341c74*/
      v19[4] = *((_OWORD *)v7 + 4); /*0x341c7c*/
      v19[5] = *((_OWORD *)v7 + 5); /*0x341c84*/
      v19[6] = *((_OWORD *)v7 + 6); /*0x341c8c*/
      v19 += 8; /*0x341c90*/
      v20 = *((_OWORD *)v7 + 7); /*0x341c94*/
      v21 = v7 + 128; /*0x341c98*/
      *(v19 - 1) = v20; /*0x341c9c*/
      *v19 = *(_OWORD *)v21; /*0x341ca3*/
      v19[1] = *((_OWORD *)v21 + 1); /*0x341caa*/
      v19[2] = *((_OWORD *)v21 + 2); /*0x341cb2*/
      v19[3] = *((_OWORD *)v21 + 3); /*0x341cba*/
      v19[4] = *((_OWORD *)v21 + 4); /*0x341cc2*/
      result = *((unsigned int *)v21 + 20); /*0x341cc6*/
      *((_DWORD *)v19 + 20) = result; /*0x341cc9*/
      ++*(_DWORD *)(a1 + 19180); /*0x341ccc*/
      ++*(_DWORD *)(a5 + 19028); /*0x341cd2*/
      if ( v5 >= *(_DWORD *)(a4 + 19028) ) /*0x341ce1*/
        break; /*0x341ce1*/
      v7 = (char *)(*(_QWORD *)(a1 + 36784) + 212LL * ((v5 + *(_DWORD *)(a4 + 19036)) % *(_DWORD *)(a1 + 36752))); /*0x341cfe*/
      result = (unsigned int)*v7; /*0x341d05*/
    }
    while ( (_DWORD)result != 99999 ); /*0x341d0d*/
  }
  return result; /*0x341d13*/
}