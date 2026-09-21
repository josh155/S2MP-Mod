__int64 __fastcall MSG_WriteFloatCase(__int64 a1, _DWORD *a2, _DWORD *a3, __m128 _XMM0)
{
  _RBX = a3; /*0x73bd51*/
  _R12 = a2; /*0x73bd54*/
  __asm /*0x73bd5a*/
  {
    vxorps xmm0, xmm0, xmm0
    vmovss xmm1, dword ptr [rbx]
    vucomiss xmm1, xmm0
  }
  __asm { vcvttss2si r14d, dword ptr [r12] }
  __asm { vmovss [rbp+var_2C], xmm1 }
  MSG_WriteBit1(a1); /*0x73bdaf*/
  __asm /*0x73bdb4*/
  {
    vmovss xmm1, [rbp+var_2C]
    vmovd eax, xmm1
  }
  if ( _EAX != 0x80000000 ) /*0x73bdbd*/
  {
    __asm /*0x73bdc8*/
    {
      vcvttss2si r13d, xmm1
      vxorps xmm0, xmm0, xmm0
      vcvtsi2ss xmm0, xmm0, r13d
      vucomiss xmm0, xmm1
    }
  }
  MSG_WriteBit1(a1); /*0x73be75*/
  return MSG_WriteLong(a1, (unsigned int)(*_RBX ^ *a2)); /*0x73bd83*/
}