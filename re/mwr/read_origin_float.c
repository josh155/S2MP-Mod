__int128 __usercall MSG_ReadOriginFloat@<xmm0>(int a1@<edi>, __int64 a2@<rsi>, __m128 _XMM0@<xmm0>)
{
  int v3; // r9d
  int v5; // edx
  int v6; // ecx
  __int128 result; // xmm0

  __asm { vmovss [rbp+var_14], xmm0 } /*0x72a610*/
  if ( (unsigned int)MSG_ReadBit(a2) ) /*0x72a618*/
  {
    _RAX = 0; /*0x72a625*/
    if ( (unsigned int)(a1 + 106) > 0x17 || (v5 = 8404993, !_bittest(&v5, a1 + 106)) ) /*0x72a637*/
    {
      _RAX = 1; /*0x72a63c*/
      if ( (unsigned int)(a1 + 105) > 0x17 || (v6 = 8404993, !_bittest(&v6, a1 + 105)) ) /*0x72a64e*/
      {
        MyAssertHandler( /*0x72a66e*/
          (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
          851,
          0,
          (unsigned int)"%s",
          (unsigned int)"(bits == MSG_FIELD_ORIGINY) || (bits == MSG_FIELD_ES_ORIGINY) || (bits == MSG_FIELD_MOVING_PLATFORM_ORIGINY)",
          v3);
        _RAX = 1; /*0x72a673*/
      }
    }
    _RCX = &unk_337EE80; /*0x72a678*/
    __asm /*0x72a687*/
    {
      vmovss xmm0, dword ptr [rcx+rax*4+150h]
      vroundss xmm0, xmm0, xmm0, 1
      vcvttss2si ebx, xmm0
    }
    *(double *)&_XMM0 = MSG_ReadBits(a2, 16); /*0x72a69a*/
    __asm /*0x72a69f*/
    {
      vxorps xmm0, xmm0, xmm0
      vroundss xmm0, xmm0, [rbp+var_14], 1
    }
    __asm { vcvttss2si ecx, xmm0 }
    __asm
    {
      vxorps xmm0, xmm0, xmm0
      vcvtsi2ss xmm0, xmm0, eax
    }
  }
  else
  {
    *(double *)_XMM0.m128_u64 = MSG_ReadBits(a2, 7); /*0x72a6c9*/
    __asm { vroundss xmm0, xmm0, [rbp+var_14], 1 } /*0x72a6ce*/
    __asm
    {
      vcvttss2si ecx, xmm0
      vxorps xmm0, xmm0, xmm0
      vcvtsi2ss xmm0, xmm0, eax
      vcvtsi2ss xmm1, xmm0, ecx
      vaddss xmm0, xmm0, xmm1
    }
  }
  return result; /*0x72a6ec*/
}