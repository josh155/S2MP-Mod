__int64 __fastcall sub_4F04B0(__int64 a1, int a2)
{
  __int64 result; // rax

  if ( (unsigned int)MSG_ReadShort(a1) ) /*0x4f04bf*/
  {
    return (unsigned int)++*(_DWORD *)(a1 + 44); /*0x4f04cb*/
  }
  else if ( a2 != 11 || (unsigned int)MSG_ReadShort(a1) ) /*0x4f04e1*/
  {
    result = MSG_ReadBits(a1, a2); /*0x4f050b*/
    *(_DWORD *)(a1 + 44) = result; /*0x4f0510*/
  }
  else
  {
    *(_DWORD *)(a1 + 44) += MSG_ReadBits(a1, 9); /*0x4f04f5*/
    return *(unsigned int *)(a1 + 44); /*0x4f04f8*/
  }
  return result; /*0x4f04d3*/
}