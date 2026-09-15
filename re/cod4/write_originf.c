int __cdecl MSG_WriteOriginFloat(int a1, int a2, int a3, float a4, float a5)
{
  float v7; // xmm0_4
  float v8; // [esp+1Ch] [ebp-2Ch]
  float v9; // [esp+20h] [ebp-28h]
  int v10; // [esp+54h] [ebp+Ch]
  int v11; // [esp+58h] [ebp+10h]

  v9 = floorf(a4 + 0.5); /*0x171d69*/
  v8 = floorf(a5 + 0.5); /*0x171d8b*/
  if ( (unsigned int)((int)v9 - (int)v8 + 64) > 0x7F ) /*0x171d9e*/
  {
    MSG_WriteBit1(a2); /*0x171dd3*/
    v7 = *(float *)&svsHeader[(a3 != -92) + 10] + 0.5; /*0x171def*/
    v11 = 16; /*0x171e04*/
    v10 = ((int)v9 + 0x8000 - (int)v7) ^ ((int)v8 + 0x8000 - (int)v7); /*0x171e15*/
  }
  else
  {
    MSG_WriteBit0(a2); /*0x171da3*/
    v11 = 7; /*0x171da8*/
    v10 = (int)v9 - (int)v8 + 64; /*0x171daf*/
  }
  return MSG_WriteBits(a2, v10, v11); /*0x171dbe*/
}