__int64 __fastcall MSG_WriteDeltaTime(__int64 a1, int a2, int a3, __int64 a4, __int64 a5, int a6)
{
  __int64 v7; // rcx
  __int64 v8; // r8
  int v9; // r9d
  __int64 v11; // rdx
  __int64 v12; // rcx
  __int64 v13; // r8
  int v14; // r9d

  if ( *(_DWORD *)(a1 + 4) ) /*0x7442f4*/
    MyAssertHandler( /*0x74431a*/
      (unsigned int)"D:\\h1\\code_source\\Runtime\\qcommon\\sv_msg_write_mp.cpp",
      821,
      0,
      (unsigned int)"%s",
      (unsigned int)"!msg->readOnly",
      a6);
  if ( (unsigned int)(a3 - a2) >= 0xFFFFFF01 || a3 - a2 == 0 ) /*0x74432e*/
  {
    MSG_WriteBit0(a1); /*0x744335*/
    return MSG_WriteBits(a1, a2 - a3, 8, v7, v8, v9); /*0x74434e*/
  }
  else
  {
    MSG_WriteBit1(a1); /*0x744353*/
    return MSG_WriteLong(a1, a3, v11, v12, v13, v14); /*0x744366*/
  }
}