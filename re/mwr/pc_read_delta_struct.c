// positive sp value has been detected, the output may be wrong!
void __fastcall sub_4EDB98(__int64 a1, __int64 a2, __int64 a3, __int64 a4, int a5, __int64 a6, int a7, __int64 a8)
{
  int v8; // eax
  __int64 v9; // rbp
  int v10; // edi
  char v11; // si
  __int64 v12; // r12
  __int64 v13; // r14
  __int64 v14; // r15
  bool v15; // r13
  int v16; // ebx
  unsigned __int16 *v17; // r12
  __int64 v18; // r13
  _BYTE *v19; // rbx
  int i; // ebx
  int v21; // [rsp-68h] [rbp-68h]
  char v22; // [rsp-58h] [rbp-58h]
  int v23; // [rsp-54h] [rbp-54h]
  int v24; // [rsp-50h] [rbp-50h]
  _BYTE *v25; // [rsp-48h] [rbp-48h]
  _BYTE *v26; // [rsp-40h] [rbp-40h]
  __int64 v27; // [rsp+8h] [rbp+8h]
  unsigned int v28; // [rsp+10h] [rbp+10h]

  v15 = 1; /*0x4edb9d*/
  v22 = 1; /*0x4edba0*/
  if ( v8 > -1 ) /*0x4edba8*/
  {
    do /*0x4edc3d*/
    {
      v16 = v10 + 1; /*0x4edbb7*/
      for ( v10 += sub_4F0780(v12, a7); v16 < v10; ++v16 ) /*0x4edbcc*/
        sub_4EC1F0(v14, v13, v9, v16); /*0x4edbdc*/
      if ( (_BYTE)a8 != v11 && v10 ) /*0x4edbf3*/
        v15 = *v26 == *v25; /*0x4edc04*/
      LOBYTE(v21) = !v15; /*0x4edc17*/
      sub_4ED0E0(v12, v28, v13, v9, (unsigned __int16 *)(v14 + 8LL * v10), v11, v21); /*0x4edc32*/
    }
    while ( v10 < v24 ); /*0x4edc3d*/
    v22 = v15; /*0x4edc43*/
    v23 = v10; /*0x4edc48*/
  }
  if ( v10 > 0 ) /*0x4edc4e*/
  {
    v17 = (unsigned __int16 *)v14; /*0x4edc50*/
    v18 = (unsigned int)v10; /*0x4edc53*/
    v19 = (_BYTE *)(v14 + 6); /*0x4edc5b*/
    do /*0x4edca0*/
    {
      if ( (*v19 & 2) != 0 ) /*0x4edc6a*/
      {
        LOBYTE(v21) = v22 == 0; /*0x4edc82*/
        sub_4ED0E0(v27, v28, v13, v9, v17, v11, v21); /*0x4edc8f*/
      }
      v17 += 4; /*0x4edc94*/
      v19 += 8; /*0x4edc98*/
      --v18; /*0x4edc9c*/
    }
    while ( v18 ); /*0x4edca0*/
    v10 = v23; /*0x4edca2*/
    v14 = a6; /*0x4edca6*/
  }
  for ( i = v10 + 1; i < a5; ++i ) /*0x4edcbf*/
    sub_4EC1F0(v14, v13, v9, i); /*0x4edccd*/
}