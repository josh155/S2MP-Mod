__int64 __fastcall sub_342240(__int64 a1, __int64 a2, __int64 a3, __int64 a4)
{
  __int64 v7; // rbx
  int v8; // eax
  __int64 result; // rax

  if ( !a3 || (*(_BYTE *)(a3 + 19000) & 8) != 0 ) /*0x34226d*/
    v7 = sub_5A4480(); /*0x34229e*/
  else
    v7 = *(_QWORD *)(a1 + 36792) + 8LL * *(_DWORD *)(a3 + 19040) % *(_DWORD *)(a1 + 36756) * (unsigned int)sub_5A47B0(); /*0x342290*/
  *(_DWORD *)(a4 + 19040) = *(_DWORD *)(a1 + 19184); /*0x3422a7*/
  v8 = sub_5A47B0(); /*0x3422ad*/
  result = sub_4EE310( /*0x3422db*/
             a2,
             *(unsigned int *)(a4 + 19004),
             v7,
             *(_QWORD *)(a1 + 36792) + 8LL * (unsigned int)(*(_DWORD *)(a1 + 19184) % *(_DWORD *)(a1 + 36756) * v8));
  ++*(_DWORD *)(a1 + 19184); /*0x3422e0*/
  return result; /*0x3422e6*/
}