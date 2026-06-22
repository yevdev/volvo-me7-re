// Pseudo-C of key Volvo ME7.0 (50GPHJ) control functions
// Ghidra 12.1 + keyhana C166 module. C166 has no Hex-Rays decompiler;
// this is Ghidra's SLEIGH-based pseudo-C, best read alongside the IDA disassembly dumps.

// ================= FUN_041a68 @ 041a68 =================

ushort FUN_041a68(ushort param_1,ushort param_2,ushort param_3)

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


// ================= FUN_041cc0 @ 041cc0 =================

ushort FUN_041cc0(ushort param_1,ushort param_2,ushort param_3,ushort param_4)

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


// ================= FUN_0411f4 @ 0411f4 =================

short FUN_0411f4(short param_1,ushort param_2,ushort param_3,ushort param_4)

{
  ushort uVar1;
  int iVar2;
  short sVar3;
  short sVar4;
  
  uVar1 = param_1 + (param_3 >> 8) * (ushort)*(byte *)((uint3)param_2 + 0x10000) + (param_4 >> 8);
  sVar4 = (short)*(char *)((uint3)uVar1 + 0x10000);
  param_4 = param_4 & 0xff;
  if (param_4 != 0) {
    sVar4 = sVar4 + (short)((uint)((int)((*(char *)((uint3)uVar1 + 0x10001) - sVar4) * 2) *
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


// ================= FUN_0dbb04 @ 0dbb04 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0dbb04(void)

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
  
  uVar4 = ((uint)DAT_02b410 * (uint)DAT_02be38 >> 0x10) * (uint)_DAT_302968;
  MDL = (ushort)uVar4;
  MDH = (ushort)(uVar4 >> 0x10);
  MDC = MDC | 0x10;
  sVar12 = (short)((uVar4 >> 10) >> 0x10);
  _DAT_302e64 = (ushort)(uVar4 >> 10);
  bVar1 = _DAT_302e64 != 0xffff;
  if (sVar12 != 0 || !bVar1) {
    _DAT_302e64 = 0xffff;
  }
  if ((DAT_01be46 & 1) == 0) {
    _DAT_302e66 = FUN_041a68(0x3e92,10,_DAT_302e3e,sVar12 - (ushort)bVar1);
  }
  else {
    _DAT_302e66 = 0;
  }
  _DAT_302e62 = _DAT_302e64 + _DAT_302e66;
  if (_DAT_302e64 + _DAT_302e66 < _DAT_302e64 || _DAT_302e64 + _DAT_302e66 < _DAT_302e66) {
    _DAT_302e62 = -1;
  }
  uVar4 = CONCAT22(_DAT_302496 >> 5,_DAT_302496 << 0xb);
  uVar2 = uVar4 / _DAT_30294a;
  MDL = (ushort)uVar2;
  MDH = (ushort)(uVar4 % (uint)_DAT_30294a);
  MDC = MDC | 0x10;
  _DAT_302e58 = MDL;
  if (_DAT_30294a == 0 || 0xffff < uVar2) {
    _DAT_302e58 = 0xffff;
  }
  _DAT_302e68 = FUN_043904(DAT_02bf32,DAT_02ae58,_DAT_302e6a,_DAT_302e68);
  uVar8 = FUN_041a68((short)&DAT_013e3a,10,FUN_00f40e);
  sVar12 = _DAT_302e58 - _DAT_302e6a;
  if (_DAT_302e58 < _DAT_302e6a) {
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
  _DAT_302e52 = (ushort)iVar5;
  uVar8 = (ushort)(_DAT_302e52 < 0x7fff);
  if (uVar9 == uVar8 && _DAT_302e52 == 0x7fff ||
      (short)(uVar9 - uVar8) < 0 !=
      (iVar5 < 0 && (short)(uVar9 - (_DAT_302e52 < 0x7fff)) < 0 != iVar5 < 0)) {
    if ((short)((uVar9 + 1) - (ushort)(_DAT_302e52 < 0x8000)) < 0 !=
        (-1 < iVar5 && (short)((uVar9 + 1) - (ushort)(_DAT_302e52 < 0x8000)) < 0 != iVar5 < 0)) {
      _DAT_302e52 = 0x8000;
    }
  }
  else {
    _DAT_302e52 = 0x7fff;
  }
  _DAT_302e5c = FUN_041b5a((short)&DAT_013e74,10,_DAT_302e52);
  iVar5 = (uint)DAT_02ae3c * (uint)DAT_02bf2e;
  MDL = (ushort)iVar5;
  MDH = (ushort)((uint)iVar5 >> 0x10);
  MDC = MDC | 0x10;
  if ((iVar5 < 0) || ((BADTYPE)(MDH >> 0xe & 1))) {
    uVar8 = 0xffff;
  }
  else {
    uVar8 = MDH << 2 | MDL >> 0xe;
  }
  _DAT_302e70 = FUN_043904(DAT_02bf30,uVar8,_DAT_302e72,_DAT_302e70);
  uVar9 = (ushort)((uint)_DAT_302e70 >> 0x10);
  _DAT_302e50 = uVar8 - uVar9;
  if (uVar8 < uVar9) {
    if (_DAT_302e50 >= 0) {
      _DAT_302e50 = -0x8000;
    }
  }
  else if (_DAT_302e50 < 0) {
    _DAT_302e50 = 0x7fff;
  }
  _DAT_302e5a = FUN_041b5a(0x3e56,10,_DAT_302e50);
  sVar12 = _DAT_302e5c + _DAT_302e5a;
  if (_DAT_302e5c < 0 == _DAT_302e5a < 0 && _DAT_302e5c + _DAT_302e5a < 0 != _DAT_302e5c < 0) {
    sVar12 = 0x7fff;
  }
  sVar11 = sVar12 + _DAT_30bf0a;
  if (sVar12 < 0 == _DAT_30bf0a < 0 && sVar12 + _DAT_30bf0a < 0 != sVar12 < 0) {
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
  uVar9 = FUN_041cc0((short)&DAT_013eca,10,_DAT_302e62,_DAT_302e3e);
  uVar13 = CONCAT22(_DAT_302e6e,_DAT_302e6c);
  if ((short)uVar8 < 0) {
    _DAT_302e5e = uVar8 + uVar9;
    if (uVar8 <= uVar8 + uVar9 && uVar9 <= uVar8 + uVar9) {
      _DAT_302e5e = 0;
    }
  }
  else {
    _DAT_302e5e = uVar8 + uVar9;
    if (uVar8 + uVar9 < uVar8 || uVar8 + uVar9 < uVar9) {
      _DAT_302e5e = 0xffff;
    }
  }
  uVar8 = _DAT_302e5e;
  uVar6 = _DAT_302e68;
  uVar7 = _DAT_302e70;
  if (_DAT_305630 < DAT_01be47) {
    _DAT_302e56 = _DAT_302e3c - _DAT_302e38;
    if (_DAT_302e3c < _DAT_302e38) {
      _DAT_302e56 = 0;
    }
    uVar10 = FUN_041a68((short)&DAT_013eac,10,_DAT_302e56);
    uVar13 = FUN_043904(uVar10,0,_DAT_302e6e,_DAT_302e6c);
    _DAT_302e54 = (ushort)((uint)uVar13 >> 0x10);
    uVar8 = _DAT_302e54 + _DAT_302e5e;
    uVar6 = _DAT_302e68;
    uVar7 = _DAT_302e70;
    if (_DAT_302e54 + _DAT_302e5e < _DAT_302e54 || _DAT_302e54 + _DAT_302e5e < _DAT_302e5e) {
      uVar8 = 0xffff;
    }
  }
  _DAT_302e60 = uVar8;
  _DAT_302e6e = (undefined2)((uint)uVar13 >> 0x10);
  _DAT_302e6c = (undefined2)uVar13;
  _DAT_302e72 = (undefined2)((uint)uVar7 >> 0x10);
  _DAT_302e70 = (undefined2)uVar7;
  _DAT_302e6a = (ushort)((uint)uVar6 >> 0x10);
  _DAT_302e68 = (undefined2)uVar6;
  return;
}


// ================= FUN_0dbf44 @ 0dbf44 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0dbf44(void)

{
  int iVar1;
  bool bVar2;
  ushort uVar3;
  ushort uVar4;
  
  if ((DAT_301868 & 1) == 0) {
    if ((DAT_30186b < DAT_01be69) && (_DAT_302e34 < DAT_02bf4a)) {
      if (((DAT_301869 & 1) == 0) && (_DAT_302e34 < DAT_02bf4a)) {
        DAT_301869 = DAT_301869 | 2;
      }
    }
    else {
      DAT_301869 = DAT_301869 & 0xfd;
    }
    if (((DAT_301869 & 2) != 0) && (DAT_301869 = DAT_301869 | 1, DAT_30186b != 0xff)) {
      DAT_30186b = DAT_30186b + 1;
    }
  }
  if (((_DAT_30256a & 8) == 0) &&
     ((((uRam00fd0e & 0x1000) != 0 || ((DAT_301869 & 2) != 0)) || ((FUN_00fd7c & 0x2000) != 0)))) {
    DAT_301867 = DAT_301867 | 6;
  }
  else {
    DAT_301867 = DAT_301867 & 0xf9;
  }
  if ((DAT_01be46 & 1) != 0) {
    if (((uRam00fd22 & 0x80) == 0) && ((DAT_301868 & 2) == 0)) {
      uRam00ff10 = uRam00ff10 & 0xffbf;
      bVar2 = false;
    }
    else {
      uRam00ff10 = uRam00ff10 | 0x40;
      bVar2 = true;
    }
    if ((short)DAT_02bf4c < 0) {
      uVar3 = DAT_02bf4c + DAT_02ae3e;
      if (DAT_02bf4c <= DAT_02bf4c + DAT_02ae3e && DAT_02ae3e <= DAT_02bf4c + DAT_02ae3e) {
        uVar3 = 0;
      }
    }
    else {
      uVar3 = DAT_02bf4c + DAT_02ae3e;
      if (DAT_02bf4c + DAT_02ae3e < DAT_02bf4c || DAT_02bf4c + DAT_02ae3e < DAT_02ae3e) {
        uVar3 = 0xffff;
      }
    }
    if (_DAT_302e38 < uVar3) {
      uRam00ff10 = uRam00ff10 | 0x40;
    }
    else {
      uRam00ff10 = uRam00ff10 & 0xffbf;
    }
    uVar3 = (uRam00ff10 & 0x40) >> 6;
    if (((DAT_30186f & 0x10) != 0) || (bVar2)) {
      if (bVar2) {
        _DAT_302e82 = DAT_017720;
        DAT_30186f = DAT_30186f & 0xdf;
      }
      else if (_DAT_302e82 == 0) {
        DAT_30186f = DAT_30186f | 0x20;
      }
      else {
        _DAT_302e82 = _DAT_302e82 + -1;
      }
      if (((bVar2) || (uVar3 == 0)) && ((DAT_30186f & 0x20) == 0)) {
        if (bVar2) {
          DAT_30186f = DAT_30186f | 0x10;
        }
      }
      else {
        DAT_30186f = DAT_30186f & 0xef;
      }
    }
    if (((DAT_30186f & 0x40) != 0) || ((uRam00fd7a & 0x8000) == 0)) {
      if ((uRam00fd7a & 0x8000) == 0) {
        _DAT_302e80 = DAT_017720;
        DAT_30186f = DAT_30186f & 0x7f;
      }
      else if (_DAT_302e80 == 0) {
        DAT_30186f = DAT_30186f | 0x80;
      }
      else {
        _DAT_302e80 = _DAT_302e80 + -1;
      }
      if ((uVar3 == 0) && ((DAT_30186f & 0x80) == 0)) {
        if ((DAT_301869 & 4) == 0) {
          if ((short)DAT_02bf4c < 0) {
            uVar3 = DAT_02bf4c + DAT_02ae3c;
            if (DAT_02bf4c <= DAT_02bf4c + DAT_02ae3c && DAT_02ae3c <= DAT_02bf4c + DAT_02ae3c) {
              uVar3 = 0;
            }
          }
          else {
            uVar3 = DAT_02bf4c + DAT_02ae3c;
            if (DAT_02bf4c + DAT_02ae3c < DAT_02bf4c || DAT_02bf4c + DAT_02ae3c < DAT_02ae3c) {
              uVar3 = 0xffff;
            }
          }
          if (uVar3 <= _DAT_302e38) {
            DAT_30186f = DAT_30186f | 0x40;
          }
        }
      }
      else {
        DAT_30186f = DAT_30186f & 0xbf;
      }
      if ((DAT_30186f & 0x40) != 0) {
        DAT_301869 = DAT_301869 | 4;
      }
    }
  }
  if (((DAT_30186f & 0x10) == 0) && ((DAT_30186f & 0x40) == 0)) {
    DAT_301867 = DAT_301867 & 0xf7;
  }
  else {
    DAT_301867 = DAT_301867 | 8;
  }
  _DAT_302e7a = FUN_042464(DAT_02bf34,0x3f35,10,0x3f3c,10,DAT_30183c);
  uVar3 = _DAT_302e60 >> 1;
  if ((short)_DAT_302e4a < 0) {
    uVar4 = _DAT_302e4a + uVar3;
    if (_DAT_302e4a <= _DAT_302e4a + uVar3 && uVar3 <= _DAT_302e4a + uVar3) {
      uVar4 = 0;
    }
  }
  else {
    uVar4 = _DAT_302e4a + uVar3;
    if (_DAT_302e4a + uVar3 < _DAT_302e4a || _DAT_302e4a + uVar3 < uVar3) {
      uVar4 = 0xffff;
    }
  }
  iVar1 = (uint)uVar4 * (uint)_DAT_302e7a;
  MDL = (ushort)iVar1;
  MDH = (ushort)((uint)iVar1 >> 0x10);
  MDC = MDC | 0x10;
  if ((iVar1 < 0) || ((BADTYPE)(MDH >> 0xe & 1))) {
    _DAT_302e7c = 0xffff;
  }
  else {
    _DAT_302e7c = MDH << 2 | (ushort)iVar1 >> 0xe;
  }
  if (((DAT_01be49 & 1) == 0) || (((DAT_301872 & 1) == 0 && ((_DAT_303abc & 1) == 0)))) {
    DAT_30186f = DAT_30186f & 0xfe;
    bVar2 = false;
  }
  else {
    DAT_30186f = DAT_30186f | 1;
    bVar2 = true;
  }
  if ((DAT_301867 & 2) == 0) {
    if ((DAT_01be4a & 1) == 0) {
      _DAT_302e7e = 0;
      uVar3 = _DAT_302e7e;
    }
    else {
      _DAT_302e7e = 0xffff;
      uVar3 = _DAT_302e7e;
    }
    goto LAB_0dc296;
  }
  if ((!bVar2) && ((DAT_301868 & 2) == 0)) {
    if ((DAT_301867 & 8) != 0) {
      uVar3 = (ushort)DAT_01be66 << 8;
      goto LAB_0dc296;
    }
    if (_DAT_302e7c < DAT_02bf4e) {
      DAT_02ae7e = DAT_02bf4e;
      uVar3 = _DAT_302e7e;
      goto LAB_0dc296;
    }
    uVar3 = _DAT_302e7c;
    if (_DAT_302e7c <= DAT_02bf50) goto LAB_0dc296;
  }
  DAT_02ae7e = DAT_02bf50;
  uVar3 = _DAT_302e7e;
LAB_0dc296:
  _DAT_302e7e = uVar3;
  if (((_DAT_302e7c < DAT_02bf50) || (_DAT_302e42 < 1)) &&
     ((DAT_02bf4e < _DAT_302e7c || (-1 < _DAT_302e42)))) {
    DAT_301867 = DAT_301867 & 0xfe;
  }
  else {
    DAT_301867 = DAT_301867 | 1;
  }
  if ((DAT_30186f & 2) == 0) {
    DAT_30186f = DAT_30186f & 0xfb;
  }
  else {
    DAT_30186f = DAT_30186f | 4;
  }
  if ((uRam00fd22 & 0x80) == 0) {
    DAT_30186f = DAT_30186f & 0xf7;
  }
  else {
    DAT_30186f = DAT_30186f | 8;
  }
  return;
}


// ================= FUN_043904 @ 043904 =================

int FUN_043904(ushort param_1,ushort param_2,ushort param_3,ushort param_4)

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


// ================= FUN_0518b8 @ 0518b8 =================

/* WARNING: Removing unreachable block (ram,0x051986) */
/* WARNING: Removing unreachable block (ram,0x0518ee) */
/* WARNING: Removing unreachable block (ram,0x0519f2) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0518b8(void)

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
  
  cVar5 = FUN_0411f4(0x33b1,0x502a,_DAT_3019b6,_DAT_3019ca);
  sVar7 = (short)cVar5;
  cVar5 = FUN_0411f4(0x3471,0x502a,_DAT_3019b6,_DAT_3019ca);
  sVar8 = (short)cVar5 * (ushort)DAT_30129c;
  uVar9 = 0xff - DAT_30129c;
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
  _DAT_3024a8 = sVar7 + sVar8;
  if (sVar7 < 0 == sVar8 < 0 && sVar7 + sVar8 < 0 != sVar7 < 0) {
    _DAT_3024a8 = 0x7fff;
  }
  cVar5 = FUN_0411f4(0x3531,0x502a,_DAT_3019b6,_DAT_3019ca);
  sVar7 = (short)cVar5;
  cVar5 = FUN_0411f4(0x35f1,0x502a,_DAT_3019b6,_DAT_3019ca);
  sVar8 = (short)cVar5 * (ushort)DAT_30129c;
  uVar9 = 0xff - DAT_30129c;
  if ((short)uVar9 < 0) {
    sVar7 = sVar7 * (uVar9 & 0x7fff) + sVar7 * -0x8000;
  }
  else {
    sVar7 = sVar7 * uVar9;
  }
  _DAT_3024aa = sVar7 + sVar8;
  if (sVar7 < 0 == sVar8 < 0 && sVar7 + sVar8 < 0 != sVar7 < 0) {
    _DAT_3024aa = 0x7fff;
  }
  uVar9 = (ushort)((int)_DAT_3024aa * (int)(short)(ushort)DAT_30129b) >> 8 |
          (short)((uint)((int)_DAT_3024aa * (int)(short)(ushort)DAT_30129b) >> 0x10) << 8;
  uVar1 = 0xff - DAT_30129b;
  if ((short)uVar1 < 0) {
    iVar4 = (int)_DAT_3024a8 * (int)(short)(uVar1 & 0x7fff);
    uVar2 = (ushort)iVar4;
    uVar1 = _DAT_3024a8 * -0x8000;
    iVar3 = CONCAT22((short)((uint)iVar4 >> 0x10) + (_DAT_3024a8 >> 1) +
                     (ushort)(uVar2 + uVar1 < uVar2 || uVar2 + uVar1 < uVar1),uVar2 + uVar1);
  }
  else {
    iVar3 = (int)_DAT_3024a8 * (int)(short)uVar1;
    iVar4 = iVar3;
  }
  MDH = (undefined2)((uint)iVar4 >> 0x10);
  MDL = (undefined2)iVar4;
  MDC = MDC | 0x10;
  uVar1 = (ushort)iVar3 >> 8 | (short)((uint)iVar3 >> 0x10) << 8;
  _DAT_3024ac = uVar1 + uVar9;
  if ((short)uVar1 < 0 == (short)uVar9 < 0 && (short)(uVar1 + uVar9) < 0 != (short)uVar1 < 0) {
    _DAT_3024ac = 0x7fff;
  }
  uVar9 = _DAT_3024ac;
  if ((short)_DAT_3024ac < 0) {
    if (_DAT_3024ac == 0x8000) {
      uVar9 = 0x7fff;
    }
    else {
      uVar9 = -_DAT_3024ac;
    }
  }
  sVar7 = (short)uVar9 >> 8;
  if ((((uVar9 & 0x80) == 0) ||
      (sVar8 = sVar7 + 1,
      (short)&DAT_01ff82 + sVar7 < 0 == (sVar7 < 0 && (short)&DAT_01ff82 + sVar7 < 0 != sVar7 < 0)))
     || (sVar8 == -0x80 || sVar7 + 0x81 < 0 != (-1 < sVar8 && sVar7 + 0x81 < 0 != sVar8 < 0))) {
    sVar8 = sVar7;
  }
  DAT_30132f = (char)sVar8;
  if ((short)_DAT_3024ac < 0) {
    DAT_30132f = -DAT_30132f;
  }
  cVar5 = DAT_3012fd + DAT_3012fe;
  if (DAT_3012fd < '\0' == DAT_3012fe < '\0' &&
      (char)(DAT_3012fd + DAT_3012fe) < '\0' != DAT_3012fd < '\0') {
    cVar5 = '\x7f';
  }
  cVar6 = cVar5 + DAT_304050;
  if (cVar5 < '\0' == DAT_304050 < '\0' && (char)(cVar5 + DAT_304050) < '\0' != cVar5 < '\0') {
    cVar6 = '\x7f';
  }
  DAT_30132e = cVar6 + DAT_30132f;
  if (cVar6 < '\0' == DAT_30132f < '\0' && (char)(cVar6 + DAT_30132f) < '\0' != cVar6 < '\0') {
    DAT_30132e = '\x7f';
  }
  return;
}


// ================= FUN_05086a @ 05086a =================

void FUN_05086a(void)

{
  short sVar1;
  ushort uVar2;
  short sVar3;
  
  sVar1 = ((short)DAT_30132e + (short)DAT_30157c + (short)DAT_3014f6 + (short)(char)PTR_FUN_012d85)
          - (ushort)bRam00f3fa;
  uVar2 = (ushort)DAT_30125d;
  if ((uRam00fd24 & 0x4000) == 0) {
    sVar3 = (short)DAT_30131d + (short)DAT_3014f6 + (short)(char)PTR_FUN_012d85;
  }
  else {
    sVar3 = sVar1 + *(char *)((uint3)uVar2 + 0x301545);
  }
  if (sVar3 == 0x7f || sVar3 + -0x7f < 0 != (sVar3 < 0 && sVar3 + -0x7f < 0 != sVar3 < 0)) {
    if (sVar3 + 0x80 < 0 == (-1 < sVar3 && sVar3 + 0x80 < 0 != sVar3 < 0)) {
      DAT_019313 = (undefined1)sVar3;
    }
    else {
      DAT_019313 = 0x80;
    }
  }
  else {
    DAT_019313 = 0x7f;
  }
  uRam00f337 = DAT_019313;
  if (uVar2 < 4) {
    uVar2 = uVar2 + 1;
  }
  else {
    uVar2 = 0;
  }
  sVar3 = sVar1 + *(char *)((uint3)uVar2 + 0x301545);
  if (sVar3 == 0x7f || sVar3 + -0x7f < 0 != (sVar3 < 0 && sVar3 + -0x7f < 0 != sVar3 < 0)) {
    if (sVar3 + 0x80 < 0 == (-1 < sVar3 && sVar3 + 0x80 < 0 != sVar3 < 0)) {
      DAT_019314 = (undefined1)sVar3;
    }
    else {
      DAT_019314 = 0x80;
    }
  }
  else {
    DAT_019314 = 0x7f;
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
      DAT_019315 = (undefined1)sVar3;
    }
    else {
      DAT_019315 = 0x80;
    }
  }
  else {
    DAT_019315 = 0x7f;
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
      DAT_019316 = (undefined1)sVar1;
    }
    else {
      DAT_019316 = 0x80;
    }
  }
  else {
    DAT_019316 = 0x7f;
  }
  return;
}


// ================= FUN_050984 @ 050984 =================

void FUN_050984(void)

{
  char cVar1;
  
  if ((uRam00fd22 & 0x80) != 0) {
    uRam00fd22 = uRam00fd22 | 0x1000;
  }
  if ((uRam00fd22 & 0x1000) != 0) {
    cRam00f338 = DAT_301329;
    DAT_019317 = DAT_301329 + DAT_301312;
    if (DAT_301329 < '\0' == DAT_301312 < '\0' &&
        (char)(DAT_301329 + DAT_301312) < '\0' != DAT_301329 < '\0') {
      DAT_019317 = 0x7f;
    }
    if (DAT_019317 == 0x50 ||
        (char)(DAT_019317 + 0xb0) < '\0' !=
        ((char)DAT_019317 < '\0' && (char)(DAT_019317 + 0xb0) < '\0' != (char)DAT_019317 < '\0')) {
      if ((char)(DAT_019317 + 0x20) < '\0' !=
          (-1 < (char)DAT_019317 && (char)(DAT_019317 + 0x20) < '\0' != (char)DAT_019317 < '\0')) {
        DAT_019317 = 0xe0;
      }
    }
    else {
      DAT_019317 = 0x50;
    }
    DAT_019318 = DAT_019317;
    DAT_019319 = DAT_019317;
    DAT_01931a = DAT_019317;
    goto LAB_050b7c;
  }
  if (((uRam00fd04 & 2) == 0) && ((uRam00fd22 & 0x4000) == 0)) {
    cVar1 = DAT_301329;
    if ((char)(DAT_301320 - DAT_301329) < '\0' ==
        (DAT_301320 < '\0' != DAT_301329 < '\0' &&
        (char)(DAT_301320 - DAT_301329) < '\0' != DAT_301320 < '\0')) {
      cVar1 = DAT_301320;
    }
    if (cVar1 == cRam009313 ||
        (char)(cVar1 - cRam009313) < '\0' !=
        (cVar1 < '\0' != cRam009313 < '\0' && (char)(cVar1 - cRam009313) < '\0' != cVar1 < '\0')) {
      DAT_019317 = cVar1 + DAT_301312;
      cRam00f338 = cVar1;
      if (cVar1 < '\0' == DAT_301312 < '\0' && (char)(cVar1 + DAT_301312) < '\0' != cVar1 < '\0') {
        DAT_019317 = 0x7f;
      }
    }
    else {
      cRam00f338 = DAT_019313;
      DAT_019317 = DAT_019313 + DAT_301312;
      if (DAT_019313 < '\0' == DAT_301312 < '\0' &&
          (char)(DAT_019313 + DAT_301312) < '\0' != DAT_019313 < '\0') {
        DAT_019317 = 0x7f;
      }
    }
    if (DAT_019317 == 0x50 ||
        (char)(DAT_019317 + 0xb0) < '\0' !=
        ((char)DAT_019317 < '\0' && (char)(DAT_019317 + 0xb0) < '\0' != (char)DAT_019317 < '\0')) {
      if ((char)(DAT_019317 + 0x20) < '\0' !=
          (-1 < (char)DAT_019317 && (char)(DAT_019317 + 0x20) < '\0' != (char)DAT_019317 < '\0')) {
        DAT_019317 = 0xe0;
      }
    }
    else {
      DAT_019317 = 0x50;
    }
    if (cVar1 == cRam009314 ||
        (char)(cVar1 - cRam009314) < '\0' !=
        (cVar1 < '\0' != cRam009314 < '\0' && (char)(cVar1 - cRam009314) < '\0' != cVar1 < '\0')) {
      DAT_019318 = cVar1 + DAT_301312;
      if (cVar1 < '\0' == DAT_301312 < '\0' && (char)(cVar1 + DAT_301312) < '\0' != cVar1 < '\0') {
        DAT_019318 = 0x7f;
      }
    }
    else {
      DAT_019318 = DAT_019314 + DAT_301312;
      if (DAT_019314 < '\0' == DAT_301312 < '\0' &&
          (char)(DAT_019314 + DAT_301312) < '\0' != DAT_019314 < '\0') {
        DAT_019318 = 0x7f;
      }
    }
    if (DAT_019318 == 0x50 ||
        (char)(DAT_019318 + 0xb0) < '\0' !=
        ((char)DAT_019318 < '\0' && (char)(DAT_019318 + 0xb0) < '\0' != (char)DAT_019318 < '\0')) {
      if ((char)(DAT_019318 + 0x20) < '\0' !=
          (-1 < (char)DAT_019318 && (char)(DAT_019318 + 0x20) < '\0' != (char)DAT_019318 < '\0')) {
        DAT_019318 = 0xe0;
      }
    }
    else {
      DAT_019318 = 0x50;
    }
    if (cVar1 == cRam009315 ||
        (char)(cVar1 - cRam009315) < '\0' !=
        (cVar1 < '\0' != cRam009315 < '\0' && (char)(cVar1 - cRam009315) < '\0' != cVar1 < '\0')) {
      DAT_019319 = cVar1 + DAT_301312;
      if (cVar1 < '\0' == DAT_301312 < '\0' && (char)(cVar1 + DAT_301312) < '\0' != cVar1 < '\0') {
        DAT_019319 = 0x7f;
      }
    }
    else {
      DAT_019319 = DAT_019315 + DAT_301312;
      if (DAT_019315 < '\0' == DAT_301312 < '\0' &&
          (char)(DAT_019315 + DAT_301312) < '\0' != DAT_019315 < '\0') {
        DAT_019319 = 0x7f;
      }
    }
    if (DAT_019319 == 0x50 ||
        (char)(DAT_019319 + 0xb0) < '\0' !=
        ((char)DAT_019319 < '\0' && (char)(DAT_019319 + 0xb0) < '\0' != (char)DAT_019319 < '\0')) {
      if ((char)(DAT_019319 + 0x20) < '\0' !=
          (-1 < (char)DAT_019319 && (char)(DAT_019319 + 0x20) < '\0' != (char)DAT_019319 < '\0')) {
        DAT_019319 = 0xe0;
      }
    }
    else {
      DAT_019319 = 0x50;
    }
    if (cVar1 == cRam009316 ||
        (char)(cVar1 - cRam009316) < '\0' !=
        (cVar1 < '\0' != cRam009316 < '\0' && (char)(cVar1 - cRam009316) < '\0' != cVar1 < '\0'))
    goto LAB_050b5c;
    DAT_01931a = DAT_019316 + DAT_301312;
    if (DAT_019316 < '\0' == DAT_301312 < '\0' &&
        (char)(DAT_019316 + DAT_301312) < '\0' != DAT_019316 < '\0') {
      DAT_01931a = 0x7f;
    }
  }
  else {
    cRam00f338 = DAT_019313;
    DAT_019317 = DAT_019313 + DAT_301312;
    if (DAT_019313 < '\0' == DAT_301312 < '\0' &&
        (char)(DAT_019313 + DAT_301312) < '\0' != DAT_019313 < '\0') {
      DAT_019317 = 0x7f;
    }
    if (DAT_019317 == 0x50 ||
        (char)(DAT_019317 + 0xb0) < '\0' !=
        ((char)DAT_019317 < '\0' && (char)(DAT_019317 + 0xb0) < '\0' != (char)DAT_019317 < '\0')) {
      if ((char)(DAT_019317 + 0x20) < '\0' !=
          (-1 < (char)DAT_019317 && (char)(DAT_019317 + 0x20) < '\0' != (char)DAT_019317 < '\0')) {
        DAT_019317 = 0xe0;
      }
    }
    else {
      DAT_019317 = 0x50;
    }
    DAT_019318 = DAT_019314 + DAT_301312;
    if (DAT_019314 < '\0' == DAT_301312 < '\0' &&
        (char)(DAT_019314 + DAT_301312) < '\0' != DAT_019314 < '\0') {
      DAT_019318 = 0x7f;
    }
    if (DAT_019318 == 0x50 ||
        (char)(DAT_019318 + 0xb0) < '\0' !=
        ((char)DAT_019318 < '\0' && (char)(DAT_019318 + 0xb0) < '\0' != (char)DAT_019318 < '\0')) {
      if ((char)(DAT_019318 + 0x20) < '\0' !=
          (-1 < (char)DAT_019318 && (char)(DAT_019318 + 0x20) < '\0' != (char)DAT_019318 < '\0')) {
        DAT_019318 = 0xe0;
      }
    }
    else {
      DAT_019318 = 0x50;
    }
    DAT_019319 = DAT_019315 + DAT_301312;
    if (DAT_019315 < '\0' == DAT_301312 < '\0' &&
        (char)(DAT_019315 + DAT_301312) < '\0' != DAT_019315 < '\0') {
      DAT_019319 = 0x7f;
    }
    cVar1 = DAT_019316;
    if (DAT_019319 == 0x50 ||
        (char)(DAT_019319 + 0xb0) < '\0' !=
        ((char)DAT_019319 < '\0' && (char)(DAT_019319 + 0xb0) < '\0' != (char)DAT_019319 < '\0')) {
      if ((char)(DAT_019319 + 0x20) < '\0' !=
          (-1 < (char)DAT_019319 && (char)(DAT_019319 + 0x20) < '\0' != (char)DAT_019319 < '\0')) {
        DAT_019319 = 0xe0;
      }
    }
    else {
      DAT_019319 = 0x50;
    }
LAB_050b5c:
    DAT_01931a = cVar1 + DAT_301312;
    if (cVar1 < '\0' == DAT_301312 < '\0' && (char)(cVar1 + DAT_301312) < '\0' != cVar1 < '\0') {
      DAT_01931a = 0x7f;
    }
  }
  if (DAT_01931a == 0x50 ||
      (char)(DAT_01931a + 0xb0) < '\0' !=
      ((char)DAT_01931a < '\0' && (char)(DAT_01931a + 0xb0) < '\0' != (char)DAT_01931a < '\0')) {
    if ((char)(DAT_01931a + 0x20) < '\0' !=
        (-1 < (char)DAT_01931a && (char)(DAT_01931a + 0x20) < '\0' != (char)DAT_01931a < '\0')) {
      DAT_01931a = 0xe0;
    }
  }
  else {
    DAT_01931a = 0x50;
  }
LAB_050b7c:
  if (cRam00f338 == DAT_301313) {
    uRam00fd22 = uRam00fd22 | 0x800;
    bRam00f339 = bRam00f339 | (byte)(1 << (ushort)DAT_30125d);
  }
  else {
    uRam00fd22 = uRam00fd22 & 0xf7ff;
    bRam00f339 = bRam00f339 & ~(byte)(1 << (ushort)DAT_30125d);
  }
  if (DAT_30125d == 0) {
    DAT_30131c = DAT_019317;
  }
  DAT_30131b = ~DAT_019317;
  bRam00f33a = DAT_019317;
  return;
}


// ================= FUN_07bd04 @ 07bd04 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ushort FUN_07bd04(void)

{
  bool bVar1;
  ushort uVar2;
  uint uVar3;
  ushort uVar4;
  
  uVar3 = _DAT_3006d4;
  if ((uRam00fd46 & 1) == 0) {
    uVar4 = (ushort)bRam00f3fa;
    if (bRam00f3fa == 0) {
      uRam00fd44 = uRam00fd44 & 0x3fff;
      DAT_301571 = 0;
    }
    else {
      DAT_301573 = DAT_301573 + -1;
      if (DAT_301573 == '\0') {
        bVar1 = bRam00f3fa < DAT_0139b8;
        bRam00f3fa = bRam00f3fa - DAT_0139b8;
        if (bVar1) {
          bRam00f3fa = 0;
        }
        uVar4 = (ushort)bRam00f3fa;
        DAT_301573 = DAT_0139ba;
        if (bRam00f3fa == 0) {
          uRam00fd44 = uRam00fd44 & 0x3fff;
          DAT_301571 = 0;
        }
      }
    }
  }
  else {
    if (DAT_301518 == 0) {
      bRam00f3fb = bRam00f3fb - 1;
    }
    uVar4 = (ushort)bRam00f3fb;
    if (bRam00f3fb == 0) {
      if ((uRam00fd44 & 0x4000) != 0) {
        if ((uRam00fd44 & 0x1000) == 0) {
          if (((uRam00fd44 & 0x800) == 0) && ((uRam00fd44 & 0x8000) != 0)) {
            _DAT_3006d2 = uRam00f400 + uRam00f3fe;
            if (uRam00f400 + uRam00f3fe < uRam00f400 || uRam00f400 + uRam00f3fe < uRam00f3fe) {
              _DAT_3006d2 = 0xffff;
            }
            if (uRam00f400 == 0) {
              _DAT_3006ca = 0xff;
              DAT_301574 = 0xff;
            }
            else {
              _DAT_3006d4 = (uint)uRam00f3fe * 0xff;
              MDL = (ushort)(_DAT_3006d4 / _DAT_3006d2);
              MDH = (undefined2)(_DAT_3006d4 % (uint)_DAT_3006d2);
              MDC = MDC | 0x10;
              _DAT_3006ca = MDL;
              if (_DAT_3006d2 == 0 || 0xffff < _DAT_3006d4 / _DAT_3006d2) {
                _DAT_3006ca = 0xffff;
              }
              if (_DAT_3006ca < 0x100) {
                DAT_301574 = DAT_3006ca;
              }
              else {
                DAT_301574 = 0xff;
              }
            }
            uVar4 = (ushort)DAT_0139bc;
            if (uVar4 <= _DAT_3006ca) {
              uVar2 = DAT_3006d8 + 0xb24c;
              if (*(char *)((uint3)uVar2 + 0x10000) == '\0') {
                uVar4 = 0;
              }
              else {
                *(char *)((uint3)uVar2 + 0x10000) = *(char *)((uint3)uVar2 + 0x10000) + -1;
                uVar4 = (ushort)*(byte *)((uint3)uVar2 + 0x10000);
                if (*(byte *)((uint3)uVar2 + 0x10000) < DAT_0139b9) {
                  *(byte *)((uint3)uVar2 + 0x10000) = DAT_0139b9;
                }
              }
            }
          }
        }
        else {
          uVar2 = DAT_3006d8 + 0xb24c;
          *(char *)((uint3)uVar2 + 0x10000) = *(char *)((uint3)uVar2 + 0x10000) + DAT_0139b7;
          uVar4 = (ushort)*(byte *)((uint3)uVar2 + 0x10000);
          if (DAT_0139b6 < *(byte *)((uint3)uVar2 + 0x10000)) {
            *(byte *)((uint3)uVar2 + 0x10000) = DAT_0139b6;
          }
        }
        uRam00fd44 = uRam00fd44 & 0xe7ff;
      }
      uRam00fd46 = uRam00fd46 & 0xfffe;
      uRam00f3fe = 0;
      uRam00f400 = 0;
      bRam00f3fb = 0;
      uVar3 = _DAT_3006d4;
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
      if ((uRam00fd42 & 0x200) != 0) {
        MDL = (ushort)*(byte *)((uint3)DAT_301518 + 0x30151c) * (ushort)DAT_0139bb;
        MDH = 0;
        MDC = MDC | 0x10;
        uVar4 = MDL >> 4;
        _DAT_3006ce = MDL;
        if (bRam00f3ed < (byte)uVar4) {
          uRam00fd44 = uRam00fd44 | 0x800;
        }
        else {
          uRam00fd44 = uRam00fd44 | 0x1000;
        }
      }
    }
  }
  _DAT_3006d6 = (undefined2)(uVar3 >> 0x10);
  _DAT_3006d4 = (undefined2)uVar3;
  if ((uRam00fd46 & 2) != 0) {
    if (DAT_301518 == 0) {
      bRam00f3fd = bRam00f3fd - 1;
    }
    uVar4 = (ushort)bRam00f3fd;
    if (bRam00f3fd == 0) {
      uRam00fd46 = uRam00fd46 & 0xfffd;
    }
  }
  if ((uRam00fd44 & 0x2000) != 0) {
    if (DAT_301518 == 0) {
      bRam00f3fc = bRam00f3fc - 1;
    }
    uVar4 = (ushort)bRam00f3fc;
    if (bRam00f3fc == 0) {
      uRam00fd44 = uRam00fd44 & 0xdfff;
    }
  }
  return uVar4;
}


// ================= FUN_0894c0 @ 0894c0 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0894c0(void)

{
  uint uVar1;
  uint uVar2;
  ushort uVar3;
  ushort uVar4;
  
  if ((uRam00fd7a & 0x8000) == 0) {
    _DAT_30299a = (ushort)DAT_304760 << 8;
  }
  else {
    _DAT_30299a = FUN_042cf4(DAT_02381c,DAT_304760,_DAT_30699a);
  }
  DAT_3047a8 = DAT_30299b;
  _DAT_305268 = FUN_041a68((short)&DAT_0137fa,8,DAT_30299b);
  _DAT_3029a6 = FUN_042464(DAT_02380c,(short)&DAT_01380d,8,(short)&DAT_013812,8,DAT_30583b);
  _DAT_3029a4 = FUN_041a68(0x37e4,8,DAT_304e27);
  uVar4 = DAT_01655e;
  if ((uRam00fd4a & 1) == 0) {
    uVar4 = DAT_01655c;
  }
  uVar1 = CONCAT22(_DAT_302986 >> 10,_DAT_302986 << 6);
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
  DAT_3047a9 = (char)uVar3;
  return;
}


// ================= FUN_08981c @ 08981c =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_08981c(void)

{
  short sVar1;
  int iVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  
  if ((DAT_019c37 & 1) == 0) {
    iVar2 = (uint)FUN_00f474 * (uint)DAT_3014ee * 0x100;
    uVar3 = (ushort)((uint)iVar2 >> 0x10);
    uVar5 = uVar3 * 2;
    if (uVar3 * 2 < uVar3) {
      uVar5 = 0xffff;
    }
  }
  else {
    iVar2 = (uint)DAT_0237f4 * (uint)DAT_3014ee * 0x100;
    uVar3 = (ushort)((uint)iVar2 >> 0x10);
    uVar5 = uVar3 * 2;
    if (uVar3 * 2 < uVar3) {
      uVar5 = 0xffff;
    }
  }
  MDH = (ushort)((uint)iVar2 >> 0x10);
  MDL = (ushort)iVar2;
  MDC = MDC | 0x10;
  _DAT_305258 = _DAT_30561e - uVar5;
  if (_DAT_30561e < uVar5) {
    if (_DAT_305258 >= 0) {
      _DAT_305258 = -0x8000;
    }
  }
  else if (_DAT_305258 < 0) {
    _DAT_305258 = 0x7fff;
  }
  _DAT_305258 = _DAT_305258 >> 1;
  uVar3 = _DAT_302e38;
  if ((DAT_019c36 & 1) != 0) {
    _DAT_3029a0 = FUN_043904(DAT_02381e,DAT_022e34,_DAT_3029a2,_DAT_3029a0);
    iVar2 = CONCAT22(MDH,MDL);
    uVar3 = (ushort)((uint)_DAT_3029a0 >> 0x10);
  }
  MDH = (ushort)((uint)iVar2 >> 0x10);
  MDL = (ushort)iVar2;
  if ((_DAT_302e38 < DAT_0237f6) && (FUN_00f386 < DAT_019c34)) {
    uVar3 = FUN_042c1c(_DAT_302e3c,1000,0x138);
  }
  else if ((DAT_0237f8 < _DAT_302960) && (FUN_00f386 < DAT_019c33)) {
    DAT_3015d1 = FUN_0419f4(0x1c3a,6,DAT_304e27);
    uVar4 = FUN_042c1c(_DAT_302960,DAT_3015d1,0x555);
    MDL = (ushort)((uint)uVar4 * (uint)DAT_023556);
    MDH = (ushort)((uint)uVar4 * (uint)DAT_023556 >> 0x10);
    MDC = MDC | 0x10;
    sVar1 = MDH - (MDL != 0xffff);
    uVar4 = MDL;
    if ((sVar1 != 0 || MDL != 0xffff) && (MDH != 0 || MDL == 0xffff)) {
      uVar4 = 0xffff;
    }
    _DAT_30297e = uVar3 - uVar4;
    if (uVar3 < uVar4) {
      _DAT_30297e = 0;
    }
    uVar3 = FUN_042c1c(_DAT_30297e,1000,0x138,sVar1);
  }
  else {
    uVar3 = FUN_042c1c(uVar3,1000,0x138);
  }
  _DAT_30297a = uVar3 - (uVar5 >> 3);
  if (uVar3 < uVar5 >> 3) {
    if (_DAT_30297a >= 0) {
      _DAT_30297a = -0x8000;
    }
  }
  else if (_DAT_30297a < 0) {
    _DAT_30297a = 0x7fff;
  }
  uVar3 = _DAT_3029a6 + _DAT_305268;
  if (_DAT_3029a6 + _DAT_305268 < _DAT_3029a6 || _DAT_3029a6 + _DAT_305268 < _DAT_305268) {
    uVar3 = 0xffff;
  }
  uVar4 = FUN_042486(DAT_0237ca,(short)&DAT_0137cc,8,0x37d8,8,_DAT_30297a);
  uVar5 = _DAT_3029a4;
  _DAT_302998 = uVar3 + uVar4;
  if (uVar3 + uVar4 < uVar3 || uVar3 + uVar4 < uVar4) {
    _DAT_302998 = -1;
  }
  uVar3 = FUN_042486(DAT_02379c,0x379e,8,0x37b4,8,_DAT_30297a);
  uVar3 = (ushort)((uint)uVar3 * (uint)uVar5 >> 0x10);
  uVar5 = uVar3 * 2;
  if (uVar3 * 2 < uVar3) {
    uVar5 = 0xffff;
  }
  MDL = (ushort)((uint)DAT_0237f2 * (uint)uVar5);
  MDH = (ushort)((uint)DAT_0237f2 * (uint)uVar5 >> 0x10);
  MDC = MDC | 0x10;
  _DAT_30525c = MDH * 2;
  if (MDH * 2 < MDH) {
    _DAT_30525c = -1;
  }
  _DAT_302982 = _DAT_306984;
  _DAT_30297c = FUN_041cc0(0x3558,8,FUN_00f40e,_DAT_306984);
  return;
}


// ================= FUN_0775c8 @ 0775c8 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0775c8(void)

{
  bool bVar1;
  uint uVar2;
  ushort uVar3;
  ushort uVar4;
  
  uVar2 = CONCAT22(MDH,MDL);
  if ((uRam00fd22 & 0x80) == 0) {
    uVar4 = (ushort)((uint)_DAT_302968 * (uint)_DAT_30297c >> 0x10);
    uVar3 = uVar4 * 2;
    if (uVar4 * 2 < uVar4) {
      uVar3 = 0xffff;
    }
    if ((short)_DAT_302a14 < 0) {
      uVar4 = _DAT_302a14 + uVar3;
      if (_DAT_302a14 <= _DAT_302a14 + uVar3 && uVar3 <= _DAT_302a14 + uVar3) {
        uVar4 = 0;
      }
    }
    else {
      uVar4 = _DAT_302a14 + uVar3;
      if (_DAT_302a14 + uVar3 < _DAT_302a14 || _DAT_302a14 + uVar3 < uVar3) {
        uVar4 = 0xffff;
      }
    }
    uVar2 = (uint)uVar4 * (uint)DAT_0237f2;
    MDC = MDC | 0x10;
    _DAT_3028ba = (ushort)(uVar2 >> 9);
    if ((short)((uVar2 >> 9) >> 0x10) != 0 || _DAT_3028ba == 0xffff) {
      _DAT_3028ba = 0xffff;
    }
    bVar1 = _DAT_30069c + _DAT_3028ba < _DAT_30069c;
    uVar4 = _DAT_30069c + _DAT_3028ba;
    _DAT_30069c = _DAT_30069c + _DAT_3028ba;
    _DAT_30069e = _DAT_30069e + (ushort)(bVar1 || uVar4 < _DAT_3028ba);
  }
  MDH = (undefined2)(uVar2 >> 0x10);
  MDL = (undefined2)uVar2;
  return;
}


// ================= FUN_086318 @ 086318 =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_086318(void)

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
  
  uVar6 = _DAT_303b7a;
  uVar10 = _DAT_303b78;
  if (((_DAT_302634 & 1) != 0) && ((_DAT_302634 & 0x8000) != 0)) {
    _DAT_30521e = 0;
    _DAT_305222 = 0;
    _DAT_30521a = 0x8000;
    _DAT_305216 = 0x8000;
    uVar14 = _DAT_300772;
    uVar2 = _DAT_300776;
    uVar3 = _DAT_30077a;
    uVar4 = _DAT_30077e;
    iVar5 = _DAT_3035ec;
    iVar15 = _DAT_3035f0;
    goto LAB_0875aa;
  }
  if ((DAT_02348e < _FUN_00f474) || ((byte)DAT_019a87 < (byte)FUN_00f40e)) {
    DAT_30479c = DAT_30479c & 0xfb;
  }
  else {
    DAT_30479c = DAT_30479c | 4;
  }
  if ((((((byte)FUN_00f40e < (byte)DAT_019a8b) || ((byte)DAT_019a88 < (byte)FUN_00f40e)) ||
       (_FUN_00f474 < DAT_023494)) || ((DAT_023490 < _FUN_00f474 || (bRam00f473 < DAT_019a91)))) ||
     (DAT_019a8f < bRam00f473)) {
    DAT_30479c = DAT_30479c & 0xfd;
  }
  else {
    DAT_30479c = DAT_30479c | 2;
  }
  if ((((byte)FUN_00f40e < (byte)DAT_019a8c) || (DAT_023492 < _FUN_00f474)) ||
     ((bRam00f473 < DAT_019a92 || (DAT_019a90 < bRam00f473)))) {
    DAT_30479c = DAT_30479c & 0xf7;
  }
  else {
    DAT_30479c = DAT_30479c | 8;
  }
  if ((bRam00f473 < DAT_019a93) || (_FUN_00f474 < DAT_023496)) {
    DAT_30479c = DAT_30479c & 0xfe;
  }
  else {
    DAT_30479c = DAT_30479c | 1;
  }
  if ((DAT_019279 & 8) == 0) {
    if ((DAT_019a89 & 1) == 0) {
      DAT_30479a = DAT_30479a & 0xdf;
    }
    else {
      DAT_30479a = DAT_30479a | 0x20;
    }
    if ((DAT_019a89 & 2) == 0) {
      DAT_30479b = DAT_30479b & 0xfb;
    }
    else {
      DAT_30479b = DAT_30479b | 4;
    }
    if ((DAT_019a89 & 4) == 0) {
      DAT_30479a = DAT_30479a & 0xbf;
    }
    else {
      DAT_30479a = DAT_30479a | 0x40;
    }
    if ((DAT_019a89 & 0x80) != 0) goto LAB_086504;
    DAT_30479b = DAT_30479b & 0xfd;
  }
  else {
    DAT_30479b = DAT_30479b | 4;
    DAT_30479a = DAT_30479a | 0x60;
LAB_086504:
    DAT_30479b = DAT_30479b | 2;
  }
  if ((((FUN_00fd5a & 0x80) == 0) || ((DAT_019a89 & 0x10) != 0)) && ((DAT_019a89 & 8) != 0)) {
    DAT_30479a = DAT_30479a & 0xf7;
  }
  else {
    DAT_30479a = DAT_30479a | 8;
  }
  _DAT_305212 = _DAT_302816 + 0x8000;
  if (_DAT_302816 < 0x8000) {
    if (_DAT_305212 >= 0) {
      _DAT_305212 = -0x8000;
    }
  }
  else if (_DAT_305212 < 0) {
    _DAT_305212 = 0x7fff;
  }
  if ((DAT_3055ba & 2) == 0) {
    DAT_30a0dc = DAT_30a0dc & 0x3d;
    DAT_30a0db = DAT_30a0db & 0x3d;
    DAT_30a0da = DAT_30a0da & 0x3d;
LAB_08667c:
    DAT_30a0dd = DAT_30a0dd & 0x3d;
  }
  else {
    if (((DAT_30479c & 4) == 0) || ((DAT_30479a & 0x20) != 0)) {
      DAT_30a0dc = DAT_30a0dc & 0x3d;
    }
    else {
      DAT_30a0dc = DAT_30a0dc | 0x80;
    }
    if (((DAT_30479c & 2) == 0) || ((DAT_30479b & 4) != 0)) {
      DAT_30a0db = DAT_30a0db & 0x3d;
    }
    else {
      DAT_30a0db = DAT_30a0db | 0x80;
    }
    if (((DAT_30479c & 1) == 0) || ((DAT_30479b & 2) != 0)) {
      DAT_30a0da = DAT_30a0da & 0x3d;
    }
    else {
      DAT_30a0da = DAT_30a0da | 0x80;
    }
    if (((DAT_30479c & 8) == 0) || ((DAT_30479a & 0x40) != 0)) goto LAB_08667c;
    DAT_30a0dd = DAT_30a0dd | 0x80;
  }
  if ((DAT_30a0dc & 0x40) == 0) {
    if (DAT_018770 < DAT_019a97) {
      DAT_018770 = DAT_018770 + 1;
      goto LAB_0866c8;
    }
    bVar1 = false;
  }
  else {
    DAT_018770 = 0;
LAB_0866c8:
    bVar1 = true;
  }
  if (bVar1) {
    DAT_30a0dc = DAT_30a0dc | 4;
  }
  else {
    DAT_30a0dc = DAT_30a0dc & 0xfb;
  }
  if ((DAT_30a0db & 0x40) == 0) {
    if (DAT_01876e < DAT_019a96) {
      DAT_01876e = DAT_01876e + 1;
      goto LAB_086728;
    }
    bVar1 = false;
  }
  else {
    DAT_01876e = 0;
LAB_086728:
    bVar1 = true;
  }
  if (bVar1) {
    DAT_30a0db = DAT_30a0db | 4;
  }
  else {
    DAT_30a0db = DAT_30a0db & 0xfb;
  }
  if ((DAT_30a0da & 0x40) == 0) {
    if (DAT_01876f < DAT_019a95) {
      DAT_01876f = DAT_01876f + 1;
      goto LAB_086788;
    }
    bVar1 = false;
  }
  else {
    DAT_01876f = 0;
LAB_086788:
    bVar1 = true;
  }
  if (bVar1) {
    DAT_30a0da = DAT_30a0da | 4;
  }
  else {
    DAT_30a0da = DAT_30a0da & 0xfb;
  }
  if ((DAT_30a0dd & 0x40) == 0) {
    if (DAT_018771 < DAT_019a98) {
      DAT_018771 = DAT_018771 + 1;
      goto LAB_0867e8;
    }
    bVar1 = false;
  }
  else {
    DAT_018771 = 0;
LAB_0867e8:
    bVar1 = true;
  }
  if (bVar1) {
    DAT_30a0dd = DAT_30a0dd | 4;
  }
  else {
    DAT_30a0dd = DAT_30a0dd & 0xfb;
  }
  sVar9 = _DAT_305212;
  if (_DAT_305212 < 0) {
    sVar9 = -_DAT_305212;
  }
  uVar7 = DAT_30a0bf;
  if (((DAT_30a0db & 4) != 0) && ((DAT_30a0db & 0x80) != 0)) {
    _DAT_300772 = FUN_043904((ushort)DAT_019a94 << 8,sVar9,_DAT_300774,_DAT_300772,_DAT_303b7a,
                             _DAT_303b78);
    uVar12 = (ushort)((uint)_DAT_300772 >> 0x16);
    if (uVar12 < 0x100) {
      DAT_304797 = (undefined1)uVar12;
    }
    else {
      DAT_304797 = 0xff;
    }
    uVar7 = DAT_019a8e;
    if ((uRam00fd4e & 0x2000) == 0) {
      uVar7 = FUN_0419f4(0x1a5b,6,DAT_304797);
    }
  }
  DAT_30a0bf = uVar7;
  uVar7 = DAT_30a0be;
  if (((DAT_30a0da & 4) != 0) &&
     (_DAT_300776 = CONCAT22(_DAT_300778,_DAT_300776), (DAT_30a0da & 0x80) != 0)) {
    _DAT_300776 = FUN_043904((ushort)DAT_019a94 << 8,sVar9,_DAT_300778,_DAT_300776,uVar6,uVar10);
    uVar12 = (ushort)((uint)_DAT_300776 >> 0x16);
    if (uVar12 < 0x100) {
      DAT_304796 = (undefined1)uVar12;
    }
    else {
      DAT_304796 = 0xff;
    }
    uVar7 = DAT_019a8d;
    if ((uRam00fd4e & 0x2000) == 0) {
      uVar7 = FUN_0419f4(0x1a4e,6,DAT_304796);
    }
  }
  DAT_30a0be = uVar7;
  if (((DAT_30a0dc & 4) != 0) &&
     (_DAT_30077a = CONCAT22(_DAT_30077c,_DAT_30077a), (DAT_30a0dc & 0x80) != 0)) {
    _DAT_30077a = FUN_043904((ushort)DAT_019a94 << 8,sVar9,_DAT_30077c,_DAT_30077a,uVar6,uVar10);
    uVar12 = (ushort)((uint)_DAT_30077a >> 0x16);
    if (uVar12 < 0x100) {
      DAT_304798 = (undefined1)uVar12;
    }
    else {
      DAT_304798 = 0xff;
    }
    DAT_30a0c0 = FUN_0419f4(0x1a68,6,DAT_304798);
  }
  if (((DAT_30a0dd & 4) != 0) &&
     (_DAT_30077e = CONCAT22(_DAT_300780,_DAT_30077e), (DAT_30a0dd & 0x80) != 0)) {
    _DAT_30077e = FUN_043904((ushort)DAT_019a94 << 8,sVar9,_DAT_300780,_DAT_30077e,uVar6,uVar10);
    uVar10 = (ushort)((uint)_DAT_30077e >> 0x16);
    if (uVar10 < 0x100) {
      DAT_304799 = (undefined1)uVar10;
    }
    else {
      DAT_304799 = 0xff;
    }
    DAT_30a0c1 = FUN_0419f4(0x1a75,6,DAT_304799);
  }
  uVar14 = CONCAT22(_DAT_3035e6,_DAT_3035e4);
  MDL = _DAT_302e0a / _DAT_302a02;
  MDH = _DAT_302e0a % _DAT_302a02;
  MDC = MDC | 0x10;
  uVar10 = MDL;
  if (_DAT_302a02 == 0) {
    uVar10 = 0xffff;
  }
  uVar10 = uVar10 * 2;
  if (0xff < uVar10) {
    uVar10 = 0xff;
  }
  sVar9 = DAT_019a86 * 0x100;
  if (((sVar9 == _DAT_3029ee ||
        sVar9 - _DAT_3029ee < 0 !=
        (sVar9 < 0 != _DAT_3029ee < 0 && sVar9 - _DAT_3029ee < 0 != sVar9 < 0)) ||
      ((char)(DAT_304950 - DAT_019a83) < '\0' ==
       (DAT_304950 < '\0' != DAT_019a83 < '\0' &&
       (char)(DAT_304950 - DAT_019a83) < '\0' != DAT_304950 < '\0'))) ||
     ((((DAT_301612 & 4) == 0 || (_DAT_3052a8 < (ushort)DAT_019a84 * 0x100)) &&
      (uVar10 < DAT_019a85)))) {
    if (((char)(DAT_304950 - DAT_019a83) < '\0' ==
         (DAT_304950 < '\0' != DAT_019a83 < '\0' &&
         (char)(DAT_304950 - DAT_019a83) < '\0' != DAT_304950 < '\0')) ||
       (sVar9 == _DAT_3029ee ||
        sVar9 - _DAT_3029ee < 0 !=
        (sVar9 < 0 != _DAT_3029ee < 0 && sVar9 - _DAT_3029ee < 0 != sVar9 < 0))) {
      uRam00fd4a = uRam00fd4a | 0x4000;
    }
  }
  else {
    uRam00fd4a = uRam00fd4a & 0xbfff;
  }
  uVar10 = DAT_02341e;
  uVar12 = DAT_023420;
  if ((uRam00fd4a & 0x4000) != 0) {
    uVar12 = _DAT_30521a;
    if (_DAT_30521a < DAT_02341e) {
      uVar12 = DAT_02341e;
    }
    uVar10 = DAT_023422;
    if ((uVar12 <= DAT_023422) && (uVar10 = _DAT_30521a, _DAT_30521a < DAT_02341e)) {
      uVar10 = DAT_02341e;
    }
    uVar8 = _DAT_30521a;
    if (DAT_023420 < _DAT_30521a) {
      uVar8 = DAT_023420;
    }
    uVar12 = DAT_023424;
    if ((DAT_023424 <= uVar8) && (uVar12 = _DAT_30521a, DAT_023420 < _DAT_30521a)) {
      uVar12 = DAT_023420;
    }
  }
  if ((DAT_30479b & 4) == 0) {
    if ((_DAT_303ada & 1) == 0) {
      uVar8 = _DAT_303b78 & 1;
    }
    else if (((DAT_023414 < _DAT_30521a) || (_DAT_30521a < DAT_023412)) && ((_DAT_303b78 & 1) != 0))
    {
      uVar8 = 1;
    }
    else {
      uVar8 = 0;
    }
    if (uVar8 == 0) {
      if ((((DAT_30a0db & 0x80) != 0) &&
          (uVar14 = CONCAT22(_DAT_3035e6,_DAT_3035e4), (DAT_30a0db & 0x40) != 0)) &&
         (uVar14 = CONCAT22(_DAT_3035e6,_DAT_3035e4), (DAT_3015ba & 2) != 0)) {
        _DAT_305226 = FUN_042486(DAT_023440,0x3442,8,0x344e,8,_DAT_305212);
        uVar14 = FUN_042f16(_DAT_305226,_DAT_305212,_DAT_3075e6,_DAT_3035e4,uVar10,uVar12);
      }
    }
    else {
      uVar14 = CONCAT22(_DAT_3035e6,_DAT_3035e4);
      if ((DAT_019a82 & 1) != 0) {
        if ((((DAT_019a82 & 4) == 0) || ((_DAT_303ada & 1) == 0)) && ((DAT_019a82 & 2) != 0)) {
          sVar9 = _DAT_305218 - _DAT_30521a;
          if (_DAT_305218 < _DAT_30521a) {
            if (sVar9 >= 0) {
              sVar9 = -0x8000;
            }
          }
          else if (sVar9 < 0) {
            sVar9 = 0x7fff;
          }
        }
        else {
          sVar9 = -0x8000 - _DAT_30521a;
          if (_DAT_30521a < 0x8001) {
            if (sVar9 < 0) {
              sVar9 = 0x7fff;
            }
          }
          else if (sVar9 >= 0) {
            sVar9 = -0x8000;
          }
        }
        uVar14 = FUN_042f16(DAT_0234ac,sVar9,_DAT_3035e6,_DAT_3035e4,uVar10,uVar12);
      }
    }
    _DAT_3035e6 = (ushort)((uint)uVar14 >> 0x10);
    _DAT_3035e4 = (undefined2)uVar14;
    _DAT_30521a = _DAT_3035e6;
  }
  else {
    _DAT_3035e4 = 0;
    _DAT_30521a = 0x8000;
  }
  uVar14 = CONCAT22(_DAT_3035ea,_DAT_3035e8);
  if ((_DAT_30521a < uVar12) && (uVar10 < _DAT_30521a)) {
    DAT_30479a = DAT_30479a & 0xfd;
  }
  else {
    DAT_30479a = DAT_30479a | 2;
  }
  uVar10 = DAT_023416;
  uVar12 = DAT_023418;
  if ((uRam00fd4a & 0x4000) != 0) {
    uVar12 = _DAT_305216;
    if (_DAT_305216 < DAT_023416) {
      uVar12 = DAT_023416;
    }
    uVar10 = DAT_02341a;
    if ((uVar12 <= DAT_02341a) && (uVar10 = _DAT_305216, _DAT_305216 < DAT_023416)) {
      uVar10 = DAT_023416;
    }
    uVar8 = _DAT_305216;
    if (DAT_023418 < _DAT_305216) {
      uVar8 = DAT_023418;
    }
    uVar12 = DAT_02341c;
    if ((DAT_02341c <= uVar8) && (uVar12 = _DAT_305216, DAT_023418 < _DAT_305216)) {
      uVar12 = DAT_023418;
    }
  }
  _DAT_3035e6 = _DAT_30521a;
  if ((DAT_30479b & 2) == 0) {
    if ((_DAT_303ada & 1) == 0) {
      uVar8 = _DAT_303b78 & 1;
    }
    else if (((DAT_023414 < _DAT_305216) || (_DAT_305216 < DAT_023412)) && ((_DAT_303b78 & 1) != 0))
    {
      uVar8 = 1;
    }
    else {
      uVar8 = 0;
    }
    if (uVar8 == 0) {
      if ((((DAT_30a0da & 0x80) != 0) &&
          (uVar14 = CONCAT22(_DAT_3035ea,_DAT_3035e8), (DAT_30a0da & 0x40) != 0)) &&
         (uVar14 = CONCAT22(_DAT_3035ea,_DAT_3035e8), (DAT_3015ba & 2) != 0)) {
        _DAT_305224 = FUN_042486(DAT_023426,(short)&DAT_013428,8,0x3434,8,_DAT_305212);
        uVar14 = FUN_042f16(_DAT_305224,_DAT_305212,_DAT_3075ea,_DAT_3035e8,uVar10,uVar12);
      }
    }
    else {
      uVar14 = CONCAT22(_DAT_3035ea,_DAT_3035e8);
      if ((DAT_019a82 & 1) != 0) {
        if ((((DAT_019a82 & 4) == 0) || ((_DAT_303ada & 1) == 0)) && ((DAT_019a82 & 2) != 0)) {
          sVar9 = _DAT_305214 - _DAT_305216;
          if (_DAT_305214 < _DAT_305216) {
            if (sVar9 >= 0) {
              sVar9 = -0x8000;
            }
          }
          else if (sVar9 < 0) {
            sVar9 = 0x7fff;
          }
        }
        else {
          sVar9 = -0x8000 - _DAT_305216;
          if (_DAT_305216 < 0x8001) {
            if (sVar9 < 0) {
              sVar9 = 0x7fff;
            }
          }
          else if (sVar9 >= 0) {
            sVar9 = -0x8000;
          }
        }
        uVar14 = FUN_042f16(DAT_0234ac,sVar9,_DAT_3035ea,_DAT_3035e8,uVar10,uVar12);
      }
    }
    _DAT_3035ea = (ushort)((uint)uVar14 >> 0x10);
    _DAT_3035e8 = (undefined2)uVar14;
    _DAT_305216 = _DAT_3035ea;
  }
  else {
    _DAT_3035e8 = 0;
    _DAT_305216 = 0x8000;
  }
  if ((_DAT_305216 < uVar12) && (uVar10 < _DAT_305216)) {
    DAT_30479a = DAT_30479a & 0xfe;
  }
  else {
    DAT_30479a = DAT_30479a | 1;
  }
  sVar9 = DAT_02349c;
  sVar13 = DAT_02349e;
  if ((uRam00fd4a & 0x4000) != 0) {
    sVar13 = _DAT_30521e;
    if (_DAT_30521e - DAT_02349c < 0 !=
        (_DAT_30521e < 0 != DAT_02349c < 0 && _DAT_30521e - DAT_02349c < 0 != _DAT_30521e < 0)) {
      sVar13 = DAT_02349c;
    }
    sVar9 = DAT_0234a0;
    if ((sVar13 == DAT_0234a0 ||
         sVar13 - DAT_0234a0 < 0 !=
         (sVar13 < 0 != DAT_0234a0 < 0 && sVar13 - DAT_0234a0 < 0 != sVar13 < 0)) &&
       (sVar9 = _DAT_30521e,
       _DAT_30521e - DAT_02349c < 0 !=
       (_DAT_30521e < 0 != DAT_02349c < 0 && _DAT_30521e - DAT_02349c < 0 != _DAT_30521e < 0))) {
      sVar9 = DAT_02349c;
    }
    sVar11 = _DAT_30521e;
    if (_DAT_30521e != DAT_02349e &&
        _DAT_30521e - DAT_02349e < 0 ==
        (_DAT_30521e < 0 != DAT_02349e < 0 && _DAT_30521e - DAT_02349e < 0 != _DAT_30521e < 0)) {
      sVar11 = DAT_02349e;
    }
    sVar13 = DAT_0234a2;
    if ((sVar11 - DAT_0234a2 < 0 ==
         (sVar11 < 0 != DAT_0234a2 < 0 && sVar11 - DAT_0234a2 < 0 != sVar11 < 0)) &&
       (sVar13 = _DAT_30521e,
       _DAT_30521e != DAT_02349e &&
       _DAT_30521e - DAT_02349e < 0 ==
       (_DAT_30521e < 0 != DAT_02349e < 0 && _DAT_30521e - DAT_02349e < 0 != _DAT_30521e < 0))) {
      sVar13 = DAT_02349e;
    }
  }
  _DAT_3035ea = _DAT_305216;
  if ((DAT_30479a & 0x20) == 0) {
    if ((_DAT_303ada & 1) == 0) {
      uVar10 = _DAT_303b78 & 1;
    }
    else if (((_DAT_30521e == DAT_02349a ||
               _DAT_30521e - DAT_02349a < 0 !=
               (_DAT_30521e < 0 != DAT_02349a < 0 && _DAT_30521e - DAT_02349a < 0 != _DAT_30521e < 0
               )) && (_DAT_30521e - DAT_023498 < 0 ==
                      (_DAT_30521e < 0 != DAT_023498 < 0 &&
                      _DAT_30521e - DAT_023498 < 0 != _DAT_30521e < 0))) || ((_DAT_303b78 & 1) == 0)
            ) {
      uVar10 = 0;
    }
    else {
      uVar10 = 1;
    }
    if (uVar10 == 0) {
      if ((((DAT_30a0dc & 0x80) != 0) &&
          (_DAT_3035ec = CONCAT22(_DAT_3035ee,_DAT_3035ec), (DAT_30a0dc & 0x40) != 0)) &&
         (_DAT_3035ec = CONCAT22(_DAT_3035ee,_DAT_3035ec), (DAT_3015ba & 2) != 0)) {
        _DAT_305228 = FUN_042486(DAT_02345a,0x345c,8,(short)&DAT_013468,8,_DAT_305212);
        _DAT_3035ec = FUN_042df4(_DAT_305228,_DAT_305212,_DAT_3075ee,_DAT_3035ec);
      }
    }
    else {
      _DAT_3035ec = CONCAT22(_DAT_3035ee,_DAT_3035ec);
      if ((DAT_019a82 & 1) != 0) {
        if ((((DAT_019a82 & 4) == 0) || ((_DAT_303ada & 1) == 0)) && ((DAT_019a82 & 2) != 0)) {
          sVar11 = _DAT_30521c - _DAT_30521e;
          if (_DAT_30521c < 0 != _DAT_30521e < 0 && _DAT_30521c - _DAT_30521e < 0 != _DAT_30521c < 0
             ) {
            sVar11 = -0x8000;
          }
        }
        else if (_DAT_30521e == -0x8000) {
          sVar11 = 0x7fff;
        }
        else {
          sVar11 = -_DAT_30521e;
        }
        _DAT_3035ec = FUN_042df4(DAT_0234ac,sVar11,_DAT_3035ee,_DAT_3035ec);
      }
    }
    _DAT_30521e = (short)(_DAT_3035ec >> 0x13);
    if (_DAT_30521e == sVar13 ||
        _DAT_30521e - sVar13 < 0 !=
        (_DAT_30521e < 0 != sVar13 < 0 && _DAT_30521e - sVar13 < 0 != _DAT_30521e < 0)) {
      if (_DAT_30521e - sVar9 < 0 !=
          (_DAT_30521e < 0 != sVar9 < 0 && _DAT_30521e - sVar9 < 0 != _DAT_30521e < 0)) {
        _DAT_3035ec = CONCAT22(sVar9 << 3,0xffff);
        _DAT_30521e = sVar9;
      }
    }
    else {
      _DAT_3035ec = (uint)(ushort)(sVar13 << 3) << 0x10;
      _DAT_30521e = sVar13;
    }
  }
  else {
    _DAT_3035ec = 0;
    _DAT_30521e = 0;
  }
  iVar15 = CONCAT22(_DAT_3035f2,_DAT_3035f0);
  if ((sVar13 == _DAT_30521e ||
       sVar13 - _DAT_30521e < 0 !=
       (sVar13 < 0 != _DAT_30521e < 0 && sVar13 - _DAT_30521e < 0 != sVar13 < 0)) ||
     (sVar9 - _DAT_30521e < 0 ==
      (sVar9 < 0 != _DAT_30521e < 0 && sVar9 - _DAT_30521e < 0 != sVar9 < 0))) {
    DAT_30479a = DAT_30479a | 0x80;
  }
  else {
    DAT_30479a = DAT_30479a & 0x7f;
  }
  sVar9 = DAT_0234a4;
  sVar13 = DAT_0234a6;
  if ((uRam00fd4a & 0x4000) != 0) {
    sVar13 = _DAT_305222;
    if (_DAT_305222 - DAT_0234a4 < 0 !=
        (_DAT_305222 < 0 != DAT_0234a4 < 0 && _DAT_305222 - DAT_0234a4 < 0 != _DAT_305222 < 0)) {
      sVar13 = DAT_0234a4;
    }
    sVar9 = DAT_0234a8;
    if ((sVar13 == DAT_0234a8 ||
         sVar13 - DAT_0234a8 < 0 !=
         (sVar13 < 0 != DAT_0234a8 < 0 && sVar13 - DAT_0234a8 < 0 != sVar13 < 0)) &&
       (sVar9 = _DAT_305222,
       _DAT_305222 - DAT_0234a4 < 0 !=
       (_DAT_305222 < 0 != DAT_0234a4 < 0 && _DAT_305222 - DAT_0234a4 < 0 != _DAT_305222 < 0))) {
      sVar9 = DAT_0234a4;
    }
    sVar11 = _DAT_305222;
    if (_DAT_305222 != DAT_0234a6 &&
        _DAT_305222 - DAT_0234a6 < 0 ==
        (_DAT_305222 < 0 != DAT_0234a6 < 0 && _DAT_305222 - DAT_0234a6 < 0 != _DAT_305222 < 0)) {
      sVar11 = DAT_0234a6;
    }
    sVar13 = DAT_0234aa;
    if ((sVar11 - DAT_0234aa < 0 ==
         (sVar11 < 0 != DAT_0234aa < 0 && sVar11 - DAT_0234aa < 0 != sVar11 < 0)) &&
       (sVar13 = _DAT_305222,
       _DAT_305222 != DAT_0234a6 &&
       _DAT_305222 - DAT_0234a6 < 0 ==
       (_DAT_305222 < 0 != DAT_0234a6 < 0 && _DAT_305222 - DAT_0234a6 < 0 != _DAT_305222 < 0))) {
      sVar13 = DAT_0234a6;
    }
  }
  if ((DAT_30479a & 0x40) == 0) {
    if ((_DAT_303ada & 1) == 0) {
      uVar10 = _DAT_303b78 & 1;
    }
    else if (((_DAT_305222 == DAT_02349a ||
               _DAT_305222 - DAT_02349a < 0 !=
               (_DAT_305222 < 0 != DAT_02349a < 0 && _DAT_305222 - DAT_02349a < 0 != _DAT_305222 < 0
               )) && (_DAT_305222 - DAT_023498 < 0 ==
                      (_DAT_305222 < 0 != DAT_023498 < 0 &&
                      _DAT_305222 - DAT_023498 < 0 != _DAT_305222 < 0))) || ((_DAT_303b78 & 1) == 0)
            ) {
      uVar10 = 0;
    }
    else {
      uVar10 = 1;
    }
    if (uVar10 == 0) {
      if ((((DAT_30a0dd & 0x80) != 0) &&
          (iVar15 = CONCAT22(_DAT_3035f2,_DAT_3035f0), (DAT_30a0dd & 0x40) != 0)) &&
         (iVar15 = CONCAT22(_DAT_3035f2,_DAT_3035f0), (DAT_3015ba & 2) != 0)) {
        _DAT_30522a = FUN_042486(DAT_023474,0x3476,8,0x3482,8,_DAT_305212);
        iVar15 = FUN_042df4(_DAT_30522a,_DAT_305212,_DAT_3075f2,_DAT_3035f0);
      }
    }
    else {
      iVar15 = CONCAT22(_DAT_3035f2,_DAT_3035f0);
      if ((DAT_019a82 & 1) != 0) {
        if ((((DAT_019a82 & 4) == 0) || ((_DAT_303ada & 1) == 0)) && ((DAT_019a82 & 2) != 0)) {
          sVar11 = _DAT_305220 - _DAT_305222;
          if (_DAT_305220 < 0 != _DAT_305222 < 0 && _DAT_305220 - _DAT_305222 < 0 != _DAT_305220 < 0
             ) {
            sVar11 = -0x8000;
          }
        }
        else if (_DAT_305222 == -0x8000) {
          sVar11 = 0x7fff;
        }
        else {
          sVar11 = -_DAT_305222;
        }
        iVar15 = FUN_042df4(DAT_0234ac,sVar11,_DAT_3035f2,_DAT_3035f0);
      }
    }
    _DAT_305222 = (short)(iVar15 >> 0x13);
    if (_DAT_305222 == sVar13 ||
        _DAT_305222 - sVar13 < 0 !=
        (_DAT_305222 < 0 != sVar13 < 0 && _DAT_305222 - sVar13 < 0 != _DAT_305222 < 0)) {
      if (_DAT_305222 - sVar9 < 0 !=
          (_DAT_305222 < 0 != sVar9 < 0 && _DAT_305222 - sVar9 < 0 != _DAT_305222 < 0)) {
        iVar15 = CONCAT22(sVar9 << 3,0xffff);
        _DAT_305222 = sVar9;
      }
    }
    else {
      iVar15 = (uint)(ushort)(sVar13 << 3) << 0x10;
      _DAT_305222 = sVar13;
    }
  }
  else {
    iVar15 = 0;
    _DAT_305222 = 0;
  }
  uVar14 = _DAT_300772;
  uVar2 = _DAT_300776;
  uVar3 = _DAT_30077a;
  uVar4 = _DAT_30077e;
  iVar5 = _DAT_3035ec;
  if ((sVar13 == _DAT_305222 ||
       sVar13 - _DAT_305222 < 0 !=
       (sVar13 < 0 != _DAT_305222 < 0 && sVar13 - _DAT_305222 < 0 != sVar13 < 0)) ||
     (sVar9 - _DAT_305222 < 0 ==
      (sVar9 < 0 != _DAT_305222 < 0 && sVar9 - _DAT_305222 < 0 != sVar9 < 0))) {
    DAT_30479b = DAT_30479b | 1;
  }
  else {
    DAT_30479b = DAT_30479b & 0xfe;
  }
LAB_0875aa:
  _DAT_3035f2 = (undefined2)((uint)iVar15 >> 0x10);
  _DAT_3035f0 = (undefined2)iVar15;
  _DAT_3035ee = (undefined2)((uint)iVar5 >> 0x10);
  _DAT_3035ec = (undefined2)iVar5;
  _DAT_300780 = (undefined2)((uint)uVar4 >> 0x10);
  _DAT_30077e = (undefined2)uVar4;
  _DAT_30077c = (undefined2)((uint)uVar3 >> 0x10);
  _DAT_30077a = (undefined2)uVar3;
  _DAT_300778 = (undefined2)((uint)uVar2 >> 0x10);
  _DAT_300776 = (undefined2)uVar2;
  _DAT_300774 = (undefined2)((uint)uVar14 >> 0x10);
  _DAT_300772 = (undefined2)uVar14;
  return;
}


// ================= FUN_04f4bc @ 04f4bc =================

/* WARNING: Removing unreachable block (ram,0x04f5fa) */
/* WARNING: Removing unreachable block (ram,0x04f558) */
/* WARNING: Removing unreachable block (ram,0x04f67c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_04f4bc(void)

{
  byte bVar1;
  ushort uVar2;
  short sVar3;
  int iVar4;
  byte bVar5;
  short sVar6;
  char cVar7;
  ushort uVar8;
  byte local_c;
  undefined1 local_a;
  
  _DAT_301ae8 = FUN_040eb0(0x582c,FUN_00f474);
  _DAT_301aec = FUN_043430(0x56cc,0x582c,_DAT_3019b4,_DAT_301ae8);
  cVar7 = FUN_0411f4(0x2aa2,0x582c,_DAT_3019b4,_DAT_301ae8);
  sVar6 = (short)cVar7;
  cVar7 = FUN_0411f4(0x2b52,0x582c,_DAT_3019b4,_DAT_301ae8);
  uVar8 = 0xff - DAT_30129c;
  if ((short)uVar8 < 0) {
    sVar6 = sVar6 * (uVar8 & 0x7fff) + sVar6 * -0x8000;
  }
  else {
    sVar6 = sVar6 * uVar8;
  }
  MDL = (ushort)((int)(short)cVar7 * (int)(short)(ushort)DAT_30129c);
  MDH = (ushort)((uint)((int)(short)cVar7 * (int)(short)(ushort)DAT_30129c) >> 0x10);
  MDC = MDC | 0x10;
  _DAT_301af0 = MDL + sVar6;
  if ((short)MDL < 0 == sVar6 < 0 && (short)(MDL + sVar6) < 0 != (short)MDL < 0) {
    _DAT_301af0 = 0x7fff;
  }
  cVar7 = FUN_0411f4(0x2c02,0x582c,_DAT_3019b4,_DAT_301ae8);
  sVar6 = (short)cVar7;
  cVar7 = FUN_0411f4(0x2cb2,0x582c,_DAT_3019b4,_DAT_301ae8);
  uVar8 = 0xff - DAT_30129c;
  if ((short)uVar8 < 0) {
    sVar6 = sVar6 * (uVar8 & 0x7fff) + sVar6 * -0x8000;
  }
  else {
    sVar6 = sVar6 * uVar8;
  }
  sVar3 = (short)cVar7 * (ushort)DAT_30129c;
  _DAT_301af2 = sVar3 + sVar6;
  if (sVar3 < 0 == sVar6 < 0 && sVar3 + sVar6 < 0 != sVar3 < 0) {
    _DAT_301af2 = 0x7fff;
  }
  uVar8 = 0xff - DAT_30129b;
  if ((short)uVar8 < 0) {
    iVar4 = (int)_DAT_301af0 * (int)(short)(uVar8 & 0x7fff);
    uVar2 = (ushort)iVar4;
    uVar8 = _DAT_301af0 * -0x8000;
    iVar4 = CONCAT22((short)((uint)iVar4 >> 0x10) + (_DAT_301af0 >> 1) +
                     (ushort)(uVar2 + uVar8 < uVar2 || uVar2 + uVar8 < uVar8),uVar2 + uVar8);
  }
  else {
    iVar4 = (int)_DAT_301af0 * (int)(short)uVar8;
  }
  uVar8 = (ushort)iVar4 >> 8 | (short)((uint)iVar4 >> 0x10) << 8;
  iVar4 = (int)_DAT_301af2 * (int)(short)(ushort)DAT_30129b;
  MDL = (ushort)iVar4;
  MDH = (ushort)((uint)iVar4 >> 0x10);
  MDC = MDC | 0x10;
  cVar7 = (char)((uint)iVar4 >> 0x10);
  sVar6 = (short)((uint)iVar4 >> 8);
  _DAT_301af4 = sVar6 + uVar8;
  if (cVar7 < '\0' == (short)uVar8 < 0 && (short)(sVar6 + uVar8) < 0 != cVar7 < '\0') {
    _DAT_301af4 = 0x7fff;
  }
  uVar8 = _DAT_301af4;
  if ((short)_DAT_301af4 < 0) {
    if (_DAT_301af4 == 0x8000) {
      uVar8 = 0x7fff;
    }
    else {
      uVar8 = -_DAT_301af4;
    }
  }
  uVar2 = (short)uVar8 >> 8;
  if ((uVar8 & 0x80) == 0) {
    uVar8 = uVar2 & 0xff;
  }
  else {
    uVar8 = uVar2 + 1;
    if (((short)((short)&DAT_01ff82 + uVar2) < 0 ==
         ((short)uVar2 < 0 && (short)((short)&DAT_01ff82 + uVar2) < 0 != (short)uVar2 < 0)) ||
       (uVar8 == 0xff80 ||
        (short)(uVar2 + 0x81) < 0 !=
        (-1 < (short)uVar8 && (short)(uVar2 + 0x81) < 0 != (short)uVar8 < 0))) {
      uVar8 = uVar2 & 0xff;
    }
  }
  DAT_301304 = (char)uVar8;
  if ((short)_DAT_301af4 < 0) {
    DAT_301304 = -DAT_301304;
  }
  DAT_3012ff = FUN_040b3e(0x2a8d,DAT_3015b9);
  DAT_3012fe = FUN_041434(DAT_0156b6,0x56b7,0x56c1,DAT_3015b9);
  DAT_3012fd = 0;
  uVar8 = (ushort)((uint)((ushort)DAT_3012ff * 0xa4) * (uint)_DAT_301aec >> 0x10);
  _DAT_301aee = uVar8 * 2;
  if (uVar8 * 2 < uVar8) {
    _DAT_301aee = 0xffff;
  }
  uVar8 = (ushort)((uint)((ushort)DAT_301302 * 0xa4) * (uint)_DAT_301aee >> 0x10);
  _DAT_301aea = uVar8 * 2;
  if (uVar8 * 2 < uVar8) {
    _DAT_301aea = -1;
  }
  cVar7 = DAT_301304 - DAT_30132b;
  if (DAT_301304 < '\0' != DAT_30132b < '\0' &&
      (char)(DAT_301304 - DAT_30132b) < '\0' != DAT_301304 < '\0') {
    cVar7 = -0x80;
  }
  sVar6 = (short)cVar7 + (short)DAT_304049 + (short)DAT_3012fe;
  if (sVar6 == 0x7f || sVar6 + -0x7f < 0 != (sVar6 < 0 && sVar6 + -0x7f < 0 != sVar6 < 0)) {
    if (sVar6 + 0x80 < 0 == (-1 < sVar6 && sVar6 + 0x80 < 0 != sVar6 < 0)) {
      local_a = (undefined1)sVar6;
      DAT_301303 = local_a;
    }
    else {
      DAT_301303 = 0x80;
    }
  }
  else {
    DAT_301303 = 0x7f;
  }
  DAT_301300 = DAT_301306;
  _DAT_301af6 = (ushort)DAT_301306;
  local_c = 1;
  do {
    bVar1 = *(byte *)((uint3)local_c + 0x301306);
    bVar5 = bVar1;
    if (DAT_301300 <= bVar1) {
      bVar5 = DAT_301300;
    }
    DAT_301300 = bVar5;
    _DAT_301af6 = _DAT_301af6 + bVar1;
    local_c = local_c + 1;
  } while (local_c < 5);
  MDL = _DAT_301af6 / 5;
  MDH = _DAT_301af6 % 5;
  MDC = MDC | 0x10;
  DAT_301302 = (char)MDL;
  return;
}


// ================= FUN_04f97a @ 04f97a =================

/* WARNING: Removing unreachable block (ram,0x04fd0e) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

short FUN_04f97a(void)

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
  
  if (DAT_01584e < FUN_00f40e) {
    DAT_3001f4 = DAT_3001f4 | 0x80;
  }
  else {
    DAT_3001f4 = DAT_3001f4 & 0x7f;
  }
  if ((DAT_3001f4 & 0x80) == 0) {
    if ((DAT_3001f4 & 2) == 0) {
      if (_DAT_3001fa == 0) {
        uRam00fd22 = uRam00fd22 & 0xfffe;
      }
      else {
        _DAT_3001fa = _DAT_3001fa + -1;
        uRam00fd22 = uRam00fd22 | 1;
      }
    }
    else {
      _DAT_3001fa = DAT_01584c;
      uRam00fd22 = uRam00fd22 | 1;
    }
  }
  if ((DAT_3001f4 & 0x80) == 0) {
    DAT_3001f4 = DAT_3001f4 & 0xfd;
  }
  else {
    DAT_3001f4 = DAT_3001f4 | 2;
  }
  if (((DAT_3001f4 & 0x80) == 0) || ((uRam00fd22 & 1) != 0)) {
    DAT_3001f4 = DAT_3001f4 & 0xf7;
  }
  else {
    DAT_3001f4 = DAT_3001f4 | 8;
  }
  if ((DAT_3001f4 & 0x80) != 0) {
    if (((DAT_3001f4 & 8) == 0) || ((DAT_3001f4 & 0x10) != 0)) {
      if (_DAT_3001f2 == 0) {
        uRam00fd22 = uRam00fd22 & 0xffef;
      }
      else {
        _DAT_3001f2 = _DAT_3001f2 + -1;
        uRam00fd22 = uRam00fd22 | 0x10;
      }
    }
    else {
      _DAT_3001f2 = DAT_01585c;
      uRam00fd22 = uRam00fd22 | 0x10;
    }
  }
  if ((DAT_3001f4 & 8) == 0) {
    DAT_3001f4 = DAT_3001f4 & 0xef;
  }
  else {
    DAT_3001f4 = DAT_3001f4 | 0x10;
  }
  if (((uRam00fd22 & 1) == 0) && ((DAT_3001f4 & 0x80) == 0)) {
    DAT_3001f4 = DAT_3001f4 & 0xdf;
  }
  else if (((DAT_3001f4 & 4) != 0) && ((uRam00fd22 & 0x10) == 0)) {
    DAT_3001f4 = DAT_3001f4 | 0x20;
  }
  if ((uRam00fd22 & 0x10) == 0) {
    DAT_3001f4 = DAT_3001f4 & 0xfb;
  }
  else {
    DAT_3001f4 = DAT_3001f4 | 4;
  }
  if ((DAT_3001f4 & 0x20) == 0) {
    if ((DAT_012d71 < DAT_3015d8) && ((DAT_3001f4 & 1) != 0)) {
      _DAT_302486 = DAT_015858;
    }
    else {
      _DAT_302486 = DAT_01584e;
    }
  }
  else {
    bVar1 = _DAT_302486 < DAT_015844;
    _DAT_302486 = _DAT_302486 - DAT_015844;
    if (bVar1) {
      _DAT_302486 = 0;
    }
    if (DAT_015858 < _DAT_302486) {
      _DAT_302486 = DAT_015858;
    }
    else if (_DAT_302486 < DAT_01584e) {
      _DAT_302486 = DAT_01584e;
    }
  }
  if ((_DAT_303c1e & 1) == 0) {
    uVar7 = _DAT_302486;
    if ((DAT_012d62 & 1) == 0) {
      uVar7 = _DAT_3001fe;
    }
  }
  else {
    uVar7 = _DAT_304f32;
    if ((uRam00fd00 & 0x10) == 0) {
      uVar7 = DAT_015850;
    }
  }
  uVar5 = uVar7;
  if (((DAT_301271 & 0x20) != 0) && (uVar5 = _DAT_301966, uVar7 < _DAT_301966)) {
    uVar5 = uVar7;
  }
  uVar7 = _DAT_300200;
  if (((uRam00fd7a & 0x10) != 0) && (uVar7 = uVar5, (DAT_3001f4 & 0x40) != 0)) {
    uVar7 = _DAT_300200 - DAT_015846;
    if (_DAT_300200 < DAT_015846) {
      uVar7 = 0;
    }
    if (DAT_015858 < uVar7) {
      _DAT_300200 = DAT_015858;
      uVar7 = _DAT_300200;
    }
    else if (uVar7 < DAT_015852) {
      _DAT_300200 = DAT_015852;
      uVar7 = _DAT_300200;
    }
  }
  _DAT_300200 = uVar7;
  if ((uRam00fd7a & 0x10) == 0) {
    DAT_3001f4 = DAT_3001f4 & 0xbf;
  }
  else {
    DAT_3001f4 = DAT_3001f4 | 0x40;
  }
  uVar7 = DAT_01585a;
  if ((uRam00fd70 & 0x200) == 0) {
    uVar7 = uVar5;
    if (((uRam00fd5c & 2) != 0) && (uVar7 = DAT_015856, uVar5 < DAT_015856)) {
      uVar7 = uVar5;
    }
    uVar5 = uVar7;
    if (((uRam00fd7a & 0x10) != 0) && (uVar5 = _DAT_300200, uVar7 < _DAT_300200)) {
      uVar5 = uVar7;
    }
    if ((uRam00fd22 & 8) == 0) {
      if (((uRam00fd42 & 0x4000) != 0) && (FUN_00f40e < DAT_015854)) {
        uRam00fd22 = uRam00fd22 | 8;
      }
    }
    else {
      if (((uRam00fd42 & 0x4000) == 0) && ((uRam00fd22 & 2) == 0)) {
        uRam00ff10 = uRam00ff10 & 0xffbf;
      }
      else {
        uRam00ff10 = uRam00ff10 | 0x40;
      }
      uRam00fd22 = uRam00fd22 & 0xfff7 | ((uRam00ff10 & 0x40) >> 6) << 3;
    }
    uVar7 = uVar5;
    if (((uRam00fd22 & 8) != 0) && (uVar7 = DAT_015854, uVar5 <= DAT_015854)) {
      uVar7 = uVar5;
    }
    if ((uRam00fd70 & 0x20) != 0) {
      uVar5 = FUN_040b3e(0x2d64,DAT_301258);
      uVar5 = (uVar5 & 0xff) * 0xa0;
      if (uVar5 <= uVar7) {
        uVar7 = uVar5;
      }
    }
  }
  uVar9 = CONCAT22(_DAT_3001f8,_DAT_3001f6);
  uVar4 = CONCAT22(MDH,MDL);
  uVar5 = DAT_015848 + uVar7;
  if (DAT_015848 + uVar7 < DAT_015848 || DAT_015848 + uVar7 < uVar7) {
    uVar5 = 0xffff;
  }
  if (uVar5 < FUN_00f40e) {
    uRam00fd22 = uRam00fd22 | 4;
  }
  else {
    uRam00fd22 = uRam00fd22 & 0xfffb;
  }
  if (_DAT_302b0a < 1) {
    _DAT_302488 = FUN_00f40e;
  }
  else {
    uVar4 = (uint)_DAT_3001fc * (uint)(ushort)(_DAT_302b0a >> 5);
    uVar5 = (ushort)uVar4;
    MDC = MDC | 0x10;
    if (0xffff < uVar4) {
      uVar5 = 0xffff;
    }
    _DAT_302488 = FUN_00f40e + uVar5;
    if (FUN_00f40e + uVar5 < FUN_00f40e || FUN_00f40e + uVar5 < uVar5) {
      _DAT_302488 = 0xffff;
    }
  }
  MDH = (undefined2)(uVar4 >> 0x10);
  MDL = (undefined2)uVar4;
  _DAT_302480 = uVar7 - _DAT_302488;
  if (uVar7 < _DAT_302488) {
    if (_DAT_302480 >= 0) {
      _DAT_302480 = -0x8000;
    }
  }
  else if (_DAT_302480 < 0) {
    _DAT_302480 = 0x7fff;
  }
  if ((_DAT_302480 == DAT_01584a ||
       _DAT_302480 - DAT_01584a < 0 !=
       (_DAT_302480 < 0 != DAT_01584a < 0 && _DAT_302480 - DAT_01584a < 0 != _DAT_302480 < 0)) &&
     ((_DAT_302480 < 1 || (_DAT_302484 < _DAT_301ac8)))) {
    if (_DAT_302480 < 1) {
      uRam00fd22 = uRam00fd22 | 2;
    }
  }
  else {
    uRam00fd22 = uRam00fd22 & 0xfffd;
  }
  _DAT_30248a = uVar7;
  if ((uRam00fd22 & 2) == 0) {
    _DAT_304f30 = _DAT_301ac8;
    _DAT_30647c = 0;
    uVar9 = 0;
  }
  else if (_DAT_302484 != 0) {
    uVar9 = FUN_042df4((ushort)DAT_30404a << 8,_DAT_302480,_DAT_3001f8,_DAT_3001f6);
    sVar6 = (short)((uint)uVar9 >> 0x10);
    uVar5 = (ushort)((int)sVar6 * 0x63a);
    MDC = MDC | 0x10;
    uVar7 = sVar6 * -0x8000;
    sVar6 = (short)((uint)((int)sVar6 * 0x63a) >> 0x10) + (sVar6 >> 1) +
            (ushort)(uVar5 + uVar7 < uVar5 || uVar5 + uVar7 < uVar7);
    _DAT_300204 = sVar6 >> 0xd;
    _DAT_300202 = uVar5 + uVar7 >> 0xd | sVar6 * 8;
    uVar7 = (ushort)(_DAT_300202 < 0x7fff);
    if (_DAT_300204 == uVar7 && _DAT_300202 == 0x7fff ||
        (short)(_DAT_300204 - uVar7) < 0 !=
        ((short)_DAT_300204 < 0 &&
        (short)(_DAT_300204 - (_DAT_300202 < 0x7fff)) < 0 != (short)_DAT_300204 < 0)) {
      _DAT_30247c = _DAT_300202;
      if ((short)((_DAT_300204 + 1) - (ushort)(_DAT_300202 < 0x8000)) < 0 !=
          (-1 < (short)_DAT_300204 &&
          (short)((_DAT_300204 + 1) - (ushort)(_DAT_300202 < 0x8000)) < 0 != (short)_DAT_300204 < 0)
         ) {
        _DAT_30247c = 0x8000;
      }
    }
    else {
      _DAT_30247c = 0x7fff;
    }
  }
  _DAT_3001f8 = (undefined2)((uint)uVar9 >> 0x10);
  _DAT_3001f6 = (undefined2)uVar9;
  sVar6 = (ushort)DAT_30404b * 0x29;
  if (sVar6 < 0) {
    iVar3 = (int)_DAT_302480 * (int)sVar6;
    uVar5 = (ushort)iVar3;
    uVar7 = _DAT_302480 * -0x8000;
    iVar2 = CONCAT22((short)((uint)iVar3 >> 0x10) + (_DAT_302480 >> 1) +
                     (ushort)(uVar5 + uVar7 < uVar5 || uVar5 + uVar7 < uVar7),uVar5 + uVar7);
    sVar6 = _DAT_302480 >> 1;
  }
  else {
    iVar2 = (int)_DAT_302480 * (int)sVar6;
    sVar6 = _DAT_302480;
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
  _DAT_30247e = (short)iVar2;
  if ((uRam00fd22 & 4) == 0) {
    if ((uRam00fd22 & 2) == 0) {
      _DAT_302484 = (ushort)DAT_012d63 << 8;
    }
    else {
      sVar6 = _DAT_30247c + _DAT_30247e;
      if ((short)_DAT_30247c < 0 == _DAT_30247e < 0 &&
          (short)(_DAT_30247c + _DAT_30247e) < 0 != (short)_DAT_30247c < 0) {
        sVar6 = 0x7fff;
      }
      bVar1 = 1 < (_DAT_304f30 >> 1 & 1);
      uVar7 = _DAT_304f30 >> 2;
      sVar8 = sVar6 + uVar7 + (ushort)bVar1;
      if ((-1 < sVar6 && (short)(sVar6 + uVar7 + (ushort)bVar1) < 0 != sVar6 < 0) ||
         (sVar6 = sVar8 + uVar7, -1 < sVar8 && (short)(sVar8 + uVar7) < 0 != sVar8 < 0)) {
        sVar6 = 0x7fff;
      }
      uVar7 = (ushort)DAT_012d63;
      _DAT_302482 = sVar6;
      if (sVar6 != uVar7 * 0x80 &&
          (short)(sVar6 + uVar7 * -0x80) < 0 ==
          (sVar6 < 0 && (short)(sVar6 + uVar7 * -0x80) < 0 != sVar6 < 0)) {
        _DAT_302482 = (ushort)DAT_012d63 << 7;
      }
      if (_DAT_302482 < 0) {
        _DAT_302484 = 0;
      }
      else {
        _DAT_302484 = _DAT_302482 << 1;
      }
    }
  }
  else {
    _DAT_302484 = 0;
  }
  return sVar6;
}


