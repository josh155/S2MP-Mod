__int64 __fastcall MSG_WriteMovingPlatformValidOrigin(
        __int64 a1,
        int *a2,
        int a3,
        __int64 a4,
        _DWORD *a5,
        double a6,
        __m128 _XMM1,
        double a8)
{
  __int64 v11; // r12
  int v16; // r9d
  __int64 result; // rax
  _DWORD *v18; // rdx
  int v19; // [rsp+Ch] [rbp-34h] BYREF
  __int64 v20; // [rsp+10h] [rbp-30h]

  _R14 = a5; /*0x73bc8b*/
  _R13 = a4; /*0x73bc8e*/
  v11 = (__int64)a2; /*0x73bc94*/
  v20 = *(_QWORD *)COMMON; /*0x73bc9a*/
  if ( *(_BYTE *)(a1 + 118) ) /*0x73bc9e*/
  {
    MSG_WriteBit1(a2); /*0x73bca7*/
    __asm { vmovss xmm0, dword ptr [r13+0] } /*0x73bcac*/
    a2 = &v19; /*0x73bcb2*/
    a1 = v11; /*0x73bcb6*/
    __asm /*0x73bcbc*/
    {
      vaddss xmm0, xmm0, cs:dword_FA0C08
      vroundss xmm0, xmm0, xmm0, 1
      vcvttss2si eax, xmm0
    }
    v19 = _EAX; /*0x73bcce*/
    MSG_WriteFloatCase(v11, &v19, _R14, _XMM0); /*0x73bcd1*/
  }
  else
  {
    MSG_WriteBit0(a2); /*0x73bcdb*/
    __asm /*0x73bce0*/
    {
      vmovss xmm0, dword ptr [r14]
      vmovss xmm1, dword ptr [r13+0]
    }
    if ( a3 == -104 ) /*0x73bcf6*/
    {
      a2 = (int *)(a1 + 4); /*0x73bcf8*/
      MSG_WriteOriginZFloat(a1, a1 + 4, v11, *(double *)_XMM0.m128_u64, *(double *)_XMM1.m128_u64); /*0x73bcfe*/
    }
    else
    {
      *(double *)_XMM0.m128_u64 = MSG_WriteOriginFloat(a1, _XMM0, _XMM1, (__int64)a2, a1 + 4, (__int64)a2, a3, v16); /*0x73bd0b*/
    }
  }
  result = *(_QWORD *)COMMON; /*0x73bd17*/
  if ( *(_QWORD *)COMMON != v20 ) /*0x73bd1e*/
  {
    PL__stack_chk_fail(*(double *)_XMM0.m128_u64, *(double *)_XMM1.m128_u64, a8); /*0x73bd2f*/
    return MSG_WriteFloatCase(a1, a2, v18, _XMM0); /*0x73bd36*/
  }
  return result; /*0x73bd20*/
}