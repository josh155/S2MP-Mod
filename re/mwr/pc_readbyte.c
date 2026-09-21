__int64 __fastcall sub_4EB510()
{
  __int64 v0; // rax
  __int64 v1; // rbp
  __int64 result; // rax
  unsigned __int64 v3; // kr00_8
  __int64 v4[2]; // [rsp+0h] [rbp-28h] BYREF
  _QWORD v5[3]; // [rsp+10h] [rbp-18h] BYREF

  v5[2] = v0; /*0x118b1c6f*/
  v3 = __readeflags(); /*0x118b1c70*/
  v5[1] = v3; /*0x118b1c70*/
  v5[0] = 16; /*0x118b1c71*/
  if ( ((unsigned __int64)v5 & 0xF) == 0 ) /*0x118b1c7a*/
    v4[1] = 24; /*0x5fad9*/
  result = 0; /*0x1175fa08*/
  v4[0] = v1; /*0x1175fa0e*/
  _InterlockedExchange64(v4, (__int64)sub_201D92); /*0x118eda27*/
  v4[0] = (__int64)&loc_11AD937D; /*0x11ae07bc*/
  return result; /*0x11ab0e42*/
}