int __cdecl MSG_ReadDeltaClient(int a1, int a2, int a3, void *a4, int a5)
{
  _BYTE v6[100]; // [esp+28h] [ebp-80h] BYREF

  if ( !a3 ) /*0x17cc50*/
    memset(v6, 0, sizeof(v6)); /*0x17ccb6*/
  return MSG_ReadDeltaStruct(a4, a5, numClientStateFields, 6, (int)&clientStateFields, numClientStateFields); /*0x17cc95*/
}