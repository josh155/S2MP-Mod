int __fastcall sub_4F72E0(__int64 a1, __int64 a2, __int16 *a3, __int16 *a4, int a5, int a6)
{
  int v6; // ebx
  int v8; // edx
  int v9; // ebx
  int result; // eax
  unsigned int v11; // edi
  int v12; // ebp

  v6 = 0; /*0x4f7304*/
  switch ( a5 ) /*0x4f731d*/
  {
    case -4: /*0x4f731d*/
    case 4: /*0x4f731d*/
      v8 = *(_DWORD *)a3; /*0x4f731f*/
      break; /*0x4f7322*/
    case -2: /*0x4f731d*/
      v8 = *a3; /*0x4f732a*/
      break; /*0x4f732e*/
    case -1: /*0x4f731d*/
      v8 = *(char *)a3; /*0x4f7336*/
      break; /*0x4f7336*/
    case 1: /*0x4f731d*/
      v8 = *(unsigned __int8 *)a3; /*0x4f7330*/
      break; /*0x4f7334*/
    case 2: /*0x4f731d*/
      v8 = (unsigned __int16)*a3; /*0x4f7324*/
      break; /*0x4f7328*/
    default:
      v8 = 0; /*0x4f733c*/
      break; /*0xf1c0000000000004*/
  }
  switch ( a5 ) /*0x4f7352*/
  {
    case -4: /*0x4f7352*/
    case 4: /*0x4f7352*/
      v6 = *(_DWORD *)a4; /*0x4f7354*/
      break; /*0x4f7357*/
    case -2: /*0x4f7352*/
      v6 = *a4; /*0x4f735f*/
      break; /*0x4f7363*/
    case -1: /*0x4f7352*/
      v6 = *(char *)a4; /*0x4f736b*/
      break; /*0x4f736b*/
    case 1: /*0x4f7352*/
      v6 = *(unsigned __int8 *)a4; /*0x4f7365*/
      break; /*0x4f7369*/
    case 2: /*0x4f7352*/
      v6 = (unsigned __int16)*a4; /*0x4f7359*/
      break; /*0x4f735d*/
    default:
      break;
  }
  v9 = v8 ^ v6; /*0x4f736f*/
  if ( a6 != 32 ) /*0x4f7378*/
    v9 &= (1 << a6) - 1; /*0x4f7383*/
  result = a6; /*0x4f7387*/
  v11 = abs32(a6); /*0x4f738c*/
  v12 = v11 & 7; /*0x4f7390*/
  if ( (v11 & 7) != 0 ) /*0x4f7393*/
  {
    result = MSG_WriteBits(a2, v9, v11 & 7); /*0x4f739d*/
    v11 -= v12; /*0x4f73a4*/
    v9 >>= v12; /*0x4f73a6*/
  }
  for ( ; v11; v11 -= 8 ) /*0x4f73aa*/
  {
    result = sub_4EBF30(a2, v9); /*0x4f73b5*/
    v9 >>= 8; /*0x4f73ba*/
  }
  return result; /*0x4f73d1*/
}