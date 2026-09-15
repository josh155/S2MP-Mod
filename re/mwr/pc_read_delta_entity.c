__int64 __fastcall sub_4ECBE0(_DWORD *a1, unsigned int a2, _BYTE *a3, __int64 a4, __int16 a5, int a6)
{
  __int64 result; // rax
  unsigned __int16 *v11; // r15
  int v13; // edx
  int v14; // edx
  int v15; // r13d
  int v16; // esi
  int v17; // ebx
  int v18; // r12d
  __int64 *v19; // rax
  __int64 v20; // r15
  int v21; // edx
  _BYTE *v22; // rax
  __int64 v23; // rcx
  __int128 v24; // xmm0
  __int128 v25; // xmm1
  __int128 v26; // xmm0
  __int128 v27; // xmm1
  __int128 v28; // xmm0
  __int128 v29; // xmm1
  __int128 v30; // xmm0
  __int128 v31; // xmm1
  int v32; // eax
  int i; // ebx
  bool v34; // al
  __int64 v35; // r12
  unsigned __int16 *v36; // rbx
  bool v37; // cl
  int j; // esi
  int v39; // [rsp+30h] [rbp-178h]
  bool v40; // [rsp+40h] [rbp-168h]
  int v41; // [rsp+44h] [rbp-164h]
  int v43; // [rsp+4Ch] [rbp-15Ch]
  __int64 v44; // [rsp+50h] [rbp-158h]
  _BYTE v45[4]; // [rsp+60h] [rbp-148h] BYREF
  __int16 v46; // [rsp+64h] [rbp-144h]
  char v47; // [rsp+6Bh] [rbp-13Dh]
  char v48; // [rsp+6Ch] [rbp-13Ch]
  int v49; // [rsp+C0h] [rbp-E8h]
  int v50; // [rsp+E4h] [rbp-C4h]
  int v51; // [rsp+108h] [rbp-A0h]

  result = MSG_ReadShort((__int64)a1); /*0x4ecc0e*/
  if ( (_DWORD)result != 1 ) /*0x4ecc16*/
  {
    if ( (unsigned int)MSG_ReadShort((__int64)a1) ) /*0x4ecc20*/
    {
      v11 = (unsigned __int16 *)off_12D4BA8[12]; /*0x4ecc59*/
      v40 = (unsigned int)MSG_ReadShort((__int64)a1) != 0; /*0x4ecc69*/
      if ( !_BitScanReverse((unsigned int *)&v13, 0x48u) ) /*0x4ecc6e*/
        v14 = 32; /*0x4ecc7d*/
      else
        v14 = v13 ^ 0x1F; /*0x4ecc78*/
      v15 = MSG_ReadBits(a1, (unsigned int)(32 - v14)); /*0x4ecc8b*/
      if ( v15 >= 72 || (*(_WORD *)a4 = a5, v16 = sub_4F0780(a1, 3, (unsigned int)(v15 + 1)) - 1, v41 = v16, v16 >= 72) ) /*0x4ecccb*/
      {
        sub_4EB190(a1); /*0x4ecc96*/
      }
      else
      {
        if ( v16 ) /*0x4ecce4*/
        {
          v17 = -1; /*0x4ecce6*/
          sub_4EC1F0((__int64)v11, (__int64)a3, a4, 0); /*0x4eccf5*/
        }
        else
        {
          LOBYTE(v39) = 0; /*0x4eccfc*/
          sub_4ED0E0((__int64)a1, a2, (__int64)a3, a4, v11, 0, v39); /*0x4ecd19*/
          v17 = 0; /*0x4ecd1e*/
          if ( v15 > 0 ) /*0x4ecd23*/
          {
            v16 = sub_4F0780(a1, 3, (unsigned int)v15); /*0x4ecd33*/
            v41 = v16; /*0x4ecd35*/
          }
        }
        v18 = *(unsigned __int8 *)(a4 + 10); /*0x4ecd39*/
        v19 = (__int64 *)sub_4F2C30(v18); /*0x4ecd41*/
        v20 = *v19; /*0x4ecd4e*/
        v21 = *((_DWORD *)v19 + 2); /*0x4ecd51*/
        v44 = *v19; /*0x4ecd54*/
        v43 = v21; /*0x4ecd59*/
        if ( a6 ) /*0x4ecd5d*/
        {
          v22 = v45; /*0x4ecd63*/
          v23 = 2; /*0x4ecd68*/
          do /*0x4ecdc1*/
          {
            v22 += 128; /*0x4ecd70*/
            v24 = *(_OWORD *)a3; /*0x4ecd77*/
            v25 = *((_OWORD *)a3 + 1); /*0x4ecd7a*/
            a3 += 128; /*0x4ecd7e*/
            *((_OWORD *)v22 - 8) = v24; /*0x4ecd85*/
            v26 = *((_OWORD *)a3 - 6); /*0x4ecd89*/
            *((_OWORD *)v22 - 7) = v25; /*0x4ecd8d*/
            v27 = *((_OWORD *)a3 - 5); /*0x4ecd91*/
            *((_OWORD *)v22 - 6) = v26; /*0x4ecd95*/
            v28 = *((_OWORD *)a3 - 4); /*0x4ecd99*/
            *((_OWORD *)v22 - 5) = v27; /*0x4ecd9d*/
            v29 = *((_OWORD *)a3 - 3); /*0x4ecda1*/
            *((_OWORD *)v22 - 4) = v28; /*0x4ecda5*/
            v30 = *((_OWORD *)a3 - 2); /*0x4ecda9*/
            *((_OWORD *)v22 - 3) = v29; /*0x4ecdad*/
            v31 = *((_OWORD *)a3 - 1); /*0x4ecdb1*/
            *((_OWORD *)v22 - 2) = v30; /*0x4ecdb5*/
            *((_OWORD *)v22 - 1) = v31; /*0x4ecdb9*/
            --v23; /*0x4ecdbd*/
          }
          while ( v23 ); /*0x4ecdc1*/
          switch ( v18 ) /*0x4ecdc7*/
          {
            case 2: /*0x4ecdc7*/
              v47 = 7; /*0x4ecdce*/
              v46 = 2046; /*0x4ecdd3*/
              break;
            case 1: /*0x4ecdc7*/
              v47 = 7; /*0x4ecde5*/
              v46 = 2046; /*0x4ecdea*/
              v48 = a5; /*0x4ecdf6*/
              v49 = 3; /*0x4ecdfa*/
              v50 = 1; /*0x4ece05*/
              break;
            case 18: /*0x4ecdc7*/
              v47 = 7; /*0x4ece1a*/
              v46 = 2046; /*0x4ece1f*/
              break;
            case 3: /*0x4ecdc7*/
              v48 = 42; /*0x4ece31*/
              v46 = 2046; /*0x4ece36*/
              break;
            default:
              v32 = v51; /*0x4ece3d*/
              if ( v18 == 6 ) /*0x4ece4d*/
                v32 = 2047; /*0x4ece4d*/
              v51 = v32; /*0x4ece50*/
              break;
          }
          a3 = v45; /*0x4ece57*/
        }
        if ( v15 < v21 ) /*0x4ece5f*/
        {
          if ( v15 ) /*0x4ece70*/
          {
            while ( 1 ) /*0x4ece80*/
            {
              for ( i = v17 + 1; i < v16; ++i ) /*0x4ece84*/
                sub_4EC1F0(v20, (__int64)a3, a4, i); /*0x4ece9c*/
              v34 = a3[10] != *(_BYTE *)(a4 + 10) || v40 && sub_4EC2E0(*(__int16 *)(v20 + 8LL * v16 + 4)); /*0x4eceb6*/
              LOBYTE(v39) = v34; /*0x4eced7*/
              sub_4ED0E0((__int64)a1, a2, (__int64)a3, a4, (unsigned __int16 *)(v20 + 8LL * v16), 0, v39); /*0x4eceee*/
              if ( v16 >= v15 ) /*0x4ecef6*/
                break; /*0x4ecef6*/
              v17 = v16; /*0x4ecf06*/
              v16 += sub_4F0780(a1, 3, (unsigned int)(v15 - v16)); /*0x4ecf0d*/
            }
            v41 = v16; /*0x4ecf14*/
          }
          v35 = v16; /*0x4ecf18*/
          if ( v16 > 0 ) /*0x4ecf1d*/
          {
            v36 = (unsigned __int16 *)(v20 + 4); /*0x4ecf23*/
            do /*0x4ecf81*/
            {
              if ( (v36[1] & 2) != 0 ) /*0x4ecf34*/
              {
                v37 = a3[10] != *(_BYTE *)(a4 + 10) || v40 && sub_4EC2E0((__int16)*v36); /*0x4ecf55*/
                LOBYTE(v39) = v37; /*0x4ecf57*/
                sub_4ED0E0((__int64)a1, a2, (__int64)a3, a4, v36 - 2, 0, v39); /*0x4ecf74*/
              }
              v36 += 4; /*0x4ecf79*/
              --v35; /*0x4ecf7d*/
            }
            while ( v35 ); /*0x4ecf81*/
            v16 = v41; /*0x4ecf83*/
            v20 = v44; /*0x4ecf87*/
          }
          for ( j = v16 + 1; j < v43; ++j ) /*0x4ecf94*/
            sub_4EC1F0(v20, (__int64)a3, a4, j); /*0x4ecfac*/
        }
        else
        {
          *a1 = 1; /*0x4ece61*/
        }
      }
    }
    else
    {
      sub_59F870(a4, a3, 256); /*0x4ecc35*/
    }
    return 0; /*0x4ecfd7*/
  }
  return result; /*0x4ecfd9*/
}