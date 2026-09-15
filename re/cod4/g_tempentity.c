int __cdecl G_TempEntity(const float *a1, int a2)
{
  int v2; // ebx
  int v3; // eax
  float v4; // xmm2_4
  float v5; // xmm1_4
  float v6; // xmm0_4

  v2 = G_Spawn(); /*0x145980*/
  *(_DWORD *)(v2 + 4) = a2 + 17; /*0x145988*/
  Scr_SetString((unsigned __int16 *)(v2 + 368), (unsigned __int16)word_17656F6); /*0x1459a4*/
  v3 = dword_176FAEC; /*0x1459ae*/
  *(_DWORD *)(v2 + 388) = dword_176FAEC; /*0x1459b4*/
  *(_DWORD *)(v2 + 344) = v3; /*0x1459ba*/
  *(_DWORD *)(v2 + 392) = 1; /*0x1459c0*/
  v4 = (float)(int)*a1; /*0x1459ce*/
  v5 = (float)(int)a1[1]; /*0x1459d7*/
  v6 = (float)(int)a1[2]; /*0x1459e0*/
  *(float *)(v2 + 24) = v4; /*0x1459e4*/
  *(float *)(v2 + 28) = v5; /*0x1459e9*/
  *(float *)(v2 + 32) = v6; /*0x1459ee*/
  *(_DWORD *)(v2 + 12) = 0; /*0x1459f3*/
  *(_DWORD *)(v2 + 16) = 0; /*0x1459fa*/
  *(_DWORD *)(v2 + 20) = 0; /*0x145a01*/
  *(_DWORD *)(v2 + 36) = 0; /*0x145a0a*/
  *(_DWORD *)(v2 + 40) = 0; /*0x145a0d*/
  *(_DWORD *)(v2 + 44) = 0; /*0x145a10*/
  *(float *)(v2 + 316) = v4; /*0x145a13*/
  *(float *)(v2 + 320) = v5; /*0x145a1b*/
  *(float *)(v2 + 324) = v6; /*0x145a23*/
  SV_LinkEntity(v2); /*0x145a2e*/
  return v2; /*0x145a35*/
}