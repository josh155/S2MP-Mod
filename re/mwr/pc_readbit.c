__int64 __fastcall sub_4EB1D0(__int64 a1, __int64 a2, int a3)
{
  __int64 result; // rax

  result = 0; /*0x4eb1d0*/
  *(_QWORD *)a1 = 0; /*0x4eb1d2*/
  *(_QWORD *)(a1 + 24) = 0; /*0x4eb1d5*/
  *(_QWORD *)(a1 + 32) = 0; /*0x4eb1d9*/
  *(_QWORD *)(a1 + 40) = 0; /*0x4eb1dd*/
  *(_QWORD *)(a1 + 48) = 0; /*0x4eb1e1*/
  *(_QWORD *)(a1 + 8) = a2; /*0x4eb1e5*/
  *(_DWORD *)(a1 + 24) = a3; /*0x4eb1e9*/
  *(_DWORD *)(a1 + 4) = 0; /*0x4eb1ed*/
  *(_QWORD *)(a1 + 16) = 0; /*0x4eb1f0*/
  *(_DWORD *)(a1 + 32) = 0; /*0x4eb1f4*/
  return result; /*0x4eb1f7*/
}