__int64 __fastcall MSG_WriteAngle16(__int64 a1, __m128 _XMM0, __int64 a3, __int64 a4, __int64 a5, __int64 a6, int a7)
{
  bool v7; // al
  __int64 result; // rax

  v7 = 1; /*0x721819*/
  __asm { vmovss [rbp+var_C], xmm0 } /*0x72181b*/
  if ( *(_DWORD *)(a1 + 4) ) /*0x721820*/
  {
    MyAssertHandler( /*0x721844*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg.cpp",
      653,
      0,
      (unsigned int)"%s",
      (unsigned int)"!sb->readOnly",
      a7);
    v7 = *(_DWORD *)(a1 + 4) == 0; /*0x72184d*/
  }
  if ( !v7 ) /*0x721852*/
    MyAssertHandler( /*0x721872*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg.cpp",
      450,
      0,
      (unsigned int)"%s",
      (unsigned int)"!msg->readOnly",
      a7);
  result = *(int *)(a1 + 28); /*0x721877*/
  if ( (int)result + 2 <= *(_DWORD *)(a1 + 24) ) /*0x721881*/
  {
    __asm { vmovss xmm0, [rbp+var_C] } /*0x72188b*/
    __asm
    {
      vmulss xmm0, xmm0, cs:dword_F9B180
      vaddss xmm0, xmm0, cs:dword_F9B184
      vroundss xmm0, xmm0, xmm0, 1
      vcvttss2si edx, xmm0
    }
    *(_WORD *)(*(_QWORD *)(a1 + 8) + result) = _EDX; /*0x7218ae*/
    *(_DWORD *)(a1 + 28) = result + 2; /*0x7218b2*/
  }
  else
  {
    *(_DWORD *)a1 = 1; /*0x721883*/
  }
  return result; /*0x7218b9*/
}