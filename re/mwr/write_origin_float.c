double __fastcall MSG_WriteOriginFloat(
        __int64 a1,
        __m128 _XMM0,
        __m128 _XMM1,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        int a7,
        int a8)
{
  int v17; // ebx
  unsigned int v18; // r12d
  __int64 v19; // rcx
  __int64 v20; // r8
  unsigned int v21; // eax
  int v22; // r9d
  int v24; // ecx
  unsigned int v25; // r13d
  int v26; // eax
  int v30; // ecx
  int v31; // r8d
  int v32; // r9d
  const char *v40; // rdx
  int v56; // r9d
  int v58; // ecx
  unsigned int v59; // r13d
  int v60; // eax
  unsigned int v64; // ebx
  int MinBitCountForNum; // eax
  int v66; // edx
  __int64 v67; // r8
  int v68; // r9d
  __int64 v69; // rcx
  bool v74; // zf
  const char *v75; // r13
  unsigned int v76; // r12d
  int v96; // eax
  int v119; // ecx
  int v120; // r8d
  int v121; // r9d

  __asm { vmovss dword ptr [rbp+var_30], xmm0 } /*0x73ad51*/
  _R14 = a5; /*0x73ad60*/
  if ( *(_DWORD *)(a6 + 4) ) /*0x73ad63*/
  {
    __asm { vmovss [rbp+var_3C], xmm1 } /*0x73ad88*/
    MyAssertHandler( /*0x73ad8d*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
      390,
      0,
      (unsigned int)"%s",
      (unsigned int)"!msg->readOnly",
      a8);
    __asm { vmovss xmm1, [rbp+var_3C] } /*0x73ad92*/
  }
  __asm { vroundss xmm0, xmm0, dword ptr [rbp+var_30], 1 } /*0x73ad97*/
  __asm
  {
    vcvttss2si ebx, xmm0
    vxorps xmm0, xmm0, xmm0
    vroundss xmm0, xmm0, xmm1, 1
    vcvttss2si eax, xmm0
  }
  v17 = _EBX - _EAX; /*0x73adb3*/
  v18 = v17 + 64; /*0x73adb5*/
  if ( (unsigned int)(v17 + 64) > 0x7F ) /*0x73adbd*/
  {
    MSG_WriteBit1(a6); /*0x73af1c*/
    if ( (unsigned int)(a7 + 106) > 0x17 || (_R12 = 0, v58 = 8404993, !_bittest(&v58, a7 + 106)) ) /*0x73af35*/
    {
      v59 = a7 + 105; /*0x73af37*/
      _R12 = 1; /*0x73af3b*/
      if ( v59 > 0x17 || (v60 = 8404993, !_bittest(&v60, v59)) ) /*0x73af50*/
        MyAssertHandler( /*0x73af70*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
          455,
          0,
          (unsigned int)"%s",
          (unsigned int)"(bits == MSG_FIELD_ORIGINY) || (bits == MSG_FIELD_ES_ORIGINY) || (bits == MSG_FIELD_MOVING_PLATFORM_ORIGINY)",
          v56);
    }
    __asm /*0x73af75*/
    {
      vmovss xmm0, dword ptr [r14+r12*4]
      vroundss xmm0, xmm0, xmm0, 1
      vcvttss2si eax, xmm0
    }
    v64 = v17 - _EAX + 0x8000; /*0x73af87*/
    MinBitCountForNum = GetMinBitCountForNum(v64); /*0x73af8f*/
    v69 = (unsigned int)MinBitCountForNum; /*0x73af94*/
    if ( MinBitCountForNum >= 17 ) /*0x73af99*/
    {
      __asm /*0x73af9f*/
      {
        vmovss xmm0, dword ptr [rbp+var_30]
        vmovss xmm3, cs:dword_FA0BF8
        vmovss xmm8, cs:dword_FA0BFC
        vmovss xmm7, cs:dword_FA0C00
      }
      v74 = (_DWORD)_R12 == 0; /*0x73afbc*/
      v75 = "X"; /*0x73afc6*/
      v76 = MinBitCountForNum; /*0x73afd4*/
      if ( !v74 ) /*0x73afd7*/
        v75 = "Y"; /*0x73afd7*/
      __asm /*0x73afe0*/
      {
        vcvtss2sd xmm0, xmm0, xmm0
        vmovsd [rbp+var_30], xmm0
        vmovss xmm4, dword ptr [r14]
        vmovss xmm5, dword ptr [r14+4]
        vmovss xmm6, dword ptr [r14+8]
        vaddss xmm1, xmm4, xmm3
        vaddss xmm2, xmm5, xmm3
        vaddss xmm3, xmm6, xmm3
        vaddss xmm4, xmm4, xmm8
        vaddss xmm5, xmm5, xmm8
        vaddss xmm6, xmm6, xmm8
        vaddss xmm4, xmm4, xmm7
        vaddss xmm5, xmm5, xmm7
        vaddss xmm6, xmm6, xmm7
        vcvtss2sd xmm1, xmm1, xmm1
        vcvtss2sd xmm2, xmm2, xmm2
        vcvtss2sd xmm3, xmm3, xmm3
        vcvtss2sd xmm4, xmm4, xmm4
        vcvtss2sd xmm5, xmm5, xmm5
        vcvtss2sd xmm6, xmm6, xmm6
      }
      v96 = va( /*0x73b039*/
              (unsigned int)"Entity with %s coordinate of %f is too far outside the playable area of the map.  The playab"
                            "le area goes from ( %f, %f, %f ) to ( %f, %f, %f )\n",
              (_DWORD)v75,
              v66,
              MinBitCountForNum,
              v67,
              v68);
      MyAssertHandler( /*0x73b062*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
        470,
        0,
        (unsigned int)"%s\n\t%s",
        (unsigned int)"bitsNeeded <= ORIGIN_FULL_BITS",
        v96);
      __asm /*0x73b067*/
      {
        vmovss xmm0, dword ptr [r14]
        vmovss xmm3, cs:dword_FA0BF8
        vmovss xmm7, cs:dword_FA0BFC
        vmovss xmm8, cs:dword_FA0C00
        vmovss xmm5, dword ptr [r14+4]
        vmovss xmm6, dword ptr [r14+8]
      }
      __asm
      {
        vaddss xmm1, xmm0, xmm3
        vaddss xmm0, xmm0, xmm7
        vaddss xmm2, xmm5, xmm3
        vaddss xmm3, xmm6, xmm3
        vaddss xmm0, xmm0, xmm8
        vcvtss2sd xmm1, xmm1, xmm1
        vcvtss2sd xmm2, xmm2, xmm2
        vcvtss2sd xmm3, xmm3, xmm3
        vcvtss2sd xmm4, xmm0, xmm0
        vaddss xmm0, xmm5, xmm7
        vaddss xmm0, xmm0, xmm8
        vcvtss2sd xmm5, xmm0, xmm0
        vaddss xmm0, xmm6, xmm7
        vaddss xmm0, xmm0, xmm8
        vcvtss2sd xmm6, xmm0, xmm0
        vmovsd xmm0, [rbp+var_30]
      }
      Com_Error( /*0x73b0e5*/
        1,
        (unsigned int)"Entity with %s coordinate of %f is too far outside the playable area of the map.  The playable are"
                      "a goes from ( %f, %f, %f ) to ( %f, %f, %f )\n",
        (_DWORD)v75,
        v119,
        v120,
        v121);
      v69 = v76; /*0x73b0ea*/
    }
    if ( !*(_BYTE *)(a1 + 28) && !*(_BYTE *)(a1 + 29) ) /*0x73b0f7*/
      SV_TrackOriginFullBits((unsigned int)v69); /*0x73b0ff*/
    *(double *)&_XMM0 = MSG_WriteBits(a6, v64, 16, v69, v67); /*0x73b11c*/
  }
  else
  {
    MSG_WriteBit0(a6); /*0x73adc3*/
    if ( !*(_BYTE *)(a1 + 28) && !*(_BYTE *)(a1 + 29) ) /*0x73add2*/
    {
      v21 = GetMinBitCountForNum(v18); /*0x73addb*/
      SV_TrackOriginDeltaBits(v21); /*0x73ade2*/
    }
    MSG_WriteBits(a6, v18, 7, v19, v20); /*0x73adf2*/
    if ( (unsigned int)(a7 + 106) > 0x17 || (_R15 = 0, v24 = 8404993, !_bittest(&v24, a7 + 106)) ) /*0x73ae0b*/
    {
      v25 = a7 + 105; /*0x73ae0d*/
      _R15 = 1; /*0x73ae11*/
      if ( v25 > 0x17 || (v26 = 8404993, !_bittest(&v26, v25)) ) /*0x73ae26*/
        MyAssertHandler( /*0x73ae46*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
          421,
          0,
          (unsigned int)"%s",
          (unsigned int)"(bits == MSG_FIELD_ORIGINY) || (bits == MSG_FIELD_ES_ORIGINY) || (bits == MSG_FIELD_MOVING_PLATFORM_ORIGINY)",
          v22);
    }
    __asm { vmovss xmm0, dword ptr [r14+r15*4] } /*0x73ae4b*/
    __asm
    {
      vaddss xmm0, xmm0, cs:dword_FA0C04
      vcvttss2si eax, xmm0
    }
    if ( (int)GetMinBitCountForNum((unsigned int)(v17 + 0x8000 - _EAX)) >= 17 ) /*0x73ae6f*/
    {
      __asm /*0x73ae75*/
      {
        vmovss xmm4, dword ptr [r14]
        vmovss xmm3, cs:dword_FA0BF8
        vmovss xmm5, dword ptr [r14+4]
        vmovss xmm6, dword ptr [r14+8]
        vmovss xmm8, cs:dword_FA0BFC
        vmovss xmm7, cs:dword_FA0C00
        vmovss xmm0, dword ptr [rbp+var_30]
      }
      v40 = "X"; /*0x73aead*/
      if ( (_DWORD)_R15 ) /*0x73aec0*/
        v40 = "Y"; /*0x73aec0*/
      __asm /*0x73aec6*/
      {
        vaddss xmm1, xmm4, xmm3
        vaddss xmm2, xmm5, xmm3
        vaddss xmm3, xmm6, xmm3
        vaddss xmm4, xmm4, xmm8
        vaddss xmm5, xmm5, xmm8
        vaddss xmm6, xmm6, xmm8
        vcvtss2sd xmm0, xmm0, xmm0
        vaddss xmm4, xmm4, xmm7
        vaddss xmm5, xmm5, xmm7
        vaddss xmm6, xmm6, xmm7
        vcvtss2sd xmm1, xmm1, xmm1
        vcvtss2sd xmm2, xmm2, xmm2
        vcvtss2sd xmm3, xmm3, xmm3
        vcvtss2sd xmm4, xmm4, xmm4
        vcvtss2sd xmm5, xmm5, xmm5
        vcvtss2sd xmm6, xmm6, xmm6
      }
      Com_Error( /*0x73af17*/
        1,
        (unsigned int)"Entity with %s coordinate of %f is too far outside the playable area of the map.  The playable are"
                      "a goes from ( %f, %f, %f ) to ( %f, %f, %f )\n",
        (_DWORD)v40,
        v30,
        v31,
        v32);
    }
  }
  return *(double *)&_XMM0; /*0x73af09*/
}