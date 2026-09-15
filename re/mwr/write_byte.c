__int64 __fastcall MSG_WriteByte(__int64 a1, char a2, __int64 a3, __int64 a4, __int64 a5, int a6)
{
  __int64 result; // rax

  if ( *(_DWORD *)(a1 + 4) ) /*0x7210bd*/
    MyAssertHandler( /*0x7210e1*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg.cpp",
      405,
      0,
      (unsigned int)"%s",
      (unsigned int)"!msg->readOnly",
      a6);
  result = *(int *)(a1 + 28); /*0x7210e6*/
  if ( (int)result >= *(_DWORD *)(a1 + 24) ) /*0x7210ed*/
  {
    *(_DWORD *)a1 = 1; /*0x7210fc*/
  }
  else
  {
    *(_BYTE *)(*(_QWORD *)(a1 + 8) + result) = a2; /*0x7210f3*/
    ++*(_DWORD *)(a1 + 28); /*0x7210f7*/
  }
  return result; /*0x721102*/
}