__int64 __fastcall MSG_ReadFloatCase(__int64 a1, _DWORD *a2, _QWORD *a3, int a4, __m128 _XMM0, __m128 _XMM1)
{
  int Bit; // r15d
  __int64 v9; // rdx
  int v10; // r9d
  int v11; // r13d
  int v12; // ecx
  int v13; // r8d
  int v14; // r9d
  int v20; // eax
  int v21; // r15d
  int v22; // r8d
  int v23; // r9d
  int v25; // eax
  int v26; // ecx

  _R12 = a2; /*0x72a4e4*/
  Bit = MSG_ReadBit(a1); /*0x72a4f2*/
  v11 = MSG_ReadBit(a1); /*0x72a4fa*/
  if ( Bit ) /*0x72a500*/
  {
    if ( v11 ) /*0x72a505*/
    {
      _R13D = *a2 ^ MSG_ReadLong(a1, a2, v9); /*0x72a516*/
      if ( a3 && a4 ) /*0x72a527*/
      {
        __asm { vmovd xmm0, r13d } /*0x72a530*/
        __asm { vcvtss2sd xmm0, xmm0, xmm0 }
        Com_Printf(25, (unsigned int)"%s:%f ", *a3, v12, v13, v14); /*0x72a547*/
      }
    }
    else
    {
      MSG_ReadBits(a1, 5); /*0x72a597*/
      v21 = v20; /*0x72a59f*/
      *(double *)_XMM0.m128_u64 = MSG_ReadByte(a1); /*0x72a5a2*/
      __asm { vcvttss2si ecx, dword ptr [r12] } /*0x72a5a7*/
      v26 = ((v21 + 32 * v25) ^ (_ECX + 4096)) - 4096; /*0x72a5bb*/
      __asm /*0x72a5c4*/
      {
        vcvtsi2ss xmm0, xmm0, ecx
        vmovd r13d, xmm0
      }
      if ( a3 && a4 ) /*0x72a5d3*/
        Com_Printf(25, (unsigned int)"%s:%i ", *a3, v26, v22, v23); /*0x72a5e6*/
    }
  }
  else
  {
    _R13D = v11 << 31; /*0x72a551*/
    __asm /*0x72a555*/
    {
      vxorps xmm1, xmm1, xmm1
      vmovd xmm0, r13d
      vucomiss xmm0, xmm1
    }
    if ( _R13D || __SETP__(_R13D, 0) ) /*0x72a551*/
      MyAssertHandler( /*0x72a588*/
        (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg_mp.cpp",
        1260,
        0,
        (unsigned int)"%s",
        (unsigned int)"*reinterpret_cast< float * >( toF ) == 0.0f",
        v10);
  }
  return _R13D; /*0x72a5f2*/
}