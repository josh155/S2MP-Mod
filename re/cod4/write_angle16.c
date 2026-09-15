int __cdecl MSG_WriteAngle16(_DWORD *a1, float a2)
{
  int v2; // esi
  int result; // eax

  v2 = a1[5]; /*0x176f45*/
  if ( v2 + 2 > a1[4] ) /*0x176f4e*/
  {
    *a1 = 1; /*0x176f80*/
  }
  else
  {
    result = (int)(float)((float)(a2 * 182.04445) + 0.5); /*0x176f63*/
    *(_WORD *)(a1[2] + v2) = result; /*0x176f67*/
    a1[5] = v2 + 2; /*0x176f6b*/
  }
  return result; /*0x176f75*/
}