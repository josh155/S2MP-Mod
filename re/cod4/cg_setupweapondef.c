int __cdecl CG_SetupWeaponDef(int a1)
{
  const char *ConfigString; // eax
  char v2; // al
  char *v3; // edx
  int v4; // edi
  int v5; // ebx
  const char *v6; // esi
  char *v8[127]; // [esp+10h] [ebp-2218h] BYREF
  char v9; // [esp+20Ch] [ebp-201Ch] BYREF
  char v10; // [esp+20Dh] [ebp-201Bh] BYREF
  int v11; // [esp+220Ch] [ebp-1Ch]

  memset(v8, 0, sizeof(v8)); /*0x76751*/
  ConfigString = (const char *)CL_GetConfigString(a1, 2258); /*0x76764*/
  strcpy(&v9, ConfigString); /*0x76776*/
  v8[0] = &v9; /*0x7677b*/
  v2 = v9; /*0x76781*/
  v3 = &v10; /*0x76788*/
  v4 = 1; /*0x7678e*/
  if ( v9 ) /*0x76795*/
  {
    while ( v2 == 32 ) /*0x767a2*/
    {
      *(v3 - 1) = 0; /*0x76810*/
      v2 = *v3; /*0x76814*/
      if ( !*v3 || v2 == 32 ) /*0x7681d*/
        goto LABEL_4; /*0x7681d*/
      if ( v4 > 126 ) /*0x76822*/
        goto LABEL_7; /*0x76822*/
      v8[v4++] = v3++; /*0x76824*/
LABEL_5:
      if ( !v2 ) /*0x767aa*/
        goto LABEL_6; /*0x767aa*/
    }
    v2 = *v3; /*0x767a4*/
LABEL_4:
    ++v3; /*0x767a7*/
    goto LABEL_5; /*0x767a7*/
  }
LABEL_6:
  if ( v4 > 0 ) /*0x767ae*/
  {
LABEL_7:
    v5 = 0; /*0x767b0*/
    do /*0x767f6*/
    {
      v6 = v8[v5++]; /*0x767c0*/
      if ( BG_GetWeaponIndexForName(v6, 0) != v5 ) /*0x767da*/
        Com_Error(2, "Weapon index mismatch for '%s'", (char)v6); /*0x767ef*/
    }
    while ( v4 != v5 ); /*0x767f6*/
  }
  return __stack_chk_guard ^ v11; /*0x76805*/
}