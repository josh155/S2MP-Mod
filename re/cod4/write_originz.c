int __cdecl MSG_WriteOriginZFloat(int a1, int a2, float a3, float a4)
{
  float v6; // [esp+10h] [ebp-28h]
  float v7; // [esp+14h] [ebp-24h]
  int v8; // [esp+44h] [ebp+Ch]
  int v9; // [esp+48h] [ebp+10h]

  v7 = floorf(a3 + 0.5); /*0x171c93*/
  v6 = floorf(a4 + 0.5); /*0x171cb5*/
  if ( (unsigned int)((int)v7 - (int)v6 + 64) > 0x7F ) /*0x171cc8*/
  {
    MSG_WriteBit1(a2); /*0x171cf3*/
    v9 = 16; /*0x171d19*/
    v8 = ((int)v7 + 0x8000 - (int)(float)(*(float *)&dword_CD2DD30 + 0.5)) /*0x171d2a*/
       ^ ((int)v6 + 0x8000 - (int)(float)(*(float *)&dword_CD2DD30 + 0.5));
  }
  else
  {
    MSG_WriteBit0(a2); /*0x171ccd*/
    v9 = 7; /*0x171cd2*/
    v8 = (int)v7 - (int)v6 + 64; /*0x171cd9*/
  }
  return MSG_WriteBits(a2, v8, v9); /*0x171ce8*/
}