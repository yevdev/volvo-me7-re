// Pseudo-C of key Volvo ME7.0 (50GPHJ) control functions
// Ghidra + keyhana C166 module. C166 has no Hex-Rays decompiler;
// this is Ghidra's SLEIGH-based pseudo-C, best read alongside the IDA disassembly dumps.

// ================= me7_lookup_1d_word @ 041a68 =================

/* 1-D word table interp (offset r12; page r13; input r14 -> r4) */

ushort me7_lookup_1d_word(ushort param_1,ushort param_2,ushort param_3)

{
  ushort uVar1;
  uint uVar2;
  ushort *puVar3;
  ushort *puVar4;
  ushort *puVar5;
  ushort uVar6;
  ushort uVar7;
  ushort uVar8;
  ushort *puVar9;
  ushort uVar10;
  
  puVar9 = (ushort *)(param_1 + 2);
  uVar1 = *(ushort *)((uint3)param_1 + (uint3)param_2 * 0x4000);
  uVar6 = 0;
  uVar8 = 0;
  uVar10 = 0;
  if (param_3 != *puVar9 && *puVar9 <= param_3) {
    puVar5 = puVar9 + (uVar1 & 0xff) + -1;
    puVar3 = puVar9 + (uVar1 & 0xff);
    if (param_3 < *puVar5) {
      do {
        puVar4 = puVar3;
        puVar5 = puVar4 + -1;
        puVar3 = puVar5;
      } while (param_3 < *puVar5);
      uVar6 = param_3 - *puVar5;
      uVar8 = *(short *)(ZEXT23(puVar4) + (uint3)param_2 * 0x4000) - *puVar5;
    }
    uVar10 = (ushort)((short)puVar5 - (short)puVar9) >> 1;
  }
  uVar7 = *(ushort *)(ZEXT23(puVar9 + uVar1 + uVar10) + (uint3)param_2 * 0x4000);
  if (uVar6 != 0) {
    uVar1 = *(ushort *)(ZEXT23(puVar9 + uVar1 + uVar10 + 1) + (uint3)param_2 * 0x4000);
    if (uVar1 < uVar7) {
      uVar2 = (uint)(uVar7 - uVar1) * (uint)uVar6;
      MDL = (short)(uVar2 / uVar8);
      MDH = (undefined2)(uVar2 % (uint)uVar8);
      MDC = MDC | 0x10;
      uVar7 = uVar7 - MDL;
    }
    else {
      uVar2 = (uint)(uVar1 - uVar7) * (uint)uVar6;
      MDL = (short)(uVar2 / uVar8);
      MDH = (undefined2)(uVar2 % (uint)uVar8);
      MDC = MDC | 0x10;
      uVar7 = uVar7 + MDL;
    }
  }
  return uVar7;
}


// ================= me7_lookup_1d_word_signed @ 041b5a =================

/* 1-D word table interp, signed axis */

short me7_lookup_1d_word_signed(ushort param_1,ushort param_2,short param_3)

{
  short *psVar1;
  short sVar2;
  ushort uVar3;
  uint uVar4;
  short *psVar5;
  ushort uVar6;
  short sVar7;
  ushort uVar8;
  short *psVar9;
  ushort uVar10;
  
  psVar9 = (short *)(param_1 + 2);
  uVar3 = *(ushort *)((uint3)param_1 + (uint3)param_2 * 0x4000);
  uVar6 = 0;
  uVar8 = 0;
  uVar10 = 0;
  psVar1 = psVar9;
  if (param_3 != *psVar1 &&
      param_3 - *psVar1 < 0 == (param_3 < 0 != *psVar1 < 0 && param_3 - *psVar1 < 0 != param_3 < 0))
  {
    psVar5 = psVar9 + ((uVar3 & 0xff) - 1);
    psVar1 = psVar5;
    if (param_3 - *psVar1 < 0 !=
        (param_3 < 0 != *psVar1 < 0 && param_3 - *psVar1 < 0 != param_3 < 0)) {
      while (psVar1 = psVar5,
            param_3 - *psVar1 < 0 !=
            (param_3 < 0 != *psVar1 < 0 && param_3 - *psVar1 < 0 != param_3 < 0)) {
        psVar5 = psVar5 + -1;
      }
      uVar6 = param_3 - *psVar5;
      uVar8 = *(short *)(ZEXT23(psVar5 + 1) + (uint3)param_2 * 0x4000) - *psVar5;
    }
    uVar10 = (ushort)((short)psVar5 - (short)psVar9) >> 1;
  }
  sVar7 = *(short *)(ZEXT23(psVar9 + uVar3 + uVar10) + (uint3)param_2 * 0x4000);
  if (uVar6 != 0) {
    sVar2 = *(short *)(ZEXT23(psVar9 + uVar3 + uVar10 + 1) + (uint3)param_2 * 0x4000);
    if (sVar7 == sVar2 ||
        sVar7 - sVar2 < 0 != (sVar7 < 0 != sVar2 < 0 && sVar7 - sVar2 < 0 != sVar7 < 0)) {
      uVar4 = (uint)(ushort)(sVar2 - sVar7) * (uint)uVar6;
      MDL = (short)(uVar4 / uVar8);
      MDH = (undefined2)(uVar4 % (uint)uVar8);
      MDC = MDC | 0x10;
      sVar7 = sVar7 + MDL;
    }
    else {
      uVar4 = (uint)(ushort)(sVar7 - sVar2) * (uint)uVar6;
      MDL = (short)(uVar4 / uVar8);
      MDH = (undefined2)(uVar4 % (uint)uVar8);
      MDC = MDC | 0x10;
      sVar7 = sVar7 - MDL;
    }
  }
  return sVar7;
}


// ================= me7_lookup_1d_byte @ 0419f4 =================

/* 1-D byte table interp (r13=page) */

ushort me7_lookup_1d_byte(ushort param_1,ushort param_2,byte param_3)

{
  ushort uVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  ushort uVar5;
  ushort uVar6;
  ushort uVar7;
  byte *pbVar8;
  short sVar9;
  
  pbVar8 = (byte *)(param_1 + 1);
  uVar1 = (ushort)*(byte *)((uint3)param_1 + (uint3)param_2 * 0x4000);
  uVar5 = 0;
  uVar7 = 0;
  sVar9 = 0;
  if (param_3 != *pbVar8 && *pbVar8 <= param_3) {
    pbVar4 = pbVar8 + uVar1 + -1;
    pbVar2 = pbVar8 + uVar1;
    if (param_3 < *pbVar4) {
      do {
        pbVar3 = pbVar2;
        pbVar4 = pbVar3 + -1;
        pbVar2 = pbVar4;
      } while (param_3 < *pbVar4);
      uVar5 = (ushort)(byte)(param_3 - *pbVar4);
      uVar7 = (ushort)(byte)(*(char *)(ZEXT23(pbVar3) + (uint3)param_2 * 0x4000) - *pbVar4);
    }
    sVar9 = (short)pbVar4 - (short)pbVar8;
  }
  uVar6 = (ushort)*(byte *)(ZEXT23(pbVar8 + sVar9 + uVar1) + (uint3)param_2 * 0x4000);
  if (uVar5 != 0) {
    uVar1 = (ushort)*(byte *)(ZEXT23(pbVar8 + sVar9 + uVar1 + 1) + (uint3)param_2 * 0x4000);
    if (uVar6 <= uVar1) {
      MDH = (uVar1 - uVar6) * uVar5;
      MDL = MDH / uVar7;
      MDH = MDH % uVar7;
      MDC = MDC | 0x10;
      return uVar6 + MDL;
    }
    MDH = (uVar6 - uVar1) * uVar5;
    MDL = MDH / uVar7;
    MDH = MDH % uVar7;
    MDC = MDC | 0x10;
    uVar6 = uVar6 - MDL;
  }
  return uVar6;
}


// ================= me7_lookup_2d_word_bilinear @ 041cc0 =================

/* 2-D bilinear word map */

ushort me7_lookup_2d_word_bilinear(ushort param_1,ushort param_2,ushort param_3,ushort param_4)

{
  ushort *puVar1;
  ushort uVar2;
  ushort uVar3;
  short sVar4;
  int iVar5;
  uint uVar6;
  ushort *puVar7;
  ushort uVar8;
  ushort *puVar9;
  ushort *puVar10;
  ushort uVar11;
  ushort uVar12;
  ushort uVar13;
  ushort uVar14;
  ushort uVar15;
  
  uVar12 = *(ushort *)((uint3)param_1 + (uint3)param_2 * 0x4000) & 0xff;
  puVar1 = (ushort *)(param_1 + 4);
  uVar11 = 0;
  uVar13 = 0;
  uVar8 = 0;
  if (param_3 != *puVar1 && *puVar1 <= param_3) {
    puVar10 = puVar1 + uVar12 + -1;
    puVar7 = puVar1 + uVar12;
    if (param_3 < *puVar10) {
      do {
        puVar9 = puVar7;
        puVar10 = puVar9 + -1;
        puVar7 = puVar10;
      } while (param_3 < *puVar10);
      uVar11 = param_3 - *puVar10;
      uVar13 = *(short *)(ZEXT23(puVar9) + (uint3)param_2 * 0x4000) - *puVar10;
    }
    uVar8 = (ushort)((short)puVar10 - (short)puVar1) >> 1;
  }
  uVar2 = *(ushort *)((uint3)(param_1 + 2) + (uint3)param_2 * 0x4000) & 0xff;
  uVar3 = uVar2 * 2;
  puVar1 = puVar1 + uVar12;
  uVar12 = 0;
  uVar14 = 0;
  uVar15 = 0;
  if (param_4 != *puVar1 && *puVar1 <= param_4) {
    puVar10 = puVar1 + uVar2 + -1;
    puVar7 = puVar1 + uVar2;
    if (param_4 < *puVar10) {
      do {
        puVar9 = puVar7;
        puVar10 = puVar9 + -1;
        puVar7 = puVar10;
      } while (param_4 < *puVar10);
      uVar12 = param_4 - *puVar10;
      uVar14 = *(short *)(ZEXT23(puVar9) + (uint3)param_2 * 0x4000) - *puVar10;
    }
    uVar15 = (ushort)((short)puVar10 - (short)puVar1) >> 1;
  }
  iVar5 = (uint)uVar8 * (uint)uVar3;
  uVar2 = (short)puVar1 + uVar15 * 2 + (short)iVar5 + uVar3;
  uVar8 = *(ushort *)((uint3)uVar2 + (uint3)param_2 * 0x4000);
  if (uVar12 != 0) {
    uVar15 = *(ushort *)((uint3)(uVar2 + 2) + (uint3)param_2 * 0x4000);
    if (uVar15 < uVar8) {
      uVar6 = (uint)(uVar8 - uVar15) * (uint)uVar12;
      sVar4 = (short)(uVar6 / uVar14);
      iVar5 = CONCAT22((short)(uVar6 % (uint)uVar14),sVar4);
      uVar8 = uVar8 - sVar4;
    }
    else {
      uVar6 = (uint)(uVar15 - uVar8) * (uint)uVar12;
      sVar4 = (short)(uVar6 / uVar14);
      iVar5 = CONCAT22((short)(uVar6 % (uint)uVar14),sVar4);
      uVar8 = uVar8 + sVar4;
    }
  }
  if (uVar11 != 0) {
    uVar15 = *(ushort *)((uint3)(uVar2 + uVar3) + (uint3)param_2 * 0x4000);
    if (uVar12 != 0) {
      uVar2 = *(ushort *)((uint3)(uVar2 + uVar3 + 2) + (uint3)param_2 * 0x4000);
      if (uVar2 < uVar15) {
        uVar15 = uVar15 - (short)(((uint)(uVar15 - uVar2) * (uint)uVar12) / (uint)uVar14);
      }
      else {
        uVar15 = uVar15 + (short)(((uint)(uVar2 - uVar15) * (uint)uVar12) / (uint)uVar14);
      }
    }
    if (uVar15 < uVar8) {
      uVar6 = (uint)(uVar8 - uVar15) * (uint)uVar11;
      sVar4 = (short)(uVar6 / uVar13);
      iVar5 = CONCAT22((short)(uVar6 % (uint)uVar13),sVar4);
      uVar8 = uVar8 - sVar4;
    }
    else {
      uVar6 = (uint)(uVar15 - uVar8) * (uint)uVar11;
      sVar4 = (short)(uVar6 / uVar13);
      iVar5 = CONCAT22((short)(uVar6 % (uint)uVar13),sVar4);
      uVar8 = uVar8 + sVar4;
    }
  }
  MDH = (undefined2)((uint)iVar5 >> 0x10);
  MDL = (undefined2)iVar5;
  MDC = MDC | 0x10;
  return uVar8;
}


// ================= me7_lookup_2d_sbyte_bilinear @ 0411f4 =================

/* 2-D bilinear sbyte map (KFZW path) */

short me7_lookup_2d_sbyte_bilinear(short param_1,ushort param_2,ushort param_3,ushort param_4)

{
  ushort uVar1;
  int iVar2;
  short sVar3;
  short sVar4;
  
  uVar1 = param_1 + (param_3 >> 8) * (ushort)*(byte *)((uint3)param_2 + 0x10000) + (param_4 >> 8);
  sVar4 = (short)*(char *)((uint3)uVar1 + 0x10000);
  param_4 = param_4 & 0xff;
  if (param_4 != 0) {
    sVar4 = sVar4 + (short)((uint)((int)((((char *)&ram0x00ce36)
                                          [(int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                                                 (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                                                       (int3)(
                                                  s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                                                  (uint3)uVar1 + 0x729)))] - sVar4) * 2) *
                                  (int)(short)(param_4 << 7)) >> 0x10);
  }
  uVar1 = uVar1 + *(byte *)((uint3)param_2 + 0x10000);
  sVar3 = (short)*(char *)((uint3)uVar1 + 0x10000);
  if (param_4 != 0) {
    sVar3 = sVar3 + (short)((uint)((int)((*(char *)((uint3)(uVar1 + 1) + 0x10000) - sVar3) * 2) *
                                  (int)(short)(param_4 << 7)) >> 0x10);
  }
  iVar2 = (int)((sVar3 - sVar4) * 2) * (int)(short)((param_3 & 0xff) << 7);
  MDL = (short)iVar2;
  MDH = (short)((uint)iVar2 >> 0x10);
  MDC = MDC | 0x10;
  return sVar4 + MDH;
}


// ================= me7_lookup_2d_word_torque @ 043430 =================

/* 2-D bilinear word map (torque / KFMIOP) */

ushort me7_lookup_2d_word_torque(short param_1,ushort param_2,ushort param_3,ushort param_4)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  ushort uVar4;
  ushort uVar5;
  
  uVar4 = (param_3 >> 8) * (ushort)*(byte *)((uint3)param_2 + 0x10000);
  uVar3 = (uint)uVar4;
  uVar1 = param_1 + ((param_4 >> 8) + uVar4) * 2;
  uVar4 = *(ushort *)((uint3)uVar1 + 0x10000);
  param_4 = param_4 << 8;
  if (param_4 != 0) {
    uVar5 = *(ushort *)
             ((char *)&ram0x00ce36 +
             (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                   (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                         (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 + (uint3)uVar1 + 0x72a))))
    ;
    if (uVar4 < uVar5) {
      uVar3 = (uint)(uVar5 - uVar4) * (uint)param_4;
      uVar4 = uVar4 + (short)(uVar3 >> 0x10);
    }
    else {
      uVar3 = (uint)(uVar4 - uVar5) * (uint)param_4;
      uVar4 = uVar4 - (short)(uVar3 >> 0x10);
    }
  }
  param_3 = param_3 << 8;
  if (param_3 != 0) {
    uVar1 = uVar1 + (ushort)*(byte *)((uint3)param_2 + 0x10000) * 2;
    uVar5 = *(ushort *)((uint3)uVar1 + 0x10000);
    if (param_4 != 0) {
      uVar1 = *(ushort *)((uint3)(uVar1 + 2) + 0x10000);
      if (uVar5 < uVar1) {
        uVar5 = uVar5 + (short)((uint)(uVar1 - uVar5) * (uint)param_4 >> 0x10);
      }
      else {
        uVar5 = uVar5 - (short)((uint)(uVar5 - uVar1) * (uint)param_4 >> 0x10);
      }
    }
    if (uVar5 <= uVar4) {
      iVar2 = (uint)(uVar4 - uVar5) * (uint)param_3;
      MDL = (short)iVar2;
      MDH = (short)((uint)iVar2 >> 0x10);
      MDC = MDC | 0x10;
      return uVar4 - MDH;
    }
    uVar3 = (uint)(uVar5 - uVar4) * (uint)param_3;
    uVar4 = uVar4 + (short)(uVar3 >> 0x10);
  }
  MDH = (short)(uVar3 >> 0x10);
  MDL = (undefined2)uVar3;
  MDC = MDC | 0x10;
  return uVar4;
}


// ================= me7_lookup_2d_byte @ 041bd4 =================

/* 2-D byte map interp */

ushort me7_lookup_2d_byte(ushort param_1,ushort param_2,byte param_3,byte param_4)

{
  byte bVar1;
  byte *pbVar2;
  ushort uVar3;
  int iVar4;
  byte *pbVar5;
  ushort uVar6;
  byte *pbVar7;
  byte *pbVar8;
  ushort uVar9;
  ushort uVar10;
  ushort uVar11;
  ushort uVar12;
  ushort uVar13;
  short sVar14;
  
  bVar1 = *(byte *)((uint3)param_1 + (uint3)param_2 * 0x4000);
  pbVar2 = (byte *)(param_1 + 2);
  uVar10 = 0;
  uVar12 = 0;
  uVar6 = 0;
  if (param_3 != *pbVar2 && *pbVar2 <= param_3) {
    pbVar8 = pbVar2 + bVar1 + -1;
    pbVar5 = pbVar2 + bVar1;
    if (param_3 < *pbVar8) {
      do {
        pbVar7 = pbVar5;
        pbVar8 = pbVar7 + -1;
        pbVar5 = pbVar8;
      } while (param_3 < *pbVar8);
      uVar10 = (ushort)(byte)(param_3 - *pbVar8);
      uVar12 = (ushort)(byte)(*(char *)(ZEXT23(pbVar7) + (uint3)param_2 * 0x4000) - *pbVar8);
    }
    uVar6 = (short)pbVar8 - (short)pbVar2;
  }
  pbVar2 = pbVar2 + bVar1;
  uVar3 = (ushort)*(byte *)((uint3)(param_1 + 1) + (uint3)param_2 * 0x4000);
  uVar11 = 0;
  uVar13 = 0;
  sVar14 = 0;
  if (param_4 != *pbVar2 && *pbVar2 <= param_4) {
    pbVar8 = pbVar2 + uVar3 + -1;
    pbVar5 = pbVar2 + uVar3;
    if (param_4 < *pbVar8) {
      do {
        pbVar7 = pbVar5;
        pbVar8 = pbVar7 + -1;
        pbVar5 = pbVar8;
      } while (param_4 < *pbVar8);
      uVar11 = (ushort)(byte)(param_4 - *pbVar8);
      uVar13 = (ushort)(byte)(*(char *)(ZEXT23(pbVar7) + (uint3)param_2 * 0x4000) - *pbVar8);
    }
    sVar14 = (short)pbVar8 - (short)pbVar2;
  }
  iVar4 = (uint)uVar6 * (uint)uVar3;
  pbVar2 = pbVar2 + sVar14 + (short)iVar4 + uVar3;
  uVar6 = (ushort)*(byte *)(ZEXT23(pbVar2) + (uint3)param_2 * 0x4000);
  if (uVar11 != 0) {
    iVar4 = (int)(short)(*(byte *)(ZEXT23(pbVar2 + 1) + (uint3)param_2 * 0x4000) - uVar6) *
            (int)(short)uVar11;
    sVar14 = (short)(iVar4 / (int)(short)uVar13);
    iVar4 = CONCAT22((short)(iVar4 % (int)(short)uVar13),sVar14);
    uVar6 = uVar6 + sVar14;
  }
  if (uVar10 != 0) {
    uVar9 = (ushort)*(byte *)(ZEXT23(pbVar2 + uVar3) + (uint3)param_2 * 0x4000);
    if (uVar11 != 0) {
      uVar9 = uVar9 + (short)(((int)(short)(*(byte *)(ZEXT23(pbVar2 + uVar3 + 1) +
                                                     (uint3)param_2 * 0x4000) - uVar9) *
                              (int)(short)uVar11) / (int)(short)uVar13);
    }
    iVar4 = (int)(short)(uVar9 - uVar6) * (int)(short)uVar10;
    sVar14 = (short)(iVar4 / (int)(short)uVar12);
    iVar4 = CONCAT22((short)(iVar4 % (int)(short)uVar12),sVar14);
    uVar6 = uVar6 + sVar14;
  }
  MDH = (undefined2)((uint)iVar4 >> 0x10);
  MDL = (undefined2)iVar4;
  MDC = MDC | 0x10;
  return uVar6;
}


// ================= me7_lookup_2d_misc @ 0415b0 =================

/* 2-D interp variant (after-start / misc) */

short me7_lookup_2d_misc(undefined2 param_1,undefined2 param_2,undefined2 param_3,short param_4,
                        undefined2 unaff_00000002,undefined2 unaff_00000004)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  short sVar5;
  int iVar4;
  ushort uVar6;
  ushort uVar7;
  ushort uVar8;
  undefined2 extraout_r11;
  undefined4 uVar9;
  
  func_0x040a5a(param_2,param_1,unaff_00000002);
  uVar9 = func_0x040ac4(param_3,extraout_r11,unaff_00000004);
  uVar8 = (ushort)((uint)uVar9 >> 0x10);
  uVar2 = param_4 + (((ushort)uVar9 >> 8) +
                    (uVar8 >> 8) * (ushort)*(byte *)(ZEXT23(&param_4) + 0x10000)) * 2;
  uVar7 = *(ushort *)((uint3)uVar2 + 0x10000);
  uVar3 = (ushort)uVar9 << 8;
  uVar1 = *(ushort *)
           ((char *)&ram0x00ce36 +
           (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                 (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                       (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 + (uint3)uVar2 + 0x72a))));
  if (uVar7 < uVar1) {
    sVar5 = (short)((uint)(uVar1 - uVar7) * (uint)uVar3 >> 0x10);
  }
  else {
    sVar5 = -(short)((uint)(uVar7 - uVar1) * (uint)uVar3 >> 0x10);
  }
  uVar7 = uVar7 + sVar5;
  uVar8 = uVar8 << 8;
  uVar2 = uVar2 + (ushort)*(byte *)(ZEXT23(&param_4) + 0x10000) * 2;
  uVar6 = *(ushort *)((uint3)uVar2 + 0x10000);
  uVar1 = *(ushort *)((uint3)(uVar2 + 2) + 0x10000);
  if (uVar6 < uVar1) {
    sVar5 = (short)((uint)(uVar1 - uVar6) * (uint)uVar3 >> 0x10);
  }
  else {
    sVar5 = -(short)((uint)(uVar6 - uVar1) * (uint)uVar3 >> 0x10);
  }
  uVar6 = uVar6 + sVar5;
  if (uVar7 < uVar6) {
    iVar4 = (uint)(uVar6 - uVar7) * (uint)uVar8;
    MDL = (short)iVar4;
    MDH = (short)((uint)iVar4 >> 0x10);
    MDC = MDC | 0x10;
    return uVar7 + MDH;
  }
  iVar4 = (uint)(uVar7 - uVar6) * (uint)uVar8;
  MDL = (short)iVar4;
  MDH = (short)((uint)iVar4 >> 0x10);
  MDC = MDC | 0x10;
  return uVar7 - MDH;
}


// ================= me7_axis_search @ 040eb0 =================

/* axis search: returns interp index+fraction (divlu) */

undefined2 me7_axis_search(ushort param_1,ushort param_2)

{
  uint uVar1;
  ushort *puVar2;
  undefined2 uVar3;
  ushort *puVar4;
  
  uVar3 = 0;
  puVar4 = (ushort *)(param_1 + 2);
  if (param_2 != *puVar4 && *puVar4 <= param_2) {
    puVar2 = puVar4 + ((*(ushort *)((uint3)param_1 + 0x10000) & 0xff) - 1);
    if (param_2 < *puVar2) {
      do {
        puVar2 = puVar2 + -1;
      } while (param_2 < *puVar2);
      uVar1 = CONCAT22(param_2 - *puVar2 >> 8,(param_2 - *puVar2) * 0x100);
      uVar3 = (undefined2)
              (uVar1 / (*(short *)((char *)&ram0x00ce36 +
                                  (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                                        (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                                              (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                                                    ZEXT23(puVar2) + 0x72a)))) - *puVar2));
      MDH = (undefined2)
            (uVar1 % (uint)(*(short *)((char *)&ram0x00ce36 +
                                      (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                                            (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                                                  (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                                                        ZEXT23(puVar2) + 0x72a)))) - *puVar2));
      MDC = MDC | 0x10;
      MDL = uVar3;
    }
    uVar3 = CONCAT11((char)((ushort)((short)puVar2 - (short)puVar4) >> 1),(char)uVar3);
  }
  return uVar3;
}


// ================= me7_pt1_integrator @ 043904 =================

/* PT1 / integrator: state += gain*(target-state) */

int me7_pt1_integrator(ushort param_1,ushort param_2,ushort param_3,ushort param_4)

{
  ushort uVar1;
  
  uVar1 = param_2 - param_3;
  if (uVar1 != 0 && param_3 <= param_2) {
    MDL = (ushort)((uint)param_1 * (uint)uVar1);
    MDH = (short)((uint)param_1 * (uint)uVar1 >> 0x10);
    MDC = MDC | 0x10;
    return CONCAT22(MDH + param_3 + (ushort)(MDL + param_4 < MDL || MDL + param_4 < param_4),
                    MDL + param_4);
  }
  if (uVar1 != 0) {
    MDL = (ushort)((uint)param_1 * (uint)-uVar1);
    MDH = (short)((uint)param_1 * (uint)-uVar1 >> 0x10);
    MDC = MDC | 0x10;
    return CONCAT22((param_3 - MDH) - (ushort)(param_4 < MDL),param_4 - MDL);
  }
  return (uint)param_3 << 0x10;
}


// ================= me7_slew_limiter @ 0438f6 =================

/* slew / ramp limiter toward target (rate-limited) */

int me7_slew_limiter(ushort param_1,short param_2,ushort param_3,ushort param_4)

{
  ushort uVar1;
  
  uVar1 = param_2 - param_3;
  if (uVar1 != 0 &&
      (short)uVar1 < 0 ==
      (param_2 < 0 != (short)param_3 < 0 && (short)(param_2 - param_3) < 0 != param_2 < 0)) {
    MDL = (ushort)((uint)param_1 * (uint)uVar1);
    MDH = (short)((uint)param_1 * (uint)uVar1 >> 0x10);
    MDC = MDC | 0x10;
    return CONCAT22(MDH + param_3 + (ushort)(MDL + param_4 < MDL || MDL + param_4 < param_4),
                    MDL + param_4);
  }
  if (uVar1 != 0) {
    MDL = (ushort)((uint)param_1 * (uint)-uVar1);
    MDH = (short)((uint)param_1 * (uint)-uVar1 >> 0x10);
    MDC = MDC | 0x10;
    return CONCAT22((param_3 - MDH) - (ushort)(param_4 < MDL),param_4 - MDL);
  }
  return (uint)param_3 << 0x10;
}


// ================= me7_integrator_minmax @ 042f16 =================

/* integrator with min/max clamp */

int me7_integrator_minmax
              (ushort param_1,ushort param_2,ushort param_3,ushort param_4,ushort unaff_00000000,
              ushort unaff_00000002)

{
  bool bVar1;
  ushort uVar2;
  int iVar3;
  ushort uVar4;
  ushort uVar5;
  
  uVar4 = MDC;
  if ((param_2 & 0x8000) == 0) {
    iVar3 = (uint)param_1 * (uint)param_2;
    uVar2 = (ushort)iVar3;
    MDL = uVar2;
    MDH = (ushort)((uint)iVar3 >> 0x10);
    MDC = MDC | 0x10;
    bVar1 = param_4 + uVar2 < param_4 || param_4 + uVar2 < uVar2;
    uVar5 = param_3 + MDH + (ushort)bVar1;
    if (param_3 + MDH < param_3 || param_3 + MDH == 0xffff && bVar1) {
      return (uint)unaff_00000002 << 0x10;
    }
  }
  else {
    iVar3 = (uint)param_1 * (uint)-param_2;
    MDL = (ushort)iVar3;
    MDH = (ushort)((uint)iVar3 >> 0x10);
    MDC = MDC | 0x10;
    uVar2 = -MDL;
    uVar5 = (param_3 - MDH) - (ushort)(param_4 < MDL);
    if (param_3 < MDH || param_3 == MDH && param_4 < MDL) {
      return (uint)unaff_00000000 << 0x10;
    }
  }
  MDH = (ushort)((uint)iVar3 >> 0x10);
  MDL = (ushort)iVar3;
  MDC = uVar4 | 0x10;
  if (uVar5 <= unaff_00000002) {
    if (unaff_00000000 <= uVar5) {
      return CONCAT22(uVar5,param_4 + uVar2);
    }
    return (uint)unaff_00000000 << 0x10;
  }
  return (uint)unaff_00000002 << 0x10;
}


// ================= me7_integrator_sat @ 042df4 =================

/* 32-bit MAC integrator with +-0x7FFF saturation */

undefined4 me7_integrator_sat(ushort param_1,ushort param_2,short param_3,ushort param_4)

{
  bool bVar1;
  ushort uVar2;
  short sVar4;
  short sVar5;
  short sVar6;
  int iVar3;
  
  if ((param_2 & 0x8000) == 0) {
    iVar3 = (uint)param_1 * (uint)param_2;
    uVar2 = (ushort)iVar3;
    sVar4 = (short)((uint)iVar3 >> 0x10);
    bVar1 = param_4 + uVar2 < param_4 || param_4 + uVar2 < uVar2;
    sVar5 = param_4 + uVar2;
    sVar6 = param_3 + sVar4 + (ushort)bVar1;
    if (param_3 < 0 == iVar3 < 0 && (short)(param_3 + sVar4 + (ushort)bVar1) < 0 != param_3 < 0) {
      sVar5 = -1;
      sVar6 = 0x7fff;
    }
  }
  else {
    iVar3 = (uint)param_1 * (uint)-param_2;
    uVar2 = (ushort)iVar3;
    sVar4 = (short)((uint)iVar3 >> 0x10);
    sVar5 = param_4 - uVar2;
    sVar6 = (param_3 - sVar4) - (ushort)(param_4 < uVar2);
    if (param_3 < 0 != iVar3 < 0 &&
        (short)((param_3 - sVar4) - (ushort)(param_4 < uVar2)) < 0 != param_3 < 0) {
      sVar5 = 0;
      sVar6 = -0x8000;
    }
  }
  MDH = (undefined2)((uint)iVar3 >> 0x10);
  MDL = (undefined2)iVar3;
  MDC = MDC | 0x10;
  return CONCAT22(sVar6,sVar5);
}


// ================= me7_fraction_blend @ 042cf4 =================

/* fraction interpolation: out = lo + frac*(hi-lo) */

ushort me7_fraction_blend(ushort param_1,short param_2,ushort param_3)

{
  int iVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  
  uVar2 = MDC;
  uVar3 = param_2 * 0x100;
  if (uVar3 < param_3) {
    iVar1 = (uint)param_1 * (uint)(param_3 + param_2 * -0x100);
    uVar3 = (ushort)((uint)iVar1 >> 0x10);
    if (uVar3 == 0) {
      uVar3 = 1;
    }
    uVar4 = param_3 - uVar3;
    if (param_3 < uVar3) {
      uVar4 = 0;
    }
  }
  else {
    if (uVar3 == param_3) {
      return param_3;
    }
    iVar1 = (uint)param_1 * (uint)(uVar3 - param_3);
    MDL = (short)iVar1;
    uVar3 = (ushort)((uint)iVar1 >> 0x10);
    MDH = uVar3;
    MDC = MDC | 0x10;
    if (uVar3 == 0) {
      uVar3 = 1;
    }
    uVar4 = uVar3 + param_3;
    if (uVar3 + param_3 < uVar3 || uVar3 + param_3 < param_3) {
      return 0xffff;
    }
  }
  MDH = (ushort)((uint)iVar1 >> 0x10);
  MDL = (undefined2)iVar1;
  MDC = uVar2 | 0x10;
  return uVar4;
}


// ================= main_control_scheduler @ 00b81c =================

/* top-level periodic control scheduler chain */

void main_control_scheduler(void)

{
  func_0x00a9fc();
  sRam00fc76 = sRam00fc76 + 1;
  func_0x043a90();
  func_0x0accaa();
  catheat_coordinator();
  func_0x054792();
  func_0x055634();
  func_0x075c5c();
  func_0x07ce76();
  func_0x055a68();
  func_0x05533c();
  idle_spark_reserve();
  torque_reserve_request();
  func_0x04e964();
  torque_coord_stage2();
  func_0x0933be();
  func_0x058e4e();
  func_0x07ff0e();
  func_0x087dfa();
  func_0x089038();
  func_0x09d872();
  func_0x0d89cc();
  func_0x08d766();
  func_0x03fffe();
  func_0x04b4f8();
  func_0x08fccc();
  func_0x0861c4();
  func_0x07cc7c();
  func_0x07a338();
  func_0x0408a2();
  func_0x09ca84();
  func_0x070d86();
  func_0x067978();
  func_0x067d98();
  func_0x07177c();
  func_0x05275a();
  diag_input_monitor_bank();
  func_0x03b35e();
  diag_setpoint_follow_monitor();
  cruise_speed_governor();
  func_0x0cb61c();
  func_0x0cb50a();
  func_0x0ca51e();
  etc_stop_learn_adapt();
  func_0x0c6fa4();
  func_0x08a072();
  func_0x0d222a();
  ign_scheduler();
  func_0x0d0f40();
  func_0x06a4ac();
  func_0x0553c6();
  func_0x054d2a();
  func_0x08a834();
  func_0x04ea22();
  func_0x0db370();
  func_0x0db49a();
  func_0x0db522();
  ldr_boost_pi_math();
  func_0x0db882();
  ldr_boost_enable_limit();
  func_0x0dc57e();
  func_0x0dc672();
  func_0x0dcb84();
  fuel_lambda_multiplier();
  func_0x00aa0c();
  return;
}


// ================= ldr_boost_pi_math @ 0dbb04 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* LDR boost PI + feed-forward math */

void ldr_boost_pi_math(void)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  ushort uVar8;
  ushort uVar9;
  undefined2 uVar10;
  short sVar11;
  short sVar12;
  undefined4 uVar13;
  
  uVar4 = ((uint)uRam02b410 * (uint)uRam02be38 >> 0x10) * (uint)_rk_w;
  MDL = (ushort)uVar4;
  MDH = (ushort)(uVar4 >> 0x10);
  MDC = MDC | 0x10;
  sVar12 = (short)((uVar4 >> 10) >> 0x10);
  uRam302e64 = (ushort)(uVar4 >> 10);
  bVar1 = uRam302e64 != 0xffff;
  if (sVar12 != 0 || !bVar1) {
    uRam302e64 = 0xffff;
  }
  if ((bRam01be46 & 1) == 0) {
    uRam302e66 = me7_lookup_1d_word(0x3e92,10,uRam302e3e,sVar12 - (ushort)bVar1);
  }
  else {
    uRam302e66 = 0;
  }
  _ldr_setpoint = uRam302e64 + uRam302e66;
  if (uRam302e64 + uRam302e66 < uRam302e64 || uRam302e64 + uRam302e66 < uRam302e66) {
    _ldr_setpoint = -1;
  }
  uVar4 = CONCAT22(_load_measured >> 5,_load_measured << 0xb);
  uVar2 = uVar4 / uRam30294a;
  MDL = (ushort)uVar2;
  MDH = (ushort)(uVar4 % (uint)uRam30294a);
  MDC = MDC | 0x10;
  _ldr_actual_ratio = MDL;
  if (uRam30294a == 0 || 0xffff < uVar2) {
    _ldr_actual_ratio = 0xffff;
  }
  _lditv_w = me7_pt1_integrator(uRam02bf32,uRam02ae58,lditv_w_2,_lditv_w);
  uVar8 = me7_lookup_1d_word(0x3e3a,10,nmot_w);
  sVar12 = _ldr_actual_ratio - lditv_w_2;
  if (_ldr_actual_ratio < lditv_w_2) {
    if (sVar12 >= 0) {
      sVar12 = -0x8000;
    }
  }
  else if (sVar12 < 0) {
    sVar12 = 0x7fff;
  }
  if ((short)uVar8 < 0) {
    iVar3 = (int)sVar12 * (int)(short)(uVar8 & 0x7fff);
    uVar9 = (ushort)iVar3;
    uVar8 = sVar12 * -0x8000;
    iVar5 = CONCAT22((short)((uint)iVar3 >> 0x10) + (sVar12 >> 1) +
                     (ushort)(uVar9 + uVar8 < uVar9 || uVar9 + uVar8 < uVar8),uVar9 + uVar8);
  }
  else {
    iVar5 = (int)sVar12 * (int)(short)uVar8;
    iVar3 = iVar5;
  }
  MDH = (ushort)((uint)iVar3 >> 0x10);
  MDL = (ushort)iVar3;
  MDC = MDC | 0x10;
  iVar5 = iVar5 >> 0xe;
  uVar9 = (ushort)((uint)iVar5 >> 0x10);
  uRam302e52 = (ushort)iVar5;
  uVar8 = (ushort)(uRam302e52 < 0x7fff);
  if (uVar9 == uVar8 && uRam302e52 == 0x7fff ||
      (short)(uVar9 - uVar8) < 0 !=
      (iVar5 < 0 && (short)(uVar9 - (uRam302e52 < 0x7fff)) < 0 != iVar5 < 0)) {
    if ((short)((uVar9 + 1) - (ushort)(uRam302e52 < 0x8000)) < 0 !=
        (-1 < iVar5 && (short)((uVar9 + 1) - (ushort)(uRam302e52 < 0x8000)) < 0 != iVar5 < 0)) {
      uRam302e52 = 0x8000;
    }
  }
  else {
    uRam302e52 = 0x7fff;
  }
  sRam302e5c = me7_lookup_1d_word_signed(0x3e74,10,uRam302e52);
  iVar5 = (uint)uRam02ae3c * (uint)uRam02bf2e;
  MDL = (ushort)iVar5;
  MDH = (ushort)((uint)iVar5 >> 0x10);
  MDC = MDC | 0x10;
  if ((iVar5 < 0) || ((BADTYPE)(MDH >> 0xe & 1))) {
    uVar8 = 0xffff;
  }
  else {
    uVar8 = MDH << 2 | MDL >> 0xe;
  }
  uRam302e70 = me7_pt1_integrator(uRam02bf30,uVar8,uRam302e70._2_2_,(undefined2)uRam302e70);
  uVar9 = (ushort)((uint)uRam302e70 >> 0x10);
  sRam302e50 = uVar8 - uVar9;
  if (uVar8 < uVar9) {
    if (sRam302e50 >= 0) {
      sRam302e50 = -0x8000;
    }
  }
  else if (sRam302e50 < 0) {
    sRam302e50 = 0x7fff;
  }
  sRam302e5a = me7_lookup_1d_word_signed(0x3e56,10,sRam302e50);
  sVar12 = sRam302e5c + sRam302e5a;
  if (sRam302e5c < 0 == sRam302e5a < 0 && sRam302e5c + sRam302e5a < 0 != sRam302e5c < 0) {
    sVar12 = 0x7fff;
  }
  sVar11 = sVar12 + sRam30bf0a;
  if (sVar12 < 0 == sRam30bf0a < 0 && sVar12 + sRam30bf0a < 0 != sVar12 < 0) {
    sVar11 = 0x7fff;
  }
  if (sVar11 + 0x4000 < 0 == (-1 < sVar11 && sVar11 + 0x4000 < 0 != sVar11 < 0)) {
    if (sVar11 != 0x3fff &&
        sVar11 + -0x3fff < 0 == (sVar11 < 0 && sVar11 + -0x3fff < 0 != sVar11 < 0)) {
      sVar11 = 0x3fff;
    }
  }
  else {
    sVar11 = -0x4000;
  }
  uVar8 = sVar11 * 2;
  uVar9 = me7_lookup_2d_word_bilinear(0x3eca,10,_ldr_setpoint,uRam302e3e);
  uVar13 = CONCAT22(uRam302e6e,uRam302e6c);
  if ((short)uVar8 < 0) {
    uRam302e5e = uVar8 + uVar9;
    if (uVar8 <= uVar8 + uVar9 && uVar9 <= uVar8 + uVar9) {
      uRam302e5e = 0;
    }
  }
  else {
    uRam302e5e = uVar8 + uVar9;
    if (uVar8 + uVar9 < uVar8 || uVar8 + uVar9 < uVar9) {
      uRam302e5e = 0xffff;
    }
  }
  uVar8 = uRam302e5e;
  uVar6 = _lditv_w;
  uVar7 = uRam302e70;
  if (uRam305630 < bRam01be47) {
    sRam302e56 = uRam302e3c - uRam302e38;
    if (uRam302e3c < uRam302e38) {
      sRam302e56 = 0;
    }
    uVar10 = me7_lookup_1d_word(0x3eac,10,sRam302e56);
    uVar13 = me7_pt1_integrator(uVar10,0,uRam302e6e,uRam302e6c);
    uRam302e54 = (ushort)((uint)uVar13 >> 0x10);
    uVar8 = uRam302e54 + uRam302e5e;
    uVar6 = _lditv_w;
    uVar7 = uRam302e70;
    if (uRam302e54 + uRam302e5e < uRam302e54 || uRam302e54 + uRam302e5e < uRam302e5e) {
      uVar8 = 0xffff;
    }
  }
  _ldr_demand = uVar8;
  uRam302e6e = (undefined2)((uint)uVar13 >> 0x10);
  uRam302e6c = (undefined2)uVar13;
  uRam302e70._2_2_ = (undefined2)((uint)uVar7 >> 0x10);
  uRam302e70._0_2_ = (undefined2)uVar7;
  lditv_w_2 = (ushort)((uint)uVar6 >> 0x10);
  _lditv_w = (undefined2)uVar6;
  return;
}


// ================= ldr_boost_enable_limit @ 0dbf44 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* LDR enable/limit state machine (KFLDIMX threshold) */

void ldr_boost_enable_limit(void)

{
  int iVar1;
  bool bVar2;
  ushort uVar3;
  ushort uVar4;
  
  if ((bRam301868 & 1) == 0) {
    if ((bRam30186b < bRam01be69) && (uRam302e34 < _KFLDIMX_threshold)) {
      if (((bRam301869 & 1) == 0) && (uRam302e34 < _KFLDIMX_threshold)) {
        bRam301869 = bRam301869 | 2;
      }
    }
    else {
      bRam301869 = bRam301869 & 0xfd;
    }
    if (((bRam301869 & 2) != 0) && (bRam301869 = bRam301869 | 1, bRam30186b != 0xff)) {
      bRam30186b = bRam30186b + 1;
    }
  }
  if (((uRam30256a & 8) == 0) &&
     ((((uRam00fd0e & 0x1000) != 0 || ((bRam301869 & 2) != 0)) || ((uRam00fd7e & 0x2000) != 0)))) {
    bRam301867 = bRam301867 | 6;
  }
  else {
    bRam301867 = bRam301867 & 0xf9;
  }
  if ((bRam01be46 & 1) != 0) {
    if (((flags_torque_revlimit & 0x80) == 0) && ((bRam301868 & 2) == 0)) {
      PSW = PSW & 0xffbf;
      bVar2 = false;
    }
    else {
      PSW = PSW | 0x40;
      bVar2 = true;
    }
    if ((short)uRam02bf4c < 0) {
      uVar3 = uRam02bf4c + uRam02ae3e;
      if (uRam02bf4c <= uRam02bf4c + uRam02ae3e && uRam02ae3e <= uRam02bf4c + uRam02ae3e) {
        uVar3 = 0;
      }
    }
    else {
      uVar3 = uRam02bf4c + uRam02ae3e;
      if (uRam02bf4c + uRam02ae3e < uRam02bf4c || uRam02bf4c + uRam02ae3e < uRam02ae3e) {
        uVar3 = 0xffff;
      }
    }
    if (uRam302e38 < uVar3) {
      PSW = PSW | 0x40;
    }
    else {
      PSW = PSW & 0xffbf;
    }
    uVar3 = (PSW & 0x40) >> 6;
    if (((bRam30186f & 0x10) != 0) || (bVar2)) {
      if (bVar2) {
        sRam302e82 = sRam017720;
        bRam30186f = bRam30186f & 0xdf;
      }
      else if (sRam302e82 == 0) {
        bRam30186f = bRam30186f | 0x20;
      }
      else {
        sRam302e82 = sRam302e82 + -1;
      }
      if (((bVar2) || (uVar3 == 0)) && ((bRam30186f & 0x20) == 0)) {
        if (bVar2) {
          bRam30186f = bRam30186f | 0x10;
        }
      }
      else {
        bRam30186f = bRam30186f & 0xef;
      }
    }
    if (((bRam30186f & 0x40) != 0) || ((_flags_start_phase & 0x8000) == 0)) {
      if ((_flags_start_phase & 0x8000) == 0) {
        sRam302e80 = sRam017720;
        bRam30186f = bRam30186f & 0x7f;
      }
      else if (sRam302e80 == 0) {
        bRam30186f = bRam30186f | 0x80;
      }
      else {
        sRam302e80 = sRam302e80 + -1;
      }
      if ((uVar3 == 0) && ((bRam30186f & 0x80) == 0)) {
        if ((bRam301869 & 4) == 0) {
          if ((short)uRam02bf4c < 0) {
            uVar3 = uRam02bf4c + uRam02ae3c;
            if (uRam02bf4c <= uRam02bf4c + uRam02ae3c && uRam02ae3c <= uRam02bf4c + uRam02ae3c) {
              uVar3 = 0;
            }
          }
          else {
            uVar3 = uRam02bf4c + uRam02ae3c;
            if (uRam02bf4c + uRam02ae3c < uRam02bf4c || uRam02bf4c + uRam02ae3c < uRam02ae3c) {
              uVar3 = 0xffff;
            }
          }
          if (uVar3 <= uRam302e38) {
            bRam30186f = bRam30186f | 0x40;
          }
        }
      }
      else {
        bRam30186f = bRam30186f & 0xbf;
      }
      if ((bRam30186f & 0x40) != 0) {
        bRam301869 = bRam301869 | 4;
      }
    }
  }
  if (((bRam30186f & 0x10) == 0) && ((bRam30186f & 0x40) == 0)) {
    bRam301867 = bRam301867 & 0xf7;
  }
  else {
    bRam301867 = bRam301867 | 8;
  }
  uRam302e7a = func_0x042464(uRam02bf34,0x3f35,10,0x3f3c,10,uRam30183c);
  uVar3 = _ldr_demand >> 1;
  if ((short)uRam302e4a < 0) {
    uVar4 = uRam302e4a + uVar3;
    if (uRam302e4a <= uRam302e4a + uVar3 && uVar3 <= uRam302e4a + uVar3) {
      uVar4 = 0;
    }
  }
  else {
    uVar4 = uRam302e4a + uVar3;
    if (uRam302e4a + uVar3 < uRam302e4a || uRam302e4a + uVar3 < uVar3) {
      uVar4 = 0xffff;
    }
  }
  iVar1 = (uint)uVar4 * (uint)uRam302e7a;
  MDL = (ushort)iVar1;
  MDH = (ushort)((uint)iVar1 >> 0x10);
  MDC = MDC | 0x10;
  if ((iVar1 < 0) || ((BADTYPE)(MDH >> 0xe & 1))) {
    _ldtvm_scaled = 0xffff;
  }
  else {
    _ldtvm_scaled = MDH << 2 | (ushort)iVar1 >> 0xe;
  }
  if (((bRam01be49 & 1) == 0) || (((bRam301872 & 1) == 0 && ((uRam303abc & 1) == 0)))) {
    bRam30186f = bRam30186f & 0xfe;
    bVar2 = false;
  }
  else {
    bRam30186f = bRam30186f | 1;
    bVar2 = true;
  }
  if ((bRam301867 & 2) == 0) {
    if ((bRam01be4a & 1) == 0) {
      uRam302e7e = 0;
      uVar3 = uRam302e7e;
    }
    else {
      uRam302e7e = 0xffff;
      uVar3 = uRam302e7e;
    }
    goto LAB_0dc296;
  }
  if ((!bVar2) && ((bRam301868 & 2) == 0)) {
    if ((bRam301867 & 8) != 0) {
      uVar3 = (ushort)bRam01be66 << 8;
      goto LAB_0dc296;
    }
    if (_ldtvm_scaled < _WG_duty_min) {
      uRam02ae7e = _WG_duty_min;
      uVar3 = uRam302e7e;
      goto LAB_0dc296;
    }
    uVar3 = _ldtvm_scaled;
    if (_ldtvm_scaled <= _WG_duty_max) goto LAB_0dc296;
  }
  uRam02ae7e = _WG_duty_max;
  uVar3 = uRam302e7e;
LAB_0dc296:
  uRam302e7e = uVar3;
  if (((_ldtvm_scaled < _WG_duty_max) || (sRam302e42 < 1)) &&
     ((_WG_duty_min < _ldtvm_scaled || (-1 < sRam302e42)))) {
    bRam301867 = bRam301867 & 0xfe;
  }
  else {
    bRam301867 = bRam301867 | 1;
  }
  if ((bRam30186f & 2) == 0) {
    bRam30186f = bRam30186f & 0xfb;
  }
  else {
    bRam30186f = bRam30186f | 4;
  }
  if ((flags_torque_revlimit & 0x80) == 0) {
    bRam30186f = bRam30186f & 0xf7;
  }
  else {
    bRam30186f = bRam30186f | 8;
  }
  return;
}


// ================= ldr_solenoid_output @ 0dc31a =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* LDR wastegate solenoid output + overboost RPM trip */

void ldr_solenoid_output(short param_1)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  
  if ((uRam00fd0e & 0x1000) != 0) {
    bRam301868 = bRam301868 | 1;
  }
  if ((bRam301868 & 1) != 0) {
    bRam301869 = bRam301869 & 0xfd;
    uRam00fd7e = uRam00fd7e & 0xdfff;
  }
  if ((bRam01be46 & 2) != 0) {
    if (((flags_torque_revlimit & 0x80) == 0) && ((bRam301870 & 1) != 0)) {
      PSW = PSW | 0x40;
    }
    else {
      PSW = PSW & 0xffbf;
    }
    if (param_1 < 0) {
      bRam301868 = bRam301868 | 4;
    }
    if (((bRam301868 & 8) != 0) ||
       (((flags_torque_revlimit & 0x80) != 0 && ((bRam301872 & 1) == 0)))) {
      if ((bRam301868 & 0x10) != 0) {
        bRam301868 = bRam301868 & 0xfb;
      }
      if (((PSW & 0x40) == 0) && ((bRam301868 & 0x10) == 0)) {
        if (((bRam301868 & 4) != 0) &&
           ((bRam304e1f < bRam01be48 && (_overboost_rpm_trip < uRam302e38)))) {
          bRam301868 = bRam301868 | 8;
        }
      }
      else {
        bRam301868 = bRam301868 & 0xf7;
      }
    }
  }
  if (((bRam01be46 & 4) != 0) &&
     (((bRam301868 & 0x20) != 0 ||
      (((((bRam301872 & 1) == 0 && (bRam304e1f == 0)) && (bRam01be67 < rpmclass_oppoint)) &&
       (((DAT_00fd34 & 0x10) != 0 || ((bRam01be46 & 8) == 0)))))))) {
    cVar3 = func_0x04238c(0x3e4b,6,nmot_rpmclass,rl_byte);
    if (cVar3 == '\x02') {
      if (cRam301871 == '\0') {
        bRam301870 = bRam301870 | 4;
      }
      else {
        cRam301871 = cRam301871 + -1;
      }
    }
    else {
      uRam019871 = uRam01be6a;
      bRam301870 = bRam301870 & 0xfb;
    }
    if (((bRam301868 & 0x10) == 0) && (cVar3 != '\0')) {
      if ((bRam301870 & 4) != 0) {
        bRam301868 = bRam301868 | 0x20;
      }
    }
    else {
      bRam301868 = bRam301868 & 0xdf;
    }
  }
  if (((bRam01be46 & 4) != 0) || ((bRam01be46 & 2) != 0)) {
    if (((bRam301868 & 8) == 0) && ((bRam301868 & 0x20) == 0)) {
      bRam301868 = bRam301868 & 0xfd;
    }
    else {
      bRam301868 = bRam301868 | 2;
    }
    if ((bRam301868 & 2) == 0) {
      uRam01ae84 = (ushort)bRam01be68;
      bRam301868 = bRam301868 & 0xef;
    }
    else if (sRam302e84 == 0) {
      bRam301868 = bRam301868 | 0x10;
    }
    else {
      sRam302e84 = sRam302e84 + -1;
    }
    if ((((bRam301868 & 0x10) != 0) && ((bRam301870 & 2) == 0)) &&
       (bVar1 = (byte)(bRam304e1f + 1) < bRam304e1f, bVar2 = bRam304e1f == 0xff,
       bRam304e1f = bRam304e1f + 1, bVar1 || bVar2)) {
      bRam304e1f = 0xff;
    }
    if ((bRam301868 & 0x10) == 0) {
      bRam301870 = bRam301870 & 0xfd;
    }
    else {
      bRam301870 = bRam301870 | 2;
    }
  }
  if ((flags_torque_revlimit & 0x80) == 0) {
    bRam301870 = bRam301870 & 0xfe;
  }
  else {
    bRam301870 = bRam301870 | 1;
  }
  return;
}


// ================= ldr_compressor_ratio @ 0d5e80 =================

/* WARNING: Removing unreachable block (ram,0x0d5f5a) */
/* WARNING: Removing unreachable block (ram,0x0d5f3e) */
/* WARNING: Removing unreachable block (ram,0x0d646a) */
/* WARNING: Removing unreachable block (ram,0x0d6452) */
/* WARNING: Removing unreachable block (ram,0x0d6200) */
/* WARNING: Removing unreachable block (ram,0x0d6222) */
/* WARNING: Removing unreachable block (ram,0x0d6aac) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* compressor pressure-ratio calc (KFLDHBN guard) */

void ldr_compressor_ratio(void)

{
  bool bVar1;
  bool bVar2;
  ushort uVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  uint uVar7;
  byte bVar8;
  ushort uVar9;
  ushort uVar10;
  ushort uVar11;
  ushort uVar12;
  short sVar13;
  undefined4 uVar14;
  int iVar15;
  uint uVar16;
  short sVar17;
  
  uVar16 = CONCAT22(MDH,MDL);
  if ((uRam00fd04 & 0x80) != 0) {
    if ((_flags_start_phase & 0x8000) != 0) {
      bVar1 = sRam30beec != -1;
      sRam30beec = sRam30beec + 1;
      sRam30beee = (sRam30beee + 1) - (ushort)bVar1;
      bRam304dd5 = bRam304dd5 + 1;
    }
    if (bRam01baa3 <= bRam304d30) {
      if ((uRam00fd7e & 4) != 0) {
        uVar16 = ((uint)MDH << 0x10) / (uint)uRam30573a;
        bRam304dd8 = (byte)(uVar16 >> 8);
        if (uRam30573a == 0 || 0xffff < uVar16) {
          bRam304dd8 = 0xff;
        }
        uVar16 = (((uint)MDH << 0x10) % (uint)uRam30573a << 0x10) / (uint)uRam30573c;
        MDL = (ushort)uVar16;
        uVar12 = MDL;
        if (uRam30573c == 0 || 0xffff < uVar16) {
          uVar12 = 0xffff;
        }
        bRam304dd9 = (byte)(uVar12 >> 8);
        MDL = MDL / 2;
        uVar10 = MDL;
        uRam307e0e = uRam30573a;
        MDL = MDL / 2;
        MDH = uVar10 % 2;
        uVar12 = MDL + uVar10;
        if (MDL + uVar10 < MDL || MDL + uVar10 < uVar10) {
          uVar12 = 0xffff;
        }
        uRam307e0c = uRam305738;
        uVar16 = ((uint)MDH << 0x10) / (uint)uVar12;
        MDL = (ushort)uVar16;
        MDH = (ushort)(((uint)MDH << 0x10) % (uint)uVar12);
        sVar13 = MDL;
        if (uVar12 == 0 || 0xffff < uVar16) {
          sVar13 = -1;
        }
        bRam304dda = (byte)((ushort)sVar13 >> 8);
        if ((bRam304dd8 == 0xd4 || (short)(bRam304dd8 - 0xd4) < 0) && (0x2a < bRam304dd8)) {
          if (bRam304dd8 < 0x34) {
            bRam304ddb = 0;
          }
          else if ((short)(bRam304dd8 - 0xcc) < 0) {
            bVar8 = bRam304dd8 - 0x33;
            if (bRam304dd8 < 0x33) {
              bVar8 = 0;
            }
            uVar16 = ((uint)bVar8 << 0x10) / 0x99;
            MDL = (ushort)uVar16;
            MDH = (ushort)(((uint)bVar8 << 0x10) % 0x99);
            sVar13 = MDL;
            if (0xffff < uVar16) {
              sVar13 = -1;
            }
            bRam304ddb = (byte)((ushort)sVar13 >> 8);
          }
          else {
            bRam304ddb = 0xff;
          }
          bRam301846 = bRam301846 | 8;
        }
        else {
          bRam301846 = bRam301846 & 0xf7;
        }
        uRam3056a9 = uRam304dd2;
        if ((bRam304dda == 0xd4 || (short)(bRam304dda - 0xd4) < 0) && (0x2a < bRam304dda)) {
          if (bRam304dda < 0x34) {
            uRam304dd2 = uRam01baa0;
          }
          else if ((short)(bRam304dda - 0xcc) < 0) {
            if (((bRam304ddb != 0x99 && -1 < (short)(bRam304ddb - 0x99)) &&
                ((short)(bRam304ddb - 0xbf) < 0)) && (nmot_rpmclass < 100)) {
              bVar8 = bRam304dda - 0x33;
              if (bRam304dda < 0x33) {
                bVar8 = 0;
              }
              uVar16 = ((uint)bVar8 << 0x10) / 0x99;
              MDL = (ushort)uVar16;
              MDH = (ushort)(((uint)bVar8 << 0x10) % 0x99);
              sVar13 = MDL;
              if (0xffff < uVar16) {
                sVar13 = -1;
              }
              uRam304dd2 = (undefined1)((ushort)sVar13 >> 8);
            }
          }
          else {
            uRam304dd2 = uRam01baa1;
          }
          bRam301846 = bRam301846 | 4;
        }
        else {
          bRam301846 = bRam301846 & 0xfb;
        }
        if (((bRam304dd9 < 0x2b) || (bRam304dd9 != 0xd4 && -1 < (short)(bRam304dd9 - 0xd4))) ||
           ((bRam301846 & 4) == 0)) {
          bRam301846 = bRam301846 & 0xfd;
        }
        else {
          if (bRam304dd9 < 0x34) {
            bRam304dd9 = 0x33;
          }
          else if (-1 < (short)(bRam304dd9 - 0xcc)) {
            bRam304dd9 = 0xcc;
          }
          bRam304dc5 = bRam304dc4;
          uVar12 = (ushort)bRam304dda * 0x100 + 0xcccd;
          if ((ushort)bRam304dda * 0x100 < 0x3333) {
            uVar12 = 0;
          }
          if (uVar12 < 0x42) {
            uVar12 = 0x41;
          }
          else {
            uVar12 = (ushort)bRam304dda * 0x100 + 0xcccd;
            if ((ushort)bRam304dda * 0x100 < 0x3333) {
              uVar12 = 0;
            }
          }
          uVar10 = bRam304dd9 - 0x33;
          if (bRam304dd9 < 0x33) {
            uVar10 = 0;
          }
          uVar16 = ((uint)uVar10 << 0x10) / (uint)uVar12;
          uVar10 = (ushort)uVar16;
          if (uVar12 == 0 || 0xffff < uVar16) {
            uVar10 = 0xffff;
          }
          uVar10 = uVar10 >> 1;
          if (0xff < uVar10) {
            uVar10 = 0xff;
          }
          uVar10 = uVar10 & 0xff;
          if (-1 < (short)(uVar10 - 0xb6)) {
            uVar10 = 0xb6;
          }
          uVar12 = uVar10 * 0xb2 >> 7;
          uRam3056a8 = (undefined1)uVar12;
          MDL = (uVar12 & 0xff) * (ushort)bRam01ba9a;
          MDH = 0;
          bRam304dc4 = (byte)(MDL >> 8);
          bRam301846 = bRam301846 | 2;
        }
        MDC = MDC | 0x10;
        if ((((bRam301846 & 8) != 0) && ((bRam301846 & 4) != 0)) && ((bRam301846 & 2) != 0)) {
          sVar13 = (ushort)bRam304dc4 * 0x40;
          sVar17 = 0;
          if ((bRam01ba99 & 1) == 0) {
            uVar12 = func_0x04274a(uRam027db6,0x3db8,9,0x3dc4,9,nmot_rpmclass);
            sVar17 = uVar12 * -0x8000;
            uVar3 = ((short)uVar12 >> 0xf) << 0xf;
            uVar10 = uVar3 | uVar12 >> 1;
            uVar12 = uVar10 + sVar13;
            sVar13 = uVar10 + sVar13;
            if (uVar3 == 0 && (short)uVar12 < 0 != (uVar3 != 0)) {
              if (uVar12 < uVar10) {
                sVar17 = 0;
                sVar13 = -0x8000;
              }
              else {
                sVar17 = -1;
                sVar13 = 0x7fff;
              }
            }
          }
          uVar14 = func_0x0e4078(sVar17,sVar13);
          uVar10 = (ushort)uVar14;
          uVar12 = uVar10 * 2;
          uVar10 = (short)((uint)uVar14 >> 0x10) * 2 +
                   (ushort)(uVar10 * 2 < uVar10 || uVar10 * 2 < uVar10);
          if ((bRam01ba99 & 2) == 0) {
            func_0x04274a(uRam027dd0,0x3dd2,9,0x3dde,9,bRam304ddb);
            iVar15 = func_0x0e4078();
            uVar11 = (ushort)((uint)iVar15 >> 0x10);
            uVar9 = (ushort)iVar15;
            bVar1 = uVar12 < uVar9;
            uVar3 = (ushort)bVar1;
            uVar12 = uVar12 - uVar9;
            bVar2 = uVar10 < uVar11;
            bVar4 = uVar10 == uVar11;
            sVar13 = uVar10 - uVar11;
            bVar5 = (short)uVar10 < 0;
            bVar6 = (short)uVar10 < 0;
            uVar10 = (uVar10 - uVar11) - uVar3;
            if (bVar5 != iVar15 < 0 && (short)(sVar13 - uVar3) < 0 != bVar6) {
              if (bVar2 || bVar4 && bVar1) {
                uVar12 = 0xffff;
                uVar10 = 0x7fff;
              }
              else {
                uVar12 = 0;
                uVar10 = 0x8000;
              }
            }
          }
          uVar16 = func_0x0e4078();
          sVar13 = (short)(uVar16 >> 0x10);
          if (sVar13 == 0) {
            sVar13 = 0;
          }
          else {
            sVar13 = sVar13 * 10;
            MDC = MDC | 0x10;
          }
          iVar15 = (uVar16 & 0xffff) * 10;
          uVar9 = (ushort)iVar15;
          sVar13 = sVar13 + (short)((uint)iVar15 >> 0x10);
          bVar1 = uVar12 + uVar9 < uVar12;
          bVar2 = uVar12 + uVar9 < uVar9;
          uVar3 = (ushort)(bVar1 || bVar2);
          uVar12 = uVar12 + uVar9;
          uVar9 = uVar10 + sVar13;
          sVar17 = uVar10 + sVar13 + uVar3;
          if ((short)uVar10 < 0 == sVar13 < 0 && (short)(uVar9 + uVar3) < 0 != (short)uVar10 < 0) {
            if (uVar9 < uVar10 || uVar9 == 0xffff && (bVar1 || bVar2)) {
              uVar12 = 0;
              sVar17 = -0x8000;
            }
            else {
              uVar12 = 0xffff;
              sVar17 = 0x7fff;
            }
          }
          if (sVar17 < 0) {
            uRam305652 = 0;
          }
          else {
            uVar16 = (uint)(uVar12 >> 0xf | sVar17 << 1) * 3;
            uRam305652 = (undefined2)uVar16;
            if (0xffff < uVar16) {
              uRam305652 = 0xffff;
            }
          }
          MDC = MDC | 0x10;
          bRam304dcb = (byte)((ushort)uRam305652 >> 8);
        }
        MDL = ((ushort)nmot_rpmclass * 0x66) / 0x46;
        MDH = ((ushort)nmot_rpmclass * 0x66) % 0x46;
        MDC = MDC | 0x10;
        if ((((bRam304ddb < bRam01baa7) && (bRam01baa6 < bRam304ddb)) && (bRam01ba9e <= MDL)) &&
           ((MDL <= bRam01ba9f && (uRam027dec <= (ushort)(_vfzg_vehicle_speed * 2))))) {
          bRam304dd3 = *(byte *)((uint3)(bRam30a128 + 0x2134) + 0x308000);
          *(byte *)((uint3)(bRam30a128 + 0x2134) + 0x308000) = bRam304dcb;
          MDL = ((ushort)bRam304dcb << 8) / 10;
          uVar10 = MDL;
          MDL = ((ushort)bRam304dd3 << 8) / 10;
          MDH = ((ushort)bRam304dd3 << 8) % 10;
          MDC = MDC | 0x10;
          uVar12 = uRam30bef6 - MDL;
          if (uRam30bef6 < MDL) {
            uVar12 = 0;
          }
          uRam30bef6 = uVar12 + uVar10;
          if (uVar12 + uVar10 < uVar12 || uVar12 + uVar10 < uVar10) {
            uRam30bef6 = 0xffff;
          }
          if (bRam30a128 == 9) {
            bRam30a128 = 0;
          }
          else {
            bRam30a128 = bRam30a128 + 1;
          }
          uRam302df2 = uRam302df2 | 1;
        }
        else {
          uRam302df2 = uRam302df2 & 0xfffe;
        }
        if (((uRam302df2 & 1) != 0) && (bRam30a128 == 0)) {
          bRam304dd7 = *(byte *)((uint3)(bRam30a127 + 0x213e) + 0x308000);
          bRam304dd6 = (byte)(uRam30bef6 >> 8);
          *(byte *)((uint3)(bRam30a127 + 0x213e) + 0x308000) = bRam304dd6;
          MDL = ((ushort)bRam304dd6 << 8) / 10;
          uVar10 = MDL;
          MDL = ((ushort)bRam304dd7 << 8) / 10;
          MDH = ((ushort)bRam304dd7 << 8) % 10;
          MDC = MDC | 0x10;
          uVar12 = uRam30bef4 - MDL;
          if (uRam30bef4 < MDL) {
            uVar12 = 0;
          }
          uRam30bef4 = uVar12 + uVar10;
          if (uVar12 + uVar10 < uVar12 || uVar12 + uVar10 < uVar10) {
            uRam30bef4 = 0xffff;
          }
          if (bRam30a127 == 9) {
            bRam30a127 = 0;
          }
          else {
            bRam30a127 = bRam30a127 + 1;
          }
        }
        if ((((uRam302df2 & 1) != 0) && (bRam30a128 == 0)) && (bRam30a127 == 0)) {
          bRam304dca = *(byte *)((uint3)(bRam30a126 + 0x2129) + 0x308000);
          bRam304dc9 = (byte)(uRam30bef4 >> 8);
          *(byte *)((uint3)(bRam30a126 + 0x2129) + 0x308000) = bRam304dc9;
          MDL = ((ushort)bRam304dc9 << 8) / 10;
          uVar10 = MDL;
          MDL = ((ushort)bRam304dca << 8) / 10;
          MDH = ((ushort)bRam304dca << 8) % 10;
          MDC = MDC | 0x10;
          uVar12 = uRam30bef2 - MDL;
          if (uRam30bef2 < MDL) {
            uVar12 = 0;
          }
          uRam30bef2 = uVar12 + uVar10;
          if (uVar12 + uVar10 < uVar12 || uVar12 + uVar10 < uVar10) {
            uRam30bef2 = 0xffff;
          }
          if (bRam30a126 == 9) {
            bRam30a126 = 0;
          }
          else {
            bRam30a126 = bRam30a126 + 1;
          }
        }
        bRam304dc8 = (byte)(uRam30bef2 >> 8);
        if ((bRam304dc8 < bRam01ba9b) && (bRam01ba9c <= bRam304dc8)) {
          bVar1 = true;
        }
        else {
          bRam301846 = bRam301846 & 0xdf;
          bVar1 = false;
        }
        bVar2 = bRam304dc8 < bRam01ba9c;
        if (!bVar2) {
          bRam301846 = bRam301846 & 0xbf;
        }
        if (bRam01baa2 < bRam304dc9) {
          bRam301846 = bRam301846 & 0x7f;
        }
        else if ((bVar1) || (bVar2)) {
          bRam301846 = bRam301846 | 0x80;
        }
        if ((bRam301846 & 0x80) == 0) {
          uRam30a133 = 0;
        }
        else if (bVar1) {
          uRam30a133 = 1;
        }
        else if (bVar2) {
          uRam30a133 = 2;
        }
        bRam301846 = bRam301846 & 0x9f;
      }
      uVar10 = me7_lookup_1d_word(0x3c14,9,_vfzg_vehicle_speed);
      uVar12 = MDL;
      if ((uVar10 <= bRam304dd5) && ((uRam00fd7e & 4) != 0)) {
        uRam307e0e = uRam3056a4;
        MDL = MDL / uRam027c70;
        MDH = uVar12 % uRam027c70;
        MDC = MDC | 0x10;
        uRam3056a6 = MDL;
        if (uRam027c70 == 0) {
          uRam3056a6 = 0xffff;
        }
        uVar12 = uRam3056a6 + uRam30bef0;
        bVar1 = uRam3056a6 + uRam30bef0 < uRam30bef0;
        uRam30bef0 = uRam3056a6 + uRam30bef0;
        if (uVar12 < uRam3056a6 || bVar1) {
          uRam30bef0 = 0xffff;
        }
        uVar10 = me7_lookup_1d_word(0x3c46,9,_vfzg_vehicle_speed);
        MDH = MDL;
        uRam307e0e = uRam30569e;
        MDL = MDL / uVar10;
        MDH = MDH % uVar10;
        MDC = MDC | 0x10;
        uVar12 = MDL;
        if (uVar10 == 0) {
          uVar12 = 0xffff;
        }
        uVar10 = uVar12 + uRam3056a2;
        bVar1 = uVar12 + uRam3056a2 < uRam3056a2;
        uRam3056a2 = uVar12 + uRam3056a2;
        if (uVar10 < uVar12 || bVar1) {
          uRam3056a2 = 0xffff;
        }
        uRam3056a4 = 0;
        uRam30569e = 0;
        bRam304dd5 = 0;
      }
      if ((0xd04 < uRam30bed2) && (uRam30bed2 < 0x1389)) {
        uVar12 = uRam30bef0 + uRam3056a2;
        if (uRam30bef0 + uRam3056a2 < uRam30bef0 || uRam30bef0 + uRam3056a2 < uRam3056a2) {
          uVar12 = 0xffff;
        }
        if (((((uRam027dea < uVar12) || ((uRam303b12 & 1) != 0)) || ((uRam303bf2 & 1) != 0)) ||
            ((uRam303ae0 & 1) != 0)) && (bRam01ba99 == 4)) {
          uRam304dc3 = 1;
        }
      }
    }
    uVar16 = CONCAT22(MDH,MDL);
    if ((((_flags_start_phase & 0x4000) != 0) && (uVar16 = CONCAT22(MDH,MDL), (uRam00fd7e & 4) != 0)
        ) && (uVar16 = CONCAT22(MDH,MDL), (_flags_start_phase & 0x8000) == 0)) {
      uVar16 = (uint)(uRam301afa >> 8) * (uint)bRam013802;
      MDL = (ushort)uVar16;
      MDH = 0;
      MDC = MDC | 0x10;
      uVar12 = MDL;
      if (0xffff < uVar16) {
        uVar12 = 0xffff;
      }
      uRam3056aa = (undefined1)(uVar12 >> 8);
      uRam3056ab = uRam3055b9;
      bRam3056ac = (byte)((ushort)sRam30beec >> 0xf) | (byte)(sRam30beee << 1);
      uRam3056ad = uRam306df0;
      uRam3056ae = (undefined1)((ushort)uRam3055d0 >> 8);
      uRam3056af = uRam304dd2;
      bRam3056b0 = bRam304dc4;
      bRam3056b1 = bRam304ddb;
      if ((bRam305846 & 0x10) == 0) {
        func_0x0d5864(0x16aa,0xc1,0x16b2,0xc1,8,8,1);
        func_0x0d5902(0x16aa,0xc1,0x3d7a,9,0x1732,0xc1,1,1,8);
        uVar7 = func_0x0d5b4a(0x16b2,0xc1,0xdd4,0xc1,0xdc2,0xc1,8,8);
        uRam307e0e = uRam305732;
        MDL = MDL / uRam027c44;
        if (uRam027c44 == 0) {
          MDL = 0xffff;
        }
        uVar12 = (ushort)(uVar7 / uRam027c3e);
        uVar16 = CONCAT22((short)(uVar7 % (uint)uRam027c3e),uVar12);
        MDC = MDC | 0x10;
        if (uRam027c3e == 0 || 0xffff < uVar7 / uRam027c3e) {
          uVar12 = 0xffff;
        }
        uVar10 = MDL + uVar12;
        if (MDL + uVar12 < MDL || MDL + uVar12 < uVar12) {
          uVar10 = 0xffff;
        }
        bVar1 = uRam3056a4 + uVar10 < uRam3056a4;
        uVar12 = uRam3056a4 + uVar10;
        uRam3056a4 = uRam3056a4 + uVar10;
        if (bVar1 || uVar12 < uVar10) {
          uRam3056a4 = 0xffff;
        }
        bRam301846 = bRam301846 | 0x10;
        uRam305732 = MDL;
      }
    }
    if (((_flags_start_phase & 0x8000) != 0) && ((uRam00fd7e & 4) != 0)) {
      MDL = (uRam301afa >> 8) * (ushort)bRam013802;
      MDH = 0;
      MDC = MDC | 0x10;
      uRam304dcc = (undefined1)(MDL >> 8);
      uRam304dcd = uRam30740e;
      uRam304dce = uRam3055b9;
      bRam304dcf = bRam304ddb;
      bRam304dd0 = bRam304dc4;
      uRam304dd1 = uRam304dd2;
      func_0x0d59e0(0xdcc,0xc1,0x1656,0xc1,6,6,1);
      func_0x0d5a7e(0xdcc,0xc1,0x3d9c,9,0x1654,0xc1,1,1,6);
      uVar10 = func_0x0d5c28(0x1656,0xc1,0xdd4,0xc1,0xdc2,0xc1,6,6);
      MDH = (ushort)((uint)uVar10 / (uint)uRam027c40);
      uVar12 = MDH;
      if (uRam027c40 == 0 || 0xffff < (uint)uVar10 / (uint)uRam027c40) {
        uVar12 = 0xffff;
      }
      uRam307e0e = uRam305654;
      MDL = MDH / uRam027c42;
      MDH = MDH % uRam027c42;
      uVar16 = CONCAT22(MDH,MDL);
      MDC = MDC | 0x10;
      if (uRam027c42 == 0) {
        MDL = 0xffff;
      }
      uVar12 = uVar12 + MDL;
      bVar1 = uRam30569e + uVar12 < uRam30569e;
      uVar10 = uRam30569e + uVar12;
      uRam30569e = uRam30569e + uVar12;
      uRam305654 = MDL;
      if (bVar1 || uVar10 < uVar12) {
        uRam30569e = 0xffff;
      }
    }
  }
  MDH = (ushort)(uVar16 >> 0x10);
  MDL = (ushort)uVar16;
  return;
}


// ================= ign_base_advance @ 0518b8 =================

/* WARNING: Removing unreachable block (ram,0x051986) */
/* WARNING: Removing unreachable block (ram,0x0518ee) */
/* WARNING: Removing unreachable block (ram,0x0519f2) */
/* base ignition advance (KFZW1-4, cam-phase blend) */

void ign_base_advance(void)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  char cVar5;
  char cVar6;
  short sVar7;
  short sVar8;
  ushort uVar9;
  int iVar4;
  
  cVar5 = me7_lookup_2d_sbyte_bilinear(0x33b1,0x502a,uRam3019b6,uRam3019ca);
  sVar7 = (short)cVar5;
  cVar5 = me7_lookup_2d_sbyte_bilinear(0x3471,0x502a,uRam3019b6,uRam3019ca);
  sVar8 = (short)cVar5 * (ushort)wnwise;
  uVar9 = 0xff - wnwise;
  if ((short)uVar9 < 0) {
    iVar3 = (int)sVar7 * (int)(short)(uVar9 & 0x7fff);
    sVar7 = (short)iVar3 + sVar7 * -0x8000;
  }
  else {
    iVar3 = (int)sVar7 * (int)(short)uVar9;
    sVar7 = (short)iVar3;
  }
  MDH = (undefined2)((uint)iVar3 >> 0x10);
  MDL = (undefined2)iVar3;
  MDC = MDC | 0x10;
  sRam3024a8 = sVar7 + sVar8;
  if (sVar7 < 0 == sVar8 < 0 && sVar7 + sVar8 < 0 != sVar7 < 0) {
    sRam3024a8 = 0x7fff;
  }
  cVar5 = me7_lookup_2d_sbyte_bilinear(0x3531,0x502a,uRam3019b6,uRam3019ca);
  sVar7 = (short)cVar5;
  cVar5 = me7_lookup_2d_sbyte_bilinear(0x35f1,0x502a,uRam3019b6,uRam3019ca);
  sVar8 = (short)cVar5 * (ushort)wnwise;
  uVar9 = 0xff - wnwise;
  if ((short)uVar9 < 0) {
    sVar7 = sVar7 * (uVar9 & 0x7fff) + sVar7 * -0x8000;
  }
  else {
    sVar7 = sVar7 * uVar9;
  }
  sRam3024aa = sVar7 + sVar8;
  if (sVar7 < 0 == sVar8 < 0 && sVar7 + sVar8 < 0 != sVar7 < 0) {
    sRam3024aa = 0x7fff;
  }
  uVar9 = (ushort)((int)sRam3024aa * (int)(short)(ushort)wnwisa) >> 8 |
          (short)((uint)((int)sRam3024aa * (int)(short)(ushort)wnwisa) >> 0x10) << 8;
  uVar1 = 0xff - wnwisa;
  if ((short)uVar1 < 0) {
    iVar4 = (int)sRam3024a8 * (int)(short)(uVar1 & 0x7fff);
    uVar2 = (ushort)iVar4;
    uVar1 = sRam3024a8 * -0x8000;
    iVar3 = CONCAT22((short)((uint)iVar4 >> 0x10) + (sRam3024a8 >> 1) +
                     (ushort)(uVar2 + uVar1 < uVar2 || uVar2 + uVar1 < uVar1),uVar2 + uVar1);
  }
  else {
    iVar3 = (int)sRam3024a8 * (int)(short)uVar1;
    iVar4 = iVar3;
  }
  MDH = (undefined2)((uint)iVar4 >> 0x10);
  MDL = (undefined2)iVar4;
  MDC = MDC | 0x10;
  uVar1 = (ushort)iVar3 >> 8 | (short)((uint)iVar3 >> 0x10) << 8;
  uRam3024ac = uVar1 + uVar9;
  if ((short)uVar1 < 0 == (short)uVar9 < 0 && (short)(uVar1 + uVar9) < 0 != (short)uVar1 < 0) {
    uRam3024ac = 0x7fff;
  }
  uVar9 = uRam3024ac;
  if ((short)uRam3024ac < 0) {
    if (uRam3024ac == 0x8000) {
      uVar9 = 0x7fff;
    }
    else {
      uVar9 = -uRam3024ac;
    }
  }
  sVar7 = (short)uVar9 >> 8;
  if ((((uVar9 & 0x80) == 0) ||
      (sVar8 = sVar7 + 1, sVar7 + -0x7e < 0 == (sVar7 < 0 && sVar7 + -0x7e < 0 != sVar7 < 0))) ||
     (sVar8 == -0x80 || sVar7 + 0x81 < 0 != (-1 < sVar8 && sVar7 + 0x81 < 0 != sVar8 < 0))) {
    sVar8 = sVar7;
  }
  cRam30132f = (char)sVar8;
  if ((short)uRam3024ac < 0) {
    cRam30132f = -cRam30132f;
  }
  cVar5 = cRam3012fd + cRam3012fe;
  if (cRam3012fd < '\0' == cRam3012fe < '\0' &&
      (char)(cRam3012fd + cRam3012fe) < '\0' != cRam3012fd < '\0') {
    cVar5 = '\x7f';
  }
  cVar6 = cVar5 + cRam304050;
  if (cVar5 < '\0' == cRam304050 < '\0' && (char)(cVar5 + cRam304050) < '\0' != cVar5 < '\0') {
    cVar6 = '\x7f';
  }
  zwbas = cVar6 + cRam30132f;
  if (cVar6 < '\0' == cRam30132f < '\0' && (char)(cVar6 + cRam30132f) < '\0' != cVar6 < '\0') {
    zwbas = '\x7f';
  }
  return;
}


// ================= ign_apply_knock_retard @ 05086a =================

/* subtract global + per-cyl knock retard */

void ign_apply_knock_retard(void)

{
  short sVar1;
  ushort uVar2;
  short sVar3;
  
  sVar1 = ((short)zwbas + (short)cRam30157c + (short)cRam3014f6 + (short)cRam012d85) -
          (ushort)wkr_global;
  uVar2 = (ushort)bRam30125d;
  if ((uRam00fd24 & 0x4000) == 0) {
    sVar3 = (short)cRam30131d + (short)cRam3014f6 + (short)cRam012d85;
  }
  else {
    sVar3 = sVar1 + *(char *)((uint3)uVar2 + 0x301545);
  }
  if (sVar3 == 0x7f || sVar3 + -0x7f < 0 != (sVar3 < 0 && sVar3 + -0x7f < 0 != sVar3 < 0)) {
    if (sVar3 + 0x80 < 0 == (-1 < sVar3 && sVar3 + 0x80 < 0 != sVar3 < 0)) {
      uRam019313 = (undefined1)sVar3;
    }
    else {
      uRam019313 = 0x80;
    }
  }
  else {
    uRam019313 = 0x7f;
  }
  uRam00f337 = uRam019313;
  if (uVar2 < 4) {
    uVar2 = uVar2 + 1;
  }
  else {
    uVar2 = 0;
  }
  sVar3 = sVar1 + *(char *)((uint3)uVar2 + 0x301545);
  if (sVar3 == 0x7f || sVar3 + -0x7f < 0 != (sVar3 < 0 && sVar3 + -0x7f < 0 != sVar3 < 0)) {
    if (sVar3 + 0x80 < 0 == (-1 < sVar3 && sVar3 + 0x80 < 0 != sVar3 < 0)) {
      uRam019314 = (undefined1)sVar3;
    }
    else {
      uRam019314 = 0x80;
    }
  }
  else {
    uRam019314 = 0x7f;
  }
  if (uVar2 < 4) {
    uVar2 = uVar2 + 1;
  }
  else {
    uVar2 = 0;
  }
  sVar3 = sVar1 + *(char *)((uint3)uVar2 + 0x301545);
  if (sVar3 == 0x7f || sVar3 + -0x7f < 0 != (sVar3 < 0 && sVar3 + -0x7f < 0 != sVar3 < 0)) {
    if (sVar3 + 0x80 < 0 == (-1 < sVar3 && sVar3 + 0x80 < 0 != sVar3 < 0)) {
      uRam019315 = (undefined1)sVar3;
    }
    else {
      uRam019315 = 0x80;
    }
  }
  else {
    uRam019315 = 0x7f;
  }
  if (uVar2 < 4) {
    uVar2 = uVar2 + 1;
  }
  else {
    uVar2 = 0;
  }
  sVar1 = sVar1 + *(char *)((uint3)uVar2 + 0x301545);
  if (sVar1 == 0x7f || sVar1 + -0x7f < 0 != (sVar1 < 0 && sVar1 + -0x7f < 0 != sVar1 < 0)) {
    if (sVar1 + 0x80 < 0 == (-1 < sVar1 && sVar1 + 0x80 < 0 != sVar1 < 0)) {
      uRam019316 = (undefined1)sVar1;
    }
    else {
      uRam019316 = 0x80;
    }
  }
  else {
    uRam019316 = 0x7f;
  }
  return;
}


// ================= ign_final_spark_out @ 050984 =================

/* final per-cylinder spark output (zwout) */

void ign_final_spark_out(void)

{
  char cVar1;
  
  if ((flags_torque_revlimit & 0x80) != 0) {
    flags_torque_revlimit = flags_torque_revlimit | 0x1000;
  }
  if ((flags_torque_revlimit & 0x1000) != 0) {
    cRam00f338 = cRam301329;
    bRam019317 = cRam301329 + cRam301312;
    if (cRam301329 < '\0' == cRam301312 < '\0' &&
        (char)(cRam301329 + cRam301312) < '\0' != cRam301329 < '\0') {
      bRam019317 = 0x7f;
    }
    if (bRam019317 == 0x50 ||
        (char)(bRam019317 + 0xb0) < '\0' !=
        ((char)bRam019317 < '\0' && (char)(bRam019317 + 0xb0) < '\0' != (char)bRam019317 < '\0')) {
      if ((char)(bRam019317 + 0x20) < '\0' !=
          (-1 < (char)bRam019317 && (char)(bRam019317 + 0x20) < '\0' != (char)bRam019317 < '\0')) {
        bRam019317 = 0xe0;
      }
    }
    else {
      bRam019317 = 0x50;
    }
    bRam019318 = bRam019317;
    bRam019319 = bRam019317;
    bRam01931a = bRam019317;
    goto LAB_050b7c;
  }
  if (((uRam00fd04 & 2) == 0) && ((flags_torque_revlimit & 0x4000) == 0)) {
    cVar1 = cRam301329;
    if ((char)(cRam301320 - cRam301329) < '\0' ==
        (cRam301320 < '\0' != cRam301329 < '\0' &&
        (char)(cRam301320 - cRam301329) < '\0' != cRam301320 < '\0')) {
      cVar1 = cRam301320;
    }
    if (cVar1 == cRam009313 ||
        (char)(cVar1 - cRam009313) < '\0' !=
        (cVar1 < '\0' != cRam009313 < '\0' && (char)(cVar1 - cRam009313) < '\0' != cVar1 < '\0')) {
      bRam019317 = cVar1 + cRam301312;
      cRam00f338 = cVar1;
      if (cVar1 < '\0' == cRam301312 < '\0' && (char)(cVar1 + cRam301312) < '\0' != cVar1 < '\0') {
        bRam019317 = 0x7f;
      }
    }
    else {
      cRam00f338 = cRam019313;
      bRam019317 = cRam019313 + cRam301312;
      if (cRam019313 < '\0' == cRam301312 < '\0' &&
          (char)(cRam019313 + cRam301312) < '\0' != cRam019313 < '\0') {
        bRam019317 = 0x7f;
      }
    }
    if (bRam019317 == 0x50 ||
        (char)(bRam019317 + 0xb0) < '\0' !=
        ((char)bRam019317 < '\0' && (char)(bRam019317 + 0xb0) < '\0' != (char)bRam019317 < '\0')) {
      if ((char)(bRam019317 + 0x20) < '\0' !=
          (-1 < (char)bRam019317 && (char)(bRam019317 + 0x20) < '\0' != (char)bRam019317 < '\0')) {
        bRam019317 = 0xe0;
      }
    }
    else {
      bRam019317 = 0x50;
    }
    if (cVar1 == cRam009314 ||
        (char)(cVar1 - cRam009314) < '\0' !=
        (cVar1 < '\0' != cRam009314 < '\0' && (char)(cVar1 - cRam009314) < '\0' != cVar1 < '\0')) {
      bRam019318 = cVar1 + cRam301312;
      if (cVar1 < '\0' == cRam301312 < '\0' && (char)(cVar1 + cRam301312) < '\0' != cVar1 < '\0') {
        bRam019318 = 0x7f;
      }
    }
    else {
      bRam019318 = cRam019314 + cRam301312;
      if (cRam019314 < '\0' == cRam301312 < '\0' &&
          (char)(cRam019314 + cRam301312) < '\0' != cRam019314 < '\0') {
        bRam019318 = 0x7f;
      }
    }
    if (bRam019318 == 0x50 ||
        (char)(bRam019318 + 0xb0) < '\0' !=
        ((char)bRam019318 < '\0' && (char)(bRam019318 + 0xb0) < '\0' != (char)bRam019318 < '\0')) {
      if ((char)(bRam019318 + 0x20) < '\0' !=
          (-1 < (char)bRam019318 && (char)(bRam019318 + 0x20) < '\0' != (char)bRam019318 < '\0')) {
        bRam019318 = 0xe0;
      }
    }
    else {
      bRam019318 = 0x50;
    }
    if (cVar1 == cRam009315 ||
        (char)(cVar1 - cRam009315) < '\0' !=
        (cVar1 < '\0' != cRam009315 < '\0' && (char)(cVar1 - cRam009315) < '\0' != cVar1 < '\0')) {
      bRam019319 = cVar1 + cRam301312;
      if (cVar1 < '\0' == cRam301312 < '\0' && (char)(cVar1 + cRam301312) < '\0' != cVar1 < '\0') {
        bRam019319 = 0x7f;
      }
    }
    else {
      bRam019319 = cRam019315 + cRam301312;
      if (cRam019315 < '\0' == cRam301312 < '\0' &&
          (char)(cRam019315 + cRam301312) < '\0' != cRam019315 < '\0') {
        bRam019319 = 0x7f;
      }
    }
    if (bRam019319 == 0x50 ||
        (char)(bRam019319 + 0xb0) < '\0' !=
        ((char)bRam019319 < '\0' && (char)(bRam019319 + 0xb0) < '\0' != (char)bRam019319 < '\0')) {
      if ((char)(bRam019319 + 0x20) < '\0' !=
          (-1 < (char)bRam019319 && (char)(bRam019319 + 0x20) < '\0' != (char)bRam019319 < '\0')) {
        bRam019319 = 0xe0;
      }
    }
    else {
      bRam019319 = 0x50;
    }
    if (cVar1 == cRam009316 ||
        (char)(cVar1 - cRam009316) < '\0' !=
        (cVar1 < '\0' != cRam009316 < '\0' && (char)(cVar1 - cRam009316) < '\0' != cVar1 < '\0'))
    goto LAB_050b5c;
    bRam01931a = cRam019316 + cRam301312;
    if (cRam019316 < '\0' == cRam301312 < '\0' &&
        (char)(cRam019316 + cRam301312) < '\0' != cRam019316 < '\0') {
      bRam01931a = 0x7f;
    }
  }
  else {
    cRam00f338 = cRam019313;
    bRam019317 = cRam019313 + cRam301312;
    if (cRam019313 < '\0' == cRam301312 < '\0' &&
        (char)(cRam019313 + cRam301312) < '\0' != cRam019313 < '\0') {
      bRam019317 = 0x7f;
    }
    if (bRam019317 == 0x50 ||
        (char)(bRam019317 + 0xb0) < '\0' !=
        ((char)bRam019317 < '\0' && (char)(bRam019317 + 0xb0) < '\0' != (char)bRam019317 < '\0')) {
      if ((char)(bRam019317 + 0x20) < '\0' !=
          (-1 < (char)bRam019317 && (char)(bRam019317 + 0x20) < '\0' != (char)bRam019317 < '\0')) {
        bRam019317 = 0xe0;
      }
    }
    else {
      bRam019317 = 0x50;
    }
    bRam019318 = cRam019314 + cRam301312;
    if (cRam019314 < '\0' == cRam301312 < '\0' &&
        (char)(cRam019314 + cRam301312) < '\0' != cRam019314 < '\0') {
      bRam019318 = 0x7f;
    }
    if (bRam019318 == 0x50 ||
        (char)(bRam019318 + 0xb0) < '\0' !=
        ((char)bRam019318 < '\0' && (char)(bRam019318 + 0xb0) < '\0' != (char)bRam019318 < '\0')) {
      if ((char)(bRam019318 + 0x20) < '\0' !=
          (-1 < (char)bRam019318 && (char)(bRam019318 + 0x20) < '\0' != (char)bRam019318 < '\0')) {
        bRam019318 = 0xe0;
      }
    }
    else {
      bRam019318 = 0x50;
    }
    bRam019319 = cRam019315 + cRam301312;
    if (cRam019315 < '\0' == cRam301312 < '\0' &&
        (char)(cRam019315 + cRam301312) < '\0' != cRam019315 < '\0') {
      bRam019319 = 0x7f;
    }
    cVar1 = cRam019316;
    if (bRam019319 == 0x50 ||
        (char)(bRam019319 + 0xb0) < '\0' !=
        ((char)bRam019319 < '\0' && (char)(bRam019319 + 0xb0) < '\0' != (char)bRam019319 < '\0')) {
      if ((char)(bRam019319 + 0x20) < '\0' !=
          (-1 < (char)bRam019319 && (char)(bRam019319 + 0x20) < '\0' != (char)bRam019319 < '\0')) {
        bRam019319 = 0xe0;
      }
    }
    else {
      bRam019319 = 0x50;
    }
LAB_050b5c:
    bRam01931a = cVar1 + cRam301312;
    if (cVar1 < '\0' == cRam301312 < '\0' && (char)(cVar1 + cRam301312) < '\0' != cVar1 < '\0') {
      bRam01931a = 0x7f;
    }
  }
  if (bRam01931a == 0x50 ||
      (char)(bRam01931a + 0xb0) < '\0' !=
      ((char)bRam01931a < '\0' && (char)(bRam01931a + 0xb0) < '\0' != (char)bRam01931a < '\0')) {
    if ((char)(bRam01931a + 0x20) < '\0' !=
        (-1 < (char)bRam01931a && (char)(bRam01931a + 0x20) < '\0' != (char)bRam01931a < '\0')) {
      bRam01931a = 0xe0;
    }
  }
  else {
    bRam01931a = 0x50;
  }
LAB_050b7c:
  if (cRam00f338 == cRam301313) {
    flags_torque_revlimit = flags_torque_revlimit | 0x800;
    bRam00f339 = bRam00f339 | (byte)(1 << (ushort)bRam30125d);
  }
  else {
    flags_torque_revlimit = flags_torque_revlimit & 0xf7ff;
    bRam00f339 = bRam00f339 & ~(byte)(1 << (ushort)bRam30125d);
  }
  if (bRam30125d == 0) {
    bRam30131c = bRam019317;
  }
  bRam30131b = ~bRam019317;
  bRam00f33a = bRam019317;
  return;
}


// ================= ign_scheduler @ 050bc6 =================

/* ignition scheduler */

void ign_scheduler(void)

{
  int iVar1;
  short sVar2;
  ushort uVar3;
  
  sVar2 = func_0x040b3e(0x2d87,rpmclass_oppoint);
  uVar3 = me7_lookup_2d_misc(uRam015aca,0x5acc,uRam015acb,0x5ad4,0x5ae4,uRam301839,nmot_w);
  iVar1 = (uint)uVar3 * (uint)(ushort)(sVar2 << 8);
  MDL = (undefined2)iVar1;
  MDH = (ushort)((uint)iVar1 >> 0x10);
  MDC = MDC | 0x10;
  uRam30249c = MDH * 2;
  if (MDH * 2 < MDH) {
    uRam30249c = 0xffff;
  }
  if (uRam30249c < 300) {
    uRam30249c = 300;
  }
  uRam30249e = FUN_042c1c(uRam30249c,1000,800);
  flags_torque_revlimit = flags_torque_revlimit & 0xdfff;
  uRam00f33c = 0;
  return;
}


// ================= knock_build_retard @ 07ba8c =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* build global knock retard */

void knock_build_retard(void)

{
  short sVar1;
  ushort uVar2;
  ushort uVar3;
  
  sRam3028d0 = sRam3028d6;
  sRam3028d8 = sRam3028d6;
  if (nmot_rpmclass < bRam019582) {
    uVar2 = bRam019582 - 3;
    uVar3 = (ushort)nmot_rpmclass;
    if ((uVar3 == uVar2 ||
         (short)(uVar3 - uVar2) < 0 != ((short)uVar2 < 0 && (short)(uVar3 - uVar2) < 0)) ||
       ((uRam00fd44 & 0x400) == 0)) {
      if (cRam019570 == '\x01') {
        sRam3028d0 = sRam302dac;
      }
      else {
        sRam3028d0 = sRam00f408;
      }
      uRam00fd44 = uRam00fd44 & 0xfbff;
      goto LAB_07bb3a;
    }
  }
  if ((uRam00fd44 & 0x400) == 0) {
    if (cRam019570 == '\x01') {
      sRam3028d6 = _rl_w;
      sRam3028d0 = sRam302dac;
    }
    else {
      sRam3028d6 = sRam302a94;
      sRam3028d0 = sRam00f408;
    }
  }
  else {
    if (cRam019570 == '\x01') {
      sRam3028d6 = _rl_w;
    }
    else {
      sRam3028d6 = sRam302a94;
    }
    sRam3028d0 = sRam3028d6 - sRam3028d0;
  }
  uRam00fd44 = uRam00fd44 | 0x400;
LAB_07bb3a:
  if ((uRam00fd44 & 0x40) != 0) {
    if ((uRam00fd44 & 0x4000) == 0) {
      bRam301570 = bRam301570 & 0xfb;
    }
    else {
      bRam301570 = bRam301570 | 4;
    }
    if ((_flags_idle_state & 1) == 0) {
      bRam301570 = bRam301570 & 0xfd;
    }
    else {
      bRam301570 = bRam301570 | 2;
    }
    if ((sRam3028d0 - sRam3028d4 < 0 ==
         (sRam3028d0 < 0 != sRam3028d4 < 0 && sRam3028d0 - sRam3028d4 < 0 != sRam3028d0 < 0)) &&
       ((uRam00fd1c & 0x2000) == 0)) {
      uRam00f3fb = uRam3006cd;
      uRam00f3fc = uRam3006cc;
      _flags_idle_state = _flags_idle_state | 1;
      uRam00fd44 = uRam00fd44 | 0x2000;
      DAT_00fd42 = DAT_00fd42 | 0x1000;
    }
    if ((_flags_idle_state & 4) == 0) {
      bRam301570 = bRam301570 & 0xfe;
    }
    else {
      bRam301570 = bRam301570 | 1;
    }
    if (((((bRam019571 & 4) == 0) || (gear_index != '\0')) && ((bRam019571 & 4) != 0)) ||
       (((((bRam019571 & 2) == 0 || ((uRam00fd44 & 0x2000) == 0)) &&
         (((bRam019571 & 2) != 0 || ((_flags_idle_state & 1) == 0)))) ||
        (((DAT_00fd4e & 0x400) == 0 && ((uRam00fd66 & 8) == 0)))))) {
      _flags_idle_state = _flags_idle_state & 0xfffb;
      if ((bRam301570 & 1) != 0) {
        bRam301572 = 0;
      }
    }
    else {
      _flags_idle_state = _flags_idle_state | 4;
      bRam301572 = func_0x042046(0x1572,6,uRam3019ae);
    }
    if (((((sRam3028d0 - sRam3028d4 < 0 ==
            (sRam3028d0 < 0 != sRam3028d4 < 0 && sRam3028d0 - sRam3028d4 < 0 != sRam3028d0 < 0)) &&
          ((uRam00fd1c & 0x2000) == 0)) && (bRam0139bd < rpmclass_oppoint)) &&
        ((DAT_00fd42 & 0x4000) == 0)) &&
       ((((_flags_idle_state & 4) == 0 && ((bRam019571 & 1) != 0)) || ((bRam019571 & 1) == 0)))) {
      uRam00fd44 = uRam00fd44 | 0x4000;
      bRam3006d1 = bRam3006d1 | 1;
    }
    else {
      bRam3006d1 = bRam3006d1 & 0xfe;
    }
    if (((uRam00fd44 & 0x4000) == 0) ||
       (((bRam301570 & 4) != 0 && (((_flags_idle_state & 1) == 0 || ((bRam301570 & 2) != 0)))))) {
      bRam3006d1 = bRam3006d1 & 0xfd;
    }
    else {
      bRam3006d1 = bRam3006d1 | 2;
      bRam3006d8 = bRam30155c;
      bRam301571 = *(byte *)((uint3)bRam30155c + 0x30324c);
    }
    if ((((bRam3006d1 & 2) != 0) ||
        ((_flags_idle_state & 4) >> 2 != (ushort)((bRam301570 & 1) != 0))) &&
       (wkr_global = bRam301571 + bRam301572,
       (byte)(bRam301571 + bRam301572) < bRam301571 || (byte)(bRam301571 + bRam301572) < bRam301572)
       ) {
      wkr_global = -1;
    }
    if ((bRam3006d1 & 2) != 0) {
      uRam301573 = uRam0139ba;
    }
    if (((bRam3006d1 & 1) != 0) &&
       (sVar1 = sRam3028d4 + sRam3028d2,
       sVar1 == sRam3028d0 ||
       sVar1 - sRam3028d0 < 0 !=
       (sVar1 < 0 != sRam3028d0 < 0 && sVar1 - sRam3028d0 < 0 != sVar1 < 0))) {
      uRam00fd44 = uRam00fd44 | 0x8000;
    }
    if (sRam302b08 - sRam3028da < 0 ==
        (sRam302b08 < 0 != sRam3028da < 0 && sRam302b08 - sRam3028da < 0 != sRam302b08 < 0)) {
      uRam00f3fd = uRam3006d0;
      _flags_idle_state = _flags_idle_state | 2;
    }
  }
  return;
}


// ================= knock_event_handler @ 07bd04 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* per-cylinder knock-event retard accumulator */

ushort knock_event_handler(void)

{
  bool bVar1;
  ushort uVar2;
  uint uVar3;
  ushort uVar4;
  
  uVar3 = uRam3006d4;
  if ((_flags_idle_state & 1) == 0) {
    uVar4 = (ushort)wkr_global;
    if (wkr_global == 0) {
      uRam00fd44 = uRam00fd44 & 0x3fff;
      uRam301571 = 0;
    }
    else {
      cRam301573 = cRam301573 + -1;
      if (cRam301573 == '\0') {
        bVar1 = wkr_global < bRam0139b8;
        wkr_global = wkr_global - bRam0139b8;
        if (bVar1) {
          wkr_global = 0;
        }
        uVar4 = (ushort)wkr_global;
        cRam301573 = cRam0139ba;
        if (wkr_global == 0) {
          uRam00fd44 = uRam00fd44 & 0x3fff;
          uRam301571 = 0;
        }
      }
    }
  }
  else {
    if (bRam301518 == 0) {
      bRam00f3fb = bRam00f3fb - 1;
    }
    uVar4 = (ushort)bRam00f3fb;
    if (bRam00f3fb == 0) {
      if ((uRam00fd44 & 0x4000) != 0) {
        if ((uRam00fd44 & 0x1000) == 0) {
          if (((uRam00fd44 & 0x800) == 0) && ((uRam00fd44 & 0x8000) != 0)) {
            uRam3006d2 = uRam00f400 + uRam00f3fe;
            if (uRam00f400 + uRam00f3fe < uRam00f400 || uRam00f400 + uRam00f3fe < uRam00f3fe) {
              uRam3006d2 = 0xffff;
            }
            if (uRam00f400 == 0) {
              uRam3006ca = 0xff;
              uRam301574 = 0xff;
            }
            else {
              uRam3006d4 = (uint)uRam00f3fe * 0xff;
              MDL = (ushort)(uRam3006d4 / uRam3006d2);
              MDH = (undefined2)(uRam3006d4 % (uint)uRam3006d2);
              MDC = MDC | 0x10;
              uRam3006ca = MDL;
              if (uRam3006d2 == 0 || 0xffff < uRam3006d4 / uRam3006d2) {
                uRam3006ca = 0xffff;
              }
              if (uRam3006ca < 0x100) {
                uRam301574 = (undefined1)uRam3006ca;
              }
              else {
                uRam301574 = 0xff;
              }
            }
            uVar4 = (ushort)bRam0139bc;
            if (uVar4 <= uRam3006ca) {
              uVar2 = bRam3006d8 + 0xb24c;
              if (*(char *)((uint3)uVar2 + 0x10000) == '\0') {
                uVar4 = 0;
              }
              else {
                *(char *)((uint3)uVar2 + 0x10000) = *(char *)((uint3)uVar2 + 0x10000) + -1;
                uVar4 = (ushort)*(byte *)((uint3)uVar2 + 0x10000);
                if (*(byte *)((uint3)uVar2 + 0x10000) < bRam0139b9) {
                  *(byte *)((uint3)uVar2 + 0x10000) = bRam0139b9;
                }
              }
            }
          }
        }
        else {
          uVar2 = bRam3006d8 + 0xb24c;
          *(char *)((uint3)uVar2 + 0x10000) = *(char *)((uint3)uVar2 + 0x10000) + cRam0139b7;
          uVar4 = (ushort)*(byte *)((uint3)uVar2 + 0x10000);
          if (bRam0139b6 < *(byte *)((uint3)uVar2 + 0x10000)) {
            *(byte *)((uint3)uVar2 + 0x10000) = bRam0139b6;
          }
        }
        uRam00fd44 = uRam00fd44 & 0xe7ff;
      }
      _flags_idle_state = _flags_idle_state & 0xfffe;
      uRam00f3fe = 0;
      uRam00f400 = 0;
      bRam00f3fb = 0;
      uVar3 = uRam3006d4;
    }
    else if ((uRam00fd44 & 0x4000) != 0) {
      if ((uRam00fd44 & 0x8000) != 0) {
        if ((uRam00fd44 & 0x100) == 0) {
          uRam00f400 = uRam00f400 + 1;
        }
        else {
          uRam00f3fe = uRam00f3fe + 1;
        }
      }
      if ((DAT_00fd42 & 0x200) != 0) {
        MDL = (ushort)*(byte *)((uint3)bRam301518 + 0x30151c) * (ushort)bRam0139bb;
        MDH = 0;
        MDC = MDC | 0x10;
        uVar4 = MDL >> 4;
        uRam3006ce = MDL;
        if (bRam00f3ed < (byte)uVar4) {
          uRam00fd44 = uRam00fd44 | 0x800;
        }
        else {
          uRam00fd44 = uRam00fd44 | 0x1000;
        }
      }
    }
  }
  uRam3006d4._2_2_ = (undefined2)(uVar3 >> 0x10);
  uRam3006d4._0_2_ = (undefined2)uVar3;
  if ((_flags_idle_state & 2) != 0) {
    if (bRam301518 == 0) {
      bRam00f3fd = bRam00f3fd - 1;
    }
    uVar4 = (ushort)bRam00f3fd;
    if (bRam00f3fd == 0) {
      _flags_idle_state = _flags_idle_state & 0xfffd;
    }
  }
  if ((uRam00fd44 & 0x2000) != 0) {
    if (bRam301518 == 0) {
      bRam00f3fc = bRam00f3fc - 1;
    }
    uVar4 = (ushort)bRam00f3fc;
    if (bRam00f3fc == 0) {
      uRam00fd44 = uRam00fd44 & 0xdfff;
    }
  }
  return uVar4;
}


// ================= fuel_lamfa_request @ 0894c0 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* driver-requested lambda (LAMFA) */

void fuel_lamfa_request(void)

{
  uint uVar1;
  uint uVar2;
  ushort uVar3;
  ushort uVar4;
  
  if ((_flags_start_phase & 0x8000) == 0) {
    sRam30299a = (ushort)bRam304760 << 8;
  }
  else {
    sRam30299a = me7_fraction_blend(uRam02381c,bRam304760,uRam30699a);
  }
  uRam3047a8 = sRam30299a._1_1_;
  uRam305268 = me7_lookup_1d_word(0x37fa,8,sRam30299a._1_1_);
  uRam3029a6 = func_0x042464(uRam02380c,0x380d,8,0x3812,8,uRam30583b);
  _lamfa_w = me7_lookup_1d_word(0x37e4,8,uRam304e27);
  uVar4 = uRam01655e;
  if ((uRam00fd4a & 1) == 0) {
    uVar4 = uRam01655c;
  }
  uVar1 = CONCAT22(uRam302986 >> 10,uRam302986 << 6);
  uVar2 = uVar1 / uVar4;
  uVar3 = (ushort)uVar2;
  MDL = uVar3;
  MDH = (short)(uVar1 % (uint)uVar4);
  MDC = MDC | 0x10;
  if (uVar4 == 0 || 0xffff < uVar2) {
    uVar3 = 0xffff;
  }
  if (0xfe < uVar3) {
    uVar3 = 0xff;
  }
  uRam3047a9 = (char)uVar3;
  return;
}


// ================= fuel_lambda_multiplier @ 08981c =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* lambda closed-loop -> commanded fuel multiplier */

void fuel_lambda_multiplier(void)

{
  short sVar1;
  int iVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  
  if ((bRam019c37 & 1) == 0) {
    iVar2 = (uint)uRam00f476 * (uint)bRam3014ee * 0x100;
    uVar3 = (ushort)((uint)iVar2 >> 0x10);
    uVar5 = uVar3 * 2;
    if (uVar3 * 2 < uVar3) {
      uVar5 = 0xffff;
    }
  }
  else {
    iVar2 = (uint)uRam0237f4 * (uint)bRam3014ee * 0x100;
    uVar3 = (ushort)((uint)iVar2 >> 0x10);
    uVar5 = uVar3 * 2;
    if (uVar3 * 2 < uVar3) {
      uVar5 = 0xffff;
    }
  }
  MDH = (ushort)((uint)iVar2 >> 0x10);
  MDL = (ushort)iVar2;
  MDC = MDC | 0x10;
  sRam305258 = uRam30561e - uVar5;
  if (uRam30561e < uVar5) {
    if (sRam305258 >= 0) {
      sRam305258 = -0x8000;
    }
  }
  else if (sRam305258 < 0) {
    sRam305258 = 0x7fff;
  }
  sRam305258 = sRam305258 >> 1;
  uVar3 = uRam302e38;
  if ((bRam019c36 & 1) != 0) {
    _fr_w = me7_pt1_integrator(uRam02381e,uRam022e34,fr_w_2,_fr_w);
    iVar2 = CONCAT22(MDH,MDL);
    uVar3 = (ushort)((uint)_fr_w >> 0x10);
  }
  MDH = (ushort)((uint)iVar2 >> 0x10);
  MDL = (ushort)iVar2;
  if ((uRam302e38 < uRam0237f6) && (bRam00f38b < bRam019c34)) {
    uVar3 = FUN_042c1c(uRam302e3c,1000,0x138);
  }
  else if ((uRam0237f8 < uRam302960) && (bRam00f38b < bRam019c33)) {
    uRam3015d1 = me7_lookup_1d_byte(0x1c3a,6,uRam304e27);
    uVar4 = FUN_042c1c(uRam302960,uRam3015d1,0x555);
    MDL = (ushort)((uint)uVar4 * (uint)uRam023556);
    MDH = (ushort)((uint)uVar4 * (uint)uRam023556 >> 0x10);
    MDC = MDC | 0x10;
    sVar1 = MDH - (MDL != 0xffff);
    uVar4 = MDL;
    if ((sVar1 != 0 || MDL != 0xffff) && (MDH != 0 || MDL == 0xffff)) {
      uVar4 = 0xffff;
    }
    sRam30297e = uVar3 - uVar4;
    if (uVar3 < uVar4) {
      sRam30297e = 0;
    }
    uVar3 = FUN_042c1c(sRam30297e,1000,0x138,sVar1);
  }
  else {
    uVar3 = FUN_042c1c(uVar3,1000,0x138);
  }
  sRam30297a = uVar3 - (uVar5 >> 3);
  if (uVar3 < uVar5 >> 3) {
    if (sRam30297a >= 0) {
      sRam30297a = -0x8000;
    }
  }
  else if (sRam30297a < 0) {
    sRam30297a = 0x7fff;
  }
  uVar3 = uRam3029a6 + uRam305268;
  if (uRam3029a6 + uRam305268 < uRam3029a6 || uRam3029a6 + uRam305268 < uRam305268) {
    uVar3 = 0xffff;
  }
  uVar4 = func_0x042486(uRam0237ca,0x37cc,8,0x37d8,8,sRam30297a);
  uVar5 = _lamfa_w;
  sRam302998 = uVar3 + uVar4;
  if (uVar3 + uVar4 < uVar3 || uVar3 + uVar4 < uVar4) {
    sRam302998 = -1;
  }
  uVar3 = func_0x042486(uRam02379c,0x379e,8,0x37b4,8,sRam30297a);
  uVar3 = (ushort)((uint)uVar3 * (uint)uVar5 >> 0x10);
  uVar5 = uVar3 * 2;
  if (uVar3 * 2 < uVar3) {
    uVar5 = 0xffff;
  }
  MDL = (ushort)((uint)uRam0237f2 * (uint)uVar5);
  MDH = (ushort)((uint)uRam0237f2 * (uint)uVar5 >> 0x10);
  MDC = MDC | 0x10;
  sRam30525c = MDH * 2;
  if (MDH * 2 < MDH) {
    sRam30525c = -1;
  }
  uRam302982 = uRam306984;
  _fuel_mult = me7_lookup_2d_word_bilinear(0x3558,8,nmot_rpmclass,uRam306984);
  return;
}


// ================= fuel_injection_qty @ 0775c8 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* rk -> injection-time accumulator (RKTI / ti) */

void fuel_injection_qty(void)

{
  bool bVar1;
  uint uVar2;
  ushort uVar3;
  ushort uVar4;
  
  uVar2 = CONCAT22(MDH,MDL);
  if ((flags_torque_revlimit & 0x80) == 0) {
    uVar4 = (ushort)((uint)_rk_w * (uint)_fuel_mult >> 0x10);
    uVar3 = uVar4 * 2;
    if (uVar4 * 2 < uVar4) {
      uVar3 = 0xffff;
    }
    if ((short)uRam302a14 < 0) {
      uVar4 = uRam302a14 + uVar3;
      if (uRam302a14 <= uRam302a14 + uVar3 && uVar3 <= uRam302a14 + uVar3) {
        uVar4 = 0;
      }
    }
    else {
      uVar4 = uRam302a14 + uVar3;
      if (uRam302a14 + uVar3 < uRam302a14 || uRam302a14 + uVar3 < uVar3) {
        uVar4 = 0xffff;
      }
    }
    uVar2 = (uint)uVar4 * (uint)uRam0237f2;
    MDC = MDC | 0x10;
    uRam3028ba = (ushort)(uVar2 >> 9);
    if ((short)((uVar2 >> 9) >> 0x10) != 0 || uRam3028ba == 0xffff) {
      uRam3028ba = 0xffff;
    }
    bVar1 = _ti_w + uRam3028ba < _ti_w;
    uVar4 = _ti_w + uRam3028ba;
    _ti_w = _ti_w + uRam3028ba;
    sRam30069e = sRam30069e + (ushort)(bVar1 || uVar4 < uRam3028ba);
  }
  MDH = (undefined2)(uVar2 >> 0x10);
  MDL = (undefined2)uVar2;
  return;
}


// ================= fuel_component_protect @ 086318 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* component-protection enrichment (KFLBTS, over-temp) */

void fuel_component_protect(void)

{
  bool bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined2 uVar6;
  undefined1 uVar7;
  ushort uVar8;
  short sVar9;
  ushort uVar10;
  short sVar11;
  ushort uVar12;
  short sVar13;
  undefined4 uVar14;
  int iVar15;
  
  uVar6 = uRam303b7a;
  uVar10 = uRam303b78;
  if (((uRam302634 & 1) != 0) && ((uRam302634 & 0x8000) != 0)) {
    sRam30521e = 0;
    sRam305222 = 0;
    uRam30521a = 0x8000;
    uRam305216 = 0x8000;
    uVar14 = uRam300772;
    uVar2 = uRam300776;
    uVar3 = uRam30077a;
    uVar4 = uRam30077e;
    iVar5 = iRam3035ec;
    iVar15 = iRam3035f0;
    goto LAB_0875aa;
  }
  if ((uRam02348e < _rl_scaled) || (bRam019a87 < nmot_rpmclass)) {
    bRam30479c = bRam30479c & 0xfb;
  }
  else {
    bRam30479c = bRam30479c | 4;
  }
  if (((((nmot_rpmclass < bRam019a8b) || (bRam019a88 < nmot_rpmclass)) || (_rl_scaled < uRam023494))
      || ((uRam023490 < _rl_scaled || (rl_byte < bRam019a91)))) || (bRam019a8f < rl_byte)) {
    bRam30479c = bRam30479c & 0xfd;
  }
  else {
    bRam30479c = bRam30479c | 2;
  }
  if (((nmot_rpmclass < bRam019a8c) || (uRam023492 < _rl_scaled)) ||
     ((rl_byte < bRam019a92 || (bRam019a90 < rl_byte)))) {
    bRam30479c = bRam30479c & 0xf7;
  }
  else {
    bRam30479c = bRam30479c | 8;
  }
  if ((rl_byte < bRam019a93) || (_rl_scaled < uRam023496)) {
    bRam30479c = bRam30479c & 0xfe;
  }
  else {
    bRam30479c = bRam30479c | 1;
  }
  if ((bRam019279 & 8) == 0) {
    if ((bRam019a89 & 1) == 0) {
      bRam30479a = bRam30479a & 0xdf;
    }
    else {
      bRam30479a = bRam30479a | 0x20;
    }
    if ((bRam019a89 & 2) == 0) {
      bRam30479b = bRam30479b & 0xfb;
    }
    else {
      bRam30479b = bRam30479b | 4;
    }
    if ((bRam019a89 & 4) == 0) {
      bRam30479a = bRam30479a & 0xbf;
    }
    else {
      bRam30479a = bRam30479a | 0x40;
    }
    if ((bRam019a89 & 0x80) != 0) goto LAB_086504;
    bRam30479b = bRam30479b & 0xfd;
  }
  else {
    bRam30479b = bRam30479b | 4;
    bRam30479a = bRam30479a | 0x60;
LAB_086504:
    bRam30479b = bRam30479b | 2;
  }
  if ((((uRam00fd60 & 0x80) == 0) || ((bRam019a89 & 0x10) != 0)) && ((bRam019a89 & 8) != 0)) {
    bRam30479a = bRam30479a & 0xf7;
  }
  else {
    bRam30479a = bRam30479a | 8;
  }
  sRam305212 = uRam302816 + 0x8000;
  if (uRam302816 < 0x8000) {
    if (sRam305212 >= 0) {
      sRam305212 = -0x8000;
    }
  }
  else if (sRam305212 < 0) {
    sRam305212 = 0x7fff;
  }
  if ((bRam3055ba & 2) == 0) {
    bRam30a0dc = bRam30a0dc & 0x3d;
    bRam30a0db = bRam30a0db & 0x3d;
    bRam30a0da = bRam30a0da & 0x3d;
LAB_08667c:
    bRam30a0dd = bRam30a0dd & 0x3d;
  }
  else {
    if (((bRam30479c & 4) == 0) || ((bRam30479a & 0x20) != 0)) {
      bRam30a0dc = bRam30a0dc & 0x3d;
    }
    else {
      bRam30a0dc = bRam30a0dc | 0x80;
    }
    if (((bRam30479c & 2) == 0) || ((bRam30479b & 4) != 0)) {
      bRam30a0db = bRam30a0db & 0x3d;
    }
    else {
      bRam30a0db = bRam30a0db | 0x80;
    }
    if (((bRam30479c & 1) == 0) || ((bRam30479b & 2) != 0)) {
      bRam30a0da = bRam30a0da & 0x3d;
    }
    else {
      bRam30a0da = bRam30a0da | 0x80;
    }
    if (((bRam30479c & 8) == 0) || ((bRam30479a & 0x40) != 0)) goto LAB_08667c;
    bRam30a0dd = bRam30a0dd | 0x80;
  }
  if ((bRam30a0dc & 0x40) == 0) {
    if (bRam018770 < bRam019a97) {
      bRam018770 = bRam018770 + 1;
      goto LAB_0866c8;
    }
    bVar1 = false;
  }
  else {
    bRam018770 = 0;
LAB_0866c8:
    bVar1 = true;
  }
  if (bVar1) {
    bRam30a0dc = bRam30a0dc | 4;
  }
  else {
    bRam30a0dc = bRam30a0dc & 0xfb;
  }
  if ((bRam30a0db & 0x40) == 0) {
    if (bRam01876e < bRam019a96) {
      bRam01876e = bRam01876e + 1;
      goto LAB_086728;
    }
    bVar1 = false;
  }
  else {
    bRam01876e = 0;
LAB_086728:
    bVar1 = true;
  }
  if (bVar1) {
    bRam30a0db = bRam30a0db | 4;
  }
  else {
    bRam30a0db = bRam30a0db & 0xfb;
  }
  if ((bRam30a0da & 0x40) == 0) {
    if (bRam01876f < bRam019a95) {
      bRam01876f = bRam01876f + 1;
      goto LAB_086788;
    }
    bVar1 = false;
  }
  else {
    bRam01876f = 0;
LAB_086788:
    bVar1 = true;
  }
  if (bVar1) {
    bRam30a0da = bRam30a0da | 4;
  }
  else {
    bRam30a0da = bRam30a0da & 0xfb;
  }
  if ((bRam30a0dd & 0x40) == 0) {
    if (bRam018771 < bRam019a98) {
      bRam018771 = bRam018771 + 1;
      goto LAB_0867e8;
    }
    bVar1 = false;
  }
  else {
    bRam018771 = 0;
LAB_0867e8:
    bVar1 = true;
  }
  if (bVar1) {
    bRam30a0dd = bRam30a0dd | 4;
  }
  else {
    bRam30a0dd = bRam30a0dd & 0xfb;
  }
  sVar9 = sRam305212;
  if (sRam305212 < 0) {
    sVar9 = -sRam305212;
  }
  uVar7 = uRam30a0bf;
  if (((bRam30a0db & 4) != 0) && ((bRam30a0db & 0x80) != 0)) {
    uRam300772 = me7_pt1_integrator((ushort)bRam019a94 << 8,sVar9,uRam300772._2_2_,
                                    (undefined2)uRam300772,uRam303b7a,uRam303b78);
    uVar12 = (ushort)((uint)uRam300772 >> 0x16);
    if (uVar12 < 0x100) {
      uRam304797 = (undefined1)uVar12;
    }
    else {
      uRam304797 = 0xff;
    }
    uVar7 = uRam019a8e;
    if ((DAT_00fd4e & 0x2000) == 0) {
      uVar7 = me7_lookup_1d_byte(0x1a5b,6,uRam304797);
    }
  }
  uRam30a0bf = uVar7;
  uVar7 = uRam30a0be;
  if (((bRam30a0da & 4) != 0) &&
     (uRam300776 = CONCAT22(uRam300776._2_2_,(undefined2)uRam300776), (bRam30a0da & 0x80) != 0)) {
    uRam300776 = me7_pt1_integrator((ushort)bRam019a94 << 8,sVar9,uRam300776._2_2_,
                                    (undefined2)uRam300776,uVar6,uVar10);
    uVar12 = (ushort)((uint)uRam300776 >> 0x16);
    if (uVar12 < 0x100) {
      uRam304796 = (undefined1)uVar12;
    }
    else {
      uRam304796 = 0xff;
    }
    uVar7 = uRam019a8d;
    if ((DAT_00fd4e & 0x2000) == 0) {
      uVar7 = me7_lookup_1d_byte(0x1a4e,6,uRam304796);
    }
  }
  uRam30a0be = uVar7;
  if (((bRam30a0dc & 4) != 0) &&
     (uRam30077a = CONCAT22(uRam30077a._2_2_,(undefined2)uRam30077a), (bRam30a0dc & 0x80) != 0)) {
    uRam30077a = me7_pt1_integrator((ushort)bRam019a94 << 8,sVar9,uRam30077a._2_2_,
                                    (undefined2)uRam30077a,uVar6,uVar10);
    uVar12 = (ushort)((uint)uRam30077a >> 0x16);
    if (uVar12 < 0x100) {
      uRam304798 = (undefined1)uVar12;
    }
    else {
      uRam304798 = 0xff;
    }
    uRam30a0c0 = me7_lookup_1d_byte(0x1a68,6,uRam304798);
  }
  if (((bRam30a0dd & 4) != 0) &&
     (uRam30077e = CONCAT22(uRam30077e._2_2_,(undefined2)uRam30077e), (bRam30a0dd & 0x80) != 0)) {
    uRam30077e = me7_pt1_integrator((ushort)bRam019a94 << 8,sVar9,uRam30077e._2_2_,
                                    (undefined2)uRam30077e,uVar6,uVar10);
    uVar10 = (ushort)((uint)uRam30077e >> 0x16);
    if (uVar10 < 0x100) {
      uRam304799 = (undefined1)uVar10;
    }
    else {
      uRam304799 = 0xff;
    }
    uRam30a0c1 = me7_lookup_1d_byte(0x1a75,6,uRam304799);
  }
  uVar14 = CONCAT22(uRam3035e6,uRam3035e4);
  MDL = uRam302e0a / uRam302a02;
  MDH = uRam302e0a % uRam302a02;
  MDC = MDC | 0x10;
  uVar10 = MDL;
  if (uRam302a02 == 0) {
    uVar10 = 0xffff;
  }
  uVar10 = uVar10 * 2;
  if (0xff < uVar10) {
    uVar10 = 0xff;
  }
  sVar9 = cRam019a86 * 0x100;
  if (((sVar9 == sRam3029ee ||
        sVar9 - sRam3029ee < 0 !=
        (sVar9 < 0 != sRam3029ee < 0 && sVar9 - sRam3029ee < 0 != sVar9 < 0)) ||
      ((char)(cRam304950 - cRam019a83) < '\0' ==
       (cRam304950 < '\0' != cRam019a83 < '\0' &&
       (char)(cRam304950 - cRam019a83) < '\0' != cRam304950 < '\0'))) ||
     ((((bRam301612 & 4) == 0 || (_evap_purge_quantity < (ushort)bRam019a84 * 0x100)) &&
      (uVar10 < bRam019a85)))) {
    if (((char)(cRam304950 - cRam019a83) < '\0' ==
         (cRam304950 < '\0' != cRam019a83 < '\0' &&
         (char)(cRam304950 - cRam019a83) < '\0' != cRam304950 < '\0')) ||
       (sVar9 == sRam3029ee ||
        sVar9 - sRam3029ee < 0 !=
        (sVar9 < 0 != sRam3029ee < 0 && sVar9 - sRam3029ee < 0 != sVar9 < 0))) {
      uRam00fd4a = uRam00fd4a | 0x4000;
    }
  }
  else {
    uRam00fd4a = uRam00fd4a & 0xbfff;
  }
  uVar10 = uRam02341e;
  uVar12 = uRam023420;
  if ((uRam00fd4a & 0x4000) != 0) {
    uVar12 = uRam30521a;
    if (uRam30521a < uRam02341e) {
      uVar12 = uRam02341e;
    }
    uVar10 = uRam023422;
    if ((uVar12 <= uRam023422) && (uVar10 = uRam30521a, uRam30521a < uRam02341e)) {
      uVar10 = uRam02341e;
    }
    uVar8 = uRam30521a;
    if (uRam023420 < uRam30521a) {
      uVar8 = uRam023420;
    }
    uVar12 = uRam023424;
    if ((uRam023424 <= uVar8) && (uVar12 = uRam30521a, uRam023420 < uRam30521a)) {
      uVar12 = uRam023420;
    }
  }
  if ((bRam30479b & 4) == 0) {
    if ((uRam303ada & 1) == 0) {
      uVar8 = uRam303b78 & 1;
    }
    else if (((uRam023414 < uRam30521a) || (uRam30521a < uRam023412)) && ((uRam303b78 & 1) != 0)) {
      uVar8 = 1;
    }
    else {
      uVar8 = 0;
    }
    if (uVar8 == 0) {
      if ((((bRam30a0db & 0x80) != 0) &&
          (uVar14 = CONCAT22(uRam3035e6,uRam3035e4), (bRam30a0db & 0x40) != 0)) &&
         (uVar14 = CONCAT22(uRam3035e6,uRam3035e4), (bRam3015ba & 2) != 0)) {
        uRam305226 = func_0x042486(uRam023440,0x3442,8,0x344e,8,sRam305212);
        uVar14 = me7_integrator_minmax(uRam305226,sRam305212,uRam3075e6,uRam3035e4,uVar10,uVar12);
      }
    }
    else {
      uVar14 = CONCAT22(uRam3035e6,uRam3035e4);
      if ((bRam019a82 & 1) != 0) {
        if ((((bRam019a82 & 4) == 0) || ((uRam303ada & 1) == 0)) && ((bRam019a82 & 2) != 0)) {
          sVar9 = uRam305218 - uRam30521a;
          if (uRam305218 < uRam30521a) {
            if (sVar9 >= 0) {
              sVar9 = -0x8000;
            }
          }
          else if (sVar9 < 0) {
            sVar9 = 0x7fff;
          }
        }
        else {
          sVar9 = -0x8000 - uRam30521a;
          if (uRam30521a < 0x8001) {
            if (sVar9 < 0) {
              sVar9 = 0x7fff;
            }
          }
          else if (sVar9 >= 0) {
            sVar9 = -0x8000;
          }
        }
        uVar14 = me7_integrator_minmax(uRam0234ac,sVar9,uRam3035e6,uRam3035e4,uVar10,uVar12);
      }
    }
    uRam3035e6 = (ushort)((uint)uVar14 >> 0x10);
    uRam3035e4 = (undefined2)uVar14;
    uRam30521a = uRam3035e6;
  }
  else {
    uRam3035e4 = 0;
    uRam30521a = 0x8000;
  }
  uVar14 = CONCAT22(uRam3035ea,uRam3035e8);
  if ((uRam30521a < uVar12) && (uVar10 < uRam30521a)) {
    bRam30479a = bRam30479a & 0xfd;
  }
  else {
    bRam30479a = bRam30479a | 2;
  }
  uVar10 = uRam023416;
  uVar12 = uRam023418;
  if ((uRam00fd4a & 0x4000) != 0) {
    uVar12 = uRam305216;
    if (uRam305216 < uRam023416) {
      uVar12 = uRam023416;
    }
    uVar10 = uRam02341a;
    if ((uVar12 <= uRam02341a) && (uVar10 = uRam305216, uRam305216 < uRam023416)) {
      uVar10 = uRam023416;
    }
    uVar8 = uRam305216;
    if (uRam023418 < uRam305216) {
      uVar8 = uRam023418;
    }
    uVar12 = uRam02341c;
    if ((uRam02341c <= uVar8) && (uVar12 = uRam305216, uRam023418 < uRam305216)) {
      uVar12 = uRam023418;
    }
  }
  uRam3035e6 = uRam30521a;
  if ((bRam30479b & 2) == 0) {
    if ((uRam303ada & 1) == 0) {
      uVar8 = uRam303b78 & 1;
    }
    else if (((uRam023414 < uRam305216) || (uRam305216 < uRam023412)) && ((uRam303b78 & 1) != 0)) {
      uVar8 = 1;
    }
    else {
      uVar8 = 0;
    }
    if (uVar8 == 0) {
      if ((((bRam30a0da & 0x80) != 0) &&
          (uVar14 = CONCAT22(uRam3035ea,uRam3035e8), (bRam30a0da & 0x40) != 0)) &&
         (uVar14 = CONCAT22(uRam3035ea,uRam3035e8), (bRam3015ba & 2) != 0)) {
        uRam305224 = func_0x042486(uRam023426,0x3428,8,0x3434,8,sRam305212);
        uVar14 = me7_integrator_minmax(uRam305224,sRam305212,uRam3075ea,uRam3035e8,uVar10,uVar12);
      }
    }
    else {
      uVar14 = CONCAT22(uRam3035ea,uRam3035e8);
      if ((bRam019a82 & 1) != 0) {
        if ((((bRam019a82 & 4) == 0) || ((uRam303ada & 1) == 0)) && ((bRam019a82 & 2) != 0)) {
          sVar9 = uRam305214 - uRam305216;
          if (uRam305214 < uRam305216) {
            if (sVar9 >= 0) {
              sVar9 = -0x8000;
            }
          }
          else if (sVar9 < 0) {
            sVar9 = 0x7fff;
          }
        }
        else {
          sVar9 = -0x8000 - uRam305216;
          if (uRam305216 < 0x8001) {
            if (sVar9 < 0) {
              sVar9 = 0x7fff;
            }
          }
          else if (sVar9 >= 0) {
            sVar9 = -0x8000;
          }
        }
        uVar14 = me7_integrator_minmax(uRam0234ac,sVar9,uRam3035ea,uRam3035e8,uVar10,uVar12);
      }
    }
    uRam3035ea = (ushort)((uint)uVar14 >> 0x10);
    uRam3035e8 = (undefined2)uVar14;
    uRam305216 = uRam3035ea;
  }
  else {
    uRam3035e8 = 0;
    uRam305216 = 0x8000;
  }
  if ((uRam305216 < uVar12) && (uVar10 < uRam305216)) {
    bRam30479a = bRam30479a & 0xfe;
  }
  else {
    bRam30479a = bRam30479a | 1;
  }
  sVar9 = sRam02349c;
  sVar13 = sRam02349e;
  if ((uRam00fd4a & 0x4000) != 0) {
    sVar13 = sRam30521e;
    if (sRam30521e - sRam02349c < 0 !=
        (sRam30521e < 0 != sRam02349c < 0 && sRam30521e - sRam02349c < 0 != sRam30521e < 0)) {
      sVar13 = sRam02349c;
    }
    sVar9 = sRam0234a0;
    if ((sVar13 == sRam0234a0 ||
         sVar13 - sRam0234a0 < 0 !=
         (sVar13 < 0 != sRam0234a0 < 0 && sVar13 - sRam0234a0 < 0 != sVar13 < 0)) &&
       (sVar9 = sRam30521e,
       sRam30521e - sRam02349c < 0 !=
       (sRam30521e < 0 != sRam02349c < 0 && sRam30521e - sRam02349c < 0 != sRam30521e < 0))) {
      sVar9 = sRam02349c;
    }
    sVar11 = sRam30521e;
    if (sRam30521e != sRam02349e &&
        sRam30521e - sRam02349e < 0 ==
        (sRam30521e < 0 != sRam02349e < 0 && sRam30521e - sRam02349e < 0 != sRam30521e < 0)) {
      sVar11 = sRam02349e;
    }
    sVar13 = sRam0234a2;
    if ((sVar11 - sRam0234a2 < 0 ==
         (sVar11 < 0 != sRam0234a2 < 0 && sVar11 - sRam0234a2 < 0 != sVar11 < 0)) &&
       (sVar13 = sRam30521e,
       sRam30521e != sRam02349e &&
       sRam30521e - sRam02349e < 0 ==
       (sRam30521e < 0 != sRam02349e < 0 && sRam30521e - sRam02349e < 0 != sRam30521e < 0))) {
      sVar13 = sRam02349e;
    }
  }
  uRam3035ea = uRam305216;
  if ((bRam30479a & 0x20) == 0) {
    if ((uRam303ada & 1) == 0) {
      uVar10 = uRam303b78 & 1;
    }
    else if (((sRam30521e == sRam02349a ||
               sRam30521e - sRam02349a < 0 !=
               (sRam30521e < 0 != sRam02349a < 0 && sRam30521e - sRam02349a < 0 != sRam30521e < 0))
             && (sRam30521e - sRam023498 < 0 ==
                 (sRam30521e < 0 != sRam023498 < 0 && sRam30521e - sRam023498 < 0 != sRam30521e < 0)
                )) || ((uRam303b78 & 1) == 0)) {
      uVar10 = 0;
    }
    else {
      uVar10 = 1;
    }
    if (uVar10 == 0) {
      if ((((bRam30a0dc & 0x80) != 0) &&
          (iRam3035ec = CONCAT22(iRam3035ec._2_2_,(undefined2)iRam3035ec), (bRam30a0dc & 0x40) != 0)
          ) && (iRam3035ec = CONCAT22(iRam3035ec._2_2_,(undefined2)iRam3035ec),
               (bRam3015ba & 2) != 0)) {
        uRam305228 = func_0x042486(uRam02345a,0x345c,8,0x3468,8,sRam305212);
        iRam3035ec = me7_integrator_sat(uRam305228,sRam305212,uRam3075ee,(undefined2)iRam3035ec);
      }
    }
    else {
      iRam3035ec = CONCAT22(iRam3035ec._2_2_,(undefined2)iRam3035ec);
      if ((bRam019a82 & 1) != 0) {
        if ((((bRam019a82 & 4) == 0) || ((uRam303ada & 1) == 0)) && ((bRam019a82 & 2) != 0)) {
          sVar11 = sRam30521c - sRam30521e;
          if (sRam30521c < 0 != sRam30521e < 0 && sRam30521c - sRam30521e < 0 != sRam30521c < 0) {
            sVar11 = -0x8000;
          }
        }
        else if (sRam30521e == -0x8000) {
          sVar11 = 0x7fff;
        }
        else {
          sVar11 = -sRam30521e;
        }
        iRam3035ec = me7_integrator_sat(uRam0234ac,sVar11,iRam3035ec._2_2_,(undefined2)iRam3035ec);
      }
    }
    sRam30521e = (short)(iRam3035ec >> 0x13);
    if (sRam30521e == sVar13 ||
        sRam30521e - sVar13 < 0 !=
        (sRam30521e < 0 != sVar13 < 0 && sRam30521e - sVar13 < 0 != sRam30521e < 0)) {
      if (sRam30521e - sVar9 < 0 !=
          (sRam30521e < 0 != sVar9 < 0 && sRam30521e - sVar9 < 0 != sRam30521e < 0)) {
        iRam3035ec = CONCAT22(sVar9 << 3,0xffff);
        sRam30521e = sVar9;
      }
    }
    else {
      iRam3035ec = (uint)(ushort)(sVar13 << 3) << 0x10;
      sRam30521e = sVar13;
    }
  }
  else {
    iRam3035ec = 0;
    sRam30521e = 0;
  }
  iVar15 = CONCAT22(iRam3035f0._2_2_,(undefined2)iRam3035f0);
  if ((sVar13 == sRam30521e ||
       sVar13 - sRam30521e < 0 !=
       (sVar13 < 0 != sRam30521e < 0 && sVar13 - sRam30521e < 0 != sVar13 < 0)) ||
     (sVar9 - sRam30521e < 0 == (sVar9 < 0 != sRam30521e < 0 && sVar9 - sRam30521e < 0 != sVar9 < 0)
     )) {
    bRam30479a = bRam30479a | 0x80;
  }
  else {
    bRam30479a = bRam30479a & 0x7f;
  }
  sVar9 = sRam0234a4;
  sVar13 = sRam0234a6;
  if ((uRam00fd4a & 0x4000) != 0) {
    sVar13 = sRam305222;
    if (sRam305222 - sRam0234a4 < 0 !=
        (sRam305222 < 0 != sRam0234a4 < 0 && sRam305222 - sRam0234a4 < 0 != sRam305222 < 0)) {
      sVar13 = sRam0234a4;
    }
    sVar9 = sRam0234a8;
    if ((sVar13 == sRam0234a8 ||
         sVar13 - sRam0234a8 < 0 !=
         (sVar13 < 0 != sRam0234a8 < 0 && sVar13 - sRam0234a8 < 0 != sVar13 < 0)) &&
       (sVar9 = sRam305222,
       sRam305222 - sRam0234a4 < 0 !=
       (sRam305222 < 0 != sRam0234a4 < 0 && sRam305222 - sRam0234a4 < 0 != sRam305222 < 0))) {
      sVar9 = sRam0234a4;
    }
    sVar11 = sRam305222;
    if (sRam305222 != sRam0234a6 &&
        sRam305222 - sRam0234a6 < 0 ==
        (sRam305222 < 0 != sRam0234a6 < 0 && sRam305222 - sRam0234a6 < 0 != sRam305222 < 0)) {
      sVar11 = sRam0234a6;
    }
    sVar13 = sRam0234aa;
    if ((sVar11 - sRam0234aa < 0 ==
         (sVar11 < 0 != sRam0234aa < 0 && sVar11 - sRam0234aa < 0 != sVar11 < 0)) &&
       (sVar13 = sRam305222,
       sRam305222 != sRam0234a6 &&
       sRam305222 - sRam0234a6 < 0 ==
       (sRam305222 < 0 != sRam0234a6 < 0 && sRam305222 - sRam0234a6 < 0 != sRam305222 < 0))) {
      sVar13 = sRam0234a6;
    }
  }
  if ((bRam30479a & 0x40) == 0) {
    if ((uRam303ada & 1) == 0) {
      uVar10 = uRam303b78 & 1;
    }
    else if (((sRam305222 == sRam02349a ||
               sRam305222 - sRam02349a < 0 !=
               (sRam305222 < 0 != sRam02349a < 0 && sRam305222 - sRam02349a < 0 != sRam305222 < 0))
             && (sRam305222 - sRam023498 < 0 ==
                 (sRam305222 < 0 != sRam023498 < 0 && sRam305222 - sRam023498 < 0 != sRam305222 < 0)
                )) || ((uRam303b78 & 1) == 0)) {
      uVar10 = 0;
    }
    else {
      uVar10 = 1;
    }
    if (uVar10 == 0) {
      if ((((bRam30a0dd & 0x80) != 0) &&
          (iVar15 = CONCAT22(iRam3035f0._2_2_,(undefined2)iRam3035f0), (bRam30a0dd & 0x40) != 0)) &&
         (iVar15 = CONCAT22(iRam3035f0._2_2_,(undefined2)iRam3035f0), (bRam3015ba & 2) != 0)) {
        uRam30522a = func_0x042486(uRam023474,0x3476,8,0x3482,8,sRam305212);
        iVar15 = me7_integrator_sat(uRam30522a,sRam305212,uRam3075f2,(undefined2)iRam3035f0);
      }
    }
    else {
      iVar15 = CONCAT22(iRam3035f0._2_2_,(undefined2)iRam3035f0);
      if ((bRam019a82 & 1) != 0) {
        if ((((bRam019a82 & 4) == 0) || ((uRam303ada & 1) == 0)) && ((bRam019a82 & 2) != 0)) {
          sVar11 = sRam305220 - sRam305222;
          if (sRam305220 < 0 != sRam305222 < 0 && sRam305220 - sRam305222 < 0 != sRam305220 < 0) {
            sVar11 = -0x8000;
          }
        }
        else if (sRam305222 == -0x8000) {
          sVar11 = 0x7fff;
        }
        else {
          sVar11 = -sRam305222;
        }
        iVar15 = me7_integrator_sat(uRam0234ac,sVar11,iRam3035f0._2_2_,(undefined2)iRam3035f0);
      }
    }
    sRam305222 = (short)(iVar15 >> 0x13);
    if (sRam305222 == sVar13 ||
        sRam305222 - sVar13 < 0 !=
        (sRam305222 < 0 != sVar13 < 0 && sRam305222 - sVar13 < 0 != sRam305222 < 0)) {
      if (sRam305222 - sVar9 < 0 !=
          (sRam305222 < 0 != sVar9 < 0 && sRam305222 - sVar9 < 0 != sRam305222 < 0)) {
        iVar15 = CONCAT22(sVar9 << 3,0xffff);
        sRam305222 = sVar9;
      }
    }
    else {
      iVar15 = (uint)(ushort)(sVar13 << 3) << 0x10;
      sRam305222 = sVar13;
    }
  }
  else {
    iVar15 = 0;
    sRam305222 = 0;
  }
  uVar14 = uRam300772;
  uVar2 = uRam300776;
  uVar3 = uRam30077a;
  uVar4 = uRam30077e;
  iVar5 = iRam3035ec;
  if ((sVar13 == sRam305222 ||
       sVar13 - sRam305222 < 0 !=
       (sVar13 < 0 != sRam305222 < 0 && sVar13 - sRam305222 < 0 != sVar13 < 0)) ||
     (sVar9 - sRam305222 < 0 == (sVar9 < 0 != sRam305222 < 0 && sVar9 - sRam305222 < 0 != sVar9 < 0)
     )) {
    bRam30479b = bRam30479b | 1;
  }
  else {
    bRam30479b = bRam30479b & 0xfe;
  }
LAB_0875aa:
  iRam3035f0._2_2_ = (undefined2)((uint)iVar15 >> 0x10);
  iRam3035f0._0_2_ = (undefined2)iVar15;
  iRam3035ec._2_2_ = (undefined2)((uint)iVar5 >> 0x10);
  iRam3035ec._0_2_ = (undefined2)iVar5;
  uRam30077e._2_2_ = (undefined2)((uint)uVar4 >> 0x10);
  uRam30077e._0_2_ = (undefined2)uVar4;
  uRam30077a._2_2_ = (undefined2)((uint)uVar3 >> 0x10);
  uRam30077a._0_2_ = (undefined2)uVar3;
  uRam300776._2_2_ = (undefined2)((uint)uVar2 >> 0x10);
  uRam300776._0_2_ = (undefined2)uVar2;
  uRam300772._2_2_ = (undefined2)((uint)uVar14 >> 0x10);
  uRam300772._0_2_ = (undefined2)uVar14;
  return;
}


// ================= torque_kfmiop_optimum @ 04f4bc =================

/* WARNING: Removing unreachable block (ram,0x04f5fa) */
/* WARNING: Removing unreachable block (ram,0x04f558) */
/* WARNING: Removing unreachable block (ram,0x04f67c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* optimum indicated-torque model (KFMIOP, 5-cyl avg) */

void torque_kfmiop_optimum(void)

{
  byte bVar1;
  ushort uVar2;
  short sVar3;
  int iVar4;
  byte bVar5;
  short sVar6;
  char cVar7;
  ushort uVar8;
  byte bStack_c;
  undefined1 uStack_a;
  
  uRam301ae8 = me7_axis_search(0x582c,_rl_w);
  uRam301aec = me7_lookup_2d_word_torque(0x56cc,0x582c,uRam3019b4,uRam301ae8);
  cVar7 = me7_lookup_2d_sbyte_bilinear(0x2aa2,0x582c,uRam3019b4,uRam301ae8);
  sVar6 = (short)cVar7;
  cVar7 = me7_lookup_2d_sbyte_bilinear(0x2b52,0x582c,uRam3019b4,uRam301ae8);
  uVar8 = 0xff - wnwise;
  if ((short)uVar8 < 0) {
    sVar6 = sVar6 * (uVar8 & 0x7fff) + sVar6 * -0x8000;
  }
  else {
    sVar6 = sVar6 * uVar8;
  }
  MDL = (ushort)((int)(short)cVar7 * (int)(short)(ushort)wnwise);
  MDH = (ushort)((uint)((int)(short)cVar7 * (int)(short)(ushort)wnwise) >> 0x10);
  MDC = MDC | 0x10;
  sRam301af0 = MDL + sVar6;
  if ((short)MDL < 0 == sVar6 < 0 && (short)(MDL + sVar6) < 0 != (short)MDL < 0) {
    sRam301af0 = 0x7fff;
  }
  cVar7 = me7_lookup_2d_sbyte_bilinear(0x2c02,0x582c,uRam3019b4,uRam301ae8);
  sVar6 = (short)cVar7;
  cVar7 = me7_lookup_2d_sbyte_bilinear(0x2cb2,0x582c,uRam3019b4,uRam301ae8);
  uVar8 = 0xff - wnwise;
  if ((short)uVar8 < 0) {
    sVar6 = sVar6 * (uVar8 & 0x7fff) + sVar6 * -0x8000;
  }
  else {
    sVar6 = sVar6 * uVar8;
  }
  sVar3 = (short)cVar7 * (ushort)wnwise;
  sRam301af2 = sVar3 + sVar6;
  if (sVar3 < 0 == sVar6 < 0 && sVar3 + sVar6 < 0 != sVar3 < 0) {
    sRam301af2 = 0x7fff;
  }
  uVar8 = 0xff - wnwisa;
  if ((short)uVar8 < 0) {
    iVar4 = (int)sRam301af0 * (int)(short)(uVar8 & 0x7fff);
    uVar2 = (ushort)iVar4;
    uVar8 = sRam301af0 * -0x8000;
    iVar4 = CONCAT22((short)((uint)iVar4 >> 0x10) + (sRam301af0 >> 1) +
                     (ushort)(uVar2 + uVar8 < uVar2 || uVar2 + uVar8 < uVar8),uVar2 + uVar8);
  }
  else {
    iVar4 = (int)sRam301af0 * (int)(short)uVar8;
  }
  uVar8 = (ushort)iVar4 >> 8 | (short)((uint)iVar4 >> 0x10) << 8;
  iVar4 = (int)sRam301af2 * (int)(short)(ushort)wnwisa;
  MDL = (ushort)iVar4;
  MDH = (ushort)((uint)iVar4 >> 0x10);
  MDC = MDC | 0x10;
  cVar7 = (char)((uint)iVar4 >> 0x10);
  sVar6 = (short)((uint)iVar4 >> 8);
  uRam301af4 = sVar6 + uVar8;
  if (cVar7 < '\0' == (short)uVar8 < 0 && (short)(sVar6 + uVar8) < 0 != cVar7 < '\0') {
    uRam301af4 = 0x7fff;
  }
  uVar8 = uRam301af4;
  if ((short)uRam301af4 < 0) {
    if (uRam301af4 == 0x8000) {
      uVar8 = 0x7fff;
    }
    else {
      uVar8 = -uRam301af4;
    }
  }
  uVar2 = (short)uVar8 >> 8;
  if ((uVar8 & 0x80) == 0) {
    uVar8 = uVar2 & 0xff;
  }
  else {
    uVar8 = uVar2 + 1;
    if (((short)(uVar2 - 0x7e) < 0 ==
         ((short)uVar2 < 0 && (short)(uVar2 - 0x7e) < 0 != (short)uVar2 < 0)) ||
       (uVar8 == 0xff80 ||
        (short)(uVar2 + 0x81) < 0 !=
        (-1 < (short)uVar8 && (short)(uVar2 + 0x81) < 0 != (short)uVar8 < 0))) {
      uVar8 = uVar2 & 0xff;
    }
  }
  cRam301304 = (char)uVar8;
  if ((short)uRam301af4 < 0) {
    cRam301304 = -cRam301304;
  }
  bRam3012ff = func_0x040b3e(0x2a8d,uRam3015b9);
  cRam3012fe = func_0x041434(uRam0156b6,0x56b7,0x56c1,uRam3015b9);
  uRam3012fd = 0;
  uVar8 = (ushort)((uint)((ushort)bRam3012ff * 0xa4) * (uint)uRam301aec >> 0x10);
  uRam301aee = uVar8 * 2;
  if (uVar8 * 2 < uVar8) {
    uRam301aee = 0xffff;
  }
  uVar8 = (ushort)((uint)((ushort)bRam301302 * 0xa4) * (uint)uRam301aee >> 0x10);
  sRam301aea = uVar8 * 2;
  if (uVar8 * 2 < uVar8) {
    sRam301aea = -1;
  }
  cVar7 = cRam301304 - cRam30132b;
  if (cRam301304 < '\0' != cRam30132b < '\0' &&
      (char)(cRam301304 - cRam30132b) < '\0' != cRam301304 < '\0') {
    cVar7 = -0x80;
  }
  sVar6 = (short)cVar7 + (short)cRam304049 + (short)cRam3012fe;
  if (sVar6 == 0x7f || sVar6 + -0x7f < 0 != (sVar6 < 0 && sVar6 + -0x7f < 0 != sVar6 < 0)) {
    if (sVar6 + 0x80 < 0 == (-1 < sVar6 && sVar6 + 0x80 < 0 != sVar6 < 0)) {
      uStack_a = (undefined1)sVar6;
      uRam301303 = uStack_a;
    }
    else {
      uRam301303 = 0x80;
    }
  }
  else {
    uRam301303 = 0x7f;
  }
  bRam301300 = bRam301306;
  uRam301af6 = (ushort)bRam301306;
  bStack_c = 1;
  do {
    bVar1 = *(byte *)((uint3)bStack_c + 0x301306);
    bVar5 = bVar1;
    if (bRam301300 <= bVar1) {
      bVar5 = bRam301300;
    }
    bRam301300 = bVar5;
    uRam301af6 = uRam301af6 + bVar1;
    bStack_c = bStack_c + 1;
  } while (bStack_c < 5);
  MDL = uRam301af6 / 5;
  MDH = uRam301af6 % 5;
  MDC = MDC | 0x10;
  bRam301302 = (char)MDL;
  return;
}


// ================= torque_kfmirl_revlimit @ 04f97a =================

/* WARNING: Removing unreachable block (ram,0x04fd0e) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* KFMIRL torque->load (rlsol) AND the NMAX rev limiter (limiters.md) */

short torque_kfmirl_revlimit(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  ushort uVar5;
  short sVar6;
  ushort uVar7;
  short sVar8;
  undefined4 uVar9;
  
  if (uRam01584e < nmot_w) {
    bRam3001f4 = bRam3001f4 | 0x80;
  }
  else {
    bRam3001f4 = bRam3001f4 & 0x7f;
  }
  if ((bRam3001f4 & 0x80) == 0) {
    if ((bRam3001f4 & 2) == 0) {
      if (sRam3001fa == 0) {
        flags_torque_revlimit = flags_torque_revlimit & 0xfffe;
      }
      else {
        sRam3001fa = sRam3001fa + -1;
        flags_torque_revlimit = flags_torque_revlimit | 1;
      }
    }
    else {
      sRam3001fa = sRam01584c;
      flags_torque_revlimit = flags_torque_revlimit | 1;
    }
  }
  if ((bRam3001f4 & 0x80) == 0) {
    bRam3001f4 = bRam3001f4 & 0xfd;
  }
  else {
    bRam3001f4 = bRam3001f4 | 2;
  }
  if (((bRam3001f4 & 0x80) == 0) || ((flags_torque_revlimit & 1) != 0)) {
    bRam3001f4 = bRam3001f4 & 0xf7;
  }
  else {
    bRam3001f4 = bRam3001f4 | 8;
  }
  if ((bRam3001f4 & 0x80) != 0) {
    if (((bRam3001f4 & 8) == 0) || ((bRam3001f4 & 0x10) != 0)) {
      if (sRam3001f2 == 0) {
        flags_torque_revlimit = flags_torque_revlimit & 0xffef;
      }
      else {
        sRam3001f2 = sRam3001f2 + -1;
        flags_torque_revlimit = flags_torque_revlimit | 0x10;
      }
    }
    else {
      sRam3001f2 = sRam01585c;
      flags_torque_revlimit = flags_torque_revlimit | 0x10;
    }
  }
  if ((bRam3001f4 & 8) == 0) {
    bRam3001f4 = bRam3001f4 & 0xef;
  }
  else {
    bRam3001f4 = bRam3001f4 | 0x10;
  }
  if (((flags_torque_revlimit & 1) == 0) && ((bRam3001f4 & 0x80) == 0)) {
    bRam3001f4 = bRam3001f4 & 0xdf;
  }
  else if (((bRam3001f4 & 4) != 0) && ((flags_torque_revlimit & 0x10) == 0)) {
    bRam3001f4 = bRam3001f4 | 0x20;
  }
  if ((flags_torque_revlimit & 0x10) == 0) {
    bRam3001f4 = bRam3001f4 & 0xfb;
  }
  else {
    bRam3001f4 = bRam3001f4 | 4;
  }
  if ((bRam3001f4 & 0x20) == 0) {
    if ((bRam012d71 < vfzg_class) && ((bRam3001f4 & 1) != 0)) {
      uRam302486 = uRam015858;
    }
    else {
      uRam302486 = uRam01584e;
    }
  }
  else {
    bVar1 = uRam302486 < uRam015844;
    uRam302486 = uRam302486 - uRam015844;
    if (bVar1) {
      uRam302486 = 0;
    }
    if (uRam015858 < uRam302486) {
      uRam302486 = uRam015858;
    }
    else if (uRam302486 < uRam01584e) {
      uRam302486 = uRam01584e;
    }
  }
  if ((uRam303c1e & 1) == 0) {
    uVar7 = uRam302486;
    if ((bRam012d62 & 1) == 0) {
      uVar7 = uRam3001fe;
    }
  }
  else {
    uVar7 = uRam304f32;
    if ((_flags_diag_cfg_a & 0x10) == 0) {
      uVar7 = uRam015850;
    }
  }
  uVar5 = uVar7;
  if (((bRam301271 & 0x20) != 0) && (uVar5 = uRam301966, uVar7 < uRam301966)) {
    uVar5 = uVar7;
  }
  uVar7 = uRam300200;
  if (((_flags_start_phase & 0x10) != 0) && (uVar7 = uVar5, (bRam3001f4 & 0x40) != 0)) {
    uVar7 = uRam300200 - uRam015846;
    if (uRam300200 < uRam015846) {
      uVar7 = 0;
    }
    if (uRam015858 < uVar7) {
      uRam300200 = uRam015858;
      uVar7 = uRam300200;
    }
    else if (uVar7 < uRam015852) {
      uRam300200 = uRam015852;
      uVar7 = uRam300200;
    }
  }
  uRam300200 = uVar7;
  if ((_flags_start_phase & 0x10) == 0) {
    bRam3001f4 = bRam3001f4 & 0xbf;
  }
  else {
    bRam3001f4 = bRam3001f4 | 0x40;
  }
  uVar7 = uRam01585a;
  if ((uRam00fd70 & 0x200) == 0) {
    uVar7 = uVar5;
    if (((uRam00fd5c & 2) != 0) && (uVar7 = uRam015856, uVar5 < uRam015856)) {
      uVar7 = uVar5;
    }
    uVar5 = uVar7;
    if (((_flags_start_phase & 0x10) != 0) && (uVar5 = uRam300200, uVar7 < uRam300200)) {
      uVar5 = uVar7;
    }
    if ((flags_torque_revlimit & 8) == 0) {
      if (((DAT_00fd42 & 0x4000) != 0) && (nmot_w < uRam015854)) {
        flags_torque_revlimit = flags_torque_revlimit | 8;
      }
    }
    else {
      if (((DAT_00fd42 & 0x4000) == 0) && ((flags_torque_revlimit & 2) == 0)) {
        PSW = PSW & 0xffbf;
      }
      else {
        PSW = PSW | 0x40;
      }
      flags_torque_revlimit = flags_torque_revlimit & 0xfff7 | ((PSW & 0x40) >> 6) << 3;
    }
    uVar7 = uVar5;
    if (((flags_torque_revlimit & 8) != 0) && (uVar7 = uRam015854, uVar5 <= uRam015854)) {
      uVar7 = uVar5;
    }
    if ((uRam00fd70 & 0x20) != 0) {
      uVar5 = func_0x040b3e(0x2d64,DAT_301258);
      uVar5 = (uVar5 & 0xff) * 0xa0;
      if (uVar5 <= uVar7) {
        uVar7 = uVar5;
      }
    }
  }
  uVar9 = CONCAT22(uRam3001f8,uRam3001f6);
  uVar4 = CONCAT22(MDH,MDL);
  uVar5 = uRam015848 + uVar7;
  if (uRam015848 + uVar7 < uRam015848 || uRam015848 + uVar7 < uVar7) {
    uVar5 = 0xffff;
  }
  if (uVar5 < nmot_w) {
    flags_torque_revlimit = flags_torque_revlimit | 4;
  }
  else {
    flags_torque_revlimit = flags_torque_revlimit & 0xfffb;
  }
  if (sRam302b0a < 1) {
    uRam302488 = nmot_w;
  }
  else {
    uVar4 = (uint)uRam3001fc * (uint)(ushort)(sRam302b0a >> 5);
    uVar5 = (ushort)uVar4;
    MDC = MDC | 0x10;
    if (0xffff < uVar4) {
      uVar5 = 0xffff;
    }
    uRam302488 = nmot_w + uVar5;
    if (nmot_w + uVar5 < nmot_w || nmot_w + uVar5 < uVar5) {
      uRam302488 = 0xffff;
    }
  }
  MDH = (undefined2)(uVar4 >> 0x10);
  MDL = (undefined2)uVar4;
  sRam302480 = uVar7 - uRam302488;
  if (uVar7 < uRam302488) {
    if (sRam302480 >= 0) {
      sRam302480 = -0x8000;
    }
  }
  else if (sRam302480 < 0) {
    sRam302480 = 0x7fff;
  }
  if ((sRam302480 == sRam01584a ||
       sRam302480 - sRam01584a < 0 !=
       (sRam302480 < 0 != sRam01584a < 0 && sRam302480 - sRam01584a < 0 != sRam302480 < 0)) &&
     ((sRam302480 < 1 || (uRam302484 < uRam301ac8)))) {
    if (sRam302480 < 1) {
      flags_torque_revlimit = flags_torque_revlimit | 2;
    }
  }
  else {
    flags_torque_revlimit = flags_torque_revlimit & 0xfffd;
  }
  uRam30248a = uVar7;
  if ((flags_torque_revlimit & 2) == 0) {
    uRam304f30 = uRam301ac8;
    uRam30647c = 0;
    uVar9 = 0;
  }
  else if (uRam302484 != 0) {
    uVar9 = me7_integrator_sat((ushort)bRam30404a << 8,sRam302480,uRam3001f8,uRam3001f6);
    sVar6 = (short)((uint)uVar9 >> 0x10);
    uVar5 = (ushort)((int)sVar6 * 0x63a);
    MDC = MDC | 0x10;
    uVar7 = sVar6 * -0x8000;
    sVar6 = (short)((uint)((int)sVar6 * 0x63a) >> 0x10) + (sVar6 >> 1) +
            (ushort)(uVar5 + uVar7 < uVar5 || uVar5 + uVar7 < uVar7);
    uRam300204 = sVar6 >> 0xd;
    uRam300202 = uVar5 + uVar7 >> 0xd | sVar6 * 8;
    uVar7 = (ushort)(uRam300202 < 0x7fff);
    if (uRam300204 == uVar7 && uRam300202 == 0x7fff ||
        (short)(uRam300204 - uVar7) < 0 !=
        ((short)uRam300204 < 0 &&
        (short)(uRam300204 - (uRam300202 < 0x7fff)) < 0 != (short)uRam300204 < 0)) {
      uRam30247c = uRam300202;
      if ((short)((uRam300204 + 1) - (ushort)(uRam300202 < 0x8000)) < 0 !=
          (-1 < (short)uRam300204 &&
          (short)((uRam300204 + 1) - (ushort)(uRam300202 < 0x8000)) < 0 != (short)uRam300204 < 0)) {
        uRam30247c = 0x8000;
      }
    }
    else {
      uRam30247c = 0x7fff;
    }
  }
  uRam3001f8 = (undefined2)((uint)uVar9 >> 0x10);
  uRam3001f6 = (undefined2)uVar9;
  sVar6 = (ushort)bRam30404b * 0x29;
  if (sVar6 < 0) {
    iVar3 = (int)sRam302480 * (int)sVar6;
    uVar5 = (ushort)iVar3;
    uVar7 = sRam302480 * -0x8000;
    iVar2 = CONCAT22((short)((uint)iVar3 >> 0x10) + (sRam302480 >> 1) +
                     (ushort)(uVar5 + uVar7 < uVar5 || uVar5 + uVar7 < uVar7),uVar5 + uVar7);
    sVar6 = sRam302480 >> 1;
  }
  else {
    iVar2 = (int)sRam302480 * (int)sVar6;
    sVar6 = sRam302480;
    iVar3 = iVar2;
  }
  MDH = (undefined2)((uint)iVar3 >> 0x10);
  MDL = (undefined2)iVar3;
  sVar8 = (short)((uint)iVar2 >> 0x10);
  MDC = MDC | 0x10;
  if (sVar8 + -0x40 < 0 == (iVar2 < 0 && sVar8 + -0x40 < 0 != iVar2 < 0)) {
    iVar2 = CONCAT22(sVar6,0x7fff);
  }
  else if (sVar8 == -0x40 || sVar8 + 0x40 < 0 != (-1 < iVar2 && sVar8 + 0x40 < 0 != iVar2 < 0)) {
    iVar2 = -0x7fff8000;
  }
  else {
    iVar2 = iVar2 >> 7;
  }
  sVar6 = (short)((uint)iVar2 >> 0x10);
  sRam30247e = (short)iVar2;
  if ((flags_torque_revlimit & 4) == 0) {
    if ((flags_torque_revlimit & 2) == 0) {
      uRam302484 = (ushort)bRam012d63 << 8;
    }
    else {
      sVar6 = uRam30247c + sRam30247e;
      if ((short)uRam30247c < 0 == sRam30247e < 0 &&
          (short)(uRam30247c + sRam30247e) < 0 != (short)uRam30247c < 0) {
        sVar6 = 0x7fff;
      }
      bVar1 = 1 < (uRam304f30 >> 1 & 1);
      uVar7 = uRam304f30 >> 2;
      sVar8 = sVar6 + uVar7 + (ushort)bVar1;
      if ((-1 < sVar6 && (short)(sVar6 + uVar7 + (ushort)bVar1) < 0 != sVar6 < 0) ||
         (sVar6 = sVar8 + uVar7, -1 < sVar8 && (short)(sVar8 + uVar7) < 0 != sVar8 < 0)) {
        sVar6 = 0x7fff;
      }
      uVar7 = (ushort)bRam012d63;
      sRam302482 = sVar6;
      if (sVar6 != uVar7 * 0x80 &&
          (short)(sVar6 + uVar7 * -0x80) < 0 ==
          (sVar6 < 0 && (short)(sVar6 + uVar7 * -0x80) < 0 != sVar6 < 0)) {
        sRam302482 = (ushort)bRam012d63 << 7;
      }
      if (sRam302482 < 0) {
        uRam302484 = 0;
      }
      else {
        uRam302484 = sRam302482 << 1;
      }
    }
  }
  else {
    uRam302484 = 0;
  }
  return sVar6;
}


// ================= pedal_channel_select @ 04e6f6 =================

/* pedal channel select / plausibility (KFPED region) */

void pedal_channel_select(void)

{
  undefined2 uStack_2;
  
  if (gear_index == '\a') {
    uRam304f2a = uRam01e774;
  }
  else {
    uRam304f2a = uRam01e772;
  }
  uRam3012ef = me7_lookup_1d_byte(0x1d1,6,rpmclass_oppoint);
  uStack_2 = (ushort)bRam0181c8;
  DAT_00fd1a = DAT_00fd1a & 0xc03f | (uStack_2 & 1) << 6 | ((uStack_2 & 2) >> 1) << 7 |
               ((uStack_2 & 4) >> 2) << 8 | ((uStack_2 & 8) >> 3) << 9 |
               ((uStack_2 & 0x10) >> 4) << 10 | ((uStack_2 & 0x20) >> 5) << 0xb |
               ((uStack_2 & 0x40) >> 6) << 0xc | (ushort)(bRam0181c8 >> 7) << 0xd;
  return;
}


// ================= load_model_kfurl @ 0d2c9a =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* air->load model: KFURL/KFURLSU speed-density, cam-blended (load-rl.md) */

void load_model_kfurl(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  ushort uVar4;
  ushort uVar5;
  short sVar6;
  ushort uVar7;
  ushort uVar8;
  
  if (cRam01ba6e == '\0') {
    sRam305642 = sRam304f02 + sRam304eca;
    if (sRam304f02 < 0 == sRam304eca < 0 && sRam304f02 + sRam304eca < 0 != sRam304f02 < 0) {
      sRam305642 = 0x7fff;
    }
    sRam305642 = sRam305642 >> 1;
    uVar8 = uRam304e96 - uRam304e90;
    if (uRam304e96 < uRam304e90) {
      uVar8 = 0;
    }
    sVar6 = (uRam304e96 >> 1) - uVar8;
    if (uRam304e96 >> 1 < uVar8) {
      if (sVar6 >= 0) {
        sVar6 = -0x8000;
      }
    }
    else if (sVar6 < 0) {
      sVar6 = 0x7fff;
    }
    sRam305644 = sRam305642 + sVar6;
    if (sRam305642 < 0 == sVar6 < 0 && sRam305642 + sVar6 < 0 != sRam305642 < 0) {
      sRam305644 = 0x7fff;
    }
    uVar8 = uRam304e96 - uRam304e92;
    if (uRam304e96 < uRam304e92) {
      uVar8 = 0;
    }
    sVar6 = uVar8 - (uRam304e96 >> 1);
    if (uVar8 < uRam304e96 >> 1) {
      if (sVar6 >= 0) {
        sVar6 = -0x8000;
      }
    }
    else if (sVar6 < 0) {
      sVar6 = 0x7fff;
    }
    sRam305640 = sRam305642 + sVar6;
    if (sRam305642 < 0 == sVar6 < 0 && sRam305642 + sVar6 < 0 != sRam305642 < 0) {
      sRam305640 = 0x7fff;
    }
    sVar6 = sRam305a24 + sRam301a2a;
    if (sRam305a24 < 0 == sRam301a2a < 0 && sRam305a24 + sRam301a2a < 0 != sRam305a24 < 0) {
      sVar6 = 0x7fff;
    }
    sVar6 = sVar6 >> 1;
    sRam30563e = sRam305640;
    if ((sVar6 - sRam305640 < 0 ==
         (sVar6 < 0 != sRam305640 < 0 && sVar6 - sRam305640 < 0 != sVar6 < 0)) &&
       (sRam30563e = sRam305644,
       sVar6 == sRam305644 ||
       sVar6 - sRam305644 < 0 !=
       (sVar6 < 0 != sRam305644 < 0 && sVar6 - sRam305644 < 0 != sVar6 < 0))) {
      sRam30563e = sVar6;
    }
    uVar8 = sRam30563e - sRam305640;
    if (sRam30563e < 0 != sRam305640 < 0 && sRam30563e - sRam305640 < 0 != sRam30563e < 0) {
      uVar8 = 0x8000;
    }
    uVar5 = sRam305644 - sRam305640;
    if (sRam305644 < 0 != sRam305640 < 0 && sRam305644 - sRam305640 < 0 != sRam305644 < 0) {
      uVar5 = 0x8000;
    }
    if ((((uVar8 == 0) || ((uVar8 == 0 && (uVar5 == 0)))) ||
        ((-1 < (short)uVar8 && ((short)uVar5 < 0)))) || (((short)uVar8 < 0 && (-1 < (short)uVar5))))
    {
      uRam302d80 = 0;
    }
    else if (uVar5 == 0) {
      uRam302d80 = 0xffff;
    }
    else {
      uVar4 = uVar5;
      if (((short)uVar8 < 0) && ((short)uVar5 < 0)) {
        uVar8 = func_0x042fe2(uVar8);
        uVar4 = func_0x042fe2(uVar5);
      }
      uVar1 = CONCAT22(uVar8 >> 1,uVar8 << 0xf);
      uVar2 = uVar1 / uVar4;
      MDL = (ushort)uVar2;
      MDH = (ushort)(uVar1 % (uint)uVar4);
      MDC = MDC | 0x10;
      uRam302d80 = MDL;
      if (uVar4 == 0 || 0xffff < uVar2) {
        uRam302d80 = 0xffff;
      }
    }
    if ((uVar5 == uRam027374 ||
         (short)(uVar5 - uRam027374) < 0 !=
         ((short)uVar5 < 0 != (short)uRam027374 < 0 &&
         (short)(uVar5 - uRam027374) < 0 != (short)uVar5 < 0)) || (uRam302d80 <= uRam027380)) {
      uRam302d80 = 0;
    }
    else if (uRam02737e < uRam302d80) {
      uRam302d80 = 0x8000;
    }
  }
  else {
    uRam026d80 = uRam02737c;
  }
  uRam302d88 = me7_lookup_2d_word_bilinear(0x3476,9,uRam304e8e,uRam307410);
  uRam305634 = me7_lookup_2d_word_bilinear(0x365e,9,uRam304e8e,uRam307410);
  uRam302d86 = me7_lookup_2d_word_bilinear(0x3382,9,uRam304e8e,uRam307410);
  uRam305632 = me7_lookup_2d_word_bilinear(0x356a,9,uRam304e8e,uRam307410);
  uVar5 = uRam027752;
  uVar8 = 0x8000 - uRam302d80;
  if (0x8000 < uRam302d80) {
    uVar8 = 0;
  }
  uVar8 = (ushort)((uint)uVar8 * (uint)uRam302d88 >> 0x10);
  uVar4 = uVar8 * 2;
  if (uVar8 * 2 < uVar8) {
    uVar4 = 0xffff;
  }
  uVar8 = (ushort)((uint)uRam302d80 * (uint)uRam302d86 >> 0x10);
  uVar7 = uVar8 * 2;
  if (uVar8 * 2 < uVar8) {
    uVar7 = 0xffff;
  }
  sRam302d82 = uVar7 + uVar4;
  if (uVar7 + uVar4 < uVar7 || uVar7 + uVar4 < uVar4) {
    sRam302d82 = -1;
  }
  uVar8 = 0x8000 - uRam302d80;
  if (0x8000 < uRam302d80) {
    uVar8 = 0;
  }
  uVar8 = (ushort)((uint)uVar8 * (uint)uRam305634 >> 0x10);
  uVar4 = uVar8 * 2;
  if (uVar8 * 2 < uVar8) {
    uVar4 = 0xffff;
  }
  MDL = (ushort)((uint)uRam306d80 * (uint)uRam305632);
  MDH = (ushort)((uint)uRam306d80 * (uint)uRam305632 >> 0x10);
  MDC = MDC | 0x10;
  uVar8 = MDH * 2;
  if (MDH * 2 < MDH) {
    uVar8 = 0xffff;
  }
  sRam305636 = uVar8 + uVar4;
  if (uVar8 + uVar4 < uVar8 || uVar8 + uVar4 < uVar4) {
    sRam305636 = -1;
  }
  uRam300da2 = me7_pt1_integrator(uRam027758,uRam026d82,uRam300da2._2_2_,(undefined2)uRam300da2);
  iVar3 = (uint)uRam304da4 * (uint)uRam305614;
  MDL = (ushort)iVar3;
  MDH = (ushort)((uint)iVar3 >> 0x10);
  MDC = MDC | 0x10;
  if ((iVar3 < 0) || ((BADTYPE)(MDH >> 0xe & 1))) {
    uRam305646 = 0xffff;
  }
  else {
    uRam305646 = MDH << 2 | MDL >> 0xe;
  }
  uRam300da6 = me7_pt1_integrator(uRam027758,sRam305636,uRam304da8,(undefined2)uRam300da6);
  uVar8 = (ushort)((uint)uRam304da8 * (uint)uRam30513c >> 0x10);
  uRam30563a = uVar8 * 2;
  if (uVar8 * 2 < uVar8) {
    uRam30563a = 0xffff;
  }
  uRam305638 = uRam30563a;
  uVar8 = (ushort)((uint)bRam304762 * 0x510a00 >> 0x10);
  uVar4 = uVar8 * 2;
  if (uVar8 * 2 < uVar8) {
    uVar4 = 0xffff;
  }
  uRam30563c = (ushort)((uint)uVar4 * (uint)uVar5 >> 0x10);
  uVar8 = (ushort)((uint)uRam30563c * 0x999a >> 0x10);
  sRam30564a = uVar8 * 2;
  if (uVar8 * 2 < uVar8) {
    sRam30564a = -1;
  }
  if (uRam305646 < uRam027754) {
    uRam026d84 = uRam027754;
    uRam305648 = uRam027754;
  }
  else if (uRam027756 < uRam305646) {
    uRam026d84 = uRam027756;
    uRam305648 = uRam027756;
  }
  else {
    uRam302d84 = uRam305646;
    uRam305648 = uRam305646;
  }
  if (uRam30563a < uRam027378) {
    uRam30563a = uRam027378;
  }
  else if (uRam02737a < uRam30563a) {
    uRam30563a = uRam02737a;
  }
  if ((_flags_start_phase & 0x4000) == 0) {
    if (uRam00f464 < 0x3fff) {
      uRam302d8a = uRam00f464 << 2;
    }
    else {
      uRam302d8a = 0xffff;
    }
  }
  else {
    iVar3 = (uint)uRam027376 * (uint)uRam00f464;
    uVar8 = (ushort)((uint)iVar3 >> 0x10);
    if ((iVar3 < 0) || ((BADTYPE)(uVar8 >> 0xe & 1))) {
      uRam302d8a = 0xffff;
    }
    else {
      uRam302d8a = uVar8 << 2 | (ushort)iVar3 >> 0xe;
    }
  }
  MDL = (short)((uint)uRam30563a * (uint)uRam302d84);
  MDH = (ushort)((uint)uRam30563a * (uint)uRam302d84 >> 0x10);
  MDC = MDC | 0x10;
  uRam302d8e = MDH >> 1;
  uRam302d90 = uRam302d8e;
  return;
}


// ================= rl_producer @ 0d34dc =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* assembles measured load rl -> loc_F47A / byte_F473(rl>>5) / loc_F478 (load-rl.md) */

void rl_producer(void)

{
  uint uVar1;
  ushort uVar2;
  
  uRam302daa = uRam302d9e;
  uRam302db4 = uRam302da2;
  uRam302db6 = uRam302da6;
  uRam00f476 = uRam302da4;
  uRam302db8 = uRam302da8;
  uRam301833 = (undefined1)((ushort)uRam302da4 >> 8);
  uRam302db0 = FUN_042c1c(uRam302bfe,uRam302da6,0x2155);
  uVar2 = uRam302db8 + uRam302d98;
  if (uRam302db8 + uRam302d98 < uRam302db8 || uRam302db8 + uRam302d98 < uRam302d98) {
    uVar2 = 0xffff;
  }
  if (uVar2 < 0x1fe1) {
    rl_byte = (undefined1)(uVar2 >> 5);
  }
  else {
    rl_byte = 0xff;
  }
  sRam302dac = uVar2 - _rl_w;
  if (uVar2 < _rl_w) {
    if (sRam302dac >= 0) {
      sRam302dac = -0x8000;
    }
  }
  else if (sRam302dac < 0) {
    sRam302dac = 0x7fff;
  }
  _rl_w_gshj = uVar2 + uRam302d94;
  if (uVar2 + uRam302d94 < uVar2 || uVar2 + uRam302d94 < uRam302d94) {
    _rl_w_gshj = -1;
  }
  _rl_w = uVar2;
  uRam302db2 = uRam302db0;
  _rl_scaled = FUN_042c1c(uRam302bfe,uRam302db8,0x2155);
  uVar1 = (uint)_rl_scaled * 0x666;
  MDL = (short)uVar1;
  MDH = (short)(uVar1 >> 0x10);
  MDC = MDC | 0x10;
  if (0xffffff < uVar1) {
    uRam00f472 = 0xff;
    return;
  }
  uRam00f472 = (char)(uVar1 >> 0x10);
  return;
}


// ================= throttle_pot_linearize @ 0c96fc =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CORRECTED (was maf_linearize - wrong): throttle-pot ch1 -> position feedback loc_F45E = (adc_ch1
   - learned-stop offset word_302CB4) x gain word_302CA2; offset/gain owned by etc_stop_learn_adapt,
   0 cal refs [C] */

ushort throttle_pot_linearize(void)

{
  bool bVar1;
  short sVar2;
  uint uVar3;
  ushort uVar4;
  short sVar5;
  ushort uVar6;
  
  if ((uRam00fd70 & 8) != 0) {
    uVar6 = _servo_pot_high_bound - _adc_ch2_raw;
    if (_servo_pot_high_bound < _adc_ch2_raw) {
      if ((short)uVar6 >= 0) {
        uVar6 = 0x8000;
      }
    }
    else if ((short)uVar6 < 0) {
      uVar6 = 0x7fff;
    }
    sVar5 = (short)uVar6 >> 0xf;
    if ((short)uVar6 < 0) {
      sVar5 = sVar5 * _servo_pot_lin_gain;
      MDC = MDC | 0x10;
    }
    MDL = (ushort)((uint)uVar6 * (uint)_servo_pot_lin_gain);
    MDH = (short)((uint)uVar6 * (uint)_servo_pot_lin_gain >> 0x10);
    MDC = MDC | 0x10;
    _throttle_pos_fb = (sVar5 + MDH) * 2 + (ushort)(MDL * 2 < MDL || MDL * 2 < MDL);
    return _servo_pot_lin_gain;
  }
  if ((uRam00fd70 & 2) == 0) {
    uVar6 = _adc_ch1_raw - _servo_pot_lin_offset;
    if (_adc_ch1_raw < _servo_pot_lin_offset) {
      if ((short)uVar6 >= 0) {
        uVar6 = 0x8000;
      }
    }
    else if ((short)uVar6 < 0) {
      uVar6 = 0x7fff;
    }
    sVar5 = (short)uVar6 >> 0xf;
    if ((short)uVar6 < 0) {
      sVar5 = sVar5 * _servo_pot_lin_gain;
      MDC = MDC | 0x10;
    }
    MDL = (ushort)((uint)uVar6 * (uint)_servo_pot_lin_gain);
    MDH = (short)((uint)uVar6 * (uint)_servo_pot_lin_gain >> 0x10);
    MDC = MDC | 0x10;
    _throttle_pos_fb = (sVar5 + MDH) * 2 + (ushort)(MDL * 2 < MDL || MDL * 2 < MDL);
    return MDL * 2;
  }
  uVar6 = _adc_ch3_raw * 4;
  if ((short)uVar6 < 0) {
    uVar6 = uVar6 ^ 0x8000;
    if ((short)uVar6 < 0 == sRam302cba < 0 || (short)(uVar6 - sRam302cba) < 0 == (short)uVar6 < 0) {
      uVar4 = uVar6 - sRam302cba ^ 0x8000;
      if ((short)uVar4 < 0) {
        uVar4 = 0x7fff;
      }
      goto LAB_0c9774;
    }
  }
  else {
    uVar4 = uVar6 - sRam302cba;
    if ((short)uVar6 < 0 == sRam302cba < 0 || (short)(uVar6 - sRam302cba) < 0 == (short)uVar6 < 0)
    goto LAB_0c9774;
  }
  uVar4 = 0x8000;
LAB_0c9774:
  sVar5 = (short)uVar4 >> 8;
  if (sVar5 < 0) {
    uVar3 = CONCAT22(-(ushort)(uVar4 * 0x100 != 0) - sVar5,uVar4 * -0x100) / (uint)uRam302cc0;
    sVar5 = (short)uVar3;
    if ((uRam302cc0 == 0 || 0xffff < uVar3) || (sVar5 < 0)) {
      sVar5 = -0x8000;
    }
    else {
      sVar5 = -sVar5;
    }
  }
  else {
    uVar3 = CONCAT22(sVar5,uVar4 * 0x100) / (uint)uRam302cc0;
    sVar5 = (short)uVar3;
    if ((uRam302cc0 == 0 || 0xffff < uVar3) || (sVar5 < 0)) {
      sVar5 = 0x7fff;
    }
  }
  bVar1 = 1 < (_servo_pot_lin_offset & 1);
  uVar6 = _servo_pot_lin_offset >> 1;
  sVar2 = (sVar5 - uVar6) - (ushort)bVar1;
  if ((sVar5 < 0 && (short)((sVar5 - uVar6) - (ushort)bVar1) < 0 != sVar5 < 0) ||
     (uVar4 = sVar2 - uVar6, sVar2 < 0 && (short)(sVar2 - uVar6) < 0 != sVar2 < 0)) {
    uVar4 = 0x8000;
  }
  sVar5 = (short)uVar4 >> 0xf;
  if ((short)uVar4 < 0) {
    sVar5 = sVar5 * _servo_pot_lin_gain;
  }
  MDL = (ushort)((uint)uVar4 * (uint)_servo_pot_lin_gain);
  MDH = (short)((uint)uVar4 * (uint)_servo_pot_lin_gain >> 0x10);
  MDC = MDC | 0x10;
  _throttle_pos_fb = (sVar5 + MDH) * 2 + (ushort)(MDL * 2 < MDL || MDL * 2 < MDL);
  return _servo_pot_lin_gain;
}


// ================= nmot_compute @ 098c42 =================

/* compute engine speed word_F410 (nmot) from crank period */

void nmot_compute(void)

{
  if (uRam30190a >> 1 < uRam301906) {
    MDL = (undefined2)(0x4c4b4 / (uint)uRam30190a);
    MDH = (undefined2)(0x4c4b4 % (uint)uRam30190a);
    MDC = MDC | 0x10;
    nmot_w = MDL;
    if (uRam30190a == 0 || 0xffff < 0x4c4b4 / (uint)uRam30190a) {
      nmot_w = 0xffff;
    }
  }
  return;
}


// ================= charge_model_estimator @ 0ad3d0 =================

/* WARNING: Removing unreachable block (ram,0x0ad3ea) */
/* WARNING: Removing unreachable block (ram,0x0ad824) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* manifold-pressure -> charge model: pressure-ratio cascade -> word_302C40/302C54 (charge.md) */

void charge_model_estimator(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  undefined2 uVar8;
  ushort uVar9;
  ushort uVar10;
  
  uVar1 = ((uint)_load_measured << 0x10) / (uint)(uRam30563a >> 1);
  uVar9 = (ushort)uVar1;
  if (uRam30563a >> 1 == 0 || 0xffff < uVar1) {
    uVar9 = 0xffff;
  }
  uVar10 = uVar9 + uRam305648;
  if (uVar9 + uRam305648 < uVar9 || uVar9 + uRam305648 < uRam305648) {
    uVar10 = 0xffff;
  }
  uVar1 = CONCAT22(uVar10 >> 1,uVar10 << 0xf) / (uint)uRam302dae;
  _charge_modeled = (ushort)uVar1;
  if (uRam302dae == 0 || 0xffff < uVar1) {
    _charge_modeled = 0xffff;
  }
  uVar1 = CONCAT22(_charge_modeled >> 1,_charge_modeled << 0xf);
  uVar2 = uVar1 / uRam302e28;
  MDL = (ushort)uVar2;
  MDH = (undefined2)(uVar1 % (uint)uRam302e28);
  MDC = MDC | 0x10;
  uVar9 = MDL;
  if (uRam302e28 == 0 || 0xffff < uVar2) {
    uVar9 = 0xffff;
  }
  uVar10 = uVar9 + uRam3053da;
  if (uVar9 + uRam3053da < uVar9 || uVar9 + uRam3053da < uRam3053da) {
    uVar10 = 0xffff;
  }
  uVar9 = uRam30561e;
  if (uRam30561e < uVar10) {
    uVar9 = uVar10;
  }
  uRam302c3c = uVar9;
  if ((flags_diag_cfg_b & 0x800) != 0) {
    uRam302c3c = uRam016ce8;
  }
  uRam301729 = (undefined1)(uRam302c3c >> 8);
  if ((uRam00fd24 & 0x4000) != 0) {
    if (bRam301863 == 0) {
      uRam00fd5e = uRam00fd5e | 0x1000;
      goto LAB_0ad4b2;
    }
    if (bRam301863 <= bRam013fe9) goto LAB_0ad4b2;
  }
  uRam00fd5e = uRam00fd5e & 0xefff;
LAB_0ad4b2:
  uVar8 = func_0x040b88(0x6d06,uRam302e2a);
  uRam300b34 = me7_pt1_integrator(uVar8,uRam302be6,uRam300b34._2_2_,(undefined2)uRam300b34);
  uVar10 = uRam302c10;
  if ((uRam00fd5e & 0x1000) == 0) {
    uVar10 = 0xffff;
  }
  iVar3 = ((uint)uVar9 * (uint)uRam302bc0 >> 0x10) * (uint)(-uVar10 - 1);
  uVar9 = (ushort)((uint)iVar3 >> 0x10);
  if ((iVar3 < 0) || ((BADTYPE)(uVar9 >> 0xe & 1))) {
    uVar9 = 0xffff;
  }
  else {
    uVar9 = uVar9 << 2 | (ushort)iVar3 >> 0xe;
  }
  uVar10 = (ushort)((uint)uVar10 * (uRam300b34 >> 0x10) >> 0x10);
  uRam302c46 = uVar10 + uVar9;
  if (uVar10 + uVar9 < uVar10 || uVar10 + uVar9 < uVar9) {
    uRam302c46 = 0xffff;
  }
  uVar1 = ((uint)bRam3014ec * 0x100 * (uint)uRam302c46) / 0x654d;
  uRam302c0e = (ushort)uVar1;
  if (0xffff < uVar1) {
    uRam302c0e = 0xffff;
  }
  if ((short)uRam302498 < 0) {
    uRam302c48 = uRam302498 + _load_measured;
    if (uRam302498 <= uRam302498 + _load_measured && _load_measured <= uRam302498 + _load_measured)
    {
      uRam302c48 = 0;
    }
  }
  else {
    uRam302c48 = uRam302498 + _load_measured;
    if (uRam302498 + _load_measured < uRam302498 || uRam302498 + _load_measured < _load_measured) {
      uRam302c48 = 0xffff;
    }
  }
  if ((uRam016ce4 <= nmot_w) && (uRam016ce6 <= nmot_w)) {
    uRam00fd5e = uRam00fd5e | 0x8000;
  }
  if ((uRam00fd5e & 0x8000) == 0) {
    uVar9 = (ushort)((uint)uRam016ce4 * (uint)bRam013fdf * 0x100 >> 0x10);
  }
  else {
    uVar9 = (ushort)((uint)uRam016ce6 * (uint)bRam013fdf * 0x100 >> 0x10);
  }
  uVar10 = uRam302bfe;
  if (uRam302bfe <= uVar9) {
    uVar10 = uVar9;
  }
  iVar3 = (uint)uRam302c48 * (uint)uVar10;
  uVar9 = (ushort)((uint)iVar3 >> 0x10);
  if ((iVar3 < 0) || ((BADTYPE)(uVar9 >> 0xe & 1))) {
    uVar9 = 0xffff;
  }
  else {
    uVar9 = uVar9 << 2 | (ushort)iVar3 >> 0xe;
  }
  uRam302c34 = (ushort)((uint)uVar9 * 0x3d7) >> 9 | (short)((uint)uVar9 * 0x3d7 >> 0x10) << 7;
  uRam302c32 = uRam302c34 - (uRam302e0a >> 8);
  if (uRam302c34 < uRam302e0a >> 8) {
    uRam302c32 = 0;
  }
  uVar1 = CONCAT22(_charge_modeled >> 1,_charge_modeled << 0xf) / (uint)uRam302c46;
  uRam302c44 = (ushort)uVar1;
  if (uRam302c46 == 0 || 0xffff < uVar1) {
    uRam302c44 = 0xffff;
  }
  uRam302c3e = uRam302c44;
  if (uRam302be2 < uRam302c44) {
    uRam302c3e = uRam302be2;
  }
  if (uRam302c44 < (ushort)PTR_DAT_016b56) {
    uRam00fd5e = uRam00fd5e & 0xf7ff;
    uRam302c42 = uRam302c44;
  }
  else {
    uRam302c42 = (ushort)PTR_DAT_016b56;
    uRam00fd5e = uRam00fd5e | 0x800;
  }
  uVar9 = (ushort)((uint)uRam302c42 * 2000 >> 0x10);
  uVar10 = uRam016768;
  if ((500 < uVar9) && (uVar10 = uRam016b50, uVar9 - 500 < 0x1f5)) {
    uVar10 = *(ushort *)((uint3)(uVar9 << 1) + 0x16380);
  }
  uRam302c0c = (ushort)((uint)uVar10 * (uint)uRam302c0e >> 0x10);
  uVar1 = CONCAT22(uRam302c32 >> 1,uRam302c32 << 0xf);
  uVar2 = uVar1 / uRam302c0c;
  MDL = (ushort)uVar2;
  MDH = (undefined2)(uVar1 % (uint)uRam302c0c);
  MDC = MDC | 0x10;
  uRam302c30 = MDL;
  if (uRam302c0c == 0 || 0xffff < uVar2) {
    uRam302c30 = 0xffff;
  }
  uRam302c38 = uRam302c30 - _DAT_303a7e;
  if (uRam302c30 < _DAT_303a7e) {
    uRam302c38 = 0;
  }
  uRam302c04 = _load_measured - uRam302c50;
  if (_load_measured < uRam302c50) {
    if ((short)uRam302c04 >= 0) {
      uRam302c04 = 0x8000;
    }
  }
  else if ((short)uRam302c04 < 0) {
    uRam302c04 = 0x7fff;
  }
  if ((short)uRam302c04 < 0) {
    if (uRam302c04 == 0x8000) {
      uRam302c04 = 0x7fff;
    }
    else {
      uRam302c04 = -uRam302c04;
    }
  }
  uRam302c50 = uRam302c4e;
  uRam302c4e = uRam302c4c;
  uRam302c4c = uRam302c4a;
  uRam302c4a = _load_measured;
  if (uRam302c04 < uRam016b9c) {
    PSW = PSW | 0x40;
  }
  else {
    PSW = PSW & 0xffbf;
  }
  uRam00fd5e = uRam00fd5e & 0xdfff | ((PSW & 0x40) >> 6) << 0xd;
  *(ushort *)((uint3)bRam300b3e * 2 + 0x302c26) = uRam302c38;
  bRam300b3e = bRam300b3e + 1;
  if (4 < bRam300b3e) {
    bRam300b3e = 0;
  }
  if ((uRam00fd5e & 0x2000) == 0) {
    uRam302c36 = uRam302c38;
  }
  else {
    bVar7 = 0;
    do {
      *(undefined2 *)((uint3)bVar7 * 2 + 0x302c12) = *(undefined2 *)((uint3)bVar7 * 2 + 0x302c26);
      bVar7 = bVar7 + 1;
    } while (bVar7 < 5);
    bVar7 = 0;
    do {
      bVar6 = 0;
      uVar9 = 0;
      bVar5 = 0;
      do {
        uVar10 = (ushort)bVar5 * 2 + 0xac12;
        if (uVar9 < *(ushort *)((uint3)uVar10 + 0x10000)) {
          uVar9 = *(ushort *)((uint3)uVar10 + 0x10000);
          bVar6 = bVar5;
        }
        bVar5 = bVar5 + 1;
      } while (bVar5 < 5);
      *(ushort *)((uint3)bVar7 * 2 + 0x302c1c) = uVar9;
      *(undefined2 *)((uint3)bVar6 * 2 + 0x302c12) = 0;
      bVar7 = bVar7 + 1;
    } while (bVar7 < 5);
    if ((uRam302c1c < uRam302c36) || (uRam302c36 < uRam302c24)) {
      uRam302c36 = uRam302c20;
    }
  }
  uRam300b3c = FUN_040d5c(0x6bf2,uRam302c36,nmot_w);
  if (_DAT_302c02 < uRam300b3c) {
    uRam300b3c = _DAT_302c02;
    uRam00fd5e = uRam00fd5e | 0x4000;
  }
  else {
    uRam00fd5e = uRam00fd5e & 0xbfff;
  }
  uRam302c06 = -uRam300b3c - 1;
  if (uRam302e28 < 0x8001) {
    uVar9 = uRam302e28 - (ushort)PTR_DAT_016b56;
    if (uRam302e28 < (ushort)PTR_DAT_016b56) {
      uVar9 = 0;
    }
    uVar10 = 0x8000 - (ushort)PTR_DAT_016b56;
    if (0x8000 < (ushort)PTR_DAT_016b56) {
      uVar10 = 0;
    }
    uVar1 = ((uint)uVar9 * (uint)uRam302c06) / (uint)uVar10;
    MDL = (ushort)uVar1;
    MDH = (undefined2)(((uint)uVar9 * (uint)uRam302c06) % (uint)uVar10);
    MDC = MDC | 0x10;
    uRam302c0a = MDL;
    if (uVar10 == 0 || 0xffff < uVar1) {
      uRam302c0a = 0xffff;
    }
  }
  else {
    uRam302c0a = uRam302c06;
    if (0x8000 < (ushort)PTR_DAT_016b56) {
      uRam302c0a = 0;
    }
  }
  if (((uRam00fd5e & 0x800) == 0) && (uRam302e28 < (ushort)PTR_DAT_016b56)) {
    uRam00fd5e = uRam00fd5e & 63999;
  }
  else {
    uRam00fd5e = uRam00fd5e | 0x600;
  }
  uRam302c5a = uRam300b3c;
  if (((uRam00fd5e & 0x1000) != 0) &&
     (uRam302c5a = uRam302c0a + uRam300b3c,
     uRam302c0a + uRam300b3c < uRam302c0a || uRam302c0a + uRam300b3c < uRam300b3c)) {
    uRam302c5a = 0xffff;
  }
  if (uRam302c58 <= uRam302c5a) {
    uRam302c5a = uRam302c58;
  }
  if ((uRam00fd7c & 0x100) != 0) {
    uRam302c5a = uRam302d7e;
  }
  if ((uRam00fd7c & 0x80) == 0) {
    uRam302c52 = func_0x040b88(0x6cea,uRam302c3e);
  }
  else {
    uRam302c52 = uRam302d7c;
  }
  uRam300b38 = me7_pt1_integrator(uRam302c52,uRam302c5a,uRam300b38._2_2_,(undefined2)uRam300b38);
  sRam302c56 = (short)((uint)uRam300b38 >> 0x10);
  uVar1 = uRam300b34;
  uVar4 = uRam300b38;
  if ((uRam00fd28 & 0x20) == 0) {
    if (((_flags_diag_cfg_a & 0x2000) == 0) && (nmot_rpmclass != '\0')) {
      _charge_filtered = sRam302c56;
      if ((uRam00fd04 & 1) != 0) {
        _charge_filtered = sRam016d04;
      }
    }
    else {
      _charge_filtered = func_0x040b88(0x6b9e,uRam301902);
      uVar1 = uRam300b34;
      uVar4 = uRam300b38;
    }
  }
  else {
    _charge_filtered = (ushort)bRam304710 << 8;
  }
  uRam300b38._2_2_ = (undefined2)((uint)uVar4 >> 0x10);
  uRam300b38._0_2_ = (undefined2)uVar4;
  uRam300b34._2_2_ = (undefined2)(uVar1 >> 0x10);
  uRam300b34._0_2_ = (undefined2)uVar1;
  return;
}


// ================= charge_model_limiter @ 0ac5de =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* charge ceiling + FD5C/FD5E region/limit machine (charge.md) */

ushort charge_model_limiter(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  short sVar4;
  short sVar5;
  byte bVar6;
  ushort uVar7;
  undefined2 uVar8;
  ushort uVar9;
  ushort uVar10;
  
  bVar6 = bRam013fdd;
  if (_throttle_pos_fb < 0) {
    uVar10 = 0;
  }
  else if (_throttle_pos_fb == 0xfff ||
           _throttle_pos_fb + -0xfff < 0 !=
           (_throttle_pos_fb < 0 && _throttle_pos_fb + -0xfff < 0 != _throttle_pos_fb < 0)) {
    uVar10 = _throttle_pos_fb << 4;
  }
  else {
    uVar10 = 0xfff0;
  }
  if (uVar10 < _DAT_302c02) {
    uRam00fd5e = uRam00fd5e & 0xff7f;
    uRam302c00 = uVar10;
  }
  else {
    uRam302c00 = _DAT_302c02;
    uRam00fd5e = uRam00fd5e | 0x80;
  }
  uRam00fd5c = uRam00fd5c & 0xf7ff | ((uRam00fd78 & 0x200) >> 9) << 0xb;
  uVar9 = uVar10 - _DAT_302c02;
  if (uVar10 < _DAT_302c02) {
    uVar9 = 0;
  }
  if (uVar9 == 0) {
    uVar10 = 0x8000;
  }
  else {
    uVar10 = 0x8000 - (ushort)PTR_DAT_016b56;
    if (0x8000 < (ushort)PTR_DAT_016b56) {
      uVar10 = 0;
    }
    uVar10 = (ushort)((uint)uVar9 * (uint)uVar10 >> 0x10);
    uVar9 = uVar10 * 2;
    if (uVar10 * 2 < uVar10) {
      uVar9 = 0xffff;
    }
    uVar10 = ~_DAT_302c02;
    uVar1 = (uint)(uVar9 >> 1) << 0x10;
    uVar2 = uVar1 / uVar10;
    MDL = (ushort)uVar2;
    MDH = (ushort)(uVar1 % (uint)uVar10);
    MDC = MDC | 0x10;
    uVar9 = MDL;
    if (uVar10 == 0 || 0xffff < uVar2) {
      uVar9 = 0xffff;
    }
    uVar10 = uVar9 + 0x8000;
    if (uVar9 + 0x8000 < 0x8000 || uVar9 + 0x8000 < uVar9) {
      uVar10 = 0xffff;
    }
  }
  uRam302bd6 = FUN_040d5c(0x6678,uRam302c00,nmot_w);
  uVar7 = uRam300b22;
  uVar9 = _DAT_303a7e + uRam302bd6;
  if (_DAT_303a7e + uRam302bd6 < _DAT_303a7e || _DAT_303a7e + uRam302bd6 < uRam302bd6) {
    uVar9 = 0xffff;
  }
  uVar10 = (ushort)((uint)uVar9 * (uint)uVar10 >> 0x10);
  uRam302bd8 = uVar10 * 2;
  if (uVar10 * 2 < uVar10) {
    uRam302bd8 = 0xffff;
  }
  iVar3 = (uint)uRam302bc0 * (uint)uRam00f460;
  uVar10 = (ushort)((uint)iVar3 >> 0x10);
  if ((iVar3 < 0) || ((BADTYPE)(uVar10 >> 0xe & 1))) {
    uRam302bc2 = 0xffff;
  }
  else {
    uRam302bc2 = uVar10 << 2 | (ushort)iVar3 >> 0xe;
  }
  uRam301727 = (undefined1)(uRam302bc2 >> 8);
  iVar3 = (uint)uRam302bc2 * (uint)bRam3014ec * 0x100;
  uVar10 = (ushort)((uint)iVar3 >> 0x10);
  if ((iVar3 < 0) || ((BADTYPE)(uVar10 >> 0xe & 1))) {
    _DAT_302bc4 = 0xffff;
  }
  else {
    _DAT_302bc4 = uVar10 << 2 | (ushort)iVar3 >> 0xe;
  }
  uVar10 = (ushort)((uint)uRam302bd8 * (uint)_DAT_302bc4 >> 0x10);
  sRam302bd2 = uVar10 * 2;
  if (uVar10 * 2 < uVar10) {
    sRam302bd2 = -1;
  }
  MDL = (ushort)((uint)uRam302bc2 * 0x654d);
  MDH = (ushort)((uint)uRam302bc2 * 0x654d >> 0x10);
  MDC = MDC | 0x10;
  if ((BADTYPE)(MDH >> 0xe)) {
    uRam302be6 = 0xffff;
  }
  else {
    uRam302be6 = MDH << 2 | MDL >> 0xe;
  }
  uRam301728 = (undefined1)(uRam302be6 >> 8);
  uRam300b16 = uRam300b22;
  uRam300b22 = uRam300af6;
  uRam300af6 = uRam300b0a;
  uRam300b0a = uRam300b1e;
  uRam300b1e = uRam300b26;
  uRam300b26 = _charge_modeled;
  sRam302bca = _charge_modeled - uVar7;
  if (_charge_modeled < uVar7) {
    if (sRam302bca >= 0) {
      sRam302bca = -0x8000;
    }
  }
  else if (sRam302bca < 0) {
    sRam302bca = 0x7fff;
  }
  uRam302bda = uRam302bd8;
  iRam300b10 = me7_slew_limiter((ushort)bRam013fe6 << 8,sRam302bca,iRam300b10._2_2_,
                                (undefined2)iRam300b10);
  sRam302bc8 = (short)((uint)iRam300b10 >> 0x10);
  if (sRam302bc8 == sRam016b5a ||
      sRam302bc8 - sRam016b5a < 0 !=
      (iRam300b10 < 0 != sRam016b5a < 0 && sRam302bc8 - sRam016b5a < 0 != iRam300b10 < 0)) {
    uRam00fd5e = uRam00fd5e & 0xffbf;
  }
  else {
    uRam00fd5e = uRam00fd5e | 0x40;
  }
  if (sRam302bca == sRam016b5c ||
      sRam302bca - sRam016b5c < 0 !=
      (sRam302bca < 0 != sRam016b5c < 0 && sRam302bca - sRam016b5c < 0 != sRam302bca < 0)) {
    PSW = PSW & 0xffbf;
  }
  else {
    PSW = PSW | 0x40;
  }
  uVar10 = ((PSW & 0x40) >> 6) << 5;
  if ((sRam302bca - ram0x016b58 < 0 ==
       (sRam302bca < 0 != ram0x016b58 < 0 && sRam302bca - ram0x016b58 < 0 != sRam302bca < 0)) ||
     ((uRam00fd5e & 0x40) != 0)) {
    uRam00fd5e = uRam00fd5e & 0xffcf | uVar10;
  }
  else {
    uRam00fd5e = uRam00fd5e & 0xffdf | uVar10 | 0x10;
  }
  uVar1 = CONCAT22(uRam00f476 >> 1,uRam00f476 << 0xf) / (uint)uRam00f464;
  uRam302be4 = (undefined2)uVar1;
  if (uRam00f464 == 0 || 0xffff < uVar1) {
    uRam302be4 = 0xffff;
  }
  uVar1 = CONCAT22(uRam302bfc >> 1,uRam302bfc << 0xf);
  uVar2 = uVar1 / uRam302bfa;
  MDL = (ushort)uVar2;
  MDH = (ushort)(uVar1 % (uint)uRam302bfa);
  MDC = MDC | 0x10;
  uVar10 = MDL;
  if (uRam302bfa == 0 || 0xffff < uVar2) {
    uVar10 = 0xffff;
  }
  sRam302bb2 = 0x7fff - uVar10;
  if (uVar10 < 0x8000) {
    if (sRam302bb2 < 0) {
      sRam302bb2 = 0x7fff;
    }
  }
  else if (sRam302bb2 >= 0) {
    sRam302bb2 = -0x8000;
  }
  if (((uRam00fd6e & 0x800) == 0) && ((uRam303b56 & 1) == 0)) {
    bRam301726 = bRam301726 & 0xfb;
  }
  else {
    bRam301726 = bRam301726 | 4;
  }
  if ((((bVar6 & 2) == 0) || ((uRam00fd5e & 0x400) == 0)) && ((bRam301726 & 4) == 0)) {
    uRam00fd5e = uRam00fd5e & 0xfffe;
  }
  else {
    uRam00fd5e = uRam00fd5e | 1;
  }
  if ((_flags_start_phase & 0x8000) == 0) {
    sRam300b18 = 0;
    sRam300b24 = sRam016b5e;
  }
  else if (sRam300b24 == 0) {
    sRam300b18 = 1;
  }
  else {
    sRam300b24 = sRam300b24 + -1;
  }
  if (((uRam00fd5e & 0x400) == 0) || (cRam013fde != '\0')) {
    sRam300afc = 1;
    cRam300b20 = cRam013fe3;
  }
  else if (cRam300b20 == '\0') {
    sRam300afc = 0;
  }
  else {
    cRam300b20 = cRam300b20 + -1;
  }
  if ((uRam00fd5e & 0x10) == 0) {
    if (sRam300b0e == 0) {
      uRam00fd5c = uRam00fd5c | 0x2000;
    }
    else {
      sRam300b0e = sRam300b0e + -1;
    }
  }
  else {
    uRam00fd5c = uRam00fd5c & 0xdfff;
    sRam300b0e = sRam016b60;
  }
  if (((DAT_00fd4e & 0x4000) == 0) || ((evap_monitor_flags & 8) == 0)) {
    if (((bRam301726 & 4) == 0) &&
       ((((uRam00fd5c & 0x2000) != 0 && (sRam300afc != 0)) && (sRam300b18 != 0)))) {
      PSW = PSW | 0x40;
    }
    else {
      PSW = PSW & 0xffbf;
    }
    uRam00fd5c = uRam00fd5c & 0xefff | ((PSW & 0x40) >> 6) << 0xc;
  }
  else {
    uRam00fd5c = uRam00fd5c & 0xefff;
  }
  if ((uRam00fd5e & 1) == 0) {
    if ((uRam00fd5c & 0x1000) != 0) {
      uVar8 = func_0x040b88(0x6b7a,uRam302be4,uRam01665a,uRam01665c);
      uRam3053d6 = me7_integrator_minmax
                             (uVar8,sRam302bb2 >> 1,uRam3053d6._2_2_,(undefined2)uRam3053d6);
      uRam306bbc = (undefined2)((uint)uRam3053d6 >> 0x10);
    }
  }
  else {
    uRam3053d6 = 0x40000000;
    uRam302bbc = 0x4000;
  }
  iVar3 = (uint)uRam302bbc * (uint)uRam303a7c;
  MDL = (ushort)iVar3;
  MDH = (ushort)((uint)iVar3 >> 0x10);
  MDC = MDC | 0x10;
  if ((iVar3 < 0) || ((BADTYPE)(MDH >> 0xe & 1))) {
    uRam302bba = 0xffff;
  }
  else {
    uRam302bba = MDH << 2 | MDL >> 0xe;
  }
  if (uRam302bbc < uRam01665c) {
    uVar10 = uRam01665c - uRam016658;
    if (uRam01665c < uRam016658) {
      uVar10 = 0;
    }
    if (uRam302bbc < uVar10) {
      uRam00fd5c = uRam00fd5c & 0x7fff;
    }
  }
  else {
    uRam00fd5c = uRam00fd5c | 0x8000;
  }
  if (uRam01665a < uRam302bbc) {
    uVar10 = uRam016656 + uRam01665a;
    if (uRam016656 + uRam01665a < uRam016656 || uRam016656 + uRam01665a < uRam01665a) {
      uVar10 = 0xffff;
    }
    if (uVar10 < uRam302bbc) {
      uRam00fd5c = uRam00fd5c & 0xbfff;
    }
  }
  else {
    uRam00fd5c = uRam00fd5c | 0x4000;
  }
  if ((uRam00fd3c & 4) == 0) {
    uRam302bbe = uRam302bbc;
    if ((bRam301726 & 4) == 0) {
      iRam300afe = (uint)uRam302bba << 0x10;
    }
    else {
      iRam300afe = me7_pt1_integrator((ushort)bRam013fe7 << 8,0x4000,iRam300afe._2_2_,
                                      (undefined2)iRam300afe);
      iVar3 = CONCAT22(MDH,MDL);
    }
  }
  else {
    uRam302bbe = 0x4000;
    iRam300afe = me7_pt1_integrator((ushort)bRam013fe7 << 8,0x4000,iRam300afe._2_2_,
                                    (undefined2)iRam300afe);
    iVar3 = CONCAT22(MDH,MDL);
  }
  uRam302bc0 = (ushort)((uint)iRam300afe >> 0x10);
  MDH = (ushort)((uint)iVar3 >> 0x10);
  MDL = (ushort)iVar3;
  if ((bVar6 & 1) == 0) {
    sRam300b2a = 1;
  }
  else {
    if (((uRam00fd5e & 0x20) == 0) || (uRam300b2e != 0)) {
      if (((uRam00fd5e & 0x400) != 0) && (uRam300b1a == 0)) {
        sRam300b2a = 1;
      }
    }
    else {
      sRam300b2a = 1;
    }
    if ((uRam00fd5c & 0x1000) == 0) {
      cRam300b14 = cRam013fe2;
      sRam300b30 = 0;
    }
    else if (cRam300b14 == '\0') {
      if (sRam300af8 == 0) {
        sRam300b2a = 1;
      }
      sRam300b30 = 1;
    }
    else {
      cRam300b14 = cRam300b14 + -1;
    }
    if (sRam302bb2 == -0x8000) {
      sRam302bb2 = -0x7fff;
    }
    if ((sRam302bb2 < 0) ||
       ((short)((uRam016652 >> 1) - sRam302bb2) < 0 !=
        (sRam302bb2 < 0 && (short)((uRam016652 >> 1) - sRam302bb2) < 0))) {
      if ((sRam302bb2 < 0) &&
         (sVar4 = -sRam302bb2, sVar5 = -(uRam016652 >> 1),
         sVar5 == sRam302bb2 ||
         sVar4 + sVar5 < 0 != (sVar4 < 0 && (short)(sVar4 - (uRam016652 >> 1)) < 0 != sVar4 < 0))) {
        sRam300afa = 1;
      }
      else {
        sRam300afa = 0;
      }
    }
    else {
      sRam300afa = 1;
    }
    if (sRam300afa == 0) {
      sRam300b08 = 0;
      cRam300b28 = cRam013fe1;
    }
    else if (cRam300b28 == '\0') {
      if (sRam300b06 == 0) {
        sRam300b2a = 1;
      }
      sRam300b08 = 1;
    }
    else {
      cRam300b28 = cRam300b28 + -1;
    }
    uRam300b2e = (uRam00fd5e & 0x20) >> 5;
    uRam300b1a = (uRam00fd5e & 0x400) >> 10;
    sRam300af8 = sRam300b30;
    sRam300b06 = sRam300b08;
  }
  if (sRam300b2a == 0) {
    if ((uRam00fd5e & 0x10) != 0) {
      uRam00fd5e = uRam00fd5e | 8;
    }
  }
  else {
    uRam00fd5e = uRam00fd5e & 0xfff7;
    sRam300b2a = 0;
  }
  uVar10 = func_0x040b88(0x665e,nmot_w);
  uRam302bc6 = uVar10;
  if ((bVar6 & 8) == 0) {
    uRam00fd5e = uRam00fd5e & 0xfffb;
  }
  else {
    sRam302bb4 = uRam302bea - uRam302bf4;
    if (uRam302bea < uRam302bf4) {
      if (sRam302bb4 >= 0) {
        sRam302bb4 = -0x8000;
      }
    }
    else if (sRam302bb4 < 0) {
      sRam302bb4 = 0x7fff;
    }
    if (uRam305234 < 0x1000) {
      cRam300b0c = cRam013fe4;
      if ((uRam302bf4 < uRam302be8) &&
         (sRam302bb4 != sRam016654 &&
          sRam302bb4 - sRam016654 < 0 ==
          (sRam302bb4 < 0 != sRam016654 < 0 && sRam302bb4 - sRam016654 < 0 != sRam302bb4 < 0))) {
        if (bRam300b2c == 0) {
          uVar10 = 0;
          if ((uRam00fd5e & 4) == 0) {
            if (uRam303a7a == 0xffff) {
              uVar10 = 0xffff;
            }
            else {
              uVar10 = uRam303a7a + 1;
              uRam303a7a = uVar10;
            }
          }
          uRam00fd5e = uRam00fd5e | 4;
        }
        else {
          bRam300b2c = bRam300b2c - 1;
          uVar10 = (ushort)bRam300b2c;
        }
      }
      else {
        uVar10 = (ushort)bRam013fe5;
        bRam300b2c = bRam013fe5;
      }
    }
    else {
      uVar10 = (ushort)bRam013fe5;
      bRam300b2c = bRam013fe5;
      if (cRam300b0c == '\0') {
        uRam00fd5e = uRam00fd5e & 0xfffb;
      }
      else {
        cRam300b0c = cRam300b0c + -1;
      }
    }
  }
  if (((((uRam00fd3c & 0x200) == 0) || ((uRam00fd5e & 8) != 0)) ||
      ((uVar10 = bRam013fdd & 0x20, (bRam013fdd & 0x20) == 0 &&
       (uVar10 = uRam303b56, (uRam303b56 & 1) != 0)))) || ((uRam00fd5e & 4) != 0)) {
    PSW = PSW | 0x40;
  }
  else {
    PSW = PSW & 0xffbf;
  }
  uRam00fd5e = uRam00fd5e & 0xfffd | ((PSW & 0x40) >> 6) << 1;
  return uVar10;
}


// ================= torque_arbitration @ 04d73a =================

/* torque coordinator arbitration: min(rlsol/VMAX/KFMIOP) -> word_31DAB2 (torque.md 3b) */

void torque_arbitration(void)

{
  ushort uVar1;
  ushort uVar2;
  
  uVar2 = uRam30512c;
  if (uRam3065ae <= uRam30512c) {
    uVar2 = uRam3025ae;
  }
  uVar1 = uRam302484;
  if (uVar2 < uRam302484) {
    uVar1 = uVar2;
  }
  uVar2 = uRam304f3c;
  if (uVar1 < uRam304f3c) {
    uVar2 = uVar1;
  }
  uVar1 = uVar2;
  if (((DAT_00fd1e & 0x1000) != 0) && (uVar1 = uRam3029b6, uVar2 < uRam3029b6)) {
    uVar1 = uVar2;
  }
  uRam301ab0 = uVar1;
  if (uRam302442 <= uVar1) {
    uRam301ab0 = uRam302442;
  }
  if (uRam301ab0 <= uRam30257e) {
    uRam301ab0 = uRam30257e;
  }
  uVar2 = uRam30243c;
  if (uVar1 < uRam30243c) {
    uVar2 = uVar1;
  }
  uVar1 = uRam30257e;
  if (uRam30257e < uVar2) {
    uVar1 = uVar2;
  }
  if ((uRam00fd20 & 0x400) == 0) {
    DAT_00fd1a = DAT_00fd1a & 0xffdf;
  }
  else if (((uRam00fd20 & 0x80) != 0) || (uVar1 != uRam30243c)) {
    DAT_00fd1a = DAT_00fd1a | 0x20;
  }
  if ((DAT_00fd1a & 0x20) == 0) {
    uRam301aae = uRam301aea - uRam3024a0;
    if (uRam301aea < uRam3024a0) {
      uRam301aae = 0;
    }
  }
  else {
    uRam301aae = uRam301afc;
    if ((uRam00fd24 & 0x20) != 0) {
      uRam301aae = 0;
    }
    if ((uRam301aae <= uVar1) && (uRam301aae = uVar1, uRam301aea < uVar1)) {
      uRam301aae = uRam301aea;
    }
  }
  uVar2 = uRam301aae;
  if ((uRam00fd20 & 0x400) != 0) {
    uVar2 = uRam301aae >> 1;
    if ((short)uRam3024f2 < 0) {
      uVar1 = uRam3024f2 + uVar2;
      if (uRam3024f2 <= uRam3024f2 + uVar2 && uVar2 <= uRam3024f2 + uVar2) {
        uVar1 = 0;
      }
    }
    else {
      uVar1 = uRam3024f2 + uVar2;
      if (uRam3024f2 + uVar2 < uRam3024f2 || uRam3024f2 + uVar2 < uVar2) {
        uVar1 = 0xffff;
      }
    }
    if (uVar1 < 0x8000) {
      uVar2 = uVar1 << 1;
    }
    else {
      uVar2 = 0xffff;
    }
  }
  uRam301ab2 = uRam301afc;
  if (uRam301afc <= uVar2) {
    uRam301ab2 = uVar2;
  }
  return;
}


// ================= torque_coordinator @ 04d86c =================

/* WARNING: Removing unreachable block (ram,0x04dd74) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* torque coordinator conditioning -> setpoint words 31E43C/3A/40/42 (torque.md 3b) */

void torque_coordinator(void)

{
  bool bVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  byte bVar7;
  byte bVar8;
  undefined2 uVar9;
  ushort uVar10;
  ushort uVar11;
  ushort uVar12;
  ushort uVar13;
  ushort uVar14;
  short sVar15;
  short sVar16;
  int iVar17;
  int iVar18;
  
  uRam30244e = uRam301abc;
  if (uRam301abc < uRam302cfe) {
    uRam30244e = uRam302cfe;
  }
  if (uRam0154ba < uRam30244e) {
    if (uRam0154b8 <= uRam30244e) {
      uRam00fd1c = uRam00fd1c | 0x8000;
    }
  }
  else {
    uRam00fd1c = uRam00fd1c & 0x7fff;
  }
  if (((uRam00fd1c & 0x8000) == 0) && ((uRam00fd72 & 0x1000) == 0)) {
    PSW = PSW & 0xffbf;
  }
  else {
    PSW = PSW | 0x40;
  }
  uVar12 = (PSW & 0x40) >> 6 ^ 1;
  if ((uRam301abc < uRam302cfe) && ((uRam00fd1c & 0x8000) != 0)) {
    PSW = PSW | 0x40;
  }
  else {
    PSW = PSW & 0xffbf;
  }
  uVar2 = ((PSW & 0x40) >> 6) << 8;
  uVar11 = uRam00fd1c & 0xdeff | uVar12 << 0xd | uVar2;
  uVar10 = uRam304f2c + uRam302536;
  if (uRam304f2c + uRam302536 < uRam304f2c || uRam304f2c + uRam302536 < uRam302536) {
    uVar10 = 0xffff;
  }
  uVar13 = uRam306534 + uRam302536;
  if (uRam306534 + uRam302536 < uRam306534 || uRam306534 + uRam302536 < uRam302536) {
    uVar13 = 0xffff;
  }
  uVar14 = uVar10 - uVar13;
  if (uVar10 < uVar13) {
    uVar14 = 0;
  }
  iVar18 = (uint)uRam30244e * (uint)uVar14;
  MDL = (ushort)iVar18;
  MDH = (ushort)((uint)iVar18 >> 0x10);
  MDC = MDC | 0x10;
  uVar13 = uVar13 >> 1;
  uVar10 = uVar13 + MDH;
  if (uVar13 + MDH < uVar13 || uVar13 + MDH < MDH) {
    uVar10 = 0xffff;
  }
  if ((short)uRam3024ea < 0) {
    uRam302446 = uRam3024ea + uVar10;
    if (uRam3024ea <= uRam3024ea + uVar10 && uVar10 <= uRam3024ea + uVar10) {
      uRam302446 = 0;
    }
  }
  else {
    uRam302446 = uRam3024ea + uVar10;
    if (uRam3024ea + uVar10 < uRam3024ea || uRam3024ea + uVar10 < uVar10) {
      uRam302446 = 0xffff;
    }
  }
  if (uRam302446 < 0x8000) {
    sRam302444 = uRam302446 << 1;
  }
  else {
    sRam302444 = -1;
  }
  if ((uRam00fd24 & 0x20) == 0) {
    if (uRam302446 < (ushort)bRam012d63 * 0x80) {
      uRam302446 = uRam302446 << 1;
    }
    else {
      uRam302446 = (ushort)bRam012d63 << 8;
    }
  }
  else {
    uRam302446 = 0;
  }
  uRam302472 = uRam302442;
  uRam302442 = uRam302446;
  if (uRam304f2c < uRam302446) {
    uRam302442 = uRam304f2c;
  }
  if ((((uRam00fd24 & 0x40) == 0) || (uVar12 == 0)) &&
     (((DAT_00fd1a & 0x1000) == 0 || ((uVar12 != 0 || ((uRam00fd1c & 0x4000) == 0)))))) {
    if (sRam302476 == 0) {
      DAT_00fd1e = DAT_00fd1e | 0x10;
    }
    else {
      sRam302476 = sRam302476 + -1;
    }
    DAT_00fd1e = DAT_00fd1e & 0xffdf;
  }
  else {
    sRam302476 = sRam0154f8;
    DAT_00fd1e = DAT_00fd1e & 0xffef | 0x20;
  }
  if ((((((DAT_00fd1e & 0x10) == 0) && ((DAT_00fd1e & 2) == 0)) && ((DAT_00fd4e & 0x400) == 0)) &&
      (sRam302b0a - sRam0154bc < 0 ==
       (sRam302b0a < 0 != sRam0154bc < 0 && sRam302b0a - sRam0154bc < 0 != sRam302b0a < 0))) &&
     ((((uRam00fd66 & 8) == 0 || ((DAT_00fd1a & 0x400) == 0)) && ((DAT_00fd1a & 0x4000) == 0)))) {
    uVar10 = uRam30244e - uRam302470;
    if (uRam30244e < uRam302470) {
      uVar10 = 0;
    }
    if ((uRam30242c < uVar10) ||
       ((((uRam00fd1c & 0x200) != 0 && ((uRam00fd24 & 0x20) == 0)) && (uRam301aea <= uRam30243e))))
    goto LAB_04d9f8;
    uRam00fd1c = uVar11;
    if ((DAT_00fd1e & 0x20) != 0) {
      uRam00fd1c = uVar11 | 0x200;
    }
  }
  else {
LAB_04d9f8:
    uRam00fd1c = uRam00fd1c & 0xdcff | uVar12 << 0xd | uVar2;
  }
  uRam302470 = uRam30244e;
  if (((uRam00fd1c & 0x200) == 0) || ((flags_torque_revlimit & 0x80) != 0)) {
    uVar12 = uRam301ab2;
    if ((flags_torque_revlimit & 0x80) != 0) {
      uVar12 = uRam301afc;
    }
    iVar17 = (uint)uVar12 << 0x10;
  }
  else {
    if ((((uRam00fd24 & 0x40) == 0) || (uVar9 = uRam0154c0, (uRam00fd1c & 0x2000) == 0)) &&
       (uVar9 = uRam0154c2, (uRam00fd1c & 0x2000) == 0)) {
      uVar9 = func_0x040b88(0x54c4,uRam302442);
      iVar18 = CONCAT22(MDH,MDL);
    }
    MDH = (ushort)((uint)iVar18 >> 0x10);
    MDL = (ushort)iVar18;
    iVar17 = me7_pt1_integrator(uVar9,uRam302442,iRam30245c._2_2_,(undefined2)iRam30245c);
    iVar18 = CONCAT22(MDH,MDL);
  }
  iRam30245c._2_2_ = (ushort)((uint)iVar17 >> 0x10);
  MDH = (ushort)((uint)iVar18 >> 0x10);
  MDL = (ushort)iVar18;
  uRam30243e = iRam30245c._2_2_;
  uRam00fd1c = uRam00fd1c & 0xffeb | ((DAT_00fd1a & 0x4000) >> 0xe) << 4 | (uRam00fd1c & 1) << 2;
  iRam30245c = iVar17;
  uRam302424 = func_0x041526(0x50fc,uRam0150fb,0x5108,0x5110,sRam30244a,gear_index);
  uRam302438 = uRam302430 - uRam302424;
  if (uRam302430 < uRam302424) {
    uRam302438 = 0;
  }
  if (((((uRam00fd1c & 0x100) == 0) || ((DAT_00fd1a & 0x2000) != 0)) && (uRam302442 < uRam302438))
     || ((((DAT_00fd1a & 0x1000) != 0 && ((uRam00fd1c & 0x2000) != 0)) &&
         ((uRam00fd1c & 0x4000) == 0)))) {
LAB_04daec:
    uRam00fd1c = uRam00fd1c | 0x20;
  }
  else {
    if ((uRam00fd38 & 2) != 0) {
      uVar12 = uRam30243c + uRam0150f0;
      if (uRam30243c + uRam0150f0 < uRam30243c || uRam30243c + uRam0150f0 < uRam0150f0) {
        uVar12 = 0xffff;
      }
      if (uVar12 < uRam301ab2) goto LAB_04daec;
    }
    uRam00fd1c = uRam00fd1c & 0xffdf;
  }
  uVar12 = ((uRam00fd1c & 0x2000) >> 0xd) << 0xe;
  if ((_flags_start_phase & 0x8000) == 0) {
    sRam30247a = sRam0154be;
    DAT_00fd1e = DAT_00fd1e & 0xff7f;
  }
  else if (sRam30247a == 0) {
    DAT_00fd1e = DAT_00fd1e | 0x80;
  }
  else {
    sRam30247a = sRam30247a + -1;
  }
  if (((((DAT_00fd1e & 2) == 0) && ((uRam303c1e & 1) == 0)) && (gear_index == 0)) &&
     ((vfzg_class < bRam012a0c && ((DAT_00fd1e & 0x80) != 0)))) {
    PSW = PSW | 0x40;
  }
  else {
    PSW = PSW & 0xffbf;
  }
  uVar2 = (PSW & 0x40) >> 6;
  uVar10 = uVar2 << 0xf;
  uVar11 = DAT_00fd1a & 0x7fff | uVar10;
  if ((((_flags_start_phase & 0x8000) == 0) || ((uRam00fd0e & 0x1000) == 0)) ||
     (((DAT_00fd1a & 0x800) != 0 && (uRam3025ae < uRam302442)))) {
    uRam00fd1c = uRam00fd1c & 0xbf7f | uVar12;
LAB_04dc12:
    uRam00fd1c = uRam00fd1c & 0xffbf;
  }
  else {
    if ((((((DAT_00fd1a & 0x40) == 0) || ((uRam00fd1c & 0x2000) != 0)) || (gear_index == 0)) ||
        (((uRam00fd1c & 0x100) != 0 && ((DAT_00fd1a & 0x2000) == 0)))) ||
       (((flags_torque_revlimit & 2) != 0 || ((flags_torque_revlimit & 0x20) != 0)))) {
LAB_04dba8:
      uRam00fd1c = uRam00fd1c & 0xbf7f | uVar12;
    }
    else {
      if ((DAT_00fd1a & 0x100) == 0) {
        PSW = PSW & 0xffbf | (uRam00fd3c & 1 ^ 1) << 6;
      }
      else {
        PSW = PSW & 0xffbf | ((uRam00fd66 & 0x20) >> 5 ^ 1) << 6;
      }
      if ((((PSW & 0x40) == 0) && ((uRam0150ee & 4) == 0)) || (vfzg_class < bRam012a0d))
      goto LAB_04dba8;
      uRam00fd1c = uRam00fd1c & 0xbfff | uVar12 | 0x80;
    }
    if ((short)uRam0150f8 < 0) {
      uRam302450 = uRam0150f8 + uRam302492;
      if (uRam0150f8 <= uRam0150f8 + uRam302492 && uRam302492 <= uRam0150f8 + uRam302492) {
        uRam302450 = 0;
      }
    }
    else {
      uRam302450 = uRam0150f8 + uRam302492;
      if (uRam0150f8 + uRam302492 < uRam0150f8 || uRam0150f8 + uRam302492 < uRam302492) {
        uRam302450 = 0xffff;
      }
    }
    if ((((DAT_00fd1a & 0x80) == 0) || ((uRam00fd24 & 0x20) != 0)) || (_rl_w <= uRam302450))
    goto LAB_04dc12;
    if (uVar2 == 0) {
      if ((gear_index != 0) && (bRam012a0b < vfzg_class)) {
        if ((DAT_00fd1a & 0x200) == 0) {
          PSW = PSW & 0xffbf | (uRam00fd3c & 1 ^ 1) << 6;
        }
        else {
          PSW = PSW & 0xffbf | ((uRam00fd66 & 0x20) >> 5 ^ 1) << 6;
        }
        if (((PSW & 0x40) != 0) && (((uRam00fd1c & 0x2000) != 0 || ((DAT_00fd1e & 2) == 0))))
        goto LAB_04dc0c;
      }
      goto LAB_04dc12;
    }
LAB_04dc0c:
    uRam00fd1c = uRam00fd1c | 0x40;
  }
  if ((DAT_00fd1a & 0x4000) == 0) {
    bVar1 = cRam3012f3 == '\0';
    cRam3012f3 = cRam3012f3 + -1;
    if (bVar1) {
      cRam3012f3 = '\0';
    }
    if (cRam3012f3 == '\0') {
      uRam00fd1c = uRam00fd1c & 0xfffe;
    }
  }
  uVar12 = uRam302440 - uRam302442;
  if (uRam302440 < uRam302442) {
    uVar12 = 0;
  }
  if (((uRam00fd1c & 0x40) == 0) || (((DAT_00fd1a & 0x4000) != 0 && (uVar12 < uRam302426)))) {
    DAT_00fd1a = DAT_00fd1a & 0x3fff | uVar10;
  }
  else {
    DAT_00fd1a = uVar11;
    if ((uRam00fd1c & 0x20) != 0) {
      uRam00fd1c = uRam00fd1c | 1;
      cRam3012f3 = '\x02';
      DAT_00fd1a = uVar11 | 0x4000;
    }
  }
  if (((uRam00fd1c & 0x40) == 0) || (((uRam00fd1c & 8) != 0 && (uVar12 < uRam302426)))) {
    uRam00fd1c = uRam00fd1c & 0xfff7;
  }
  else if (((uRam00fd1c & 0x100) == 0) || ((DAT_00fd1a & 0x2000) != 0)) {
    uVar12 = uRam302430 - uRam0150f2;
    if (uRam302430 < uRam0150f2) {
      uVar12 = 0;
    }
    if (uRam302442 < uVar12) {
      uRam00fd1c = uRam00fd1c | 8;
    }
  }
  if (((uRam00fd1c & 8) == 0) && ((uRam00fd1c & 1) == 0)) {
    uRam00fd1c = uRam00fd1c & 0xfffd;
  }
  else {
    uRam00fd1c = uRam00fd1c | 2;
  }
  if (((DAT_00fd1a & 0x4000) == 0) || ((uRam00fd1c & 0x10) != 0)) {
    if (((uRam00fd1c & 2) == 0) && ((uRam302472 <= uRam302442 || (uRam301ab2 <= uRam302442)))) {
      if (uRam301ab2 < uRam302442) goto LAB_04dce8;
      iRam302460._2_2_ = uRam302442;
      goto LAB_04dcfa;
    }
    iVar18 = me7_pt1_integrator(uRam302456,uRam302442,iRam302460._2_2_,(undefined2)iRam302460);
  }
  else {
    if ((DAT_00fd1a & 0x8000) == 0) {
LAB_04dce8:
      iRam302460._2_2_ = uRam301ab2;
    }
    else {
      uVar12 = func_0x040b88(0x54e6,nmot_w);
      iRam302460._2_2_ = uVar12 + uRam301ab2;
      if (uVar12 + uRam301ab2 < uVar12 || uVar12 + uRam301ab2 < uRam301ab2) {
        iRam302460._2_2_ = 0xffff;
      }
    }
LAB_04dcfa:
    iVar18 = (uint)iRam302460._2_2_ << 0x10;
  }
  iRam302460._2_2_ = (ushort)((uint)iVar18 >> 0x10);
  uRam302430 = iRam302460._2_2_;
  uVar12 = DAT_00fd1e & 0xfffb | ((DAT_00fd1e & 2) >> 1) << 2;
  sRam30244a = (uRam301ab2 >> 1) - (uRam302546 >> 1);
  if (uRam301ab2 >> 1 < uRam302546 >> 1) {
    if (sRam30244a >= 0) {
      sRam30244a = -0x8000;
    }
  }
  else if (sRam30244a < 0) {
    sRam30244a = 0x7fff;
  }
  uRam302422 = uRam302442 - uRam302432;
  if (uRam302442 < uRam302432) {
    uRam302422 = 0;
  }
  iRam302460 = iVar18;
  if ((uRam00fd1c & 0x400) == 0) {
    if ((DAT_00fd1e & 0x40) == 0) {
      DAT_00fd1e = uVar12;
      uRam302428 = func_0x0415de(uRam015170,0x5174,uRam015172,0x5184,0x5190,sRam30244a,nmot_w);
    }
    else {
      DAT_00fd1e = uVar12;
      uRam302428 = me7_lookup_2d_word_torque(0x51f0,0x4f5e,uRam301974,uRam301992);
    }
  }
  else {
    iVar18 = (uint)uRam3028f4 * 0x2535;
    MDL = (ushort)iVar18;
    MDH = (ushort)((uint)iVar18 >> 0x10);
    MDC = MDC | 0x10;
    if (iVar18 < 0) {
      uVar11 = 0xffff;
    }
    else {
      uVar11 = MDH << 2 | MDL >> 0xe;
    }
    sRam30242e = nmot_w - uVar11;
    if (nmot_w < uVar11) {
      if (sRam30242e >= 0) {
        sRam30242e = -0x8000;
      }
    }
    else if (sRam30242e < 0) {
      sRam30242e = 0x7fff;
    }
    DAT_00fd1e = uVar12;
    uRam302428 = func_0x041526(uRam015250,0x5252,uRam015251,0x5262,0x5266,sRam30242e,uRam30127f);
  }
  if (uRam302428 < uRam302422) {
    PSW = PSW | 0x40;
  }
  else {
    PSW = PSW & 0xffbf;
  }
  uVar11 = (PSW & 0x40) >> 6;
  uVar12 = DAT_00fd1e & 0xfffe | uVar11;
  if ((uRam00fd1c & 0x80) == 0) {
LAB_04de3c:
    DAT_00fd1e = DAT_00fd1e & 0xfffc | uVar11;
  }
  else {
    if ((DAT_00fd1e & 2) != 0) {
      uVar10 = uRam302442 - uRam302440;
      if (uRam302442 < uRam302440) {
        uVar10 = 0;
      }
      if (uVar10 < uRam30242a) goto LAB_04de3c;
    }
    DAT_00fd1e = uVar12;
    if (uVar11 != 0) {
      DAT_00fd1e = uVar12 | 2;
    }
  }
  if ((((DAT_00fd1e & 2) == 0) || ((DAT_00fd1e & 4) != 0)) &&
     (((DAT_00fd1e & 2) != 0 ||
      (((uRam302472 < uRam302442 || (uRam0150f6 <= uRam302422)) && (uRam301ab2 < uRam302442)))))) {
    uRam00fd1c = uRam00fd1c & 0xf7ff;
    sVar15 = (uRam302442 >> 3) - (uRam302432 >> 3);
    if (uRam302442 >> 3 < uRam302432 >> 3) {
      if (sVar15 >= 0) {
        sVar15 = -0x8000;
      }
    }
    else if (sVar15 < 0) {
      sVar15 = 0x7fff;
    }
    iRam302468 = me7_integrator_sat(uRam30245a,sVar15,iRam302468._2_2_,(undefined2)iRam302468);
    sVar16 = (short)((uint)iRam302468 >> 0x10);
    MDL = (ushort)((uint)uRam302432 * (uint)uRam302420);
    MDH = (ushort)((uint)uRam302432 * (uint)uRam302420 >> 0x10);
    MDC = MDC | 0x10;
    bVar1 = 1 < (MDH >> 1 & 1);
    uVar12 = MDH >> 2;
    sVar15 = (sVar16 - uVar12) - (ushort)bVar1;
    if ((iRam302468 < 0 && (short)((sVar16 - uVar12) - (ushort)bVar1) < 0 != iRam302468 < 0) ||
       (sVar16 = sVar15 - uVar12, sVar15 < 0 && (short)(sVar15 - uVar12) < 0 != sVar15 < 0)) {
      sVar16 = -0x8000;
    }
    iVar18 = me7_integrator_sat(uRam30245a,sVar16,iRam30246c._2_2_,(undefined2)iRam30246c);
    uVar3 = CONCAT22(MDH,MDL);
  }
  else {
    uVar12 = uRam00fd1c | 0x800;
    if (((DAT_00fd1e & 2) == 0) || ((DAT_00fd1e & 4) != 0)) {
      uVar11 = uRam301ab2;
      uRam00fd1c = uVar12;
      if (uRam301ab2 < uRam302442) {
        uVar11 = uRam302442;
      }
    }
    else if ((uRam00fd1c & 0x400) == 0) {
      uRam00fd1c = uVar12;
      uVar12 = FUN_040d5c(0x5430,uRam302442,nmot_w);
      uVar11 = uRam301ab2;
      if (uRam301ab2 <= uVar12) {
        uVar11 = uVar12;
      }
    }
    else {
      uVar11 = uRam302474;
      uRam00fd1c = uVar12;
      if (uRam302442 < uRam302474) {
        uVar11 = uRam302442;
      }
    }
    uVar3 = (uint)uVar11 * (uint)uRam302420;
    MDC = MDC | 0x10;
    iRam302468 = (uVar3 >> 0x11) << 0x10;
    iVar18 = (uint)(uVar11 >> 3) << 0x10;
  }
  iRam30246c._2_2_ = (ushort)((uint)iVar18 >> 0x10);
  MDH = (ushort)(uVar3 >> 0x10);
  MDL = (ushort)uVar3;
  if ((short)iRam30246c._2_2_ < 1) {
    uRam302432 = 0;
  }
  else if (iRam30246c._2_2_ < 0x2000) {
    uRam302432 = iRam30246c._2_2_ << 3;
  }
  else {
    uRam302432 = 0xffff;
  }
  uVar12 = uRam302434;
  if (((((((uRam00fd1c & 1) == 0) && ((uRam00fd1c & 0x200) == 0)) && ((uRam00fd1c & 0x80) != 0)) &&
       (((DAT_00fd1e & 2) == 0 && ((flags_torque_revlimit & 0x80) == 0)))) &&
      (sRam30244a - sRam0154b6 < 0 !=
       (sRam30244a < 0 != sRam0154b6 < 0 && sRam30244a - sRam0154b6 < 0 != sRam30244a < 0))) &&
     (uRam30243c < uRam0154b2)) {
    uRam302478 = uRam302478 >> 1;
    if ((short)uRam0150f4 < 0) {
      uVar11 = uRam0150f4 + uRam302478;
      if (uRam0150f4 <= uRam0150f4 + uRam302478 && uRam302478 <= uRam0150f4 + uRam302478) {
        uVar11 = 0;
      }
    }
    else {
      uVar11 = uRam0150f4 + uRam302478;
      if (uRam0150f4 + uRam302478 < uRam0150f4 || uRam0150f4 + uRam302478 < uRam302478) {
        uVar11 = 0xffff;
      }
    }
    if (uVar11 < uRam302442 >> 1) {
      if ((DAT_00fd1e & 8) == 0) {
        DAT_00fd1e = DAT_00fd1e | 8;
        uVar12 = uRam301ab2;
      }
      goto LAB_04dfe8;
    }
  }
  DAT_00fd1e = DAT_00fd1e & 0xfff7;
LAB_04dfe8:
  uRam302478 = uRam30243c;
  iRam30246c = iVar18;
  bVar7 = func_0x040ca4(0x29d7,DAT_301258,nmot_rpmclass);
  bVar8 = bVar7 - 0x40;
  if (bVar7 < 0x40) {
    bVar8 = 0;
  }
  MDL = (ushort)bVar8 * (ushort)*(byte *)((uint3)gear_index + 0x129c4);
  MDH = 0;
  MDC = MDC | 0x10;
  uVar11 = (MDL >> 7) + 0x40;
  if (0xff < uVar11) {
    uVar11 = 0xff;
  }
  uRam3012ec = (undefined1)uVar11;
  sRam30244c = uVar12 - uRam302546;
  if (uVar12 < uRam302546) {
    if (sRam30244c >= 0) {
      sRam30244c = -0x8000;
    }
  }
  else if (sRam30244c < 0) {
    sRam30244c = 0x7fff;
  }
  if ((uRam00fd1c & 0x400) == 0) {
    uVar10 = func_0x0415de(uRam015296,0x529a,uRam015298,0x52aa,0x52ba,sRam30244c,nmot_w);
  }
  else {
    uVar10 = func_0x0415de(uRam01533a,0x533e,uRam01533c,0x534e,0x5356,sRam30244c,nmot_w);
  }
  iVar18 = CONCAT22(uRam302466,uRam302464);
  uVar3 = (uint)uVar10 * (uint)uVar11;
  MDL = (ushort)uVar3;
  MDH = (ushort)(uVar3 >> 0x10);
  MDC = MDC | 0x10;
  uVar11 = (ushort)(uVar3 >> 6);
  if ((short)((uVar3 >> 6) >> 0x10) == 0) {
    uVar10 = uVar12 + uVar11;
    if (uVar12 + uVar11 < uVar12 || uVar12 + uVar11 < uVar11) {
      uVar10 = 0xffff;
    }
  }
  else {
    uVar10 = 0xffff;
  }
  uRam302434 = uRam302442;
  if (uVar10 <= uRam302442) {
    uRam302434 = uVar10;
  }
  uRam302440 = uRam30243e;
  if ((((uRam00fd1c & 0x200) == 0) && (uRam302440 = uRam302430, (uRam00fd1c & 2) == 0)) &&
     ((uRam302440 = uRam302432, (DAT_00fd1e & 2) == 0 &&
      (uRam302440 = uRam302434, (DAT_00fd1e & 8) == 0)))) {
    uRam302440 = uRam302442;
  }
  iVar17 = iRam30245c;
  iVar4 = iRam302460;
  iVar5 = iRam302468;
  iVar6 = iRam30246c;
  if ((flags_torque_revlimit & 0x80) == 0) {
    uRam30243c = uRam0154b0;
    if ((uRam0150ee & 0x100) == 0) {
      uVar12 = uRam302440 >> 1;
      if ((short)uRam30253e < 0) {
        uRam30243c = uRam30253e + uVar12;
        if (uRam30253e <= uRam30253e + uVar12 && uVar12 <= uRam30253e + uVar12) {
          uRam30243c = 0;
        }
      }
      else {
        uRam30243c = uRam30253e + uVar12;
        if (uRam30253e + uVar12 < uRam30253e || uRam30253e + uVar12 < uVar12) {
          uRam30243c = 0xffff;
        }
      }
      if (uRam30243c < 0x8000) {
        uRam30243c = uRam30243c << 1;
      }
      else {
        uRam30243c = 0xffff;
      }
    }
    if ((ushort)bRam012d63 * 0x100 < uRam30243c) {
      uRam30243c = (ushort)bRam012d63 << 8;
    }
    uRam3012f2 = (undefined1)(uRam30243c >> 8);
    if ((uRam0150ee & 0x80) == 0) {
      if ((uRam00fd1c & 1) == 0) {
        uVar12 = uRam302446 >> 1;
        if ((short)uRam30253e < 0) {
          uVar10 = uRam30253e + uVar12;
          if (uRam30253e <= uRam30253e + uVar12 && uVar12 <= uRam30253e + uVar12) {
            uVar10 = 0;
          }
        }
        else {
          uVar10 = uRam30253e + uVar12;
          if (uRam30253e + uVar12 < uRam30253e || uRam30253e + uVar12 < uVar12) {
            uVar10 = 0xffff;
          }
        }
        if (((DAT_00fd1e & 2) != 0) || (uVar11 = uVar10, (DAT_00fd1e & 8) != 0)) {
          if (((DAT_00fd1e & 2) == 0) && (((uRam0150ee & 0x200) == 0 || ((DAT_00fd1e & 8) == 0)))) {
            bRam3012ed = 0x40;
          }
          else {
            bVar7 = func_0x040ca4(0x29f1,DAT_301258,nmot_rpmclass);
            bVar8 = bVar7 - 0x40;
            if (bVar7 < 0x40) {
              bVar8 = 0;
            }
            uVar12 = (ushort)bVar8 * (ushort)*(byte *)((uint3)gear_index + 0x129cc);
            uVar3 = (uint)uVar12;
            MDC = MDC | 0x10;
            uVar12 = (uVar12 >> 7) + 0x40;
            if (0xff < uVar12) {
              uVar12 = 0xff;
            }
            bRam3012ed = (byte)uVar12;
          }
          bVar8 = bRam3012ed;
          MDH = (ushort)(uVar3 >> 0x10);
          MDL = (ushort)uVar3;
          if ((uRam0150ee & 0x20) == 0) {
            uRam302436 = uRam30243c;
            uVar12 = me7_lookup_2d_misc(uRam015396,0x5398,uRam015397,0x53a0,0x53b0,gear_index,
                                        uRam30243c);
            uVar3 = (uint)(uVar12 >> 1) * (uint)bVar8 * 0x100;
            uVar12 = (ushort)(uVar3 >> 0x10);
            MDC = MDC | 0x10;
            iVar17 = iRam30245c;
            iVar4 = iRam302460;
            iVar5 = iRam302468;
            iVar6 = iRam30246c;
            if ((BADTYPE)(uVar12 >> 0xe)) {
              uVar11 = 0xffff;
            }
            else {
              uVar11 = uVar12 << 2 | (ushort)uVar3 >> 0xe;
            }
          }
          else {
            uRam302436 = uRam30243c - uRam304f6a;
            if (uRam30243c < uRam304f6a) {
              uRam302436 = 0;
            }
            uVar11 = me7_lookup_2d_misc(uRam015396,0x5398,uRam015397,0x53a0,0x53b0,gear_index,
                                        uRam302436);
            uVar12 = uVar11 + uRam304f6a;
            if (uVar11 + uRam304f6a < uVar11 || uVar11 + uRam304f6a < uRam304f6a) {
              uVar12 = 0xffff;
            }
            uVar3 = (uint)(uVar12 >> 1) * (uint)bVar8 * 0x100;
            uVar12 = (ushort)(uVar3 >> 0x10);
            MDC = MDC | 0x10;
            iVar17 = iRam30245c;
            iVar4 = iRam302460;
            iVar5 = iRam302468;
            iVar6 = iRam30246c;
            if ((BADTYPE)(uVar12 >> 0xe)) {
              uVar11 = 0xffff;
            }
            else {
              uVar11 = uVar12 << 2 | (ushort)uVar3 >> 0xe;
            }
          }
          iVar18 = CONCAT22(uRam302466,uRam302464);
          if (uVar10 <= uVar11) {
            uVar11 = uVar10;
            iVar18 = CONCAT22(uRam302466,uRam302464);
          }
        }
      }
      else {
        if (((uRam00fd1c & 1) == 0) || ((uRam00fd1c & 4) != 0)) {
          iVar18 = me7_pt1_integrator(uRam302456,uRam302446,uRam302466,uRam302464);
          uVar3 = CONCAT22(MDH,MDL);
        }
        else {
          if ((uRam0150ee & 2) == 0) {
            uRam302466 = uRam302442;
          }
          else {
            uRam302466 = uRam302438;
            if (uRam302438 < uRam302442) {
              uRam302466 = uRam302442;
            }
          }
          iVar18 = (uint)uRam302466 << 0x10;
        }
        uVar12 = (ushort)((uint)iVar18 >> 0x11);
        iVar17 = iRam30245c;
        iVar4 = iRam302460;
        iVar5 = iRam302468;
        iVar6 = iRam30246c;
        if ((short)uRam30253e < 0) {
          uVar11 = uRam30253e + uVar12;
          if (uRam30253e <= uRam30253e + uVar12 && uVar12 <= uRam30253e + uVar12) {
            uVar11 = 0;
          }
        }
        else {
          uVar11 = uRam30253e + uVar12;
          if (uRam30253e + uVar12 < uRam30253e || uRam30253e + uVar12 < uVar12) {
            uVar11 = 0xffff;
          }
        }
      }
      if (uVar11 < 0x8000) {
        sRam30243a = uVar11 << 1;
      }
      else {
        sRam30243a = -1;
      }
    }
    else {
      sRam30243a = sRam0154b4;
    }
  }
  else {
    uRam30243c = 0;
    sRam30243a = 0;
    uRam3012f2 = 0;
  }
  uRam302466 = (ushort)((uint)iVar18 >> 0x10);
  uRam302464 = (undefined2)iVar18;
  iRam30246c._2_2_ = (ushort)((uint)iVar6 >> 0x10);
  iRam30246c._0_2_ = (undefined2)iVar6;
  iRam302468._2_2_ = (undefined2)((uint)iVar5 >> 0x10);
  iRam302468._0_2_ = (undefined2)iVar5;
  iRam302460._2_2_ = (ushort)((uint)iVar4 >> 0x10);
  iRam302460._0_2_ = (undefined2)iVar4;
  iRam30245c._2_2_ = (ushort)((uint)iVar17 >> 0x10);
  iRam30245c._0_2_ = (undefined2)iVar17;
  MDH = (ushort)(uVar3 >> 0x10);
  MDL = (ushort)uVar3;
  bRam3012f1 = (uRam00fd1c & 0x200) != 0;
  if ((uRam00fd1c & 0x40) != 0) {
    bRam3012f1 = bRam3012f1 | 2;
  }
  if ((DAT_00fd1a & 0x4000) != 0) {
    bRam3012f1 = bRam3012f1 | 4;
  }
  if ((uRam00fd1c & 1) != 0) {
    bRam3012f1 = bRam3012f1 | 8;
  }
  if ((uRam00fd1c & 0x80) != 0) {
    bRam3012f1 = bRam3012f1 | 0x10;
  }
  if ((DAT_00fd1e & 2) != 0) {
    bRam3012f1 = bRam3012f1 | 0x20;
  }
  if ((DAT_00fd1e & 8) != 0) {
    bRam3012f1 = bRam3012f1 | 0x40;
  }
  return;
}


// ================= torque_coord_init @ 04d84e =================

/* torque coordinator init prologue */

void torque_coord_init(void)

{
  uRam30245a = 0xccd;
  uRam302456 = 0xccd;
  uRam302420 = 0x8000;
  uRam30247a = uRam0154be;
  return;
}


// ================= torque_coord_stage2 @ 04e3ae =================

/* WARNING: Removing unreachable block (ram,0x04e434) */
/* torque coordinator next stage (sub_B81C callee) */

void torque_coord_stage2(void)

{
  short sVar1;
  uint uVar2;
  uint uVar3;
  ushort uVar4;
  bool bVar5;
  char cVar6;
  byte bVar7;
  ushort uVar8;
  
  uVar8 = uRam302454;
  if (sRam30244a - sRam302448 < 0 ==
      (sRam30244a < 0 != sRam302448 < 0 && sRam30244a - sRam302448 < 0 != sRam30244a < 0)) {
    uVar8 = uRam302452;
  }
  MDL = (ushort)((uint)uVar8 * (uint)bRam3012ef);
  MDH = (short)((uint)uVar8 * (uint)bRam3012ef >> 0x10);
  MDC = MDC | 0x10;
  uRam302456 = MDL >> 7 | MDH << 9;
  uRam302426 = func_0x042486(uRam01e550,0x2552,7,0x2562,7,sRam30244a);
  uVar8 = uRam302458;
  if ((DAT_00fd1e & 2) == 0) {
    bRam3012ee = 0x40;
    uRam30245a = uRam302458;
  }
  else {
    cVar6 = me7_lookup_2d_byte(0x1df,6,DAT_301258,nmot_rpmclass);
    bVar7 = (byte)((ushort)(byte)(-cVar6 - 1) * (ushort)*(byte *)((uint3)gear_index + 0x181c9) >> 8)
    ;
    bRam3012ee = 0x80 - bVar7;
    if (0x80 < bVar7) {
      bRam3012ee = 0;
    }
    bRam3012ee = bRam3012ee >> 1;
    uVar2 = CONCAT22(uVar8 >> 2,uVar8 << 0xe);
    uVar3 = uVar2 / ((uint)bRam3012ee << 8);
    MDL = (ushort)uVar3;
    MDH = (short)(uVar2 % ((uint)bRam3012ee << 8));
    MDC = MDC | 0x10;
    uRam30245a = MDL;
    if (bRam3012ee == 0 || 0xffff < uVar3) {
      uRam30245a = 0xffff;
    }
  }
  uRam30242a = func_0x042486(0x2584,7,(short)s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_012591 + 3,7,
                             sRam30244a);
  if (((uRam00fd66 & 8) == 0) && ((uRam00fd1c & 0x1000) != 0)) {
    uRam0192f4 = uRam018215;
  }
  if (cRam3012f4 == '\0') {
    DAT_00fd1e = DAT_00fd1e & 0xffbf;
  }
  else {
    cRam3012f4 = cRam3012f4 + -1;
    DAT_00fd1e = DAT_00fd1e | 0x40;
  }
  uVar8 = ((uRam00fd66 & 8) >> 3) << 0xc;
  if ((bRam301271 & 2) == 0) {
    if (cRam3012f5 == '\0') {
      bVar5 = false;
    }
    else {
      bVar5 = true;
      cRam3012f5 = cRam3012f5 + -1;
    }
  }
  else {
    bVar5 = true;
    uRam0192f5 = uRam018216;
  }
  if ((!bVar5) && ((bRam301271 & 0x80) != 0)) {
    bVar7 = bRam01820d;
    if ((bRam30127f != 0) && (bVar7 = bRam018214, bRam30127f < 8)) {
      bVar7 = *(byte *)((uint3)bRam30127f + 0x1820d);
    }
    if ((ushort)bVar7 == (ushort)nmot_rpmclass || (short)((ushort)bVar7 - (ushort)nmot_rpmclass) < 0
       ) {
      bVar7 = bRam018205;
      if ((bRam30127f != 0) && (bVar7 = bRam01820c, bRam30127f < 8)) {
        bVar7 = *(byte *)((uint3)bRam30127f + 0x18205);
      }
      if (-1 < (short)((ushort)bVar7 - (ushort)nmot_rpmclass)) {
        uRam00fd1c = uRam00fd1c & 0xefff | uVar8 | 0x400;
        uVar8 = *(ushort *)((uint3)bRam30127f * 2 + 0x1e572);
        uVar4 = uRam302548 * 2;
        sVar1 = ((short)uRam302548 >> 0xf) * 2 +
                (ushort)(uRam302548 * 2 < uRam302548 || uRam302548 * 2 < uRam302548) +
                ((short)uVar8 >> 0xf) + (ushort)(uVar4 + uVar8 < uVar4 || uVar4 + uVar8 < uVar8);
        if (sVar1 < 0) {
          sRam302474 = 0;
          return;
        }
        if (sVar1 == 0) {
          sRam302474 = uVar4 + uVar8;
          return;
        }
        sRam302474 = 0xffff;
        return;
      }
    }
  }
  uRam00fd1c = uRam00fd1c & 0xebff | uVar8;
  return;
}


// ================= vvt_intake_ctrl @ 049db8 =================

/* WARNING: Removing unreachable block (ram,0x04a5ac) */
/* WARNING: Removing unreachable block (ram,0x04a59c) */
/* WARNING: Removing unreachable block (ram,0x04a03e) */
/* VVT intake cam-phase PI controller -> duty byte_31D2CF (cam-timing.md) */

void vvt_intake_ctrl(void)

{
  bool bVar1;
  char cVar2;
  bool bVar3;
  ushort uVar4;
  ushort uVar5;
  uint uVar7;
  undefined4 uVar8;
  byte bVar9;
  ushort uVar10;
  short sVar11;
  short sVar12;
  undefined4 uVar13;
  int iVar6;
  
  if ((bRam301293 & 1) != 0) {
    if ((bRam012953 & 1) == 0) {
      sRam00f308 = sRam301a76;
    }
    else if ((bRam012953 & 4) == 0) {
      sVar11 = sRam301a76 - sRam00f308;
      if (sRam301a76 < 0 != sRam00f308 < 0 && sRam301a76 - sRam00f308 < 0 != sRam301a76 < 0) {
        sVar11 = -0x8000;
      }
      if (sVar11 < 0) {
        uVar13 = me7_slew_limiter(uRam0150bc,sRam301a76,uRam301a86._2_2_,(undefined2)uRam301a86);
      }
      else {
        uVar13 = me7_slew_limiter(uRam0150be,sRam301a76,uRam301a86._2_2_,(undefined2)uRam301a86);
      }
      uRam301a86._2_2_ = (short)((uint)uVar13 >> 0x10);
      sRam00f308 = uRam301a86._2_2_;
      uRam301a86 = uVar13;
    }
    else {
      sRam00f308 = sRam0150c8;
    }
  }
  uVar7 = CONCAT22(MDH,MDL);
  if ((bRam30318d & 8) != 0) {
    if ((bRam00f2e7 & 0x20) == 0) {
      sRam00f306 = sRam301a2a;
    }
    else {
      *(short *)((uint3)bRam3001ac * 2 + 0x3001ae) = sRam301a2a;
      if (bRam3001ac < 3) {
        bRam3001ac = bRam3001ac + 1;
      }
      else {
        bRam3001ac = 0;
      }
      sRam00f306 = sRam3001ae + sRam3001b0 + sRam3001b2 + sRam3001b4 >> 2;
    }
    uRam00f2ec = sRam00f306 - sRam00f304;
    if (sRam00f306 < 0 != sRam00f304 < 0 && sRam00f306 - sRam00f304 < 0 != sRam00f306 < 0) {
      uRam00f2ec = 0x8000;
    }
    sRam00f304 = sRam00f306;
    uVar7 = CONCAT22(MDH,MDL);
    if ((((((uRam00fd16 & 0x2000) == 0) &&
          (uVar7 = CONCAT22(MDH,MDL), (bRam012953 & 1) != 0 || (bRam00f2e7 & 8) == 0)) &&
         (uVar7 = CONCAT22(MDH,MDL),
         sRam301a2a - sRam0150c6 < 0 ==
         (sRam301a2a < 0 != sRam0150c6 < 0 && sRam301a2a - sRam0150c6 < 0 != sRam301a2a < 0))) &&
        ((uVar7 = CONCAT22(MDH,MDL),
         sRam301a2a == sRam0150c4 ||
         sRam301a2a - sRam0150c4 < 0 !=
         (sRam301a2a < 0 != sRam0150c4 < 0 && sRam301a2a - sRam0150c4 < 0 != sRam301a2a < 0) &&
         (uVar7 = CONCAT22(MDH,MDL), (bRam30318d & 8) != 0)))) &&
       (uVar7 = CONCAT22(MDH,MDL), (uRam00fd16 & 0x4000) != 0)) {
      uVar10 = uRam00f2ec;
      if ((short)uRam00f2ec < 0) {
        uVar10 = -uRam00f2ec;
      }
      uVar7 = (uint)uVar10 * (uint)bRam012955 * 0x100;
      MDC = MDC | 0x10;
      if ((uVar7 & 0xc0000000) == 0) {
        uVar10 = (short)(uVar7 >> 0x10) << 1 | (ushort)uVar7 >> 0xf;
        if ((short)uRam00f2ec < 0) {
          uVar10 = -uVar10;
        }
      }
      else if ((short)uRam00f2ec < 0) {
        uVar10 = 0x8000;
      }
      else {
        uVar10 = 0x7fff;
      }
      if (sRam00f2fa - sRam00f2f6 < 0 !=
          (sRam00f2fa < 0 != sRam00f2f6 < 0 && sRam00f2fa - sRam00f2f6 < 0 != sRam00f2fa < 0)) {
        bVar3 = sRam00f2f2 < 0;
        sVar11 = uVar10 + sRam00f2f2;
        sRam00f2f2 = uVar10 + sRam00f2f2;
        if ((short)uVar10 < 0 == bVar3 && sVar11 < 0 != (short)uVar10 < 0) {
          sRam00f2f2 = 0x7fff;
        }
        sVar11 = -sRam0150c2;
        if (-sRam00f2f2 == sRam0150c2 ||
            sVar11 + -sRam00f2f2 < 0 !=
            (sVar11 < 0 != sRam00f2f2 < 0 && sVar11 - sRam00f2f2 < 0 != sVar11 < 0)) {
          sVar11 = -sRam0150c0;
          if (sVar11 - sRam00f2f2 < 0 !=
              (sVar11 < 0 != sRam00f2f2 < 0 && sVar11 - sRam00f2f2 < 0 != sVar11 < 0)) {
            sRam00f2f2 = -sRam0150c0;
          }
        }
        else {
          sRam00f2f2 = -sRam0150c2;
        }
      }
      if (sRam00f2fa != sRam00f2fe &&
          sRam00f2fa - sRam00f2fe < 0 ==
          (sRam00f2fa < 0 != sRam00f2fe < 0 && sRam00f2fa - sRam00f2fe < 0 != sRam00f2fa < 0)) {
        bVar3 = sRam00f2f4 < 0;
        sVar11 = uVar10 + sRam00f2f4;
        sRam00f2f4 = uVar10 + sRam00f2f4;
        if ((short)uVar10 < 0 == bVar3 && sVar11 < 0 != (short)uVar10 < 0) {
          sRam00f2f4 = 0x7fff;
        }
        if (sRam0150c0 == sRam00f2f4 ||
            sRam0150c0 - sRam00f2f4 < 0 !=
            (sRam0150c0 < 0 != sRam00f2f4 < 0 && sRam0150c0 - sRam00f2f4 < 0 != sRam0150c0 < 0)) {
          if (sRam0150c2 - sRam00f2f4 < 0 !=
              (sRam0150c2 < 0 != sRam00f2f4 < 0 && sRam0150c2 - sRam00f2f4 < 0 != sRam0150c2 < 0)) {
            sRam00f2f4 = sRam0150c2;
          }
        }
        else {
          sRam00f2f4 = sRam0150c0;
        }
      }
    }
  }
  uVar13 = uRam301a86;
  uVar8 = uRam3001a8;
  if ((bRam301293 & 1) == 0) goto LAB_04a5ca;
  if ((bRam3012d2 & 1) == 0) {
    if ((bRam00f2e7 & 1) == 0) {
      if ((bRam00f2e6 & 0x40) == 0) {
        if ((short)uRam00f2ee < 0) {
          sRam00f2f0 = uRam00f2ee + sRam0150ac;
          if ((short)uRam00f2ee < 0 == sRam0150ac < 0 &&
              (short)(uRam00f2ee + sRam0150ac) < 0 != (short)uRam00f2ee < 0) {
            sRam00f2f0 = 0x7fff;
          }
          if (-1 < sRam00f2f0) goto LAB_04a0b8;
        }
        else {
          sRam00f2f0 = uRam00f2ee - sRam0150ac;
          if ((short)uRam00f2ee < 0 != sRam0150ac < 0 &&
              (short)(uRam00f2ee - sRam0150ac) < 0 != (short)uRam00f2ee < 0) {
            sRam00f2f0 = -0x8000;
          }
          if (sRam00f2f0 < 1) {
LAB_04a0b8:
            sRam00f2f0 = 0;
          }
        }
        sVar11 = uRam0150b6 + (ushort)bRam3012d0 * -0x100;
        if (uRam0150b6 < (ushort)bRam3012d0 * 0x100) {
          if (sVar11 >= 0) {
            sVar11 = -0x8000;
          }
        }
        else if (sVar11 < 0) {
          sVar11 = 0x7fff;
        }
        sVar12 = uRam0150ba + (ushort)bRam3012d0 * -0x100;
        if (uRam0150ba < (ushort)bRam3012d0 * 0x100) {
          if (sVar12 >= 0) {
            sVar12 = -0x8000;
          }
        }
        else if (sVar12 < 0) {
          sVar12 = 0x7fff;
        }
        if (sRam00f2f0 < 0) {
          MDL = (ushort)((int)sRam00f2f4 * (int)sRam00f2f0);
          MDH = (short)((uint)((int)sRam00f2f4 * (int)sRam00f2f0) >> 0x10);
          MDC = MDC | 0x10;
          sRam00f2fc = func_0x042ff8(MDH,MDL,sVar12);
          uVar7 = CONCAT22(MDH,MDL);
        }
        else {
          MDL = (ushort)((int)sRam00f2f2 * (int)sRam00f2f0);
          MDH = (short)((uint)((int)sRam00f2f2 * (int)sRam00f2f0) >> 0x10);
          MDC = MDC | 0x10;
          sRam00f2fc = func_0x042ff8(MDH,MDL,sVar11);
          uVar7 = CONCAT22(MDH,MDL);
        }
      }
      else {
        sRam00f2fc = sRam00f2f2;
      }
    }
    else {
      sRam00f2fc = sRam00f2f4;
    }
    MDH = (short)(uVar7 >> 0x10);
    MDL = (ushort)uVar7;
    bVar3 = 1 < (uRam0150ae & 1);
    uVar10 = uRam0150ae >> 1;
    sVar11 = (sRam0150a8 - uVar10) - (ushort)bVar3;
    if ((sRam0150a8 < 0 && (short)((sRam0150a8 - uVar10) - (ushort)bVar3) < 0 != sRam0150a8 < 0) ||
       (sVar12 = sVar11 - uVar10, sVar11 < 0 && (short)(sVar11 - uVar10) < 0 != sVar11 < 0)) {
      sVar12 = -0x8000;
    }
    if ((((bRam012953 & 1) == 0) && ((bRam3012bc & 1) != 0)) &&
       (sVar12 == sRam00f302 ||
        sVar12 - sRam00f302 < 0 !=
        (sVar12 < 0 != sRam00f302 < 0 && sVar12 - sRam00f302 < 0 != sVar12 < 0))) {
      bRam00f2e7 = bRam00f2e7 | 8;
    }
    else {
      bRam00f2e7 = bRam00f2e7 & 0xf7;
    }
    if ((bRam00f2e7 & 8) == 0) {
      sRam00f2f8 = sRam00f2fc;
    }
    else {
      sRam00f2f8 = 0;
    }
    if ((bRam00f2e7 & 1) == 0) {
      bRam00f2e8 = bRam00f2e9;
    }
    else {
      bRam00f2e8 = bRam00f2ea;
    }
    uRam3001a8 = me7_slew_limiter((ushort)bRam00f2e8 << 8,sRam00f2f8,uRam3001a8._2_2_,
                                  (undefined2)uRam3001a8);
    sRam00f2fa = (short)((uint)uRam3001a8 >> 0x10);
    if ((bRam30318d & 8) == 0) {
      sVar12 = sRam00f2fa >> 6;
      bVar3 = sRam00f304 < 0;
      sVar11 = sRam00f304 + sVar12;
      bVar1 = sRam00f304 < 0;
      sRam00f304 = sRam00f304 + sVar12;
      if (bVar3 == sVar12 < 0 && sVar11 < 0 != bVar1) {
        sRam00f304 = 0x7fff;
      }
    }
    MDL = 0xff / bRam00f2e8;
    if (bRam00f2e8 == 0) {
      MDL = 0xff;
    }
    uVar10 = MDL * 0x200 - 0x400;
    if (MDL * 0x200 < 0x400) {
      uVar10 = 0;
    }
    if ((short)uVar10 < 0) {
      iVar6 = (int)sRam00f2fa * (int)(short)(uVar10 & 0x7fff);
      uVar5 = (ushort)iVar6;
      uVar4 = sRam00f2fa * -0x8000;
      uVar10 = uVar5 + uVar4;
      sRam00f300 = (short)((uint)iVar6 >> 0x10) + (sRam00f2fa >> 1) +
                   (ushort)(uVar5 + uVar4 < uVar5 || uVar5 + uVar4 < uVar4);
      if (sRam00f300 < 0) {
        sRam00f300 = sRam00f300 + (ushort)(uVar10 - 1 < uVar10 || uVar10 != 0);
      }
    }
    else {
      iVar6 = (int)sRam00f2fa * (int)(short)uVar10;
      uVar10 = (ushort)iVar6;
      sRam00f300 = (short)((uint)iVar6 >> 0x10);
      if (iVar6 < 0) {
        sRam00f300 = sRam00f300 + (ushort)(uVar10 - 1 < uVar10 || uVar10 != 0);
      }
    }
    sRam00f302 = sRam00f300 + sRam00f304;
    if (sRam00f300 < 0 == sRam00f304 < 0 && sRam00f300 + sRam00f304 < 0 != sRam00f300 < 0) {
      sRam00f302 = 0x7fff;
    }
    if (((bRam012953 & 1) == 0) && ((bRam3012bc & 1) != 0)) {
      sRam301a80 = 0;
    }
    else {
      sRam301a80 = sRam00f308 - sRam00f302;
      if (sRam00f308 < 0 != sRam00f302 < 0 && sRam00f308 - sRam00f302 < 0 != sRam00f308 < 0) {
        sRam301a80 = -0x8000;
      }
    }
    sVar11 = -sRam0150b0;
    if (-sRam301a80 == sRam0150b0 ||
        sVar11 + -sRam301a80 < 0 !=
        (sVar11 < 0 != sRam301a80 < 0 && sVar11 - sRam301a80 < 0 != sVar11 < 0)) {
      bRam00f2e6 = bRam00f2e6 & 0xbf;
    }
    else {
      bRam00f2e6 = bRam00f2e6 | 0x40;
    }
    if ((((bRam30401f & 8) == 0) && ((bRam012953 & 1) != 0 || (bRam3012bc & 1) == 0)) &&
       (sRam0150b0 - sRam301a80 < 0 ==
        (sRam0150b0 < 0 != sRam301a80 < 0 && sRam0150b0 - sRam301a80 < 0 != sRam0150b0 < 0))) {
      bRam00f2e7 = bRam00f2e7 & 0xfe;
    }
    else {
      bRam00f2e7 = bRam00f2e7 | 1;
    }
    if (((bRam00f2e6 & 0x40) == 0) && ((bRam00f2e7 & 1) == 0)) {
      bRam00f2e6 = bRam00f2e6 | 0x10;
    }
    else {
      bRam00f2e6 = bRam00f2e6 & 0xef;
    }
    iVar6 = (int)sRam301a80 * (int)sRam0150b4;
    MDL = (ushort)iVar6;
    MDH = (short)((uint)iVar6 >> 0x10);
    MDC = MDC | 0x10;
    if (MDH == 0x3f || MDH + -0x3f < 0 != (iVar6 < 0 && MDH + -0x3f < 0 != iVar6 < 0)) {
      if (MDH + 0x40 < 0 == (-1 < iVar6 && MDH + 0x40 < 0 != iVar6 < 0)) {
        uRam00f2ee = MDL >> 7 | MDH << 9;
      }
      else {
        uRam00f2ee = 0x8000;
      }
    }
    else {
      uRam00f2ee = 0x7fff;
    }
    if (((bRam00f2e6 & 4) == 0) ||
       ((((bRam00f2e6 & 0x10) == 0 && ((bRam3001b6 & 4) != 0)) || ((bRam00f2e7 & 0x40) != 0)))) {
      bRam00f2e6 = bRam00f2e6 & 0xfe;
      bRam00f2e5 = bRam012963;
    }
    else if ((bRam00f2e6 & 0x10) != 0) {
      bRam00f2e6 = bRam00f2e6 | 1;
    }
    if (((bRam00f2e6 & 1) != 0) && (bVar3 = bRam00f2e5 < 2, bRam00f2e5 = bRam00f2e5 - 2, bVar3)) {
      bRam00f2e5 = 0;
    }
    if (bRam00f2e5 == 0) {
      bRam3001b6 = bRam3001b6 | 1;
    }
    else {
      bRam3001b6 = bRam3001b6 & 0xfe;
    }
    if ((bRam00f2e6 & 0x10) == 0) {
      bRam3001b6 = bRam3001b6 & 0xfb;
    }
    else {
      bRam3001b6 = bRam3001b6 | 4;
    }
    if (((bRam00f2e6 & 4) == 0) || ((bRam3001b6 & 2) != 0)) {
      cRam00f2e2 = '\0';
    }
    else if ((bRam3001b6 & 1) != 0) {
      if ((ushort)bRam3012d0 < uRam301a84 >> 8) {
        bVar3 = -1 < cRam00f2e2;
        cVar2 = cRam00f2e2 + '\x01';
        bVar1 = cRam00f2e2 < '\0';
        cRam00f2e2 = cRam00f2e2 + '\x01';
        if (bVar3 && cVar2 < '\0' != bVar1) {
          cRam00f2e2 = '\x7f';
        }
      }
      else if ((uRam301a84 >> 8 < (ushort)bRam3012d0) &&
              (bVar3 = cRam00f2e2 < '\0', cVar2 = cRam00f2e2 + -1, bVar1 = cRam00f2e2 < '\0',
              cRam00f2e2 = cRam00f2e2 + -1, bVar3 && cVar2 < '\0' != bVar1)) {
        cRam00f2e2 = -0x80;
      }
    }
    bVar9 = func_0x042fca((short)cRam00f2e2);
    if (bRam012952 < bVar9) {
      bRam3001b6 = bRam3001b6 | 2;
    }
    else {
      bRam3001b6 = bRam3001b6 & 0xfd;
    }
    if ((bRam3001b6 & 2) != 0) {
      if (cRam00f2e2 < '\x01') {
        bVar3 = bRam00f2e4 == 0;
        bRam00f2e4 = bRam00f2e4 - 1;
        if (bVar3) {
          bRam00f2e4 = 0;
        }
        if (bRam00f2e4 < bRam3001a7) {
          bRam00f2e4 = bRam3001a7;
        }
      }
      else {
        bVar3 = (byte)(bRam00f2e4 + 1) < bRam00f2e4;
        bVar1 = bRam00f2e4 == 0xff;
        bRam00f2e4 = bRam00f2e4 + 1;
        if (bVar3 || bVar1) {
          bRam00f2e4 = 0xff;
        }
        if (bRam3001a5 < bRam00f2e4) {
          bRam00f2e4 = bRam3001a5;
        }
      }
    }
    bRam3012d0 = bRam00f2e4;
    if ((bRam00f2e7 & 1) == 0) {
      if ((bRam00f2e6 & 0x40) == 0) {
        if ((short)uRam00f2ee < 1) {
          uRam301a84 = (ushort)bRam00f2e4 * 0x100 + uRam00f2ee;
          if ((ushort)bRam00f2e4 * 0x100 < -uRam00f2ee) {
            uRam301a84 = 0;
          }
        }
        else {
          uVar10 = (ushort)bRam00f2e4 * 0x100;
          uRam301a84 = uVar10 + uRam00f2ee;
          if (uVar10 + uRam00f2ee < uVar10 || uVar10 + uRam00f2ee < uRam00f2ee) {
            uRam301a84 = 0xffff;
          }
        }
      }
      else {
        uRam301a84 = uRam0150b6;
      }
    }
    else {
      uRam301a84 = uRam0150ba;
    }
    uVar7 = (uint)uRam301a84 * (uint)bRam00f2e3 * 0x100;
    uVar10 = (ushort)(uVar7 >> 0x10);
    MDC = MDC | 0x10;
    uRam301a82 = uVar10 * 2;
    if (uVar10 * 2 < uVar10) {
      uRam301a82 = 0xffff;
    }
    if (uRam301a82 < uRam0150b8) {
      bRam00f2e7 = bRam00f2e7 & 0xbf;
    }
    else {
      bRam00f2e7 = bRam00f2e7 | 0x40;
    }
    uVar13 = uRam301a86;
    uVar8 = uRam3001a8;
    if ((bRam00f2e7 & 4) != 0) {
      if ((bRam00f2e7 & 0x40) == 0) {
        uRam301a82 = -uRam301a82 - 1;
        goto LAB_04a5ca;
      }
LAB_04a592:
      uRam301a82 = -uRam0150b8 - 1;
      uVar13 = uRam301a86;
      uVar8 = uRam3001a8;
      goto LAB_04a5ca;
    }
    if ((bRam00f2e7 & 0x40) == 0) goto LAB_04a5ca;
  }
  else {
    bRam00f2e6 = bRam00f2e6 & 0xbf | 0x10;
    uRam301a84 = uRam0150ba;
    if (uRam0150ba < uRam0150b8) {
      bRam00f2e7 = bRam00f2e7 & 0xbe;
    }
    else {
      bRam00f2e7 = bRam00f2e7 & 0xfe | 0x40;
    }
    if ((bRam00f2e7 & 4) != 0) {
      if ((bRam00f2e7 & 0x40) == 0) {
        uRam301a82 = -uRam0150ba - 1;
        goto LAB_04a5ca;
      }
      goto LAB_04a592;
    }
    if ((bRam00f2e7 & 0x40) == 0) {
      uRam301a82 = uRam0150ba;
      goto LAB_04a5ca;
    }
  }
  uRam301a82 = uRam0150b8;
  uVar13 = uRam301a86;
  uVar8 = uRam3001a8;
LAB_04a5ca:
  uRam3001a8._2_2_ = (undefined2)((uint)uVar8 >> 0x10);
  uRam3001a8._0_2_ = (undefined2)uVar8;
  uRam301a86._2_2_ = (short)((uint)uVar13 >> 0x10);
  uRam301a86._0_2_ = (undefined2)uVar13;
  MDH = (short)(uVar7 >> 0x10);
  MDL = (ushort)uVar7;
  uRam3012cf = (char)(uRam301a84 >> 8);
  return;
}


// ================= vvt_exhaust_ctrl @ 04c878 =================

/* WARNING: Removing unreachable block (ram,0x04d05c) */
/* WARNING: Removing unreachable block (ram,0x04d04c) */
/* WARNING: Removing unreachable block (ram,0x04cafe) */
/* VVT exhaust cam-phase PI controller -> duty byte_31D2E5 (cam-timing.md) */

void vvt_exhaust_ctrl(void)

{
  bool bVar1;
  char cVar2;
  bool bVar3;
  ushort uVar4;
  ushort uVar5;
  uint uVar7;
  undefined4 uVar8;
  byte bVar9;
  short sVar10;
  short sVar11;
  ushort uVar12;
  undefined4 uVar13;
  int iVar6;
  
  if ((bRam301293 & 4) != 0) {
    if ((bRam0129b2 & 1) == 0) {
      sRam00f332 = sRam301a96;
    }
    else if ((bRam0129b2 & 4) == 0) {
      sVar10 = sRam301a96 - sRam00f332;
      if (sRam301a96 < 0 != sRam00f332 < 0 && sRam301a96 - sRam00f332 < 0 != sRam301a96 < 0) {
        sVar10 = -0x8000;
      }
      if (sVar10 < 0) {
        uVar13 = me7_slew_limiter(uRam0150e0,sRam301a96,uRam301aa6._2_2_,(undefined2)uRam301aa6);
      }
      else {
        uVar13 = me7_slew_limiter(uRam0150e2,sRam301a96,uRam301aa6._2_2_,(undefined2)uRam301aa6);
      }
      uRam301aa6._2_2_ = (short)((uint)uVar13 >> 0x10);
      sRam00f332 = uRam301aa6._2_2_;
      uRam301aa6 = uVar13;
    }
    else {
      sRam00f332 = sRam0150ec;
    }
  }
  uVar7 = CONCAT22(MDH,MDL);
  if ((bRam30318d & 4) != 0) {
    if ((bRam00f311 & 0x20) == 0) {
      sRam00f330 = sRam301a24;
    }
    else {
      *(short *)((uint3)bRam3001d2 * 2 + 0x3001d4) = sRam301a24;
      if (bRam3001d2 < 3) {
        bRam3001d2 = bRam3001d2 + 1;
      }
      else {
        bRam3001d2 = 0;
      }
      sRam00f330 = sRam3001d4 + sRam3001d6 + sRam3001d8 + sRam3001da >> 2;
    }
    uRam00f316 = sRam00f330 - sRam00f32c;
    if (sRam00f330 < 0 != sRam00f32c < 0 && sRam00f330 - sRam00f32c < 0 != sRam00f330 < 0) {
      uRam00f316 = 0x8000;
    }
    sRam00f32c = sRam00f330;
    uVar7 = CONCAT22(MDH,MDL);
    if ((((((uRam00fd16 & 0x2000) == 0) &&
          (uVar7 = CONCAT22(MDH,MDL), (bRam0129b2 & 1) != 0 || (bRam00f311 & 8) == 0)) &&
         (uVar7 = CONCAT22(MDH,MDL),
         sRam301a24 - sRam0150ea < 0 ==
         (sRam301a24 < 0 != sRam0150ea < 0 && sRam301a24 - sRam0150ea < 0 != sRam301a24 < 0))) &&
        ((uVar7 = CONCAT22(MDH,MDL),
         sRam301a24 == sRam0150e8 ||
         sRam301a24 - sRam0150e8 < 0 !=
         (sRam301a24 < 0 != sRam0150e8 < 0 && sRam301a24 - sRam0150e8 < 0 != sRam301a24 < 0) &&
         (uVar7 = CONCAT22(MDH,MDL), (bRam30318d & 4) != 0)))) &&
       (uVar7 = CONCAT22(MDH,MDL), (uRam00fd16 & 0x4000) != 0)) {
      uVar12 = uRam00f316;
      if ((short)uRam00f316 < 0) {
        uVar12 = -uRam00f316;
      }
      uVar7 = (uint)uVar12 * (uint)bRam0129b4 * 0x100;
      MDC = MDC | 0x10;
      if ((uVar7 & 0xc0000000) == 0) {
        uVar12 = (short)(uVar7 >> 0x10) << 1 | (ushort)uVar7 >> 0xf;
        if ((short)uRam00f316 < 0) {
          uVar12 = -uVar12;
        }
      }
      else if ((short)uRam00f316 < 0) {
        uVar12 = 0x8000;
      }
      else {
        uVar12 = 0x7fff;
      }
      if (sRam00f322 - sRam00f320 < 0 !=
          (sRam00f322 < 0 != sRam00f320 < 0 && sRam00f322 - sRam00f320 < 0 != sRam00f322 < 0)) {
        bVar3 = sRam00f31c < 0;
        sVar10 = uVar12 + sRam00f31c;
        sRam00f31c = uVar12 + sRam00f31c;
        if ((short)uVar12 < 0 == bVar3 && sVar10 < 0 != (short)uVar12 < 0) {
          sRam00f31c = 0x7fff;
        }
        sVar10 = -sRam0150e6;
        if (-sRam00f31c == sRam0150e6 ||
            sVar10 + -sRam00f31c < 0 !=
            (sVar10 < 0 != sRam00f31c < 0 && sVar10 - sRam00f31c < 0 != sVar10 < 0)) {
          sVar10 = -sRam0150e4;
          if (sVar10 - sRam00f31c < 0 !=
              (sVar10 < 0 != sRam00f31c < 0 && sVar10 - sRam00f31c < 0 != sVar10 < 0)) {
            sRam00f31c = -sRam0150e4;
          }
        }
        else {
          sRam00f31c = -sRam0150e6;
        }
      }
      if (sRam00f322 != sRam00f328 &&
          sRam00f322 - sRam00f328 < 0 ==
          (sRam00f322 < 0 != sRam00f328 < 0 && sRam00f322 - sRam00f328 < 0 != sRam00f322 < 0)) {
        bVar3 = sRam00f31e < 0;
        sVar10 = uVar12 + sRam00f31e;
        sRam00f31e = uVar12 + sRam00f31e;
        if ((short)uVar12 < 0 == bVar3 && sVar10 < 0 != (short)uVar12 < 0) {
          sRam00f31e = 0x7fff;
        }
        if (sRam0150e4 == sRam00f31e ||
            sRam0150e4 - sRam00f31e < 0 !=
            (sRam0150e4 < 0 != sRam00f31e < 0 && sRam0150e4 - sRam00f31e < 0 != sRam0150e4 < 0)) {
          if (sRam0150e6 - sRam00f31e < 0 !=
              (sRam0150e6 < 0 != sRam00f31e < 0 && sRam0150e6 - sRam00f31e < 0 != sRam0150e6 < 0)) {
            sRam00f31e = sRam0150e6;
          }
        }
        else {
          sRam00f31e = sRam0150e4;
        }
      }
    }
  }
  uVar13 = uRam301aa6;
  uVar8 = uRam3001ce;
  if ((bRam301293 & 4) == 0) goto LAB_04d07a;
  if ((bRam3012e8 & 1) == 0) {
    if ((bRam00f311 & 1) == 0) {
      if ((bRam00f310 & 0x40) == 0) {
        if ((short)uRam00f318 < 0) {
          sRam00f31a = uRam00f318 + sRam0150d0;
          if ((short)uRam00f318 < 0 == sRam0150d0 < 0 &&
              (short)(uRam00f318 + sRam0150d0) < 0 != (short)uRam00f318 < 0) {
            sRam00f31a = 0x7fff;
          }
          if (-1 < sRam00f31a) goto LAB_04cb78;
        }
        else {
          sRam00f31a = uRam00f318 - sRam0150d0;
          if ((short)uRam00f318 < 0 != sRam0150d0 < 0 &&
              (short)(uRam00f318 - sRam0150d0) < 0 != (short)uRam00f318 < 0) {
            sRam00f31a = -0x8000;
          }
          if (sRam00f31a < 1) {
LAB_04cb78:
            sRam00f31a = 0;
          }
        }
        sVar10 = uRam0150da + (ushort)bRam3012e6 * -0x100;
        if (uRam0150da < (ushort)bRam3012e6 * 0x100) {
          if (sVar10 >= 0) {
            sVar10 = -0x8000;
          }
        }
        else if (sVar10 < 0) {
          sVar10 = 0x7fff;
        }
        sVar11 = uRam0150de + (ushort)bRam3012e6 * -0x100;
        if (uRam0150de < (ushort)bRam3012e6 * 0x100) {
          if (sVar11 >= 0) {
            sVar11 = -0x8000;
          }
        }
        else if (sVar11 < 0) {
          sVar11 = 0x7fff;
        }
        if (sRam00f31a < 0) {
          MDL = (ushort)((int)sRam00f31e * (int)sRam00f31a);
          MDH = (short)((uint)((int)sRam00f31e * (int)sRam00f31a) >> 0x10);
          MDC = MDC | 0x10;
          sRam00f326 = func_0x042ff8(MDH,MDL,sVar11);
          uVar7 = CONCAT22(MDH,MDL);
        }
        else {
          MDL = (ushort)((int)sRam00f31c * (int)sRam00f31a);
          MDH = (short)((uint)((int)sRam00f31c * (int)sRam00f31a) >> 0x10);
          MDC = MDC | 0x10;
          sRam00f326 = func_0x042ff8(MDH,MDL,sVar10);
          uVar7 = CONCAT22(MDH,MDL);
        }
      }
      else {
        sRam00f326 = sRam00f31c;
      }
    }
    else {
      sRam00f326 = sRam00f31e;
    }
    MDH = (short)(uVar7 >> 0x10);
    MDL = (ushort)uVar7;
    bVar3 = 1 < (uRam0150d2 & 1);
    uVar12 = uRam0150d2 >> 1;
    sVar10 = (sRam01e44a - uVar12) - (ushort)bVar3;
    if ((sRam01e44a < 0 && (short)((sRam01e44a - uVar12) - (ushort)bVar3) < 0 != sRam01e44a < 0) ||
       (sVar11 = sVar10 - uVar12, sVar10 < 0 && (short)(sVar10 - uVar12) < 0 != sVar10 < 0)) {
      sVar11 = -0x8000;
    }
    if ((((bRam0129b2 & 1) == 0) && ((uRam00fd18 & 0x8000) != 0)) &&
       (sVar11 == sRam00f32e ||
        sVar11 - sRam00f32e < 0 !=
        (sVar11 < 0 != sRam00f32e < 0 && sVar11 - sRam00f32e < 0 != sVar11 < 0))) {
      bRam00f311 = bRam00f311 | 8;
    }
    else {
      bRam00f311 = bRam00f311 & 0xf7;
    }
    if ((bRam00f311 & 8) == 0) {
      sRam00f324 = sRam00f326;
    }
    else {
      sRam00f324 = 0;
    }
    if ((bRam00f311 & 1) == 0) {
      bRam00f312 = bRam00f313;
    }
    else {
      bRam00f312 = bRam00f314;
    }
    uRam3001ce = me7_slew_limiter((ushort)bRam00f312 << 8,sRam00f324,uRam3001ce._2_2_,
                                  (undefined2)uRam3001ce);
    sRam00f322 = (short)((uint)uRam3001ce >> 0x10);
    if ((bRam30318d & 4) == 0) {
      sVar11 = sRam00f322 >> 6;
      bVar3 = sRam00f32c < 0;
      sVar10 = sRam00f32c + sVar11;
      bVar1 = sRam00f32c < 0;
      sRam00f32c = sRam00f32c + sVar11;
      if (bVar3 == sVar11 < 0 && sVar10 < 0 != bVar1) {
        sRam00f32c = 0x7fff;
      }
    }
    MDL = 0xff / bRam00f312;
    if (bRam00f312 == 0) {
      MDL = 0xff;
    }
    uVar12 = MDL * 0x200 - 0x400;
    if (MDL * 0x200 < 0x400) {
      uVar12 = 0;
    }
    if ((short)uVar12 < 0) {
      iVar6 = (int)sRam00f322 * (int)(short)(uVar12 & 0x7fff);
      uVar5 = (ushort)iVar6;
      uVar4 = sRam00f322 * -0x8000;
      uVar12 = uVar5 + uVar4;
      sRam00f32a = (short)((uint)iVar6 >> 0x10) + (sRam00f322 >> 1) +
                   (ushort)(uVar5 + uVar4 < uVar5 || uVar5 + uVar4 < uVar4);
      if (sRam00f32a < 0) {
        sRam00f32a = sRam00f32a + (ushort)(uVar12 - 1 < uVar12 || uVar12 != 0);
      }
    }
    else {
      iVar6 = (int)sRam00f322 * (int)(short)uVar12;
      uVar12 = (ushort)iVar6;
      sRam00f32a = (short)((uint)iVar6 >> 0x10);
      if (iVar6 < 0) {
        sRam00f32a = sRam00f32a + (ushort)(uVar12 - 1 < uVar12 || uVar12 != 0);
      }
    }
    sRam00f32e = sRam00f32a + sRam00f32c;
    if (sRam00f32a < 0 == sRam00f32c < 0 && sRam00f32a + sRam00f32c < 0 != sRam00f32a < 0) {
      sRam00f32e = 0x7fff;
    }
    if (((bRam0129b2 & 1) == 0) && ((uRam00fd18 & 0x8000) != 0)) {
      sRam301aa0 = 0;
    }
    else {
      sRam301aa0 = sRam00f332 - sRam00f32e;
      if (sRam00f332 < 0 != sRam00f32e < 0 && sRam00f332 - sRam00f32e < 0 != sRam00f332 < 0) {
        sRam301aa0 = -0x8000;
      }
    }
    if ((bRam0129b2 & 1) == 0) {
      uVar12 = uRam00fd18 >> 0xf;
    }
    else {
      uVar12 = 0;
    }
    sVar10 = -sRam0150d4;
    if (-sRam301aa0 == sRam0150d4 ||
        sVar10 + -sRam301aa0 < 0 !=
        (sVar10 < 0 != sRam301aa0 < 0 && sVar10 - sRam301aa0 < 0 != sVar10 < 0)) {
      bRam00f310 = bRam00f310 & 0xbf;
    }
    else {
      bRam00f310 = bRam00f310 | 0x40;
    }
    if ((((bRam30401f & 2) == 0) && (uVar12 == 0)) &&
       (sRam0150d4 - sRam301aa0 < 0 ==
        (sRam0150d4 < 0 != sRam301aa0 < 0 && sRam0150d4 - sRam301aa0 < 0 != sRam0150d4 < 0))) {
      bRam00f311 = bRam00f311 & 0xfe;
    }
    else {
      bRam00f311 = bRam00f311 | 1;
    }
    if (((bRam00f310 & 0x40) == 0) && ((bRam00f311 & 1) == 0)) {
      bRam00f310 = bRam00f310 | 0x10;
    }
    else {
      bRam00f310 = bRam00f310 & 0xef;
    }
    iVar6 = (int)sRam301aa0 * (int)sRam0150d8;
    MDL = (ushort)iVar6;
    MDH = (short)((uint)iVar6 >> 0x10);
    MDC = MDC | 0x10;
    if (MDH == 0x3f || MDH + -0x3f < 0 != (iVar6 < 0 && MDH + -0x3f < 0 != iVar6 < 0)) {
      if (MDH + 0x40 < 0 == (-1 < iVar6 && MDH + 0x40 < 0 != iVar6 < 0)) {
        uRam00f318 = MDL >> 7 | MDH << 9;
      }
      else {
        uRam00f318 = 0x8000;
      }
    }
    else {
      uRam00f318 = 0x7fff;
    }
    if (((bRam00f310 & 4) == 0) ||
       ((((bRam00f310 & 0x10) == 0 && ((bRam3001dc & 4) != 0)) || ((bRam00f311 & 0x40) != 0)))) {
      bRam00f310 = bRam00f310 & 0xfe;
      bRam00f30f = bRam0129c2;
    }
    else if ((bRam00f310 & 0x10) != 0) {
      bRam00f310 = bRam00f310 | 1;
    }
    if (((bRam00f310 & 1) != 0) && (bVar3 = bRam00f30f < 2, bRam00f30f = bRam00f30f - 2, bVar3)) {
      bRam00f30f = 0;
    }
    if (bRam00f30f == 0) {
      bRam3001dc = bRam3001dc | 1;
    }
    else {
      bRam3001dc = bRam3001dc & 0xfe;
    }
    if ((bRam00f310 & 0x10) == 0) {
      bRam3001dc = bRam3001dc & 0xfb;
    }
    else {
      bRam3001dc = bRam3001dc | 4;
    }
    if (((bRam00f310 & 4) == 0) || ((bRam3001dc & 2) != 0)) {
      cRam00f30c = '\0';
    }
    else if ((bRam3001dc & 1) != 0) {
      if ((ushort)bRam3012e6 < uRam301aa4 >> 8) {
        bVar3 = -1 < cRam00f30c;
        cVar2 = cRam00f30c + '\x01';
        bVar1 = cRam00f30c < '\0';
        cRam00f30c = cRam00f30c + '\x01';
        if (bVar3 && cVar2 < '\0' != bVar1) {
          cRam00f30c = '\x7f';
        }
      }
      else if ((uRam301aa4 >> 8 < (ushort)bRam3012e6) &&
              (bVar3 = cRam00f30c < '\0', cVar2 = cRam00f30c + -1, bVar1 = cRam00f30c < '\0',
              cRam00f30c = cRam00f30c + -1, bVar3 && cVar2 < '\0' != bVar1)) {
        cRam00f30c = -0x80;
      }
    }
    bVar9 = func_0x042fca((short)cRam00f30c);
    if (bRam0129b1 < bVar9) {
      bRam3001dc = bRam3001dc | 2;
    }
    else {
      bRam3001dc = bRam3001dc & 0xfd;
    }
    if ((bRam3001dc & 2) != 0) {
      if (cRam00f30c < '\x01') {
        bVar3 = bRam00f30e == 0;
        bRam00f30e = bRam00f30e - 1;
        if (bVar3) {
          bRam00f30e = 0;
        }
        if (bRam00f30e < bRam3001cd) {
          bRam00f30e = bRam3001cd;
        }
      }
      else {
        bVar3 = (byte)(bRam00f30e + 1) < bRam00f30e;
        bVar1 = bRam00f30e == 0xff;
        bRam00f30e = bRam00f30e + 1;
        if (bVar3 || bVar1) {
          bRam00f30e = 0xff;
        }
        if (bRam3001cb < bRam00f30e) {
          bRam00f30e = bRam3001cb;
        }
      }
    }
    bRam3012e6 = bRam00f30e;
    if ((bRam00f311 & 1) == 0) {
      if ((bRam00f310 & 0x40) == 0) {
        if ((short)uRam00f318 < 1) {
          uRam301aa4 = (ushort)bRam00f30e * 0x100 + uRam00f318;
          if ((ushort)bRam00f30e * 0x100 < -uRam00f318) {
            uRam301aa4 = 0;
          }
        }
        else {
          uVar12 = (ushort)bRam00f30e * 0x100;
          uRam301aa4 = uVar12 + uRam00f318;
          if (uVar12 + uRam00f318 < uVar12 || uVar12 + uRam00f318 < uRam00f318) {
            uRam301aa4 = 0xffff;
          }
        }
      }
      else {
        uRam301aa4 = uRam0150da;
      }
    }
    else {
      uRam301aa4 = uRam0150de;
    }
    uVar7 = (uint)uRam301aa4 * (uint)bRam00f30d * 0x100;
    uVar12 = (ushort)(uVar7 >> 0x10);
    MDC = MDC | 0x10;
    uRam301aa2 = uVar12 * 2;
    if (uVar12 * 2 < uVar12) {
      uRam301aa2 = 0xffff;
    }
    if (uRam301aa2 < uRam0150dc) {
      bRam00f311 = bRam00f311 & 0xbf;
    }
    else {
      bRam00f311 = bRam00f311 | 0x40;
    }
    uVar13 = uRam301aa6;
    uVar8 = uRam3001ce;
    if ((bRam00f311 & 4) != 0) {
      if ((bRam00f311 & 0x40) == 0) {
        uRam301aa2 = -uRam301aa2 - 1;
        goto LAB_04d07a;
      }
LAB_04d042:
      uRam301aa2 = -uRam0150dc - 1;
      uVar13 = uRam301aa6;
      uVar8 = uRam3001ce;
      goto LAB_04d07a;
    }
    if ((bRam00f311 & 0x40) == 0) goto LAB_04d07a;
  }
  else {
    bRam00f310 = bRam00f310 & 0xbf | 0x10;
    uRam301aa4 = uRam0150de;
    if (uRam0150de < uRam0150dc) {
      bRam00f311 = bRam00f311 & 0xbe;
    }
    else {
      bRam00f311 = bRam00f311 & 0xfe | 0x40;
    }
    if ((bRam00f311 & 4) != 0) {
      if ((bRam00f311 & 0x40) == 0) {
        uRam301aa2 = -uRam0150de - 1;
        goto LAB_04d07a;
      }
      goto LAB_04d042;
    }
    if ((bRam00f311 & 0x40) == 0) {
      uRam301aa2 = uRam0150de;
      goto LAB_04d07a;
    }
  }
  uRam301aa2 = uRam0150dc;
  uVar13 = uRam301aa6;
  uVar8 = uRam3001ce;
LAB_04d07a:
  uRam3001ce._2_2_ = (undefined2)((uint)uVar8 >> 0x10);
  uRam3001ce._0_2_ = (undefined2)uVar8;
  uRam301aa6._2_2_ = (short)((uint)uVar13 >> 0x10);
  uRam301aa6._0_2_ = (undefined2)uVar13;
  MDH = (short)(uVar7 >> 0x10);
  MDL = (ushort)uVar7;
  uRam3012e5 = (char)(uRam301aa4 >> 8);
  return;
}


// ================= vvt_intake_setpoint @ 048786 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* VVT intake cam-angle setpoint map KFWNWSAPE @0x1DB32 */

void vvt_intake_setpoint(void)

{
  if ((bRam301286 & 0x10) == 0) {
    sRam304ec8 = sRam01dc6c - sRam304e9c;
    if (sRam01dc6c < 0 != sRam304e9c < 0 && sRam01dc6c - sRam304e9c < 0 != sRam01dc6c < 0) {
      sRam304ec8 = -0x8000;
    }
  }
  else {
    sRam304ec8 = sRam01dc6c;
  }
  uRam304eca = uRam01dc6e;
  if ((bRam301286 & 0x40) == 0) {
    if ((bRam301286 & 2) == 0) {
      uRam304ec0 = uRam01dc68;
    }
    else {
      uRam304ec0 = func_0x0435b4(0x1b32,7,nmot_w,_rk_w);
    }
  }
  else {
    if (((bRam3012c2 & 1) == 0) || (cRam3012c0 == '\0')) {
      uRam0192c0 = uRam018150;
    }
    else if ((cRam3012c0 != '\0') && (cRam3012c0 = cRam3012c0 + -1, cRam3012c0 == '\0')) {
      if ((bRam3012be & 1) == 0) {
        bRam3012be = bRam3012be | 1;
      }
      else {
        bRam3012be = bRam3012be & 0xfe;
      }
    }
    if ((bRam3012be & 1) == 0) {
      uRam304ec0 = uRam01dc66;
    }
    else {
      uRam304ec0 = uRam01dc64;
    }
  }
  if ((bRam301286 & 0x40) == 0) {
    bRam3012c2 = bRam3012c2 & 0xfe;
  }
  else {
    bRam3012c2 = bRam3012c2 | 1;
  }
  uRam304028 = me7_lookup_2d_byte(0x129,6,rpmclass_oppoint,uRam304979);
  uRam304eb6 = func_0x04274a(uRam01dc52,0x1c54,7,0x1c5c,7,uRam305614);
  uRam304027 = me7_lookup_1d_byte(0x143,6,uRam304979);
  uRam304eb2 = me7_lookup_1d_word(0x1c20,7,uRam304979);
  return;
}


// ================= vvt_exhaust_setpoint @ 04b12e =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* VVT exhaust cam-angle setpoint map KFWNWSAPA @0x1E338 */

void vvt_exhaust_setpoint(void)

{
  if ((bRam301287 & 0x10) == 0) {
    sRam304f02 = sRam01e454 - sRam01da1a;
    if (sRam01e454 < 0 != sRam01da1a < 0 && sRam01e454 - sRam01da1a < 0 != sRam01e454 < 0) {
      sRam304f02 = -0x8000;
    }
  }
  else {
    sRam304f02 = sRam01e454;
  }
  uRam304f04 = uRam01e456;
  if ((bRam301287 & 0x40) == 0) {
    if ((bRam301287 & 2) == 0) {
      uRam304efa = uRam01e44c;
    }
    else {
      uRam304efa = func_0x0435b4(0x2338,7,nmot_w,_rk_w);
    }
  }
  else {
    if (((bRam3012d7 & 1) == 0) || (cRam3012d6 == '\0')) {
      uRam0192d6 = uRam0181a1;
    }
    else if ((cRam3012d6 != '\0') && (cRam3012d6 = cRam3012d6 + -1, cRam3012d6 == '\0')) {
      if ((bRam3012d4 & 1) == 0) {
        bRam3012d4 = bRam3012d4 | 1;
      }
      else {
        bRam3012d4 = bRam3012d4 & 0xfe;
      }
    }
    if ((bRam3012d4 & 1) == 0) {
      uRam304efa = uRam01e450;
    }
    else {
      uRam304efa = uRam01e44e;
    }
  }
  if ((bRam301287 & 0x40) == 0) {
    bRam3012d7 = bRam3012d7 & 0xfe;
  }
  else {
    bRam3012d7 = bRam3012d7 | 1;
  }
  uRam304037 = me7_lookup_2d_byte(0x179,6,rpmclass_oppoint,uRam304979);
  uRam304ef2 = func_0x04274a(uRam01e438,0x243a,7,0x2442,7,uRam305614);
  uRam304036 = me7_lookup_1d_byte(0x193,6,uRam304979);
  uRam301a92 = me7_lookup_1d_word(0x2426,7,uRam304979);
  return;
}


// ================= cam_edge_latch @ 044d22 =================

/* cam-sensor edge latch -> measured cam angle (nwist) */

void cam_edge_latch(void)

{
  uRam301a10 = uRam301a2e;
  uRam301a0e = uRam301a2c;
  if ((uRam00fd14 & 0x4000) == 0) {
    bRam301293 = bRam301293 & 0xfe;
  }
  else {
    bRam301293 = bRam301293 | 1;
  }
  uRam301a0c = uRam00f2bc;
  if ((uRam00fd14 & 0x8000) == 0) {
    bRam301293 = bRam301293 & 0xfb;
  }
  else {
    bRam301293 = bRam301293 | 4;
  }
  uRam301a0a = uRam00f2ba;
  uRam00fd14 = uRam00fd14 & 0x3fff;
  return;
}


// ================= lambda_adaptation_lra @ 088540 =================

/* WARNING: Removing unreachable block (ram,0x088790) */
/* WARNING: Removing unreachable block (ram,0x088792) */
/* WARNING: Removing unreachable block (ram,0x0888ce) */
/* WARNING: Removing unreachable block (ram,0x0885aa) */
/* WARNING: Removing unreachable block (ram,0x0885e8) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* long-term lambda adaptation (LRA): cascaded PT1 -> persistent trim word_30A18A (fueling.md 7) */

void lambda_adaptation_lra(void)

{
  bool bVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  ushort uVar6;
  ushort uVar7;
  undefined4 uVar8;
  
  uVar6 = uRam303b14;
  if ((((uRam303b14 & 0xf00) == 0x100) || ((uRam303b14 & 0xf00) == 0x200)) ||
     ((uRam303b14 & 0xf00) == 0x400)) {
    bRam3015ca = bRam3015ca | 2;
  }
  else {
    bRam3015ca = bRam3015ca & 0xfd;
  }
  uRam305256 = me7_lookup_1d_word(0x3542,8,vfzg_class);
  uRam305252 = (ushort)bRam30543e;
  uRam30524e = uRam305252 * bRam019c2f;
  MDL = uRam30524e;
  uRam305254 = uRam30524e;
  if ((bRam019c2e & 1) != 0) {
    uRam30524a = (ushort)bRam30143f;
    uRam305246 = uRam30524a * bRam019c2f;
    uRam305254 = uRam30524e + uRam305246;
    MDL = uRam305246;
    uRam305248 = uRam305246;
    if (uRam30524e + uRam305246 < uRam30524e || uRam30524e + uRam305246 < uRam305246) {
      uRam305254 = 0xffff;
    }
  }
  MDC = MDC | 0x10;
  MDH = 0;
  uRam30523c = uRam305254;
  uRam305250 = uRam30524e;
  if ((bRam019c2e & 2) == 0) {
    uRam305242 = uRam305254;
  }
  else {
    uRam302972 = me7_pt1_integrator(uRam305256,uRam305254,uRam306974,(undefined2)uRam302972);
    uRam305242 = (ushort)((uint)uRam302972 >> 0x10);
    uRam30524c = uRam305242;
  }
  if (cRam3055d8 == '\0') {
    if (uRam302970 < uRam02353c) {
      uRam302970 = uRam302970 + 1;
    }
    else {
      bRam3015cf = bRam3015cf | 0x20;
    }
  }
  if (vfzg_class == '\0') {
    if (((bRam3015cf & 0x20) != 0) || ((uRam3035f8 & 0x8000) != 0)) {
      bRam3015ca = bRam3015ca | 4;
    }
  }
  else {
    bRam3015ca = bRam3015ca & 0xfb;
    bRam3015cf = bRam3015cf & 0xdf;
    uRam302970 = 0;
  }
  _lambda_trim_applied = uRam305242;
  if ((bRam3015ca & 4) == 0) {
    uVar8 = me7_pt1_integrator(uRam023540,uRam305242,uRam306978,(undefined2)uRam302976);
  }
  else {
    uVar8 = me7_pt1_integrator(uRam305256,uRam305242,uRam306978,(undefined2)uRam302976);
  }
  uRam302976._2_2_ = (ushort)((uint)uVar8 >> 0x10);
  if (((uRam00fd3a & 0x200) != 0) && (uRam30296e < uRam02353e)) {
    uRam30296e = uRam30296e + 1;
  }
  if ((bRam019c2e & 4) == 0) {
LAB_0887f6:
    if (((uRam30296e != uRam02353e) && ((uRam3035f8 & 0x8000) == 0)) || ((bRam3015ca & 2) != 0))
    goto LAB_08881c;
    bRam3015c8 = bRam3015c8 | 4;
  }
  else {
    uRam30523a = _lambda_trim_applied - uRam302976._2_2_;
    uVar7 = -(ushort)(_lambda_trim_applied < uRam302976._2_2_);
    if ((short)uVar7 < 0) {
      bVar1 = uRam30523a != 0;
      uRam30523a = -uRam30523a;
      uVar7 = -(uVar7 + bVar1);
    }
    uVar2 = (ushort)(uRam30523a != 0xffff);
    if ((uVar7 != uVar2 || uRam30523a != 0xffff) &&
        (short)(uVar7 - uVar2) < 0 ==
        ((short)uVar7 < 0 && (short)(uVar7 - (uRam30523a != 0xffff)) < 0 != (short)uVar7 < 0)) {
      uRam30523a = 0xffff;
    }
    if (uRam02352c < uRam30523a) {
      bRam3015ca = bRam3015ca | 1;
    }
    else {
      bRam3015ca = bRam3015ca & 0xfe;
    }
    if ((bRam3015ca & 1) == 0) goto LAB_0887f6;
LAB_08881c:
    bRam3015c8 = bRam3015c8 & 0xfb;
  }
  if ((bRam3015ca & 2) == 0) {
    if ((bRam3015c8 & 4) != 0) {
      bRam3015c8 = bRam3015c8 | 8;
    }
  }
  else {
    bRam3015c8 = bRam3015c8 & 0xf7;
  }
  if ((bRam3015c8 & 8) == 0) {
    bRam3015c9 = bRam3015c9 & 0xfe;
  }
  else {
    bRam3015c9 = bRam3015c9 | 1;
  }
  if (((uVar6 & 1) == 0) && ((bRam3015c8 & 8) != 0)) {
    bRam3015c8 = bRam3015c8 | 0x80;
  }
  else {
    bRam3015c8 = bRam3015c8 & 0x7f;
  }
  if ((bRam3015c8 & 4) != 0) {
    _lambda_trim_nv = _lambda_trim_applied;
  }
  if ((bRam3015ca & 2) == 0) {
    uRam305240 = _lambda_trim_nv;
  }
  else {
    uRam305240 = uRam023536;
  }
  uRam307e0e = uRam305240;
  MDL = MDL / 10;
  if (MDL < 0x100) {
    uRam3047a5 = (undefined1)MDL;
  }
  else {
    uRam3047a5 = 0xff;
  }
  if ((bRam3015c8 & 4) != 0) {
    uVar7 = uRam02352a - uRam02352e;
    if (uRam02352a < uRam02352e) {
      uVar7 = 0;
    }
    if (uRam305240 < uVar7) {
      bRam3015cf = bRam3015cf & 0xfe;
    }
    else {
      uVar7 = uRam02352a + uRam02352e;
      if (uRam02352a + uRam02352e < uRam02352a || uRam02352a + uRam02352e < uRam02352e) {
        uVar7 = 0xffff;
      }
      if (uVar7 < uRam305240) {
        bRam3015cf = bRam3015cf | 1;
      }
    }
    if ((bRam3015cf & 1) == 0) {
      uRam0195cb = uRam019c2d;
      bRam3015c8 = bRam3015c8 & 0xfd;
    }
    else if (cRam3015cb == '\0') {
      bRam3015c8 = bRam3015c8 | 2;
    }
    else {
      cRam3015cb = cRam3015cb + -1;
    }
    uVar7 = uRam023528 - uRam02352e;
    if (uRam023528 < uRam02352e) {
      uVar7 = 0;
    }
    if (uRam305240 < uVar7) {
      bRam3015cf = bRam3015cf & 0xfd;
    }
    else {
      uVar7 = uRam023528 + uRam02352e;
      if (uRam023528 + uRam02352e < uRam023528 || uRam023528 + uRam02352e < uRam02352e) {
        uVar7 = 0xffff;
      }
      if (uVar7 < uRam305240) {
        bRam3015cf = bRam3015cf | 2;
      }
    }
    if ((bRam3015cf & 2) == 0) {
      if (cRam3015cc == '\0') {
        bRam3015c8 = bRam3015c8 | 1;
      }
      else {
        cRam3015cc = cRam3015cc + -1;
      }
    }
    else {
      uRam0195cc = uRam019c2d;
      bRam3015c8 = bRam3015c8 & 0xfe;
    }
    uVar7 = uRam023534 - uRam02352e;
    if (uRam023534 < uRam02352e) {
      uVar7 = 0;
    }
    if (uRam305240 < uVar7) {
      bRam3015cf = bRam3015cf & 0xfb;
    }
    else {
      uVar7 = uRam023534 + uRam02352e;
      if (uRam023534 + uRam02352e < uRam023534 || uRam023534 + uRam02352e < uRam02352e) {
        uVar7 = 0xffff;
      }
      if (uVar7 < uRam305240) {
        bRam3015cf = bRam3015cf | 4;
      }
    }
    if ((bRam3015cf & 4) == 0) {
      uRam0195cd = uRam019c2d;
      bRam3015c8 = bRam3015c8 & 0xef;
    }
    else if (cRam3015cd == '\0') {
      bRam3015c8 = bRam3015c8 | 0x10;
    }
    else {
      cRam3015cd = cRam3015cd + -1;
    }
    if ((bRam019c2e & 0x10) == 0) {
      uVar7 = uRam023530 - uRam02352e;
      if (uRam023530 < uRam02352e) {
        uVar7 = 0;
      }
      if (uRam305240 < uVar7) {
LAB_088b10:
        bRam3015cf = bRam3015cf & 0xf7;
      }
      else {
        uVar7 = uRam023530 + uRam02352e;
        if (uRam023530 + uRam02352e < uRam023530 || uRam023530 + uRam02352e < uRam02352e) {
          uVar7 = 0xffff;
        }
        if (uVar7 < uRam305240) {
LAB_088b40:
          bRam3015cf = bRam3015cf | 8;
        }
      }
    }
    else {
      uVar7 = uRam023532 - uRam02352e;
      if (uRam023532 < uRam02352e) {
        uVar7 = 0;
      }
      if (uRam305250 < uVar7) goto LAB_088b10;
      uVar7 = uRam023532 + uRam02352e;
      if (uRam023532 + uRam02352e < uRam023532 || uRam023532 + uRam02352e < uRam02352e) {
        uVar7 = 0xffff;
      }
      if (uVar7 < uRam305250) goto LAB_088b40;
    }
    if ((bRam3015cf & 8) == 0) {
      if (cRam3015ce == '\0') {
        bRam3015cf = bRam3015cf | 0x10;
      }
      else {
        cRam3015ce = cRam3015ce + -1;
      }
    }
    else {
      uRam0195ce = uRam019c2d;
      bRam3015cf = bRam3015cf & 0xef;
    }
  }
  if ((uVar6 & 1) == 0) {
    bVar5 = bRam301271;
    if ((bRam019c2e & 8) == 0) {
      bVar5 = bRam3015cf;
    }
    if ((bVar5 & 0x10) != 0) {
      bRam3015c8 = bRam3015c8 | 0x40;
      goto LAB_088be2;
    }
  }
  else {
    bRam3015c8 = bRam3015c8 & 0xcc;
  }
  bRam3015c8 = bRam3015c8 & 0xbf;
LAB_088be2:
  uVar3 = CONCAT22(uRam02353a >> 0xf,uRam02353a << 1) / 0x29;
  uVar7 = (ushort)uVar3;
  if (0xffff < uVar3) {
    uVar7 = 0xffff;
  }
  uRam305244 = uVar7 - uRam305240;
  if (uVar7 < uRam305240) {
    uRam305244 = 0;
  }
  uVar3 = CONCAT22(uRam305244 >> 4,uRam305244 << 0xc) / (uint)uRam02353a;
  uVar7 = (ushort)uVar3;
  if (uRam02353a == 0 || 0xffff < uVar3) {
    uVar7 = 0xffff;
  }
  if (uVar7 < 0x100) {
    uRam3047a7 = (undefined1)uVar7;
  }
  else {
    uRam3047a7 = 0xff;
  }
  uVar3 = CONCAT22(uRam305240 >> 4,uRam305240 << 0xc);
  uVar4 = uVar3 / uRam023538;
  MDL = (ushort)uVar4;
  MDH = (undefined2)(uVar3 % (uint)uRam023538);
  MDC = MDC | 0x10;
  uVar7 = MDL;
  if (uRam023538 == 0 || 0xffff < uVar4) {
    uVar7 = 0xffff;
  }
  if (uVar7 < 0x100) {
    uRam3047a6 = (undefined1)uVar7;
  }
  else {
    uRam3047a6 = 0xff;
  }
  uRam302976 = uVar8;
  func_0x0b31ac(0x47,uVar6);
  return;
}


// ================= lra_boot_restore @ 0884e8 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* LRA power-on restore of persisted lambda trim */

void lra_boot_restore(void)

{
  if ((DAT_00fd4e & 0x100) != 0) {
    _lambda_trim_nv = 0;
  }
  uRam30a978 = _lambda_trim_nv;
  uRam302974 = uRam302978;
  uRam0195cb = uRam019c2d;
  uRam0195cc = uRam019c2d;
  uRam0195cd = uRam019c2d;
  uRam0195ce = uRam019c2d;
  bRam3015ca = bRam3015ca | 4;
  return;
}


// ================= evap_purge_ctrl @ 08de10 =================

/* WARNING: Removing unreachable block (ram,0x08e9ce) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* EVAP canister-purge (TEV) controller: duty byte_30A0C2 + fuel-portion FSRFKAS (fueling.md 8) */

void evap_purge_ctrl(void)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  ushort uVar5;
  int iVar6;
  byte bVar7;
  ushort uVar8;
  ushort uVar9;
  ushort uVar10;
  byte extraout_RH4;
  undefined2 uVar11;
  char cVar12;
  short sVar13;
  short sVar14;
  
  if (((bRam301612 & 0x40) == 0) || ((bRam3015fe & 2) == 0)) {
    uRam3052aa = 0x4000;
  }
  else {
    uVar3 = CONCAT22(uRam302822 >> 2,uRam302822 << 0xe) / (uint)uRam30294c;
    uVar8 = (ushort)uVar3;
    if (uRam30294c == 0 || 0xffff < uVar3) {
      uVar8 = 0xffff;
    }
    uVar8 = (ushort)((uint)uVar8 * (uint)uRam302816 >> 0x10);
    MDC = MDC | 0x10;
    uRam3052aa = uVar8 * 2;
    if (uVar8 * 2 < uVar8) {
      uRam3052aa = 0xffff;
    }
  }
  if (uRam3052aa < 0x8000) {
    _evap_purge_quantity = uRam3052aa << 1;
  }
  else {
    _evap_purge_quantity = 0xffff;
  }
  uRam3052c0 = uRam30694a;
  uVar8 = (ushort)((uint)uRam30694a * 0xf000 >> 0x10);
  uVar3 = ((uint)_rl_scaled << 0x10) / (uint)uVar8;
  uRam304956 = (undefined1)(uVar3 >> 8);
  if (uVar8 == 0 || 0xffff < uVar3) {
    uRam304956 = 0xff;
  }
  MDL = (ushort)bRam3047a9 * (ushort)bRam019df3;
  MDH = 0;
  MDC = MDC | 0x10;
  if (MDL < 0x8000) {
    uRam304957 = (undefined1)(MDL >> 7);
  }
  else {
    uRam304957 = 0xff;
  }
  if (((bRam305603 & 0x80) == 0) && ((uRam00fd16 & 0x400) != 0)) {
    bRam304959 = bRam304959 | 0x10;
  }
  else {
    bRam304959 = bRam304959 & 0xef;
  }
  if ((uRam00fd16 & 0x400) == 0) {
    bRam301603 = bRam301603 & 0x7f;
  }
  else {
    bRam301603 = bRam301603 | 0x80;
  }
  if ((bRam301604 & 0x10) == 0) {
    if (((bRam301604 & 2) == 0) && ((bRam304958 & 1) != 0)) {
      bRam301604 = bRam301604 | 1;
    }
  }
  else {
    bRam301604 = bRam301604 & 0xfe;
  }
  if (((bRam301604 & 1) == 0) || ((bRam301612 & 1) != 0)) {
    bRam301604 = bRam301604 & 0xef;
  }
  else {
    bRam301604 = bRam301604 | 0x10;
  }
  if (((uRam303b78 & 1) == 0) || ((uRam303ada & 1) != 0)) {
    bRam301600 = bRam301600 & 0xfe;
  }
  else {
    bRam301600 = bRam301600 | 1;
  }
  if ((bRam301600 & 1) == 0) {
    bRam301604 = bRam301604 & 0xfb;
  }
  else {
    bRam301604 = bRam301604 | 4;
  }
  if (((((bRam301604 & 8) == 0) && ((bRam301604 & 4) != 0)) || ((bRam301604 & 0x10) != 0)) ||
     (((bRam304958 & 1) != 0 && ((bRam304959 & 0x10) != 0)))) {
    bRam304959 = bRam304959 | 2;
  }
  else {
    bRam304959 = bRam304959 & 0xfd;
  }
  if ((bRam304958 & 1) == 0) {
    bRam301604 = bRam301604 & 0xfd;
  }
  else {
    bRam301604 = bRam301604 | 2;
  }
  if ((bRam301604 & 4) == 0) {
    bRam301604 = bRam301604 & 0xf7;
  }
  else {
    bRam301604 = bRam301604 | 8;
  }
  uRam30494c = (undefined1)(uRam3052aa >> 8);
  bRam3015f9 = me7_lookup_1d_byte(0x1dbe,6,uRam3052aa >> 8);
  if ((bRam3015ff & 2) == 0) {
    uVar8 = func_0x04210c(0x1e4b,6,0xf44,5,uRam30198c,uRam301980);
    uVar9 = me7_lookup_1d_byte(0x1dea,6,uRam304957);
    uRam3015fa = (undefined1)((uVar8 & 0xff) * (uVar9 & 0xff) >> 8);
    if ((short)uRam3029ea < 0) {
      iVar6 = (int)sRam3029ee * (int)(short)(uRam3029ea & 0x7fff);
      uVar10 = (ushort)iVar6;
      uVar9 = sRam3029ee * -0x8000;
      uVar8 = uVar10 + uVar9;
      sVar13 = (short)((uint)iVar6 >> 0x10) + (sRam3029ee >> 1) +
               (ushort)(uVar10 + uVar9 < uVar10 || uVar10 + uVar9 < uVar9);
      if (sVar13 < 0) {
        sVar13 = sVar13 + (ushort)(uVar8 - 1 < uVar8 || uVar8 != 0);
      }
    }
    else {
      iVar6 = (int)sRam3029ee * (int)(short)uRam3029ea;
      uVar8 = (ushort)iVar6;
      sVar13 = (short)((uint)iVar6 >> 0x10);
      if (iVar6 < 0) {
        sVar13 = sVar13 + (ushort)(uVar8 - 1 < uVar8 || uVar8 != 0);
      }
    }
    if (sVar13 == 0x3ff || sVar13 + -0x3ff < 0 != (sVar13 < 0 && sVar13 + -0x3ff < 0 != sVar13 < 0))
    {
      if (sVar13 + 0x400 < 0 != (-1 < sVar13 && sVar13 + 0x400 < 0 != sVar13 < 0)) {
        sVar13 = -0x400;
      }
    }
    else {
      sVar13 = 0x3ff;
    }
    cRam30494f = (char)(sVar13 >> 3);
    cVar12 = (bRam3055fa >> 1) - cRam30494f;
    if (cRam30494f < '\0' && (char)((bRam3055fa >> 1) - cRam30494f) < '\0') {
      cVar12 = -0x80;
    }
    sVar13 = (short)cVar12 * (ushort)bRam019df4;
    MDC = MDC | 0x10;
    if (sVar13 + -0x200 < 0 == (sVar13 < 0 && sVar13 + -0x200 < 0 != sVar13 < 0)) {
      cVar12 = '\b';
    }
    else if (sVar13 + 0x200 < 0 == (-1 < sVar13 && sVar13 + 0x200 < 0 != sVar13 < 0)) {
      cVar12 = (char)(sVar13 >> 6);
    }
    else {
      cVar12 = -8;
    }
    bVar1 = 1 < (bRam3015f9 >> 1 & 1);
    bVar7 = bRam3015f9 >> 2;
    cVar2 = (cVar12 - bVar7) - bVar1;
    if ((cVar12 < '\0' && (char)((cVar12 - bVar7) - bVar1) < '\0' != cVar12 < '\0') ||
       (evap_fuel_portion = cVar2 - bVar7,
       cVar2 < '\0' && (char)(cVar2 - bVar7) < '\0' != cVar2 < '\0')) {
      evap_fuel_portion = -0x80;
    }
  }
  else {
    evap_fuel_portion = -(bRam3015f9 >> 1);
  }
  if ((short)uRam3029ec < 0) {
    iVar6 = (int)sRam3029ee * (int)(short)(uRam3029ec & 0x7fff);
    uVar9 = (ushort)iVar6;
    uVar8 = sRam3029ee * -0x8000;
    iVar6 = CONCAT22((short)((uint)iVar6 >> 0x10) + (sRam3029ee >> 1) +
                     (ushort)(uVar9 + uVar8 < uVar9 || uVar9 + uVar8 < uVar8),uVar9 + uVar8);
  }
  else {
    iVar6 = (int)sRam3029ee * (int)(short)uRam3029ec;
  }
  iVar6 = iVar6 >> 0xb;
  uVar10 = (ushort)((uint)iVar6 >> 0x10);
  uVar8 = (ushort)iVar6;
  uVar9 = (ushort)(uVar8 < 0x7fff);
  if (uVar10 == uVar9 && uVar8 == 0x7fff ||
      (short)(uVar10 - uVar9) < 0 !=
      (iVar6 < 0 && (short)(uVar10 - (uVar8 < 0x7fff)) < 0 != iVar6 < 0)) {
    uRam3052b4 = uVar8;
    if ((short)((uVar10 + 1) - (ushort)(uVar8 < 0x8000)) < 0 !=
        (-1 < iVar6 && (short)((uVar10 + 1) - (ushort)(uVar8 < 0x8000)) < 0 != iVar6 < 0)) {
      uRam3052b4 = 0x8000;
    }
  }
  else {
    uRam3052b4 = 0x7fff;
  }
  uRam304950 = (undefined1)(uRam3052b4 >> 8);
  uVar3 = CONCAT22(uRam302e0a >> 7,uRam302e0a << 9) / (uint)uRam306a02;
  uRam3029f2 = (ushort)uVar3;
  if (uRam306a02 == 0 || 0xffff < uVar3) {
    uRam3029f2 = 0xffff;
  }
  iVar6 = (uint)uRam3029f2 * (uint)uRam3052c0;
  MDL = (ushort)iVar6;
  MDH = (ushort)((uint)iVar6 >> 0x10);
  MDC = MDC | 0x10;
  if ((iVar6 < 0) || ((BADTYPE)(MDH >> 0xe & 1))) {
    uRam3029ec = 0xffff;
  }
  else {
    uRam3029ec = MDH << 2 | MDL >> 0xe;
  }
  if (uRam3029ec < 0x4000) {
    uRam3029ec = uRam3029ec << 2;
  }
  else {
    uRam3029ec = -1;
  }
  uRam30494d = (undefined1)(uRam3029ec >> 8);
  if (uRam306e06 == 0) {
    if (uRam302a46 < uRam023a14) {
      uRam302a46 = uRam302a46 + 1;
    }
    else {
      bRam301603 = bRam301603 | 8;
    }
  }
  else {
    bRam301603 = bRam301603 & 0xf7;
    uRam302a46 = 0;
  }
  if (((bRam304959 & 2) == 0) && ((bRam301603 & 8) == 0)) {
    uRam302a22 = func_0x042ea8(0x1000,uRam302e06,uRam302a22._2_2_,(undefined2)uRam302a22);
  }
  else {
    uRam302a22 = 0;
  }
  uRam304954 = (undefined1)((uint)uRam302a22 >> 0x18);
  MDL = (ushort)((uint)uRam3029fa * (uint)uRam306e08);
  MDH = (ushort)((uint)uRam3029fa * (uint)uRam306e08 >> 0x10);
  MDC = MDC | 0x10;
  uRam3052ac = FUN_042c1c(MDH,uRam3052c0 >> 3,uRam302a02);
  if ((bRam305612 & 8) == 0) {
    uVar9 = func_0x04210c(0x1e0d,6,0x2811,4,uRam301982,uRam3019d4);
  }
  else {
    uVar9 = func_0x04210c(0x1e3b,6,0xf44,5,uRam30198c,uRam301980);
  }
  uVar9 = uVar9 & 0xff;
  uVar10 = me7_lookup_1d_byte(0x1ddf,6,uRam304954);
  if ((uVar10 & 0xff) < uVar9) {
    uVar9 = uVar10 & 0xff;
  }
  uRam3052ae = uVar9 * 0x100;
  uVar9 = uRam3029ea;
  if (uRam3069ea < uRam3052ac) {
    uVar9 = uRam3052ac;
  }
  uRam3052b0 = uRam3052ae;
  if (uVar9 <= uRam3052ae) {
    uRam3052b0 = uVar9;
  }
  bRam3015fb = func_0x042020(0x1e5c,6,uRam301982);
  if (((bRam301613 & 1) == 0) && ((bRam304959 & 8) == 0)) {
    bRam301603 = bRam301603 & 0xfe;
  }
  else {
    bRam301603 = bRam301603 | 1;
  }
  if (((bRam301603 & 1) == 0) && ((bRam301613 & 2) != 0)) {
    bRam304959 = bRam304959 | 4;
  }
  else {
    bRam304959 = bRam304959 & 0xfb;
  }
  if ((bRam304959 & 4) == 0) {
    uVar9 = uRam023a18;
    if ((bRam301603 & 1) == 0) {
      uVar9 = uRam023a16;
    }
    MDH = uRam3052b2 >> 1;
    if ((short)MDH < 0) {
      if (uVar9 == 0) {
        uVar8 = 0;
        uRam30529c = 0x8000;
      }
      else {
        MDL = -MDH / uVar9;
        MDH = -MDH % uVar9;
        uVar10 = (ushort)(((uint)MDH << 0x10) / (uint)uVar9);
        MDH = (ushort)(((uint)MDH << 0x10) % (uint)uVar9);
        MDC = MDC | 0x10;
        uVar8 = -uVar10;
        uRam30529c = -(ushort)(uVar10 != 0) - MDL;
        MDL = uVar10;
      }
    }
    else if (uVar9 == 0) {
      uVar8 = 0xffff;
      uRam30529c = 0x7fff;
    }
    else {
      MDL = MDH / uVar9;
      MDH = MDH % uVar9;
      uVar8 = (ushort)(((uint)MDH << 0x10) / (uint)uVar9);
      MDH = (ushort)(((uint)MDH << 0x10) % (uint)uVar9);
      MDC = MDC | 0x10;
      uRam30529c = MDL;
      MDL = uVar8;
    }
    iVar6 = CONCAT22(MDH,MDL);
    sRam30529e = -uRam30529c;
    if (sRam30529e == 0) {
      sRam30529e = -1;
      iVar6 = CONCAT22(MDH,MDL);
    }
  }
  else {
    uRam30494e = (undefined1)(uRam3029ea >> 8);
    uVar9 = me7_lookup_1d_byte(0x1dd4,6,uRam3029ea >> 8);
    uRam3029fe = (uVar9 & 0xff) * (ushort)bRam3015fb;
    sVar13 = (short)evap_fuel_portion << 8;
    if ((short)uRam3029fe < 0) {
      iVar6 = (int)sVar13 * (int)(short)(uRam3029fe & 0x7fff);
      uVar9 = (ushort)iVar6;
      sRam30529e = (short)((uint)iVar6 >> 0x10) + (sVar13 >> 1);
      if (sRam30529e < 0) {
        sRam30529e = sRam30529e + (ushort)(uVar9 - 1 < uVar9 || uVar9 != 0);
      }
    }
    else {
      iVar6 = (int)sVar13 * (int)(short)uRam3029fe;
      uVar9 = (ushort)iVar6;
      sRam30529e = (short)((uint)iVar6 >> 0x10);
      if (iVar6 < 0) {
        sRam30529e = sRam30529e + (ushort)(uVar9 - 1 < uVar9 || uVar9 != 0);
      }
    }
    MDC = MDC | 0x10;
    uRam3052b2 = uRam3069ea;
  }
  MDH = (ushort)((uint)iVar6 >> 0x10);
  MDL = (ushort)iVar6;
  uRam302a16 = func_0x0430da(0x5000,sRam30529e,uRam306a18,(undefined2)uRam302a16,0,0,uRam3052b0 >> 1
                             ,uRam3052b0 << 0xf,uVar8);
  uRam3029ea = (short)((uint)uRam302a16 >> 0x10) << 1;
  if ((bRam301613 & 2) == 0) {
    uRam3052a0 = 0;
  }
  else {
    uRam3052a0 = me7_lookup_1d_word(0x396c,8,uRam3029f4);
  }
  uVar9 = me7_lookup_1d_word(0x3982,8,uRam302a0a);
  bVar7 = bRam3015f9;
  if (bRam019dd3 <= bRam3015f9) {
    bVar7 = bRam019dd3;
  }
  uVar3 = (uint)uVar9 * (uint)bVar7 * 0x100;
  if (uVar3 < 0x10000000) {
    uVar10 = (ushort)uVar3 >> 0xc | (short)(uVar3 >> 0x10) << 4;
  }
  else {
    uVar10 = 0xffff;
  }
  if ((bRam301613 & 2) == 0) {
    sVar13 = -(uVar10 >> 1);
  }
  else {
    sVar13 = (uVar9 >> 1) - (uVar10 >> 1);
    if (uVar9 >> 1 < uVar10 >> 1) {
      if (sVar13 >= 0) {
        sVar13 = -0x8000;
      }
    }
    else if (sVar13 < 0) {
      sVar13 = 0x7fff;
    }
  }
  uVar9 = (ushort)bRam3015fb << 8;
  if ((short)uVar9 < 0) {
    iVar6 = (int)sVar13 * (int)(short)(uVar9 & 0x7fff);
    uVar5 = (ushort)iVar6;
    uVar10 = sVar13 * -0x8000;
    uVar9 = uVar5 + uVar10;
    sRam3052a4 = (short)((uint)iVar6 >> 0x10) + (sVar13 >> 1) +
                 (ushort)(uVar5 + uVar10 < uVar5 || uVar5 + uVar10 < uVar10);
    if (sRam3052a4 < 0) {
      sRam3052a4 = sRam3052a4 + (ushort)(uVar9 - 1 < uVar9 || uVar9 != 0);
    }
  }
  else {
    iVar6 = (int)sVar13 * (int)(short)uVar9;
    uVar9 = (ushort)iVar6;
    sRam3052a4 = (short)((uint)iVar6 >> 0x10);
    if (iVar6 < 0) {
      sRam3052a4 = sRam3052a4 + (ushort)(uVar9 - 1 < uVar9 || uVar9 != 0);
    }
  }
  MDH = (ushort)((uint)iVar6 >> 0x10);
  MDL = (ushort)iVar6;
  MDC = MDC | 0x10;
  if ((bRam304959 & 2) == 0) {
    uRam302a26 = CONCAT22(uRam302a26._2_2_,(undefined2)uRam302a26);
    if (((bRam3015ff & 2) == 0) &&
       (uRam302a26 = CONCAT22(uRam302a26._2_2_,(undefined2)uRam302a26), (bRam301613 & 8) != 0)) {
      bVar7 = me7_lookup_1d_byte(0x1db3,6,uRam30494d);
      me7_lookup_1d_word(0x39b0,8,uRam3052ac);
      if (extraout_RH4 <= bVar7) {
        bVar7 = extraout_RH4;
      }
      uVar9 = (ushort)bVar7 << 8;
      sVar13 = -0x8000 - _evap_purge_quantity;
      if (_evap_purge_quantity < 0x8001) {
        if (sVar13 < 0) {
          sVar13 = 0x7fff;
        }
      }
      else if (sVar13 >= 0) {
        sVar13 = -0x8000;
      }
      if ((short)uVar9 < 0) {
        iVar6 = (int)sVar13 * (int)(short)(uVar9 & 0x7fff);
        uVar5 = (ushort)iVar6;
        uVar10 = sVar13 * -0x8000;
        uVar9 = uVar5 + uVar10;
        sRam30529a = (short)((uint)iVar6 >> 0x10) + (sVar13 >> 1) +
                     (ushort)(uVar5 + uVar10 < uVar5 || uVar5 + uVar10 < uVar10);
        if (sRam30529a < 0) {
          sRam30529a = sRam30529a + (ushort)(uVar9 - 1 < uVar9 || uVar9 != 0);
        }
      }
      else {
        iVar6 = (int)sVar13 * (int)(short)uVar9;
        uVar9 = (ushort)iVar6;
        sRam30529a = (short)((uint)iVar6 >> 0x10);
        if (iVar6 < 0) {
          sRam30529a = sRam30529a + (ushort)(uVar9 - 1 < uVar9 || uVar9 != 0);
        }
      }
      MDH = (ushort)((uint)iVar6 >> 0x10);
      MDL = (ushort)iVar6;
      MDC = MDC | 0x10;
      bRam30494b = bVar7;
      bRam304955 = func_0x042020(0x1e08,6,uRam301982);
      bVar1 = 1 < (uRam3052bc >> 10 & 1);
      bVar7 = (byte)(uRam3052bc >> 0xb);
      cVar12 = (cRam019e5b - bVar7) - bVar1;
      if ((cRam019e5b < '\0' && (char)((cRam019e5b - bVar7) - bVar1) < '\0' != cRam019e5b < '\0') ||
         (cRam30494a = cVar12 - bVar7,
         cVar12 < '\0' && (char)(cVar12 - bVar7) < '\0' != cVar12 < '\0')) {
        cRam30494a = -0x80;
      }
      bVar1 = 1 < (uRam3052bc >> 2 & 1);
      uVar9 = uRam3052bc >> 3;
      sVar13 = (sRam023a06 - uVar9) - (ushort)bVar1;
      if ((sRam023a06 < 0 && (short)((sRam023a06 - uVar9) - (ushort)bVar1) < 0 != sRam023a06 < 0) ||
         (sVar14 = sVar13 - uVar9, sVar13 < 0 && (short)(sVar13 - uVar9) < 0 != sVar13 < 0)) {
        sVar14 = -0x8000;
      }
      uRam302a26 = func_0x0430da((ushort)bRam304955 << 7,sRam30529a,uRam306a28,
                                 (undefined2)uRam302a26,(short)cRam30494a << 8,0,sVar14,0,uVar8);
      sRam3052a2 = (short)((uint)uRam302a26 >> 0x10);
    }
  }
  else {
    sRam3052a2 = 0;
    uRam302a26 = 0;
  }
  sRam3052be = sRam3052a2 + (uRam3052bc >> 2);
  if (-1 < sRam3052a2 && (short)(sRam3052a2 + (uRam3052bc >> 2)) < 0 != sRam3052a2 < 0) {
    sRam3052be = 0x7fff;
  }
  uVar9 = (ushort)bRam019df5 << 8;
  if ((short)uVar9 < 0) {
    iVar6 = (int)sRam3052be * (int)(short)(uVar9 & 0x7fff);
    uVar5 = (ushort)iVar6;
    uVar10 = sRam3052be * -0x8000;
    uVar9 = uVar5 + uVar10;
    sRam3029ee = (short)((uint)iVar6 >> 0x10) + (sRam3052be >> 1) +
                 (ushort)(uVar5 + uVar10 < uVar5 || uVar5 + uVar10 < uVar10);
    if (sRam3029ee < 0) {
      sRam3029ee = sRam3029ee + (ushort)(uVar9 - 1 < uVar9 || uVar9 != 0);
    }
  }
  else {
    iVar6 = (int)sRam3052be * (int)(short)uVar9;
    uVar9 = (ushort)iVar6;
    sRam3029ee = (short)((uint)iVar6 >> 0x10);
    if (iVar6 < 0) {
      sRam3029ee = sRam3029ee + (ushort)(uVar9 - 1 < uVar9 || uVar9 != 0);
    }
  }
  MDH = (ushort)((uint)iVar6 >> 0x10);
  MDL = (ushort)iVar6;
  MDC = MDC | 0x10;
  if ((bRam304959 & 2) == 0) {
    if ((bRam301612 & 1) != 0) {
      uRam302a32 = me7_slew_limiter(uRam023a1c,uRam0229ee,uRam302a32._2_2_,(undefined2)uRam302a32);
      iVar6 = CONCAT22(MDH,MDL);
      cRam304952 = (char)((uint)uRam302a32 >> 0x18);
    }
    if ((uRam00fd0e & 0x1000) != 0) {
      sVar13 = (ushort)bRam019df5 << 6;
      if ((short)uRam3052ba < 0) {
        iVar6 = (int)sVar13 * (int)(short)(uRam3052ba & 0x7fff);
        sRam3052b6 = (short)((uint)iVar6 >> 0x10) + (sVar13 >> 1);
      }
      else {
        iVar6 = (int)sVar13 * (int)(short)uRam3052ba;
        uVar9 = (ushort)iVar6;
        sRam3052b6 = (short)((uint)iVar6 >> 0x10);
        if (iVar6 < 0) {
          sRam3052b6 = sRam3052b6 + (ushort)(uVar9 - 1 < uVar9 || uVar9 != 0);
        }
      }
      MDH = (ushort)((uint)iVar6 >> 0x10);
      MDL = (ushort)iVar6;
      MDC = MDC | 0x10;
      iRam302a36 = me7_slew_limiter(uRam023a1c,sRam3052b6,iRam302a36._2_2_,(undefined2)iRam302a36);
      iVar6 = CONCAT22(MDH,MDL);
      cRam304951 = (char)((uint)iRam302a36 >> 0x18);
    }
  }
  else {
    uRam302a32 = 0;
    cRam304952 = '\0';
    uRam306a38 = 0;
    iRam302a36 = (uint)iRam302a36._2_2_ << 0x10;
    cRam304951 = '\0';
  }
  MDH = (ushort)((uint)iVar6 >> 0x10);
  MDL = (ushort)iVar6;
  if ((bRam304959 & 2) == 0) {
    uRam302a2a = CONCAT22(uRam302a2a._2_2_,(ushort)uRam302a2a);
    if ((((bRam301613 & 8) != 0) &&
        (uRam302a2a = CONCAT22(uRam302a2a._2_2_,(ushort)uRam302a2a), (bRam3015ff & 2) == 0)) &&
       (uRam302a2a = CONCAT22(uRam302a2a._2_2_,(ushort)uRam302a2a), (bRam304958 & 1) == 0)) {
      sVar13 = sRam3052a2;
      if (((bRam304959 & 1) != 0) && (-1 < sRam3052a2)) {
        sVar13 = 0;
      }
      uVar9 = me7_lookup_1d_word(0x399a,8,uRam3029f2);
      if ((short)uVar9 < 0) {
        iVar6 = (int)sVar13 * (int)(short)(uVar9 & 0x7fff);
        uVar5 = (ushort)iVar6;
        uVar10 = sVar13 * -0x8000;
        uVar9 = uVar5 + uVar10;
        sVar13 = (short)((uint)iVar6 >> 0x10) + (sVar13 >> 1) +
                 (ushort)(uVar5 + uVar10 < uVar5 || uVar5 + uVar10 < uVar10);
        if (sVar13 < 0) {
          sVar13 = sVar13 + (ushort)(uVar9 - 1 < uVar9 || uVar9 != 0);
        }
      }
      else {
        iVar6 = (int)sVar13 * (int)(short)uVar9;
        uVar9 = (ushort)iVar6;
        sVar13 = (short)((uint)iVar6 >> 0x10);
        if (iVar6 < 0) {
          sVar13 = sVar13 + (ushort)(uVar9 - 1 < uVar9 || uVar9 != 0);
        }
      }
      MDH = (ushort)((uint)iVar6 >> 0x10);
      MDL = (ushort)iVar6;
      MDC = MDC | 0x10;
      uVar9 = me7_lookup_1d_word(0x39dc,8,uRam3029ec);
      uRam302a2a = func_0x0430da(uVar9 >> 2,sVar13,uRam302a2a._2_2_,(ushort)uRam302a2a,0,0,
                                 uRam023a0a >> 1,uRam023a0a << 0xf,uVar8);
      iVar6 = CONCAT22(MDH,MDL);
      uRam3052c2 = (short)(uRam302a2a >> 0x10) << 1;
    }
  }
  else {
    uRam3052c2 = 0;
    uRam306a2a = 0;
    uRam302a2a = (uint)(ushort)uRam302a2a;
  }
  if ((bRam304959 & 2) == 0) {
    if (uRam302e06 == 0) {
      uVar9 = 0x1000;
    }
    else {
      uVar3 = CONCAT22(uRam302e06 >> 4,uRam306e06 << 0xc) / (uint)uRam3052c2;
      uVar10 = (ushort)uVar3;
      MDC = MDC | 0x10;
      if (uRam3052c2 == 0 || 0xffff < uVar3) {
        uVar10 = 0xffff;
      }
      uVar9 = uVar10 + 0x1000;
      if (uVar10 + 0x1000 < uVar10 || uVar10 + 0x1000 < 0x1000) {
        uVar9 = 0xffff;
      }
    }
    uVar10 = MDC;
    uVar3 = ((uint)((ushort)bRam019db2 * -0x100 - 1 >> 4) << 0x10 | 0xf000) / (uint)uVar9;
    sRam3052a6 = (short)uVar3;
    if (uVar9 == 0 || 0xffff < uVar3) {
      sRam3052a6 = -1;
    }
    sRam3052a6 = sRam3052a6 + (ushort)bRam019db2 * 0x100;
    uRam3052cc = (ushort)((uint)uRam3052c2 * (uint)(-sRam3052a6 - 1) >> 0x10);
    uRam3052c6 = uRam3052c2 - uRam3052cc;
    sVar13 = (uRam3052c6 >> 1) - (uRam3052c8 >> 1);
    if (uRam3052c6 >> 1 < uRam3052c8 >> 1) {
      if (sVar13 >= 0) {
        sVar13 = -0x8000;
      }
    }
    else if (sVar13 < 0) {
      sVar13 = 0x7fff;
    }
    if ((bRam304959 & 1) == 0) {
      uRam3052ce = 0;
    }
    else if (sVar13 < 1) {
      uRam3052ce = 0;
    }
    else {
      uRam3052ce = sVar13 << 1;
    }
    sRam3052c4 = sVar13 - (uRam3052ce >> 1);
    if (sVar13 < 0 && (short)(sVar13 - (uRam3052ce >> 1)) < 0 != sVar13 < 0) {
      sRam3052c4 = -0x8000;
    }
    uVar9 = uRam306e06 - uRam3052cc;
    if (uRam306e06 < uRam3052cc) {
      uVar9 = 0;
    }
    uVar3 = ((uint)(uVar9 >> 1) << 0x10) / (uint)uRam302e00;
    uRam3052d0 = (ushort)uVar3;
    MDC = MDC | 0x10;
    if (uRam302e00 == 0 || 0xffff < uVar3) {
      uRam3052d0 = 0xffff;
    }
    if ((bRam305613 & 8) == 0) {
      if (uRam302a4a < uRam023a1a) {
        uRam302a4a = uRam302a4a + 1;
      }
      else {
        bRam301604 = bRam301604 & 0xdf;
      }
    }
    else {
      uRam302a4a = 0;
      bRam301604 = bRam301604 | 0x20;
    }
    if ((((bRam301604 & 0x20) != 0) &&
        (uRam302a2e = CONCAT22(uRam302a2e._2_2_,(undefined2)uRam302a2e), (bRam3015ff & 2) == 0)) &&
       (uRam302a2e = CONCAT22(uRam302a2e._2_2_,(undefined2)uRam302a2e), (bRam304958 & 1) == 0)) {
      uVar9 = uRam02396a >> 2;
      MDL = 0xffff / uVar9;
      MDH = 0xffff % uVar9;
      MDC = uVar10 | 0x10;
      uVar10 = MDL;
      if (uVar9 == 0) {
        uVar10 = 0xffff;
      }
      uRam302a2e = func_0x0430da(uVar10,sRam3052c4,uRam306a30,(undefined2)uRam302a2e,0,0,0x7fff,
                                 0xffff,uVar8);
      uRam3052ba = (short)((uint)uRam302a2e >> 0x10) << 1;
    }
    uRam3052d2 = (ushort)((uint)uRam3052ba * (uint)uRam3052d0 >> 0x10);
    iVar6 = (uint)uRam3052d0 * (uint)(-uRam3052ba - 1);
    MDL = (ushort)iVar6;
    uVar8 = (ushort)((uint)iVar6 >> 0x10);
    MDC = MDC | 0x10;
    MDH = uVar8;
    uRam3052d4 = uVar8;
    uVar9 = me7_lookup_1d_word(0x39f2,8,uRam3052d0);
    uVar9 = (ushort)(((uint)uVar9 * (uint)uVar8 >> 0x10) * (uint)uRam3052ba >> 0x10);
    uVar8 = uVar9 + uRam3052d2;
    if (uVar9 + uRam3052d2 < uVar9 || uVar9 + uRam3052d2 < uRam3052d2) {
      uVar8 = 0xffff;
    }
    uVar8 = (ushort)((uint)uVar8 * (uint)uRam302e00 >> 0x10);
    uRam3052c8 = uVar8 * 2;
    if (uVar8 * 2 < uVar8) {
      uRam3052c8 = 0xffff;
    }
    if (uRam3052ba < 0xfffe) {
      bRam304959 = bRam304959 & 0xfe;
    }
    else {
      bRam304959 = bRam304959 | 1;
    }
    if (uRam023a0e < uRam302e06) {
      sRam3052ca = uRam3052cc + uRam3052c8;
      if (uRam3052cc + uRam3052c8 < uRam3052cc || uRam3052cc + uRam3052c8 < uRam3052c8) {
        sRam3052ca = -1;
      }
      uVar9 = uRam023a0e;
      if (uRam023a0e <= uRam022e06) {
        uVar9 = uRam302e06;
      }
      if (sRam3052ca == 0) {
        uRam3052b8 = 0;
        uVar8 = uRam3052b8;
      }
      else {
        uVar3 = ((uint)uVar8 << 0x10) / (uint)uVar9;
        uVar8 = (ushort)uVar3;
        uRam3052b8 = uVar8;
        sRam307e0c = sRam3052ca;
        if (uVar9 == 0 || 0xffff < uVar3) {
          uVar8 = 0xffff;
          uRam3052b8 = uVar8;
        }
      }
    }
    else {
      uVar8 = uRam3052ba;
      if (uRam3052ba <= uRam3052bc) {
        uVar8 = uRam3052bc;
      }
    }
    uVar3 = CONCAT22(uRam302e06 >> 1,uRam302e06 << 0xf);
    uVar4 = uVar3 / uRam302e00;
    MDL = (ushort)uVar4;
    MDH = (ushort)(uVar3 % (uint)uRam302e00);
    MDC = MDC | 0x10;
    uRam3052d6 = MDL;
    if (uRam302e00 == 0 || 0xffff < uVar4) {
      uRam3052d6 = 0xffff;
    }
    uVar11 = me7_lookup_1d_word(0x3a1e,8,uRam3052d6);
    iRam302a42 = me7_pt1_integrator(uVar11,uVar8,iRam302a42._2_2_,(undefined2)iRam302a42);
    uRam3052bc = (ushort)((uint)iRam302a42 >> 0x10);
    iVar6 = CONCAT22(MDH,MDL);
  }
  else {
    uRam3052bc = 0;
    uRam306a44 = 0;
    iRam302a42 = (uint)iRam302a42._2_2_ << 0x10;
    uRam302a2e = 0;
    uRam3052ba = 0;
    bRam304959 = bRam304959 & 0xfe;
  }
  MDH = (ushort)((uint)iVar6 >> 0x10);
  MDL = (ushort)iVar6;
  if (((bRam301613 & 2) == 0) ||
     (((((bRam3015ff & 2) == 0 ||
        ((uRam0239c6 < _evap_purge_quantity && (_evap_purge_quantity < uRam0239c8)))) &&
       (sRam3029ee != sRam0239ce &&
        sRam3029ee - sRam0239ce < 0 ==
        (sRam3029ee < 0 != sRam0239ce < 0 && sRam3029ee - sRam0239ce < 0 != sRam3029ee < 0))) &&
      (sRam3029ee - sRam0239d0 < 0 !=
       (sRam3029ee < 0 != sRam0239d0 < 0 && sRam3029ee - sRam0239d0 < 0 != sRam3029ee < 0))))) {
    bRam301603 = bRam301603 & 0xdf;
    uRam302a48 = 0;
  }
  else if (uRam302a48 < uRam023a12) {
    uRam302a48 = uRam302a48 + 1;
  }
  else {
    bRam301603 = bRam301603 | 0x20;
  }
  if ((bRam304959 & 0x10) == 0) {
    if ((bRam301603 & 0x20) != 0) {
      bRam304958 = bRam304958 | 1;
    }
  }
  else {
    bRam304958 = bRam304958 & 0xfe;
  }
  cRam304953 = cRam304952;
  if (cRam304952 == cRam304951 ||
      (char)(cRam304952 - cRam304951) < '\0' !=
      (cRam304952 < '\0' != cRam304951 < '\0' &&
      (char)(cRam304952 - cRam304951) < '\0' != cRam304952 < '\0')) {
    cRam304953 = cRam304951;
  }
  if (cRam304953 < '\x01') {
    cRam304953 = '\0';
  }
  evap_purge_duty = me7_lookup_1d_byte(0x1da8,6,cRam304953);
  uRam30a0c4 = evap_purge_duty;
  uRam30a0c3 = evap_purge_duty;
  return;
}


// ================= cranking_inj_qty @ 07040c =================

/* WARNING: Removing unreachable block (ram,0x070660) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cranking injection quantity: start map 0x21282 keyed rpm x load (fueling.md 10) */

undefined2 cranking_inj_qty(void)

{
  bool bVar1;
  bool bVar2;
  short sVar3;
  int iVar4;
  ushort uVar5;
  undefined2 uVar6;
  uint uVar7;
  short sStack_a;
  
  if ((bRam01be74 & 0x10) == 0) {
    uRam3050f8 = 0;
  }
  else {
    uRam3050f8 = uRam0211f0;
  }
  if (((_flags_start_phase & 0x4000) == 0) || ((bRam01be74 & 8) == 0)) {
    bRam3014c4 = bRam3014c4 & 0xfe;
  }
  else {
    bRam3014c4 = bRam3014c4 | 1;
  }
  bRam30473e = me7_lookup_2d_byte(0x1282,8,nmot_rpmclass,rl_byte);
  MDL = (ushort)((uint)bRam30473e * 0x8500);
  MDH = (short)((uint)bRam30473e * 0x8500 >> 0x10);
  MDC = MDC | 0x10;
  uRam30510a = func_0x032cb8(MDL + 0xb000,
                             MDH + 0x4f + (ushort)(MDL + 0xb000 < MDL || MDL + 0xb000 < 0xb000),
                             0x7c83);
  uRam30510c = me7_lookup_1d_word(0x12f8,8,_rl_scaled);
  uRam305108 = func_0x040b88(0x5eb0,uRam30510a);
  uVar5 = uRam00f366;
  if (((bRam01be74 & 0x20) == 0) && (uVar5 = uRam00f368, (bRam01be74 & 0x40) == 0)) {
    uVar5 = uRam00f36a;
  }
  uRam3050fe = (uRam305108 - uRam00f364) - uVar5;
  sVar3 = (-(ushort)(uRam305108 < uRam00f364) - ((short)uRam00f364 >> 0xf)) -
          (ushort)(uRam305108 - uRam00f364 < uVar5);
  bVar2 = -1 < sVar3 && sVar3 + 1 < 0 != sVar3 < 0;
  bVar1 = sVar3 + 1 < 0;
  if ((sVar3 == -1 || bVar1 != bVar2) && ((bVar1 != bVar2 || (uRam3050fe < 0x8000)))) {
    uRam3050fe = 0x8000;
  }
  else if ((-1 < sVar3) && ((0 < sVar3 || (0x7fff < uRam3050fe)))) {
    uRam3050fe = 0x7fff;
  }
  uRam3027f4 = func_0x04195e(0x12e4,8,uRam3050fe,uRam3027f4);
  uRam305104 = uRam3035d8;
  uRam3027f2 = func_0x041844(0x12da,8,uRam3035d8,uRam3027f2);
  uRam3050fc = func_0x042290(0x11f2,8,0x12da,8,uRam3027f4,uRam3027f2);
  sRam305100 = func_0x042290(0x123a,8,0x12da,8,uRam3027f4,uRam3067f2);
  sStack_a = sRam305100;
  if ((bRam3058ce & 2) == 0) {
    sStack_a = 0;
  }
  uVar5 = func_0x042020(0xa8c,6,uRam301988);
  iVar4 = (int)(short)(uVar5 & 0xff) * (int)sStack_a;
  MDL = (ushort)iVar4;
  MDH = (short)((uint)iVar4 >> 0x10);
  MDC = MDC | 0x10;
  sRam305102 = (short)((uint)iVar4 >> 8);
  uVar5 = me7_lookup_1d_byte(0x12c8,8,uRam30a032);
  iVar4 = (int)(short)(uVar5 & 0xff) * (int)sRam305102;
  MDL = (ushort)iVar4;
  MDH = (short)((uint)iVar4 >> 0x10);
  MDC = MDC | 0x10;
  iVar4 = iVar4 >> 6;
  sVar3 = (short)((uint)iVar4 >> 0x10);
  uRam3050fa = (ushort)iVar4;
  bVar2 = -1 < iVar4 && sVar3 + 1 < 0 != iVar4 < 0;
  bVar1 = sVar3 + 1 < 0;
  if ((sVar3 == -1 || bVar1 != bVar2) && ((bVar1 != bVar2 || (uRam3050fa < 0x8000)))) {
    uRam3050fa = 0x8000;
  }
  else if (0x7fff < iVar4) {
    uRam3050fa = 0x7fff;
  }
  uRam305106 = func_0x0420a8(0x12b4,8,uRam301988);
  uVar7 = (uint)CONCAT12(bRam3054c4,uRam3005e0) & 0x1ffff;
  if ((bRam3054c4 & 1) == 0) {
    if ((bRam3018ce & 1) != 0) {
      uVar6 = func_0x0420a8(0x12b4,8,uRam301988,uRam0212c4,0,uRam0212c6,0);
      uVar7 = func_0x0430da(uVar6,uRam3050fc,uRam3045e2,uRam3005e0);
      uRam3005e2 = (undefined2)(uVar7 >> 0x10);
    }
  }
  else {
    uRam3045e2 = uRam3050f8;
    uVar7 = (uint)uRam3050f8 << 0x10;
  }
  uRam3005e0 = (undefined2)uVar7;
  _cranking_inj_qty = uRam3005e2;
  return (short)(uVar7 >> 0x10);
}


// ================= afterstart_enrich @ 07157a =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* after-start enrichment decay vs timer word_302D70 -> word_302812 (fueling.md 10) */

void afterstart_enrich(void)

{
  uRam3014ca = me7_lookup_1d_byte(0xa99,6,rpmclass_oppoint);
  if ((_flags_idle_state & 0x200) == 0) {
    uRam302812 = me7_lookup_2d_misc(uRam015f08,0x5f0a,uRam015f09,0x5f10,0x5f18,rpmclass_oppoint,
                                    _afterstart_timer);
  }
  else {
    uRam302812 = uRam015f06;
  }
  uRam302814 = uRam015f04;
  return;
}


// ================= start_state_machine @ 0d22b6 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* start/after-start state machine: word_FD7A.14/.15 + after-start timer word_302D70 */

void start_state_machine(void)

{
  byte bVar1;
  
  if ((_afterstart_timer != -1) && ((_flags_start_phase & 0x8000) != 0)) {
    _afterstart_timer = _afterstart_timer + 1;
  }
  if (((_flags_start_phase & 0x4000) == 0) && ((_flags_start_phase & 0x8000) == 0)) {
    if ((uRam00fd0e & 0x1000) != 0) {
      _flags_start_phase = _flags_start_phase | 0x4000;
    }
  }
  else {
    bVar1 = func_0x040b3e(0x476b,rpmclass_oppoint);
    if (bVar1 < nmot_rpmclass) {
      if ((_flags_start_phase & 0x4000) != 0) {
        _flags_start_phase = _flags_start_phase & 0xbfff | 0x8000;
        return;
      }
    }
    else {
      bVar1 = func_0x040b3e(0x4764,uRam301626);
      if ((nmot_rpmclass < bVar1) && ((_flags_start_phase & 0x4000) == 0)) {
        _flags_start_phase = _flags_start_phase & 0x7fff | 0x4000;
        return;
      }
    }
  }
  return;
}


// ================= rk_producer @ 0875d4 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* relative fuel mass rk: folds start/after-start enrich -> word_302968 */

void rk_producer(void)

{
  uint uVar1;
  short sVar2;
  ushort uVar3;
  byte bVar4;
  byte bVar5;
  ushort uVar6;
  ushort uVar7;
  
  uVar1 = (uint)((ushort)bRam304787 * (ushort)bRam30561e) * (uint)uRam30291c;
  uVar7 = (ushort)(uVar1 >> 0x10);
  uVar6 = uVar7 * 2;
  if (uVar7 * 2 < uVar7) {
    uVar6 = 0xffff;
  }
  if (((bRam014772 & 0x80) == 0) && ((uRam00fd48 & 2) != 0)) {
    uVar1 = (uint)uRam302d78 * (uint)uVar6;
    uVar6 = (ushort)(uVar1 >> 0xc);
    if ((short)((uVar1 >> 0xc) >> 0x10) != 0) {
      uVar6 = 0xffff;
    }
  }
  MDC = MDC | 0x10;
  if ((uRam00fd48 & 2) == 0) {
    bVar5 = 2;
  }
  else {
    bVar5 = 0;
  }
  bVar4 = 0;
  while( true ) {
    MDH = (ushort)(uVar1 >> 0x10);
    MDL = (undefined2)uVar1;
    if (bVar5 < bVar4) break;
    MDC = MDC | 0x10;
    uVar1 = (uint)*(ushort *)((uint3)bVar4 * 2 + 0x30290e) * (uint)uVar6 >> 10;
    uVar7 = (ushort)uVar1;
    if ((short)(uVar1 >> 0x10) == 0) {
      *(ushort *)((uint3)bVar4 * 2 + 0x30295a) = uVar7;
    }
    else {
      uVar7 = 0xffff;
      *(undefined2 *)((uint3)bVar4 * 2 + 0x30295a) = 0xffff;
    }
    uVar1 = (uint)uRam302a94 * (uint)uVar7 >> 0xb;
    uVar7 = (ushort)uVar1;
    if ((short)(uVar1 >> 0x10) != 0) {
      uVar7 = 0xffff;
    }
    if ((short)uRam302958 < 0) {
      uVar3 = uRam302958 + uVar7;
      if (uRam302958 <= uRam302958 + uVar7 && uVar7 <= uRam302958 + uVar7) {
        uVar3 = 0;
      }
    }
    else {
      uVar3 = uRam302958 + uVar7;
      if (uRam302958 + uVar7 < uRam302958 || uRam302958 + uVar7 < uVar7) {
        uVar3 = 0xffff;
      }
    }
    if (bVar4 == 0) {
      if (uVar3 < 0x8000) {
        sRam30296a = uVar3 << 1;
      }
      else {
        sRam30296a = -1;
      }
    }
    if (((uRam00fd48 & 2) != 0) &&
       (uVar1 = CONCAT22(uVar3 >> 4,uVar3 << 0xc) / (uint)uRam30294a, uVar3 = (ushort)uVar1,
       uRam30294a == 0 || 0xffff < uVar1)) {
      uVar3 = 0xffff;
    }
    uVar7 = (ushort)((uint)uVar3 * (uint)_start_enrich_factor >> 0x10);
    uVar3 = uVar7 * 2;
    if (uVar7 * 2 < uVar7) {
      uVar3 = 0xffff;
    }
    if ((short)uRam302936 < 0) {
      uVar7 = uRam302936 + uVar3;
      if (uRam302936 <= uRam302936 + uVar3 && uVar3 <= uRam302936 + uVar3) {
        uVar7 = 0;
      }
    }
    else {
      uVar7 = uRam302936 + uVar3;
      if (uRam302936 + uVar3 < uRam302936 || uRam302936 + uVar3 < uVar3) {
        uVar7 = 0xffff;
      }
    }
    MDL = (undefined2)((uint)uVar7 * (uint)uRam302956);
    MDH = (ushort)((uint)uVar7 * (uint)uRam302956 >> 0x10);
    MDC = MDC | 0x10;
    uVar7 = MDH * 2;
    if (MDH * 2 < MDH) {
      uVar7 = 0xffff;
    }
    uVar3 = uVar7;
    if (bVar4 != 0) {
      uVar3 = uRam302966;
    }
    uRam302966 = uVar3;
    if ((short)uRam302a14 < 0) {
      uVar3 = -uRam302a14;
      sVar2 = uVar3 + uVar7;
      if (uVar3 + uVar7 < uVar3 || uVar3 + uVar7 < uVar7) {
        sVar2 = -1;
      }
    }
    else {
      sVar2 = uVar7 - uRam302a14;
      if (uVar7 < uRam302a14) {
        sVar2 = 0;
      }
    }
    *(short *)((uint3)bVar4 * 2 + 0x302960) = sVar2;
    uVar1 = CONCAT22(MDH,MDL);
    bVar4 = bVar4 + 1;
  }
  _rk_w = uRam302960;
  return;
}


// ================= start_inj_assembly @ 0717f0 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* start/warm injection-factor assembly -> word_30281A */

void start_inj_assembly(void)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  ushort uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  int iVar11;
  ushort uVar12;
  ushort uVar13;
  short sVar14;
  ushort uVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  short sVar19;
  
  uVar6 = uRam016066;
  if ((bRam301667 & 1) == 0) {
    uRam302834 = uRam016068;
    bRam304741 = func_0x0433ba(uRam01606a,0x606c,0x6078,_rl_scaled);
  }
  else {
    uRam306834 = uRam30531a;
    bRam304741 = bRam304989;
  }
  uVar12 = (PSW & 8) >> 3;
  PSW = PSW & 0xffbf;
  if ((uRam00fd36 & 0x100) != 0x100) {
    uRam302848 = uRam302834 >> 1;
    uRam30284a = uRam302848;
  }
  if (uRam30284a == 0) {
    if (uRam302848 != 0) {
      uRam302848 = uRam302848 - 1;
    }
    uRam302808 = (ushort)bRam304741 * -0x20;
  }
  else {
    uRam302808 = (ushort)bRam304741 << 5;
    uRam30284a = uRam30284a - 1;
  }
  uRam30280a = uRam302808;
  if ((short)uRam302808 < 1) {
    bRam3014cd = bRam3014cd & 0xfe;
  }
  else {
    bRam3014cd = bRam3014cd | 1;
  }
  if (((bRam3014cd & 1) != 0) != ((bRam3014cd & 2) != 0)) {
    PSW = PSW | (uVar12 ^ 1) << 6 | 0x40;
  }
  uRam00fd36 = uRam00fd36 & 0xfe7f | uVar12 << 8 | ((PSW & 0x40) >> 6) << 7;
  if ((bRam3014cd & 1) == 0) {
    bRam3014cd = bRam3014cd & 0xfd;
  }
  else {
    bRam3014cd = bRam3014cd | 2;
  }
  uRam302892 = me7_slew_limiter(uRam302846,uRam302808,uRam302892._2_2_,(undefined2)uRam302892);
  uRam302804 = func_0x04385e(0xa862,(short)((uint)uRam302892 >> 0x10),uRam302844,0xe39);
  if ((short)uRam302804 < 0) {
    uVar12 = uRam302804 + 0x8000;
    if (uRam302804 <= uRam302804 + 0x8000 && 0x7fff < uRam302804 + 0x8000) {
      uVar12 = 0;
    }
  }
  else {
    uVar12 = uRam302804 + 0x8000;
    if (uRam302804 + 0x8000 < uRam302804 || uRam302804 + 0x8000 < 0x8000) {
      uVar12 = 0xffff;
    }
  }
  MDL = (ushort)(0x40000000 / (uint)uVar12);
  MDH = (undefined2)(0x40000000 % (uint)uVar12);
  MDC = MDC | 0x10;
  uVar15 = MDL;
  if (uVar12 == 0 || 0xffff < 0x40000000 / (uint)uVar12) {
    uVar15 = 0xffff;
  }
  sRam302806 = uVar15 + 0x8000;
  if (uVar15 < 0x8000) {
    if (sRam302806 >= 0) {
      sRam302806 = -0x8000;
    }
  }
  else if (sRam302806 < 0) {
    sRam302806 = 0x7fff;
  }
  if ((bRam018a98 & 1) != 0) {
    uRam00fd36 = uRam00fd36 & 0xffbf | ((DAT_00fd34 & 0x20) >> 5) << 6;
    goto LAB_071a3e;
  }
  if (((bRam3014cd & 8) == 0) && ((DAT_00fd34 & 0x20) != 0)) {
    if ((bRam3014cb & 1) == 0) {
      if ((bRam018a98 & 0x10) != 0) {
        if (sRam30281c == -0x8000) {
          sVar19 = 0x7fff;
        }
        else {
          sVar19 = sRam30281c;
          if (sRam30281c < 0) {
            sVar19 = -sRam30281c;
          }
        }
        if (sVar19 != sRam016064 &&
            sVar19 - sRam016064 < 0 ==
            (sVar19 < 0 != sRam016064 < 0 && sVar19 - sRam016064 < 0 != sVar19 < 0))
        goto LAB_0719e4;
      }
      uRam3027fe = uRam30280c;
    }
    else {
LAB_0719e4:
      if (((bRam018a98 & 0x20) == 0) && (-1 < (short)uRam30280c)) {
        PSW = PSW & 0xffbf;
      }
      else {
        PSW = PSW | 0x40;
      }
      uRam00fd36 = uRam00fd36 & 0xffbf | PSW & 0x40;
      uRam3027fe = 0;
    }
  }
  else {
    uRam00fd36 = uRam00fd36 & 0xffbf;
    if ((bRam018a98 & 2) != 0) {
      uRam3027fe = uRam30280c;
    }
  }
  if ((DAT_00fd34 & 0x20) == 0) {
    bRam3014cd = bRam3014cd & 0xf7;
  }
  else {
    bRam3014cd = bRam3014cd | 8;
  }
LAB_071a3e:
  if ((((bRam013833 & 0x40) == 0) || ((DAT_00fd34 & 0x200) == 0)) &&
     (((bRam013833 & 0x40) != 0 || (((DAT_00fd34 & 0x200) == 0 || ((bRam3014cd & 4) != 0)))))) {
    PSW = PSW & 0xffbf;
  }
  else {
    PSW = PSW | 0x40;
  }
  uVar12 = PSW & 0x40;
  if ((DAT_00fd34 & 0x200) == 0) {
    bRam3014cd = bRam3014cd & 0xfb;
  }
  else {
    bRam3014cd = bRam3014cd | 4;
  }
  if (((bRam013833 & 4) == 0) &&
     (((((((DAT_00fd34 & 0x100) == 0 || ((DAT_00fd34 & 0x20) != 0)) || ((bRam3014c6 & 1) != 0)) ||
        ((uRam304f82 < uRam306080 || (0x1001 < uRam30294c)))) || (uRam30294c < 0xfff)) ||
      (rpmclass_oppoint < bRam013899)))) {
    PSW = PSW & 0xffbf;
  }
  else {
    PSW = PSW | 0x40;
  }
  uVar15 = (PSW & 0x40) >> 6;
  uRam00fd36 = uRam00fd36 & 0xeffb | (uVar12 >> 6) << 2 | uVar15 << 0xc;
  uVar12 = sRam30280e >> 3;
  if ((short)uVar12 < 0) {
    uVar12 = -uVar12;
    uRam302824 = uVar12 + uRam302736;
    if (uVar12 + uRam302736 < uVar12 || uVar12 + uRam302736 < uRam302736) {
      uRam302824 = 0xffff;
    }
  }
  else {
    uRam302824 = uRam302736 - uVar12;
    if (uRam302736 < uVar12) {
      uRam302824 = 0;
    }
  }
  if (uVar15 != 0) {
    uVar12 = sRam302806 >> 3;
    if ((short)uVar12 < 0) {
      uVar12 = -uVar12;
      uVar15 = uVar12 + uRam302824;
      bVar1 = uVar12 + uRam302824 < uRam302824;
      uRam302824 = uVar12 + uRam302824;
      if (uVar15 < uVar12 || bVar1) {
        uRam302824 = 0xffff;
      }
    }
    else {
      bVar1 = uRam302824 < uVar12;
      uRam302824 = uRam302824 - uVar12;
      if (bVar1) {
        uRam302824 = 0;
      }
    }
  }
  uRam302822 = uRam302824;
  if ((uRam30294c <= uVar6) && (uRam302824 < uVar6)) {
    uRam302822 = uVar6;
  }
  uVar12 = func_0x04385e(0xa86a,uRam30294a,uRam302844,0x1555);
  sVar14 = cRam3014c9 * 8;
  sVar19 = sRam302810 + sVar14;
  if (sRam302810 < 0 == sVar14 < 0 && sRam302810 + sVar14 < 0 != sRam302810 < 0) {
    sVar19 = 0x7fff;
  }
  uVar15 = sVar19 >> 3;
  if ((short)uVar15 < 0) {
    uRam302820 = uVar15 + uVar12;
    if (uVar15 <= uVar15 + uVar12 && uVar12 <= uVar15 + uVar12) {
      uRam302820 = 0;
    }
  }
  else {
    uRam302820 = uVar15 + uVar12;
    if (uVar15 + uVar12 < uVar15 || uVar15 + uVar12 < uVar12) {
      uRam302820 = 0xffff;
    }
  }
  uRam30281e = uRam302820;
  if ((uRam30294c <= uVar6) && (uRam302820 < uVar6)) {
    uRam30281e = uVar6;
  }
  uVar12 = uRam302822 - uRam30281e;
  if (uRam302822 < uRam30281e) {
    if ((short)uVar12 >= 0) {
      uVar12 = 0x8000;
    }
  }
  else if ((short)uVar12 < 0) {
    uVar12 = 0x7fff;
  }
  sVar19 = uVar12 * -0x8000;
  uVar13 = ((short)uVar12 >> 0xf) << 0xf;
  uVar15 = uVar13 | uVar12 >> 1;
  iVar17 = CONCAT22(uVar15,sVar19);
  if (uVar13 == 0) {
    uVar7 = CONCAT22(uVar15,sVar19) / (uint)uRam30281e;
    MDL = (ushort)uVar7;
    MDH = (undefined2)(CONCAT22(uVar15,sVar19) % (uint)uRam30281e);
    if ((uRam30281e == 0 || 0xffff < uVar7) || (sVar14 = MDL, (short)MDL < 0)) {
      sVar14 = 0x7fff;
    }
  }
  else {
    uVar7 = CONCAT22(-(ushort)(sVar19 != 0) - uVar15,uVar12 * -0x8000);
    uVar8 = uVar7 / uRam30281e;
    MDL = (ushort)uVar8;
    MDH = (undefined2)(uVar7 % (uint)uRam30281e);
    if ((uRam30281e == 0 || 0xffff < uVar8) || ((short)MDL < 0)) {
      sVar14 = -0x8000;
    }
    else {
      sVar14 = -MDL;
    }
  }
  MDC = MDC | 0x10;
  if ((DAT_00fd34 & 0x100) == 0) {
    uRam30284c = 0;
  }
  else if (uRam30284c != 0xffff) {
    uRam30284c = me7_fraction_blend(0x1999,0xff,uRam30284c,sVar19,uVar15);
  }
  if ((short)uRam30284c < 0) {
    iVar18 = (int)sVar14 * (int)(short)(uRam30284c & 0x7fff);
    uVar15 = (ushort)iVar18;
    uVar12 = sVar14 * -0x8000;
    sRam30281c = (short)((uint)iVar18 >> 0x10) + (sVar14 >> 1) +
                 (ushort)(uVar15 + uVar12 < uVar15 || uVar15 + uVar12 < uVar12);
  }
  else {
    iVar18 = (int)sVar14 * (int)(short)uRam30284c;
    sRam30281c = (short)((uint)iVar18 >> 0x10);
  }
  MDH = (undefined2)((uint)iVar18 >> 0x10);
  MDL = (ushort)iVar18;
  MDC = MDC | 0x10;
  uRam302880 = uRam302812 + 0x8000;
  if ((((DAT_00fd34 & 0x100) == 0) || ((uRam00fd36 & 0x40) != 0)) || ((uRam00fd36 & 4) != 0)) {
    uRam30280c = 0;
    uRam302840 = 0;
    uRam302890 = 0;
    sRam302842 = 0;
    uRam302836 = 0;
    uRam302838 = 0;
    iVar16 = 0;
    iVar11 = 0;
    uRam30283c = 0;
    uRam302886 = 0;
    uRam302888 = 0;
    uRam30283e = 0;
    uRam30288a = 0;
    uRam30288c = 0;
    uRam00fd36 = uRam00fd36 & 0xf3ff | 0x200;
    uVar10 = uRam302892;
  }
  else {
    if ((DAT_00fd34 & 2) != 0) {
      uRam30283a = uRam3027da + 0x8000;
      uRam302882 = 0;
      uRam302884 = uRam30283a;
    }
    if ((((bRam013833 & 0x20) == 0) || (uVar6 < uRam30294c)) ||
       ((uVar6 < uRam302820 || (uVar6 < uRam302824)))) {
      PSW = PSW & 0xffbf;
    }
    else {
      PSW = PSW | 0x40;
    }
    uVar6 = uRam00fd36 & 0x20;
    uRam00fd36 = uRam00fd36 & 0xffdf | ((PSW & 0x40) >> 6) << 5;
    if (uVar6 == 0x20) {
      iVar16 = me7_slew_limiter(uRam01607e,0,uRam302884,uRam302882);
      uRam302890 = (ushort)((uint)iVar16 >> 0x10);
      iVar18 = CONCAT22(MDH,MDL);
      iVar11 = iVar16;
    }
    else {
      uRam302800 = uRam302880;
      if (((DAT_00fd34 & 0x20) != 0) && ((bRam018a98 & 0x40) == 0)) {
        uRam302800 = uRam3027fe;
      }
      iVar17 = func_0x0e4058();
      iVar16 = CONCAT22(uRam30283a,uRam302882);
      sVar19 = (short)((uint)iVar17 >> 0x10);
      bVar5 = iVar17 < 0 && sVar19 + -0x1ff < 0 != iVar17 < 0;
      bVar1 = sVar19 + -0x1ff < 0;
      if ((bVar1 == bVar5) && (sVar19 != 0x1ff && bVar1 == bVar5)) {
        iVar17 = 0x1ffffff;
      }
      else {
        bVar5 = -1 < iVar17 && sVar19 + 0x200 < 0 != iVar17 < 0;
        bVar1 = sVar19 + 0x200 < 0;
        if ((sVar19 == -0x200 || bVar1 != bVar5) && (bVar1 != bVar5)) {
          iVar17 = -0x2000000;
        }
      }
      iVar18 = (int)(short)((ushort)iVar17 >> 10 | (short)((uint)iVar17 >> 0x10) << 6) * 0x148;
      uVar12 = (ushort)iVar18;
      sVar14 = (short)((uint)iVar18 >> 0x10);
      MDC = MDC | 0x10;
      bVar1 = uRam302882 + uVar12 < uRam302882;
      bVar5 = uRam302882 + uVar12 < uVar12;
      uVar6 = (ushort)(bVar1 || bVar5);
      sVar19 = uRam302882 + uVar12;
      uVar12 = uRam302884 + sVar14;
      uRam302890 = uRam302884 + sVar14 + uVar6;
      if ((short)uRam302884 < 0 == iVar18 < 0 &&
          (short)(uVar12 + uVar6) < 0 != (short)uRam302884 < 0) {
        if (uVar12 < uRam302884 || uVar12 == 0xffff && (bVar1 || bVar5)) {
          sVar19 = 0;
          uRam302890 = 0x8000;
        }
        else {
          sVar19 = -1;
          uRam302890 = 0x7fff;
        }
      }
      iVar17 = iVar18;
      if (uRam302890 == uRam01608a ||
          (short)(uRam302890 - uRam01608a) < 0 !=
          ((short)uRam302890 < 0 != (short)uRam01608a < 0 &&
          (short)(uRam302890 - uRam01608a) < 0 != (short)uRam302890 < 0)) {
        if ((short)(uRam302890 - uRam302800) < 0 ==
            ((short)uRam302890 < 0 != (short)uRam302800 < 0 &&
            (short)(uRam302890 - uRam302800) < 0 != (short)uRam302890 < 0)) {
          uRam00fd36 = uRam00fd36 & 0xf3ff;
          iVar16 = CONCAT22(uRam30283a,uRam302882);
          iVar11 = CONCAT22(uRam302884,sVar19);
        }
        else {
          uRam302890 = uRam302800;
          uRam00fd36 = uRam00fd36 & 0xfbff | 0x800;
          iVar16 = CONCAT22(uRam30283a,uRam302882);
          iVar11 = (uint)uRam302884 << 0x10;
        }
      }
      else {
        uRam302890 = uRam01608a;
        uRam00fd36 = uRam00fd36 & 0xf7ff | 0x400;
        iVar11 = (uint)uRam302884 << 0x10;
      }
    }
    uRam302884 = (ushort)((uint)iVar11 >> 0x10);
    uRam30288e = (undefined2)iVar11;
    uRam30283a = (ushort)((uint)iVar16 >> 0x10);
    uRam302882 = (ushort)iVar16;
    MDH = (undefined2)((uint)iVar18 >> 0x10);
    MDL = (ushort)iVar18;
    uRam302840 = uRam302890;
    if ((flags_diag_cfg_b & 0x200) == 0) {
      iVar17 = func_0x0e4058(iVar17);
      uVar13 = (ushort)((uint)iVar17 >> 0x10);
      uVar15 = (ushort)iVar17;
      iVar18 = func_0x0e4058();
      sVar19 = (short)((uint)iVar18 >> 0x10);
      uVar12 = (ushort)iVar18;
      bVar1 = uVar15 + uVar12 < uVar15;
      bVar5 = uVar15 + uVar12 < uVar12;
      uVar6 = (ushort)(bVar1 || bVar5);
      uVar15 = uVar15 + uVar12;
      uVar12 = uVar13 + sVar19;
      sVar19 = uVar13 + sVar19 + uVar6;
      if (iVar17 < 0 == iVar18 < 0 && (short)(uVar12 + uVar6) < 0 != iVar17 < 0) {
        if (uVar12 < uVar13 || uVar12 == 0xffff && (bVar1 || bVar5)) {
          uVar15 = 0;
          sVar19 = -0x8000;
        }
        else {
          uVar15 = 0xffff;
          sVar19 = 0x7fff;
        }
      }
      uVar6 = ((short)uRam016082 >> 0xf) << 0xb | uRam016082 >> 5;
      bVar1 = uRam016082 * 0x800 < uVar15;
      if ((short)((uVar6 - sVar19) - (ushort)bVar1) < 0 ==
          ((short)uVar6 < 0 != sVar19 < 0 &&
          (short)((uVar6 - sVar19) - (ushort)bVar1) < 0 != (short)uVar6 < 0)) {
        uVar13 = uRam016084 * 0x800;
        uVar6 = ((short)uRam016084 >> 0xf) << 0xb | uRam016084 >> 5;
        uVar12 = (ushort)(uVar13 < uVar15);
        if (uVar6 - sVar19 == uVar12 && uVar13 == uVar15 ||
            (short)((uVar6 - sVar19) - uVar12) < 0 !=
            ((short)uVar6 < 0 != sVar19 < 0 &&
            (short)((uVar6 - sVar19) - (ushort)(uVar13 < uVar15)) < 0 != (short)uVar6 < 0)) {
          uRam302836 = uVar15 >> 0xb | sVar19 << 5;
        }
        else {
          uRam302836 = uRam016084;
        }
      }
      else {
        uRam302836 = uRam016082;
      }
      iVar17 = func_0x0e4058(iVar18);
      uVar13 = (ushort)((uint)iVar17 >> 0x10);
      uVar15 = (ushort)iVar17;
      iVar18 = func_0x0e4058();
      iVar11 = CONCAT22(uRam302884,uRam30288e);
      iVar16 = CONCAT22(uRam30283a,uRam302882);
      sVar19 = (short)((uint)iVar18 >> 0x10);
      uVar12 = (ushort)iVar18;
      bVar1 = uVar15 + uVar12 < uVar15;
      bVar5 = uVar15 + uVar12 < uVar12;
      uVar6 = (ushort)(bVar1 || bVar5);
      uVar15 = uVar15 + uVar12;
      uVar12 = uVar13 + sVar19;
      sVar19 = uVar13 + sVar19 + uVar6;
      if (iVar17 < 0 == iVar18 < 0 && (short)(uVar12 + uVar6) < 0 != iVar17 < 0) {
        if (uVar12 < uVar13 || uVar12 == 0xffff && (bVar1 || bVar5)) {
          uVar15 = 0;
          sVar19 = -0x8000;
        }
        else {
          uVar15 = 0xffff;
          sVar19 = 0x7fff;
        }
      }
      uVar6 = ((short)uRam016082 >> 0xf) << 0xb | uRam016082 >> 5;
      bVar1 = uRam016082 * 0x800 < uVar15;
      if ((short)((uVar6 - sVar19) - (ushort)bVar1) < 0 ==
          ((short)uVar6 < 0 != sVar19 < 0 &&
          (short)((uVar6 - sVar19) - (ushort)bVar1) < 0 != (short)uVar6 < 0)) {
        uVar13 = uRam016084 * 0x800;
        uVar6 = ((short)uRam016084 >> 0xf) << 0xb | uRam016084 >> 5;
        uVar12 = (ushort)(uVar13 < uVar15);
        if (uVar6 - sVar19 == uVar12 && uVar13 == uVar15 ||
            (short)((uVar6 - sVar19) - uVar12) < 0 !=
            ((short)uVar6 < 0 != sVar19 < 0 &&
            (short)((uVar6 - sVar19) - (ushort)(uVar13 < uVar15)) < 0 != (short)uVar6 < 0)) {
          uRam302838 = uVar15 >> 0xb | sVar19 << 5;
        }
        else {
          uRam302838 = uRam016084;
        }
      }
      else {
        uRam302838 = uRam016082;
      }
      sVar19 = uRam302838 - uRam302836;
      if ((short)uRam302838 < 0 != (short)uRam302836 < 0 &&
          (short)(uRam302838 - uRam302836) < 0 != (short)uRam302838 < 0) {
        sVar19 = -0x8000;
      }
      iVar17 = (int)sRam302832 * (int)sVar19;
      sVar19 = (short)((uint)iVar17 >> 0x10);
      bVar5 = iVar17 < 0 && sVar19 + -0x1ff < 0 != iVar17 < 0;
      bVar1 = sVar19 + -0x1ff < 0;
      if ((bVar1 == bVar5) && (sVar19 != 0x1ff && bVar1 == bVar5)) {
        iVar17 = 0x1ffffff;
      }
      else {
        bVar5 = -1 < iVar17 && sVar19 + 0x200 < 0 != iVar17 < 0;
        bVar1 = sVar19 + 0x200 < 0;
        if ((sVar19 == -0x200 || bVar1 != bVar5) && (bVar1 != bVar5)) {
          iVar17 = -0x2000000;
        }
      }
      uVar6 = (ushort)iVar17 >> 10 | (short)((uint)iVar17 >> 0x10) << 6;
      sVar19 = (short)uRam302836 >> 1;
      sRam302842 = uVar6 + sVar19;
      if ((short)uVar6 < 0 == sVar19 < 0 && (short)(uVar6 + sVar19) < 0 != (short)uVar6 < 0) {
        sRam302842 = 0x7fff;
      }
      iVar17 = (int)sRam302826 * (int)sRam30281c;
      uVar15 = (ushort)iVar17;
      uVar13 = (ushort)((uint)iVar17 >> 0x10);
      iVar18 = (int)sRam30282a * (int)sRam302842;
      iVar9 = iVar18 >> 1;
      uVar12 = (ushort)iVar9;
      sVar19 = (short)((uint)iVar9 >> 0x10);
      bVar1 = uVar15 + uVar12 < uVar15;
      bVar5 = uVar15 + uVar12 < uVar12;
      uVar6 = (ushort)(bVar1 || bVar5);
      uVar15 = uVar15 + uVar12;
      uVar12 = uVar13 + sVar19;
      sVar19 = uVar13 + sVar19 + uVar6;
      if (iVar17 < 0 == iVar9 < 0 && (short)(uVar12 + uVar6) < 0 != iVar17 < 0) {
        if (uVar12 < uVar13 || uVar12 == 0xffff && (bVar1 || bVar5)) {
          uVar15 = 0;
          sVar19 = -0x8000;
        }
        else {
          uVar15 = 0xffff;
          sVar19 = 0x7fff;
        }
      }
      bVar5 = sVar19 < 0 && sVar19 + -0x1ff < 0 != sVar19 < 0;
      bVar1 = sVar19 + -0x1ff < 0;
      if ((bVar1 == bVar5) && (sVar19 != 0x1ff && bVar1 == bVar5)) {
        uVar15 = 0xffff;
        sVar19 = 0x1ff;
      }
      else {
        bVar5 = -1 < sVar19 && sVar19 + 0x200 < 0 != sVar19 < 0;
        bVar1 = sVar19 + 0x200 < 0;
        if ((sVar19 == -0x200 || bVar1 != bVar5) && (bVar1 != bVar5)) {
          uVar15 = 0;
          sVar19 = -0x200;
        }
      }
      uVar6 = uVar15 >> 10 | sVar19 << 6;
      uRam302802 = uRam302840 + uVar6;
      if ((short)uRam302840 < 0 == (short)uVar6 < 0 &&
          (short)(uRam302840 + uVar6) < 0 != (short)uRam302840 < 0) {
        uRam302802 = 0x7fff;
        iVar16 = CONCAT22(uRam30283a,uRam302882);
        iVar11 = CONCAT22(uRam302884,uRam30288e);
      }
    }
    else {
      iVar18 = (int)sRam302826 * (int)sRam30281c;
      sVar19 = (short)((uint)iVar18 >> 0x10);
      bVar5 = iVar18 < 0 && sVar19 + -0x1ff < 0 != iVar18 < 0;
      bVar1 = sVar19 + -0x1ff < 0;
      if ((bVar1 == bVar5) && (sVar19 != 0x1ff && bVar1 == bVar5)) {
        iVar9 = 0x1ffffff;
      }
      else {
        bVar5 = -1 < iVar18 && sVar19 + 0x200 < 0 != iVar18 < 0;
        bVar1 = sVar19 + 0x200 < 0;
        iVar9 = iVar18;
        if ((sVar19 == -0x200 || bVar1 != bVar5) && (bVar1 != bVar5)) {
          iVar9 = -0x2000000;
        }
      }
      uVar6 = (ushort)iVar9 >> 10 | (short)((uint)iVar9 >> 0x10) << 6;
      uRam302802 = uRam302890 + uVar6;
      if ((short)uRam302890 < 0 == (short)uVar6 < 0 &&
          (short)(uRam302890 + uVar6) < 0 != (short)uRam302890 < 0) {
        uRam302802 = 0x7fff;
      }
      uRam302886 = 0;
      uRam302888 = 0;
      uRam30283c = 0;
      uRam30288a = 0;
      uRam30288c = 0;
      uRam30283e = 0;
    }
    uRam302884 = (ushort)((uint)iVar11 >> 0x10);
    uRam30288e = (undefined2)iVar11;
    uRam30283a = (ushort)((uint)iVar16 >> 0x10);
    uRam302882 = (ushort)iVar16;
    MDH = (undefined2)((uint)iVar18 >> 0x10);
    MDL = (ushort)iVar18;
    MDC = MDC | 0x10;
    if (((DAT_00fd34 & 0x20) == 0) ||
       ((short)(uRam302802 - uRam3027fe) < 0 ==
        ((short)uRam302802 < 0 != (short)uRam3027fe < 0 &&
        (short)(uRam302802 - uRam3027fe) < 0 != (short)uRam302802 < 0))) {
      uRam30280c = uRam302802;
      uRam00fd36 = uRam00fd36 | 0x200;
    }
    else {
      uRam30280c = uRam3027fe;
      uRam00fd36 = uRam00fd36 & 0xfdff;
    }
    if ((((uRam00fd36 & 0x200) != 0) || ((bRam018a98 & 0x40) == 0)) && ((uRam00fd36 & 0x20) == 0)) {
      iVar17 = func_0x0e4058(iVar17);
      sVar19 = (short)((uint)iVar17 >> 0x10);
      bVar5 = iVar17 < 0 && sVar19 + -0x1ff < 0 != iVar17 < 0;
      bVar1 = sVar19 + -0x1ff < 0;
      if ((bVar1 == bVar5) && (sVar19 != 0x1ff && bVar1 == bVar5)) {
        iVar17 = 0x1ffffff;
      }
      else {
        bVar5 = -1 < iVar17 && sVar19 + 0x200 < 0 != iVar17 < 0;
        bVar1 = sVar19 + 0x200 < 0;
        if ((sVar19 == -0x200 || bVar1 != bVar5) && (bVar1 != bVar5)) {
          iVar17 = -0x2000000;
        }
      }
      uVar6 = (ushort)iVar17 >> 10 | (short)((uint)iVar17 >> 0x10) << 6;
      if ((uRam00fd36 & 0x400) == 0) {
        if ((uRam00fd36 & 0x800) == 0) {
          iVar18 = (int)(short)uVar6 * 0x28f;
          uVar12 = (ushort)iVar18;
          sVar19 = (short)((uint)iVar18 >> 0x10);
          bVar1 = uRam302882 + uVar12 < uRam302882;
          bVar5 = uRam302882 + uVar12 < uVar12;
          uVar6 = (ushort)(bVar1 || bVar5);
          uRam302882 = uRam302882 + uVar12;
          uVar12 = uRam302884 + sVar19;
          bVar2 = uVar12 < uRam302884;
          bVar3 = (short)uRam302884 < 0;
          bVar4 = (short)uRam302884 < 0;
          uRam302884 = uRam302884 + sVar19 + uVar6;
          if (bVar3 == iVar18 < 0 && (short)(uVar12 + uVar6) < 0 != bVar4) {
            if (bVar2 || uVar12 == 0xffff && (bVar1 || bVar5)) {
              uRam302882 = 0;
              uRam302884 = -0x8000;
            }
            else {
              uRam302882 = -1;
              uRam302884 = 0x7fff;
            }
          }
        }
        else {
          iVar18 = (int)(short)uVar6 * 0x148;
          sVar19 = (short)iVar18;
          uVar12 = (ushort)((uint)iVar18 >> 0x10);
          uVar6 = (ushort)(sVar19 != 0);
          uRam302882 = -sVar19;
          uRam302884 = (uRam302800 - uVar12) - uVar6;
          if ((short)uRam302800 < 0 != iVar18 < 0 &&
              (short)((uRam302800 - uVar12) - uVar6) < 0 != (short)uRam302800 < 0) {
            if (uRam302800 < uVar12 || uRam302800 == uVar12 && sVar19 != 0) {
              uRam302882 = -1;
              uRam302884 = 0x7fff;
            }
            else {
              uRam302882 = 0;
              uRam302884 = -0x8000;
            }
          }
        }
      }
      else {
        iVar18 = (int)(short)uVar6 * 0x148;
        sVar19 = (short)iVar18;
        uVar12 = (ushort)((uint)iVar18 >> 0x10);
        uVar6 = (ushort)(sVar19 != 0);
        uRam302882 = -sVar19;
        uRam302884 = (uRam01608a - uVar12) - uVar6;
        if ((short)uRam01608a < 0 != iVar18 < 0 &&
            (short)((uRam01608a - uVar12) - uVar6) < 0 != (short)uRam01608a < 0) {
          if (uRam01608a < uVar12 || uRam01608a == uVar12 && sVar19 != 0) {
            uRam302882 = -1;
            uRam302884 = 0x7fff;
          }
          else {
            uRam302882 = 0;
            uRam302884 = -0x8000;
          }
        }
      }
      iVar11 = CONCAT22(uRam302884,uRam30288e);
      MDC = MDC | 0x10;
      iVar16 = CONCAT22(uRam302884,uRam302882);
    }
    uVar10 = uRam302892;
    if ((flags_diag_cfg_b & 0x200) == 0) {
      iVar17 = (int)(short)uRam302836 * 0x28f;
      uVar6 = (ushort)iVar17;
      sVar19 = (short)((uint)iVar17 >> 0x10);
      bVar5 = iVar17 < 0 && sVar19 + -0x1fff < 0 != iVar17 < 0;
      bVar1 = sVar19 + -0x1fff < 0;
      if ((bVar1 == bVar5) && (sVar19 != 0x1fff && bVar1 == bVar5)) {
        uVar12 = 0xffff;
        sVar19 = 0x7fff;
      }
      else {
        bVar5 = -1 < iVar17 && sVar19 + 0x2000 < 0 != iVar17 < 0;
        bVar1 = sVar19 + 0x2000 < 0;
        if ((sVar19 == -0x2000 || bVar1 != bVar5) && (bVar1 != bVar5)) {
          uVar12 = 0;
          sVar19 = -0x8000;
        }
        else {
          uVar12 = uVar6 * 4;
          sVar19 = (sVar19 * 2 + (ushort)(uVar6 * 2 < uVar6 || uVar6 * 2 < uVar6)) * 2 +
                   (ushort)(uVar6 * 4 < uVar6 * 2 || uVar6 * 4 < uVar6 * 2);
        }
      }
      bVar1 = uRam302886 + uVar12 < uRam302886;
      bVar5 = uRam302886 + uVar12 < uVar12;
      uVar6 = (ushort)(bVar1 || bVar5);
      uRam302886 = uRam302886 + uVar12;
      uVar12 = uRam302888 + sVar19;
      bVar2 = uVar12 < uRam302888;
      bVar3 = (short)uRam302888 < 0;
      bVar4 = (short)uRam302888 < 0;
      uRam302888 = uRam302888 + sVar19 + uVar6;
      if (bVar3 == sVar19 < 0 && (short)(uVar12 + uVar6) < 0 != bVar4) {
        if (bVar2 || uVar12 == 0xffff && (bVar1 || bVar5)) {
          uRam302886 = 0;
          uRam302888 = 0x8000;
        }
        else {
          uRam302886 = 0xffff;
          uRam302888 = 0x7fff;
        }
      }
      if (uRam302888 == uRam016086 ||
          (short)(uRam302888 - uRam016086) < 0 !=
          ((short)uRam302888 < 0 != (short)uRam016086 < 0 &&
          (short)(uRam302888 - uRam016086) < 0 != (short)uRam302888 < 0)) {
        if ((short)(uRam302888 - uRam016088) < 0 !=
            ((short)uRam302888 < 0 != (short)uRam016088 < 0 &&
            (short)(uRam302888 - uRam016088) < 0 != (short)uRam302888 < 0)) {
          uRam302888 = uRam016088;
          uRam302886 = 0;
        }
      }
      else {
        uRam302888 = uRam016086;
        uRam302886 = 0;
      }
      uRam30283c = uRam302888;
      sVar19 = uRam302836 - uRam302838;
      if ((short)uRam302836 < 0 != (short)uRam302838 < 0 &&
          (short)(uRam302836 - uRam302838) < 0 != (short)uRam302836 < 0) {
        sVar19 = -0x8000;
      }
      iVar18 = (int)sVar19 * 0x28f;
      uVar6 = (ushort)iVar18;
      sVar19 = (short)((uint)iVar18 >> 0x10);
      MDC = MDC | 0x10;
      bVar5 = iVar18 < 0 && sVar19 + -0x1fff < 0 != iVar18 < 0;
      bVar1 = sVar19 + -0x1fff < 0;
      if ((bVar1 == bVar5) && (sVar19 != 0x1fff && bVar1 == bVar5)) {
        uVar12 = 0xffff;
        sVar19 = 0x7fff;
      }
      else {
        bVar5 = -1 < iVar18 && sVar19 + 0x2000 < 0 != iVar18 < 0;
        bVar1 = sVar19 + 0x2000 < 0;
        if ((sVar19 == -0x2000 || bVar1 != bVar5) && (bVar1 != bVar5)) {
          uVar12 = 0;
          sVar19 = -0x8000;
        }
        else {
          uVar12 = uVar6 * 4;
          sVar19 = (sVar19 * 2 + (ushort)(uVar6 * 2 < uVar6 || uVar6 * 2 < uVar6)) * 2 +
                   (ushort)(uVar6 * 4 < uVar6 * 2 || uVar6 * 4 < uVar6 * 2);
        }
      }
      bVar1 = uRam30288a + uVar12 < uRam30288a;
      bVar5 = uRam30288a + uVar12 < uVar12;
      uVar6 = (ushort)(bVar1 || bVar5);
      uRam30288a = uRam30288a + uVar12;
      uVar12 = uRam30288c + sVar19;
      bVar2 = uVar12 < uRam30288c;
      bVar3 = (short)uRam30288c < 0;
      bVar4 = (short)uRam30288c < 0;
      uRam30288c = uRam30288c + sVar19 + uVar6;
      if (bVar3 == sVar19 < 0 && (short)(uVar12 + uVar6) < 0 != bVar4) {
        if (bVar2 || uVar12 == 0xffff && (bVar1 || bVar5)) {
          uRam30288a = 0;
          uRam30288c = 0x8000;
        }
        else {
          uRam30288a = 0xffff;
          uRam30288c = 0x7fff;
        }
      }
      if (uRam30288c == uRam016086 ||
          (short)(uRam30288c - uRam016086) < 0 !=
          ((short)uRam30288c < 0 != (short)uRam016086 < 0 &&
          (short)(uRam30288c - uRam016086) < 0 != (short)uRam30288c < 0)) {
        if ((short)(uRam30288c - uRam016088) < 0 !=
            ((short)uRam30288c < 0 != (short)uRam016088 < 0 &&
            (short)(uRam30288c - uRam016088) < 0 != (short)uRam30288c < 0)) {
          uRam30288c = uRam016088;
          uRam30288a = 0;
        }
      }
      else {
        uRam30288c = uRam016086;
        uRam30288a = 0;
      }
      uRam30283e = uRam30288c;
    }
  }
  uRam302884 = (ushort)((uint)iVar11 >> 0x10);
  uRam30288e = (undefined2)iVar11;
  uRam302892._2_2_ = (undefined2)((uint)uVar10 >> 0x10);
  uRam302892._0_2_ = (undefined2)uVar10;
  uRam30283a = (ushort)((uint)iVar16 >> 0x10);
  uRam302882 = (ushort)iVar16;
  MDH = (undefined2)((uint)iVar18 >> 0x10);
  MDL = (ushort)iVar18;
  if ((DAT_00fd34 & 0x100) == 0) {
    if ((DAT_00fd34 & 2) == 0) {
      uRam302818 = 0x8000;
    }
    else {
      uRam302818 = uRam3027da;
    }
  }
  else if ((short)uRam30280c < 0) {
    uRam302818 = uRam30280c + 0x8000;
    if (uRam30280c <= uRam30280c + 0x8000 && 0x7fff < uRam30280c + 0x8000) {
      uRam302818 = 0;
    }
  }
  else {
    uRam302818 = uRam30280c + 0x8000;
    if (uRam30280c + 0x8000 < uRam30280c || uRam30280c + 0x8000 < 0x8000) {
      uRam302818 = 0xffff;
    }
  }
  if (uRam015f04 < uRam302818) {
    uRam302816 = uRam015f04;
    uRam00fd36 = uRam00fd36 & 0xffef | 8;
  }
  else if (uRam302818 < uRam302812) {
    uRam302816 = uRam302812;
    uRam00fd36 = uRam00fd36 & 0xfff7 | 0x10;
  }
  else {
    uRam302816 = uRam302818;
    uRam00fd36 = uRam00fd36 & 0xffe7;
  }
  if ((uRam00fd36 & 0x1000) == 0) {
    _start_enrich_factor = uRam302816;
  }
  else if ((short)uRam30280a < 0) {
    _start_enrich_factor = uRam30280a + uRam302816;
    if (uRam30280a <= uRam30280a + uRam302816 && uRam302816 <= uRam30280a + uRam302816) {
      _start_enrich_factor = 0;
    }
  }
  else {
    _start_enrich_factor = uRam30280a + uRam302816;
    if (uRam30280a + uRam302816 < uRam30280a || uRam30280a + uRam302816 < uRam302816) {
      _start_enrich_factor = 0xffff;
    }
  }
  return;
}


// ================= idle_air_governor_llr @ 07d58e =================

/* WARNING: Removing unreachable block (ram,0x07e0da) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* idle-speed governor (LLR, air/torque-reserve); arms word_FD46.9 (idle-governor.md) */

ushort idle_air_governor_llr(void)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  short sVar5;
  ushort uVar6;
  ushort uVar7;
  byte bVar8;
  byte bVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  uint uVar12;
  undefined4 uVar13;
  undefined1 uStack_10;
  byte bStack_c;
  
  uRam305172 = uRam304f70;
  uVar6 = (uRam00fd66 & 4) >> 2;
  uVar7 = (uRam00fd66 & 0x10) >> 4;
  if ((((bRam301591 & 0x10) != 0) && (uVar6 == 0)) || (((bRam301591 & 4) != 0 && (uVar7 == 0)))) {
    bRam301591 = bRam301591 | 0x20;
  }
  if (uVar6 == 1) {
    bRam301591 = bRam301591 | 0x10;
  }
  else {
    bRam301591 = bRam301591 & 0xef;
  }
  if (uVar7 == 1) {
    bRam301591 = bRam301591 | 4;
  }
  else {
    bRam301591 = bRam301591 & 0xfb;
  }
  if ((bRam301591 & 0x20) == 0) {
    uRam01958b = uRam0196fa;
    bRam301591 = bRam301591 & 0xf7;
  }
  else if (cRam30158b == '\0') {
    bRam301591 = bRam301591 | 8;
  }
  else {
    cRam30158b = cRam30158b + -1;
  }
  if ((uRam00fd3a & 0x8000) == 0) {
    if ((_flags_diag_cfg_a & 0x10) == 0) {
      if ((bRam301591 & 8) == 0) {
        bVar4 = false;
      }
      else {
        bVar4 = true;
      }
    }
    else {
      bVar4 = true;
    }
    if ((bVar4) && (bRam019701 < vfzg_class)) goto LAB_07d664;
LAB_07d672:
    bRam301591 = bRam301591 & 0xbf;
  }
  else {
LAB_07d664:
    if ((_flags_start_phase & 0x8000) == 0) goto LAB_07d672;
    bRam301591 = bRam301591 | 0x40;
  }
  if (((uRam00fd1c & 0x2000) == 0) || ((bRam301591 & 0x40) != 0)) {
    if (cRam30158a == '\0') {
      bRam301580 = bRam301580 | 1;
    }
    else {
      cRam30158a = cRam30158a + -1;
    }
  }
  else {
    cRam01958a = cRam0196ff;
    if (cRam0196ff == '\0') {
      cRam30158a = '\x01';
    }
  }
  if ((uRam02200a < _afterstart_timer) && ((_flags_idle_state & 0x200) != 0)) {
    bRam301580 = bRam301580 | 2;
  }
  else {
    bRam301580 = bRam301580 & 0xfd;
  }
  if ((((uRam303b5c & 1) == 0) && ((uRam303bea & 1) == 0)) && ((uRam303bd6 & 1) == 0)) {
    bRam301581 = bRam301581 & 0xfe;
  }
  else {
    bRam301581 = bRam301581 | 1;
  }
  uVar12 = CONCAT22(MDH,MDL);
  if (((_flags_start_phase & 0x4000) != 0) && (uVar12 = CONCAT22(MDH,MDL), (bRam301590 & 0x10) == 0)
     ) {
    uRam30158c = uRam303271;
    bRam304784 = bRam301626;
    uVar12 = CONCAT22(MDH,MDL);
    if ((bRam30574c & 1) != 0) {
      uVar6 = func_0x04272a(uRam021e2a,0x1e2c,8,0x1e38,8,uRam3055d0);
      uVar7 = MDC;
      uRam30516a = (ushort)((uint)(uVar6 & 0xff) * (uint)uRam305168 >> 8);
      uVar6 = (ushort)bRam304784 * 0x20 + 0x2586;
      sRam305178 = uVar6 + uRam30516a;
      if (uVar6 + uRam30516a < uVar6 || uVar6 + uRam30516a < uRam30516a) {
        sRam305178 = -1;
      }
      MDC = MDC | 0x10;
      uRam30517a = (ushort)((uint)bRam0196c8 * (uint)uRam30516a >> 8);
      if (sRam021ff8 == 0) {
        uRam305170 = 0;
        uVar12 = (uint)bRam0196c8 * (uint)uRam30516a;
      }
      else {
        MDL = (ushort)((uint)uRam30517a * 0xe10c);
        MDH = (undefined2)((uint)uRam30517a * 0xe10c >> 0x10);
        MDC = uVar7 | 0x10;
        uVar12 = func_0x0e40de();
        uVar6 = (ushort)((uVar12 >> 3) >> 0x10);
        uRam305170 = (ushort)(uVar12 >> 3);
        uVar12 = CONCAT22(MDH,MDL);
        if ((uVar6 != (uRam305170 != 0xffff) || uRam305170 != 0xffff) &&
            (uVar6 != 0 || uRam305170 == 0xffff)) {
          uRam305170 = 0xffff;
          uVar12 = CONCAT22(MDH,MDL);
        }
      }
    }
  }
  MDH = (undefined2)(uVar12 >> 0x10);
  MDL = (ushort)uVar12;
  if (bRam304979 < bRam304784) {
    uVar6 = (ushort)bRam304784 - (ushort)bRam304979;
    uVar7 = (ushort)bRam0196cc;
    bVar4 = uVar6 == uVar7 ||
            (short)(uVar6 - uVar7) < 0 !=
            ((short)uVar6 < 0 && (short)(uVar6 - uVar7) < 0 != (short)uVar6 < 0);
  }
  else {
    uVar6 = (ushort)bRam304979 - (ushort)bRam304784;
    uVar7 = (ushort)bRam0196cc;
    if (uVar6 == uVar7 ||
        (short)(uVar6 - uVar7) < 0 !=
        ((short)uVar6 < 0 && (short)(uVar6 - uVar7) < 0 != (short)uVar6 < 0)) {
      bVar4 = true;
    }
    else {
      bVar4 = false;
    }
  }
  if ((bVar4) && ((((bRam0196c9 & 2) == 0 || (uRam022004 < uRam3055d0)) || ((bRam30174c & 1) == 0)))
     ) {
    if ((bRam0196c9 & 4) != 0) {
      bVar8 = bRam30558c - bRam304979;
      if (bRam30558c < bRam304979) {
        bVar8 = 0;
      }
      if (bVar8 < bRam0196cd) goto LAB_07d8e8;
    }
    bRam301581 = bRam301581 | 2;
  }
  else {
LAB_07d8e8:
    bRam301581 = bRam301581 & 0xfd;
  }
  uVar6 = 0;
  if ((bRam301591 & 1) != 0) {
    uRam30516c = uRam305614;
  }
  if (((_flags_start_phase & 0x4000) == 0) || ((bRam301590 & 0x10) != 0)) {
    bRam301591 = bRam301591 & 0xfe;
  }
  else {
    bRam301591 = bRam301591 | 1;
  }
  if ((_flags_start_phase & 0x4000) == 0) {
    bRam301590 = bRam301590 & 0xef;
  }
  else {
    bRam301590 = bRam301590 | 0x10;
  }
  if ((bRam0196ca & 1) == 0) {
    uRam305176 = uRam305174 - uRam305170;
    if (uRam305174 < uRam305170) {
      uRam305176 = 0;
    }
  }
  else {
    uRam305176 = uRam305174;
  }
  if ((((((uRam305176 == 0) || (uVar6 = uRam302634 & 1, uVar6 != 0)) ||
        ((_flags_diag_cfg_a & 0x8000) == 0)) ||
       ((uVar6 = 0, (bRam301581 & 2) == 0 &&
        ((uVar6 = 0, (bRam30174c & 1) == 0 || (uVar6 = uRam305170, uRam021ea8 <= uRam305170)))))) ||
      ((bRam304979 < bRam019700 && ((uRam00fd48 & 0x20) != 0)))) ||
     ((((bRam301581 & 1) != 0 || (uRam30516c <= uRam021e3e)) || ((uRam00fd16 & 2) == 0)))) {
    bRam301580 = bRam301580 & 0xdf;
  }
  else {
    bRam301580 = bRam301580 | 0x20;
  }
  if (((bRam301580 & 0x20) == 0) || ((_flags_start_phase & 0x8000) == 0)) {
    bRam301580 = bRam301580 & 0xf7;
  }
  else {
    bRam301580 = bRam301580 | 8;
  }
  if (uRam305176 == 0) {
    bRam301580 = bRam301580 | 0x80;
  }
  else {
    bRam301580 = bRam301580 & 0x7f;
  }
  if (((_flags_start_phase & 0x8000) == 0) || (bRam00f472 <= bRam0196f7)) {
    uRam01a8fe = (ushort)bRam0196fe;
    bRam301590 = bRam301590 & 0xfd;
  }
  else if (sRam3028fe == 0) {
    bRam301590 = bRam301590 | 2;
  }
  else {
    sRam3028fe = sRam3028fe + -1;
  }
  if ((((((bRam301591 & 2) != 0) && ((_flags_idle_state & 0x200) == 0)) && ((bRam301580 & 4) == 0))
      && (((bRam301581 & 1) == 0 && ((bRam301590 & 2) == 0)))) && (_afterstart_timer <= uRam02200c))
  {
    bRam30157f = bRam30157f | 1;
  }
  if ((_flags_idle_state & 0x200) == 0) {
LAB_07db14:
    PSW = PSW & 0xffbf;
  }
  else {
    if (((bRam301590 & 2) == 0) && ((uRam302634 & 1) == 0)) {
      uVar13 = func_0x042464(uRam021eaa,0x1eab,8,0x1eb0,8,bRam304979);
      uVar6 = (ushort)((uint)uVar13 >> 0x10);
      uVar12 = CONCAT22(MDH,MDL);
      if ((uRam3028f8 < (ushort)uVar13) &&
         (((uVar12 = CONCAT22(MDH,MDL), _afterstart_timer <= uRam02200c &&
           (uVar12 = CONCAT22(MDH,MDL), (bRam301580 & 4) == 0)) &&
          (uVar12 = CONCAT22(MDH,MDL), (bRam301581 & 1) == 0)))) goto LAB_07db14;
    }
    PSW = PSW | 0x40;
  }
  MDH = (undefined2)(uVar12 >> 0x10);
  MDL = (ushort)uVar12;
  uVar7 = (PSW & 0x40) >> 6;
  _flags_idle_state = _flags_idle_state & 0xf7ff | uVar7 << 0xb;
  if ((bRam301582 != 0) && (uVar7 != 0)) {
    uRam302902 = uRam302900;
    uRam302900 = me7_fraction_blend((ushort)bRam019702 << 8,0,uRam302900);
    uVar12 = CONCAT22(MDH,MDL);
    uVar6 = uRam302902;
    if (uRam302902 == uRam302900) {
      bRam301582 = bRam301582 - 1;
      uVar12 = CONCAT22(MDH,MDL);
    }
    else {
      uRam302900._1_1_ = (byte)(uRam302900 >> 8);
      bRam301582 = uRam302900._1_1_;
    }
  }
  bVar8 = (byte)(uVar6 >> 8);
  if ((uRam3028f8 == 0xffff) || (bRam301582 <= bRam0196ce)) {
    bRam301580 = bRam301580 | 0x50;
  }
  else if ((uRam00fd0e & 0x1000) == 0) {
    bRam301580 = bRam301580 & 0xbf | 0x10;
  }
  else {
    bRam301580 = bRam301580 & 0xaf;
  }
  if ((bRam301580 & 0x80) == 0) {
    if ((_flags_idle_state & 0x800) == 0) {
      bVar8 = 0;
      uRam307e0c = uRam305172;
      uVar2 = (uVar12 & 0xffff0000) / (uint)uRam305176;
      uRam3028f8 = (ushort)uVar2;
      uVar12 = CONCAT22((short)((uVar12 & 0xffff0000) % (uint)uRam305176),uRam3028f8);
      MDC = MDC | 0x10;
      if (uRam305176 == 0 || 0xffff < uVar2) {
        uRam3028f8 = 0xffff;
      }
      uRam301587 = (undefined1)((ushort)uRam3068f8 >> 8);
      uRam30517c = uRam3028f8;
    }
  }
  else {
    uRam301587 = 0;
    uRam3028f8 = 0;
    uRam30517c = 0;
  }
  MDH = (undefined2)(uVar12 >> 0x10);
  MDL = (ushort)uVar12;
  if ((bRam301580 & 0x40) == 0) {
    if (((bRam301580 & 0x20) != 0) && ((uRam00fd0e & 0x1000) != 0)) {
      _flags_idle_state = _flags_idle_state | 0x400;
    }
  }
  else {
    _flags_idle_state = _flags_idle_state & 0xfbff;
  }
  if (((_flags_idle_state & 0x400) == 0) || ((uRam00fd0e & 0x1000) == 0)) {
    bRam30157f = bRam30157f & 0xfd;
  }
  else {
    bRam30157f = bRam30157f | 2;
  }
  if ((_flags_idle_state & 0x200) == 0) {
    bRam301591 = bRam301591 & 0xfd;
  }
  else {
    bRam301591 = bRam301591 | 2;
  }
  if ((bRam301580 & 0x10) == 0) {
    if ((bRam301580 & 8) != 0) {
      _flags_idle_state = _flags_idle_state | 0x200;
    }
  }
  else {
    _flags_idle_state = _flags_idle_state & 0xfdff;
  }
  if ((_flags_idle_state & 0x200) == 0) {
    uRam301586 = 0;
  }
  else {
    if ((uRam022010 < _afterstart_timer) &&
       (uRam3028f6 = uRam021fd0 + uRam0228f6,
       uRam021fd0 + uRam0228f6 < uRam021fd0 || uRam021fd0 + uRam0228f6 < uRam0228f6)) {
      uRam3028f6 = 0xffff;
    }
    if ((uRam00fd1c & 0x2000) == 0) {
      uVar6 = me7_lookup_1d_word((short)&DAT_011e62,8,uRam3028f8);
    }
    else {
      uVar6 = me7_lookup_1d_word(0x1e84,8,uRam3028f8);
    }
    uVar7 = uRam3028f6;
    if (uVar6 <= uRam3028f6) {
      uVar7 = uVar6;
    }
    uVar12 = (uint)bRam301582 * (uint)uVar7;
    MDC = MDC | 0x10;
    bVar8 = 0;
    uRam301586 = (undefined1)(uVar12 >> 0x10);
  }
  MDH = (undefined2)(uVar12 >> 0x10);
  MDL = (ushort)uVar12;
  if (((((bRam0196c9 & 1) == 0) || ((bRam301580 & 1) == 0)) || ((bRam301580 & 2) == 0)) &&
     ((_flags_idle_state & 0x400) != 0)) {
    _flags_idle_state = _flags_idle_state | 0x3000;
    uRam3028fa = 0;
  }
  else if ((uRam3028fa < uRam02200e) && ((_flags_idle_state & 0x1000) != 0)) {
    uRam3028fa = uRam3028fa + 1;
    _flags_idle_state = _flags_idle_state & 0xdfff;
    sVar5 = FUN_042c1c(uRam3028fa,0xffff,uRam02200e);
    uVar12 = CONCAT22(MDH,MDL);
    bVar8 = 0;
    bRam301583 = (byte)((ushort)(-1 - sVar5) >> 8);
  }
  else {
    _flags_idle_state = _flags_idle_state & 0xcfff;
  }
  MDH = (undefined2)(uVar12 >> 0x10);
  MDL = (ushort)uVar12;
  if ((bRam0196c9 & 0x20) == 0) {
    bStack_c = bRam30471c;
  }
  else {
    bStack_c = bRam30471b;
  }
  bVar9 = bRam0196fc + bRam0196cb;
  if ((byte)(bRam0196fc + bRam0196cb) < bRam0196fc || (byte)(bRam0196fc + bRam0196cb) < bRam0196cb)
  {
    bVar9 = 0xff;
  }
  uVar6 = CONCAT11(bVar8,bVar9 - 10);
  if (bVar9 < 10) {
    uVar6 = (ushort)bVar8 << 8;
  }
  uVar10 = (undefined1)(uVar6 >> 8);
  if ((byte)uVar6 < bStack_c) {
    uVar6 = CONCAT11(uVar10,1);
    bRam301590 = bRam301590 | 1;
  }
  else if (bStack_c < bRam0196fc) {
    uVar6 = CONCAT11(uVar10,0xfe);
    bRam301590 = bRam301590 & 0xfe;
  }
  if (bRam0196fd <= bStack_c) {
    uVar6 = CONCAT11((char)(uVar6 >> 8),8);
    bRam301590 = bRam301590 | 8;
  }
  if ((((_flags_idle_state & 0x2000) == 0) && ((bRam301590 & 8) != 0)) && ((bRam301590 & 1) == 0)) {
    PSW = PSW | 0x40;
  }
  else {
    PSW = PSW & 0xffbf;
  }
  uVar1 = (PSW & 0x40) >> 6;
  uVar7 = _flags_idle_state & 0xbfff | uVar1 << 0xe;
  if ((bRam0196c9 & 8) == 0) {
    uRam30516e = uRam305616 >> 1;
  }
  else {
    uRam30516e = uRam305614;
  }
  if (((bRam301590 & 4) == 0) && ((bRam301591 & 0x40) != 0)) {
    if (sRam3028fc == 0) {
      bRam301590 = bRam301590 | 4;
    }
    else {
      sRam3028fc = sRam3028fc + -1;
    }
  }
  else {
    uRam0228fc = uRam022006;
  }
  if ((bRam0196c9 & 0x10) != 0) {
    bRam301590 = bRam301590 | 0x80;
  }
  if ((((_flags_idle_state & 0x1000) == 0) && (uVar1 == 0)) || ((bRam301590 & 0x80) != 0)) {
    uVar10 = 0;
    _flags_idle_state = uVar7;
    uVar11 = 0;
  }
  else {
    _flags_idle_state = uVar7;
    uVar6 = me7_lookup_2d_byte(0x16d8,6,uRam301587,uRam304db0);
    MDL = (uVar6 & 0xff) * (ushort)bRam301583;
    MDH = 0;
    MDC = MDC | 0x10;
    uVar7 = MDL >> 7;
    if ((bRam301590 & 4) == 0) {
      uVar6 = func_0x0425e8(uRam021eea,0x1eec,8,uRam021eeb,0x1ef4,8,0x1efc,8,rpmclass_oppoint,
                            uRam30516e);
      iVar3 = (uint)(uVar6 & 0xff) * (uint)uVar7;
      MDL = (ushort)iVar3;
      MDH = (undefined2)((uint)iVar3 >> 0x10);
      MDC = MDC | 0x10;
      uVar10 = (undefined1)((uint)iVar3 >> 8);
      if (0xff < MDL >> 8) {
        uVar10 = 0xff;
      }
      uVar13 = func_0x0425e8(uRam021eb8,0x1eba,8,uRam021eb9,0x1ec2,8,0x1eca,8,rpmclass_oppoint,
                             uRam30516e);
      uVar6 = (ushort)((uint)uVar13 >> 0x10);
      uVar12 = (uint)((ushort)uVar13 & 0xff) * (uint)uVar7;
      MDC = MDC | 0x10;
      uVar11 = (undefined1)(uVar12 >> 8);
      if (0xff < (ushort)uVar12 >> 8) {
        uVar11 = 0xff;
      }
    }
    else {
      uVar13 = func_0x0425e8(uRam021eb8,0x1eba,8,uRam021eb9,0x1ec2,8,0x1eca,8,rpmclass_oppoint,
                             uRam30516e);
      uVar6 = (ushort)((uint)uVar13 >> 0x10);
      uVar12 = (uint)((ushort)uVar13 & 0xff) * (uint)uVar7;
      MDC = MDC | 0x10;
      uVar10 = (undefined1)(uVar12 >> 8);
      uVar11 = uVar10;
      if (0xff < (ushort)uVar12 >> 8) {
        uVar10 = 0xff;
        uVar11 = uVar10;
      }
    }
  }
  MDH = (undefined2)(uVar12 >> 0x10);
  MDL = (ushort)uVar12;
  if ((bRam30127a & 0x20) == 0) {
    uRam301588 = uVar11;
    if ((uRam302634 & 0x4000) != 0) {
      uRam019589 = uRam0196f9;
      uVar10 = uRam301589;
    }
  }
  else {
    uRam019589 = uRam0196f8;
    uVar6 = CONCAT11((char)(uVar6 >> 8),uRam0196f8);
    uRam019588 = uRam0196f8;
    uVar10 = uRam301589;
  }
  uRam301589 = uVar10;
  if ((_flags_idle_state & 0x200) == 0) {
    uRam022904 = uRam022008;
    bRam301580 = bRam301580 & 0xfb;
  }
  else if (sRam302904 == 0) {
    uVar6 = bRam301580 & 1;
    if ((bRam301580 & 1) == 0) {
      bRam301580 = bRam301580 | 4;
    }
    else {
      bRam301580 = bRam301580 & 0xfb;
    }
  }
  else {
    sRam302904 = sRam302904 + -1;
  }
  if ((bRam0196c9 & 0x40) == 0) {
    if ((bRam301278 & 2) == 0) {
      bVar4 = false;
    }
    else {
      bVar4 = true;
    }
  }
  else {
    bVar4 = true;
  }
  if ((((bVar4) && ((uRam00fd0e & 0x1000) != 0)) &&
      (((_flags_idle_state & 0x400) != 0 && (cRam30158d != '\0')))) &&
     (((((bRam301580 & 1) == 0 && ((_flags_idle_state & 0x800) == 0)) &&
       (((flags_diag_cfg_b & 0x1000) == 0 || (((bRam301277 & 0x80) == 0 || ((bRam301277 & 4) == 0)))
        ))) || ((bRam0196c9 & 0x80) != 0)))) {
    PSW = PSW | 0x40;
  }
  else {
    PSW = PSW & 0xffbf;
  }
  uVar7 = _flags_idle_state & 0x7fff | ((PSW & 0x40) >> 6) << 0xf;
  if ((_flags_idle_state & 0x200) == 0) {
    uRam301584 = 0;
    _flags_idle_state = uVar7;
  }
  else {
    _flags_idle_state = uVar7;
    uVar6 = me7_lookup_1d_byte(0x16cf,6,rpmclass_oppoint);
    uVar6 = (ushort)bRam301582 * (uVar6 & 0xff);
    MDH = 0;
    MDC = MDC | 0x10;
    MDL = uVar6;
    uVar7 = me7_lookup_1d_word(0x1e40,8,uRam3028f8,uVar6);
    uVar12 = (uint)uVar7 * (uint)uVar6;
    MDC = MDC | 0x10;
    uVar6 = 0;
    uRam301584 = (undefined1)(uVar12 >> 0x18);
  }
  MDH = (undefined2)(uVar12 >> 0x10);
  MDL = (ushort)uVar12;
  if ((_flags_idle_state & 0x200) == 0) {
    uRam304782 = 0;
    uRam304783 = 0;
  }
  else {
    uVar6 = me7_lookup_1d_byte(0x1ffa,8,uRam304db0);
    uVar6 = (uVar6 & 0xff) * (ushort)bRam301582;
    MDH = 0;
    MDC = MDC | 0x10;
    MDL = uVar6;
    uVar7 = func_0x042638(uRam021f1c,0x1f1e,8,uRam021f1d,0x1f2e,8,0x1f36,8,uRam3028f8,bRam304979);
    iVar3 = (uint)(uVar7 & 0xff) * (uint)uVar6;
    MDL = (ushort)iVar3;
    MDH = (undefined2)((uint)iVar3 >> 0x10);
    MDC = MDC | 0x10;
    if ((ushort)(iVar3 >> 0xf) < 0x100) {
      uStack_10 = (undefined1)(iVar3 >> 0xf);
      uRam304782 = uStack_10;
    }
    else {
      uRam304782 = 0xff;
    }
    uVar7 = func_0x042638(uRam021f76,0x1f78,8,uRam021f77,0x1f88,8,0x1f90,8,uRam3028f8,bRam304979,0);
    uVar12 = (uint)(uVar7 & 0xff) * (uint)uVar6;
    MDC = MDC | 0x10;
    uVar7 = (ushort)((int)uVar12 >> 0xf);
    uVar6 = -(ushort)(uVar7 < 0xff);
    if (uVar6 == 0 && uVar7 == 0xff || uVar7 < 0xff) {
      uStack_10 = (undefined1)((int)uVar12 >> 0xf);
      uRam304783 = uStack_10;
    }
    else {
      uRam304783 = 0xff;
    }
  }
  MDH = (undefined2)(uVar12 >> 0x10);
  MDL = (ushort)uVar12;
  if ((_flags_start_phase & 0x8000) == 0) {
    bRam301590 = bRam301590 & 0xbf;
  }
  else {
    bRam301590 = bRam301590 | 0x40;
  }
  return uVar6;
}


// ================= idle_reserve_shape @ 07e36c =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* idle reserve shaping vs rpm -> word_305182 (idle-governor.md) */

void idle_reserve_shape(void)

{
  int iVar1;
  undefined2 uVar3;
  ushort uVar4;
  undefined4 uVar5;
  ushort uVar2;
  
  if ((bRam019703 & 1) == 0) {
    uRam305188 = uRam30243c;
  }
  else {
    uVar4 = uRam30243c >> 1;
    if ((short)uRam3024ea < 0) {
      uVar2 = -uRam3024ea;
      uRam305188 = uVar2 + uVar4;
      if (uVar2 + uVar4 < uVar2 || uVar2 + uVar4 < uVar4) {
        uRam305188 = 0xffff;
      }
    }
    else {
      uRam305188 = uVar4 - uRam3024ea;
      if (uVar4 < uRam3024ea) {
        uRam305188 = 0;
      }
    }
    if (uRam305188 < 0x7fff) {
      uRam305188 = uRam305188 << 1;
    }
    else {
      uRam305188 = 0xffff;
    }
  }
  if ((bRam30127a & 0x20) == 0) {
    if ((uRam302634 & 0x4000) == 0) {
      uRam30517e = 0;
    }
    else {
      uRam30517e = me7_lookup_2d_word_bilinear(0x208c,8,nmot_w,uRam305188);
    }
  }
  else {
    uRam30517e = me7_lookup_2d_word_bilinear(0x2058,8,uRam305188,uRam307410);
  }
  if (((uRam00fd1c & 0x2000) == 0) || ((bRam019703 & 4) == 0)) {
    uVar3 = me7_lookup_2d_word_bilinear(0x20c0,8,nmot_w,uRam305188);
    uVar5 = me7_pt1_integrator((ushort)bRam019715 << 8,uVar3,uRam300706._2_2_,(undefined2)uRam300706
                              );
  }
  else {
    uVar3 = me7_lookup_2d_word_bilinear(0x2164,8,nmot_w,uRam305188);
    uVar5 = me7_pt1_integrator((ushort)bRam019715 << 8,uVar3,uRam300706._2_2_,(undefined2)uRam300706
                              );
  }
  uRam300706._2_2_ = (ushort)((uint)uVar5 >> 0x10);
  iVar1 = CONCAT22(MDH,MDL);
  uRam305180 = uRam300706._2_2_;
  if ((_flags_idle_state & 0x200) == 0) {
    uVar4 = 0;
  }
  else {
    iVar1 = (uint)uRam30518a *
            (uint)((ushort)((uint)bRam301586 * (uint)uRam300706._2_2_) >> 8 |
                  (short)((uint)bRam301586 * (uint)uRam300706._2_2_ >> 0x10) << 8);
    uVar4 = (ushort)iVar1;
    uVar2 = (ushort)((uint)iVar1 >> 0x10);
    MDC = MDC | 0x10;
    if (uVar2 + 0xc001 == (ushort)(uVar4 != 0xffff) && uVar4 == 0xffff ||
        (uVar2 < 0x3fff || uVar2 == 0x3fff && uVar4 != 0xffff)) {
      uVar4 = uVar4 >> 0xe | uVar2 << 2;
    }
    else {
      uVar4 = 0xffff;
    }
  }
  MDH = (undefined2)((uint)iVar1 >> 0x10);
  MDL = (undefined2)iVar1;
  if ((_flags_idle_state & 0x4000) == 0) {
    uRam305184 = 0;
  }
  else {
    uRam300706 = uVar5;
    uRam305184 = me7_lookup_2d_word_bilinear(0x2024,8,nmot_w,uRam305188);
    iVar1 = CONCAT22(MDH,MDL);
    uVar5 = uRam300706;
  }
  uRam300706._2_2_ = (ushort)((uint)uVar5 >> 0x10);
  uRam300706._0_2_ = (undefined2)uVar5;
  MDH = (undefined2)((uint)iVar1 >> 0x10);
  MDL = (undefined2)iVar1;
  _idle_torque_reserve = uVar4;
  if (uVar4 <= uRam305184) {
    _idle_torque_reserve = uRam305184;
  }
  uRam304785 = (char)(_idle_torque_reserve >> 8);
  return;
}


// ================= catheat_coordinator @ 052d16 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* catalyst-heating / warm-up coordinator (FWM/KAT) -> mode byte_30133D (warmup-idle-thermal.md 1)
    */

void catheat_coordinator(void)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  ushort uVar4;
  short sVar5;
  char cVar6;
  
  iVar1 = CONCAT22(MDH,MDL);
  if ((flags_diag_cfg_b & 0x200) != 0) {
    catheat_mode = 0;
    goto LAB_053604;
  }
  uRam3024c4 = func_0x0418da(0x537,6,(short)catheat_mode,uRam3024c4);
  if ((uRam00fd3a & 0x8000) == 0) {
    cVar6 = bRam019655 - bRam018502;
    if (bRam019655 < bRam018502) {
      cVar6 = '\0';
    }
  }
  else {
    cVar6 = bRam019655 - bRam0184c1;
    if (bRam019655 < bRam0184c1) {
      cVar6 = '\0';
    }
  }
  if ((cVar6 != '\0') && ((uRam00fd1c & 0x2000) == 0)) {
    bVar3 = bRam018540 - 8;
    if (bRam018540 < 8) {
      bVar3 = 0;
    }
    if (bVar3 < rpmclass_oppoint) {
      if (bRam018540 < rpmclass_oppoint) {
        bRam30133e = bRam30133e | 0x40;
      }
    }
    else {
      bRam30133e = bRam30133e & 0xbf;
    }
  }
  bRam301341 = bRam301341 & 0xfb;
  if ((uRam303bea & 1) == 0) {
    bVar3 = bRam01853f - bRam01842c;
    if (bRam01853f < bRam01842c) {
      bVar3 = 0;
    }
    if (bRam304979 <= bVar3) {
      bRam301341 = bRam301341 | 4;
    }
  }
  bRam301341 = bRam301341 & 0xfd;
  if ((uRam303bd6 & 1) == 0) {
    bVar3 = bRam01853e - bRam01842b;
    if (bRam01853e < bRam01842b) {
      bVar3 = 0;
    }
    if (bRam301626 <= bVar3) {
      bRam301341 = bRam301341 | 2;
    }
  }
  if ((((uRam3035be < uRam01efbe) || ((bRam301341 & 4) != 0)) || ((bRam301341 & 2) != 0)) &&
     ((uRam00fd1c & 0x2000) == 0)) {
    bRam30133e = bRam30133e & 0xfb;
  }
  else if (((((_flags_start_phase & 0x4000) == 0) && (uRam01efc0 < uRam3035be)) &&
           (((uRam303bd6 & 1) != 0 || (bRam01853e < bRam301626)))) &&
          (((uRam303bea & 1) != 0 || (bRam01853f < rpmclass_oppoint)))) {
    bRam30133e = bRam30133e | 4;
  }
  if ((((bRam301276 & 8) == 0) && ((uRam00fd1c & 0x2000) == 0)) && (bRam018546 < vfzg_class)) {
    bRam30133e = bRam30133e & 0x7f;
  }
  else if ((bRam301276 & 8) != 0) {
    bRam30133e = bRam30133e | 0x80;
  }
  bVar3 = bRam301350;
  if ((uRam00fd3a & 0x8000) == 0) {
    bVar3 = bRam301352;
  }
  if (bVar3 < bRam301351) {
    bVar3 = bRam301351;
  }
  cVar6 = bRam301655 - bVar3;
  if (bRam301655 < bVar3) {
    cVar6 = '\0';
  }
  if (((cVar6 != '\0') && ((uRam00fd1c & 0x2000) == 0)) || (bRam301655 == 0)) {
    if ((bRam30133e & 0x20) == 0) {
      bRam30133e = bRam30133e & 0xef;
    }
    else {
      bRam30133e = bRam30133e | 0x10;
    }
  }
  if (((uRam00fd70 & 0x200) == 0) && ((uRam00fd70 & 0x20) == 0)) {
    bRam30133e = bRam30133e & 0xfd;
  }
  else {
    bRam30133e = bRam30133e | 2;
  }
  bVar3 = bRam301353;
  if (((bRam301275 & 1) == 0) && (bVar3 = bRam018500, (bRam30133e & 4) == 0)) {
    bVar3 = 0;
  }
  if ((uRam00fd3a & 0x8000) == 0) {
    if ((bRam30133e & 0x10) == 0) {
      bRam301344 = bRam301351;
      if (bRam301351 < bRam301354) {
        bRam301344 = bRam301354;
      }
    }
    else {
      bRam301344 = bRam301352;
      if (bRam301352 < bRam301354) {
        bRam301344 = bRam301354;
      }
    }
    bVar2 = bRam301589;
    if (bRam301589 <= bVar3) {
      bVar2 = bVar3;
    }
    bVar3 = bRam30405a;
    if (bRam30405a <= bVar2) {
      bVar3 = bVar2;
    }
    bVar2 = bVar3;
    if (((bRam30133e & 2) != 0) && (bVar2 = bRam018509, bRam018509 <= bVar3)) {
      bVar2 = bVar3;
    }
    bVar3 = bVar2;
    if (((uRam00fd38 & 0x400) != 0) && (bVar3 = bRam304058, bRam304058 <= bVar2)) {
      bVar3 = bVar2;
    }
    bVar2 = bRam0184fe;
    if (bRam0184fe <= bVar3) {
      bVar2 = bVar3;
    }
    if (bRam018547 < vfzg_class) {
      bRam301341 = bRam301341 | 0x10;
    }
    else if (vfzg_class < bRam018548) {
      bRam301341 = bRam301341 & 0xef;
    }
    bVar3 = bVar2;
    if ((((uRam00fd04 & 0x10) != 0) && ((bRam301341 & 0x10) != 0)) &&
       (bVar3 = bRam0184ff, bRam0184ff <= bVar2)) {
      bVar3 = bVar2;
    }
    bVar2 = bVar3;
    if (((bRam30133e & 0x40) != 0) && (bVar2 = bRam018502, bRam018502 <= bVar3)) {
      bVar2 = bVar3;
    }
    bVar3 = bVar2;
    if (((bRam30133e & 0x80) != 0) && (bVar3 = bRam018503, bRam018503 <= bVar2)) {
      bVar3 = bVar2;
    }
    bVar2 = bVar3;
    if (((uRam00fd5c & 2) != 0) && (bVar2 = bRam018508, bRam018508 <= bVar3)) {
      bVar2 = bVar3;
    }
    bVar3 = bVar2;
    if (((uRam00fd38 & 8) != 0) && (bVar3 = bRam018501, bRam018501 <= bVar2)) {
      bVar3 = bVar2;
    }
    bVar2 = bVar3;
    if ((((uRam00fd08 & 2) != 0) && ((bRam018427 & 0x80) == 0)) &&
       (bVar2 = bRam018507, bRam018507 <= bVar3)) {
      bVar2 = bVar3;
    }
    bRam301346 = bRam304011;
    if (bRam304011 <= bVar2) {
      bRam301346 = bVar2;
    }
    if (bRam301346 < bRam304059) {
      bRam301346 = bRam304059;
    }
    bRam30134c = bRam301344;
    if (bRam301344 < bRam301346) {
      bRam30134c = bRam301346;
    }
  }
  else {
    if ((bRam30133e & 0x10) == 0) {
      bRam301343 = bRam301351;
    }
    else {
      bRam301343 = bRam301350;
    }
    bVar2 = bRam301588;
    if (bRam301588 <= bVar3) {
      bVar2 = bVar3;
    }
    bVar3 = bRam30405a;
    if (bRam30405a <= bVar2) {
      bVar3 = bVar2;
    }
    bVar2 = bVar3;
    if (((bRam30133e & 2) != 0) && (bVar2 = bRam018509, bRam018509 <= bVar3)) {
      bVar2 = bVar3;
    }
    bVar3 = bVar2;
    if (((uRam00fd38 & 0x400) != 0) && (bVar3 = bRam304057, bRam304057 <= bVar2)) {
      bVar3 = bVar2;
    }
    bVar2 = bRam0184c3;
    if (bRam0184c3 <= bVar3) {
      bVar2 = bVar3;
    }
    if (bRam018544 < vfzg_class) {
      bRam301341 = bRam301341 | 8;
    }
    else if (vfzg_class < bRam018545) {
      bRam301341 = bRam301341 & 0xf7;
    }
    bVar3 = bVar2;
    if ((((uRam00fd04 & 0x10) != 0) && ((bRam301341 & 8) != 0)) &&
       (bVar3 = bRam0184bf, bRam0184bf <= bVar2)) {
      bVar3 = bVar2;
    }
    bVar2 = bVar3;
    if (((bRam301366 & 1) != 0) && (bVar2 = bRam0184c6, bRam0184c6 <= bVar3)) {
      bVar2 = bVar3;
    }
    bVar3 = bVar2;
    if (((bRam30133e & 0x40) != 0) && (bVar3 = bRam0184c1, bRam0184c1 <= bVar2)) {
      bVar3 = bVar2;
    }
    bVar2 = bVar3;
    if (((bRam30133e & 0x80) != 0) && (bVar2 = bRam0184c5, bRam0184c5 <= bVar3)) {
      bVar2 = bVar3;
    }
    bVar3 = bVar2;
    if (((uRam00fd5c & 2) != 0) && (bVar3 = bRam0184c4, bRam0184c4 <= bVar2)) {
      bVar3 = bVar2;
    }
    bVar2 = bVar3;
    if (((uRam00fd38 & 8) != 0) && (bVar2 = bRam0184c0, bRam0184c0 <= bVar3)) {
      bVar2 = bVar3;
    }
    bRam301345 = bVar2;
    if ((((uRam00fd08 & 2) != 0) && ((bRam018427 & 0x80) == 0)) &&
       (bRam301345 = bRam0184c2, bRam0184c2 <= bVar2)) {
      bRam301345 = bVar2;
    }
    if (bRam301345 < bRam304059) {
      bRam301345 = bRam304059;
    }
    bRam30134c = bRam301343;
    if (bRam301343 < bRam301345) {
      bRam30134c = bRam301345;
    }
  }
  if ((((((((uRam00fd24 & 0x4000) == 0) || ((uRam00fd08 & 2) != 0)) ||
         (((bRam30133e & 2) != 0 || (((_DAT_302632 & 0x40) != 0 || ((bRam301366 & 1) != 0)))))) ||
        (bRam30134c < bRam30134b)) ||
       (((bRam018427 & 1) != 0 ||
        ((((bRam018427 & 4) != 0 && ((uRam00fd3a & 0x8000) == 0)) && ((bRam301340 & 1) != 0)))))) ||
      ((((bRam018427 & 2) != 0 && ((uRam00fd1c & 0x2000) == 0)) && (bRam30134c >> 2 < nmot_rpmclass)
       ))) || (((bRam018427 & 8) != 0 && (bRam0184b7 < bRam30495d)))) {
    bRam30134b = bRam30134c;
  }
  if ((((((_flags_start_phase & 0x8000) == 0) ||
        ((((bRam018428 & 1) != 0 && ((uRam00fd38 & 0x400) == 0)) && ((bRam301340 & 4) != 0)))) ||
       ((((bRam018428 & 2) != 0 && ((uRam00fd38 & 8) == 0)) && ((bRam301340 & 2) != 0)))) ||
      ((((bRam018428 & 4) != 0 && ((uRam00fd3a & 0x8000) != 0)) && ((bRam301340 & 1) == 0)))) ||
     ((((bRam018428 & 8) != 0 && (bRam30495d <= bRam0184b7)) && ((bRam301340 & 8) != 0)))) {
    sRam3024ca = (ushort)bRam30134b << 8;
  }
  else {
    sRam3024ca = me7_fraction_blend((ushort)bRam018549 << 8,bRam30134b,sRam3024ca);
  }
  bVar3 = sRam3024ca._1_1_;
  bRam30134e = sRam3024ca._1_1_;
  if ((uRam00fd38 & 0x400) == 0) {
    bRam301340 = bRam301340 & 0xfb;
  }
  else {
    bRam301340 = bRam301340 | 4;
  }
  if ((uRam00fd38 & 8) == 0) {
    bRam301340 = bRam301340 & 0xfd;
  }
  else {
    bRam301340 = bRam301340 | 2;
  }
  if ((uRam00fd3a & 0x8000) == 0) {
    bRam301340 = bRam301340 & 0xfe;
  }
  else {
    bRam301340 = bRam301340 | 1;
  }
  if (bRam0184b7 < bRam30495d) {
    bRam301340 = bRam301340 | 8;
  }
  else {
    bRam301340 = bRam301340 & 0xf7;
  }
  bVar2 = me7_lookup_1d_byte(0x4aa,6,vfzg_class);
  if (bVar3 < bVar2) {
    bVar3 = me7_lookup_1d_byte(0x4aa,6,vfzg_class);
  }
  bRam30134a = bVar3;
  if ((bRam018427 & 0x80) != 0) {
    uVar4 = (ushort)bRam304012 * 4;
    if (0xff < uVar4) {
      uVar4 = 0xff;
    }
    bRam30134a = (byte)uVar4;
    if ((byte)uVar4 <= bVar3) {
      bRam30134a = bVar3;
    }
  }
  MDL = (ushort)bRam019655 * (ushort)bRam01842d;
  MDH = 0;
  MDC = MDC | 0x10;
  bVar3 = (byte)((ushort)MDL >> 8);
  bRam301347 = bVar3 - bRam0184b5;
  if (bVar3 < bRam0184b5) {
    bRam301347 = 0;
  }
  if ((uRam00fd26 & 0x20) == 0) {
    bVar3 = bRam30134a + bRam01842a;
    if ((byte)(bRam30134a + bRam01842a) < bRam30134a || (byte)(bRam30134a + bRam01842a) < bRam01842a
       ) {
      bVar3 = 0xff;
    }
    if ((bVar3 < bRam301347) &&
       (bRam301347 = bRam30134a + bRam01842a,
       (byte)(bRam30134a + bRam01842a) < bRam30134a || (byte)(bRam30134a + bRam01842a) < bRam01842a)
       ) {
      bRam301347 = 0xff;
    }
  }
  else {
    bVar3 = bRam30134a + bRam018429;
    if ((byte)(bRam30134a + bRam018429) < bRam30134a || (byte)(bRam30134a + bRam018429) < bRam018429
       ) {
      bVar3 = 0xff;
    }
    if ((bVar3 < bRam301347) &&
       (bRam301347 = bRam30134a + bRam018429,
       (byte)(bRam30134a + bRam018429) < bRam30134a || (byte)(bRam30134a + bRam018429) < bRam018429)
       ) {
      bRam301347 = 0xff;
    }
  }
  bRam30134d = bRam30134a;
  if ((uRam00fd24 & 0x4000) == 0) {
    if ((_flags_idle_state & 0x1000) == 0) {
      uVar4 = me7_lookup_1d_byte(0x43b,6,rpmclass_oppoint);
      uVar4 = (uVar4 & 0xff) * (ushort)bRam30134d;
    }
    else {
      uVar4 = me7_lookup_1d_byte(0x42e,6,rpmclass_oppoint);
      uVar4 = (uVar4 & 0xff) * (ushort)bRam30134d;
    }
    MDC = MDC | 0x10;
    if (uVar4 >> 7 < 0xff) {
      bRam301349 = (byte)(uVar4 >> 7);
    }
    else {
      bRam301349 = 0xff;
    }
    bVar3 = bRam01850a;
    if (bRam019349 < bRam01850a) {
      bVar3 = bRam301349;
    }
LAB_053584:
    uRam3024c8._1_1_ = bVar3;
    uRam3024c8 = (ushort)uRam3024c8._1_1_ << 8;
  }
  else {
    bVar2 = bRam301347;
    if (bRam301347 < bRam30134a) {
      bVar2 = bRam30134a;
    }
    bVar3 = bRam01850a;
    if (bVar2 < bRam01850a) {
      bVar3 = bVar2;
    }
    if (((bRam30134a < bRam301347) && (bRam301348 < bRam301347)) &&
       ((char)(cRam0184c7 - cRam019658) < '\0' !=
        (cRam0184c7 < '\0' != cRam019658 < '\0' &&
        (char)(cRam0184c7 - cRam019658) < '\0' != cRam0184c7 < '\0'))) goto LAB_053584;
    sVar5 = func_0x04210c(0x486,6,0x537,6,uRam3019e6,uRam3024c4);
    uRam3024c8 = me7_fraction_blend(sVar5 << 8,bVar3,uRam3024c8);
  }
  iVar1 = (uint)uRam3024c8 * 0x2800;
  uRam3024c6 = (undefined2)((uint)iVar1 >> 0x10);
  MDC = MDC | 0x10;
  bRam301348 = uRam3024c8._1_1_;
  sVar5 = (ushort)bRam30134d - (ushort)bRam301655;
  if (sVar5 == 0x7f || sVar5 + -0x7f < 0 != (sVar5 < 0 && sVar5 + -0x7f < 0 != sVar5 < 0)) {
    if (sVar5 + 0x80 < 0 == (-1 < sVar5 && sVar5 + 0x80 < 0 != sVar5 < 0)) {
      catheat_mode = (char)sVar5;
    }
    else {
      catheat_mode = 0x80;
    }
  }
  else {
    catheat_mode = 0x7f;
  }
LAB_053604:
  MDH = (undefined2)((uint)iVar1 >> 0x10);
  MDL = (short)iVar1;
  return;
}


// ================= thermal_estimator @ 064c80 =================

/* WARNING: Removing unreachable block (ram,0x065c12) */
/* WARNING: Removing unreachable block (ram,0x065a12) */
/* WARNING: Removing unreachable block (ram,0x0659b2) */
/* WARNING: Removing unreachable block (ram,0x065b14) */
/* WARNING: Removing unreachable block (ram,0x065caa) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* multi-channel estimator: 6 PT1 over rpm x load maps; thermal role inferred
   (warmup-idle-thermal.md 2) */

void thermal_estimator(void)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  char cVar6;
  char cVar7;
  byte bVar8;
  byte bVar9;
  short sVar10;
  ushort uVar11;
  ushort uVar12;
  ushort uVar13;
  ushort uVar14;
  undefined2 uVar15;
  ushort uVar16;
  short sVar17;
  short sVar18;
  undefined4 uVar19;
  
  if ((_flags_start_phase & 0x8000) == 0) {
    uRam30267c = uRam30267c & 0xfff7;
  }
  else {
    uRam30267c = uRam30267c | 8;
  }
  bRam304718 = me7_lookup_2d_byte(0x980,6,nmot_rpmclass,rl_byte);
  uRam304f78 = me7_lookup_2d_word_bilinear(0x3c6c,7,nmot_w,_rl_w);
  uVar16 = (ushort)bRam30545c;
  MDL = uRam30267e / uVar16;
  MDH = uRam30267e % uVar16;
  MDC = MDC | 0x10;
  if (uVar16 == 0) {
    uRam304712 = 0xff;
  }
  else {
    uRam304712 = (undefined1)MDL;
  }
  uRam30145c = 1;
  uRam30267e = (ushort)bRam30130d;
  if ((_flags_start_phase & 0x4000) == 0) {
    if ((uRam30267c & 8) != 0) {
      bVar1 = uRam304f8c + _rl_scaled < uRam304f8c;
      uVar16 = uRam304f8c + _rl_scaled;
      uRam304f8c = uRam304f8c + _rl_scaled;
      uRam304f8e = uRam304f8e + (bVar1 || uVar16 < _rl_scaled);
      if ((uRam304f8e - 0x3f != (ushort)(uRam304f8c != 0xffff) || uRam304f8c != 0xffff) &&
          (0x3e < uRam304f8e && (uRam304f8e != 0x3f || uRam304f8c == 0xffff))) {
        uRam304f8c = 0xffff;
        uRam304f8e = 0x3f;
      }
      uRam304f70 = uRam304f8c >> 6 | uRam304f8e << 10;
      bRam304715 = (byte)(uRam304f70 >> 8);
    }
  }
  else {
    uRam304f8c = 0;
    uRam304f8e = 0;
    bRam304715 = 0;
  }
  if (((flags_diag_cfg_b & 0x2000) == 0) || ((uRam303bf6 & 1) != 0)) {
    if (((uRam303bd6 & 1) == 0) && (bRam30a008 <= bRam309626)) {
      if ((bRam0189fd < vfzg_class) &&
         (((bRam0189ea < nmot_rpmclass && (bRam018929 < bRam304715)) &&
          (bRam30a008 = bRam019626 - bRam018919, bRam019626 < bRam018919)))) {
        bRam30a008 = 0;
      }
    }
    else {
      bVar1 = bRam30a008 <= bRam309626;
      bRam30a008 = bRam301626;
      if (bVar1) {
        bRam30a008 = bRam0189fa;
      }
    }
    bRam30471a = bRam30a008;
  }
  else {
    bRam30471a = bRam304d30;
  }
  if ((flags_torque_revlimit & 0x80) == 0) {
    uVar16 = (ushort)bRam304718;
    cVar6 = func_0x042420(uRam01fc1a,0x3c1b,7,0x3c1e,7,bRam30471a);
    sVar10 = uVar16 - (short)cVar6;
    if (((_flags_idle_state & 0x200) != 0) || ((_flags_idle_state & 0x8000) != 0)) {
      sVar10 = sVar10 + (ushort)bRam0189ed;
    }
    if ((_flags_idle_state & 0x4000) != 0) {
      sVar10 = sVar10 + (ushort)bRam0189ee;
    }
    cVar6 = func_0x042180(0x95c,6,0x26eb,4,uRam301984,uRam301970);
    cVar7 = func_0x042180(0x938,6,0xf2c,5,uRam301984,uRam30197c);
    uVar16 = (sVar10 + cVar6) - (short)cVar7;
  }
  else {
    uVar16 = (ushort)bRam0189ef;
  }
  sVar10 = me7_lookup_1d_word_signed(0x3dbc,7,rpmclass_oppoint);
  uVar14 = uRam304f78;
  sVar10 = uVar16 + (sVar10 >> 8);
  if (sVar10 + -10 < 0 == (sVar10 < 0 && sVar10 + -10 < 0 != sVar10 < 0)) {
    if (sVar10 == 0xff || sVar10 + -0xff < 0 != (sVar10 < 0 && sVar10 + -0xff < 0 != sVar10 < 0)) {
      bRam304719 = (byte)sVar10;
    }
    else {
      bRam304719 = 0xff;
    }
  }
  else {
    bRam304719 = 10;
  }
  if ((flags_torque_revlimit & 0x80) == 0) {
    uVar11 = me7_lookup_1d_word_signed(0x3c00,7,bRam301626);
    uVar16 = uVar14 + uVar11;
    uVar12 = func_0x042290(0x3d10,7,0x26eb,4,uRam301984,uRam301970);
    uVar13 = func_0x042290(0x3c24,7,0xf2c,5,uRam301984,uRam30197c);
    sVar10 = ((((short)uVar11 >> 0xf) +
               (ushort)(uVar14 + uVar11 < uVar14 || uVar14 + uVar11 < uVar11) +
               ((short)uVar12 >> 0xf) +
              (ushort)(uVar16 + uVar12 < uVar16 || uVar16 + uVar12 < uVar12)) -
             ((short)uVar13 >> 0xf)) - (ushort)(uVar16 + uVar12 < uVar13);
    uVar16 = (uVar16 + uVar12) - uVar13;
  }
  else {
    sVar10 = 0;
    uVar16 = uRam01fdd8;
  }
  uVar14 = me7_lookup_1d_word_signed(0x3dbc,7,rpmclass_oppoint);
  uVar3 = CONCAT22(MDH,MDL);
  uRam304f7a = uVar16 + uVar14;
  uVar16 = sVar10 + ((short)uVar14 >> 0xf) +
           (ushort)(uVar16 + uVar14 < uVar16 || uVar16 + uVar14 < uVar14);
  if ((short)(uVar16 - (uRam304f7a < 0xa00)) < 0 ==
      ((short)uVar16 < 0 && (short)(uVar16 - (uRam304f7a < 0xa00)) < 0 != (short)uVar16 < 0)) {
    uVar14 = (ushort)(uRam304f7a != 0xffff);
    if ((uVar16 != uVar14 || uRam304f7a != 0xffff) &&
        (short)(uVar16 - uVar14) < 0 ==
        ((short)uVar16 < 0 && (short)(uVar16 - (uRam304f7a != 0xffff)) < 0 != (short)uVar16 < 0)) {
      uRam304f7a = 0xffff;
    }
  }
  else {
    uRam304f7a = 0xa00;
  }
  if ((((bRam304711 & 1) != 0) && ((uRam30267c & 0x40) == 0)) ||
     (((flags_torque_revlimit & 0x80) != 0 && ((uRam30267c & 0x800) == 0)))) {
    bVar8 = bRam30471d;
    if (bRam30471d < bRam0189f3) {
      bVar8 = bRam0189f3;
    }
    if (((flags_torque_revlimit & 0x80) == 0) || ((uRam00fd28 & 0x1000) == 0)) {
      uRam304f9c._2_2_ = (ushort)bVar8 << 8;
    }
    else {
      uVar16 = (ushort)bRam0189f0 * 0x100;
      uRam304f9c._2_2_ = uVar16 + uRam304f80;
      if (uVar16 + uRam304f80 < uVar16 || uVar16 + uRam304f80 < uRam304f80) {
        uRam304f9c._2_2_ = -1;
      }
    }
    uRam304f9c._0_2_ = 0;
  }
  if ((flags_torque_revlimit & 0x80) == 0) {
    uRam30267c = uRam30267c & 0xf7ff;
  }
  else {
    uRam30267c = uRam30267c | 0x800;
  }
  if (((bRam304711 & 1) != 0) && ((uRam30267c & 0x40) == 0)) {
    uRam304f84._2_2_ = (ushort)bRam304717 << 8;
    uRam304f84._0_2_ = 0;
    uRam304f88._0_2_ = 0;
    bRam30471b = bRam30471d;
    if (bRam30471d < bRam0189f3) {
      bRam30471b = bRam0189f3;
    }
    uRam304f80 = (ushort)bRam30471b << 8;
    uRam304f94._0_2_ = 0;
    uRam304f98._0_2_ = 0;
    uRam304fa0 = 0;
    bRam30471c = bRam30471b;
    uRam304f82 = uRam304f80;
    uRam304f88._2_2_ = uRam304f84._2_2_;
    uRam304f94._2_2_ = uRam304f80;
    uRam304f98._2_2_ = uRam304f80;
    uRam304fa2 = uRam304f80;
    if ((bRam304711 & 1) == 0) {
      uRam30267c = uRam30267c & 0xffbf;
    }
    else {
      uRam30267c = uRam30267c | 0x40;
    }
  }
  uVar19 = CONCAT22(uRam304f80,uRam304fa0);
  if ((bRam304711 & 1) != 0) {
    if ((uRam00fd28 & 0x800) != 0) {
      uVar15 = func_0x0420a8(0x3e04,7,uRam301986);
      uRam304f88 = me7_pt1_integrator(uVar15,(ushort)bRam304719 << 8,uRam304f88._2_2_,
                                      (undefined2)uRam304f88);
    }
    if ((uRam30267c & 8) != 0) {
      uVar15 = func_0x0420a8(0x3dda,7,uRam301986);
      uRam304f84 = me7_pt1_integrator(uVar15,(ushort)bRam304719 << 8,uRam304f84._2_2_,
                                      (undefined2)uRam304f84);
    }
    cVar6 = func_0x042020(0x91a,6,uRam301986);
    uVar16 = uRam304f88._2_2_ - 0xa00;
    if (uRam304f88 < 0xa000000) {
      uVar16 = 0;
    }
    iVar2 = (uint)(byte)(-cVar6 - 1) * (uint)uVar16;
    MDL = (ushort)iVar2;
    MDH = (ushort)((uint)iVar2 >> 0x10);
    MDC = MDC | 0x10;
    uVar14 = MDL >> 8 | MDH << 8;
    uVar16 = uVar14 + 0xa00;
    if (uVar14 + 0xa00 < uVar14 || uVar14 + 0xa00 < 0xa00) {
      uVar16 = 0xffff;
    }
    uVar14 = uRam304f84._2_2_ - 0xa00;
    if (uRam304f84 < 0xa000000) {
      uVar14 = 0;
    }
    uVar11 = func_0x042020(0x91a,6,uRam301986);
    uVar3 = (uint)(uVar11 & 0xff) * (uint)uVar14;
    MDL = (ushort)uVar3;
    MDH = (ushort)(uVar3 >> 0x10);
    MDC = MDC | 0x10;
    uVar11 = (ushort)(uVar3 >> 8);
    uVar14 = uVar11 + 0xa00;
    if (uVar11 + 0xa00 < uVar11 || uVar11 + 0xa00 < 0xa00) {
      uVar14 = 0xffff;
    }
    uRam304f74 = (uVar16 + uVar14) - 0xa00;
    if ((uVar16 + uVar14 < uVar16 || uVar16 + uVar14 < uVar14) != uVar16 + uVar14 < 0xa00 ||
        uRam304f74 == 0xffff) {
      uRam304f74 = 0xffff;
    }
    bRam304716 = (byte)(uRam304f74 >> 8);
    if ((bRam304716 < bRam0189eb) || ((flags_torque_revlimit & 0x80) != 0)) {
      uRam304f7e = (short)cRam0189f8 << 8;
      uRam304f7c = (short)cRam0189f7 << 8;
    }
    else {
      bVar8 = func_0x042020(0x9e4,6,uRam301970);
      bVar9 = func_0x042020(0x9de,6,uRam30197c);
      if (bVar8 < bVar9) {
        bVar8 = func_0x042020(0x9e4,6,uRam301970);
      }
      else {
        bVar8 = func_0x042020(0x9de,6,uRam30197c);
      }
      cVar6 = func_0x042082(0x92a,6,uRam301986);
      uVar16 = cVar6 * 0x100;
      uVar14 = uVar16;
      if ((short)uVar16 < 0) {
        uVar14 = cVar6 * -0x100;
      }
      uVar3 = (uint)uVar14 * (uint)bVar8 * 0x100;
      MDL = 0;
      MDH = (ushort)(uVar3 >> 0x10);
      MDC = MDC | 0x10;
      if ((uVar3 & 0xc0000000) == 0) {
        uRam304f7e = MDH * 2;
        if ((short)uVar16 < 0) {
          uRam304f7e = MDH * -2;
        }
      }
      else if ((short)uVar16 < 0) {
        uRam304f7e = 0x8000;
      }
      else {
        uRam304f7e = 0x7fff;
      }
      bVar8 = func_0x042020(0x9d8,6,uRam301970);
      bVar9 = func_0x042020(0x9d2,6,uRam30197c);
      if (bVar8 < bVar9) {
        bVar8 = func_0x042020(0x9d8,6,uRam301970);
      }
      else {
        bVar8 = func_0x042020(0x9d2,6,uRam30197c);
      }
      cVar6 = func_0x042082(0x931,6,uRam301986);
      uVar16 = cVar6 * 0x100;
      uVar14 = uVar16;
      if ((short)uVar16 < 0) {
        uVar14 = cVar6 * -0x100;
      }
      uVar3 = (uint)uVar14 * (uint)bVar8 * 0x100;
      sVar10 = (short)(uVar3 >> 0x10);
      MDC = MDC | 0x10;
      if ((uVar3 & 0xc0000000) == 0) {
        uRam304f7c = sVar10 * 2;
        if ((short)uVar16 < 0) {
          uRam304f7c = sVar10 * -2;
        }
      }
      else if ((short)uVar16 < 0) {
        uRam304f7c = 0x8000;
      }
      else {
        uRam304f7c = 0x7fff;
      }
    }
    uVar19 = CONCAT22(uRam304f80,uRam304fa0);
    MDH = (ushort)(uVar3 >> 0x10);
    MDL = (ushort)uVar3;
    if ((uRam00fd28 & 0x1000) != 0) {
      if ((short)uRam304f7e < 0) {
        sVar10 = uRam304f7e + uRam304f74;
        if (uRam304f7e <= uRam304f7e + uRam304f74 && uRam304f74 <= uRam304f7e + uRam304f74) {
          sVar10 = 0;
        }
      }
      else {
        sVar10 = uRam304f7e + uRam304f74;
        if (uRam304f7e + uRam304f74 < uRam304f7e || uRam304f7e + uRam304f74 < uRam304f74) {
          sVar10 = -1;
        }
      }
      uVar15 = func_0x0420a8(0x3df6,7,uRam301986);
      uVar19 = me7_pt1_integrator(uVar15,sVar10,uRam304f94._2_2_,(undefined2)uRam304f94);
      uRam304f82 = (ushort)((uint)uVar19 >> 0x10);
      uRam304f94._3_1_ = (byte)((uint)uVar19 >> 0x18);
      bRam30471c = uRam304f94._3_1_;
      if ((short)uRam304f7c < 0) {
        sVar10 = uRam304f7c + uRam304f74;
        if (uRam304f7c <= uRam304f7c + uRam304f74 && uRam304f74 <= uRam304f7c + uRam304f74) {
          sVar10 = 0;
        }
      }
      else {
        sVar10 = uRam304f7c + uRam304f74;
        if (uRam304f7c + uRam304f74 < uRam304f7c || uRam304f7c + uRam304f74 < uRam304f74) {
          sVar10 = -1;
        }
      }
      uRam304f94 = uVar19;
      uVar15 = func_0x0420a8(0x3de8,7,uRam301986);
      uRam304f98 = me7_pt1_integrator(uVar15,sVar10,uRam304f98._2_2_,(undefined2)uRam304f98);
      uVar15 = func_0x0420a8(0x3de8,7,uRam301986);
      uRam304f9c = me7_pt1_integrator(uVar15,uRam304f98._2_2_,uRam304f9c._2_2_,
                                      (undefined2)uRam304f9c);
      uVar15 = func_0x0420a8(0x3de8,7,uRam301986);
      uVar19 = me7_pt1_integrator(uVar15,uRam304f9c._2_2_,uRam304fa2,uRam304fa0);
      uVar3 = CONCAT22(MDH,MDL);
      uRam304fa2._1_1_ = (byte)((uint)uVar19 >> 0x18);
      bRam30471b = uRam304fa2._1_1_;
      uRam304fa2 = (ushort)((uint)uVar19 >> 0x10);
    }
  }
  uRam304f80 = (ushort)((uint)uVar19 >> 0x10);
  uRam304fa0 = (undefined2)uVar19;
  if ((bRam30174c & 1) == 0) {
    uRam304f76 = uRam01fdd6;
  }
  else {
    uRam304f76 = uRam3055d0;
  }
  if ((((uRam30267c & 8) != 0) && ((uRam30267c & 0x10) == 0)) || ((uRam302634 & 0x40) != 0)) {
    bRam304711 = bRam304711 | 1;
    if ((uRam306634 & 0x40) == 0) {
      cVar6 = (char)((short)(bRam30471a - 0x40) >> 3);
      sVar10 = (bRam30a004 - 10) - (short)cVar6;
      if (sVar10 < 1) {
        cVar7 = (char)(sVar10 * (ushort)bRam304713 >> 8);
      }
      else {
        cVar7 = (char)(sVar10 * (ushort)bRam304713 >> 8);
      }
      bRam304717 = cVar7 + cVar6 + 10;
      uVar16 = (bRam30a005 - 10) - (short)cVar6;
      if ((short)uVar16 < 1) {
        uVar3 = (int)(short)uVar16 * (int)(short)(ushort)bRam304714;
        MDC = MDC | 0x10;
        bRam30471d = (char)(uVar3 >> 8) + cVar6 + 10;
      }
      else {
        uVar3 = (uint)uVar16 * (uint)bRam304714;
        MDC = MDC | 0x10;
        bRam30471d = (char)(uVar3 >> 8) + cVar6 + 10;
      }
    }
    else {
      bRam304717 = bRam0189ec;
      bRam30471d = bRam0189f9;
    }
  }
  if ((uRam30267c & 8) == 0) {
    uRam30267c = uRam30267c & 0xffef;
  }
  else {
    uRam30267c = uRam30267c | 0x10;
  }
  if ((_flags_start_phase & 0x4000) == 0) {
    if ((uRam30267c & 8) != 0) {
      uVar16 = (bRam304719 - 10) + (short)cRam0189f4;
      if ((short)uVar16 < 0) {
        uVar3 = (uint)_rl_scaled * (uint)-uVar16;
        uVar16 = (ushort)uVar3;
        uVar14 = (ushort)(uVar3 >> 0x10);
        if (uVar14 - 7 == (ushort)(uVar16 != 0xffff) && uVar16 == 0xffff ||
            (uVar14 < 7 || uVar14 == 7 && uVar16 != 0xffff)) {
          if (uVar14 == 0 && uVar16 < 0xff) {
            uVar16 = 0;
          }
          else {
            uVar16 = uVar16 >> 3 | uVar14 << 0xd;
          }
        }
        else {
          uVar16 = 0xffff;
        }
        if (uRam304f92 == 0 && (uRam304f92 != 0 || uRam304f90 <= uVar16)) {
          uRam304f90 = 0;
          uRam304f92 = 0;
        }
        else {
          bVar1 = uRam304f90 < uVar16;
          uRam304f90 = uRam304f90 - uVar16;
          uRam304f92 = uRam304f92 - bVar1;
        }
      }
      else {
        uVar3 = (uint)_rl_scaled * (uint)uVar16;
        uVar16 = (ushort)uVar3;
        uVar14 = (ushort)(uVar3 >> 0x10);
        if (uVar14 - 7 == (ushort)(uVar16 != 0xffff) && uVar16 == 0xffff ||
            (uVar14 < 7 || uVar14 == 7 && uVar16 != 0xffff)) {
          if (uVar14 == 0 && uVar16 < 0xff) {
            uVar16 = 0;
          }
          else {
            uVar16 = uVar16 >> 3 | uVar14 << 0xd;
          }
        }
        else {
          uVar16 = 0xffff;
        }
        uVar14 = uVar16 + uRam304f90;
        bVar1 = uVar16 + uRam304f90 < uRam304f90;
        uRam304f90 = uVar16 + uRam304f90;
        uRam304f92 = uRam304f92 + (uVar14 < uVar16 || bVar1);
        if ((uRam304f92 - 0x7ff != (ushort)(uRam304f90 != 0xffff) || uRam304f90 != 0xffff) &&
            (0x7fe < uRam304f92 && (uRam304f92 != 0x7ff || uRam304f90 == 0xffff))) {
          uRam304f90 = 0xffff;
          uRam304f92 = 0x7ff;
        }
      }
      MDC = MDC | 0x10;
      uRam304f72 = uRam304f90 >> 0xb | uRam304f92 << 5;
    }
  }
  else {
    uRam304f90 = 0;
    uRam304f92 = 0;
    uRam304f72 = 0;
  }
  MDH = (ushort)(uVar3 >> 0x10);
  MDL = (ushort)uVar3;
  if ((bRam3031a9 & 1) == 0) {
    if ((((_flags_start_phase & 0x4000) == 0) && ((uRam30267c & 0x20) != 0)) && (bRam30a006 < 6)) {
      bRam30a006 = bRam30a006 + 1;
      bRam304723 = 0;
    }
  }
  else {
    bRam30a006 = bRam304723;
  }
  if ((bRam3031a9 & 4) == 0) {
    if ((((_flags_start_phase & 0x4000) == 0) && ((uRam30267c & 0x20) != 0)) && (bRam30a007 < 6)) {
      bRam30a007 = bRam30a007 + 1;
      bRam304722 = 0;
    }
  }
  else {
    bRam30a007 = bRam304722;
  }
  uVar16 = func_0x0421f4(0x3d8a,7,0x2849,4,uRam3019d0,uRam3019e4);
  uVar3 = (uint)uVar16 * (uint)(((ushort)bRam30a006 * (ushort)bRam018926 >> 3) + 0x20);
  MDL = (ushort)uVar3;
  MDH = (ushort)(uVar3 >> 0x10);
  MDC = MDC | 0x10;
  uVar3 = uVar3 >> 5;
  uVar14 = (ushort)(uVar3 >> 0x10);
  uVar16 = (ushort)uVar3;
  if ((uVar14 - 6 != (ushort)(uVar16 < 0xfff9) || uVar16 != 0xfff9) &&
      (5 < uVar14 && (uVar14 != 6 || uVar16 >= 0xfff9))) {
    uVar3 = 0x6fff9;
  }
  sVar10 = (short)(uVar3 >> 0x10);
  uVar16 = func_0x0421f4(0x3d58,7,0x2849,4,uRam3019ce,uRam3019e4);
  uVar4 = (uint)uVar16 * (uint)(((ushort)bRam30a007 * (ushort)bRam018923 >> 3) + 0x20);
  uVar5 = uVar4 >> 5;
  if ((_flags_idle_state & 0x8000) != 0) {
    uVar16 = (ushort)(uVar4 >> 0x15);
    if (uVar16 == 0) {
      sVar18 = 0;
    }
    else {
      sVar18 = uVar16 * bRam0189fe;
    }
    uVar4 = (uVar5 & 0xffff) * (uint)(ushort)bRam0189fe;
    uVar16 = sVar18 + (short)(uVar4 >> 0x10);
    uVar5 = CONCAT22(uVar16 >> 8,(ushort)uVar4 >> 8 | uVar16 * 0x100);
  }
  uVar14 = (ushort)(uVar5 >> 0x10);
  uVar16 = (ushort)uVar5;
  if ((uVar14 - 6 != (ushort)(uVar16 < 0xfff9) || uVar16 != 0xfff9) &&
      (5 < uVar14 && (uVar14 != 6 || uVar16 >= 0xfff9))) {
    uVar5 = 0x6fff9;
  }
  sVar18 = (short)(uVar5 >> 0x10);
  if ((bRam304711 & 0x20) == 0) {
    if ((uRam30267c & 0x80) == 0) {
      if (sVar18 == 0) {
        sVar17 = 0;
      }
      else {
        sVar17 = sVar18 * (ushort)bRam018922;
      }
      uVar4 = (uVar5 & 0xffff) * (uint)(ushort)bRam018922;
      uVar16 = sVar17 + (short)(uVar4 >> 0x10);
      uVar14 = uVar16 >> 7;
      if (uVar14 == 0 && (uVar14 != 0 || ((ushort)uVar4 >> 7 | uVar16 * 0x200) <= uRam304f72)) {
        bRam304711 = bRam304711 | 4;
      }
      else {
        bRam304711 = bRam304711 & 0xfb;
      }
      if (uRam01fdd2 < _rl_scaled) {
        if (bRam30471e < bRam0189f5) {
          bRam30471e = bRam30471e + 1;
        }
        else {
          bRam304711 = bRam304711 | 2;
        }
      }
      else {
        bRam30471e = 0;
        bRam304711 = bRam304711 & 0xfd;
      }
      if (((bRam304711 & 2) != 0) && ((bRam304711 & 4) != 0)) {
        uRam30267c = uRam30267c | 0x80;
      }
    }
    else if (bRam304720 < bRam0189fb) {
      bRam304720 = bRam304720 + 1;
    }
    else {
      bRam304711 = bRam304711 | 0x20;
    }
  }
  if ((bRam304711 & 0x40) == 0) {
    if ((uRam30267c & 0x100) == 0) {
      if (sVar10 == 0) {
        sVar17 = 0;
      }
      else {
        sVar17 = sVar10 * (ushort)bRam018925;
      }
      uVar4 = (uVar3 & 0xffff) * (uint)(ushort)bRam018925;
      uVar16 = sVar17 + (short)(uVar4 >> 0x10);
      uVar14 = uVar16 >> 7;
      if (uVar14 == 0 && (uVar14 != 0 || ((ushort)uVar4 >> 7 | uVar16 * 0x200) <= uRam304f72)) {
        bRam304711 = bRam304711 | 8;
      }
      else {
        bRam304711 = bRam304711 & 0xf7;
      }
      if (uRam01fdd4 < _rl_scaled) {
        if (bRam30471f < bRam0189f6) {
          bRam30471f = bRam30471f + 1;
        }
        else {
          bRam304711 = bRam304711 | 0x10;
        }
      }
      else {
        bRam30471f = 0;
        bRam304711 = bRam304711 & 0xef;
      }
      if (((bRam304711 & 0x10) != 0) && ((bRam304711 & 8) != 0)) {
        uRam30267c = uRam30267c | 0x100;
      }
    }
    else if (bRam304721 < bRam0189fc) {
      bRam304721 = bRam304721 + 1;
    }
    else {
      bRam304711 = bRam304711 | 0x40;
    }
  }
  if ((bRam304711 & 0x40) == 0) {
    if (sVar10 == 0) {
      sVar10 = 0;
    }
    else {
      sVar10 = sVar10 * (ushort)bRam018924;
    }
    uVar4 = (uVar3 & 0xffff) * (uint)(ushort)bRam018924;
    uVar16 = sVar10 + (short)(uVar4 >> 0x10);
    uVar3 = CONCAT22(uVar16 >> 5,(ushort)uVar4 >> 5 | uVar16 * 0x800);
  }
  uVar14 = (ushort)(uVar3 >> 0x10);
  uVar16 = (ushort)uVar3;
  if ((uRam302634 & 0x40) == 0) {
    if ((uVar14 != (uVar16 != 0xffff) || uVar16 != 0xffff) && (uVar14 != 0 || uVar16 == 0xffff)) {
      uVar3 = 0xffff;
    }
  }
  else if (uVar3 != CONCAT12(uVar16 < uRam01fc22,uRam01fc22) &&
           (uVar14 != 0 || uVar16 >= uRam01fc22)) {
    uVar3 = (uint)uRam01fc22;
  }
  sVar10 = (short)(uVar3 >> 0x10);
  if (sVar10 == 0 && (sVar10 != 0 || (ushort)uVar3 <= uRam304f72)) {
    uRam00fd28 = uRam00fd28 | 0x1000;
  }
  if ((bRam304711 & 0x20) == 0) {
    if (sVar18 == 0) {
      sVar18 = 0;
    }
    else {
      sVar18 = sVar18 * (ushort)bRam018921;
    }
    uVar4 = (uVar5 & 0xffff) * (uint)(ushort)bRam018921;
    uVar16 = sVar18 + (short)(uVar4 >> 0x10);
    uVar5 = CONCAT22(uVar16 >> 5,(ushort)uVar4 >> 5 | uVar16 * 0x800);
  }
  MDH = (ushort)(uVar4 >> 0x10);
  MDL = (ushort)uVar4;
  uVar14 = (ushort)(uVar5 >> 0x10);
  uVar16 = (ushort)uVar5;
  MDC = MDC | 0x10;
  if ((uRam302634 & 0x40) == 0) {
    if ((uVar14 != (uVar16 != 0xffff) || uVar16 != 0xffff) && (uVar14 != 0 || uVar16 == 0xffff)) {
      uVar5 = 0xffff;
    }
  }
  else if (uVar5 != CONCAT12(uVar16 < uRam01fc22,uRam01fc22) &&
           (uVar14 != 0 || uVar16 >= uRam01fc22)) {
    uVar5 = (uint)uRam01fc22;
  }
  sVar10 = (short)(uVar5 >> 0x10);
  if (sVar10 == 0 && (sVar10 != 0 || (ushort)uVar5 <= uRam304f72)) {
    uRam00fd28 = uRam00fd28 | 0x800;
  }
  if ((uRam30267c & 8) != 0) {
    bRam30a004 = bRam304716;
    bRam30a005 = bRam30471c;
    if ((uRam00fd28 & 0x800) == 0) {
      bRam3031a9 = bRam3031a9 & 0xfb;
    }
    else {
      bRam3031a9 = bRam3031a9 | 4;
    }
    if ((uRam00fd28 & 0x1000) == 0) {
      bRam3031a9 = bRam3031a9 & 0xfe;
    }
    else {
      bRam3031a9 = bRam3031a9 | 1;
    }
  }
  bRam304713 = func_0x042020(0x90d,6,uRam3019f6);
  bRam304714 = func_0x042020(0x913,6,uRam3019f6);
  if ((_flags_start_phase & 0x4000) == 0) {
    uRam30267c = uRam30267c & 0xffdf;
  }
  else {
    uRam30267c = uRam30267c | 0x20;
  }
  return;
}


// ================= idle_spark_reserve @ 053dec =================

/* WARNING: Removing unreachable block (ram,0x054392) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* idle/startup spark reserve + knock-window -> byte_301360 (warmup-idle-thermal.md 3) */

void idle_spark_reserve(void)

{
  bool bVar1;
  uint uVar2;
  ushort uVar3;
  int iVar4;
  undefined2 uVar6;
  int iVar5;
  uint uVar7;
  int iVar8;
  byte bVar9;
  char cVar10;
  byte bVar11;
  ushort uVar12;
  short sVar13;
  ushort uVar14;
  short sVar15;
  short sVar16;
  ushort uVar17;
  int iVar18;
  undefined4 uVar19;
  int iVar20;
  uint uVar21;
  
  bVar9 = bRam01863d;
  if (((((bRam01863d & 1) == 0) || ((_flags_idle_state & 0x400) == 0)) || ((bRam301361 & 2) == 0))
     && (((bRam01863d & 2) == 0 || ((_flags_idle_state & 0x8000) == 0)))) {
    uRam00fd26 = uRam00fd26 & 0xfff7;
  }
  else {
    uRam00fd26 = uRam00fd26 | 8;
  }
  idle_spark_reserve =
       func_0x042544(uRam01efd4,0x2fd6,7,uRam01efd5,0x2fdc,7,0x2fe0,7,(short)catheat_mode,uRam301655
                    );
  iVar8 = CONCAT22(iRam30251c._2_2_,(undefined2)iRam30251c);
  uVar19 = CONCAT22(uRam30250c._2_2_,(undefined2)uRam30250c);
  iVar5 = CONCAT22(iRam302528._2_2_,(undefined2)iRam302528);
  iVar20 = CONCAT22(iRam302524._2_2_,(undefined2)iRam302524);
  uVar21 = CONCAT22(uRam302518._2_2_,(undefined2)uRam302518);
  iVar18 = CONCAT22(MDH,sRam302522);
  uVar7 = CONCAT22(uRam302514._2_2_,(undefined2)uRam302514);
  iVar4 = CONCAT22(iRam302510._2_2_,(undefined2)iRam302510);
  if (((bRam30127a & 8) == 0) && ((uRam00fd24 & 0x4000) != 0)) {
    if (bRam301364 < bRam0137c4) {
      bRam301364 = bRam301364 + 1;
    }
    else {
      bRam301362 = bRam301362 | 8;
    }
  }
  else {
    bRam301362 = bRam301362 & 0xf7;
    bRam301364 = 0;
  }
  uVar12 = (ushort)bRam013705 * 4;
  uVar14 = (ushort)bRam30134a * 0x28;
  uRam30250a = uVar14 + uVar12;
  if (uVar14 + uVar12 < uVar14 || uVar14 + uVar12 < uVar12) {
    uRam30250a = 0xffff;
  }
  if ((((bRam301361 & 1) != 0) || ((bRam301362 & 8) != 0)) ||
     ((nmot_w <= uRam30250a && ((uRam00fd24 & 0x8000) != 0)))) {
    uRam00fd26 = uRam00fd26 & 0xffdf;
  }
  if (((uRam00fd26 & 0x20) == 0) || ((bVar9 & 4) == 0)) {
    uRam00fd26 = uRam00fd26 & 0xffef;
  }
  else {
    uRam00fd26 = uRam00fd26 | 0x10;
  }
  if ((flags_diag_cfg_b & 0x200) != 0) {
    sRam3024ea = 0;
    uRam3024ec = 0;
    goto LAB_0546b2;
  }
  if (((_DAT_302632 & 0x40) == 0) && ((uRam00fd26 & 0x10) == 0)) {
    uVar12 = func_0x041106(0x36f8,uRam301990);
    sRam302508 = (uVar12 & 0xff) << 7;
    cVar10 = func_0x041126(0x36ec,uRam301990);
  }
  else {
    uVar12 = func_0x041106(0x36fe,uRam301990);
    sRam302508 = (uVar12 & 0xff) << 7;
    cVar10 = func_0x041126(0x36f2,uRam301990);
  }
  iVar18 = CONCAT22(iRam302528._2_2_,(undefined2)iRam302528);
  iVar4 = CONCAT22(MDH,MDL);
  sRam302506 = (short)cVar10 << 7;
  if ((uRam00fd26 & 1) == 0) {
    sRam3024e2 = 0;
  }
  else {
    if ((uRam00fd26 & 4) == 0) {
      if ((_flags_idle_state & 0x200) == 0) {
        bVar11 = func_0x042020(0x641,6,uRam30198a);
      }
      else {
        bVar11 = func_0x042020(0x647,6,uRam30198a);
      }
    }
    else {
      bVar11 = func_0x041106(0x3707,uRam30198a);
    }
    uVar12 = func_0x041106(0x370d,uRam3024c4);
    iVar4 = (int)(short)((uVar12 & 0xff) * (short)cRam301658) * (int)(short)-(ushort)bVar11;
    MDL = (ushort)iVar4;
    MDH = (ushort)((uint)iVar4 >> 0x10);
    MDC = MDC | 0x10;
    iVar18 = iVar4 >> 4;
    uVar17 = (ushort)((uint)iVar18 >> 0x10);
    uVar12 = (ushort)iVar18;
    uVar14 = (ushort)(uVar12 < 0x7fff);
    if (uVar17 == uVar14 && uVar12 == 0x7fff ||
        (short)(uVar17 - uVar14) < 0 !=
        (iVar18 < 0 && (short)(uVar17 - (uVar12 < 0x7fff)) < 0 != iVar18 < 0)) {
      if ((short)((uVar17 + 1) - (ushort)(uVar12 < 0x8000)) < 0 !=
          (-1 < iVar18 && (short)((uVar17 + 1) - (ushort)(uVar12 < 0x8000)) < 0 != iVar18 < 0)) {
        uVar12 = 0x8000;
      }
    }
    else {
      uVar12 = 0x7fff;
    }
    uVar14 = uVar12;
    if ((short)uVar12 < 0) {
      if (uVar12 == 0x8000) {
        uVar14 = 0x7fff;
      }
      else {
        uVar14 = -uVar12;
      }
    }
    sVar13 = sRam3024e2;
    if (sRam3024e2 < 0) {
      if (sRam3024e2 == -0x8000) {
        sVar13 = 0x7fff;
      }
      else {
        sVar13 = -sRam3024e2;
      }
    }
    if ((short)(uVar14 - sVar13) < 0 ==
        ((short)uVar14 < 0 != sVar13 < 0 && (short)(uVar14 - sVar13) < 0 != (short)uVar14 < 0)) {
      iVar18 = (uint)uVar12 << 0x10;
    }
    else {
      iVar18 = me7_slew_limiter((ushort)bRam0137c6 << 8,uVar12,iRam302528._2_2_,
                                (undefined2)iRam302528);
      iVar4 = CONCAT22(MDH,MDL);
    }
    iRam302528._2_2_ = (short)((uint)iVar18 >> 0x10);
    sRam3024e2 = iRam302528._2_2_;
  }
  MDH = (ushort)((uint)iVar4 >> 0x10);
  MDL = (ushort)iVar4;
  iRam302528 = iVar18;
  bRam30135f = func_0x042020(0x677,6,uRam3019e6);
  if ((_flags_start_phase & 0x8000) == 0) {
    cRam301363 = cRam0137c2;
LAB_0540a0:
    bRam301362 = bRam301362 & 0xfb;
  }
  else {
    if (cRam301363 != '\0') {
      cRam301363 = cRam301363 + -1;
      goto LAB_0540a0;
    }
    bRam301362 = bRam301362 | 4;
  }
  if ((DAT_00fd4e & 0x4000) == 0) {
    if ((uRam00fd56 & 0x2000) == 0) {
      if (((bRam301362 & 4) == 0) ||
         (((uRam00fd24 & 0x2000) == 0 &&
          (catheat_mode == cRam013704 ||
           (char)(catheat_mode - cRam013704) < '\0' !=
           (catheat_mode < '\0' != cRam013704 < '\0' &&
           (char)(catheat_mode - cRam013704) < '\0' != catheat_mode < '\0'))))) {
        iVar18 = (uint)MDH << 0x10;
      }
      else if ((uRam00fd24 & 0x4000) == 0) {
        iVar18 = CONCAT22(MDH,(ushort)bRam30135f << 5);
      }
      else if ((uRam00fd26 & 4) == 0) {
        iVar18 = (uint)bRam01371a * 0x1fffe0;
        MDL = (ushort)iVar18;
        MDC = MDC | 0x10;
      }
      else {
        iVar18 = (uint)bRam01371d * 0x1fffe0;
        MDL = (ushort)iVar18;
        MDC = MDC | 0x10;
      }
    }
    else {
      iVar18 = (uint)bRam01371b * 0x1fffe0;
      MDL = (ushort)iVar18;
      MDC = MDC | 0x10;
    }
  }
  else {
    iVar18 = CONCAT22(MDH,(ushort)bRam01371c * -0x20);
  }
  MDH = (ushort)((uint)iVar18 >> 0x10);
  sVar13 = (short)iVar18;
  if (((_flags_start_phase & 0x4000) == 0) &&
     (sVar13 != sRam302522 &&
      sVar13 - sRam302522 < 0 ==
      (sVar13 < 0 != sRam302522 < 0 && sVar13 - sRam302522 < 0 != sVar13 < 0))) {
    uVar19 = me7_slew_limiter((ushort)bRam0137c7 << 8,sVar13,sRam302522,uRam302520);
    uRam302520 = (undefined2)uVar19;
    iVar18 = CONCAT22(MDH,(short)((uint)uVar19 >> 0x10));
  }
  else {
    uRam302520 = 0;
  }
  MDH = (ushort)((uint)iVar18 >> 0x10);
  sRam302522 = (short)iVar18;
  if ((bRam301356 & 1) == 0) {
    if (((flags_torque_revlimit & 0x100) == 0) && ((uRam00fd4c & 0x4000) == 0)) {
      sRam302502 = sRam302522;
    }
    else {
      sRam302502 = sRam3024e6;
    }
  }
  else {
    sRam302502 = 0;
  }
  if (((uRam00fd24 & 0x2000) == 0) &&
     (catheat_mode == cRam013704 ||
      (char)(catheat_mode - cRam013704) < '\0' !=
      (catheat_mode < '\0' != cRam013704 < '\0' &&
      (char)(catheat_mode - cRam013704) < '\0' != catheat_mode < '\0'))) {
    uVar12 = 0;
  }
  else {
    uRam3024fe = func_0x04101c(0x37ba,(short)catheat_mode,uRam3024fe);
    if ((uRam00fd26 & 4) == 0) {
      uVar12 = func_0x042020(0x66b,6,uRam3024fe);
      iVar18 = CONCAT22(MDH,sRam302522);
      uVar12 = (uVar12 & 0xff) << 5;
    }
    else {
      uVar12 = func_0x042020(0x671,6,uRam3024fe);
      iVar18 = CONCAT22(MDH,sRam302522);
      uVar12 = (uVar12 & 0xff) << 5;
    }
  }
  MDH = (ushort)((uint)iVar18 >> 0x10);
  sRam302522 = (short)iVar18;
  if (iRam302524._2_2_ == uVar12 ||
      (short)(iRam302524._2_2_ - uVar12) < 0 !=
      ((short)iRam302524._2_2_ < 0 &&
      (short)(iRam302524._2_2_ - uVar12) < 0 != (short)iRam302524._2_2_ < 0)) {
    iVar20 = (uint)uVar12 << 0x10;
  }
  else {
    iVar20 = me7_slew_limiter((ushort)bRam0137c7 << 8,uVar12,iRam302524._2_2_,(undefined2)iRam302524
                             );
    iVar18 = CONCAT22(MDH,sRam302522);
  }
  uVar21 = CONCAT22(uRam302518._2_2_,(undefined2)uRam302518);
  iRam302524._2_2_ = (ushort)((uint)iVar20 >> 0x10);
  iVar4 = CONCAT22(iRam302510._2_2_,(undefined2)iRam302510);
  uVar7 = CONCAT22(uRam302514._2_2_,(undefined2)uRam302514);
  MDH = (ushort)((uint)iVar18 >> 0x10);
  sRam302522 = (short)iVar18;
  if (((_DAT_302632 & 0x40) != 0) && (uRam01efd2 < nmot_w)) {
    iRam302524._2_2_ = 0;
  }
  sRam302500 = iRam302524._2_2_;
  if (((_flags_start_phase & 0x4000) == 0) &&
     (((cRam01371e != '\x01' || ((uRam00fd26 & 4) != 0)) || ((bRam301362 & 0x10) == 0)))) {
    if ((uRam00fd24 & 0x8000) == 0) {
      sRam3024e4 = sRam302502;
      if ((sRam3024e6 - sRam302502 < 0 ==
           (sRam3024e6 < 0 != sRam302502 < 0 && sRam3024e6 - sRam302502 < 0 != sRam3024e6 < 0)) &&
         (sRam3024e4 = iRam302524._2_2_, uVar21 = CONCAT22(uRam302518._2_2_,(undefined2)uRam302518),
         sRam3024e6 == iRam302524._2_2_ ||
         (short)(sRam3024e6 - iRam302524._2_2_) < 0 !=
         (sRam3024e6 < 0 != (short)iRam302524._2_2_ < 0 &&
         (short)(sRam3024e6 - iRam302524._2_2_) < 0 != sRam3024e6 < 0))) {
        sRam3024e4 = sRam3024e6;
        uVar21 = CONCAT22(uRam302518._2_2_,(undefined2)uRam302518);
      }
    }
    else {
      iRam302524 = iVar20;
      if ((evap_monitor_flags & 8) == 0) {
        if ((uRam00fd26 & 4) == 0) {
          bRam30135e = func_0x042020(0x657,6,uRam3024fa);
        }
        else {
          bRam30135e = func_0x042020(0x661,6,uRam3024fa);
        }
      }
      else {
        bRam30135e = func_0x042020(0x64d,6,uRam3024fa);
      }
      uVar21 = CONCAT22(uRam302518._2_2_,(undefined2)uRam302518);
      if ((((DAT_00fd4e & 0x4000) != 0) && ((evap_monitor_flags & 8) != 0)) &&
         ((bRam301362 & 1) == 0)) {
        sRam3024e8 = sRam3024e6;
      }
      if (((bRam30160a & 2) == 0) && ((bRam301362 & 2) != 0)) {
        if (sRam3024e8 == sRam3024e6 ||
            sRam3024e8 - sRam3024e6 < 0 !=
            (sRam3024e8 < 0 != sRam3024e6 < 0 && sRam3024e8 - sRam3024e6 < 0 != sRam3024e8 < 0)) {
          uVar21 = 0;
        }
        else {
          MDL = (ushort)(sRam3024e8 - sRam3024e6) / (ushort)bRam0137c1;
          MDC = MDC | 0x10;
          uVar21 = (uint)MDL << 0x10;
        }
      }
      else if (uRam302518._2_2_ != 0) {
        MDL = 0xffff / bRam0137c1;
        MDH = 0xffff % (ushort)bRam0137c1;
        MDC = MDC | 0x10;
        uVar21 = me7_pt1_integrator(MDL,0,uRam302518._2_2_,(undefined2)uRam302518);
      }
      uVar7 = (uVar21 >> 0x10) * (uint)bRam013713 * 2;
      uVar2 = uVar7 / (ushort)bRam30135e;
      uRam3024f6 = (ushort)uVar2;
      if (bRam30135e == 0 || 0xffff < uVar2) {
        uRam3024f6 = 0xffff;
      }
      sVar16 = (short)cRam013706;
      sVar13 = sVar16 * 0x28;
      sVar15 = sRam3024f8;
      if (sRam3024f8 == sVar13 ||
          sRam3024f8 + sVar16 * -0x28 < 0 !=
          (sRam3024f8 < 0 != sVar13 < 0 && sRam3024f8 + sVar16 * -0x28 < 0 != sRam3024f8 < 0)) {
        sVar15 = sVar13;
      }
      bVar1 = 1 < (uRam3024f6 & 1);
      uVar12 = uRam3024f6 >> 1;
      sVar13 = sVar15 + uVar12 + (ushort)bVar1;
      if ((-1 < sVar15 && (short)(sVar15 + uVar12 + (ushort)bVar1) < 0 != sVar15 < 0) ||
         (sVar16 = sVar13 + uVar12, -1 < sVar13 && (short)(sVar13 + uVar12) < 0 != sVar13 < 0)) {
        sVar16 = 0x7fff;
      }
      iVar4 = (int)sVar16 * (int)(short)(ushort)bRam30135e;
      MDL = (ushort)iVar4;
      uVar6 = (undefined2)((uint)iVar4 >> 0x10);
      MDC = MDC | 0x10;
      iVar4 = iVar4 >> 8;
      uVar17 = (ushort)((uint)iVar4 >> 0x10);
      uVar12 = (ushort)iVar4;
      uVar14 = (ushort)(uVar12 < 0x7fff);
      if (uVar17 == uVar14 && uVar12 == 0x7fff ||
          (short)(uVar17 - uVar14) < 0 !=
          (iVar4 < 0 && (short)(uVar17 - (uVar12 < 0x7fff)) < 0 != iVar4 < 0)) {
        if ((short)((uVar17 + 1) - (ushort)(uVar12 < 0x8000)) < 0 !=
            (-1 < iVar4 && (short)((uVar17 + 1) - (ushort)(uVar12 < 0x8000)) < 0 != iVar4 < 0)) {
          uVar12 = 0x8000;
        }
      }
      else {
        uVar12 = 0x7fff;
      }
      sRam3024e6 = uVar12 + sRam3024e6;
      sRam3024e4 = sRam302502;
      iVar18 = CONCAT22(uVar6,sRam302522);
      iVar20 = iRam302524;
      if ((sRam3024e6 - sRam302502 < 0 ==
           (sRam3024e6 < 0 != sRam302502 < 0 && sRam3024e6 - sRam302502 < 0 != sRam3024e6 < 0)) &&
         (sRam3024e4 = sRam302500, iVar18 = CONCAT22(uVar6,sRam302522),
         sRam3024e6 == sRam302500 ||
         sRam3024e6 - sRam302500 < 0 !=
         (sRam3024e6 < 0 != sRam302500 < 0 && sRam3024e6 - sRam302500 < 0 != sRam3024e6 < 0))) {
        sRam3024e4 = sRam3024e6;
        iVar18 = CONCAT22(uVar6,sRam302522);
      }
    }
  }
  else if ((_flags_start_phase & 0x4000) == 0) {
    sRam3024e4 = 0;
    uVar7 = CONCAT22(uRam302514._2_2_,(undefined2)uRam302514);
    iVar4 = CONCAT22(iRam302510._2_2_,(undefined2)iRam302510);
    uVar21 = CONCAT22(uRam302518._2_2_,(undefined2)uRam302518);
  }
  else {
    sRam3024e4 = (ushort)bRam30135f << 5;
    uVar7 = CONCAT22(uRam302514._2_2_,(undefined2)uRam302514);
    iVar4 = CONCAT22(iRam302510._2_2_,(undefined2)iRam302510);
    uVar21 = CONCAT22(uRam302518._2_2_,(undefined2)uRam302518);
  }
  iVar8 = CONCAT22(iRam30251c._2_2_,(undefined2)iRam30251c);
  MDH = (ushort)((uint)iVar18 >> 0x10);
  iVar5 = CONCAT22(MDH,MDL);
  sRam302522 = (short)iVar18;
  sRam3024e6 = sRam3024e4;
  sRam3024ea = sRam3024e4;
  if ((uRam00fd26 & 1) == 0) {
    uRam3024ec = 0;
    iVar5 = iRam302528;
    uVar19 = uRam30250c;
  }
  else {
    if (((_flags_idle_state & 0x200) == 0) || ((bVar9 & 8) == 0)) {
      iRam302510 = iVar4;
      uRam302514 = uVar7;
      uRam302518 = uVar21;
      iRam302524 = iVar20;
      uRam30250c = me7_slew_limiter((ushort)bRam0137c8 << 8,uRam302b08,uRam30250c._2_2_,
                                    (undefined2)uRam30250c);
      uRam302504 = (undefined2)((uint)uRam30250c >> 0x10);
      if ((uRam00fd26 & 4) == 0) {
        sVar13 = func_0x0414f8(uRam015bea,0x5bec,uRam015beb,0x5bf8,0x5bfc,uRam302504,uRam30131f);
      }
      else {
        sVar13 = func_0x0414f8(uRam015c2c,0x5c2e,uRam015c2d,0x5c3a,0x5c3e,uRam302504,uRam30131f);
      }
      uVar12 = func_0x041106(0x3714,uRam3024c4);
      iVar5 = (int)sVar13 * (int)(short)(uVar12 & 0xff);
      MDC = MDC | 0x10;
      uVar12 = (ushort)iVar5 >> 8 | (short)((uint)iVar5 >> 0x10) << 8;
      uRam3024e0 = uVar12;
      iVar4 = iRam302510;
      uVar7 = uRam302514;
      uVar21 = uRam302518;
      iVar20 = iRam302524;
    }
    else {
      uVar12 = 0;
    }
    MDH = (ushort)((uint)iVar5 >> 0x10);
    MDL = (ushort)iVar5;
    iRam302510 = iVar4;
    uRam302514 = uVar7;
    uRam302518 = uVar21;
    iRam302524 = iVar20;
    uRam3024fc = func_0x040f32(0x37b5,uRam30131f,uRam3024fc);
    iVar18 = CONCAT22(MDH,MDL);
    if ((uRam00fd26 & 0x20) == 0) {
      if ((uRam00fd26 & 4) == 0) {
        if ((_flags_idle_state & 0x200) == 0) {
          uVar12 = func_0x04119c(0x373d,0x37b5,uRam3024fa,uRam3024fc);
          uVar12 = uVar12 & 0xff;
        }
        else {
          uVar12 = func_0x04119c(0x3765,0x37b5,uRam3024fa,uRam3024fc);
          uVar12 = uVar12 & 0xff;
        }
      }
      else {
        uVar12 = func_0x04119c(0x378d,0x37b5,uRam3024fa,uRam3024fc);
        uVar12 = uVar12 & 0xff;
      }
      iVar18 = (int)sRam3024f8 * (int)(short)uVar12;
      MDL = (ushort)iVar18;
      MDH = (ushort)((uint)iVar18 >> 0x10);
      MDC = MDC | 0x10;
      iVar4 = iVar18 >> 3;
      uVar12 = (ushort)((uint)iVar4 >> 0x10);
      uVar14 = (ushort)iVar4;
      if ((short)((uVar12 + 1) - (ushort)(uVar14 < 0x8000)) < 0 ==
          (-1 < iVar4 && (short)((uVar12 + 1) - (ushort)(uVar14 < 0x8000)) < 0 != iVar4 < 0)) {
        uVar17 = (ushort)(uVar14 < 0x7fff);
        if ((uVar12 != uVar17 || uVar14 != 0x7fff) &&
            (short)(uVar12 - uVar17) < 0 ==
            (iVar4 < 0 && (short)(uVar12 - (uVar14 < 0x7fff)) < 0 != iVar4 < 0)) {
          uVar14 = 0x7fff;
        }
      }
      else {
        uVar14 = 0x8000;
      }
      if (iRam30251c._2_2_ < 0xfffe) {
        iRam30251c = me7_pt1_integrator((ushort)bRam0137c5 << 8,0xffff,iRam30251c._2_2_,
                                        (undefined2)iRam30251c);
        uVar12 = (ushort)((uint)iRam30251c >> 0x10);
        if (iRam30251c < 0) {
          iVar18 = (int)(short)uVar14 * (int)(short)(uVar12 & 0x7fff);
          uVar3 = (ushort)iVar18;
          MDC = MDC | 0x10;
          uVar17 = uVar14 * -0x8000;
          uVar12 = uVar3 + uVar17;
          uVar14 = (short)((uint)iVar18 >> 0x10) + ((short)uVar14 >> 1) +
                   (ushort)(uVar3 + uVar17 < uVar3 || uVar3 + uVar17 < uVar17);
          if ((short)uVar14 < 0) {
            uVar14 = uVar14 + (uVar12 - 1 < uVar12 || uVar12 != 0);
          }
        }
        else {
          iVar18 = (int)(short)uVar14 * (int)(short)uVar12;
          uVar12 = (ushort)iVar18;
          uVar14 = (ushort)((uint)iVar18 >> 0x10);
          MDC = MDC | 0x10;
          if (iVar18 < 0) {
            uVar14 = uVar14 + (uVar12 - 1 < uVar12 || uVar12 != 0);
          }
        }
      }
      uRam3024ee = uVar14;
      if ((((_flags_idle_state & 0x200) == 0) || (uVar12 = uVar14, (bVar9 & 8) == 0)) &&
         (uVar12 = uRam3024e0 + uVar14,
         (short)uRam3024e0 < 0 == (short)uVar14 < 0 &&
         (short)(uRam3024e0 + uVar14) < 0 != (short)uRam3024e0 < 0)) {
        uVar12 = 0x7fff;
      }
    }
    else {
      iRam30251c = 0;
      uRam3024ee = 0;
    }
    MDH = (ushort)((uint)iVar18 >> 0x10);
    MDL = (ushort)iVar18;
    if ((_DAT_302632 & 0x40) == 0) {
      uVar14 = func_0x041106(0x36e6,uRam301990);
      iVar18 = CONCAT22(MDH,MDL);
      uVar14 = uVar14 & 0xff;
    }
    else {
      uVar14 = (ushort)bRam018640;
    }
    MDH = (ushort)((uint)iVar18 >> 0x10);
    MDL = (ushort)iVar18;
    uVar17 = uVar14 * 0x80;
    iVar4 = iRam302510;
    uVar7 = uRam302514;
    uVar21 = uRam302518;
    iVar20 = iRam302524;
    if (uVar12 == uVar17 ||
        (short)(uVar12 + uVar14 * -0x80) < 0 !=
        ((short)uVar12 < 0 && (short)(uVar12 + uVar14 * -0x80) < 0 != (short)uVar12 < 0)) {
      cVar10 = cRam01863f;
      if ((_DAT_302632 & 0x40) == 0) {
        cVar10 = func_0x041126(0x36e0,uRam301990);
        iVar18 = CONCAT22(MDH,MDL);
        iVar4 = iRam302510;
        uVar7 = uRam302514;
      }
      sVar13 = (short)cVar10;
      uVar17 = sVar13 * 0x80;
      uVar21 = uRam302518;
      iVar20 = iRam302524;
      if ((short)(uVar12 + sVar13 * -0x80) < 0 ==
          ((short)uVar12 < 0 != (short)uVar17 < 0 &&
          (short)(uVar12 + sVar13 * -0x80) < 0 != (short)uVar12 < 0)) {
        uVar17 = uVar12;
      }
    }
    MDH = (ushort)((uint)iVar18 >> 0x10);
    MDL = (ushort)iVar18;
    iVar18 = CONCAT22(MDH,sRam302522);
    uRam3024ec = uVar17;
    iVar5 = iRam302528;
    uVar19 = uRam30250c;
    iVar8 = iRam30251c;
  }
LAB_0546b2:
  iRam30251c._2_2_ = (ushort)((uint)iVar8 >> 0x10);
  iRam30251c._0_2_ = (undefined2)iVar8;
  uRam30250c._2_2_ = (undefined2)((uint)uVar19 >> 0x10);
  uRam30250c._0_2_ = (undefined2)uVar19;
  iRam302528._2_2_ = (short)((uint)iVar5 >> 0x10);
  iRam302528._0_2_ = (undefined2)iVar5;
  iRam302524._2_2_ = (ushort)((uint)iVar20 >> 0x10);
  iRam302524._0_2_ = (undefined2)iVar20;
  uRam302518._2_2_ = (short)(uVar21 >> 0x10);
  uRam302518._0_2_ = (undefined2)uVar21;
  MDH = (ushort)((uint)iVar18 >> 0x10);
  sRam302522 = (short)iVar18;
  uRam302514._2_2_ = (undefined2)(uVar7 >> 0x10);
  uRam302514._0_2_ = (undefined2)uVar7;
  iRam302510._2_2_ = (undefined2)((uint)iVar4 >> 0x10);
  iRam302510._0_2_ = (undefined2)iVar4;
  if ((uRam00fd26 & 4) == 0) {
    bRam301362 = bRam301362 & 0xef;
  }
  else {
    bRam301362 = bRam301362 | 0x10;
  }
  if ((bRam30160a & 2) == 0) {
    bRam301362 = bRam301362 & 0xfd;
  }
  else {
    bRam301362 = bRam301362 | 2;
  }
  if (((DAT_00fd4e & 0x4000) == 0) || ((evap_monitor_flags & 8) == 0)) {
    bRam301362 = bRam301362 & 0xfe;
  }
  else {
    bRam301362 = bRam301362 | 1;
  }
  return;
}


// ================= egt_sensor_model @ 0945c2 =================

/* WARNING: Removing unreachable block (ram,0x094da6) */
/* WARNING: Removing unreachable block (ram,0x094dac) */
/* WARNING: Removing unreachable block (ram,0x094dae) */
/* WARNING: Removing unreachable block (ram,0x094db4) */
/* WARNING: Removing unreachable block (ram,0x094db2) */
/* WARNING: Removing unreachable block (ram,0x094e08) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* exhaust-gas-temp sensor model + diag (EXA* cals) -> byte_304974 (warmup-idle-thermal.md 4) */

void egt_sensor_model(void)

{
  bool bVar1;
  bool bVar2;
  ushort uVar3;
  ushort uVar4;
  bool bVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  byte bVar9;
  byte bVar10;
  byte bVar11;
  char cVar12;
  char cVar13;
  char cVar14;
  undefined2 uVar15;
  short sVar16;
  ushort uVar17;
  ushort uVar18;
  ushort uVar19;
  ushort uStack_24;
  ushort uStack_22;
  ushort uStack_20;
  ushort uStack_1e;
  byte bStack_1c;
  byte bStack_16;
  short sStack_14;
  byte bStack_12;
  
  uVar4 = uRam303bf0;
  uVar3 = uRam303bec;
  bRam304970 = bRam00f472;
  bRam30496f = 0x80;
  bRam301640 = bRam301640 & 0xf8;
  uStack_22 = uRam303bec;
  uStack_24 = uRam303bf0;
  if ((bRam301636 & 1) == 0) {
    uVar15 = me7_lookup_1d_word(0x3cd4,8,uRam302ac0);
  }
  else {
    uVar15 = me7_lookup_1d_word(0x3c82,8,uRam302ac0);
  }
  iVar7 = CONCAT22(MDH,MDL);
  if ((uRam00fd52 & 0x2000) != 0) {
    egt_modeled = (byte)((ushort)uVar15 >> 8);
    uRam00fd52 = uRam00fd52 & 0xdfff;
    uRam3052f6 = uVar15;
  }
  if ((_flags_start_phase & 0x4000) == 0) {
    bRam301641 = bRam301641 & 0xdf;
  }
  else {
    bRam301641 = bRam301641 | 0x20;
  }
  if ((bRam019f46 & 1) == 0) {
    if ((egt_modeled < bRam019fdd) || (bRam30183b <= bRam019fee)) {
      bRam301636 = bRam301636 & 0xfe;
    }
    else if (bRam019fde < egt_modeled) {
      bRam301636 = bRam301636 | 1;
    }
  }
  else if (((egt_modeled < bRam019fdd) || (bRam30183b <= bRam019fee)) || ((bRam301641 & 0x20) != 0))
  {
    bRam301636 = bRam301636 & 0xfe;
  }
  else if ((bRam019fde < egt_modeled) && ((_flags_start_phase & 0x8000) != 0)) {
    bRam301636 = bRam301636 | 1;
  }
  bRam301637 = bRam301637 | 1;
  if ((uRam00fd0e & 0x1000) == 0) {
    bRam301641 = bRam301641 & 0xf7;
  }
  else {
    bRam301641 = bRam301641 | 8;
  }
  if ((bRam301641 & 8) == 0) {
    uRam302aca = 0;
    bRam30163e = bRam30163e & 0xfd;
  }
  else if (uRam302aca < uRam023c70) {
    uRam302aca = uRam302aca + 1;
  }
  else {
    bRam30163e = bRam30163e | 2;
  }
  if (((bRam301641 & 8) != 0) && ((bRam301640 & 8) == 0)) {
    bRam304977 = bRam304978;
    if (bRam304975 <= bRam304978) {
      bRam304977 = bRam304975;
    }
    uVar18 = (ushort)bRam304977;
    uRam302ae2 = uVar18 << 10;
    uRam302ae4 = (ushort)(uVar18 < 0x40) * -0x400 | uVar18 - 0x40 >> 6;
  }
  if ((uRam00fd16 & 0x20) == 0) {
    if (((uRam00fd52 & 0x1000) == 0) && ((bRam301641 & 0x20) == 0)) {
      bRam301640 = bRam301640 & 0xfd;
    }
    else {
      bRam301640 = bRam301640 | 2;
    }
    if (((bRam301640 & 2) == 0) && ((bRam30163c & 8) != 0)) {
      uVar18 = me7_lookup_1d_byte(0x1fe5,6,bRam304975);
      iVar7 = (uint)(uVar18 & 0xff) * 0xc800;
      MDC = MDC | 0x10;
      sRam3052f4 = (short)((uint)iVar7 >> 8);
      iRam302ade = iVar7;
    }
    else if ((((flags_torque_revlimit & 0x80) == 0) &&
             (iVar7 = CONCAT22(MDH,MDL), iRam302ade = CONCAT22(iRam302ade._2_2_,(ushort)iRam302ade),
             (_flags_start_phase & 0x8000) != 0)) &&
            (iVar7 = CONCAT22(MDH,MDL), iRam302ade = CONCAT22(iRam302ade._2_2_,(ushort)iRam302ade),
            (bRam301641 & 8) != 0)) {
      uVar18 = me7_lookup_1d_byte(0x1f49,6,bRam304970);
      uVar18 = uVar18 & 0xff;
      if (sRam3052f4 == 0) {
        sRam3052f4 = 0;
        iVar7 = CONCAT22(MDH,MDL);
        iRam302ade = CONCAT22(iRam302ade._2_2_,(ushort)iRam302ade);
      }
      else {
        if (iRam302ade._2_2_ == 0 && (iRam302ade._2_2_ != 0 || (ushort)iRam302ade <= uVar18)) {
          iRam302ade._0_2_ = 0;
          iRam302ade._2_2_ = 0;
        }
        else {
          bVar1 = (ushort)iRam302ade < uVar18;
          iRam302ade._0_2_ = (ushort)iRam302ade - uVar18;
          iRam302ade._2_2_ = iRam302ade._2_2_ - bVar1;
        }
        if (iRam302ade._2_2_ < 0x100) {
          sRam3052f4 = CONCAT11((char)iRam302ade._2_2_,(char)((ushort)iRam302ade >> 8));
          iVar7 = CONCAT22(MDH,MDL);
          iRam302ade = CONCAT22(iRam302ade._2_2_,(ushort)iRam302ade);
        }
        else {
          sRam3052f4 = -1;
          iVar7 = CONCAT22(MDH,MDL);
          iRam302ade = CONCAT22(iRam302ade._2_2_,(ushort)iRam302ade);
        }
      }
    }
  }
  else {
    sRam3052f4 = 0;
    iVar7 = CONCAT22(MDH,MDL);
    iRam302ade = CONCAT22(iRam302ade._2_2_,(ushort)iRam302ade);
  }
  MDH = (short)((uint)iVar7 >> 0x10);
  MDL = (short)iVar7;
  if (sRam3052f4 == 0) {
    bRam301640 = bRam301640 | 1;
  }
  bVar9 = func_0x040b3e(0x3e82,bRam304975);
  uVar6 = CONCAT22(MDH,MDL);
  uVar8 = CONCAT22(MDH,MDL);
  if ((((bRam301640 & 1) != 0) && ((bRam30163c & 1) == 0)) &&
     (((uRam00fd52 & 0x1000) == 0 && (((bRam301641 & 8) != 0 && (egt_modeled < bVar9)))))) {
    bRam30163d = bRam30163d | 0x20;
  }
  if (bRam019fd8 < egt_modeled) {
    bRam30163d = bRam30163d | 4;
  }
  else {
    bRam30163d = bRam30163d & 0xfb;
  }
  if (bRam304975 < bRam019fd7) {
    sStack_14 = (ushort)egt_modeled - (ushort)bRam304975;
    if ((ushort)egt_modeled < (ushort)bRam304975) {
      if (sStack_14 >= 0) {
        sStack_14 = -0x8000;
      }
    }
    else if (sStack_14 < 0) {
      sStack_14 = 0x7fff;
    }
    if (sStack_14 < 0) {
      sStack_14 = -sStack_14;
    }
    if (sStack_14 == 0xff ||
        sStack_14 + -0xff < 0 != (sStack_14 < 0 && sStack_14 + -0xff < 0 != sStack_14 < 0)) {
      bStack_16 = (byte)sStack_14;
    }
    else {
      bStack_16 = 0xff;
    }
    if (bRam304715 < bRam019f5f) {
      uRam022ad4 = uRam023c72;
      bRam301644 = bRam301644 & 0xfd;
    }
    else if (sRam302ad4 == 0) {
      bRam301644 = bRam301644 | 2;
    }
    else {
      sRam302ad4 = sRam302ad4 + -1;
    }
    if ((((bRam301644 & 2) == 0) || (bRam019f48 < bStack_16)) || (bRam019fd7 <= egt_modeled)) {
      bRam30163d = bRam30163d & 0xf7;
    }
    else {
      bRam30163d = bRam30163d | 8;
    }
  }
  else if (egt_modeled < bRam019fd7) {
    bRam30163d = bRam30163d | 8;
  }
  else {
    bRam30163d = bRam30163d & 0xf7;
  }
  if (((bRam30163d & 4) == 0) && ((bRam30163d & 8) == 0)) {
    bRam30496d = bRam30496d & 0xfd;
  }
  else {
    bRam30496d = bRam30496d | 2;
  }
  if ((((bRam301641 & 8) == 0) || ((bRam30163d & 8) != 0)) ||
     (((uRam00fd52 & 0x1000) != 0 || (bRam019fd8 < egt_modeled)))) {
LAB_094ae0:
    bRam30163e = bRam30163e & 0xbf;
  }
  else {
    bVar10 = bRam304977 + bRam019f5a;
    if ((byte)(bRam304977 + bRam019f5a) < bRam304977 || (byte)(bRam304977 + bRam019f5a) < bRam019f5a
       ) {
      bVar10 = 0xff;
    }
    if (egt_modeled <= bVar10) {
      bVar10 = bRam304977 - bRam019f59;
      if (bRam304977 < bRam019f59) {
        bVar10 = 0;
      }
      if (bVar10 <= egt_modeled) goto LAB_094ae0;
    }
    if ((bRam301637 & 1) == 0) goto LAB_094ae0;
    bRam30163e = bRam30163e | 0x40;
  }
  if ((bRam30163e & 0x40) == 0) {
    bRam301636 = bRam301636 & 0xf7;
  }
  else {
    bRam301636 = bRam301636 | 8;
  }
  if (((((bRam30163d & 4) == 0) && ((bRam30163d & 8) == 0)) && ((bRam30163d & 0x20) == 0)) &&
     ((bRam30163d & 0x10) == 0)) {
    bRam30163c = bRam30163c & 0xdf;
    uRam022ac2 = uRam023c66;
    if (sRam302ac4 == 0) {
      bRam30163c = bRam30163c | 0x10;
    }
    else {
      sRam302ac4 = sRam302ac4 + -1;
    }
  }
  else {
    bRam30163c = bRam30163c & 0xef;
    uRam022ac4 = uRam023c66;
    if (sRam302ac2 == 0) {
      bRam30163c = bRam30163c | 0x20;
    }
    else {
      sRam302ac2 = sRam302ac2 + -1;
    }
  }
  if ((((bRam30163d & 4) == 0) && ((bRam30163d & 8) == 0)) &&
     ((((bRam30163d & 0x20) == 0 && ((bRam30163d & 0x10) == 0)) &&
      ((((bRam30163e & 0x40) == 0 || ((bRam301636 & 0x20) == 0)) && ((uRam303bea & 1) == 0)))))) {
    bRam301643 = bRam301643 & 0xef;
  }
  else {
    bRam301643 = bRam301643 | 0x10;
  }
  if ((_flags_start_phase & 0x8000) == 0) {
    bRam30163c = bRam30163c & 0xfd;
    uRam022ac8 = uRam023c60;
  }
  else if (sRam302ac8 == 0) {
    bRam30163c = bRam30163c | 2;
  }
  else {
    sRam302ac8 = sRam302ac8 + -1;
  }
  if ((uRam303bd6 & 1) == 0) {
    bRam301640 = bRam301640 & 0xfb;
  }
  else if ((bRam301641 & 0x20) == 0) {
    bRam301640 = bRam301640 & 0xfb;
  }
  else {
    bRam301640 = bRam301640 | 4;
  }
  bRam301645 = bRam019fd5;
  if (bRam019fd5 <= bVar9) {
    bRam301645 = bVar9;
  }
  if ((((bRam301640 & 4) == 0) || ((bRam30163d & 2) != 0)) &&
     (((uRam3055d0 == 0 || (((bRam30163e & 1) != 0 || (bRam019f47 == 0)))) &&
      (((bRam30163e & 2) == 0 || ((bRam30163e & 4) != 0)))))) {
    bVar10 = bRam304971;
    if ((bRam301641 & 8) != 0) {
      bVar9 = func_0x040b3e(0x3e82,bRam304979);
      uVar6 = CONCAT22(MDH,MDL);
      bVar10 = bVar9;
      if (bVar9 <= bRam019fd5) {
        bVar10 = bRam019fd5;
      }
      if ((bRam30163c & 2) == 0) {
        cVar12 = '\0';
      }
      else {
        cVar12 = func_0x042596(uRam023b96,0x3b98,8,uRam023b97,0x3b9d,8,0x3ba1,8,bRam304970,
                               bRam304971);
        uVar18 = MDC;
        uVar6 = (int)(short)cVar12 * (int)(short)(ushort)bRam30496f;
        MDH = (short)uVar6;
        MDC = MDC | 0x10;
        if (MDH == 0x3fff || MDH + -0x3fff < 0 != (MDH < 0 && MDH + -0x3fff < 0 != MDH < 0)) {
          if (MDH + 0x407f < 0 == (-1 < MDH && MDH + 0x407f < 0 != MDH < 0)) {
            MDL = MDH / 0x80;
            MDH = MDH % 0x80;
            uVar6 = CONCAT22(MDH,MDL);
            MDC = uVar18 | 0x10;
            cVar12 = (char)MDL;
          }
          else {
            cVar12 = -0x80;
          }
        }
        else {
          cVar12 = '\x7f';
        }
      }
      uStack_20 = (ushort)cVar12;
      uStack_1e = (short)uStack_20 >> 0xf;
      if (((bVar10 <= bRam304971) && (uStack_20 != 0 && -1 < (short)uStack_1e)) ||
         ((bRam304971 == 0 && ((short)uStack_1e < 0)))) {
        uStack_20 = 0;
        uStack_1e = 0;
      }
      bVar1 = uStack_20 + uRam302ae6 < uStack_20;
      bVar2 = uStack_20 + uRam302ae6 < uRam302ae6;
      uVar18 = (ushort)(bVar1 || bVar2);
      uRam302ae6 = uStack_20 + uRam302ae6;
      uVar19 = uStack_1e + uRam302ae8;
      bVar5 = (short)uRam302ae8 < 0;
      uRam302ae8 = uStack_1e + uRam302ae8 + uVar18;
      if ((short)uStack_1e < 0 == bVar5 && (short)(uVar19 + uVar18) < 0 != (short)uStack_1e < 0) {
        if (uVar19 < uStack_1e || uVar19 == 0xffff && (bVar1 || bVar2)) {
          uRam302ae6 = 0;
          uRam302ae8 = 0x8000;
        }
        else {
          uRam302ae6 = 0xffff;
          uRam302ae8 = 0x7fff;
        }
      }
      if ((short)(uRam302ae8 + 1) < 0 ==
          (-1 < (short)uRam302ae8 && (short)(uRam302ae8 + 1) < 0 != (short)uRam302ae8 < 0)) {
        uVar18 = (ushort)(uRam302ae6 < 0xfc00);
        if (uRam302ae8 - 2 == uVar18 && uRam302ae6 == 0xfc00 ||
            (short)((uRam302ae8 - 2) - uVar18) < 0 !=
            ((short)uRam302ae8 < 0 &&
            (short)((uRam302ae8 - 2) - (ushort)(uRam302ae6 < 0xfc00)) < 0 != (short)uRam302ae8 < 0))
        {
          bRam304971 = ((byte)(uRam302ae6 >> 10) | (byte)(uRam302ae8 << 6)) + 0x40;
        }
        else {
          bRam304971 = 0xff;
        }
      }
      else {
        bRam304971 = 0;
      }
      if (bRam304971 <= bVar10) {
        bVar10 = bRam304971;
      }
    }
  }
  else {
    bStack_1c = bRam019fd4;
    if (((bRam019f47 == 0) || (((uRam00fd60 & 0x10) == 0 && ((bRam019f47 & 1) != 0)))) ||
       (((bRam019f47 & 1) == 0 && ((uRam303bd6 & 1) != 0)))) {
      if ((uRam303bd6 & 1) == 0) {
        if (bRam019fd4 <= bRam301626) {
          bStack_1c = bRam301626;
        }
      }
      else {
        bStack_1c = bRam019fd3;
        uVar8 = uVar6;
      }
    }
    else if ((bRam30163e & 2) == 0) {
      bStack_1c = me7_lookup_1d_word(0x3c74,8,uRam3055d0);
      uVar8 = CONCAT22(MDH,MDL);
    }
    else {
      if ((uRam303bd6 & 1) == 0) {
        if (bRam019fd4 <= bRam301626) {
          bStack_1c = bRam301626;
        }
      }
      else {
        bStack_1c = bRam019fd3;
      }
      uVar18 = (ushort)bRam303270 - (ushort)bStack_1c;
      if ((ushort)bRam303270 < (ushort)bStack_1c) {
        if ((short)uVar18 >= 0) {
          uVar18 = 0x8000;
        }
      }
      else if ((short)uVar18 < 0) {
        uVar18 = 0x7fff;
      }
      uVar17 = me7_lookup_1d_word(0x3b60,8,uRam3055d0);
      uVar19 = uVar18;
      if ((short)uVar18 < 0) {
        uVar19 = -uVar18;
      }
      uVar8 = (uint)uVar19 * (uint)uVar17;
      MDC = MDC | 0x10;
      if ((uVar8 & 0xc0000000) == 0) {
        uVar19 = (short)(uVar8 >> 0x10) << 1 | (ushort)uVar8 >> 0xf;
        if ((short)uVar18 < 0) {
          uVar19 = -uVar19;
        }
      }
      else if ((short)uVar18 < 0) {
        uVar19 = 0x8000;
      }
      else {
        uVar19 = 0x7fff;
      }
      sVar16 = bRam303270 - uVar19;
      if ((short)uVar19 < 0 && (short)(bRam303270 - uVar19) < 0) {
        sVar16 = -0x8000;
      }
      if (sVar16 < 0) {
        bStack_1c = 0;
      }
      else if (sVar16 == 0xff ||
               sVar16 + -0xff < 0 != (sVar16 < 0 && sVar16 + -0xff < 0 != sVar16 < 0)) {
        bStack_1c = (byte)sVar16;
      }
      else {
        bStack_1c = 0xff;
      }
    }
    bVar10 = bRam019fd5;
    if (bStack_1c <= bRam019fd5) {
      bVar10 = bStack_1c;
    }
    uVar18 = (ushort)bVar10;
    uRam302ae6 = uVar18 << 10;
    uRam302ae8 = (ushort)(uVar18 < 0x40) * -0x400 | uVar18 - 0x40 >> 6;
    uVar6 = uVar8;
  }
  bRam304971 = bVar10;
  MDH = (short)(uVar6 >> 0x10);
  MDL = (short)uVar6;
  if (bRam304971 < bRam305645) {
    bRam30496d = bRam30496d & 0xfe;
  }
  else {
    bRam30496d = bRam30496d | 1;
  }
  if ((bRam301643 & 0x10) == 0) {
    bRam304976 = egt_modeled;
  }
  else {
    bRam304976 = bRam304971;
  }
  sRam302ace = me7_fraction_blend(0xa0a,bRam304976,uRam306ace);
  rpmclass_oppoint = (byte)((ushort)sRam302ace >> 8);
  if ((_flags_start_phase & 0x4000) != 0) {
    bRam30163d = bRam30163d | 1;
    uRam019646 = uRam019fe3;
  }
  if (((bRam30163d & 1) == 0) || (bRam019fdc <= bRam304976)) {
LAB_0950c4:
    uRam00fd52 = uRam00fd52 & 0xf7ff;
  }
  else {
    bVar10 = bRam304976 + bRam019f5c;
    if ((byte)(bRam304976 + bRam019f5c) < bRam304976 || (byte)(bRam304976 + bRam019f5c) < bRam019f5c
       ) {
      bVar10 = 0xff;
    }
    if (((bRam304979 < bVar10) || ((bRam301643 & 0x10) != 0)) || ((bRam301644 & 0x10) != 0))
    goto LAB_0950c4;
    uRam00fd52 = uRam00fd52 | 0x800;
  }
  if ((bRam304979 < bRam304976) || ((bRam30163d & 1) == 0)) {
    uRam00fd52 = uRam00fd52 & 0xefff;
  }
  else if ((uRam00fd52 & 0x800) != 0) {
    uRam00fd52 = uRam00fd52 | 0x1000;
  }
  if (((bRam301641 & 0x20) != 0) && ((bRam30163c & 4) == 0)) {
    bRam30563a = bRam304976;
    bRam304979 = bRam304976;
    bRam304975 = egt_modeled;
    sRam302ace = (ushort)bRam304976 << 8;
  }
  if ((uRam00fd52 & 0x800) != 0) {
    bRam304975 = egt_modeled;
    bRam304979 = rpmclass_oppoint;
  }
  if ((bRam019f45 & 8) == 0) goto LAB_09556c;
  if ((bRam301636 & 0x40) == 0) {
    bRam301643 = bRam301643 & 0xfe;
  }
  else {
    bRam301643 = bRam301643 | 1;
  }
  if (bRam304971 < bRam019fd9) {
    uRam3052f8 = 0;
    uRam3052fa = 0;
    uRam01964a = uRam019fce;
    bRam301642 = bRam301642 & 0xbf;
    bRam301636 = bRam301636 & 0xbf;
  }
  else {
    if ((bRam019ff0 < vfzg_class) && (vfzg_class < bRam019fef)) {
      bRam301642 = bRam301642 | 4;
    }
    else {
      bRam301642 = bRam301642 & 0xfb;
    }
    bVar10 = me7_lookup_1d_byte(0x1fb5,6,vfzg_class);
    if (bVar10 < bRam304970) {
      bVar10 = me7_lookup_1d_byte(0x1f9f,6,vfzg_class);
      if (bVar10 <= bRam304970) goto LAB_0951fa;
      bRam301642 = bRam301642 | 0x10;
    }
    else {
LAB_0951fa:
      bRam301642 = bRam301642 & 0xef;
    }
    if (((flags_torque_revlimit & 0x80) == 0) &&
       (((bRam301642 & 4) == 0 || ((bRam301642 & 0x10) == 0)))) {
      if ((bRam301642 & 0x40) != 0) {
        if (cRam30164a == '\0') {
          uRam3052f8 = 0;
        }
        else {
          cRam30164a = cRam30164a + -1;
          uRam3052f8 = uRam3052f8 + 1;
        }
      }
    }
    else {
      uRam01964a = uRam019fce;
      if (uRam023d28 < uRam3052f8) {
        uRam3052fa = 0;
        bRam301642 = bRam301642 & 0xbf;
        bRam301636 = bRam301636 & 0xbf;
      }
      else {
        bRam301642 = bRam301642 | 0x40;
        uRam3052fa = uRam3052fa + 1;
        if (((uRam023d2a < uRam3052fa) && (bRam019fe2 <= bRam304975)) && (bRam304975 <= bRam019fe1))
        {
          bRam301636 = bRam301636 | 0x40;
        }
        else {
          bRam301636 = bRam301636 & 0xbf;
        }
      }
    }
    if ((uRam023d28 < uRam3052f8) || (cRam30164a == '\0')) {
      uRam3052fa = 0;
      uRam3052f8 = 0;
      bRam301642 = bRam301642 & 0xbf;
      bRam301636 = bRam301636 & 0xbf;
    }
  }
  if ((bRam301636 & 0x80) == 0) {
    bRam301643 = bRam301643 & 0xfd;
  }
  else {
    bRam301643 = bRam301643 | 2;
  }
  if (bRam304971 < bRam019fd9) {
    uRam3052fc = 0;
    uRam3052fe = 0;
    uRam01964b = uRam019fce;
    bRam301642 = bRam301642 & 0x7f;
    bRam301636 = bRam301636 & 0x7f;
  }
  else {
    if ((vfzg_class < bRam019ff2) || (bRam019ff1 < vfzg_class)) {
      bRam301642 = bRam301642 & 0xf7;
    }
    else {
      bRam301642 = bRam301642 | 8;
    }
    bVar10 = me7_lookup_1d_byte(0x1fc0,6,vfzg_class);
    if (bVar10 < bRam304970) {
      bVar10 = me7_lookup_1d_byte(0x1faa,6,vfzg_class);
      if (bVar10 <= bRam304970) goto LAB_0953ba;
      bRam301642 = bRam301642 | 0x20;
    }
    else {
LAB_0953ba:
      bRam301642 = bRam301642 & 0xdf;
    }
    if (((bRam301642 & 8) == 0) || ((bRam301642 & 0x20) == 0)) {
      if ((bRam301642 & 0x80) != 0) {
        if (cRam30164b == '\0') {
          uRam3052fc = 0;
        }
        else {
          cRam30164b = cRam30164b + -1;
          uRam3052fc = uRam3052fc + 1;
        }
      }
    }
    else {
      uRam01964b = uRam019fce;
      if (uRam023d2c < uRam3052fc) {
        uRam3052fe = 0;
        bRam301642 = bRam301642 & 0x7f;
        bRam301636 = bRam301636 & 0x7f;
      }
      else {
        bRam301642 = bRam301642 | 0x80;
        uRam3052fe = uRam3052fe + 1;
        if (((uRam023d2e < uRam3052fe) && (bRam019fe2 <= bRam304975)) && (bRam304975 <= bRam019fe1))
        {
          bRam301636 = bRam301636 | 0x80;
        }
        else {
          bRam301636 = bRam301636 & 0x7f;
        }
      }
    }
    if ((uRam023d2c < uRam3052fc) || (cRam30164b == '\0')) {
      uRam3052fe = 0;
      uRam3052fc = 0;
      bRam301642 = bRam301642 & 0x7f;
      bRam301636 = bRam301636 & 0x7f;
    }
  }
  if ((((bRam301643 & 1) == 0) && ((bRam301636 & 0x40) != 0)) && (bRam30496b != 0xff)) {
    bRam30496b = bRam30496b + 1;
  }
  if ((((bRam301643 & 2) == 0) && ((bRam301636 & 0x80) != 0)) && (bRam30496c != 0xff)) {
    bRam30496c = bRam30496c + 1;
  }
  if ((bRam30496b < bRam019f42) || (bRam30496c < bRam019f43)) {
    bRam301639 = bRam301639 & 0xfb;
  }
  else {
    bRam301639 = bRam301639 | 4;
  }
LAB_09556c:
  if ((bRam019f45 & 2) == 0) {
    bRam301636 = bRam301636 & 0xfd | 4;
    bRam301643 = bRam301643 & 0x5f;
  }
  else {
    if ((bRam019f45 & 4) == 0) {
      bRam301636 = bRam301636 & 0xfd;
    }
    else {
      if ((bRam301640 & 0x10) == 0) {
        bRam301640 = bRam301640 & 0xdf;
      }
      else {
        bRam301640 = bRam301640 | 0x20;
      }
      if ((uRam00fd3a & 0x200) == 0) {
        uRam019647 = uRam019fd1;
        bRam301640 = bRam301640 & 0xef;
      }
      else if (cRam301647 == '\0') {
        bRam301640 = bRam301640 | 0x10;
      }
      else {
        cRam301647 = cRam301647 + -1;
      }
      if ((((bRam301640 & 0x20) == 0) && ((bRam301640 & 0x10) != 0)) &&
         (((bRam30163d & 4) == 0 &&
          (((((uRam00fd52 & 0x1000) == 0 && ((bRam30174c & 1) != 0)) && ((DAT_00fd4e & 0x100) == 0))
           && ((uRam023c5e <= uRam3055d0 && (bRam019fd2 < bRam30a026)))))))) {
        bVar10 = bRam30a026 - egt_modeled;
        if (bRam30a026 < egt_modeled) {
          bVar10 = 0;
        }
        if (bVar10 < bRam019f58) {
          bRam301636 = bRam301636 | 2;
          bRam301639 = bRam301639 | 1;
          bRam301638 = bRam301638 & 0xdf;
        }
        else {
          bRam301636 = bRam301636 & 0xfd;
          bRam301638 = bRam301638 | 0x20;
          bRam301639 = bRam301639 & 0xfe;
        }
      }
      else if ((egt_modeled <= bRam019fd2) && (bRam30a026 <= bRam019fd2)) {
        bRam301636 = bRam301636 & 0xfd;
        bRam301638 = bRam301638 | 0x20;
        bRam301639 = bRam301639 & 0xfe;
      }
    }
    if ((bRam019f45 & 8) == 0) {
      bRam301643 = bRam301643 & 0x7f;
    }
    else {
      if ((_flags_start_phase & 0x8000) != 0) {
        if (bRam304972 < egt_modeled) {
          bRam304972 = egt_modeled;
        }
        if (egt_modeled < bRam304973) {
          bRam304973 = egt_modeled;
        }
      }
      bVar11 = me7_lookup_1d_byte(0x1f7a,6,egt_modeled);
      bVar10 = bRam304972 - bRam304973;
      if (bRam304972 < bRam304973) {
        bVar10 = 0;
      }
      if (bVar11 < bVar10) {
        if ((bRam301639 & 4) == 0) {
          bRam301638 = bRam301638 & 0x7f;
          bRam301639 = bRam301639 & 0xfd;
        }
        else {
          bRam301638 = bRam301638 | 0x80;
          bRam301639 = bRam301639 & 0xfd;
        }
      }
      else {
        if ((bRam301639 & 4) == 0) {
          bRam301639 = bRam301639 & 0xfd;
        }
        else if ((((bRam30163d & 4) == 0) && ((bRam30163d & 8) == 0)) && ((uRam303c1e & 1) == 0)) {
          bRam301639 = bRam301639 | 2;
        }
        else {
          bRam301639 = bRam301639 & 0xfd;
        }
        bRam301638 = bRam301638 & 0x7f;
      }
      if ((bRam301639 & 2) == 0) {
        bRam301643 = bRam301643 & 0x7f;
      }
      else {
        bRam301643 = bRam301643 | 0x80;
      }
    }
    if ((_flags_start_phase & 0x8000) == 0) {
      if ((uRam303bea & 1) == 0) {
        bRam00e195 = egt_modeled;
        if (egt_modeled < bRam019fdb) {
          bRam00e195 = bRam019fdb;
          uRam302aea = CONCAT22(uRam302aea._2_2_,(undefined2)uRam302aea);
        }
      }
      else {
        bRam01a195 = bRam019fdb;
        uRam302aea = CONCAT22(uRam302aea._2_2_,(undefined2)uRam302aea);
      }
    }
    else {
      if ((flags_torque_revlimit & 0x80) == 0) {
        uVar15 = func_0x0435b4(0x3bf6,8,bRam00f472,bRam00e195,(bRam019fdb - 0x40) * 0x80,0,
                               (bRam019fda - 0x40) * 0x80,0);
        uRam302aea = func_0x0430da(0x199a,uVar15,uRam302aea._2_2_,(undefined2)uRam302aea);
      }
      else {
        uVar15 = func_0x04274a(uRam023c40,0x3c42,8,0x3c4c,8,bRam00e195,(bRam019fdb - 0x40) * 0x80,0,
                               (bRam019fda - 0x40) * 0x80,0);
        uRam302aea = func_0x0430da(0x199a,uVar15,uRam302aea._2_2_,(undefined2)uRam302aea);
      }
      uVar18 = (ushort)((int)uRam302aea >> 0x17);
      if ((short)uVar18 < 0) {
        bRam00e195 = (char)uVar18 + 0x40;
        if (uVar18 <= uVar18 + 0x40 && 0x3f < uVar18 + 0x40) {
          bRam00e195 = 0;
        }
      }
      else {
        bRam00e195 = (char)uVar18 + 0x40;
        if (uVar18 + 0x40 < uVar18 || uVar18 + 0x40 < 0x40) {
          bRam00e195 = 0xff;
        }
      }
    }
    if ((bRam019fcc < nmot_rpmclass) && (bRam019f5d < bRam304715)) {
      if ((((bRam019f44 & 2) == 0) || ((uRam303b7e & 1) == 0)) &&
         (((bRam019f44 & 4) == 0 || ((uRam303b80 & 1) == 0)))) {
        bRam301643 = bRam301643 & 0xf7;
        uRam022ad8 = uRam023c6a;
      }
      else if (sRam302ad8 == 0) {
        bRam301643 = bRam301643 | 8;
      }
      else {
        sRam302ad8 = sRam302ad8 + -1;
        bRam301643 = bRam301643 & 0xf7;
      }
      if ((((uRam303b9c & 1) == 0) && ((uRam303b5c & 1) == 0)) && ((bRam301643 & 8) == 0)) {
        bRam301638 = bRam301638 | 1;
      }
      else {
        bRam301638 = bRam301638 & 0xfe;
      }
    }
    else {
      bRam301638 = bRam301638 & 0xfe;
    }
    uVar19 = (ushort)bRam00e195;
    uVar17 = me7_lookup_2d_byte(0x1f60,6,vfzg_class,uRam30497a);
    uVar17 = uVar17 & 0xff;
    uVar18 = uVar17 + uVar19;
    if (uVar17 + uVar19 < uVar17 || uVar17 + uVar19 < uVar19) {
      uVar18 = 0xffff;
    }
    uVar19 = uVar18 - 0x40;
    if (uVar18 < 0x40) {
      uVar19 = 0;
    }
    if (uVar19 < 0x100) {
      bStack_12 = (byte)uVar19;
      bRam00e194 = bStack_12;
    }
    else {
      bRam00e194 = 0xff;
    }
    bVar10 = egt_modeled - bRam019f5b;
    if (egt_modeled < bRam019f5b) {
      bVar10 = 0;
    }
    if (((bRam019fdb < bVar10) && ((bRam301638 & 1) != 0)) && (bRam00e194 < bVar10)) {
      if (sRam302ada == 0) {
        bRam301638 = bRam301638 | 8;
      }
      else {
        sRam302ada = sRam302ada + -1;
        bRam301638 = bRam301638 & 0xf7;
      }
    }
    else {
      bRam301638 = bRam301638 & 0xf7;
      uRam022ada = uRam023c6c;
    }
    if ((bRam019fdb < bVar10) || ((bRam301638 & 1) == 0)) {
      bRam301638 = bRam301638 & 0xef;
      uRam022adc = uRam023c6e;
    }
    else if (sRam302adc == 0) {
      bRam301638 = bRam301638 | 0x10;
    }
    else {
      sRam302adc = sRam302adc + -1;
      bRam301638 = bRam301638 & 0xef;
    }
    if ((bRam301638 & 0x10) == 0) {
      if ((bRam301638 & 8) != 0) {
        bRam301638 = bRam301638 & 0xbf | 4;
      }
    }
    else {
      bRam301638 = bRam301638 & 0xfb | 0x40;
    }
    if (((bRam019f44 & 1) == 0) || (((bRam019f44 & 1) != 0 && ((bRam301638 & 0x40) != 0)))) {
      bRam301644 = bRam301644 | 8;
    }
    else {
      bRam301644 = bRam301644 & 0xf7;
    }
    if (((((bRam019f44 & 1) == 0) || ((bRam30163d & 8) != 0)) || ((bRam30163d & 4) != 0)) ||
       (((uRam303c1e & 1) != 0 || ((bRam301638 & 4) == 0)))) {
      bRam301643 = bRam301643 & 0xdf;
    }
    else {
      bRam301643 = bRam301643 | 0x20;
    }
    if ((bRam019f45 & 4) == 0) {
      if ((bRam019f45 & 8) == 0) {
        if ((bRam301644 & 8) == 0) {
          bRam301636 = bRam301636 & 0xfb;
        }
        else {
          bRam301636 = bRam301636 | 4;
        }
      }
      else if (((bRam301644 & 8) == 0) || ((bRam301638 & 0x80) == 0)) {
        bRam301636 = bRam301636 & 0xfb;
      }
      else {
        bRam301636 = bRam301636 | 4;
      }
    }
    else if ((bRam019f45 & 8) == 0) {
      if (((bRam301644 & 8) == 0) || ((bRam301638 & 0x20) == 0)) {
        bRam301636 = bRam301636 & 0xfb;
      }
      else {
        bRam301636 = bRam301636 | 4;
      }
    }
    else if ((((bRam301644 & 8) == 0) || ((bRam301638 & 0x20) == 0)) || ((bRam301638 & 0x80) == 0))
    {
      bRam301636 = bRam301636 & 0xfb;
    }
    else {
      bRam301636 = bRam301636 | 4;
    }
  }
  if ((((((bRam301643 & 0x20) == 0) && ((bRam301636 & 2) == 0)) && ((bRam301636 & 8) == 0)) &&
      ((bRam301643 & 0x80) == 0)) || ((bRam301636 & 0x20) == 0)) {
    bRam30163d = bRam30163d & 0xef;
  }
  else {
    bRam30163d = bRam30163d | 0x10;
  }
  if (((((bRam30163c & 0x10) == 0) || (egt_modeled < bVar9)) ||
      (((bRam301640 & 1) == 0 || (((bRam301636 & 4) == 0 || ((bRam301636 & 0x20) == 0)))))) ||
     ((uRam00fd0e & 0x1000) == 0)) {
    if ((bRam30163c & 0x20) == 0) {
      bRam301644 = bRam301644 & 0xef;
    }
    else {
      bRam301644 = bRam301644 | 0x10;
    }
    bRam301643 = bRam301643 & 0xbf;
  }
  else {
    bRam301644 = bRam301644 & 0xef;
    bRam301643 = bRam301643 | 0x40;
  }
  if (bRam304975 < bRam019fd7) {
    if (((((bRam30163d & 4) == 0) && ((bRam30163d & 8) == 0)) && ((bRam301644 & 2) != 0)) &&
       ((bRam301637 & 1) != 0)) {
      if (sRam302ad6 == 0) {
        bRam301644 = bRam301644 | 4;
      }
      else {
        sRam302ad6 = sRam302ad6 + -1;
      }
    }
    else {
      uRam022ad6 = uRam023c68;
      bRam301644 = bRam301644 & 0xfb;
    }
  }
  else if ((((bRam30163d & 4) == 0) && ((bRam30163d & 8) == 0)) && ((bRam301637 & 1) != 0)) {
    if (sRam302ad6 == 0) {
      bRam301644 = bRam301644 | 4;
    }
    else {
      sRam302ad6 = sRam302ad6 + -1;
    }
  }
  else {
    uRam022ad6 = uRam023c68;
    bRam301644 = bRam301644 & 0xfb;
  }
  if ((bRam301644 & 0x10) == 0) {
    if ((bRam301644 & 4) != 0) {
      uStack_22 = ((uVar3 & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
    }
  }
  else if ((bRam30163d & 4) == 0) {
    if ((bRam30163d & 8) != 0) {
      uStack_22 = (uVar3 >> 8 & 0x90 | 0x62) << 8 | 2;
    }
  }
  else {
    uStack_22 = (uVar3 >> 8 & 0x90 | 0x61) << 8 | 2;
  }
  if ((bRam301644 & 0x10) == 0) {
    if ((bRam301643 & 0x40) != 0) {
      uStack_24 = ((uVar4 & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
    }
  }
  else if ((bRam301643 & 0x20) == 0) {
    if ((bRam301636 & 8) == 0) {
      if (((bRam301636 & 2) == 0) && ((bRam301643 & 0x80) == 0)) {
        if ((bRam30163d & 0x20) != 0) {
          uStack_24 = (uVar4 >> 8 & 0x90 | 100) << 8 | 2;
        }
      }
      else {
        uStack_24 = (uVar4 >> 8 & 0x90 | 0x68) << 8 | 2;
      }
    }
    else {
      uStack_24 = (uVar4 >> 8 & 0x90 | 0x62) << 8 | 2;
    }
  }
  else {
    uStack_24 = (uVar4 >> 8 & 0x90 | 0x61) << 8 | 2;
  }
  bVar9 = func_0x040b3e(0x3e82,bRam304975);
  iVar7 = CONCAT22(MDH,MDL);
  bRam304978 = bRam019fd6;
  if (bRam019fd6 <= bVar9) {
    bRam304978 = bVar9;
  }
  if ((uRam307bf6 & 1) == 0) {
    uRam30497a = uRam30a113;
  }
  else {
    uRam30497a = uRam019fe4;
  }
  if ((uRam00fd52 & 0x1000) == 0) {
    if (sRam302ac6 == 0) {
      bRam30163c = bRam30163c & 0xbf;
    }
    else {
      sRam302ac6 = sRam302ac6 + -1;
    }
  }
  else {
    bRam30163c = bRam30163c | 0x40;
    uRam022ac6 = uRam023c60;
  }
  if ((flags_torque_revlimit & 0x80) == 0) {
    if (((bRam30163c & 0x40) == 0) && ((bRam30163c & 2) != 0)) {
      cVar13 = func_0x042596(uRam023bd6,0x3bd8,8,uRam023bd7,0x3bdd,8,0x3be1,8,bRam304970,uRam30497a)
      ;
      cVar14 = func_0x042596(uRam023bb6,0x3bb8,8,uRam023bb7,0x3bbd,8,0x3bc1,8,bRam304970,bRam304977)
      ;
      uVar3 = MDC;
      cVar12 = cVar14 + cVar13;
      if (cVar14 < '\0' == cVar13 < '\0' && (char)(cVar14 + cVar13) < '\0' != cVar14 < '\0') {
        cVar12 = '\x7f';
      }
      iVar7 = (int)(short)cVar12 * (int)(short)(ushort)bRam30496f;
      MDH = (short)iVar7;
      MDC = MDC | 0x10;
      if (MDH == 0x3fff || MDH + -0x3fff < 0 != (MDH < 0 && MDH + -0x3fff < 0 != MDH < 0)) {
        if (MDH + 0x407f < 0 == (-1 < MDH && MDH + 0x407f < 0 != MDH < 0)) {
          MDL = MDH / 0x80;
          MDH = MDH % 0x80;
          iVar7 = CONCAT22(MDH,MDL);
          MDC = uVar3 | 0x10;
          cVar12 = (char)MDL;
        }
        else {
          cVar12 = -0x80;
        }
      }
      else {
        cVar12 = '\x7f';
      }
    }
    else {
      cVar12 = '\0';
    }
  }
  else {
    cVar12 = func_0x042596(uRam023b76,0x3b78,8,uRam023b77,0x3b7d,8,0x3b81,8,bRam304970,bRam304977);
    iVar7 = CONCAT22(MDH,MDL);
  }
  MDH = (short)((uint)iVar7 >> 0x10);
  MDL = (short)iVar7;
  uStack_20 = (ushort)cVar12;
  uStack_1e = (short)uStack_20 >> 0xf;
  if (((uRam00fd52 & 0x1000) == 0) && ((bRam30163c & 0x80) != 0)) {
    bRam304977 = bRam304978;
    if (bRam304975 <= bRam304978) {
      bRam304977 = bRam304975;
    }
    uVar3 = (ushort)bRam304977;
    uRam302ae2 = uVar3 << 10;
    uRam302ae4 = (ushort)(uVar3 < 0x40) * -0x400 | uVar3 - 0x40 >> 6;
  }
  else if ((bRam301641 & 8) != 0) {
    if (((bRam304978 <= bRam304977) && (uStack_20 != 0 && -1 < (short)uStack_1e)) ||
       ((bRam304977 == 0 && ((short)uStack_1e < 0)))) {
      uStack_20 = 0;
      uStack_1e = 0;
    }
    bVar1 = uStack_20 + uRam302ae2 < uStack_20;
    bVar2 = uStack_20 + uRam302ae2 < uRam302ae2;
    uVar3 = (ushort)(bVar1 || bVar2);
    uRam302ae2 = uStack_20 + uRam302ae2;
    uVar4 = uStack_1e + uRam302ae4;
    bVar5 = (short)uRam302ae4 < 0;
    uRam302ae4 = uStack_1e + uRam302ae4 + uVar3;
    if ((short)uStack_1e < 0 == bVar5 && (short)(uVar4 + uVar3) < 0 != (short)uStack_1e < 0) {
      if (uVar4 < uStack_1e || uVar4 == 0xffff && (bVar1 || bVar2)) {
        uRam302ae2 = 0;
        uRam302ae4 = 0x8000;
      }
      else {
        uRam302ae2 = 0xffff;
        uRam302ae4 = 0x7fff;
      }
    }
    if ((short)(uRam302ae4 + 1) < 0 ==
        (-1 < (short)uRam302ae4 && (short)(uRam302ae4 + 1) < 0 != (short)uRam302ae4 < 0)) {
      uVar3 = (ushort)(uRam302ae2 < 0xfc00);
      if (uRam302ae4 - 2 == uVar3 && uRam302ae2 == 0xfc00 ||
          (short)((uRam302ae4 - 2) - uVar3) < 0 !=
          ((short)uRam302ae4 < 0 &&
          (short)((uRam302ae4 - 2) - (ushort)(uRam302ae2 < 0xfc00)) < 0 != (short)uRam302ae4 < 0)) {
        bRam304977 = ((byte)(uRam302ae2 >> 10) | (byte)(uRam302ae4 << 6)) + 0x40;
      }
      else {
        bRam304977 = 0xff;
      }
    }
    else {
      bRam304977 = 0;
    }
    if (bRam304978 < bRam304977) {
      bRam304977 = bRam304978;
    }
  }
  if (bRam019fcb < nmot_rpmclass) {
    uRam302ad0 = 0;
    if (bRam301648 < bRam019fcf) {
      bRam301648 = bRam301648 + 1;
    }
    else {
      bRam301641 = bRam301641 & 0xfd;
    }
  }
  else if (uRam302ad0 < uRam023c62) {
    uRam302ad0 = uRam302ad0 + 1;
    if (bRam301648 < bRam019fcf) {
      bRam301648 = bRam301648 + 1;
    }
    else {
      bRam301641 = bRam301641 & 0xfd;
    }
  }
  else {
    bRam301641 = bRam301641 | 2;
    bRam301648 = 0;
  }
  if (bRam019fcd < nmot_rpmclass) {
    uRam302ad2 = 0;
    if (bRam301649 < bRam019fd0) {
      bRam301649 = bRam301649 + 1;
    }
    else {
      bRam301641 = bRam301641 & 0xbf;
    }
  }
  else if (uRam302ad2 < uRam023c64) {
    uRam302ad2 = uRam302ad2 + 1;
    if (bRam301649 < bRam019fd0) {
      bRam301649 = bRam301649 + 1;
    }
    else {
      bRam301641 = bRam301641 & 0xbf;
    }
  }
  else {
    bRam301641 = bRam301641 | 0x40;
    bRam301649 = 0;
  }
  if ((((bRam301641 & 2) == 0) || (bRam304975 < bRam019fe0)) || (bRam019fdf < bRam304975)) {
    bRam301636 = bRam301636 & 0xef;
  }
  else {
    bRam301636 = bRam301636 | 0x10;
  }
  if ((bRam301641 & 0x40) == 0) {
    bRam301636 = bRam301636 & 0xdf;
  }
  else {
    bRam301636 = bRam301636 | 0x20;
  }
  if ((bRam301641 & 8) == 0) {
    bRam301640 = bRam301640 & 0xf7;
  }
  else {
    bRam301640 = bRam301640 | 8;
  }
  if ((bRam301640 & 1) == 0) {
    bRam30163c = bRam30163c & 0xfe;
  }
  else {
    bRam30163c = bRam30163c | 1;
  }
  if ((bRam301641 & 0x20) == 0) {
    bRam30163c = bRam30163c & 0xfb;
  }
  else {
    bRam30163c = bRam30163c | 4;
  }
  if ((_flags_start_phase & 0x8000) == 0) {
    bRam30163d = bRam30163d & 0x7f;
  }
  else {
    bRam30163d = bRam30163d | 0x80;
  }
  if ((bRam301640 & 2) == 0) {
    bRam30163c = bRam30163c & 0xf7;
  }
  else {
    bRam30163c = bRam30163c | 8;
  }
  if ((uRam00fd52 & 0x1000) == 0) {
    bRam30163c = bRam30163c & 0x7f;
  }
  else {
    bRam30163c = bRam30163c | 0x80;
  }
  if ((bRam301640 & 4) == 0) {
    bRam30163d = bRam30163d & 0xfd;
  }
  else {
    bRam30163d = bRam30163d | 2;
  }
  if (uRam3055d0 == 0) {
    bRam30163e = bRam30163e & 0xfe;
  }
  else {
    bRam30163e = bRam30163e | 1;
  }
  if ((bRam30163e & 2) == 0) {
    bRam30163e = bRam30163e & 0xfb;
  }
  else {
    bRam30163e = bRam30163e | 4;
  }
  func_0x0b31ac(0xb3,uStack_22);
  func_0x0b31ac(0xb5,uStack_24);
  func_0x0b8250(0x3c56,8);
  return;
}


// ================= egt_sensor_model_ch2 @ 093f2c =================

/* WARNING: Removing unreachable block (ram,0x094162) */
/* WARNING: Removing unreachable block (ram,0x094168) */
/* WARNING: Removing unreachable block (ram,0x09416a) */
/* WARNING: Removing unreachable block (ram,0x094170) */
/* WARNING: Removing unreachable block (ram,0x09416e) */
/* WARNING: Removing unreachable block (ram,0x09438c) */
/* EGT sensor model, 2nd channel */

void egt_sensor_model_ch2(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  byte extraout_RH4;
  ushort uVar5;
  ushort uVar6;
  ushort uVar7;
  
  uRam022ad4 = uRam023c72;
  uRam022acc = uRam023d26;
  uRam022ad6 = uRam023c68;
  uRam022ad8 = uRam023c6a;
  uRam022ac2 = uRam023c66;
  uRam022ac4 = uRam023c66;
  uRam022ac6 = uRam023c60;
  uRam022ac8 = uRam023c60;
  uRam019647 = uRam019fd1;
  uRam3052fa = 0;
  uRam3052fe = 0;
  uRam3052f8 = 0;
  uRam3052fc = 0;
  uRam01964a = uRam019fce;
  uRam01964b = uRam019fce;
  uRam302ac0 = uRam301948;
  me7_lookup_1d_word(0x3cd4,8,uRam301948);
  if (bRam019fde < extraout_RH4) {
    bRam301636 = bRam301636 | 1;
  }
  else {
    bRam301636 = bRam301636 & 0xfe;
  }
  if ((bRam301636 & 1) == 0) {
    PSW = PSW & 0xffbf;
  }
  else {
    PSW = PSW | 0x40;
  }
  uRam00fd8e = uRam00fd8e & 0xfffb | ((PSW & 0x40) >> 6 ^ 1) << 2;
  uRam30163b = 0x61;
  uRam3052f6 = me7_lookup_1d_word(0x3cd4,8,uRam302ac0);
  egt_modeled = (byte)((ushort)uRam3052f6 >> 8);
  bRam304975 = egt_modeled;
  if ((((bRam019f47 == 0) || (((uRam00fd60 & 0x10) == 0 && ((bRam019f47 & 1) != 0)))) ||
      (((bRam019f47 & 1) == 0 && ((uRam303bd6 & 1) != 0)))) || ((DAT_00fd4e & 0x100) != 0)) {
    if ((uRam303bd6 & 1) == 0) {
      bVar4 = bRam019fd4;
      if (bRam019fd4 <= bRam301626) {
        bVar4 = bRam301626;
      }
      uVar6 = (ushort)bVar4;
      uVar1 = CONCAT22(MDH,MDL);
    }
    else {
      uVar6 = (ushort)bRam019fd3;
      uVar1 = CONCAT22(MDH,MDL);
    }
  }
  else if ((bRam30163e & 2) == 0) {
    uVar6 = me7_lookup_1d_word(0x3c74,8,uRam3055d0);
    uVar1 = CONCAT22(MDH,MDL);
    if (0xff < uVar6) {
      uVar6 = 0xff;
      uVar1 = CONCAT22(MDH,MDL);
    }
  }
  else {
    bVar4 = bRam019fd3;
    if (((uRam303bd6 & 1) == 0) && (bVar4 = bRam019fd4, bRam019fd4 <= bRam301626)) {
      bVar4 = bRam301626;
    }
    uVar6 = (ushort)bRam303270 - (ushort)bVar4;
    if ((ushort)bRam303270 < (ushort)bVar4) {
      if ((short)uVar6 >= 0) {
        uVar6 = 0x8000;
      }
    }
    else if ((short)uVar6 < 0) {
      uVar6 = 0x7fff;
    }
    uVar5 = me7_lookup_1d_word(0x3b60,8,uRam3055d0);
    uVar7 = uVar6;
    if ((short)uVar6 < 0) {
      uVar7 = -uVar6;
    }
    uVar1 = (uint)uVar7 * (uint)uVar5;
    MDC = MDC | 0x10;
    if ((uVar1 & 0xc0000000) == 0) {
      uVar7 = (short)(uVar1 >> 0x10) << 1 | (ushort)uVar1 >> 0xf;
      if ((short)uVar6 < 0) {
        uVar7 = -uVar7;
      }
    }
    else if ((short)uVar6 < 0) {
      uVar7 = 0x8000;
    }
    else {
      uVar7 = 0x7fff;
    }
    uVar6 = bRam303270 - uVar7;
    if ((short)uVar7 < 0 && (short)(bRam303270 - uVar7) < 0) {
      uVar6 = 0x8000;
    }
    if ((short)uVar6 < 0) {
      uVar6 = 0;
    }
    else if (uVar6 != 0xff &&
             (short)(uVar6 - 0xff) < 0 ==
             ((short)uVar6 < 0 && (short)(uVar6 - 0xff) < 0 != (short)uVar6 < 0)) {
      uVar6 = 0xff;
    }
  }
  MDH = (undefined2)(uVar1 >> 0x10);
  MDL = (undefined2)uVar1;
  bRam304971 = bRam019fd5;
  if ((byte)uVar6 <= bRam019fd5) {
    bRam304971 = (byte)uVar6;
  }
  uVar6 = bRam304971 - 0x40;
  sRam302ae6 = (ushort)bRam304971 << 10;
  uRam302ae8 = ((short)uVar6 >> 0xf) << 10 | uVar6 >> 6;
  if (((egt_modeled < bRam019fd7) || ((uRam303bea & 1) != 0)) ||
     (rpmclass_oppoint = egt_modeled, bRam019fd8 < egt_modeled)) {
    rpmclass_oppoint = bRam304971;
  }
  bRam301637 = bRam301637 | 1;
  sRam302ace = (ushort)rpmclass_oppoint << 8;
  bRam304976 = rpmclass_oppoint;
  bRam304979 = rpmclass_oppoint;
  bVar4 = func_0x040b3e(0x3e82,bRam304975);
  bRam304978 = bRam019fd6;
  if (bRam019fd6 <= bVar4) {
    bRam304978 = bVar4;
  }
  bVar4 = func_0x040b3e(0x3e82,bRam304979);
  iVar3 = CONCAT22(uRam302ae0,uRam302ade);
  iVar2 = CONCAT22(MDH,MDL);
  bRam301645 = bRam019fd5;
  if (bRam019fd5 <= bVar4) {
    bRam301645 = bVar4;
  }
  bRam304977 = bRam304978;
  if (bRam304975 <= bRam304978) {
    bRam304977 = bRam304975;
  }
  uVar6 = bRam304977 - 0x40;
  sRam302ae2 = (ushort)bRam304977 << 10;
  uRam302ae4 = ((short)uVar6 >> 0xf) << 10 | uVar6 >> 6;
  if (bRam304971 < bRam305645) {
    bRam30496d = bRam30496d & 0xfe;
  }
  else {
    bRam30496d = bRam30496d | 1;
  }
  uRam304973 = 0xff;
  if ((uRam00fd16 & 0x20) == 0) {
    uVar6 = me7_lookup_1d_byte(0x1fe5,6,bRam304975);
    iVar2 = (uint)(uVar6 & 0xff) * 0xc800;
    MDC = MDC | 0x10;
    sRam3052f4 = (short)((uint)iVar2 >> 8);
    iVar3 = iVar2;
  }
  else {
    sRam3052f4 = 0;
  }
  uRam302ae0 = (undefined2)((uint)iVar3 >> 0x10);
  uRam302ade = (undefined2)iVar3;
  MDH = (undefined2)((uint)iVar2 >> 0x10);
  MDL = (undefined2)iVar2;
  if (sRam3052f4 == 0) {
    bRam301640 = bRam301640 | 1;
    bRam30163c = bRam30163c | 1;
  }
  if ((DAT_00fd4e & 0x100) != 0) {
    bRam01b271 = bRam019fd5;
    bRam01b270 = bRam019fd5;
    bRam30a026 = bRam019fd5;
  }
  if ((uRam303bea & 1) == 0) {
    bRam00e195 = egt_modeled;
    if (egt_modeled < bRam019fdb) {
      bRam00e195 = bRam019fdb;
    }
  }
  else {
    bRam01a195 = bRam019fdb;
  }
  sRam302aec = (bRam00e195 - 0x40) * 0x80;
  uRam302aea = 0;
  uRam022ada = uRam023c6c;
  uRam022adc = uRam023c6e;
  bRam301639 = bRam301639 & 0xfe;
  if ((bRam019f44 & 1) == 0) {
    bRam301638 = bRam301638 & 0xc3 | 0x40;
  }
  else {
    bRam301638 = bRam301638 & 0x83;
  }
  uRam30496e = uRam019f5e;
  if ((uRam307bf6 & 1) == 0) {
    uRam30497a = uRam30a113;
  }
  else {
    uRam30497a = uRam019fe4;
  }
  return;
}


// ================= egt_overtemp_consumer @ 08c636 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* EGT over-temp: byte_304974 vs EFFMFA2 -> overheat flag byte_3007DD */

void egt_overtemp_consumer(void)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  ushort uVar6;
  char cVar7;
  ushort uVar8;
  short sVar9;
  short sVar10;
  byte bVar11;
  ushort uStack_8;
  int iVar5;
  
  uVar6 = uRam303be8;
  uStack_8 = uRam303be8;
  bRam3007d7 = bRam3007d7 + 1;
  if (bRam3007d7 == 0xfa) {
    bRam3007d7 = 0;
  }
  sVar1 = bRam30a113 - 0x40;
  sVar10 = (egt_modeled - 0x40) * 0x80;
  sVar9 = sVar10 + sVar1 * -0x80;
  if (sVar10 < 0 != sVar1 * 0x80 < 0 && sVar10 + sVar1 * -0x80 < 0 != sVar10 < 0) {
    sVar9 = -0x8000;
  }
  uVar8 = sVar9 >> 7;
  if ((short)uVar8 < 0) {
    cRam3047b5 = (char)uVar8 + '@';
    if (uVar8 <= uVar8 + 0x40 && 0x3f < uVar8 + 0x40) {
      cRam3047b5 = '\0';
    }
  }
  else {
    cRam3047b5 = (char)uVar8 + '@';
    if (uVar8 + 0x40 < uVar8 || uVar8 + 0x40 < 0x40) {
      cRam3047b5 = -1;
    }
  }
  if ((ushort)bRam00f472 == bRam3047d6 + 1 || (short)((ushort)bRam00f472 - (bRam3047d6 + 1)) < 0) {
    if ((bRam3007da & 0x40) == 0) {
      cRam3007db = me7_lookup_1d_byte(0x1d67,6,cRam3047b5);
    }
    if (cRam3007db == '\0') {
      bRam3047b1 = me7_lookup_1d_byte(0x1d67,6,cRam3047b5);
    }
    else {
      bRam3047b1 = me7_lookup_1d_byte(0x1d74,6,cRam3047b5);
      cRam3047db = cRam3047db + -1;
    }
    bRam3007da = bRam3007da | 0x40;
  }
  else {
    bRam3047b1 = me7_lookup_1d_byte(0x1d74,6,cRam3047b5);
    bRam3007da = bRam3007da & 0xbf;
  }
  if (-1 < (short)(bRam3047b1 - 199)) {
    bRam3047b1 = 199;
  }
  bRam3007d6 = bRam00f472;
  cRam3007e6 = (flags_torque_revlimit & 0x80) != 0;
  *(char *)((uint3)bRam3007d8 + 0x304880) = cRam3007e6;
  __nop();
  if (bRam3047d8 < bRam3047b1) {
    uRam3047e6 = *(undefined1 *)((uint3)((bRam3007d8 + 200) - (ushort)bRam3047b1) + 0x304880);
    __nop();
  }
  else {
    uRam3047e6 = *(undefined1 *)((uint3)((ushort)bRam3007d8 - (ushort)bRam3047b1) + 0x304880);
    __nop();
  }
  bRam3007d8 = bRam3007d8 + 1;
  if (-1 < (short)(bRam3007d8 - 200)) {
    bRam3007d8 = 0;
  }
  *(byte *)((uint3)bRam3007e7 + 0x3047b7) = bRam00f472;
  __nop();
  if (bRam3047e7 < bRam3047b1) {
    uRam3047b3 = *(undefined1 *)((uint3)((bRam3007e7 + 200) - (ushort)bRam3047b1) + 0x3047b7);
    __nop();
  }
  else {
    uRam3047b3 = *(undefined1 *)((uint3)((ushort)bRam3007e7 - (ushort)bRam3047b1) + 0x3047b7);
    __nop();
  }
  bRam3007e7 = bRam3007e7 + 1;
  if (-1 < (short)(bRam3007e7 - 200)) {
    bRam3007e7 = 0;
  }
  if (((_flags_start_phase & 0x4000) == 0) && ((uRam00fd52 & 0x1000) == 0)) {
    if (cRam3007dc == '\0') {
      egt_overtemp_flag = egt_overtemp_flag & 0xfe;
    }
    else {
      MDL = bRam3007d7 / 10;
      MDH = (ushort)bRam3007d7 % 10;
      MDC = MDC | 0x10;
      if ((char)MDH == '\0') {
        cRam3007dc = cRam3007dc + -1;
      }
    }
  }
  else {
    egt_overtemp_flag = egt_overtemp_flag | 1;
    cRam3007dc = me7_lookup_1d_byte(0x1d98,6,bRam304979);
  }
  if (((uRam00fd0e & 0x1000) == 0) || ((egt_overtemp_flag & 1) != 0)) {
    if ((uRam303bea & 1) == 0) {
      if (bRam019d94 < egt_modeled) {
        bRam3047b4 = bRam019d94;
      }
      else if (egt_modeled < 0xb) {
        bRam3047b4 = 0xb;
      }
      else {
        bRam3047b4 = egt_modeled;
      }
    }
    else if (bRam019d94 < bRam019d93) {
      bRam3047b4 = bRam019d94;
    }
    else if (bRam019d93 < 0xb) {
      bRam3047b4 = 0xb;
    }
    else {
      bRam3047b4 = bRam019d93;
    }
    iRam3007e0 = (uint)((bRam3047b4 - 0x40) * 0x80) << 0x10;
  }
  else {
    sVar1 = (bRam019d94 - 0x40) * 0x80;
    if (cRam3007e6 == '\x01') {
      uVar8 = func_0x042464(uRam02391a,0x391b,8,0x3922,8,bRam304979,0xe556,0,sVar1,0);
      cVar7 = func_0x042596(uRam0238f6,0x38f8,8,uRam0238f7,0x38fe,8,0x3902,8,bRam3047b4,bRam30a113);
      sVar1 = (short)cVar7;
      if ((short)uVar8 < 0) {
        iVar5 = (int)sVar1 * (int)(short)(uVar8 & 0x7fff);
        uVar3 = (ushort)iVar5;
        uVar8 = sVar1 * -0x8000;
        iVar4 = CONCAT22((short)((uint)iVar5 >> 0x10) + (sVar1 >> 1) +
                         (ushort)(uVar3 + uVar8 < uVar3 || uVar3 + uVar8 < uVar8),uVar3 + uVar8);
      }
      else {
        iVar4 = (int)sVar1 * (int)(short)uVar8;
        iVar5 = iVar4;
      }
      MDH = (ushort)((uint)iVar5 >> 0x10);
      MDL = (ushort)iVar5;
      MDC = MDC | 0x10;
      iRam3007e0 = func_0x0430da(0x199a,(ushort)iVar4 >> 0xc | (short)((uint)iVar4 >> 0x10) << 4,
                                 iRam3007e0._2_2_,(undefined2)iRam3007e0);
    }
    else {
      uVar8 = me7_lookup_1d_byte(0x1d81,6,bRam30a113);
      sVar9 = (uVar8 & 0xff) - 0x40;
      sVar2 = (bRam3047b4 - 0x40) * 0x80;
      sVar10 = sVar2 + sVar9 * -0x80;
      if (sVar2 < 0 != sVar9 * 0x80 < 0 && sVar2 + sVar9 * -0x80 < 0 != sVar2 < 0) {
        sVar10 = -0x8000;
      }
      uVar8 = sVar10 >> 7;
      if ((short)uVar8 < 0) {
        cRam3047b6 = (char)uVar8 + '@';
        if (uVar8 <= uVar8 + 0x40 && 0x3f < uVar8 + 0x40) {
          cRam3047b6 = '\0';
        }
      }
      else {
        cRam3047b6 = (char)uVar8 + '@';
        if (uVar8 + 0x40 < uVar8 || uVar8 + 0x40 < 0x40) {
          cRam3047b6 = -1;
        }
      }
      uVar8 = func_0x042464(uRam02391a,0x391b,8,0x3922,8,bRam304979,0xe556,0,sVar1,0);
      cVar7 = func_0x042596(uRam0238ca,0x38cc,8,uRam0238cb,0x38d2,8,0x38d7,8,uRam3047b3,cRam3047b6);
      sVar1 = (short)cVar7;
      if ((short)uVar8 < 0) {
        iVar5 = (int)sVar1 * (int)(short)(uVar8 & 0x7fff);
        uVar3 = (ushort)iVar5;
        uVar8 = sVar1 * -0x8000;
        iVar4 = CONCAT22((short)((uint)iVar5 >> 0x10) + (sVar1 >> 1) +
                         (ushort)(uVar3 + uVar8 < uVar3 || uVar3 + uVar8 < uVar8),uVar3 + uVar8);
      }
      else {
        iVar4 = (int)sVar1 * (int)(short)uVar8;
        iVar5 = iVar4;
      }
      MDH = (ushort)((uint)iVar5 >> 0x10);
      MDL = (ushort)iVar5;
      MDC = MDC | 0x10;
      iRam3007e0 = func_0x0430da(0x199a,(ushort)iVar4 >> 0xc | (short)((uint)iVar4 >> 0x10) << 4,
                                 iRam3007e0._2_2_,(undefined2)iRam3007e0);
    }
    uVar8 = (ushort)(iRam3007e0 >> 0x17);
    if ((short)uVar8 < 0) {
      bRam3047b4 = (char)uVar8 + 0x40;
      if (uVar8 <= uVar8 + 0x40 && 0x3f < uVar8 + 0x40) {
        bRam3047b4 = 0;
      }
    }
    else {
      bRam3047b4 = (char)uVar8 + 0x40;
      if (uVar8 + 0x40 < uVar8 || uVar8 + 0x40 < 0x40) {
        bRam3047b4 = 0xff;
      }
    }
  }
  if ((bRam019d63 & 1) == 0) {
    DAT_00fd4e = DAT_00fd4e & 0xefff;
  }
  else {
    DAT_00fd4e = DAT_00fd4e | 0x1000;
  }
  bVar11 = bRam019d90;
  if ((uRam303bf6 & 1) == 0) {
    bVar11 = bRam019d91;
  }
  if (((((((DAT_00fd4e & 0x1000) == 0) || ((flags_torque_revlimit & 0x80) != 0)) ||
        ((uRam303bea & 1) != 0)) || ((bVar11 <= bRam30a113 || (bRam30a113 <= bRam019d92)))) ||
      (bRam304715 <= bRam019d66)) || ((bRam019d97 <= bRam304979 || (uRam3055d0 < uRam023934)))) {
    DAT_00fd4e = DAT_00fd4e & 0xf7ff;
  }
  else {
    DAT_00fd4e = DAT_00fd4e | 0x800;
  }
  if (bRam019d95 <= egt_modeled) {
    egt_overtemp_flag = egt_overtemp_flag | 2;
  }
  if (((DAT_00fd4e & 0x800) == 0) || ((egt_overtemp_flag & 2) != 0)) {
    cRam3007de = bRam019d8f + bRam019d64;
    if ((byte)(bRam019d8f + bRam019d64) < bRam019d8f || (byte)(bRam019d8f + bRam019d64) < bRam019d64
       ) {
      cRam3007de = -1;
    }
  }
  else if (cRam3007de == '\0') {
    egt_overtemp_flag = egt_overtemp_flag | 4;
  }
  else {
    cRam3007de = cRam3007de + -1;
  }
  if (egt_modeled < bRam3047b4) {
    bRam3047b2 = bRam3047b4 - egt_modeled;
    if (bRam3047b4 < egt_modeled) {
      bRam3047b2 = 0;
    }
  }
  else {
    bRam3047b2 = 0;
  }
  if (((bRam3047b2 <= bRam019d65) || ((DAT_00fd4e & 0x800) == 0)) || ((egt_overtemp_flag & 2) != 0))
  {
    if ((((bRam3007da & 4) == 0) && (bRam3015f1 = bRam3015f1 & 0xdf, bRam00f472 < bRam019d8e)) &&
       (((_flags_start_phase & 0x8000) != 0 && (sRam3007e4 != -1)))) {
      sRam3007e4 = sRam3007e4 + 1;
    }
    goto LAB_08cdb2;
  }
  if ((bRam3007da & 4) != 0) goto LAB_08cdb2;
  sRam305290 = sRam3007e4;
  uVar8 = FUN_042c1c(sRam3007e4,0xffff,uRam305630);
  if (uVar8 < uRam023932) {
    uVar8 = FUN_042c1c(uRam305630,uRam023930,0x402);
    if (uRam304f70 <= uVar8) goto LAB_08cd70;
    bRam3015f1 = bRam3015f1 | 0x20;
  }
  else {
LAB_08cd70:
    bRam3015f1 = bRam3015f1 & 0xdf;
  }
  bRam3007da = bRam3007da | 4;
LAB_08cdb2:
  if ((bRam3015f1 & 0x20) == 0) {
    bRam0187d9 = bRam019d8f;
    bRam3015f1 = bRam3015f1 & 0xfe;
  }
  else if (cRam3007d9 == '\0') {
    bRam3015f1 = bRam3015f1 | 1;
  }
  else {
    cRam3007d9 = cRam3007d9 + -1;
  }
  if ((bRam3015f1 & 4) == 0) {
    if ((bRam3015f1 & 1) != 0) {
      egt_overtemp_flag = egt_overtemp_flag | 8;
    }
  }
  else {
    egt_overtemp_flag = egt_overtemp_flag & 0xf7;
  }
  if (((bRam3007da & 8) == 0) && (bRam019d96 < egt_modeled)) {
    uRam305292 = uRam305630;
    uVar8 = FUN_042c1c(uRam305630,uRam02392e,0x402);
    if (uRam304f70 < uVar8) {
      bRam3015f1 = bRam3015f1 | 0x10;
    }
    else {
      bRam3015f1 = bRam3015f1 & 0xef;
    }
    bRam3007da = bRam3007da | 8;
  }
  if (((((egt_overtemp_flag & 4) == 0) || ((egt_overtemp_flag & 2) == 0)) ||
      ((egt_overtemp_flag & 8) != 0)) || ((bRam3015f1 & 0x10) == 0)) {
    bRam3015f1 = bRam3015f1 & 0xfb;
  }
  else {
    bRam3015f1 = bRam3015f1 | 4;
    egt_overtemp_flag = egt_overtemp_flag | 0x10;
  }
  if ((((uRam303bea & 2) == 0) && ((bRam019d63 & 2) == 0)) || ((uRam303bea & 1) != 0)) {
    bRam3007da = bRam3007da & 0x7f;
  }
  else {
    bRam3007da = bRam3007da | 0x80;
  }
  if ((((egt_overtemp_flag & 0x40) == 0) && ((bRam3007da & 0x80) == 0)) && ((bRam3015f1 & 1) != 0))
  {
    egt_overtemp_flag = egt_overtemp_flag | 0x20;
  }
  else {
    egt_overtemp_flag = egt_overtemp_flag & 0xdf;
  }
  if (((bRam3007da & 0x80) == 0) && ((bRam3015f1 & 1) != 0)) {
    egt_overtemp_flag = egt_overtemp_flag | 0x40;
  }
  else {
    egt_overtemp_flag = egt_overtemp_flag & 0xbf;
  }
  if ((egt_overtemp_flag & 0x20) != 0) {
    uStack_8 = uVar6 & 0xff00 | uVar6 & 0xff00 | 4;
    func_0x0b31ac(0xb1,uStack_8);
  }
  if ((bRam3007da & 0x80) != 0) {
    if ((egt_overtemp_flag & 8) == 0) {
      bRam3015f1 = bRam3015f1 & 0xfd;
    }
    else {
      bRam3015f1 = bRam3015f1 | 2;
    }
    if ((egt_overtemp_flag & 0x10) == 0) {
      bRam3015f1 = bRam3015f1 & 0xf7;
    }
    else {
      bRam3015f1 = bRam3015f1 | 8;
    }
  }
  if ((bRam3015f1 & 2) != 0) {
    uStack_8 = (uStack_8 >> 8 & 0x90 | 0x68) << 8 | 2;
  }
  if ((bRam3015f1 & 8) != 0) {
    uStack_8 = ((uStack_8 & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
  }
  func_0x0b31ac(0xb1,uStack_8);
  return;
}


// ================= vmax_speed_limiter @ 050000 =================

/* WARNING: Removing unreachable block (ram,0x0500bc) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* vehicle-speed limiter (VMAX): PI torque governor -> word_304F3C (limiters.md) */

void vmax_speed_limiter(void)

{
  int iVar1;
  uint uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  undefined4 uVar6;
  
  uVar2 = CONCAT22(MDH,MDL);
  uRam304f40 = uRam304f34;
  if ((short)uRam3069be < 1) {
    uRam304f3e = _vfzg_vehicle_speed;
  }
  else {
    uVar2 = (uint)uRam3069be * (uint)*(byte *)((uint3)gear_index + 0x182ba) * 0x100;
    uVar5 = (ushort)(uVar2 >> 0x10);
    MDC = MDC | 0x10;
    uRam304f3e = _vfzg_vehicle_speed + uVar5;
    if (_vfzg_vehicle_speed + uVar5 < _vfzg_vehicle_speed || _vfzg_vehicle_speed + uVar5 < uVar5) {
      uRam304f3e = 0xffff;
    }
  }
  sRam304f36 = uRam304f34 - uRam304f3e;
  if (uRam304f34 < uRam304f3e) {
    if (sRam304f36 >= 0) {
      sRam304f36 = -0x8000;
    }
  }
  else if (sRam304f36 < 0) {
    sRam304f36 = 0x7fff;
  }
  if ((sRam304f36 < 1) || (uRam304f3c < uRam305ac8)) {
    if ((flags_torque_revlimit & 0x20) == 0) {
      uRam300206._2_2_ = uRam301ac8 >> 8;
      uRam300206._0_2_ = uRam301ac8 << 8;
    }
    flags_torque_revlimit = flags_torque_revlimit | 0x20;
    iVar1 = (int)sRam304f36 * (int)(short)(ushort)*(byte *)((uint3)gear_index + 0x182b2);
    MDL = (ushort)iVar1;
    MDH = (ushort)((uint)iVar1 >> 0x10);
    MDC = MDC | 0x10;
    uVar5 = (ushort)(MDL < 0x7fff);
    if (MDH == uVar5 && MDL == 0x7fff ||
        (short)(MDH - uVar5) < 0 != (iVar1 < 0 && (short)(MDH - (MDL < 0x7fff)) < 0 != iVar1 < 0)) {
      uRam304f3a = MDL;
      if ((short)((MDH + 1) - (ushort)(MDL < 0x8000)) < 0 !=
          (-1 < iVar1 && (short)((MDH + 1) - (ushort)(MDL < 0x8000)) < 0 != iVar1 < 0)) {
        uRam304f3a = 0x8000;
      }
    }
    else {
      uRam304f3a = 0x7fff;
    }
    uVar5 = uRam302534 >> 1;
    if ((short)uRam3024ea < 0) {
      uVar3 = uRam3024ea + uVar5;
      if (uRam3024ea <= uRam3024ea + uVar5 && uVar5 <= uRam3024ea + uVar5) {
        uVar3 = 0;
      }
    }
    else {
      uVar3 = uRam3024ea + uVar5;
      if (uRam3024ea + uVar5 < uRam3024ea || uRam3024ea + uVar5 < uVar5) {
        uVar3 = 0xffff;
      }
    }
    uVar6 = me7_integrator_minmax
                      (*(undefined2 *)((uint3)gear_index * 2 + 0x1edc0),sRam304f36,uRam300206._2_2_,
                       (short)uRam300206,(uVar3 & 0x7fff) >> 7,0xff);
    uRam304f38 = (short)((uint)uVar6 >> 0x10) * 0x100 + ((ushort)uVar6 >> 8);
    uVar5 = uRam304f38 >> 1;
    if ((short)uRam304f3a < 0) {
      uVar4 = uRam304f3a + uVar5;
      if (uRam304f3a <= uRam304f3a + uVar5 && uVar5 <= uRam304f3a + uVar5) {
        uVar4 = 0;
      }
    }
    else {
      uVar4 = uRam304f3a + uVar5;
      if (uRam304f3a + uVar5 < uRam304f3a || uRam304f3a + uVar5 < uVar5) {
        uVar4 = 0xffff;
      }
    }
    uVar2 = (uint)uVar4 * 2;
    uVar5 = (ushort)uVar2;
    MDC = MDC | 0x10;
    if (0xffff < uVar2) {
      uVar5 = 0xffff;
    }
    uRam304f3c = uVar3 * 2;
    if (uVar3 * 2 <= uVar5) {
      uRam304f3c = uVar5;
    }
  }
  else {
    flags_torque_revlimit = flags_torque_revlimit & 0xffdf;
    uRam304f3c = 0xffff;
    uVar6 = uRam300206;
  }
  uRam300206._2_2_ = (ushort)((uint)uVar6 >> 0x10);
  uRam300206._0_2_ = (short)uVar6;
  MDH = (ushort)(uVar2 >> 0x10);
  MDL = (ushort)uVar2;
  return;
}


// ================= vmax_table_lookup @ 00a5ee =================

/* VMAX gear-dependent speed-limit table reader (0x1BECC) */

void vmax_table_lookup(void)

{
  if ((bRam304009 != 0) && (bRam304009 < 0xb)) {
    uRam304e2e = func_0x042464(uRam01bec0,0x3ec1,6,0x3ecc,6,bRam304009);
    return;
  }
  uRam304e2e = uRam01bee2;
  return;
}


// ================= diag_o2_sensor_monitor @ 0a5a9e =================

/* WARNING: Removing unreachable block (ram,0x0a6110) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC: O2/lambda-sensor OBD monitor (INHASE02/04/05); no control */

undefined1 diag_o2_sensor_monitor(void)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  byte bVar4;
  undefined1 uVar5;
  undefined2 uVar6;
  short sVar7;
  byte bVar8;
  ushort uVar9;
  ushort uVar10;
  ushort uStack_4e;
  ushort uStack_4c;
  ushort uStack_4a;
  undefined1 auStack_48 [4];
  ushort uStack_44;
  undefined1 auStack_40 [4];
  ushort uStack_3c;
  ushort uStack_38;
  ushort uStack_36;
  ushort uStack_34;
  ushort uStack_32;
  ushort uStack_30;
  ushort uStack_2e;
  ushort uStack_2c;
  ushort uStack_2a;
  ushort uStack_28;
  ushort uStack_26;
  ushort uStack_24;
  
  if ((_flags_diag_enable_b & 4) == 0) {
    DAT_301714 = DAT_301714 & 0xe7;
    uRam30a250 = 0;
    return 0xf7;
  }
  bVar4 = bRam30a017 & 1;
  if ((uRam026dc4 < uRam0241be) || (uRam0241bc < uRam302dc4)) {
    uVar6 = 0;
  }
  else {
    uVar6 = 1;
  }
  cRam3009fa = FUN_032ebe(0x89fb,uVar6,uRam01a199);
  if ((((bRam30171b & 2) == 0) || (bRam304d30 <= bRam01a19a)) || (cRam3009fa == '\0')) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  bVar3 = (uRam00fd0e & 0x1000) != 0;
  uRam300a00 = bVar3 && cRam300a01 == '\0';
  bVar8 = bRam301715;
  if ((((bRam301715 & 1) == 0) && ((bool)uRam300a00)) &&
     ((ushort)bRam304979 <= (ushort)bRam304d30 + (ushort)bRam01a197)) {
    uVar9 = bRam30a04a + 1;
    if (0xff < uVar9) {
      uVar9 = 0xff;
    }
    bRam30a04a = (byte)uVar9;
    bVar8 = bRam301715 | 1;
    if (bRam01a186 <= bRam30a04a) {
      bVar8 = bRam301715 | 3;
    }
  }
  bRam301715 = bVar8;
  bVar1 = (1 << (ushort)bRam01a191 & uRam30a252) != 0;
  uRam300a0a = bVar1 && cRam300a0b == '\0';
  if ((bool)uRam300a0a) {
    bRam30a04a = 0;
  }
  if (((char)(cRam304952 - cRam01a195) < '\0' ==
       (cRam304952 < '\0' != cRam01a195 < '\0' &&
       (char)(cRam304952 - cRam01a195) < '\0' != cRam304952 < '\0')) ||
     ((cRam304954 == '\0' && ((bRam01a17b & 1) != 0)))) {
    DAT_301714 = DAT_301714 | 0x20;
  }
  else {
    DAT_301714 = DAT_301714 & 0xdf;
  }
  if ((((bRam3015e0 & 4) == 0) || ((bRam3015e0 & 1) == 0)) &&
     (((DAT_30170f & 1) == 0 || ((DAT_30170f & 2) == 0)))) {
    uRam3009fc = false;
    cRam3009fd = 0;
  }
  else {
    uRam3009fc = cRam3009fd == '\0';
    cRam3009fd = 1;
  }
  if (((bool)uRam3009fc != false) || ((bRam301716 & 1) != 0)) {
    bRam30a04c = 0;
    bRam30a04b = 0;
  }
  if ((((DAT_303332 & 1) == 0) || ((DAT_303331 & 0x80) == 0)) ||
     ((1 << (ushort)bRam01a18b & uRam30a252) == 0)) {
    uRam3009f4 = false;
    cRam3009f5 = 0;
  }
  else {
    uRam3009f4 = cRam3009f5 == '\0';
    cRam3009f5 = 1;
  }
  if ((bool)uRam3009f4 != false) {
    uVar9 = bRam30a04c + 1;
    if (0xff < uVar9) {
      uVar9 = 0xff;
    }
    bRam30a04c = (byte)uVar9;
  }
  if ((bRam01a188 < bRam30a04c) || (bRam01a187 < bRam30a04b)) {
    bRam303330 = bRam303330 & 0xfe;
  }
  else if ((bool)uRam3009fc != false) {
    bRam303330 = bRam303330 | 1;
  }
  if (bRam01a184 < bRam3049ba) {
    uRam305380 = ~(1 << (ushort)bRam01a193);
  }
  else {
    uRam305380 = 0xffff;
  }
  if (bRam01a182 < bRam3049b8) {
    uRam305380 = ~(1 << (ushort)bRam01a191) & uRam305380;
  }
  else {
    uRam305380 = 1 << (ushort)bRam01a191 | uRam305380;
  }
  if (bRam01a180 < bRam3049b6) {
    uRam305380 = ~(1 << (ushort)bRam01a18f) & uRam305380;
  }
  else {
    uRam305380 = 1 << (ushort)bRam01a18f | uRam305380;
  }
  if (bRam01a181 < bRam3049b7) {
    uRam305380 = ~(1 << (ushort)bRam01a190) & uRam305380;
  }
  else {
    uRam305380 = 1 << (ushort)bRam01a190 | uRam305380;
  }
  if (bRam01a17d < bRam3049b3) {
    uRam305380 = ~(1 << (ushort)bRam01a18b) & uRam305380;
  }
  else {
    uRam305380 = 1 << (ushort)bRam01a18b | uRam305380;
  }
  if (bRam01a17c < bRam3049b2) {
    uRam305380 = ~(1 << (ushort)bRam01a18a) & uRam305380;
  }
  else {
    uRam305380 = 1 << (ushort)bRam01a18a | uRam305380;
  }
  if (bRam01a17e < bRam3049b4) {
    uRam305380 = ~(1 << (ushort)bRam01a18d) & uRam305380;
  }
  else {
    uRam305380 = 1 << (ushort)bRam01a18d | uRam305380;
  }
  if (bRam01a183 < bRam3049b9) {
    uRam305380 = ~(1 << (ushort)bRam01a192) & uRam305380;
  }
  else {
    uRam305380 = 1 << (ushort)bRam01a192 | uRam305380;
  }
  if (bRam01a17f < bRam3049b5) {
    uRam305380 = ~(1 << (ushort)bRam01a18e) & uRam305380;
  }
  else {
    uRam305380 = 1 << (ushort)bRam01a18e | uRam305380;
  }
  if (bRam01a185 < bRam3049bb) {
    uRam305380 = ~(1 << (ushort)bRam01a194) & uRam305380;
  }
  else {
    uRam305380 = 1 << (ushort)bRam01a194 | uRam305380;
  }
  uRam30537c = uRam30537e;
  if ((bRam305715 & 1) == 0) {
    uVar9 = 0;
  }
  else {
    uVar9 = 1 << (ushort)bRam01a193;
  }
  if ((bRam301715 & 2) == 0) {
    uVar9 = ~(1 << (ushort)bRam01a191) & uVar9;
  }
  else {
    uVar9 = 1 << (ushort)bRam01a191 | uVar9;
  }
  if ((_DAT_302632 & 0x800) == 0) {
    uVar9 = ~(1 << (ushort)bRam01a18f) & uVar9;
  }
  else {
    uVar9 = 1 << (ushort)bRam01a18f | uVar9;
  }
  if ((DAT_301712 & 2) == 0) {
    uVar9 = ~(1 << (ushort)bRam01a190) & uVar9;
  }
  else {
    uVar9 = 1 << (ushort)bRam01a190 | uVar9;
  }
  if (((bRam303330 & 1) == 0) || ((bRam301716 & 2) == 0)) {
    uVar9 = ~(1 << (ushort)bRam01a18b) & uVar9;
  }
  else {
    uVar9 = 1 << (ushort)bRam01a18b | uVar9;
  }
  if (bVar2) {
    uVar9 = 1 << (ushort)bRam01a18a | uVar9;
  }
  else {
    uVar9 = ~(1 << (ushort)bRam01a18a) & uVar9;
  }
  if ((_DAT_302632 & 0x20) == 0) {
    uVar9 = ~(1 << (ushort)bRam01a18e) & uVar9;
  }
  else {
    uVar9 = 1 << (ushort)bRam01a18e | uVar9;
  }
  if ((bRam30170d & 1) == 0) {
    uVar9 = ~(1 << (ushort)bRam01a18d) & uVar9;
  }
  else {
    uVar9 = 1 << (ushort)bRam01a18d | uVar9;
  }
  if ((bRam301711 & 4) == 0) {
    uVar9 = ~(1 << (ushort)bRam01a192) & uVar9;
  }
  else {
    uVar9 = 1 << (ushort)bRam01a192 | uVar9;
  }
  uVar9 = ~(1 << (ushort)bRam01a194) & uVar9;
  if (bRam01a17a == 0) {
    uVar9 = ~(1 << (ushort)bRam01a18c) & uVar9;
  }
  else {
    uVar9 = 1 << (ushort)bRam01a18c | uVar9;
  }
  uVar9 = uVar9 & uRam305380;
  uVar10 = ~uRam305376 & uRam30a252;
  if ((uVar10 != 0) && ((uRam3035f8 & 0x8000) != 0)) {
    uVar10 = 0xffff;
  }
  uRam305374 = (~uRam30537e & uVar9 | uRam305374) & ~(~uVar9 & uRam30537e | uVar10 | uRam305382);
  uRam305376 = uRam30a252;
  if ((((((uRam307be0 & 1) == 0) && ((uRam303be4 & 1) == 0)) && ((bRam30332a & 1) == 0)) &&
      (((bRam30332a & 2) == 0 && ((uRam303ab2 & 1) == 0)))) && ((uRam303ab0 & 1) == 0)) {
    DAT_301713 = DAT_301713 | 2;
  }
  else {
    DAT_301713 = DAT_301713 & 0xfd;
  }
  if ((((DAT_301713 & 2) == 0) || ((uRam303bea & 1) != 0)) ||
     (((uRam303c1e & 1) != 0 || ((_flags_diag_enable_b & 4) == 0)))) {
    DAT_301713 = DAT_301713 & 0xfb;
  }
  else {
    DAT_301713 = DAT_301713 | 4;
  }
  cRam300a01 = bVar3;
  cRam300a0b = bVar1;
  uRam30537e = uVar9;
  cRam300a02 = func_0x032e88(0x8a03,(uRam3035f8 & 0x8000) != 0,uRam01a19d);
  if ((uRam026dc4 < uRam0241c6) || (uRam0241c4 < uRam302dc4)) {
    uVar6 = 0;
  }
  else {
    uVar6 = 1;
  }
  cRam3009fe = FUN_032ebe(0x89ff,uVar6,uRam01a199);
  if ((((bRam30332c & 0x20) == 0) || ((bRam01a15f & 4) != 0)) && ((bRam3015e0 & 8) != 0)) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  if ((((uRam303ac0 & 1) == 0) && (uRam0241b6 <= uRam305614)) &&
     ((bRam01a196 <= bRam304979 && ((bRam01a19c < bRam304d30 && (bRam304d30 < bRam01a19b)))))) {
    if (bVar2) {
      bVar3 = true;
    }
    else if (((bRam3015c8 & 1) == 0) && ((bRam3015c9 & 1) != 0)) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    if ((((!bVar3) || (_vfzg_vehicle_speed != 0)) || (cRam300a02 == '\0')) || (cRam3009fe == '\0'))
    goto LAB_0a6378;
    DAT_301713 = DAT_301713 | 0x10;
  }
  else {
LAB_0a6378:
    DAT_301713 = DAT_301713 & 0xef;
  }
  if (uRam0241b8 <= uRam305630) {
    bRam301716 = bRam301716 | 2;
  }
  if ((bRam301716 & 2) != 0) {
    if (bVar2) {
      bVar3 = true;
    }
    else if (((bRam3015c8 & 2) == 0) && ((bRam3015c9 & 1) != 0)) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    if (bVar3) {
      DAT_301713 = DAT_301713 | 0x80;
      goto LAB_0a63d6;
    }
  }
  DAT_301713 = DAT_301713 & 0x7f;
LAB_0a63d6:
  sVar7 = func_0x0bc6c6(0x17,(ushort)auStack_48 & 0x3fff,3);
  if ((((sVar7 == 0) || ((uStack_44 & 2) == 0)) || ((uStack_44 & 4) == 0)) &&
     (((sVar7 = func_0x0bc6c6(0xae,(ushort)auStack_40 & 0x3fff,3), sVar7 == 0 ||
       ((uStack_3c & 2) == 0)) || ((uStack_3c & 4) == 0)))) {
    bRam30332f = bRam30332f & 0xfe;
  }
  else {
    bRam30332f = bRam30332f | 1;
  }
  if ((bRam30332f & 1) == 0) {
    DAT_301713 = DAT_301713 | 0x40;
  }
  else {
    DAT_301713 = DAT_301713 & 0xbf;
  }
  uVar9 = uRam30256a & 8;
  if ((uRam026dc4 < uRam0241c2) || (uRam0241c0 < uRam302dc4)) {
    uVar6 = 0;
  }
  else {
    uVar6 = 1;
  }
  cRam3009f6 = FUN_032ebe(0x89f7,uVar6,uRam01a199);
  sVar7 = uRam305398;
  if (cRam3009f6 == '\0') {
    DAT_301714 = DAT_301714 & 0x7f;
  }
  else {
    DAT_301714 = DAT_301714 | 0x80;
  }
  if ((uVar9 == 0) && (cRam3009f6 != '\0')) {
    DAT_301713 = DAT_301713 | 8;
  }
  else {
    DAT_301713 = DAT_301713 & 0xf7;
  }
  if ((uRam302634 & 1) == 0) {
    DAT_301713 = DAT_301713 | 0x20;
  }
  else {
    DAT_301713 = DAT_301713 & 0xdf;
  }
  if ((uRam00fd0e & 0x1000) != 0) {
    bRam301716 = bRam301716 | 0x10;
  }
  if (((bRam301716 & 0x10) == 0) || ((uRam00fd0e & 0x1000) != 0)) {
    bVar3 = false;
  }
  else {
    bVar3 = true;
  }
  if (((uRam3035f8 & 0x8000) == 0) || (!bVar3)) {
    if (((bVar3) && ((uRam3035f8 & 0x8000) != 0)) ||
       (((uRam00fd3a & 0x200) != 0 && ((uRam00fd0e & 0x1000) == 0)))) {
      bRam3049bc = 1;
    }
    else if (((uRam00fd0e & 0x1000) != 0) && ((uRam00fd3a & 0x200) != 0)) {
      bRam3049bc = 2;
    }
  }
  else {
    bRam3049bc = 0;
  }
  uStack_4e = uRam305374;
  if ((DAT_301713 & 0x20) == 0) {
    if ((DAT_301713 & 4) == 0) {
      if ((DAT_301713 & 0x10) == 0) {
        if ((DAT_301713 & 0x80) == 0) {
          if ((DAT_301713 & 8) == 0) {
            uVar9 = uRam305374;
            if ((DAT_301713 & 0x40) == 0) {
              uVar9 = ~uRam305390 & uRam305374;
            }
            uStack_4e = ~uRam305388 & uVar9;
          }
          else if ((DAT_301713 & 0x40) == 0) {
            uStack_4e = ~uRam305390 & uRam305374;
          }
          uStack_4e = ~uRam305396 & uStack_4e;
        }
        else if ((DAT_301713 & 8) == 0) {
          if ((DAT_301713 & 0x40) == 0) {
            uStack_4e = ~uRam305390 & uRam305374;
          }
          uStack_4e = ~uRam305388 & uStack_4e;
        }
        else if ((DAT_301713 & 0x40) == 0) {
          uStack_4e = ~uRam305390 & uRam305374;
        }
        uStack_4c = uStack_4e & ~uRam30538a;
      }
      else {
        if ((DAT_301713 & 0x80) == 0) {
          if ((DAT_301713 & 8) == 0) {
            uVar9 = uRam305374;
            if ((DAT_301713 & 0x40) == 0) {
              uVar9 = ~uRam305390 & uRam305374;
            }
            uStack_4e = ~uRam305388 & uVar9;
          }
          else if ((DAT_301713 & 0x40) == 0) {
            uStack_4e = ~uRam305390 & uRam305374;
          }
          uStack_4e = ~uRam305396 & uStack_4e;
        }
        else if ((DAT_301713 & 8) == 0) {
          if ((DAT_301713 & 0x40) == 0) {
            uStack_4e = ~uRam305390 & uRam305374;
          }
          uStack_4e = ~uRam305388 & uStack_4e;
        }
        else if ((DAT_301713 & 0x40) == 0) {
          uStack_4e = ~uRam305390 & uRam305374;
        }
        uStack_4c = uStack_4e;
      }
      uStack_4a = uStack_4c & ~uRam305386;
    }
    else {
      if ((DAT_301713 & 0x10) == 0) {
        if ((DAT_301713 & 0x80) == 0) {
          if ((DAT_301713 & 8) == 0) {
            uVar9 = uRam305374;
            if ((DAT_301713 & 0x40) == 0) {
              uVar9 = ~uRam305390 & uRam305374;
            }
            uStack_4e = ~uRam305388 & uVar9;
          }
          else if ((DAT_301713 & 0x40) == 0) {
            uStack_4e = ~uRam305390 & uRam305374;
          }
          uStack_4e = ~uRam305396 & uStack_4e;
        }
        else if ((DAT_301713 & 8) == 0) {
          if ((DAT_301713 & 0x40) == 0) {
            uStack_4e = ~uRam305390 & uRam305374;
          }
          uStack_4e = ~uRam305388 & uStack_4e;
        }
        else if ((DAT_301713 & 0x40) == 0) {
          uStack_4e = ~uRam305390 & uRam305374;
        }
        uStack_4c = uStack_4e & ~uRam30538a;
      }
      else {
        if ((DAT_301713 & 0x80) == 0) {
          if ((DAT_301713 & 8) == 0) {
            uVar9 = uRam305374;
            if ((DAT_301713 & 0x40) == 0) {
              uVar9 = ~uRam305390 & uRam305374;
            }
            uStack_4e = ~uRam305388 & uVar9;
          }
          else if ((DAT_301713 & 0x40) == 0) {
            uStack_4e = ~uRam305390 & uRam305374;
          }
          uStack_4e = ~uRam305396 & uStack_4e;
        }
        else if ((DAT_301713 & 8) == 0) {
          if ((DAT_301713 & 0x40) == 0) {
            uStack_4e = ~uRam305390 & uRam305374;
          }
          uStack_4e = ~uRam305388 & uStack_4e;
        }
        else if ((DAT_301713 & 0x40) == 0) {
          uStack_4e = ~uRam305390 & uRam305374;
        }
        uStack_4c = uStack_4e;
      }
      uStack_4a = uStack_4c;
    }
    uRam30539e = uStack_4a & ~uRam30538c;
  }
  else if ((DAT_301713 & 4) == 0) {
    if ((DAT_301713 & 0x10) == 0) {
      if ((DAT_301713 & 0x80) == 0) {
        if ((DAT_301713 & 8) == 0) {
          uVar9 = uRam305374;
          if ((DAT_301713 & 0x40) == 0) {
            uVar9 = ~uRam305390 & uRam305374;
          }
          uStack_4e = ~uRam305388 & uVar9;
        }
        else if ((DAT_301713 & 0x40) == 0) {
          uStack_4e = ~uRam305390 & uRam305374;
        }
        uStack_4e = ~uRam305396 & uStack_4e;
      }
      else if ((DAT_301713 & 8) == 0) {
        if ((DAT_301713 & 0x40) == 0) {
          uStack_4e = ~uRam305390 & uRam305374;
        }
        uStack_4e = ~uRam305388 & uStack_4e;
      }
      else if ((DAT_301713 & 0x40) == 0) {
        uStack_4e = ~uRam305390 & uRam305374;
      }
      uStack_4c = uStack_4e & ~uRam30538a;
    }
    else {
      if ((DAT_301713 & 0x80) == 0) {
        if ((DAT_301713 & 8) == 0) {
          uVar9 = uRam305374;
          if ((DAT_301713 & 0x40) == 0) {
            uVar9 = ~uRam305390 & uRam305374;
          }
          uStack_4e = ~uRam305388 & uVar9;
        }
        else if ((DAT_301713 & 0x40) == 0) {
          uStack_4e = ~uRam305390 & uRam305374;
        }
        uStack_4e = ~uRam305396 & uStack_4e;
      }
      else if ((DAT_301713 & 8) == 0) {
        if ((DAT_301713 & 0x40) == 0) {
          uStack_4e = ~uRam305390 & uRam305374;
        }
        uStack_4e = ~uRam305388 & uStack_4e;
      }
      else if ((DAT_301713 & 0x40) == 0) {
        uStack_4e = ~uRam305390 & uRam305374;
      }
      uStack_4c = uStack_4e;
    }
    uRam30539e = uStack_4c & ~uRam305386;
  }
  else if ((DAT_301713 & 0x10) == 0) {
    if ((DAT_301713 & 0x80) == 0) {
      if ((DAT_301713 & 8) == 0) {
        uVar9 = uRam305374;
        if ((DAT_301713 & 0x40) == 0) {
          uVar9 = ~uRam305390 & uRam305374;
        }
        uStack_4e = ~uRam305388 & uVar9;
      }
      else if ((DAT_301713 & 0x40) == 0) {
        uStack_4e = ~uRam305390 & uRam305374;
      }
      uStack_4e = ~uRam305396 & uStack_4e;
    }
    else if ((DAT_301713 & 8) == 0) {
      if ((DAT_301713 & 0x40) == 0) {
        uStack_4e = ~uRam305390 & uRam305374;
      }
      uStack_4e = ~uRam305388 & uStack_4e;
    }
    else if ((DAT_301713 & 0x40) == 0) {
      uStack_4e = ~uRam305390 & uRam305374;
    }
    uRam30539e = uStack_4e & ~uRam30538a;
  }
  else if ((DAT_301713 & 0x80) == 0) {
    if ((DAT_301713 & 8) == 0) {
      uVar9 = uRam305374;
      if ((DAT_301713 & 0x40) == 0) {
        uVar9 = ~uRam305390 & uRam305374;
      }
      uVar9 = ~uRam305388 & uVar9;
    }
    else {
      uVar9 = uRam305374;
      if ((DAT_301713 & 0x40) == 0) {
        uVar9 = ~uRam305390 & uRam305374;
      }
    }
    uRam30539e = ~uRam305396 & uVar9;
  }
  else if ((DAT_301713 & 8) == 0) {
    uVar9 = uRam305374;
    if ((DAT_301713 & 0x40) == 0) {
      uVar9 = ~uRam305390 & uRam305374;
    }
    uRam30539e = ~uRam305388 & uVar9;
  }
  else {
    uRam30539e = uRam305374;
    if ((DAT_301713 & 0x40) == 0) {
      uRam30539e = ~uRam305390 & uRam305374;
    }
  }
  if (bRam3049bc == 1) {
    uStack_4a = uRam30538e;
  }
  else if (bRam3049bc == 2) {
    uStack_4a = uRam305394;
  }
  else if (bRam3049bc == 3) {
    uStack_4a = 0xffff;
  }
  else {
    uStack_4a = uRam305392;
  }
  uRam30539e = uStack_4a & uRam30539e;
  if ((uRam30539e & uRam0241a6) == 0) {
    bRam30a0e5 = bRam30a0e5 & 0x3d;
  }
  else {
    bRam30a0e5 = bRam30a0e5 | 0x80;
  }
  if ((~uRam0241a6 & uRam30539e) == 0) {
    bRam30a0e4 = bRam30a0e4 & 0x3d;
  }
  else {
    bRam30a0e4 = bRam30a0e4 | 0x80;
  }
  if (((uRam303be2 & 2) != 0) || (((uRam303ab4 & 2) != 0 && ((uRam303ab4 & 1) != 0)))) {
    bRam30a0e5 = bRam30a0e5 | 8;
  }
  if (((bRam30a0e5 & 0x40) == 0) && (1 < bRam3049bc)) {
    bVar3 = false;
  }
  else {
    bVar3 = true;
  }
  if (bRam3049bc < 2) {
    bVar1 = true;
  }
  else if ((bRam30a0e4 & 0x40) == 0) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  sRam30539c = uRam305398;
  if (bVar1) {
    uRam305398 = uRam30539e;
    if (!bVar3) {
      uRam305398 = ~uRam0241a6 & uRam30539e;
    }
  }
  else {
    uVar9 = uRam30539e;
    if (!bVar3) {
      uVar9 = ~uRam0241a6 & uRam30539e;
    }
    uRam305398 = uRam0241a6 & uVar9;
  }
  bVar8 = ((byte)((ushort)uRam00fd5a >> 8) & 0x40) >> 6;
  uRam30539a = uRam305398 >> 1;
  if (uRam305398 == 0) {
    uRam30a24e = 0;
    uRam305382 = 0;
    DAT_301713 = DAT_301713 & 0xfe;
    bRam301716 = bRam301716 & 0xfe;
  }
  else if (sVar7 == 0) {
    uRam30a24e = 0;
    uRam305382 = 0;
    DAT_301713 = DAT_301713 | 1;
    bRam301716 = bRam301716 & 0xfe;
  }
  else {
    if ((DAT_303334 & 0x10) == 0) {
      uStack_34 = uRam305398;
    }
    else {
      uStack_34 = ~uRam3053ac & uRam305398;
    }
    if ((DAT_303334 & 4) == 0) {
      uStack_32 = uStack_34;
    }
    else {
      uStack_32 = uStack_34 & ~uRam3053a8;
    }
    if ((DAT_303334 & 8) == 0) {
      uStack_30 = uStack_32;
    }
    else {
      uStack_30 = uStack_32 & ~uRam3053aa;
    }
    if ((DAT_301714 & 0x40) == 0) {
      uStack_2e = uStack_30;
    }
    else {
      uStack_2e = uStack_30 & ~uRam3053b2;
    }
    if (((DAT_303334 & 2) == 0) && ((DAT_303334 & 1) == 0)) {
      uStack_2c = uStack_2e;
    }
    else {
      uStack_2c = uStack_2e & ~uRam3053a6;
    }
    if ((bRam301716 & 1) == 0) {
      uStack_2a = uStack_2c;
    }
    else {
      uStack_2a = uStack_2c & ~uRam3053a0;
    }
    if (((DAT_303332 & 1) == 0) || ((DAT_301714 & 0x20) == 0)) {
      uStack_28 = uStack_2a;
    }
    else {
      uStack_28 = uStack_2a & ~uRam3053b0;
    }
    if ((bRam01a15f & 1) == 0 || (bRam30332c & 0x80) == 0) {
      uStack_26 = uStack_28;
    }
    else {
      uStack_26 = uStack_28 & ~uRam3053ae;
    }
    if (bVar2) {
      bVar8 = 0;
    }
    if (bVar8 == 0) {
      uStack_24 = uStack_26;
    }
    else {
      uStack_24 = uStack_26 & ~uRam3053a4;
    }
    if (bVar4 == 0) {
      uRam30a24e = uStack_24;
    }
    else {
      uRam30a24e = uStack_24 & ~uRam3053a2;
    }
    uRam305382 = uRam305398 ^ uRam30a24e;
    if (uRam30539a < uRam305382) {
      if (uRam30539a < uStack_34) {
        if (uRam30539a < uStack_32) {
          if (uRam30539a < uStack_30) {
            if (uRam30539a < uStack_2e) {
              if (uRam30539a < uStack_2c) {
                if (uRam30539a < uStack_2a) {
                  if (uRam30539a < uStack_28) {
                    if (uRam30539a < uStack_26) {
                      if (uRam30539a < uStack_24) {
                        if (uRam30a24e <= uRam30539a) {
                          uVar9 = bRam30a041 + 1;
                          if (0xff < uVar9) {
                            uVar9 = 0xff;
                          }
                          bRam30a041 = (byte)uVar9;
                        }
                      }
                      else {
                        uVar9 = bRam30a042 + 1;
                        if (0xff < uVar9) {
                          uVar9 = 0xff;
                        }
                        bRam30a042 = (byte)uVar9;
                      }
                    }
                    else {
                      uVar9 = bRam30a047 + 1;
                      if (0xff < uVar9) {
                        uVar9 = 0xff;
                      }
                      bRam30a047 = (byte)uVar9;
                    }
                  }
                  else {
                    uVar9 = bRam30a048 + 1;
                    if (0xff < uVar9) {
                      uVar9 = 0xff;
                    }
                    bRam30a048 = (byte)uVar9;
                  }
                }
                else {
                  uVar9 = bRam30a040 + 1;
                  if (0xff < uVar9) {
                    uVar9 = 0xff;
                  }
                  bRam30a040 = (byte)uVar9;
                }
              }
              else {
                uVar9 = bRam30a043 + 1;
                if (0xff < uVar9) {
                  uVar9 = 0xff;
                }
                bRam30a043 = (byte)uVar9;
              }
            }
            else {
              uVar9 = bRam30a049 + 1;
              if (0xff < uVar9) {
                uVar9 = 0xff;
              }
              bRam30a049 = (byte)uVar9;
            }
          }
          else {
            uVar9 = bRam30a045 + 1;
            if (0xff < uVar9) {
              uVar9 = 0xff;
            }
            bRam30a045 = (byte)uVar9;
          }
        }
        else {
          uVar9 = bRam30a044 + 1;
          if (0xff < uVar9) {
            uVar9 = 0xff;
          }
          bRam30a044 = (byte)uVar9;
        }
      }
      else {
        uVar9 = bRam30a046 + 1;
        if (0xff < uVar9) {
          uVar9 = 0xff;
        }
        bRam30a046 = (byte)uVar9;
        bRam301716 = bRam301716 & 0xfe;
      }
    }
    else {
      uRam305382 = 0;
    }
  }
  uRam30537a = uRam30a250;
  uStack_38 = 0x8000;
  if (uRam30a24e == 0) {
    uRam305378 = 0;
    uRam30537a = 0;
  }
  else {
    while (uStack_38 != 0) {
      if ((uStack_38 & uRam30a24e) == 0) {
        uStack_38 = uStack_38 >> 1;
      }
      else {
        uRam305378 = uStack_38;
        uStack_38 = 0;
      }
    }
  }
  if ((1 << (ushort)bRam01a18c & uRam305378) == 0) {
    uRam30a250 = uRam305378;
  }
  else if ((1 << (ushort)bRam01a18c & uRam305378) == 0) {
    uRam30a250 = 0;
  }
  else {
    uRam30a250 = 1 << (ushort)bRam01a17a;
  }
  if (uRam30a250 != 0) {
    if (uRam30a250 == uRam30537a) {
      DAT_301713 = DAT_301713 & 0xfe;
    }
    else {
      DAT_301713 = DAT_301713 | 1;
    }
    if ((DAT_301713 & 1) == 0) {
      bVar2 = uRam3053b4 + 1 < uRam3053b4;
      bVar3 = uRam3053b4 == 0xffff;
      uRam3053b4 = uRam3053b4 + 1;
      if (((bVar2 || bVar3) != (uRam3053b4 != 0xffff) || uRam3053b4 != 0xffff) &&
          ((bVar2 || bVar3) || uRam3053b4 == 0xffff)) {
        uRam3053b4 = 0xffff;
      }
      if (uRam0241ba < uRam3053b4) {
        DAT_301714 = DAT_301714 | 0x40;
      }
      else {
        DAT_301714 = DAT_301714 & 0xbf;
      }
    }
    else {
      uRam3053b4 = 0;
      DAT_301714 = DAT_301714 & 0xbf;
    }
  }
  uStack_36 = 0x8000;
  if (uRam305382 == 0) {
    _DAT_305384 = 0;
  }
  else {
    while (uStack_36 != 0) {
      if ((uStack_36 & uRam305382) == 0) {
        uStack_36 = uStack_36 >> 1;
      }
      else {
        _DAT_305384 = uStack_36;
        uStack_36 = 0;
      }
    }
  }
  if ((1 << (ushort)bRam01a193 & _DAT_305384) == 0) {
    if ((1 << (ushort)bRam01a191 & _DAT_305384) == 0) {
      if ((1 << (ushort)bRam01a18f & _DAT_305384) == 0) {
        if ((1 << (ushort)bRam01a190 & _DAT_305384) == 0) {
          if ((1 << (ushort)bRam01a18b & _DAT_305384) == 0) {
            if ((1 << (ushort)bRam01a18a & _DAT_305384) == 0) {
              if ((1 << (ushort)bRam01a194 & _DAT_305384) == 0) {
                if ((1 << (ushort)bRam01a18d & _DAT_305384) == 0) {
                  if ((1 << (ushort)bRam01a18e & _DAT_305384) == 0) {
                    if ((1 << (ushort)bRam01a192 & _DAT_305384) != 0) {
                      uVar9 = bRam30a055 + 1;
                      if (0xff < uVar9) {
                        uVar9 = 0xff;
                      }
                      bRam30a055 = (byte)uVar9;
                    }
                  }
                  else {
                    uVar9 = bRam30a051 + 1;
                    if (0xff < uVar9) {
                      uVar9 = 0xff;
                    }
                    bRam30a051 = (byte)uVar9;
                  }
                }
                else {
                  uVar9 = bRam30a050 + 1;
                  if (0xff < uVar9) {
                    uVar9 = 0xff;
                  }
                  bRam30a050 = (byte)uVar9;
                }
              }
              else {
                uVar9 = bRam30a057 + 1;
                if (0xff < uVar9) {
                  uVar9 = 0xff;
                }
                bRam30a057 = (byte)uVar9;
              }
            }
            else {
              uVar9 = bRam30a04e + 1;
              if (0xff < uVar9) {
                uVar9 = 0xff;
              }
              bRam30a04e = (byte)uVar9;
            }
          }
          else {
            uVar9 = bRam30a04f + 1;
            if (0xff < uVar9) {
              uVar9 = 0xff;
            }
            bRam30a04f = (byte)uVar9;
          }
        }
        else {
          uVar9 = bRam30a053 + 1;
          if (0xff < uVar9) {
            uVar9 = 0xff;
          }
          bRam30a053 = (byte)uVar9;
        }
      }
      else {
        uVar9 = bRam30a052 + 1;
        if (0xff < uVar9) {
          uVar9 = 0xff;
        }
        bRam30a052 = (byte)uVar9;
      }
    }
    else {
      uVar9 = bRam30a054 + 1;
      if (0xff < uVar9) {
        uVar9 = 0xff;
      }
      bRam30a054 = (byte)uVar9;
    }
  }
  else {
    uVar9 = bRam30a056 + 1;
    if (0xff < uVar9) {
      uVar9 = 0xff;
    }
    bRam30a056 = (byte)uVar9;
  }
  if ((uRam30a250 & uRam0241a6) == 0) {
    if ((DAT_303331 & 1) == 0) {
      bRam30a0e5 = bRam30a0e5 & 0xfb;
    }
  }
  else {
    bRam30a0e5 = bRam30a0e5 | 4;
  }
  if ((~uRam0241a6 & uRam30a250) == 0) {
    if ((DAT_303331 & 1) == 0) {
      bRam30a0e4 = bRam30a0e4 & 0xfb;
    }
  }
  else {
    bRam30a0e4 = bRam30a0e4 | 4;
  }
  if (uRam30a250 == 0) {
    if ((DAT_303331 & 1) == 0) {
      DAT_301714 = DAT_301714 & 0xe7;
    }
  }
  else {
    if ((uRam30a250 & uRam0241a6) == 0) {
      DAT_301714 = DAT_301714 & 0xef;
    }
    else {
      DAT_301714 = DAT_301714 | 0x10;
    }
    if ((~uRam0241a6 & uRam30a250) == 0) {
      DAT_301714 = DAT_301714 & 0xf7;
    }
    else {
      DAT_301714 = DAT_301714 | 8;
    }
  }
  if ((DAT_301713 & 1) != 0) {
    if ((1 << (ushort)bRam01a193 & uRam30a250) == 0) {
      if ((1 << (ushort)bRam01a191 & uRam30a250) == 0) {
        if ((1 << (ushort)bRam01a18f & uRam30a250) == 0) {
          if ((1 << (ushort)bRam01a190 & uRam30a250) == 0) {
            if ((1 << (ushort)bRam01a18b & uRam30a250) == 0) {
              if ((1 << (ushort)bRam01a18a & uRam30a250) == 0) {
                if ((1 << (ushort)bRam01a18d & uRam30a250) == 0) {
                  if ((1 << (ushort)bRam01a192 & uRam30a250) == 0) {
                    if ((1 << (ushort)bRam01a18e & uRam30a250) == 0) {
                      if ((1 << (ushort)bRam01a194 & uRam30a250) != 0) {
                        uVar9 = bRam3049bb + 1;
                        if (0xff < uVar9) {
                          uVar9 = 0xff;
                        }
                        bRam3049bb = (byte)uVar9;
                      }
                    }
                    else {
                      uVar9 = bRam3049b5 + 1;
                      if (0xff < uVar9) {
                        uVar9 = 0xff;
                      }
                      bRam3049b5 = (byte)uVar9;
                    }
                  }
                  else {
                    uVar9 = bRam3049b9 + 1;
                    if (0xff < uVar9) {
                      uVar9 = 0xff;
                    }
                    bRam3049b9 = (byte)uVar9;
                  }
                }
                else {
                  uVar9 = bRam3049b4 + 1;
                  if (0xff < uVar9) {
                    uVar9 = 0xff;
                  }
                  bRam3049b4 = (byte)uVar9;
                }
              }
              else {
                uVar9 = bRam3049b2 + 1;
                if (0xff < uVar9) {
                  uVar9 = 0xff;
                }
                bRam3049b2 = (byte)uVar9;
              }
            }
            else {
              uVar9 = bRam3049b3 + 1;
              if (0xff < uVar9) {
                uVar9 = 0xff;
              }
              bRam3049b3 = (byte)uVar9;
            }
          }
          else {
            uVar9 = bRam3049b7 + 1;
            if (0xff < uVar9) {
              uVar9 = 0xff;
            }
            bRam3049b7 = (byte)uVar9;
          }
        }
        else {
          uVar9 = bRam3049b6 + 1;
          if (0xff < uVar9) {
            uVar9 = 0xff;
          }
          bRam3049b6 = (byte)uVar9;
        }
      }
      else {
        uVar9 = bRam3049b8 + 1;
        if (0xff < uVar9) {
          uVar9 = 0xff;
        }
        bRam3049b8 = (byte)uVar9;
      }
    }
    else {
      uVar9 = bRam3049ba + 1;
      if (0xff < uVar9) {
        uVar9 = 0xff;
      }
      bRam3049ba = (byte)uVar9;
    }
  }
  if (((uRam3035f8 & 0x8000) == 0) || (uRam30a250 != 0)) {
    uVar6 = 0;
  }
  else {
    uVar6 = 1;
  }
  cRam3009f8 = func_0x032e88(0x89f9,uVar6,uRam01a198);
  if (cRam3009f8 != '\0') {
    DAT_301714 = DAT_301714 & 0xfb;
  }
  bVar2 = (1 << (ushort)bRam01a18b & uRam30a250) != 0;
  uRam300a06 = bVar2 && cRam300a07 == '\0';
  if ((bool)uRam300a06) {
    uVar9 = bRam30a04b + 1;
    if (0xff < uVar9) {
      uVar9 = 0xff;
    }
    bRam30a04b = (byte)uVar9;
  }
  if (((DAT_303334 & 1) == 0) && ((DAT_303334 & 2) == 0)) {
    bVar3 = false;
  }
  else {
    bVar3 = true;
  }
  uRam300a04 = bVar3 && cRam300a05 == '\0';
  if ((bool)uRam300a04) {
    uVar9 = bRam30a04d + 1;
    if (0xff < uVar9) {
      uVar9 = 0xff;
    }
    bRam30a04d = (byte)uVar9;
  }
  bVar1 = (uRam30a252 & uRam0241a6) != 0;
  if (((!bVar3) && (bVar1)) || ((bRam301716 & 1) != 0)) {
    bRam30a04d = 0;
  }
  uRam300a08 = bVar1 && cRam300a09 == '\0';
  if (bRam01a189 < bRam30a04d) {
    DAT_301714 = DAT_301714 | 1;
  }
  else {
    DAT_301714 = DAT_301714 & 0xfe;
  }
  if ((DAT_301713 & 1) == 0) {
    if (((bool)uRam300a04) || ((bool)uRam300a08)) {
      uVar5 = 2;
      DAT_301714 = DAT_301714 | 2;
    }
    else {
      uVar5 = 0;
    }
  }
  else {
    uVar5 = 0xfd;
    DAT_301714 = DAT_301714 & 0xfd;
  }
  cRam300a05 = bVar3;
  cRam300a07 = bVar2;
  cRam300a09 = bVar1;
  return uVar5;
}


// ================= diag_brake_booster @ 0724e2 =================

/* DIAGNOSTIC: brake-booster (BKV) vacuum diag -> byte_304753 fault */

void diag_brake_booster(void)

{
  ushort uVar1;
  ushort uVar2;
  
  MDH = MDL;
  if ((uRam00fdfe & 2) != 0) {
    if (((((bRam018aad < bRam30400b) || (bRam018aaf < bRam304e27)) ||
         (bRam018ab0 < rpmclass_oppoint)) || (uRam021658 < uRam305112)) ||
       (((bRam018aae < bRam304752 && (bRam018ab1 < rpmclass_oppoint)) &&
        (((uRam00fd36 & 0x4000) == 0 && (cRam304757 != '\x03')))))) {
      uRam30a17a = uRam02165a;
      uRam30a17c = uRam02165c;
      uRam30a17e = uRam02165e;
      uRam30a180 = uRam021660;
      uRam30a182 = uRam021662;
      uRam30a184 = uRam021664;
      bRam30a00e = bRam018aa7;
      uRam30a00f = uRam018aa8;
      uRam30a010 = uRam018aa9;
      uRam30a011 = uRam018aaa;
      uRam30a012 = uRam018aab;
      uRam30a013 = uRam018aac;
      uRam30a00b = 1;
      bRam30a00c = bRam018aa7;
      uRam30a186 = 0;
      uRam3035f8 = uRam3035f8 | 8;
    }
    else if ((((bRam018ac3 < bRam30400b) || (bRam018ac5 < bRam304e27)) ||
             ((bRam018ac6 < rpmclass_oppoint || (uRam021674 < uRam305112)))) ||
            ((((bRam018ac4 < bRam304752 && (bRam018ac7 < rpmclass_oppoint)) &&
              ((uRam00fd36 & 0x4000) == 0)) && (cRam304757 != '\x03')))) {
      uRam30a17a = uRam021676;
      uRam30a17c = uRam021678;
      uRam30a17e = uRam02167a;
      uRam30a180 = uRam02167c;
      uRam30a182 = uRam02167e;
      uRam30a184 = uRam021680;
      bRam30a00e = bRam018abd;
      uRam30a00f = uRam018abe;
      uRam30a010 = uRam018abf;
      uRam30a011 = uRam018ac0;
      uRam30a012 = uRam018ac1;
      uRam30a013 = uRam018ac2;
      uRam30a00b = 1;
      bRam30a00c = bRam018abd;
      uRam30a186 = 0;
      uRam3035f8 = uRam3035f8 | 8;
    }
    else if ((((bRam018ab8 < bRam30400b) || (bRam018aba < bRam304e27)) ||
             ((bRam018abb < rpmclass_oppoint || (uRam021666 < uRam305112)))) ||
            (((bRam018ab9 < bRam304752 && (bRam018abc < rpmclass_oppoint)) &&
             (((uRam00fd36 & 0x4000) == 0 && (cRam304757 != '\x03')))))) {
      uRam30a17a = uRam021668;
      uRam30a17c = uRam02166a;
      uRam30a17e = uRam02166c;
      uRam30a180 = uRam02166e;
      uRam30a182 = uRam021670;
      uRam30a184 = uRam021672;
      bRam30a00e = bRam018ab2;
      uRam30a00f = uRam018ab3;
      uRam30a010 = uRam018ab4;
      uRam30a011 = uRam018ab5;
      uRam30a012 = uRam018ab6;
      uRam30a013 = uRam018ab7;
      uRam30a00b = 1;
      bRam30a00c = bRam018ab2;
      uRam30a186 = 0;
      uRam3035f8 = uRam3035f8 | 8;
    }
  }
  switch(uRam30a00b) {
  case 0:
    uRam3035f8 = uRam3035f8 & 0xfff7;
    DAT_01200c._0_1_ = 0;
    break;
  case 1:
    if (uRam01217a < uRam012186) {
      DAT_01200c._0_1_ = DAT_01200e._1_1_;
      DAT_01200a._1_1_ = 2;
    }
    uRam012186 = uRam012186 + 1;
    break;
  case 2:
    if (uRam01217c < uRam012186) {
      DAT_01200c._0_1_ = uRam012010;
      DAT_01200a._1_1_ = 3;
    }
    uRam012186 = uRam012186 + 1;
    break;
  case 3:
    if (uRam01217e < uRam012186) {
      DAT_01200c._0_1_ = uRam012011;
      DAT_01200a._1_1_ = 4;
    }
    uRam012186 = uRam012186 + 1;
    break;
  case 4:
    if (uRam012180 < uRam012186) {
      DAT_01200c._0_1_ = uRam012012;
      DAT_01200a._1_1_ = 5;
    }
    uRam012186 = uRam012186 + 1;
    break;
  case 5:
    if (uRam012182 < uRam012186) {
      DAT_01200c._0_1_ = uRam012013;
      DAT_01200a._1_1_ = 6;
    }
    uRam012186 = uRam012186 + 1;
    break;
  case 6:
    if (uRam012184 < uRam012186) {
      DAT_01200c._0_1_ = 0;
      DAT_01200a._1_1_ = 0;
    }
    uRam012186 = uRam012186 + 1;
  }
  uVar1 = (ushort)bRam018b38;
  uRam30be0e = (ushort)bRam30a00c;
  MDL = MDL / uVar1;
  MDH = MDH % uVar1;
  MDC = MDC | 0x10;
  if (uVar1 == 0) {
    uRam30a00d = 0xff;
  }
  else {
    uRam30a00d = (undefined1)MDL;
  }
  uVar1 = me7_lookup_1d_byte(0xae8,6,uRam30a00d);
  uVar2 = me7_lookup_1d_byte(0xb1d,6,uRam301839);
  MDL = (uVar1 & 0xff) * (uVar2 & 0xff);
  MDH = 0;
  MDC = MDC | 0x10;
  uRam30061a = MDL;
  if (MDL < 0x7fff) {
    brake_booster_diag = (byte)(MDL >> 7);
  }
  else {
    brake_booster_diag = 0xff;
  }
  bRam300630 = brake_booster_diag;
  if ((uRam00fd36 & 0x4000) != 0) {
    brake_booster_diag = uRam018acd;
    return;
  }
  if (brake_booster_diag <= bRam018bf0) {
    bRam018630 = bRam018bf0;
  }
  if (bRam018bf1 <= brake_booster_diag) {
    brake_booster_diag = bRam018bf1;
  }
  return;
}


// ================= diag_brake_booster_front @ 072c02 =================

/* WARNING: Removing unreachable block (ram,0x0730ec) */
/* WARNING: Removing unreachable block (ram,0x07301e) */
/* WARNING: Removing unreachable block (ram,0x073080) */
/* WARNING: Removing unreachable block (ram,0x07335a) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC: brake-booster diag front-end / state machine */

void diag_brake_booster_front(void)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  byte bVar5;
  byte bVar6;
  ushort uVar7;
  ushort uVar8;
  
  uVar2 = CONCAT22(MDH,MDL);
  if (((_flags_start_phase & 0x8000) != 0) && (uVar2 = CONCAT22(MDH,MDL), (bRam30062c & 0x20) == 0))
  {
    uVar2 = (uint)uRam3055d0 * 10;
    uRam30061a = (ushort)uVar2;
    MDC = MDC | 0x10;
    if (0xffff < uVar2) {
      uRam30061a = 0xffff;
    }
    bVar1 = uRam30a188 < uRam30861a;
    uRam30a188 = uRam30a188 - uRam30861a;
    if (bVar1) {
      uRam30a188 = 0;
    }
  }
  MDH = (ushort)(uVar2 >> 0x10);
  MDL = (ushort)uVar2;
  if ((_flags_start_phase & 0x8000) == 0) {
    bRam30062c = bRam30062c & 0xdf;
  }
  else {
    bRam30062c = bRam30062c | 0x20;
  }
  if (((uRam30256a & 8) == 0) || ((bRam30062c & 0x10) != 0)) {
    if (((uRam303b2e & 0xf00) == 0x100) && ((bRam30062c & 8) == 0)) {
      uRam30a188 = uRam021688;
    }
  }
  else {
    uRam30a188 = uRam021686;
  }
  if ((uRam30256a & 8) == 0) {
    bRam30062c = bRam30062c & 0xef;
  }
  else {
    bRam30062c = bRam30062c | 0x10;
  }
  if ((uRam303b2e & 0xf00) == 0x100) {
    bRam30062c = bRam30062c | 8;
  }
  else {
    bRam30062c = bRam30062c & 0xf7;
  }
  if (uRam30a188 == 0) {
    uRam00fd36 = uRam00fd36 & 0xbfff;
  }
  else {
    uRam30a188 = uRam30a188 - 1;
    if (((uRam30bbea & 1) == 0) && (rpmclass_oppoint < bRam018bf8)) {
      uRam00fd36 = uRam00fd36 | 0x4000;
    }
    else {
      uRam00fd36 = uRam00fd36 & 0xbfff;
    }
  }
  if ((_flags_start_phase & 0x8000) == 0) {
    uRam300632 = me7_fraction_blend(uRam018bf5,uRam304716,uRam304632);
    iVar3 = CONCAT22(MDH,MDL);
    uRam304752 = (undefined1)((ushort)uRam300632 >> 8);
    if ((uRam00fdfe & 4) != 0) {
      uRam00fdfe = uRam00fdfe | 1;
    }
    if (((uRam00fd36 & 0x4000) == 0) && (cRam304757 != '\x03')) {
      diag_brake_booster();
      iVar3 = CONCAT22(MDH,MDL);
      uRam00fdfe = uRam00fdfe & 0xfffd;
      uVar4 = CONCAT22(uRam300628._2_2_,(undefined2)uRam300628);
    }
    else {
      uRam30a00c = 0;
      uRam30a00b = 0;
      uRam3035f8 = uRam3035f8 & 0xfff7;
      uRam30a17a = 0;
      uRam30a17c = 0;
      uRam30a17e = 0;
      uRam30a180 = 0;
      uRam30a182 = 0;
      uRam30a184 = 0;
      uRam30a00e = 0;
      uRam30a00f = 0;
      uRam30a010 = 0;
      uRam30a011 = 0;
      uRam30a012 = 0;
      uRam30a013 = 0;
      cRam30a00d = '\0';
      uVar4 = CONCAT22(uRam300628._2_2_,(undefined2)uRam300628);
    }
  }
  else {
    uRam30a00c = 0;
    uRam30a00b = 0;
    uRam3035f8 = uRam3035f8 & 0xfff7;
    uRam30a17a = 0;
    uRam30a17c = 0;
    uRam30a17e = 0;
    uRam30a180 = 0;
    uRam30a182 = 0;
    uRam30a184 = 0;
    uRam30a00e = 0;
    uRam30a00f = 0;
    uRam30a010 = 0;
    uRam30a011 = 0;
    uRam30a012 = 0;
    uRam30a013 = 0;
    uRam00fdfe = uRam00fdfe & 0xfffe | 6;
    if ((bRam30062c & 1) == 0) {
      if (bRam018bbc <= bRam301839) {
        bRam30062c = bRam30062c | 1;
        uRam00fd36 = uRam00fd36 & 0xdfff;
      }
    }
    else if (bRam301839 <= bRam018bbb) {
      bRam30062c = bRam30062c & 0xfe;
      uRam00fd36 = uRam00fd36 | 0x2000;
    }
    bRam304749 = bRam018b7a;
    if ((uRam30256c & 0x800) == 0) {
      bRam304749 = 0;
    }
    uRam300628 = me7_pt1_integrator((ushort)bRam018bfa << 8,(ushort)rpmclass_oppoint << 8,
                                    uRam300628._2_2_,(undefined2)uRam300628);
    uRam305114 = (ushort)((uint)uRam300628 >> 0x10);
    uVar7 = uRam305114 - uRam30461e;
    if (uRam305114 < uRam30461e) {
      uVar7 = 0;
    }
    uRam305112 = uVar7 + 0x4000;
    if (uVar7 + 0x4000 < 0x4000 || uVar7 + 0x4000 < uVar7) {
      uRam305112 = 0xffff;
    }
    uRam30461e = uRam305114;
    if ((uRam00fd36 & 0x2000) == 0) {
      bRam30474d = me7_lookup_1d_byte(0xb46,6,rpmclass_oppoint);
    }
    else {
      bRam30474d = me7_lookup_1d_byte(0xb53,6,rpmclass_oppoint);
    }
    if ((bRam30462c & 2) == 0) {
      if (uRam021684 <= uRam305112) {
        bRam30062c = bRam30062c | 2;
      }
    }
    else if (uRam305112 <= uRam021682) {
      bRam30062c = bRam30062c & 0xfd;
    }
    if ((bRam018bf9 < rpmclass_oppoint) && ((bRam30062c & 2) != 0)) {
      bRam30474e = bRam018bba;
    }
    else {
      bRam30474e = 0;
    }
    if ((bRam304d30 < bRam018bfb) || (bRam018bfc < bRam304d30)) {
      bRam304748 = 0;
    }
    else {
      bRam304748 = me7_lookup_2d_byte(0xb7b,6,vfzg_class,rpmclass_oppoint);
    }
    bVar5 = bRam30474d + bRam30474e;
    if ((byte)(bRam30474d + bRam30474e) < bRam30474d || (byte)(bRam30474d + bRam30474e) < bRam30474e
       ) {
      bVar5 = 0xff;
    }
    if ((bRam304748 <= bVar5) &&
       (bRam304748 = bRam30474d + bRam30474e,
       (byte)(bRam30474d + bRam30474e) < bRam30474d || (byte)(bRam30474d + bRam30474e) < bRam30474e)
       ) {
      bRam304748 = 0xff;
    }
    bVar5 = me7_lookup_1d_byte(0xbad,6,uRam30400b);
    bVar6 = me7_lookup_2d_byte(0xbbe,6,uRam301626,rl_byte);
    if (bVar6 < bVar5) {
      bRam304747 = me7_lookup_1d_byte(0xbad,6,uRam30400b);
    }
    else {
      bRam304747 = me7_lookup_2d_byte(0xbbe,6,uRam301626,rl_byte);
    }
    bRam304746 = me7_lookup_1d_byte(0xb39,6,uRam304716);
    if ((uRam00fd36 & 0x2000) == 0) {
      bRam300622 = me7_lookup_1d_byte(0xb60,6,bRam3014cf);
    }
    else {
      bRam300622 = me7_lookup_1d_byte(0xb6d,6,bRam3014cf);
    }
    uVar7 = me7_lookup_1d_byte(0xb2b,6,vfzg_class);
    MDL = (ushort)bRam300622 * (uVar7 & 0xff);
    bRam300634 = (byte)(MDL >> 7);
    bRam304745 = bRam300634;
    if (((bRam3014cf < bRam018bf2) || (bRam018bfd < vfzg_class)) || ((bRam301447 & 1) == 0)) {
      if ((uRam300624 != 0) && (uRam300624 = uRam300624 - 1, bRam300634 < bRam018aa6)) {
        bRam304745 = bRam018aa6;
      }
    }
    else {
      if (bRam300634 < bRam018aa6) {
        bRam304745 = bRam018aa6;
      }
      MDL = (ushort)bRam018bf6 * 10;
      uRam300624 = MDL;
    }
    if (((uRam00fd38 & 0x40) == 0) && ((bRam30062c & 0x40) != 0)) {
      MDL = (ushort)bRam018bf7 * 10;
      uRam30062e = MDL;
    }
    MDC = MDC | 0x10;
    MDH = 0;
    if (((uRam00fd38 & 0x40) == 0) &&
       ((((uRam00fd38 & 0x40) != 0 || ((bRam30062c & 0x40) == 0)) && (uRam30062e != 0)))) {
      uRam30062e = uRam30062e - 1;
    }
    if (((uRam30062e == 0) || ((uRam00fd38 & 0x40) != 0)) || (bRam304744 < bRam304745)) {
      bRam304744 = bRam304745;
    }
    if ((uRam00fd38 & 0x40) == 0) {
      bRam30062c = bRam30062c & 0xbf;
    }
    else {
      bRam30062c = bRam30062c | 0x40;
    }
    if ((uRam303bea & 1) == 0) {
      bRam30474c = bRam304748;
      bRam304743 = me7_lookup_1d_byte(0xadb,6,rpmclass_oppoint);
    }
    else {
      bRam30474c = bRam018acc;
      bRam304743 = bRam018ac9;
    }
    if ((uRam303bac & 1) == 0) {
      bRam30474a = bRam304744;
      bRam304742 = me7_lookup_1d_byte(0xace,6,bRam3014cf);
    }
    else {
      bRam30474a = bRam018aca;
      bRam304742 = bRam018ac8;
    }
    if (((uRam303bfa & 1) == 0) && ((uRam303bd6 & 1) == 0)) {
      bRam30474b = bRam304747;
    }
    else {
      bRam30474b = bRam018acb;
    }
    bRam300630 = bRam304746;
    if (bRam304746 <= bRam304749) {
      bRam300630 = bRam304749;
    }
    if (bRam300630 <= bRam30474c) {
      bRam304630 = bRam30474c;
    }
    if (bRam300630 <= bRam30474b) {
      bRam304630 = bRam30474b;
    }
    bRam304750 = bRam300630;
    if (bRam300630 <= bRam30474a) {
      bRam304750 = bRam30474a;
    }
    if (bRam304751 < bRam304750) {
      uRam300626 = func_0x042d5a(0x1b00,(ushort)bRam018bf4 << 7,uRam300626,0,0x7800);
      bRam304751 = (byte)(uRam300626 >> 7);
      uRam304620 = 0;
    }
    else {
      bVar5 = bRam304751 - bRam018bbd;
      if (bRam304751 < bRam018bbd) {
        bVar5 = 0;
      }
      if (bRam304750 < bVar5) {
        uRam300626 = func_0x042d5a(0x1b00,(ushort)bRam018bf3 * -0x80,uRam300626,0,0x7800);
        bRam304751 = (byte)(uRam300626 >> 7);
        uRam304620 = 0;
      }
    }
    if (bRam304750 == 0) {
      MDL = (ushort)bRam018b2a * 10;
      MDH = 0;
      MDC = MDC | 0x10;
      if (uRam300620 < MDL) {
        uRam300620 = uRam300620 + 1;
      }
      else {
        bRam304751 = 0;
        uRam304626 = 0;
      }
    }
    else {
      uRam300620 = 0;
    }
    bRam300630 = bRam304751;
    if (bRam304751 <= bRam304743) {
      bRam300630 = bRam304743;
    }
    bRam30474f = bRam304742;
    if (bRam304742 <= bRam304630) {
      bRam30474f = bRam300630;
    }
    uRam300632 = me7_fraction_blend(uRam018bf5,uRam304716,uRam304632);
    MDH = MDL;
    uRam304752 = (undefined1)((ushort)uRam300632 >> 8);
    uVar7 = (ushort)bRam018b38;
    uRam307e0e = (ushort)bRam30474f;
    MDL = MDL / uVar7;
    MDH = MDH % uVar7;
    MDC = MDC | 0x10;
    if (uVar7 == 0) {
      cRam30a00d = -1;
    }
    else {
      cRam30a00d = (char)MDL;
    }
    if (cRam30a00d == '\0') {
      uRam00fd36 = uRam00fd36 & 0x7fff;
      bRam30061c = 0;
    }
    else if (bRam30061c < bRam018b1c) {
      bRam30061c = bRam30061c + 1;
      uRam00fd36 = uRam00fd36 | 0x8000;
    }
    else {
      uRam00fd36 = uRam00fd36 & 0x7fff;
    }
    uVar7 = me7_lookup_1d_byte(0xae8,6,cRam30a00d);
    uVar8 = me7_lookup_1d_byte(0xb1d,6,bRam301839);
    iVar3 = (uint)(uVar7 & 0xff) * (uint)(uVar8 & 0xff);
    uRam30061a = (ushort)iVar3;
    MDC = MDC | 0x10;
    if (uRam30061a < 0x7fff) {
      bRam300630 = (byte)(uRam30061a >> 7);
    }
    else {
      bRam300630 = 0xff;
    }
    if ((uRam00fd36 & 0x8000) != 0) {
      bRam300630 = 0;
    }
    uVar4 = uRam300628;
    if ((uRam00fd36 & 0x4000) == 0) {
      if (bRam300630 <= bRam018bf0) {
        bRam018630 = bRam018bf0;
      }
      brake_booster_diag = bRam300630;
      if (bRam018bf1 <= bRam300630) {
        brake_booster_diag = bRam018bf1;
      }
    }
    else {
      brake_booster_diag = bRam018acd;
    }
  }
  uRam300628._2_2_ = (undefined2)((uint)uVar4 >> 0x10);
  uRam300628._0_2_ = (undefined2)uVar4;
  MDH = (ushort)((uint)iVar3 >> 0x10);
  MDL = (ushort)iVar3;
  return;
}


// ================= diag_knock_circuit @ 039fca =================

/* DIAGNOSTIC: knock-control-circuit diag (CDKK*) -> word_FD06/FD08 */

void diag_knock_circuit(void)

{
  bool bVar1;
  ushort uVar2;
  uint uVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  ushort uVar7;
  byte bVar8;
  byte bVar9;
  short sVar10;
  ushort uVar11;
  ushort uVar12;
  ushort uVar13;
  int iVar14;
  
  uRam3018f6 = uRam30193a * 2;
  if (uRam3018f6 < 0x400) {
    bVar5 = (byte)((uRam30193a & 0x7fff) >> 1);
  }
  else {
    bVar5 = 0xff;
  }
  bVar4 = (byte)(uRam301938 >> 2);
  bVar9 = bVar4;
  if (bVar4 <= bRam012630) {
    bVar9 = bRam012630;
  }
  bVar6 = bVar5;
  if (bVar5 <= bRam012630) {
    bVar6 = bRam012630;
  }
  bVar8 = bVar9 - bVar6;
  if (bVar9 < bVar6) {
    if ((char)bVar8 >= '\0') {
      bVar8 = 0x80;
    }
  }
  else if ((char)bVar8 < '\0') {
    bVar8 = 0x7f;
  }
  if (bVar8 == 0x80) {
    bVar8 = 0x7f;
  }
  else if ((char)bVar8 < '\0') {
    bVar8 = -bVar8;
  }
  if (((bVar4 <= bRam01263d) || (bVar9 = bRam01261f, bVar5 <= bRam01263d)) &&
     ((bVar4 <= bRam012638 || (bVar9 = bRam01261e, bVar5 <= bRam012638)))) {
    bVar9 = bRam01261d;
  }
  if (bVar9 < bVar8) {
    uRam00fd06 = uRam00fd06 | 0x800;
  }
  else {
    uRam00fd06 = uRam00fd06 & 0xf7ff;
  }
  if ((uRam00fd68 & 0x2000) == 0) {
    bRam301256 = bRam301256 & 0xf7;
    bRam301255 = bRam301255 & 0xfe;
    bRam301254 = bRam301254 & 0xfb;
    bRam30010a = bRam30010a & 0xfc;
    cRam3000e1 = cRam012627;
    cRam3000e2 = cRam012629;
  }
  else {
    if (bRam012631 < bVar4) {
      bRam301256 = bRam301256 | 8;
      if (cRam3000e1 == '\0') {
        bRam301255 = bRam301255 | 0x10;
      }
      else {
        cRam3000e1 = cRam3000e1 + -1;
      }
    }
    else {
      bRam301256 = bRam301256 & 0xf7;
      cRam3000e1 = cRam012627;
    }
    if (bRam012633 < bVar5) {
      if (cRam3000e2 == '\0') {
        bRam301255 = bRam301255 | 0x41;
      }
      else {
        cRam3000e2 = cRam3000e2 + -1;
        bRam301255 = bRam301255 | 1;
      }
    }
    else {
      cRam3000e2 = cRam012629;
      bRam301255 = bRam301255 & 0xfe;
    }
    if (((((bRam301255 & 0x10) == 0) && ((bRam301255 & 0x40) == 0)) && ((uRam00fd06 & 0x800) != 0))
       && ((uRam00fd06 & 0x4000) == 0)) {
      bVar9 = bRam301254 | 4;
      if (((bRam301254 & 0x10) == 0) && (bVar4 < bRam012632)) {
        bRam30010a = bRam30010a | 1;
      }
      else {
        bRam30010a = bRam30010a & 0xfe;
      }
      bVar6 = bRam301254 & 0x40;
      bRam301254 = bVar9;
      if ((bVar6 == 0) && (bVar5 < bRam012634)) {
        bRam30010a = bRam30010a | 2;
        goto LAB_03a1b2;
      }
    }
    else {
      bRam30010a = bRam30010a & 0xfe;
      bRam301254 = bRam301254 & 0xfb;
    }
    bRam30010a = bRam30010a & 0xfd;
  }
LAB_03a1b2:
  if (((((bRam301256 & 8) == 0) && ((bRam301255 & 1) == 0)) && ((bRam301254 & 4) == 0)) &&
     ((uRam00fd06 & 0x4000) == 0)) {
    bRam301256 = bRam301256 | 4;
  }
  else {
    bRam301256 = bRam301256 & 0xfb;
  }
  if ((bRam01261c & 0x20) != 0) {
    if ((bVar4 < bRam012632) && (bVar5 < bRam012634)) {
      bRam300109 = bRam300109 | 0x80;
    }
    else {
      bRam300109 = bRam300109 & 0x7f;
    }
  }
  if (((bRam300109 & 0x80) == 0) && ((bRam30010a & 1) == 0)) {
    bRam301256 = bRam301256 & 0xef;
    cRam3000e4 = cRam012628;
  }
  else {
    bRam301256 = bRam301256 | 0x10;
    if (cRam3000e4 == '\0') {
      bRam301255 = bRam301255 | 8;
    }
    else {
      cRam3000e4 = cRam3000e4 + -1;
    }
  }
  if (((bRam300109 & 0x80) == 0) && ((bRam30010a & 2) == 0)) {
    bRam301255 = bRam301255 & 0xfd;
    cRam3000e5 = cRam01262a;
  }
  else if (cRam3000e5 == '\0') {
    bRam301255 = bRam301255 | 0x22;
  }
  else {
    cRam3000e5 = cRam3000e5 + -1;
    bRam301255 = bRam301255 | 2;
  }
  if ((((bRam301254 & 4) == 0) || ((bRam301255 & 8) != 0)) || ((bRam301255 & 0x20) != 0)) {
    bRam301254 = bRam301254 & 0xf7;
    cRam3000e3 = cRam012626;
  }
  else {
    bRam301254 = bRam301254 | 8;
    if (cRam3000e3 == '\0') {
      bRam301255 = bRam301255 | 4;
    }
    else {
      cRam3000e3 = cRam3000e3 + -1;
    }
  }
  if ((bRam301256 & 4) == 0) {
    cRam3000e6 = cRam012623;
  }
  else {
    if (bVar4 < bRam012632) {
      if (cRam3000e6 == '\0') {
        bRam301256 = bRam301256 | 1;
      }
      else {
        cRam3000e6 = cRam3000e6 + -1;
      }
    }
    else {
      cRam3000e6 = cRam012623;
    }
    if (((bRam012639 < bVar4) && (bRam012639 < bVar5)) && ((bRam301256 & 1) != 0)) {
      bRam301254 = bRam301254 | 0x20;
    }
  }
  if (((bRam303187 & 1) == 0) && ((bRam301254 & 0x20) == 0)) {
    bRam301254 = bRam301254 & 0xef;
  }
  else {
    bRam301254 = bRam301254 | 0x10;
  }
  if ((bRam301256 & 4) == 0) {
    cRam3000e7 = cRam012624;
  }
  else {
    if (bVar5 < bRam012634) {
      if (cRam3000e7 == '\0') {
        bRam301256 = bRam301256 | 2;
      }
      else {
        cRam3000e7 = cRam3000e7 + -1;
      }
    }
    else {
      cRam3000e7 = cRam012624;
    }
    if (((bRam012639 < bVar4) && (bRam012639 < bVar5)) && ((bRam301256 & 2) != 0)) {
      bRam301254 = bRam301254 | 0x80;
    }
  }
  if (((bRam303187 & 2) == 0) && ((bRam301254 & 0x80) == 0)) {
    bRam301254 = bRam301254 & 0xbf;
  }
  else {
    bRam301254 = bRam301254 | 0x40;
  }
  if (((bRam300108 & 1) == 0) && ((bRam301255 & 4) != 0)) {
    if (bVar5 < bVar4) {
      bVar9 = bRam301255 & 0x40;
    }
    else {
      bVar9 = bRam301255 & 0x10;
    }
    if (bVar9 != 0) {
      bRam300108 = bRam300108 | 1;
    }
  }
  if (((((uRam00fd80 & 0x8000) == 0) && ((uRam00fd68 & 0x2000) != 0)) && ((bRam300108 & 1) == 0)) &&
     ((((bRam301255 & 0x10) == 0 && ((bRam301255 & 8) == 0)) ||
      (((bRam301255 & 0x40) == 0 && ((bRam301255 & 0x20) == 0)))))) {
    uRam00fd08 = uRam00fd08 & 0xfffd;
  }
  else {
    uRam00fd08 = uRam00fd08 | 2;
  }
  if (((bRam301255 & 0x10) == 0) && ((bRam301255 & 8) == 0)) {
    uRam00fd08 = uRam00fd08 & 0xfffe;
    if (((bRam301255 & 0x40) == 0) && ((bRam301255 & 0x20) == 0)) {
      if ((bRam301255 & 4) == 0) {
        uRam00fd06 = uRam00fd06 & 0x3fff;
      }
      else {
        uRam00fd06 = uRam00fd06 & 0x7fff | 0x4000;
      }
    }
    else if ((bRam301255 & 4) == 0) {
      uRam00fd06 = uRam00fd06 | 0xc000;
    }
    else {
      uRam00fd06 = uRam00fd06 & 0x7fff | 0x4000;
    }
  }
  else {
    uRam00fd06 = uRam00fd06 & 0x7fff | 0x4000;
    if (((bRam301255 & 0x40) == 0) && (((bRam301255 & 0x20) == 0 && ((bRam301255 & 4) == 0)))) {
      uRam00fd08 = uRam00fd08 | 1;
    }
    else {
      uRam00fd08 = uRam00fd08 & 0xfffe;
    }
  }
  if ((bVar4 < bRam01262e) && (bVar5 < bRam01262f)) {
    bRam30010a = bRam30010a | 0x80;
  }
  else {
    bRam30010a = bRam30010a & 0x7f;
  }
  if (((uRam00fd68 & 0x2000) != 0) && ((uRam00fd06 & 0x4000) == 0)) {
    uRam3000fa = uRam301938 + uRam30193a * -2;
    if (uRam301938 < uRam3018f6) {
      if ((short)uRam3000fa >= 0) {
        uRam3000fa = 0x8000;
      }
    }
    else if ((short)uRam3000fa < 0) {
      uRam3000fa = 0x7fff;
    }
    if ((bRam30010a & 0x80) != 0) {
      uRam3000fc = func_0x042fe2(uRam3000fa);
      uRam3000fe = func_0x042fe2(sRam3035a0);
      if (uRam3000fc < uRam3000fe) {
        iVar14 = (uint)uRam3000fa << 0x10;
      }
      else {
        iVar14 = me7_slew_limiter(uRam014ef4,uRam3000fa,iRam300104._2_2_,(undefined2)iRam300104);
      }
      iRam300104._2_2_ = (short)((uint)iVar14 >> 0x10);
      sRam3035a0 = iRam300104._2_2_;
      iRam300104 = iVar14;
    }
    sVar10 = sRam3035a0 + sRam014eea;
    if (sRam3035a0 < 0 == sRam014eea < 0 && sRam3035a0 + sRam014eea < 0 != sRam3035a0 < 0) {
      sVar10 = 0x7fff;
    }
    if ((short)(sVar10 - uRam3000fa) < 0 ==
        (sVar10 < 0 != (short)uRam3000fa < 0 && (short)(sVar10 - uRam3000fa) < 0 != sVar10 < 0)) {
      uVar11 = sRam3035a0 - sRam014eea;
      if (sRam3035a0 < 0 != sRam014eea < 0 && sRam3035a0 - sRam014eea < 0 != sRam3035a0 < 0) {
        uVar11 = 0x8000;
      }
      if (uVar11 == uRam3000fa ||
          (short)(uVar11 - uRam3000fa) < 0 !=
          ((short)uVar11 < 0 != (short)uRam3000fa < 0 &&
          (short)(uVar11 - uRam3000fa) < 0 != (short)uVar11 < 0)) {
        cRam3000ed = cRam012622;
        goto LAB_03a560;
      }
    }
    if (cRam3000ed != '\0') {
      cRam3000ed = cRam3000ed + -1;
    }
  }
LAB_03a560:
  iVar14 = CONCAT22(iRam300100._2_2_,(undefined2)iRam300100);
  if ((bRam30010a & 0x80) == 0) {
    if ((((cRam3000ed == '\0') && ((uRam00fd68 & 0x2000) != 0)) && ((uRam00fd06 & 0x4000) == 0)) &&
       ((bVar4 < bRam012635 && (bVar5 < bRam012635)))) {
      bRam301256 = bRam301256 | 0x80;
    }
  }
  else {
    bRam301256 = bRam301256 & 0x7f;
  }
  if ((bRam300109 & 0x20) == 0) {
    bRam300109 = bRam300109 & 0xbf;
  }
  else {
    bRam300109 = bRam300109 | 0x40;
  }
  if (bRam01262d < bVar4) {
    bRam300109 = bRam300109 | 0x20;
  }
  else {
    bRam300109 = bRam300109 & 0xdf;
  }
  if ((((uRam00fd68 & 0x2000) == 0) || ((uRam00fd06 & 0x4000) != 0)) || ((bRam01261c & 1) == 0)) {
    bRam301254 = bRam301254 & 0xfd;
    cRam3000ea = cRam01262b;
  }
  else {
    if ((bRam300108 & 2) == 0) {
      bRam300108 = bRam300108 & 0xfb;
    }
    else {
      bRam300108 = bRam300108 | 4;
    }
    if ((bRam300108 & 8) == 0) {
      bRam300108 = bRam300108 & 0xef;
    }
    else {
      bRam300108 = bRam300108 | 0x10;
    }
    uRam3000f4 = uRam3018f8;
    if (uRam3018f6 < uRam3018f8) {
      iVar14 = (uint)uRam3018f6 << 0x10;
    }
    else {
      iVar14 = me7_pt1_integrator(uRam014ef6,uRam3018f6,iRam300100._2_2_,(undefined2)iRam300100);
    }
    iRam300100._2_2_ = (ushort)((uint)iVar14 >> 0x10);
    uRam3018f8 = iRam300100._2_2_;
    if (bRam01262e < bVar4) {
      cRam3000e9 = cRam012625;
      bRam300108 = bRam300108 & 0xf7 | 2;
    }
    else {
      bRam300108 = bRam300108 & 0xfd;
      if (cRam3000e9 == '\0') {
        bRam300108 = bRam300108 | 8;
      }
      else {
        cRam3000e9 = cRam3000e9 + -1;
      }
    }
    if ((((bRam300108 & 0x10) != 0) && ((bRam300108 & 2) != 0)) && ((bRam300108 & 4) == 0)) {
      uRam3035a2 = uRam3000f4;
    }
    uVar11 = uRam3035a2 + uRam014ee8;
    if (uRam3035a2 + uRam014ee8 < uRam3035a2 || uRam3035a2 + uRam014ee8 < uRam014ee8) {
      uVar11 = 0xffff;
    }
    if (uRam3018f6 < uVar11) {
      bRam30010a = bRam30010a | 0x20;
    }
    else {
      bRam30010a = bRam30010a & 0xdf;
    }
    if (((bRam300109 & 0x20) != 0) && ((bRam300109 & 0x40) == 0)) {
      if ((bRam30010a & 0x20) == 0) {
        bRam301256 = bRam301256 & 0xbf;
      }
      else {
        bRam301256 = bRam301256 | 0x40;
      }
    }
    if (((bRam30010a & 0x20) == 0) || ((bRam300109 & 0x20) == 0)) {
      cRam3000ea = cRam01262b;
      bRam30010a = bRam30010a & 0xbf;
    }
    else if (cRam3000ea == '\0') {
      bRam30010a = bRam30010a | 0x40;
    }
    else {
      cRam3000ea = cRam3000ea + -1;
    }
    if ((((bRam301256 & 0x40) == 0) || ((bRam300109 & 0x20) == 0)) && ((bRam30010a & 0x40) == 0)) {
      bRam301254 = bRam301254 & 0xfd;
    }
    else {
      bRam301254 = bRam301254 | 2;
    }
  }
  if (((bRam301254 & 2) == 0) && ((bRam301255 & 0x80) == 0)) {
    if (bVar4 < bRam01262e) {
      bRam301254 = bRam301254 & 0xfe;
    }
  }
  else {
    bRam301254 = bRam301254 | 1;
  }
  if ((bRam301254 & 1) == 0) {
    bVar5 = bRam300108 & 0xdf;
    if (bVar4 < bRam01262d) {
      bRam300108 = bRam300108 & 0x9f;
    }
    else {
      bVar9 = bRam300108 & 0x40;
      bRam300108 = bVar5;
      if (bVar9 == 0) {
        bRam300108 = bVar5 | 0x40;
        bRam301255 = bRam301255 & 0x7f;
        if (bRam301252 == 0) {
          bRam301252 = 0;
        }
        else {
          bRam301252 = bRam301252 - 1;
        }
      }
    }
  }
  else {
    bVar5 = bRam300108 & 0xbf;
    if (bVar4 < bRam01263b) {
      bRam300108 = bRam300108 & 0x9f;
    }
    else {
      bVar9 = bRam300108 & 0x20;
      bRam300108 = bVar5;
      if (bVar9 == 0) {
        bRam300108 = bVar5 | 0x20;
        if (bRam301252 < bRam012640) {
          bRam301252 = bRam301252 + 1;
        }
        if (bRam301252 == bRam012640) {
          bRam301255 = bRam301255 | 0x80;
        }
      }
    }
  }
  if (((((((bRam301256 & 8) == 0) || ((bRam301255 & 0x10) != 0)) &&
        (((bRam301256 & 0x10) == 0 || ((bRam301255 & 8) != 0)))) &&
       (((bRam301255 & 1) == 0 || ((bRam301255 & 0x40) != 0)))) &&
      (((bRam301255 & 2) == 0 || ((bRam301255 & 0x20) != 0)))) &&
     (((bRam301254 & 8) == 0 || ((bRam301255 & 4) != 0)))) {
    PSW = PSW & 0xffbf;
  }
  else {
    PSW = PSW | 0x40;
  }
  uVar2 = ((PSW & 0x40) >> 6) << 3;
  uVar11 = uRam00fd08 & 0xfff7 | uVar2;
  if ((uRam00fd08 & 8) == 8) {
    if (cRam301257 == '\0') {
      uRam00fd08 = uVar11 | 0x40;
    }
    else {
      cRam301257 = cRam301257 + -1;
      uRam00fd08 = uVar11;
    }
  }
  else {
    cRam301257 = cRam012621;
    uRam00fd08 = uRam00fd08 & 0xffb7 | uVar2;
  }
  if ((uRam00fd08 & 8) == 0) {
    if ((uRam00fd08 & 2) == 0) {
      if ((uRam00fd08 & 1) == 0) {
        if (((uRam00fd06 & 0x8000) == 0) &&
           (((uRam00fd06 & 0x4000) != 0 || ((bRam301256 & 0x80) != 0)))) {
          uRam3018fc = uRam301938;
          if (uRam3018f6 <= uRam301938) {
            uRam3018fc = uRam3018f6;
          }
        }
        else {
          uRam3018fc = uRam301938;
        }
      }
      else {
        uRam3018fc = uRam3018f6;
      }
    }
    else {
      uRam3018fc = (ushort)bRam01263c << 2;
    }
  }
  else if ((uRam00fd08 & 0x40) != 0) {
    uRam3018fc = 0;
  }
  sVar10 = uRam3018fc - uRam3018fa;
  if (uRam3018fc < uRam3018fa) {
    if (sVar10 >= 0) {
      sVar10 = -0x8000;
    }
  }
  else if (sVar10 < 0) {
    sVar10 = 0x7fff;
  }
  iRam300100 = iVar14;
  uVar7 = func_0x042fe2(sVar10);
  uVar2 = uRam301902;
  uVar11 = uRam301900;
  if (uRam014eec < uVar7) {
    if (uRam014eec * 2 < uVar7) {
      uRam3018fa = uRam3018fc;
    }
    else if (sVar10 < 1) {
      bVar1 = uRam3018fa < uRam014eec;
      uRam3018fa = uRam3018fa - uRam014eec;
      if (bVar1) {
        uRam3018fa = 0;
      }
    }
    else {
      uRam3018fa = uRam3018fa + uRam014eec;
    }
  }
  if ((uRam00fd06 & 0x4000) == 0) {
    if ((bRam301254 & 1) == 0) {
      uVar7 = (ushort)bRam01263c << 2;
    }
    else {
      uVar7 = (ushort)bRam01263b << 2;
    }
  }
  else {
    uVar7 = (ushort)bRam01263a << 2;
  }
  if ((uRam00fd04 & 0x100) == 0) {
    bRam3000e0 = bRam012636;
  }
  else {
    bRam3000e0 = bRam012637;
  }
  uVar12 = (ushort)bRam3000e0 * 4;
  if ((uRam3018fa <= (ushort)bRam3000e0 * 4) && (uVar12 = uVar7, uVar7 <= uRam3018fa)) {
    uVar12 = uRam3018fa;
  }
  uVar13 = uVar12 - uVar7;
  if (uVar12 < uVar7) {
    uVar13 = 0;
  }
  uRam3000f2 = uRam301900;
  bVar9 = (byte)(uVar7 >> 2);
  bVar5 = bRam3000e0 - bVar9;
  if (bRam3000e0 < bVar9) {
    bVar5 = 0;
  }
  uVar3 = ((uint)uVar13 << 0x10) / ((uint)bVar5 << 2);
  uVar7 = (ushort)uVar3;
  MDL = uVar7;
  MDH = (short)(((uint)uVar13 << 0x10) % ((uint)bVar5 << 2));
  MDC = MDC | 0x10;
  if (bVar5 == 0 || 0xffff < uVar3) {
    uVar7 = 0xffff;
  }
  uRam301900 = uVar7;
  uRam3000ee = uRam301902;
  if (((uRam00fd06 & 0x4000) == 0) && (((uRam00fd6e & 0x400) == 0 || ((bRam01261c & 2) == 0)))) {
    if ((uRam00fd08 & 0x20) == 0) {
      bRam300109 = bRam300109 & 0xee;
    }
    else {
      bRam300109 = bRam300109 & 0xef | 1;
    }
    uRam3000f0 = uRam3018fe + uRam014eee;
    if (uRam3018fe + uRam014eee < uRam3018fe || uRam3018fe + uRam014eee < uRam014eee) {
      uRam3000f0 = 0xffff;
    }
    if ((bRam01261c & 0x10) == 0) {
      if ((uRam00fd64 & 0x800) == 0) {
        bRam300108 = bRam300108 & 0x7f;
      }
      else if (uVar7 == 0) {
        bRam300108 = bRam300108 | 0x80;
      }
      if ((((bRam300108 & 0x80) == 0) && ((uRam00fd64 & 0x800) != 0)) &&
         (((bRam301278 & 0x40) != 0 || (((bRam30127b & 2) == 0 || ((bRam30127b & 1) == 0)))))) {
        PSW = PSW | 0x40;
      }
      else {
        PSW = PSW & 0xffbf;
      }
      uRam00fd06 = uRam00fd06 & 0xdfff | ((PSW & 0x40) >> 6) << 0xd;
    }
    else {
      if (((uVar7 == 0) || (((uRam00fd3a & 0x20) == 0 && ((bRam30010a & 4) != 0)))) ||
         (((uRam00fd64 & 0x400) == 0 && ((bRam30010a & 8) != 0)))) {
        bRam300109 = bRam300109 & 0xfd;
      }
      else if ((((uRam00fd3a & 0x20) != 0) && ((bRam30010a & 4) == 0)) ||
              (((uRam00fd64 & 0x400) != 0 && ((bRam30010a & 8) == 0)))) {
        bRam300109 = bRam300109 | 2;
      }
      if ((bRam300109 & 2) == 0) {
        bRam300108 = bRam300108 & 0x7f;
      }
      else if (uVar7 == 0) {
        bRam300108 = bRam300108 | 0x80;
      }
      if ((((bRam300108 & 0x80) == 0) && ((bRam300109 & 2) != 0)) &&
         (((bRam301278 & 0x40) != 0 || (((bRam30127b & 2) == 0 || ((bRam30127b & 1) == 0)))))) {
        PSW = PSW | 0x40;
      }
      else {
        PSW = PSW & 0xffbf;
      }
      uRam00fd06 = uRam00fd06 & 0xdfff | ((PSW & 0x40) >> 6) << 0xd;
      if ((uRam00fd3a & 0x20) == 0) {
        bRam30010a = bRam30010a & 0xfb;
      }
      else {
        bRam30010a = bRam30010a | 4;
      }
      if ((uRam00fd64 & 0x400) == 0) {
        bRam30010a = bRam30010a & 0xf7;
      }
      else {
        bRam30010a = bRam30010a | 8;
      }
    }
    if ((uRam00fd06 & 0x2000) == 0) {
      cRam3000eb = cRam01262c;
      bRam30010a = bRam30010a & 0xef;
    }
    else if (cRam3000eb == '\0') {
      bRam30010a = bRam30010a | 0x10;
    }
    else {
      cRam3000eb = cRam3000eb + -1;
    }
    if ((bRam30010a & 0x10) == 0) {
      uRam00fd08 = uRam00fd08 & 0xffdf;
    }
    else if ((bRam012620 <= nmot_rpmclass) &&
            ((bRam01263e <= vfzg_class || ((uRam303c1e & 1) != 0)))) {
      uRam00fd08 = uRam00fd08 | 0x20;
    }
    if ((uRam00fd08 & 0x20) == 0) {
      if (uRam3000f0 < uVar7) {
        if (((bRam300109 & 1) != 0) && (uRam014ef8 < uVar11)) {
          uRam00fd08 = uRam00fd08 | 0x10;
        }
      }
      else {
        uRam00fd08 = uRam00fd08 & 0xffef;
      }
      uRam3018fe = uVar7;
      if (((uRam00fd08 & 0x10) != 0) && (uRam3000f0 < uVar7)) {
        uRam3018fe = uRam3000f0;
      }
    }
    else {
      uVar11 = uRam3018fe - uRam014ef2;
      if (uRam3018fe < uRam014ef2) {
        uVar11 = 0;
      }
      uVar12 = uRam014ef8;
      if (uRam014ef8 <= uVar11) {
        uVar12 = uVar11;
      }
      uRam3018fe = uVar7;
      if (uVar12 <= uVar7) {
        uRam3018fe = uVar12;
      }
      if (uVar7 <= uRam3000f0) {
        uRam00fd08 = uRam00fd08 & 0xffef;
      }
    }
  }
  else {
    bRam300109 = bRam300109 | 0x10;
    if ((uRam00fd64 & 0x1000) == 0) {
      bVar1 = uRam3018fe + uRam014ef0 < uRam3018fe;
      uVar11 = uRam3018fe + uRam014ef0;
      uRam3018fe = uRam3018fe + uRam014ef0;
      if (bVar1 || uVar11 < uRam014ef0) {
        uRam3018fe = 0xffff;
      }
      if ((ushort)bRam01263f * 0x100 <= uVar7) {
        uVar7 = (ushort)bRam01263f << 8;
      }
      if (uVar7 <= uRam3018fe) {
        uRam3018fe = uVar7;
      }
    }
    else {
      uRam3018fe = 0;
    }
  }
  uRam3000f8 = uRam3018fe;
  if (((bRam301256 & 0x20) != 0) || ((uRam00fd06 & 0x1000) != 0)) {
    uRam3018fe = 0;
  }
  uRam301902 = uRam3018fe;
  DAT_301258 = (char)(uRam3018fe >> 8);
  sRam3018f4 = uRam3018fe - uVar2;
  if (uRam3018fe < uVar2) {
    if (sRam3018f4 >= 0) {
      sRam3018f4 = -0x8000;
    }
  }
  else if (sRam3018f4 < 0) {
    sRam3018f4 = 0x7fff;
  }
  uRam301253 = (char)((ushort)sRam3018f4 >> 8);
  return;
}


// ================= diag_knock_circuit_init @ 039f24 =================

/* DIAGNOSTIC: knock-control diag init/reset */

void diag_knock_circuit_init(void)

{
  if ((DAT_00fd4e & 0x100) != 0) {
    bRam303187 = bRam303187 | 3;
    sRam3035a2 = (ushort)bRam012634 << 2;
    uRam3035a0 = 0;
    uRam300106 = 0;
    uRam300104 = 0;
  }
  uRam3000e1 = uRam012627;
  uRam3000e2 = uRam012629;
  uRam3000e3 = uRam012626;
  uRam3000e4 = uRam012628;
  uRam3000e5 = uRam01262a;
  uRam3000ea = uRam01262b;
  uRam3000e6 = uRam012623;
  uRam3000e7 = uRam012624;
  uRam0180e8 = uRam018079;
  uRam3000e9 = uRam012625;
  uRam3000eb = uRam01262c;
  uRam3000ed = uRam012622;
  uRam301257 = uRam012621;
  sRam3018fa = (ushort)bRam01263a << 2;
  sRam3000f4 = sRam3035a2;
  return;
}


// ================= diag_rationality_monitor @ 09a034 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC: sensor/model rationality monitor -> FD34/FD36 DTC */

void diag_rationality_monitor(void)

{
  bool bVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  byte bVar9;
  short sVar10;
  undefined2 uVar11;
  byte extraout_RH4;
  ushort uVar12;
  ushort uVar13;
  short sVar14;
  ushort uVar15;
  int iVar16;
  undefined4 uVar17;
  
  uVar17 = uRam300908;
  uVar6 = uRam30090c;
  uVar7 = uRam300910;
  uVar8 = uRam300916;
  if (((bRam30166c & 1) == 0) && ((_flags_diag_enable_a & 0x400) != 0)) {
    if ((bRam30166d & 4) == 0) {
      uRam305310 = 0;
    }
    else {
      uRam305310 = uRam023e98;
    }
    bVar3 = (uRam302634 & 0x1000) != 0;
    uRam300900 = bVar3 && cRam300901 == '\0';
    if (((bRam301669 & 8) != 0) || ((bool)uRam300900)) {
      bRam301669 = bRam301669 | 4;
    }
    else {
      bRam301669 = bRam301669 & 0xfb;
    }
    if ((bRam301669 & 4) != 0) {
      bRam303272 = bRam303272 & 0xfe;
    }
    uVar15 = uRam3026a6 * -8 + 0x8000;
    uVar13 = -(ushort)(0x8000 < uRam3026a6 * 8) - (uRam3026a6 >> 0xd);
    if ((short)((uVar13 + 1) - (ushort)(uVar15 < 0x8000)) < 0 ==
        (-1 < (short)uVar13 &&
        (short)((uVar13 + 1) - (ushort)(uVar15 < 0x8000)) < 0 != (short)uVar13 < 0)) {
      uVar12 = (ushort)(uVar15 < 0x7fff);
      if ((uVar13 != uVar12 || uVar15 != 0x7fff) &&
          (short)(uVar13 - uVar12) < 0 ==
          ((short)uVar13 < 0 && (short)(uVar13 - (uVar15 < 0x7fff)) < 0 != (short)uVar13 < 0)) {
        uVar15 = 0x7fff;
      }
    }
    else {
      uVar15 = 0x8000;
    }
    cRam300901 = bVar3;
    uRam300908 = me7_slew_limiter(uRam023f38,uVar15,uRam300908._2_2_,(undefined2)uRam300908);
    uVar12 = (ushort)((uint)uRam300908 >> 0x10);
    uVar13 = uVar15 - uVar12;
    uVar15 = (((short)uVar15 >> 0xf) - ((short)uVar12 >> 0xf)) - (ushort)(uVar15 < uVar12);
    if ((short)((uVar15 + 1) - (ushort)(uVar13 < 0x8000)) < 0 ==
        (-1 < (short)uVar15 &&
        (short)((uVar15 + 1) - (ushort)(uVar13 < 0x8000)) < 0 != (short)uVar15 < 0)) {
      uVar12 = (ushort)(uVar13 < 0x7fff);
      if ((uVar15 != uVar12 || uVar13 != 0x7fff) &&
          (short)(uVar15 - uVar12) < 0 ==
          ((short)uVar15 < 0 && (short)(uVar15 - (uVar13 < 0x7fff)) < 0 != (short)uVar15 < 0)) {
        uVar13 = 0x7fff;
      }
    }
    else {
      uVar13 = 0x8000;
    }
    if ((short)uRam302694 < 0) {
      iVar4 = (int)(short)uVar13 * (int)(short)(uRam302694 & 0x7fff);
      uVar12 = (ushort)iVar4;
      uVar15 = uVar13 * -0x8000;
      iVar16 = CONCAT22((short)((uint)iVar4 >> 0x10) + ((short)uVar13 >> 1) +
                        (ushort)(uVar12 + uVar15 < uVar12 || uVar12 + uVar15 < uVar15),
                        uVar12 + uVar15);
    }
    else {
      iVar16 = (int)(short)uVar13 * (int)(short)uRam302694;
      iVar4 = iVar16;
    }
    MDH = (undefined2)((uint)iVar4 >> 0x10);
    MDL = (ushort)iVar4;
    MDC = MDC | 0x10;
    iVar16 = iVar16 >> 10;
    uVar13 = (ushort)((uint)iVar16 >> 0x10);
    uVar15 = (ushort)iVar16;
    if ((short)((uVar13 + 1) - (ushort)(uVar15 < 0x8000)) < 0 ==
        (-1 < iVar16 && (short)((uVar13 + 1) - (ushort)(uVar15 < 0x8000)) < 0 != iVar16 < 0)) {
      uVar12 = (ushort)(uVar15 < 0x7fff);
      if ((uVar13 != uVar12 || uVar15 != 0x7fff) &&
          (short)(uVar13 - uVar12) < 0 ==
          (iVar16 < 0 && (short)(uVar13 - (uVar15 < 0x7fff)) < 0 != iVar16 < 0)) {
        uVar15 = 0x7fff;
      }
    }
    else {
      uVar15 = 0x8000;
    }
    uRam30090c = me7_slew_limiter(uRam023f3a,uVar15,uRam30090c._2_2_,(undefined2)uRam30090c);
    uVar13 = (ushort)((uint)uRam30090c >> 0x10);
    uVar15 = (ushort)bRam01a03f;
    uRam305318 = uVar13 + uVar15;
    uVar15 = ((short)uVar13 >> 0xf) + (ushort)(uVar13 + uVar15 < uVar13 || uVar13 + uVar15 < uVar15)
    ;
    uVar13 = (ushort)(uRam305318 < 0x7fff);
    if ((uVar15 != uVar13 || uRam305318 != 0x7fff) &&
        (short)(uVar15 - uVar13) < 0 ==
        ((short)uVar15 < 0 && (short)(uVar15 - (uRam305318 < 0x7fff)) < 0 != (short)uVar15 < 0)) {
      uRam305318 = 0x7fff;
    }
    iVar16 = func_0x032c02((uRam305318 + uRam305316) * 0x40,
                           (((short)uRam305318 >> 0xf) + ((short)uRam305316 >> 0xf) +
                           (ushort)(uRam305318 + uRam305316 < uRam305318 ||
                                   uRam305318 + uRam305316 < uRam305316)) * 0x40 |
                           uRam305318 + uRam305316 >> 10,uRam01a03e);
    uVar15 = (ushort)((uint)iVar16 >> 0x10);
    uRam305314 = (ushort)iVar16;
    if ((short)((uVar15 + 1) - (ushort)(uRam305314 < 0x8000)) < 0 ==
        (-1 < iVar16 && (short)((uVar15 + 1) - (ushort)(uRam305314 < 0x8000)) < 0 != iVar16 < 0)) {
      uVar13 = (ushort)(uRam305314 < 0x7fff);
      if ((uVar15 != uVar13 || uRam305314 != 0x7fff) &&
          (short)(uVar15 - uVar13) < 0 ==
          (iVar16 < 0 && (short)(uVar15 - (uRam305314 < 0x7fff)) < 0 != iVar16 < 0)) {
        uRam305314 = 0x7fff;
      }
    }
    else {
      uRam305314 = 0x8000;
    }
    uVar17 = func_0x0430da(0x199a,uRam305314,uRam300916._2_2_,(undefined2)uRam300916,0xff80,0,0x7f,0
                          );
    uRam300916._2_1_ = (char)((uint)uVar17 >> 0x10);
    cRam30498d = uRam300916._2_1_;
    uRam300916 = uVar17;
    sVar10 = func_0x04272a(uRam023e9a,0x3e9c,8,0x3ea6,8,uRam306694);
    uVar11 = func_0x042d2c(sVar10 << 8,(short)cRam30498d,uRam304906);
    uRam300906._1_1_ = (char)((ushort)uVar11 >> 8);
    MDL = (ushort)((int)(short)uRam300906._1_1_ * (int)(short)(ushort)bRam01a03c);
    MDH = (undefined2)
          ((uint)((int)(short)uRam300906._1_1_ * (int)(short)(ushort)bRam01a03c) >> 0x10);
    MDC = MDC | 0x10;
    sVar10 = ((short)MDL >> 7) + (ushort)bRam01a03d;
    sVar14 = sVar10 + 0x26;
    if (sVar14 < 0) {
      sVar14 = 0;
    }
    else if (sVar14 != 0xff &&
             sVar10 + -0xd9 < 0 == (sVar14 < 0 && sVar10 + -0xd9 < 0 != sVar14 < 0)) {
      sVar14 = 0xff;
    }
    bRam30498c = (byte)sVar14;
    if ((short)(bRam3054bc - 0x26) < 0) {
      bVar9 = 0;
    }
    else {
      bVar9 = (byte)(bRam3054bc - 0x26);
    }
    uRam300906 = uVar11;
    uVar11 = me7_fraction_blend((ushort)bRam01a043 << 8,bVar9,uRam300920);
    iVar16 = CONCAT22(MDH,MDL);
    uRam300920._1_1_ = (byte)((ushort)uVar11 >> 8);
    bRam304992 = uRam300920._1_1_;
    if ((bRam30566c & 0x40) != 0) {
      uVar15 = (ushort)bVar9 - (ushort)uRam300920._1_1_;
      if ((short)uVar15 < 1) {
        uVar15 = -uVar15;
      }
      uRam300920 = uVar11;
      uRam300924 = me7_fraction_blend((ushort)bRam01a044 << 8,uVar15 & 0xff,uRam300924);
      MDL = (uRam300924 >> 8) * (ushort)bRam01a023;
      MDH = 0;
      MDC = MDC | 0x10;
      uVar15 = MDL >> 3;
      if (0xff < uVar15) {
        uVar15 = 0xff;
      }
      bRam304985 = (byte)uVar15;
      uVar11 = func_0x042d2c((ushort)bRam01a045 << 8,
                             (short)((ushort)bRam304992 - (ushort)bRam30498e) >> 1,uRam30091e);
      uRam30091e._1_1_ = (char)((ushort)uVar11 >> 8);
      cRam304991 = uRam30091e._1_1_;
      bVar9 = bRam304985;
      if (bRam01a040 <= bRam304985) {
        bVar9 = bRam01a040;
      }
      sVar10 = (ushort)bVar9 * (short)uRam30091e._1_1_;
      if ((short)uRam023eac < 0) {
        iVar16 = (int)sVar10 * (int)(short)(uRam023eac & 0x7fff);
        uVar13 = (ushort)iVar16;
        uVar15 = sVar10 * -0x8000;
        iVar4 = CONCAT22((short)((uint)iVar16 >> 0x10) + (sVar10 >> 1) +
                         (ushort)(uVar13 + uVar15 < uVar13 || uVar13 + uVar15 < uVar15),
                         uVar13 + uVar15);
      }
      else {
        iVar4 = (int)sVar10 * (int)(short)uRam023eac;
        iVar16 = iVar4;
      }
      MDC = MDC | 0x10;
      uRam305316 = (ushort)iVar4 >> 0xb | (short)((uint)iVar4 >> 0x10) << 5;
      uRam30091e = uVar11;
      uVar11 = uRam300920;
    }
    uRam300920 = uVar11;
    MDH = (undefined2)((uint)iVar16 >> 0x10);
    MDL = (ushort)iVar16;
    if ((short)(bRam30498c - 0x26) < 0) {
      bVar9 = 0;
    }
    else {
      bVar9 = (byte)(bRam30498c - 0x26);
    }
    uVar11 = me7_fraction_blend((ushort)bRam01a043 << 8,bVar9,uRam300922);
    uRam300922._1_1_ = (byte)((ushort)uVar11 >> 8);
    bRam30498e = uRam300922._1_1_;
    if ((bRam30566c & 0x40) != 0) {
      uVar15 = (ushort)bVar9 - (ushort)uRam300922._1_1_;
      if ((short)uVar15 < 1) {
        uVar15 = -uVar15;
      }
      uRam300922 = uVar11;
      uRam300914 = me7_fraction_blend((ushort)bRam01a044 << 8,uVar15 & 0xff,uRam300914);
      MDL = (uRam300914 >> 8) * (ushort)bRam01a023;
      MDH = 0;
      MDC = MDC | 0x10;
      uVar15 = MDL >> 3;
      if (0xff < uVar15) {
        uVar15 = 0xff;
      }
      bRam304987 = (byte)uVar15;
      uVar11 = uRam300922;
    }
    uRam300922 = uVar11;
    if (((bRam301669 & 8) == 0) || ((bRam301668 & 0x10) == 0)) {
      uRam300902 = false;
      cRam300903 = '\0';
    }
    else {
      uRam300902 = cRam300903 == '\0';
      cRam300903 = '\x01';
    }
    if ((bool)uRam300902 != false) {
      bRam30a032 = bRam304984;
    }
    if ((uRam302634 & 0x1000) == 0) {
      me7_lookup_2d_word_bilinear(0x3eae,8,uRam302694,uRam30500a);
      bRam30498b = extraout_RH4;
    }
    else {
      bRam30498b = func_0x04272a(uRam023f0a,0x3f0c,8,0x3f16,8,uRam30500a);
    }
    uVar13 = (ushort)bRam304987 * (ushort)bRam30498b;
    uVar5 = (uint)uVar13;
    uVar15 = uVar13 >> 7;
    if (0xff < uVar15) {
      uVar15 = 0xff;
    }
    bRam304988 = (byte)uVar15;
    if ((((cRam01a034 == '\0') || (bRam01a037 <= bRam304985)) ||
        ((uVar15 & 0xff) <= (ushort)bRam01a038 + (ushort)bRam304985)) ||
       ((ushort)bRam01a03b <= (ushort)bRam01a038 + (uVar15 & 0xff))) {
      sVar10 = ((ushort)bRam304985 - (uVar15 & 0xff)) + (ushort)bRam01a03b;
      if (sVar10 < 0) {
        sVar10 = 0;
      }
      else if (sVar10 != 0xff &&
               sVar10 + -0xff < 0 == (sVar10 < 0 && sVar10 + -0xff < 0 != sVar10 < 0)) {
        sVar10 = 0xff;
      }
      bRam304986 = (byte)sVar10;
    }
    else {
      bRam304986 = bRam304985;
    }
    if ((bRam30166c & 0x40) != 0) {
      bRam30166b = bRam30166b | 4;
    }
    if (cRam3008fd == '\0') {
      if (((bRam30166b & 4) != 0) && (cRam3008fc == '\0')) {
        uRam0188fd = uRam01a042;
      }
    }
    else {
      cRam3008fd = cRam3008fd + -1;
    }
    cRam3008fc = (bRam30166b & 4) != 0;
    if ((bRam301669 & 4) == 0) {
      if ((bRam30166d & 4) == 0) {
        if (bRam304988 < bRam01a039) {
          bVar3 = false;
        }
        else {
          bVar3 = true;
        }
      }
      else {
        bVar3 = bRam01a03a <= bRam304988;
      }
      if (((bVar3) && ((bRam301667 & 0x40) == 0)) &&
         (((bRam30166c & 0x40) != 0 && (cRam3008fd == '\0')))) {
        bRam301667 = bRam301667 | 4;
      }
      else {
        bRam301667 = bRam301667 & 0xfb;
      }
      if (((bRam301667 & 4) != 0) &&
         (bVar3 = uRam30530e + 1 < uRam30530e, bVar1 = uRam30530e == 0xffff,
         uRam30530e = uRam30530e + 1, uVar5 = (uint)uVar13,
         ((bVar3 || bVar1) != (uRam30530e != 0xffff) || uRam30530e != 0xffff) &&
         ((bVar3 || bVar1) || uRam30530e == 0xffff))) {
        uRam30530e = 0xffff;
      }
    }
    else {
      uVar5 = (uint)bRam30a032 * (uint)uRam023e96 >> 7;
      uVar15 = (ushort)(uVar5 >> 0x10);
      uRam300910._2_2_ = (ushort)uVar5;
      if ((uVar15 != uRam300910._2_2_ < 0x7fff || uRam300910._2_2_ != 0x7fff) &&
          (uVar15 != 0 || uRam300910._2_2_ >= 0x7fff)) {
        uRam300910._2_2_ = 0x7fff;
      }
      uRam300910._0_2_ = 0;
      uRam30530e = uRam023e96;
      uVar5 = (uint)bRam30a032 * (uint)uRam023e96;
    }
    uVar17 = CONCAT22(uRam300910._2_2_,(undefined2)uRam300910);
    MDH = (undefined2)(uVar5 >> 0x10);
    MDL = (ushort)uVar5;
    MDC = MDC | 0x10;
    if ((bRam301667 & 4) != 0) {
      uVar17 = me7_integrator_sat(0x200,bRam304986,uRam304912,(undefined2)uRam300910);
      uVar5 = CONCAT22(MDH,MDL);
    }
    uRam300910._2_2_ = (ushort)((uint)uVar17 >> 0x10);
    MDH = (undefined2)(uVar5 >> 0x10);
    MDL = (ushort)uVar5;
    sRam30530c = uRam300910._2_2_ << 1;
    sVar10 = uRam300910._2_2_ << 7;
    uVar15 = uRam300910._2_2_ & 0x7fff;
    uRam300910 = uVar17;
    uVar17 = func_0x032cb8(sVar10,uVar15 >> 9,uRam30530e);
    uVar13 = (ushort)((uint)uVar17 >> 0x10);
    uVar15 = (ushort)uVar17;
    if ((uVar13 != uVar15 < 0xff || uVar15 != 0xff) && (uVar13 != 0 || uVar15 >= 0xff)) {
      uVar15 = 0xff;
    }
    bRam304984 = (byte)uVar15;
    uVar15 = uRam023f34;
    if ((uRam306634 & 0x1000) == 0) {
      uVar15 = uRam023f32;
    }
    if (uVar15 < uRam30530e) {
      bRam301667 = bRam301667 | 0x40;
    }
    else {
      bRam301667 = bRam301667 & 0xbf;
    }
    uRam30091a = me7_fraction_blend((ushort)bRam01a046 << 8,rl_byte,uRam30091a);
    sVar10 = (uRam30091a >> 8) - (ushort)rl_byte;
    if (sVar10 + 0x7f < 0 == (-1 < sVar10 && sVar10 + 0x7f < 0 != sVar10 < 0)) {
      if (sVar10 != 0x7f && sVar10 + -0x7f < 0 == (sVar10 < 0 && sVar10 + -0x7f < 0 != sVar10 < 0))
      {
        sVar10 = 0x7f;
      }
    }
    else {
      sVar10 = 0x81;
    }
    bRam304990 = (byte)sVar10;
    cVar2 = cRam01a036;
    if ((bRam30566d & 4) == 0) {
      cVar2 = cRam01a035;
    }
    bVar9 = bRam304990;
    if ((char)bRam304990 < '\x01') {
      bVar9 = -bRam304990;
    }
    uVar13 = (ushort)bVar9;
    uVar15 = (ushort)cVar2;
    if ((((((bRam30166b & 4) == 0) || ((bRam30166d & 1) != 0)) || ((bRam301667 & 0x40) != 0)) ||
        (((bRam30166c & 8) != 0 || ((bRam30166c & 2) != 0)))) ||
       (uVar13 != uVar15 &&
        (short)(uVar13 - uVar15) < 0 == ((short)uVar15 < 0 && (short)(uVar13 - uVar15) < 0))) {
      bRam301667 = bRam301667 & 0xfe;
    }
    else {
      bRam301667 = bRam301667 | 1;
    }
    uVar17 = uRam300908;
    uVar6 = uRam30090c;
    uVar7 = uRam300910;
    uVar8 = uRam300916;
    if ((bRam301667 & 1) != 0) {
      if ((bRam30166d & 4) == 0) {
        uRam30531a = me7_lookup_1d_word(0x3f1c,8,uRam302694);
      }
      else {
        uRam30531a = uRam023f36;
      }
      if ((bRam30166d & 4) == 0) {
        uRam304989 = func_0x04272a(uRam023ef8,0x3efa,8,0x3f04,8,uRam302694);
        uVar17 = uRam300908;
        uVar6 = uRam30090c;
        uVar7 = uRam300910;
        uVar8 = uRam300916;
      }
      else {
        uRam304989 = uRam01a02c;
        uVar17 = uRam300908;
        uVar6 = uRam30090c;
        uVar7 = uRam300910;
        uVar8 = uRam300916;
      }
    }
  }
  uRam300916._2_2_ = (undefined2)((uint)uVar8 >> 0x10);
  uRam300916._0_2_ = (undefined2)uVar8;
  uRam300910._2_2_ = (ushort)((uint)uVar7 >> 0x10);
  uRam300910._0_2_ = (undefined2)uVar7;
  uRam30090c._2_2_ = (undefined2)((uint)uVar6 >> 0x10);
  uRam30090c._0_2_ = (undefined2)uVar6;
  uRam300908._2_2_ = (undefined2)((uint)uVar17 >> 0x10);
  uRam300908._0_2_ = (undefined2)uVar17;
  return;
}


// ================= diag_misfire_monitor @ 0a0000 =================

/* WARNING: Removing unreachable block (ram,0x0a10be) */
/* WARNING: Removing unreachable block (ram,0x0a149c) */
/* WARNING: Removing unreachable block (ram,0x0a14ae) */
/* WARNING: Removing unreachable block (ram,0x0a14ac) */
/* WARNING: Removing unreachable block (ram,0x0a14b4) */
/* WARNING: Removing unreachable block (ram,0x0a14d0) */
/* WARNING: Removing unreachable block (ram,0x0a14ce) */
/* WARNING: Removing unreachable block (ram,0x0a14d4) */
/* WARNING: Removing unreachable block (ram,0x0a14dc) */
/* WARNING: Removing unreachable block (ram,0x0a14e0) */
/* WARNING: Removing unreachable block (ram,0x0a14e4) */
/* WARNING: Removing unreachable block (ram,0x0a14ea) */
/* WARNING: Removing unreachable block (ram,0x0a14e8) */
/* WARNING: Removing unreachable block (ram,0x0a14d8) */
/* WARNING: Removing unreachable block (ram,0x0a14ee) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC: running-roughness / misfire detection (Laufunruhe) -> FDAE/FDB0/FDB2 */

ushort diag_misfire_monitor(void)

{
  ushort *puVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  ushort *puVar5;
  ushort *puVar6;
  undefined1 *puVar7;
  undefined1 *puVar8;
  ushort uVar10;
  ushort extraout_r3;
  ushort extraout_r3_00;
  ushort extraout_r3_01;
  ushort extraout_r3_02;
  ushort extraout_r3_03;
  ushort extraout_r3_04;
  ushort extraout_r3_05;
  byte extraout_RL4;
  char cVar11;
  char cVar12;
  undefined1 extraout_RH4;
  short sVar13;
  ushort uVar14;
  undefined1 extraout_RH5;
  short sVar15;
  byte bVar16;
  short sVar17;
  byte bVar19;
  ushort uVar18;
  short sVar20;
  undefined2 uVar21;
  short sVar22;
  ushort uVar23;
  ushort uStack_4;
  undefined1 uVar9;
  
  if ((_flags_diag_enable_a & 0x200) == 0) {
    return 0;
  }
  if ((_flags_diag_cfg_a & 0x10) == 0) {
    uRam302b5e = func_0x040f32(0x3f16,rl_byte,uRam302b5e);
  }
  else {
    uRam302b5e = func_0x040f32(0x3f1a,rl_byte,uRam302b5e);
  }
  uRam30214c = uRam302b5e >> 8 | uRam302b5e << 8;
  if ((_flags_diag_cfg_a & 0x10) == 0) {
    uRam302b60 = func_0x040f32(0x3f1e,nmot_rpmclass,uRam302b60);
    uVar23 = extraout_r3_00;
  }
  else {
    uRam302b60 = func_0x040f32(0x3f27,nmot_rpmclass,uRam302b60);
    uVar23 = extraout_r3;
  }
  uRam30214a = uRam302b60 >> 8 | uRam302b60 << 8;
  __atomic(3);
  puVar6 = &uStack_4;
  DAT_00e316 = &uStack_4;
  puVar5 = &uStack_4;
  if (cRam013ec1 == '\0') {
    func_0x09f32e();
    sRam303a0a = 0;
    uRam303a0c = 0;
    uVar23 = extraout_r3_01;
    puVar5 = DAT_00e316;
  }
  DAT_00e316 = puVar5;
  uRam00fdae = uRam00fdae & 0xbfff;
  for (uVar14 = 0; uVar14 < 8; uVar14 = uVar14 + 1) {
    bRam3016cd = 0;
    for (uVar10 = 0; uVar10 < 0x60; uVar10 = uVar10 + 0x18) {
      bRam3016ce = 0xff;
      bRam3016cf = 0;
      for (puVar6 = (ushort *)0x0; puVar6 < (undefined1 *)0x18;
          puVar6 = (ushort *)((short)puVar6 + 8)) {
        bVar16 = *(byte *)(ZEXT23((undefined1 *)((short)puVar6 + uVar14 + uVar10)) + 0x30327c);
        uVar23 = CONCAT11(bVar16,(char)uVar23);
        bVar19 = bVar16;
        if (bVar16 <= bRam3016cf) {
          bVar19 = bRam3016cf;
        }
        bRam3016cf = bVar19;
        if (bRam3016ce <= bVar16) {
          bVar16 = bRam3016ce;
        }
        bRam3016ce = bVar16;
      }
      if (bRam3016cd < (byte)(bRam3016cf - bRam3016ce)) {
        bRam3016cd = bRam3016cf - bRam3016ce;
      }
    }
    *(byte *)((uint3)uVar14 + 0x3016c4) = bRam3016cd;
    bRam3016cc = *(byte *)((uint3)uVar14 + 0x13eca);
    if ((_flags_diag_cfg_a & 0x10) != 0) {
      bRam3016cc = *(byte *)((uint3)uVar14 + 0x13ec2);
    }
    if (bRam3016cd < bRam3016cc) {
      bRam303278 = bRam303278 | (byte)(1 << uVar14);
    }
    else {
      bRam303278 = bRam303278 & ((byte)(1 << uVar14) ^ 0xff);
    }
    if (bRam013ed2 < bRam3016cd) {
      uRam00fdae = uRam00fdae | 0x4000;
    }
  }
  uVar14 = ((PSW & 8) >> 3) << 0xc;
  uVar10 = uRam00fdae & 0xefff | uVar14;
  if ((uRam00fdae & 0x4000) != 0) {
    uRam00fdae = uRam00fdae & 0xafff | uVar14;
    sRam303a0a = sRam303a0a + 1;
    func_0x09f32e();
    uVar23 = extraout_r3_02;
    uVar10 = uRam00fdae;
  }
  uRam00fdae = uVar10;
  bVar16 = bRam013f28;
  if ((_flags_diag_cfg_a & 0x10) == 0) {
    bVar16 = bRam013f1f;
  }
  uVar14 = (ushort)bVar16;
  bVar16 = bRam013f29;
  if ((_flags_diag_cfg_a & 0x10) == 0) {
    bVar16 = bRam013f20;
  }
  uVar18 = bVar16 - uVar14 >> 1;
  uVar10 = uVar14 - uVar18;
  if (uVar14 < uVar18) {
    uVar10 = uVar10 & 0xff00;
  }
  bRam30213c = (byte)uVar10;
  bRam30213d = bVar16 - (char)uVar18;
  uVar9 = uRam013f2a;
  if ((_flags_diag_cfg_a & 0x10) == 0) {
    uVar9 = uRam013f21;
  }
  sVar15 = CONCAT11((char)(uVar10 >> 8),uVar9);
  sVar17 = sVar15 - (sVar15 - (ushort)bVar16 >> 1);
  bRam30213e = (byte)sVar17;
  uVar9 = uRam013f2b;
  if ((_flags_diag_cfg_a & 0x10) == 0) {
    uVar9 = uRam013f22;
  }
  sVar13 = CONCAT11((char)((ushort)sVar17 >> 8),uVar9);
  sVar17 = sVar13 - ((ushort)(sVar13 - sVar15) >> 1);
  bRam30213f = (byte)sVar17;
  uVar9 = uRam013f2c;
  if ((_flags_diag_cfg_a & 0x10) == 0) {
    uVar9 = uRam013f23;
  }
  sVar15 = CONCAT11((char)((ushort)sVar17 >> 8),uVar9);
  sVar17 = sVar15 - ((ushort)(sVar15 - sVar13) >> 1);
  bRam302140 = (byte)sVar17;
  uVar9 = uRam013f2d;
  if ((_flags_diag_cfg_a & 0x10) == 0) {
    uVar9 = uRam013f24;
  }
  sVar13 = CONCAT11((char)((ushort)sVar17 >> 8),uVar9);
  sVar17 = sVar13 - ((ushort)(sVar13 - sVar15) >> 1);
  bRam302141 = (byte)sVar17;
  uVar9 = uRam013f2e;
  if ((_flags_diag_cfg_a & 0x10) == 0) {
    uVar9 = uRam013f25;
  }
  sVar15 = CONCAT11((char)((ushort)sVar17 >> 8),uVar9);
  sVar17 = sVar15 - ((ushort)(sVar15 - sVar13) >> 1);
  bRam302142 = (byte)sVar17;
  bVar16 = bRam013f2f;
  if ((_flags_diag_cfg_a & 0x10) == 0) {
    bVar16 = bRam013f26;
  }
  bVar19 = (byte)((ushort)(CONCAT11((char)((ushort)sVar17 >> 8),bVar16) - sVar15) >> 1);
  bRam302143 = bVar16 - bVar19;
  bRam302144 = bVar16 + bVar19;
  if ((byte)(bVar16 + bVar19) < bVar16 || (byte)(bVar16 + bVar19) < bVar19) {
    bRam302144 = 0xff;
  }
  bVar16 = bRam013f1b;
  if ((_flags_diag_cfg_a & 0x10) == 0) {
    bVar16 = bRam013f17;
  }
  uVar14 = (ushort)bVar16;
  bVar16 = bRam013f1c;
  if ((_flags_diag_cfg_a & 0x10) == 0) {
    bVar16 = bRam013f18;
  }
  uVar18 = bVar16 - uVar14 >> 1;
  uVar10 = uVar14 - uVar18;
  if (uVar14 < uVar18) {
    uVar10 = uVar10 & 0xff00;
  }
  bRam302145 = (byte)uVar10;
  bRam302146 = bVar16 - (char)uVar18;
  cVar11 = cRam013f1d;
  if ((_flags_diag_cfg_a & 0x10) == 0) {
    cVar11 = cRam013f19;
  }
  uVar10 = CONCAT11((char)(uVar10 >> 8),cVar11);
  uVar14 = uVar10 - bVar16 >> 1;
  bRam302147 = cVar11 - (char)uVar14;
  bRam302148 = cVar11 + (char)uVar14;
  if (uVar10 + uVar14 < uVar10 || uVar10 + uVar14 < uVar14) {
    bRam302148 = 0xff;
  }
  if (nmot_rpmclass < bRam30213c) {
    bVar16 = 0;
  }
  else if (nmot_rpmclass < bRam30213d) {
    bVar16 = 1;
  }
  else if (nmot_rpmclass < bRam30213e) {
    bVar16 = 2;
  }
  else if (nmot_rpmclass < bRam30213f) {
    bVar16 = 3;
  }
  else if (nmot_rpmclass < bRam302140) {
    bVar16 = 4;
  }
  else if (nmot_rpmclass < bRam302141) {
    bVar16 = 5;
  }
  else if (nmot_rpmclass < bRam302142) {
    bVar16 = 6;
  }
  else if (nmot_rpmclass < bRam302143) {
    bVar16 = 7;
  }
  else if (nmot_rpmclass < bRam302144) {
    bVar16 = 8;
  }
  else {
    bVar16 = 9;
  }
  if (rl_byte < bRam302145) {
    uRam302136 = (ushort)bVar16;
  }
  else if (rl_byte < bRam302146) {
    uRam302136 = CONCAT11(1,bVar16);
  }
  else if (rl_byte < bRam302147) {
    uRam302136 = CONCAT11(2,bVar16);
  }
  else if (rl_byte < bRam302148) {
    uRam302136 = CONCAT11(3,bVar16);
  }
  else {
    uRam302136 = CONCAT11(4,bVar16);
  }
  bVar16 = (char)uRam302136 - 1;
  bVar19 = (byte)(uRam302136 >> 8);
  if (bVar16 < 8) {
    uRam30213a = uRam302136;
    if ((flags_torque_revlimit & 0x80) == 0) {
      uRam302138 = CONCAT11(bVar19 - 1,bVar16);
      if (2 < (byte)(bVar19 - 1)) goto LAB_0a03a4;
    }
    else {
      if (3 < bVar19) goto LAB_0a03a4;
      uRam302138 = CONCAT11((bVar19 - 1) + (bVar19 == 0),bVar16);
    }
  }
  else {
LAB_0a03a4:
    uRam302138 = 0xffff;
    uRam30213a = 0;
  }
  MDL = (uRam30213a & 0xff) * 10;
  MDH = 0;
  MDC = MDC | 0x10;
  cRam3016ea = (char)(uRam30213a >> 8) + (char)MDL;
  if (uRam302138 == 0xffff) {
    bRam303276 = bRam303276 & 0xbf;
    uRam00fdae = uRam00fdae & 0xfbfc;
  }
  else {
    uVar14 = uRam302138 & 0xff;
    uVar10 = (bRam303278 >> uVar14 & 1) << 10;
    bRam303276 = bRam303276 & 0xbf | (bRam303277 >> uVar14 & 1) << 6;
    if ((_flags_diag_cfg_a & 0x10) == 0) {
      uVar14 = uVar14 + 0x3ed3;
    }
    else {
      uVar14 = uVar14 + 0x3eeb;
    }
    if ((flags_torque_revlimit & 0x80) == 0) {
      if (((char)(uRam302138 >> 8) != '\0') || ((*(byte *)((uint3)uVar14 + 0x10000) & 4) == 0))
      goto LAB_0a0414;
      uRam00fdae = uRam00fdae & 0xfbfc | uVar10;
    }
    else if ((*(byte *)((uint3)uVar14 + 0x10000) & 4) == 0) {
LAB_0a0414:
      uRam00fdae = uRam00fdae & 0xfbfd | uVar10 | 1;
    }
    else {
      uRam00fdae = uRam00fdae & 0xfbfe | uVar10 | 2;
    }
  }
  if ((uRam00fd26 & 0x8000) == 0) {
    uVar21 = 0x4221;
  }
  else {
    uVar21 = 0x4261;
  }
  uRam00e5b6 = uVar23;
  uVar21 = func_0x04119c(uVar21,0x273e,uRam3019c2,uRam301998);
  bRam3016c2 = (byte)uVar21;
  if ((uRam00fd58 & 0x800) == 0) {
    uVar9 = (undefined1)((ushort)uVar21 >> 8);
    bRam3016ab = 0x80;
  }
  else {
    me7_lookup_1d_byte(0x20f3,6,uRam304785);
    uVar9 = extraout_RH4;
    bRam3016ab = extraout_RL4;
  }
  uVar23 = CONCAT11(uVar9,rpmclass_oppoint);
  if (bRam013f49 < rpmclass_oppoint) {
    uRam00fdfe = uRam00fdfe & 0xffdf;
  }
  else {
    uVar23 = CONCAT11(uVar9,bRam304979);
    if (bRam304979 < bRam307f4a) {
      uRam00fdfe = uRam00fdfe | 0x20;
    }
  }
  uVar14 = uRam00e5b6;
  if ((uRam00fdac & 1) != 0) {
    bVar16 = bRam00e19d;
    if (0x21 < bRam00e19c) {
      puVar6 = (ushort *)0x10;
      bRam00e19d = 0x10;
      uRam00fdac = uRam00fdac & 0xfffe;
      uVar10 = 0;
      uRam301c00 = uRam301c00 & 0xffef;
      uRam301c02 = uRam301c02 & 0xffef;
      uRam301c04 = uRam301c04 & 0xffef;
      uRam301c06 = uRam301c06 & 0xffef;
      uRam301c08 = uRam301c08 & 0xffef;
      uRam301c0a = uRam301c0a & 0xffef;
LAB_0a04fe:
      uVar14 = CONCAT11((char)(uVar14 >> 8),*(byte *)((uint3)uVar10 + 0x301c00));
      if ((*(byte *)((uint3)uVar10 + 0x301c00) & 0x10) == 0) goto code_r0x0a0506;
      uRam30241c = uRam30241c + 1;
      for (uVar23 = 0x14 - (uVar10 >> 1); 4 < uVar23; uVar23 = uVar23 - 5) {
      }
      uVar10 = 0;
      while( true ) {
        uVar18 = uVar23;
        uVar23 = *(ushort *)((uint3)uVar10 + 0x301b00);
        if (uVar23 == 0xffff) {
          uVar23 = 0xffff;
          *(ushort *)((uint3)uVar10 + 0x301c00) = *(ushort *)((uint3)uVar10 + 0x301c00) | 0x20;
          cRam3016b7 = cRam013f4c;
          cRam3016b9 = cRam013f4c;
          uRam00fdae = uRam00fdae | 4;
          cRam3016e7 = cRam013ec0;
        }
        else if (uVar18 != 0) {
          cRam3016e6 = *(char *)((uint3)((uVar18 - 1) * 0x18 + -0x4d84 +
                                        (uRam30214a & 0xff) + (uRam30214c & 0xff) * 8) + 0x10000) +
                       -0x80;
          uVar3 = (uint)uVar23 * (uint)(cRam3016e6 * 4 + 0x8000);
          uVar23 = (ushort)(uVar3 / 0x8000);
          MDH = (ushort)(uVar3 % 0x8000);
          MDC = MDC | 0x10;
          MDL = uVar23;
        }
        *(ushort *)((uint3)uVar10 + 0x301f00) = uVar23;
        if (0x19 < uVar10) break;
        uVar10 = uVar10 + 2;
        uVar23 = uVar18 + 1;
        if (4 < uVar18 + 1) {
          uVar23 = uVar18 - 4;
        }
      }
      bRam3016b4 = (byte)uVar18;
      if (4 < uVar18) {
        bRam3016b4 = bRam3016b4 - 5;
      }
      uVar23 = 0;
      while( true ) {
        if ((*(byte *)((uint3)uVar23 + 0x302314) & 0x20) == 0) {
          if (cRam3016b7 != '\0') {
            cRam3016b7 = cRam3016b7 + -1;
          }
          if (cRam3016b9 != '\0') {
            cRam3016b9 = cRam3016b9 + -1;
          }
          if (cRam3016b6 != '\0') {
            cRam3016b6 = cRam3016b6 + -1;
          }
        }
        if (7 < (byte)uVar23) break;
        uVar23 = (ushort)(byte)((byte)uVar23 + 1);
      }
      sRam302108 = uRam301f16 - uRam301f14;
      if (uRam301f16 < uRam301f14) {
        if (sRam302108 >= 0) {
          sRam302108 = -0x8000;
        }
      }
      else if (sRam302108 < 0) {
        sRam302108 = 0x7fff;
      }
      sRam302106 = uRam301f14 - uRam301f12;
      if (uRam301f14 < uRam301f12) {
        if (sRam302106 >= 0) {
          sRam302106 = -0x8000;
        }
      }
      else if (sRam302106 < 0) {
        sRam302106 = 0x7fff;
      }
      sRam302104 = uRam301f12 - uRam009f10;
      if (uRam301f12 < uRam009f10) {
        if (sRam302104 >= 0) {
          sRam302104 = -0x8000;
        }
      }
      else if (sRam302104 < 0) {
        sRam302104 = 0x7fff;
      }
      goto LAB_0a0678;
    }
    goto LAB_0a1a3a;
  }
LAB_0a0678:
  puVar5 = DAT_00e316;
  __atomic(3);
  if ((((uRam303a98 & 1) == 0) && ((uRam303b9c & 1) == 0)) &&
     ((vfzg_class <= bRam01a0f0 || ((uRam00fd64 & 0x800) == 0)))) {
    PSW = PSW & 0xffbf;
  }
  else {
    PSW = PSW | 0x40;
  }
  uVar23 = PSW & 0x40;
  if (((uRam303be4 & 1) == 0) && ((uRam303be0 & 1) == 0)) {
    PSW = PSW & 0xffbf;
  }
  else {
    PSW = PSW | 0x40;
  }
  uVar10 = PSW & 0x40;
  if (((uRam303b82 & 1) == 0) && ((uRam303b50 & 1) == 0)) {
    PSW = PSW & 0xffbf;
  }
  else {
    PSW = PSW | 0x40;
  }
  uVar18 = PSW & 0x40;
  if (((((uRam303a98 & 1) == 0) && ((uRam303b9c & 1) == 0)) && ((uRam00fd0e & 0x100) == 0)) &&
     (((uRam00fd5c & 2) == 0 && ((vfzg_class <= bRam01a0f0 || ((uRam00fd64 & 0x800) == 0)))))) {
    PSW = PSW & 0xffbf;
  }
  else {
    PSW = PSW | 0x40;
  }
  uVar2 = PSW & 0x40;
  if ((((uRam303ba0 & 1) == 0) && ((uRam303ba2 & 1) == 0)) && ((bRam3012ea & 1) == 0)) {
    PSW = PSW & 0xffbf;
  }
  else {
    PSW = PSW | 0x40;
  }
  uRam00fd58 = uRam00fd58 & 0xe85f | (uVar23 >> 6) << 8 | (uVar10 >> 6) << 0xc | (uVar18 >> 6) << 7
               | (uVar2 >> 6) << 9 | ((PSW & 0x40) >> 6) << 10 |
               ((_flags_start_phase & 0x2000) >> 0xd) << 5;
  __atomic(3);
  uRam00e5b6 = uVar14;
  puRam00e5b8 = (undefined1 *)puVar6;
  *DAT_00e316 = *DAT_00e316;
  uVar23 = uRam302b0a;
  if ((short)uRam302b0a < 0) {
    uVar23 = -uRam302b0a;
  }
  if (cRam3016b6 == '\0') {
    puVar1 = (ushort *)((uRam301998 >> 8) * 2 + 0x661c);
    if (uVar23 == *puVar1 || uVar23 < *puVar1) {
LAB_0a0790:
      uRam00fdb0 = uRam00fdb0 & 0xfffd;
    }
    else {
      uRam00fdb0 = uRam00fdb0 | 2;
    }
  }
  else {
    if (uVar23 <= uRam01662c) goto LAB_0a0790;
    uRam00fdb0 = uRam00fdb0 | 2;
  }
  if ((uRam00fdac & 8) == 0) {
    uRam00fdb0 = uRam00fdb0 & 0xffdf;
  }
  else {
    uRam00fdac = uRam00fdac & 0xfff7;
    uRam00fdb0 = uRam00fdb0 | 0x20;
  }
  __atomic(3);
  uVar23 = *DAT_00e316;
  *DAT_00e316 = (ushort)bRam304979;
  DAT_00e316 = (ushort *)uVar23;
  puVar5[-1] = 9;
  puVar5[-2] = 0xfa;
  uRam302b62 = func_0x042464(uRam0240f4,0xf5,9);
  bRam3016aa = func_0x040b3e(0x3f31,nmot_rpmclass);
  __atomic(3);
  *puVar5 = (ushort)DAT_00e316;
  uVar23 = uRam00fd58;
  if (_afterstart_timer < uRam302b62) {
    uRam00fdb0 = uRam00fdb0 | 0x10;
  }
  else {
    uRam00fdb0 = uRam00fdb0 & 0xffef;
  }
  if (((((uRam00fdb0 & 2) == 0) && ((uRam00fdb0 & 0x20) == 0)) &&
      ((*(byte *)((uint3)((byte)(bRam00e19d + 2) >> 1) + 0x302314) & 0x20) == 0)) &&
     (((uRam00fdb0 & 0x10) == 0 && ((uRam00fd58 & 0x20) == 0)))) {
    if ((((DAT_00fd1e & 0x400) != 0) || ((DAT_00fd1e & 0x2000) != 0)) ||
       (((uRam00fd20 & 0x20) != 0 && (bRam3016aa < DAT_301792)))) {
      uRam00fd58 = uRam00fd58 | 8;
      goto LAB_0a094a;
    }
    uRam00fd58 = uRam00fd58 & 0xfff7;
    if ((((((((uVar23 & 0x40) != 0) || ((uVar23 & 0x400) != 0)) || ((uRam00fd10 & 0x8000) == 0)) ||
          ((((bRam013f30 & 2) != 0 && ((uRam00fd6e & 0x400) != 0)) ||
           (((bRam013f4f & 0x40) != 0 && (((DAT_00fd4e & 0x4000) != 0 && (cRam3016a1 != '\0'))))))))
         || ((flags_torque_revlimit & 0x80) != 0)) ||
        (((uRam00fdb2 & 0x100) == 0 &&
         ((((((bRam013f4f & 0x80) != 0 &&
             ((bool)((byte)((uRam00fd38 & 0x40) >> 6) ^ (byte)((uRam00fdae & 8) >> 3)))) ||
            (((bRam013f4f & 0x20) != 0 &&
             (((uRam00fd1c & 0x2000) != 0 && ((uRam00fdb0 & 0x1000) == 0)))))) ||
           (((_flags_diag_cfg_a & 0x10) != 0 &&
            ((((bRam013f4f & 1) != 0 && ((bool)((byte)(uRam00fd26 >> 0xf) ^ (byte)uRam00fdb0 & 1)))
             || (((bRam013f4f & 2) != 0 &&
                 ((bool)((byte)uRam00fd28 & 1 ^ (byte)(uRam00fdae >> 0xf)))))))))) ||
          (((((bRam013f4f & 8) != 0 && (cRam3016b6 == '\0')) &&
            ((bool)(((byte)(uRam00fd16 >> 8) & 0x40) >> 6 ^ (byte)((uRam00fdb2 & 4) >> 2)))) ||
           (((bRam013f4f & 0x10) != 0 &&
            ((bool)((byte)((uRam00fd66 & 8) >> 3) ^ ((byte)(uRam00fdb0 >> 8) & 0x40) >> 6)))))))))))
       || ((bRam301626 < bRam013f9b ||
           ((((uVar23 & 0x100) != 0 || ((uRam00fd0e & 0x100) != 0)) ||
            (((uRam00fd5c & 2) != 0 ||
             ((((uRam00fd70 & 0x200) != 0 || ((uRam00fd26 & 0x1000) != 0)) ||
              ((uVar23 & 0x1000) != 0)))))))))) goto LAB_0a094a;
    if ((uRam00fdb0 & 0x2000) != 0) {
      uRam00fdb0 = uRam00fdb0 & 0xdfff;
      uRam00fdac = uRam00fdac | 2;
    }
  }
  else {
LAB_0a094a:
    if ((bRam013f50 & 1) == 0) {
      uRam00fdac = uRam00fdac & 0xfffd;
    }
    else {
      uRam00fdac = uRam00fdac | 2;
    }
  }
  uRam00fdae = uRam00fdae & 0x7fff | uRam00fd28 << 0xf;
  uRam00fdb0 = uRam00fdb0 & 0xaffe | uRam00fd26 >> 0xf | ((uRam00fd1c & 0x2000) >> 0xd) << 0xc |
               ((uRam00fd66 & 8) >> 3) << 0xe;
  uRam00fdb2 = uRam00fdb2 & 0xfefb | ((uRam00fd16 & 0x4000) >> 0xe) << 2;
  __atomic(3);
  DAT_00e316 = (ushort *)*puVar5;
  if ((((uRam00fd1c & 0x2000) == 0) || (vfzg_class != 0)) || ((uRam303c1e & 1) != 0)) {
    PSW = PSW & 0xffbf;
  }
  else {
    PSW = PSW | 0x40;
  }
  uRam00fd58 = uRam00fd58 & 0xdfff | ((PSW & 0x40) >> 6 ^ 1) << 0xd;
  bRam3016a9 = func_0x040b3e(0x3f3e,uRam304785);
  __atomic(3);
  *puVar5 = (ushort)DAT_00e316;
  DAT_00e316 = puVar5;
  if ((uRam00fd58 & 0x2000) == 0) {
    uVar23 = func_0x041106(0x3f51,uRam301998);
  }
  else {
    uVar23 = func_0x04119c(0x3f5b,0x273e,uRam301974,uRam301998);
  }
  puVar6 = DAT_00e316;
  MDL = (ushort)((uint)uVar23 * (uint)bRam3016a9);
  MDH = (ushort)((uint)uVar23 * (uint)bRam3016a9 >> 0x10);
  MDC = MDC | 0x10;
  uVar23 = MDL >> 7;
  if (0xff < uVar23) {
    uVar23 = 0xff;
  }
  if (rl_byte < (byte)uVar23) {
    uRam00fdb0 = uRam00fdb0 | 8;
  }
  else {
    uRam00fdb0 = uRam00fdb0 & 0xfff7;
  }
  if ((bRam013f5a < nmot_rpmclass) || (nmot_rpmclass < bRam013f59)) {
    uRam00fdb0 = uRam00fdb0 | 4;
  }
  else {
    uRam00fdb0 = uRam00fdb0 & 0xfffb;
  }
  if (((((uRam00fdb0 & 8) == 0) && ((uRam00fdb0 & 4) == 0)) && ((uRam00fd4c & 0x200) != 0)) &&
     (((bRam013f30 & 1) == 0 || (((uRam00fd70 & 0x20) == 0 && ((uRam00fd70 & 0x200) == 0)))))) {
    uRam00fdac = uRam00fdac & 0xfffb;
  }
  else {
    uRam00fdac = uRam00fdac | 4;
  }
  if ((((uRam00fdac & 4) == 0) && ((uRam00fdac & 2) != 0)) && ((_flags_start_phase & 0x100) == 0)) {
    if (cRam3016b9 == '\0') {
      uRam00fd58 = uRam00fd58 & 0xffef;
    }
  }
  else {
    uRam00fd58 = uRam00fd58 | 0x10;
    cRam3016b9 = cRam3016b5;
  }
  puVar8 = (undefined1 *)(ushort)bRam00e19d;
  if ((((uRam00fd1c & 0x2000) == 0) || (vfzg_class != 0)) || ((uRam303c1e & 1) != 0)) {
    PSW = PSW & 0xffbf;
  }
  else {
    PSW = PSW | 0x40;
  }
  uVar23 = (PSW & 0x40) >> 6;
  uRam00fd58 = uRam00fd58 & 0xbfff | uVar23 << 0xe;
  if (uVar23 == 0) {
    if ((uRam00fd26 & 0x8000) == 0) {
      if ((uRam00fd28 & 1) == 0) {
        uVar21 = 0x42a1;
      }
      else {
        uVar21 = 0x4321;
      }
    }
    else {
      uVar21 = 0x42e1;
    }
    cVar11 = me7_lookup_2d_sbyte_bilinear(uVar21,0x273e,uRam3019c2,uRam301998);
  }
  else {
    __atomic(3);
    uVar23 = *DAT_00e316;
    puRam00e5b8 = puVar8;
    *DAT_00e316 = (ushort)rl_byte;
    DAT_00e316 = (ushort *)uVar23;
    puVar6[-1] = 9;
    puVar6[-2] = 0x125;
    cVar11 = func_0x042420(uRam02411c,0x11d,9);
    __atomic(3);
    *puVar6 = (ushort)DAT_00e316;
    puVar8 = puRam00e5b8;
    DAT_00e316 = puVar6;
  }
  if ((uRam00fdfe & 0x20) == 0) {
    uVar21 = 0x4421;
  }
  else {
    uVar21 = 0x4429;
  }
  cRam3016eb = func_0x041126(uVar21,uRam3019ea);
  cRam3016ae = cVar11 + cRam3016eb;
  if (cVar11 < '\0' == cRam3016eb < '\0' && (char)(cVar11 + cRam3016eb) < '\0' != cVar11 < '\0') {
    cRam3016ae = '\x7f';
  }
  if ((uRam00fd26 & 0x8000) == 0) {
    if ((uRam00fd28 & 1) == 0) {
      uVar21 = 0x4112;
    }
    else {
      uVar21 = 0x4192;
    }
  }
  else {
    uVar21 = 0x4152;
  }
  cVar11 = me7_lookup_2d_sbyte_bilinear(uVar21,0x273e,uRam3019c2,uRam301998);
  cRam3016ee = cVar11 + cRam3016eb;
  if (cVar11 < '\0' == cRam3016eb < '\0' && (char)(cVar11 + cRam3016eb) < '\0' != cVar11 < '\0') {
    cRam3016ee = '\x7f';
  }
  if ((uRam00fd26 & 0x8000) == 0) {
    if ((uRam00fd28 & 1) == 0) {
      uVar21 = 0x4009;
    }
    else {
      uVar21 = 0x4089;
    }
  }
  else {
    uVar21 = 0x4049;
  }
  uRam3016de = func_0x04119c(uVar21,0x273e,uRam3019c2,uRam301998);
  bRam3016d9 = func_0x041106(0x4001,uRam301998);
  cRam3016e2 = me7_lookup_2d_sbyte_bilinear(0x43a1,0x273e,uRam3019c2,uRam301998);
  cRam3016e3 = me7_lookup_2d_sbyte_bilinear(0x43e1,0x273e,uRam3019c2,uRam301998);
  uVar23 = uRam00fdae;
  uVar21 = 0x4441;
  bVar16 = 3;
  if ((bRam303276 & 0x80) == 0) {
LAB_0a0c74:
    cVar11 = func_0x041126(uVar21,uRam301998);
    uVar14 = extraout_r3_04;
  }
  else {
    uVar18 = uRam30214a & 0xff;
    uVar14 = CONCAT11(extraout_RH5,bRam303277) >> uVar18;
    uVar10 = uVar14 & 1;
    cVar11 = (char)(uRam30214a >> 8);
    if (cVar11 != '\0') {
      uVar10 = uVar10 & (uVar14 & 2) >> 1;
    }
    uRam00fdae = uRam00fdae & 0xfeff | uVar10 << 8;
    uVar21 = 0x4439;
    bVar16 = 2;
    if (uVar10 == 0) goto LAB_0a0c74;
    uVar14 = CONCAT11(*(undefined1 *)((uint3)(uRam30214c & 0xff) + 0x30327a),
                      *(undefined1 *)((uint3)(uRam30214c & 0xff) + 0x303279)) >> uVar18;
    uVar2 = uVar14 & 1;
    uVar23 = uVar23 & 0xfcff | uVar10 << 8;
    cVar12 = (char)(uRam30214c >> 8);
    if (cVar12 != '\0') {
      uVar2 = uVar2 & (uVar14 & 0x100) >> 8;
    }
    uRam00fdae = uVar23 | uVar2 << 9;
    if (cVar11 != '\0') {
      uVar10 = (uVar2 & (uVar14 & 2) >> 1) << 9;
      uRam00fdae = uVar23 | uVar10;
      if (cVar12 != '\0') {
        uRam00fdae = uVar23 | uVar10 & uVar14 & 0x200;
      }
    }
    uVar21 = 0x4431;
    bVar16 = 1;
    if ((uRam00fdae & 0x200) == 0) goto LAB_0a0c74;
    uVar23 = bRam303278 >> uVar18 & 1;
    if (cVar11 != '\0') {
      uVar23 = uVar23 & (bRam303278 >> uVar18 & 2) >> 1;
    }
    uRam00fdae = uRam00fdae & 0xf7ff | uVar23 << 0xb;
    bVar16 = 0;
    cVar11 = '\0';
    uVar14 = extraout_r3_03;
    if (uVar23 == 0) {
      bVar16 = 1;
      goto LAB_0a0c74;
    }
  }
  cRam3016b3 = cVar11 << 1;
  cVar12 = '\0';
  cRam3016b2 = cVar11;
  bRam3016c3 = bVar16;
  if ((bVar16 & 2) != 0) {
    cVar12 = func_0x041126(0x4109,uRam301998);
    uVar14 = extraout_r3_05;
  }
  uVar23 = uRam00fdae | 0x20;
  if (rpmclass_oppoint < bRam013f04) {
    uVar23 = uRam00fdae & 0xffdf;
  }
  uRam00fdae = uVar23;
  if ((((uRam00fdae & 0x20) == 0) || ((uRam00fd60 & 0x80) != 0)) ||
     (((((uRam00fd16 & 0x200) != 0 || (((uRam00fd10 & 0x8000) == 0 || ((uRam00fd58 & 0x80) != 0))))
       || ((uRam00fd5a & 0x10) != 0)) ||
      ((((uRam00fdae & 0x10) != 0 || ((uRam00fd4c & 0x1000) == 0)) || ((uRam00fd58 & 0x400) != 0))))
     )) {
    if ((bRam013f50 & 2) == 0) {
      uRam00fdae = uRam00fdae | 0x80;
    }
    else {
      uRam00fdae = uRam00fdae & 0xff7f;
    }
  }
  else {
    uRam00fdae = uRam00fdae & 0xff7f;
  }
  if (((((bRam013f4f & 0x80) != 0) &&
       ((bool)((byte)((uRam00fd38 & 0x40) >> 6) ^ (byte)((uRam00fdae & 8) >> 3)))) ||
      (((uRam00fd10 & 0x8000) == 0 ||
       (((flags_torque_revlimit & 0x80) == 0 ||
        ((*(byte *)((uint3)(byte)(bRam00e19d + 2) + 0x301c00) & 0x20) != 0)))))) ||
     (((uRam00fd58 & 0x20) != 0 ||
      (((((((uRam00fdb0 & 0x10) != 0 || ((uRam00fd58 & 0x200) != 0)) || ((uRam00fd70 & 0x200) != 0))
         || (((uRam00fd58 & 0x1000) != 0 || ((uRam00fd06 & 8) != 0)))) ||
        ((uRam00fd58 & 0x400) != 0)) || ((uRam00fd26 & 0x1000) != 0)))))) {
    if ((bRam013f50 & 4) == 0) {
      uRam00fdae = uRam00fdae | 0x40;
    }
    else {
      uRam00fdae = uRam00fdae & 0xffbf;
    }
  }
  else {
    uRam00fdae = uRam00fdae & 0xffbf;
  }
  uRam00fdae = uRam00fdae & 0xfff7 | ((uRam00fd38 & 0x40) >> 6) << 3;
  cRam3016ec = cVar12;
  if (((((bRam013f30 & 2) != 0) && ((uRam00fd6e & 0x400) != 0)) ||
      ((uVar23 = bRam013f30 & 1, (bRam013f30 & 1) != 0 && ((uRam00fd70 & 0x20) != 0)))) ||
     ((uRam00fd5c & 2) != 0)) {
    uVar23 = 0x40;
    bRam304d9f = bRam304d9f | 0x40;
  }
  while (bVar16 = (byte)puVar8, 0x11 < (byte)(bRam00e19c - bVar16)) {
    uVar9 = (undefined1)((ushort)puVar8 >> 8);
    puVar7 = (undefined1 *)CONCAT11(uVar9,bVar16 + 2);
    if ((*(byte *)((uint3)((byte)(bVar16 + 2) >> 1) + 0x302314) & 0x20) == 0) {
      if (cRam3016b6 != '\0') {
        cRam3016b6 = cRam3016b6 + -1;
      }
      cRam3016b5 = cRam013f4b;
    }
    else {
      cRam3016b5 = cRam013f4c;
      cRam3016b7 = cRam013f4c;
      cRam3016b9 = cRam013f4c;
      cRam3016b6 = cRam013f4d;
    }
    uVar23 = bRam3016b4 + 1;
    if (4 < uVar23) {
      uVar23 = bRam3016b4 - 4;
    }
    bRam3016b4 = (byte)uVar23;
    if ((((uRam00fdac & 4) == 0) && ((uRam00fdac & 2) != 0)) && (cRam3016b9 != '\0')) {
      cRam3016b9 = cRam3016b9 + -1;
    }
    bVar19 = puVar7[-0x6400];
    uRam00e5b6 = CONCAT11((char)(uVar14 >> 8),bVar19);
    if ((bVar19 & 0x10) != 0) {
      uRam30241c = uRam30241c + 1;
    }
    sRam302102 = sRam302104;
    sRam302104 = sRam302106;
    sRam302106 = sRam302108;
    uVar23 = *(ushort *)((uint3)CONCAT11(uVar9,bVar16 + 8) + 0x301f00);
    uVar14 = *(ushort *)((uint3)CONCAT11(uVar9,bVar16 + 6) + 0x301f00);
    sRam302108 = uVar23 - uVar14;
    if (uVar23 < uVar14) {
      if (sRam302108 >= 0) {
        sRam302108 = -0x8000;
      }
    }
    else if (sRam302108 < 0) {
      sRam302108 = 0x7fff;
    }
    uVar23 = *(ushort *)((uint3)CONCAT11(uVar9,bVar16 - 4) + 0x301f00);
    sRam302100 = *(ushort *)(ZEXT23(puVar8) + 0x301f00) - uVar23;
    if (*(ushort *)(ZEXT23(puVar8) + 0x301f00) < uVar23) {
      if (sRam302100 >= 0) {
        sRam302100 = -0x8000;
      }
    }
    else if (sRam302100 < 0) {
      sRam302100 = 0x7fff;
    }
    sRam302100 = sRam302100 >> 1;
    uVar23 = *(ushort *)((uint3)CONCAT11(uVar9,bVar16 - 8) + 0x301b00);
    sRam302150 = uVar23 - *(ushort *)(ZEXT23(puVar7) + 0x301b00);
    if (uVar23 < *(ushort *)(ZEXT23(puVar7) + 0x301b00)) {
      if (sRam302150 >= 0) {
        sRam302150 = -0x8000;
      }
    }
    else if (sRam302150 < 0) {
      sRam302150 = 0x7fff;
    }
    if (sRam302150 < 0) {
      sRam302150 = -sRam302150;
    }
    sVar17 = 0;
    uVar23 = *(ushort *)(puVar7 + -0x6500);
    uVar3 = (uint)uVar23 * (uint)uVar23;
    MDL = (ushort)(uVar3 >> 0x10);
    uVar14 = (ushort)uVar3;
    if (MDL == 0) {
LAB_0a0ea0:
      MDL = uVar14;
      cRam00e19b = (char)sVar17;
    }
    else {
      cRam00e19b = '\x10';
      sVar17 = 0;
      if (MDL != 0) {
        sVar17 = LZCOUNT(MDL);
      }
      if (sVar17 != 0) {
        sVar17 = 0x10 - sVar17;
        uVar14 = (ushort)((uVar3 & 0xffff | (uint)MDL << 0x10) / (uint)(ushort)(1 << sVar17));
        goto LAB_0a0ea0;
      }
    }
    sVar17 = 0;
    uVar3 = (uint)uVar23 * (uint)MDL;
    MDL = (ushort)(uVar3 >> 0x10);
    uVar23 = (ushort)uVar3;
    if (MDL == 0) {
LAB_0a0ec0:
      MDL = uVar23;
      cVar11 = (char)sVar17;
    }
    else {
      cVar11 = '\x10';
      sVar17 = 0;
      if (MDL != 0) {
        sVar17 = LZCOUNT(MDL);
      }
      if (sVar17 != 0) {
        sVar17 = 0x10 - sVar17;
        uVar23 = (ushort)((uVar3 & 0xffff | (uint)MDL << 0x10) / (uint)(ushort)(1 << sVar17));
        goto LAB_0a0ec0;
      }
    }
    cRam00e19b = cRam00e19b + cVar11;
    sVar17 = 0;
    if (sRam302150 != 0) {
      sVar17 = LZCOUNT(sRam302150) + -1;
    }
    uVar10 = CONCAT11((char)((ushort)sVar17 >> 8),(char)sVar17 + '\x10' + cRam00e19b);
    uVar3 = (uint)(ushort)(sRam302150 << sVar17) << 0x10;
    uVar14 = (ushort)(uVar3 / MDL);
    MDH = (ushort)(uVar3 % (uint)MDL);
    MDC = MDC | 0x10;
    uVar23 = uVar10 - 0x26;
    if (uVar10 < 0x26) {
      if (uVar14 == 0) {
        uVar23 = 0;
      }
      else if ((ushort)LZCOUNT(uVar14) < -uVar23) {
        uVar23 = 0xffff;
      }
      else {
        uVar23 = uVar14 << -uVar23;
      }
    }
    else if (uVar23 < 0x10) {
      uVar23 = uVar14 >> uVar23;
    }
    else {
      uVar23 = 0;
    }
    if (0x7f < uVar23) {
      uVar23 = 0x7f;
    }
    bRam3016e4 = (byte)uVar23;
    if (bRam013f03 < bRam3016e4) {
      uRam00fdb0 = uRam00fdb0 | 0x800;
    }
    else {
      uRam00fdb0 = uRam00fdb0 & 0xf7ff;
    }
    if ((bVar19 & 0x10) == 0) {
      if (((((uRam00fdae & 1) == 0) || ((uRam00fdae & 0x80) != 0)) || ((uRam00fdae & 0x10) != 0)) ||
         ((((uRam00fdb0 & 0x800) != 0 || ((bRam303276 & 4) != 0)) ||
          ((cRam3016b7 != '\0' || (uRam00fdae = uRam00fdae & 0xfffb, cRam013ec1 == '\0')))))) {
        uRam00fdac = uRam00fdac & 0xefff;
      }
    }
    else {
      if ((((uRam00fdae & 1) == 0) || ((uRam00fdae & 0x80) != 0)) ||
         ((((uRam00fdae & 0x10) != 0 || (((uRam00fdb0 & 0x800) != 0 || ((bRam303276 & 4) != 0)))) ||
          ((cRam3016b7 != '\0' || (uRam00fdae = uRam00fdae & 0xfffb, cRam013ec1 == '\0')))))) {
        uRam00fdac = uRam00fdac & 0xcfff;
      }
      else {
        uRam00fdac = uRam00fdac | 0x2000;
      }
      bRam303276 = bRam303276 & 0xfe | ((byte)(uRam00fdac >> 8) & 0x10) >> 4;
      uRam00fdac = uRam00fdac & 0xefff | ((uRam00fdac & 0x2000) >> 0xd) << 0xc;
    }
    if ((bVar19 & 0x10) == 0) {
      if (((((uRam00fdae & 2) == 0) || ((uRam00fdae & 0x40) != 0)) || ((uRam00fdb0 & 0x800) != 0))
         || (cRam013ec1 == '\0')) {
        uRam00fdac = uRam00fdac & 0xbfff;
      }
    }
    else {
      if ((((uRam00fdae & 2) == 0) || ((uRam00fdae & 0x40) != 0)) ||
         (((uRam00fdb0 & 0x800) != 0 || (cRam013ec1 == '\0')))) {
        uRam00fdac = uRam00fdac & 0x3fff;
      }
      else {
        uRam00fdac = uRam00fdac | 0x8000;
      }
      bRam303276 = bRam303276 & 0xfd | (byte)(((uRam00fdac & 0x4000) >> 0xe) << 1);
      uRam00fdac = uRam00fdac & 0xbfff | (uRam00fdac >> 0xf) << 0xe;
    }
    if (((bRam303276 & 1) == 0) && ((bRam303276 & 2) == 0)) {
      bRam303276 = bRam303276 & 0xf7;
      cRam3016e7 = cRam013ec0;
    }
    else if ((bVar19 & 0x10) != 0) {
      if (cRam3016e7 == '\0') {
        bRam303276 = bRam303276 | 8;
      }
      else {
        cRam3016e7 = cRam3016e7 + -1;
      }
    }
    uRam00e5b2 = MDL;
    cRam3016e5 = cRam00e19b;
    uRam30214e = MDL;
    if ((bVar19 & 0x10) != 0) {
      uRam3016e9 = (undefined1)(CONCAT11(uVar9,bVar16 - 8) >> 1);
      puRam00e5b8 = puVar7;
      MDL = uVar14;
      func_0x09f3b6();
      puVar7 = puRam00e5b8;
    }
    if ((uRam00e5b6 & 0x10) == 0) {
      iVar4 = (uint)(bRam3016b4 - 1) * 0x18;
      MDL = (ushort)iVar4;
      MDH = (ushort)((uint)iVar4 >> 0x10);
      MDC = MDC | 0x10;
      uVar21 = 0x3f1e;
      if ((_flags_diag_cfg_a & 0x10) != 0) {
        uVar21 = 0x3f27;
      }
      cRam3016e6 = func_0x04119c(MDL + -0x4d84,uVar21,uRam30214c >> 8 | uRam30214c << 8,
                                 uRam30214a >> 8 | uRam30214a << 8);
      cRam3016e6 = cRam3016e6 + -0x80;
      uVar23 = cRam3016e6 * 4 + 0x8000;
    }
    else {
      uVar23 = 0x8000;
    }
    uVar14 = CONCAT11((char)((ushort)puVar7 >> 8),(char)puVar7 + '\n');
    uVar3 = (uint)*(ushort *)((uint3)uVar14 + 0x301b00) * (uint)uVar23;
    MDL = (ushort)(uVar3 / 0x8000);
    MDH = (ushort)(uVar3 % 0x8000);
    MDC = MDC | 0x10;
    *(ushort *)((uint3)uVar14 + 0x301f00) = MDL;
    puVar6 = DAT_00e316;
    if (_afterstart_timer >> 2 < 0x100) {
      uRam00f431 = (undefined1)(_afterstart_timer >> 2);
    }
    else {
      uRam00f431 = 0xff;
    }
    __atomic(3);
    DAT_00e316 = (ushort *)*DAT_00e316;
    puRam00e5b8 = puVar7;
    bRam00f430 = me7_lookup_1d_byte(0x20fc,6,uRam00f431);
    __atomic(3);
    *puVar6 = (ushort)DAT_00e316;
    puVar8 = puRam00e5b8;
    DAT_00e316 = puVar6;
    cRam3016af = func_0x0427ba((short)cRam3016ae,cRam3016b2);
    cVar11 = cRam3016af;
    if ((((char)(cRam3016af - cRam3016b0) < '\0' !=
          (cRam3016af < '\0' != cRam3016b0 < '\0' &&
          (char)(cRam3016af - cRam3016b0) < '\0' != cRam3016af < '\0')) &&
        (cVar11 = cRam3016b0, (uRam00e5b6 & 0x10) != 0)) &&
       (((uRam30241c & 1) == 0 &&
        ((cVar12 = func_0x042968((short)cRam3016b0,uRam01421c), cVar11 = cVar12, cVar12 != -0x80 &&
         (cVar11 = cRam3016af,
         (char)(cVar12 - cRam3016af) < '\0' ==
         (cVar12 < '\0' != cRam3016af < '\0' && (char)(cVar12 - cRam3016af) < '\0' != cVar12 < '\0')
         )))))) {
      cVar11 = cVar12;
    }
    cRam3016b0 = cVar11;
    cVar11 = cRam3016e2;
    if ((uRam00fd26 & 0x8000) != 0) {
      cVar11 = cRam3016e3;
    }
    cRam3016e1 = cRam3016eb + cVar11;
    if (cRam3016eb < '\0' == cVar11 < '\0' &&
        (char)(cRam3016eb + cVar11) < '\0' != cRam3016eb < '\0') {
      cRam3016e1 = '\x7f';
    }
    cVar11 = cRam3016e1;
    if (((((char)(cRam3016e1 - cRam3016e0) < '\0' !=
           (cRam3016e1 < '\0' != cRam3016e0 < '\0' &&
           (char)(cRam3016e1 - cRam3016e0) < '\0' != cRam3016e1 < '\0')) &&
         (cVar11 = cRam3016e0, (uRam00e5b6 & 0x10) != 0)) && ((uRam30241c & 1) == 0)) &&
       ((cVar12 = func_0x042968((short)cRam3016e0,uRam01421c), cVar11 = cVar12, cVar12 != -0x80 &&
        (cVar11 = cRam3016e1,
        (char)(cVar12 - cRam3016e1) < '\0' ==
        (cVar12 < '\0' != cRam3016e1 < '\0' && (char)(cVar12 - cRam3016e1) < '\0' != cVar12 < '\0'))
        ))) {
      cVar11 = cVar12;
    }
    cRam3016e0 = cVar11;
    cRam3016ef = cRam3016ee + cRam3016ec;
    if (cRam3016ee < '\0' == cRam3016ec < '\0' &&
        (char)(cRam3016ee + cRam3016ec) < '\0' != cRam3016ee < '\0') {
      cRam3016ef = '\x7f';
    }
    cVar11 = cRam3016ef;
    if ((((char)(cRam3016ef - cRam3016ed) < '\0' !=
          (cRam3016ef < '\0' != cRam3016ed < '\0' &&
          (char)(cRam3016ef - cRam3016ed) < '\0' != cRam3016ef < '\0')) &&
        (cVar11 = cRam3016ed, (uRam00e5b6 & 0x10) != 0)) &&
       (((uRam30241c & 1) == 0 &&
        ((cVar12 = func_0x042968((short)cRam3016ed,uRam014111), cVar11 = cVar12, cVar12 != -0x80 &&
         (cVar11 = cRam3016ef,
         (char)(cVar12 - cRam3016ef) < '\0' ==
         (cVar12 < '\0' != cRam3016ef < '\0' && (char)(cVar12 - cRam3016ef) < '\0' != cVar12 < '\0')
         )))))) {
      cVar11 = cVar12;
    }
    cRam3016ed = cVar11;
    bRam3016dd = func_0x042778(cRam3016b3,uRam3016de);
    uVar10 = uRam00e5b6;
    bVar16 = bRam3016dd;
    if ((((bRam3016dd < bRam3016dc) && (bVar16 = bRam3016dc, (uRam00e5b6 & 0x10) != 0)) &&
        ((uRam30241c & 1) == 0)) &&
       ((bRam3016dc < PTR_DAT_013ffe._2_1_ ||
        (bVar16 = bRam3016dc - PTR_DAT_013ffe._2_1_,
        (byte)(bRam3016dc - PTR_DAT_013ffe._2_1_) < bRam3016dd)))) {
      bVar16 = bRam3016dd;
    }
    bRam3016dc = bVar16;
    uRam00fdb0 = uRam00fdb0 & 0xfe3f;
    if ((uRam00fdac & 4) != 0) {
      uRam00fdae = uRam00fdae | 0x2000;
      cRam3016b8 = cRam3016b5;
    }
    if (cRam3016b8 == '\0') {
      uRam00fdae = uRam00fdae & 0xdfff;
    }
    else if ((uRam00fdac & 4) == 0) {
      cRam3016b8 = cRam3016b8 + -1;
    }
    if ((uRam00fdac & 2) == 0) {
      uRam00fdb0 = uRam00fdb0 | 0x2000;
      cRam3016b7 = cRam3016b5;
      uRam00fdae = uRam00fdae | 4;
    }
    sVar17 = *(short *)(puVar8 + -0x6500);
    uRam00fdac = uRam00fdac & 0xfc7f;
    *(short *)((uint3)bRam3016b4 * 2 + 0x302112) = sVar17;
    if (cRam3016b7 == '\0') {
      uVar23 = uRam00fdae & 0xfffb;
      uVar14 = uRam00fdae & 0x2000;
      uRam00fdae = uVar23;
      if (uVar14 != 0) {
        uVar10 = uVar10 | 8;
        goto LAB_0a12e2;
      }
LAB_0a12fe:
      cVar11 = (char)puVar8;
      uVar9 = (undefined1)((ushort)puVar8 >> 8);
      if (cRam01421f == '\x01') {
        if (nmot_rpmclass < bRam01444a) {
          sVar17 = sRam302102;
          sVar15 = sRam302100;
          if (sRam302100 - sRam302102 < 0 ==
              (sRam302100 < 0 != sRam302102 < 0 && sRam302100 - sRam302102 < 0 != sRam302100 < 0)) {
            sVar17 = sRam302100;
            sVar15 = sRam302102;
          }
          sVar13 = sRam302104;
          if (sVar17 - sRam302104 < 0 ==
              (sVar17 < 0 != sRam302104 < 0 && sVar17 - sRam302104 < 0 != sVar17 < 0)) {
            sVar13 = sVar17;
            sVar17 = sRam302104;
          }
          sVar20 = sRam302106;
          if (sVar13 - sRam302106 < 0 ==
              (sVar13 < 0 != sRam302106 < 0 && sVar13 - sRam302106 < 0 != sVar13 < 0)) {
            sVar20 = sVar13;
            sVar13 = sRam302106;
          }
          if (sVar20 - sRam302108 < 0 ==
              (sVar20 < 0 != sRam302108 < 0 && sVar20 - sRam302108 < 0 != sVar20 < 0)) {
            sVar20 = sRam302108;
          }
          sVar22 = sVar17;
          if (sVar15 - sVar17 < 0 == (sVar15 < 0 != sVar17 < 0 && sVar15 - sVar17 < 0 != sVar15 < 0)
             ) {
            sVar22 = sVar15;
            sVar15 = sVar17;
          }
          sRam30210c = sVar13;
          if (sVar22 - sVar13 < 0 == (sVar22 < 0 != sVar13 < 0 && sVar22 - sVar13 < 0 != sVar22 < 0)
             ) {
            sRam30210c = sVar22;
            sVar22 = sVar13;
          }
          if (sRam30210c - sVar20 < 0 ==
              (sRam30210c < 0 != sVar20 < 0 && sRam30210c - sVar20 < 0 != sRam30210c < 0)) {
            sRam30210c = sVar20;
          }
          if (sVar15 - sVar22 < 0 == (sVar15 < 0 != sVar22 < 0 && sVar15 - sVar22 < 0 != sVar15 < 0)
             ) {
            sVar22 = sVar15;
          }
          sVar17 = sVar22;
          sRam302110 = sRam30210c;
          if (sVar22 - sRam30210c < 0 ==
              (sVar22 < 0 != sRam30210c < 0 && sVar22 - sRam30210c < 0 != sVar22 < 0)) {
            sVar17 = sRam30210c;
            sRam30210c = sVar22;
            sRam302110 = sVar22;
          }
        }
        else {
LAB_0a1394:
          cVar12 = cVar11 + cRam01444b * -2;
          uVar23 = *(ushort *)((uint3)CONCAT11(uVar9,cVar12) + 0x301f00);
          uVar14 = *(ushort *)((uint3)CONCAT11(uVar9,cVar12 + '\n') + 0x301f00);
          if (uVar14 < uVar23) {
            MDH = 0xffff;
          }
          else {
            MDH = 0;
          }
          sRam30210e = (short)(CONCAT22(MDH,uVar14 - uVar23) / 5);
          MDC = MDC | 0x10;
          sRam302110 = sRam30210e;
        }
        sVar15 = sRam302104 - sRam302110;
        if (sRam302104 < 0 != sRam302110 < 0 && sRam302104 - sRam302110 < 0 != sRam302104 < 0) {
          if (sVar15 < 0) {
            sVar15 = 0x7fff;
          }
          else {
            sVar15 = -0x8000;
          }
        }
        uVar23 = uRam00fdac & 0x40;
        uRam00fdac = uRam00fdac & 0xffbf;
        if (uVar23 == 0x40) {
          uRam00fdac = uRam00fdac | (PSW & 1) << 6 | 0x40;
          sVar15 = -sVar15;
        }
        sVar13 = 0;
        if (sVar15 != 0) {
          sVar13 = LZCOUNT(sVar15) + -1;
        }
        MDH = sVar15 << sVar13;
        uVar23 = CONCAT11((char)((ushort)sVar13 >> 8),(char)sVar13 + '\x10' + cRam00e19b);
        MDL = 0;
        if (uRam00e5b2 == 0) goto LAB_0a144c;
        MDL = (ushort)(((uint)MDH << 0x10) / (uint)uRam00e5b2);
        MDH = (ushort)(((uint)MDH << 0x10) % (uint)uRam00e5b2);
        MDC = MDC | 0x10;
        uVar14 = uVar23 - 0x26;
        if (uVar23 < 0x26) {
          if (MDL == 0) {
            uVar23 = 0;
          }
          else if ((ushort)LZCOUNT(MDL) < -uVar14) {
            uVar23 = 0xffff;
          }
          else {
            uVar23 = MDL << -uVar14;
          }
        }
        else if (uVar14 < 0x10) {
          uVar23 = MDL >> uVar14;
        }
        else {
          uVar23 = 0;
        }
        if (0x7f < uVar23) {
          uVar23 = 0x7f;
        }
        bRam00e19e = (byte)uVar23;
        if ((uRam00fdac & 0x40) != 0) {
          bRam00e19e = -bRam00e19e;
        }
      }
      else {
        if (cRam014220 == '\x01') goto LAB_0a1394;
LAB_0a144c:
        bRam00e19e = 0;
      }
      if (((uRam00fdae & 0x2000) == 0) && ((uRam00fdb2 & 2) != 0)) {
        uVar23 = uRam00fdae & 4;
joined_r0x0a1492:
        if ((uVar23 == 0) && ((uRam00fdb2 & 0x8000) != 0)) {
          bRam00e19e = 0;
          uRam00e5b4 = uRam00e5b4 & 0xff;
          uRam302122 = uRam302122 & 0xff00;
          puVar7 = puVar8 + -10;
          do {
            *(undefined2 *)(ZEXT23(puVar7) + 0x302000) = 0;
            iVar4 = CONCAT22(MDH,MDL);
            puVar7 = puVar7 + 2;
          } while (puVar7 <= puVar8);
          bRam3016db = 0;
          bRam3016df = 0;
          goto LAB_0a1826;
        }
      }
      else if (((uRam00fdae & 4) == 0) && ((uRam00fdb2 & 1) != 0)) {
        uVar23 = uRam00fdae & 0x2000;
        goto joined_r0x0a1492;
      }
      uRam00fdac = uRam00fdac & 0xf3ff;
      bVar16 = bRam00e19e;
      if ((char)bRam00e19e < '\0') {
        uRam00fdac = uRam00fdac | 0x800;
        bVar16 = -bRam00e19e;
      }
      sVar15 = (short)((uint)bVar16 * 0x100 * (uint)bRam3016d9 * 0x100 >> 0x10);
      if ((uRam00fdac & 0x800) != 0) {
        sVar15 = -sVar15;
      }
      uVar23 = *(ushort *)((uint3)CONCAT11(uVar9,cVar11 + -10) + 0x302000);
      if ((short)uVar23 < 0) {
        uVar23 = -uVar23;
        uRam00fdac = uRam00fdac | 0x400;
      }
      iVar4 = (uint)((ushort)bRam3016d9 * -0x100) * (uint)uVar23;
      MDL = (ushort)iVar4;
      MDH = (ushort)((uint)iVar4 >> 0x10);
      MDC = MDC | 0x10;
      sVar13 = MDH;
      if ((uRam00fdac & 0x400) != 0) {
        sVar13 = -MDH;
      }
      uVar23 = sVar13 + sVar15;
      if (sVar13 < 0 == sVar15 < 0 && sVar13 + sVar15 < 0 != sVar13 < 0) {
        if ((short)uVar23 < 0) {
          uVar23 = 0x7fff;
        }
        else {
          uVar23 = 0x8000;
        }
      }
      *(ushort *)(puVar8 + -0x6000) = uVar23;
      bVar16 = (byte)(uVar23 >> 8);
      if ((uVar10 & 0x10) != 0) {
        bRam3016db = bRam3016df;
        bRam3016df = bVar16;
      }
      bVar19 = bVar16;
      if ((char)(bVar16 - bRam3016df) < '\0' ==
          ((short)uVar23 < 0 != (short)((ushort)bRam3016df << 8) < 0 &&
          (char)(bVar16 - bRam3016df) < '\0' != (short)uVar23 < 0)) {
        bVar19 = bRam3016df;
      }
      uRam00e5b6 = uVar10;
      bRam3016df = bVar19;
      uRam302122 = uVar23;
      cRam3016da = func_0x0427ba((short)(char)bRam3016db,bRam3016dc,sVar17);
      puVar6 = DAT_00e316;
      iVar4 = CONCAT22(MDH,MDL);
      if ((char)(cRam3016da - bVar16) < '\0' ==
          (cRam3016da < '\0' != (short)uVar23 < 0 &&
          (char)(cRam3016da - bVar16) < '\0' != cRam3016da < '\0')) {
        uRam00fdac = uRam00fdac & 0xff7f;
      }
      else {
        uRam00fdac = uRam00fdac | 0x80;
      }
      if (cRam3016ac == '\0') {
        uVar23 = *(ushort *)((uint3)CONCAT11(uVar9,cVar11 + -4) + 0x301f00);
        uVar10 = (ushort)((uint)*(ushort *)(puVar8 + -0x6100) * 3);
        iVar4 = (uint)*(ushort *)((uint3)CONCAT11(uVar9,cVar11 + -2) + 0x301f00) * 3;
        uVar18 = (ushort)iVar4;
        uVar14 = (uVar23 + uVar10) - uVar18;
        uVar18 = (((short)((uint)*(ushort *)(puVar8 + -0x6100) * 3 >> 0x10) +
                  (ushort)(uVar23 + uVar10 < uVar23 || uVar23 + uVar10 < uVar10)) -
                 (short)((uint)iVar4 >> 0x10)) - (ushort)(uVar23 + uVar10 < uVar18);
        uVar23 = *(ushort *)((uint3)CONCAT11(uVar9,cVar11 + '\x02') + 0x301f00);
        uVar10 = uVar14 - uVar23;
        uVar23 = (ushort)(uVar14 < uVar23);
        sVar17 = uVar18 - uVar23;
        if (sVar17 < 0) {
          uVar14 = -uVar10;
          if (sVar17 == -1) {
            if (uVar10 == 0) {
              uVar14 = 0xffff;
            }
          }
          else {
            uVar14 = 0xffff;
          }
        }
        else {
          uVar14 = uVar10;
          if (uVar18 != uVar23) {
            uVar14 = 0xffff;
          }
        }
        uVar14 = uVar14 >> 1;
        sVar17 = 0;
        if (uVar14 != 0) {
          sVar17 = LZCOUNT(uVar14) + -1;
        }
        uVar10 = CONCAT11((char)((ushort)sVar17 >> 8),(char)sVar17 + '\x10' + cRam00e19b);
        uRam302134 = (ushort)(((uint)(uVar14 << sVar17) << 0x10) / (uint)uRam00e5b2);
        uVar23 = uVar10 - 0x26;
        if (uVar10 < 0x26) {
          if (uRam302134 == 0) {
            uRam302134 = 0;
          }
          else if ((ushort)LZCOUNT(uRam302134) < -uVar23) {
            uRam302134 = 0xffff;
          }
          else {
            uRam302134 = uRam302134 << -uVar23;
          }
        }
        else if (uVar23 < 0x10) {
          uRam302134 = uRam302134 >> uVar23;
        }
        else {
          uRam302134 = 0;
        }
        if (0x7fff < uRam302134) {
          uRam302134 = 0x7fff;
        }
        MDL = (ushort)((uint)bRam01421e * (uint)uRam302134);
        if (0xffff < (uint)bRam01421e * (uint)uRam302134) {
          MDL = 0xffff;
        }
        uVar3 = ((uint)bRam01421d * (uint)MDL) / 0x40;
        MDL = (ushort)uVar3;
        if (0xffff < uVar3) {
          MDL = 0xffff;
        }
        iVar4 = (uint)(byte)-bRam01421e * 0x100 * (uint)uRam00e5b4;
        uVar23 = (ushort)((uint)iVar4 >> 0x10);
        MDC = MDC | 0x10;
        uRam00e5b4 = MDL + uVar23;
        if ((MDL + uVar23 < MDL || MDL + uVar23 < uVar23) || (0x7fff < uRam00e5b4)) {
          uRam00e5b4 = 0x7fff;
        }
      }
      cVar11 = cRam3016b0;
      if (((char)(cRam3016e0 - uRam00e5b4._1_1_) < '\0' !=
           (cRam3016e0 < '\0' != (short)uRam00e5b4 < 0 &&
           (char)(cRam3016e0 - uRam00e5b4._1_1_) < '\0' != cRam3016e0 < '\0')) &&
         ((bRam3016c3 & 3) < 2)) {
        iVar4 = (int)(short)(ushort)bRam3016c2 * (int)(short)cRam3016b0;
        MDC = MDC | 0x10;
        cVar11 = (char)((uint)iVar4 >> 8);
      }
      if (cVar11 < 0) {
LAB_0a1706:
        bRam3016b1 = bRam014449;
      }
      else {
        if ((ushort)bRam3016ab * (ushort)bRam00f430 < 0x8000) {
          uVar23 = (ushort)bRam3016ab * (ushort)bRam00f430 >> 7;
        }
        else {
          uVar23 = 0xff;
        }
        iVar4 = (int)(short)uVar23 * (int)(short)cVar11;
        MDC = MDC | 0x10;
        if ((ushort)iVar4 < 0x4000) {
          bRam3016b1 = (byte)((ushort)iVar4 >> 7);
        }
        else {
          bRam3016b1 = 0x7f;
        }
        if ((uRam00fd58 & 0x800) != 0) {
          if ((char)bRam3016b1 < '\0') {
            bRam3016b1 = 0x7f;
          }
          if (bRam3016b1 < bRam014449) goto LAB_0a1706;
        }
      }
      MDH = (ushort)((uint)iVar4 >> 0x10);
      MDL = (ushort)iVar4;
      if ((((char)(bRam3016b1 - bRam00e19e) < '\0' ==
            ((char)bRam3016b1 < '\0' != (char)bRam00e19e < '\0' &&
            (char)(bRam3016b1 - bRam00e19e) < '\0' != (char)bRam3016b1 < '\0')) ||
          ((uRam00fdae & 4) != 0)) || (cRam3016ac != '\0')) {
        uRam00fdac = uRam00fdac & 0xfdff;
      }
      else {
        uRam00fdac = uRam00fdac | 0x200;
      }
      if ((uRam00fd58 & 0x10) == 0) {
        __atomic(3);
        DAT_00e316 = (ushort *)*DAT_00e316;
        puRam00e5b8 = puVar8;
        func_0x09fa22();
        __atomic(3);
        *puVar6 = (ushort)DAT_00e316;
        iVar4 = CONCAT22(MDH,MDL);
        puVar8 = puRam00e5b8;
      }
      MDH = (ushort)((uint)iVar4 >> 0x10);
      MDL = (ushort)iVar4;
      uVar10 = uRam00e5b6;
      DAT_00e316 = puVar6;
      if (cRam3016ac == '\0') {
        uRam00fdb0 = uRam00fdb0 & 0x7fff;
        if ((uRam00fdac & 0x200) != 0) {
          uRam00fdb0 = uRam00fdb0 | 0x100;
          uVar10 = uRam00e5b6 | 4;
        }
        if ((uRam00fdac & 0x100) != 0) {
          uVar14 = CONCAT11((char)((ushort)puVar8 >> 8),(char)puVar8 + -6);
          uVar23 = *(ushort *)((uint3)uVar14 + 0x301c00);
          uVar14 = uVar14 >> 1;
          bVar16 = *(byte *)((uint3)uVar14 + 0x302314);
          *(byte *)((uint3)uVar14 + 0x302314) = bVar16 | 1;
          iVar4 = CONCAT22(MDH,MDL);
          if (((uVar23 & 4) == 0) && (iVar4 = CONCAT22(MDH,MDL), (bVar16 & 2) == 0)) {
            uRam00fdb0 = uRam00fdb0 | 0x80;
            iVar4 = CONCAT22(MDH,MDL);
          }
        }
      }
      MDH = (ushort)((uint)iVar4 >> 0x10);
      MDL = (ushort)iVar4;
      if (((uRam00fdac & 0x80) != 0) && ((uRam00fdae & 4) == 0)) {
        *(byte *)((uint3)((ushort)puVar8 >> 1) + 0x302314) =
             *(byte *)((uint3)((ushort)puVar8 >> 1) + 0x302314) | 2;
        iVar4 = CONCAT22(MDH,MDL);
        uRam00fdb0 = uRam00fdb0 | 0x40;
      }
      puVar6 = DAT_00e316;
      MDH = (ushort)((uint)iVar4 >> 0x10);
      MDL = (ushort)iVar4;
      if (((uRam00fd58 & 0x10) == 0) && (((uRam00fdb0 & 0x100) != 0 || ((uRam00fdb0 & 0x40) != 0))))
      {
        __atomic(3);
        DAT_00e316 = (ushort *)*DAT_00e316;
        uRam00e5b6 = uVar10;
        puRam00e5b8 = puVar8;
        func_0x09f92e(bRam3016b4);
        __atomic(3);
        *puVar6 = (ushort)DAT_00e316;
        iVar4 = CONCAT22(MDH,MDL);
        puVar8 = puRam00e5b8;
        uVar10 = uRam00e5b6;
      }
      MDH = (ushort)((uint)iVar4 >> 0x10);
      MDL = (ushort)iVar4;
      DAT_00e316 = puVar6;
      if (((uRam00fd58 & 0x10) == 0) && ((uRam00fdb0 & 0x80) != 0)) {
        bVar16 = bRam3016b4 + 3;
        if (4 < bVar16) {
          bVar16 = bRam3016b4 - 2;
        }
        __atomic(3);
        DAT_00e316 = (ushort *)*puVar6;
        uRam00e5b6 = uVar10;
        puRam00e5b8 = puVar8;
        func_0x09f92e(bVar16);
        __atomic(3);
        *puVar6 = (ushort)DAT_00e316;
        iVar4 = CONCAT22(MDH,MDL);
        puVar8 = puRam00e5b8;
        uVar10 = uRam00e5b6;
        DAT_00e316 = puVar6;
      }
    }
    else {
      uVar23 = uRam00fdae | 4;
      uVar10 = uVar10 & 0xfff7 | 0x80 | ((uRam00fdae & 0x2000) >> 0xd) << 3;
      uRam00fdae = uVar23;
      if ((uRam00fdac & 2) != 0) {
        cRam3016b7 = cRam3016b7 + -1;
      }
LAB_0a12e2:
      *(byte *)((uint3)((ushort)puVar8 >> 1) + 0x302314) =
           *(byte *)((uint3)((ushort)puVar8 >> 1) + 0x302314) & 0x20;
      iVar4 = CONCAT22(MDH,MDL);
      if (((uRam00fdae & 4) != 0) || ((uRam00fdae & 0x2000) != 0)) goto LAB_0a12fe;
    }
LAB_0a1826:
    MDH = (ushort)((uint)iVar4 >> 0x10);
    MDL = (ushort)iVar4;
    *(ushort *)(puVar8 + -0x6300) = CONCAT11(rl_byte,bRam3016b1);
    *(ushort *)(puVar8 + -0x6200) = CONCAT11(uRam00e5b4._1_1_,cRam3016e0);
    *(byte *)((uint3)((ushort)puVar8 >> 1) + 0x302314) =
         *(byte *)((uint3)((ushort)puVar8 >> 1) + 0x302314) & 0x23 |
         (byte)(((PSW & 8) >> 3 ^ 1) << 2) | (byte)((((PSW & 8) >> 3 ^ 1) << 0xb) >> 8) |
         (byte)((((bRam303276 & 0x20) >> 5) << 0xc) >> 8) |
         (byte)((((bRam303276 & 0x40) >> 6) << 0xe) >> 8) |
         (byte)((((uRam00fdae & 0x400) >> 10) << 0xf) >> 8);
    uRam00fd56 = uRam00fd56 & 0xbfff | ((uRam00fdae & 0x1000) >> 0xc) << 0xe;
    uVar14 = uVar10 & 0xffbe | bRam303276 & 1 | ((bRam303276 & 2) >> 1) << 6;
    *(ushort *)(puVar8 + -0x6400) = CONCAT11(bRam00e19e,(char)uVar14);
    uVar23 = (ushort)puVar8 >> 1;
    *(char *)((uint3)uVar23 + 0x302294) = cRam3016da;
    *(byte *)((uint3)uVar23 + 0x302394) = *(byte *)((uint3)uVar23 + 0x302394) & 0x80 | bRam3016c3;
    *(char *)((uint3)((ushort)puVar8 >> 1) + 0x302214) = cRam3016ed;
    if (nmot_rpmclass < bRam014212) {
      PSW = PSW | 0x40;
    }
    else {
      PSW = PSW & 0xffbf;
    }
    uVar23 = ((PSW & 0x40) >> 6) << 2 | ((uVar10 & 8) >> 3) << 1 | (uVar10 & 0x80) >> 7;
    *(char *)((uint3)bRam3016b4 + 0x302414) = (char)uVar23;
    uRam00fdac = uRam00fdac & 0xffef | ((uVar10 & 0x80) >> 7) << 4;
    if (cRam3016ac == '\0') {
      uVar10 = uRam00fdb0 & 0x7fff;
      if (cRam3016ad == '\0') {
        if (((uRam00fdb0 & 0x100) != 0) ||
           (uVar23 = CONCAT11((char)((ushort)puVar8 >> 8),(char)puVar8 + -6) >> 1,
           uRam00fdb0 = uVar10, (*(byte *)((uint3)uVar23 + 0x302314) & 1) != 0)) {
          uVar23 = 0;
          uRam00fdb0 = uVar10;
          if ((*(byte *)((uint3)((ushort)puVar8 >> 1) + 0x302394) & 0x80) == 0) {
            if (cRam3016b6 == '\0') {
              uRam00e5b6 = uVar14;
              uVar23 = func_0x041106(0x4213,uRam301998);
              uVar14 = uRam00e5b6;
            }
            else {
              uVar23 = (ushort)bRam01421b;
            }
            uRam00fdb0 = uRam00fdb0 | 0x8000;
          }
          cRam3016ac = (char)uVar23;
        }
      }
      else {
        uVar18 = uRam00fdb0 & 0x100;
        uRam00fdb0 = uVar10;
        if ((uVar18 != 0) ||
           (uVar23 = CONCAT11((char)((ushort)puVar8 >> 8),(char)puVar8 + -6) >> 1,
           (*(byte *)((uint3)uVar23 + 0x302314) & 1) != 0)) goto LAB_0a1960;
        cRam3016ad = cRam3016ad + -1;
      }
    }
    else {
      cRam3016ac = cRam3016ac + -1;
      if (cRam3016ac == '\0') {
LAB_0a1960:
        cRam3016ad = cRam01444c;
      }
    }
    *(byte *)((uint3)bRam3016b4 + 0x3016ba) = bRam00e19e;
    *(ushort *)((uint3)bRam3016b4 * 2 + 0x302124) = uRam302122;
    uVar10 = (ushort)(byte)(bRam3016b4 + 3);
    if (4 < uVar10) {
      uVar10 = (ushort)(byte)(bRam3016b4 - 2);
    }
    *(undefined1 *)((uint3)uVar10 + 0x3016d1) = uRam3016d0;
    if (((uRam00fdae & 4) == 0) &&
       ((((uRam00fdb0 & 0x80) != 0 || ((uRam00fdb0 & 0x40) != 0)) || ((uRam00fdb0 & 0x100) != 0))))
    {
      uRam00fdae = uRam00fdae | 0x10;
      uRam3016e8 = uRam013ebf;
      uVar10 = uRam016604;
      if ((_flags_idle_state & 0x200) != 0) {
        uVar10 = uRam016602;
      }
      if ((uVar10 <= uRam302b6a) && (uRam016608 < _afterstart_timer)) {
        bRam303276 = bRam303276 | 4;
      }
    }
    else {
      uRam00fdae = uRam00fdae & 0xffef;
    }
    uRam00fdb2 = uRam00fdb2 & 0xfffc | ((uRam00fdae & 0x2000) >> 0xd) << 1 | (uRam00fdae & 4) >> 2 |
                 0x8000;
  }
LAB_0a1a3a:
  bRam00e19d = bVar16;
  __atomic(3);
  DAT_00e316 = (ushort *)*DAT_00e316;
  return uVar23;
code_r0x0a0506:
  bVar16 = (byte)uVar10;
  uVar10 = (ushort)(byte)(bVar16 + 2);
  if (((byte)(bVar16 + 2) < bVar16 || (byte)(bVar16 + 2) < 2) || (bRam00e19c <= (byte)(bVar16 + 2)))
  goto LAB_0a19f6;
  goto LAB_0a04fe;
LAB_0a19f6:
  uRam00fdac = uRam00fdac | 0x11;
  uRam00fdae = uRam00fdae | 0x2004;
  uRam00fdb0 = uRam00fdb0 & 0xfdff;
  uRam00fdb2 = uRam00fdb2 & 0xffdf | 3;
  bRam00e19c = 0;
  bRam00e19d = 0;
  bRam00e19e = 0;
  uRam00e5b4 = 0;
  uRam302122 = 0;
  uRam3016d0 = 0;
  cRam3016b7 = cRam3016b5;
  cRam3016b9 = cRam3016b5;
  uRam00fd58 = uRam00fd58 | 0x10;
  cRam3016b6 = cRam013f4d;
  bVar16 = bRam00e19d;
  goto LAB_0a1a3a;
}


// ================= diag_codeword_expand_init @ 009a52 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC-CONFIG: expands ~40 cal codewords (KAMFZ/CD*/CW* band 0x18000-0x1802D + 0x12600/03/05)
   into RAM enable flags word_3018D6/D8, byte_301220-22, word_FD00/FD02 bits [C]; init path (sole
   caller sub_A082) */

void diag_codeword_expand_init(void)

{
  if ((s_DDDDDDDDDDDDDD_017ff2[0xe] & 1U) == 0) {
    _flags_diag_enable_a = _flags_diag_enable_a & 0xffbf;
  }
  else {
    _flags_diag_enable_a = _flags_diag_enable_a | 0x40;
  }
  if ((s_DDDDDDDDDDDDDD_017ff2[0xf] & 1U) == 0) {
    _flags_diag_enable_b = _flags_diag_enable_b & 0xffef;
  }
  else {
    _flags_diag_enable_b = _flags_diag_enable_b | 0x10;
  }
  if ((s_DDDDDDDDDDDDDD_017ff2[0x10] & 1U) == 0) {
    _flags_diag_enable_b = _flags_diag_enable_b & 0xfffb;
  }
  else {
    _flags_diag_enable_b = _flags_diag_enable_b | 4;
  }
  if ((s_DDDDDDDDDDDDDD_017ff2[0x11] & 1U) == 0) {
    _flags_diag_enable_a = _flags_diag_enable_a & 0xefff;
  }
  else {
    _flags_diag_enable_a = _flags_diag_enable_a | 0x1000;
  }
  if ((bRam018007 & 1) == 0) {
    _flags_diag_enable_b = _flags_diag_enable_b & 0xfbff;
  }
  else {
    _flags_diag_enable_b = _flags_diag_enable_b | 0x400;
  }
  if ((bRam018005 & 1) == 0) {
    _flags_diag_enable_b = _flags_diag_enable_b & 0xfff7;
  }
  else {
    _flags_diag_enable_b = _flags_diag_enable_b | 8;
  }
  if ((bRam01800b & 1) == 0) {
    _flags_diag_enable_a = _flags_diag_enable_a & 0xfff7;
  }
  else {
    _flags_diag_enable_a = _flags_diag_enable_a | 8;
  }
  if ((bRam01800c & 1) == 0) {
    _flags_diag_enable_b = _flags_diag_enable_b & 0xffbf;
  }
  else {
    _flags_diag_enable_b = _flags_diag_enable_b | 0x40;
  }
  if ((bRam01800d & 1) == 0) {
    _flags_diag_enable_a = _flags_diag_enable_a & 0xffdf;
  }
  else {
    _flags_diag_enable_a = _flags_diag_enable_a | 0x20;
  }
  if ((bRam018009 & 1) == 0) {
    _flags_diag_enable_b = _flags_diag_enable_b & 0xbfff;
  }
  else {
    _flags_diag_enable_b = _flags_diag_enable_b | 0x4000;
  }
  if ((bRam01800a & 1) == 0) {
    _flags_diag_enable_b = _flags_diag_enable_b & 0x7fff;
  }
  else {
    _flags_diag_enable_b = _flags_diag_enable_b | 0x8000;
  }
  if ((bRam01800f & 1) == 0) {
    _flags_diag_enable_a = _flags_diag_enable_a & 0xfbff;
  }
  else {
    _flags_diag_enable_a = _flags_diag_enable_a | 0x400;
  }
  if ((bRam018010 & 1) == 0) {
    _flags_diag_enable_b = _flags_diag_enable_b & 0xff7f;
  }
  else {
    _flags_diag_enable_b = _flags_diag_enable_b | 0x80;
  }
  if ((bRam018012 & 1) == 0) {
    _flags_diag_enable_a = _flags_diag_enable_a & 0xfeff;
  }
  else {
    _flags_diag_enable_a = _flags_diag_enable_a | 0x100;
  }
  if ((bRam018015 & 1) == 0) {
    _flags_diag_enable_b = _flags_diag_enable_b & 0xfffe;
  }
  else {
    _flags_diag_enable_b = _flags_diag_enable_b | 1;
  }
  if ((bRam018016 & 1) == 0) {
    _flags_diag_enable_a = _flags_diag_enable_a & 0xfffb;
  }
  else {
    _flags_diag_enable_a = _flags_diag_enable_a | 4;
  }
  if ((bRam018017 & 1) == 0) {
    _flags_diag_enable_a = _flags_diag_enable_a & 0xf7ff;
  }
  else {
    _flags_diag_enable_a = _flags_diag_enable_a | 0x800;
  }
  if ((bRam018018 & 1) == 0) {
    _flags_diag_enable_a = _flags_diag_enable_a & 0xfffe;
  }
  else {
    _flags_diag_enable_a = _flags_diag_enable_a | 1;
  }
  if ((bRam018019 & 1) == 0) {
    _flags_diag_enable_b = _flags_diag_enable_b & 0xf7ff;
  }
  else {
    _flags_diag_enable_b = _flags_diag_enable_b | 0x800;
  }
  if ((bRam01801b & 1) == 0) {
    _flags_diag_enable_b = _flags_diag_enable_b & 0xefff;
  }
  else {
    _flags_diag_enable_b = _flags_diag_enable_b | 0x1000;
  }
  if ((bRam01801a & 1) == 0) {
    _flags_diag_enable_a = _flags_diag_enable_a & 0xffef;
  }
  else {
    _flags_diag_enable_a = _flags_diag_enable_a | 0x10;
  }
  if ((bRam01801c & 1) == 0) {
    _flags_diag_enable_a = _flags_diag_enable_a & 0xfdff;
  }
  else {
    _flags_diag_enable_a = _flags_diag_enable_a | 0x200;
  }
  if ((bRam018020 & 1) == 0) {
    _flags_diag_enable_b = _flags_diag_enable_b & 0xfffd;
  }
  else {
    _flags_diag_enable_b = _flags_diag_enable_b | 2;
  }
  if ((bRam018021 & 1) == 0) {
    _flags_diag_enable_a = _flags_diag_enable_a & 0xff7f;
  }
  else {
    _flags_diag_enable_a = _flags_diag_enable_a | 0x80;
  }
  if ((bRam018022 & 1) == 0) {
    _flags_diag_enable_b = _flags_diag_enable_b & 0xffdf;
  }
  else {
    _flags_diag_enable_b = _flags_diag_enable_b | 0x20;
  }
  if ((bRam018023 & 1) == 0) {
    _flags_diag_enable_a = _flags_diag_enable_a & 0xfffd;
  }
  else {
    _flags_diag_enable_a = _flags_diag_enable_a | 2;
  }
  if ((bRam018006 & 1) == 0) {
    flags_diag_enable_d = flags_diag_enable_d & 0xfe;
  }
  else {
    flags_diag_enable_d = flags_diag_enable_d | 1;
  }
  if ((bRam018013 & 1) == 0) {
    flags_diag_enable_d = flags_diag_enable_d & 0xfd;
  }
  else {
    flags_diag_enable_d = flags_diag_enable_d | 2;
  }
  if ((bRam01801f & 1) == 0) {
    flags_diag_enable_d = flags_diag_enable_d & 0xfb;
  }
  else {
    flags_diag_enable_d = flags_diag_enable_d | 4;
  }
  if ((bRam018014 & 1) == 0) {
    flags_diag_enable_d = flags_diag_enable_d & 0xf7;
  }
  else {
    flags_diag_enable_d = flags_diag_enable_d | 8;
  }
  if ((bRam01801d & 1) == 0) {
    _flags_diag_enable_a = _flags_diag_enable_a & 0xdfff;
  }
  else {
    _flags_diag_enable_a = _flags_diag_enable_a | 0x2000;
  }
  if ((bRam01801d & 2) == 0) {
    _flags_diag_enable_a = _flags_diag_enable_a & 0xbfff;
  }
  else {
    _flags_diag_enable_a = _flags_diag_enable_a | 0x4000;
  }
  if ((bRam01801d & 4) == 0) {
    _flags_diag_enable_a = _flags_diag_enable_a & 0x7fff;
  }
  else {
    _flags_diag_enable_a = _flags_diag_enable_a | 0x8000;
  }
  if ((bRam018011 & 1) == 0) {
    _flags_diag_enable_b = _flags_diag_enable_b & 0xfdff;
  }
  else {
    _flags_diag_enable_b = _flags_diag_enable_b | 0x200;
  }
  if ((bRam018011 & 2) == 0) {
    _flags_diag_enable_b = _flags_diag_enable_b & 0xfeff;
  }
  else {
    _flags_diag_enable_b = _flags_diag_enable_b | 0x100;
  }
  uRam019222 = uRam018027;
  _flags_diag_cfg_a =
       _flags_diag_cfg_a & 0x7400 | ((byte)s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_012591[0x6f] & 1) << 1
       | (bRam01802d & 4) >> 2 | (ushort)bRam018028 << 0xf | (bRam018029 & 1) << 4 |
       ((bRam018029 & 4) >> 2) << 5 | (bRam018026 & 1) << 3 | ((bRam018026 & 2) >> 1) << 2 | 0x5400
       | ((bRam012603 & 2) >> 1) << 8 | ((bRam012603 & 4) >> 2) << 6 | ((bRam012603 & 8) >> 3) << 7
       | ((bRam012603 & 0x10) >> 4) << 9;
  flags_diag_cfg_b =
       flags_diag_cfg_b & 0xe06 | (bRam01802d & 1) << 0xe | ((bRam01802d & 2) >> 1) << 0xf |
       (bRam01802a & 1) << 5 | ((bRam01802a & 2) >> 1) << 3 | ((bRam01802a & 0x10) >> 4) << 6 |
       ((bRam01802a & 0x20) >> 5) << 4 | (bRam01802c & 1) << 0xd | (bRam018028 & 2) >> 1 |
       ((bRam018028 & 4) >> 2) << 0xc | (bRam012605 & 1) << 7 | ((bRam012605 & 2) >> 1) << 8;
  if ((bRam018004 & 1) == 0) {
    flags_diag_enable_c = flags_diag_enable_c & 0xfe;
  }
  else {
    flags_diag_enable_c = flags_diag_enable_c | 1;
  }
  if ((bRam01800e & 1) == 0) {
    flags_diag_enable_c = flags_diag_enable_c & 0xfd;
  }
  else {
    flags_diag_enable_c = flags_diag_enable_c | 2;
  }
  if ((bRam01801e & 1) == 0) {
    flags_diag_enable_c = flags_diag_enable_c & 0xfb;
  }
  else {
    flags_diag_enable_c = flags_diag_enable_c | 4;
  }
  if ((bRam018024 & 1) == 0) {
    flags_diag_enable_c = flags_diag_enable_c & 0xf7;
  }
  else {
    flags_diag_enable_c = flags_diag_enable_c | 8;
  }
  if ((bRam018008 & 1) == 0) {
    flags_diag_enable_c = flags_diag_enable_c & 0xef;
    return;
  }
  flags_diag_enable_c = flags_diag_enable_c | 0x10;
  return;
}


// ================= etc_stop_learn_adapt @ 0c7eea =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* ADAPTATION: motor-servo pot stop-learn state machine (byte_301779 states 0-0xB) [C mechanism / I
   identity=electronic throttle]: learns pot low/high stops word_302CB2/word_303C4C (12-bit clamp) +
   2-point gain/slope test vs 0x16Fxx cals, persists via EEPROM helpers sub_386F2/sub_38ECE, outputs
   linearizer offset word_302CB4 + bound word_302CC4; fail -> code byte_301775 (0x14/0x18-0x1E) +
   defaults 16F1A/16F30/16EFA via sub_C891C */

void etc_stop_learn_adapt(void)

{
  bool bVar1;
  uint uVar2;
  undefined1 uVar3;
  ushort uVar4;
  short sVar5;
  ushort uVar6;
  
  uVar2 = CONCAT22(MDH,MDL);
  if (((uRam00fd6a & 0x4000) == 0) || ((uRam00fd6c & 0x20) != 0)) goto LAB_0c88c6;
  if ((uRam00fd28 & 0x40) == 0) {
    if ((((uRam00fd70 & 0x80) == 0) && ((uRam00fd70 & 0x20) == 0)) &&
       (((uRam00fd6c & 1) == 0 && (((uRam00fd80 & 2) == 0 && ((uRam00fd70 & 0x40) == 0)))))) {
      if (bRam014653 < bRam301655) {
        servo_adapt_errcode = 0x18;
        uRam00fd6c = uRam00fd6c | 0x80;
      }
      else if ((((uRam016f02 < uRam302ca4) || ((DAT_00fd4e & 0x100) != 0)) ||
               ((bRam303353 & 1) == 0)) || ((bRam303353 & 2) == 0)) {
        bRam301778 = bRam301778 | 0x10;
        if (bRam014656 < vfzg_class) {
          servo_adapt_errcode = 0x19;
          uRam00fd6c = uRam00fd6c | 0x80;
        }
        else if (DAT_301258 < bRam014654) {
          if (bRam30177d < bRam30183a) {
            if ((rpmclass_oppoint < bRam014658) || (bRam014657 < rpmclass_oppoint)) {
              servo_adapt_errcode = 0x1c;
              uRam00fd6c = uRam00fd6c | 0x80;
            }
            else if (bRam301626 < bRam014655) {
              servo_adapt_errcode = 0x1e;
              uRam00fd6c = uRam00fd6c | 0x80;
            }
            else {
              uRam00fd6c = uRam00fd6c | 0x10;
            }
          }
          else {
            servo_adapt_errcode = 0x1b;
            uRam00fd6c = uRam00fd6c | 0x80;
          }
        }
        else {
          servo_adapt_errcode = 0x1a;
          uRam00fd6c = uRam00fd6c | 0x80;
        }
      }
      else {
        uRam302ca4 = uRam302ca4 + 1;
      }
    }
    else {
      servo_adapt_errcode = 0x14;
      uRam00fd6c = uRam00fd6c | 0x80;
    }
  }
  else if ((((((uRam00fd6c & 0x8000) == 0) || ((uRam00fd6e & 0x10) == 0)) && ((uRam00fd80 & 2) == 0)
            ) && (((uRam00fd70 & 0x20) == 0 && ((uRam00fd6c & 1) == 0)))) &&
          ((uRam00fd70 & 0x40) == 0)) {
    bRam301778 = bRam301778 | 0x10;
    if (bRam30177d < bRam30183a) {
      uRam00fd6c = uRam00fd6c | 0x10;
    }
    else {
      servo_adapt_errcode = 0x1b;
      uRam00fd6c = uRam00fd6c | 0x80;
    }
  }
  else {
    servo_adapt_errcode = 0x14;
    uRam00fd6c = uRam00fd6c | 0x80;
  }
  if ((uRam00fd6c & 0x80) != 0) {
    bRam301778 = bRam301778 | 0x40;
    func_0x0c891c();
    uVar2 = CONCAT22(MDH,MDL);
    goto LAB_0c88c6;
  }
  if ((uRam00fd6c & 0x10) == 0) {
    _servo_pot_low_learned = uRam303c44;
    _servo_pot_high_learned = uRam303c4a;
    goto LAB_0c88c6;
  }
  if (servo_adapt_state == '\0') {
    uRam00fd6c = uRam00fd6c | 8;
    _servo_pot_low_learned = uRam016f16;
    _servo_pot_high_learned = uRam016f2e;
    uRam302cc8 = 0;
    uRam00fd6a = uRam00fd6a | 0x30;
    servo_adapt_state = '\x01';
    bRam301778 = bRam301778 & 0xf0 | 5;
    uVar2 = CONCAT22(MDH,MDL);
    goto LAB_0c88c6;
  }
  if (servo_adapt_state == '\x01') {
    bVar1 = _servo_pot_low_learned < uRam016f0e;
    _servo_pot_low_learned = _servo_pot_low_learned - uRam016f0e;
    if (bVar1) {
      _servo_pot_low_learned = 0;
    }
    uVar6 = uRam016f0e + _servo_pot_high_learned;
    bVar1 = uRam016f0e + _servo_pot_high_learned < _servo_pot_high_learned;
    _servo_pot_high_learned = uRam016f0e + _servo_pot_high_learned;
    if (uVar6 < uRam016f0e || bVar1) {
      _servo_pot_high_learned = 0xffff;
    }
    if (0xfff < _servo_pot_low_learned) {
      _servo_pot_low_learned = 0xfff;
    }
    if (0xfff < _servo_pot_high_learned) {
      _servo_pot_high_learned = 0xfff;
    }
    uVar2 = CONCAT22(MDH,MDL);
    if (((uRam00fd68 & 8) == 0) && (uVar2 = CONCAT22(MDH,MDL), uRam016f0a < _servo_pwm_duty)) {
      if (bRam30177a == 0) {
        uRam302cb0 = _adc_ch1_raw;
        uRam302cc2 = _adc_ch2_raw;
        bRam301778 = bRam301778 & 0xf0 | 6;
      }
      if (bRam30177a < bRam01464b) {
        uRam302cb0 = uRam302cb0 + _adc_ch1_raw >> 1;
        uRam302cc2 = uRam302cc2 + _adc_ch2_raw >> 1;
        bRam30177a = bRam30177a + 1;
        uVar2 = CONCAT22(MDH,MDL);
      }
      else {
        bRam30177a = 0;
        _servo_pot_low_learned = uRam302cb0;
        _servo_pot_high_learned = uRam302cc2;
        if ((uRam302cb0 < uRam016f18) || (uRam016f2c < uRam302cc2)) {
          uRam00fd6c = uRam00fd6c | 0x800;
          bRam301778 = bRam301778 | 0x20;
          func_0x0c891c();
          uVar2 = CONCAT22(MDH,MDL);
        }
        else {
          servo_adapt_state = '\x02';
          uVar2 = CONCAT22(MDH,MDL);
        }
      }
    }
    goto LAB_0c88c6;
  }
  if (servo_adapt_state == '\x02') {
    uVar6 = uRam016f34 + _servo_pot_low_learned;
    bVar1 = uRam016f34 + _servo_pot_low_learned < _servo_pot_low_learned;
    _servo_pot_low_learned = uRam016f34 + _servo_pot_low_learned;
    if (uVar6 < uRam016f34 || bVar1) {
      _servo_pot_low_learned = 0xffff;
    }
    bVar1 = _servo_pot_high_learned < uRam016f34;
    _servo_pot_high_learned = _servo_pot_high_learned - uRam016f34;
    if (bVar1) {
      _servo_pot_high_learned = 0;
    }
    uVar6 = uRam016f34 + uRam016f16;
    if (uRam016f34 + uRam016f16 < uRam016f34 || uRam016f34 + uRam016f16 < uRam016f16) {
      uVar6 = 0xffff;
    }
    if (_servo_pot_low_learned <= uVar6) {
      uVar6 = uRam016f2e - uRam016f34;
      if (uRam016f2e < uRam016f34) {
        uVar6 = 0;
      }
      if (uVar6 <= _servo_pot_high_learned) {
        uRam302cb0 = _adc_ch1_raw;
        servo_adapt_state = '\x03';
        uVar2 = CONCAT22(MDH,MDL);
        goto LAB_0c88c6;
      }
    }
    uRam00fd6c = uRam00fd6c | 0x800;
    bRam301778 = bRam301778 | 0x20;
    func_0x0c891c();
    uVar2 = CONCAT22(MDH,MDL);
    goto LAB_0c88c6;
  }
  if (servo_adapt_state == '\x03') {
    if (((uRam00fd68 & 8) == 0) && (uRam016f0c < _servo_pwm_duty)) {
      bRam30177a = 0;
      uVar6 = uRam016f08 + uRam302cc8;
      bVar1 = uRam016f08 + uRam302cc8 < uRam302cc8;
      uRam302cc8 = uRam016f08 + uRam302cc8;
      uVar2 = CONCAT22(MDH,MDL);
      if (uVar6 < uRam016f08 || bVar1) {
        uRam302cc8 = 0xffff;
      }
    }
    else if (bRam30177a < bRam01464c) {
      bRam30177a = bRam30177a + 1;
      uVar2 = CONCAT22(MDH,MDL);
    }
    else {
      bRam30177a = 0;
      if (uRam302cb0 < _adc_ch1_raw) {
        uVar6 = uRam016f32 + _servo_pot_low_learned;
        if (uRam016f32 + _servo_pot_low_learned < uRam016f32 ||
            uRam016f32 + _servo_pot_low_learned < _servo_pot_low_learned) {
          uVar6 = 0xffff;
        }
        if (_adc_ch1_raw <= uVar6) {
          servo_adapt_state = '\x04';
          uVar2 = CONCAT22(MDH,MDL);
          goto LAB_0c88c6;
        }
      }
      uRam00fd6c = uRam00fd6c | 0x800;
      bRam301778 = bRam301778 | 0x20;
      func_0x0c891c();
      uVar2 = CONCAT22(MDH,MDL);
    }
    goto LAB_0c88c6;
  }
  if (servo_adapt_state == '\x04') {
    uVar6 = _servo_pot_low_learned - uRam303c44;
    if (_servo_pot_low_learned < uRam303c44) {
      if ((short)uVar6 >= 0) {
        uVar6 = 0x8000;
      }
    }
    else if ((short)uVar6 < 0) {
      uVar6 = 0x7fff;
    }
    if (((short)uVar6 < 0) && (bVar1 = uVar6 == 0x8000, uVar6 = -uVar6, bVar1)) {
      uVar6 = 0x7fff;
    }
    if ((((uRam016f10 < uVar6) || ((DAT_00fd4e & 0x100) != 0)) || ((bRam303353 & 2) == 0)) ||
       ((uRam00fd6c & 0x40) != 0)) {
      uRam303c44 = _servo_pot_low_learned;
      uRam303c4a = _servo_pot_high_learned;
    }
    servo_adapt_state = '\x05';
    bRam301778 = bRam301778 & 0xf0 | 2;
    bRam303353 = bRam303353 | 1;
    uVar2 = CONCAT22(MDH,MDL);
    goto LAB_0c88c6;
  }
  if (servo_adapt_state == '\x05') {
    uVar6 = uRam302cac - _servo_pot_low_learned;
    if (uRam302cac < _servo_pot_low_learned) {
      uVar6 = 0;
    }
    uVar2 = (uint)uVar6 * (uint)_servo_pot_lin_gain;
    MDL = (ushort)uVar2;
    MDH = (ushort)(uVar2 >> 0x10);
    MDC = MDC | 0x10;
    uRam302cca = MDL >> 0xb | MDH << 5;
    if ((uRam302cca < uRam016f44) || (uRam016f42 < uRam302cca)) {
      uRam302cca = uRam016f44;
      uRam00fd6c = uRam00fd6c | 0x100;
      bRam301778 = bRam301778 | 0x20;
      func_0x0c898a();
      uVar2 = CONCAT22(MDH,MDL);
    }
    else {
      uVar6 = uRam302cac - uRam303c40;
      if (uRam302cac < uRam303c40) {
        if ((short)uVar6 >= 0) {
          uVar6 = 0x8000;
        }
      }
      else if ((short)uVar6 < 0) {
        uVar6 = 0x7fff;
      }
      if (((short)uVar6 < 0) && (bVar1 = uVar6 == 0x8000, uVar6 = -uVar6, bVar1)) {
        uVar6 = 0x7fff;
      }
      uVar3 = (undefined1)((MDH << 5) >> 8);
      if ((((uRam016f10 < uVar6) || ((DAT_00fd4e & 0x100) != 0)) || ((bRam303353 & 2) == 0)) ||
         ((uRam00fd6c & 0x40) != 0)) {
        uRam303c40 = uRam302cac;
        uRam303c42 = uRam302cae;
        uRam303c4e = uRam302cca;
        uRam304d49 = uVar3;
      }
      else {
        uVar6 = uRam302cca - uRam303c4e;
        if (uRam302cca < uRam303c4e) {
          if ((short)uVar6 >= 0) {
            uVar6 = 0x8000;
          }
        }
        else if ((short)uVar6 < 0) {
          uVar6 = 0x7fff;
        }
        if (((short)uVar6 < 0) && (bVar1 = uVar6 == 0x8000, uVar6 = -uVar6, bVar1)) {
          uVar6 = 0x7fff;
        }
        if (uRam016f48 < uVar6) {
          uRam303c40 = uRam302cac;
          uRam303c42 = uRam302cae;
          uRam303c4e = uRam302cca;
          uRam304d49 = uVar3;
        }
      }
      servo_adapt_state = '\x06';
      uRam00fd6c = uRam00fd6c & 0xfdff;
    }
    goto LAB_0c88c6;
  }
  if (servo_adapt_state == '\x06') {
    uRam302cce = 0;
    uVar6 = (ushort)bRam30177f * 0x10 - _servo_pot_low_learned;
    if ((ushort)bRam30177f * 0x10 < _servo_pot_low_learned) {
      uVar6 = 0;
    }
    uVar4 = uVar6 - uRam016f50;
    if (uVar6 < uRam016f50) {
      uVar4 = 0;
    }
    uVar2 = (uint)uVar4 * (uint)(_servo_pot_lin_gain >> 0xb);
    uRam302cc8 = (ushort)uVar2;
    MDC = MDC | 0x10;
    if (0xffff < uVar2) {
      uRam302cc8 = 0xffff;
    }
    bRam30177f = 0;
    servo_adapt_state = '\a';
    uRam302ccc = uRam302cc8;
    goto LAB_0c88c6;
  }
  if (servo_adapt_state == '\a') {
    if (bRam30177a < bRam01464d) {
      bRam30177a = bRam30177a + 1;
      uVar2 = CONCAT22(MDH,MDL);
    }
    else {
      bRam30177a = 0;
      uRam302cb6 = _adc_ch1_raw >> 2;
      uRam302cbc = _adc_ch3_raw;
      if (_adc_ch3_raw < uRam016f24) {
        bRam301778 = bRam301778 | 0x20;
        func_0x0c8970();
        uVar2 = CONCAT22(MDH,MDL);
      }
      else {
        servo_adapt_state = '\b';
        uVar2 = CONCAT22(MDH,MDL);
      }
    }
    goto LAB_0c88c6;
  }
  if (servo_adapt_state == '\b') {
    uRam302cc8 = uRam302cce;
    servo_adapt_state = '\t';
    uVar2 = CONCAT22(MDH,MDL);
    goto LAB_0c88c6;
  }
  if (servo_adapt_state != '\t') {
    if (servo_adapt_state == '\n') {
      if (bRam300bf0 == 0x40) {
        bRam300bf0 = 0;
        cRam300bf6 = cRam300bf6 + '\x01';
      }
      else if (0x7f < bRam300bf0) {
        uRam302cc8 = 0;
        uRam00fd6a = uRam00fd6a & 0xffcf;
        func_0x0c7d7c();
        uRam00fd6c = uRam00fd6c & 0xfff7 | 0x20;
        if (cRam014642 == '\0') {
          uRam00fd28 = uRam00fd28 & 0xffbf;
        }
      }
      uVar2 = CONCAT22(MDH,MDL);
      if (bRam300bf0 == 0) {
        if (cRam300bf6 == '\0') {
          if ((bRam303353 & 1) == 0) {
            uRam300bf8 = uRam300bf8 & 0xfffe;
          }
          else {
            uRam300bf8 = uRam300bf8 | 1;
          }
          if ((bRam303353 & 4) == 0) {
            uRam300bf8 = uRam300bf8 & 0xfffd;
          }
          else {
            uRam300bf8 = uRam300bf8 | 2;
          }
          if ((bRam303353 & 2) == 0) {
            uRam300bf8 = uRam300bf8 & 0xfffb;
          }
          else {
            uRam300bf8 = uRam300bf8 | 4;
          }
          func_0x0386f2(uRam300bf8,0xe,0xc);
          func_0x0386f2(uRam303c40,0xe,2);
          func_0x0386f2(uRam303c44,0xe,4);
          func_0x0386f2(uRam303c46,0xe,6);
          func_0x0386f2(uRam303c48,0xe,8);
          func_0x0386f2(uRam303c4e,0xe,10);
          func_0x0386f2(uRam303c4a,0xf,4);
          func_0x0386f2(uRam303c42,0xf,2);
          uRam300bef = 5;
          uRam300bf2 = 0xb47c;
          uRam300bec = 0xe;
          uRam300bed = 0;
          uRam300bee = 0xe;
          sVar5 = func_0x038ece(0x8bec);
          uVar2 = CONCAT22(MDH,MDL);
          if (sVar5 == 0) {
            uRam302cc8 = 0;
            uRam00fd6a = uRam00fd6a & 0xffcf;
            func_0x0c7d7c();
            uRam00fd6c = uRam00fd6c & 0xfff7 | 0x20;
            uVar2 = CONCAT22(MDH,MDL);
            if (cRam014642 == '\0') {
              uRam00fd28 = uRam00fd28 & 0xffbf;
              uVar2 = CONCAT22(MDH,MDL);
            }
          }
        }
        else if (cRam300bf6 == '\x01') {
          uRam300bf2 = 0xb48c;
          uRam300bec = 0xf;
          uRam300bed = 0;
          uRam300bee = 0xe;
          sVar5 = func_0x038ece(0x8bec);
          uVar2 = CONCAT22(MDH,MDL);
          if (sVar5 == 0) {
            bRam300bf0 = 0;
            cRam300bf6 = '\x03';
            uVar2 = CONCAT22(MDH,MDL);
          }
        }
        else if (cRam300bf6 == '\x02') {
          servo_adapt_state = '\v';
          uVar2 = CONCAT22(MDH,MDL);
        }
        else if (cRam300bf6 == '\x03') {
          sVar5 = func_0x038ece(0x8bec);
          uVar2 = CONCAT22(MDH,MDL);
          if (sVar5 == 0) {
            uRam302cc8 = 0;
            uRam00fd6a = uRam00fd6a & 0xffcf;
            func_0x0c7d7c();
            uRam00fd6c = uRam00fd6c & 0xfff7 | 0x20;
            uVar2 = CONCAT22(MDH,MDL);
            if (cRam014642 == '\0') {
              uRam00fd28 = uRam00fd28 & 0xffbf;
              uVar2 = CONCAT22(MDH,MDL);
            }
          }
        }
        else {
          servo_adapt_state = '\v';
          uVar2 = CONCAT22(MDH,MDL);
        }
      }
    }
    else {
      uVar2 = CONCAT22(MDH,MDL);
      if (servo_adapt_state == '\v') {
        uRam302cc8 = 0;
        uRam00fd6a = uRam00fd6a & 0xffcf;
        func_0x0c7d7c();
        uRam00fd6c = uRam00fd6c & 0xfff7 | 0x20;
        bRam301778 = bRam301778 | 0x80;
        uVar2 = CONCAT22(MDH,MDL);
        if (cRam014642 == '\0') {
          uRam00fd28 = uRam00fd28 & 0xffbf;
          uVar2 = CONCAT22(MDH,MDL);
        }
      }
    }
    goto LAB_0c88c6;
  }
  if (bRam30177a < bRam01464e) {
    bRam30177a = bRam30177a + 1;
    uVar2 = CONCAT22(MDH,MDL);
    goto LAB_0c88c6;
  }
  bRam30177a = 0;
  uRam302cb8 = _adc_ch1_raw >> 2;
  uRam302cbe = _adc_ch3_raw;
  if (uRam016f26 < _adc_ch3_raw) {
    bRam301778 = bRam301778 | 0x20;
    func_0x0c8970();
    uVar2 = CONCAT22(MDH,MDL);
    goto LAB_0c88c6;
  }
  sVar5 = uRam302cb8 - uRam302cb6;
  if (uRam302cb8 < uRam302cb6) {
    if (sVar5 >= 0) {
      sVar5 = -0x8000;
    }
  }
  else if (sVar5 < 0) {
    sVar5 = 0x7fff;
  }
  if (sVar5 == 0) {
    sVar5 = 0x7fff;
    uRam302cc0 = 0x7fff;
  }
  else {
    func_0x0e4058();
    sVar5 = func_0x0e4078();
    uRam302cc0 = func_0x0e4078();
  }
  uVar6 = MDL;
  if ((short)uRam302cbc < 0) {
    uVar4 = uRam302cbc ^ 0x8000;
    if ((short)uVar4 < 0 != sVar5 < 0 && (short)(uVar4 - sVar5) < 0 != (short)uVar4 < 0)
    goto LAB_0c85a8;
    uRam302cba = uVar4 - sVar5 ^ 0x8000;
    if ((short)uRam302cba < 0) {
      uRam302cba = 0x7fff;
    }
  }
  else {
    uRam302cba = uRam302cbc - sVar5;
    if ((short)uRam302cbc < 0 != sVar5 < 0 &&
        (short)(uRam302cbc - sVar5) < 0 != (short)uRam302cbc < 0) {
LAB_0c85a8:
      uRam302cba = 0x8000;
    }
  }
  if (((short)(uRam302cba - sRam016f22) < 0 ==
       ((short)uRam302cba < 0 != sRam016f22 < 0 &&
       (short)(uRam302cba - sRam016f22) < 0 != (short)uRam302cba < 0)) &&
     (uRam302cba == uRam016f20 ||
      (short)(uRam302cba - uRam016f20) < 0 !=
      ((short)uRam302cba < 0 != (short)uRam016f20 < 0 &&
      (short)(uRam302cba - uRam016f20) < 0 != (short)uRam302cba < 0))) {
    if ((uRam302cc0 < uRam016f2a) || (uRam016f28 < uRam302cc0)) {
      bRam301778 = bRam301778 | 0x20;
      func_0x0c8970();
      uVar2 = CONCAT22(MDH,MDL);
    }
    else {
      uRam027e0e = uRam026a76;
      MDL = MDL / uRam302cc0;
      MDH = uVar6 % uRam302cc0;
      uVar2 = CONCAT22(MDH,MDL);
      MDC = MDC | 0x10;
      if (uRam302cc0 == 0) {
        MDL = 0xffff;
      }
      bRam30177f = (char)MDL - bRam01465a;
      if (MDL < bRam01465a) {
        bRam30177f = 0;
      }
      uRam303c48 = uRam302cc0;
      bRam300bf0 = 0;
      cRam300bf6 = '\0';
      servo_adapt_state = '\n';
      bRam303353 = bRam303353 | 2;
      uRam303c46 = uRam302cba;
    }
  }
  else {
    bRam301778 = bRam301778 | 0x20;
    func_0x0c8970();
    uVar2 = CONCAT22(MDH,MDL);
  }
LAB_0c88c6:
  MDH = (ushort)(uVar2 >> 0x10);
  MDL = (ushort)uVar2;
  _servo_pot_lin_offset = _servo_pot_low_learned + sRam302cc6;
  if (0xfff < _servo_pot_lin_offset) {
    _servo_pot_lin_offset = 0xfff;
  }
  _servo_pot_high_bound = _servo_pot_high_learned - sRam302cc6;
  if (0xfff < _servo_pot_high_bound) {
    _servo_pot_high_bound = 0xfff;
  }
  uRam30177e = (char)(_servo_pot_lin_offset >> 4);
  uRam301780 = (char)(_servo_pot_high_bound >> 4);
  return;
}


// ================= can_rx_signal_unpack @ 05637c =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* COMMS: RX signal-unpack task [C]: polls (flag-ptr,mask) pairs in cal 0x11A32-0x11AE8, extracts
   signals via descriptor readers sub_E3A86/sub_E3ACE (word signals get -0x200 offset) into
   byte_301427-48 / word_302580-25AA mirrors, clears flags, publishes word_30256A/6C/6E +
   word_FD26.11/.12/.14; calls two cal-held far code ptrs 0x11B42/0x11B92 via push-rets trampoline
   sub_8E52 */

void can_rx_signal_unpack(void)

{
  byte bVar1;
  char cVar2;
  
  if ((uRam30256c & 0x80) != 0) {
    return;
  }
  if ((uRam303aa4 & 1) != 0) {
    return;
  }
  func_0x0e3650();
  if ((((uRam30256c & 0x200) == 0) && (cVar2 = FUN_008e52(0x1b08), cVar2 != '\0')) &&
     (cVar2 = FUN_008e52(7000), cVar2 != '\0')) {
    uRam30256c = uRam30256c | 0x200;
  }
  if ((_flags_diag_cfg_a & 0x10) != 0) {
    cVar2 = func_0x0e3a86(0x3e6);
    if (cVar2 == '\0') {
      uRam30256a = uRam30256a & 0xefff;
    }
    else {
      uRam30256a = uRam30256a | 0x1000;
    }
    bVar1 = *(byte *)((uint3)uRam011ada + 0x10000) & bRam011adc;
    if (bVar1 == 0) {
      uRam30256e = uRam30256e & 0xfeff;
    }
    else {
      sRam302582 = func_0x0e3ace(0x5ec,bVar1);
      sRam302582 = sRam302582 + -0x200;
      uRam30256e = uRam30256e | 0x100;
      *(byte *)((uint3)uRam011ada + 0x10000) = *(byte *)((uint3)uRam011ada + 0x10000) & ~bRam011adc;
    }
    bVar1 = *(byte *)((uint3)uRam011ae0 + 0x10000) & bRam011ae2;
    if (bVar1 == 0) {
      uRam30256e = uRam30256e & 0xfdff;
    }
    else {
      sRam302580 = func_0x0e3ace(0x5fa,bVar1);
      sRam302580 = sRam302580 + -0x200;
      uRam30256e = uRam30256e | 0x200;
      *(byte *)((uint3)uRam011ae0 + 0x10000) = *(byte *)((uint3)uRam011ae0 + 0x10000) & ~bRam011ae2;
    }
    if ((*(byte *)((uint3)uRam011ace + 0x10000) & bRam011ad0) == 0) {
      uRam30256e = uRam30256e & 0xfffb;
    }
    else {
      uRam30256e = uRam30256e | 4;
      cVar2 = func_0x0e3a86(0x4d4);
      if (cVar2 == '\0') {
        uRam30256e = uRam30256e & 0xfffd;
      }
      else {
        uRam30256e = uRam30256e | 2;
      }
      *(byte *)((uint3)uRam011ace + 0x10000) = *(byte *)((uint3)uRam011ace + 0x10000) & ~bRam011ad0;
    }
    if ((*(byte *)((uint3)uRam011ab6 + 0x10000) & bRam011ab8) == 0) {
      uRam30256e = uRam30256e & 0xfff7;
    }
    else {
      uRam30256e = uRam30256e | 8;
      cRam30142a = func_0x0e3a86(0x3bc);
      *(byte *)((uint3)uRam011ab6 + 0x10000) = *(byte *)((uint3)uRam011ab6 + 0x10000) & ~bRam011ab8;
    }
    bVar1 = *(byte *)((uint3)uRam011ae6 + 0x10000) & bRam011ae8;
    if (bVar1 != 0) {
      sRam302584 = func_0x0e3ace(0x608,bVar1);
      sRam302584 = sRam302584 + -0x200;
      *(byte *)((uint3)uRam011ae6 + 0x10000) = *(byte *)((uint3)uRam011ae6 + 0x10000) & ~bRam011ae8;
    }
  }
  if ((*(byte *)((uint3)uRam011a4a + 0x10000) & bRam011a4c) == 0) {
    uRam30256e = uRam30256e & 0x7fff;
  }
  else {
    uRam30256e = uRam30256e | 0x8000;
    *(byte *)((uint3)uRam011a4a + 0x10000) = *(byte *)((uint3)uRam011a4a + 0x10000) & ~bRam011a4c;
    uRam3025aa = func_0x0e3ace(0x624);
    uRam301438 = func_0x0e3a86(0x632);
  }
  if (((bRam301447 & 0x80) == 0) && ((bRam300259 & 4) == 0)) {
    cVar2 = func_0x0e3a86(0x2a4);
    if (cVar2 == '\0') {
      uRam30256a = uRam30256a & 0xfffd;
    }
    else {
      uRam30256a = uRam30256a | 2;
    }
    cVar2 = func_0x0e3a86(0x5b4);
    if (cVar2 == '\0') {
      uRam30256c = uRam30256c & 0xfffb;
    }
    else {
      uRam30256c = uRam30256c | 4;
    }
    cVar2 = func_0x0e3a86(0x2c0);
    if (cVar2 == '\0') goto LAB_0565f2;
    uRam30256a = uRam30256a | 0x400;
  }
  else {
    bRam300259 = bRam300259 | 4;
    uRam30256a = uRam30256a & 0xfffd;
    uRam30256c = uRam30256c & 0xfffb;
LAB_0565f2:
    uRam30256a = uRam30256a & 0xfbff;
  }
  cVar2 = func_0x0e3a86(0x4f0);
  if (cVar2 == '\0') {
    uRam30256c = uRam30256c & 0xfffd;
  }
  else {
    uRam30256c = uRam30256c | 2;
  }
  if ((bRam013800 & 1) == 0) {
    uRam00fd26 = uRam00fd26 & 0xefff;
  }
  else {
    if ((((uRam30256a & 2) == 0) && ((uRam30256c & 2) == 0)) &&
       (((uRam30256c & 4) == 0 && ((uRam30256a & 0x400) == 0)))) {
      PSW = PSW & 0xffbf;
    }
    else {
      PSW = PSW | 0x40;
    }
    uRam00fd26 = uRam00fd26 & 0xefff | ((PSW & 0x40) >> 6) << 0xc;
  }
  sRam302594 = func_0x0e3ace(0x4fe);
  sRam302594 = sRam302594 + -0x200;
  uRam30137a = func_0x0e3a86(0x472);
  if ((*(byte *)((uint3)uRam011a32 + 0x10000) & bRam011a34) == 0) {
    uRam30256c = uRam30256c & 0xefff;
  }
  else {
    uRam30256c = uRam30256c | 0x1000;
    uRam301437 = func_0x0e3a86(0x2dc);
    bRam30137b = func_0x0e3a86(0x2ce);
    if (bRam30137b < 0xfa) {
      MDL = ((ushort)bRam30137b << 8) / 0xfa;
      MDH = ((ushort)bRam30137b << 8) % 0xfa;
      MDC = MDC | 0x10;
      uRam301443 = (undefined1)MDL;
    }
    else {
      uRam301443 = 0xff;
    }
    *(byte *)((uint3)uRam011a32 + 0x10000) = *(byte *)((uint3)uRam011a32 + 0x10000) & ~bRam011a34;
  }
  if ((bRam301448 & 0x20) == 0) {
    if ((*(byte *)((uint3)uRam011a86 + 0x10000) & bRam011a88) != 0) {
      uRam30256a = uRam30256a | 0x10;
      cVar2 = func_0x0e3a86(0x456);
      if (cVar2 == '\0') {
        uRam30256a = uRam30256a & 0xfff7;
      }
      else {
        uRam30256a = uRam30256a | 8;
      }
      *(byte *)((uint3)uRam011a86 + 0x10000) = *(byte *)((uint3)uRam011a86 + 0x10000) & ~bRam011a88;
      goto LAB_05673a;
    }
  }
  else {
    uRam30256a = uRam30256a & 0xfff7;
  }
  uRam30256a = uRam30256a & 0xffef;
LAB_05673a:
  bVar1 = *(byte *)((uint3)uRam011a62 + 0x10000) & bRam011a64;
  if (bVar1 != 0) {
    uRam302598 = func_0x0e3ace(0x34c,bVar1);
    *(byte *)((uint3)uRam011a62 + 0x10000) = *(byte *)((uint3)uRam011a62 + 0x10000) & ~bRam011a64;
  }
  if ((*(byte *)((uint3)uRam011a92 + 0x10000) & bRam011a94) == 0) {
    uRam30256e = uRam30256e & 0xffbf;
  }
  else {
    uRam30256e = uRam30256e | 0x40;
    uRam30142d = func_0x0e3a86(0x4b8);
    uRam301431 = func_0x0e3a86(0x4c6);
    *(byte *)((uint3)uRam011a92 + 0x10000) = *(byte *)((uint3)uRam011a92 + 0x10000) & ~bRam011a94;
  }
  if ((*(byte *)((uint3)uRam011a7a + 0x10000) & bRam011a7c) == 0) {
    uRam30256e = uRam30256e & 0xf7ff;
  }
  else {
    uRam30256e = uRam30256e | 0x800;
    *(byte *)((uint3)uRam011a7a + 0x10000) = *(byte *)((uint3)uRam011a7a + 0x10000) & ~bRam011a7c;
    if ((bRam301448 & 0x80) == 0) {
      uRam30142e = func_0x0e3a86(0x42c);
    }
    uRam301432 = func_0x0e3a86(0x43a);
  }
  uRam302592 = func_0x0e3ace(0x536);
  cVar2 = func_0x0e3a86(0x57c);
  if (cVar2 == '\0') {
    uRam30256c = uRam30256c & 0xbfff;
  }
  else {
    uRam30256c = uRam30256c | 0x4000;
  }
  uRam302590 = func_0x0e3ace(0x552);
  cVar2 = func_0x0e3a86(0x560);
  if (cVar2 == '\0') {
    uRam30256c = uRam30256c & 0x7fff;
  }
  else {
    uRam30256c = uRam30256c | 0x8000;
  }
  uRam30143c = func_0x0e3a86(0x58a);
  uRam30143b = func_0x0e3a86(0x544);
  uRam30143a = func_0x0e3a86(0x56e);
  uRam30137d = func_0x0e3a86(0x330);
  uRam30142f = func_0x0e3a86(0x33e);
  if ((*(byte *)((uint3)uRam011aa4 + 0x10000) & bRam011aa6) == 0) {
    uRam30256e = uRam30256e & 0xfffe;
  }
  else {
    uRam30256e = uRam30256e | 1;
    cRam30137c = func_0x0e3a86(0x306);
    *(byte *)((uint3)uRam011aa4 + 0x10000) = *(byte *)((uint3)uRam011aa4 + 0x10000) & ~bRam011aa6;
  }
  if ((bRam013801 & 1) == 0) {
    uRam00fd26 = uRam00fd26 & 0xf7ff;
  }
  else if ((_flags_diag_cfg_a & 0x10) == 0) {
    if (cRam30137c == '\x02') {
      PSW = PSW | 0x40;
    }
    else {
      PSW = PSW & 0xffbf;
    }
    uRam00fd26 = uRam00fd26 & 0xf7ff | ((PSW & 0x40) >> 6) << 0xb;
  }
  else {
    if ((cRam30142a == '\x02') || (((uRam30256e & 2) != 0 && ((bRam013801 & 2) != 0)))) {
      PSW = PSW | 0x40;
    }
    else {
      PSW = PSW & 0xffbf;
    }
    uRam00fd26 = uRam00fd26 & 0xf7ff | ((PSW & 0x40) >> 6) << 0xb;
  }
  if ((bRam300259 & 1) == 0) {
    cVar2 = func_0x0e3a86(0x35a);
    if (cVar2 == '\0') {
      uRam30256c = uRam30256c & 0xfff7;
    }
    else {
      uRam30256c = uRam30256c | 8;
    }
  }
  else {
    bVar1 = *(byte *)((uint3)uRam011a56 + 0x10000) & bRam011a58;
    if (bVar1 == 0) {
      uRam00fd26 = uRam00fd26 & 0xbfff;
    }
    else {
      uRam00fd26 = uRam00fd26 | 0x4000;
      *(byte *)((uint3)uRam011a56 + 0x10000) = *(byte *)((uint3)uRam011a56 + 0x10000) & ~bRam011a58;
    }
    uRam301429 = func_0x0e3a86(0x2ea,bVar1);
    uRam301428 = func_0x0e3a86(0x2f8);
    uRam301427 = func_0x0e3a86(0x314);
  }
  can_rx_msg_handler_bank(uRam300250);
  return;
}


// ================= diag_monitor_enable_table_init @ 0beedc =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC-CONFIG: builds per-monitor enable table word_30BE38+8k (page 0xC2) from the codeword
   flags of diag_codeword_expand_init (word_3018D6/D8, byte_301220) [C]; walks per-monitor cal
   tables 0x1B8E3 (1 B/monitor) + 0x1B8F1 (3 B/monitor) */

void diag_monitor_enable_table_init(void)

{
  bool bVar1;
  bool bVar2;
  
  uRam30be38 = (ushort)((flags_diag_enable_c & 1) != 0);
  uRam30be40 = (ushort)((bRam019220 & 4) != 0);
  uRam30be80 = (ushort)((uRam0198d8 & 0x4000) != 0);
  bVar1 = (uRam0198d6 & 1) != 0;
  uRam30be48 = (ushort)bVar1;
  bVar2 = (_flags_diag_enable_b & 1) != 0;
  uRam30be50 = (ushort)bVar1;
  if (bVar1) {
    uRam30be58 = 1;
    uRam30be60 = 1;
    if (bVar2) {
      uRam30be68 = 1;
      goto LAB_0bf042;
    }
  }
  else {
    uRam30be58 = 0;
    uRam30be60 = 0;
  }
  uRam30be68 = 0;
LAB_0bf042:
  if ((bVar1) && (bVar2)) {
    uRam30be70 = 1;
  }
  else {
    uRam30be70 = 0;
  }
  if ((bVar1) && (bVar2)) {
    uRam30be78 = 1;
  }
  else {
    uRam30be78 = 0;
  }
  uRam30be88 = (ushort)((uRam0198d6 & 8) != 0);
  return;
}


// ================= hfm_adc_latch @ 03ff30 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* latch raw HFM ADC channel: loc_F2DE = loc_F2DC & 0x3FF (10-bit; peer of sub_3FF58 pot latch) [C]
    */

void hfm_adc_latch(void)

{
  _hfm_raw = uRam00f2dc & 0x3ff;
  return;
}


// ================= hfm_sample_linearize @ 07633c =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* per-sample HFM linearization: MAF curve 0x160E8 (128-pt word, /8 interp; overflow substitute
   word_161E8) on loc_F2DE -> loc_F382, accumulates sum loc_F37A:F37C + count loc_F37E [C] */

void hfm_sample_linearize(void)

{
  bool bVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  
  iVar4 = CONCAT22(MDH,MDL);
  _ml_hfm_inst = uRam0161e8;
  if (_hfm_raw >> 3 < 0x80) {
    uVar3 = (_hfm_raw >> 3) << 1;
    sVar2 = *(short *)((uint3)uVar3 + 0x160e8);
    iVar4 = (int)(*(short *)((uint3)uVar3 + 0x160ea) - sVar2) * (int)(short)(_hfm_raw & 7);
    MDC = MDC | 0x10;
    _ml_hfm_inst = sVar2 + ((ushort)iVar4 >> 3 | (short)((uint)iVar4 >> 0x10) << 0xd);
  }
  MDH = (undefined2)((uint)iVar4 >> 0x10);
  MDL = (undefined2)iVar4;
  bVar1 = _ml_hfm_accum + _ml_hfm_inst < _ml_hfm_accum;
  uVar3 = _ml_hfm_accum + _ml_hfm_inst;
  _ml_hfm_accum = _ml_hfm_accum + _ml_hfm_inst;
  sRam00f37c = sRam00f37c + ((short)_ml_hfm_inst >> 0xf) + (ushort)(bVar1 || uVar3 < _ml_hfm_inst);
  sRam00f37e = sRam00f37e + 1;
  return;
}


// ================= hfm_average_kfkhfm @ 07628c =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* drains HFM accumulator atomically -> mean air mass loc_F384/loc_F386 (divl); x KFKHFM factor
   word_3028A8 -> loc_F380, >=0 clamp -> word_F388, MLMIN 0x160E6 floor -> word_3028AA [C] */

void hfm_average_kfkhfm(void)

{
  uint uVar1;
  int iVar2;
  short sVar3;
  ushort uVar4;
  
  sVar3 = sRam00f37e;
  iVar2 = _ml_hfm_accum;
  __atomic(3);
  PSW = PSW | 0xf000;
  __nop();
  sRam00f37e = 0;
  _ml_hfm_accum = 0;
  ml_hfm_accum_2 = 0;
  if ((uRam00fd3c & 2) == 0) {
    uRam00fd3c = uRam00fd3c | 2;
    uRam00f386 = _ml_hfm_inst;
  }
  else {
    MDC = MDC | 0x10;
    uRam00f386 = (ushort)(iVar2 / (int)sVar3);
  }
  _ml_hfm = uRam00f386;
  uVar4 = uRam00f386;
  if ((short)uRam00f386 < 0) {
    uVar4 = -uRam00f386;
  }
  uVar1 = (uint)uVar4 * (uint)_kfkhfm_factor;
  MDL = (ushort)uVar1;
  MDH = (short)(uVar1 >> 0x10);
  MDC = MDC | 0x10;
  if ((uVar1 & 0xc0000000) == 0) {
    _ml_hfm_corr = MDH << 1 | (ushort)uVar1 >> 0xf;
    if ((short)uRam00f386 < 0) {
      _ml_hfm_corr = -_ml_hfm_corr;
    }
  }
  else if ((short)uRam00f386 < 0) {
    _ml_hfm_corr = 0x8000;
  }
  else {
    _ml_hfm_corr = 0x7fff;
  }
  _ml_hfm_corr_pos = _ml_hfm_corr;
  if ((short)_ml_hfm_corr < 1) {
    _ml_hfm_corr_pos = 0;
  }
  if ((short)(_ml_hfm_corr - sRam0160e6) < 0 !=
      ((short)_ml_hfm_corr < 0 != sRam0160e6 < 0 &&
      (short)(_ml_hfm_corr - sRam0160e6) < 0 != (short)_ml_hfm_corr < 0)) {
    _ml_hfm_corr_floor = sRam0160e6;
    return;
  }
  _ml_hfm_corr_floor = _ml_hfm_corr;
  return;
}


// ================= hfm_kfkhfm_lookup @ 07638e =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* KFKHFM 0x138A5 byte map (rpm-class byte_F40E x load byte_F473, via sub_40CA4) -> correction
   factor word_3028A8 (<<8) [C] */

void hfm_kfkhfm_lookup(void)

{
  byte bVar1;
  
  bVar1 = func_0x040ca4(0x38a3,nmot_rpmclass,rl_byte);
  _kfkhfm_factor = (ushort)bVar1 << 8;
  return;
}


// ================= diag_hfm_plausibility @ 076a68 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC: HFM plausibility window: KFMLDMX 0x16208 (Throttle#=loc_F45E via word_3028AC,
   RPM=byte_F40E) xFMLDMXKO clamp MLDHFMKO -> upper bound; ml_hfm loc_F384 vs MLDHFMKU 0x2188A +
   window word_305138/word_305136 (filter ZMLRO 0x13986) -> fault bits word_FD3C.3-.7 [C] */

void diag_hfm_plausibility(void)

{
  short sVar1;
  int iVar2;
  
  if (((bRam013985 & 2) == 0) || ((uRam00fd7e & 0x400) == 0)) {
    _hfm_diag_throttle_axis = _throttle_pos_fb;
  }
  else {
    _hfm_diag_throttle_axis = 0xfff;
  }
  _ml_plaus_max =
       func_0x0414f8(uRam0161ec,0x61ee,uRam0161ed,0x61fe,0x6208,_hfm_diag_throttle_axis,
                     nmot_rpmclass);
  sRam00e4e8 = func_0x04305c(_ml_plaus_max,uRam0161ea,0xc);
  if (sRam00e4e8 != sRam016298 &&
      sRam00e4e8 - sRam016298 < 0 ==
      (sRam00e4e8 < 0 != sRam016298 < 0 && sRam00e4e8 - sRam016298 < 0 != sRam00e4e8 < 0)) {
    sRam00e4e8 = sRam016298;
  }
  if (_ml_hfm - sRam02188a < 0 ==
      (_ml_hfm < 0 != sRam02188a < 0 && _ml_hfm - sRam02188a < 0 != _ml_hfm < 0)) {
    uRam00fd3c = uRam00fd3c & 0xff7f;
  }
  else {
    uRam00fd3c = uRam00fd3c | 0x80;
  }
  iVar2 = me7_slew_limiter((ushort)bRam013986 << 8,_ml_hfm,sRam3028b0,uRam3028ae);
  sRam3028b0 = (short)((uint)iVar2 >> 0x10);
  uRam3028ae = (short)iVar2;
  sRam00e4ea = sRam3028b0;
  sVar1 = _ml_hfm;
  if (_ml_hfm != sRam3028b0 &&
      _ml_hfm - sRam3028b0 < 0 ==
      (_ml_hfm < 0 != iVar2 < 0 && _ml_hfm - sRam3028b0 < 0 != _ml_hfm < 0)) {
    sVar1 = sRam3028b0;
  }
  if (sVar1 == _ml_plaus_max ||
      sVar1 - _ml_plaus_max < 0 !=
      (sVar1 < 0 != _ml_plaus_max < 0 && sVar1 - _ml_plaus_max < 0 != sVar1 < 0)) {
    uRam00fd3c = uRam00fd3c & 0xffbf;
  }
  else {
    uRam00fd3c = uRam00fd3c | 0x40;
  }
  sVar1 = _ml_hfm;
  if (_ml_hfm - sRam3028b0 < 0 !=
      (_ml_hfm < 0 != iVar2 < 0 && _ml_hfm - sRam3028b0 < 0 != _ml_hfm < 0)) {
    sVar1 = sRam3028b0;
  }
  if (sVar1 - _ml_plaus_min < 0 ==
      (sVar1 < 0 != _ml_plaus_min < 0 && sVar1 - _ml_plaus_min < 0 != sVar1 < 0)) {
    uRam00fd3c = uRam00fd3c & 0xffdf;
  }
  else {
    uRam00fd3c = uRam00fd3c | 0x20;
  }
  if ((((uRam00fd3c & 0x20) == 0) && ((uRam00fd3c & 0x40) == 0)) &&
     (_ml_hfm != sRam305134 &&
      _ml_hfm - sRam305134 < 0 ==
      (_ml_hfm < 0 != sRam305134 < 0 && _ml_hfm - sRam305134 < 0 != _ml_hfm < 0))) {
    uRam00fd3c = uRam00fd3c & 0xffef;
  }
  else if (((uRam00fd3c & 0x20) != 0) || ((uRam00fd3c & 0x40) != 0)) {
    uRam00fd3c = uRam00fd3c | 0x10;
  }
  if ((bRam3015f3 & 0x20) != 0) {
    if ((bRam3015f3 & 0x40) == 0) {
      PSW = PSW | 0x40;
    }
    else {
      PSW = PSW & 0xffbf;
    }
    uRam00fdfe = uRam00fdfe & 0xffef | ((PSW & 0x40) >> 6 ^ 1) << 4;
  }
  if (((((uRam00fd3c & 0x10) == 0) && (((bRam3015f3 & 0x40) == 0 || ((bRam3015f3 & 0x20) == 0)))) ||
      ((bRam3014e3 & 4) == 0)) && (((uRam00fdfe & 0x10) != 0 || ((uRam303b5c & 1) == 0)))) {
    uRam00fd3c = uRam00fd3c & 0xfff7;
    return;
  }
  uRam00fd3c = uRam00fd3c | 8;
  return;
}


// ================= diag_hfm_bounds_status @ 076462 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC: HFM diag manager: KFMLDMN 0x217F6 (rpm-class x throttle pos loc_F45E) -> lower bound
   word_305136 (0x76706); threshold band 0x21886-0x21894; packs status via sub_B31AC [C for bound;
   overall role partial] */

void diag_hfm_bounds_status(void)

{
  byte bVar1;
  ushort uStack_2;
  
  if ((DAT_00fd34 & 0x10) == 0) {
    uRam0228b2 = uRam021888;
    bRam3014e5 = bRam3014e5 & 0xfe;
  }
  else if (sRam3028b2 == 0) {
    bRam3014e5 = bRam3014e5 | 1;
  }
  else {
    sRam3028b2 = sRam3028b2 + -1;
  }
  if ((uRam0217cc < uRam022816) && (uRam302816 < uRam0217ce)) {
    uRam0228b4 = uRam021886;
    bRam3014e5 = bRam3014e5 & 0xfd;
  }
  else if (sRam3028b4 == 0) {
    bRam3014e5 = bRam3014e5 | 2;
  }
  else {
    sRam3028b4 = sRam3028b4 + -1;
  }
  if ((bRam3014e5 & 1) != 0) {
    bRam3014e5 = bRam3014e5 | 4;
  }
  if (((bRam3014e5 & 4) == 0) || ((bRam3014e5 & 8) != 0)) {
    bVar1 = bRam3031ab;
    if ((((bRam3014e5 & 2) != 0) && (bVar1 = bRam3031ab | 2, cRam018ca2 != '\0')) &&
       ((uRam303ade & 1) != 0)) {
      bVar1 = bRam3031ab | 3;
    }
  }
  else {
    bVar1 = bRam3031ab & 0xfc;
  }
  bRam3031ab = bVar1;
  if ((bRam3014e5 & 4) == 0) {
    bRam3014e5 = bRam3014e5 & 0xf7;
  }
  else {
    bRam3014e5 = bRam3014e5 | 8;
  }
  if (((bRam3031ab & 2) == 0) ||
     ((((uRam303b56 & 1) == 0 &&
       (((bRam3031ab & 1) == 0 || (((uRam303ac0 & 1) != 0 && ((uRam303abe & 1) != 0)))))) ||
      ((uRam303aa8 & 1) != 0)))) {
    bRam3014e4 = bRam3014e4 & 0xfb;
  }
  else {
    bRam3014e4 = bRam3014e4 | 4;
  }
  if ((uRam00fdfe & 0x10) == 0) {
    MDL = uRam021892 / 10;
    MDH = uRam021892 % 10;
    if (uRam305630 <= MDL) goto LAB_0765ee;
LAB_0765e6:
    bRam3014e3 = bRam3014e3 | 4;
  }
  else {
    MDL = uRam021894 / 10;
    MDH = uRam021894 % 10;
    if (MDL < uRam305630) goto LAB_0765e6;
LAB_0765ee:
    bRam3014e3 = bRam3014e3 & 0xfb;
  }
  MDC = MDC | 0x10;
  if ((bRam30a108 & 0x10) == 0) {
    bRam3014e4 = bRam3014e4 & 0xfd;
  }
  else {
    bRam3014e4 = bRam3014e4 | 2;
  }
  if (((((bRam3014e3 & 2) == 0) || ((bRam3014e4 & 2) != 0)) ||
      ((uRam01990e <= bRam018caa || (((uRam00fd6e & 0x800) != 0 || ((uRam00fd70 & 0x200) != 0))))))
     || (((bRam013985 & 1) != 0 && ((uRam00fd7e & 0x400) != 0)))) {
    bRam3014e4 = bRam3014e4 & 0xfe;
  }
  else {
    bRam3014e4 = bRam3014e4 | 1;
  }
  if (bRam018ca9 < bRam30183b) {
    if (sRam3028b6 == 0) {
      bRam3014e5 = bRam3014e5 | 0x10;
    }
    else {
      sRam3028b6 = sRam3028b6 + -1;
    }
  }
  else {
    sRam3028b6 = sRam01629c;
    bRam3014e5 = bRam3014e5 & 0xef;
  }
  if (((bRam3014e3 & 4) == 0) || ((bRam3014e5 & 0x10) == 0)) {
    bRam3014e3 = bRam3014e3 & 0xfd;
  }
  else {
    bRam3014e3 = bRam3014e3 | 2;
  }
  _ml_plaus_min =
       func_0x0426da(uRam0217da,0x17dc,8,uRam0217db,0x17ec,8,0x17f6,8,_throttle_pos_fb,nmot_rpmclass
                    );
  if ((((uRam307aa8 & 1) == 0) && ((bRam3014e4 & 1) != 0)) && ((uRam00fd3c & 0x100) != 0)) {
    if (cRam3014e7 == '\0') {
      bRam3014e5 = bRam3014e5 | 0x20;
    }
    else {
      cRam3014e7 = cRam3014e7 + -1;
    }
  }
  else {
    uRam0194e7 = uRam018ca5;
    bRam3014e5 = bRam3014e5 & 0xdf;
  }
  if ((((uRam303aa8 & 1) == 0) && ((bRam3014e4 & 1) != 0)) && ((uRam00fd3c & 0x80) != 0)) {
    if (cRam3014e8 == '\0') {
      bRam3014e5 = bRam3014e5 | 0x40;
    }
    else {
      cRam3014e8 = cRam3014e8 + -1;
    }
  }
  else {
    uRam0194e8 = uRam018ca4;
    bRam3014e5 = bRam3014e5 & 0xbf;
  }
  if ((((uRam303aa8 & 1) == 0) && ((bRam3014e4 & 1) != 0)) && ((uRam00fd3c & 0x20) != 0)) {
    if (cRam3014e9 == '\0') {
      bRam3014e5 = bRam3014e5 | 0x80;
    }
    else {
      cRam3014e9 = cRam3014e9 + -1;
    }
  }
  else {
    uRam0194e9 = uRam018ca8;
    bRam3014e5 = bRam3014e5 & 0x7f;
  }
  if ((((uRam303aa8 & 1) == 0) && ((bRam3014e4 & 1) != 0)) && ((uRam00fd3c & 0x40) != 0)) {
    if (cRam3014ea == '\0') {
      bRam3014e6 = bRam3014e6 | 1;
    }
    else {
      cRam3014ea = cRam3014ea + -1;
    }
  }
  else {
    uRam0194ea = uRam018ca7;
    bRam3014e6 = bRam3014e6 & 0xfe;
  }
  if (((((((uRam303aa8 & 1) == 0) && ((bRam3014e4 & 1) != 0)) && ((uRam00fd3c & 0x100) != 0)) ||
       (((((uRam303aa8 & 1) == 0 && ((bRam3014e4 & 1) != 0)) && ((uRam00fd3c & 0x80) != 0)) ||
        ((((uRam303aa8 & 1) == 0 && ((bRam3014e4 & 1) != 0)) && ((uRam00fd3c & 0x40) != 0)))))) ||
      ((((uRam303aa8 & 1) == 0 && ((bRam3014e4 & 1) != 0)) && ((uRam00fd3c & 0x20) != 0)))) ||
     (((bRam3014e4 & 1) == 0 || ((bRam3014e4 & 4) != 0)))) {
    bRam3014e6 = bRam3014e6 & 0xfb;
  }
  else {
    bRam3014e6 = bRam3014e6 | 4;
  }
  if ((bRam3014e6 & 4) == 0) {
    uRam0194eb = uRam018ca6;
    bRam3014e6 = bRam3014e6 & 0xfd;
  }
  else if (cRam3014eb == '\0') {
    bRam3014e6 = bRam3014e6 | 2;
  }
  else {
    cRam3014eb = cRam3014eb + -1;
  }
  uStack_2 = uRam303b5c;
  if (((((bRam3014e6 & 2) == 0) || ((bRam3015f3 & 0x20) == 0)) ||
      (((bRam3014e4 & 1) != 0 && (((bRam3015f3 & 0x20) != 0 && ((bRam3015f3 & 1) != 0)))))) ||
     (((bRam3014e4 & 1) != 0 && (((bRam3015f3 & 0x20) != 0 && ((bRam3015f3 & 8) != 0)))))) {
    if ((bRam3014e5 & 0x20) == 0) {
      if ((bRam3014e5 & 0x40) == 0) {
        if (((bRam3014e5 & 0x80) == 0) &&
           ((((bRam3014e4 & 1) == 0 || ((bRam3015f3 & 0x20) == 0)) || ((bRam3015f3 & 1) == 0)))) {
          if (((bRam3014e6 & 1) == 0) &&
             ((((bRam3014e4 & 1) == 0 || ((bRam3015f3 & 0x20) == 0)) || ((bRam3015f3 & 8) == 0))))
          goto LAB_0769d8;
          uStack_2 = (uRam303b5c >> 8 & 0xfff0 | 8) << 8;
        }
        else {
          uStack_2 = (uRam303b5c >> 8 & 0xfff0 | 4) << 8;
        }
      }
      else {
        uStack_2 = (uRam303b5c >> 8 & 0xfff0 | 2) << 8;
      }
    }
    else {
      uStack_2 = (uRam303b5c >> 8 & 0xfff0 | 1) << 8;
    }
  }
  else {
    uStack_2 = uRam303b5c & 0xf0fe;
  }
  uStack_2 = (uStack_2 >> 8 & 0x9f | 0x60) << 8 | 2;
LAB_0769d8:
  func_0x0b31ac(0x6b,uStack_2);
  if (((bRam3014e4 & 1) == 0) || ((bRam3015f3 & 0x10) == 0)) {
    uRam3028b8 = uRam02188e;
    if (uRam02188e < uRam021890) {
      uRam3028b8 = uRam021890;
    }
    bRam3014e3 = bRam3014e3 & 0xfe;
  }
  else if (uRam3028b8 == 0) {
    bRam3014e3 = bRam3014e3 | 1;
  }
  else {
    uRam3028b8 = uRam3028b8 - 1;
  }
  if (((bRam3014e3 & 1) != 0) && (bRam01447c != 0xff)) {
    *(byte *)((uint3)(bRam01447c + 0x9db) + 0x304000) =
         *(byte *)((uint3)(bRam01447c + 0x9db) + 0x304000) | 1;
  }
  return;
}


// ================= diag_input_monitor_bank @ 0c5f2c =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC: debounced monitor bank (1st slot of sub_B81C chain): CAN-mirror status (byte_301437
   state 0/1/3, byte_301443 hysteresis 0x14576/77, word_30256C.12) + ADC byte byte_3014D2
   (=word_301934>>2; min/max 0x1458B/88/89, stuck-check 0x1457C, slow baseline word_303C3E via
   sub_42CF4 gain 0x16EAC, deviation byte_30175A) -> monitor-mask flags word_FD64.11/.12 (gate
   misfire sub_A0000 + knock-diag sub_39FCA) and word_FD66.2/.5 (idle gov sub_7D58E / torque coord
   sub_4D86C) + one-shot fault bytes byte_301767-6F [C mechanism; monitored module identity I] */

void diag_input_monitor_bank(void)

{
  ushort uVar1;
  ushort uVar2;
  bool bVar3;
  byte bVar4;
  
  if (((uRam30256c & 0x1000) == 0) && ((_flags_start_phase & 0x8000) != 0)) {
    bVar3 = true;
  }
  else {
    bVar3 = false;
  }
  if (bVar3) {
    if (bRam01975b < bRam01457d) {
      bRam01975b = bRam01975b + 1;
      goto LAB_0c5f6c;
    }
    bRam01975b = -1;
    uRam00fd64 = uRam00fd64 | 0x20;
  }
  else {
    bRam01975b = '\0';
LAB_0c5f6c:
    uRam00fd64 = uRam00fd64 & 0xffdf;
  }
  if ((uRam00fd64 & 0x20) != 0) {
    uRam301767 = 1;
  }
  if (cRam301437 == '\x03') {
    bRam01975c = '\0';
LAB_0c5fb0:
    uRam00fd64 = uRam00fd64 & 0xffbf;
  }
  else {
    if (bRam01975c < bRam01457e) {
      bRam01975c = bRam01975c + 1;
      goto LAB_0c5fb0;
    }
    bRam01975c = -1;
    uRam00fd64 = uRam00fd64 | 0x40;
  }
  if (((_flags_start_phase & 0x8000) == 0) || (cRam301437 != '\0')) {
    bVar3 = false;
  }
  else {
    bVar3 = true;
  }
  if (bVar3) {
    if (bRam01975d < bRam01457f) {
      bRam01975d = bRam01975d + 1;
      goto LAB_0c5fec;
    }
    bRam01975d = -1;
    uRam00fd64 = uRam00fd64 | 0x80;
  }
  else {
    bRam01975d = '\0';
LAB_0c5fec:
    uRam00fd64 = uRam00fd64 & 0xff7f;
  }
  if ((uRam00fd64 & 0x80) != 0) {
    uRam301768 = 1;
  }
  if (((((uRam00fd3a & 0x20) == 0) && ((_flags_start_phase & 0x8000) != 0)) &&
      (bRam014587 < bRam301443)) && (cRam301437 != '\x01')) {
    bVar3 = true;
  }
  else {
    bVar3 = false;
  }
  if (bVar3) {
    if (bRam01975e < bRam014580) {
      bRam01975e = bRam01975e + 1;
      goto LAB_0c6046;
    }
    bRam01975e = -1;
    uRam00fd64 = uRam00fd64 | 0x100;
  }
  else {
    bRam01975e = '\0';
LAB_0c6046:
    uRam00fd64 = uRam00fd64 & 0xfeff;
  }
  if ((uRam00fd64 & 0x100) != 0) {
    uRam301769 = 1;
  }
  if (cRam301437 == '\x01') {
    if (bRam01975f < bRam014581) {
      bRam01975f = bRam01975f + 1;
      goto LAB_0c608a;
    }
    bRam01975f = -1;
    uRam00fd64 = uRam00fd64 | 0x200;
  }
  else {
    bRam01975f = '\0';
LAB_0c608a:
    uRam00fd64 = uRam00fd64 & 0xfdff;
  }
  if (cRam301437 == '\x03') {
    uRam30176a = 1;
  }
  if ((uRam00fd64 & 0x400) == 0) {
    if (bRam014577 < bRam301443) {
      uRam00fd64 = uRam00fd64 | 0x400;
    }
    else {
LAB_0c60c0:
      uVar2 = (PSW & 8) >> 3 ^ 1;
      PSW = PSW & 0xffbf | uVar2 << 6;
      uRam00fd64 = uRam00fd64 & 0xfbff | uVar2 << 10;
    }
  }
  else {
    if (bRam014576 <= bRam301443) goto LAB_0c60c0;
    uRam00fd64 = uRam00fd64 & 0xfbff;
  }
  if (((uRam00fd64 & 0x20) == 0) && ((uRam00fd64 & 0x40) == 0)) {
    if ((((uRam00fd64 & 0x200) == 0) && (((uRam303a9a & 1) == 0 && ((uRam00fd3a & 0x20) == 0)))) &&
       ((uRam00fd64 & 0x400) == 0)) goto LAB_0c60fc;
LAB_0c60f8:
    uRam00fd64 = uRam00fd64 | 0x1000;
  }
  else {
    if ((((uRam00fd64 & 0x200) != 0) || ((uRam303a9a & 1) != 0)) || ((uRam00fd3a & 0x20) != 0))
    goto LAB_0c60f8;
LAB_0c60fc:
    uRam00fd64 = uRam00fd64 & 0xefff;
  }
  if ((uRam00fd64 & 0x1000) == 0) {
    bRam019760 = '\0';
LAB_0c612c:
    uRam00fd64 = uRam00fd64 & 0xdfff;
  }
  else {
    if (bRam019760 < bRam014582) {
      bRam019760 = bRam019760 + 1;
      goto LAB_0c612c;
    }
    bRam019760 = -1;
    uRam00fd64 = uRam00fd64 | 0x2000;
  }
  if ((((uRam00fd64 & 0x400) == 0) || ((uRam00fd3a & 0x20) == 0)) ||
     (((uRam303a9a & 1) != 0 || ((uRam00fd64 & 0x40) != 0)))) {
    PSW = PSW & 0xffbf;
  }
  else {
    PSW = PSW | 0x40;
  }
  uVar1 = ((PSW & 0x40) >> 6) << 0xb;
  uVar2 = uRam00fd64 & 0xf7ff | uVar1;
  if ((_flags_diag_cfg_a & 0x10) == 0) {
    if (bRam3014d2 < bRam01458b) {
      if (bRam019761 < bRam014583) {
        bRam019761 = bRam019761 + 1;
        goto LAB_0c6192;
      }
      bRam019761 = 0xff;
      uRam00fd64 = uVar2 | 0x8000;
    }
    else {
      bRam019761 = 0;
LAB_0c6192:
      uRam00fd64 = uRam00fd64 & 0x77ff | uVar1;
    }
    if ((uRam00fd64 & 0x8000) != 0) {
      uRam30176b = 1;
    }
    if (bRam014588 < bRam3014d2) {
      if (bRam019762 < bRam014583) {
        bRam019762 = bRam019762 + 1;
        goto LAB_0c61d8;
      }
      bRam019762 = 0xff;
      uRam00fd66 = uRam00fd66 | 1;
    }
    else {
      bRam019762 = 0;
LAB_0c61d8:
      uRam00fd66 = uRam00fd66 & 0xfffe;
    }
    if ((uRam00fd66 & 1) != 0) {
      uRam30176c = 1;
    }
    if (bRam014589 < bRam3014d2) {
      if (bRam019763 < bRam014583) {
        bRam019763 = bRam019763 + 1;
        goto LAB_0c621e;
      }
      bRam019763 = 0xff;
      uRam00fd66 = uRam00fd66 | 2;
    }
    else {
      bRam019763 = 0;
LAB_0c621e:
      uRam00fd66 = uRam00fd66 & 0xfffd;
    }
    uVar2 = uRam00fd64;
    if ((uRam00fd66 & 2) != 0) {
      uRam30176d = 1;
    }
  }
  uRam00fd64 = uVar2;
  if (bRam019765 < bRam014584) {
    bRam019765 = bRam019765 + 1;
  }
  else {
    bRam019765 = -1;
    uRam30176e = 1;
    if ((((uRam00fd64 & 0x8000) == 0) && ((uRam00fd66 & 1) == 0)) && ((uRam00fd66 & 2) == 0)) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    if (bVar3) {
      if (uRam01ac90 < uRam016eae) {
        uRam01ac90 = uRam01ac90 + 1;
        goto LAB_0c6294;
      }
      uRam01ac90 = 0xffff;
      uRam00fd64 = uRam00fd64 | 0x4000;
    }
    else {
      uRam01ac90 = 0;
LAB_0c6294:
      uRam00fd64 = uRam00fd64 & 0xbfff;
    }
    if ((uRam00fd64 & 0x4000) != 0) {
      uRam30176f = 1;
    }
  }
  if ((_flags_diag_cfg_a & 0x10) == 0) {
    if (((((uRam00fd66 & 0x40) == 0) || ((uRam00fd64 & 0x8000) != 0)) || ((uRam00fd66 & 1) != 0)) ||
       ((((uRam00fd66 & 2) != 0 || (bRam01458a < bRam3014d2)) ||
        ((bRam3014d2 < bRam01458c || ((_flags_start_phase & 0x8000) == 0)))))) {
      uRam00fd64 = uRam00fd64 & 0xfff7;
    }
    else {
      uRam00fd64 = uRam00fd64 | 8;
      uRam303c3e = me7_fraction_blend(uRam016eac,bRam3014d2,uRam303c3e);
    }
    bVar4 = (byte)((ushort)uRam303c3e >> 8);
    bRam30175a = bVar4 - bRam3014d2;
    if (bVar4 < bRam3014d2) {
      bRam30175a = 0;
    }
    if (bRam300be0 < bRam3014d2) {
      bRam300be0 = bRam3014d2 - bRam300be0;
    }
    else {
      bRam300be0 = bRam300be0 - bRam3014d2;
    }
    if (bRam300be0 < bRam01457c) {
      if (bRam01f5c0 < bRam016eb0) {
        bRam01f5c0 = bRam01f5c0 + 1;
        goto LAB_0c634a;
      }
      bRam01f5c0 = 0xff;
      uRam00fd66 = uRam00fd66 | 0x40;
    }
    else {
      bRam01f5c0 = 0;
LAB_0c634a:
      uRam00fd66 = uRam00fd66 & 0xffbf;
    }
    bRam300be0 = bRam3014d2;
  }
  if ((_flags_diag_cfg_a & 0x10) == 0) {
    if ((uRam00fd66 & 0x80) == 0) {
      if (bRam014579 < bRam30175a) {
        uRam00fd66 = uRam00fd66 | 0x80;
      }
      else {
LAB_0c637e:
        uVar2 = PSW & 8;
        PSW = PSW & 0xffbf;
        uRam00fd66 = uRam00fd66 & 0xff7f | (uVar2 >> 3 ^ 1) << 7;
      }
    }
    else {
      if (bRam014578 <= bRam30175a) goto LAB_0c637e;
      uRam00fd66 = uRam00fd66 & 0xff7f;
    }
    if (bRam01457a < bRam3014d2) {
      if (bRam019764 < bRam014585) {
        bRam019764 = bRam019764 + 1;
      }
      else {
        bRam019764 = 0xff;
      }
    }
    else {
      bRam019764 = 0;
    }
    uVar2 = (PSW & 8) >> 3 ^ 1;
    PSW = PSW & 0xffbf | uVar2 << 6;
    if ((((uRam00fd64 & 0x8000) == 0) && ((uRam00fd66 & 1) == 0)) && ((uRam00fd66 & 2) == 0)) {
      if ((uRam00fd66 & 0x80) == 0) {
        uRam00fd66 = uRam00fd66 & 0xfff7;
      }
      else {
        uRam00fd66 = uRam00fd66 | 8;
      }
      if (bRam01457b < bRam30175a) {
        uRam00fd66 = uRam00fd66 | 0x10;
      }
      else {
        uRam00fd66 = uRam00fd66 & 0xffef;
      }
      if (uVar2 == 1) goto LAB_0c6406;
    }
    else {
      uRam00fd66 = uRam00fd66 | 0x18;
    }
    uRam00fd66 = uRam00fd66 | 4;
  }
  else {
    uRam00fd66 = uRam00fd66 & 0xffe7;
LAB_0c6406:
    uRam00fd66 = uRam00fd66 & 0xfffb;
  }
  uRam00fd66 = uRam00fd66 & 0xffdf | ((uRam00fd66 & 0x10) >> 4) << 5;
  return;
}


// ================= diag_monitor_status_report @ 0c6410 =================

/* DIAGNOSTIC: consumes+clears the one-shot monitor bytes byte_301767-6F of diag_input_monitor_bank
   -> state bits word_FD64.4 / word_FD66.8/.9, packs status to CAN via sub_B31AC x2
   (0xC660E/0xC661C) [C] */

void diag_monitor_status_report(void)

{
  bool bVar1;
  ushort uStack_4;
  ushort uStack_2;
  
  uStack_4 = uRam303a9a;
  uStack_2 = uRam303b4a;
  if (bRam014586 < bRam301839) {
    if ((uRam00fd64 & 0x10) == 0) {
      if (cRam301768 == '\0') {
        if (cRam301767 == '\0') {
          if (cRam301769 == '\0') goto LAB_0c64d0;
          uStack_4 = (uRam303a9a >> 8 & 0xfff0 | 8) << 8;
        }
        else {
          uStack_4 = (uRam303a9a >> 8 & 0xfff0 | 4) << 8;
        }
      }
      else {
        uStack_4 = (uRam303a9a >> 8 & 0xfff0 | 1) << 8;
      }
      uStack_4 = (uStack_4 >> 8 & 0x9f | 0x60) << 8 | 2;
      cRam301767 = '\0';
      cRam301768 = '\0';
      cRam301769 = '\0';
    }
    else {
      uStack_4 = ((uRam303a9a & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
      cRam301767 = '\0';
      cRam301768 = '\0';
      cRam301769 = '\0';
      uRam00fd64 = uRam00fd64 & 0xffef;
    }
  }
LAB_0c64d0:
  if (cRam30176a != '\0') {
    uStack_4 = (uStack_4 >> 8 & 0x9f | 0x60) << 8 | 2;
  }
  if (bRam014586 < bRam301839) {
    if (cRam30176f == '\0') {
      if (cRam30176c == '\0') {
        if (cRam30176b == '\0') {
          if (cRam30176d == '\0') goto LAB_0c65b8;
          uStack_2 = (uRam303b4a >> 8 & 0xfff0 | 8) << 8 | 1;
        }
        else {
          uStack_2 = (uRam303b4a >> 8 & 0xfff0 | 2) << 8 | 1;
        }
      }
      else {
        uStack_2 = (uRam303b4a >> 8 & 0xfff0 | 1) << 8 | 1;
      }
      cRam30176d = '\0';
      cRam30176b = '\0';
      cRam30176c = '\0';
    }
    else {
      uStack_2 = ((uRam303b4a & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
      cRam30176d = '\0';
      cRam30176b = '\0';
      cRam30176c = '\0';
      cRam30176f = '\0';
    }
  }
LAB_0c65b8:
  if (cRam30176e != '\0') {
    uStack_2 = (uStack_2 >> 8 & 0x9f | 0x60) << 8 | 2;
  }
  if ((((uRam00fd64 & 0x8000) == 0) && ((uRam00fd66 & 1) == 0)) && ((uRam00fd66 & 2) == 0)) {
    uStack_2 = uStack_2 & 0xffbf;
  }
  else {
    uStack_2 = uStack_2 & 0xff00 | uStack_2 & 0xff00 | 0x40;
  }
  func_0x0b31ac(10,uStack_4);
  func_0x0b31ac(0x62,uStack_2);
  if ((((uRam00fd64 & 0x20) == 0) && ((uRam00fd64 & 0x80) == 0)) && ((uRam00fd64 & 0x100) == 0)) {
    if (((uRam00fd3a & 0x20) != 0) && (bRam014587 < bRam301443)) {
      uRam00fd66 = uRam00fd66 | 0x100;
    }
    if (((uRam00fd3a & 0x20) == 0) && (bRam301443 <= bRam014587)) {
      uRam00fd66 = uRam00fd66 | 0x200;
    }
  }
  else {
    uRam00fd66 = uRam00fd66 & 0xfcff;
  }
  if (((uRam00fd66 & 0x100) == 0) || ((uRam00fd66 & 0x200) == 0)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    if (bRam01b95f <= bRam019766) {
      uRam00fd64 = uRam00fd64 | 0x10;
      bRam019766 = 0xff;
      return;
    }
    bRam019766 = bRam019766 + 1;
  }
  else {
    bRam019766 = '\0';
  }
  uRam00fd64 = uRam00fd64 & 0xffef;
  return;
}


// ================= diag_setpoint_follow_monitor @ 0c9f44 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC: deviation supervision: reference word_3029C6 (from sub_8A834, zeroed on fault) vs
   slew-follower word_302CF8 (sub_CA5C6, rate cal word_26B4E) in both directions (cals 0x16F5A/5C,
   debounce counts 0x16F5E/60) + ADC word_30196E cross-check (thresholds 0x16F52/54 split at
   word_16F62); enable window rpm-class byte_F40E in [0x14744,0x14743] + byte_3014DD in
   [0x14742,0x14741], masked by word_FD64.12; -> status bytes byte_300C06/13/14, byte_301794, flags
   loc_FD70.13-.15 / loc_FD72.0-.1 [C mechanism; supervised quantity identity I] */

ushort diag_setpoint_follow_monitor(void)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  ushort uVar5;
  undefined1 uVar7;
  ushort uVar6;
  ushort uVar8;
  
  if (_vfzg_vehicle_speed < _cruise_set_speed) {
    if (((uRam00fd78 & 4) == 0) || (_cruise_set_speed - _vfzg_vehicle_speed <= uRam016f5c)) {
      bRam300c14 = bRam300c14 & 0xfe;
      uRam300c16 = 0;
    }
    else if (uRam300c16 < uRam016f60) {
      uRam300c16 = uRam300c16 + 1;
    }
    else {
      bRam300c14 = bRam300c14 | 1;
    }
    uRam300c10 = 0;
    bRam300c14 = bRam300c14 & 0xfd;
  }
  else {
    if (((uRam00fd78 & 4) == 0) || (_vfzg_vehicle_speed - _cruise_set_speed <= uRam016f5a)) {
      bRam300c14 = bRam300c14 & 0xfd;
      uRam300c10 = 0;
    }
    else if (uRam300c10 < uRam016f5e) {
      uRam300c10 = uRam300c10 + 1;
    }
    else {
      bRam300c14 = bRam300c14 | 2;
    }
    uRam300c16 = 0;
    bRam300c14 = bRam300c14 & 0xfe;
  }
  if (((((uRam00fd0a & 2) == 0) && ((uRam00fd08 & 0x2000) == 0)) && ((bRam300c14 & 1) == 0)) &&
     ((bRam300c14 & 2) == 0)) {
    bRam301794 = bRam301794 & 0xfe;
    bVar4 = false;
  }
  else {
    bRam301794 = bRam301794 | 1;
    bVar4 = true;
  }
  if (((uRam00fd78 & 2) == 0) || ((uRam00fd82 & 2) != 0)) {
    bRam300c14 = bRam300c14 & 0xfb;
    bRam300c18 = 0;
  }
  else if (bRam300c18 < bRam01474b) {
    bRam300c18 = bRam300c18 + 1;
  }
  else {
    bRam300c14 = bRam300c14 | 4;
  }
  if ((uRam00fd78 & 2) == 0) {
    bRam300c14 = bRam300c14 & 0xe7;
    bRam300c07 = 0;
    bRam300c12 = 0;
  }
  else {
    if ((char)(cRam3015d7 - cRam01473e) < '\0' ==
        (cRam3015d7 < '\0' != cRam01473e < '\0' &&
        (char)(cRam3015d7 - cRam01473e) < '\0' != cRam3015d7 < '\0')) {
      bRam300c14 = bRam300c14 & 0xf7;
      bRam300c07 = 0;
    }
    else if (bRam300c07 < bRam01474c) {
      bRam300c07 = bRam300c07 + 1;
    }
    else {
      bRam300c14 = bRam300c14 | 8;
    }
    if ((cRam3015d7 == cRam01473d ||
         (char)(cRam3015d7 - cRam01473d) < '\0' !=
         (cRam3015d7 < '\0' != cRam01473d < '\0' &&
         (char)(cRam3015d7 - cRam01473d) < '\0' != cRam3015d7 < '\0')) ||
       ((uRam00fd1c & 0x100) == 0)) {
      bRam300c14 = bRam300c14 & 0xef;
      bRam300c12 = 0;
    }
    else if (bRam300c12 < bRam01474a) {
      bRam300c12 = bRam300c12 + 1;
    }
    else {
      bRam300c14 = bRam300c14 | 0x10;
    }
  }
  if ((((uRam00fd04 & 4) == 0) && ((bRam300c14 & 8) != 0)) || ((bRam300c14 & 0x10) != 0)) {
    bRam301794 = bRam301794 | 8;
    bVar3 = true;
  }
  else {
    bRam301794 = bRam301794 & 0xf7;
    bVar3 = false;
  }
  if (((uRam30256c & 4) == 0) || ((bRam014740 & 1) != 0)) {
    bRam300c06 = bRam300c06 & 0xfe;
    bRam300c15 = 0;
  }
  else if (bRam300c15 < bRam014749) {
    bRam300c15 = bRam300c15 + 1;
  }
  else {
    bRam300c06 = bRam300c06 | 1;
  }
  if (((uRam30256a & 0x400) == 0) || ((bRam014740 & 2) != 0)) {
    bRam300c06 = bRam300c06 & 0xfd;
    bRam300c0b = 0;
  }
  else if (bRam300c0b < bRam014746) {
    bRam300c0b = bRam300c0b + 1;
  }
  else {
    bRam300c06 = bRam300c06 | 2;
  }
  if (((uRam30256c & 2) == 0) || ((bRam01473f & 1) != 0)) {
    bRam300c14 = bRam300c14 & 0xdf;
    bRam300c09 = 0;
  }
  else if (bRam300c09 < bRam014748) {
    bRam300c09 = bRam300c09 + 1;
  }
  else {
    bRam300c14 = bRam300c14 | 0x20;
  }
  if (((DAT_00fd1e & 0x2000) == 0) || ((bRam01473f & 0x40) != 0)) {
    bRam300c14 = bRam300c14 & 0xbf;
    bRam300c08 = 0;
  }
  else if (bRam300c08 < bRam014747) {
    bRam300c08 = bRam300c08 + 1;
  }
  else {
    bRam300c14 = bRam300c14 | 0x40;
  }
  if (uRam30196e < _vfzg_vehicle_speed) {
    uVar8 = _vfzg_vehicle_speed - uRam30196e;
  }
  else {
    uVar8 = uRam30196e - _vfzg_vehicle_speed;
  }
  uVar5 = uRam016f54;
  if (uRam016f62 < _vfzg_vehicle_speed) {
    uVar5 = uRam016f52;
  }
  if (uVar5 < uVar8) {
    if (bRam300c19 < bRam014745) {
      bRam300c19 = bRam300c19 + 1;
    }
    else {
      bRam300c14 = bRam300c14 | 0x80;
    }
  }
  else {
    bRam300c14 = bRam300c14 & 0x7f;
    bRam300c19 = 0;
  }
  if ((((((((uRam00fd64 & 0x1000) != 0) || ((uRam00fd66 & 8) != 0)) || ((uRam00fd3c & 1) != 0)) ||
        (((bRam301278 & 4) != 0 || (bRam014743 < nmot_rpmclass)))) || (nmot_rpmclass < bRam014744))
      || (((bRam014741 < gear_index || (gear_index < bRam014742)) ||
          (((bRam300c14 & 4) != 0 || (((uRam00fd70 & 0x200) != 0 && ((bRam01473f & 0x10) == 0)))))))
      ) || ((bVar3 && ((bRam01473f & 0x80) != 0)))) {
    bRam300c13 = bRam300c13 | 0x20;
    bVar1 = true;
  }
  else {
    bRam300c13 = bRam300c13 & 0xdf;
    bVar1 = false;
  }
  if (((uRam00fd04 & 4) == 0) &&
     ((((((bRam300c06 & 1) != 0 || ((bRam300c06 & 2) != 0)) || ((bRam300c14 & 0x20) != 0)) ||
       (((bRam300c14 & 0x40) != 0 || (((bRam300c14 & 0x80) != 0 && ((bRam01473f & 2) != 0)))))) ||
      ((uRam3029c0 < uRam016f66 || (uRam016f64 < uRam3029c0)))))) {
    bRam300c13 = bRam300c13 | 0x40;
    bVar2 = true;
  }
  else {
    bRam300c13 = bRam300c13 & 0xbf;
    bVar2 = false;
  }
  if ((bVar1) || (bVar2)) {
    bRam301794 = bRam301794 | 2;
    bVar1 = true;
  }
  else {
    bRam301794 = bRam301794 & 0xfd;
    bVar1 = false;
  }
  if (((((((uRam00fd0a & 1) != 0) || ((uRam303a9a & 1) != 0)) || ((uRam303c1e & 1) != 0)) ||
       ((((uRam00fd06 & 0x4000) != 0 && ((bRam01473f & 4) != 0)) ||
        (((uRam00fd70 & 0x20) != 0 && ((bRam01473f & 8) == 0)))))) ||
      (((uRam00fd6e & 0x400) != 0 && ((bRam01473f & 0x20) != 0)))) ||
     ((bVar3 && ((bRam01473f & 0x80) == 0)))) {
    uRam00fd70 = uRam00fd70 | 0x4000;
  }
  uVar8 = uRam00fd70;
  if ((bVar1) || ((uRam00fd70 & 0x4000) != 0)) {
    PSW = PSW | 0x40;
  }
  else {
    PSW = PSW & 0xffbf;
  }
  uVar5 = (PSW & 0x40) >> 6;
  uRam00fd70 = uRam00fd70 & 0x7fff | uVar5 << 0xf;
  if ((_vfzg_vehicle_speed < uRam300c0e) || (uRam300c04 < _vfzg_vehicle_speed)) {
    uRam00fd72 = uRam00fd72 & 0xfffd;
  }
  else {
    uRam00fd72 = uRam00fd72 | 2;
  }
  uVar6 = _vfzg_vehicle_speed;
  if ((uVar5 != 0) || (uVar6 = 0, bVar4)) {
    uVar7 = (undefined1)(uVar6 >> 8);
    uRam00fd72 = uRam00fd72 & 0xfffe;
  }
  else if ((((uRam00fd04 & 4) == 0) && ((uRam00fd72 & 2) == 0)) ||
          (((((uRam00fd0a & 0x100) == 0 || ((bRam300c13 & 1) != 0)) &&
            (((uRam00fd0a & 0x400) == 0 || ((bRam300c13 & 2) != 0)))) &&
           ((((uRam00fd0a & 0x80) == 0 || ((bRam300c13 & 4) != 0)) &&
            (((uRam00fd0a & 0x200) == 0 || ((bRam300c13 & 8) != 0)))))))) {
    uVar7 = 0;
    bRam301794 = bRam301794 & 0xfb;
  }
  else {
    uVar7 = 0;
    bRam301794 = bRam301794 | 4;
    uRam00fd72 = uRam00fd72 | 1;
  }
  if ((uRam00fd0a & 0x100) == 0) {
    bRam300c13 = bRam300c13 & 0xfe;
  }
  else {
    bRam300c13 = bRam300c13 | 1;
  }
  if ((uRam00fd0a & 0x80) == 0) {
    bRam300c13 = bRam300c13 & 0xfb;
  }
  else {
    bRam300c13 = bRam300c13 | 4;
  }
  if ((uRam00fd0a & 0x400) == 0) {
    bRam300c13 = bRam300c13 & 0xfd;
  }
  else {
    bRam300c13 = bRam300c13 | 2;
  }
  if ((uRam00fd0a & 0x200) == 0) {
    bRam300c13 = bRam300c13 & 0xf7;
  }
  else {
    bRam300c13 = bRam300c13 | 8;
  }
  if ((uRam00fd72 & 1) == 0) {
    if (bVar4) {
      uVar6 = 0x10;
      bRam300c13 = bRam300c13 | 0x10;
    }
    else {
      uVar6 = bRam300c13 & 0x10;
      if (((bRam300c13 & 0x10) != 0) && (uVar6 = (ushort)bRam300c0d, bRam300c0d == bRam300c0c)) {
        bRam300c13 = bRam300c13 & 0xef;
      }
    }
    if ((bRam300c13 & 0x10) == 0) {
      bRam300c0d = 0;
    }
    else {
      uVar6 = (ushort)bRam300c0d;
      if (bRam300c0d < bRam300c0c) {
        bRam300c0d = bRam300c0d + 1;
        uVar6 = (ushort)bRam300c0d;
      }
    }
    if ((((bRam300c13 & 0x10) == 0) || (uVar6 = (ushort)bRam300c0d, bRam300c0d != bRam300c0c)) &&
       (uVar5 == 0)) {
      if (bRam300c0a < 2) {
        bRam300c0a = bRam300c0a + 1;
        return (ushort)bRam300c0a;
      }
      uRam00fd70 = uVar8 & 0x5fff;
      return (ushort)bRam300c0a;
    }
    uRam00fd70 = uRam00fd70 | 0x2000;
    bRam300c0a = 0;
    return uVar6;
  }
  uRam00fd70 = uVar8 & 0x5fff | uVar5 << 0xf;
  bRam300c13 = bRam300c13 & 0xef;
  bRam300c0d = 0;
  return CONCAT11(uVar7,0xef);
}


// ================= diag_obd_param_seed_init @ 0a7d34 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC-CONFIG: copies OBD scalar band 0x2418E-0x241B4 into RAM mirrors
   word_305386-word_3053B2; builds monitor bitmasks from cal bit-indexes byte_1A18C/1A18F/1A191 ->
   word_305398/word_30539C; edge-detects status transitions (byte_300A04/05, byte_3009F4/F5,
   byte_300A08-0B); gates on NV word_30A252 & mask word_241A6 + CDDST flag word_3018D8.2 ->
   byte_301714.2 [C] */

ushort diag_obd_param_seed_init(void)

{
  bool bVar1;
  ushort uVar2;
  
  uRam305388 = uRam024196;
  uRam305396 = uRam0241a4;
  uRam30538a = uRam024198;
  uRam305390 = uRam02419e;
  uRam305386 = uRam024194;
  uRam30538c = uRam02419a;
  uRam30538e = uRam02419c;
  uRam305392 = uRam0241a0;
  uRam305394 = uRam0241a2;
  uRam3053ac = uRam0241a8;
  uRam3053a8 = uRam0241ae;
  uRam3053aa = uRam0241b0;
  uRam3053a6 = uRam0241aa;
  uRam3053a2 = uRam0241ac;
  uRam3053a0 = uRam0241b2;
  uRam3053b2 = uRam0241b4;
  uRam3053b0 = uRam024192;
  uRam3053a4 = uRam024190;
  uRam3053ae = uRam02418e;
  if (cRam01a17a == '\0') {
    if ((_DAT_302632 & 0x800) == 0) {
      uRam30539c = 0;
    }
    else {
      uRam30539c = 1 << (ushort)bRam01a18f;
    }
    uRam30539c = uRam30539c & ~(1 << (ushort)bRam01a18c);
  }
  else {
    if ((_DAT_302632 & 0x800) == 0) {
      uRam30539c = 0;
    }
    else {
      uRam30539c = 1 << (ushort)bRam01a18f;
    }
    uRam30539c = uRam30539c | 1 << (ushort)bRam01a18c;
  }
  uRam305398 = uRam30539c;
  if (((bRam307334 & 1) == 0) && ((DAT_303334 & 2) == 0)) {
    bRam300a04 = false;
    cRam300a05 = 0;
  }
  else {
    bRam300a04 = cRam300a05 == '\0';
    cRam300a05 = 1;
  }
  bRam3009f4 = cRam3009f5 == '\0';
  cRam3009f5 = 1;
  bVar1 = (uRam30a252 & uRam0241a6) != 0;
  bRam300a08 = bVar1 && cRam300a09 == '\0';
  cRam300a09 = bVar1;
  if ((_flags_diag_enable_b & 4) == 0) {
    DAT_301714 = DAT_301714 & 0xfb;
  }
  else {
    DAT_301714 = DAT_301714 | 4;
  }
  uVar2 = 1 << (ushort)bRam01a191 & uRam30a252;
  bRam300a0a = uVar2 != 0 && cRam300a0b == '\0';
  cRam300a0b = uVar2 != 0;
  return uVar2;
}


// ================= servo_position_loop @ 0c677a =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* throttle-servo PD position loop: error = setpoint loc_F446 - feedback loc_F45E, deadband cals
   0x16EB2-0x16EB8, P+D -> direction bit word_FD68.3 + port word_FFD0, PWM duty loc_F440 ->
   word_FE34 (period 9999) (etc-throttle.md 2) [C] */

void servo_position_loop(void)

{
  bool bVar1;
  ushort uVar2;
  int iVar3;
  ushort uVar4;
  ushort uVar5;
  short sVar6;
  ushort uVar7;
  
  if ((uRam00fd6a & 2) == 0) {
    return;
  }
  _servo_pos_error = _servo_pos_setpoint - _throttle_pos_fb;
  if ((short)_servo_pos_error < 0) {
    if ((short)(_servo_pos_error + 0xfff) < 0 !=
        (-1 < (short)_servo_pos_error &&
        (short)(_servo_pos_error + 0xfff) < 0 != (short)_servo_pos_error < 0)) {
      _servo_pos_error = 0xf001;
    }
  }
  else if (0xfff < _servo_pos_error) {
    _servo_pos_error = 0xfff;
  }
  if ((uRam00fd70 & 2) == 0) {
    uRam00f448 = uRam016eb2;
    uRam00f44a = uRam016eb6;
  }
  else {
    uRam00f448 = uRam016eb4;
    uRam00f44a = uRam016eb8;
  }
  uRam00f43e = uRam00f45a - _throttle_pos_fb;
  uVar7 = uRam00f43e;
  if ((short)uRam00f43e < 0) {
    uVar7 = -uRam00f43e;
  }
  if (uVar7 < uRam00f448) {
    uVar7 = _servo_pos_error;
    if ((short)_servo_pos_error < 0) {
      uVar7 = -_servo_pos_error;
    }
    if (uVar7 == uRam00f44a ||
        (short)(uVar7 - uRam00f44a) < 0 !=
        ((short)uVar7 < 0 != (short)uRam00f44a < 0 &&
        (short)(uVar7 - uRam00f44a) < 0 != (short)uVar7 < 0)) {
      uVar7 = 0;
      goto LAB_0c681a;
    }
  }
  uVar7 = (ushort)((int)(short)(ushort)bRam00f434 * (int)(short)uRam00f43e);
  MDC = MDC | 0x10;
  if ((int)(short)(ushort)bRam00f434 * (int)(short)uRam00f43e < 0) {
    if (uVar7 == 0xd800 ||
        (short)(uVar7 + 0x2800) < 0 !=
        (-1 < (short)uVar7 && (short)(uVar7 + 0x2800) < 0 != (short)uVar7 < 0)) {
      uVar7 = 0xd800;
    }
  }
  else if (0x2800 < uVar7) {
    uVar7 = 0x2800;
  }
LAB_0c681a:
  uVar4 = MDC;
  uRam00f45a = _throttle_pos_fb;
  uVar7 = ((short)uVar7 >> 1) + sRam00f456;
  if ((short)uVar7 < 0) {
    uRam00fd68 = uRam00fd68 & 0xfff7;
    _servo_pwm_duty = (ushort)((uint)bRam00f436 * (uint)-uVar7);
    if (0xffff < (uint)bRam00f436 * (uint)-uVar7) {
      _servo_pwm_duty = 0xffff;
    }
    P7 = P7 & 0xff00 | P7 & 0xff00 | 0x84;
  }
  else {
    uRam00fd68 = uRam00fd68 | 8;
    _servo_pwm_duty = (ushort)((uint)bRam00f436 * (uint)uVar7);
    if (0xffff < (uint)bRam00f436 * (uint)uVar7) {
      _servo_pwm_duty = 0xffff;
    }
    P7 = P7 & 0xff00 | P7 & 0xff00 | 0x84;
  }
  iVar3 = (uint)_servo_pwm_duty * 0x2711;
  MDL = (short)iVar3;
  MDH = (short)((uint)iVar3 >> 0x10);
  MDC = MDC | 0x10;
  PW2 = MDH;
  PT2 = 9999;
  cRam00f438 = cRam00f438 + -1;
  if (cRam00f438 < '\0') {
    iVar3 = (int)(short)(ushort)bRam00f437 * (int)(short)_servo_pos_error;
    MDL = (ushort)iVar3;
    MDH = (short)((uint)iVar3 >> 0x10);
    MDC = uVar4 | 0x10;
    if (iVar3 == (short)MDL) {
      if (-1 < iVar3) {
        uRam00f452 = MDL >> 3;
        uRam00f450 = MDL << 0xd;
      }
      else {
        uRam00f452 = MDL >> 3 | 0xe000;
        uRam00f450 = MDL << 0xd;
      }
    }
    else {
      if (-1 < iVar3) {
        uRam00f452 = 0x1000;
      }
      else {
        uRam00f452 = 0xf000;
      }
      uRam00f450 = 0;
    }
    sRam00f454 = uRam00f44c + uRam00f450;
    sRam00f456 = sRam00f44e + uRam00f43c + uRam00f452 +
                 (ushort)(uRam00f44c + uRam00f450 < uRam00f44c ||
                         uRam00f44c + uRam00f450 < uRam00f450);
    cRam00f438 = 2;
    return;
  }
  if (cRam00f438 == '\0') {
    uVar7 = _servo_pos_error;
    if ((short)_servo_pos_error < 0) {
      uVar7 = -_servo_pos_error;
    }
    uVar5 = uVar7 >> 3;
    if (0x1f < uVar5) {
      uVar5 = 0x1f;
    }
    if ((short)(_throttle_pos_fb - (uRam302cca >> 4)) < 0 ==
        ((short)_throttle_pos_fb < 0 &&
        (short)(_throttle_pos_fb - (uRam302cca >> 4)) < 0 != (short)_throttle_pos_fb < 0)) {
      bRam00f437 = bRam014635;
      bRam00f434 = bRam014590;
      bRam00f435 = *(byte *)((uint3)uVar5 + 0x14595);
    }
    else if ((uRam00fd70 & 2) == 0) {
      bRam00f437 = bRam014639;
      bRam00f435 = *(byte *)((uint3)uVar5 + 0x14615);
      bRam00f434 = bRam014594;
    }
    else if ((uRam00fd68 & 2) == 0) {
      uVar2 = sRam016eba >> 4;
      if (uVar7 != uVar2 &&
          (short)(uVar7 - uVar2) < 0 ==
          ((short)uVar7 < 0 != (short)uVar2 < 0 && (short)(uVar7 - uVar2) < 0 != (short)uVar7 < 0))
      {
        bRam00f437 = bRam014636;
        bRam00f435 = *(byte *)((uint3)uVar5 + 0x145b5);
        bRam00f434 = bRam014591;
      }
    }
    else {
      sVar6 = sRam00f444;
      if (sRam00f444 < 0) {
        sVar6 = -sRam00f444;
      }
      if (sVar6 == sRam016eba ||
          sVar6 - sRam016eba < 0 !=
          (sVar6 < 0 != sRam016eba < 0 && sVar6 - sRam016eba < 0 != sVar6 < 0)) {
        if (sVar6 == sRam016ebc ||
            sVar6 - sRam016ebc < 0 !=
            (sVar6 < 0 != sRam016ebc < 0 && sVar6 - sRam016ebc < 0 != sVar6 < 0)) {
          bRam00f437 = bRam014638;
          bRam00f435 = *(byte *)((uint3)uVar5 + 0x145f5);
          bRam00f434 = bRam014593;
        }
        else {
          bRam00f437 = bRam014637;
          bRam00f435 = *(byte *)((uint3)uVar5 + 0x145d5);
          bRam00f434 = bRam014592;
        }
      }
      else {
        bRam00f437 = bRam014636;
        bRam00f435 = *(byte *)((uint3)uVar5 + 0x145b5);
        bRam00f434 = bRam014591;
      }
    }
    iVar3 = (int)(short)((ushort)bRam00f435 << 7) * (int)(short)(_servo_pos_error << 2);
    MDL = (ushort)iVar3;
    MDH = (short)((uint)iVar3 >> 0x10);
    MDC = uVar4 | 0x10;
    bVar1 = uRam00f44c + MDL < uRam00f44c;
    uVar7 = uRam00f44c + MDL;
    uRam00f44c = uRam00f44c + MDL;
    sRam00f44e = sRam00f44e + MDH + (ushort)(bVar1 || uVar7 < MDL);
    sVar6 = -sRam00f43a;
    if (sVar6 - sRam00f44e < 0 ==
        (sVar6 < 0 != sRam00f44e < 0 && sVar6 - sRam00f44e < 0 != sVar6 < 0)) {
      uRam00f44c = 0;
      sRam00f44e = sVar6;
    }
    if (sRam00f43a == sRam00f44e ||
        sRam00f43a - sRam00f44e < 0 !=
        (sRam00f43a < 0 != sRam00f44e < 0 && sRam00f43a - sRam00f44e < 0 != sRam00f43a < 0)) {
      sRam00f44e = sRam00f43a;
      uRam00f44c = 0;
    }
    return;
  }
  if (((uRam00fd66 & 0x8000) != 0) && (cRam01458d != '\0')) {
    if ((uRam00fd68 & 1) == 0) {
      if ((((short)_servo_pos_error < 1) && (-1 < (short)uRam00f458)) ||
         ((-1 < (short)_servo_pos_error && ((short)uRam00f458 < 1)))) {
        uRam00fd66 = uRam00fd66 & 0x7fff;
      }
    }
    else {
      uRam00f45c = _throttle_pos_fb;
      uRam00fd66 = uRam00fd66 & 0xdfff;
      uRam00fd68 = uRam00fd68 & 0xfffe;
    }
    if ((uRam00fd68 & 0x100) == 0) {
      sVar6 = _throttle_pos_fb - uRam00f45c;
      if (_throttle_pos_fb < uRam00f45c) {
        sVar6 = -sVar6;
      }
      if ((sVar6 != sRam016ef0 &&
           sVar6 - sRam016ef0 < 0 ==
           (sVar6 < 0 != sRam016ef0 < 0 && sVar6 - sRam016ef0 < 0 != sVar6 < 0)) &&
         ((uRam00fd66 & 0x2000) == 0)) {
        sRam302c94 = uRam00f43c;
        uRam00fd66 = uRam00fd66 | 0x2000;
      }
    }
    if ((uRam00fd66 & 0x8000) == 0) {
      uRam00f43c = 0;
    }
    else {
      iVar3 = (int)(short)((ushort)bRam01458f << 7) * (int)(short)_servo_pos_error;
      uRam00f43c = ((short)((uint)iVar3 >> 0x10) << 2 | (ushort)iVar3 >> 0xe) + uRam00f43c;
      if ((short)uRam00f43c < 0) {
        if ((short)(uRam00f43c + 0x200) < 0 !=
            (-1 < (short)uRam00f43c && (short)(uRam00f43c + 0x200) < 0 != (short)uRam00f43c < 0)) {
          uRam00f43c = 0xfe00;
        }
      }
      else if (0x200 < uRam00f43c) {
        uRam00f43c = 0x200;
      }
    }
    MDH = (short)((uint)iVar3 >> 0x10);
    MDL = (ushort)iVar3;
    MDC = uVar4 | 0x10;
    uRam00f458 = _servo_pos_error;
    return;
  }
  return;
}


// ================= torque_reserve_request @ 05369c =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CONTROL: torque-reserve (MDRES-type) builder, sub_B81C slot: idle reserve MRESLL 0x18637<<6 (ramp
   byte_1854D, timer TVRESLL 0x1EFD0, gates CWLLDE 0x1854C.0 / DNLLRESW 0x1EFC2 vs word_3024F8 /
   vfzg_class byte_3015D8 vs LIVFZDE 0x18632) + cat-heat/warmup reserve from KFMRES byte-map bank
   0x18551/69/81/99/B1/C9/E1 (2-D via sub_4210C, axes word_30197E/word_301990) capped MRESKH 0x1EFCC
   when word_FD46.9 + components word_3024DC (map 0x18608) / word_3024D4 (byte_18638) with
   per-component ramp-downs -> final min vs map 0x185FE(word_3019F0) -> word_3024D6 [C mechanism;
   MDRES identity I] */

void torque_reserve_request(void)

{
  bool bVar1;
  char cVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  
  if ((bRam01854c & 1) == 0) {
    if (sRam3024f8 == sRam01efc2 ||
        sRam3024f8 - sRam01efc2 < 0 !=
        (sRam3024f8 < 0 != sRam01efc2 < 0 && sRam3024f8 - sRam01efc2 < 0 != sRam3024f8 < 0)) {
      PSW = PSW & 0xffbf;
    }
    else {
      PSW = PSW | 0x40;
    }
  }
  else {
    cVar2 = func_0x041ae2(0x5f1,6,(short)catheat_mode);
    if ((cVar2 == cRam301658 ||
         (char)(cVar2 - cRam301658) < '\0' !=
         (cVar2 < '\0' != cRam301658 < '\0' && (char)(cVar2 - cRam301658) < '\0' != cVar2 < '\0'))
       || (bRam018632 <= vfzg_class)) {
      PSW = PSW & 0xffbf;
    }
    else {
      PSW = PSW | 0x40;
    }
  }
  if (((bRam30135c & 4) == 0) || ((PSW & 0x40) == 0)) {
    if (_mres_ll_timer == 0) {
      bRam30135c = bRam30135c & 0xfe;
    }
    else {
      _mres_ll_timer = _mres_ll_timer + -1;
    }
  }
  else {
    bRam30135c = bRam30135c | 1;
    uRam01e4de = uRam01efd0;
  }
  if ((bRam30135c & 1) == 0) {
    bRam301356 = bRam301356 & 0xfe;
    if (((bRam30135c & 4) != 0) && (_mres_idle = uRam01a4d0 - bRam01854d, uRam01a4d0 < bRam01854d))
    {
      _mres_idle = 0;
    }
  }
  else {
    if ((bRam01854c & 2) == 0) {
      bRam301356 = bRam301356 & 0xfe;
    }
    else {
      bRam301356 = bRam301356 | 1;
    }
    _mres_idle = (ushort)bRam018637 << 6;
  }
  if ((bRam018633 < bRam30175a) || (bRam30175a < bRam018635)) {
    bRam301357 = bRam301357 & 0xfe;
  }
  else {
    bRam301357 = bRam301357 | 1;
  }
  if ((bRam018634 < bRam30175a) || (bRam30175a < bRam018636)) {
    bRam301356 = bRam301356 & 0xfd;
  }
  else {
    bRam301356 = bRam301356 | 2;
  }
  if (((bRam301356 & 2) == 0) || (bRam01863c <= vfzg_class)) {
    uVar5 = 0;
  }
  else {
    cRam301355 = bRam30175a - bRam30135b;
    if (bRam30175a < bRam30135b) {
      if (cRam301355 >= '\0') {
        cRam301355 = -0x80;
      }
    }
    else if (cRam301355 < '\0') {
      cRam301355 = '\x7f';
    }
    cRam301355 = cRam301355 >> 1;
    uVar5 = func_0x042442(uRam01efc4,0x2fc5,7,0x2fc8,7,(short)cRam301355);
    uVar5 = uVar5 & 0xff;
  }
  if (uRam3024d2 >> 6 < uVar5) {
    uVar5 = func_0x042442(uRam01efc4,0x2fc5,7,0x2fc8,7,(short)cRam301355);
    uRam3024d2 = (uVar5 & 0xff) << 6;
    bRam30135a = 0;
  }
  else if (bRam30135a < bRam01863b) {
    bRam30135a = bRam30135a + 1;
  }
  else if ((uRam3024d2 != 0) &&
          (bVar1 = uRam3024d2 < bRam01854f, uRam3024d2 = uRam3024d2 - bRam01854f, bVar1)) {
    uRam3024d2 = 0;
  }
  bRam30135b = bRam30175a;
  if ((_flags_start_phase & 0x4000) == 0) {
    if (bRam301359 < bRam01863a) {
      bRam301359 = bRam301359 + 1;
    }
    else if ((uRam3024dc != 0) &&
            (bVar1 = uRam3024dc < bRam01854e, uRam3024dc = uRam3024dc - bRam01854e, bVar1)) {
      uRam3024dc = 0;
    }
  }
  else {
    uVar5 = me7_lookup_1d_byte(0x608,6,rpmclass_oppoint);
    uRam3024dc = (uVar5 & 0xff) << 6;
    bRam301359 = 0;
  }
  if ((bRam30127c & 0x80) == 0) {
    if ((uRam3024d4 != 0) &&
       (bVar1 = uRam3024d4 < bRam018550, uRam3024d4 = uRam3024d4 - bRam018550, bVar1)) {
      uRam3024d4 = 0;
    }
  }
  else {
    uRam3024d4 = (ushort)bRam018638 << 6;
  }
  uRam3024da = 0;
  uRam3024d8 = 0;
  if (((uRam00fd1c & 0x2000) == 0) &&
     ((((bRam301357 & 1) != 0 || ((bRam01854b & 1) != 0)) && (vfzg_class < bRam01863c)))) {
    bRam301356 = bRam301356 | 4;
  }
  else {
    bRam301356 = bRam301356 & 0xfb;
  }
  if ((uRam00fd1c & 0x2000) == 0) {
    uVar5 = 0;
  }
  else {
    if ((((bRam301357 & 1) == 0) || (bRam01863c <= vfzg_class)) && ((bRam301366 & 4) == 0)) {
      if ((uRam00fd26 & 0x400) == 0) {
        if ((uRam00fd3a & 0x8000) == 0) {
          uVar5 = func_0x04210c(0x551,6,0xf3a,5,uRam301990,uRam30197e);
          uVar5 = uVar5 & 0xff;
        }
        else {
          uVar5 = func_0x04210c(0x569,6,0xf3a,5,uRam301990,uRam30197e);
          uVar5 = uVar5 & 0xff;
        }
      }
      else {
        uVar5 = func_0x04210c(0x5c9,6,0xf3a,5,uRam301990,uRam30197e);
        uVar5 = uVar5 & 0xff;
      }
    }
    else {
      uVar4 = func_0x04210c(0x581,6,0xf3a,5,uRam301990,uRam30197e);
      uVar4 = uVar4 & 0xff;
      uVar3 = uRam3024d2 >> 6;
      uVar5 = uVar3 + uVar4;
      if (uVar3 + uVar4 < uVar3 || uVar3 + uVar4 < uVar4) {
        uVar5 = 0xffff;
      }
    }
    uVar3 = func_0x04210c(0x5e1,6,0xf3a,5,uRam3019d2,uRam30197e);
    uVar5 = uVar5 + (uVar3 & 0xff);
    if (uVar5 < 0x401) {
      _mres_catheat_base = uVar5 * 0x40;
    }
    else {
      _mres_catheat_base = 0xffff;
    }
    uVar5 = uRam3024dc + _mres_catheat_base;
    if (uRam3024dc + _mres_catheat_base < uRam3024dc ||
        uRam3024dc + _mres_catheat_base < _mres_catheat_base) {
      uVar5 = 0xffff;
    }
    uVar3 = me7_lookup_1d_byte(0x61d,6,uRam304db0,uVar5);
    uVar4 = (uVar3 & 0xff) * 0x40;
    uVar3 = uVar4 + uVar5;
    if (uVar4 + uVar5 < uVar4 || uVar4 + uVar5 < uVar5) {
      uVar3 = 0xffff;
    }
    uVar5 = uVar3;
    if (((_flags_idle_state & 0x200) != 0) && (uVar5 = uRam01efcc, uVar3 <= uRam01efcc)) {
      uVar5 = uVar3;
    }
    uVar3 = _mres_idle + uVar5;
    if (_mres_idle + uVar5 < _mres_idle || _mres_idle + uVar5 < uVar5) {
      uVar3 = 0xffff;
    }
    uVar5 = uRam3024d4 + uVar3;
    if (uRam3024d4 + uVar3 < uRam3024d4 || uRam3024d4 + uVar3 < uVar3) {
      uVar5 = 0xffff;
    }
    if (bRam30157d < bRam30136a) {
      if (bRam301369 < bRam30136a) {
        uVar3 = (ushort)bRam30136a << 8;
      }
      else {
        uVar3 = (ushort)bRam301369 << 8;
      }
    }
    else if (bRam301369 < bRam30157d) {
      uVar3 = (ushort)bRam30157d << 8;
    }
    else {
      uVar3 = (ushort)bRam301369 << 8;
    }
    if (uVar5 <= uVar3) {
      uVar5 = uVar3;
    }
    uVar3 = uRam3024da;
    if (uRam3024da <= uVar5) {
      uVar3 = uVar5;
    }
    uVar4 = uVar3;
    if (((bRam301276 & 8) != 0) && (uVar4 = uRam01efce, uRam01efce <= uVar3)) {
      uVar4 = uVar3;
    }
    uVar5 = uVar4;
    if ((_flags_idle_state & 0x200) != 0) {
      uVar5 = func_0x04210c(0x599,6,0x2838,4,uRam3024c4,uRam3019de);
      uVar5 = (uVar5 & 0xff) * 0x40;
      if (uVar4 <= uVar5) {
        uVar5 = uVar4;
      }
    }
  }
  if ((bRam301356 & 4) == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = func_0x04210c(0x5b1,6,0xf3a,5,uRam301990,uRam30197e);
    uVar3 = (uVar3 & 0xff) << 6;
  }
  uVar4 = uRam3024d2 + uVar3;
  if (uRam3024d2 + uVar3 < uRam3024d2 || uRam3024d2 + uVar3 < uVar3) {
    uVar4 = 0xffff;
  }
  if ((bRam01854b & 2) == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = (ushort)bRam301369 << 8;
  }
  if (uVar4 < uVar5) {
    uVar4 = uVar5;
    if (uVar5 <= uVar3) {
      uVar4 = uVar3;
    }
  }
  else if (uVar4 <= uVar3) {
    uVar4 = uVar3;
  }
  uVar5 = uVar4;
  if (((uRam00fd26 & 0x400) != 0) &&
     (uVar5 = (ushort)bRam30136b * 0x100, (ushort)bRam30136b * 0x100 <= uVar4)) {
    uVar5 = uVar4;
  }
  uVar3 = uRam3024d8;
  if (uRam3024d8 <= uVar5) {
    uVar3 = uVar5;
  }
  uVar5 = func_0x042020(0x5fe,6,uRam3019f0);
  _mres_request = (uVar5 & 0xff) * 0x40;
  if (uVar3 <= _mres_request) {
    _mres_request = uVar3;
  }
  return;
}


// ================= can_rx_msg_handler_bank @ 056e00 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* COMMS: 2nd half of can_rx_signal_unpack (sub_5637C 0x56982): jump-table handler bank
   (index<=0x62, table 0xC1E2, 0x56E04/0x56E16) - each case polls a cal-held (flag-ptr,mask) pair
   0x11A50-0x11B0C, extracts via descriptor readers sub_E3A86/sub_E3ACE/sub_E3B34/sub_E40DE into
   byte_3014xx/word_3025xx mirrors, clears the flag; msg-timeout counter byte_30143D vs byte_13803;
   codeword byte_137FF; handshake bits via ptrs word_11B0C/word_11B5C [C] */

void can_rx_msg_handler_bank(undefined1 param_1)

{
  int iVar1;
  undefined4 uVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;
  ushort uVar6;
  undefined2 uStack_6;
  undefined2 uStack_4;
  char acStack_2 [2];
  
  iVar1 = CONCAT22(MDH,MDL);
  uVar2 = uRam30255a;
  switch(param_1) {
  case 0:
  case 5:
  case 10:
  case 0xf:
  case 0x14:
  case 0x19:
  case 0x1e:
  case 0x23:
  case 0x28:
  case 0x2d:
  case 0x32:
  case 0x37:
  case 0x3c:
  case 0x41:
  case 0x46:
  case 0x4b:
  case 0x50:
  case 0x55:
  case 0x5a:
  case 0x5f:
    iVar1 = CONCAT22(MDH,MDL);
    if ((_flags_diag_cfg_a & 0x10) != 0) {
      uVar6 = func_0x0e3a86(0x464);
      uRam00fd28 = uRam00fd28 & 0xfffe | uVar6 & 1;
      uVar6 = func_0x0e3a86(0x464);
      uRam00fd26 = uRam00fd26 & 0x7fff | ((uVar6 & 2) >> 1) << 0xf;
      iVar1 = CONCAT22(MDH,MDL);
      uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
    }
    break;
  case 1:
  case 0xb:
  case 0x15:
  case 0x1f:
  case 0x29:
  case 0x33:
  case 0x3d:
  case 0x47:
  case 0x51:
  case 0x5b:
    iVar1 = CONCAT22(MDH,MDL);
    if (((_flags_diag_cfg_a & 0x10) != 0) &&
       (bVar4 = *(byte *)((uint3)uRam011ab0 + 0x10000) & bRam011ab2, iVar1 = CONCAT22(MDH,MDL),
       bVar4 != 0)) {
      uRam30142c = func_0x0e3a86(0x3ae,bVar4);
      *(byte *)((uint3)uRam011ab0 + 0x10000) = *(byte *)((uint3)uRam011ab0 + 0x10000) & ~bRam011ab2;
      iVar1 = CONCAT22(MDH,MDL);
      uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
    }
    break;
  case 2:
  case 0xc:
  case 0x16:
  case 0x20:
  case 0x2a:
  case 0x34:
  case 0x3e:
  case 0x48:
  case 0x52:
  case 0x5c:
    iVar1 = CONCAT22(MDH,MDL);
    if ((_flags_diag_cfg_a & 0x10) != 0) {
      if ((*(byte *)((uint3)uRam011ac8 + 0x10000) & bRam011aca) == 0) {
        uRam30256c = uRam30256c & 0xffbf;
        iVar1 = CONCAT22(MDH,MDL);
      }
      else {
        uRam30256c = uRam30256c | 0x40;
        *(byte *)((uint3)uRam011ac8 + 0x10000) =
             *(byte *)((uint3)uRam011ac8 + 0x10000) & ~bRam011aca;
        uRam30142b = func_0x0e3a86(0x3f4);
        uRam301430 = func_0x0e3a86(0x402);
        cVar5 = func_0x0e3a86(0x48e);
        if (cVar5 == '\0') {
          uRam30256a = uRam30256a & 0xdfff;
          iVar1 = CONCAT22(MDH,MDL);
          uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
        }
        else {
          uRam30256a = uRam30256a | 0x2000;
          iVar1 = CONCAT22(MDH,MDL);
          uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
        }
      }
    }
    break;
  case 3:
  case 0xd:
  case 0x17:
  case 0x21:
  case 0x2b:
  case 0x35:
  case 0x3f:
  case 0x49:
  case 0x53:
  case 0x5d:
    cVar5 = func_0x0e3a86(0x4e2);
    if (cVar5 == '\0') {
      uRam30256c = uRam30256c & 0xdfff;
    }
    else {
      uRam30256c = uRam30256c | 0x2000;
    }
    uRam30137f = func_0x0e3a86(0x322);
    iVar1 = CONCAT22(MDH,MDL);
    uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
    break;
  case 4:
  case 0xe:
  case 0x18:
  case 0x22:
  case 0x2c:
  case 0x36:
  case 0x40:
  case 0x4a:
  case 0x54:
  case 0x5e:
    if (((_flags_diag_cfg_a & 0x10) == 0) ||
       ((*(byte *)((uint3)uRam011aec + 0x10000) & bRam011aee) == 0)) {
      uRam30256e = uRam30256e & 0xfbff;
      iVar1 = CONCAT22(MDH,MDL);
    }
    else {
      uRam30256e = uRam30256e | 0x400;
      *(byte *)((uint3)uRam011aec + 0x10000) = *(byte *)((uint3)uRam011aec + 0x10000) & ~bRam011aee;
      uRam301445 = func_0x0e3a86(0x640);
      uRam301439 = func_0x0e3a86(0x64e);
      iVar1 = CONCAT22(MDH,MDL);
      uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
    }
    break;
  case 7:
  case 0x1b:
  case 0x2f:
  case 0x43:
  case 0x57:
    if ((uRam00fd28 & 4) != 0) {
      *(byte *)((uint3)uRam011b0c + 0x10000) = *(byte *)((uint3)uRam011b0c + 0x10000) | 2;
      *(byte *)((uint3)uRam011b5c + 0x10000) = *(byte *)((uint3)uRam011b5c + 0x10000) | 2;
      uRam00fd28 = uRam00fd28 & 0xfffb;
      bRam30143d = 0;
      uRam30256c = uRam30256c & 0xffcf;
    }
    func_0x0e3b34(0x410,acStack_2,1,0);
    if (acStack_2[0] == '\x01') {
      func_0x0e3b34(0x410,0x8252,7,1);
      if (bRam30143d < bRam013803) {
        sRam302596 = CONCAT11(bRam300257,bRam300258);
        sRam302588 = func_0x0e3ace(0x41e);
        sRam302586 = -1 - sRam302588;
        if (sRam302596 == sRam302588) {
          uRam30256c = uRam30256c | 0x10;
        }
        if (sRam302596 == sRam302586) {
          uRam30256c = uRam30256c | 0x20;
        }
      }
      uStack_4 = CONCAT11(bRam300253,uRam300254);
      uStack_6 = CONCAT11(uRam300255,bRam300256);
      if (uStack_4 + 1 == (ushort)(uStack_6 != -1) && uStack_6 == -1) {
        sRam30255e = -1;
        sRam302560 = -1;
        sRam30259c = -1;
        sRam30259a = -1;
        uRam30255a = 0xffffffff;
      }
      else {
        sRam30255e = uStack_6;
        sRam302560 = uStack_4;
        sRam30259c = uStack_6;
        sRam30259a = uStack_4;
        uRam30255a = func_0x0e40de();
      }
      if ((bRam300252 & 0x10) == 0) {
        uRam30256a = uRam30256a & 0xf7ff;
      }
      else {
        uRam30256a = uRam30256a | 0x800;
      }
      bRam301424 = bRam300252 & 0xf;
    }
    else if (acStack_2[0] == '\x02') {
      func_0x0e3b34(0x410,0x8252,7,1);
      uStack_4 = bRam300256 & 0xff0f;
      uStack_6 = CONCAT11(bRam300257,bRam300258);
      uRam302562 = uStack_6;
      uRam302564 = uStack_4;
      uRam3025a4 = uStack_6;
      uRam3025a2 = uStack_4;
      uRam301444 = uRam300255;
      uRam301435 = (undefined1)((short)((bRam300253 & 0xf) & 0xc) >> 2);
      uStack_6 = CONCAT11(bRam300253,uRam300254) & 0x3ff;
      if (uStack_6 < 0x200) {
        uRam3025a6 = uStack_6;
      }
      else {
        uRam3025a6 = uStack_6 | 0xfc00;
      }
      bRam301440 = bRam300252;
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
    }
    else if (acStack_2[0] == '\x05') {
      func_0x0e3b34(0x410,0x8252,7,1);
      uRam3025a8 = (bRam300257 & 0xf) << 8 | (ushort)bRam300258;
      uRam30257a = CONCAT11(uRam300255,bRam300256);
      uRam30257c = CONCAT11(bRam300253,uRam300254);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
    }
    else if (acStack_2[0] == '\x10') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 1;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 8) < 0);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam301381 != -1)) {
        cRam301381 = cRam301381 + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == '\x11') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 8;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 0xf) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam301382 != -1)) {
        cRam301382 = cRam301382 + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == '\x12') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 0xf;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 0x16) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam301383 != -1)) {
        cRam301383 = cRam301383 + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == '\x13') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 0x16;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 0x1d) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam301384 != -1)) {
        cRam301384 = cRam301384 + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == '\x14') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 0x1d;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 0x24) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam301385 != -1)) {
        cRam301385 = cRam301385 + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == '\x15') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 0x24;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 0x2b) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam301386 != -1)) {
        cRam301386 = cRam301386 + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == '\x16') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 0x2b;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 0x32) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam301387 != -1)) {
        cRam301387 = cRam301387 + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == '\x17') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 0x32;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 0x39) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam301388 != -1)) {
        cRam301388 = cRam301388 + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == '\x18') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 0x39;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 0x40) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam301389 != -1)) {
        cRam301389 = cRam301389 + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == '\x19') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 0x40;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 0x47) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam30138a != -1)) {
        cRam30138a = cRam30138a + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == '\x1a') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 0x47;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 0x4e) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam30138b != -1)) {
        cRam30138b = cRam30138b + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == '\x1b') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 0x4e;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 0x55) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam30138c != -1)) {
        cRam30138c = cRam30138c + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == '\x1c') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 0x55;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 0x5c) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam30138d != -1)) {
        cRam30138d = cRam30138d + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == '\x1d') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 0x5c;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 99) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam30138e != -1)) {
        cRam30138e = cRam30138e + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == '\x1e') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 99;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 0x6a) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam30138f != -1)) {
        cRam30138f = cRam30138f + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == '\x1f') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 0x6a;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 0x71) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam301390 != -1)) {
        cRam301390 = cRam301390 + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == ' ') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 0x71;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 0x78) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam301391 != -1)) {
        cRam301391 = cRam301391 + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == '!') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 0x78;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 0x7f) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam301392 != -1)) {
        cRam301392 = cRam301392 + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == '\"') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 0x7f;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 0x86) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam301393 != -1)) {
        cRam301393 = cRam301393 + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else if (acStack_2[0] == '#') {
      func_0x0e3b34(0x410,0x8252,7,1);
      bVar4 = 0;
      bVar3 = 0x86;
      do {
        *(undefined1 *)((uint3)bVar3 + 0x301395) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        bVar4 = bVar4 + 1;
        bVar3 = bVar3 + 1;
      } while ((short)(bVar3 - 0x8d) < 0);
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (((*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0) &&
         (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), cRam301394 != -1)) {
        cRam301394 = cRam301394 + '\x01';
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    else {
      uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      if (acStack_2[0] == -1) {
        func_0x0e3b34(0x410,0x8252,7,1);
        uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
        if (((bRam300252 == 0x7a) &&
            (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a),
            (*(byte *)((uint3)uRam011afe + 0x10000) & bRam011b00) != 0)) &&
           (uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a), (bRam300259 & 0x40) == 0
           )) {
          bRam300259 = bRam300259 | 8;
          uStack_4 = (ushort)bRam300253;
          uStack_6 = CONCAT11(uRam300254,uRam300255);
          uRam302552 = uStack_6;
          uRam302554 = uStack_4;
          uRam302572 = uStack_6;
          uRam302570 = uStack_4;
          uStack_4 = (ushort)bRam300256;
          uStack_6 = CONCAT11(bRam300257,bRam300258);
          uRam302556 = uStack_6;
          uRam302558 = uStack_4;
          uRam302576 = uStack_6;
          uRam302574 = uStack_4;
          uRam30255a = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
        }
      }
    }
    *(byte *)((uint3)uRam011afe + 0x10000) = *(byte *)((uint3)uRam011afe + 0x10000) & ~bRam011b00;
    if (cRam0137ff == '\0') {
      uRam30256c = uRam30256c | 0x30;
    }
    iVar1 = CONCAT22(MDH,MDL);
    uVar2 = uRam30255a;
    if ((bRam013803 <= bRam30143d) &&
       ((((uRam30256c & 0x10) == 0 || (iVar1 = CONCAT22(MDH,MDL), (uRam30256c & 0x20) == 0)) &&
        (iVar1 = CONCAT22(MDH,MDL), (uRam303b34 & 1) == 0)))) {
      *(byte *)((uint3)uRam011b0c + 0x10000) = *(byte *)((uint3)uRam011b0c + 0x10000) & 0xfd;
      *(byte *)((uint3)uRam011b5c + 0x10000) = *(byte *)((uint3)uRam011b5c + 0x10000) & 0xfd;
      bRam300259 = bRam300259 | 2;
      iVar1 = CONCAT22(MDH,MDL);
      uVar2 = uRam30255a;
    }
    break;
  case 8:
  case 0x12:
  case 0x1c:
  case 0x26:
  case 0x30:
  case 0x3a:
  case 0x44:
  case 0x4e:
  case 0x58:
  case 0x62:
    if ((*(byte *)((uint3)uRam011a50 + 0x10000) & bRam011a52) == 0) {
      uRam30256a = uRam30256a & 0xfeff;
    }
    else {
      uRam30256a = uRam30256a | 0x100;
      *(byte *)((uint3)uRam011a50 + 0x10000) = *(byte *)((uint3)uRam011a50 + 0x10000) & ~bRam011a52;
      uRam301378 = func_0x0e3a86(0x2b2);
    }
    uRam301423 = func_0x0e3a86(0x3a0);
    cVar5 = func_0x0e3a86(0x4aa);
    if (cVar5 == '\0') {
      uRam30256c = uRam30256c & 0xf7ff;
      iVar1 = CONCAT22(MDH,MDL);
      uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
    }
    else {
      uRam30256c = uRam30256c | 0x800;
      iVar1 = CONCAT22(MDH,MDL);
      uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
    }
    break;
  case 9:
    if (((_flags_diag_cfg_a & 0x10) == 0) ||
       ((*(byte *)((uint3)uRam011abc + 0x10000) & bRam011abe) == 0)) {
      uRam30256a = uRam30256a & 0xfdff;
      iVar1 = CONCAT22(MDH,MDL);
    }
    else {
      uRam30256a = uRam30256a | 0x200;
      *(byte *)((uint3)uRam011abc + 0x10000) = *(byte *)((uint3)uRam011abc + 0x10000) & ~bRam011abe;
      uRam301442 = func_0x0e3a86(0x3ca);
      uRam301436 = func_0x0e3a86(0x3d8);
      iVar1 = CONCAT22(MDH,MDL);
      uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
    }
    break;
  case 0x11:
  case 0x25:
  case 0x39:
  case 0x4d:
  case 0x61:
    func_0x0e3b34(0x616,acStack_2,1,0);
    if (acStack_2[0] == '\x10') {
      if ((bRam30318f & 8) == 0) {
        func_0x0e3b34(0x616,0x8252,7,1);
        bRam30318f = bRam30318f | 1;
        bRam303198 = bRam300256;
        bRam303199 = bRam300257;
        bRam30319a = bRam300258;
      }
    }
    else if (acStack_2[0] == '\x11') {
      if ((bRam30318f & 8) == 0) {
        func_0x0e3b34(0x616,0x8252,7,1);
        bRam30318f = bRam30318f | 2;
        uVar6 = 3;
        bVar4 = 0;
        do {
          *(undefined1 *)((uint3)uVar6 + 0x303198) = *(undefined1 *)((uint3)bVar4 + 0x300252);
          uVar6 = (ushort)(byte)((char)uVar6 + 1);
          bVar4 = bVar4 + 1;
        } while (bVar4 < 7);
      }
    }
    else if ((acStack_2[0] == '\x12') && ((bRam30318f & 8) == 0)) {
      func_0x0e3b34(0x616,0x8252,7,1);
      bRam30318f = bRam30318f | 4;
      uVar6 = 10;
      bVar4 = 0;
      do {
        *(undefined1 *)((uint3)uVar6 + 0x303198) = *(undefined1 *)((uint3)bVar4 + 0x300252);
        uVar6 = (ushort)(byte)((char)uVar6 + 1);
        bVar4 = bVar4 + 1;
      } while (bVar4 < 7);
    }
    iVar1 = CONCAT22(MDH,MDL);
    uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
    if ((((bRam30318f & 1) != 0) &&
        (iVar1 = CONCAT22(MDH,MDL), uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a),
        (bRam30318f & 2) != 0)) &&
       (iVar1 = CONCAT22(MDH,MDL), uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a),
       (bRam30318f & 4) != 0)) {
      bRam30318f = bRam30318f | 8;
      iVar1 = CONCAT22(MDH,MDL);
      uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
    }
    break;
  case 0x13:
    if ((_flags_diag_cfg_a & 0x10) == 0) {
      uRam30256e = uRam30256e | 0x1080;
    }
    else if ((*(byte *)((uint3)uRam011ad4 + 0x10000) & bRam011ad6) == 0) {
      uRam30256e = uRam30256e & 0xef7f;
    }
    else {
      uRam30256e = uRam30256e | 0x1080;
      *(byte *)((uint3)uRam011ad4 + 0x10000) = *(byte *)((uint3)uRam011ad4 + 0x10000) & ~bRam011ad6;
      cVar5 = func_0x0e3a86(0x5a6);
      if (cVar5 == '\0') {
        uRam30256c = uRam30256c & 0xfffe;
      }
      else {
        if (cVar5 != '\x01') {
          if (cVar5 == '\x02') {
            uRam30256c = uRam30256c & 0xfffe;
          }
          else {
            if (cVar5 != '\x03') goto code_r0x057bba;
            uRam30256c = uRam30256c | 1;
          }
          uRam30256a = uRam30256a | 0x80;
          goto code_r0x057bba;
        }
        uRam30256c = uRam30256c | 1;
      }
      uRam30256a = uRam30256a & 0xff7f;
    }
code_r0x057bba:
    if ((*(byte *)((uint3)uRam011a9e + 0x10000) & bRam011aa0) == 0) {
      uRam30256e = uRam30256e & 0xdfff;
      iVar1 = CONCAT22(MDH,MDL);
      uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
    }
    else {
      uRam30256e = uRam30256e | 0x2000;
      *(byte *)((uint3)uRam011a9e + 0x10000) = *(byte *)((uint3)uRam011a9e + 0x10000) & ~bRam011aa0;
      cVar5 = func_0x0e3a86(0x598);
      if (cVar5 == '\0') {
        uRam30256a = uRam30256a & 0xbfff;
        iVar1 = CONCAT22(MDH,MDL);
        uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
      else {
        uRam30256a = uRam30256a | 0x4000;
        iVar1 = CONCAT22(MDH,MDL);
        uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
      }
    }
    break;
  case 0x1d:
    cVar5 = func_0x0e3a86(0x480);
    if (cVar5 == '\0') {
      uRam30256a = uRam30256a & 0xfffb;
      iVar1 = CONCAT22(MDH,MDL);
      uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
    }
    else {
      uRam30256a = uRam30256a | 4;
      iVar1 = CONCAT22(MDH,MDL);
      uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
    }
    break;
  case 0x27:
    if ((*(byte *)((uint3)uRam011a6e + 0x10000) & bRam011a70) == 0) {
      uRam30256e = uRam30256e & 0xbfff;
    }
    else {
      uRam30256e = uRam30256e | 0x4000;
      uRam30143f = func_0x0e3a86(0x368);
      uRam301434 = func_0x0e3a86(0x376);
      uRam30143e = func_0x0e3a86(900);
      uRam301433 = func_0x0e3a86(0x392);
      *(byte *)((uint3)uRam011a6e + 0x10000) = *(byte *)((uint3)uRam011a6e + 0x10000) & ~bRam011a70;
    }
    uVar6 = func_0x0e3ace(0x49c);
    iVar1 = (uint)uVar6 * 0x741;
    MDC = MDC | 0x10;
    uRam3035d0 = (ushort)iVar1 >> 9 | (short)((uint)iVar1 >> 0x10) << 7;
    uVar2 = CONCAT22(uRam30255a._2_2_,(undefined2)uRam30255a);
  }
  uRam30255a._2_2_ = (undefined2)((uint)uVar2 >> 0x10);
  uRam30255a._0_2_ = (undefined2)uVar2;
  MDH = (undefined2)((uint)iVar1 >> 0x10);
  MDL = (undefined2)iVar1;
  return;
}


// ================= cruise_speed_governor @ 0ca5c6 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CONTROL: cruise-control-type vehicle-speed governor (sub_B81C chain, caller 0xCA4B8-region):
   state machine byte_300C1E 0..6 (jump table 0xD33E) off switch-edge bits word_FD0A.7-.10 (from
   debounce 0x3B4A2) -> set-speed word_302CF8 slewed at word_26B4E toward vfzg word_3029C6, clamp
   [word_300C3A,word_300C38], engage bands word_26B24/word_26B50; speed-corr word_302CD6 (maps
   0x26A7A/0x26B02 keyed vfzg, bands word_26B54/56/58); PI: gain map 0x26BE0 keyed set-speed
   (sub_41A68), ramp sub_42486 (word_26BAE, tbls 0x26BB0/0x26BC0), integrator sub_430DA state
   word_300C3E:40, 2-D map sub_43430 (z 0x6F6C-rel) -> torque request word_302CE4 (zero below
   word_26B7A) -> sub_CB61C region; supervised by diag_setpoint_follow_monitor [C mechanism;
   cruise/FGR identity I - no dict token] */

void cruise_speed_governor(void)

{
  bool bVar1;
  bool bVar2;
  short sVar3;
  ushort uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  short sVar9;
  ushort uVar10;
  undefined2 uVar11;
  ushort uVar12;
  short sVar13;
  ushort uVar14;
  ushort uVar15;
  short sVar16;
  int iVar17;
  ushort uStack_a;
  ushort uStack_8;
  
  iVar7 = CONCAT22(MDH,MDL);
  if (((uRam00fd0a & 0x80) == 0) || ((uRam00fd76 & 0x10) != 0)) {
    uRam00fd74 = uRam00fd74 & 0xfffb;
  }
  else {
    uRam00fd74 = uRam00fd74 | 4;
  }
  if (((uRam00fd0a & 0x80) == 0) && ((uRam00fd76 & 0x10) != 0)) {
    uRam00fd74 = uRam00fd74 | 2;
  }
  else {
    uRam00fd74 = uRam00fd74 & 0xfffd;
  }
  if ((uRam00fd0a & 0x80) == 0) {
    uRam018c1a = uRam01b98d;
    uRam00fd74 = uRam00fd74 & 0xfff7;
LAB_0ca628:
    uRam00fd74 = uRam00fd74 & 0xfffe;
  }
  else {
    if (cRam300c1a != '\0') {
      cRam300c1a = cRam300c1a + -1;
    }
    if ((cRam300c1a == '\0') && (cRam300c1c != '\0')) {
      uRam00fd74 = uRam00fd74 | 8;
    }
    else {
      uRam00fd74 = uRam00fd74 & 0xfff7;
    }
    if (cRam300c1a != '\0') goto LAB_0ca628;
    uRam00fd74 = uRam00fd74 | 1;
  }
  cRam300c1c = cRam300c1a;
  uVar15 = ((uRam00fd0a & 0x80) >> 7) << 4;
  if (((uRam00fd0a & 0x200) == 0) || ((uRam00fd76 & 0x20) != 0)) {
    uRam00fd74 = uRam00fd74 & 0xf7ff;
  }
  else {
    uRam00fd74 = uRam00fd74 | 0x800;
  }
  if (((uRam00fd0a & 0x200) == 0) && ((uRam00fd76 & 0x20) != 0)) {
    uRam00fd74 = uRam00fd74 | 0x400;
  }
  else {
    uRam00fd74 = uRam00fd74 & 0xfbff;
  }
  if ((uRam00fd0a & 0x200) == 0) {
    uRam018c1b = uRam01b98d;
    uRam00fd74 = uRam00fd74 & 0xefff;
LAB_0ca692:
    uRam00fd74 = uRam00fd74 & 0xfdff;
  }
  else {
    if (cRam300c1b != '\0') {
      cRam300c1b = cRam300c1b + -1;
    }
    if ((((uRam00fd0a & 0x200) == 0) || (cRam300c1b != '\0')) || (cRam300c1d == '\0')) {
      uRam00fd74 = uRam00fd74 & 0xefff;
    }
    else {
      uRam00fd74 = uRam00fd74 | 0x1000;
    }
    if (cRam300c1b != '\0') goto LAB_0ca692;
    uRam00fd74 = uRam00fd74 | 0x200;
  }
  cRam300c1d = cRam300c1b;
  uVar10 = ((uRam00fd0a & 0x200) >> 9) << 5;
  uVar14 = uRam00fd76 & 0xffcf | uVar15 | uVar10;
  iVar17 = _cruise_i_state_lo;
  if ((uRam00fd04 & 4) != 0) goto LAB_0cb3b8;
  if (((uRam00fd0a & 0x100) == 0) || ((uRam00fd76 & 4) != 0)) {
    uRam00fd74 = uRam00fd74 & 0xfeff;
  }
  else {
    uRam00fd74 = uRam00fd74 | 0x100;
  }
  uVar14 = ((uRam00fd0a & 0x100) >> 8) << 2;
  if (((uRam00fd0a & 0x400) == 0) || ((uRam00fd76 & 8) != 0)) {
    uRam00fd74 = uRam00fd74 & 0xdfff;
  }
  else {
    uRam00fd74 = uRam00fd74 | 0x2000;
  }
  uVar4 = ((uRam00fd0a & 0x400) >> 10) << 3;
  uVar12 = _cruise_set_speed - _vfzg_vehicle_speed;
  if (_cruise_set_speed < _vfzg_vehicle_speed) {
    uVar12 = 0;
  }
  if (uRam026b50 < uVar12) {
LAB_0ca6fc:
    uRam00fd76 = uRam00fd76 & 0xff43 | uVar15 | uVar10 | uVar14 | uVar4;
  }
  else {
    uVar12 = _vfzg_vehicle_speed - _cruise_set_speed;
    if (_vfzg_vehicle_speed < _cruise_set_speed) {
      uVar12 = 0;
    }
    if (uRam026b24 < uVar12) goto LAB_0ca6fc;
    uRam00fd76 = uRam00fd76 & 0xffc3 | uVar15 | uVar10 | uVar14 | uVar4 | 0x80;
  }
  if ((uRam00fd76 & 0x80) == 0) {
    uRam00fd74 = uRam00fd74 & 0xffbf;
LAB_0ca734:
    uRam00fd74 = uRam00fd74 & 0xffef;
  }
  else {
    if ((uRam302cfe < uRam016fdc) && (bRam301797 < bRam01b96b)) {
      uRam00fd74 = uRam00fd74 | 0x40;
    }
    else {
      uRam00fd74 = uRam00fd74 & 0xffbf;
    }
    if (bRam01b96b <= bRam301796) goto LAB_0ca734;
    uRam00fd74 = uRam00fd74 | 0x10;
  }
  uVar15 = uRam00fd72;
  switch(cruise_state) {
  case 0:
    if (((uRam00fd72 & 1) == 0) || ((uRam00fd04 & 4) != 0)) {
      cruise_state = 0;
      uRam00fd74 = uRam00fd74 & 0x7fff;
code_r0x0caa0c:
      uVar15 = uRam00fd72 & 0xfef7;
    }
    else if (((uRam00fd74 & 0x2000) == 0) ||
            ((_cruise_set_speed <= _vfzg_vehicle_speed || ((uRam00fd72 & 2) == 0)))) {
      if ((((uRam00fd74 & 0x100) != 0) ||
          (((uRam00fd74 & 0x2000) != 0 && ((_cruise_set_speed != 0 || ((bRam01396e & 4) != 0))))))
         && ((uRam00fd72 & 2) != 0)) {
        uVar15 = uRam00fd74 & 0x7fff;
        uVar10 = uRam00fd74 & 0x2000;
        uRam00fd74 = uVar15;
        if ((uVar10 != 0) && (_cruise_set_speed != 0)) {
          uRam00fd76 = uRam00fd76 | 1;
        }
        goto code_r0x0caa26;
      }
      if (((uRam00fd74 & 8) != 0) && ((uRam00fd72 & 2) != 0)) {
        uRam00fd74 = uRam00fd74 & 0x7fff;
        goto code_r0x0ca9f6;
      }
      if ((((uRam00fd74 & 0x1000) != 0) && ((bRam01396e & 8) != 0)) && ((uRam00fd72 & 2) != 0)) {
        uRam00fd74 = uRam00fd74 & 0x7fff;
        goto code_r0x0caa0a;
      }
      uRam00fd74 = uRam00fd74 & 0x7fff;
    }
    else {
      uRam00fd74 = uRam00fd74 & 0x7fff;
code_r0x0ca8aa:
      cruise_state = 2;
      uRam00fd76 = uRam00fd76 | 2;
      uVar15 = uRam00fd72 | 0x108;
    }
    break;
  case 1:
    if (((uRam00fd72 & 1) == 0) || ((uRam00fd04 & 4) != 0)) {
      cruise_state = 0;
      uRam00fd72 = uRam00fd72 & 0xf3bf;
      uRam00fd74 = uRam00fd74 & 0xbfff;
      uRam00fd76 = uRam00fd76 & 0xfffe;
      goto code_r0x0caa0c;
    }
    if (((uRam00fd74 & 4) == 0) || ((uRam00fd74 & 0x40) == 0)) {
      if ((uRam00fd74 & 8) != 0) {
        uRam00fd72 = uRam00fd72 & 0xf3bf;
        uRam00fd74 = uRam00fd74 & 0xbfff;
        uRam00fd76 = uRam00fd76 & 0xfffe;
        goto code_r0x0ca9f6;
      }
      if (((uRam00fd74 & 0x800) == 0) || ((uRam00fd74 & 0x10) == 0)) {
        if ((uRam00fd74 & 0x1000) != 0) {
          uRam00fd72 = uRam00fd72 & 0xf3bf;
          uRam00fd74 = uRam00fd74 & 0xbfff;
          uRam00fd76 = uRam00fd76 & 0xfffe;
          goto code_r0x0caa0a;
        }
        uVar15 = _cruise_set_speed - _vfzg_vehicle_speed;
        if (_cruise_set_speed < _vfzg_vehicle_speed) {
          uVar15 = 0;
        }
        if (uRam012b52 < uVar15) {
          uRam00fd72 = uRam00fd72 & 0xf3bf;
          uRam00fd74 = uRam00fd74 & 0xbfff;
          uRam00fd76 = uRam00fd76 & 0xfffe;
          goto code_r0x0ca8aa;
        }
        if ((uRam00fd74 & 0x100) != 0) {
          uRam00fd72 = uRam00fd72 & 0xf3ff;
        }
        uRam00fd76 = uRam00fd76 & 0xfffe;
        uVar15 = uRam00fd72;
        uRam00fd74 = uRam00fd74 & 0xbfff;
      }
      else {
        cruise_state = 6;
        uRam00fd76 = uRam00fd76 & 0xfffe;
        uRam00fd74 = uRam00fd74 & 0xbfff | 0x20;
        uVar15 = uRam00fd72 & 0xf3bf | 0x108;
      }
    }
    else {
      cruise_state = 4;
      uRam00fd76 = uRam00fd76 & 0xfffe;
      uRam00fd74 = uRam00fd74 & 0xbfff | 0x80;
      uVar15 = uRam00fd72 & 0xf3bf | 0x108;
    }
    break;
  case 2:
    if (((uRam00fd72 & 1) == 0) || ((uRam00fd04 & 4) != 0)) {
      cruise_state = 0;
      uRam00fd76 = uRam00fd76 & 0xfffd;
      goto code_r0x0caa0c;
    }
    if (((uRam00fd74 & 8) == 0) || ((bRam01396e & 1) != 0)) {
      if (((uRam00fd74 & 0x1000) != 0) && ((bRam01396e & 2) == 0)) {
        uRam00fd76 = uRam00fd76 & 0xfffd;
code_r0x0caa0a:
        cruise_state = 5;
        uRam00fd72 = uRam00fd72 | 0x200;
        goto code_r0x0caa0c;
      }
      if (((uRam00fd74 & 0x100) != 0) || (_cruise_set_speed <= _vfzg_vehicle_speed)) {
        uRam00fd76 = uRam00fd76 & 0xfffd;
        if ((uRam00fd74 & 0x100) == 0) goto code_r0x0caa24;
        goto code_r0x0caa26;
      }
    }
    else {
      uRam00fd76 = uRam00fd76 & 0xfffd;
code_r0x0ca9f6:
      cruise_state = 3;
      uVar15 = uRam00fd72 | 0x10c;
    }
    break;
  case 3:
    if (((uRam00fd72 & 1) == 0) || ((uRam00fd04 & 4) != 0)) {
      uRam00fd72 = uRam00fd72 & 0xfffb;
code_r0x0ca9ba:
      cruise_state = 0;
      uRam00fd74 = uRam00fd74 | 0x8000;
      goto code_r0x0caa0c;
    }
    if (((uRam00fd74 & 2) != 0) || (uRam302cf2 <= _vfzg_vehicle_speed)) {
      uRam00fd72 = uRam00fd72 & 0xfffb | 0x400;
code_r0x0caa26:
      cruise_state = 1;
      uVar15 = uRam00fd72 & 0xfeff | 0x48;
      if ((uRam00fd74 & 0x100) != 0) {
        uVar15 = uRam00fd72 & 0xf2ff | 0x48;
      }
    }
    break;
  case 4:
    if (((uRam00fd72 & 1) == 0) || ((uRam00fd04 & 4) != 0)) {
      cruise_state = 0;
      uRam00fd74 = uRam00fd74 & 0xff7f;
      goto code_r0x0caa0c;
    }
    if ((uRam00fd74 & 8) != 0) {
      uRam00fd74 = uRam00fd74 & 0xff7f;
      goto code_r0x0ca9f6;
    }
    if ((uRam00fd74 & 0x1000) != 0) {
      uRam00fd74 = uRam00fd74 & 0xff7f;
      goto code_r0x0caa0a;
    }
    if (_cruise_set_speed <= uRam302cf4) {
      uRam00fd74 = uRam00fd74 & 0xff7f;
code_r0x0caa24:
      uRam00fd74 = uRam00fd74 | 0x4000;
      goto code_r0x0caa26;
    }
    break;
  case 5:
    if (((uRam00fd72 & 1) == 0) || ((uRam00fd04 & 4) != 0)) {
      uRam00fd72 = uRam00fd72 & 0xfdff;
      goto code_r0x0ca9ba;
    }
    if (((uRam00fd74 & 0x400) != 0) || (_vfzg_vehicle_speed <= uRam302cf6)) {
      uRam00fd72 = uRam00fd72 & 0xfdff | 0x800;
      goto code_r0x0caa26;
    }
    break;
  case 6:
    if (((uRam00fd72 & 1) == 0) || ((uRam00fd04 & 4) != 0)) {
      cruise_state = 0;
      uRam00fd74 = uRam00fd74 & 0xffdf;
      goto code_r0x0caa0c;
    }
    if ((uRam00fd74 & 8) != 0) {
      uRam00fd74 = uRam00fd74 & 0xffdf;
      goto code_r0x0ca9f6;
    }
    if ((uRam00fd74 & 0x1000) != 0) {
      uRam00fd74 = uRam00fd74 & 0xffdf;
      goto code_r0x0caa0a;
    }
    if (uRam302cf4 <= _cruise_set_speed) {
      uRam00fd74 = uRam00fd74 & 0xffdf;
      goto code_r0x0caa24;
    }
    break;
  default:
    cruise_state = 0;
    uRam00fd76 = uRam00fd76 & 0xfffc;
    uVar15 = uRam00fd72 & 0xf0b3;
    uRam00fd74 = uRam00fd74 & 0x3f5f;
  }
  uRam00fd72 = uVar15;
  if ((uRam00fd72 & 0x400) == 0) {
    sRam300c26 = sRam300c34;
    uRam00fd72 = uRam00fd72 & 0xbfff;
    uRam00fd76 = uRam00fd76 & 0xfbff;
  }
  else if (sRam300c26 == 0) {
    if ((uRam00fd76 & 0x400) == 0) {
      uRam00fd72 = uRam00fd72 | 0x4000;
      uRam00fd76 = uRam00fd76 | 0x400;
    }
    else {
      uRam00fd72 = uRam00fd72 & 0xbfff;
    }
  }
  else {
    sRam300c26 = sRam300c26 + -1;
  }
  if ((uRam00fd72 & 0x800) == 0) {
    sRam300c28 = sRam300c36;
    uRam00fd72 = uRam00fd72 & 0x7fff;
    uRam00fd76 = uRam00fd76 & 0xf7ff;
  }
  else if (sRam300c28 == 0) {
    if ((uRam00fd76 & 0x800) == 0) {
      uRam00fd72 = uRam00fd72 | 0x8000;
      uRam00fd76 = uRam00fd76 | 0x800;
    }
    else {
      uRam00fd72 = uRam00fd72 & 0x7fff;
    }
  }
  else {
    sRam300c28 = sRam300c28 + -1;
  }
  if (((((((uRam00fd72 & 8) == 0) || ((bRam300c44 & 2) != 0)) &&
        (((uRam00fd72 & 0x100) == 0 || ((uRam00fd76 & 0x40) != 0)))) &&
       (((uRam00fd72 & 0x100) != 0 || ((uRam00fd76 & 0x40) == 0)))) &&
      (((uRam00fd72 & 0x40) == 0 || ((uRam00fd74 & 0x100) == 0)))) &&
     (((uRam00fd72 & 0x4000) == 0 && ((uRam00fd72 & 0x8000) == 0)))) {
    uRam00fd72 = uRam00fd72 & 0xffef;
  }
  else {
    uRam00fd72 = uRam00fd72 | 0x10;
  }
  if (((uRam00fd72 & 8) == 0) && ((uRam00fd72 & 0x200) == 0)) {
    uRam00fd72 = uRam00fd72 & 0xffdf;
  }
  else {
    uRam00fd72 = uRam00fd72 | 0x20;
  }
  uVar15 = _vfzg_vehicle_speed;
  if (((((uRam00fd74 & 0x100) == 0) || ((uRam00fd72 & 0x40) == 0)) &&
      (((uRam00fd72 & 0x400) == 0 || ((bRam300c44 & 1) != 0)))) &&
     ((((uRam00fd72 & 8) == 0 || ((bRam300c44 & 2) != 0)) &&
      (((uRam00fd76 & 2) == 0 || ((uRam00fd76 & 0x200) != 0)))))) {
    uVar15 = uRam302cf4;
  }
  if ((uRam00fd76 & 2) == 0) {
    uRam00fd76 = uRam00fd76 & 0x1fff;
  }
  if ((((uRam00fd72 & 4) == 0) && ((uRam00fd76 & 2) == 0)) && ((uRam00fd74 & 0x80) == 0)) {
    if ((uRam00fd72 & 0x4000) == 0) {
      if ((uRam00fd72 & 0x8000) == 0) {
        if ((uRam00fd74 & 0x20) == 0) {
          if (((uRam00fd74 & 0x4000) != 0) || ((uRam00fd76 & 1) != 0)) {
            uVar15 = _cruise_set_speed;
          }
        }
        else {
          uRam01acda = (ushort)bRam01b96c;
          bVar1 = uVar15 < uRam302cda;
          uVar15 = uVar15 - uRam302cda;
          if (bVar1) {
            uVar15 = 0;
          }
        }
      }
      else {
        bVar1 = uVar15 < uRam300c2c;
        uVar15 = uVar15 - uRam300c2c;
        if (bVar1) {
          uVar15 = 0;
        }
      }
    }
    else {
      bVar1 = uVar15 + uRam300c2a < uVar15;
      uVar10 = uVar15 + uRam300c2a;
      uVar15 = uVar15 + uRam300c2a;
      if (bVar1 || uVar10 < uRam300c2a) {
        uVar15 = 0xffff;
      }
    }
    if (uRam300c38 < uVar15) {
      uRam302cf4 = uRam300c38;
    }
    else {
      uRam302cf4 = uVar15;
      if (uVar15 < uRam300c3a) {
        uRam302cf4 = uRam300c3a;
      }
    }
  }
  else {
    if ((uRam00fd76 & 2) == 0) {
      if ((uRam00fd72 & 4) == 0) {
        uRam01acd6 = (ushort)bRam01b96d;
      }
      else {
        _cruise_speed_corr = me7_lookup_1d_word(0x2a7a,9,_vfzg_vehicle_speed);
      }
    }
    else {
      uVar10 = _cruise_set_speed - _vfzg_vehicle_speed;
      if (_cruise_set_speed < _vfzg_vehicle_speed) {
        uVar10 = 0;
      }
      if (uRam026b58 < uVar10) {
        if (uRam026b56 < uVar10) {
          if (uVar10 <= uRam026b54) {
            uRam00fd76 = uRam00fd76 | 0x2000;
          }
        }
        else {
          uRam00fd76 = uRam00fd76 | 0x4000;
        }
      }
      else {
        uRam00fd76 = uRam00fd76 | 0x8000;
      }
      if ((uRam00fd76 & 0x8000) == 0) {
        if ((uRam00fd76 & 0x4000) == 0) {
          if ((uRam00fd76 & 0x2000) == 0) {
            _cruise_speed_corr = me7_lookup_1d_word(0x2b02,9,_vfzg_vehicle_speed);
          }
          else {
            _cruise_speed_corr = uRam300c20;
          }
        }
        else {
          _cruise_speed_corr = uRam300c22;
        }
      }
      else {
        _cruise_speed_corr = uRam300c24;
      }
    }
    if (uRam302cfe < uRam016fdc) {
      uRam302cd8 = _cruise_speed_corr;
    }
    else {
      uRam302cd8 = 0;
    }
    uVar10 = uVar15 + uRam302cd8;
    if (uVar15 + uRam302cd8 < uVar15 || uVar15 + uRam302cd8 < uRam302cd8) {
      uVar10 = 0xffff;
    }
    uRam302cf4 = uVar10;
    if (((uRam00fd1c & 0x100) == 0) &&
       (uRam302cf4 = _vfzg_vehicle_speed, _vfzg_vehicle_speed <= uVar10)) {
      uRam302cf4 = uVar10;
    }
  }
  iVar17 = CONCAT22(_cruise_i_state_hi,_cruise_i_state_lo);
  iVar7 = CONCAT22(MDH,MDL);
  if (((uRam00fd72 & 4) == 0) && ((uRam00fd76 & 2) == 0)) {
    uRam301798 = 0;
  }
  else if (_cruise_speed_corr < 0x100) {
    uRam301798 = cruise_speed_corr;
  }
  else {
    uRam301798 = 0xff;
  }
  uVar15 = uRam302cf4;
  if ((uRam00fd72 & 0x40) == 0) {
    if ((((uRam00fd74 & 0x8000) == 0) || ((bRam01b96e & 0x20) == 0)) && ((uRam00fd0a & 2) == 0)) {
      if (((uRam00fd74 & 0x8000) == 0) || (uVar15 = _vfzg_vehicle_speed, (bRam01b96e & 0x20) != 0))
      {
        if (((uRam00fd74 & 0x80) == 0) || (((uRam00fd74 & 0x40) == 0 || ((uRam00fd74 & 4) == 0)))) {
          if ((((uRam00fd74 & 0x20) != 0) && ((uRam00fd74 & 0x10) != 0)) &&
             ((uRam00fd74 & 0x800) != 0)) {
            if ((bRam01b96e & 0x10) == 0) {
              uVar15 = _cruise_set_speed - uRam026b4e;
              if (_cruise_set_speed < uRam026b4e) {
                uVar15 = 0;
              }
            }
            else {
              uVar15 = _vfzg_vehicle_speed - uRam026b4e;
              if (_vfzg_vehicle_speed < uRam026b4e) {
                uVar15 = 0;
              }
            }
            if (uVar15 <= _cruise_set_speed) goto LAB_0cad66;
          }
        }
        else {
          if ((bRam01b96e & 0x10) == 0) {
            uVar15 = _cruise_set_speed + uRam026b4e;
            if (_cruise_set_speed + uRam026b4e < _cruise_set_speed ||
                _cruise_set_speed + uRam026b4e < uRam026b4e) {
              uVar15 = 0xffff;
            }
          }
          else {
            uVar15 = _vfzg_vehicle_speed + uRam026b4e;
            if (_vfzg_vehicle_speed + uRam026b4e < _vfzg_vehicle_speed ||
                _vfzg_vehicle_speed + uRam026b4e < uRam026b4e) {
              uVar15 = 0xffff;
            }
          }
          if (_cruise_set_speed <= uVar15) goto LAB_0cad66;
        }
        uVar15 = _cruise_set_speed;
      }
    }
    else {
      uVar15 = 0;
    }
  }
LAB_0cad66:
  if (uVar15 == 0) {
    _cruise_set_speed = 0;
  }
  else if (uRam300c38 < uVar15) {
    _cruise_set_speed = uRam300c38;
  }
  else {
    _cruise_set_speed = uVar15;
    if (uVar15 < uRam300c3a) {
      _cruise_set_speed = uRam300c3a;
    }
  }
  if ((uRam00fd74 & 0x80) == 0) {
    bRam301797 = 0;
  }
  else if ((((uRam00fd74 & 4) != 0) && ((uRam00fd74 & 0x40) != 0)) && (bRam301797 != 0xff)) {
    bRam301797 = bRam301797 + 1;
  }
  if ((uRam00fd74 & 0x20) == 0) {
    bRam301796 = 0;
  }
  else if ((((uRam00fd74 & 0x800) != 0) && ((uRam00fd74 & 0x10) != 0)) && (bRam301796 != 0xff)) {
    bRam301796 = bRam301796 + 1;
  }
  if ((uRam00fd72 & 8) == 0) {
LAB_0cae16:
    uRam00fd72 = uRam00fd72 & 0xdfff;
  }
  else {
    uVar15 = uRam026b2a + uRam026cf4;
    if (uRam026b2a + uRam026cf4 < uRam026b2a || uRam026b2a + uRam026cf4 < uRam026cf4) {
      uVar15 = 0xffff;
    }
    uVar10 = uRam026b2c + uRam026cf4;
    if (uRam026b2c + uRam026cf4 < uRam026b2c || uRam026b2c + uRam026cf4 < uRam026cf4) {
      uVar10 = 0xffff;
    }
    if (_vfzg_vehicle_speed < uVar15) {
      if (_vfzg_vehicle_speed <= uVar10) {
        uRam00fd76 = uRam00fd76 & 0xfeff;
      }
    }
    else {
      uRam00fd76 = uRam00fd76 | 0x100;
    }
    if ((uRam00fd76 & 0x100) != 0) goto LAB_0cae16;
    uRam00fd72 = uRam00fd72 | 0x2000;
  }
  if ((uRam00fd72 & 8) == 0) {
LAB_0cae5a:
    uRam00fd72 = uRam00fd72 & 0xefff;
  }
  else {
    uVar15 = uRam026b26 + uRam026cf4;
    if (uRam026b26 + uRam026cf4 < uRam026b26 || uRam026b26 + uRam026cf4 < uRam026cf4) {
      uVar15 = 0xffff;
    }
    uVar10 = uRam026b28 + uRam026cf4;
    if (uRam026b28 + uRam026cf4 < uRam026b28 || uRam026b28 + uRam026cf4 < uRam026cf4) {
      uVar10 = 0xffff;
    }
    if (_vfzg_vehicle_speed < uVar15) {
      if (_vfzg_vehicle_speed <= uVar10) {
        uRam00fd76 = uRam00fd76 & 0xefff;
      }
    }
    else {
      uRam00fd76 = uRam00fd76 | 0x1000;
    }
    if ((uRam00fd76 & 0x1000) != 0) goto LAB_0cae5a;
    uRam00fd72 = uRam00fd72 | 0x1000;
  }
  if ((uRam00fd72 & 8) == 0) {
    uRam00fd72 = uRam00fd72 & 0xff7f;
LAB_0cb364:
    _cruise_torque_req = 0;
  }
  else {
    sVar9 = me7_lookup_1d_byte(0x3980,6,nmot_rpmclass);
    uVar15 = sVar9 * 0x100;
    if ((((uRam00fd72 & 0x40) == 0) || ((uRam00fd74 & 0x100) == 0)) && ((bRam300c44 & 2) != 0)) {
      if ((((uRam00fd72 & 0x400) == 0) || ((bRam300c44 & 1) != 0)) || (uRam302cfe <= uVar15)) {
        uRam302ce2 = uRam302cfe;
      }
      else {
LAB_0caec8:
        uRam302ce2 = uVar15;
      }
    }
    else {
      uVar10 = uRam301abc;
      if (uRam301abc <= uRam026b7c) {
        uVar10 = uRam026b7c;
      }
      uRam302ce2 = uRam302cfe;
      if (uRam302cfe <= uVar10) {
        uRam302ce2 = uVar10;
      }
      if (uVar15 < uRam302ce2) goto LAB_0caec8;
    }
    bRam304d4a = me7_lookup_1d_byte(0x396f,6,nmot_rpmclass);
    uVar10 = MDC;
    uVar15 = (ushort)bRam304d4a;
    uVar5 = CONCAT22(uRam302ce2 >> 9,uRam302ce2 << 7);
    uVar6 = uVar5 / uVar15;
    MDL = (ushort)uVar6;
    MDH = (undefined2)(uVar5 % (uint)uVar15);
    MDC = MDC | 0x10;
    uRam302ce8 = MDL;
    if (uVar15 == 0 || 0xffff < uVar6) {
      uRam302ce8 = 0xffff;
    }
    if ((uRam00fd72 & 0x100) == 0) {
      uRam302cde = func_0x040f9e(0x6fcc,_cruise_set_speed,uRam302cde);
      uVar10 = me7_lookup_2d_word_torque(0x6f6c,0x28b7,uRam302cde,uRam3019fe);
      uRam302ce0 = uRam300c2e;
      uRam302cea = uRam300c32;
      uVar5 = CONCAT22(uRam302ce8 >> 0xd,uRam302ce8 << 3);
      uVar6 = uVar5 / uRam300c2e;
      MDL = (ushort)uVar6;
      MDH = (undefined2)(uVar5 % (uint)uRam300c2e);
      MDC = MDC | 0x10;
      uVar15 = MDL;
      if (uRam300c2e == 0 || 0xffff < uVar6) {
        uVar15 = 0xffff;
      }
    }
    else {
      uRam302ce0 = uRam300c30;
      uRam302cea = uRam302cec;
      uVar5 = CONCAT22(uRam302ce8 >> 0xd,uRam302ce8 << 3);
      uVar6 = uVar5 / uRam300c30;
      MDL = (ushort)uVar6;
      MDH = (undefined2)(uVar5 % (uint)uRam300c30);
      MDC = uVar10 | 0x10;
      uVar15 = MDL;
      if (uRam300c30 == 0 || 0xffff < uVar6) {
        uVar15 = 0xffff;
      }
      uVar10 = uVar15;
      if ((uRam00fd76 & 0x40) != 0) {
        uVar10 = uRam302cf0;
      }
    }
    uRam302cf0 = uVar10;
    iVar17 = CONCAT22(_cruise_i_state_hi,_cruise_i_state_lo);
    if (((uRam00fd72 & 0x40) == 0) || ((bRam01b96e & 0x40) != 0)) {
LAB_0cb01a:
      uRam302cee = 0;
      iVar17 = 0;
    }
    else if ((((uRam00fd74 & 0x100) == 0) && (((uRam00fd72 & 8) == 0 || ((bRam300c44 & 2) != 0))))
            && (((uRam00fd76 & 2) != 0 || ((uRam00fd76 & 0x200) == 0)))) {
      if (uRam302ce2 < uRam016fdc) {
        sRam302cdc = _cruise_set_speed - _vfzg_vehicle_speed;
        if (_cruise_set_speed < _vfzg_vehicle_speed) {
          if (sRam302cdc >= 0) {
            sRam302cdc = -0x8000;
          }
        }
        else if (sRam302cdc < 0) {
          sRam302cdc = 0x7fff;
        }
        uVar15 = me7_lookup_1d_word(0x2be0,9,_cruise_set_speed,0);
        uVar11 = func_0x042486(uRam026bae,0x2bb0,9,0x2bc0,9,sRam302cdc,0,0,uVar15 >> 1);
        iVar17 = func_0x0430da(uVar11,sRam302cdc >> 1,_cruise_i_state_hi,_cruise_i_state_lo);
        uRam302cee = (short)((uint)iVar17 >> 0x10) << 1;
      }
    }
    else {
      if (uVar15 <= uRam302cf0) goto LAB_0cb01a;
      uVar15 = uVar15 - uRam302cf0;
      uVar10 = me7_lookup_1d_word(0x2be0,9,_cruise_set_speed);
      if (uVar10 < uVar15) {
        uVar15 = me7_lookup_1d_word(0x2be0,9,_cruise_set_speed);
      }
      iVar17 = (uint)(uVar15 >> 1) << 0x10;
      uRam302cee = uVar15;
    }
    uVar15 = uRam302cee + uRam302cf0;
    if (uRam302cee + uRam302cf0 < uRam302cee || uRam302cee + uRam302cf0 < uRam302cf0) {
      uVar15 = 0xffff;
    }
    uVar10 = uRam302cf4 + uVar15;
    if (uRam302cf4 + uVar15 < uRam302cf4 || uRam302cf4 + uVar15 < uVar15) {
      uVar10 = 0xffff;
    }
    sVar9 = uVar10 - _vfzg_vehicle_speed;
    if (uVar10 < _vfzg_vehicle_speed) {
      if (sVar9 >= 0) {
        sVar9 = -0x8000;
      }
    }
    else if (sVar9 < 0) {
      sVar9 = 0x7fff;
    }
    uVar15 = uRam302cec - 1;
    if (uRam302cec == 0) {
      uVar15 = 0;
    }
    if ((uRam00fd72 & 0x10) == 0) {
      sVar13 = uRam302cee - uRam300c42;
      if (uRam302cee < uRam300c42) {
        if (sVar13 >= 0) {
          sVar13 = -0x8000;
        }
      }
      else if (sVar13 < 0) {
        sVar13 = 0x7fff;
      }
      sVar16 = sRam300c3c + sVar13;
      if (sRam300c3c < 0 == sVar13 < 0 && sRam300c3c + sVar13 < 0 != sRam300c3c < 0) {
        sVar16 = 0x7fff;
      }
      if ((short)uVar15 < 0) {
        iVar7 = (int)sVar16 * (int)(short)(uVar15 & 0x7fff);
        uVar10 = (ushort)iVar7;
        uVar15 = sVar16 * -0x8000;
        iVar7 = CONCAT22((short)((uint)iVar7 >> 0x10) + (sVar16 >> 1) +
                         (ushort)(uVar10 + uVar15 < uVar10 || uVar10 + uVar15 < uVar15),
                         uVar10 + uVar15);
      }
      else {
        iVar7 = (int)sVar16 * (int)(short)uVar15;
      }
    }
    else if ((short)uVar15 < 0) {
      iVar7 = (int)sVar9 * (int)(short)(uVar15 & 0x7fff);
      uVar10 = (ushort)iVar7;
      uVar15 = sVar9 * -0x8000;
      iVar7 = CONCAT22((short)((uint)iVar7 >> 0x10) + (sVar9 >> 1) +
                       (ushort)(uVar10 + uVar15 < uVar10 || uVar10 + uVar15 < uVar15),
                       uVar10 + uVar15);
    }
    else {
      iVar7 = (int)sVar9 * (int)(short)uVar15;
    }
    uStack_8 = (ushort)((uint)iVar7 >> 0x10);
    uStack_a = (ushort)iVar7;
    uVar15 = uRam302cec + 1;
    if (uRam302cec + 1 < uRam302cec || uRam302cec == 0xffff) {
      uVar15 = 0xffff;
    }
    if ((short)uVar15 < 0) {
      iVar8 = (int)sVar9 * (int)(short)(uVar15 & 0x7fff);
      uVar10 = (ushort)iVar8;
      uVar15 = sVar9 * -0x8000;
      iVar8 = CONCAT22((short)((uint)iVar8 >> 0x10) + (sVar9 >> 1) +
                       (ushort)(uVar10 + uVar15 < uVar10 || uVar10 + uVar15 < uVar15),
                       uVar10 + uVar15);
    }
    else {
      iVar8 = (int)sVar9 * (int)(short)uVar15;
    }
    uVar14 = (ushort)((uint)iVar8 >> 0x10);
    bVar1 = (ushort)iVar8 < uStack_a;
    uVar15 = (ushort)(iVar8 - iVar7);
    uVar10 = (uVar14 - uStack_8) - (ushort)bVar1;
    if (iVar8 < 0 != iVar7 < 0 && iVar8 - iVar7 < 0 != iVar8 < 0) {
      if (uVar14 < uStack_8 || uVar14 == uStack_8 && bVar1) {
        uVar15 = 0xffff;
        uVar10 = 0x7fff;
      }
      else {
        uVar15 = 0;
        uVar10 = 0x8000;
      }
    }
    uVar14 = (ushort)(uVar15 < 0x7fff);
    if (uVar10 == uVar14 && uVar15 == 0x7fff ||
        (short)(uVar10 - uVar14) < 0 !=
        ((short)uVar10 < 0 && (short)(uVar10 - (uVar15 < 0x7fff)) < 0 != (short)uVar10 < 0)) {
      if ((short)((uVar10 + 1) - (ushort)(uVar15 < 0x8000)) < 0 !=
          (-1 < (short)uVar10 &&
          (short)((uVar10 + 1) - (ushort)(uVar15 < 0x8000)) < 0 != (short)uVar10 < 0)) {
        uVar15 = 0x8000;
      }
    }
    else {
      uVar15 = 0x7fff;
    }
    if ((short)uRam302ce0 < 0) {
      iVar7 = (int)(short)uVar15 * (int)(short)(uRam302ce0 & 0x7fff);
      uVar14 = (ushort)iVar7;
      uVar10 = uVar15 * -0x8000;
      iVar7 = CONCAT22((short)((uint)iVar7 >> 0x10) + ((short)uVar15 >> 1) +
                       (ushort)(uVar14 + uVar10 < uVar14 || uVar14 + uVar10 < uVar10),
                       uVar14 + uVar10);
    }
    else {
      iVar7 = (int)(short)uVar15 * (int)(short)uRam302ce0;
    }
    iVar7 = iVar7 >> 4;
    sVar13 = (short)((uint)iVar7 >> 0x10);
    uVar15 = uRam302cea - 1;
    if (uRam302cea == 0) {
      uVar15 = 0;
    }
    uVar5 = (uint)(uRam302ce8 >> 1) * (uint)uVar15;
    bVar2 = 1 < ((ushort)uVar5 & 1);
    bVar1 = (short)iVar7 == -1 && bVar2;
    uVar15 = (short)iVar7 + (ushort)bVar2;
    sVar16 = sVar13 + (ushort)bVar1;
    if (iVar7 < 0 || (short)(sVar13 + (ushort)bVar1) < 0 == iVar7 < 0) {
      uVar5 = uVar5 >> 1;
      uVar10 = (ushort)uVar5;
      sVar3 = (short)(uVar5 >> 0x10);
      bVar1 = uVar15 + uVar10 < uVar15 || uVar15 + uVar10 < uVar10;
      uVar15 = uVar15 + uVar10;
      sVar13 = sVar16 + sVar3 + (ushort)bVar1;
      if (-1 < sVar16 && (short)(sVar16 + sVar3 + (ushort)bVar1) < 0 != sVar16 < 0) goto LAB_0cb2c6;
      bVar1 = uVar15 + uVar10 < uVar15 || uVar15 + uVar10 < uVar10;
      uVar15 = uVar15 + uVar10;
      sVar16 = sVar13 + sVar3 + (ushort)bVar1;
      if (-1 < sVar13 && (short)(sVar13 + sVar3 + (ushort)bVar1) < 0 != sVar13 < 0) goto LAB_0cb2c6;
    }
    else {
LAB_0cb2c6:
      uVar15 = 0xffff;
      sVar16 = 0x7fff;
    }
    if (sVar16 == 0 && uVar15 == 0 || sVar16 < 0) {
      uRam302ce6 = 0;
    }
    else {
      uVar10 = uRam302cea + 1;
      if (uRam302cea + 1 < uRam302cea || uRam302cea == 0xffff) {
        uVar10 = 0xffff;
      }
      uVar5 = CONCAT22(sVar16 * 2 + (ushort)(uVar15 * 2 < uVar15 || uVar15 * 2 < uVar15),uVar15 * 2)
              / (uint)uVar10;
      uRam302ce6 = (ushort)uVar5;
      if (uVar10 == 0 || 0xffff < uVar5) {
        uRam302ce6 = 0xffff;
      }
    }
    iVar7 = (uint)uRam302ce6 * (uint)bRam304d4a * 0x100;
    uVar15 = (ushort)((uint)iVar7 >> 0x10);
    MDC = MDC | 0x10;
    _cruise_torque_req = uVar15 * 2;
    if (uVar15 * 2 < uVar15) {
      _cruise_torque_req = 0xffff;
    }
    if ((uRam00fd72 & 0x1000) == 0) {
      if (_cruise_torque_req <= uRam026b7a) {
        uRam00fd72 = uRam00fd72 | 0x80;
      }
    }
    else {
      uRam00fd72 = uRam00fd72 & 0xff7f;
    }
    sRam300c3c = sVar9;
    if ((uRam00fd72 & 0x80) != 0) goto LAB_0cb364;
  }
  if ((uRam00fd72 & 8) == 0) {
    bRam300c44 = bRam300c44 & 0xfd;
  }
  else {
    bRam300c44 = bRam300c44 | 2;
  }
  if ((uRam00fd72 & 0x400) == 0) {
    bRam300c44 = bRam300c44 & 0xfe;
  }
  else {
    bRam300c44 = bRam300c44 | 1;
  }
  uRam300c42 = uRam302cee;
  uVar14 = uRam00fd76 & 0xfdbf | ((uRam00fd72 & 0x100) >> 8) << 6 | ((uRam00fd76 & 2) >> 1) << 9;
LAB_0cb3b8:
  uRam00fd76 = uVar14;
  _cruise_i_state_hi = (undefined2)((uint)iVar17 >> 0x10);
  _cruise_i_state_lo = (undefined2)iVar17;
  MDH = (undefined2)((uint)iVar7 >> 0x10);
  MDL = (ushort)iVar7;
  return;
}


// ================= diag_throttle_angle_from_charge @ 0c983a =================

/* WARNING: Removing unreachable block (ram,0x0c9af2) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC: expected-throttle-angle-from-charge monitor (0x0B722 slot): expected wdk byte_301791
   = min(2-D map 0x1465E(rpm-class byte_F40E x charge byte_30178C), cap tbl 0x14724); two PT1 banks
   byte_30178E/byte_301790 (sub_42CF4, rate tbl 0x1470B); pot window byte_30177F<<4 +/- word_16F50
   vs word_301952 -> word_FD6E.14; majority-vote deviation above min-rpm byte_14709 ('Minimum engine
   speed for calculation of throttle angle default value from charge', dict-exact) with time cal
   TDKPAW 0x1470A -> fault bits loc_FD70.3/.4, word_FD6E.3/.4/.8/.9/.10, word_FD6C.15 [C] */

void diag_throttle_angle_from_charge(void)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  byte bVar4;
  short sVar5;
  byte bVar6;
  ushort uVar7;
  ushort uVar8;
  
  iVar3 = CONCAT22(MDH,MDL);
  sRam300bfc = _throttle_pos_fb;
  if (_throttle_pos_fb < 1) {
    DAT_301792 = 0;
  }
  else if (_throttle_pos_fb + -0x1000 < 0 ==
           (_throttle_pos_fb < 0 && _throttle_pos_fb + -0x1000 < 0 != _throttle_pos_fb < 0)) {
    DAT_301792 = 0xff;
  }
  else {
    DAT_301792 = (undefined1)(_throttle_pos_fb >> 4);
  }
  sRam302cd0 = _throttle_pos_fb - sRam300bfa;
  if (_throttle_pos_fb < 0 != sRam300bfa < 0 &&
      _throttle_pos_fb - sRam300bfa < 0 != _throttle_pos_fb < 0) {
    sRam302cd0 = -0x8000;
  }
  sRam300bfa = _throttle_pos_fb;
  uVar7 = (ushort)bRam30177f * 0x10 - uRam016f50;
  if ((ushort)bRam30177f * 0x10 < uRam016f50) {
    uVar7 = 0;
  }
  if (uVar7 < _adc_ch1_raw) {
    uVar8 = (ushort)bRam30177f * 0x10;
    uVar7 = uVar8 + uRam016f50;
    if (uVar8 + uRam016f50 < uVar8 || uVar8 + uRam016f50 < uRam016f50) {
      uVar7 = 0xffff;
    }
    if (uVar7 <= _adc_ch1_raw) {
      uRam00fd6e = uRam00fd6e | 0x4000;
    }
  }
  else {
    uRam00fd6e = uRam00fd6e & 0xbfff;
  }
  if (bRam301839 < bRam01471e) {
    if (bRam301839 <= bRam01471f) {
      uRam00fd6e = uRam00fd6e & 0xdfff;
    }
  }
  else {
    uRam00fd6e = uRam00fd6e | 0x2000;
  }
  if (((((_flags_start_phase & 0x4000) == 0) && ((uRam00fd6e & 0x4000) == 0)) &&
      ((uRam303ad8 & 1) == 0)) && ((uRam00fd6e & 0x2000) != 0)) {
    uRam00fd70 = uRam00fd70 | 2;
  }
  else {
    uRam00fd70 = uRam00fd70 & 0xfffd;
  }
  if (((uRam00fd70 & 0x200) == 0) && ((uRam00fd68 & 0x2000) != 0)) {
    if ((uRam00fd6c & 0x8000) == 0) {
      sVar5 = _adc_ch1_raw - _servo_pot_lin_offset;
      if (_adc_ch1_raw < _servo_pot_lin_offset) {
        sVar5 = 0;
      }
      iVar3 = (uint)(ushort)(sVar5 << 4) * (uint)_servo_pot_lin_gain;
      uVar7 = (ushort)((uint)iVar3 >> 0x10);
      MDC = MDC | 0x10;
      uVar8 = uVar7 * 2;
      if (uVar7 * 2 < uVar7) {
        uVar8 = 0xffff;
      }
      bRam30178d = (byte)(uVar8 >> 8);
      sRam302cd2 = (uVar8 >> 8) << 4;
    }
    if ((uRam00fd6e & 0x10) == 0) {
      sVar5 = _servo_pot_high_bound - _adc_ch2_raw;
      if (_servo_pot_high_bound < _adc_ch2_raw) {
        sVar5 = 0;
      }
      iVar3 = (uint)(ushort)(sVar5 << 4) * (uint)_servo_pot_lin_gain;
      uVar7 = (ushort)((uint)iVar3 >> 0x10);
      MDC = MDC | 0x10;
      uVar8 = uVar7 * 2;
      if (uVar7 * 2 < uVar7) {
        uVar8 = 0xffff;
      }
      bRam30178f = (byte)(uVar8 >> 8);
      sRam302cd4 = (uVar8 >> 8) << 4;
    }
    if ((uRam00fd6c & 0x8000) == 0) {
      if (((ushort)bRam014720 * 0x10 < _adc_ch1_raw) || (_adc_ch1_raw < (ushort)bRam014721 * 0x10))
      {
        PSW = PSW | 0x40;
      }
      else {
        PSW = PSW & 0xffbf;
      }
      uVar7 = PSW & 0x40;
      if ((uRam00fd6e & 1) == 1) {
        if (bRam301785 < bRam014718) {
          bRam301785 = bRam301785 + 1;
        }
        else {
          uRam00fd6c = uRam00fd6c | 0x8000;
        }
      }
      else {
        bRam301785 = 0;
      }
      if (((uRam00fd6c & 0x8000) == 0) || (_adc_ch1_raw <= (ushort)bRam014720 * 0x10)) {
        PSW = PSW & 0xffbf;
      }
      else {
        PSW = PSW | 0x40;
      }
      uVar8 = PSW & 0x40;
      if (((uRam00fd6c & 0x8000) == 0) || ((ushort)bRam014721 * 0x10 <= _adc_ch1_raw)) {
        PSW = PSW & 0xffbf;
      }
      else {
        PSW = PSW | 0x40;
      }
      uRam00fd6e = uRam00fd6e & 0xfff8 | uVar7 >> 6 | (uVar8 >> 6) << 2 | ((PSW & 0x40) >> 6) << 1;
    }
    if ((uRam00fd6e & 0x10) == 0) {
      if (((bRam014708 < nmot_rpmclass) || ((uRam00fd6c & 0x8000) != 0)) &&
         (_adc_ch2_raw < (ushort)bRam014723 * 0x10)) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      if (((ushort)bRam014722 * 0x10 < _adc_ch2_raw) || (bVar1)) {
        PSW = PSW | 0x40;
      }
      else {
        PSW = PSW & 0xffbf;
      }
      uVar7 = uRam00fd6e & 0x20;
      uRam00fd6e = uRam00fd6e & 0xffdf | ((PSW & 0x40) >> 6) << 5;
      if (uVar7 == 0x20) {
        if (bRam301786 < bRam014719) {
          bRam301786 = bRam301786 + 1;
        }
        else {
          uRam00fd6e = uRam00fd6e | 0x10;
        }
      }
      else {
        bRam301786 = 0;
      }
      if (((uRam00fd6e & 0x10) == 0) || (_adc_ch2_raw <= (ushort)bRam014722 * 0x10)) {
        PSW = PSW & 0xffbf;
      }
      else {
        PSW = PSW | 0x40;
      }
      uVar7 = PSW & 0x40;
      if (((uRam00fd6e & 0x10) == 0) || (!bVar1)) {
        PSW = PSW & 0xffbf;
      }
      else {
        PSW = PSW | 0x40;
      }
      uRam00fd6e = uRam00fd6e & 0xff3f | (uVar7 >> 6) << 7 | PSW & 0x40;
    }
    if ((((uRam00fd6c & 0x8000) == 0) && ((uRam00fd6e & 0x10) == 0)) && ((uRam00fd6e & 0x200) == 0))
    {
      if (bRam014708 < nmot_rpmclass) {
        if (bRam30178d < bRam30178f) {
          bVar6 = bRam30178f - bRam30178d;
        }
        else {
          bVar6 = bRam30178d - bRam30178f;
        }
      }
      else {
        bVar6 = bRam30178d - bRam30178f;
        if (bRam30178d < bRam30178f) {
          bVar6 = 0;
        }
      }
      if ((((uRam00fd6e & 1) == 0) && ((uRam00fd6e & 0x20) == 0)) && (bRam01465b < bVar6)) {
        PSW = PSW | 0x40;
      }
      else {
        PSW = PSW & 0xffbf;
      }
      bVar1 = (short)uRam00fd6e < 0;
      uRam00fd6e = uRam00fd6e & 0x7fff | ((PSW & 0x40) >> 6) << 0xf;
      if (bVar1) {
        if (bRam301788 < bRam01471b) {
          bRam301788 = bRam301788 + 1;
        }
        else {
          uRam00fd6e = uRam00fd6e | 0x200;
        }
      }
      else {
        bRam301788 = 0;
      }
    }
    if ((((uRam00fd6e & 1) == 0) && ((uRam00fd6e & 0x20) == 0)) && ((uRam00fd6e & 0x8000) == 0)) {
      uRam00fd6e = uRam00fd6e & 0xf7ff;
    }
    else {
      uRam00fd6e = uRam00fd6e | 0x800;
      uVar7 = (ushort)bRam30127e * (ushort)bRam3014ec >> 8;
      MDL = ((ushort)rl_byte << 8) / uVar7;
      MDH = ((ushort)rl_byte << 8) % uVar7;
      MDC = MDC | 0x10;
      uVar8 = MDL;
      if (uVar7 == 0) {
        uVar8 = 0xffff;
      }
      wdk_charge_axis = (undefined1)(uVar8 >> 3);
      bRam301793 = func_0x040b3e(0x4724,nmot_rpmclass);
      wdk_expected_from_charge = func_0x040ca4(0x465e,nmot_rpmclass,wdk_charge_axis);
      iVar3 = CONCAT22(MDH,MDL);
      if (bRam301793 < wdk_expected_from_charge) {
        wdk_expected_from_charge = bRam301793;
        iVar3 = CONCAT22(MDH,MDL);
      }
    }
    MDH = (ushort)((uint)iVar3 >> 0x10);
    MDL = (ushort)iVar3;
    if (((((uRam00fd6e & 0x20) == 0) && ((uRam00fd6e & 0x8000) == 0)) ||
        ((uRam00fd6c & 0x8000) != 0)) || ((uRam00fd6e & 1) != 0)) {
      cRam300c02 = '\0';
    }
    else {
      bVar6 = bRam30178d;
      if (bRam301793 <= bRam30178d) {
        bVar6 = bRam301793;
      }
      if (cRam300c02 == '\0') {
        cRam300c02 = '\x01';
        sRam300bfe = (ushort)bVar6 << 8;
        wdk_expected_filt_a = bVar6;
      }
      else {
        sVar5 = func_0x040b3e(0x470b,nmot_rpmclass);
        sRam300bfe = me7_fraction_blend(sVar5 << 8,bVar6,sRam300bfe);
        iVar3 = CONCAT22(MDH,MDL);
        wdk_expected_filt_a = (byte)((ushort)sRam300bfe >> 8);
      }
    }
    MDH = (ushort)((uint)iVar3 >> 0x10);
    MDL = (ushort)iVar3;
    if ((((uRam00fd6e & 1) == 0) && ((uRam00fd6e & 0x8000) == 0)) ||
       (((uRam00fd6e & 0x10) != 0 || ((uRam00fd6e & 0x20) != 0)))) {
      cRam300c03 = '\0';
    }
    else {
      bVar6 = bRam30178f;
      if (bRam301793 <= bRam30178f) {
        bVar6 = bRam301793;
      }
      if (cRam300c03 == '\0') {
        cRam300c03 = '\x01';
        sRam300c00 = (ushort)bVar6 << 8;
        wdk_expected_filt_b = bVar6;
      }
      else {
        sVar5 = func_0x040b3e(0x470b,nmot_rpmclass);
        sRam300c00 = me7_fraction_blend(sVar5 << 8,bVar6,sRam300c00);
        iVar3 = CONCAT22(MDH,MDL);
        wdk_expected_filt_b = (byte)((ushort)sRam300c00 >> 8);
      }
    }
    if ((uRam00fd3c & 4) == 0) {
      bRam30178b = 0;
      uRam00fd6e = uRam00fd6e & 0xefff;
    }
    else if (bRam30178b < bRam01471a) {
      bRam30178b = bRam30178b + 1;
    }
    else {
      uRam00fd6e = uRam00fd6e | 0x1000;
    }
    if (((uRam00fd6c & 0x8000) == 0) && (((uRam00fd6e & 0x10) != 0 || ((uRam00fd6e & 0x200) != 0))))
    {
      if (wdk_expected_filt_a < wdk_expected_from_charge) {
        bVar6 = wdk_expected_from_charge - wdk_expected_filt_a;
      }
      else {
        bVar6 = wdk_expected_filt_a - wdk_expected_from_charge;
      }
      if ((((uRam00fd6e & 1) == 0) && (bRam014709 < nmot_rpmclass)) && (bRam01465c < bVar6)) {
        PSW = PSW | 0x40;
      }
      else {
        PSW = PSW & 0xffbf;
      }
      uVar7 = uRam00fd70 & 1;
      uRam00fd70 = uRam00fd70 & 0xfffe | (PSW & 0x40) >> 6;
      if (uVar7 == 1) {
        if (bRam301789 < bRam01471c) {
          bRam301789 = bRam301789 + 1;
        }
        else {
          uRam00fd6c = uRam00fd6c | 0x8000;
        }
      }
      else {
        bRam301789 = 0;
      }
      if ((uRam00fd6e & 0x1000) != 0) {
        uRam00fd6c = uRam00fd6c | 0x8000;
      }
      uRam00fd6e = uRam00fd6e & 0xfff7 | (uRam00fd6c >> 0xf) << 3;
    }
    if (((uRam00fd6e & 0x10) == 0) && (((uRam00fd6c & 0x8000) != 0 || ((uRam00fd6e & 0x200) != 0))))
    {
      if (wdk_expected_filt_b < wdk_expected_from_charge) {
        bVar6 = wdk_expected_from_charge - wdk_expected_filt_b;
      }
      else {
        bVar6 = wdk_expected_filt_b - wdk_expected_from_charge;
      }
      if ((((uRam00fd6e & 0x20) == 0) && (bRam014709 < nmot_rpmclass)) && (bRam01465d < bVar6)) {
        PSW = PSW | 0x40;
      }
      else {
        PSW = PSW & 0xffbf;
      }
      uVar7 = uRam00fd70 & 4;
      uRam00fd70 = uRam00fd70 & 0xfffb | ((PSW & 0x40) >> 6) << 2;
      if (uVar7 == 4) {
        if (bRam30178a < bRam01471d) {
          bRam30178a = bRam30178a + 1;
        }
        else {
          uRam00fd6e = uRam00fd6e | 0x10;
        }
      }
      else {
        bRam30178a = 0;
      }
      if ((uRam00fd6e & 0x1000) != 0) {
        uRam00fd6e = uRam00fd6e | 0x10;
      }
      uRam00fd6e = uRam00fd6e & 0xfeff | ((uRam00fd6e & 0x10) >> 4) << 8;
    }
    if (((uRam00fd6c & 0x8000) == 0) && ((uRam00fd6e & 0x10) == 0)) {
      if (wdk_expected_filt_a < wdk_expected_from_charge) {
        bVar6 = wdk_expected_from_charge - wdk_expected_filt_a;
      }
      else {
        bVar6 = wdk_expected_filt_a - wdk_expected_from_charge;
      }
      if (wdk_expected_filt_b < wdk_expected_from_charge) {
        bVar4 = wdk_expected_from_charge - wdk_expected_filt_b;
      }
      else {
        bVar4 = wdk_expected_filt_b - wdk_expected_from_charge;
      }
      if ((((uRam00fd6e & 0x8000) == 0) || (nmot_rpmclass <= bRam014709)) || (bVar6 <= bVar4)) {
        uRam00fd70 = uRam00fd70 & 0xffef;
      }
      else {
        uRam00fd70 = uRam00fd70 | 0x10;
      }
    }
    else {
      uRam00fd6e = uRam00fd6e & 0xfdff;
      uRam00fd70 = uRam00fd70 & 0xffef;
    }
    if ((uRam00fd6e & 0x200) != 0) {
      if (bRam014709 < nmot_rpmclass) {
        if (bRam301787 < bRam01470a) {
          bRam301787 = bRam301787 + 1;
          if ((uRam00fd70 & 0x10) == 0) {
            bVar1 = (byte)(bRam301783 + 1) < bRam301783;
            bVar2 = bRam301783 == 0xff;
            bRam301783 = bRam301783 + 1;
            if (bVar1 || bVar2) {
              bRam301783 = 0xff;
            }
          }
          else {
            bVar1 = (byte)(bRam301784 + 1) < bRam301784;
            bVar2 = bRam301784 == 0xff;
            bRam301784 = bRam301784 + 1;
            if (bVar1 || bVar2) {
              bRam301784 = 0xff;
            }
          }
        }
        else if (bRam301783 < bRam301784) {
          uRam00fd6c = uRam00fd6c | 0x8000;
          uRam00fd6e = uRam00fd6e & 0xfdff | 8;
        }
        else {
          uRam00fd6e = uRam00fd6e & 0xfdff | 0x110;
        }
      }
      else {
        bRam301787 = 0;
        bRam301783 = 0;
        bRam301784 = 0;
      }
    }
    if (((uRam00fd6e & 0x10) == 0) &&
       (((uRam00fd6c & 0x8000) != 0 || (((uRam00fd6e & 0x20) == 0 && ((uRam00fd6e & 1) != 0)))))) {
      PSW = PSW | 0x40;
    }
    else {
      PSW = PSW & 0xffbf;
    }
    uRam00fd70 = uRam00fd70 & 0xfff7 | ((PSW & 0x40) >> 6) << 3;
    if ((((uRam00fd6c & 0x8000) == 0) && ((uRam00fd6e & 0x10) == 0)) && ((uRam00fd6e & 0x200) == 0))
    {
      PSW = PSW & 0xffbf;
    }
    else {
      PSW = PSW | 0x40;
    }
    uRam00fd6e = uRam00fd6e & 0xfbff | ((PSW & 0x40) >> 6) << 10;
  }
  MDH = (ushort)((uint)iVar3 >> 0x10);
  MDL = (ushort)iVar3;
  return;
}


// ================= diag_status_frame_init @ 0e018c =================

/* DIAGNOSTIC-CONFIG: initializes the diagnostic status/ID frame RAM block word_300404-word_3004D8
   from 27 config-word+mask pairs 0x2C52A-0x2C580 (pattern: val AND mask, merged with (~mask &
   literal); e.g. 0xE01A4 and r4,word_2C566; 0xE0234/0x2C55E), plus literal seeds
   (#5Fh,#3Bh,#888h,#434Ah,'o','n'); block is consumed by the 0xE1xxx frame packer (sub_E134E copies
   loc_F7B6/C6/C8.. into CAN mirror byte_305780-79D); sole caller sub_642C2 when
   word_300404!=0x3FD0; ends 0xE05F0 or r2,#0Ch -> loc_F5E6 [C mechanism; frame identity I] */

undefined2 diag_status_frame_init(void)

{
  uRam00f7b0 = 0;
  uRam00f7b2 = 0;
  uRam00f7b4 = 0;
  uRam02f7b6 = uRam02c53a & uRam02c566;
  uRam02f7c4 = uRam02c52a & uRam02c556;
  uRam00f7b8 = uRam02c52a & uRam02c556;
  uRam00f7c6 = uRam02c52c & uRam02c558 | ~uRam02c558;
  uRam00f7ba = uRam00f7c6;
  uRam00f7c8 = uRam02c52e & uRam02c55a | ~uRam02c55a & 0xf7ff;
  uRam00f7bc = uRam00f7c8;
  uRam00f7ca = uRam02c530 & uRam02c55c | ~uRam02c55c;
  uRam00f7be = uRam00f7ca;
  uRam00f7ce = uRam02c532 & uRam02c55e | ~uRam02c55e & 0xfff0;
  uRam00f7c0 = uRam00f7ce;
  uRam00f7d0 = uRam02c534 & uRam02c560 | ~uRam02c560 & 0x5fea;
  uRam00f7c2 = uRam00f7d0;
  uRam30041a = 0x5f;
  uRam30041c = 0x3b;
  uRam30041e = 0;
  uRam300420 = 0x20;
  uRam300422 = 0;
  uRam300424 = 0;
  uRam300426 = 0;
  uRam300428 = 0;
  uRam30042a = 0;
  uRam30042c = 0;
  uRam30042e = 0;
  uRam300430 = 0;
  uRam300432 = 0;
  uRam300434 = 0;
  uRam300436 = 0;
  uRam300438 = 0;
  uRam30043a = 0;
  uRam30043c = 0;
  uRam30043e = 0;
  uRam300440 = 0;
  uRam300442 = 0;
  uRam300444 = 0;
  uRam300446 = 0;
  uRam300448 = 0;
  uRam30044a = 0;
  uRam30044c = 0;
  uRam30044e = 0;
  uRam300450 = 0;
  uRam300452 = 0;
  uRam300454 = 0;
  uRam300456 = 0;
  uRam300458 = 0;
  uRam30045a = 0;
  uRam30045c = 0;
  uRam30045e = 0;
  uRam300460 = 0x888;
  uRam300462 = 0x888;
  uRam300464 = 0x888;
  uRam300466 = 0x888;
  uRam300468 = 0x888;
  uRam30046a = 0x888;
  uRam30046c = 0x888;
  uRam30046e = 0x888;
  uRam30048e = 0;
  uRam300490 = 0;
  uRam300492 = 0;
  uRam300494 = 0;
  uRam300496 = 0;
  uRam300498 = 0;
  uRam30049a = 0;
  uRam30049c = 0;
  uRam30049e = 0;
  uRam3004a0 = 0;
  uRam3004a2 = 0;
  uRam3004a4 = 0;
  uRam3004a6 = 0;
  uRam3004a8 = 0;
  uRam3004aa = 0;
  uRam3004ac = 0;
  uRam3004ae = 0;
  uRam3004b0 = 0;
  uRam3004b2 = 0;
  uRam3004b4 = 0;
  uRam3004b6 = 0;
  uRam3004b8 = 0x434a;
  uRam3004ba = 0;
  uRam3004bc = 0;
  uRam3004be = 0x434a;
  uRam3004c0 = 0;
  uRam3004c2 = 0x6f;
  uRam3004c4 = 0;
  uRam3004c6 = 0;
  uRam3004c8 = 0;
  uRam3004ca = 0x6e;
  uRam3004cc = 0;
  uRam3004ce = 0;
  uRam3004d0 = 0;
  uRam300470 = uRam02c536 & uRam02c562 | ~uRam02c562 & 0xff;
  uRam300472 = uRam02c538 & uRam02c564 | ~uRam02c564 & 0xff;
  uRam300474 = uRam02c53c & uRam02c568 | ~uRam02c568 & 0x7d;
  uRam300476 = uRam02c53e & uRam02c56a | ~uRam02c56a & 0x7802;
  uRam300478 = uRam02c540 & uRam02c56c | ~uRam02c56c & 0x50c;
  uRam30047a = uRam02c542 & uRam02c56e | ~uRam02c56e & 0x4f;
  uRam02c47c = uRam02c544 & uRam02c570;
  uRam30047e = uRam02c546 & uRam02c572 | ~uRam02c572 & 0x7f;
  uRam300480 = uRam02c548 & uRam02c574 | ~uRam02c574 & 0xb3;
  uRam300482 = uRam02c54a & uRam02c576 | ~uRam02c576 & 0x85fd;
  uRam300484 = uRam02c54c & uRam02c578 | ~uRam02c578 & 0x98f7;
  uRam300486 = uRam02c54e & uRam02c57a | ~uRam02c57a & 0xff;
  uRam300488 = uRam02c550 & uRam02c57c | ~uRam02c57c & 0x80;
  uRam30048a = uRam02c552 & uRam02c57e | ~uRam02c57e & 0x4c;
  uRam30048c = uRam02c554 & uRam02c580 | ~uRam02c580 & 0xcf;
  uRam3004d2 = 0;
  uRam3004d3 = 0;
  uRam3004d6 = 0;
  uRam3004d8 = 0;
  uRam00f5e6 = uRam02c53c & uRam02c568 | ~uRam02c568 & 0x7d | 0xc;
  return 0x841a;
}


// ================= diag_egt_status_monitor @ 0922b8 =================

/* WARNING: Removing unreachable block (ram,0x092492) */
/* WARNING: Removing unreachable block (ram,0x092b2e) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC: debounced EGT/exhaust status monitor bank (13x debounce sub_32E88, packs status via
   sub_B31AC x2); reads EXA*/EFF* exhaust-diag cals EXAAAA 0x19F1b/EXAFRAO 0x19F2f/EFFZET8
   0x19F11/EFFZZZ 0x19F16 (0x19F10-0x19F37) + 0x23B14-0x23B1A; e.g. 0x92356 cmpb rl4,byte_19F26;
   0x92368 movbz r14,byte_19F27 (debounce delta); sets status bytes byte_30084C/54/6C/78/7A/7C +
   flag bank byte_301624/625; NO actuator/port write (verified: 0 word_FExx/FFxx writes) [C
   mechanism; EGT/exhaust identity I - EXA* shared with egt_sensor_model] */

byte diag_egt_status_monitor(void)

{
  bool bVar1;
  ushort uVar2;
  bool bVar3;
  char cVar4;
  undefined2 uVar5;
  short sVar6;
  short sVar7;
  byte bVar8;
  ushort uStack_10;
  ushort uStack_e;
  
  bVar3 = (uRam00fd0e & 0x1000) != 0;
  uRam30085e = !bVar3 && cRam30085f != '\0';
  if ((bool)uRam30085e) {
    cRam300846 = '\0';
  }
  else if ((_flags_start_phase & 0x8000) != 0) {
    cRam300846 = -1;
  }
  uRam300878 = cRam300846 == '\0' && cRam300879 != '\0';
  if ((bool)uRam300878) {
    egt_diag_status_flags_a = egt_diag_status_flags_a | 0x80;
  }
  else {
    egt_diag_status_flags_a = egt_diag_status_flags_a & 0x7f;
  }
  cRam30085f = bVar3;
  cRam300879 = cRam300846 != '\0';
  bRam304967 = me7_lookup_1d_byte(0x3aea,8,uRam3014d8);
  cRam30086c = func_0x032e88(0x886d,bRam019f26 < bRam304967,uRam019f27);
  cRam30084c = func_0x032ea4(0x884a,_flags_start_phase >> 0xf,uRam023b14);
  if (((cRam30084c == '\0') || ((uRam00fd1c & 0x2000) == 0)) ||
     ((flags_torque_revlimit & 0x80) != 0)) {
    uVar5 = 0;
  }
  else {
    uVar5 = 1;
  }
  cRam300874 = func_0x032ea4(0x8872,uVar5,uRam023b16);
  if (cRam300874 == '\0') {
    egt_diag_status_flags_a = egt_diag_status_flags_a & 0xfd;
  }
  else {
    egt_diag_status_flags_a = egt_diag_status_flags_a | 2;
  }
  bVar3 = bRam304967 < bRam019f25;
  uRam300844 = bVar3 && cRam300845 == '\0';
  if ((bool)uRam300844) {
    bRam304968 = bRam304967;
    bRam304964 = bRam304715;
  }
  uVar2 = (ushort)bRam304967 - (ushort)bRam304968;
  cRam300845 = bVar3;
  if ((bRam019f12 & 2) == 0) {
    if (bRam304967 < bRam019f25) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
  }
  else {
    if ((bRam304967 < bRam019f25) && ((ushort)bRam304964 + (ushort)bRam019f1b <= (ushort)bRam304715)
       ) {
      if ((short)uVar2 < 1) {
        uVar2 = -uVar2;
      }
      if ((uVar2 & 0xff) == (ushort)bRam019f14 || (short)((uVar2 & 0xff) - (ushort)bRam019f14) < 0)
      {
        if ((bRam019f12 & 4) == 0) {
          bVar3 = true;
        }
        else {
          cVar4 = func_0x03306e(0x8868,bRam30a113,uRam019f22,uRam019f21);
          if ((cVar4 == '\0') || ((uRam303bf6 & 1) != 0)) {
            bVar3 = false;
          }
          else {
            bVar3 = true;
          }
        }
        if (bVar3) {
          bVar3 = true;
          goto LAB_0924fc;
        }
      }
    }
    bVar3 = false;
  }
LAB_0924fc:
  if ((bVar3) && ((egt_diag_status_flags_a & 2) != 0)) {
    uVar5 = 1;
  }
  else {
    uVar5 = 0;
  }
  cRam300842 = func_0x032e88(0x8843,uVar5,uRam019f27);
  if ((bRam019f26 < bRam304967) || (bRam304967 < bRam019f25)) {
    uVar5 = 0;
  }
  else {
    uVar5 = 1;
  }
  cRam300864 = func_0x032e88(0x8865,uVar5,uRam019f27);
  if ((bRam30a10d & 0x40) == 0) {
    egt_diag_status_flags_b = egt_diag_status_flags_b | 4;
  }
  else {
    egt_diag_status_flags_b = egt_diag_status_flags_b & 0xfb;
  }
  uVar2 = (ushort)bRam304967 - (ushort)bRam30563a;
  if ((short)uVar2 < 1) {
    uVar2 = -uVar2;
  }
  bVar3 = -1 < (short)((uVar2 & 0xff) - (ushort)bRam019f19);
  bVar1 = (uVar2 & 0xff) != (ushort)bRam019f19;
  cRam30086e = func_0x032e88(0x886f,bVar1 && bVar3,uRam019f2a);
  sVar7 = (ushort)bRam303271 - (ushort)bRam304979;
  if (sVar7 < 1) {
    sVar7 = -sVar7;
  }
  bRam304962 = (byte)sVar7;
  if (((uRam00fd0e & 0x1000) == 0) || ((_flags_start_phase & 0x8000) == 0)) {
    uVar5 = 0;
  }
  else {
    uVar5 = 1;
  }
  cRam300856 = func_0x032e88(0x8857,uVar5,uRam019f2c);
  if ((((bRam304979 < bRam019f30) || (bRam019f2f < bRam304979)) || (bRam303271 < bRam019f2d)) ||
     ((bRam304962 < bRam019f18 || (cRam300856 == '\0')))) {
    egt_diag_status_flags_a = egt_diag_status_flags_a & 0xfe;
  }
  else {
    egt_diag_status_flags_a = egt_diag_status_flags_a | 1;
  }
  if ((uRam00fd52 & 0x1000) != 0) {
    egt_diag_status_flags_b = egt_diag_status_flags_b | 1;
  }
  cRam300862 = func_0x032ea4(0x8860,_flags_start_phase >> 0xf,uRam023b18);
  if (cRam300862 == '\0') {
    egt_diag_status_flags_b = egt_diag_status_flags_b & 0xf7;
  }
  else {
    egt_diag_status_flags_b = egt_diag_status_flags_b | 8;
  }
  if (((bVar1 && bVar3) || ((egt_diag_status_flags_a & 1) == 0)) || (uRam023b1a <= uRam305630)) {
    if (((cRam30086e != '\0') && ((egt_diag_status_flags_a & 1) != 0)) && (uRam305630 < uRam023b1a))
    {
      cRam30087e = -1;
    }
  }
  else {
    cRam30087e = '\0';
  }
  if (((cRam30086e == '\0') || ((egt_diag_status_flags_a & 1) == 0)) || (uRam023b1a <= uRam305630))
  {
    if (((!bVar1 || !bVar3) && ((egt_diag_status_flags_a & 1) != 0)) && (uRam305630 < uRam023b1a)) {
      cRam30085a = -1;
    }
  }
  else {
    cRam30085a = '\0';
  }
  if (((bRam019f1c < bRam01b472) && (bRam00f472 < bRam019f1d)) && (bRam019f36 <= vfzg_class)) {
    uVar5 = 1;
  }
  else {
    uVar5 = 0;
  }
  cRam300850 = func_0x032e88(0x8851,uVar5,uRam019f2b);
  if (((cRam300850 == '\0') || (bRam304967 < bRam019f23)) || ((egt_diag_status_flags_b & 4) != 0)) {
    cVar4 = '\0';
  }
  else {
    cVar4 = '\x01';
  }
  if (cVar4 == '\0') {
    if ((cRam300850 != '\0') && (bRam304967 < bRam019f23)) {
      cRam300852 = -1;
    }
  }
  else {
    cRam300852 = '\0';
  }
  if (((_flags_start_phase & 0x8000) != 0) &&
     ((ushort)bRam304967 != (ushort)bRam304965 &&
      -1 < (short)((ushort)bRam304967 - (ushort)bRam304965))) {
    bRam304965 = bRam304967;
  }
  if (((_flags_start_phase & 0x8000) != 0) &&
     ((ushort)bRam304966 != (ushort)bRam304967 &&
      -1 < (short)((ushort)bRam304966 - (ushort)bRam304967))) {
    bRam304966 = bRam304967;
  }
  if (((((vfzg_class < bRam019f34) || (bRam01b472 <= bRam019f1f)) || (bRam019f1e <= bRam00f472)) ||
      (((uRam00fd1c & 0x2000) != 0 || ((flags_torque_revlimit & 0x80) != 0)))) ||
     (bRam019f31 < bRam304979)) {
    bRam301623 = bRam301623 & 0xfe;
  }
  else {
    bRam301623 = bRam301623 | 1;
  }
  cRam300876 = func_0x032e88(0x8877,(bRam301623 & 1) != 0,uRam019f28);
  bVar3 = cRam300876 != '\0';
  uRam300848 = bVar3 && cRam300849 == '\0';
  cRam300849 = bVar3;
  if ((bool)uRam300848) {
    func_0x032fc4(0x8840,1,0,0xff);
  }
  bRam304969 = bRam300840;
  if (((bRam019f31 < bRam304979) || ((uRam00fd1c & 0x2000) == 0)) ||
     ((bRam019f35 < vfzg_class || (rpmclass_oppoint <= bRam019f2e)))) {
    bRam301623 = bRam301623 & 0xfd;
  }
  else {
    bRam301623 = bRam301623 | 2;
  }
  cRam300870 = func_0x032e88(0x8871,(bRam301623 & 2) != 0,uRam019f29);
  bVar3 = cRam300870 != '\0';
  uRam300858 = bVar3 && cRam300859 == '\0';
  cRam300859 = bVar3;
  if ((bool)uRam300858) {
    func_0x032fc4(0x884e,1,0,0xff);
  }
  bRam30496a = bRam30084e;
  if (((((bRam305625 & 4) == 0) &&
       (sVar7 = (ushort)bRam304965 - (ushort)bRam304966,
       (short)(sVar7 - (ushort)bRam019f15) < 0 !=
       (sVar7 < 0 && (short)(sVar7 - (ushort)bRam019f15) < 0 != sVar7 < 0))) &&
      (bRam019f10 <= bRam304969)) && (bRam019f11 <= bRam30084e)) {
    egt_diag_status_flags_b = egt_diag_status_flags_b | 2;
  }
  else {
    egt_diag_status_flags_b = egt_diag_status_flags_b & 0xfd;
  }
  sVar7 = (ushort)bRam304965 - (ushort)bRam304966;
  if ((((short)(sVar7 - (ushort)bRam019f15) < 0 ==
        (sVar7 < 0 && (short)(sVar7 - (ushort)bRam019f15) < 0 != sVar7 < 0)) &&
      (bRam019f10 <= bRam304969)) && (bRam019f11 <= bRam30084e)) {
    egt_diag_status_flags_b = egt_diag_status_flags_b | 0x10;
  }
  else {
    egt_diag_status_flags_b = egt_diag_status_flags_b & 0xef;
  }
  if ((((egt_diag_status_flags_b & 4) == 0) && (cRam30087e != '\0')) &&
     (((egt_diag_status_flags_b & 1) == 0 && ((egt_diag_status_flags_b & 8) != 0)))) {
    uVar5 = 1;
  }
  else {
    uVar5 = 0;
  }
  cRam300854 = func_0x032e88(0x8855,uVar5,uRam019f27);
  cRam30087a = func_0x032e88(0x887b,(bRam019f12 & 1) != 0 && (egt_diag_status_flags_b & 2) != 0,
                             uRam019f27);
  cRam30087c = func_0x032e88(0x887d,cVar4,uRam019f27);
  if (((((egt_diag_status_flags_b & 4) == 0) && (cRam30085a != '\0')) &&
      ((bRam019f12 & 1) == 0 || (egt_diag_status_flags_b & 0x10) != 0)) && (cRam300852 != '\0')) {
    uVar5 = 1;
  }
  else {
    uVar5 = 0;
  }
  cRam300866 = func_0x032e88(0x8867,uVar5,uRam019f27);
  if ((egt_diag_status_flags_b & 8) == 0) {
    if ((bRam019f13 & 1) != 0) {
      uVar2 = uRam303bea;
      if ((bRam019f13 & 2) != 0) {
        uVar2 = uRam303bf6;
      }
      if ((uVar2 & 1) == 0) {
        if ((bRam019f13 & 2) == 0) {
          sVar7 = (ushort)bRam303271 - (ushort)rpmclass_oppoint;
          if (sVar7 < 1) {
            sVar7 = -sVar7;
          }
          bRam304961 = (byte)sVar7;
          if (bRam019f16 < bRam304961) {
            if (bRam304961 < bRam019f17) {
              bRam304963 = bRam019f24;
            }
            else {
              sVar7 = (ushort)rpmclass_oppoint - (ushort)bRam019f20;
              if (sVar7 < 0) {
                sVar7 = 0;
              }
              bRam304963 = (byte)sVar7;
            }
          }
          else {
            bRam304963 = bRam30a025;
          }
        }
        else {
          cRam30086a = func_0x032e88(0x886b,_flags_start_phase >> 0xf,uRam019f33);
          if (cRam30086a == '\0') {
            bRam304963 = bRam019f24;
          }
          else {
            sVar7 = (ushort)bRam30a113 + (ushort)bRam019f32;
            sVar6 = sVar7 + -0x40;
            if (sVar6 < 0) {
              sVar6 = 0;
            }
            else if (sVar6 != 0xff &&
                     sVar7 + -0x13f < 0 == (sVar6 < 0 && sVar7 + -0x13f < 0 != sVar6 < 0)) {
              sVar6 = 0xff;
            }
            bRam304963 = (byte)sVar6;
          }
        }
        goto LAB_092c5a;
      }
    }
    bRam304963 = bRam019f24;
  }
LAB_092c5a:
  uStack_e = uRam303bd8;
  if (cRam30086c == '\0') {
    if (cRam300842 == '\0') {
      if (cRam300864 != '\0') {
        uStack_e = ((uRam303bd8 & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
      }
    }
    else {
      uStack_e = (uRam303bd8 >> 8 & 0x90 | 0x62) << 8 | 2;
    }
  }
  else {
    uStack_e = (uRam303bd8 >> 8 & 0x90 | 0x61) << 8 | 2;
  }
  func_0x0b31ac(0xa9,uStack_e);
  uStack_10 = uRam303bda;
  if (cRam30087c == '\0') {
    if (cRam300854 == '\0') {
      if (cRam30087a == '\0') {
        if (cRam300866 != '\0') {
          uStack_10 = ((uRam303bda & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
        }
      }
      else {
        uStack_10 = (uRam303bda >> 8 & 0x90 | 0x68) << 8 | 2;
      }
    }
    else {
      uStack_10 = (uRam303bda >> 8 & 0x90 | 0x62) << 8 | 2;
    }
  }
  else {
    uStack_10 = (uRam303bda >> 8 & 0x90 | 0x61) << 8 | 2;
  }
  func_0x0b31ac(0xaa,uStack_10);
  func_0x0b8250(0x3ae2,8);
  if (((uRam303bd8 & 1) != 0) || (bVar8 = bRam304967, (uRam303bda & 1) != 0)) {
    bVar8 = bRam304963;
  }
  uRam30085c = me7_fraction_blend((ushort)bRam019f37 << 8,bVar8,uRam30085c);
  uVar5 = uRam30085c;
  uRam30085c._1_1_ = (byte)((ushort)uRam30085c >> 8);
  bRam301626 = uRam30085c._1_1_;
  sRam3052f0 = (ushort)uRam30085c._1_1_ * 0x20 + 0x2586;
  if ((bRam305624 & 0x80) != 0) {
    bRam30a025 = uRam30085c._1_1_;
    sRam30a1cc = sRam3052f0;
  }
  uRam30085c = uVar5;
  return bRam305624 & 0x80;
}


// ================= diag_o2_sensor_status_pack @ 06c6da =================

/* WARNING: Removing unreachable block (ram,0x06d034) */
/* WARNING: Removing unreachable block (ram,0x06d218) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC: O2/lambda-sensor diagnostic status packer, gated by codeword byte_301220.1 (CDSLS);
   34x debounce sub_32E88 + 12x CAN-pack sub_B31AC of status words word_303B70/74/64 (e.g. 0x6C73A
   calls sub_B31AC with tag #75h); reads threshold band 0x210CA-0x21104 incl. MSDRKAT
   0x210cc/MSDRKAT2 0x210ec (0x6D454 cmp r8,MSDRKAT) + NDLDRAPU 0x18a78 + 0x1FFF6/0x1FFFA; adjacent
   dict FLAMPFT/FLAMPMR/Nernst-cell-temp confirm lambda/exhaust; no actuator write [C mechanism;
   O2/lambda identity I] */

void diag_o2_sensor_status_pack(void)

{
  short sVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  short sVar5;
  ushort uVar6;
  bool bVar7;
  undefined4 uVar8;
  undefined2 uVar9;
  ushort uVar10;
  ushort uVar11;
  ushort uVar12;
  ushort uVar13;
  ushort uVar14;
  ushort uVar15;
  ushort uVar16;
  
  uVar14 = uRam303b74;
  uVar15 = _o2_diag_status_word;
  uVar13 = uRam303b6c;
  uVar12 = uRam303b68;
  uVar16 = uRam303b64;
  uVar11 = uRam303b30;
  if ((flags_diag_enable_c & 2) == 0) {
    uVar11 = ((_o2_diag_status_word & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
    func_0x0b31ac(0x75,uVar11,uVar11);
    uVar11 = ((uRam303b74 & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
    func_0x0b31ac(0x77,uVar11,uVar11);
    uVar14 = ((uRam303b64 & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
    func_0x0b31ac(0x6f,uVar14,uVar11,uVar14);
    uVar15 = ((uRam303b68 & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
    func_0x0b31ac(0x71,uVar15,uVar15,uVar11,uVar14);
    uVar16 = ((uRam303b6c & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
    func_0x0b31ac(0x73,uVar16,uVar15,uVar16,uVar11,uVar14);
    uVar12 = ((uRam303b30 & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
    func_0x0b31ac(0x55,uVar12,uVar12,uVar15,uVar16,uVar11,uVar14);
    uVar8 = CONCAT22(uRam3005a2._2_2_,(undefined2)uRam3005a2);
    goto LAB_06d976;
  }
  uVar8 = uRam3005a2;
  if ((((uRam021104 < uRam302dc0) || (uRam302dc0 < 0x6b00)) || ((_flags_start_phase & 0x8000) == 0))
     || ((uRam00fd0e & 0x1000) == 0)) goto LAB_06d976;
  uVar10 = uRam3035d4;
  if ((short)uRam3035d4 < 1) {
    uVar10 = -uRam3035d4;
  }
  sVar1 = (short)uRam0210e6 >> 0xf;
  sVar5 = -(ushort)(uVar10 < uRam0210e6);
  if (sVar5 == sVar1 && uVar10 == uRam0210e6 ||
      sVar5 - sVar1 < 0 != (sVar1 < 0 && (short)(-(ushort)(uVar10 < uRam0210e6) - sVar1) < 0)) {
    uVar10 = uRam3035d2;
    if ((short)uRam3035d2 < 1) {
      uVar10 = -uRam3035d2;
    }
    sVar5 = -(ushort)(uVar10 < uRam0210e6);
    if ((sVar5 != sVar1 || uVar10 != uRam0210e6) &&
        sVar5 - sVar1 < 0 == (sVar1 < 0 && (short)(-(ushort)(uVar10 < uRam0210e6) - sVar1) < 0))
    goto LAB_06c960;
    bRam30148f = bRam30148f & 0xfd;
  }
  else {
LAB_06c960:
    bRam30148f = bRam30148f | 2;
  }
  func_0x032ef0(0x8554,(bRam30148f & 2) != 0,100);
  cRam30056e = func_0x032e88(0x856f,(uRam00fd30 & 8) >> 3,100);
  if ((uRam00fd30 & 8) != 0) {
    cRam30057c = func_0x032e88(0x857d,0,uRam018a77);
    cRam30056a = func_0x032e88(0x856b,0,uRam018a77);
    cRam30056c = func_0x032e88(0x856d,0,uRam018a77);
    cRam300578 = func_0x032e88(0x8579,0,uRam018a77);
    cRam300576 = func_0x032e88(0x8577,0,uRam018a77);
    cRam30057a = func_0x032e88(0x857b,0,uRam018a77);
    cRam30058e = func_0x032e88(0x858f,0,uRam018a78);
    cRam300556 = func_0x032e88(0x8557,0,uRam018a6f);
    bRam30148f = bRam30148f & 0xf7;
    cRam3005b0 = FUN_032ebe((short)s_pppppppppppppppppppppppp_________018599 + 0x18,1,0);
    cRam3005ae = func_0x032e88((short)s_pppppppppppppppppppppppp_________018599 + 0x16,0,10);
    cRam300570 = func_0x032e88(0x8571,0,uRam018a72);
    cRam3005a6 = func_0x032e88((short)s_pppppppppppppppppppppppp_________018599 + 0xe,0,uRam018a74);
  }
  if ((((bRam30148f & 2) == 0) && ((uRam00fd30 & 4) == 0)) &&
     (((uRam00fd30 & 2) == 0 && ((uRam00fd30 & 8) == 0)))) {
    bRam30148f = bRam30148f & 0xfe;
  }
  else {
    bRam30148f = bRam30148f | 1;
  }
  cRam30058e = func_0x032e88(0x858f,(bRam30148f & 1) == 0,uRam018a78);
  if (cRam300554 == '\0') {
    if (cRam30056e != '\0') {
      uVar11 = (uVar11 >> 8 & 0xfff0 | 2) << 8;
      goto LAB_06cb6a;
    }
    if ((uRam00fd30 & 2) != 0) {
      uVar11 = (uVar11 >> 8 & 0xfff0 | 8) << 8;
      goto LAB_06cb6a;
    }
    if ((uRam00fd30 & 4) != 0) {
      uVar11 = (uVar11 >> 8 & 0xfff0 | 4) << 8;
      goto LAB_06cb6a;
    }
    if (cRam30058e != '\0') {
      uVar11 = uVar11 & 0xf0fe;
      goto LAB_06cb6a;
    }
  }
  else {
    uVar11 = (uVar11 >> 8 & 0xfff0 | 1) << 8;
LAB_06cb6a:
    uVar11 = (uVar11 >> 8 & 0x9f | 0x60) << 8 | 2;
  }
  func_0x0b31ac(0x55,uVar11);
  cRam30057c = func_0x032e88(0x857d,(uRam00fd30 & 0x80) >> 7,uRam018a77);
  cRam30056c = func_0x032e88(0x856d,uRam00fd30 & 1,uRam018a77);
  cRam300578 = func_0x032e88(0x8579,(uRam00fd30 & 0x20) >> 5,uRam018a77);
  cRam300576 = func_0x032e88(0x8577,(uRam00fd30 & 0x10) >> 4,uRam018a77);
  cRam30057a = func_0x032e88(0x857b,(uRam00fd30 & 0x40) >> 6,uRam018a77);
  cRam30056a = func_0x032e88(0x856b,uRam00fd2e >> 0xf,uRam018a77);
  cRam300568 = FUN_032ebe(0x8569,uRam00fd2e >> 0xf,0x32);
  uVar11 = uRam302688;
  if (cRam300568 == '\0') {
    bRam301490 = bRam301490 & 0xfb;
  }
  else {
    bRam301490 = bRam301490 | 4;
  }
  cRam300556 = func_0x032e88(0x8557,(bRam301468 & 1) != 0,uRam018a6f);
  if (cRam300556 != '\0') {
    bRam301494 = bRam301494 | 0x10;
  }
  if ((((bRam301494 & 0x10) == 0) || ((bRam304736 & 1) != 0)) ||
     (((bRam30146a & 4) != 0 || (uRam305088 < uRam0210ec)))) {
    bRam301493 = bRam301493 & 0xef;
  }
  else {
    bRam301493 = bRam301493 | 0x10;
  }
  if (((bRam301493 & 0x10) == 0) || ((bRam30148f & 8) != 0)) {
    uVar9 = 0;
  }
  else {
    uVar9 = 1;
  }
  cRam3005a8 = func_0x032e88((short)s_pppppppppppppppppppppppp_________018599 + 0x10,uVar9,
                             uRam018a76);
  if (cRam3005a8 != '\0') {
    bRam30148f = bRam30148f | 8;
  }
  cRam300582 = func_0x032e88(0x8583,(bRam30148f & 8) != 0,0x14);
  if (((bRam301494 & 0x10) == 0) || (uRam0210ec <= uRam305088)) {
    bRam301493 = bRam301493 & 0xdf;
  }
  else {
    bRam301493 = bRam301493 | 0x20;
  }
  if ((uRam0210fc < uRam02271e) && (uRam30271e < uRam0210fe)) {
    uVar9 = 1;
  }
  else {
    uVar9 = 0;
  }
  cRam3005b0 = FUN_032ebe((short)s_pppppppppppppppppppppppp_________018599 + 0x18,uVar9,6);
  if ((bRam301485 & 2) != 0) {
    bRam301496 = 0;
  }
  bVar3 = (bRam301468 & 0x10) != 0;
  cRam30055a = bVar3 && cRam30055b == '\0';
  cRam30055b = bVar3;
  func_0x032f14((short)s_pppppppppppppppppppppppp_________018599 + 0x11,
                (flags_torque_revlimit & 0x80) >> 7,uRam0210f4);
  if (((((uRam00fd0e & 0x1000) == 0) || ((uRam00fd2c & 0x100) != 0)) || (cRam3005ac != '\0')) ||
     (uRam302dc0 < 0x6e00)) {
    bVar3 = true;
  }
  else {
    bVar3 = false;
  }
  if ((cRam30055a != '\0') || (bVar3)) {
    uVar9 = 1;
  }
  else {
    uVar9 = 0;
  }
  func_0x032f5c(0x8584,uVar9,uRam0210f2);
  if (cRam300586 == '\0') {
    bRam301495 = bRam301495 | 0x10;
  }
  else {
    bRam301495 = bRam301495 & 0xef;
  }
  if (((cRam3005b0 != '\0') && ((bRam301493 & 0x10) != 0)) && (bRam018a7a < bRam301496)) {
    bRam301492 = bRam301492 | 0x10;
  }
  if ((uRam0210fa < uRam30271e) || (uRam30271e < uRam0210f8)) {
    uVar9 = 1;
  }
  else {
    uVar9 = 0;
  }
  cRam3005ae = func_0x032e88((short)s_pppppppppppppppppppppppp_________018599 + 0x16,uVar9,10);
  cRam300558 = func_0x032e88(0x8559,cRam300582,0x14);
  if (cRam300558 != '\0') {
    bRam30148f = bRam30148f & 0xf7;
  }
  if ((((cRam300582 != '\0') && (cRam3005ae != '\0')) && ((bRam304736 & 1) == 0)) &&
     ((bRam30146a & 4) == 0)) {
    bRam301492 = bRam301492 | 4;
  }
  if ((((bRam301468 & 4) == 0) || ((flags_torque_revlimit & 0x80) == 0)) ||
     ((uRam0210f0 <= uRam305004 || (((_flags_start_phase & 0x8000) == 0 || ((bRam30146a & 4) != 0)))
      ))) {
    bVar3 = false;
  }
  else {
    bVar3 = true;
  }
  if ((bVar3) && (uRam01fff6 <= uRam30271e)) {
    uVar9 = 1;
  }
  else {
    uVar9 = 0;
  }
  cRam300570 = func_0x032e88(0x8571,uVar9,uRam018a72);
  if (cRam300570 == '\0') {
    bRam301495 = bRam301495 & 0xfe;
  }
  else {
    bRam301495 = bRam301495 | 1;
  }
  if (((bRam3015c8 & 0x40) == 0) && ((bRam3015c8 & 0x80) != 0)) {
    bRam301493 = bRam301493 | 4;
  }
  else {
    bRam301493 = bRam301493 & 0xfb;
  }
  if (((bRam3015c8 & 0x40) == 0) || ((bRam3015c8 & 0x80) == 0)) {
    bRam301493 = bRam301493 & 0xfd;
  }
  else {
    bRam301493 = bRam301493 | 2;
  }
  if ((bRam3015c8 & 0x80) == 0) {
    bRam301493 = bRam301493 | 8;
  }
  else {
    bRam301493 = bRam301493 & 0xf7;
  }
  if ((((bRam301495 & 1) == 0) || ((bRam301493 & 2) == 0)) &&
     (((bRam301495 & 1) == 0 || ((bRam301493 & 8) == 0)))) {
    bVar4 = false;
  }
  else {
    bVar4 = true;
  }
  cRam300574 = func_0x032ea4(0x8572,(bRam301495 & 4) != 0,uRam01fffa);
  if ((((bRam301495 & 1) != 0) && ((bRam301493 & 4) != 0)) || ((bVar4 && (cRam300574 != '\0')))) {
    bRam301492 = bRam301492 | 1;
  }
  else {
    bRam301492 = bRam301492 & 0xfe;
  }
  if ((bRam301492 & 1) != 0) {
    bRam301490 = bRam301490 | 0x40;
  }
  if ((bVar3) && (uRam30271e < uRam01fff6)) {
    uVar9 = 1;
  }
  else {
    uVar9 = 0;
  }
  cRam30058c = func_0x032e88(0x858d,uVar9,uRam018a73);
  uVar10 = uRam303ada;
  if (((uRam302634 & 1) == 0) || ((bRam018a6e & 1) == 0)) {
    bVar3 = false;
  }
  else {
    bVar3 = true;
  }
  if ((cRam30058c != '\0') || (bVar3)) {
    bRam301494 = bRam301494 | 1;
  }
  uVar6 = DAT_00fd34 & 0x100;
  if ((uRam021100 < uRam02271e) && (uRam30271e < uRam021102)) {
    uVar9 = 1;
  }
  else {
    uVar9 = 0;
  }
  cRam300598 = func_0x032e88((short)s_pppppppppppppppppppppppp_________018599,uVar9,uRam018a71);
  if (cRam300598 == '\0') {
    bRam301490 = bRam301490 & 0xfe;
  }
  else {
    bRam301490 = bRam301490 | 1;
  }
  if (((uVar6 == 0) ||
      (((((uRam0210e8 < uRam02294c && (uRam30294c < uRam0210ea)) || ((bRam301490 & 1) == 0)) ||
        (((uVar10 & 0xf00) == 0x200 || ((bRam301468 & 4) == 0)))) || ((bRam30146a & 4) != 0)))) ||
     ((bRam00f348 & 2) != 0)) {
    bRam301491 = bRam301491 & 0xfb;
  }
  else {
    bRam301491 = bRam301491 | 4;
  }
  if (((uRam303b26 & 1) == 0) && ((bRam301491 & 4) != 0)) {
    bVar3 = true;
  }
  else {
    bVar3 = false;
  }
  if (bVar3) {
    uVar9 = me7_lookup_1d_word(0x10d0,8,uRam30294c);
    uRam3005a2 = me7_integrator_sat(uVar9,uVar11 >> 1,uRam3005a2._2_2_,(undefined2)uRam3005a2);
    if ((bRam301491 & 1) != 0) goto LAB_06d18c;
    uVar9 = 1;
  }
  else {
LAB_06d18c:
    uVar9 = 0;
  }
  cRam3005a0 = FUN_032ebe((short)s_pppppppppppppppppppppppp_________018599 + 8,uVar9,uRam018a79);
  uRam30059e = cRam3005a0 != '\0' && cRam30059f == '\0';
  if (((bool)uRam30059e) || (uVar8 = uRam3005a2, (bRam301490 & 1) == 0)) {
    uVar8 = 0;
  }
  uRam3005a2._2_2_ = (short)((uint)uVar8 >> 0x10);
  uRam3050d4 = uRam3005a2._2_2_ * 2;
  if (uRam0210ce < uRam3050d4) {
    bRam301491 = bRam301491 | 1;
  }
  else {
    bRam301491 = bRam301491 & 0xfe;
  }
  if ((((uRam303be0 & 1) == 0) && ((uRam303be0 & 2) != 0)) && ((flags_torque_revlimit & 0x80) != 0))
  {
    uVar9 = 1;
  }
  else {
    uVar9 = 0;
  }
  cRam30059f = cRam3005a0 != '\0';
  uRam3005a2 = uVar8;
  cRam300580 = func_0x032e88(0x8581,uVar9,0x1e);
  if ((((bRam301468 & 4) == 0) || (uRam0210ee <= uRam30271e)) ||
     ((cRam300580 == '\0' || ((bRam30146a & 4) != 0)))) {
    uVar9 = 0;
  }
  else {
    uVar9 = 1;
  }
  cRam3005a6 = func_0x032e88((short)s_pppppppppppppppppppppppp_________018599 + 0xe,uVar9,uRam018a74
                            );
  if (cRam3005a6 != '\0') {
    bRam301494 = bRam301494 | 0x40;
  }
  uVar11 = uRam30280a;
  if ((short)uRam30280a < 1) {
    uVar11 = -uRam30280a;
  }
  cRam300588 = func_0x032e88(0x8589,uRam0210ca <= uVar11,uRam018a70);
  bVar3 = (DAT_00fd34 & 0x100) != 0;
  uRam300566 = bVar3 && cRam300567 == '\0';
  bVar4 = (DAT_00fd34 & 0x20) != 0;
  if (bVar4) {
    uRam300564 = cRam300565 == '\0';
  }
  else {
    uRam300564 = cRam300565 != '\0';
  }
  bVar2 = (bRam3018ce & 2) == 0;
  if (bVar2) {
    uRam300562 = cRam300563 != '\0';
  }
  else {
    uRam300562 = cRam300563 == '\0';
  }
  cRam300563 = !bVar2;
  bVar2 = (_flags_idle_state & 0x200) != 0;
  if (bVar2) {
    uRam300560 = cRam300561 == '\0';
  }
  else {
    uRam300560 = cRam300561 != '\0';
  }
  if (((((bRam00f348 & 2) != 0) || ((bRam301468 & 4) == 0)) ||
      (((bRam301468 & 1) == 0 ||
       ((((DAT_00fd34 & 0x100) == 0 || ((bRam301490 & 1) == 0)) || (cRam300588 == '\0')))))) ||
     ((((((uRam00fd36 & 0x1000) == 0 || ((bool)uRam300566)) || ((DAT_00fd34 & 2) != 0)) ||
       (((bool)uRam300564 != false || ((bool)uRam300562 != false)))) ||
      (((bool)uRam300560 != false || ((bRam30146a & 4) != 0)))))) {
    bVar7 = false;
  }
  else {
    bVar7 = true;
  }
  uRam30059c = bVar7 && cRam30059d == '\0';
  if ((bool)uRam30059c) {
    uRam3050d2 = uRam302816;
  }
  if ((bVar7) &&
     (uRam3050d0 = uRam3050d2 - uRam302816,
     -(ushort)(uRam3050d2 < uRam302816) == 0 && uRam3050d0 == 0 ||
     (short)-(ushort)(uRam3050d2 < uRam302816) < 0)) {
    uRam3050d0 = -uRam3050d0;
  }
  if ((bVar7) && (uRam0210cc < uRam3050d0)) {
    uVar9 = 1;
  }
  else {
    uVar9 = 0;
  }
  cRam300561 = bVar2;
  cRam300565 = bVar4;
  cRam300567 = bVar3;
  cRam30059d = bVar7;
  cRam30057e = func_0x032e88(0x857f,uVar9,uRam018a75);
  if (cRam30057e != '\0') {
    bRam301494 = bRam301494 | 4;
  }
  if (((bRam301493 & 0x20) == 0) || ((bRam301492 & 0x10) != 0)) {
    uVar9 = 0;
  }
  else {
    uVar9 = 1;
  }
  cRam300596 = func_0x032e88(0x8597,uVar9,uRam018a78);
  if (((bRam301493 & 0x20) == 0) || ((bRam301492 & 4) != 0)) {
    uVar9 = 0;
  }
  else {
    uVar9 = 1;
  }
  cRam300594 = func_0x032e88(0x8595,uVar9,uRam018a78);
  if (((bRam301490 & 0x40) == 0) && ((bRam301494 & 1) != 0)) {
    cRam30058a = cRam30058b == '\0';
    cRam30058b = '\x01';
  }
  else {
    cRam30058a = false;
    cRam30058b = '\0';
  }
  if ((((bRam301494 & 4) == 0) && ((bRam301491 & 1) == 0)) && ((bRam301494 & 0x40) == 0)) {
    bVar3 = false;
  }
  else {
    bVar3 = true;
  }
  if ((((uRam00fd36 & 0x1000) != 0) && ((bRam301468 & 4) != 0)) &&
     ((!bVar3 && (((bRam301490 & 1) == 0 && (uRam300590 != 0xffff)))))) {
    uRam300590 = uRam300590 + 1;
  }
  if (bVar3) {
    uRam300590 = 0;
  }
  uRam3050d6 = uRam300590;
  if (uRam0210f6 < uRam300590) {
    bRam301490 = bRam301490 | 0x10;
  }
  else {
    bRam301490 = bRam301490 & 0xef;
  }
  if (((((cRam30057c == '\0') && (cRam30056c == '\0')) && (cRam300578 == '\0')) &&
      ((cRam300576 == '\0' && (cRam30057a == '\0')))) &&
     ((cRam30056a == '\0' && ((bRam30146a & 4) == 0)))) {
    uVar9 = 1;
  }
  else {
    uVar9 = 0;
  }
  cRam300592 = func_0x032e88(0x8593,uVar9,uRam018a78);
  if ((bRam301492 & 0x10) == 0) {
    if (cRam300596 != '\0') {
      uVar14 = uVar14 & 0xf0fe;
      goto LAB_06d60c;
    }
  }
  else {
    uVar14 = (uVar14 >> 8 & 0xfff0 | 4) << 8;
LAB_06d60c:
    uVar14 = (uVar14 >> 8 & 0x9f | 0x60) << 8 | 2;
  }
  func_0x0b31ac(0x77,uVar14);
  if ((bRam301492 & 4) == 0) {
    if (cRam300594 != '\0') {
      uVar15 = uVar15 & 0xf0fe;
      goto LAB_06d680;
    }
  }
  else {
    uVar15 = (uVar15 >> 8 & 0xfff0 | 4) << 8;
LAB_06d680:
    uVar15 = (uVar15 >> 8 & 0x9f | 0x60) << 8 | 2;
  }
  func_0x0b31ac(0x75,uVar15);
  if ((bRam301490 & 0x40) == 0) {
    if (cRam30058a != '\0') {
      uVar16 = uVar16 & 0xf0fe;
      goto LAB_06d6f4;
    }
  }
  else {
    uVar16 = (uVar16 >> 8 & 0xfff0 | 4) << 8;
LAB_06d6f4:
    uVar16 = (uVar16 >> 8 & 0x9f | 0x60) << 8 | 2;
  }
  func_0x0b31ac(0x6f,uVar16);
  if ((bRam301491 & 1) == 0) {
    if ((bRam301494 & 0x40) != 0) {
      uVar12 = (uVar12 >> 8 & 0xfff0 | 8) << 8;
      goto LAB_06d7ae;
    }
    if ((bRam301494 & 4) != 0) {
      uVar12 = (uVar12 >> 8 & 0xfff0 | 1) << 8;
      goto LAB_06d7ae;
    }
    if ((bRam301490 & 0x10) != 0) {
      uVar12 = uVar12 & 0xf0fe;
      goto LAB_06d7ae;
    }
  }
  else {
    uVar12 = (uVar12 >> 8 & 0xfff0 | 4) << 8;
LAB_06d7ae:
    uVar12 = (uVar12 >> 8 & 0x9f | 0x60) << 8 | 2;
  }
  func_0x0b31ac(0x71,uVar12);
  if (((cRam30057c == '\0') && (cRam30056c == '\0')) && (cRam300578 == '\0')) {
    if (((cRam300576 != '\0') || (cRam30057a != '\0')) || (cRam30056a != '\0')) {
      uVar13 = (uVar13 >> 8 & 0xfff0 | 2) << 8;
      goto LAB_06d858;
    }
    if (cRam300592 != '\0') {
      uVar13 = uVar13 & 0xf0fe;
      goto LAB_06d858;
    }
  }
  else {
    uVar13 = (uVar13 >> 8 & 0xfff0 | 1) << 8;
LAB_06d858:
    uVar13 = (uVar13 >> 8 & 0x9f | 0x60) << 8 | 2;
  }
  func_0x0b31ac(0x73,uVar13);
  if ((((((uRam303b74 & 1) == 0) || ((uRam303b74 & 2) == 0)) &&
       (((_o2_diag_status_word & 1) == 0 || ((_o2_diag_status_word & 2) == 0)))) &&
      (((uRam303b64 & 1) == 0 || ((uRam303b64 & 2) == 0)))) &&
     ((((uRam303b68 & 1) == 0 || ((uRam303b68 & 2) == 0)) &&
      (((uRam303b6c & 1) == 0 || ((uRam303b6c & 2) == 0)))))) {
    bRam30148f = bRam30148f & 0xfb;
  }
  else {
    bRam30148f = bRam30148f | 4;
  }
  if (((uRam303b30 & 1) != 0) && ((uRam303b30 & 2) != 0)) {
    bRam304d9a = bRam304d9a | 0x20;
  }
  if (((uRam303b74 & 1) != 0) && ((uRam303b74 & 2) != 0)) {
    bRam304d9e = bRam304d9e | 0x80;
  }
  if (((_o2_diag_status_word & 1) != 0) && ((_o2_diag_status_word & 2) != 0)) {
    bRam304d9e = bRam304d9e | 0x20;
  }
  if (((uRam303b64 & 1) != 0) && ((uRam303b64 & 2) != 0)) {
    bRam304d9d = bRam304d9d | 0x80;
  }
  uVar8 = uRam3005a2;
  if (((uRam303b68 & 1) != 0) && ((uRam303b68 & 2) != 0)) {
    bRam304d9e = bRam304d9e | 2;
  }
LAB_06d976:
  uRam3005a2._2_2_ = (short)((uint)uVar8 >> 0x10);
  uRam3005a2._0_2_ = (undefined2)uVar8;
  return;
}


// ================= diag_evap_purge_monitor @ 09d894 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC: EVAP purge-system monitor; gated by codeword word_3018D6.1 + word_FD02.9; reads purge
   quantity word_3052A8 (produced by evap_purge_ctrl 0x8DE10, writer 0x8DE8E) at 0x9DBCA,
   divlu-normalizes -> word_30535A, PT1-filters via sub_43904 (e.g. 0x9DC42) into page-C2 EVAP RAM
   byte_30A0E2/word_30A20A; reads EXBLASH2 0x1a06f (0x9E4D2), byte_1A06D/1A06E; status flag banks
   byte_30169C-3016A8; packs via sub_B31AC; no actuator write [C mechanism; EVAP-system identity I]
    */

void diag_evap_purge_monitor(void)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar4;
  uint uVar5;
  undefined1 uVar6;
  undefined2 uVar7;
  ushort uVar8;
  short sVar9;
  ushort uVar10;
  byte bVar11;
  int iVar12;
  undefined4 uVar13;
  ushort uStack_10;
  undefined1 uStack_a;
  int iVar3;
  
  uVar1 = uRam303ac2;
  iVar12 = CONCAT22(MDH,MDL);
  uStack_10 = uRam303ac2;
  if ((_flags_diag_enable_a & 2) == 0) {
    uStack_10 = ((uRam303ac2 & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
    uRam305354 = 0x8000;
    uRam3056a1 = 0;
    uRam305366 = 0;
    uRam305368 = 0;
    uRam305352 = 0;
    bRam30169d = bRam30169d & 0xfe;
    evap_monitor_flags = evap_monitor_flags & 0xb0;
  }
  else {
    if (((flags_diag_cfg_b & 0x200) == 0) || ((evap_monitor_flags & 1) != 0)) {
      if (((bRam301608 & 1) == 0) && ((evap_monitor_flags & 1) == 0)) {
        bRam30a0e2 = bRam30a0e2 & 0xfb;
        bRam3016a7 = bRam3016a7 & 0xef;
        bRam30169f = bRam30169f & 0xfe;
        bRam3016a8 = bRam3016a8 & 0xbe;
        if (cRam3016a4 != '\0') {
          cRam3016a4 = cRam3016a4 + -1;
        }
        bRam30169e = bRam30169e & 0x7f;
        bRam3016a6 = bRam3016a6 & 0xdd;
      }
      else {
        if ((bRam301607 & 0x10) == 0) {
          evap_monitor_flags = evap_monitor_flags & 0xf7;
          uRam0196a2 = uRam01a0e4;
        }
        else if (cRam3016a2 == '\0') {
          evap_monitor_flags = evap_monitor_flags | 8;
        }
        else {
          cRam3016a2 = cRam3016a2 + -1;
        }
        if (((bRam3016a8 & 0x20) == 0) && ((evap_monitor_flags & 8) != 0)) {
          bRam30169d = bRam30169d | 1;
        }
        else {
          bRam30169d = bRam30169d & 0xfe;
        }
        if ((evap_monitor_flags & 8) == 0) {
          bRam3016a8 = bRam3016a8 & 0xdf;
        }
        else {
          bRam3016a8 = bRam3016a8 | 0x20;
        }
        if ((uRam302e02 == 0) && ((evap_monitor_flags & 8) == 0)) {
          bRam3016a7 = bRam3016a7 | 0x80;
        }
        else {
          bRam3016a7 = bRam3016a7 & 0x7f;
        }
        if ((evap_monitor_flags & 1) == 0) {
          bRam3016a8 = bRam3016a8 & 0xfe;
        }
        else {
          bRam3016a8 = bRam3016a8 | 1;
        }
        if ((bRam3016a7 & 0x80) == 0) {
          if ((evap_monitor_flags & 8) != 0) {
            evap_monitor_flags = evap_monitor_flags | 1;
          }
        }
        else {
          evap_monitor_flags = evap_monitor_flags & 0xfe;
        }
        if (((bRam3016a8 & 1) == 0) || ((evap_monitor_flags & 1) != 0)) {
          if ((bRam301607 & 0x10) != 0) {
            bRam3016a8 = bRam3016a8 | 0x40;
          }
        }
        else {
          bRam3016a8 = bRam3016a8 & 0xbf;
        }
        if (((bRam3016a8 & 0x40) == 0) && ((bRam3016a7 & 0x10) == 0)) {
          bRam30169f = bRam30169f & 0xfe;
          bRam30a0e2 = bRam30a0e2 & 0xfb;
        }
        else {
          bRam30169f = bRam30169f | 1;
          bRam30a0e2 = bRam30a0e2 | 4;
        }
        if ((bRam3016a8 & 0x40) == 0) {
          bRam3016a7 = bRam3016a7 & 0xef;
        }
        else {
          bRam3016a7 = bRam3016a7 | 0x10;
        }
        if ((evap_monitor_flags & 1) == 0) {
          evap_monitor_flags = evap_monitor_flags & 0xfb;
        }
        else {
          evap_monitor_flags = evap_monitor_flags | 4;
        }
        MDL = (ushort)(0x8000000 / (uint)_evap_purge_quantity);
        MDH = (short)(0x8000000 % (uint)_evap_purge_quantity);
        MDC = MDC | 0x10;
        uRam30535a = MDL;
        if (_evap_purge_quantity == 0 || 0xffff < 0x8000000 / (uint)_evap_purge_quantity) {
          uRam30535a = 0xffff;
        }
        sVar9 = uRam30535a - uRam305358;
        if (uRam30535a < uRam305358) {
          if (sVar9 >= 0) {
            sVar9 = -0x8000;
          }
        }
        else if (sVar9 < 0) {
          sVar9 = 0x7fff;
        }
        uRam30534a = func_0x042fe2(sVar9);
        uVar7 = me7_lookup_1d_word(0xd6,9,uRam30534a);
        uRam302b4a = me7_pt1_integrator(uVar7,uRam30535a,uRam306b4c,(undefined2)uRam302b4a);
        uRam305358 = (ushort)((uint)uRam302b4a >> 0x10);
        uRam302b46 = me7_pt1_integrator(uRam0240d4,uRam30534a,uRam306b48,(undefined2)uRam302b46);
        uVar13 = CONCAT22(uRam302b42._2_2_,(ushort)uRam302b42);
        uRam305348 = (ushort)((uint)uRam302b46 >> 0x10);
        iVar12 = CONCAT22(MDH,MDL);
        if ((bRam30569c & 4) == 0) {
          bRam3049a3 = 0;
        }
        else if (((evap_monitor_flags & 2) == 0) && (bRam3049a3 != 0xff)) {
          bRam3049a3 = bRam3049a3 + 1;
        }
        if (uRam305348 < uRam0240ae) {
          bRam3016a5 = bRam3016a5 | 1;
        }
        else {
          bRam3016a5 = bRam3016a5 & 0xfe;
        }
        if ((bRam3016a5 & 1) == 0) {
          PSW = PSW & 0xffbf;
        }
        else {
          PSW = PSW | 0x40;
        }
        uVar8 = (PSW & 0x40) >> 6;
        if (((bRam30169d & 1) == 0) && ((bRam30169e & 0x80) == 0)) {
          if ((uVar8 == 0) && (bRam01a0df < bRam3049a3)) {
            bRam30169b = bRam30169b | 1;
          }
        }
        else {
          bRam30169b = bRam30169b & 0xfe;
        }
        if ((evap_monitor_flags & 2) == 0) {
          bRam3016a6 = bRam3016a6 & 0xdf;
        }
        else {
          bRam3016a6 = bRam3016a6 | 0x20;
        }
        if ((bRam3016a7 & 0x80) == 0) {
          if ((uVar8 != 0) && (bRam01a0de < bRam3049a3)) {
            evap_monitor_flags = evap_monitor_flags | 2;
          }
        }
        else {
          evap_monitor_flags = evap_monitor_flags & 0xfd;
        }
        if ((evap_monitor_flags & 2) != 0) {
          if ((bRam3016a6 & 0x20) == 0) {
            uRam30535c = uRam305358;
          }
          sRam305356 = uRam30535c - uRam305358;
          if (uRam30535c < uRam305358) {
            if (sRam305356 >= 0) {
              sRam305356 = -0x8000;
            }
          }
          else if (sRam305356 < 0) {
            sRam305356 = 0x7fff;
          }
          sRam305356 = sRam305356 >> 1;
        }
        if (((bRam30169e & 0x80) == 0) && ((bRam30169d & 1) == 0)) {
          if ((((bRam3016a0 & 1) == 0) && ((evap_monitor_flags & 2) != 0)) &&
             ((sRam305356 - sRam0240ac < 0 ==
               (sRam305356 < 0 != sRam0240ac < 0 && sRam305356 - sRam0240ac < 0 != sRam305356 < 0)
              || (sRam305356 == sRam0240aa ||
                  sRam305356 - sRam0240aa < 0 !=
                  (sRam305356 < 0 != sRam0240aa < 0 && sRam305356 - sRam0240aa < 0 != sRam305356 < 0
                  ))))) {
            bRam3016a0 = bRam3016a0 | 1;
          }
        }
        else {
          bRam3016a0 = bRam3016a0 & 0xfe;
        }
        if (((evap_monitor_flags & 2) == 0) || ((evap_monitor_flags & 8) == 0)) {
          bRam3049a1 = 0;
        }
        else if (bRam3049a1 != 0xff) {
          bRam3049a1 = bRam3049a1 + 1;
        }
        if (((bRam30169e & 0x80) == 0) && ((bRam30169d & 1) == 0)) {
          if (((bRam30169b & 8) == 0) &&
             ((((bRam3016a0 & 1) == 0 && ((bRam301607 & 0x10) == 0)) && (bRam01a0dd <= bRam3049a1)))
             ) {
            bRam30169b = bRam30169b | 8;
          }
        }
        else {
          bRam30169b = bRam30169b & 0xf7;
        }
        if ((((bRam301607 & 0x10) == 0) && (((bRam3016a6 & 0x40) == 0 || ((bRam30169e & 8) != 0))))
           && (((bRam30169d & 1) == 0 && ((bRam30169e & 0x80) == 0)))) {
          iRam302b52 = 0;
          sRam30534c = 0;
          sRam305350 = 0;
          uRam305364 = 0;
        }
        else {
          uVar8 = FUN_042c1c(uRam302da8,uRam302bfe,0x2155);
          sVar9 = me7_lookup_1d_byte(0x20e5,6,rl_byte);
          uVar10 = FUN_042c1c(sVar9 << 8,uRam305368,0x2aab);
          if (uVar10 < 0x100) {
            uStack_a = (undefined1)uVar10;
            uRam30499b = uStack_a;
          }
          else {
            uRam30499b = 0xff;
          }
          bRam30499d = me7_lookup_2d_byte(0x2071,6,uRam30130d,uRam30499b);
          iVar12 = CONCAT22(iRam302b4e._2_2_,(undefined2)iRam302b4e);
          uVar4 = (uint)uVar8 * (uint)bRam30499d * 0x100;
          MDL = (ushort)uVar4;
          MDH = (short)(uVar4 >> 0x10);
          MDC = MDC | 0x10;
          if (uVar4 < 0x8000000) {
            uVar8 = MDH << 5 | MDL >> 0xb;
            uVar5 = uVar4 * 0x20;
          }
          else {
            uVar8 = 0xffff;
            uVar5 = uVar4;
          }
          bRam30499e = bRam30499d;
          if ((bRam30169d & 1) == 0) {
            if ((evap_monitor_flags & 8) != 0) {
              iVar12 = me7_pt1_integrator(uRam0240ee,uVar8,iRam302b4e._2_2_,(undefined2)iRam302b4e,
                                          uVar5);
              uVar4 = CONCAT22(MDH,MDL);
            }
          }
          else {
            iVar12 = (uint)uVar8 << 0x10;
          }
          iRam302b4e._2_2_ = (ushort)((uint)iVar12 >> 0x10);
          MDH = (short)(uVar4 >> 0x10);
          MDL = (ushort)uVar4;
          uRam305360 = iRam302b4e._2_2_;
          if ((bRam30569d & 1) == 0) {
            if ((evap_monitor_flags & 8) != 0) {
              iRam302b4e = iVar12;
              sRam302b3c = me7_fraction_blend(uRam0240ee,bRam30499e,uRam306b3c);
              iVar12 = iRam302b4e;
            }
          }
          else {
            sRam302b3c = (ushort)bRam30499e << 8;
          }
          bRam30499c = (byte)((ushort)sRam302b3c >> 8);
          if ((bRam30569c & 2) == 0) {
            uRam30535e = uRam305360;
            uVar8 = 0;
          }
          else {
            uVar8 = uRam30535e - uRam305360;
            if (uRam30535e < uRam305360) {
              if ((short)uVar8 >= 0) {
                uVar8 = 0x8000;
              }
            }
            else if ((short)uVar8 < 0) {
              uVar8 = 0x7fff;
            }
          }
          if ((short)uVar8 < 0) {
            uVar4 = ((uint)-uVar8 << 0x10) / ((uint)bRam30499c << 8);
            MDL = (ushort)uVar4;
            MDH = (short)(((uint)-uVar8 << 0x10) % ((uint)bRam30499c << 8));
            if ((bRam30499c == 0 || 0xffff < uVar4) || ((short)MDL < 0)) {
              sRam305350 = -0x8000;
            }
            else {
              sRam305350 = -MDL;
            }
          }
          else {
            uVar4 = ((uint)uVar8 << 0x10) / ((uint)bRam30499c << 8);
            MDL = (ushort)uVar4;
            MDH = (short)(((uint)uVar8 << 0x10) % ((uint)bRam30499c << 8));
            if ((bRam30499c == 0 || 0xffff < uVar4) || (sRam305350 = MDL, (short)MDL < 0)) {
              sRam305350 = 0x7fff;
            }
          }
          MDC = MDC | 0x10;
          if ((bRam30569d & 1) == 0) {
            if ((evap_monitor_flags & 8) != 0) {
              iRam302b4e = iVar12;
              iRam302b52 = me7_pt1_integrator(uRam0240f0,uRam026e06,iRam302b52._2_2_,
                                              (undefined2)iRam302b52,uVar5);
              iVar12 = iRam302b4e;
            }
          }
          else {
            iRam302b52 = (uint)uRam302e06 << 0x10;
          }
          uRam305364 = (ushort)((uint)iRam302b52 >> 0x13);
          if ((short)uRam305364 < 0) {
            iVar3 = (int)(short)uRam30536a * (int)(short)uRam305364;
            uVar2 = (ushort)iVar3;
            uVar10 = uRam30536a * -0x8000;
            uVar8 = uVar2 + uVar10;
            sRam30534c = (short)((uint)iVar3 >> 0x10) + ((short)uRam30536a >> 1) +
                         (ushort)(uVar2 + uVar10 < uVar2 || uVar2 + uVar10 < uVar10);
            if (sRam30534c < 0) {
              sRam30534c = sRam30534c + (ushort)(uVar8 - 1 < uVar8 || uVar8 != 0);
            }
          }
          else {
            iVar3 = (int)(short)uRam30536a * (int)(short)uRam305364;
            uVar8 = (ushort)iVar3;
            sRam30534c = (short)((uint)iVar3 >> 0x10);
            if (iVar3 < 0) {
              sRam30534c = sRam30534c + (ushort)(uVar8 - 1 < uVar8 || uVar8 != 0);
            }
          }
          MDH = (short)((uint)iVar3 >> 0x10);
          MDL = (ushort)iVar3;
          MDC = MDC | 0x10;
          if (sRam30534c + -0x2000 < 0 ==
              (sRam30534c < 0 && sRam30534c + -0x2000 < 0 != sRam30534c < 0)) {
            sRam30534c = 0x7fff;
          }
          else if (sRam30534c == -0x2000 ||
                   sRam30534c + 0x2000 < 0 !=
                   (-1 < sRam30534c && sRam30534c + 0x2000 < 0 != sRam30534c < 0)) {
            sRam30534c = -0x8000;
          }
          else {
            sRam30534c = sRam30534c << 2;
          }
          iRam302b4e = iVar12;
          uVar8 = func_0x042464(uRam0240c0,0xc1,9,0xc6,9,uRam30184f);
          if ((bRam30169d & 1) != 0) {
            uRam302b42._2_2_ = uRam30a20a >> 9;
            uRam302b42._0_2_ = uRam30a20a << 7;
          }
          uVar13 = CONCAT22(uRam302b42._2_2_,(ushort)uRam302b42);
          if ((evap_monitor_flags & 2) != 0) {
            sVar9 = sRam305350 - sRam30534c;
            if (sRam305350 < 0 != sRam30534c < 0 && sRam305350 - sRam30534c < 0 != sRam305350 < 0) {
              sVar9 = -0x8000;
            }
            uVar13 = func_0x0430da(uVar8 >> 1,sVar9,uRam302b42._2_2_,(ushort)uRam302b42,
                                   sRam0240d0 >> 8,sRam0240d0 << 8,sRam0240d2 >> 8,sRam0240d2 << 8);
          }
          uRam302b42._2_2_ = (ushort)((uint)uVar13 >> 0x10);
          uRam302b42._0_2_ = (ushort)uVar13;
          uRam30536a = uRam302b42._2_2_ << 8 | (ushort)uRam302b42 >> 8;
          if ((short)uRam30536a < 0) {
            uRam30536c = 0;
          }
          else {
            uRam30536c = uRam30536a << 1;
          }
          iVar12 = (uint)uRam302e04 * (uint)bRam01a0dc;
          MDL = (ushort)iVar12;
          MDH = (short)((uint)iVar12 >> 0x10);
          MDC = MDC | 0x10;
          if (uRam302e02 < (ushort)((uint)iVar12 >> 8)) {
            bRam3016a0 = bRam3016a0 & 0xdf;
            bRam3049a2 = 0;
          }
          else {
            bRam3016a0 = bRam3016a0 | 0x20;
            if (bRam3049a2 != 0xff) {
              bRam3049a2 = bRam3049a2 + 1;
            }
          }
          if (bRam3049a2 < bRam01a0e2) {
            bRam30169e = bRam30169e & 0xdf;
          }
          else {
            bRam30169e = bRam30169e | 0x20;
          }
          if (bRam3049a2 < bRam01a0e3) {
            bRam3016a0 = bRam3016a0 & 0xbf;
          }
          else {
            bRam3016a0 = bRam3016a0 | 0x40;
          }
          if ((bRam30169d & 1) == 0) {
            if (sRam305350 == sRam0240b0 ||
                sRam305350 - sRam0240b0 < 0 !=
                (sRam305350 < 0 != sRam0240b0 < 0 && sRam305350 - sRam0240b0 < 0 != sRam305350 < 0))
            {
              bRam30169e = bRam30169e | 0x10;
            }
            else {
              sVar9 = sRam305350 - sRam30534c;
              if (sRam305350 < 0 != sRam30534c < 0 && sRam305350 - sRam30534c < 0 != sRam305350 < 0)
              {
                sVar9 = -0x8000;
              }
              if ((sVar9 - sRam0240b4 < 0 !=
                   (sVar9 < 0 != sRam0240b4 < 0 && sVar9 - sRam0240b4 < 0 != sVar9 < 0)) ||
                 (sVar9 != sRam0240b6 &&
                  sVar9 - sRam0240b6 < 0 ==
                  (sVar9 < 0 != sRam0240b6 < 0 && sVar9 - sRam0240b6 < 0 != sVar9 < 0))) {
                bRam30169e = bRam30169e | 0x10;
              }
            }
          }
          else {
            bRam30169e = bRam30169e & 0xef;
          }
          if (uRam30536c < uRam0240ce) {
            bRam3016a7 = bRam3016a7 & 0xdf;
          }
          else {
            bRam3016a7 = bRam3016a7 | 0x20;
          }
          if (((bRam30169e & 0x80) == 0) &&
             (((bRam30169e & 0x20) == 0 || ((bRam3016a7 & 0x20) != 0)))) {
            if ((bRam30169d & 1) != 0) {
              bRam3016a0 = bRam3016a0 | 8;
            }
          }
          else {
            bRam3016a0 = bRam3016a0 & 0xf7;
          }
          if (((bRam30169e & 0x80) == 0) &&
             ((((bRam30169e & 0x20) == 0 || ((bRam3016a7 & 0x20) == 0)) &&
              (sRam305350 - sRam0240b2 < 0 !=
               (sRam305350 < 0 != sRam0240b2 < 0 && sRam305350 - sRam0240b2 < 0 != sRam305350 < 0)))
             )) {
            if ((bRam30169d & 1) != 0) {
              bRam3016a0 = bRam3016a0 | 0x10;
            }
          }
          else {
            bRam3016a0 = bRam3016a0 & 0xef;
          }
          if (((bRam30169d & 1) == 0) && ((bRam30169e & 0x80) == 0)) {
            if ((((evap_monitor_flags & 8) != 0) &&
                (((bRam30169e & 0x10) != 0 && ((bRam3016a0 & 0x20) != 0)))) ||
               (((bRam3016a0 & 8) == 0 && (((bRam3016a0 & 0x10) == 0 && ((bRam3016a0 & 0x40) != 0)))
                ))) {
              bRam30169b = bRam30169b | 2;
            }
          }
          else {
            bRam30169b = bRam30169b & 0xfd;
          }
          if (((bRam30169e & 0x80) == 0) && ((bRam30169d & 1) == 0)) {
            if (((bRam3016a0 & 8) != 0) && ((bRam3016a0 & 0x40) != 0)) {
              bRam3016a0 = bRam3016a0 | 2;
            }
            if (((bRam3016a0 & 1) == 0) && ((bRam3016a0 & 2) == 0)) {
              if (((bRam3016a0 & 0x40) != 0) && ((bRam3016a0 & 0x10) != 0)) {
                bRam3016a0 = bRam3016a0 | 4;
              }
            }
            else {
              bRam3016a0 = bRam3016a0 & 0xfb;
            }
          }
          else {
            bRam3016a0 = bRam3016a0 & 0xf9;
          }
          if (((bRam3016a0 & 0x40) != 0) && ((bRam01a06f & 1) == 0)) {
            bRam303274 = bRam303274 | 1;
          }
          if ((bRam30169e & 0x20) != 0) {
            uVar7 = uRam0240ec;
            if ((bRam303274 & 1) == 0) {
              uVar7 = 0x199a;
            }
            uRam302b42 = uVar13;
            uRam302b5a = me7_pt1_integrator(uVar7,uRam30536c,uRam306b5c,(undefined2)uRam302b5a,uVar5
                                           );
            uRam30a20a = (ushort)((uint)uRam302b5a >> 0x10);
            iVar12 = CONCAT22(MDH,MDL);
            uVar13 = uRam302b42;
          }
        }
        if ((bRam30169e & 8) == 0) {
          bRam3016a6 = bRam3016a6 & 0xbf;
        }
        else {
          bRam3016a6 = bRam3016a6 | 0x40;
        }
        if ((((bRam3016a5 & 0x10) == 0) && ((evap_monitor_flags & 4) != 0)) ||
           ((bRam30169e & 0x80) != 0)) {
          bRam3016a0 = bRam3016a0 & 0x7f;
          bRam30169b = bRam30169b & 0xef;
        }
        else {
          if (((bRam3016a0 & 1) != 0) || (((bRam3016a0 & 0x40) != 0 && ((bRam30169b & 2) == 0)))) {
            bRam3016a0 = bRam3016a0 | 0x80;
          }
          if (((bRam3016a0 & 0x80) == 0) &&
             ((((bRam30169b & 1) != 0 || ((bRam30169b & 8) != 0)) ||
              (((bRam30169b & 2) != 0 ||
               (((bRam3016a5 & 0x10) != 0 && ((evap_monitor_flags & 4) == 0)))))))) {
            bRam30169b = bRam30169b | 0x10;
          }
        }
        if ((evap_monitor_flags & 4) == 0) {
          bRam3016a5 = bRam3016a5 & 0xef;
        }
        else {
          bRam3016a5 = bRam3016a5 | 0x10;
        }
        if (((bRam3016a5 & 0x20) == 0) && ((bRam30169b & 0x10) != 0)) {
          bRam3016a5 = bRam3016a5 | 0x40;
        }
        else {
          bRam3016a5 = bRam3016a5 & 0xbf;
        }
        if ((bRam30169e & 0x80) == 0) {
          if ((((bRam3016a5 & 0x40) != 0) && ((bRam30169f & 1) != 0)) && (bRam30499a < bRam01a06e))
          {
            bRam30499a = bRam30499a + 1;
          }
        }
        else {
          bRam30499a = 0;
        }
        if (bRam30499a == bRam01a06e) {
          bRam30169b = bRam30169b | 0x20;
        }
        else {
          bRam30169b = bRam30169b & 0xdf;
        }
        if ((bRam30169b & 0x10) == 0) {
          bRam3016a5 = bRam3016a5 & 0xdf;
        }
        else {
          bRam3016a5 = bRam3016a5 | 0x20;
        }
        if (((bRam3016a5 & 0x80) == 0) && ((bRam3016a0 & 0x80) != 0)) {
          bRam30169e = bRam30169e | 1;
        }
        else {
          bRam30169e = bRam30169e & 0xfe;
        }
        bVar11 = bRam01a06d;
        if ((uRam302634 & 4) != 0) {
          bVar11 = 1;
        }
        if ((bRam30169e & 0x80) == 0) {
          if (((bRam30169e & 1) != 0) && (bRam304998 < bVar11)) {
            bRam304998 = bRam304998 + 1;
          }
        }
        else {
          bRam304998 = 0;
        }
        if (bVar11 == bRam304998) {
          bRam30169b = bRam30169b | 0x80;
        }
        else {
          bRam30169b = bRam30169b & 0x7f;
        }
        if (((bRam01a06f & 1) == 0) &&
           (((((bRam3016a0 & 1) != 0 || ((bRam3016a0 & 2) != 0)) ||
             (((bRam30169b & 0x80) != 0 && ((bRam3016a0 & 4) != 0)))) ||
            (((uRam303be0 & 2) != 0 && ((uRam303be0 & 1) == 0)))))) {
          bRam3016a7 = bRam3016a7 | 0x40;
        }
        else {
          bRam3016a7 = bRam3016a7 & 0xbf;
        }
        bRam304999 = bRam30499a;
        if (((bRam3056a5 & 0x40) == 0) && ((bRam30169e & 1) == 0)) {
          if (cRam3016a4 != '\0') {
            cRam3016a4 = cRam3016a4 + -1;
          }
        }
        else {
          uRam0196a4 = uRam01a0e0;
        }
        if (cRam3016a4 == '\0') {
          bRam30169e = bRam30169e | 8;
        }
        else {
          bRam30169e = bRam30169e & 0xf7;
        }
        if (((uRam302634 & 4) == 0) && (((bRam30169e & 8) == 0 || ((bRam01a06f & 1) == 0)))) {
          bRam3016a6 = bRam3016a6 & 0xfe;
        }
        else {
          bRam3016a6 = bRam3016a6 | 1;
        }
        if (((bRam3016a6 & 2) == 0) && ((bRam3016a6 & 1) != 0)) {
          bRam30169e = bRam30169e | 0x80;
        }
        else {
          bRam30169e = bRam30169e & 0x7f;
        }
        if ((bRam3016a6 & 1) == 0) {
          bRam3016a6 = bRam3016a6 & 0xfd;
        }
        else {
          bRam3016a6 = bRam3016a6 | 2;
        }
        uRam302b42 = uVar13;
        if (((bRam30169b & 0x20) == 0) && ((bRam3016a7 & 0x40) == 0)) {
          bRam30169e = bRam30169e & 0xfb;
        }
        else {
          bRam30169e = bRam30169e | 4;
        }
      }
      MDH = (short)((uint)iVar12 >> 0x10);
      MDL = (ushort)iVar12;
      if (((evap_monitor_flags & 8) == 0) || ((evap_monitor_flags & 2) == 0)) {
        bRam3016a5 = bRam3016a5 & 0xfb;
      }
      else {
        bRam3016a5 = bRam3016a5 | 4;
      }
      if (((bRam3016a5 & 8) == 0) && ((bRam3016a5 & 4) != 0)) {
        uRam302b56._0_2_ = 0;
        uRam302b56._2_2_ = 0;
      }
      sRam30534e = sRam305350;
      if (sRam305350 < 1) {
        sRam30534e = 0;
      }
      uVar7 = FUN_042c1c(sRam30534e,0x10b,uRam302bfe);
      uRam305366 = 0;
      if ((bRam30569c & 8) == 0) {
        uVar7 = 0;
      }
      uRam302b56 = me7_pt1_integrator(uRam0240f2,uVar7,uRam302b56._2_2_,(undefined2)uRam302b56);
      uRam305368 = (undefined2)((uint)uRam302b56 >> 0x10);
      if ((bRam3056a5 & 4) == 0) {
        if ((bRam3016a5 & 8) != 0) {
          uRam302b3e._0_2_ = 0;
          uRam302b3e._2_2_ = 0;
        }
        uVar13 = CONCAT22(uRam302b3e._2_2_,(undefined2)uRam302b3e);
        if (bRam3049a4 != 0xff) {
          bRam3049a4 = bRam3049a4 + 1;
          uVar13 = CONCAT22(uRam302b3e._2_2_,(undefined2)uRam302b3e);
        }
      }
      else {
        uVar13 = func_0x0430da(uRam0240be >> 6,sRam302bb2 >> 2,uRam302b3e._2_2_,
                               (undefined2)uRam302b3e,uRam0240b8,0,uRam0240ba,0);
        bRam3049a4 = 0;
      }
      uRam302b3e._2_2_ = (undefined2)((uint)uVar13 >> 0x10);
      if ((((bRam301607 & 0x10) != 0) && ((uRam00fd5e & 2) != 0)) && ((uRam00fd7c & 0x200) == 0)) {
        uRam302b3e._2_2_ = 0;
      }
      if ((bRam3056a5 & 4) == 0) {
        bRam3016a5 = bRam3016a5 & 0xf7;
      }
      else {
        bRam3016a5 = bRam3016a5 | 8;
      }
      uRam305352 = uRam302b3e._2_2_;
      uRam302b3e = uVar13;
      uRam3049a0 = me7_lookup_1d_byte(0x20bf,6,bRam3049a1);
      uVar6 = uRam3049a0;
      if ((bRam3056a5 & 4) == 0) {
        uVar6 = uRam30499f;
      }
      uRam30499f = uVar6;
      bRam3049a5 = me7_lookup_2d_byte(0x20aa,6,uRam30499f,uRam307472);
      if ((bRam3056a5 & 4) == 0) {
        if (bRam3049a5 <= bRam3049a4) {
          bRam3016a6 = bRam3016a6 | 4;
        }
      }
      else {
        bRam3016a6 = bRam3016a6 & 0xfb;
      }
      if (((bRam3016a6 & 8) == 0) && ((bRam3016a6 & 4) != 0)) {
        bRam3016a6 = bRam3016a6 | 0x10;
        uRam0196a3 = uRam01a0e1;
      }
      else if (cRam3016a3 == '\0') {
        bRam3016a6 = bRam3016a6 & 0xef;
      }
      else {
        cRam3016a3 = cRam3016a3 + -1;
      }
      if ((bRam3016a6 & 4) == 0) {
        bRam3016a6 = bRam3016a6 & 0xf7;
      }
      else {
        bRam3016a6 = bRam3016a6 | 8;
      }
      if (((bRam30169e & 0x80) == 0) && ((bRam30169d & 1) == 0)) {
        if ((bRam301607 & 0x10) != 0) {
          bRam3016a5 = bRam3016a5 | 2;
        }
      }
      else {
        bRam3016a5 = bRam3016a5 & 0xfd;
      }
      if (((bRam3016a5 & 2) == 0) || ((bRam3016a6 & 0x10) == 0)) {
        evap_monitor_flags = evap_monitor_flags & 0xbf;
      }
      else {
        evap_monitor_flags = evap_monitor_flags | 0x40;
      }
      if ((evap_monitor_flags & 0x40) == 0) {
        uRam305354 = 0x8000;
      }
      else {
        MDL = (ushort)(0x8000000 / (uint)uRam30535c);
        MDH = (short)(0x8000000 % (uint)uRam30535c);
        MDC = MDC | 0x10;
        uRam305354 = MDL;
        if (uRam30535c == 0 || 0xffff < 0x8000000 / (uint)uRam30535c) {
          uRam305354 = 0xffff;
        }
      }
    }
    else {
      uRam305354 = 0x8000;
      uRam3056a1 = 0;
      uRam305368 = 0;
      uRam305366 = 0;
      uRam305352 = 0;
      bRam30169d = bRam30169d & 0xfe;
      evap_monitor_flags = evap_monitor_flags & 0xb1;
      cRam3016a3 = '\0';
      bRam3016a8 = bRam3016a8 & 0xfe;
      uRam302b56 = 0;
      uRam302b3e = 0;
      bRam3016a5 = bRam3016a5 & 0xfd;
      if (cRam3016a4 != '\0') {
        cRam3016a4 = cRam3016a4 + -1;
      }
      bRam3016a6 = bRam3016a6 & 0xdd;
      bRam30169e = bRam30169e & 0x7f;
      bRam30a0e2 = bRam30a0e2 & 0xfb;
    }
    if ((bRam01a06f & 1) == 0) {
      if ((((bRam3016a0 & 2) == 0) && ((bRam3016a0 & 1) == 0)) || ((bRam30169e & 1) == 0)) {
        if (((bRam3016a0 & 4) != 0) && ((bRam30169e & 1) != 0)) {
          if (sRam304f4c == sRam0240bc ||
              sRam304f4c - sRam0240bc < 0 !=
              (sRam304f4c < 0 != sRam0240bc < 0 && sRam304f4c - sRam0240bc < 0 != sRam304f4c < 0)) {
            uVar1 = uVar1 >> 8 & 0xfff0 | 1;
          }
          else {
            uVar1 = uVar1 >> 8 & 0xfff0 | 2;
          }
          uStack_10 = (uVar1 & 0x9f | 0x60) << 8 | 2;
        }
      }
      else {
        uStack_10 = ((uVar1 & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
      }
    }
    if ((bRam3016a0 & 0x80) == 0) {
      bRam3016a5 = bRam3016a5 & 0x7f;
    }
    else {
      bRam3016a5 = bRam3016a5 | 0x80;
    }
  }
  func_0x0b31ac(0x1e,uStack_10);
  return;
}


// ================= diag_obd_monitor_cddst @ 0aac4e =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC: CDDST-gated OBD monitor (reader of cluster 0x23FC8-0x24016); gated by
   word_3018D8.2=CDDST (0xAAC5A mov r4,word_3018D8; and #4); edge-tracks byte_303331/303332,
   debounces via sub_32EF0/32FC4/32F5C + one PT1 sub_43904, packs status via sub_B31AC; reads
   threshold scalars word_23FD4-0x23FE8 (0xAAED8 cmp r4,word_23FD4) via mov/cmp + byte config
   byte_1A1A2-8 (near INHASE06); status flags byte_30171B/71C [C mechanism; exact monitor identity
   I] */

void diag_obd_monitor_cddst(void)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  undefined2 uVar5;
  undefined4 uVar6;
  ushort uVar7;
  
  uVar7 = uRam303aa0;
  if ((_flags_diag_enable_b & 4) == 0) {
    obd_cddst_monitor_flags = obd_cddst_monitor_flags & 0xdf;
  }
  else {
    obd_cddst_monitor_flags = obd_cddst_monitor_flags | 0x20;
  }
  if ((obd_cddst_monitor_flags & 0x20) == 0) {
    bRam30171b = bRam30171b & 0xfc;
    uVar7 = ((uRam303aa0 & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
    func_0x0b31ac(0xd,uVar7,uVar7);
  }
  else {
    bVar1 = (DAT_303331 & 0x80) != 0;
    bVar2 = (DAT_303332 & 1) != 0;
    bVar3 = (bRam01a1a4 & 2) != 0;
    if (bVar3) {
      if ((obd_cddst_monitor_flags & 1) == 0) {
        if (bVar1) {
          cRam300ab8 = -1;
        }
      }
      else {
        cRam300ab8 = '\0';
      }
      if (cRam300ab8 == '\0') {
        bRam303335 = bRam303335 & 0xdf;
      }
      else {
        bRam303335 = bRam303335 | 0x20;
      }
    }
    bVar4 = (bRam01a1a4 & 1) != 0;
    if (bVar4) {
      if ((obd_cddst_monitor_flags & 1) == 0) {
        if (((bRam3015e0 & 1) != 0) && ((bRam3015e0 & 4) != 0)) {
          cRam300ab4 = -1;
        }
      }
      else {
        cRam300ab4 = '\0';
      }
      if (cRam300ab4 == '\0') {
        bRam303335 = bRam303335 & 0xf7;
      }
      else {
        bRam303335 = bRam303335 | 8;
      }
    }
    if (((bRam30171b & 2) == 0) || ((DAT_301714 & 8) == 0)) {
      uVar5 = 0;
    }
    else {
      uVar5 = 1;
    }
    func_0x032f5c(0x8ad6,uVar5,uRam023fd8);
    uVar6 = CONCAT22(uRam3053ca,uRam300ada);
    if (((bRam3015e0 & 8) == 0) || ((bRam01a1a4 & 4) == 0)) {
      uRam3053c6 = 0;
    }
    else {
      uVar6 = me7_pt1_integrator(uRam023fe8,uRam30523c,uRam304adc,uRam300ada);
      uRam300adc = (ushort)((uint)uVar6 >> 0x10);
      uRam3053c6 = uRam300adc - uRam30523c;
      if (((short)-(ushort)(uRam300adc < uRam30523c) < 0) ||
         (((short)-(ushort)(uRam300adc < uRam30523c) < 1 && (uRam3053c6 == 0)))) {
        uRam3053c6 = -uRam3053c6;
      }
    }
    uRam3053ca = (undefined2)((uint)uVar6 >> 0x10);
    uRam300ada = (undefined2)uVar6;
    if (((((((bRam307335 & 0x20) == 0) || (!bVar3)) && ((bVar3 || (bVar4)))) &&
         ((!bVar4 || ((bRam303335 & 8) == 0)))) || (uRam305630 <= uRam023fdc)) ||
       ((cRam300ad8 != '\0' || (_vfzg_vehicle_speed < uRam023fe2)))) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    if (bVar3) {
      obd_cddst_monitor_flags = obd_cddst_monitor_flags | 0x10;
    }
    if (((_vfzg_vehicle_speed < uRam023fe4) ||
        (((((uRam023fe6 < _vfzg_vehicle_speed && (uRam023fd6 < uRam3053cc)) ||
           (ram0x023fd4 < uRam3053c6)) || ((obd_cddst_monitor_flags & 1) != 0)) ||
         (((bRam303335 & 4) != 0 && ((bRam303335 & 2) == 0)))))) ||
       ((obd_cddst_monitor_flags & 0x40) != 0)) {
      bVar4 = true;
    }
    else {
      bVar4 = false;
    }
    if (bVar4) {
      uRam300ace = 0;
    }
    else if (bVar3) {
      uRam300ace = 0xff;
    }
    uRam3053cc = _vfzg_vehicle_speed - uRam3053ce;
    if (((short)-(ushort)(_vfzg_vehicle_speed < uRam3053ce) < 0) ||
       (((short)-(ushort)(_vfzg_vehicle_speed < uRam3053ce) < 1 && (uRam3053cc == 0)))) {
      uRam3053cc = -uRam3053cc;
    }
    if (cRam304ace == '\0') {
      bRam30171b = bRam30171b & 0xfd;
    }
    else {
      bRam30171b = bRam30171b | 2;
    }
    uRam3053ce = _vfzg_vehicle_speed;
    bVar3 = (bRam30571c & 0x10) != 0;
    uRam300ab6 = bVar3 && cRam300ab7 == '\0';
    cRam300ab7 = bVar3;
    if ((bool)uRam300ab6) {
      func_0x032fc4(0x8ab0,1,0,cRam01a1a3);
      uVar6 = CONCAT22(uRam3053ca,uRam300ada);
    }
    uRam3053ca = (undefined2)((uint)uVar6 >> 0x10);
    uRam300ada = (undefined2)uVar6;
    cRam30a05b = cRam300ab0;
    cRam300ac4 = bVar2 && cRam300ac5 == '\0';
    if (((!bVar2 || cRam300ac5 != '\0') || (bVar1)) || ((bRam30171b & 2) == 0)) {
      obd_cddst_monitor_flags = obd_cddst_monitor_flags & 0xfd;
    }
    else {
      obd_cddst_monitor_flags = obd_cddst_monitor_flags | 2;
    }
    cRam300ac5 = bVar2;
    if ((((bRam30171b & 2) != 0) && ((bool)cRam300ac4)) && (bVar1)) {
      func_0x032fc4(0x8abe,1,0,cRam01a1a2);
      uVar6 = CONCAT22(uRam3053ca,uRam300ada);
    }
    uRam3053ca = (undefined2)((uint)uVar6 >> 0x10);
    uRam300ada = (undefined2)uVar6;
    cRam30a05a = cRam300abe;
    if ((bRam01a1a4 & 1) != 0) {
      if ((bRam303335 & 8) == 0) {
        cRam300ad0 = '\0';
        cRam300ad1 = '\0';
      }
      else {
        cRam300ad0 = cRam300ad1 == '\0';
        cRam300ad1 = '\x01';
      }
    }
    if (cRam300ad0 == '\0') {
      if (((cRam01a1a3 == cRam30a05b) || ((uRam303c1e & 1) != 0)) ||
         (((obd_cddst_monitor_flags & 2) != 0 || (cRam01a1a2 == cRam300abe)))) {
        cRam300ad4 = -1;
      }
    }
    else {
      cRam300ad4 = '\0';
    }
    if (cRam300ad4 == '\0') {
      obd_cddst_monitor_flags = obd_cddst_monitor_flags & 0xfe;
    }
    else {
      obd_cddst_monitor_flags = obd_cddst_monitor_flags | 1;
    }
    if ((obd_cddst_monitor_flags & 1) == 0) {
      if ((((bRam30171b & 2) != 0) && (cRam300ac4 != '\0')) && (bVar1)) {
        cRam300ac0 = -1;
      }
    }
    else {
      cRam300ac0 = '\0';
    }
    if (cRam300ac0 == '\0') {
      bRam303335 = bRam303335 & 0xfb;
    }
    else {
      bRam303335 = bRam303335 | 4;
    }
    if ((obd_cddst_monitor_flags & 1) != 0) {
      cRam300abe = '\0';
    }
    bVar1 = (bRam303335 & 4) != 0;
    cRam300ad2 = bVar1 && cRam300ad3 == '\0';
    if (((obd_cddst_monitor_flags & 1) != 0) || ((bool)cRam300ad2)) {
      cRam300ab0 = '\0';
      obd_cddst_monitor_flags = obd_cddst_monitor_flags & 0xef;
      cRam30a05b = '\0';
      cRam30a05a = '\0';
    }
    cRam300ad3 = bVar1;
    func_0x032ef0(0x8ae2,uRam023fe0 <= _vfzg_vehicle_speed,uRam01a1a8);
    bVar1 = (bRam30171b & 1) != 0;
    uRam300abc = !bVar1 && cRam300abd != '\0';
    if (((cRam300ac4 != '\0') && ((DAT_303331 & 0x80) == 0)) || ((bool)uRam300abc)) {
      obd_cddst_monitor_flags = obd_cddst_monitor_flags & 0xf7;
    }
    else if ((cRam300ac4 != '\0') && ((DAT_303331 & 0x80) != 0)) {
      obd_cddst_monitor_flags = obd_cddst_monitor_flags | 8;
    }
    if ((((bRam30332f & 1) == 0) || ((bRam01a1a4 & 8) != 0)) && ((obd_cddst_monitor_flags & 8) != 0)
       ) {
      uVar5 = 1;
    }
    else {
      uVar5 = 0;
    }
    cRam300abd = bVar1;
    func_0x032ef0(0x8ade,uVar5,uRam01a1a6);
    if ((cRam300ade == '\0') || (cRam300ae2 == '\0')) {
      uRam300aca = false;
      cRam300acb = '\0';
    }
    else {
      uRam300aca = cRam300acb == '\0';
      cRam300acb = '\x01';
    }
    if (((bool)uRam300aca == false) &&
       ((((bRam303335 & 4) == 0 || (cRam300ae2 == '\0')) || ((bRam303335 & 1) != 0)))) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if ((bRam01a1a4 & 0x10) == 0) {
      obd_cddst_monitor_flags = obd_cddst_monitor_flags & 0xfb;
    }
    else if (((bRam01a1a4 & 0x10) != 0) && (bVar1)) {
      obd_cddst_monitor_flags = obd_cddst_monitor_flags | 4;
    }
    if (((obd_cddst_monitor_flags & 4) != 0) || (bVar1)) {
      uVar5 = 1;
    }
    else {
      uVar5 = 0;
    }
    func_0x032f5c(0x8ac6,uVar5,uRam023fda);
    if (((obd_cddst_monitor_flags & 1) == 0) && (cRam300ac4 == '\0')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      cRam300ae0 = '\0';
    }
    else if (cRam300ac8 != '\0') {
      cRam300ae0 = -1;
    }
    if (cRam300ac8 == '\0') {
      bRam30171b = bRam30171b & 0xfe;
    }
    else {
      bRam30171b = bRam30171b | 1;
    }
    if (cRam300ae0 == '\0') {
      bRam303335 = bRam303335 & 0xfe;
    }
    else {
      bRam303335 = bRam303335 | 1;
    }
    func_0x032ef0(0x8ac2,_vfzg_vehicle_speed <= uRam023fde,uRam01a1a7);
    if (bVar1) {
      cRam300acc = '\0';
    }
    else if (((bRam303335 & 1) != 0) && (cRam300ac2 != '\0')) {
      cRam300acc = -1;
    }
    if (cRam300acc == '\0') {
      bRam303335 = bRam303335 & 0xfd;
    }
    else {
      bRam303335 = bRam303335 | 2;
    }
    bVar1 = (obd_cddst_monitor_flags & 2) != 0;
    uRam300aba = bVar1 && cRam300abb == '\0';
    if ((cRam300ad2 == '\0') || ((obd_cddst_monitor_flags & 2) != 0)) {
      if (((bool)uRam300aba) && ((bRam303335 & 4) == 0)) {
        uVar7 = ((uVar7 & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
      }
    }
    else {
      uVar7 = (uVar7 >> 8 & 0x90 | 0x61) << 8 | 2;
    }
    cRam300abb = bVar1;
    func_0x0b31ac(0xd,uVar7);
  }
  return;
}


// ================= diag_adc_range_monitor @ 0c253e =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC: ADC/sensor range-window plausibility monitor; reads min/max window word-pairs
   0x26A50-0x26A68 (cfg_26A50_etc_adc_windows) vs page-C1 ADC cells + byte config 0x1B92A-0x1B949,
   1-D byte lookup sub_419F4 + PT1 sub_43904; sets range-fault flags word_FD60.8-.11 +
   word_FD62.3-.6 (0xC26C8 bset word_FD60.8; 0xC2684 bset word_FD60.10); packs via sub_B31AC; no
   actuator/setpoint write [C mechanism; monitored-channel identity I] */

void diag_adc_range_monitor(void)

{
  bool bVar1;
  bool bVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  short sVar7;
  ushort uVar8;
  ushort uStack_12;
  ushort uStack_10;
  ushort uStack_e;
  ushort uStack_c;
  ushort uStack_a;
  
  uVar5 = uRam303b0e;
  uStack_12 = uRam303b06;
  uStack_10 = uRam303b0a;
  uStack_e = uRam303bcc;
  uStack_c = uRam303bd0;
  uStack_a = uRam303b0e;
  if ((_flags_diag_enable_a & 0x100) == 0) {
    uRam00fd62 = uRam00fd62 | 1;
    uStack_e = (uRam303bcc >> 8 & 0x90 | 0x60) << 8 | 2;
    uStack_10 = (uRam303b0a >> 8 & 0x90 | 0x60) << 8 | 2;
    uStack_12 = (uRam303b06 >> 8 & 0x90 | 0x60) << 8 | 2;
    uStack_c = (uRam303bd0 >> 8 & 0x90 | 0x60) << 8 | 2;
    uRam00fd60 = uRam00fd60 & 0xff7f | 0x6020;
    goto LAB_0c389c;
  }
  if (cRam01b92a == '\0') {
    uRam00fd62 = uRam00fd62 & 0xffef;
  }
  else {
    uRam00fd62 = uRam00fd62 | 0x10;
  }
  if ((uRam00fd62 & 0x10) == 0) {
    if ((bRam30a0dc & 0x40) == 0) {
      uRam00fd62 = uRam00fd62 & 0xffdf;
    }
    else {
      uRam00fd62 = uRam00fd62 | 0x20;
    }
    if ((bRam30479a & 0x20) == 0) {
      PSW = PSW | 0x40;
    }
    else {
      PSW = PSW & 0xffbf;
    }
    uVar8 = PSW & 0x40;
    if ((bRam30479a & 0x80) == 0) {
      PSW = PSW | 0x40;
    }
    else {
      PSW = PSW & 0xffbf;
    }
    uRam00fd62 = uRam00fd62 & 0xffb7 | (uVar8 >> 6 ^ 1) << 3 | ((PSW & 0x40) >> 6 ^ 1) << 6;
    sRam3055e0 = sRam30521e;
    uVar8 = (uRam00fd60 & 0x400) >> 10;
    bVar2 = (bRam301754 & 0x10) == 0;
    if (bVar2) {
      PSW = PSW | 0x40;
    }
    else {
      PSW = PSW & 0xffbf;
    }
  }
  else {
    if ((bRam30a0dd & 0x40) == 0) {
      uRam00fd62 = uRam00fd62 & 0xffdf;
    }
    else {
      uRam00fd62 = uRam00fd62 | 0x20;
    }
    if ((bRam30479a & 0x40) == 0) {
      PSW = PSW | 0x40;
    }
    else {
      PSW = PSW & 0xffbf;
    }
    uVar8 = PSW & 0x40;
    if ((bRam30479b & 1) == 0) {
      PSW = PSW | 0x40;
    }
    else {
      PSW = PSW & 0xffbf;
    }
    uRam00fd62 = uRam00fd62 & 0xffb7 | (uVar8 >> 6 ^ 1) << 3 | ((PSW & 0x40) >> 6 ^ 1) << 6;
    sRam3055e0 = sRam305222;
    uVar8 = (uRam00fd60 & 0x800) >> 0xb;
    bVar2 = (bRam301754 & 0x40) == 0;
    if (bVar2) {
      PSW = PSW | 0x40;
    }
    else {
      PSW = PSW & 0xffbf;
    }
  }
  bVar2 = !bVar2;
  if ((sRam30521e == sRam026a64 ||
       sRam30521e - sRam026a64 < 0 !=
       (sRam30521e < 0 != sRam026a64 < 0 && sRam30521e - sRam026a64 < 0 != sRam30521e < 0)) &&
     (sRam30521e - sRam026a62 < 0 ==
      (sRam30521e < 0 != sRam026a62 < 0 && sRam30521e - sRam026a62 < 0 != sRam30521e < 0))) {
    uRam00fd60 = uRam00fd60 & 0xfbff;
  }
  else {
    uRam00fd60 = uRam00fd60 | 0x400;
  }
  if ((uRam026a58 < uRam30521a) || (uRam30521a < uRam026a56)) {
    uRam00fd60 = uRam00fd60 | 0x200;
  }
  else {
    uRam00fd60 = uRam00fd60 & 0xfdff;
  }
  if ((uRam026a54 < uRam305216) || (uRam305216 < uRam026a52)) {
    uRam00fd60 = uRam00fd60 | 0x100;
  }
  else {
    uRam00fd60 = uRam00fd60 & 0xfeff;
  }
  if ((sRam305222 == sRam026a68 ||
       sRam305222 - sRam026a68 < 0 !=
       (sRam305222 < 0 != sRam026a68 < 0 && sRam305222 - sRam026a68 < 0 != sRam305222 < 0)) &&
     (sRam305222 - sRam026a66 < 0 ==
      (sRam305222 < 0 != sRam026a66 < 0 && sRam305222 - sRam026a66 < 0 != sRam305222 < 0))) {
    uRam00fd60 = uRam00fd60 & 0xf7ff;
  }
  else {
    uRam00fd60 = uRam00fd60 | 0x800;
  }
  if (((((uRam00fd60 & 0x400) == 0) && ((uRam00fd60 & 0x200) == 0)) && ((uRam00fd60 & 0x100) == 0))
     && ((uRam00fd60 & 0x800) == 0)) {
    PSW = PSW & 0xffbf;
  }
  else {
    PSW = PSW | 0x40;
  }
  uVar3 = (PSW & 0x40) >> 6;
  if ((uRam00fd60 & 0x40) == 0) {
    if ((((bRam3015c8 & 0x40) != 0) && ((bRam3015c8 & 0x80) != 0)) && (uVar3 != 0)) {
      bRam303345 = bRam303345 | 2;
    }
  }
  else {
    bRam303345 = bRam303345 & 0xfd;
    uRam303c36 = 0;
    uRam303c38 = 0;
    uRam3055dc = 0;
  }
  if (((bRam303345 & 2) != 0) && ((flags_torque_revlimit & 0x80) == 0)) {
    uVar4 = (ushort)bRam00f472;
    uVar6 = uVar4 + uRam303c36;
    bVar1 = uVar4 + uRam303c36 < uRam303c36;
    uRam303c36 = uVar4 + uRam303c36;
    uRam303c38 = uRam303c38 + (uVar6 < uVar4 || bVar1);
    if ((uRam303c38 - 0xf != (ushort)(uRam303c36 != 0xffff) || uRam303c36 != 0xffff) &&
        (0xe < uRam303c38 && (uRam303c38 != 0xf || uRam303c36 == 0xffff))) {
      uRam303c36 = 0xffff;
      uRam303c38 = 0xf;
    }
    if (uRam026a5a < (uRam303c36 >> 4 | uRam303c38 << 0xc)) {
      uRam3055dc = uRam026a5a;
    }
    else {
      uRam3055dc = uRam303c36 >> 4 | uRam303c38 << 0xc;
    }
  }
  if ((uVar3 != 0) || ((uRam00fd60 & 0x40) != 0)) {
    uRam30be90 = uRam3055dc;
  }
  if (uRam3055dc < uRam026a5a) {
    uVar6 = uRam3055dc - uRam30be90;
    if (uRam3055dc < uRam30be90) {
      uVar6 = 0;
    }
    if (uRam026a5e < uVar6) goto LAB_0c2808;
    uRam00fd60 = uRam00fd60 & 0xff3f | uVar3 << 7;
  }
  else {
LAB_0c2808:
    uRam00fd60 = uRam00fd60 & 0xff7f | uVar3 << 7 | 0x40;
  }
  if (uRam026a5c < uRam3055dc) {
    PSW = PSW | 0x40;
  }
  else {
    PSW = PSW & 0xffbf;
  }
  uVar3 = (PSW & 0x40) >> 6;
  if (((((uRam00fd62 & 4) == 4) || ((bRam3015c8 & 0x40) == 0)) || ((bRam3015c8 & 0x80) == 0)) ||
     ((uRam00fd60 & 0x80) == 0)) {
    if (uVar3 != 0) {
      bRam303345 = bRam303345 | 1;
    }
  }
  else {
    bRam303345 = bRam303345 & 0xfe;
  }
  if ((bRam01b92b & 0x10) == 0) {
    if ((bRam303345 & 1) == 0) {
      PSW = PSW | 0x40;
    }
    else {
      PSW = PSW & 0xffbf;
    }
    uRam00fd60 = uRam00fd60 & 0xffdf | ((PSW & 0x40) >> 6 ^ 1) << 5;
  }
  else {
    if (((bRam303345 & 1) == 0) && ((_DAT_302632 & 0x100) == 0)) {
      PSW = PSW & 0xffbf;
    }
    else {
      PSW = PSW | 0x40;
    }
    uRam00fd60 = uRam00fd60 & 0xffdf | ((PSW & 0x40) >> 6) << 5;
  }
  if ((((bRam3015ba & 2) != 0) && ((bRam30479a & 2) == 0)) &&
     (((bRam30a0db & 0x40) != 0 && (((uRam00fd60 & 0x20) != 0 && (bRam304d36 <= bRam01b940)))))) {
    bRam304d36 = bRam304d36 + 1;
  }
  if ((bRam30479b & 4) == 0) {
    if ((bRam01b940 < bRam304d36) && (((bRam301754 & 4) != 0 || ((uRam00fd60 & 0x200) != 0)))) {
      if (uRam3055da < uRam30521a) {
        if (uRam30521a - uRam3055da <= uRam026a50) {
          uRam00fd60 = uRam00fd60 | 0x4000;
        }
      }
      else if (uRam3055da - uRam30521a <= uRam026a50) {
        uRam00fd60 = uRam00fd60 | 0x4000;
      }
    }
  }
  else {
    uRam00fd60 = uRam00fd60 | 0x4000;
  }
  if ((bRam01b940 < bRam304d36) ||
     ((((bRam301754 & 4) != 0 && ((bRam301753 & 8) == 0)) && ((bRam01b92c & 1) == 0)))) {
    bRam304d36 = 0;
    uRam3055da = uRam30521a;
  }
  if ((bRam301754 & 4) == 0) {
    bRam301753 = bRam301753 & 0xf7;
  }
  else {
    bRam301753 = bRam301753 | 8;
  }
  if ((((bRam3015ba & 2) != 0) && ((uRam00fd62 & 0x40) == 0)) &&
     ((((uRam00fd62 & 0x20) != 0 && (((uRam00fd60 & 0x4000) != 0 && ((uRam00fd60 & 0x20) != 0)))) &&
      (bRam304d3a <= bRam01b946)))) {
    bRam304d3a = bRam304d3a + 1;
  }
  if ((uRam00fd62 & 8) == 0) {
    if ((bRam01b946 < bRam304d3a) && ((bVar2 || (uVar8 != 0)))) {
      if (sRam3055de - sRam3055e0 < 0 ==
          (sRam3055de < 0 != sRam3055e0 < 0 && sRam3055de - sRam3055e0 < 0 != sRam3055de < 0)) {
        sVar7 = sRam3055de - sRam3055e0;
        if (sVar7 == sRam026a60 ||
            sVar7 - sRam026a60 < 0 !=
            (sVar7 < 0 != sRam026a60 < 0 && sVar7 - sRam026a60 < 0 != sVar7 < 0)) {
          bRam301752 = bRam301752 | 0x40;
        }
      }
      else {
        sVar7 = sRam3055e0 - sRam3055de;
        if (sVar7 == sRam026a60 ||
            sVar7 - sRam026a60 < 0 !=
            (sVar7 < 0 != sRam026a60 < 0 && sVar7 - sRam026a60 < 0 != sVar7 < 0)) {
          bRam301752 = bRam301752 | 0x40;
        }
      }
    }
  }
  else {
    bRam301752 = bRam301752 | 0x40;
  }
  if ((bRam01b946 < bRam304d3a) ||
     (((bVar2 && ((bRam301753 & 0x10) == 0)) && ((bRam01b92c & 1) == 0)))) {
    bRam304d3a = 0;
    sRam3055de = sRam3055e0;
  }
  if (((uRam00fd60 & 0x4000) == 0) || ((bRam301752 & 0x40) == 0)) {
    PSW = PSW & 0xffbf;
  }
  else {
    PSW = PSW | 0x40;
  }
  uVar6 = (PSW & 0x40) >> 6;
  uVar8 = uRam00fd62 & 0xfffa | uVar3 << 2 | uVar6;
  if (bVar2) {
    bRam301753 = bRam301753 | 0x10;
  }
  else {
    bRam301753 = bRam301753 & 0xef;
  }
  if (((bRam3015ba & 2) != 0) && ((uRam00fd60 & 0x20) != 0)) {
    if ((bRam30a0db & 0x40) != 0) {
      if (bRam01b942 < bRam304d35) {
        bRam301752 = bRam301752 | 0x80;
      }
      else {
        bRam304d35 = bRam304d35 + 1;
      }
    }
    if (((((bRam01b92c & 2) == 0) && ((uRam00fd60 & 0x100) == 0)) && ((bRam301754 & 1) != 0)) &&
       ((bRam301753 & 0x20) == 0)) {
      bRam304d34 = 0;
    }
    if (((uRam00fd60 & 0x100) == 0) && ((bRam301754 & 1) != 0)) {
      bRam301753 = bRam301753 | 0x20;
    }
    else {
      bRam301753 = bRam301753 & 0xdf;
    }
    if (((bRam30a0da & 0x40) != 0) &&
       (((((bRam303346 & 1) != 0 && ((uRam00fd60 & 0x100) == 0)) && ((bRam301754 & 1) != 0)) ||
        (((bRam303346 & 1) == 0 || ((uRam00fd60 & 0x100) != 0)))))) {
      if (bRam01b941 < bRam304d34) {
        bRam301753 = bRam301753 | 4;
      }
      else {
        bRam304d34 = bRam304d34 + 1;
      }
    }
    if (((bRam30a0dd & 0x40) != 0) && (((bRam301752 & 0x80) != 0 || ((uRam00fd60 & 0x4000) != 0))))
    {
      if (bRam01b948 < bRam304d39) {
        bRam301753 = bRam301753 | 1;
      }
      else {
        bRam304d39 = bRam304d39 + 1;
      }
    }
    if (((bRam30a0dc & 0x40) != 0) && (((bRam301752 & 0x80) != 0 || ((uRam00fd60 & 0x4000) != 0))))
    {
      if (bRam01b947 < bRam304d38) {
        bRam301753 = bRam301753 | 2;
      }
      else {
        bRam304d38 = bRam304d38 + 1;
      }
    }
  }
  if ((((uRam00fd60 & 0x4000) == 0) && ((bRam30479b & 4) == 0)) &&
     (((bRam301752 & 0x80) == 0 ||
      ((((bRam303346 & 4) == 0 || ((uRam00fd60 & 0x200) == 0)) && ((bRam303346 & 4) != 0)))))) {
    bRam304d33 = bRam304d33 & 0xfd;
  }
  else {
    bRam304d33 = bRam304d33 | 2;
  }
  if ((((bRam30479a & 0x40) == 0) && ((uVar6 == 0 || ((uRam00fd62 & 0x10) == 0)))) &&
     (((bRam301753 & 1) == 0 ||
      ((((bRam303346 & 0x40) == 0 || ((uRam00fd60 & 0x800) == 0)) && ((bRam303346 & 0x40) != 0))))))
  {
    bRam304d33 = bRam304d33 & 0xef;
  }
  else {
    bRam304d33 = bRam304d33 | 0x10;
  }
  if ((((bRam30479a & 0x20) == 0) && ((uVar6 == 0 || ((uRam00fd62 & 0x10) != 0)))) &&
     (((bRam301753 & 2) == 0 ||
      ((((bRam303346 & 0x10) == 0 || ((uRam00fd60 & 0x400) == 0)) && ((bRam303346 & 0x10) != 0))))))
  {
    bRam304d33 = bRam304d33 & 0xf7;
  }
  else {
    bRam304d33 = bRam304d33 | 8;
  }
  if (((bRam301753 & 4) == 0) && ((bRam30479b & 2) == 0)) {
    bRam304d33 = bRam304d33 & 0xfb;
  }
  else {
    bRam304d33 = bRam304d33 | 4;
  }
  if ((uRam00fd60 & 0x400) == 0) {
    bRam301751 = bRam301751 & 0xfe;
    if (((uRam00fd60 & 0x400) == 0) && ((bRam301752 & 1) != 0)) {
      uStack_e = uRam303bcc & 0xfffb;
    }
  }
  else {
    if (((bRam304d33 & 8) == 0) || ((uRam00fd60 & 0x20) != 0)) {
      bRam301751 = bRam301751 & 0xfe;
    }
    else {
      bRam301751 = bRam301751 | 1;
    }
    if (((bRam301751 & 0x10) == 0) && ((bRam301751 & 1) != 0)) {
      uStack_e = uRam303bcc & 0xff00 | uRam303bcc & 0xff00 | 4;
      bRam301750 = bRam301750 | 0x40;
    }
    else {
      bRam301750 = bRam301750 & 0xbf;
    }
  }
  if ((bRam301751 & 1) == 0) {
    bRam301751 = bRam301751 & 0xef;
  }
  else {
    bRam301751 = bRam301751 | 0x10;
  }
  if ((uRam00fd60 & 0x400) == 0) {
    bRam301752 = bRam301752 & 0xfe;
  }
  else {
    bRam301752 = bRam301752 | 1;
  }
  if ((bRam30479a & 0x20) == 0) {
    if ((uRam00fd60 & 0x400) == 0) {
      if (((bRam304d33 & 8) != 0) && ((uRam00fd60 & 0x20) != 0)) {
        uStack_e = (uStack_e >> 8 & 0x90 | 0x60) << 8 | 2;
      }
    }
    else if (((bRam304d33 & 8) != 0) && ((uRam00fd60 & 0x20) != 0)) {
      if (sRam30521e - sRam026a64 < 0 ==
          (sRam30521e < 0 != sRam026a64 < 0 && sRam30521e - sRam026a64 < 0 != sRam30521e < 0)) {
        uStack_e = (uStack_e >> 8 & 0x90 | 0x61) << 8 | 1;
      }
      else if (sRam30521e == sRam026a62 ||
               sRam30521e - sRam026a62 < 0 !=
               (sRam30521e < 0 != sRam026a62 < 0 && sRam30521e - sRam026a62 < 0 != sRam30521e < 0))
      {
        uStack_e = (uStack_e >> 8 & 0x90 | 0x62) << 8 | 1;
      }
    }
  }
  else {
    uStack_e = (uStack_e >> 8 & 0x90 | 0x60) << 8 | 2;
  }
  if ((uRam00fd60 & 0x20) == 0) {
    bRam301750 = bRam301750 & 0xf0;
  }
  else {
    if ((bRam304d33 & 8) == 0) {
      bRam301750 = bRam301750 & 0xfb;
    }
    else {
      bRam301750 = bRam301750 | 4;
    }
    if ((bRam304d33 & 2) == 0) {
      bRam301750 = bRam301750 & 0xfd;
    }
    else {
      bRam301750 = bRam301750 | 2;
    }
    if ((bRam304d33 & 4) == 0) {
      bRam301750 = bRam301750 & 0xfe;
    }
    else {
      bRam301750 = bRam301750 | 1;
    }
    if ((bRam304d33 & 0x10) == 0) {
      bRam301750 = bRam301750 & 0xf7;
    }
    else {
      bRam301750 = bRam301750 | 8;
    }
  }
  if ((uRam00fd60 & 0x200) == 0) {
    bRam301751 = bRam301751 & 0xfd;
    if (((uRam00fd60 & 0x200) == 0) && ((bRam301752 & 8) != 0)) {
      uStack_10 = uRam303b0a & 0xfffb;
    }
  }
  else {
    if (((bRam304d33 & 2) == 0) || ((uRam00fd60 & 0x20) != 0)) {
      bRam301751 = bRam301751 & 0xfd;
    }
    else {
      bRam301751 = bRam301751 | 2;
    }
    if (((bRam301751 & 0x20) == 0) && ((bRam301751 & 2) != 0)) {
      uStack_10 = uRam303b0a & 0xff00 | uRam303b0a & 0xff00 | 4;
      bRam301750 = bRam301750 | 0x20;
    }
    else {
      bRam301750 = bRam301750 & 0xdf;
    }
  }
  if ((bRam301751 & 2) == 0) {
    bRam301751 = bRam301751 & 0xdf;
  }
  else {
    bRam301751 = bRam301751 | 0x20;
  }
  if ((uRam00fd60 & 0x200) == 0) {
    bRam301752 = bRam301752 & 0xf7;
  }
  else {
    bRam301752 = bRam301752 | 8;
  }
  if ((bRam30479b & 4) == 0) {
    if ((uRam00fd60 & 0x200) == 0) {
      if (((bRam304d33 & 2) != 0) && ((uRam00fd60 & 0x20) != 0)) {
        uStack_10 = (uStack_10 >> 8 & 0x90 | 0x60) << 8 | 2;
      }
    }
    else if (((bRam304d33 & 2) != 0) && ((uRam00fd60 & 0x20) != 0)) {
      if (uRam30521a < uRam026a58) {
        if (uRam30521a <= uRam026a56) {
          uStack_10 = (uStack_10 >> 8 & 0x90 | 0x62) << 8 | 1;
        }
      }
      else {
        uStack_10 = (uStack_10 >> 8 & 0x90 | 0x61) << 8 | 1;
      }
    }
  }
  else {
    uStack_10 = (uStack_10 >> 8 & 0x90 | 0x60) << 8 | 2;
  }
  if ((uRam00fd60 & 0x100) == 0) {
    bRam301751 = bRam301751 & 0xfb;
    if (((uRam00fd60 & 0x100) == 0) && ((bRam301752 & 4) != 0)) {
      uStack_12 = uRam303b06 & 0xfffb;
    }
  }
  else {
    if (((bRam304d33 & 4) == 0) || ((uRam00fd60 & 0x20) != 0)) {
      bRam301751 = bRam301751 & 0xfb;
    }
    else {
      bRam301751 = bRam301751 | 4;
    }
    if (((bRam301751 & 0x40) == 0) && ((bRam301751 & 4) != 0)) {
      uStack_12 = uRam303b06 & 0xff00 | uRam303b06 & 0xff00 | 4;
      bRam301750 = bRam301750 | 0x10;
    }
    else {
      bRam301750 = bRam301750 & 0xef;
    }
  }
  if ((bRam301751 & 4) == 0) {
    bRam301751 = bRam301751 & 0xbf;
  }
  else {
    bRam301751 = bRam301751 | 0x40;
  }
  if ((uRam00fd60 & 0x100) == 0) {
    bRam301752 = bRam301752 & 0xfb;
  }
  else {
    bRam301752 = bRam301752 | 4;
  }
  if ((bRam30479b & 2) == 0) {
    if ((uRam00fd60 & 0x100) == 0) {
      if (((bRam304d33 & 4) != 0) && ((uRam00fd60 & 0x20) != 0)) {
        uStack_12 = (uStack_12 >> 8 & 0x90 | 0x60) << 8 | 2;
      }
    }
    else if (((bRam304d33 & 4) != 0) && ((uRam00fd60 & 0x20) != 0)) {
      if (uRam305216 < uRam026a54) {
        if (uRam305216 <= uRam026a52) {
          uStack_12 = (uStack_12 >> 8 & 0x90 | 0x62) << 8 | 1;
        }
      }
      else {
        uStack_12 = (uStack_12 >> 8 & 0x90 | 0x61) << 8 | 1;
      }
    }
  }
  else {
    uStack_12 = (uStack_12 >> 8 & 0x90 | 0x60) << 8 | 2;
  }
  if ((uRam00fd60 & 0x800) == 0) {
    bRam301751 = bRam301751 & 0xf7;
    if (((uRam00fd60 & 0x800) == 0) && ((bRam301752 & 2) != 0)) {
      uStack_c = uRam303bd0 & 0xfffb;
    }
  }
  else {
    if (((bRam304d33 & 0x10) == 0) || ((uRam00fd60 & 0x20) != 0)) {
      bRam301751 = bRam301751 & 0xf7;
    }
    else {
      bRam301751 = bRam301751 | 8;
    }
    if (((bRam301751 & 0x80) == 0) && ((bRam301751 & 8) != 0)) {
      uStack_c = uRam303bd0 & 0xff00 | uRam303bd0 & 0xff00 | 4;
      bRam301750 = bRam301750 | 0x80;
    }
    else {
      bRam301750 = bRam301750 & 0x7f;
    }
  }
  if ((bRam301751 & 8) == 0) {
    bRam301751 = bRam301751 & 0x7f;
  }
  else {
    bRam301751 = bRam301751 | 0x80;
  }
  if ((uRam00fd60 & 0x800) == 0) {
    bRam301752 = bRam301752 & 0xfd;
  }
  else {
    bRam301752 = bRam301752 | 2;
  }
  if ((bRam30479a & 0x40) == 0) {
    if ((uRam00fd60 & 0x800) == 0) {
      if (((bRam304d33 & 0x10) != 0) && ((uRam00fd60 & 0x20) != 0)) {
        uStack_c = (uStack_c >> 8 & 0x90 | 0x60) << 8 | 2;
      }
    }
    else if (((bRam304d33 & 0x10) != 0) && ((uRam00fd60 & 0x20) != 0)) {
      if (sRam305222 - sRam026a68 < 0 ==
          (sRam305222 < 0 != sRam026a68 < 0 && sRam305222 - sRam026a68 < 0 != sRam305222 < 0)) {
        uStack_c = (uStack_c >> 8 & 0x90 | 0x61) << 8 | 1;
      }
      else if (sRam305222 == sRam026a66 ||
               sRam305222 - sRam026a66 < 0 !=
               (sRam305222 < 0 != sRam026a66 < 0 && sRam305222 - sRam026a66 < 0 != sRam305222 < 0))
      {
        uStack_c = (uStack_c >> 8 & 0x90 | 0x62) << 8 | 1;
      }
    }
  }
  else {
    uStack_c = (uStack_c >> 8 & 0x90 | 0x60) << 8 | 2;
  }
  if (((((bRam301612 & 1) == 0) && ((uRam302634 & 1) != 0)) && ((uRam302634 & 0x8000) != 0)) &&
     (bRam01b945 <= rpmclass_oppoint)) {
    bRam301752 = bRam301752 | 0x10;
  }
  else {
    bRam301752 = bRam301752 & 0xef;
  }
  uRam00fd62 = uVar8;
  if (((bRam301752 & 0x10) == 0) || ((DAT_00fd34 & 0x10) == 0)) {
    uRam300bda = 0x7fff0000;
    bRam304d37 = 0;
    uRam00fd60 = uRam00fd60 & 0xefff;
  }
  else {
    if ((uRam00fd60 & 0x1000) == 0) {
      bRam301752 = bRam301752 & 0xdf;
    }
    else {
      bRam301752 = bRam301752 | 0x20;
    }
    if (bRam304d37 != 0xff) {
      bRam304d37 = bRam304d37 + 1;
    }
    uRam300bda = me7_pt1_integrator((ushort)bRam01b949 << 8,uRam302816,uRam300bda._2_2_,
                                    (undefined2)uRam300bda);
    uVar8 = (ushort)((uint)uRam300bda >> 0x10);
    if (uRam302816 < uVar8) {
      if ((bRam01b943 < bRam304d37) && (uVar8 - uRam302816 < (ushort)bRam01b92d * 0x100)) {
        uRam00fd60 = uRam00fd60 | 0x1000;
      }
    }
    else if ((bRam01b943 < bRam304d37) && (uRam302816 - uVar8 < (ushort)bRam01b92d * 0x100)) {
      uRam00fd60 = uRam00fd60 | 0x1000;
    }
    if ((uRam00fd60 & 0x1000) == 0) {
      if (bRam01b944 < bRam304d37) {
        uStack_a = (uVar5 >> 8 & 0x90 | 0x68) << 8 | 1;
      }
    }
    else {
      uVar5 = uVar5 >> 8;
      uStack_a = (uVar5 & 0x9f | 0x60) << 8 | 2;
      sVar7 = me7_lookup_1d_byte(0x392e,6,uRam301626);
      if (uRam300bda._2_2_ < (ushort)(sVar7 * 0x100)) {
        uStack_a = (uVar5 & 0x90 | 0x62) << 8 | 1;
      }
      else {
        sVar7 = me7_lookup_1d_byte(0x3937,6,uRam301626);
        if ((ushort)(sVar7 * 0x100) < uRam300bda._2_2_) {
          uStack_a = (uVar5 & 0x90 | 0x61) << 8 | 1;
        }
        else if (((bRam301752 & 0x20) == 0) && (bRam304d37 <= bRam01b944)) {
          uStack_a = (uVar5 & 0x90 | 0x60) << 8 | 2;
        }
      }
    }
  }
  uRam00fd60 = uRam00fd60 & 0xdfff | (uRam00fd62 & 1) << 0xd;
LAB_0c389c:
  func_0x0b31ac(0x40,uStack_12);
  func_0x0b31ac(0x42,uStack_10);
  func_0x0b31ac(0xa3,uStack_e);
  func_0x0b31ac(0xa5,uStack_c);
  func_0x0b31ac(0x44,uStack_a);
  return;
}


// ================= diag_boost_status_monitor @ 0d777a =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC: boost/charge status monitor + CAN packer (3x sub_B31AC); gated
   word_FD04.7/word_FD7A.15/word_FD7E.2; reads word thresholds 0x27DEE-0x27DFA via mov/cmp (0xD785C
   cmp r7,word_27DF2; 0xD7EB0 cmp r6,word_27DEE) + byte config 0x1BAA8-0x1BABB; sets status bits
   word_FD7E.2-.5 + byte_304DDF; no actuator/setpoint write [C mechanism; monitor identity I] */

void diag_boost_status_monitor(void)

{
  bool bVar1;
  ushort uVar2;
  short sVar3;
  byte bVar4;
  byte bVar5;
  ushort uVar6;
  byte bVar7;
  ushort uStack_a;
  ushort uStack_8;
  ushort uStack_6;
  
  if ((uRam303bf6 & 1) != 0) {
    return;
  }
  if (bRam304d30 < bRam01bab4) {
    return;
  }
  if ((uRam00fd04 & 0x80) == 0) {
    return;
  }
  if ((_flags_start_phase & 0x8000) == 0) {
    return;
  }
  if ((uRam00fd7e & 4) != 0) {
    uRam305740 = uRam305740 + 1;
    uRam00fd7e = uRam00fd7e & 0xfffb;
  }
  if ((bRam304dd8 < bRam01bab1) || (bRam01bab0 < bRam304dd8)) {
    uRam00fd7e = uRam00fd7e | 8;
    uRam305742 = uRam305742 + 1;
  }
  else {
    uRam00fd7e = uRam00fd7e & 0xfff7;
  }
  if ((bRam304dd9 < bRam01bab1) || (bRam01bab0 < bRam304dd9)) {
    uRam00fd7e = uRam00fd7e | 0x10;
    uRam305742 = uRam305742 + 1;
  }
  else {
    uRam00fd7e = uRam00fd7e & 0xffef;
  }
  if ((bRam304dda < bRam01bab1) || (bRam01bab0 < bRam304dda)) {
    uRam00fd7e = uRam00fd7e | 0x20;
    uRam305742 = uRam305742 + 1;
  }
  else {
    uRam00fd7e = uRam00fd7e & 0xffdf;
  }
  uStack_8 = uRam303ae0 & 0xf0ff;
  if (uRam305740 < uRam027df2) {
    if (sRam302df8 == 0) {
      bRam301849 = bRam301849 | 0x20;
    }
    else {
      sRam302df8 = sRam302df8 + -1;
    }
  }
  else {
    uRam026df8 = uRam027df4;
    bRam301849 = bRam301849 & 0xdf;
  }
  if (((bRam301849 & 0x20) == 0) || ((uRam00fd7e & 2) == 0)) {
    bRam30184b = bRam30184b & 0xfe;
  }
  else {
    bRam30184b = bRam30184b | 1;
  }
  if (((bRam301849 & 0x20) == 0) || ((uRam00fd7e & 2) != 0)) {
    bRam30184b = bRam30184b & 0xfd;
  }
  else {
    bRam30184b = bRam30184b | 2;
  }
  if (uRam305742 < bRam01bab3) {
    bRam30184b = bRam30184b & 0xfb;
  }
  else {
    bRam30184b = bRam30184b | 4;
  }
  if ((uRam305740 < uRam027df2) && ((uRam305740 < 0xff || (bRam01bab3 <= uRam305742)))) {
    bRam30184b = bRam30184b & 0xf7;
  }
  else {
    bRam30184b = bRam30184b | 8;
  }
  if (uRam027dfa <= uRam305740) {
    uRam305742 = 0;
  }
  if (uRam305740 == 0) {
    uRam026df4 = uRam027df4;
    bRam301849 = bRam301849 & 0xbf;
  }
  else if (sRam302df4 == 0) {
    bRam301849 = bRam301849 | 0x40;
  }
  else {
    sRam302df4 = sRam302df4 + -1;
  }
  if ((bRam301849 & 0x40) != 0) {
    uRam305740 = 0;
    uRam026df4 = uRam027df4;
    bRam301849 = bRam301849 & 0xbf;
  }
  if ((bRam30184b & 1) == 0) {
    if ((bRam30184b & 2) != 0) {
      uStack_8 = ((uRam303ae0 & 0xf000) >> 8 | 2) << 8;
      goto LAB_0d7a44;
    }
    if ((bRam30184b & 4) != 0) {
      uStack_8 = ((uRam303ae0 & 0xf000) >> 8 | 4) << 8;
      goto LAB_0d7a44;
    }
    if ((bRam30184b & 8) != 0) {
      uStack_8 = uRam303ae0 & 0xf0fe;
      goto LAB_0d7a44;
    }
  }
  else {
    uStack_8 = ((uRam303ae0 & 0xf000) >> 8 | 1) << 8;
LAB_0d7a44:
    uStack_8 = (uStack_8 >> 8 & 0x9f | 0x60) << 8 | 2;
  }
  func_0x0b31ac(0x2d,uStack_8);
  uStack_6 = uRam303bf2 & 0xf0ff;
  bVar4 = (char)((ushort)bRam301626 * 3 >> 2) + 0xc;
  uVar6 = ((ushort)rpmclass_oppoint * 3 >> 2) + 0xc;
  uVar2 = ((ushort)bRam304ddb * 200 >> 8) + 0x14;
  if ((bRam301849 & 1) == 0) {
    bRam304de0 = bRam304ddb;
    bRam301849 = bRam301849 | 1;
  }
  if ((bRam01bab6 < bVar4) && (uRam027df6 < uRam3055d0)) {
    bRam301849 = bRam301849 | 8;
  }
  else {
    bRam301849 = bRam301849 & 0xf7;
  }
  bVar7 = (byte)uVar6;
  if (bVar7 < (byte)uVar2) {
    sVar3 = (uVar2 & 0xff) - (uVar6 & 0xff);
  }
  else {
    sVar3 = (uVar6 & 0xff) - (uVar2 & 0xff);
  }
  if ((ushort)bRam01bab7 < sVar3 + 0x3cU) {
    bRam301849 = bRam301849 | 0x10;
  }
  else {
    bRam301849 = bRam301849 & 0xef;
  }
  if ((bRam301849 & 0x10) == 0) {
    bRam019847 = bRam01bab2;
    bRam30184a = bRam30184a & 0xfe;
  }
  else if (cRam301847 == '\0') {
    bRam30184a = bRam30184a | 1;
  }
  else {
    cRam301847 = cRam301847 + -1;
  }
  if (((bRam301849 & 8) == 0) || ((bRam30184a & 1) == 0)) {
    bRam301849 = bRam301849 & 0xfd;
  }
  else {
    bRam301849 = bRam301849 | 2;
  }
  if ((bRam01bab5 < bVar4) && (bRam01baba < bVar7)) {
    bRam301849 = bRam301849 | 8;
  }
  else {
    bRam301849 = bRam301849 & 0xf7;
  }
  if ((byte)uVar2 < bRam01bab9) {
    if (sRam302df6 == 0) {
      bRam30184a = bRam30184a | 2;
    }
    else {
      sRam302df6 = sRam302df6 + -1;
    }
  }
  else {
    uRam026df6 = uRam027df8;
    bRam30184a = bRam30184a & 0xfd;
  }
  if (((bRam301849 & 8) == 0) || ((bRam30184a & 2) == 0)) {
    bRam301849 = bRam301849 & 0xfb;
  }
  else {
    bRam301849 = bRam301849 | 4;
  }
  if (((bRam301849 & 2) == 0) && ((bRam301849 & 4) == 0)) {
    bRam30184b = bRam30184b & 0xef;
  }
  else {
    bRam30184b = bRam30184b | 0x10;
  }
  if (bRam304de0 < bRam304ddb) {
    uVar6 = (ushort)bRam304ddb - (ushort)bRam304de0;
  }
  else {
    uVar6 = (ushort)bRam304de0 - (ushort)bRam304ddb;
  }
  uVar2 = (ushort)bRam01babb;
  if (uVar6 == uVar2 ||
      (short)(uVar6 - uVar2) < 0 !=
      ((short)uVar6 < 0 && (short)(uVar6 - uVar2) < 0 != (short)uVar6 < 0)) {
    bRam301849 = bRam301849 & 0xf7;
  }
  else {
    bRam301849 = bRam301849 | 8;
  }
  if (((bRam301849 & 0x10) == 0) && (bRam301848 < bRam01bab2)) {
    bRam301849 = bRam301849 | 0x80;
    bRam301848 = bRam301848 + 1;
  }
  else {
    bRam301849 = bRam301849 & 0x7f;
  }
  if ((bRam30184b & 0x10) == 0) {
    if ((((bRam301849 & 0x80) != 0) || ((bRam301849 & 8) != 0)) || ((bRam301849 & 4) == 0)) {
      uStack_6 = uRam303bf2 & 0xf0fe;
      goto LAB_0d7d66;
    }
  }
  else {
    uStack_6 = ((uRam303bf2 & 0xf000) >> 8 | 8) << 8;
LAB_0d7d66:
    uStack_6 = (uStack_6 >> 8 & 0x9f | 0x60) << 8 | 2;
  }
  func_0x0b31ac(0xb6,uStack_6);
  uStack_a = uRam303b12 & 0xf0ff;
  bVar4 = bRam304ddf;
  if (nmot_rpmclass < bRam01baab) {
    bVar4 = 1;
  }
  bVar5 = bRam304ddf | bVar4;
  if (bRam01baac < bRam30740e) {
    bVar5 = 2;
  }
  bVar5 = bRam304ddf | bVar4 | bVar5;
  bVar4 = bVar5;
  if (bRam3055d8 < 4) {
    bVar4 = 4;
  }
  bVar5 = bVar5 | bVar4;
  bRam304ddf = bVar5;
  if (bRam01baaf < bRam3055d8) {
    bRam304ddf = 8;
  }
  bRam304ddf = bVar5 | bRam304ddf;
  if (((bRam01baa9 < bRam304dc4) && (bRam304dc4 < bRam01baaa)) &&
     ((bRam01bab8 < bVar7 && (bRam304ddf == 0xf)))) {
    if (bRam304dc5 < bRam304dc4) {
      uVar6 = (ushort)bRam304dc4 - (ushort)bRam304dc5;
    }
    else {
      uVar6 = (ushort)bRam304dc5 - (ushort)bRam304dc4;
    }
    uVar2 = (ushort)bRam01baa8;
    if (uVar6 == uVar2 ||
        (short)(uVar6 - uVar2) < 0 !=
        ((short)uVar6 < 0 && (short)(uVar6 - uVar2) < 0 != (short)uVar6 < 0)) {
      bVar1 = uRam30573e < 2;
      uRam30573e = uRam30573e - 2;
      if (bVar1) {
        uRam30573e = 0;
      }
      bRam304ddf = 0;
    }
    else {
      uRam30573e = uRam30573e + 1;
      if (uRam027dee < uRam30573e) {
        uRam30573e = uRam027dee;
      }
    }
  }
  MDH = (ushort)bRam304dc8 * 0x2d + 0x9f6;
  MDL = MDH / 0x41;
  MDH = MDH % 0x41;
  MDC = MDC | 0x10;
  bVar4 = (byte)MDL;
  if (bRam01baae < bVar4) {
    bRam30184a = bRam30184a | 4;
  }
  else {
    bRam30184a = bRam30184a & 0xfb;
  }
  if (bVar4 < bRam01baad) {
    bRam30184a = bRam30184a | 8;
  }
  else {
    bRam30184a = bRam30184a & 0xf7;
  }
  if (uRam30573e == uRam027df0) {
    bRam30184a = bRam30184a | 0x20;
  }
  else {
    bRam30184a = bRam30184a & 0xdf;
  }
  if (((bRam01baae < bVar4) && (bVar4 < bRam01baad)) && (uRam30573e != 0)) {
    bRam30184a = bRam30184a & 0xef;
  }
  else {
    bRam30184a = bRam30184a | 0x10;
  }
  if ((bRam30184a & 4) == 0) {
    if ((bRam30184a & 8) == 0) {
      if ((bRam30184a & 0x20) == 0) {
        if ((bRam30184a & 0x10) == 0) goto LAB_0d8034;
        uStack_a = uRam303b12 & 0xf0fe;
      }
      else {
        uStack_a = ((uRam303b12 & 0xf000) >> 8 | 8) << 8;
      }
    }
    else {
      uStack_a = ((uRam303b12 & 0xf000) >> 8 | 2) << 8;
    }
  }
  else {
    uStack_a = ((uRam303b12 & 0xf000) >> 8 | 1) << 8;
  }
  uStack_a = (uStack_a >> 8 & 0x9f | 0x60) << 8 | 2;
LAB_0d8034:
  func_0x0b31ac(0x46,uStack_a);
  return;
}


// ================= diag_boost_limit_monitor @ 0d8dca =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC: boost/limit status monitor; 1-D byte lookups sub_419F4 (0xD8DE4/0xD8E0A/0xD8EBA) +
   sub_41BD4/sub_42D2C; reads byte tables 0x1BAC2-0x1BB50 + word 0x27EA8-0x27EB0; sets status/flag
   bytes byte_300E28/2C/2D + byte_301852 + word_FD7E.7, gated word_FD3C.9/FD6C.15/FD1C.13; packs via
   sub_B31AC x2; no actuator/setpoint write [C mechanism; monitor identity I] */

byte diag_boost_limit_monitor(void)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  ushort uVar4;
  byte bVar5;
  char cVar6;
  ushort uStack_a;
  
  bVar5 = me7_lookup_1d_byte(0x3b3d,6,uRam304db1);
  if (bVar5 < nmot_rpmclass) {
    bRam301852 = bRam301852 | 4;
  }
  else {
    bRam301852 = bRam301852 & 0xfb;
  }
  bRam304e0e = me7_lookup_1d_byte(0x3b1a,6,uRam301729);
  bVar5 = bRam304e0e >> 1;
  cVar6 = bVar5 - cRam01bac2;
  if (cRam01bac2 < '\0' && (char)(bVar5 - cRam01bac2) < '\0') {
    cVar6 = -0x80;
  }
  if (cVar6 < '\0') {
    cVar6 = '\0';
  }
  sVar1 = -(short)cRam304e17;
  sVar2 = -(short)(char)bVar5;
  if (sVar2 == cRam304e17 ||
      sVar1 + sVar2 < 0 != (sVar1 < 0 && sVar1 - (char)bVar5 < 0 != sVar1 < 0)) {
    sVar2 = (short)cVar6;
    if (sVar1 - sVar2 < 0 != (sVar1 < 0 != sVar2 < 0 && sVar1 - sVar2 < 0 != sVar1 < 0)) {
      bRam300e28 = bRam300e28 & 0xfe;
    }
  }
  else {
    bRam300e28 = bRam300e28 | 1;
  }
  uStack_a = uRam303b52;
  if ((bRam300e28 & 1) == 0) {
    bRam300e22 = 0;
  }
  else if (bRam300e22 < bRam01bb4f) {
    bRam300e22 = bRam300e22 + 1;
  }
  else {
    uStack_a = (uRam303b52 >> 8 & 0x90 | 0x61) << 8 | 2;
  }
  bRam304e0f = me7_lookup_1d_byte(0x3b2b,6,uRam301729);
  if ((((bRam301852 & 4) == 0) || (_rl_w <= (ushort)bRam01bb44 * 0x20)) || ((DAT_301850 & 2) == 0))
  {
LAB_0d8f3e:
    bRam300e23 = 0;
  }
  else {
    sVar1 = (short)cRam304e17;
    sVar2 = (short)(char)(bRam304e0f >> 1);
    if (sVar2 == -sVar1 || sVar2 + sVar1 < 0 != (-sVar1 < 0 && sVar2 + sVar1 < 0)) goto LAB_0d8f3e;
    if (bRam300e23 < bRam01bb50) {
      bRam300e23 = bRam300e23 + 1;
    }
    else {
      uStack_a = (uStack_a >> 8 & 0x90 | 0x60) << 8 | 2;
    }
  }
  func_0x0b31ac(0x66,uStack_a);
  uVar4 = uRam303b54;
  bVar5 = bRam01bb42;
  if ((uRam303b54 & 1) == 0) {
    bVar5 = bRam01bb43;
  }
  if ((((DAT_301850 & 2) == 0) || ((uRam00fd7e & 0x80) != 0)) ||
     (((bRam301852 & 4) == 0 || (_rl_w <= (ushort)bVar5 * 0x20)))) {
    bRam300e28 = bRam300e28 & 0xfd;
  }
  else {
    bRam300e28 = bRam300e28 | 2;
  }
  uStack_a = uRam303b54;
  sRam300e32 = func_0x042d2c(uRam027eae,(short)cRam304e17,_DAT_304e32);
  cVar6 = (char)((ushort)sRam300e32 >> 8);
  cRam304e0d = cRam304e17;
  if ((char)(cVar6 - cRam304e17) < '\0' !=
      (sRam300e32 < 0 != cRam304e17 < '\0' && (char)(cVar6 - cRam304e17) < '\0' != sRam300e32 < 0))
  {
    cRam304e0d = cVar6;
  }
  if ((((bRam304e28 & 2) == 0) ||
      (cRam304e0d == cRam01bac3 ||
       (char)(cRam304e0d - cRam01bac3) < '\0' !=
       (cRam304e0d < '\0' != cRam01bac3 < '\0' &&
       (char)(cRam304e0d - cRam01bac3) < '\0' != cRam304e0d < '\0'))) ||
     ((sRam305760 - sRam027eaa < 0 !=
       (sRam305760 < 0 != sRam027eaa < 0 && sRam305760 - sRam027eaa < 0 != sRam305760 < 0) &&
      (sRam305758 - sRam027eb0 < 0 !=
       (sRam305758 < 0 != sRam027eb0 < 0 && sRam305758 - sRam027eb0 < 0 != sRam305758 < 0))))) {
    bRam300e28 = bRam300e28 & 0xf7;
    bRam300e27 = 0;
  }
  else if (bRam300e27 < bRam01bb46) {
    bRam300e27 = bRam300e27 + 1;
  }
  else {
    uStack_a = (uVar4 >> 8 & 0x90 | 0x62) << 8 | 2;
    bRam300e28 = bRam300e28 | 8;
  }
  if ((((char)(cRam304e17 - cRam01bac4) < '\0' ==
        (cRam304e17 < '\0' != cRam01bac4 < '\0' &&
        (char)(cRam304e17 - cRam01bac4) < '\0' != cRam304e17 < '\0')) || ((bRam300e28 & 2) == 0)) ||
     (sRam305760 - sRam027ea8 < 0 !=
      (sRam305760 < 0 != sRam027ea8 < 0 && sRam305760 - sRam027ea8 < 0 != sRam305760 < 0))) {
    bRam301852 = bRam301852 & 0xfd;
    bRam300e26 = 0;
  }
  else {
    bRam301852 = bRam301852 | 2;
    if (bRam300e26 < bRam01bb4e) {
      bRam300e26 = bRam300e26 + 1;
    }
    else {
      uStack_a = (uStack_a >> 8 & 0x90 | 0x60) << 8 | 2;
    }
  }
  func_0x0b31ac(0x67,uStack_a);
  uVar4 = uRam303b56;
  uStack_a = uRam303b56;
  if ((_flags_start_phase & 0x8000) == 0) {
    uRam018e36 = (ushort)bRam01bb4c;
    bRam300e2c = bRam300e2c & 0xef;
  }
  else if (sRam300e36 == 0) {
    bRam300e2c = bRam300e2c | 0x10;
  }
  else {
    sRam300e36 = sRam300e36 + -1;
  }
  if ((bRam01bb3c < nmot_rpmclass) && ((bRam300e2c & 0x10) != 0)) {
    bRam300e2d = bRam300e2d | 1;
  }
  else {
    bRam300e2d = bRam300e2d & 0xfe;
  }
  bRam304e10 = me7_lookup_2d_byte(0x3ac8,6,nmot_rpmclass,DAT_301792);
  MDL = (ushort)bRam304e10 * (ushort)bRam01bac5;
  MDH = 0;
  MDC = MDC | 0x10;
  uVar3 = MDL * 4;
  sVar1 = (ushort)(MDL * 2 < MDL || MDL * 2 < MDL) * 2 +
          (ushort)(MDL * 4 < MDL * 2 || MDL * 4 < MDL * 2);
  if (-sVar1 == (ushort)(uRam302be4 < uVar3) && uRam302be4 == uVar3 ||
      (sVar1 != 0 || sVar1 == 0 && uRam302be4 < uVar3)) {
    bRam301852 = bRam301852 & 0xfe;
  }
  else {
    bRam301852 = bRam301852 | 1;
  }
  if ((((uRam00fd3c & 0x200) == 0) || ((uRam00fd6c & 0x8000) != 0)) ||
     (((uRam00fd6e & 0x10) != 0 || ((uRam303abe & 1) != 0)))) {
    bRam301852 = bRam301852 & 0xf7;
  }
  else {
    bRam301852 = bRam301852 | 8;
  }
  if ((DAT_301850 & 2) == 0) {
    if (sRam300e20 == 0) {
      bRam300e2c = bRam300e2c | 0x40;
    }
    else {
      sRam300e20 = sRam300e20 + -1;
    }
  }
  else {
    uRam018e20 = (ushort)bRam01bb4d;
    bRam300e2c = bRam300e2c & 0xbf;
  }
  if (((uRam00fd1c & 0x2000) == 0) && ((DAT_00fd1e & 0x400) == 0)) {
    bRam300e28 = bRam300e28 & 0xdf;
  }
  else {
    bRam300e28 = bRam300e28 | 0x20;
  }
  if (((bRam300e28 & 0x20) != 0) && ((bRam300e28 & 0x40) == 0)) {
    uRam018e34 = (ushort)bRam01bb4d;
  }
  if (sRam300e34 == 0) {
    bRam300e2c = bRam300e2c & 0xfe;
  }
  else {
    bRam300e2c = bRam300e2c | 1;
  }
  if ((bRam300e2c & 1) != 0) {
    sRam300e34 = sRam300e34 + -1;
  }
  if ((bRam300e2c & 1) == 0) {
    bRam301851 = bRam301851 | 2;
  }
  else {
    bRam301851 = bRam301851 & 0xfd;
  }
  if ((bRam300e28 & 0x20) == 0) {
    bRam300e28 = bRam300e28 & 0xbf;
  }
  else {
    bRam300e28 = bRam300e28 | 0x40;
  }
  if (((((DAT_301850 & 2) == 0) || ((bRam300e2d & 1) == 0)) || ((bRam301852 & 1) == 0)) ||
     ((bRam301852 & 8) == 0)) {
    bRam300e2d = bRam300e2d & 0xfd;
  }
  else {
    bRam300e2d = bRam300e2d | 2;
  }
  if ((bRam300e2d & 2) == 0) {
    uRam018e2e = (ushort)bRam01bb47;
    bRam300e2c = bRam300e2c & 0xdf;
  }
  else if (sRam300e2e == 0) {
    bRam300e2c = bRam300e2c | 0x20;
  }
  else {
    sRam300e2e = sRam300e2e + -1;
  }
  if ((bRam300e2c & 0x20) != 0) {
    uStack_a = (uVar4 >> 8 & 0x90 | 0x62) << 8 | 2;
  }
  bRam304e11 = me7_lookup_1d_byte(0x3e9c,9,rpmclass_oppoint);
  if ((((bRam305850 & 2) == 0) || ((bRam300e2d & 1) == 0)) || ((bRam301852 & 8) == 0)) {
LAB_0d9382:
    bRam300e2d = bRam300e2d & 0xfb;
  }
  else {
    MDL = (ushort)bRam304e10 * (ushort)bRam01bac6;
    MDH = 0;
    MDC = MDC | 0x10;
    uVar4 = MDL * 4;
    sVar1 = (ushort)(MDL * 2 < MDL || MDL * 2 < MDL) * 2 +
            (ushort)(MDL * 4 < MDL * 2 || MDL * 4 < MDL * 2);
    if (-sVar1 == (ushort)(uRam302be4 < uVar4) && uRam302be4 == uVar4 ||
        (sVar1 != 0 || sVar1 == 0 && uRam302be4 < uVar4)) goto LAB_0d9382;
    bRam300e2d = bRam300e2d | 4;
  }
  if ((bRam300e2d & 4) == 0) {
    uRam018e30 = (ushort)bRam01bb49;
    bRam300e2c = bRam300e2c & 0xfb;
  }
  else if (sRam300e30 == 0) {
    bRam300e2c = bRam300e2c | 4;
  }
  else {
    sRam300e30 = sRam300e30 + -1;
  }
  if ((((bRam300e2d & 1) == 0) || ((uRam00fd1c & 0x2000) == 0)) ||
     (((bRam301851 & 2) == 0 || (((bRam301852 & 8) == 0 || ((uRam00fd5e & 2) != 0)))))) {
LAB_0d9412:
    bRam300e2d = bRam300e2d & 0xf7;
  }
  else {
    MDL = (ushort)bRam304e10 * (ushort)bRam304e11;
    MDH = 0;
    MDC = MDC | 0x10;
    cVar6 = (MDL * 2 < MDL || MDL * 2 < MDL) * '\x02' + (MDL * 4 < MDL * 2 || MDL * 4 < MDL * 2);
    if (cVar6 == '\0' && (cVar6 != '\0' || MDL * 4 <= uRam302be4)) goto LAB_0d9412;
    bRam300e2d = bRam300e2d | 8;
  }
  if ((bRam300e2d & 8) == 0) {
    uRam018e38 = (ushort)bRam01bb4a;
    bRam300e2c = bRam300e2c & 0x7f;
  }
  else if (sRam300e38 == 0) {
    bRam300e2c = bRam300e2c | 0x80;
  }
  else {
    sRam300e38 = sRam300e38 + -1;
  }
  if ((((((bRam300e2d & 1) != 0) && ((bRam300e2c & 0x40) != 0)) && ((uRam00fd78 & 2) == 0)) &&
      (((uRam303be0 & 1) == 0 && ((bRam301851 & 2) != 0)))) &&
     (((bRam301852 & 8) != 0 && (((uRam00fd5e & 2) == 0 && (uRam3029f0 < uRam027eac)))))) {
    MDL = (ushort)bRam304e10 * (ushort)bRam01bac7;
    MDH = 0;
    MDC = MDC | 0x10;
    uVar4 = MDL * 4;
    sVar1 = (ushort)(MDL * 2 < MDL || MDL * 2 < MDL) * 2 +
            (ushort)(MDL * 4 < MDL * 2 || MDL * 4 < MDL * 2);
    if ((-sVar1 != (ushort)(uRam302be4 < uVar4) || uRam302be4 != uVar4) &&
        (sVar1 == 0 && (sVar1 != 0 || uRam302be4 >= uVar4))) {
      bRam300e2d = bRam300e2d | 0x10;
      goto LAB_0d94d6;
    }
  }
  bRam300e2d = bRam300e2d & 0xef;
LAB_0d94d6:
  if ((bRam300e2d & 0x10) == 0) {
    uRam018e24 = (ushort)bRam01bb4b;
    bRam300e2c = bRam300e2c & 0xf7;
  }
  else if (sRam300e24 == 0) {
    bRam300e2c = bRam300e2c | 8;
  }
  else {
    sRam300e24 = sRam300e24 + -1;
  }
  if ((((bRam300e2c & 4) == 0) && ((bRam300e2c & 0x80) == 0)) && ((bRam300e2c & 8) == 0)) {
    bRam300e2d = bRam300e2d & 0xdf;
  }
  else {
    bRam300e2d = bRam300e2d | 0x20;
  }
  if ((bRam300e2d & 0x20) != 0) {
    uStack_a = (uStack_a >> 8 & 0x90 | 0x61) << 8 | 2;
  }
  if ((((((bRam300e2d & 2) == 0) && ((bRam300e2d & 4) == 0)) &&
       (((bRam300e2d & 8) == 0 && (((bRam300e2d & 0x10) == 0 && ((bRam301852 & 4) != 0)))))) &&
      ((DAT_301850 & 2) != 0)) &&
     ((((bRam301852 & 8) != 0 && ((uRam00fd5e & 2) == 0)) && ((ushort)bRam01bb45 * 0x20 < _rl_w))))
  {
    bRam300e2d = bRam300e2d | 0x40;
  }
  else {
    bRam300e2d = bRam300e2d & 0xbf;
  }
  if ((bRam300e2d & 0x40) == 0) {
    uRam018e2a = (ushort)bRam01bb48;
    bRam300e2c = bRam300e2c & 0xfd;
  }
  else if (sRam300e2a == 0) {
    bRam300e2c = bRam300e2c | 2;
  }
  else {
    sRam300e2a = sRam300e2a + -1;
  }
  if ((bRam300e2c & 2) != 0) {
    uStack_a = (uStack_a >> 8 & 0x90 | 0x60) << 8 | 2;
  }
  func_0x0b31ac(0x68,uStack_a);
  if ((((bRam300e28 & 8) != 0) || ((bRam300e2c & 0x20) != 0)) ||
     (bVar5 = bRam300e2d & 0x20, (bRam300e2d & 0x20) != 0)) {
    bVar5 = 1;
    bRam301851 = bRam301851 | 1;
  }
  return bVar5;
}


// ================= diag_rationality_monitor_b @ 09b534 =================

/* WARNING: Removing unreachable block (ram,0x09be1e) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC: sensor/model rationality-monitor channel (cluster with diag_rationality_monitor
   sub_9A034 + sub_99414, ALGORITHM.md): builds a modelled quantity via PT1 sub_42CF4 + clamped
   integrator sub_430DA, windows it vs scalar thresholds (byte band 0x1A054-0x1A05F incl EXBLASH
   0x1A05B; word band 0x23F84-0x23FA2 at 0x9BEF6 mov r6,word_23F84 - both mov/cmp not maps) ->
   state/status bytes byte_30167E/7F/301684, byte_304994/95, page-C2 byte_30A0ED/30A038, model words
   word_302B1E/22/28, word_305324/2C; packs CAN frame 0x63 (0x9C83C mov r12,#63h; sub_B31AC); no
   actuator/setpoint write [C mechanism; monitored channel I] */

void diag_rationality_monitor_b(void)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  ushort uVar5;
  undefined2 uVar6;
  ushort uVar7;
  ushort uVar8;
  ushort uVar9;
  short sVar10;
  ushort uStack_e;
  
  uVar5 = uRam303b4c;
  uStack_e = uRam303b4c;
  if (((bRam01a055 & 4) == 0) && ((uRam302634 & 8) == 0)) {
    uRam305324 = 0;
  }
  else {
    uRam305324 = uRam023f88;
  }
  if ((_flags_diag_enable_b & 1) != 0) {
    if ((uRam023f96 < _rl_scaled) && (_rl_scaled < uRam023f94)) {
      cRam304994 = cRam01a058;
      bRam301673 = bRam301673 | 1;
    }
    else if (cRam304994 == '\0') {
      bRam301673 = bRam301673 & 0xfe;
    }
    else {
      cRam304994 = cRam304994 + -1;
    }
    if ((flags_torque_revlimit & 0x80) == 0) {
      bRam301679 = bRam301679 & 0xfe;
    }
    else {
      bRam301679 = bRam301679 | 1;
      if ((bRam30167d & 0x10) == 0) {
        uRam30532c = 0;
      }
      uVar7 = _rl_scaled + uRam30532c;
      bVar3 = _rl_scaled + uRam30532c < uRam30532c;
      uRam30532c = _rl_scaled + uRam30532c;
      if (uVar7 < _rl_scaled || bVar3) {
        uRam30532c = 0xffff;
      }
    }
    if (uRam023f98 < uRam30532c) {
      bRam301673 = bRam301673 | 2;
    }
    else {
      bRam301673 = bRam301673 & 0xfd;
    }
    if (((((uRam303bb0 & 1) == 0) && ((uRam303be0 & 1) == 0)) && ((uRam303be4 & 1) == 0)) &&
       ((uRam303c02 & 1) == 0)) {
      bRam30167d = bRam30167d & 0xfb;
    }
    else {
      bRam30167d = bRam30167d | 4;
    }
  }
  if ((_flags_diag_enable_b & 1) == 0) {
    uStack_e = ((uRam303b4c & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
    goto LAB_09c838;
  }
  if ((bRam30167d & 4) == 0) {
    bRam301677 = bRam301677 & 0xfe;
  }
  else {
    bRam301677 = bRam301677 | 1;
  }
  if ((bRam30a0ed & 0x40) == 0) {
    bRam301678 = bRam301678 & 0xfd;
  }
  else {
    bRam301678 = bRam301678 | 2;
  }
  if ((((uRam303b5e & 1) == 0) && ((uRam303b22 & 1) == 0)) && ((uRam303b1e & 1) == 0)) {
    PSW = PSW & 0xffbf;
    bVar3 = false;
  }
  else {
    PSW = PSW | 0x40;
    bVar3 = true;
  }
  if ((bRam30a0f8 & 0x40) == 0) {
    bRam301678 = bRam301678 & 0xfe;
  }
  else {
    bRam301678 = bRam301678 | 1;
  }
  if (bVar3) {
    bRam301678 = bRam301678 | 4;
  }
  else {
    bRam301678 = bRam301678 & 0xfb;
  }
  if (((bRam301677 & 1) == 0) && ((bRam301678 & 4) == 0)) {
    bRam301672 = bRam301672 & 0xfd;
  }
  else {
    bRam301672 = bRam301672 | 2;
  }
  if (((uRam023f92 < _rl_scaled) && ((bRam301671 & 2) != 0)) && ((uRam302634 & 1) == 0)) {
    if ((bRam01a055 & 0x10) == 0) {
      if ((bRam3018ce & 1) == 0) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
    }
    else {
      bVar1 = (bRam3018ce & 2) != 0;
    }
    if (((!bVar1) && ((bRam301670 & 8) == 0)) &&
       (((bRam301674 & 1) == 0 && ((bRam301671 & 8) == 0)))) goto LAB_09b7d2;
    PSW = PSW | 0x40;
  }
  else {
LAB_09b7d2:
    PSW = PSW & 0xffbf;
  }
  uVar7 = PSW & 0x40;
  if ((bVar3) || (((uRam302634 & 1) != 0 && ((uRam302634 & 8) != 0)))) {
    PSW = PSW | 0x40;
  }
  else {
    PSW = PSW & 0xffbf;
  }
  if ((uVar7 == 0x40) && ((bRam301678 & 2) != 0)) {
    bRam301670 = bRam301670 | 1;
  }
  else {
    bRam301670 = bRam301670 & 0xfe;
  }
  if ((PSW & 0x40) == 0) {
    bRam30a0ed = bRam30a0ed & 0x3d;
  }
  else {
    bRam30a0ed = bRam30a0ed | 0x80;
  }
  if ((bRam301686 & 0x20) == 0) {
    bRam301674 = bRam301674 & 0xfb;
  }
  else {
    bRam301674 = bRam301674 | 4;
  }
  if ((bRam301671 & 0x40) == 0) {
    bRam301686 = bRam301686 & 0xbf;
  }
  else {
    bRam301686 = bRam301686 | 0x40;
  }
  if ((uRam00fd56 & 0x400) == 0) {
    uRam022b22 = uRam023f9e;
    bRam301671 = bRam301671 & 0xfd;
  }
  else if (sRam302b22 == 0) {
    bRam301671 = bRam301671 | 2;
  }
  else {
    sRam302b22 = sRam302b22 + -1;
  }
  if (((uRam303b4c & 1) == 0) && ((uRam303b4c & 2) != 0)) {
    bRam301687 = bRam301687 | 0x40;
  }
  else {
    bRam301687 = bRam301687 & 0xbf;
  }
  if (((bRam301670 & 4) == 0) || ((bRam301687 & 0x20) != 0)) {
    PSW = PSW & 0xffbf;
    bVar3 = false;
  }
  else {
    PSW = PSW | 0x40;
    bVar3 = true;
  }
  if (((bRam301687 & 0x40) == 0) || ((bRam301687 & 0x80) != 0)) {
    if (bVar3) {
      bRam30a037 = bRam30a037 | 4;
      bRam30a038 = bRam30473e;
    }
  }
  else {
    bRam30a037 = bRam30a037 & 0xfb;
  }
  if ((((bRam301671 & 0x10) == 0) || ((bRam301671 & 0x20) == 0)) && ((bRam30a037 & 4) != 0)) {
    bRam304995 = bRam30a038;
  }
  else {
    bRam304995 = bRam30473e;
  }
  if ((bRam301687 & 0x40) == 0) {
    bRam301687 = bRam301687 & 0x7f;
  }
  else {
    bRam301687 = bRam301687 | 0x80;
  }
  if ((bRam301670 & 4) == 0) {
    bRam301687 = bRam301687 & 0xdf;
  }
  else {
    bRam301687 = bRam301687 | 0x20;
  }
  if (bRam3014bc < bRam304995) {
    bRam301686 = bRam301686 & 0xef;
    uRam01967e = uRam01a05c;
  }
  else if (cRam30167e == '\0') {
    bRam301686 = bRam301686 | 0x10;
  }
  else {
    cRam30167e = cRam30167e + -1;
  }
  if (bRam304995 < bRam3014bc) {
    bRam301686 = bRam301686 & 0xf7;
    uRam01967f = uRam01a05c;
  }
  else if (cRam30167f == '\0') {
    bRam301686 = bRam301686 | 8;
  }
  else {
    cRam30167f = cRam30167f + -1;
  }
  if ((bRam301674 & 4) == 0) {
    if (((bRam301671 & 2) != 0) && ((bRam301686 & 8) != 0)) {
      bRam301671 = bRam301671 | 0x20;
    }
  }
  else {
    bRam301671 = bRam301671 & 0xdf;
  }
  if ((bRam301674 & 4) == 0) {
    if (((bRam301671 & 2) != 0) && ((bRam301686 & 0x10) != 0)) {
      bRam301671 = bRam301671 | 0x10;
    }
  }
  else {
    bRam301671 = bRam301671 & 0xef;
  }
  if (((bRam301671 & 0x10) == 0) || ((bRam301671 & 0x20) == 0)) {
    bRam301671 = bRam301671 & 0xbf;
  }
  else {
    bRam301671 = bRam301671 | 0x40;
  }
  if (((bRam301671 & 0x40) == 0) || ((bRam301686 & 0x40) != 0)) {
    bRam301670 = bRam301670 & 0x7f;
  }
  else {
    bRam301670 = bRam301670 | 0x80;
  }
  if (((bRam301671 & 0x40) == 0) || ((bRam301670 & 4) != 0)) {
    bRam301686 = bRam301686 & 0xdf;
    uRam022b28 = uRam023fa0;
  }
  else if (sRam302b28 == 0) {
    bRam301686 = bRam301686 | 0x20;
  }
  else {
    sRam302b28 = sRam302b28 + -1;
  }
  if ((((uRam302634 & 1) == 0) || ((uRam302634 & 8) == 0)) && ((bRam01a055 & 4) == 0)) {
    bRam30167d = bRam30167d & 0xf7;
    bRam301671 = bRam301671 & 0xf7;
  }
  else {
    if (((bRam301687 & 2) == 0) || ((bRam301671 & 2) == 0)) {
      bRam30167d = bRam30167d & 0xf7;
    }
    else if ((bRam30167d & 8) == 0) {
      bRam301671 = bRam301671 | 8;
      bRam30167d = bRam30167d | 8;
    }
    if ((((bRam301671 & 0x10) != 0) && ((bRam301671 & 0x20) != 0)) || ((bRam301670 & 4) != 0)) {
      bRam301671 = bRam301671 & 0xf7;
    }
  }
  if ((DAT_00fd34 & 0x10) == 0) {
    uRam302b1e = 0;
    bRam301687 = bRam301687 & 0xfd;
  }
  else if (uRam302b1e < uRam023f9a) {
    uRam302b1e = uRam302b1e + 1;
  }
  else {
    bRam301687 = bRam301687 | 2;
  }
  if ((bRam301671 & 0x40) == 0) {
    if ((bRam301670 & 1) != 0) {
      if (uRam023f9c < uRam302b16) {
        bRam301670 = bRam301670 | 8;
      }
      else {
        uRam302b16 = uRam302b16 + 1;
      }
    }
  }
  else {
    bRam301670 = bRam301670 & 0xf7;
  }
  if (((bRam301671 & 0x80) != 0) || ((bRam301674 & 4) != 0)) {
    uRam302b16 = 0;
    bRam301670 = bRam301670 & 0xf7;
  }
  if (((((bRam301673 & 1) == 0) || ((bRam301671 & 2) == 0)) || ((uRam00fd4c & 0x1000) == 0)) ||
     (((bRam301670 & 4) != 0 || ((bRam301678 & 2) == 0)))) {
    bRam301672 = bRam301672 & 0xfe;
  }
  else {
    bRam301672 = bRam301672 | 1;
  }
  if ((((bRam3031aa & 2) == 0) && ((bRam3031aa & 1) == 0)) || ((_flags_start_phase & 0x8000) == 0))
  {
    bRam301688 = bRam301688 & 0xfd;
  }
  else {
    bRam301688 = bRam301688 | 2;
  }
  if (((bRam301670 & 0x80) == 0) && ((bRam301670 & 4) == 0)) {
    bRam301688 = bRam301688 & 0xf7;
  }
  else {
    bRam301688 = bRam301688 | 8;
  }
  if (((bRam301688 & 8) == 0) || ((bRam301688 & 0x10) != 0)) {
    if (((bRam301688 & 2) != 0) && ((bRam301688 & 4) == 0)) {
      bRam301688 = bRam301688 | 0x20;
    }
  }
  else {
    bRam301688 = bRam301688 & 0xdf;
  }
  if (((bRam301688 & 0x20) == 0) || ((bRam301671 & 2) == 0)) {
    PSW = PSW & 0xffbf;
  }
  else {
    PSW = PSW | 0x40;
  }
  uVar7 = PSW & 0x40;
  if (bVar3) {
    bRam301674 = bRam301674 | 1;
  }
  else {
    bRam301674 = bRam301674 & 0xfe;
  }
  if ((bRam301688 & 2) == 0) {
    bRam301688 = bRam301688 & 0xfb;
  }
  else {
    bRam301688 = bRam301688 | 4;
  }
  if ((bRam301688 & 8) == 0) {
    bRam301688 = bRam301688 & 0xef;
  }
  else {
    bRam301688 = bRam301688 | 0x10;
  }
  if ((bRam301672 & 1) == 0) {
    PSW = PSW | 0x40;
  }
  else {
    PSW = PSW & 0xffbf;
  }
  uVar8 = (PSW & 0x40) >> 6 ^ 1;
  if ((uVar7 == 0x40) || ((bRam301674 & 1) == 0)) {
    bRam301674 = bRam301674 & 0xbf;
  }
  else {
    bRam301674 = bRam301674 | 0x40;
  }
  if (((bRam301671 & 8) == 0) || (uVar8 == 0)) {
    bRam301670 = bRam301670 & 0xef;
  }
  else {
    bRam301670 = bRam301670 | 0x10;
  }
  if ((uVar8 == 0) || ((bRam301670 & 8) == 0)) {
    bRam301671 = bRam301671 & 0xfb;
  }
  else {
    bRam301671 = bRam301671 | 4;
  }
  bRam301672 = bRam301672 & 0xf7;
  sVar10 = uRam305328 - uRam30694a;
  if (uRam305328 < uRam30694a) {
    if (sVar10 >= 0) {
      sVar10 = -0x8000;
    }
  }
  else if (sVar10 < 0) {
    sVar10 = 0x7fff;
  }
  if (sVar10 < 0) {
    if (sVar10 == -0x8000) {
      sVar10 = 0x7fff;
    }
    else {
      iVar4 = (int)sVar10;
      sVar10 = (short)-iVar4;
      MDH = (undefined2)((uint)-iVar4 >> 0x10);
      MDC = MDC | 0x10;
      MDL = sVar10;
    }
  }
  if ((sVar10 == 0x29 || sVar10 + -0x29 < 0 != (sVar10 < 0 && sVar10 + -0x29 < 0 != sVar10 < 0)) ||
     ((bRam301670 & 0x40) == 0)) {
    bRam301684 = 0;
    bRam30167d = bRam30167d & 0xfe;
  }
  else if (bRam01a057 < bRam301684) {
    bRam30167d = bRam30167d | 1;
  }
  else {
    bRam301684 = bRam301684 + 1;
  }
  if ((bRam301686 & 2) == 0) {
    bRam301686 = bRam301686 & 0xfb;
  }
  else {
    bRam301686 = bRam301686 | 4;
  }
  if ((((bRam301674 & 0x40) == 0) && ((bRam301670 & 0x10) == 0)) && ((bRam301671 & 4) == 0)) {
    bRam301686 = bRam301686 & 0xfd;
  }
  else {
    bRam301686 = bRam301686 | 2;
  }
  if ((((bRam301670 & 0x40) == 0) ||
      (sVar10 != 0x29 && sVar10 + -0x29 < 0 == (sVar10 < 0 && sVar10 + -0x29 < 0 != sVar10 < 0))) ||
     ((bRam301686 & 4) == 0)) {
    bRam301670 = bRam301670 & 0xdf;
  }
  else {
    bRam301670 = bRam301670 | 0x20;
  }
  if ((bRam301671 & 0x40) == 0) {
    bRam301678 = bRam301678 & 0xcf;
  }
  else {
    bRam301678 = bRam301678 & 0xef | 0x20;
  }
  if (((bRam301670 & 0x40) != 0) != ((bRam301687 & 1) != 0)) {
    uRam305326 = 0x1000;
    uRam302b2c._2_2_ = 0x800;
    uRam302b2c._0_2_ = 0;
  }
  if ((bRam301687 & 1) == 0) {
    uRam305320 = 0x1000;
    bRam301674 = bRam301674 & 0xfd;
  }
  else {
    bVar3 = false;
    if (((bRam301671 & 0x10) != 0) && ((bRam301671 & 0x20) == 0)) {
      bVar3 = true;
    }
    uVar7 = uRam023f86 + 0x1000;
    if (uRam023f86 + 0x1000 < uRam023f86 || uRam023f86 + 0x1000 < 0x1000) {
      uVar7 = 0xffff;
    }
    uVar8 = 0x1000 - uRam023f84;
    if (0x1000 < uRam023f84) {
      uVar8 = 0;
    }
    uVar9 = uRam023f8e;
    if (uRam023f8e <= uVar8) {
      uVar9 = uVar8;
    }
    uRam302b1a = uRam023f90;
    if ((bRam021670 & 0x10) != 0) {
      uRam302b1a = uRam023f8c;
    }
    if (bVar3) {
      uRam302b1c = 0x7fff;
      uRam305320 = uVar7;
    }
    else {
      uRam302b1c = 0x8000;
      uRam305320 = uVar9;
    }
    uRam302b2c = func_0x0430da(uRam302b1a,uRam302b1c,uRam302b2c._2_2_,(undefined2)uRam302b2c,
                               uVar9 >> 1,uVar9 << 0xf,uVar7 >> 1,uVar7 << 0xf);
    uRam305326 = (ushort)uRam302b2c >> 0xf | (short)((uint)uRam302b2c >> 0x10) << 1;
    if (bVar3) {
      if (uRam305326 < uRam305320) {
        bRam301674 = bRam301674 & 0xfd;
      }
      else {
        bRam301674 = bRam301674 | 2;
      }
    }
    else if (uRam305320 < uRam305326) {
      bRam301674 = bRam301674 & 0xfd;
    }
    else {
      bRam301674 = bRam301674 | 2;
    }
  }
  if (((bRam021670 & 0x20) == 0) || ((bRam301674 & 2) == 0)) {
    uRam302b20 = uRam023fa2;
    bRam301671 = bRam301671 & 0x7f;
  }
  else if (uRam302b20 == 0) {
    bRam301671 = bRam301671 | 0x80;
  }
  else {
    uRam302b20 = uRam302b20 - 1;
  }
  if (((bRam301672 & 4) == 0) || ((bRam301671 & 0x40) == 0)) {
    if (((bRam301671 & 0x80) != 0) &&
       ((((bRam301671 & 8) != 0 || ((bRam301670 & 8) != 0)) || ((bRam301674 & 1) != 0)))) {
      bRam301670 = bRam301670 | 4;
    }
  }
  else {
    bRam301670 = bRam301670 & 0xfb;
  }
  if ((bRam301670 & 0x40) == 0) {
    bRam301687 = bRam301687 & 0xfe;
  }
  else {
    bRam301687 = bRam301687 | 1;
  }
  if ((((bRam30167d & 1) == 0) && ((bRam301686 & 2) != 0)) &&
     (((bRam301671 & 0x80) == 0 && ((bRam301678 & 0x20) == 0)))) {
    if ((bRam301686 & 2) != 0) {
      bRam301670 = bRam301670 | 0x40;
    }
  }
  else {
    bRam301670 = bRam301670 & 0xbf;
  }
  if (((bRam301678 & 0x20) == 0) && ((bRam301686 & 2) != 0)) {
    uRam305328 = uRam305326;
  }
  else {
    uRam305328 = 0x1000;
  }
  if ((bRam301679 & 1) == 0) {
    uRam019681 = uRam01a059;
    bRam301679 = bRam301679 & 0xf7;
  }
  else if (cRam301681 == '\0') {
    bRam301679 = bRam301679 | 8;
  }
  else {
    cRam301681 = cRam301681 + -1;
  }
  if ((uRam00fd28 & 0x1000) == 0) {
    sRam302b26 = 300;
    bRam301688 = bRam301688 & 0xfe;
  }
  else if (sRam302b26 == 0) {
    bRam301688 = bRam301688 | 1;
  }
  else {
    sRam302b26 = sRam302b26 + -1;
  }
  if (((bRam301688 & 1) == 0) || ((bRam30149c & 1) == 0)) {
    bRam301677 = bRam301677 & 0xfb;
  }
  else {
    bRam301677 = bRam301677 | 4;
  }
  if (((((((_flags_diag_cfg_a & 0x100) == 0) || ((bRam301679 & 8) == 0)) || ((bRam301673 & 2) == 0))
       || (((bRam301677 & 1) != 0 || ((uRam00fd56 & 2) == 0)))) || ((bRam301678 & 1) == 0)) ||
     ((bRam301677 & 4) == 0)) {
    bVar3 = false;
  }
  else {
    bVar3 = true;
  }
  if ((bRam01a05f < bRam3014bc) && (bVar3)) {
    if (cRam301682 == '\0') {
      bRam301670 = bRam301670 | 2;
    }
    else {
      cRam301682 = cRam301682 + -1;
    }
  }
  else {
    uRam019682 = uRam01a05a;
    bRam301670 = bRam301670 & 0xfd;
  }
  if ((!bVar3) || (bRam01a05f < bRam3014bc)) {
    uRam019683 = uRam01a05a;
    bRam301679 = bRam301679 & 0xef;
  }
  else if (cRam301683 == '\0') {
    bRam301679 = bRam301679 | 0x10;
  }
  else {
    cRam301683 = cRam301683 + -1;
  }
  if ((bRam301679 & 0x10) == 0) {
    if ((bRam301670 & 2) != 0) {
      bRam30a037 = bRam30a037 | 2;
    }
  }
  else {
    bRam30a037 = bRam30a037 & 0xfd;
  }
  if (((bRam301686 & 1) == 0) &&
     (((flags_torque_revlimit & 0x80) != 0 || ((bRam301670 & 0x20) != 0)))) {
    bRam301672 = bRam301672 & 0xfb;
  }
  else if (((bRam301670 & 2) != 0) || ((bRam301679 & 0x10) != 0)) {
    bRam301672 = bRam301672 | 4;
  }
  if ((uRam00fd56 & 4) == 0) {
    uRam019680 = uRam01a05b;
    bRam301687 = bRam301687 & 0xef;
  }
  else if (cRam301680 == '\0') {
    bRam301687 = bRam301687 | 0x10;
  }
  else {
    cRam301680 = cRam301680 + -1;
  }
  if (((bRam301687 & 0x10) == 0) || ((bRam301673 & 2) == 0)) {
    bRam301676 = bRam301676 & 0xbf;
  }
  else {
    bRam301676 = bRam301676 | 0x40;
  }
  if (((bRam301676 & 0x40) == 0) || ((bRam301686 & 0x80) != 0)) {
    if ((bRam301676 & 0x20) != 0) {
      bRam304996 = 0;
    }
    bRam301676 = bRam301676 & 0xdf;
  }
  else {
    bVar1 = (byte)(bRam304996 + 1) < bRam304996;
    bVar2 = bRam304996 == 0xff;
    bRam304996 = bRam304996 + 1;
    if (bVar1 || bVar2) {
      bRam304996 = 0xff;
    }
    uVar6 = me7_fraction_blend(uRam023f8a,uRam02167b,uRam302b2a);
    uRam302b2a._1_1_ = (byte)((ushort)uVar6 >> 8);
    bRam303273 = uRam302b2a._1_1_;
    uRam302b2a = uVar6;
    if (uRam302b2a._1_1_ < bRam01a05e) {
      if (bRam304996 < bRam01a054) {
        if ((bRam301676 & 0x20) != 0) {
          bRam304996 = 0;
        }
        bRam301676 = bRam301676 & 0xdf;
      }
      else {
        bRam301676 = bRam301676 | 0x20;
        bRam30a037 = bRam30a037 | 1;
      }
    }
    else {
      if ((bRam301676 & 0x20) != 0) {
        bRam304996 = 0;
      }
      bRam301676 = bRam301676 & 0xdf;
      bRam30a037 = bRam30a037 & 0xfe;
    }
  }
  if ((bRam301676 & 0x40) == 0) {
    bRam301686 = bRam301686 & 0x7f;
  }
  else {
    bRam301686 = bRam301686 | 0x80;
  }
  if ((((bRam30167a & 1) == 0) && ((bRam301671 & 2) != 0)) || ((bRam301678 & 8) != 0)) {
    PSW = PSW | 0x40;
  }
  else {
    PSW = PSW & 0xffbf;
  }
  if (bVar3) {
    uRam305332 = 0;
  }
  if ((((bRam301671 & 2) != 0) && ((bRam301670 & 1) != 0)) && (uRam305332 != 0xffff)) {
    uRam305332 = uRam305332 + 1;
  }
  if ((PSW & 0x40) == 0) {
    if ((uRam023f9c < uRam305332) && ((bRam301670 & 1) != 0)) {
      bRam301677 = bRam301677 | 8;
    }
  }
  else {
    bRam301677 = bRam301677 & 0xf7;
  }
  if (((bRam301677 & 8) == 0) || ((bRam301672 & 1) == 0)) {
    bRam301677 = bRam301677 & 0xef;
  }
  else {
    bRam301677 = bRam301677 | 0x10;
  }
  if (((bRam30167a & 2) != 0) != ((bRam301677 & 0x10) != 0)) {
    uRam305334 = 0;
  }
  if ((bRam30167a & 2) != 0) {
    uRam305334 = uRam305334 + 1;
  }
  uVar7 = uRam023fa2 + uRam305330;
  if (uRam023fa2 + uRam305330 < uRam023fa2 || uRam023fa2 + uRam305330 < uRam305330) {
    uVar7 = 0xffff;
  }
  if (uVar7 < uRam305334) {
    bRam301677 = bRam301677 | 0x80;
  }
  if ((((bRam30167a & 4) == 0) && ((bRam301672 & 4) != 0)) && ((bRam301677 & 0x80) != 0)) {
    bRam301677 = bRam301677 | 0x20;
  }
  uVar7 = uRam023fa2 + uRam30532e;
  if (uRam023fa2 + uRam30532e < uRam023fa2 || uRam023fa2 + uRam30532e < uRam30532e) {
    uVar7 = 0xffff;
  }
  if (uVar7 < uRam305334) {
    bRam301677 = bRam301677 | 0x40;
  }
  bVar3 = false;
  if ((bRam301677 & 0x40) != 0) {
    bVar3 = sRam305322 != 0;
    if (bVar3) {
      sRam305322 = sRam305322 + -1;
    }
    bVar3 = !bVar3;
    if (((bRam3015c8 & 0x40) == 0) && ((bRam3015c8 & 0x80) != 0)) {
      bVar3 = true;
    }
  }
  if ((((bRam301677 & 0x20) == 0) || ((bRam301677 & 0x80) == 0)) || (!bVar3)) {
    bRam301679 = bRam301679 & 0xfb;
  }
  else {
    bRam301679 = bRam301679 | 4;
  }
  if (((((bRam301671 & 0x10) == 0) || ((bRam301671 & 0x20) == 0)) || ((bRam30a037 & 2) != 0)) ||
     (((bRam301670 & 4) != 0 && ((bRam301672 & 4) == 0)))) {
    bRam301677 = bRam301677 & 0xfd;
  }
  else {
    bRam301677 = bRam301677 | 2;
  }
  if (((bRam301671 & 0x10) == 0) && ((bRam301670 & 4) != 0)) {
    bRam301674 = bRam301674 | 0x20;
  }
  else {
    bRam301674 = bRam301674 & 0xdf;
  }
  if (((bRam301671 & 0x20) == 0) && ((bRam301670 & 4) != 0)) {
    if ((bRam01a055 & 8) == 0) {
      if ((bRam3031aa & 2) == 0) {
        bVar3 = true;
      }
      else {
        bVar3 = false;
      }
    }
    else {
      bVar3 = false;
    }
    if (!bVar3) {
      if ((uRam302634 & 8) == 0) {
        if ((bRam301672 & 4) == 0) {
          bVar3 = false;
        }
        else {
          bVar3 = true;
        }
      }
      else {
        bVar3 = true;
      }
      if (!bVar3) goto LAB_09c660;
    }
    bRam301676 = bRam301676 | 0x10;
  }
  else {
LAB_09c660:
    bRam301676 = bRam301676 & 0xef;
  }
  if ((bRam301670 & 2) == 0) {
    bRam301674 = bRam301674 & 0x7f;
  }
  else {
    bRam301674 = bRam301674 | 0x80;
  }
  if ((bRam301674 & 0x20) != 0) {
    bRam301674 = bRam301674 | 0x10;
  }
  if (((bRam301674 & 0x10) != 0) && (sRam302b24 != 0)) {
    sRam302b24 = sRam302b24 + -1;
  }
  if ((((bRam301674 & 0x20) == 0) ||
      ((sRam302b24 != 0 && (((bRam3015c8 & 0x40) != 0 || ((bRam3015c8 & 0x80) == 0)))))) &&
     (((uRam303b4c & 1) == 0 || ((bRam30168a & 0x40) == 0)))) {
    bRam301671 = bRam301671 & 0xfe;
  }
  else {
    bRam301671 = bRam301671 | 1;
  }
  if ((bRam301677 & 2) == 0) {
    if ((bRam301671 & 1) == 0) {
      if ((bRam301676 & 0x10) == 0) {
        if ((bRam301674 & 0x80) != 0) {
          uStack_e = (uVar5 >> 8 & 0x90 | 100) << 8 | 2;
        }
      }
      else {
        uStack_e = (uVar5 >> 8 & 0x90 | 0x62) << 8 | 2;
      }
    }
    else {
      uStack_e = (uVar5 >> 8 & 0x90 | 0x61) << 8 | 2;
    }
  }
  else {
    uStack_e = ((uVar5 & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
  }
  if (((((bRam301671 & 1) == 0) && ((bRam301676 & 0x10) == 0)) && ((bRam301679 & 4) == 0)) &&
     ((bRam301674 & 0x80) == 0)) {
    bRam301678 = bRam301678 & 0xf7;
  }
  else {
    bRam301678 = bRam301678 | 8;
  }
  if (((bRam301678 & 8) != 0) && (bRam014461 != 0xff)) {
    *(byte *)((uint3)(bRam014461 + 0x9db) + 0x10000) =
         *(byte *)((uint3)(bRam014461 + 0x9db) + 0x10000) | 1;
    DPP0 = 4;
    __nop();
  }
  if ((bRam30146e & 0x10) != 0) {
    bRam304d9c = bRam304d9c | 8;
  }
LAB_09c838:
  func_0x0b31ac(99,uStack_e);
  if ((bRam301679 & 1) == 0) {
    bRam30167d = bRam30167d & 0xef;
  }
  else {
    bRam30167d = bRam30167d | 0x10;
  }
  if ((bRam301677 & 0x10) == 0) {
    bRam30167a = bRam30167a & 0xfd;
  }
  else {
    bRam30167a = bRam30167a | 2;
  }
  if (((flags_torque_revlimit & 0x80) == 0) && ((bRam301670 & 0x20) == 0)) {
    bRam301686 = bRam301686 & 0xfe;
  }
  else {
    bRam301686 = bRam301686 | 1;
  }
  if ((bRam301671 & 2) == 0) {
    bRam30167a = bRam30167a & 0xfe;
  }
  else {
    bRam30167a = bRam30167a | 1;
  }
  if ((bRam301672 & 4) == 0) {
    bRam30167a = bRam30167a & 0xfb;
  }
  else {
    bRam30167a = bRam30167a | 4;
  }
  return;
}


// ================= lsu_nernst_temp_model @ 06aa66 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* lambda/O2 sensor (LSU) Nernst-cell internal-resistance -> temperature signal model: 6x interp
   (sub_42EA8 32-bit mul helper) over characteristic 0x210A4 (dict 'Nernst cell Ri->temp'), reads
   LALIO 0x15E52 + MSDPWMAP 0x210AC + Bosch-II map 0x212C6 -> model words
   word_3050AE/B0/B6/B8/BA/BC/BE/CA/CC + word_305092; state-machine bytes byte_30472A-31; sets
   status bit word_FD2E.4 (0x6B316); packs CAN frame 0x99 (sub_B31AC); no actuator/PWM write seen [C
   mechanism; exact sensor bank/role I] */

void lsu_nernst_temp_model(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  byte bVar7;
  bool bVar8;
  ushort uVar9;
  undefined2 uVar10;
  ushort uVar11;
  short sVar12;
  short sVar13;
  short sVar14;
  undefined4 uVar15;
  ushort uStack_a;
  
  uVar11 = uRam303bb8;
  uVar9 = uRam3027d2;
  uVar10 = uRam302688;
  sVar12 = sRam00f35e;
  sVar14 = sRam00f35c;
  uVar15 = CONCAT22(uRam3050c6,uRam3050aa);
  uStack_a = uRam303bb8;
  if ((flags_diag_enable_c & 4) == 0) {
    uStack_a = ((uRam303bb8 & 0xf000) >> 8 & 0x9f | 0x60) << 8 | 2;
    goto LAB_06c032;
  }
  if ((bRam301670 & 0x20) == 0) {
    bRam301483 = bRam301483 & 0xfd;
  }
  else {
    bRam301483 = bRam301483 | 2;
  }
  if ((bRam3018ce & 1) == 0) {
    bRam301483 = bRam301483 & 0xfb;
  }
  else {
    bRam301483 = bRam301483 | 4;
  }
  if ((bRam3018ce & 2) == 0) {
    bRam301483 = bRam301483 & 0x77;
  }
  else {
    bRam301483 = bRam301483 & 0x7f | 8;
  }
  if ((bRam301670 & 0x80) == 0) {
    bRam301483 = bRam301483 & 0xdf;
  }
  else {
    bRam301483 = bRam301483 | 0x20;
  }
  if ((uRam00fd56 & 0x400) == 0) {
    bRam301483 = bRam301483 & 0xef;
  }
  else {
    bRam301483 = bRam301483 | 0x10;
  }
  bRam30147e = bRam30147e & 0xef | 0x20;
  uVar1 = uRam303b5e & 1;
  uVar2 = uRam303b4c & 1;
  uVar4 = (uRam303b5e & 2) >> 1;
  uVar5 = (uRam303b4c & 2) >> 1;
  uVar3 = uRam303c14 & 1;
  uVar6 = (uRam303c14 & 2) >> 1;
  if (((uRam00fd2c & 0x400) == 0) || ((bRam301483 & 0x10) == 0)) {
    bRam301478 = bRam301478 & 0xfb;
  }
  else {
    bRam301478 = bRam301478 | 4;
  }
  if ((uRam0210ba < uRam302736) && (uRam302736 < uRam0210bc)) {
    bRam301477 = bRam301477 | 0x20;
  }
  else {
    bRam301477 = bRam301477 & 0xdf;
  }
  if (uRam302736 < uRam0210b4) {
    bRam301478 = bRam301478 & 0xfd;
  }
  else {
    bRam301478 = bRam301478 | 2;
  }
  uRam3050ae = me7_pt1_integrator(uRam015e52,uRam302736,uRam3050ae._2_2_,(undefined2)uRam3050ae);
  if (uRam0210b2 < (ushort)((uint)uRam3050ae >> 0x10)) {
    bRam301478 = bRam301478 & 0xfe;
  }
  else {
    bRam301478 = bRam301478 | 1;
  }
  if (uRam0210c8 < uVar9) {
    bRam301477 = bRam301477 & 0xfb;
  }
  else {
    bRam301477 = bRam301477 | 4;
  }
  if (uVar9 < uRam0210c6) {
    bRam301477 = bRam301477 & 0xfd;
  }
  else {
    bRam301477 = bRam301477 | 2;
  }
  if (sVar14 == sRam0210c0 ||
      sVar14 - sRam0210c0 < 0 !=
      (sVar14 < 0 != sRam0210c0 < 0 && sVar14 - sRam0210c0 < 0 != sVar14 < 0)) {
    bRam30147a = bRam30147a & 0xfd;
  }
  else {
    bRam30147a = bRam30147a | 2;
  }
  if (sVar14 - sRam0210be < 0 ==
      (sVar14 < 0 != sRam0210be < 0 && sVar14 - sRam0210be < 0 != sVar14 < 0)) {
    bRam30147a = bRam30147a & 0xfe;
  }
  else {
    bRam30147a = bRam30147a | 1;
  }
  if (((bRam30147a & 1) == 0) && ((bRam30147a & 2) == 0)) {
    bRam301477 = bRam301477 & 0xfe;
  }
  else {
    bRam301477 = bRam301477 | 1;
  }
  if (((((_flags_start_phase & 0x8000) == 0) || ((bRam301481 & 1) != 0)) || ((bRam301477 & 1) == 0))
     || (sRam3050bc != 0)) {
    if (((bRam301483 & 4) != 0) && (uVar5 != 0)) {
      if (sRam3050bc == 0) {
        bRam301481 = bRam301481 & 0xfd;
      }
      else {
        sRam3050bc = sRam3050bc + -1;
      }
    }
  }
  else {
    sRam3050bc = sRam0210c2;
    bRam301481 = bRam301481 | 2;
  }
  if ((bRam301481 & 2) == 0) {
    bRam30147a = bRam30147a | 8;
  }
  else {
    bRam30147a = bRam30147a & 0xf7;
  }
  if ((((((uRam303b18 & 1) == 0) && ((uRam303ada & 1) == 0)) &&
       (((uRam303b30 & 1) == 0 &&
        ((((_o2_diag_status_word & 1) == 0 && ((uRam303b74 & 1) == 0)) && ((uRam303b64 & 1) == 0))))
       )) && (((uRam303b68 & 1) == 0 && ((uRam303b6c & 1) == 0)))) &&
     (((uRam303b26 & 1) == 0 && ((uRam303b2a & 1) == 0)))) {
    bRam301484 = bRam301484 & 0xef;
  }
  else {
    bRam301484 = bRam301484 | 0x10;
  }
  if ((bRam30a109 & 0x40) == 0) {
    bRam30147b = bRam30147b & 0xf7;
  }
  else {
    bRam30147b = bRam30147b | 8;
  }
  if (((bRam3031aa & 1) == 0) && ((bRam3031aa & 2) == 0)) {
    bRam301484 = bRam301484 | 0x20;
  }
  else {
    bRam301484 = bRam301484 & 0xdf;
  }
  if (((((((bRam301477 & 1) == 0) || ((bRam30147a & 8) == 0)) ||
        ((_flags_start_phase & 0x8000) == 0)) || ((bRam30147b & 8) == 0)) &&
      (((bRam301477 & 1) == 0 || ((uRam302634 & 0x800) == 0)))) || ((bRam301484 & 0x20) == 0)) {
    sRam3050b6 = sRam0210c4;
    bRam301479 = bRam301479 & 0xdf;
  }
  else if (sRam3050b6 == 0) {
    bRam301479 = bRam301479 | 0x20;
  }
  else {
    sRam3050b6 = sRam3050b6 + -1;
  }
  if ((((bRam301483 & 0x20) == 0) && ((bRam018a64 & 2) == 0)) ||
     (((bRam301479 & 0x20) == 0 || ((bRam30147a & 2) == 0)))) {
    bRam301479 = bRam301479 & 0x7f;
  }
  else {
    bRam301479 = bRam301479 | 0x80;
  }
  if (((((bRam301483 & 0x20) == 0) && ((bRam018a64 & 2) == 0)) || ((bRam301479 & 0x20) == 0)) ||
     ((bRam30147a & 1) == 0)) {
    bRam301479 = bRam301479 & 0xbf;
  }
  else {
    bRam301479 = bRam301479 | 0x40;
  }
  if (((bRam30147e & 0x20) == 0) || (uVar4 == 0)) {
    bRam301481 = bRam301481 & 0xfb;
  }
  else {
    bRam301481 = bRam301481 | 4;
  }
  if ((((bRam301483 & 8) == 0) || ((bRam301481 & 4) == 0)) || (uVar5 == 0)) {
    bRam301478 = bRam301478 & 0xdf;
  }
  else {
    bRam301478 = bRam301478 | 0x20;
  }
  if (((sVar12 < 1) || (sVar14 < 1)) && ((-1 < sVar12 || (-1 < sVar14)))) {
    bRam301481 = bRam301481 & 0xef;
  }
  else {
    bRam301481 = bRam301481 | 0x10;
  }
  sVar12 = func_0x042fe2(sVar12);
  if (((bRam301483 & 8) == 0) || ((bRam301481 & 4) == 0)) {
LAB_06af4c:
    bRam301481 = bRam301481 & 0xf7;
  }
  else {
    if (((bRam301481 & 0x10) == 0) ||
       (sVar12 == sRam0210a6 ||
        sVar12 - sRam0210a6 < 0 !=
        (sVar12 < 0 != sRam0210a6 < 0 && sVar12 - sRam0210a6 < 0 != sVar12 < 0))) {
      sVar13 = func_0x042fe2(sVar14);
      sVar14 = sVar12 - sRam0210a6;
      if (sVar12 < 0 != sRam0210a6 < 0 && sVar12 - sRam0210a6 < 0 != sVar12 < 0) {
        sVar14 = -0x8000;
      }
      if (sVar13 - sVar14 < 0 == (sVar13 < 0 != sVar14 < 0 && sVar13 - sVar14 < 0 != sVar13 < 0))
      goto LAB_06af4c;
    }
    bRam301481 = bRam301481 | 8;
  }
  if ((((uRam00fd36 & 8) == 0) && (((bRam301481 & 8) == 0 || (uVar5 == 0)))) ||
     ((bRam301478 & 4) == 0)) {
    bRam30147b = bRam30147b & 0xfb;
  }
  else {
    bRam30147b = bRam30147b | 4;
  }
  if ((((bRam30147b & 4) == 0) || ((bRam301478 & 2) == 0)) || ((bRam301477 & 2) == 0)) {
    bRam301477 = bRam301477 & 0xbf;
  }
  else {
    bRam301477 = bRam301477 | 0x40;
  }
  if ((((bRam301478 & 4) == 0) || ((bRam301481 & 8) == 0)) ||
     (((uRam00fd36 & 0x10) != 0 || ((bRam018a64 & 1) == 0)))) {
    bRam30147b = bRam30147b & 0xfe;
  }
  else {
    bRam30147b = bRam30147b | 1;
  }
  if ((((bRam301478 & 4) == 0) || ((uRam00fd36 & 0x10) != 0)) ||
     (((bRam301481 & 4) == 0 || (((DAT_00fd34 & 0x100) == 0 || (uRam30294c <= uRam0210b8)))))) {
    bRam30147b = bRam30147b & 0xfd;
  }
  else {
    bRam30147b = bRam30147b | 2;
  }
  if ((((bRam301477 & 2) == 0) || ((bRam30147b & 1) == 0)) &&
     (((bRam301477 & 2) == 0 || ((bRam30147b & 2) == 0)))) {
    cRam304730 = cRam018a68;
    bRam301477 = bRam301477 & 0x7f;
  }
  else if (cRam304730 == '\0') {
    bRam301477 = bRam301477 | 0x80;
  }
  else {
    cRam304730 = cRam304730 + -1;
  }
  if (((((bRam301478 & 4) == 0) || ((DAT_00fd34 & 0x100) == 0)) || ((bRam301481 & 4) == 0)) ||
     (((uRam00fd36 & 8) != 0 || (uRam0210b6 <= uRam30294c)))) {
    bRam30147a = bRam30147a & 0xdf;
  }
  else {
    bRam30147a = bRam30147a | 0x20;
  }
  if ((((bRam018a64 & 1) == 0) || ((bRam301478 & 4) == 0)) ||
     (((bRam301481 & 8) == 0 || ((uRam00fd36 & 8) != 0)))) {
    bRam30147a = bRam30147a & 0xbf;
  }
  else {
    bRam30147a = bRam30147a | 0x40;
  }
  if ((((bRam30147a & 0x20) == 0) || ((bRam301477 & 4) == 0)) &&
     (((bRam30147a & 0x40) == 0 || ((bRam301477 & 4) == 0)))) {
    cRam30472f = cRam018a68;
    bRam301477 = bRam301477 & 0xef;
  }
  else if (cRam30472f == '\0') {
    bRam301477 = bRam301477 | 0x10;
  }
  else {
    cRam30472f = cRam30472f + -1;
  }
  if (((bRam301478 & 4) == 0) ||
     ((((bRam301481 & 8) == 0 || (uVar5 == 0)) && ((uRam00fd36 & 0x10) == 0)))) {
    bRam30147a = bRam30147a & 0x7f;
  }
  else {
    bRam30147a = bRam30147a | 0x80;
  }
  if ((((bRam30147a & 0x80) == 0) || ((bRam301477 & 4) == 0)) || ((bRam301478 & 1) == 0)) {
    bRam301477 = bRam301477 & 0xf7;
  }
  else {
    bRam301477 = bRam301477 | 8;
  }
  if ((bRam301670 & 1) == 0) {
    bRam301484 = bRam301484 & 0x7f;
  }
  else {
    bRam301484 = bRam301484 | 0x80;
  }
  if ((bRam301672 & 1) == 0) {
    bRam30147f = bRam30147f & 0xf7;
  }
  else {
    bRam30147f = bRam30147f | 8;
  }
  if ((bRam301672 & 4) == 0) {
    bRam30147f = bRam30147f & 0xef;
  }
  else {
    bRam30147f = bRam30147f | 0x10;
  }
  uRam3050ba = uRam305330;
  uRam3050b8 = uRam30532e;
  uRam3050be = uRam023fa2;
  uRam3050cc = uRam305330 + uRam023fa2;
  if (uRam305330 + uRam023fa2 < uRam305330 || uRam305330 + uRam023fa2 < uRam023fa2) {
    uRam3050cc = 0xffff;
  }
  uRam3050ca = uRam30532e + uRam023fa2;
  if (uRam30532e + uRam023fa2 < uRam30532e || uRam30532e + uRam023fa2 < uRam023fa2) {
    uRam3050ca = 0xffff;
  }
  if ((bRam305483 & 4) != 0) {
    sVar14 = sRam0210a8 - sRam30a172;
    if (sRam0210a8 < 0 != sRam30a172 < 0 && sRam0210a8 - sRam30a172 < 0 != sRam0210a8 < 0) {
      sVar14 = -0x8000;
    }
    uRam305092 = func_0x0430da(sVar14,uRam305092._2_2_,(undefined2)uRam305092,0,0,uRam0212c6,0);
    sRam30a172 = (short)((uint)uRam305092 >> 0x10);
  }
  if ((((bRam301484 & 0x20) == 0) ||
      (sRam30a172 - sRam0210a4 < 0 !=
       (sRam30a172 < 0 != sRam0210a4 < 0 && sRam30a172 - sRam0210a4 < 0 != sRam30a172 < 0))) ||
     (uVar5 == 0)) {
    sRam3050b2 = sRam0210c4;
    bRam301480 = bRam301480 & 0xfe;
  }
  else if (sRam3050b2 == 0) {
    bRam301480 = bRam301480 | 1;
  }
  else {
    sRam3050b2 = sRam3050b2 + -1;
  }
  if (((bRam301480 & 1) != 0) &&
     ((((bRam018a64 & 2) != 0 || ((bRam018a64 & 0x80) != 0)) ||
      (((bRam018a64 & 0x80) == 0 && ((bRam301483 & 0x20) != 0)))))) {
    uRam00fd2e = uRam00fd2e | 0x10;
  }
  if (((uRam00fd2e & 0x10) != 0) && ((bRam301484 & 0x40) == 0)) {
    uRam305092 = 0;
    sRam30a172 = 0;
  }
  if ((uRam00fd2e & 0x10) == 0) {
    bRam301484 = bRam301484 & 0xbf;
  }
  else {
    bRam301484 = bRam301484 | 0x40;
  }
  if ((bRam30147e & 0x40) == 0) {
    bRam30147e = bRam30147e & 0x7f;
  }
  else {
    bRam30147e = bRam30147e | 0x80;
  }
  if ((((uVar5 == 0) || ((bRam301483 & 8) == 0)) || ((bRam30147e & 0x20) == 0)) ||
     (((bRam301478 & 4) == 0 || (uVar4 == 0)))) {
    bRam30147f = bRam30147f & 0xfd;
  }
  else {
    bRam30147f = bRam30147f | 2;
  }
  if (((bRam30147f & 2) == 0) || ((bRam30147b & 0x40) != 0)) {
    if (bRam30472a < bRam018a69) {
      bRam30472a = bRam30472a + 1;
    }
    else {
      bRam30147e = bRam30147e & 0xbf;
    }
  }
  else {
    bRam30147e = bRam30147e | 0x40;
    bRam30472a = 0;
  }
  if (((((((bRam30147b & 0x20) == 0) &&
         ((((bRam30147e & 0x80) != 0 || ((bRam30147e & 0x40) == 0)) || ((bRam30147f & 1) == 0)))) &&
        (((uVar2 == 0 && (uVar1 == 0)) && ((bRam301483 & 0x80) == 0)))) &&
       (((uVar3 == 0 || (uVar6 == 0)) || ((bRam30147b & 0x40) != 0)))) &&
      ((((bRam301497 & 1) == 0 && (((bRam301477 & 8) != 0 || ((bRam30147d & 4) == 0)))) &&
       (((bRam301477 & 0x40) != 0 || ((bRam30147d & 0x10) == 0)))))) &&
     (((bRam018a64 & 0x20) == 0 ||
      ((((bRam301477 & 0x80) != 0 || ((bRam30147d & 0x20) == 0)) &&
       (((bRam301477 & 0x10) != 0 || ((bRam30147d & 8) == 0)))))))) {
    if ((bRam30147f & 2) != 0) {
      uRam305096 = func_0x042ea8(uVar10,uRam305096._2_2_,(undefined2)uRam305096);
      uRam3050c0 = (ushort)((uint)uRam305096 >> 0x10);
    }
  }
  else {
    uRam305096 = 0;
    uRam3050c0 = 0;
  }
  if (((bRam30147f & 2) == 0) && ((bRam301483 & 2) == 0)) {
    bRam30147f = bRam30147f | 1;
  }
  else {
    bRam30147f = bRam30147f & 0xfe;
  }
  if (uRam0210b0 < uRam3050c0) {
    bRam30147b = bRam30147b | 0x40;
  }
  else {
    bRam30147b = bRam30147b & 0xbf;
  }
  if ((((bRam30147b & 0x40) != 0) && (uVar6 != 0)) &&
     (((bRam018a64 & 0x80) != 0 || (((bRam018a64 & 0x80) == 0 && ((bRam301483 & 0x20) != 0)))))) {
    bRam30147b = bRam30147b | 0x20;
  }
  if ((bRam301477 & 8) == 0) {
    bRam30147d = bRam30147d & 0xfb;
  }
  else {
    bRam30147d = bRam30147d | 4;
  }
  if ((bRam301477 & 0x10) == 0) {
    bRam30147d = bRam30147d & 0xf7;
  }
  else {
    bRam30147d = bRam30147d | 8;
  }
  if ((bRam301477 & 0x40) == 0) {
    bRam30147d = bRam30147d & 0xef;
  }
  else {
    bRam30147d = bRam30147d | 0x10;
  }
  if ((bRam301477 & 0x80) == 0) {
    bRam30147d = bRam30147d & 0xdf;
  }
  else {
    bRam30147d = bRam30147d | 0x20;
  }
  if (((((uRam00fd2e & 0x10) == 0) || ((bRam301484 & 0x80) == 0)) || ((bRam30147f & 8) == 0)) ||
     ((bRam30147b & 0x20) == 0)) {
    bRam30147f = bRam30147f & 0xbf;
  }
  else {
    bRam30147f = bRam30147f | 0x40;
  }
  if (((bRam30147f & 0x40) != 0) != ((bRam30147f & 0x80) != 0)) {
    uRam3050ce = 0;
  }
  if ((bRam30147f & 0x80) != 0) {
    uRam3050ce = uRam3050ce + 1;
  }
  if (uRam3050cc < uRam3050ce) {
    bRam30147c = bRam30147c | 2;
  }
  if (uRam3050ca < uRam3050ce) {
    bRam30147c = bRam30147c | 1;
  }
  if ((bRam30147c & 1) == 0) {
    sRam3050b4 = sRam3050c8;
    bRam30147f = bRam30147f & 0xdf;
  }
  else if (sRam3050b4 == 0) {
    bRam30147f = bRam30147f | 0x20;
  }
  else {
    sRam3050b4 = sRam3050b4 + -1;
  }
  if ((((bRam30147c & 2) != 0) && ((bRam30147f & 0x10) != 0)) && ((bRam30147d & 1) == 0)) {
    bRam30147c = bRam30147c | 4;
  }
  bVar8 = false;
  if (((bRam30147c & 4) != 0) && ((bRam30147c & 2) != 0)) {
    bVar8 = true;
  }
  if (((bRam3015c8 & 0x40) == 0) && ((bRam3015c8 & 0x80) != 0)) {
    if ((bVar8) && ((bRam30147c & 1) != 0)) goto LAB_06b6c6;
LAB_06b6d0:
    bRam30147b = bRam30147b & 0x7f;
  }
  else {
    if ((!bVar8) || ((bRam30147f & 0x20) == 0)) goto LAB_06b6d0;
LAB_06b6c6:
    bRam30147b = bRam30147b | 0x80;
  }
  if ((bRam30147f & 0x40) == 0) {
    bRam30147f = bRam30147f & 0x7f;
  }
  else {
    bRam30147f = bRam30147f | 0x80;
  }
  if ((bRam30147f & 0x10) == 0) {
    bRam30147d = bRam30147d & 0xfe;
  }
  else {
    bRam30147d = bRam30147d | 1;
  }
  if ((((bRam018a64 & 2) == 0) && ((bRam018a64 & 0x80) != 0)) && ((bRam018a64 & 0x10) == 0)) {
    if ((bRam30147b & 0x80) != 0) {
LAB_06b754:
      bRam30147c = bRam30147c | 8;
    }
  }
  else if (((bRam018a64 & 0x10) != 0) || (((bRam018a64 & 0x10) == 0 && ((uRam00fd2e & 0x10) != 0))))
  goto LAB_06b754;
  if (((bRam018a64 & 0x80) == 0) || ((bRam018a64 & 4) != 0)) {
    if ((bRam018a64 & 4) != 0) goto LAB_06b79c;
    if ((bRam018a64 & 4) == 0) {
      bVar7 = bRam30147b & 0x20;
      goto joined_r0x06b798;
    }
  }
  else {
    bVar7 = bRam30147b & 0x80;
joined_r0x06b798:
    if (bVar7 != 0) {
LAB_06b79c:
      bRam30147b = bRam30147b | 0x10;
    }
  }
  if ((bRam301481 & 0x20) == 0) {
    bRam301481 = bRam301481 & 0xbf;
  }
  else {
    bRam301481 = bRam301481 | 0x40;
  }
  if ((uVar3 == 0) || (uVar6 == 0)) {
    bRam30147f = bRam30147f & 0xfb;
  }
  else {
    bRam30147f = bRam30147f | 4;
  }
  if (((bRam301477 & 0x40) == 0) || (uRam0210ae < uRam3050c4)) {
    if (bRam30472d < bRam018a69) {
      bRam30472d = bRam30472d + 1;
    }
    else {
      bRam301481 = bRam301481 & 0xdf;
    }
  }
  else {
    bRam301481 = bRam301481 | 0x20;
    bRam30472d = 0;
  }
  if (((((bRam301481 & 0x40) == 0) && ((bRam301481 & 0x20) != 0)) ||
      ((uRam3050c4 <= uRam0210ae && ((bRam30147f & 4) != 0)))) || ((bRam301497 & 1) != 0)) {
    uRam3050a2 = 0;
    uRam3050c4 = 0;
  }
  else if ((bRam301477 & 0x40) != 0) {
    uRam3050a2 = func_0x042ea8(0x199a,uVar10,uRam3050a2._2_2_,(undefined2)uRam3050a2);
    uRam3050c4 = (ushort)((uint)uRam3050a2 >> 0x10);
  }
  if ((bRam301482 & 2) == 0) {
    bRam301482 = bRam301482 & 0xfb;
  }
  else {
    bRam301482 = bRam301482 | 4;
  }
  if (((bRam3031aa & 2) == 0) && ((bRam301477 & 0x80) != 0)) {
    bRam301482 = bRam301482 | 2;
    bRam30472e = 0;
  }
  else if (bRam30472e < bRam018a69) {
    bRam30472e = bRam30472e + 1;
  }
  else {
    bRam301482 = bRam301482 & 0xfd;
  }
  if (((((((bRam301482 & 2) == 0) || ((bRam301482 & 4) != 0)) || ((bRam301482 & 1) == 0)) &&
       (((bRam301497 & 1) == 0 && ((bRam301481 & 0x80) == 0)))) && (uVar2 == 0)) &&
     ((uVar1 == 0 && (((bRam3031aa & 2) != 0 || ((bRam30147f & 4) == 0)))))) {
    if ((bRam301477 & 0x80) != 0) {
      uRam3050a6 = func_0x042ea8(0x199a,uVar10,uRam3050a6._2_2_,(undefined2)uRam3050a6);
      uRam30a176 = (ushort)((uint)uRam3050a6 >> 0x10);
    }
  }
  else {
    uRam3050a6 = 0;
    uRam30a176 = 0;
  }
  if (((bRam301477 & 0x80) == 0) && ((bRam301483 & 2) == 0)) {
    bRam301482 = bRam301482 | 1;
  }
  else {
    bRam301482 = bRam301482 & 0xfe;
  }
  if (uRam0210b0 < uRam30a176) {
    bRam3031aa = bRam3031aa | 2;
  }
  else {
    bRam3031aa = bRam3031aa & 0xfd;
  }
  if (((bRam3031aa & 2) != 0) && ((bRam301483 & 0x20) != 0)) {
    bRam301481 = bRam301481 | 0x80;
  }
  if (((bRam301481 & 0x80) == 0) && ((uRam3050c4 <= uRam0210ae || (uVar6 == 0)))) {
    bRam301479 = bRam301479 & 0xef;
  }
  else {
    bRam301479 = bRam301479 | 0x10;
  }
  if ((bRam301482 & 8) == 0) {
    bRam301482 = bRam301482 & 0xef;
  }
  else {
    bRam301482 = bRam301482 | 0x10;
  }
  if (((bRam301477 & 8) == 0) || (uRam0210ae < uRam3050c2)) {
    if (bRam30472b < bRam018a69) {
      bRam30472b = bRam30472b + 1;
    }
    else {
      bRam301482 = bRam301482 & 0xf7;
    }
  }
  else {
    bRam301482 = bRam301482 | 8;
    bRam30472b = 0;
  }
  if (((((bRam301482 & 0x10) == 0) && ((bRam301482 & 8) != 0)) ||
      ((uRam3050c2 <= uRam0210ae && ((bRam30147f & 4) != 0)))) || ((bRam301497 & 1) != 0)) {
    uRam30509a = 0;
    uRam3050c2 = 0;
  }
  else if ((bRam301477 & 8) != 0) {
    uRam30509a = func_0x042ea8(0x199a,uVar10,uRam30509a._2_2_,(undefined2)uRam30509a);
    uRam3050c2 = (ushort)((uint)uRam30509a >> 0x10);
  }
  if ((bRam301482 & 0x20) == 0) {
    bRam301482 = bRam301482 & 0xbf;
  }
  else {
    bRam301482 = bRam301482 | 0x40;
  }
  if (((bRam301477 & 0x10) == 0) || ((bRam3031aa & 1) != 0)) {
    if (bRam30472c < bRam018a69) {
      bRam30472c = bRam30472c + 1;
    }
    else {
      bRam301482 = bRam301482 & 0xdf;
    }
  }
  else {
    bRam301482 = bRam301482 | 0x20;
    bRam30472c = 0;
  }
  if (((((bRam301483 & 1) == 0) &&
       ((((bRam301482 & 0x40) != 0 || ((bRam301482 & 0x20) == 0)) || ((bRam301482 & 0x80) == 0))))
      && ((((bRam301483 & 0x80) == 0 && (uVar1 == 0)) && (uVar2 == 0)))) &&
     (((bRam301497 & 1) == 0 && (((bRam3031aa & 1) != 0 || ((bRam30147f & 4) == 0)))))) {
    if ((bRam301477 & 0x10) != 0) {
      uRam30509e = func_0x042ea8(0x199a,uVar10,uRam30509e._2_2_,(undefined2)uRam30509e);
      uRam30a174 = (ushort)((uint)uRam30509e >> 0x10);
    }
  }
  else {
    uRam30509e = 0;
    uRam30a174 = 0;
  }
  if (((bRam301477 & 0x10) == 0) && ((bRam301483 & 2) == 0)) {
    bRam301482 = bRam301482 | 0x80;
  }
  else {
    bRam301482 = bRam301482 & 0x7f;
  }
  if (uRam0210b0 < uRam30a174) {
    bRam3031aa = bRam3031aa | 1;
  }
  else {
    bRam3031aa = bRam3031aa & 0xfe;
  }
  if (((bRam3031aa & 1) != 0) && ((bRam301483 & 0x20) != 0)) {
    bRam301483 = bRam301483 | 1;
  }
  if (((bRam301483 & 1) == 0) && (uRam3050c2 <= uRam0210ae)) {
    bRam301479 = bRam301479 & 0xf7;
  }
  else {
    bRam301479 = bRam301479 | 8;
  }
  if ((((((bRam30147b & 0x10) != 0) && ((bRam30147c & 8) != 0)) || ((bRam301479 & 0x40) != 0)) ||
      ((((bRam301479 & 0x80) != 0 || ((bRam301479 & 8) != 0)) || ((bRam301479 & 0x10) != 0)))) &&
     (bRam01447d != 0xff)) {
    *(byte *)((uint3)(bRam01447d + 0x9db) + 0x304000) =
         *(byte *)((uint3)(bRam01447d + 0x9db) + 0x304000) | 1;
  }
  uVar15 = CONCAT22(uRam3050c6,uRam3050aa);
  if ((((bRam3031aa & 2) == 0) && ((bRam3031aa & 1) == 0)) && ((bRam301490 & 1) == 0)) {
    bRam301478 = bRam301478 & 0xf7;
  }
  else {
    bRam301478 = bRam301478 | 8;
  }
  if ((bRam301478 & 0x20) == 0) {
    if (cRam304731 != '\0') {
      cRam304731 = cRam304731 + -1;
      goto LAB_06bd04;
    }
    bRam301483 = bRam301483 & 0xbf;
  }
  else {
    cRam304731 = cRam018a67;
LAB_06bd04:
    bRam301483 = bRam301483 | 0x40;
  }
  if (((uRam302634 & 1) == 0) || ((uRam302634 & 0x800) == 0)) {
    bRam30a0f0 = bRam30a0f0 & 0x3d;
  }
  else {
    bRam30a0f0 = bRam30a0f0 | 0x80;
  }
  if (((uRam302634 & 0x800) != 0) || ((uRam302634 & 1) == 0)) {
    if (((uRam302634 & 1) == 0) || (((uRam302634 & 0x800) != 0 && ((bRam30a0f0 & 0x40) != 0)))) {
      bRam301484 = bRam301484 | 4;
    }
    else {
      bRam301484 = bRam301484 & 0xfb;
    }
    if ((uRam303bb8 & 1) == 0) {
      if ((bRam301478 & 4) == 0) goto LAB_06bdc0;
LAB_06bdb8:
      bRam301484 = bRam301484 | 2;
    }
    else {
      if (((((bRam301483 & 0x40) != 0) && ((bRam301477 & 0x40) == 0)) && ((bRam301477 & 0x80) == 0))
         && (((bRam301477 & 8) == 0 && ((bRam301477 & 0x10) == 0)))) goto LAB_06bdb8;
LAB_06bdc0:
      bRam301484 = bRam301484 & 0xfd;
    }
    if (((((((bRam301477 & 1) == 0) && ((bRam301479 & 8) == 0)) &&
          (((bRam301479 & 0x10) == 0 &&
           ((((bRam3031aa & 2) == 0 && ((bRam3031aa & 1) == 0)) && ((bRam301484 & 2) != 0)))))) &&
         (((bRam301484 & 4) != 0 && (uVar3 == 0)))) && (uVar6 != 0)) &&
       (((bRam301497 & 1) == 0 && ((bRam30147e & 0x20) != 0)))) {
      bRam301478 = bRam301478 | 0x10;
    }
    else {
      bRam301478 = bRam301478 & 0xef;
    }
    if ((bRam301478 & 0x10) == 0) {
      uVar15 = 0;
    }
    else {
      uVar15 = func_0x042ea8(0x199a,uVar10,uRam3050ac,uRam3050aa);
    }
    uRam3050c6 = (ushort)((uint)uVar15 >> 0x10);
    if ((((bRam30547a & 8) == 0) && ((uRam302634 & 0x800) == 0)) && ((bRam018a64 & 0x40) == 0)) {
LAB_06bec0:
      bRam301479 = bRam301479 & 0xfd;
    }
    else {
      uVar9 = uRam0210ac;
      if ((uRam302634 & 0x800) == 0) {
        uVar9 = uRam0210aa;
      }
      if (uRam3050c6 <= uVar9) goto LAB_06bec0;
      bRam301479 = bRam301479 | 2;
    }
    if ((bRam30147e & 1) == 0) {
      bRam30147e = bRam30147e & 0xfb;
    }
    else {
      bRam30147e = bRam30147e | 4;
    }
    if ((((bRam3031aa & 1) == 0) && ((bRam3031aa & 2) == 0)) && ((bRam301479 & 0x20) == 0)) {
      bRam30147e = bRam30147e & 0xfe;
    }
    else {
      bRam30147e = bRam30147e | 1;
    }
    if (((bRam30147e & 4) == 0) && ((bRam30147e & 1) != 0)) {
      uStack_a = uVar11 & 0xff00 | uVar11 & 0xff00 | 4;
    }
    if ((bRam30147e & 2) == 0) {
      bRam30147e = bRam30147e & 0xf7;
    }
    else {
      bRam30147e = bRam30147e | 8;
    }
    if (((bRam30147e & 1) == 0) || ((uVar2 == 0 && (uVar1 == 0)))) {
      bRam30147e = bRam30147e & 0xfd;
    }
    else {
      bRam30147e = bRam30147e | 2;
    }
    if (((bRam30147e & 8) == 0) && ((bRam30147e & 2) != 0)) {
      uStack_a = uStack_a & 0xfffb;
    }
    if ((bRam301479 & 0x80) == 0) {
      if ((bRam301479 & 0x40) != 0) {
        uStack_a = (uStack_a >> 8 & 0xfff0 | 2) << 8;
        goto LAB_06bfe4;
      }
      if ((bRam301479 & 0x10) != 0) {
        uStack_a = (uStack_a >> 8 & 0xfff0 | 8) << 8;
        goto LAB_06bfe4;
      }
      if ((bRam301479 & 8) != 0) {
        uStack_a = (uStack_a >> 8 & 0xfff0 | 4) << 8;
        goto LAB_06bfe4;
      }
      if ((bRam301479 & 2) != 0) {
        uStack_a = uStack_a & 0xf0fe;
        goto LAB_06bfe4;
      }
    }
    else {
      uStack_a = (uStack_a >> 8 & 0xfff0 | 1) << 8;
LAB_06bfe4:
      uStack_a = (uStack_a >> 8 & 0x9f | 0x60) << 8 | 2;
    }
    uRam3050ac = uRam3050c6;
    if (((bRam30146e & 0x10) != 0) || (((uRam303bb8 & 1) != 0 && ((uRam303bb8 & 2) != 0)))) {
      bRam304da3 = bRam304da3 | 2;
    }
  }
  if ((_flags_start_phase & 0x8000) == 0) {
    bRam301481 = bRam301481 & 0xfe;
  }
  else {
    bRam301481 = bRam301481 | 1;
  }
LAB_06c032:
  uRam3050c6 = (ushort)((uint)uVar15 >> 0x10);
  uRam3050aa = (undefined2)uVar15;
  func_0x0b31ac(0x99,uStack_a);
  return;
}


// ================= diag_boost_pressure_monitor @ 0d9ea0 =================

/* DIAGNOSTIC: boost-pressure (Ladedruck) diagnosis/monitor: reads LD* diag cals
   FTLDIA/FTLDIAP/LDEIAO/LDEIAP/LDEIAPS/LDEIAU/LDHIA/STLDIA1-4/TLDIAN/CWLDIMX/UMDYLDR
   (0x1BD1F-0x1BD7D) + LDAMN/LDDIAN/LDDIAP/LDMXNN/LDMXNP/LDRQ0S/TVLDMX (0x2C452-0x2C4DC) + 0x2C100
   adj KFLDIWL; uses debounce family sub_32E88 x4/sub_33006 x4/sub_330F2 x3 + lookup sub_419F4 ->
   fault/state bytes byte_304E17/19/1A + byte_300E46/48/4A/4E/50 (0xDA46A movb byte_300E46,rl6); no
   actuator/setpoint write [C] */

void diag_boost_pressure_monitor(void)

{
  bool bVar1;
  bool bVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  char cVar6;
  char cVar7;
  byte bVar8;
  ushort uVar9;
  ushort uVar10;
  short sVar11;
  short sVar12;
  short sVar13;
  undefined2 uVar14;
  short sVar15;
  short sStack_e;
  
  if ((DAT_301850 & 2) == 0) {
    cRam304e17 = '\0';
  }
  else {
    sVar13 = (uRam302c3c >> 8) - (uRam00f466 >> 7);
    if (sVar13 + 0x80 < 0 == (-1 < sVar13 && sVar13 + 0x80 < 0 != sVar13 < 0)) {
      if (sVar13 != 0x7f && sVar13 + -0x7f < 0 == (sVar13 < 0 && sVar13 + -0x7f < 0 != sVar13 < 0))
      {
        sVar13 = 0x7f;
      }
    }
    else {
      sVar13 = 0x80;
    }
    cRam304e17 = (char)sVar13;
  }
  cVar6 = func_0x033084(0x8e4c,(short)cRam304e17,1,(short)cRam01bd7d);
  if (cVar6 == '\0') {
    bRam30185f = bRam30185f & 0xfe;
  }
  else {
    bRam30185f = bRam30185f | 1;
  }
  if ((bRam30185f & 1) == 0) {
    uRam305768 = func_0x0420a8(0x48e,0xb,uRam3019b0);
  }
  else {
    uRam305768 = func_0x0421f4(0x312,0xb,0x2701,4,uRam3019b0,uRam30197a);
  }
  if ((bRam30185f & 1) == 0) {
    uRam305766 = 0;
  }
  else {
    uRam305766 = func_0x0421f4(0x392,0xb,0x2701,4,uRam3019b0,uRam30197a);
  }
  uVar10 = uRam02c48c;
  if ((bRam30585f & 1) != 0) {
    uVar10 = func_0x0421f4(0x292,0xb,0x2701,4,uRam3019b0,uRam30197a);
  }
  uRam30576a = uVar10 - uRam305766;
  if (uVar10 < uRam305766) {
    uRam30576a = 0;
  }
  uVar10 = uRam302e20;
  if (cRam01bd1f != '\0') {
    uVar10 = 0;
  }
  sRam305770 = uRam302c3c - uVar10;
  if (uRam302c3c < uVar10) {
    sRam305770 = 0;
  }
  uRam302e18 = func_0x041844(0x4b4,0xb,sRam305770,uRam302e18);
  uVar9 = func_0x0421f4(0,0xb,0x4b4,0xb,uRam3019b2,uRam302e18);
  cVar6 = func_0x042596(uRam02c100,0x102,0xb,uRam02c101,0x10a,0xb,0x112,0xb,uRam304979,uRam304715);
  cVar7 = func_0x042082(0x3d67,6,uRam3019d8);
  uVar10 = func_0x04210c(0x3d22,6,0x27c3,4,uRam30199c,uRam3019b8);
  uVar10 = (uVar10 & 0xff) + (short)cVar7 + (short)cVar6;
  uVar3 = uVar10 * 0x80;
  uRam30575c = uVar9 + uVar3;
  uVar10 = (((short)uVar10 >> 0xf) << 7 | uVar10 >> 9) +
           (ushort)(uVar9 + uVar3 < uVar9 || uVar9 + uVar3 < uVar3);
  uVar3 = (ushort)(uRam30575c < 0x7fff);
  if ((uVar10 != uVar3 || uRam30575c != 0x7fff) &&
      (short)(uVar10 - uVar3) < 0 ==
      ((short)uVar10 < 0 && (short)(uVar10 - (uRam30575c < 0x7fff)) < 0 != (short)uVar10 < 0)) {
    uRam30575c = 0x7fff;
  }
  cVar6 = func_0x033006(0x8e44,nmot_rpmclass,uRam01bd66,uRam01bd73);
  if (cVar6 == '\0') {
    cVar6 = func_0x033006(0x8e42,nmot_rpmclass,uRam01bd66,uRam01bd72);
    if (cVar6 == '\0') {
      cVar6 = func_0x033006(0x8e40,nmot_rpmclass,uRam01bd66,uRam01bd71);
      if (cVar6 == '\0') {
        cVar6 = func_0x033006(0x8e3e,nmot_rpmclass,uRam01bd66,uRam01bd70);
        if (cVar6 == '\0') {
          bRam304e19 = 0;
        }
        else {
          bRam304e19 = 1;
        }
      }
      else {
        bRam304e19 = 2;
      }
    }
    else {
      bRam304e19 = 3;
    }
  }
  else {
    bRam304e19 = 4;
  }
  if (bRam304e1a == bRam304e19) {
    bRam301860 = bRam301860 & 0xfd;
  }
  else {
    bRam301860 = bRam301860 | 2;
  }
  bRam304e1a = bRam304e19;
  uVar10 = func_0x032cb8(uRam306496 << 8,uRam306496 >> 8,uRam305772);
  if (bRam01bd6f < uVar10) {
    bRam301860 = bRam301860 | 1;
  }
  else {
    bRam301860 = bRam301860 & 0xfe;
  }
  if (gear_index == '\x01') {
    sStack_e = func_0x0420da(0x458,0xb,uRam30199e);
  }
  else {
    sStack_e = func_0x0420da(0x478,0xb,uRam30199e);
  }
  sVar13 = sStack_e + uRam30575a;
  if (sStack_e < 0 == (short)uRam30575a < 0 && (short)(sStack_e + uRam30575a) < 0 != sStack_e < 0) {
    sVar13 = 0x7fff;
  }
  bVar2 = 0 < (short)uRam305760;
  bVar8 = me7_lookup_1d_byte(0x4ae,0xb,uRam304db1);
  bVar1 = nmot_rpmclass <= bVar8;
  if (((((sVar13 == sStack_e ||
          sVar13 - sStack_e < 0 !=
          (sVar13 < 0 != sStack_e < 0 && sVar13 - sStack_e < 0 != sVar13 < 0)) ||
        (cRam304e17 != cRam01bd65 &&
         (char)(cRam304e17 - cRam01bd65) < '\0' ==
         (cRam304e17 < '\0' != cRam01bd65 < '\0' &&
         (char)(cRam304e17 - cRam01bd65) < '\0' != cRam304e17 < '\0'))) || ((bRam301860 & 1) == 0))
      && ((((char)(cRam01bd65 - cRam304e17) < '\0' ==
            (cRam01bd65 < '\0' != cRam304e17 < '\0' &&
            (char)(cRam01bd65 - cRam304e17) < '\0' != cRam01bd65 < '\0') ||
           ((char)(cRam304e17 - cRam01bd62) < '\0' ==
            (cRam304e17 < '\0' != cRam01bd62 < '\0' &&
            (char)(cRam304e17 - cRam01bd62) < '\0' != cRam304e17 < '\0'))) ||
          (((bRam301860 & 1) == 0 ||
           ((short)(uRam30575a - uRam305760) < 0 !=
            ((short)uRam30575a < 0 != (short)uRam305760 < 0 &&
            (short)(uRam30575a - uRam305760) < 0 != (short)uRam30575a < 0))))))) ||
     ((!bVar2 || (bVar1)))) {
    uVar14 = 0;
  }
  else {
    uVar14 = 1;
  }
  cRam300e4e = func_0x032e88(0x8e4f,uVar14,uRam01bd74);
  if (cRam300e4e == '\0') {
    bRam30185f = bRam30185f & 0xfb;
  }
  else {
    bRam30185f = bRam30185f | 4;
  }
  bVar8 = func_0x042020(0x3d75,6,uRam30199c);
  if (((((short)(uRam30575a - uRam305760) < 0 ==
         ((short)uRam30575a < 0 != (short)uRam305760 < 0 &&
         (short)(uRam30575a - uRam305760) < 0 != (short)uRam30575a < 0)) ||
       (cRam304e17 == cRam01bd63 ||
        (char)(cRam304e17 - cRam01bd63) < '\0' !=
        (cRam304e17 < '\0' != cRam01bd63 < '\0' &&
        (char)(cRam304e17 - cRam01bd63) < '\0' != cRam304e17 < '\0'))) || (!bVar2)) || (bVar1)) {
    uVar14 = 0;
  }
  else {
    uVar14 = 1;
  }
  cRam300e50 = func_0x032e88(0x8e51,uVar14,bVar8);
  if ((((short)(uRam30575a - uRam305760) < 0 ==
        ((short)uRam30575a < 0 != (short)uRam305760 < 0 &&
        (short)(uRam30575a - uRam305760) < 0 != (short)uRam30575a < 0)) ||
      (cRam304e17 == cRam01bd63 ||
       (char)(cRam304e17 - cRam01bd63) < '\0' !=
       (cRam304e17 < '\0' != cRam01bd63 < '\0' &&
       (char)(cRam304e17 - cRam01bd63) < '\0' != cRam304e17 < '\0'))) ||
     ((!bVar2 ||
      ((bVar1 || ((char)(cRam304e17 - cRam01bd64) < '\0' ==
                  (cRam304e17 < '\0' != cRam01bd64 < '\0' &&
                  (char)(cRam304e17 - cRam01bd64) < '\0' != cRam304e17 < '\0'))))))) {
    uVar14 = 0;
  }
  else {
    uVar14 = 1;
  }
  MDL = (ushort)bVar8 * (ushort)bRam01bd21;
  MDH = 0;
  MDC = MDC | 0x10;
  cRam300e48 = func_0x032e88(0x8e49,uVar14,MDL >> 7);
  if ((cRam300e50 == '\0') && (cRam300e48 == '\0')) {
    bRam30185f = bRam30185f & 0xf7;
  }
  else {
    bRam30185f = bRam30185f | 8;
  }
  if ((((bRam301860 & 1) == 0) || (!bVar2)) || (bVar1)) {
    uVar14 = 0;
  }
  else {
    uVar14 = 1;
  }
  MDL = (ushort)bVar8 * (ushort)bRam01bd20;
  MDH = 0;
  MDC = MDC | 0x10;
  cRam300e4a = func_0x032e88(0x8e4b,uVar14,MDL >> 7);
  cRam300e46 = bVar2 && cRam300e47 == '\0';
  if (((cRam300e4a == '\0') || ((bRam301860 & 2) != 0)) || ((bool)cRam300e46)) {
    bRam30185f = bRam30185f & 0xfd;
  }
  else {
    bRam30185f = bRam30185f | 2;
  }
  cRam300e47 = bVar2;
  if ((bRam30185f & 2) != 0) {
    *(ushort *)((uint3)bRam304e19 * 2 + 0x30bf00) = uRam305758;
  }
  if ((cRam300e46 != '\0') || ((bRam301860 & 2) != 0)) {
    sVar11 = *(short *)((uint3)bRam304e19 * 2 + 0x30bf00);
    sVar12 = sVar11 - uRam305758;
    if (sVar11 < 0 != (short)uRam305758 < 0 && (short)(sVar11 - uRam305758) < 0 != sVar11 < 0) {
      sVar12 = -0x8000;
    }
    sVar11 = func_0x0330f2(uRam02c488,sVar12,uRam02c48a);
    uRam300e54 = sVar11 + uRam305758;
    if (sVar11 < 0 == (short)uRam305758 < 0 && (short)(sVar11 + uRam305758) < 0 != sVar11 < 0) {
      uRam300e54 = 0x7fff;
    }
  }
  if (((bRam30185f & 4) != 0) || ((bRam30185f & 8) != 0)) {
    uVar14 = uRam02c454;
    if ((bRam30185f & 4) == 0) {
      uVar14 = uRam02c456;
    }
    func_0x032f9e(0x8e54,uVar14,uRam02c452,0x7fff);
  }
  uRam305758 = uRam300e54;
  if ((bRam305860 & 1) == 0) {
    uRam305752 = 0;
  }
  else {
    uRam305752 = func_0x0426da(uRam02c412,0x414,0xb,uRam02c413,0x41c,0xb,0x422,0xb,(short)cRam301658
                               ,nmot_rpmclass);
  }
  uVar10 = uRam30575c + uRam305758;
  uRam30575a = uVar10 + uRam305752;
  uVar10 = ((short)uRam30575c >> 0xf) + ((short)uRam305758 >> 0xf) +
           (ushort)(uRam30575c + uRam305758 < uRam30575c || uRam30575c + uRam305758 < uRam305758) +
           ((short)uRam305752 >> 0xf) +
           (ushort)(uVar10 + uRam305752 < uVar10 || uVar10 + uRam305752 < uRam305752);
  if ((short)((uVar10 + 1) - (ushort)(uRam30575a < 0x8000)) < 0 ==
      (-1 < (short)uVar10 &&
      (short)((uVar10 + 1) - (ushort)(uRam30575a < 0x8000)) < 0 != (short)uVar10 < 0)) {
    uVar3 = (ushort)(uRam30575a < 0x7fff);
    if ((uVar10 != uVar3 || uRam30575a != 0x7fff) &&
        (short)(uVar10 - uVar3) < 0 ==
        ((short)uVar10 < 0 && (short)(uVar10 - (uRam30575a < 0x7fff)) < 0 != (short)uVar10 < 0)) {
      uRam30575a = 0x7fff;
    }
  }
  else {
    uRam30575a = 0x8000;
  }
  sVar12 = func_0x0420da(0x468,0xb,uRam30199e);
  sVar11 = sRam02c4dc - sVar12;
  if (sRam02c4dc < 0 != sVar12 < 0 && sRam02c4dc - sVar12 < 0 != sRam02c4dc < 0) {
    sVar11 = -0x8000;
  }
  sVar15 = uRam30575a - sVar12;
  if ((short)uRam30575a < 0 != sVar12 < 0 &&
      (short)(uRam30575a - sVar12) < 0 != (short)uRam30575a < 0) {
    sVar15 = -0x8000;
  }
  uRam305756 = func_0x0330f2(0,sVar15,sVar11);
  uRam30575e = func_0x0330f2(sStack_e,sVar13,sRam02c4dc);
  if ((bRam305850 & 2) == 0) {
    cRam304e18 = '\0';
    uRam305754 = 0;
  }
  else {
    sVar13 = (short)cRam304e18;
    if ((short)uRam305768 < 0) {
      iVar4 = (int)sVar13 * (int)(short)(uRam305768 & 0x7fff);
      uVar3 = (ushort)iVar4;
      uVar10 = sVar13 * -0x8000;
      iVar4 = CONCAT22((short)((uint)iVar4 >> 0x10) + (sVar13 >> 1) +
                       (ushort)(uVar3 + uVar10 < uVar3 || uVar3 + uVar10 < uVar10),uVar3 + uVar10);
    }
    else {
      iVar4 = (int)sVar13 * (int)(short)uRam305768;
    }
    uVar10 = (ushort)((uint)iVar4 >> 0x10);
    uRam305754 = (ushort)iVar4;
    MDC = MDC | 0x10;
    if ((short)((uVar10 + 1) - (ushort)(uRam305754 < 0x8000)) < 0 ==
        (-1 < iVar4 && (short)((uVar10 + 1) - (ushort)(uRam305754 < 0x8000)) < 0 != iVar4 < 0)) {
      uVar3 = (ushort)(uRam305754 < 0x7fff);
      if ((uVar10 != uVar3 || uRam305754 != 0x7fff) &&
          (short)(uVar10 - uVar3) < 0 ==
          (iVar4 < 0 && (short)(uVar10 - (uRam305754 < 0x7fff)) < 0 != iVar4 < 0)) {
        uRam305754 = 0x7fff;
      }
    }
    else {
      uRam305754 = 0x8000;
    }
    cRam304e18 = cRam304e17;
  }
  cRam300e52 = cRam304e17 - cRam300e53;
  if (cRam304e17 < '\0' != cRam300e53 < '\0' &&
      (char)(cRam304e17 - cRam300e53) < '\0' != cRam304e17 < '\0') {
    cRam300e52 = -0x80;
  }
  cRam304e53 = cRam304e17;
  sVar13 = (short)cRam304e17;
  if ((short)uRam30576a < 0) {
    iVar4 = (int)sVar13 * (int)(short)(uRam30576a & 0x7fff);
    uVar3 = (ushort)iVar4;
    uVar10 = sVar13 * -0x8000;
    iVar4 = CONCAT22((short)((uint)iVar4 >> 0x10) + (sVar13 >> 1) +
                     (ushort)(uVar3 + uVar10 < uVar3 || uVar3 + uVar10 < uVar10),uVar3 + uVar10);
  }
  else {
    iVar4 = (int)sVar13 * (int)(short)uRam30576a;
  }
  uVar10 = (ushort)((uint)iVar4 >> 0x10);
  uRam305762 = (ushort)iVar4;
  if ((short)((uVar10 + 1) - (ushort)(uRam305762 < 0x8000)) < 0 ==
      (-1 < iVar4 && (short)((uVar10 + 1) - (ushort)(uRam305762 < 0x8000)) < 0 != iVar4 < 0)) {
    uVar3 = (ushort)(uRam305762 < 0x7fff);
    if ((uVar10 != uVar3 || uRam305762 != 0x7fff) &&
        (short)(uVar10 - uVar3) < 0 ==
        (iVar4 < 0 && (short)(uVar10 - (uRam305762 < 0x7fff)) < 0 != iVar4 < 0)) {
      uRam305762 = 0x7fff;
    }
  }
  else {
    uRam305762 = 0x8000;
  }
  sVar13 = (short)cRam304e52;
  if ((short)uRam305766 < 0) {
    iVar5 = (int)sVar13 * (int)(short)(uRam305766 & 0x7fff);
    uVar3 = (ushort)iVar5;
    uVar10 = sVar13 * -0x8000;
    iVar4 = CONCAT22((short)((uint)iVar5 >> 0x10) + (sVar13 >> 1) +
                     (ushort)(uVar3 + uVar10 < uVar3 || uVar3 + uVar10 < uVar10),uVar3 + uVar10);
  }
  else {
    iVar4 = (int)sVar13 * (int)(short)uRam305766;
    iVar5 = iVar4;
  }
  MDH = (undefined2)((uint)iVar5 >> 0x10);
  MDL = (ushort)iVar5;
  uVar10 = (ushort)((uint)iVar4 >> 0x10);
  uRam305764 = (ushort)iVar4;
  MDC = MDC | 0x10;
  if ((short)((uVar10 + 1) - (ushort)(uRam305764 < 0x8000)) < 0 ==
      (-1 < iVar4 && (short)((uVar10 + 1) - (ushort)(uRam305764 < 0x8000)) < 0 != iVar4 < 0)) {
    uVar3 = (ushort)(uRam305764 < 0x7fff);
    if ((uVar10 != uVar3 || uRam305764 != 0x7fff) &&
        (short)(uVar10 - uVar3) < 0 ==
        (iVar4 < 0 && (short)(uVar10 - (uRam305764 < 0x7fff)) < 0 != iVar4 < 0)) {
      uRam305764 = 0x7fff;
    }
  }
  else {
    uRam305764 = 0x8000;
  }
  if ((bRam305850 & 2) == 0) {
    uRam305760 = 0;
  }
  else {
    sVar13 = (short)uRam305760 >> 0xf;
    uVar10 = uRam305754 + uRam305760;
    bVar1 = uRam305754 + uRam305760 < uRam305760;
    uRam305760 = uRam305754 + uRam305760;
    sVar13 = ((short)uRam305754 >> 0xf) + sVar13 + (ushort)(uVar10 < uRam305754 || bVar1);
    sVar11 = (short)uRam305756 >> 0xf;
    uVar10 = (ushort)(uRam305760 < uRam305756);
    if (sVar13 - sVar11 == uVar10 && uRam305760 == uRam305756 ||
        (short)((sVar13 - sVar11) - uVar10) < 0 !=
        (sVar13 < 0 != sVar11 < 0 &&
        (short)((sVar13 - sVar11) - (ushort)(uRam305760 < uRam305756)) < 0 != sVar13 < 0)) {
      uRam305760 = uRam305756;
      sVar13 = sVar11;
    }
    sVar11 = (short)uRam30575e >> 0xf;
    if ((short)((sVar13 - sVar11) - (ushort)(uRam305760 < uRam30575e)) < 0 ==
        (sVar13 < 0 != sVar11 < 0 &&
        (short)((sVar13 - sVar11) - (ushort)(uRam305760 < uRam30575e)) < 0 != sVar13 < 0)) {
      uRam305760 = uRam30575e;
    }
  }
  uVar10 = uRam305764 + uRam305760;
  uRam30576c = uRam305762 + uVar10;
  uVar10 = ((short)uRam305762 >> 0xf) +
           ((short)uRam305764 >> 0xf) + ((short)uRam305760 >> 0xf) +
           (ushort)(uRam305764 + uRam305760 < uRam305764 || uRam305764 + uRam305760 < uRam305760) +
           (ushort)(uRam305762 + uVar10 < uRam305762 || uRam305762 + uVar10 < uVar10);
  if ((short)((uVar10 + 1) - (ushort)(uRam30576c < 0x8000)) < 0 ==
      (-1 < (short)uVar10 &&
      (short)((uVar10 + 1) - (ushort)(uRam30576c < 0x8000)) < 0 != (short)uVar10 < 0)) {
    uVar3 = (ushort)(uRam30576c < 0x7fff);
    if ((uVar10 != uVar3 || uRam30576c != 0x7fff) &&
        (short)(uVar10 - uVar3) < 0 ==
        ((short)uVar10 < 0 && (short)(uVar10 - (uRam30576c < 0x7fff)) < 0 != (short)uVar10 < 0)) {
      uRam30576c = 0x7fff;
    }
  }
  else {
    uRam30576c = 0x8000;
  }
  uRam302e1a = func_0x04195e(0x4c6,0xb,uRam30576c,uRam302e1a);
  uRam30576e = func_0x042290(0x152,0xb,0x4c6,0xb,uRam3019b2,uRam302e1a);
  return;
}


// ================= driveline_antijerk_damper @ 0967fe =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CONTROL: anti-jerk / load-change damper (ARMD+dashpot cal family
   CWARMD/TVKUPAR/TVKUPHS/TVKUPRS/TZSPINI/DSTOFFS/DSTGRAD/KLTDS/VLTEDK): rpm-delta
   (word_30243C-word_302546)/2 -> word_302AF4, T4-dt scaled filter via sub_430DA -> word_3008A6;
   per-gear delta-n threshold table DNFILO 0x165DE indexed by gear byte_3014DD clamp 1-7 (0x96B3A
   mov r9,[r8+#65DEh]); oscillation magnitude word_3008B0 vs word_165A8 gates; disable path bset
   word_FD54.0/.1 + reload dashpot ctr byte_301651=DSTOFFS, byte_300880=TZSPINI, zero filter history
   302AFC/300882-30089C (torque.md 7) [C mechanism; ARMD/dashpot identity I] */

void driveline_antijerk_damper(void)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  ushort uVar5;
  int iVar4;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  byte bVar14;
  ushort uVar15;
  ushort uVar16;
  ushort uVar17;
  short sVar18;
  
  iVar4 = CONCAT22(MDH,MDL);
  sRam302af4 = (uRam30243c >> 1) - (uRam302546 >> 1);
  if (uRam30243c >> 1 < uRam302546 >> 1) {
    if (sRam302af4 >= 0) {
      sRam302af4 = -0x8000;
    }
  }
  else if (sRam302af4 < 0) {
    sRam302af4 = 0x7fff;
  }
  if (100 < nmot_rpmclass) {
    sRam302af2 = sRam302af4 - uRam302af6;
    if (sRam302af4 < 0 != (short)uRam302af6 < 0 &&
        (short)(sRam302af4 - uRam302af6) < 0 != sRam302af4 < 0) {
      sRam302af2 = -0x8000;
    }
    if ((nmot_rpmclass < 0x70) || ((bRam3008b6 & 4) == 0)) {
      if ((bRam3008b6 & 4) == 0) {
        MDL = (ushort)((uint)uRam302af0 * 0x98);
        MDH = (short)((uint)uRam302af0 * 0x98 >> 0x10);
        MDC = MDC | 0x10;
        iRam3008a6 = func_0x0430da(MDL >> 8 | MDH << 8,sRam302af2,iRam3008a6._2_2_,
                                   (undefined2)iRam3008a6,0,0,0x7fff,0xffff);
        uRam302b02 = (ushort)((uint)iRam3008a6 >> 0x10);
        sRam3008aa = T4;
      }
    }
    else {
      uRam3008ac = T4 - sRam3008aa;
      sRam3008aa = T4;
      uRam3008ae = (ushort)((uint)uRam3008ac * 0x3200 >> 0x10);
      MDL = (ushort)((uint)uRam302af0 * (uint)uRam3008ae);
      MDH = (short)((uint)uRam302af0 * (uint)uRam3008ae >> 0x10);
      MDC = MDC | 0x10;
      iRam3008a6 = func_0x0430da(MDL >> 8 | MDH << 8,iRam3008a6._2_2_,(undefined2)iRam3008a6,0,0,
                                 0x7fff,0xffff);
      uRam302b02 = (ushort)((uint)iRam3008a6 >> 0x10);
      bRam3008b6 = bRam3008b6 & 0xfb;
    }
    sRam302b00 = uRam302b02 - nmot_w;
    if (uRam302b02 < nmot_w) {
      if (sRam302b00 >= 0) {
        sRam302b00 = -0x8000;
      }
    }
    else if (sRam302b00 < 0) {
      sRam302b00 = 0x7fff;
    }
    uVar15 = (ushort)bRam30164d * 0xa4 >> 5;
    if ((short)uVar15 < 0) {
      iVar4 = (int)sRam302b00 * (int)(short)uVar15;
      uVar16 = (ushort)iVar4;
      uVar15 = sRam302b00 * -0x8000;
      iVar3 = CONCAT22((short)((uint)iVar4 >> 0x10) + (sRam302b00 >> 1) +
                       (ushort)(uVar16 + uVar15 < uVar16 || uVar16 + uVar15 < uVar15),
                       uVar16 + uVar15);
    }
    else {
      iVar3 = (int)sRam302b00 * (int)(short)uVar15;
      iVar4 = iVar3;
    }
    uVar16 = (ushort)((uint)iVar3 >> 0x10);
    uRam302af6 = (ushort)iVar3;
    MDC = MDC | 0x10;
    uVar15 = (ushort)(uRam302af6 < 0x7fff);
    if (uVar16 == uVar15 && uRam302af6 == 0x7fff ||
        (short)(uVar16 - uVar15) < 0 !=
        (iVar3 < 0 && (short)(uVar16 - (uRam302af6 < 0x7fff)) < 0 != iVar3 < 0)) {
      if ((short)((uVar16 + 1) - (ushort)(uRam302af6 < 0x8000)) < 0 !=
          (-1 < iVar3 && (short)((uVar16 + 1) - (ushort)(uRam302af6 < 0x8000)) < 0 != iVar3 < 0)) {
        uRam302af6 = 0x8000;
      }
    }
    else {
      uRam302af6 = 0x7fff;
    }
  }
  iVar13 = CONCAT22(uRam30088c,uRam30088a);
  iVar3 = CONCAT22(uRam30088c,uRam30088a);
  if (vfzg_class < bRam013eb3) {
    bRam3008b6 = bRam3008b6 & 0xfe;
  }
  else {
    bVar14 = bRam013eb3 + bRam013e8c;
    if ((byte)(bRam013eb3 + bRam013e8c) < bRam013eb3 || (byte)(bRam013eb3 + bRam013e8c) < bRam013e8c
       ) {
      bVar14 = 0xff;
    }
    if (bVar14 < vfzg_class) {
      bRam3008b6 = bRam3008b6 | 1;
    }
  }
  if (cRam013e8b != '\0') {
    if ((uRam00fd54 & 8) == 0) {
      bRam30164f = 0;
    }
    else {
      bVar1 = (byte)(bRam30164f + 1) < bRam30164f;
      bVar2 = bRam30164f == 0xff;
      bRam30164f = bRam30164f + 1;
      if (bVar1 || bVar2) {
        bRam30164f = 0xff;
      }
    }
    if ((uRam00fd52 & 0x8000) == 0) {
      bRam301650 = 0;
    }
    else {
      bVar1 = (byte)(bRam301650 + 1) < bRam301650;
      bVar2 = bRam301650 == 0xff;
      bRam301650 = bRam301650 + 1;
      if (bVar1 || bVar2) {
        bRam301650 = 0xff;
      }
    }
    bVar14 = bRam013ea6;
    if ((1 < gear_index) && (bVar14 = bRam013eab, (short)(gear_index - 7) < 0)) {
      bVar14 = *(byte *)((uint3)gear_index + 0x13ea5);
    }
    if (-1 < (short)((ushort)bVar14 - (ushort)bRam30164f)) {
      bVar14 = bRam013eac;
      if ((1 < gear_index) && (bVar14 = bRam013eb1, (short)(gear_index - 7) < 0)) {
        bVar14 = *(byte *)((uint3)gear_index + 0x13eab);
      }
      if (-1 < (short)((ushort)bVar14 - (ushort)bRam301650)) {
        uRam00fd54 = uRam00fd54 | 4;
        goto LAB_096a9e;
      }
    }
    uRam00fd54 = uRam00fd54 & 0xfffb;
  }
LAB_096a9e:
  if (sRam302b00 == sRam302afe ||
      sRam302b00 - sRam302afe < 0 !=
      (sRam302b00 < 0 != sRam302afe < 0 && sRam302b00 - sRam302afe < 0 != sRam302b00 < 0)) {
    cRam30164e = cRam013ea5;
  }
  else if (cRam30164e != '\0') {
    cRam30164e = cRam30164e + -1;
  }
  if ((uRam00fd54 & 1) == 0) {
    bVar1 = cRam301651 == '\0';
    cRam301651 = cRam301651 + -1;
    if (bVar1) {
      cRam301651 = '\0';
    }
    if (cRam301651 == '\0') {
      uRam00fd54 = uRam00fd54 & 0xfffd;
    }
  }
  if (((((((uRam00fd64 & 0x1000) == 0) || (cRam30164e != '\0')) &&
        ((cRam013e8b != '\0' || ((uRam00fd66 & 0x10) == 0)))) &&
       ((((cRam013e8b == '\0' || ((uRam00fd54 & 4) == 0)) && (gear_index != 0)) &&
        (uRam30243c == uRam301ad0)))) && (((bRam3008b6 & 2) != 0 || ((uRam00fd26 & 0x8000) == 0))))
     && (((uRam00fd3c & 1) == 0 &&
         (sRam3008b0 == sRam0165a8 ||
          sRam3008b0 - sRam0165a8 < 0 !=
          (sRam3008b0 < 0 != sRam0165a8 < 0 && sRam3008b0 - sRam0165a8 < 0 != sRam3008b0 < 0))))) {
    uVar15 = uRam0165e0;
    if ((1 < gear_index) && (uVar15 = uRam0165ea, (short)(gear_index - 7) < 0)) {
      uVar15 = *(ushort *)((uint3)gear_index * 2 + 0x165de);
    }
    if ((uVar15 < uRam302afa) && (cRam300880 == '\0')) goto LAB_096b56;
    uVar15 = uRam00fd54 & 0xfffe;
    iVar6 = iRam3008a6;
    if (cRam301651 == '\0') {
      uVar15 = uRam00fd54 & 0xfffc;
    }
  }
  else {
LAB_096b56:
    cRam301651 = cRam013ea2;
    cRam300880 = cRam013eb2;
    uRam302afc = 0;
    uRam300882 = 0;
    uRam300884 = 0;
    sRam300886 = 0;
    sRam300888 = 0;
    uRam30088e = 0;
    uRam300890 = 0;
    uRam300892 = 0;
    uRam300894 = 0;
    uRam300896 = 0;
    uRam300898 = 0;
    uRam30089a = 0;
    sRam30089c = 0;
    uRam30089e = 0;
    uRam3008a0 = 0;
    uRam3008a2 = 0;
    uRam3008a4 = 0;
    uRam302b02 = nmot_w;
    uVar15 = uRam00fd54 | 3;
    iVar6 = (uint)nmot_w << 0x10;
  }
  uRam00fd54 = uVar15;
  iRam3008a6._2_2_ = (undefined2)((uint)iVar6 >> 0x10);
  iRam3008a6._0_2_ = (undefined2)iVar6;
  iVar12 = CONCAT22(uRam300890,uRam30088e);
  iVar11 = CONCAT22(uRam300894,uRam300892);
  iVar10 = CONCAT22(uRam300894,uRam300892);
  iVar9 = CONCAT22(uRam300898,uRam300896);
  iVar8 = CONCAT22(uRam300898,uRam300896);
  iVar7 = CONCAT22(sRam30089c,uRam30089a);
  iVar6 = CONCAT22(sRam30089c,uRam30089a);
  if ((uRam00fd26 & 0x8000) == 0) {
    bRam3008b6 = bRam3008b6 & 0xfd;
  }
  else {
    bRam3008b6 = bRam3008b6 | 2;
  }
  if (uRam0165dc < uRam30244e) {
    bRam3008b6 = bRam3008b6 | 8;
  }
  else if (uRam30244e < uRam0165de) {
    bRam3008b6 = bRam3008b6 & 0xf7;
  }
  if (((((_flags_start_phase & 0x8000) != 0) && ((flags_torque_revlimit & 0x80) == 0)) &&
      ((uRam00fd66 & 0x10) == 0)) &&
     (((bRam3008b6 & 1) != 0 && (((uRam00fd1c & 0x2000) == 0 || (bRam013ea1 <= nmot_rpmclass)))))) {
    bVar14 = bRam013e9b;
    if ((1 < gear_index) && (bVar14 = bRam013ea0, (short)(gear_index - 7) < 0)) {
      bVar14 = *(byte *)((uint3)gear_index + 0x13e9a);
    }
    if (((((ushort)bVar14 == (ushort)nmot_rpmclass ||
           (short)((ushort)bVar14 - (ushort)nmot_rpmclass) < 0) && (nmot_rpmclass <= bRam013e9a)) &&
        (((uRam00fd54 & 2) == 0 && (bRam013ea3 <= rpmclass_oppoint)))) &&
       (((bRam3008b6 & 8) == 0 || (bRam013ea4 <= rpmclass_oppoint)))) {
      PSW = PSW & 0xffbf;
      goto LAB_096ca8;
    }
  }
  PSW = PSW | 0x40;
LAB_096ca8:
  uRam00fd52 = uRam00fd52 & 0xbfff | ((PSW & 0x40) >> 6 ^ 1) << 0xe;
  if (cRam300880 != '\0') {
    cRam300880 = cRam300880 + -1;
  }
  cRam300881 = cRam300881 + '\x01';
  if (cRam300881 == '\x01') {
    iVar4 = (int)(short)uRam300884 * (int)sRam0165a6;
    MDC = MDC | 0x10;
    iVar6 = iVar4;
    iVar8 = CONCAT22(uRam300898,uRam300896);
    iVar10 = CONCAT22(uRam300894,uRam300892);
    iVar12 = CONCAT22(uRam300890,uRam30088e);
    iVar3 = CONCAT22(uRam30088c,uRam30088a);
  }
  else if (cRam300881 == '\x02') {
    iVar4 = (int)(short)uRam300882 * (int)sRam0165a4;
    uVar17 = (ushort)iVar4;
    uVar5 = (ushort)((uint)iVar4 >> 0x10);
    MDC = MDC | 0x10;
    bVar1 = uVar17 + uRam30089a < uVar17;
    bVar2 = uVar17 + uRam30089a < uRam30089a;
    uVar15 = (ushort)(bVar1 || bVar2);
    uVar17 = uVar17 + uRam30089a;
    uVar16 = uVar5 + sRam30089c;
    sVar18 = uVar5 + sRam30089c + uVar15;
    if (iVar4 < 0 == sRam30089c < 0 && (short)(uVar16 + uVar15) < 0 != iVar4 < 0) {
      if (uVar16 < uVar5 || uVar16 == 0xffff && (bVar1 || bVar2)) {
        uVar17 = 0;
        sVar18 = -0x8000;
      }
      else {
        uVar17 = 0xffff;
        sVar18 = 0x7fff;
      }
    }
    uRam3008a4 = sVar18 >> 0xe;
    uRam3008a2 = uVar17 >> 0xe | sVar18 << 2;
    iVar6 = CONCAT22(sRam30089c,uRam30089a);
    iVar8 = iVar4;
    iVar10 = CONCAT22(uRam300894,uRam300892);
    iVar12 = CONCAT22(uRam300890,uRam30088e);
    iVar3 = CONCAT22(uRam30088c,uRam30088a);
  }
  else if (cRam300881 == '\x03') {
    iVar4 = (int)sRam300888 * (int)sRam0165a2;
    MDC = MDC | 0x10;
    iVar6 = CONCAT22(sRam30089c,uRam30089a);
    iVar8 = CONCAT22(uRam300898,uRam300896);
    iVar10 = iVar4;
    iVar12 = CONCAT22(uRam300890,uRam30088e);
    iVar3 = CONCAT22(uRam30088c,uRam30088a);
  }
  else if (cRam300881 == '\x04') {
    iVar4 = (int)sRam300886 * (int)sRam0165a0;
    uRam30089e = (ushort)iVar4;
    sVar18 = (short)((uint)iVar4 >> 0x10);
    MDC = MDC | 0x10;
    bVar1 = uRam300892 + uRam30089e < uRam300892;
    bVar2 = uRam300892 + uRam30089e < uRam30089e;
    uVar15 = (ushort)(bVar1 || bVar2);
    uRam30089e = uRam300892 + uRam30089e;
    uVar16 = uRam300894 + sVar18;
    uRam3008a0 = uRam300894 + sVar18 + uVar15;
    iVar6 = iVar7;
    iVar8 = iVar9;
    iVar10 = iVar11;
    iVar12 = iVar4;
    iVar3 = iVar13;
    if ((short)uRam300894 < 0 == iVar4 < 0 && (short)(uVar16 + uVar15) < 0 != (short)uRam300894 < 0)
    {
      if (uVar16 < uRam300894 || uVar16 == 0xffff && (bVar1 || bVar2)) {
        uRam30089e = 0;
        uRam3008a0 = 0x8000;
      }
      else {
        uRam30089e = 0xffff;
        uRam3008a0 = 0x7fff;
      }
    }
  }
  else if (cRam300881 == '\x05') {
    cRam300881 = '\0';
    iVar4 = (int)sRam302b00 * (int)sRam01659e;
    uVar15 = (ushort)iVar4;
    sVar18 = (short)((uint)iVar4 >> 0x10);
    MDC = MDC | 0x10;
    bVar1 = uRam30089e + uVar15 < uRam30089e;
    bVar2 = uRam30089e + uVar15 < uVar15;
    uVar15 = (ushort)(bVar1 || bVar2);
    uVar16 = uRam3008a0 + sVar18;
    sVar18 = uRam3008a0 + sVar18 + uVar15;
    if ((short)uRam3008a0 < 0 == iVar4 < 0 && (short)(uVar16 + uVar15) < 0 != (short)uRam3008a0 < 0)
    {
      if (uVar16 < uRam3008a0 || uVar16 == 0xffff && (bVar1 || bVar2)) {
        sVar18 = -0x8000;
      }
      else {
        sVar18 = 0x7fff;
      }
    }
    uRam30089e = sVar18 >> 3;
    uRam3008a0 = sVar18 >> 0xf;
    uVar15 = (ushort)(uRam30089e < uRam3008a2);
    uRam302afc = uRam30089e - uRam3008a2;
    uVar16 = (uRam3008a0 - uRam3008a4) - uVar15;
    if ((short)uRam3008a0 < 0 != (short)uRam3008a4 < 0 &&
        (short)((uRam3008a0 - uRam3008a4) - uVar15) < 0 != (short)uRam3008a0 < 0) {
      if (uRam3008a0 < uRam3008a4 || uRam3008a0 == uRam3008a4 && uRam30089e < uRam3008a2) {
        uRam302afc = 0xffff;
        uVar16 = 0x7fff;
      }
      else {
        uRam302afc = 0;
        uVar16 = 0x8000;
      }
    }
    uVar15 = (ushort)(uRam302afc < 0x7fff);
    if (uVar16 == uVar15 && uRam302afc == 0x7fff ||
        (short)(uVar16 - uVar15) < 0 !=
        ((short)uVar16 < 0 && (short)(uVar16 - (uRam302afc < 0x7fff)) < 0 != (short)uVar16 < 0)) {
      if ((short)((uVar16 + 1) - (ushort)(uRam302afc < 0x8000)) < 0 !=
          (-1 < (short)uVar16 &&
          (short)((uVar16 + 1) - (ushort)(uRam302afc < 0x8000)) < 0 != (short)uVar16 < 0)) {
        uRam302afc = 0x8000;
      }
    }
    else {
      uRam302afc = 0x7fff;
    }
    if ((short)uRam302afc < 0) {
      uRam302afa = -uRam302afc;
      if (uRam302afc == 0x8000) {
        uRam302afa = 0x7fff;
      }
    }
    else {
      uRam302afa = uRam302afc;
    }
    sRam3008b0 = uRam302afc - uRam300882;
    if ((short)uRam302afc < 0 != (short)uRam300882 < 0 &&
        (short)(uRam302afc - uRam300882) < 0 != (short)uRam302afc < 0) {
      sRam3008b0 = -0x8000;
    }
    if ((sRam3008b0 < 0) && (bVar1 = sRam3008b0 == -0x8000, sRam3008b0 = -sRam3008b0, bVar1)) {
      sRam3008b0 = 0x7fff;
    }
    sRam300888 = sRam300886;
    sRam300886 = sRam302b00;
    uRam300884 = uRam300882;
    uRam300882 = uRam302afc;
    iVar6 = CONCAT22(sRam30089c,uRam30089a);
    iVar8 = CONCAT22(uRam300898,uRam300896);
    iVar10 = CONCAT22(uRam300894,uRam300892);
    iVar12 = CONCAT22(uRam300890,uRam30088e);
    iVar3 = iVar4;
  }
  uRam30088c = (undefined2)((uint)iVar3 >> 0x10);
  uRam30088a = (undefined2)iVar3;
  uRam300890 = (undefined2)((uint)iVar12 >> 0x10);
  uRam30088e = (undefined2)iVar12;
  uRam300894 = (ushort)((uint)iVar10 >> 0x10);
  uRam300892 = (ushort)iVar10;
  uRam300898 = (undefined2)((uint)iVar8 >> 0x10);
  uRam300896 = (undefined2)iVar8;
  sRam30089c = (short)((uint)iVar6 >> 0x10);
  uRam30089a = (ushort)iVar6;
  MDH = (short)((uint)iVar4 >> 0x10);
  MDL = (ushort)iVar4;
  return;
}


// ================= diag_kwp_localid_capability @ 05eb80 =================

/* DIAGNOSTIC/comms: KWP2000 local-ID capability helper: jump-table on ID 0x81-0x9A (0x5EB86 cmpb
   rl4,#19h), reads per-ID cal enable byte 0x1F518-0x1F538, returns item count 5/4/2/1 if enabled
   else 0; called by KWP service handler sub_5F172 (SID+0x40 response builder) [C] */

bool diag_kwp_localid_capability(undefined1 param_1)

{
  undefined1 uVar1;
  
  switch(param_1) {
  case 0x81:
  case 0x82:
    if (cRam013518 == '\0') {
      uVar1 = 0;
    }
    else {
      uVar1 = 5;
    }
    break;
  case 0x83:
    if (cRam01351d == '\0') {
      uVar1 = 0;
    }
    else {
      uVar1 = 4;
    }
    return (bool)uVar1;
  case 0x84:
    return cRam013521 != '\0';
  case 0x85:
    return cRam013522 != '\0';
  case 0x86:
    if (cRam013523 == '\0') {
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
    return (bool)uVar1;
  case 0x87:
    return cRam013525 != '\0';
  case 0x88:
    return cRam013526 != '\0';
  case 0x89:
    return cRam013527 != '\0';
  case 0x8a:
    return cRam013528 != '\0';
  case 0x8b:
    return cRam013529 != '\0';
  case 0x8c:
    return cRam01352a != '\0';
  case 0x8d:
    return cRam01352b != '\0';
  case 0x8e:
    return cRam01352c != '\0';
  case 0x8f:
    return cRam01352d != '\0';
  case 0x90:
    return cRam01352e != '\0';
  case 0x91:
    return cRam01352f != '\0';
  case 0x92:
    return cRam013530 != '\0';
  case 0x93:
    return cRam013531 != '\0';
  case 0x94:
    return cRam013533 != '\0';
  case 0x95:
    return cRam013534 != '\0';
  case 0x96:
    return cRam013532 != '\0';
  case 0x97:
    return cRam013535 != '\0';
  case 0x98:
    return cRam013536 != '\0';
  case 0x99:
    return cRam013537 != '\0';
  case 0x9a:
    return cRam013538 != '\0';
  default:
    return false;
  }
  return (bool)uVar1;
}


// ================= diag_obd_denominator_update @ 0af080 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* DIAGNOSTIC: OBD in-use-counter general-denominator update (IUMPR-style):
   engine-run/at-speed/continuous-idle timers from 32-bit T4-tick accumulator word_300B50/52
   (quantum 0x1312D via sub_8DD8) vs cal 0x24986-0x2499A; env gates byte_304D30 vs byte_1A1C9 +
   word_305614 vs word_24986; increments NV counters word_30A298 (denominator 0xAF3C2) / word_30A29A
   (ign-cycle 0xAF210); per-monitor loop over 24 flag bytes 0xC1:0x9DB + word ctrs 0xC2:0x229C,
   fault check via sub_BF0E4 [C mechanism; IUMPR identity I] */

void diag_obd_denominator_update(void)

{
  bool bVar1;
  byte bVar2;
  ushort uVar3;
  undefined4 uVar4;
  ushort in_r1;
  ushort uVar5;
  short sVar6;
  ushort uVar7;
  byte bVar8;
  ushort uVar9;
  ushort unaff_r8;
  ushort uVar10;
  int iVar11;
  
  bRam30172e = bRam30172e & 0x87;
  bVar8 = 0;
  do {
    *(byte *)((uint3)(bVar8 + 0x9db) + 0x304000) =
         *(byte *)((uint3)(bVar8 + 0x9db) + 0x304000) & 0xfb;
    bVar8 = bVar8 + 1;
  } while (bVar8 < 0x18);
  bVar8 = 0;
  do {
    if ((bRam30333e <= bVar8) || (0x3b < bVar8)) {
      if (((bRam30172e & 0x20) == 0) && (((bRam30172e & 8) == 0 || ((bRam30172e & 0x10) == 0)))) {
        bRam30172e = bRam30172e & 0xdf;
      }
      else {
        bRam30172e = bRam30172e | 0x20;
      }
      if ((uRam302634 & 1) != 0) {
        bRam30172e = bRam30172e | 0x80;
      }
      if ((bRam30172f & 1) == 0) {
        if (cRam3049d3 == '\0') {
          bRam30172f = bRam30172f | 1;
        }
        if (nmot_w < uRam024990) {
          cRam3049d3 = cRam01a1c7;
        }
        else if (cRam3049d3 != '\0') {
          cRam3049d3 = cRam3049d3 + -1;
        }
      }
      if ((((bRam30172e & 0x40) == 0) && ((bRam30172f & 1) != 0)) && ((bRam30172e & 4) == 0)) {
        _obd_ign_cycle_ctr = _obd_ign_cycle_ctr + 1;
        bRam30172e = bRam30172e | 4;
      }
      if (bRam304d30 < bRam01a1c9) {
        bRam30172f = bRam30172f & 0xdf;
      }
      else {
        bRam30172f = bRam30172f | 0x20;
      }
      if (uRam305614 < uRam024986) {
        bRam30172f = bRam30172f & 0xfd;
      }
      else {
        bRam30172f = bRam30172f | 2;
      }
      if (((bRam30172f & 2) == 0) || ((bRam30172f & 0x20) == 0)) {
        bRam30172e = bRam30172e & 0xfe;
      }
      else {
        bRam30172e = bRam30172e | 1;
      }
      if ((bRam30172e & 2) == 0) {
        if ((((bRam30172f & 1) == 0) || ((bRam30172e & 1) == 0)) || ((bRam30172e & 0x20) != 0)) {
          if ((bRam30172f & 8) == 0) {
            uRam3054aa = 0;
          }
        }
        else {
          iVar11 = func_0x008dd8();
          iVar11 = iVar11 - CONCAT22(uRam302c6e._2_2_,(undefined2)uRam302c6e);
          uVar5 = (ushort)iVar11;
          bVar1 = uRam300b50 + uVar5 < uRam300b50;
          uVar9 = uRam300b50 + uVar5;
          uRam300b50 = uRam300b50 + uVar5;
          for (sRam300b52 = sRam300b52 + (short)((uint)iVar11 >> 0x10) +
                            (ushort)(bVar1 || uVar9 < uVar5);
              (sRam300b52 - 1U != (ushort)(uRam300b50 < 0x312d) || uRam300b50 != 0x312d) &&
              (sRam300b52 != 0 && (sRam300b52 != 1 || uRam300b50 >= 0x312d));
              sRam300b52 = sRam300b52 + -1) {
            if ((bRam30172f & 4) == 0) {
              if (uRam3054a8 != 0xffff) {
                uRam3054a8 = uRam3054a8 + 1;
              }
              if (uRam024992 < uRam3054a8) {
                bRam30172f = bRam30172f | 4;
              }
            }
            if (((bRam30172f & 0x10) == 0) && (uRam024998 <= _vfzg_vehicle_speed)) {
              if (uRam3054ac != 0xffff) {
                uRam3054ac = uRam3054ac + 1;
              }
              if (uRam024996 < uRam3054ac) {
                bRam30172f = bRam30172f | 0x10;
              }
            }
            if ((bRam30172f & 8) == 0) {
              if (((uRam00fd1c & 0x2000) == 0) || (uRam02499a < _vfzg_vehicle_speed)) {
                uRam3054aa = 0;
              }
              else {
                if (uRam3054aa != 0xffff) {
                  uRam3054aa = uRam3054aa + 1;
                }
                if (uRam024994 < uRam3054aa) {
                  bRam30172f = bRam30172f | 8;
                }
              }
            }
            uRam300b50 = uRam300b50 + 0xced3;
          }
          if ((((bRam30172f & 0x10) != 0) && ((bRam30172f & 8) != 0)) && ((bRam30172f & 4) != 0)) {
            _obd_denominator_ctr = _obd_denominator_ctr + 1;
            bRam30172e = bRam30172e | 2;
          }
        }
        uRam302c6e = func_0x008dd8();
      }
      bVar8 = 0;
      do {
        uVar9 = bVar8 + 0x9db;
        if ((((*(byte *)((uint3)uVar9 + 0x304000) & 8) == 0) &&
            ((*(byte *)((uint3)uVar9 + 0x304000) & 1) != 0)) &&
           (*(short *)((uint3)bVar8 * 2 + 0x305458) == 0)) {
          sVar6 = func_0x0bf0e4(*(undefined2 *)((uint3)bVar8 * 2 + 0x30a2cc));
          if (sVar6 != 0) {
            *(byte *)((uint3)uVar9 + 0x304000) = *(byte *)((uint3)uVar9 + 0x304000) | 8;
          }
        }
        bVar8 = bVar8 + 1;
      } while (bVar8 < 0x18);
      if ((bRam30172e & 0x20) == 0) {
        bVar8 = 0;
        do {
          uVar9 = bVar8 + 0x9db;
          if ((*(byte *)((uint3)uVar9 + 0x304000) & 4) == 0) {
            if ((((*(byte *)((uint3)uVar9 + 0x304000) & 2) == 0) &&
                ((*(byte *)((uint3)uVar9 + 0x304000) & 0x20) == 0)) && ((bRam30172e & 2) != 0)) {
              uVar5 = (ushort)bVar8 * 2 + 0x229c;
              *(short *)((uint3)uVar5 + 0x308000) = *(short *)((uint3)uVar5 + 0x308000) + 1;
              *(byte *)((uint3)uVar9 + 0x304000) = *(byte *)((uint3)uVar9 + 0x304000) | 0x20;
              if (0xfffd < *(ushort *)((uint3)uVar5 + 0x308000)) {
                uVar10 = (ushort)bVar8 * 2 + 0x22fc;
                *(ushort *)((uint3)uVar10 + 0x308000) = *(ushort *)((uint3)uVar10 + 0x308000) >> 1;
                *(ushort *)((uint3)uVar5 + 0x308000) = *(ushort *)((uint3)uVar5 + 0x308000) >> 1;
              }
            }
            if ((((((bRam30172f & 1) != 0) && ((*(byte *)((uint3)uVar9 + 0x304000) & 0x10) == 0)) &&
                 ((*(byte *)((uint3)uVar9 + 0x304000) & 1) != 0)) &&
                (((*(byte *)((uint3)uVar9 + 0x304000) & 8) != 0 &&
                 (*(short *)((uint3)bVar8 * 2 + 0x305458) == 0)))) && ((bRam30172e & 0x80) == 0)) {
              uVar5 = (ushort)bVar8 * 2 + 0x22fc;
              *(short *)((uint3)uVar5 + 0x308000) = *(short *)((uint3)uVar5 + 0x308000) + 1;
              *(byte *)((uint3)uVar9 + 0x304000) = *(byte *)((uint3)uVar9 + 0x304000) | 0x10;
              if (0xfffd < *(ushort *)((uint3)uVar5 + 0x308000)) {
                *(ushort *)((uint3)uVar5 + 0x308000) = *(ushort *)((uint3)uVar5 + 0x308000) >> 1;
                uVar9 = (ushort)bVar8 * 2 + 0x229c;
                *(ushort *)((uint3)uVar9 + 0x308000) = *(ushort *)((uint3)uVar9 + 0x308000) >> 1;
              }
            }
          }
          bVar8 = bVar8 + 1;
        } while (bVar8 < 0x18);
      }
      sRam305496 = _obd_denominator_ctr;
      sRam305498 = _obd_ign_cycle_ctr;
      bVar8 = 1;
      uVar4 = uRam302c6e;
      do {
        bRam301730 = bRam301730 & 0xfd;
        uVar9 = 0;
        do {
          if ((*(byte *)((uint3)*(ushort *)((uint3)(uVar9 << 2) + 0x16d4e) +
                        (uint3)*(ushort *)((uint3)(uVar9 << 2) + 0x16d50) * 0x10000) & bVar8) != 0)
          {
            uVar5 = in_r1;
            uVar10 = unaff_r8;
            if ((bRam301730 & 2) == 0) {
              bRam301730 = bRam301730 | 2;
              uVar5 = uVar9;
              uVar10 = 0xffff;
            }
            uVar3 = uVar9 << 1;
            uRam302c6e = uVar4;
            uVar7 = FUN_042c1c(*(undefined2 *)((uint3)uVar3 + 0x30a2fc),0x2005,
                               *(undefined2 *)((uint3)uVar3 + 0x30a29c));
            in_r1 = uVar9;
            unaff_r8 = uVar7;
            uVar4 = uRam302c6e;
            if (((uVar10 <= uVar7) && (in_r1 = uVar5, unaff_r8 = uVar10, uVar7 == uVar10)) &&
               (in_r1 = uVar9,
               *(ushort *)((uint3)uVar3 + 0x30a29c) <=
               *(ushort *)((uint3)((uVar5 & 0xff) << 1) + 0x30a29c))) {
              in_r1 = uVar5;
            }
          }
          uRam302c6e._2_2_ = (undefined2)((uint)uVar4 >> 0x10);
          uRam302c6e._0_2_ = (undefined2)uVar4;
          bVar2 = (char)uVar9 + 1;
          uVar9 = (ushort)bVar2;
        } while (bVar2 < 0x18);
        if (bVar8 == 1) {
          if ((bRam301730 & 2) == 0) {
            uRam30549a = 0;
            uRam305488 = 0;
            uRam3049d4 = 0;
          }
          else {
            uVar9 = (in_r1 & 0xff) << 1;
            uRam30549a = *(undefined2 *)((uint3)uVar9 + 0x30a2fc);
            uRam305488 = *(undefined2 *)((uint3)uVar9 + 0x30a29c);
            uRam3049d4 = *(undefined1 *)((uint3)(in_r1 & 0xff) + 0x14487);
          }
        }
        else if (bVar8 == 2) {
          if ((bRam301730 & 2) == 0) {
            uRam30549c = 0;
            uRam30548a = 0;
            uRam3049d5 = 0;
          }
          else {
            uVar9 = (in_r1 & 0xff) << 1;
            uRam30549c = *(undefined2 *)((uint3)uVar9 + 0x30a2fc);
            uRam30548a = *(undefined2 *)((uint3)uVar9 + 0x30a29c);
            uRam3049d5 = *(undefined1 *)((uint3)(in_r1 & 0xff) + 0x14487);
          }
        }
        else if (bVar8 == 4) {
          if ((bRam301730 & 2) == 0) {
            uRam3054a2 = 0;
            uRam305490 = 0;
            uRam3049d8 = 0;
          }
          else {
            uVar9 = (in_r1 & 0xff) << 1;
            uRam3054a2 = *(undefined2 *)((uint3)uVar9 + 0x30a2fc);
            uRam305490 = *(undefined2 *)((uint3)uVar9 + 0x30a29c);
            uRam3049d8 = *(undefined1 *)((uint3)(in_r1 & 0xff) + 0x14487);
          }
        }
        else if (bVar8 == 8) {
          if ((bRam301730 & 2) == 0) {
            uRam3054a4 = 0;
            uRam305492 = 0;
            uRam3049d9 = 0;
          }
          else {
            uVar9 = (in_r1 & 0xff) << 1;
            uRam3054a4 = *(undefined2 *)((uint3)uVar9 + 0x30a2fc);
            uRam305492 = *(undefined2 *)((uint3)uVar9 + 0x30a29c);
            uRam3049d9 = *(undefined1 *)((uint3)(in_r1 & 0xff) + 0x14487);
          }
        }
        else if (bVar8 == 0x10) {
          if ((bRam301730 & 2) == 0) {
            uRam3054a0 = 0;
            uRam30548e = 0;
            uRam3049d7 = 0;
          }
          else {
            uVar9 = (in_r1 & 0xff) << 1;
            uRam3054a0 = *(undefined2 *)((uint3)uVar9 + 0x30a2fc);
            uRam30548e = *(undefined2 *)((uint3)uVar9 + 0x30a29c);
            uRam3049d7 = *(undefined1 *)((uint3)(in_r1 & 0xff) + 0x14487);
          }
        }
        else if (bVar8 == 0x20) {
          if ((bRam301730 & 2) == 0) {
            uRam30549e = 0;
            uRam30548c = 0;
            uRam3049d6 = 0;
          }
          else {
            uVar9 = (in_r1 & 0xff) << 1;
            uRam30549e = *(undefined2 *)((uint3)uVar9 + 0x30a2fc);
            uRam30548c = *(undefined2 *)((uint3)uVar9 + 0x30a29c);
            uRam3049d6 = *(undefined1 *)((uint3)(in_r1 & 0xff) + 0x14487);
          }
        }
        else if (bVar8 == 0x40) {
          if ((bRam301730 & 2) == 0) {
            uRam3054a6 = 0;
            uRam305494 = 0;
            uRam3049da = 0;
          }
          else {
            uVar9 = (in_r1 & 0xff) << 1;
            uRam3054a6 = *(undefined2 *)((uint3)uVar9 + 0x30a2fc);
            uRam305494 = *(undefined2 *)((uint3)uVar9 + 0x30a29c);
            uRam3049da = *(undefined1 *)((uint3)(in_r1 & 0xff) + 0x14487);
          }
        }
        bVar8 = bVar8 << 1;
      } while (bVar8 < 0x41);
      return;
    }
    MDL = (ushort)bVar8 * 0x66;
    MDH = 0;
    MDC = MDC | 0x10;
    if (((((*(ushort *)((uint3)MDL + 0x30a4e6) & 0x4000) == 0) &&
         (*(short *)((uint3)MDL + 0x30a4e8) != 0)) && (9 < *(byte *)((uint3)MDL + 0x30a4ed))) &&
       (*(byte *)((uint3)MDL + 0x30a4ed) < 0xd)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (bVar1) {
      uVar9 = *(ushort *)((uint3)MDL + 0x30a4e6);
      if ((uVar9 & 0x4000) == 0) {
        if (*(short *)((uint3)MDL + 0x30a4e8) == 0) {
          uVar9 = 0;
          goto LAB_0af15a;
        }
        uVar9 = *(ushort *)((uint3)MDL + 0x30a4f0);
        if ((uVar9 & 1) == 0) goto LAB_0af15a;
        bVar1 = true;
      }
      else {
LAB_0af15a:
        bVar1 = false;
      }
      if (bVar1) {
        func_0x0bd410(bVar8,uVar9);
      }
    }
    bVar8 = bVar8 + 1;
  } while( true );
}


// ================= torque_request_arbiter @ 04ebfe =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CONTROL: torque-request min/max arbiter in 0x31Dxxx/0x31Exxx torque RAM: clamps word_304F2C vs
   coordinator setpoint 31E43C -> 31DAC8; below rpm gate byte_12A12*40 vs word_F410 -> bset
   word_FD1E.9 + default byte_12D63<<8, else min-select 31E5B4/31E5AE/31E5B2 -> 31DAC6, 31DAC4 [C
   mechanism; arbiter identity I] */

undefined4 torque_request_arbiter(void)

{
  bool bVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  
  uRam301ac8 = uRam304f2c;
  if (uRam30643c <= uRam304f2c) {
    uRam301ac8 = uRam30243c;
  }
  if (nmot_w < ((ushort)bRam012a12 * 4 + (ushort)bRam30134a) * 0x28) {
    DAT_00fd1e = DAT_00fd1e | 0x200;
    uVar3 = (ushort)bRam012d63 << 8;
    uVar4 = uVar3;
    uRam301ac6 = uVar3;
  }
  else {
    DAT_00fd1e = DAT_00fd1e & 0xfdff;
    uVar3 = uRam3025ae;
    if (((bRam301272 & 1) != 0) && (uVar3 = uRam3025b2, uRam3025ae <= uRam3025b2)) {
      uVar3 = uRam3025ae;
    }
    uVar4 = uRam3025b4;
    uRam301ac6 = uRam3025b4;
    if (uVar3 < uRam3025b4) {
      uRam301ac6 = uVar3;
    }
  }
  uRam301ac4 = uRam30243c;
  if (uVar4 <= uRam30243c) {
    uRam301ac4 = uVar4;
  }
  uVar4 = uRam30257e;
  if (uRam30257e <= uRam301ac4) {
    uVar4 = uRam301ac4;
  }
  uVar2 = uRam301960;
  if (uRam301960 <= uVar4) {
    uVar2 = uVar4;
  }
  if (uVar2 <= uVar3) {
    uVar3 = uVar2;
  }
  uVar4 = uRam30512c;
  if (uVar3 <= uRam30512c) {
    uVar4 = uVar3;
  }
  uRam301ad0 = uVar4;
  if (((bRam012a10 & 1) != 0) && (uRam301ad0 = uRam304f3c, uVar4 <= uRam304f3c)) {
    uRam301ad0 = uVar4;
  }
  uRam301acc = uRam302484;
  if (uRam301ad0 <= uRam302484) {
    uRam301acc = uRam301ad0;
  }
  if ((bRam301272 & 4) == 0) {
    uRam301ad0 = uRam301acc;
  }
  if ((uRam3025ac < uRam301ac8) ||
     ((uRam301acc == uRam3025ae && (uRam3025ae < (ushort)bRam012d63 * 0x100)))) {
    DAT_00fd1e = DAT_00fd1e | 0x400;
  }
  else {
    DAT_00fd1e = DAT_00fd1e & 0xfbff;
  }
  if (uRam301ac4 < uRam30257e) {
    DAT_00fd1e = DAT_00fd1e | 0x2000;
  }
  else {
    DAT_00fd1e = DAT_00fd1e & 0xdfff;
  }
  if ((uRam301960 == 0) && (uRam3025b4 == 0)) {
    uRam00fd20 = uRam00fd20 | 1;
  }
  else {
    uRam00fd20 = uRam00fd20 & 0xfffe;
  }
  if (((uRam00fd20 & 1) == 0) && (uRam301960 <= uRam301ac4)) {
    DAT_00fd1e = DAT_00fd1e & 0x7fff;
  }
  else {
    DAT_00fd1e = DAT_00fd1e | 0x8000;
  }
  if (((DAT_00fd1e & 0x2000) == 0) && ((DAT_00fd1e & 0x8000) == 0)) {
    DAT_00fd1e = DAT_00fd1e & 0xbfff;
  }
  else {
    DAT_00fd1e = DAT_00fd1e | 0x4000;
  }
  if (((DAT_00fd1e & 0x4000) == 0) && (uRam301ac8 <= uRam301acc)) {
    DAT_00fd1e = DAT_00fd1e & 0xf7ff;
  }
  else {
    DAT_00fd1e = DAT_00fd1e | 0x800;
  }
  uVar3 = (uRam3029b6 >> 1) - (uRam301ad4 >> 1);
  if (uRam3029b6 >> 1 < uRam301ad4 >> 1) {
    if ((short)uVar3 >= 0) {
      uVar3 = 0x8000;
    }
  }
  else if ((short)uVar3 < 0) {
    uVar3 = 0x7fff;
  }
  uRam301ac2 = uVar3;
  uRam301ad2 = uRam301acc;
  if (uRam3029b6 <= uRam301acc) {
    uRam301ad2 = uRam3029b6;
  }
  uVar4 = uVar3;
  if ((((uRam00fd7e & 0x400) == 0) && ((uRam00fd20 & 0x1000) != 0)) && (cRam3012f8 == '\0')) {
    cRam3012f8 = cRam012a13;
    uVar4 = CONCAT11((char)(uVar3 >> 8),cRam012a13);
  }
  bVar1 = cRam3012f8 != '\0';
  if (bVar1) {
    cRam3012f8 = cRam3012f8 + -1;
  }
  if ((((sRam30526c == 0) && (uVar4 = uRam302e3a, uRam302e3a == 0)) && (_mres_request == 0)) &&
     ((((_flags_idle_state & 0x200) == 0 && ((_flags_idle_state & 0x4000) == 0)) ||
      (cRam304785 == '\0')))) {
    if ((bRam012a0f & 1) == 0) {
      PSW = PSW & 0xffbf;
    }
    else if (sRam301abe == sRam301ade) {
      PSW = PSW | 0x40;
    }
    else {
      PSW = PSW & 0xffbf;
    }
    if ((PSW & 0x40) != 0) goto LAB_04ee04;
    uRam00fd20 = uRam00fd20 & 0xfffb;
  }
  else {
LAB_04ee04:
    uRam00fd20 = uRam00fd20 | 4;
  }
  if (((((DAT_00fd1e & 2) == 0) && ((uRam00fd1c & 0x200) == 0)) && ((DAT_00fd1a & 0x4000) == 0)) &&
     (((DAT_00fd1e & 8) == 0 || ((bRam012a0e & 0x40) == 0)))) {
    uRam00fd20 = uRam00fd20 & 0xfff7;
  }
  else {
    uRam00fd20 = uRam00fd20 | 8;
  }
  if ((flags_torque_revlimit & 0x100) == 0) {
LAB_04ee4c:
    if (bVar1) goto LAB_04ee50;
    uRam00fd20 = uRam00fd20 & 0xffef;
  }
  else {
    if ((bRam012a0e & 1) == 0) {
      if ((bRam012a0e & 4) != 0) {
        uVar2 = _rl_w - uRam302492;
        if (_rl_w < uRam302492) {
          uVar2 = 0;
        }
        uVar4 = (ushort)bRam012a11;
        if (uVar2 <= uVar4) goto LAB_04ee50;
      }
      goto LAB_04ee4c;
    }
LAB_04ee50:
    uRam00fd20 = uRam00fd20 | 0x10;
  }
  if (((uRam00fd66 & 0x20) == 0) && ((uRam00fd1c & 0x2000) == 0)) {
    uRam00fd20 = uRam00fd20 & 0xfeff;
  }
  else {
    uRam00fd20 = uRam00fd20 | 0x100;
  }
  if ((uRam301960 == 0) || (uRam301ad0 != uRam301960)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (uRam305aea < uRam30512c) {
    uRam00fd20 = uRam00fd20 & 0xfffd;
  }
  else if (uRam301ad0 == uRam30512c) {
    uRam00fd20 = uRam00fd20 | 2;
  }
  if (((bVar1) || (uRam301ad0 == uRam30243c)) || (uRam301ad0 == uRam3025b4)) {
    PSW = PSW & 0xffbf;
  }
  else {
    PSW = PSW | 0x40;
  }
  if (((((uRam00fd20 & 4) == 0) && ((uRam00fd20 & 8) == 0)) &&
      (((uRam00fd20 & 0x10) == 0 && (((uRam00fd20 & 0x100) == 0 && ((uRam00fd20 & 2) == 0)))))) &&
     ((PSW & 0x40) == 0)) {
    uRam00fd20 = uRam00fd20 & 0xff3f;
  }
  else {
    uRam00fd20 = uRam00fd20 & 0xffbf | PSW & 0x40 | 0x80;
  }
  uVar2 = uRam30512c;
  if (((bVar1) || (uRam301ad0 == uRam3025b4)) || (uVar2 = uRam3025b4, uRam3025b4 < uRam301aea)) {
    uRam00fd20 = uRam00fd20 | 0x20;
  }
  else {
    uRam00fd20 = uRam00fd20 & 0xffdf;
  }
  if (((uRam00fd20 & 0x80) == 0) && ((uRam00fd20 & 0x20) == 0)) {
    uRam00fd20 = uRam00fd20 & 0xf7ff;
  }
  else {
    uRam00fd20 = uRam00fd20 | 0x800;
  }
  if ((uRam00fd20 & 0x800) == 0) {
LAB_04ef0c:
    if (((uRam3029b6 < uRam301aea) || (((uRam00fd20 & 0x4000) != 0 && ((DAT_00fd4e & 8) != 0)))) &&
       ((uRam3029b6 < uRam301acc ||
        (((bRam301272 & 2) == 0 || (uVar2 = bRam012a0e & 0x20, (bRam012a0e & 0x20) == 0)))))) {
      if ((short)uVar3 < 0) {
        uRam00fd20 = uRam00fd20 | 0x2000;
      }
      goto LAB_04ef3e;
    }
  }
  else {
    uVar2 = uRam301ad0;
    if (uRam301ad0 < uRam301afc) {
      uVar2 = uRam301afc;
    }
    if (uRam3029b6 < uVar2) goto LAB_04ef0c;
  }
  uRam00fd20 = uRam00fd20 & 0xdfff;
  uVar3 = uVar2;
LAB_04ef3e:
  if (((flags_torque_revlimit & 0x80) == 0) && ((uRam00fd20 & 0x2000) != 0)) {
    DAT_00fd1e = DAT_00fd1e | 0x1000;
  }
  else {
    DAT_00fd1e = DAT_00fd1e & 0xefff;
  }
  if (((DAT_00fd1e & 0x1000) == 0) || ((DAT_00fd4e & 0x10) == 0)) {
    bRam3012f9 = 0;
    uRam00fd20 = uRam00fd20 & 0xfbff | ((uRam00fd20 & 0x800) >> 0xb) << 10;
  }
  else {
    if (bRam3012f9 < bRam012a14) {
      bRam3012f9 = bRam3012f9 + 1;
    }
    if (((uRam00fd20 & 0x800) == 0) && (bRam3012f9 < bRam012a14)) {
      PSW = PSW & 0xffbf;
    }
    else {
      PSW = PSW | 0x40;
    }
    uVar3 = CONCAT11((char)(uVar3 >> 8),bRam3012f9);
    uRam00fd20 = uRam00fd20 & 0xfbff | ((PSW & 0x40) >> 6) << 10;
  }
  uRam301aca = uRam301ad0;
  if ((((uRam00fd20 & 0x80) == 0) && ((uRam00fd20 & 0x20) != 0)) &&
     (uRam301aca = uRam3025b4, uRam3025b4 <= uRam301ad0)) {
    uRam301aca = uRam301ad0;
  }
  uRam00fd20 = uRam00fd20 & 0xefff | ((uRam00fd7e & 0x400) >> 10) << 0xc;
  return CONCAT22(uVar4,uVar3);
}


// ================= measlist_copy_1 @ 064180 =================

/* WARNING: Type propagation algorithm not settling */
/* cal-defined RAM-snapshot copy list 1: enables byte_17F69, count byte_17F68 clamp 10, address
   table 0x17F6A -> buffer 0xA63A page 0xC2, id 5 [C mechanism; DAQ identity I] */

byte measlist_copy_1(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  
  if ((s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_017cac[0x2bd] & 1U) == 0) {
    return s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_017cac[0x2bd] & 1;
  }
  uVar3 = (ushort)(byte)s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_017cac[700];
  if (10 < uVar3) {
    uVar3 = 10;
  }
  uVar2 = 0xa63a;
  uVar1 = (short)s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_017cac + 0x2be;
  while( true ) {
    if (uVar3 + 0xa63a <= uVar2) {
      uRam303ffc = 5;
      uRam303ff6 = 5;
      return 5;
    }
    if (((*(ushort *)((uint3)uVar1 + 0x10000) & 1) != 0) ||
       (*(short *)((char *)&ram0x00ce36 +
                  (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                        (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                              (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                                    (uint3)uVar1 + 0x72a)))) !=
        *(short *)((uint3)uVar1 + 0x10000) + 1)) break;
    *(undefined2 *)((uint3)uVar2 + 0x10000) =
         *(undefined2 *)((uint3)*(ushort *)((uint3)uVar1 + 0x10000) + 0x10000);
    uVar2 = uVar2 + 2;
    uVar1 = uVar1 + 4;
  }
  for (; uVar2 < uVar3 + 0xa63a; uVar2 = uVar2 + 1) {
    *(undefined1 *)((uint3)uVar2 + 0x10000) =
         *(undefined1 *)((uint3)*(ushort *)((uint3)uVar1 + 0x10000) + 0x10000);
    uVar1 = uVar1 + 2;
  }
  uRam303ff6 = 5;
  uRam303ffc = 5;
  return 5;
}


// ================= measlist_copy_2 @ 0641ea =================

/* WARNING: Type propagation algorithm not settling */
/* cal-defined RAM-snapshot copy list 2: byte_17F7F/byte_17F7E clamp 26, table 0x17F80 -> 0xA644
   page 0xC2, id 2; called 0xB6C8/0xB812 [C mechanism; DAQ identity I] */

byte measlist_copy_2(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  
  if ((bRam017f7f & 1) == 0) {
    return bRam017f7f & 1;
  }
  uVar3 = (ushort)bRam017f7e;
  if (0x1a < uVar3) {
    uVar3 = 0x1a;
  }
  uVar2 = 0xa644;
  uVar1 = 0x7f80;
  while( true ) {
    if (uVar3 + 0xa644 <= uVar2) {
      uRam303ffe = 2;
      uRam303ff8 = 2;
      return 2;
    }
    if (((*(ushort *)((uint3)uVar1 + 0x10000) & 1) != 0) ||
       (*(short *)((char *)&ram0x00ce36 +
                  (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                        (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                              (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                                    (uint3)uVar1 + 0x72a)))) !=
        *(short *)((uint3)uVar1 + 0x10000) + 1)) break;
    *(undefined2 *)((uint3)uVar2 + 0x10000) =
         *(undefined2 *)((uint3)*(ushort *)((uint3)uVar1 + 0x10000) + 0x10000);
    uVar2 = uVar2 + 2;
    uVar1 = uVar1 + 4;
  }
  for (; uVar2 < uVar3 + 0xa644; uVar2 = uVar2 + 1) {
    *(undefined1 *)((uint3)uVar2 + 0x10000) =
         *(undefined1 *)((uint3)*(ushort *)((uint3)uVar1 + 0x10000) + 0x10000);
    uVar1 = uVar1 + 2;
  }
  uRam303ff8 = 2;
  uRam303ffe = 2;
  return 2;
}


// ================= measlist_copy_3 @ 064256 =================

/* WARNING: Type propagation algorithm not settling */
/* cal-defined RAM-snapshot copy list 3: byte_17FB5/byte_17FB4 clamp 30, table 0x17FB6 -> 0xA65E
   page 0xC2, id 1 [C mechanism; DAQ identity I] */

byte measlist_copy_3(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  
  if ((bRam017fb5 & 1) == 0) {
    return bRam017fb5 & 1;
  }
  uVar3 = (ushort)bRam017fb4;
  if (0x1e < uVar3) {
    uVar3 = 0x1e;
  }
  uVar2 = 0xa65e;
  uVar1 = 0x7fb6;
  while( true ) {
    if (uVar3 + 0xa65e <= uVar2) {
      uRam303ffe = 1;
      uRam303ffa = 1;
      return 1;
    }
    if (((*(ushort *)((uint3)uVar1 + 0x10000) & 1) != 0) ||
       (*(short *)((char *)&ram0x00ce36 +
                  (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                        (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                              (int3)(s_DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD_000e36 +
                                    (uint3)uVar1 + 0x72a)))) !=
        *(short *)((uint3)uVar1 + 0x10000) + 1)) break;
    *(undefined2 *)((uint3)uVar2 + 0x10000) =
         *(undefined2 *)((uint3)*(ushort *)((uint3)uVar1 + 0x10000) + 0x10000);
    uVar2 = uVar2 + 2;
    uVar1 = uVar1 + 4;
  }
  for (; uVar2 < uVar3 + 0xa65e; uVar2 = uVar2 + 1) {
    *(undefined1 *)((uint3)uVar2 + 0x10000) =
         *(undefined1 *)((uint3)*(ushort *)((uint3)uVar1 + 0x10000) + 0x10000);
    uVar1 = uVar1 + 2;
  }
  uRam303ffa = 1;
  uRam303ffe = 1;
  return 1;
}


// ================= diag_kwp_localid_resp_len @ 05e7be =================

/* DIAGNOSTIC-COMMS: KWP2000 per-local-ID response-length provider, sibling of
   diag_kwp_localid_capability sub_5EB80: ID-0x81 range 0x19 (0x5E7C0 subb rl4,#81h; 0x5E7C4 cmpb
   rl4,#19h) jump table 0xC452 (0x5E7D0 add r4,#0C452h); per ID reads enable WORD in 0x1F4B0-0x1F514
   (0x5E7DC mov r4,word_1F4B4) -> nonzero returns fixed byte count 2/4/6/0xC/0x14 else 0; sole
   caller KWP positive-response builder sub_5F172 (0x5F1D8) [C] */

undefined1 diag_kwp_localid_resp_len(undefined1 param_1)

{
  undefined1 uVar1;
  
  switch(param_1) {
  case 0x81:
  case 0x82:
    if (sRam0134b4 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 6;
    }
    return uVar1;
  case 0x83:
    if (sRam0134ba == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 0x14;
    }
    return uVar1;
  case 0x84:
    if (sRam0134ce == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
    return uVar1;
  case 0x85:
    if (sRam0134d0 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
    return uVar1;
  case 0x86:
    if (sRam0134d2 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 4;
    }
    return uVar1;
  case 0x87:
    if (sRam0134d6 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 4;
    }
    return uVar1;
  case 0x88:
    if (sRam0134da == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
    return uVar1;
  case 0x89:
    if (sRam0134dc == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
    break;
  case 0x8a:
    if (sRam0134de == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 0xc;
    }
    return uVar1;
  case 0x8b:
    if (sRam0134ea == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
    return uVar1;
  case 0x8c:
    if (sRam0134ec == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
    return uVar1;
  case 0x8d:
    if (sRam0134ee == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 4;
    }
    return uVar1;
  case 0x8e:
    if (sRam0134f2 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
    return uVar1;
  case 0x8f:
    if (sRam0134f4 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 6;
    }
    return uVar1;
  case 0x90:
    if (sRam0134fa == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 6;
    }
    return uVar1;
  case 0x91:
    if (sRam013500 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 8;
    }
    return uVar1;
  case 0x92:
    if (sRam013508 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
    return uVar1;
  case 0x93:
    if (sRam01350a == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
    return uVar1;
  case 0x94:
    if (sRam0134b0 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
    return uVar1;
  case 0x95:
    if (sRam0134b2 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
    return uVar1;
  case 0x96:
    if (sRam01350c == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
    return uVar1;
  case 0x97:
    if (sRam01350e == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
    return uVar1;
  case 0x98:
    if (sRam013510 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
    return uVar1;
  case 0x99:
    if (sRam013512 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
    return uVar1;
  case 0x9a:
    if (sRam013514 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 4;
    }
    return uVar1;
  default:
    return 0;
  }
  return uVar1;
}


// ================= etc_adapt_sequencer @ 0c77de =================

/* WARNING: Removing unreachable block (ram,0x0c7cda) */
/* WARNING: Removing unreachable block (ram,0x0c7ce4) */
/* WARNING: Removing unreachable block (ram,0x0c7cea) */
/* WARNING: Removing unreachable block (ram,0x0c7ce8) */
/* WARNING: Removing unreachable block (ram,0x0c7ce2) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* ETC stop-learn precondition/sequencer state machine (entered via sub_C77DA from sub_C75C2):
   temp/condition windows from cfg_14635 band (0xC77F4 cmpb rl4(byte_30163A),byte_14658; 0xC78D2
   byte_3015D8 vs byte_14656); drift check (word_16F1A-word_302CB2)*word_302CA2 vs word_302C6C
   (0xC780C-0xC783A); own state byte_301776 + counter byte_301777 (vs byte_14647/48) + status nibble
   byte_301778; spring/return checks loc_F45E vs word_302CCA+word_16F3E/40 (0xC79D2/0xC7A2A); abort
   code byte_301775 (1-9) + word_FD6C.2 -> sub_C7D5E; success arms stop-learn gate word_FD6A.14
   (0xC7B66 bset) consumed by etc_stop_learn_adapt sub_C7EEA (etc-throttle.md 3) [C] */

void etc_adapt_sequencer(void)

{
  uint uVar1;
  byte bVar2;
  ushort uVar3;
  short sVar4;
  
  uVar1 = CONCAT22(MDH,MDL);
  if ((_flags_start_phase & 0x8000) != 0) {
    uRam00fd6a = uRam00fd6a | 0x80;
  }
  if (((((uRam00fd68 & 0x80) != 0) && (uVar1 = CONCAT22(MDH,MDL), (uRam00fd6a & 0x80) == 0)) &&
      (uVar1 = CONCAT22(MDH,MDL), (uRam00fd70 & 8) == 0)) &&
     (((uVar1 = CONCAT22(MDH,MDL), bRam014658 <= rpmclass_oppoint &&
       (uVar1 = CONCAT22(MDH,MDL), rpmclass_oppoint <= bRam014657)) &&
      (uVar1 = CONCAT22(MDH,MDL), bRam014655 <= bRam301626)))) {
    uVar3 = uRam016f1a - _servo_pot_low_learned;
    if (uRam016f1a < _servo_pot_low_learned) {
      uVar3 = 0;
    }
    uVar1 = (uint)uVar3 * (uint)_servo_pot_lin_gain;
    MDL = (undefined2)uVar1;
    MDH = (undefined2)(uVar1 >> 0x10);
    MDC = MDC | 0x10;
    sVar4 = (short)((uVar1 >> 0xb) >> 0x10);
    if (sVar4 != 0 || sVar4 == 0 && uRam302c6c < (ushort)(uVar1 >> 0xb)) {
      uRam00fd6a = uRam00fd6a & 0x87ff | 0x80;
      etc_adapt_seq_state = '\0';
      etc_adapt_seq_counter = 0;
      bRam303353 = bRam303353 & 0xfd;
      uRam00fd6c = uRam00fd6c & 0xff49 | 0x200;
      servo_adapt_state = 0;
      uRam30177a = 0;
      servo_adapt_errcode = 0;
      bRam301778 = 0x10;
      func_0x0c77da();
      uVar1 = CONCAT22(MDH,MDL);
    }
  }
  MDH = (undefined2)(uVar1 >> 0x10);
  MDL = (undefined2)uVar1;
  if ((uRam00fd6a & 0x4000) != 0) goto LAB_0c7b6e;
  if ((uRam00fd28 & 0x40) == 0) {
    if ((((uRam00fd70 & 0x80) == 0) && ((uRam00fd70 & 0x20) == 0)) && ((uRam00fd80 & 2) == 0)) {
      if (bRam014656 < vfzg_class) {
        servo_adapt_errcode = 5;
        uRam00fd6c = uRam00fd6c | 4;
      }
      else if (bRam014646 < bRam301655) {
        servo_adapt_errcode = 6;
        uRam00fd6c = uRam00fd6c | 4;
      }
      else if ((uRam00fd70 & 8) == 0) {
        if ((uRam00fd68 & 0x1000) == 0) {
          servo_adapt_errcode = 9;
          uRam00fd6c = uRam00fd6c | 4;
        }
        else if (rpmclass_oppoint < bRam014645) {
          servo_adapt_errcode = 7;
          uRam00fd6c = uRam00fd6c | 4;
        }
        else if (bRam301626 < bRam014644) {
          servo_adapt_errcode = 8;
          uRam00fd6c = uRam00fd6c | 4;
        }
      }
      else {
        servo_adapt_errcode = 4;
        uRam00fd6c = uRam00fd6c | 4;
      }
    }
    else {
      servo_adapt_errcode = 1;
      uRam00fd6c = uRam00fd6c | 4;
    }
  }
  else if ((((uRam00fd70 & 0x20) == 0) && ((uRam00fd80 & 2) == 0)) &&
          (((uRam00fd6c & 0x8000) == 0 || ((uRam00fd6e & 0x10) == 0)))) {
    if ((uRam00fd70 & 8) == 0) {
      if ((uRam00fd68 & 0x1000) == 0) {
        servo_adapt_errcode = 9;
        uRam00fd6c = uRam00fd6c | 4;
      }
    }
    else {
      servo_adapt_errcode = 4;
      uRam00fd6c = uRam00fd6c | 4;
    }
  }
  else {
    servo_adapt_errcode = 1;
    uRam00fd6c = uRam00fd6c | 4;
  }
  if ((uRam00fd6c & 4) != 0) {
    bRam301778 = bRam301778 | 0x40;
    func_0x0c7d5e();
    uVar1 = CONCAT22(MDH,MDL);
    goto LAB_0c7b6e;
  }
  if (etc_adapt_seq_state == '\0') {
    sRam302cc8 = uRam016f4a + uRam302cca;
    if (uRam016f4a + uRam302cca < uRam016f4a || uRam016f4a + uRam302cca < uRam302cca) {
      sRam302cc8 = -1;
    }
    uRam00fd6a = uRam00fd6a | 0x110;
    etc_adapt_seq_state = '\x01';
    etc_adapt_seq_counter = etc_adapt_seq_counter + 1;
    bRam301778 = bRam301778 & 0xf0 | 1;
    goto LAB_0c7b6e;
  }
  if (etc_adapt_seq_state == '\x01') {
    if (etc_adapt_seq_counter < bRam014647) {
      etc_adapt_seq_counter = etc_adapt_seq_counter + 1;
      bVar2 = bRam301778 & 0xf0;
      bRam301778 = bVar2 | 3;
      sVar4 = (uRam302cca >> 4) + (uRam016f3e >> 4);
      if (sVar4 == _throttle_pos_fb ||
          sVar4 - _throttle_pos_fb < 0 != (_throttle_pos_fb < 0 && sVar4 - _throttle_pos_fb < 0)) {
        uRam00fd6a = uRam00fd6a | 8;
        etc_adapt_seq_state = '\x02';
        bRam301778 = bVar2 | 4;
      }
    }
    else {
      uRam00fd6c = uRam00fd6c | 1;
      bRam301778 = bRam301778 | 0x20;
      func_0x0c7d5e();
      uVar1 = CONCAT22(MDH,MDL);
    }
    goto LAB_0c7b6e;
  }
  if (etc_adapt_seq_state == '\x02') {
    if (etc_adapt_seq_counter < bRam014648) {
      sVar4 = (uRam302cca >> 4) + (uRam016f40 >> 4);
      if (sVar4 == _throttle_pos_fb ||
          sVar4 - _throttle_pos_fb < 0 != (_throttle_pos_fb < 0 && sVar4 - _throttle_pos_fb < 0)) {
        etc_adapt_seq_counter = etc_adapt_seq_counter + 1;
      }
      else {
        uRam00fd6a = uRam00fd6a & 0xfeff;
        if ((((DAT_00fd4e & 0x100) == 0) && ((uRam00fd6c & 0x400) == 0)) && ((bRam303353 & 2) != 0))
        {
          etc_adapt_seq_state = '\x04';
          uRam00fd6c = uRam00fd6c | 2;
        }
        else {
          bRam301778 = bRam301778 & 0xf0 | 2;
          etc_adapt_seq_state = '\x03';
          uRam00fd6c = uRam00fd6c | 2;
        }
      }
    }
    else {
      uRam00fd6c = uRam00fd6c | 1;
      uRam00fd6a = uRam00fd6a | 0x8000;
      bRam301778 = bRam301778 | 0x20;
      func_0x0c7d5e();
      uVar1 = CONCAT22(MDH,MDL);
    }
    goto LAB_0c7b6e;
  }
  if (etc_adapt_seq_state != '\x03') {
    if (etc_adapt_seq_state == '\x04') {
      uRam00fd6a = uRam00fd6a & 0xffe7 | 0x4000;
      sRam302cc8 = 0;
      uRam00fd6c = uRam00fd6c & 0xfbff;
    }
    goto LAB_0c7b6e;
  }
  if (bRam30177b < bRam01464f) {
    bRam30177b = bRam30177b + 1;
    goto LAB_0c7b6e;
  }
  if (bRam30177b == bRam01464f) {
    uRam302cac = _adc_ch1_raw;
    uRam302cae = _adc_ch2_raw;
  }
  bVar2 = bRam01464f + bRam014650;
  if ((byte)(bRam01464f + bRam014650) < bRam01464f || (byte)(bRam01464f + bRam014650) < bRam014650)
  {
    bVar2 = 0xff;
  }
  if (bRam30177b < bVar2) {
    uRam302cac = uRam302cac + _adc_ch1_raw >> 1;
    uRam302cae = uRam302cae + _adc_ch2_raw >> 1;
    bRam30177b = bRam30177b + 1;
    goto LAB_0c7b6e;
  }
  uVar3 = uRam303c40 - uRam016f00;
  if (uRam303c40 < uRam016f00) {
    uVar3 = 0;
  }
  if (uRam302cac < uVar3) {
LAB_0c7afc:
    uRam00fd6c = uRam00fd6c | 0x200;
    bRam303353 = bRam303353 & 0xfd;
    uRam302cca = uRam016f44;
    bRam301778 = bRam301778 | 0x10;
  }
  else {
    uVar3 = uRam016efe + uRam303c40;
    if (uRam016efe + uRam303c40 < uRam016efe || uRam016efe + uRam303c40 < uRam303c40) {
      uVar3 = 0xffff;
    }
    if (uVar3 < uRam302cac) goto LAB_0c7afc;
    uVar3 = uRam303c42 - uRam016efe;
    if (uRam303c42 < uRam016efe) {
      uVar3 = 0;
    }
    if (uRam302cae < uVar3) goto LAB_0c7afc;
    uVar3 = uRam016f00 + uRam303c42;
    if (uRam016f00 + uRam303c42 < uRam016f00 || uRam016f00 + uRam303c42 < uRam303c42) {
      uVar3 = 0xffff;
    }
    if (uVar3 < uRam302cae) goto LAB_0c7afc;
    uRam302cca = uRam303c4e;
    func_0x0c7d7c();
    uVar1 = CONCAT22(MDH,MDL);
  }
  bRam30177b = 0;
  etc_adapt_seq_state = '\x04';
  uRam00fd6c = uRam00fd6c & 0xfbff;
LAB_0c7b6e:
  MDH = (undefined2)(uVar1 >> 0x10);
  MDL = (undefined2)uVar1;
  if (cRam014642 == '\0') {
    if (((uRam00fd6c & 0x20) != 0) && (9 < servo_adapt_state)) {
      bRam301778 = bRam301778 & 0xf0 | 8;
      uRam00fd6a = uRam00fd6a | 0x1800;
    }
  }
  else if ((((uRam00fd6c & 0x20) != 0) && (9 < servo_adapt_state)) && ((uRam00fd6a & 0x1000) == 0))
  {
    if ((uRam00fd28 & 0x40) == 0) {
      if (((((uRam00fd70 & 0x80) == 0) && ((uRam00fd70 & 0x20) == 0)) && ((uRam00fd80 & 2) == 0)) &&
         ((uRam00fd70 & 8) == 0)) {
        if (bRam014656 < vfzg_class) {
          servo_adapt_errcode = 0x2c;
          uRam00fd6a = uRam00fd6a | 0x2000;
        }
        else if (bRam014646 < bRam301655) {
          servo_adapt_errcode = 0x2d;
          uRam00fd6a = uRam00fd6a | 0x2000;
        }
        else if (rpmclass_oppoint < bRam014645) {
          servo_adapt_errcode = 0x2e;
          uRam00fd6a = uRam00fd6a | 0x2000;
        }
        else if (bRam301626 < bRam014644) {
          servo_adapt_errcode = 0x2f;
          uRam00fd6a = uRam00fd6a | 0x2000;
        }
      }
      else {
        servo_adapt_errcode = 0x28;
        uRam00fd6a = uRam00fd6a | 0x2000;
      }
    }
    else if ((((uRam00fd6c & 0x8000) != 0) && ((uRam00fd6e & 0x10) != 0)) ||
            (((uRam00fd70 & 0x20) != 0 || (((uRam00fd80 & 2) != 0 || ((uRam00fd70 & 8) != 0)))))) {
      servo_adapt_errcode = 0x28;
      uRam00fd6a = uRam00fd6a | 0x2000;
    }
    if ((uRam00fd6a & 0x2000) != 0) {
      bRam301778 = bRam301778 | 0x40;
      func_0x0c7d4e();
      return;
    }
    if (etc_adapt_seq_state == '\x04') {
      sRam302cc8 = uRam016f4c;
      uRam00fd6a = uRam00fd6a | 0x110;
      etc_adapt_seq_state = 5;
      etc_adapt_seq_counter = 1;
      bRam301778 = bRam301778 & 0xf0 | 7;
      return;
    }
    if (etc_adapt_seq_state == '\x05') {
      if (bRam014649 <= etc_adapt_seq_counter) {
        uRam00fd6a = uRam00fd6a | 0x400;
        bRam301778 = bRam301778 | 0x20;
        func_0x0c7d4e();
        return;
      }
      etc_adapt_seq_counter = etc_adapt_seq_counter + 1;
      if ((_throttle_pos_fb - sRam016f3c < 0 ==
           (_throttle_pos_fb < 0 != sRam016f3c < 0 &&
           _throttle_pos_fb - sRam016f3c < 0 != _throttle_pos_fb < 0)) &&
         (_throttle_pos_fb == sRam016f3a ||
          _throttle_pos_fb - sRam016f3a < 0 !=
          (_throttle_pos_fb < 0 != sRam016f3a < 0 &&
          _throttle_pos_fb - sRam016f3a < 0 != _throttle_pos_fb < 0))) {
        uRam00fd6a = uRam00fd6a | 8;
        etc_adapt_seq_state = 6;
        return;
      }
    }
    else if (etc_adapt_seq_state == '\x06') {
      if (bRam01464a <= etc_adapt_seq_counter) {
        uRam00fd6a = uRam00fd6a | 0x600;
        bRam301778 = bRam301778 | 0x20;
        func_0x0c7d4e();
        return;
      }
      sVar4 = (uRam302cca >> 4) - sRam016f38;
      if (sRam016f38 < 0 && (short)((uRam302cca >> 4) - sRam016f38) < 0) {
        sVar4 = -0x8000;
      }
      if (sVar4 - _throttle_pos_fb < 0 ==
          (sVar4 < 0 != _throttle_pos_fb < 0 && sVar4 - _throttle_pos_fb < 0 != sVar4 < 0)) {
        etc_adapt_seq_counter = etc_adapt_seq_counter + 1;
      }
      else {
        uRam00fd6a = uRam00fd6a & 0xfee7 | 0x1800;
        sRam302cc8 = 0;
        bRam301778 = bRam301778 & 0xf0 | 8;
      }
      uRam00fd28 = uRam00fd28 & 0xffbf;
      return;
    }
  }
  return;
}


// ================= can_msgobj_reinit @ 057eba =================

/* COMMS: CAN message-object reinit/recovery driver (callers=2): gated by sub_E356A flag, resets CAN
   controller msg-obj control regs 0xEF00/0xEE00 (bset .6) + 0xEF03/0xEE03 (0x57ECA-0x57F06);
   per-channel down-counts loc_F526/loc_F526+1, and when <3 calls two cal-held far-code hooks via
   push-rets trampoline sub_8E52 (r12=#1B08h ch1 word_11B3A/3C, r12=#1B58h ch2 word_11B8A/8C; retry
   word_11B22/24, word_11B72/74), sets word_30256C|=0x80 on give-up and bit1 of far ptrs
   word_11B0C/11B5C [C] */

void can_msgobj_reinit(void)

{
  char cVar1;
  
  cVar1 = func_0x0e356a();
  if (cVar1 != '\0') {
    bRam01ef03 = bRam01ef03 & 0xf9;
    bRam01ee03 = bRam01ee03 & 0xf9;
    bRam01ef00 = bRam01ef00 & 0x8f;
    bRam01ee00 = bRam01ee00 & 0x8f;
    while ((bRam00f526 < 3 && (cVar1 = FUN_008e52(0x1b08), cVar1 == '\0'))) {
      bRam00f526 = bRam00f526 + 1;
    }
    if (bRam00f526 < 3) {
      FUN_008e52(0x1b08);
      if ((uRam303b34 & 1) == 0) {
        *(byte *)((uint3)uRam011b0c + 0x10000) = *(byte *)((uint3)uRam011b0c + 0x10000) | 2;
        uRam30143d = 0;
      }
    }
    else {
      uRam30256c = uRam30256c | 0x80;
    }
    while ((bRam00f527 < 3 && (cVar1 = FUN_008e52(7000), cVar1 == '\0'))) {
      bRam00f527 = bRam00f527 + 1;
    }
    if (bRam00f527 < 3) {
      FUN_008e52(7000);
      if ((uRam303b34 & 1) == 0) {
        *(byte *)((uint3)uRam011b5c + 0x10000) = *(byte *)((uint3)uRam011b5c + 0x10000) | 2;
        uRam30143d = 0;
      }
      return;
    }
  }
  uRam30256c = uRam30256c | 0x80;
  return;
}


// ================= ebox_temp_sensor_lin @ 030274 =================

/* CONTROL: E-Box (ECU) temperature-sensor linearization: reads the 'Characteristic line for E-Box
   temperature sensor' curve (cfg_1D0D8_ebox_curve_count, x@0x1D0DA y@0x1D0FE) via sub_4272A over
   word_301944/word_303BFE -> byte_30400B (0x302BC movb byte_30400B,rl6), then cmpb vs threshold
   byte_1805D (0x302C4) [C dict-anchored; over-temp gating role I] */

void ebox_temp_sensor_lin(void)

{
  bool bVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uStack_a;
  ushort uStack_8;
  ushort uStack_6;
  
  uVar3 = uRam303bfe;
  uVar2 = uRam303bfc;
  uStack_a = uRam303bfa;
  uStack_8 = uRam303bfc;
  uStack_6 = uRam303bfe;
  bRam30400b = func_0x04272a(uRam01d0d8,0x10da,7,0x10fe,7,uRam301944);
  if (bRam30400b < bRam01805d) {
    bRam01fca9 = '\0';
LAB_0302fe:
    bVar1 = false;
  }
  else {
    if (bRam01fca9 < bRam018058) {
      bRam01fca9 = bRam01fca9 + 1;
      goto LAB_0302fe;
    }
    bRam01fca9 = -1;
    bVar1 = true;
  }
  if (bVar1) {
    if ((uStack_a & 0xf00) == 0x200) {
      uStack_a = uStack_a & 0xf0fe;
    }
    uStack_a = (uStack_a >> 8 & 0x9f | 0x60) << 8 | 2;
  }
  if (bRam01805c < bRam30400b) {
    bRam01fcab = '\0';
LAB_030376:
    bVar1 = false;
  }
  else {
    if (bRam01fcab < bRam018058) {
      bRam01fcab = bRam01fcab + 1;
      goto LAB_030376;
    }
    bRam01fcab = -1;
    bVar1 = true;
  }
  if (bVar1) {
    if ((uStack_a & 0xf00) == 0x100) {
      uStack_a = uStack_a & 0xf0fe;
    }
    uStack_a = (uStack_a >> 8 & 0x9f | 0x60) << 8 | 2;
  }
  if (bRam30400b < bRam01805d) {
    if (bRam01fca8 < bRam018058) {
      bRam01fca8 = bRam01fca8 + 1;
      goto LAB_0303ee;
    }
    bRam01fca8 = -1;
    bVar1 = true;
  }
  else {
    bRam01fca8 = '\0';
LAB_0303ee:
    bVar1 = false;
  }
  if (bVar1) {
    uStack_a = (uStack_a >> 8 & 0x90 | 0x62) << 8 | 2;
  }
  if (bRam01805c < bRam30400b) {
    if (bRam01fcaa < bRam018058) {
      bRam01fcaa = bRam01fcaa + 1;
      goto LAB_03045a;
    }
    bRam01fcaa = -1;
    bVar1 = true;
  }
  else {
    bRam01fcaa = '\0';
LAB_03045a:
    bVar1 = false;
  }
  if (bVar1) {
    uStack_a = (uStack_a >> 8 & 0x90 | 0x61) << 8 | 2;
  }
  if ((bRam01805a < bRam30400b) && ((uStack_a & 1) == 0)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    if (bRam01fcac < bRam018059) {
      bRam01fcac = bRam01fcac + 1;
      goto LAB_0304ce;
    }
    bRam01fcac = -1;
    bVar1 = true;
  }
  else {
    bRam01fcac = '\0';
LAB_0304ce:
    bVar1 = false;
  }
  if (bVar1) {
    uStack_8 = (uVar2 >> 8 & 0x90 | 0x68) << 8 | 2;
  }
  if (bRam01805a < bRam30400b) {
    bRam01fcad = '\0';
LAB_03054e:
    bVar1 = false;
  }
  else {
    if (bRam01fcad < bRam018059) {
      bRam01fcad = bRam01fcad + 1;
      goto LAB_03054e;
    }
    bRam01fcad = -1;
    bVar1 = true;
  }
  if (bVar1) {
    if ((uStack_8 & 0xf00) == 0x800) {
      uStack_8 = uStack_8 & 0xf0fe;
    }
    uStack_8 = (uStack_8 >> 8 & 0x9f | 0x60) << 8 | 2;
  }
  if ((bRam01805b < bRam30400b) && ((uStack_a & 1) == 0)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    if (bRam01fcae < bRam018059) {
      bRam01fcae = bRam01fcae + 1;
      goto LAB_0305e4;
    }
    bRam01fcae = -1;
    bVar1 = true;
  }
  else {
    bRam01fcae = '\0';
LAB_0305e4:
    bVar1 = false;
  }
  if (bVar1) {
    uStack_6 = (uVar3 >> 8 & 0x90 | 0x68) << 8 | 2;
  }
  if (bRam01805b < bRam30400b) {
    bRam01fcaf = '\0';
  }
  else {
    if (bRam018059 <= bRam01fcaf) {
      bRam01fcaf = -1;
      bVar1 = true;
      goto LAB_030666;
    }
    bRam01fcaf = bRam01fcaf + 1;
  }
  bVar1 = false;
LAB_030666:
  if (bVar1) {
    if ((uStack_6 & 0xf00) == 0x800) {
      uStack_6 = uStack_6 & 0xf0fe;
    }
    uStack_6 = (uStack_6 >> 8 & 0x9f | 0x60) << 8 | 2;
  }
  func_0x0b31ac(0xba,uStack_a);
  func_0x0b31ac(0xbc,uStack_6);
  func_0x0b31ac(0xbb,uStack_8);
  return;
}


// ================= t2htrblk_temp_curve @ 055dce =================

/* CONTROL: heater/temperature curve channel: reads T2HTRBLK 6-pt curve (cfg_1F3DC, x@0x1F3DD
   y@0x1F3E3) via sub_42420 over input byte_304DB0, result<<7 -> word_304F66 (0x55E00 movbz
   r12,T2HTRBLK; 0x55E1A mov word_304F66,r12); paired earlier curve -> word_304F6A [C; T2HTRBLK
   identity from inline IDA label, not in dict export] */

void t2htrblk_temp_curve(void)

{
  bool bVar1;
  short sVar2;
  ushort uVar3;
  char cVar4;
  
  uRam304f6a = func_0x0420a8(0x33ea,7,uRam3019f0);
  cVar4 = func_0x042420(uRam01f3dc,0x33dd,7,0x33e3,7,uRam304db0);
  sRam304f66 = (short)cVar4 << 7;
  uRam30254a = func_0x042464(uRam01f412,0x3413,7,0x341a,7,uRam30563a);
  if ((bRam01871a & 4) == 0) {
    bVar1 = 1 < (uRam304f6a & 1);
    uVar3 = uRam304f6a >> 1;
    sVar2 = sRam304f66 + uVar3 + (ushort)bVar1;
    if ((-1 < sRam304f66 && (short)(sRam304f66 + uVar3 + (ushort)bVar1) < 0 != sRam304f66 < 0) ||
       (sRam302550 = sVar2 + uVar3, -1 < sVar2 && (short)(sVar2 + uVar3) < 0 != sVar2 < 0)) {
      sRam302550 = 0x7fff;
    }
  }
  return;
}


// ================= lrl_target_integrator @ 0d35ee =================

/* CONTROL (load-rl module, beside rl_producer sub_D34DC / sub_D337C): saturating integrator step
   toward a page-9 word-map target: target = sub_41CC0 lookup (base #3A02h page9 0x27A02, axes
   word_302CFE + nmot word_F410) -> r9, then sub_43904(gain cfg_27BBE_integrator_gain 0x27BBE,
   target r9, state word_300DAC/DAE) -> word_300DAC/DAE and page-C1 word_30564E (0xD3632/0xD3640) [C
   mechanism; integrated quantity I] */

void lrl_target_integrator(void)

{
  undefined2 uVar1;
  
  if ((((uRam00fd72 & 4) == 0) && ((uRam00fd76 & 2) == 0)) || ((bRam01ba6f & 1) == 0)) {
    uVar1 = me7_lookup_2d_word_bilinear(0x3a02,9,uRam302cfe,nmot_w);
  }
  else {
    uVar1 = me7_lookup_1d_word(0x3bc0,9,uRam302cfe);
  }
  uRam300dac = me7_pt1_integrator(uRam027bbe,uVar1,uRam300dac._2_2_,(undefined2)uRam300dac);
  uRam30564e = (short)((uint)uRam300dac >> 0x10);
  return;
}


// ================= pedal_region_bytemap_ch @ 04eaa8 =================

/* CONTROL: reads the byte map at 0x1ED78 (dict 'Map Bosch II 8', pedal region; x/y counts
   cfg_1ED76) via 2-D byte lookup sub_42544 (x-count byte_1ED76, y-count byte_1ED77) -> byte_304047
   (0x4EAD8/0x4EAE8/0x4EAEC) [C; pedal/ETC role I] */

void pedal_region_bytemap_ch(void)

{
  int iVar1;
  ushort uVar2;
  short sVar3;
  
  bRam304047 = func_0x042544(uRam01ed76,0x2d78,7,uRam01ed77,0x2d7b,7,0x2d80,7,(short)cRam304952,
                             uRam3012f2);
  bRam304048 = me7_lookup_1d_byte(0x21d,6,nmot_rpmclass);
  sVar3 = 200 - (ushort)bRam304047;
  if (bRam304047 < 0xc9) {
    if (sVar3 < 0) {
      sVar3 = 0x7fff;
    }
  }
  else if (sVar3 >= 0) {
    sVar3 = 0;
  }
  uVar2 = (ushort)bRam304048 << 8;
  sVar3 = sVar3 << 7;
  if ((short)uVar2 < 0) {
    iVar1 = (int)sVar3 * (int)(short)(uVar2 & 0x7fff);
    uVar2 = (ushort)iVar1;
    sVar3 = (short)((uint)iVar1 >> 0x10) + (sVar3 >> 1);
    if (sVar3 < 0) {
      sVar3 = sVar3 + (ushort)(uVar2 - 1 < uVar2 || uVar2 != 0);
    }
  }
  else {
    iVar1 = (int)sVar3 * (int)(short)uVar2;
    uVar2 = (ushort)iVar1;
    sVar3 = (short)((uint)iVar1 >> 0x10);
    if (iVar1 < 0) {
      sVar3 = sVar3 + (ushort)(uVar2 - 1 < uVar2 || uVar2 != 0);
    }
  }
  MDH = (undefined2)((uint)iVar1 >> 0x10);
  MDL = (undefined2)iVar1;
  MDC = MDC | 0x10;
  if ((bRam301612 & 4) == 0) {
    uVar2 = uRam01ed90 >> 1;
  }
  else {
    uVar2 = -(uRam01ed90 >> 1);
  }
  if ((flags_diag_cfg_b & 0x200) == 0) {
    sRam301ac0 = func_0x042d5a(0xffff,uVar2,sRam301ac0,0x6400 - sVar3,0x6400);
    iVar1 = CONCAT22(MDH,MDL);
  }
  else {
    sRam301ac0 = 0x6400;
  }
  MDH = (undefined2)((uint)iVar1 >> 0x10);
  MDL = (undefined2)iVar1;
  uRam304046 = (char)(sRam301ac0 >> 7);
  return;
}


// ================= diag_obd_monitor_seq @ 0a8dc2 =================

/* DIAGNOSTIC: OBD-monitor init/step sequencer (callers=1; 0xA8DC2-0xAA3C4, reads 22 cal maps):
   large branch machine dispatching to loc_AA3B6 tail, seeds monitor RAM word_300A18/300A22/300A28
   from cfg_24310_obdmon_init_words + word_24266 then arms byte_300A74=#14h, calls helper steps
   sub_A8B02/sub_A8B6E/sub_A8C64 (0xA8DF0/0xA8E7C/0xA8EC4) [C mechanism; specific monitor identity
   I] */

ushort diag_obd_monitor_seq(void)

{
  bool bVar1;
  short sVar2;
  int iVar4;
  int iVar5;
  bool bVar6;
  ushort uVar7;
  ushort uVar8;
  ushort uStack_2a;
  int iVar3;
  
  iVar4 = CONCAT22(MDH,MDL);
  iVar3 = CONCAT22(MDH,MDL);
  iVar5 = CONCAT22(MDH,MDL);
  switch(uRam300a76) {
  case 1:
    if (cRam300a5f == '\0') {
      if (cRam300a58 == '\0') {
        uRam300a76 = 2;
        uVar7 = func_0x0a8c64();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        uVar7 = (ushort)bRam300a62;
        bRam300a54 = bRam300a62;
        uRam300a53 = uRam300a60;
        iVar3 = iVar4;
      }
    }
    else {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
    }
    break;
  case 2:
    if (cRam300a5f == '\0') {
      if (cRam300a63 == '\0') {
        uRam300a76 = 0;
        cRam300a74 = '\n';
        uVar7 = 0;
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        bVar6 = sRam300a4a == 0;
        sRam300a4a = sRam300a4a + -1;
        if ((short)-(ushort)bVar6 < 0) {
          sRam300a4a = 0;
        }
        cRam300a63 = sRam300a4a != 0;
        uVar7 = (ushort)(byte)cRam300a63;
        iVar3 = CONCAT22(MDH,MDL);
      }
    }
    else {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
    }
    break;
  case 3:
    if (cRam300a5f == '\0') {
      if ((cRam300a5e == '\0') && (uRam300a10 != 0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (bVar6) {
        uRam300a76 = 2;
        uVar7 = func_0x0a8c64();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        if ((cRam300a75 == ' ') || (cRam300a75 == '!')) {
          bVar6 = true;
        }
        else {
          bVar6 = false;
        }
        if (bVar6) {
          uRam300a76 = 6;
          uVar7 = func_0x0a8c44();
          iVar3 = CONCAT22(MDH,MDL);
        }
        else if (uRam300a2e < uRam300a1e) {
          uRam300a76 = 5;
          uRam300a2c = uRam300a1e;
          uRam300a5d = 0;
          bRam300a54 = 0;
          uRam300a53 = 0;
          uVar7 = func_0x0a8ca0();
          iVar3 = CONCAT22(MDH,MDL);
        }
        else if (uRam300a12 < uRam0101d6) {
          if ((uRam300a46 < uRam300a44) && (uRam300a40 < uRam300a42)) {
            bVar6 = true;
          }
          else {
            bVar6 = false;
          }
          if (bVar6) {
            uRam300a76 = 6;
            uRam300a36 = uRam300a1e;
            uRam300a2c = uRam300a1e;
            uVar7 = func_0x0a8c44();
            iVar3 = CONCAT22(MDH,MDL);
          }
          else {
            uRam300a12 = uRam300a1e - uRam300a36;
            if (-(ushort)(uRam300a1e < uRam300a36) == 0 && uRam300a12 == 0 ||
                (short)-(ushort)(uRam300a1e < uRam300a36) < 0) {
              uRam300a12 = -uRam300a12;
            }
            bVar6 = uRam300a44 + 1 < uRam300a44;
            bVar1 = uRam300a44 == 0xffff;
            uRam300a44 = uRam300a44 + 1;
            if (bVar6 || bVar1) {
              uVar7 = 0;
            }
            else {
              uVar7 = (ushort)(uRam300a44 != 0xffff) << 1 | (ushort)(uRam300a44 == 0xffff) << 3;
            }
            if (!(bool)((byte)(uVar7 >> 3) | (byte)(uVar7 >> 1) & 1)) {
              uRam300a44 = 0xffff;
            }
            uVar7 = uRam300a42 + 1;
            if (uRam300a42 + 1 < uRam300a42 || uRam300a42 == 0xffff) {
              uVar8 = 0;
            }
            else {
              uVar8 = (ushort)(uVar7 != 0xffff) << 1 | (ushort)(uVar7 == 0xffff) << 3;
            }
            uRam300a42 = uVar7;
            if (!(bool)((byte)(uVar8 >> 3) | (byte)(uVar8 >> 1) & 1)) {
              uVar7 = 0xffff;
              uRam300a42 = uVar7;
            }
          }
        }
        else {
          uRam300a76 = 3;
          uVar7 = func_0x0a8c14();
          iVar3 = CONCAT22(MDH,MDL);
        }
      }
    }
    else {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
    }
    break;
  case 4:
    if (cRam300a5f == '\0') {
      if ((cRam300a5e == '\0') && (uRam300a10 != 0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (bVar6) {
        uRam300a76 = 2;
        uVar7 = func_0x0a8c64();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        uVar7 = 0;
        iVar3 = CONCAT22(MDH,MDL);
      }
    }
    else {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
    }
    break;
  case 5:
    if (cRam300a5f == '\0') {
      if ((cRam300a5e == '\0') && (uRam300a10 != 0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (bVar6) {
        uRam300a76 = 2;
        uVar7 = func_0x0a8c64();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        uVar7 = 0;
        iVar3 = CONCAT22(MDH,MDL);
      }
    }
    else {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
    }
    break;
  case 6:
    if (cRam300a5f == '\0') {
      if ((cRam300a5e == '\0') && (uRam300a10 != 0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (bVar6) {
        uRam300a76 = 2;
        uVar7 = func_0x0a8c64();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else if (uRam0101d6 < uRam300a12) {
        uRam300a76 = 3;
        uVar7 = func_0x0a8c14();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        iVar3 = (uint)uRam300a46 * (uint)uRam0101da;
        sVar2 = (short)iVar3;
        uVar7 = (ushort)((uint)iVar3 >> 0x10);
        MDC = MDC | 0x10;
        if (uRam300a44 - uVar7 == (ushort)(sVar2 != 0) && sVar2 == 0 ||
            (uRam300a44 < uVar7 || uRam300a44 == uVar7 && sVar2 != 0)) {
          bVar6 = uRam300a44 + 1 < uRam300a44;
          bVar1 = uRam300a44 == 0xffff;
          uRam300a44 = uRam300a44 + 1;
          if (bVar6 || bVar1) {
            uVar7 = 0;
          }
          else {
            uVar7 = (ushort)(uRam300a44 != 0xffff) << 1 | (ushort)(uRam300a44 == 0xffff) << 3;
          }
          if (!(bool)((byte)(uVar7 >> 3) | (byte)(uVar7 >> 1) & 1)) {
            uRam300a44 = 0xffff;
          }
          uVar8 = uRam300a42 + 1;
          if (uRam300a42 + 1 < uRam300a42 || uRam300a42 == 0xffff) {
            uVar7 = 0;
          }
          else {
            uVar7 = (ushort)(uVar8 != 0xffff) << 1 | (ushort)(uVar8 == 0xffff) << 3;
          }
          if (!(bool)((byte)(uVar7 >> 3) | (byte)(uVar7 >> 1) & 1)) {
            uVar8 = 0xffff;
          }
          uVar7 = uRam300a1e - uRam300a38;
          uRam300a12 = uVar7;
          uRam300a42 = uVar8;
          if (-(ushort)(uRam300a1e < uRam300a38) == 0 && uVar7 == 0 ||
              (short)-(ushort)(uRam300a1e < uRam300a38) < 0) {
            uVar7 = -uVar7;
            uRam300a12 = uVar7;
          }
        }
        else {
          uRam300a76 = 7;
          uRam300a26 = uRam300a1e;
          if (cRam300a69 == '\0') {
            uRam300a53 = 0;
            uRam300a64 = 1;
            uRam300a30 = uRam300a1e;
            uRam300a2e = uRam300a1e;
            sRam300a4e = sRam01036e;
            cRam300a6f = sRam01036e == 0;
          }
          uVar7 = 0x21;
          cRam300a74 = '!';
        }
      }
    }
    else {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
    }
    break;
  case 7:
    if (cRam300a5f == '\0') {
      if ((cRam300a5e == '\0') && (uRam300a10 != 0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (bVar6) {
        uRam300a76 = 2;
        uVar7 = func_0x0a8c64();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        if ((cRam300a6f == '\0') || (uRam300a36 <= uRam300a2e)) {
          bVar6 = false;
        }
        else {
          bVar6 = true;
        }
        if (bVar6) {
          uRam300a76 = 5;
          uRam300a64 = 0;
          bRam300a54 = 0;
          cRam300a5e = '\x01';
          uVar7 = func_0x0a8ca0();
          iVar3 = CONCAT22(MDH,MDL);
        }
        else {
          if ((uRam010268 < uRam300a30) && (cRam300a6f != '\0')) {
            bVar6 = true;
          }
          else {
            bVar6 = false;
          }
          if (bVar6) {
            uVar7 = 8;
            uRam300a76 = 8;
            uRam300a6a = 1;
            cRam300a5e = '\x01';
            cRam300a74 = '#';
            uRam300a5d = 0;
            bRam300a54 = 0;
            uRam300a64 = 0;
            iVar3 = CONCAT22(MDH,MDL);
          }
          else {
            if ((cRam300a6f == '\0') || (uRam01026a <= uRam300a30)) {
              bVar6 = false;
            }
            else {
              bVar6 = true;
            }
            if (bVar6) {
              uVar7 = 8;
              uRam300a76 = 8;
              uRam300a6b = 1;
              cRam300a5e = '\x01';
              cRam300a74 = '#';
              uRam300a5d = 0;
              bRam300a54 = 0;
              uRam300a64 = 0;
              iVar3 = CONCAT22(MDH,MDL);
            }
            else {
              if ((((cRam300a6f == '\0') || (uRam300a34 <= uRam300a2a)) || (cRam300a5a == '\0')) &&
                 (((cRam300a5a != '\0' || (uRam300a32 <= uRam300a26)) || (cRam300a6f == '\0')))) {
                bVar6 = false;
              }
              else {
                bVar6 = true;
              }
              if (bVar6) {
                uVar7 = 9;
                uRam300a76 = 9;
                uRam300a64 = 0;
                bRam300a54 = 0;
                cRam300a5e = '\x01';
                cRam300a74 = '$';
                cRam300a5b = '\x01';
                cRam300a71 = '\x01';
                uRam300a5d = 0;
                iVar3 = CONCAT22(MDH,MDL);
              }
              else if (cRam300a6f == '\0') {
                uVar7 = func_0x0a8cbe();
                iVar3 = CONCAT22(MDH,MDL);
              }
              else {
                uRam300a76 = 4;
                uRam300a64 = 0;
                bRam300a54 = 0;
                cRam300a5e = '\x01';
                cRam300a74 = '%';
                uRam300a65 = 1;
                uRam300a72 = 1;
                uRam300a2c = uRam300a36;
                uRam300a5d = 0;
                uVar7 = uRam300a36;
                iVar3 = CONCAT22(MDH,MDL);
              }
            }
          }
        }
      }
    }
    else {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
    }
    break;
  case 8:
    if (cRam300a5f == '\0') {
      if ((cRam300a5e == '\0') && (uRam300a10 != 0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (bVar6) {
        uRam300a76 = 2;
        uVar7 = func_0x0a8c64();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        uVar7 = 0;
        iVar3 = CONCAT22(MDH,MDL);
      }
    }
    else {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
    }
    break;
  case 9:
    if (cRam300a5f == '\0') {
      if ((cRam300a5e == '\0') && (uRam300a10 != 0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (bVar6) {
        uRam300a76 = 2;
        uVar7 = func_0x0a8c64();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        uVar7 = 0;
        iVar3 = CONCAT22(MDH,MDL);
      }
    }
    else {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
    }
    break;
  case 10:
    if (cRam300a5f == '\0') {
      if ((cRam300a5e == '\0') && (uRam300a10 != 0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (bVar6) {
        uRam300a76 = 2;
        uVar7 = func_0x0a8c64();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else if (cRam300a67 == '\0') {
        uVar7 = (ushort)bRam300a73;
        iVar3 = CONCAT22(MDH,MDL);
        if (bRam300a73 != 0) {
          uRam300a59 = 0;
          uRam300a5d = 1;
          iVar3 = CONCAT22(MDH,MDL);
        }
      }
      else {
        if (bRam300a73 != 0) {
          uRam300a59 = 0;
        }
        uRam300a76 = 0xb;
        cRam300a74 = '>';
        cRam300a5e = '\x01';
        uRam300a5d = 0;
        uVar7 = 0xb;
        iVar3 = CONCAT22(MDH,MDL);
      }
    }
    else {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
    }
    break;
  case 0xb:
    if (cRam300a5f == '\0') {
      if ((cRam300a5e == '\0') && (uRam300a10 != 0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (bVar6) {
        uRam300a76 = 2;
        uVar7 = func_0x0a8c64();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        uVar7 = (ushort)bRam300a73;
        iVar3 = CONCAT22(MDH,MDL);
        if (bRam300a73 != 0) {
          uRam300a59 = 0;
          uRam300a5d = 1;
          iVar3 = CONCAT22(MDH,MDL);
        }
      }
    }
    else {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
    }
    break;
  case 0xc:
    if (cRam300a5f != '\0') {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
      break;
    }
    if ((cRam300a5e == '\0') && (uRam300a10 != 0)) {
      bVar6 = false;
    }
    else {
      bVar6 = true;
    }
    if (bVar6) {
      uRam300a76 = 2;
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
      break;
    }
    if (cRam300a74 == '\x18') {
      if ((bRam01215f & 1) == 0) {
        bVar6 = false;
      }
      else if ((cRam300a68 == '\0') || ((uRam300a10 & uRam010130) != 0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (!bVar6) goto code_r0x0a9e40;
      bVar6 = true;
    }
    else {
code_r0x0a9e40:
      bVar6 = false;
    }
    if (bVar6) {
      uRam300a76 = 10;
      cRam300a74 = '=';
      uVar7 = 10;
      iVar3 = CONCAT22(MDH,MDL);
    }
    else {
      if (((cRam300a5b == '\0') && (cRam300a71 != '\0')) && (cRam300a5c != '\0')) {
        bVar6 = true;
      }
      else {
        bVar6 = false;
      }
      if (bVar6) {
        uRam300a76 = 3;
        cRam300a74 = '\x1e';
        uVar7 = func_0x0a8c14();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        if (((cRam300a70 == '\0') || (cRam300a56 != '\0')) || (cRam300a58 == '\0')) {
          bVar6 = false;
        }
        else {
          bVar6 = true;
        }
        if (bVar6) {
          uRam300a76 = 1;
          cRam300a74 = '(';
          uVar7 = 1;
          iVar3 = CONCAT22(MDH,MDL);
        }
        else {
          if ((uRam010268 < uRam300a30) && (cRam300a6e != '\0')) {
            bVar6 = true;
          }
          else {
            bVar6 = false;
          }
          if (bVar6) {
            uRam300a76 = 0x10;
            uRam300a6a = 1;
            cRam300a5e = '\x01';
            uRam300a64 = 0;
            uVar7 = func_0x0a8b58();
            iVar3 = CONCAT22(MDH,MDL);
          }
          else {
            if ((cRam300a6e == '\0') || (uRam01026a <= uRam300a30)) {
              bVar6 = false;
            }
            else {
              bVar6 = true;
            }
            if (bVar6) {
              uRam300a76 = 0x10;
              uRam300a6b = 1;
              cRam300a5e = '\x01';
              uRam300a64 = 0;
              uVar7 = func_0x0a8b58();
              iVar3 = CONCAT22(MDH,MDL);
            }
            else if (cRam300a6e == '\0') {
              bVar6 = sRam300a4c == 0;
              sRam300a4c = sRam300a4c + -1;
              if ((short)-(ushort)bVar6 < 0) {
                sRam300a4c = 0;
              }
              cRam300a6e = sRam300a4c == 0;
              uRam300a30 = uRam300a1e;
              uVar7 = uRam300a1e;
              iVar3 = iVar5;
              if ((short)uRam0101d4 < 0) {
                uRam300a2e = uRam0101d4 + uRam300a1e;
                if (uRam0101d4 <= uRam0101d4 + uRam300a1e && uRam300a1e <= uRam0101d4 + uRam300a1e)
                {
                  uRam300a2e = 0;
                }
              }
              else {
                uRam300a2e = uRam0101d4 + uRam300a1e;
                if (uRam0101d4 + uRam300a1e < uRam0101d4 || uRam0101d4 + uRam300a1e < uRam300a1e) {
                  uRam300a2e = 0xffff;
                }
              }
            }
            else {
              uRam300a76 = 0x13;
              uRam300a64 = 0;
              if (cRam300a69 == '\0') {
                uRam300a53 = 1;
                sRam300a50 = sRam010374;
                cRam300a70 = sRam010374 == 0;
              }
              cRam300a74 = '\x17';
              uVar7 = 0x17;
              iVar3 = CONCAT22(MDH,MDL);
            }
          }
        }
      }
    }
    break;
  case 0xd:
    if (cRam300a5f != '\0') {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
      break;
    }
    if ((cRam300a5e == '\0') && (uRam300a10 != 0)) {
      bVar6 = false;
    }
    else {
      bVar6 = true;
    }
    if (bVar6) {
      uRam300a76 = 2;
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
      break;
    }
    if (cRam300a74 == '\x18') {
      if ((bRam01215f & 1) == 0) {
        bVar6 = false;
      }
      else if ((cRam300a68 == '\0') || ((uRam300a10 & uRam010130) != 0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (!bVar6) goto code_r0x0aa2f6;
      bVar6 = true;
    }
    else {
code_r0x0aa2f6:
      bVar6 = false;
    }
    if (bVar6) {
      uRam300a76 = 10;
      cRam300a74 = '=';
      uVar7 = 10;
      iVar3 = CONCAT22(MDH,MDL);
    }
    else {
      if (((cRam300a5b == '\0') && (cRam300a71 != '\0')) && (cRam300a5c != '\0')) {
        bVar6 = true;
      }
      else {
        bVar6 = false;
      }
      if (bVar6) {
        uRam300a76 = 3;
        cRam300a74 = '\x1e';
        uVar7 = func_0x0a8c14();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        if (((cRam300a70 == '\0') || (cRam300a56 != '\0')) || (cRam300a58 == '\0')) {
          bVar6 = false;
        }
        else {
          bVar6 = true;
        }
        if (bVar6) {
          uRam300a76 = 1;
          cRam300a74 = '(';
          uVar7 = 1;
          iVar3 = CONCAT22(MDH,MDL);
        }
        else {
          uVar7 = 0;
          iVar3 = CONCAT22(MDH,MDL);
        }
      }
    }
    break;
  case 0xe:
    if (cRam300a5f != '\0') {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
      break;
    }
    if ((cRam300a5e == '\0') && (uRam300a10 != 0)) {
      bVar6 = false;
    }
    else {
      bVar6 = true;
    }
    if (bVar6) {
      uRam300a76 = 2;
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
      break;
    }
    if (cRam300a74 == '\x18') {
      if ((bRam01215f & 1) == 0) {
        bVar6 = false;
      }
      else if ((cRam300a68 == '\0') || ((uRam300a10 & uRam010130) != 0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (!bVar6) goto code_r0x0aa1fa;
      bVar6 = true;
    }
    else {
code_r0x0aa1fa:
      bVar6 = false;
    }
    if (bVar6) {
      uRam300a76 = 10;
      cRam300a74 = '=';
      uVar7 = 10;
      iVar3 = CONCAT22(MDH,MDL);
    }
    else {
      if (((cRam300a5b == '\0') && (cRam300a71 != '\0')) && (cRam300a5c != '\0')) {
        bVar6 = true;
      }
      else {
        bVar6 = false;
      }
      if (bVar6) {
        uRam300a76 = 3;
        cRam300a74 = '\x1e';
        uVar7 = func_0x0a8c14();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        if (((cRam300a70 == '\0') || (cRam300a56 != '\0')) || (cRam300a58 == '\0')) {
          bVar6 = false;
        }
        else {
          bVar6 = true;
        }
        if (bVar6) {
          uRam300a76 = 1;
          cRam300a74 = '(';
          uVar7 = 1;
          iVar3 = CONCAT22(MDH,MDL);
        }
        else {
          uVar7 = 0;
          iVar3 = CONCAT22(MDH,MDL);
        }
      }
    }
    break;
  case 0xf:
    if (cRam300a5f != '\0') {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
      break;
    }
    if ((cRam300a5e == '\0') && (uRam300a10 != 0)) {
      bVar6 = false;
    }
    else {
      bVar6 = true;
    }
    if (bVar6) {
      uRam300a76 = 2;
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
      break;
    }
    if (cRam300a74 == '\x18') {
      if ((bRam01215f & 1) == 0) {
        bVar6 = false;
      }
      else if ((cRam300a68 == '\0') || ((uRam300a10 & uRam010130) != 0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (!bVar6) goto code_r0x0aa05c;
      bVar6 = true;
    }
    else {
code_r0x0aa05c:
      bVar6 = false;
    }
    if (bVar6) {
      uRam300a76 = 10;
      cRam300a74 = '=';
      uVar7 = 10;
      iVar3 = CONCAT22(MDH,MDL);
    }
    else {
      if (((cRam300a5b == '\0') && (cRam300a71 != '\0')) && (cRam300a5c != '\0')) {
        bVar6 = true;
      }
      else {
        bVar6 = false;
      }
      if (bVar6) {
        uRam300a76 = 3;
        cRam300a74 = '\x1e';
        uVar7 = func_0x0a8c14();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        if (((cRam300a70 == '\0') || (cRam300a56 != '\0')) || (cRam300a58 == '\0')) {
          bVar6 = false;
        }
        else {
          bVar6 = true;
        }
        if (bVar6) {
          uRam300a76 = 1;
          cRam300a74 = '(';
          uVar7 = 1;
          iVar3 = CONCAT22(MDH,MDL);
        }
        else if (uRam300a34 < uRam300a2a) {
          uRam300a76 = 0xe;
          uVar7 = func_0x0a8be8();
          iVar3 = CONCAT22(MDH,MDL);
        }
        else if (uRam300a40 < uRam300a42) {
          uRam300a76 = 0x11;
          if (cRam300a69 == '\0') {
            uRam300a53 = 0;
            uRam300a64 = 1;
            uRam300a30 = uRam300a1e;
            uRam300a2e = uRam300a1e;
            sRam300a4e = sRam01036e;
            cRam300a6f = sRam01036e == 0;
          }
          cRam300a74 = '\x1a';
          uVar7 = 0x1a;
          iVar3 = CONCAT22(MDH,MDL);
        }
        else {
          uRam300a2a = uRam300a1e;
          bVar6 = uRam300a42 + 1 < uRam300a42;
          bVar1 = uRam300a42 == 0xffff;
          uVar7 = uRam300a42 + 1;
          uRam300a42 = uVar7;
          iVar3 = CONCAT22(MDH,MDL);
          if (((bVar6 || bVar1) != (uVar7 != 0xffff) || uVar7 != 0xffff) &&
              ((bVar6 || bVar1) || uVar7 == 0xffff)) {
            uVar7 = 0xffff;
            uRam300a42 = uVar7;
          }
        }
      }
    }
    break;
  case 0x10:
    if (cRam300a5f != '\0') {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
      break;
    }
    if ((cRam300a5e == '\0') && (uRam300a10 != 0)) {
      bVar6 = false;
    }
    else {
      bVar6 = true;
    }
    if (bVar6) {
      uRam300a76 = 2;
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
      break;
    }
    if (cRam300a74 == '\x18') {
      if ((bRam01215f & 1) == 0) {
        bVar6 = false;
      }
      else if ((cRam300a68 == '\0') || ((uRam300a10 & uRam010130) != 0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (!bVar6) goto code_r0x0a9d44;
      bVar6 = true;
    }
    else {
code_r0x0a9d44:
      bVar6 = false;
    }
    if (bVar6) {
      uRam300a76 = 10;
      cRam300a74 = '=';
      uVar7 = 10;
      iVar3 = CONCAT22(MDH,MDL);
    }
    else {
      if (((cRam300a5b == '\0') && (cRam300a71 != '\0')) && (cRam300a5c != '\0')) {
        bVar6 = true;
      }
      else {
        bVar6 = false;
      }
      if (bVar6) {
        uRam300a76 = 3;
        cRam300a74 = '\x1e';
        uVar7 = func_0x0a8c14();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        if (((cRam300a70 == '\0') || (cRam300a56 != '\0')) || (cRam300a58 == '\0')) {
          bVar6 = false;
        }
        else {
          bVar6 = true;
        }
        if (bVar6) {
          uRam300a76 = 1;
          cRam300a74 = '(';
          uVar7 = 1;
          iVar3 = CONCAT22(MDH,MDL);
        }
        else {
          uVar7 = 0;
          iVar3 = CONCAT22(MDH,MDL);
        }
      }
    }
    break;
  case 0x11:
    if (cRam300a5f != '\0') {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
      break;
    }
    if ((cRam300a5e == '\0') && (uRam300a10 != 0)) {
      bVar6 = false;
    }
    else {
      bVar6 = true;
    }
    if (bVar6) {
      uRam300a76 = 2;
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
      break;
    }
    if (cRam300a74 == '\x18') {
      if ((bRam01215f & 1) == 0) {
        bVar6 = false;
      }
      else if ((cRam300a68 == '\0') || ((uRam300a10 & uRam010130) != 0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (!bVar6) goto code_r0x0a9b8a;
      bVar6 = true;
    }
    else {
code_r0x0a9b8a:
      bVar6 = false;
    }
    if (bVar6) {
      uRam300a76 = 10;
      cRam300a74 = '=';
      uVar7 = 10;
      iVar3 = CONCAT22(MDH,MDL);
    }
    else {
      if (((cRam300a5b == '\0') && (cRam300a71 != '\0')) && (cRam300a5c != '\0')) {
        bVar6 = true;
      }
      else {
        bVar6 = false;
      }
      if (bVar6) {
        uRam300a76 = 3;
        cRam300a74 = '\x1e';
        uVar7 = func_0x0a8c14();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        if (((cRam300a70 == '\0') || (cRam300a56 != '\0')) || (cRam300a58 == '\0')) {
          bVar6 = false;
        }
        else {
          bVar6 = true;
        }
        if (bVar6) {
          uRam300a76 = 1;
          cRam300a74 = '(';
          uVar7 = 1;
          iVar3 = CONCAT22(MDH,MDL);
        }
        else {
          if ((uRam010268 < uRam300a30) && (cRam300a6f != '\0')) {
            bVar6 = true;
          }
          else {
            bVar6 = false;
          }
          if (bVar6) {
            uRam300a76 = 0x10;
            uRam300a6a = 1;
            cRam300a5e = '\x01';
            uRam300a64 = 0;
            uVar7 = func_0x0a8b58();
            iVar3 = CONCAT22(MDH,MDL);
          }
          else {
            if ((cRam300a6f == '\0') || (uRam01026a <= uRam300a30)) {
              bVar6 = false;
            }
            else {
              bVar6 = true;
            }
            if (bVar6) {
              uRam300a76 = 0x10;
              uRam300a6b = 1;
              cRam300a5e = '\x01';
              uRam300a64 = 0;
              uVar7 = func_0x0a8b58();
              iVar3 = CONCAT22(MDH,MDL);
            }
            else {
              if ((cRam300a6f == '\0') || (uRam300a2a < uRam300a34)) {
                bVar6 = false;
              }
              else {
                bVar6 = true;
              }
              if (bVar6) {
                uRam300a76 = 0xe;
                uVar7 = func_0x0a8be8();
                iVar3 = CONCAT22(MDH,MDL);
              }
              else if (cRam300a6f == '\0') {
                uVar7 = func_0x0a8cbe();
                iVar3 = CONCAT22(MDH,MDL);
              }
              else {
                uRam300a76 = 0xd;
                uVar7 = func_0x0a8bbc();
                iVar3 = CONCAT22(MDH,MDL);
              }
            }
          }
        }
      }
    }
    break;
  case 0x12:
    if (cRam300a5f != '\0') {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
      break;
    }
    if ((cRam300a5e == '\0') && (uRam300a10 != 0)) {
      bVar6 = false;
    }
    else {
      bVar6 = true;
    }
    if (bVar6) {
      uRam300a76 = 2;
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
      break;
    }
    if (cRam300a74 == '\x18') {
      if ((bRam01215f & 1) == 0) {
        bVar6 = false;
      }
      else if ((cRam300a68 == '\0') || ((uRam300a10 & uRam010130) != 0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (!bVar6) goto code_r0x0a99a8;
      bVar6 = true;
    }
    else {
code_r0x0a99a8:
      bVar6 = false;
    }
    if (bVar6) {
      uRam300a76 = 10;
      cRam300a74 = '=';
      uVar7 = 10;
      iVar3 = CONCAT22(MDH,MDL);
    }
    else {
      if (((cRam300a5b == '\0') && (cRam300a71 != '\0')) && (cRam300a5c != '\0')) {
        bVar6 = true;
      }
      else {
        bVar6 = false;
      }
      if (bVar6) {
        uRam300a76 = 3;
        cRam300a74 = '\x1e';
        uVar7 = func_0x0a8c14();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        if (((cRam300a70 == '\0') || (cRam300a56 != '\0')) || (cRam300a58 == '\0')) {
          bVar6 = false;
        }
        else {
          bVar6 = true;
        }
        if (bVar6) {
          uRam300a76 = 1;
          cRam300a74 = '(';
          uVar7 = 1;
          iVar3 = CONCAT22(MDH,MDL);
        }
        else if (uRam300a32 < uRam300a26) {
          uRam300a76 = 0xe;
          uRam300a59 = 0;
          uVar7 = func_0x0a8be8();
          iVar3 = CONCAT22(MDH,MDL);
        }
        else {
          if (((cRam300a6d == '\0') && (cRam300a66 == '\0')) || (uRam300a42 <= uRam300a3e)) {
            bVar6 = false;
          }
          else {
            bVar6 = true;
          }
          if (bVar6) {
            uRam300a76 = 0xd;
            uVar7 = func_0x0a8bbc();
            iVar3 = CONCAT22(MDH,MDL);
          }
          else if (uRam300a3e < uRam300a42) {
            uRam300a76 = 0xf;
            if (cRam300a69 == '\0') {
              uRam300a2a = uRam300a1e;
              cRam300a5a = '\x01';
              iVar4 = (uint)uRam300a20 * (uint)uRam300a1c;
              uVar7 = (ushort)((uint)iVar4 >> 0x10);
              MDC = MDC | 0x10;
              uRam300a34 = uRam300a30 - uVar7;
              if ((short)-(ushort)(uRam300a30 < uVar7) < 0) {
                uRam300a34 = 0;
              }
            }
            cRam300a74 = '\x19';
            uVar7 = 0x19;
            iVar3 = iVar4;
          }
          else {
            uRam300a26 = uRam300a1e;
            bVar6 = uRam300a42 + 1 < uRam300a42;
            bVar1 = uRam300a42 == 0xffff;
            uVar7 = uRam300a42 + 1;
            uRam300a42 = uVar7;
            iVar3 = CONCAT22(MDH,MDL);
            if (((bVar6 || bVar1) != (uVar7 != 0xffff) || uVar7 != 0xffff) &&
                ((bVar6 || bVar1) || uVar7 == 0xffff)) {
              uVar7 = 0xffff;
              uRam300a42 = uVar7;
            }
          }
        }
      }
    }
    break;
  case 0x13:
    if (cRam300a5f != '\0') {
      uRam300a76 = 2;
      func_0x0a8b02();
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
      break;
    }
    if ((cRam300a5e == '\0') && (uRam300a10 != 0)) {
      bVar6 = false;
    }
    else {
      bVar6 = true;
    }
    if (bVar6) {
      uRam300a76 = 2;
      uVar7 = func_0x0a8c64();
      iVar3 = CONCAT22(MDH,MDL);
      break;
    }
    if (cRam300a74 == '\x18') {
      if ((bRam01215f & 1) == 0) {
        bVar6 = false;
      }
      else if ((cRam300a68 == '\0') || ((uRam300a10 & uRam010130) != 0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (!bVar6) goto code_r0x0a95c8;
      bVar6 = true;
    }
    else {
code_r0x0a95c8:
      bVar6 = false;
    }
    if (bVar6) {
      uRam300a76 = 10;
      cRam300a74 = '=';
      uVar7 = 10;
      iVar3 = CONCAT22(MDH,MDL);
    }
    else {
      if (((cRam300a5b == '\0') && (cRam300a71 != '\0')) && (cRam300a5c != '\0')) {
        bVar6 = true;
      }
      else {
        bVar6 = false;
      }
      if (bVar6) {
        uRam300a76 = 3;
        cRam300a74 = '\x1e';
        uVar7 = func_0x0a8c14();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        if (((cRam300a70 == '\0') || (cRam300a56 != '\0')) || (cRam300a58 == '\0')) {
          bVar6 = false;
        }
        else {
          bVar6 = true;
        }
        if (bVar6) {
          uRam300a76 = 1;
          cRam300a74 = '(';
          uVar7 = 1;
          iVar3 = CONCAT22(MDH,MDL);
        }
        else {
          if ((((cRam300a56 == '\0') && (cRam300a55 != '\0')) ||
              ((cRam300a56 != '\0' && (cRam300a55 == '\0')))) &&
             ((sRam300a18 != 0 && (cRam300a70 != '\0')))) {
            bVar6 = true;
          }
          else {
            bVar6 = false;
          }
          if (bVar6) {
            uRam300a76 = 0xc;
            if ((cRam300a57 != '\0') &&
               (bVar6 = uRam300a16 + 1 < uRam300a16, bVar1 = uRam300a16 == 0xffff,
               uRam300a16 = uRam300a16 + 1,
               ((bVar6 || bVar1) != (uRam300a16 != 0xffff) || uRam300a16 != 0xffff) &&
               ((bVar6 || bVar1) || uRam300a16 == 0xffff))) {
              uRam300a16 = 0xffff;
            }
            bVar6 = sRam300a18 == 0;
            sRam300a18 = sRam300a18 + -1;
            if ((short)-(ushort)bVar6 < 0) {
              sRam300a18 = 0;
            }
            bVar1 = uRam300a14 + 1 < uRam300a14 || uRam300a14 == 0xffff;
            uRam300a14 = uRam300a14 + 1;
            if ((bVar1 != (uRam300a14 != 0xffff) || uRam300a14 != 0xffff) &&
                (bVar1 || uRam300a14 == 0xffff)) {
              uRam300a14 = 0xffff;
            }
            uRam300a28 = uRam010266;
            cRam300a56 = '\0';
            cRam300a57 = '\0';
            uRam300a53 = 0;
            uVar7 = func_0x0a8b6e(bVar1,-(ushort)bVar6);
            iVar3 = CONCAT22(MDH,MDL);
          }
          else {
            if ((cRam300a56 == '\0') || (cRam300a70 == '\0')) {
              bVar6 = false;
            }
            else {
              bVar6 = true;
            }
            if (bVar6) {
              uRam300a76 = 0x10;
              uRam300a6c = 1;
              cRam300a5e = '\x01';
              uVar7 = func_0x0a8b58();
              iVar3 = CONCAT22(MDH,MDL);
            }
            else {
              if ((((cRam300a5c == '\0') && (cRam300a61 == '\0')) || (cRam300a56 != '\0')) ||
                 (cRam300a70 == '\0')) {
                bVar6 = false;
              }
              else {
                bVar6 = true;
              }
              if (bVar6) {
                uRam300a76 = 0x12;
                if (cRam300a69 == '\0') {
                  uRam300a59 = 1;
                  uRam300a26 = uRam300a1e;
                  iVar4 = (uint)uRam300a20 * (uint)uRam300a1a;
                  uRam300a32 = (ushort)((uint)iVar4 >> 0x10);
                  MDC = MDC | 0x10;
                  bVar6 = uRam300a28 + uRam300a32 < uRam300a28;
                  bVar1 = uRam300a28 + uRam300a32 < uRam300a32;
                  uRam300a32 = uRam300a28 + uRam300a32;
                  if (((bVar6 || bVar1) != (uRam300a32 != 0xffff) || uRam300a32 != 0xffff) &&
                      ((bVar6 || bVar1) || uRam300a32 == 0xffff)) {
                    uRam300a32 = 0xffff;
                  }
                }
                cRam300a74 = '\x18';
                uVar7 = 0x18;
                iVar3 = iVar4;
              }
              else {
                if (uRam300a1e < uRam300a28) {
                  sRam300a50 = sRam010374;
                  uRam300a20 = uRam300a30 - uRam300a1e;
                  if ((short)-(ushort)(uRam300a30 < uRam300a1e) < 0) {
                    uRam300a20 = 0;
                  }
                  uRam300a28 = uRam300a1e;
                }
                else {
                  bVar6 = sRam300a50 == 0;
                  sRam300a50 = sRam300a50 + -1;
                  if ((short)-(ushort)bVar6 < 0) {
                    sRam300a50 = 0;
                  }
                }
                cRam300a70 = sRam300a50 == 0;
                if ((bool)cRam300a70) {
                  if (uRam300a20 < uRam300a22) {
                    uRam300a22 = uRam300a20;
                  }
                  if (uRam300a24 < uRam300a20) {
                    uRam300a24 = uRam300a20;
                  }
                  if (cRam300a55 == '\0') {
                    uStack_2a = uRam0101d2;
                  }
                  else {
                    uStack_2a = uRam0101d0;
                  }
                  if ((cRam300a55 != '\0') || (uStack_2a < uRam300a20)) {
                    cRam300a57 = '\0';
                  }
                  else {
                    cRam300a57 = '\x01';
                  }
                  if ((cRam300a57 == '\0') &&
                     (((uStack_2a < uRam300a20 &&
                       (sVar2 = -(ushort)(uRam300a24 < uRam300a22),
                       bVar6 = uRam300a24 - uRam300a22 < uRam010264,
                       (short)(sVar2 - (ushort)bVar6) < 0 !=
                       (sVar2 < 0 && (short)(sVar2 - (ushort)bVar6) < 0 != sVar2 < 0))) ||
                      (cRam300a55 == '\0')))) {
                    cRam300a56 = '\0';
                  }
                  else {
                    cRam300a56 = '\x01';
                  }
                }
                bVar6 = uRam300a42 + 1 < uRam300a42;
                bVar1 = uRam300a42 == 0xffff;
                uVar7 = uRam300a42 + 1;
                uRam300a42 = uVar7;
                iVar3 = CONCAT22(MDH,MDL);
                if (((bVar6 || bVar1) != (uVar7 != 0xffff) || uVar7 != 0xffff) &&
                    ((bVar6 || bVar1) || uVar7 == 0xffff)) {
                  uVar7 = 0xffff;
                  uRam300a42 = uVar7;
                }
              }
            }
          }
        }
      }
    }
    break;
  default:
    if (cRam300a5f == '\0') {
      if (((((cRam300a6d == '\0') && (cRam300a61 == '\0')) && (cRam300a5c == '\0')) &&
          ((cRam300a58 == '\0' || (sRam300a48 == 0)))) || (sRam300a3a != 0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (bVar6) {
        uRam300a76 = 0xc;
        if (cRam300a69 == '\0') {
          uRam300a52 = 1;
          uRam300a24 = 0;
          uRam024a28 = uRam024266;
          uRam300a22 = uRam024266;
          if (cRam300a55 == '\0') {
            uRam024a18 = uRam024312;
          }
          else {
            uRam024a18 = uRam024310;
          }
        }
        cRam300a74 = '\x14';
        uVar7 = func_0x0a8b6e();
        iVar3 = CONCAT22(MDH,MDL);
      }
      else {
        if (((cRam300a58 == '\0') || (sRam300a48 != 0)) || (sRam300a3a != 0)) {
          bVar6 = false;
        }
        else {
          bVar6 = true;
        }
        if (bVar6) {
          uRam300a76 = 1;
          cRam300a74 = '(';
          uVar7 = 1;
          iVar3 = CONCAT22(MDH,MDL);
        }
        else {
          uVar7 = 0;
          iVar3 = CONCAT22(MDH,MDL);
        }
      }
    }
    else {
      uRam300a76 = 0;
      func_0x0a8b02();
      cRam300a74 = '\n';
      uVar7 = 10;
      iVar3 = CONCAT22(MDH,MDL);
    }
  }
  MDH = (undefined2)((uint)iVar3 >> 0x10);
  MDL = (undefined2)iVar3;
  return uVar7;
}


