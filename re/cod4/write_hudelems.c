int __usercall MSG_WriteDeltaHudElems@<eax>(int a1@<edx>, int a2, _DWORD *a3, int a4)
{
  _DWORD *v4; // edx
  int v5; // eax
  float *v6; // edx
  float *v7; // esi
  BOOL v8; // eax
  char *v9; // esi
  unsigned int i; // ebx
  int result; // eax
  int v12; // [esp+20h] [ebp-48h]
  int v13; // [esp+24h] [ebp-44h]
  int v15; // [esp+34h] [ebp-34h]
  unsigned int v16; // [esp+38h] [ebp-30h]
  int v17; // [esp+3Ch] [ebp-2Ch]
  unsigned int v18; // [esp+40h] [ebp-28h]
  _DWORD *v19; // [esp+44h] [ebp-24h]
  _DWORD *v21; // [esp+4Ch] [ebp-1Ch]

  if ( !a4 || !*a3 ) /*0x1728a3*/
    return MSG_WriteBits(a1, 0, 5); /*0x172ac7*/
  v21 = a3; /*0x1728ad*/
  v4 = a3; /*0x1728b0*/
  v17 = 0; /*0x1728b2*/
  do /*0x1728c9*/
  {
    if ( ++v17 == a4 ) /*0x1728d5*/
    {
      MSG_WriteBits(a1, v17, 5); /*0x1728ec*/
      goto LABEL_7; /*0x1728ec*/
    }
    v5 = v4[40]; /*0x1728bb*/
    v4 += 40; /*0x1728c1*/
  }
  while ( v5 ); /*0x1728c9*/
  result = MSG_WriteBits(a1, v17, 5); /*0x172a97*/
  if ( !v17 ) /*0x172aa1*/
    return result; /*0x172aa1*/
LABEL_7:
  v15 = 0; /*0x1728f1*/
  do /*0x172a0b*/
  {
    v19 = &unk_40FDC4; /*0x1728fb*/
    v16 = 0; /*0x172902*/
    v18 = 0; /*0x172909*/
    do /*0x172994*/
    {
      v6 = (float *)(*v19 + a2); /*0x17291b*/
      v7 = (float *)((char *)v21 + *v19); /*0x172921*/
      if ( *(_DWORD *)v6 != *(_DWORD *)v7 ) /*0x17292a*/
      {
        switch ( v19[1] ) /*0x172934*/
        {
          case 0xFFFFFF9C: /*0x172934*/
          case 0xFFFFFFA9: /*0x172934*/
            v8 = (unsigned __int16)(int)(float)((float)(182.04445 * *v7) + 0.5) == (unsigned __int16)(int)(float)((float)(182.04445 * *v6) + 0.5); /*0x172a7a*/
            goto LABEL_12; /*0x172a7d*/
          case 0xFFFFFFA1: /*0x172934*/
            v8 = *(_DWORD *)v6 / 100 == *(_DWORD *)v7 / 100; /*0x172a3c*/
            goto LABEL_12; /*0x172a3f*/
          case 0xFFFFFFA4: /*0x172934*/
          case 0xFFFFFFA5: /*0x172934*/
          case 0xFFFFFFA6: /*0x172934*/
            *(float *)&v13 = floorf(*v6 + 0.5); /*0x172951*/
            *(float *)&v12 = floorf(*v7 + 0.5); /*0x17296f*/
            v8 = v13 == v12; /*0x17297c*/
LABEL_12:
            if ( !v8 ) /*0x172981*/
              goto LABEL_13; /*0x172981*/
            break; /*0x172981*/
          default:
LABEL_13:
            v18 = v16; /*0x172983*/
            break; /*0x172986*/
        }
      }
      ++v16; /*0x172989*/
      v19 += 4; /*0x17298c*/
    }
    while ( v16 != 40 ); /*0x172994*/
    MSG_WriteBits(a1, v18, 6); /*0x1729af*/
    v9 = (char *)&hudElemFields; /*0x1729b4*/
    for ( i = 0; i <= v18; ++i ) /*0x1729b9*/
    {
      MSG_WriteDeltaField(a2, v21, v9, i, 0); /*0x1729e6*/
      v9 += 16; /*0x1729ec*/
    }
    ++v15; /*0x1729f4*/
    a2 += 160; /*0x1729f7*/
    v21 += 40; /*0x1729fe*/
    result = v17; /*0x172a05*/
  }
  while ( v15 != v17 ); /*0x172a0b*/
  return result; /*0x172a11*/
}