int __cdecl MSG_WriteDeltaPlayerstate(int a1, int a2, int a3, _BYTE *a4, int a5)
{
  int v5; // edx
  int v6; // ebx
  int v7; // eax
  float *v8; // edx
  float *v9; // edi
  int MinBitCountForNum; // eax
  char v11; // si
  int v12; // ebx
  int v13; // eax
  float *v14; // edx
  float *v15; // eax
  bool v16; // al
  char v17; // al
  int v18; // ebx
  _DWORD *v19; // ecx
  _DWORD *v20; // edx
  int k; // ebx
  int v22; // edi
  _DWORD *v23; // ebx
  int m; // esi
  int v25; // ebx
  int v26; // edx
  int v27; // edx
  int v28; // edx
  int v29; // edx
  int v30; // edx
  int v31; // edx
  int v32; // edx
  int v33; // edx
  _DWORD *v34; // esi
  int ii; // edi
  int kk; // ebx
  int v38; // eax
  float *v39; // edx
  float *v40; // esi
  BOOL v41; // eax
  int v42; // [esp+28h] [ebp-3000h]
  int v43; // [esp+2Ch] [ebp-2FFCh]
  int v44; // [esp+30h] [ebp-2FF8h]
  int v45; // [esp+34h] [ebp-2FF4h]
  int v46; // [esp+38h] [ebp-2FF0h]
  int v47; // [esp+3Ch] [ebp-2FECh]
  _BYTE *v48; // [esp+44h] [ebp-2FE4h]
  int v49; // [esp+50h] [ebp-2FD8h]
  int v50; // [esp+54h] [ebp-2FD4h]
  int v51; // [esp+58h] [ebp-2FD0h]
  char *j; // [esp+5Ch] [ebp-2FCCh]
  float *v53; // [esp+60h] [ebp-2FC8h]
  int v54; // [esp+64h] [ebp-2FC4h]
  int v55; // [esp+68h] [ebp-2FC0h]
  char v56; // [esp+6Ch] [ebp-2FBCh]
  _DWORD *v57; // [esp+70h] [ebp-2FB8h]
  int n; // [esp+74h] [ebp-2FB4h]
  int v59; // [esp+78h] [ebp-2FB0h]
  _DWORD *v60; // [esp+7Ch] [ebp-2FACh]
  int i; // [esp+80h] [ebp-2FA8h]
  _DWORD *v62; // [esp+84h] [ebp-2FA4h]
  _DWORD *v63; // [esp+88h] [ebp-2FA0h]
  int jj; // [esp+8Ch] [ebp-2F9Ch]
  _DWORD v66[4]; // [esp+98h] [ebp-2F90h]
  _BYTE v67[12132]; // [esp+A8h] [ebp-2F80h] BYREF
  int v68; // [esp+300Ch] [ebp-1Ch]

  v48 = a4; /*0x173231*/
  MSG_GetUsedBitCount(a2); /*0x173256*/
  if ( !a4 ) /*0x173263*/
  {
    memset(v67, 0, sizeof(v67)); /*0x174410*/
    v48 = v67; /*0x174415*/
  }
  if ( !*(_BYTE *)(a1 + 13) /*0x1742f0*/
    && (v5 = *(_DWORD *)(a1 + 4), dword_CD2DD60)
    && (float)((float)((float)((float)(*(float *)(a5 + 28) - *(float *)(v5 + 1588))
                             * (float)(*(float *)(a5 + 28) - *(float *)(v5 + 1588)))
                     + (float)((float)(*(float *)(a5 + 32) - *(float *)(v5 + 1592))
                             * (float)(*(float *)(a5 + 32) - *(float *)(v5 + 1592))))
             + (float)((float)(*(float *)(a5 + 36) - *(float *)(v5 + 1596))
                     * (float)(*(float *)(a5 + 36) - *(float *)(v5 + 1596)))) <= 0.0099999998
    && *(_DWORD *)(v5 + 1600) == *(_DWORD *)a5 )
  {
    MSG_WriteBit0(a2); /*0x1742ff*/
    v56 = 0; /*0x174304*/
  }
  else
  {
    MSG_WriteBit1(a2); /*0x1732ee*/
    v56 = 1; /*0x1732f3*/
  }
  v60 = &unk_40F490; /*0x1732fd*/
  v51 = 0; /*0x173307*/
  for ( i = 1; i != 142; ++i ) /*0x173311*/
  {
    v6 = *(v60 - 2); /*0x173326*/
    if ( v6 == -87 ) /*0x17332c*/
    {
      if ( *(_BYTE *)(a1 + 13) /*0x1735fb*/
        || (*(_BYTE *)(a5 + 20) & 2) != 0
        || ((v48[176] ^ *(_BYTE *)(a5 + 176)) & 2) != 0
        || *(_DWORD *)(a5 + 1436) != 1023
        || *(_DWORD *)(a5 + 4) == 5 )
      {
LABEL_16:
        v51 = i; /*0x1733b0*/
      }
    }
    else if ( *((_BYTE *)v60 - 4) == 3 && (v16 = v56, !*(_BYTE *)(a1 + 13)) ) /*0x173621*/
    {
LABEL_26:
      if ( v16 ) /*0x1734e2*/
        goto LABEL_16; /*0x1734e2*/
    }
    else
    {
      v7 = *(v60 - 3); /*0x17333e*/
      v8 = (float *)&v48[v7]; /*0x173347*/
      v9 = (float *)(v7 + a5); /*0x173350*/
      if ( *(_DWORD *)&v48[v7] != *(_DWORD *)(v7 + a5) ) /*0x173359*/
      {
        switch ( v6 ) /*0x173363*/
        {
          case -100: /*0x173363*/
          case -87: /*0x173363*/
            v16 = (unsigned __int16)(int)(float)((float)(182.04445 * *v9) + 0.5) != (unsigned __int16)(int)(float)((float)(182.04445 * *v8) + 0.5); /*0x173546*/
            goto LABEL_26; /*0x173549*/
          case -95: /*0x173363*/
            v16 = *(_DWORD *)&v48[v7] / 100 != *(_DWORD *)(v7 + a5) / 100; /*0x17350e*/
            goto LABEL_26; /*0x173511*/
          case -92: /*0x173363*/
          case -91: /*0x173363*/
          case -90: /*0x173363*/
            *(float *)&v47 = floorf(*v8 + 0.5); /*0x1734a1*/
            *(float *)&v46 = floorf(*v9 + 0.5); /*0x1734c5*/
            v16 = v47 != v46; /*0x1734d5*/
            goto LABEL_26; /*0x1734d5*/
          default:
            goto LABEL_16;
        }
      }
    }
    v60 += 4; /*0x1733bc*/
  }
  MinBitCountForNum = GetMinBitCountForNum(0x8Du); /*0x1733e0*/
  MSG_WriteBits(a2, v51, MinBitCountForNum); /*0x1733fc*/
  if ( v51 > 0 ) /*0x173409*/
  {
    v49 = 0; /*0x17340f*/
    for ( j = (char *)&playerStateFields; ; j += 16 ) /*0x173419*/
    {
      v11 = j[12]; /*0x173429*/
      if ( v11 == 2 ) /*0x173432*/
        break; /*0x173432*/
      v12 = *((_DWORD *)j + 2); /*0x173438*/
      if ( v12 == -87 ) /*0x17343e*/
      {
        if ( *(_BYTE *)(a1 + 13) ) /*0x173639*/
          goto LABEL_40; /*0x17363d*/
        if ( (*(_BYTE *)(a5 + 20) & 2) != 0 /*0x17367d*/
          || ((v48[176] ^ *(_BYTE *)(a5 + 176)) & 2) != 0
          || *(_DWORD *)(a5 + 1436) != 1023
          || *(_DWORD *)(a5 + 4) == 5 )
        {
          goto LABEL_32; /*0x17367d*/
        }
      }
      else if ( v11 != 3 || *(_BYTE *)(a1 + 13) ) /*0x173db6*/
      {
        v13 = *((_DWORD *)j + 1); /*0x173454*/
        v14 = (float *)&v48[v13]; /*0x17345d*/
        v15 = (float *)(a5 + v13); /*0x173460*/
        v53 = v15; /*0x173466*/
        if ( *(_DWORD *)v14 != *(_DWORD *)v15 ) /*0x173472*/
        {
          switch ( v12 ) /*0x173484*/
          {
            case -100: /*0x173484*/
            case -87: /*0x173484*/
              if ( (unsigned __int16)(int)(float)((float)(182.04445 * *v15) + 0.5) == (unsigned __int16)(int)(float)((float)(182.04445 * *v14) + 0.5) ) /*0x17425b*/
                break; /*0x17425b*/
              goto LABEL_31; /*0x17425b*/
            case -95: /*0x173484*/
              if ( *(_DWORD *)v14 / 100 != *(_DWORD *)v15 / 100 ) /*0x173572*/
                goto LABEL_31; /*0x173572*/
              break; /*0x173572*/
            case -92: /*0x173484*/
            case -91: /*0x173484*/
            case -90: /*0x173484*/
              *(float *)&v45 = floorf(*v14 + 0.5); /*0x17428a*/
              *(float *)&v44 = floorf(*v53 + 0.5); /*0x1742b4*/
              if ( v45 == v44 ) /*0x1742c9*/
                break; /*0x1742c9*/
              goto LABEL_31; /*0x1742c9*/
            default:
              goto LABEL_31;
          }
        }
      }
      else if ( v56 ) /*0x173dc2*/
      {
        break; /*0x173dc2*/
      }
      MSG_WriteBit0(a2); /*0x1742cf*/
LABEL_34:
      if ( ++v49 == v51 ) /*0x1735e5*/
        goto LABEL_47; /*0x1735e5*/
    }
LABEL_31:
    if ( *(_BYTE *)(a1 + 13) ) /*0x17357e*/
LABEL_40:
      v17 = 0; /*0x17362c*/
    else
LABEL_32:
      v17 = v11 == 3; /*0x17358a*/
    MSG_WriteDeltaField(v48, a5, j, v49, v17); /*0x1735ce*/
    goto LABEL_34; /*0x1735ce*/
  }
LABEL_47:
  v18 = *(_DWORD *)(a5 + 328) != *((_DWORD *)v48 + 82); /*0x173696*/
  if ( *(_DWORD *)(a5 + 332) != *((_DWORD *)v48 + 83) ) /*0x1736ca*/
    v18 = (*(_DWORD *)(a5 + 328) != *((_DWORD *)v48 + 82)) | 2; /*0x1736ca*/
  if ( *(_DWORD *)(a5 + 336) != *((_DWORD *)v48 + 84) ) /*0x1736e4*/
    v18 |= 4u; /*0x1736e4*/
  if ( *(_DWORD *)(a5 + 340) != *((_DWORD *)v48 + 85) ) /*0x173704*/
    v18 |= 8u; /*0x173704*/
  if ( *(_DWORD *)(a5 + 344) != *((_DWORD *)v48 + 86) ) /*0x17371e*/
    v18 |= 0x10u; /*0x17371e*/
  if ( v18 ) /*0x173723*/
  {
    MSG_WriteBit1(a2); /*0x173732*/
    MSG_WriteBits(a2, v18, 5); /*0x17374c*/
    if ( (v18 & 1) != 0 ) /*0x173754*/
    {
      MSG_WriteShort(a2, *(_DWORD *)(a5 + 328)); /*0x174349*/
      if ( (v18 & 2) != 0 ) /*0x174351*/
        goto LABEL_184; /*0x174351*/
LABEL_58:
      if ( (v18 & 4) == 0 ) /*0x173766*/
        goto LABEL_59; /*0x173766*/
LABEL_185:
      MSG_WriteShort(a2, *(_DWORD *)(a5 + 336)); /*0x17437e*/
      if ( (v18 & 8) != 0 ) /*0x17439f*/
        goto LABEL_186; /*0x17439f*/
LABEL_60:
      if ( (v18 & 0x10) != 0 ) /*0x173778*/
LABEL_187:
        MSG_WriteByte(a2, *(_DWORD *)(a5 + 344)); /*0x1743d4*/
    }
    else
    {
      if ( (v18 & 2) == 0 ) /*0x17375d*/
        goto LABEL_58; /*0x17375d*/
LABEL_184:
      MSG_WriteShort(a2, *(_DWORD *)(a5 + 332)); /*0x174357*/
      if ( (v18 & 4) != 0 ) /*0x174378*/
        goto LABEL_185; /*0x174378*/
LABEL_59:
      if ( (v18 & 8) == 0 ) /*0x17376f*/
        goto LABEL_60; /*0x17376f*/
LABEL_186:
      MSG_WriteBits(a2, *(_DWORD *)(a5 + 340), 6); /*0x1743a5*/
      if ( (v18 & 0x10) != 0 ) /*0x1743ce*/
        goto LABEL_187; /*0x1743ce*/
    }
  }
  else
  {
    MSG_WriteBit0(a2); /*0x173e37*/
  }
  v59 = a5; /*0x173784*/
  v62 = v48; /*0x173790*/
  v19 = (_DWORD *)a5; /*0x173796*/
  v20 = v48; /*0x173798*/
  for ( k = 1; k != 5; ++k ) /*0x17379e*/
  {
    v66[k - 1] = 0; /*0x1737a3*/
    if ( v19[87] != v20[87] ) /*0x1737ba*/
      v66[k - 1] = 1; /*0x1737bc*/
    if ( v19[88] != v20[88] ) /*0x1737d3*/
      v66[k - 1] |= 2u; /*0x1737d5*/
    if ( v19[89] != v20[89] ) /*0x1737e9*/
      v66[k - 1] |= 4u; /*0x1737eb*/
    if ( v19[90] != v20[90] ) /*0x1737ff*/
      v66[k - 1] |= 8u; /*0x173801*/
    if ( v19[91] != v20[91] ) /*0x173815*/
      v66[k - 1] |= 0x10u; /*0x173817*/
    if ( v19[92] != v20[92] ) /*0x17382b*/
      v66[k - 1] |= 0x20u; /*0x17382d*/
    if ( v19[93] != v20[93] ) /*0x173841*/
      v66[k - 1] |= 0x40u; /*0x173843*/
    if ( v19[94] != v20[94] ) /*0x173857*/
      v66[k - 1] |= 0x80u; /*0x173859*/
    if ( v19[95] != v20[95] ) /*0x173870*/
      v66[k - 1] |= 0x100u; /*0x173872*/
    if ( v19[96] != v20[96] ) /*0x173889*/
      v66[k - 1] |= 0x200u; /*0x17388b*/
    if ( v19[97] != v20[97] ) /*0x1738a2*/
      v66[k - 1] |= 0x400u; /*0x1738a4*/
    if ( v19[98] != v20[98] ) /*0x1738bb*/
      v66[k - 1] |= 0x800u; /*0x1738bd*/
    if ( v19[99] != v20[99] ) /*0x1738d4*/
      v66[k - 1] |= 0x1000u; /*0x1738d6*/
    if ( v19[100] != v20[100] ) /*0x1738ed*/
      v66[k - 1] |= 0x2000u; /*0x1738ef*/
    if ( v19[101] != v20[101] ) /*0x173906*/
      v66[k - 1] |= 0x4000u; /*0x173908*/
    if ( v19[102] != v20[102] ) /*0x17391f*/
      v66[k - 1] |= 0x8000u; /*0x173921*/
    v19 += 16; /*0x17392d*/
    v20 += 16; /*0x173930*/
  }
  if ( v66[0] || v66[1] || v66[2] || v66[3] ) /*0x174204*/
  {
    MSG_WriteBit1(a2); /*0x17395d*/
    v50 = 0; /*0x173962*/
LABEL_98:
    while ( 2 ) /*0x173972*/
    {
      while ( 1 ) /*0x173972*/
      {
        v22 = v66[v50]; /*0x173972*/
        if ( v22 ) /*0x17397b*/
          break; /*0x17397b*/
        MSG_WriteBit0(a2); /*0x173d8c*/
        if ( ++v50 == 4 ) /*0x173d9e*/
          goto LABEL_103; /*0x173d9e*/
      }
      MSG_WriteBit1(a2); /*0x17398a*/
      MSG_WriteShort(a2, v22); /*0x17399c*/
      v23 = (_DWORD *)(a5 + (v50 << 6) + 348); /*0x1739b0*/
      for ( m = 0; m != 16; ++m ) /*0x1739b7*/
      {
        while ( ((v22 >> m) & 1) == 0 ) /*0x1739c8*/
        {
          ++m; /*0x1739ce*/
          ++v23; /*0x1739cf*/
          if ( m == 16 ) /*0x1739d5*/
          {
            if ( ++v50 != 4 ) /*0x1739e4*/
              goto LABEL_98; /*0x1739e4*/
            goto LABEL_103; /*0x1739e4*/
          }
        }
        MSG_WriteShort(a2, *v23++); /*0x173d44*/
      }
      if ( ++v50 != 4 ) /*0x173d63*/
        continue; /*0x173d63*/
      break;
    }
  }
  else
  {
    MSG_WriteBit0(a2); /*0x174213*/
  }
LABEL_103:
  v63 = (_DWORD *)a5; /*0x1739e6*/
  for ( n = 0; n != 128; n += 16 ) /*0x1739f2*/
  {
    v25 = v63[215] != v62[215]; /*0x173a16*/
    if ( v63[216] != v62[216] ) /*0x173a2a*/
      v25 = (v63[215] != v62[215]) | 2; /*0x173a2a*/
    if ( v63[217] != v62[217] ) /*0x173a44*/
      v25 |= 4u; /*0x173a44*/
    if ( v63[218] != v62[218] ) /*0x173a64*/
      v25 |= 8u; /*0x173a64*/
    if ( v63[219] != v62[219] ) /*0x173a7e*/
      v25 |= 0x10u; /*0x173a7e*/
    if ( v63[220] != v62[220] ) /*0x173a9e*/
      v25 |= 0x20u; /*0x173a9e*/
    if ( v63[221] != v62[221] ) /*0x173ab8*/
      v25 |= 0x40u; /*0x173ab8*/
    v26 = v25; /*0x173ac7*/
    if ( v63[222] != v62[222] ) /*0x173ad8*/
    {
      LOBYTE(v26) = v25 | 0x80; /*0x173ac9*/
      v25 = v26; /*0x173ad8*/
    }
    v27 = v25; /*0x173ae7*/
    if ( v63[223] != v62[223] ) /*0x173af2*/
    {
      BYTE1(v27) = BYTE1(v25) | 1; /*0x173ae9*/
      v25 = v27; /*0x173af2*/
    }
    v28 = v25; /*0x173b01*/
    if ( v63[224] != v62[224] ) /*0x173b12*/
    {
      BYTE1(v28) = BYTE1(v25) | 2; /*0x173b03*/
      v25 = v28; /*0x173b12*/
    }
    v29 = v25; /*0x173b21*/
    if ( v63[225] != v62[225] ) /*0x173b2c*/
    {
      BYTE1(v29) = BYTE1(v25) | 4; /*0x173b23*/
      v25 = v29; /*0x173b2c*/
    }
    v30 = v25; /*0x173b3b*/
    if ( v63[226] != v62[226] ) /*0x173b4c*/
    {
      BYTE1(v30) = BYTE1(v25) | 8; /*0x173b3d*/
      v25 = v30; /*0x173b4c*/
    }
    v31 = v25; /*0x173b5b*/
    if ( v63[227] != v62[227] ) /*0x173b66*/
    {
      BYTE1(v31) = BYTE1(v25) | 0x10; /*0x173b5d*/
      v25 = v31; /*0x173b66*/
    }
    v32 = v25; /*0x173b75*/
    if ( v63[228] != v62[228] ) /*0x173b86*/
    {
      BYTE1(v32) = BYTE1(v25) | 0x20; /*0x173b77*/
      v25 = v32; /*0x173b86*/
    }
    v33 = v25; /*0x173b95*/
    if ( v63[229] != v62[229] ) /*0x173ba0*/
    {
      BYTE1(v33) = BYTE1(v25) | 0x40; /*0x173b97*/
      v25 = v33; /*0x173ba0*/
    }
    if ( v63[230] != v62[230] ) /*0x173bbb*/
      BYTE1(v25) |= 0x80u; /*0x173bbd*/
    if ( v25 ) /*0x173bc2*/
    {
      MSG_WriteBit1(a2); /*0x173bd1*/
      MSG_WriteShort(a2, v25); /*0x173be3*/
      v34 = (_DWORD *)(a5 + 4 * n + 860); /*0x173bf4*/
      for ( ii = 0; ii != 16; ++ii ) /*0x173bfb*/
      {
        while ( ((v25 >> ii) & 1) == 0 ) /*0x173c11*/
        {
          ++ii; /*0x173c00*/
          ++v34; /*0x173c01*/
          if ( ii == 16 ) /*0x173c07*/
            goto LABEL_139; /*0x173c07*/
        }
        MSG_WriteShort(a2, *v34++); /*0x173c22*/
      }
    }
    else
    {
      MSG_WriteBit0(a2); /*0x173d79*/
    }
LABEL_139:
    v63 += 16; /*0x173c30*/
    v62 += 16; /*0x173c37*/
  }
  if ( !memcmp(v48 + 1628, (const void *)(a5 + 1628), 0x1C0u) ) /*0x173c7b*/
  {
    MSG_WriteBit0(a2); /*0x173c91*/
  }
  else
  {
    MSG_WriteBit1(a2); /*0x173eb9*/
    for ( jj = 0; jj != 16; ++jj ) /*0x173ebe*/
    {
      MSG_WriteBits(a2, *(_DWORD *)(v59 + 1628), 3); /*0x174090*/
      v38 = 28 * jj + 1616; /*0x17409c*/
      v54 = a5 + v38 + 12; /*0x1740ab*/
      v55 = (int)&v48[v38 + 12]; /*0x1740bb*/
      v57 = &unk_40FD64; /*0x1740c1*/
      while ( 1 ) /*0x1740e1*/
      {
        v39 = (float *)(*v57 + v55); /*0x1740e1*/
        v40 = (float *)(*v57 + v54); /*0x1740e9*/
        if ( *(_DWORD *)v39 != *(_DWORD *)v40 ) /*0x1740f1*/
          break; /*0x1740f1*/
LABEL_169:
        v57 += 4; /*0x17415e*/
        if ( v57 == (_DWORD *)&unk_40FDC4 ) /*0x17416f*/
        {
          MSG_WriteBit0(a2); /*0x17417e*/
          goto LABEL_163; /*0x174183*/
        }
      }
      switch ( v57[1] ) /*0x1740ff*/
      {
        case 0xFFFFFF9C: /*0x1740ff*/
        case 0xFFFFFFA9: /*0x1740ff*/
          v41 = (unsigned __int16)(int)(float)((float)(182.04445 * *v40) + 0.5) == (unsigned __int16)(int)(float)((float)(182.04445 * *v39) + 0.5); /*0x1741be*/
          goto LABEL_168; /*0x1741c1*/
        case 0xFFFFFFA1: /*0x1740ff*/
          v41 = *(_DWORD *)v39 / 100 == *(_DWORD *)v40 / 100; /*0x1741e6*/
          goto LABEL_168; /*0x1741e9*/
        case 0xFFFFFFA4: /*0x1740ff*/
        case 0xFFFFFFA5: /*0x1740ff*/
        case 0xFFFFFFA6: /*0x1740ff*/
          *(float *)&v43 = floorf(*v39 + 0.5); /*0x17411c*/
          *(float *)&v42 = floorf(*v40 + 0.5); /*0x174140*/
          v41 = v43 == v42; /*0x174153*/
LABEL_168:
          if ( v41 ) /*0x174158*/
            goto LABEL_169; /*0x174158*/
          goto LABEL_162; /*0x174158*/
        default:
LABEL_162:
          MSG_WriteBit1(a2); /*0x173ecd*/
          MSG_WriteDeltaField(v55, v54, &objectiveFields, 0, 0); /*0x173f15*/
          MSG_WriteDeltaField(v55, v54, &unk_40FD70, 1, 0); /*0x173f54*/
          MSG_WriteDeltaField(v55, v54, &unk_40FD80, 2, 0); /*0x173f93*/
          MSG_WriteDeltaField(v55, v54, &unk_40FD90, 3, 0); /*0x173fd2*/
          MSG_WriteDeltaField(v55, v54, &unk_40FDA0, 4, 0); /*0x174011*/
          MSG_WriteDeltaField(v55, v54, &unk_40FDB0, 5, 0); /*0x174050*/
          break; /*0x174050*/
      }
LABEL_163:
      v59 += 28; /*0x17405b*/
    }
  }
  if ( !memcmp(v48 + 2212, (const void *)(a5 + 2212), 0x26C0u) ) /*0x173cbd*/
  {
    MSG_WriteBit0(a2); /*0x173cd3*/
  }
  else
  {
    MSG_WriteBit1(a2); /*0x173e4a*/
    MSG_WriteDeltaHudElems(a2, (int)(v48 + 7172), (_DWORD *)(a5 + 7172), 31); /*0x173e83*/
    MSG_WriteDeltaHudElems(a2, (int)(v48 + 2212), (_DWORD *)(a5 + 2212), 31); /*0x173ea6*/
  }
  if ( !memcmp(v48 + 2076, (const void *)(a5 + 2076), 0x80u) ) /*0x173cfe*/
  {
    MSG_WriteBit0(a2); /*0x173d14*/
  }
  else
  {
    MSG_WriteBit1(a2); /*0x173dd6*/
    MSG_WriteByte(a2, *(_BYTE *)(a5 + 2076)); /*0x173df5*/
    for ( kk = 1; kk != 128; ++kk ) /*0x173dfa*/
      MSG_WriteByte(a2, *(_BYTE *)(kk + a5 + 2076)); /*0x173e1b*/
  }
  return __stack_chk_guard ^ v68; /*0x173d2a*/
}