__int64 __fastcall MSG_WriteShort(__int64 a1, __int16 a2, __int64 a3, __int64 a4, __int64 a5, int a6)
{
  __int64 result; // rax

  if ( *(_DWORD *)(a1 + 4) ) /*0x72118d*/
    MyAssertHandler( /*0x7211b1*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\msg.cpp",
      450,
      0,
      (unsigned int)"%s",
      (unsigned int)"!msg->readOnly",
      a6);
  result = *(int *)(a1 + 28); /*0x7211b6*/
  if ( (int)result + 2 <= *(_DWORD *)(a1 + 24) ) /*0x7211c0*/
  {
    *(_WORD *)(*(_QWORD *)(a1 + 8) + result) = a2; /*0x7211ce*/
    *(_DWORD *)(a1 + 28) = result + 2; /*0x7211d3*/
  }
  else
  {
    *(_DWORD *)a1 = 1; /*0x7211c2*/
  }
  return result; /*0x7211d6*/
}