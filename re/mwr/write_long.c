__int64 __fastcall MSG_WriteLong(__int64 a1, int a2, __int64 a3, __int64 a4, __int64 a5, int a6)
{
  __int64 result; // rax

  if ( *(_DWORD *)(a1 + 4) ) /*0x720f0d*/
    MyAssertHandler( /*0x720f31*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg.cpp",
      477,
      0,
      (unsigned int)"%s",
      (unsigned int)"!msg->readOnly",
      a6);
  result = *(int *)(a1 + 28); /*0x720f36*/
  if ( (int)result + 4 <= *(_DWORD *)(a1 + 24) ) /*0x720f40*/
  {
    *(_DWORD *)(*(_QWORD *)(a1 + 8) + result) = a2; /*0x720f4e*/
    *(_DWORD *)(a1 + 28) = result + 4; /*0x720f52*/
  }
  else
  {
    *(_DWORD *)a1 = 1; /*0x720f42*/
  }
  return result; /*0x720f55*/
}