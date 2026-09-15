__int128 __usercall MSG_ReadAngle16@<xmm0>(__int64 a1@<rdi>, __m128 _XMM0@<xmm0>)
{
  __int128 result; // xmm0

  *(double *)_XMM0.m128_u64 = MSG_ReadShort(a1); /*0x7223f4*/
  __asm /*0x7223f9*/
  {
    vcvtsi2ss xmm0, xmm0, eax
    vmulss xmm0, xmm0, cs:dword_F9B194
  }
  return result; /*0x722405*/
}