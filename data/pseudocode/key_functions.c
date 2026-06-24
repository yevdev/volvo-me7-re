// Pseudo-C of key Volvo ME7.0 (50GPHJ) control functions
// Ghidra + keyhana C166 module. C166 has no Hex-Rays decompiler;
// this is Ghidra's SLEIGH-based pseudo-C, best read alongside the IDA disassembly dumps.

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
  func_0x05369c();
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
  func_0x0c5f2c();
  func_0x03b35e();
  func_0x0c9f44();
  func_0x0ca5c6();
  func_0x0cb61c();
  func_0x0cb50a();
  func_0x0ca51e();
  func_0x0c7eea();
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
           ((MDL <= bRam01ba9f && (uRam027dec <= (ushort)(sRam3029c6 * 2))))) {
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
      uVar10 = me7_lookup_1d_word(0x3c14,9,sRam3029c6);
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
        uVar10 = me7_lookup_1d_word(0x3c46,9,sRam3029c6);
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
    if (((((bRam019571 & 4) == 0) || (cRam3014dd != '\0')) && ((bRam019571 & 4) != 0)) ||
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
     ((((bRam301612 & 4) == 0 || (uRam3052a8 < (ushort)bRam019a84 * 0x100)) && (uVar10 < bRam019a85)
      ))) {
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
    if ((bRam012d71 < bRam3015d8) && ((bRam3001f4 & 1) != 0)) {
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
    if ((uRam00fd00 & 0x10) == 0) {
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
  
  if (cRam3014dd == '\a') {
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


// ================= maf_linearize @ 0c96fc =================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* HFM/MAF voltage -> air-mass signal loc_F45E (linear gain/offset) */

ushort maf_linearize(void)

{
  bool bVar1;
  short sVar2;
  uint uVar3;
  ushort uVar4;
  short sVar5;
  ushort uVar6;
  
  if ((uRam00fd70 & 8) != 0) {
    uVar6 = uRam302cc4 - uRam301954;
    if (uRam302cc4 < uRam301954) {
      if ((short)uVar6 >= 0) {
        uVar6 = 0x8000;
      }
    }
    else if ((short)uVar6 < 0) {
      uVar6 = 0x7fff;
    }
    sVar5 = (short)uVar6 >> 0xf;
    if ((short)uVar6 < 0) {
      sVar5 = sVar5 * uRam302ca2;
      MDC = MDC | 0x10;
    }
    MDL = (ushort)((uint)uVar6 * (uint)uRam302ca2);
    MDH = (short)((uint)uVar6 * (uint)uRam302ca2 >> 0x10);
    MDC = MDC | 0x10;
    _ml_hfm = (sVar5 + MDH) * 2 + (ushort)(MDL * 2 < MDL || MDL * 2 < MDL);
    return uRam302ca2;
  }
  if ((uRam00fd70 & 2) == 0) {
    uVar6 = uRam301952 - uRam302cb4;
    if (uRam301952 < uRam302cb4) {
      if ((short)uVar6 >= 0) {
        uVar6 = 0x8000;
      }
    }
    else if ((short)uVar6 < 0) {
      uVar6 = 0x7fff;
    }
    sVar5 = (short)uVar6 >> 0xf;
    if ((short)uVar6 < 0) {
      sVar5 = sVar5 * uRam302ca2;
      MDC = MDC | 0x10;
    }
    MDL = (ushort)((uint)uVar6 * (uint)uRam302ca2);
    MDH = (short)((uint)uVar6 * (uint)uRam302ca2 >> 0x10);
    MDC = MDC | 0x10;
    _ml_hfm = (sVar5 + MDH) * 2 + (ushort)(MDL * 2 < MDL || MDL * 2 < MDL);
    return MDL * 2;
  }
  uVar6 = sRam301950 * 4;
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
  bVar1 = 1 < (uRam302cb4 & 1);
  uVar6 = uRam302cb4 >> 1;
  sVar2 = (sVar5 - uVar6) - (ushort)bVar1;
  if ((sVar5 < 0 && (short)((sVar5 - uVar6) - (ushort)bVar1) < 0 != sVar5 < 0) ||
     (uVar4 = sVar2 - uVar6, sVar2 < 0 && (short)(sVar2 - uVar6) < 0 != sVar2 < 0)) {
    uVar4 = 0x8000;
  }
  sVar5 = (short)uVar4 >> 0xf;
  if ((short)uVar4 < 0) {
    sVar5 = sVar5 * uRam302ca2;
  }
  MDL = (ushort)((uint)uVar4 * (uint)uRam302ca2);
  MDH = (short)((uint)uVar4 * (uint)uRam302ca2 >> 0x10);
  MDC = MDC | 0x10;
  _ml_hfm = (sVar5 + MDH) * 2 + (ushort)(MDL * 2 < MDL || MDL * 2 < MDL);
  return uRam302ca2;
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
  if ((DAT_00fd02 & 0x800) != 0) {
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
    if (((uRam00fd00 & 0x2000) == 0) && (nmot_rpmclass != '\0')) {
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
  if (_ml_hfm < 0) {
    uVar10 = 0;
  }
  else if (_ml_hfm == 0xfff ||
           _ml_hfm + -0xfff < 0 != (_ml_hfm < 0 && _ml_hfm + -0xfff < 0 != _ml_hfm < 0)) {
    uVar10 = _ml_hfm << 4;
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
  if (((DAT_00fd4e & 0x4000) == 0) || ((bRam30169c & 8) == 0)) {
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
  uRam302424 = func_0x041526(0x50fc,uRam0150fb,0x5108,0x5110,sRam30244a,bRam3014dd);
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
  if (((((DAT_00fd1e & 2) == 0) && ((uRam303c1e & 1) == 0)) && (bRam3014dd == 0)) &&
     ((bRam3015d8 < bRam012a0c && ((DAT_00fd1e & 0x80) != 0)))) {
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
    if ((((((DAT_00fd1a & 0x40) == 0) || ((uRam00fd1c & 0x2000) != 0)) || (bRam3014dd == 0)) ||
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
      if ((((PSW & 0x40) == 0) && ((uRam0150ee & 4) == 0)) || (bRam3015d8 < bRam012a0d))
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
      if ((bRam3014dd != 0) && (bRam012a0b < bRam3015d8)) {
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
  MDL = (ushort)bVar8 * (ushort)*(byte *)((uint3)bRam3014dd + 0x129c4);
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
            uVar12 = (ushort)bVar8 * (ushort)*(byte *)((uint3)bRam3014dd + 0x129cc);
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
            uVar12 = me7_lookup_2d_misc(uRam015396,0x5398,uRam015397,0x53a0,0x53b0,bRam3014dd,
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
            uVar11 = me7_lookup_2d_misc(uRam015396,0x5398,uRam015397,0x53a0,0x53b0,bRam3014dd,
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
    bVar7 = (byte)((ushort)(byte)(-cVar6 - 1) * (ushort)*(byte *)((uint3)bRam3014dd + 0x181c9) >> 8)
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
  uRam305256 = me7_lookup_1d_word(0x3542,8,cRam3015d8);
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
  if (cRam3015d8 == '\0') {
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
    uRam3052a8 = uRam3052aa << 1;
  }
  else {
    uRam3052a8 = 0xffff;
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
      sVar13 = -0x8000 - uRam3052a8;
      if (uRam3052a8 < 0x8001) {
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
     (((((bRam3015ff & 2) == 0 || ((uRam0239c6 < uRam3052a8 && (uRam3052a8 < uRam0239c8)))) &&
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
    if ((DAT_00fd02 & 0x200) == 0) {
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
    if ((DAT_00fd02 & 0x200) == 0) {
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
    if ((uRam00fd00 & 0x10) == 0) {
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
    if ((bVar4) && (bRam019701 < bRam3015d8)) goto LAB_07d664;
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
  if ((((((uRam305176 == 0) || (uVar6 = uRam302634 & 1, uVar6 != 0)) || ((uRam00fd00 & 0x8000) == 0)
        ) || ((uVar6 = 0, (bRam301581 & 2) == 0 &&
              ((uVar6 = 0, (bRam30174c & 1) == 0 || (uVar6 = uRam305170, uRam021ea8 <= uRam305170)))
              ))) || ((bRam304979 < bRam019700 && ((uRam00fd48 & 0x20) != 0)))) ||
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
       (((DAT_00fd02 & 0x1000) == 0 || (((bRam301277 & 0x80) == 0 || ((bRam301277 & 4) == 0)))))) ||
      ((bRam0196c9 & 0x80) != 0)))) {
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
  if ((DAT_00fd02 & 0x200) != 0) {
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
  if ((((bRam301276 & 8) == 0) && ((uRam00fd1c & 0x2000) == 0)) && (bRam018546 < bRam3015d8)) {
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
    if (bRam018547 < bRam3015d8) {
      bRam301341 = bRam301341 | 0x10;
    }
    else if (bRam3015d8 < bRam018548) {
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
    if (bRam018544 < bRam3015d8) {
      bRam301341 = bRam301341 | 8;
    }
    else if (bRam3015d8 < bRam018545) {
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
  bVar2 = me7_lookup_1d_byte(0x4aa,6,bRam3015d8);
  if (bVar3 < bVar2) {
    bVar3 = me7_lookup_1d_byte(0x4aa,6,bRam3015d8);
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
  if (((DAT_00fd02 & 0x2000) == 0) || ((uRam303bf6 & 1) != 0)) {
    if (((uRam303bd6 & 1) == 0) && (bRam30a008 <= bRam309626)) {
      if ((bRam0189fd < bRam3015d8) &&
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
  if ((DAT_00fd02 & 0x200) != 0) {
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
      if ((bRam30169c & 8) == 0) {
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
      if ((((DAT_00fd4e & 0x4000) != 0) && ((bRam30169c & 8) != 0)) && ((bRam301362 & 1) == 0)) {
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
  if (((DAT_00fd4e & 0x4000) == 0) || ((bRam30169c & 8) == 0)) {
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
    if ((bRam019ff0 < bRam3015d8) && (bRam3015d8 < bRam019fef)) {
      bRam301642 = bRam301642 | 4;
    }
    else {
      bRam301642 = bRam301642 & 0xfb;
    }
    bVar10 = me7_lookup_1d_byte(0x1fb5,6,bRam3015d8);
    if (bVar10 < bRam304970) {
      bVar10 = me7_lookup_1d_byte(0x1f9f,6,bRam3015d8);
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
    if ((bRam3015d8 < bRam019ff2) || (bRam019ff1 < bRam3015d8)) {
      bRam301642 = bRam301642 & 0xf7;
    }
    else {
      bRam301642 = bRam301642 | 8;
    }
    bVar10 = me7_lookup_1d_byte(0x1fc0,6,bRam3015d8);
    if (bVar10 < bRam304970) {
      bVar10 = me7_lookup_1d_byte(0x1faa,6,bRam3015d8);
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
    uVar17 = me7_lookup_2d_byte(0x1f60,6,bRam3015d8,uRam30497a);
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
    uRam304f3e = uRam3029c6;
  }
  else {
    uVar2 = (uint)uRam3069be * (uint)*(byte *)((uint3)bRam3014dd + 0x182ba) * 0x100;
    uVar5 = (ushort)(uVar2 >> 0x10);
    MDC = MDC | 0x10;
    uRam304f3e = uRam3029c6 + uVar5;
    if (uRam3029c6 + uVar5 < uRam3029c6 || uRam3029c6 + uVar5 < uVar5) {
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
    iVar1 = (int)sRam304f36 * (int)(short)(ushort)*(byte *)((uint3)bRam3014dd + 0x182b2);
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
                      (*(undefined2 *)((uint3)bRam3014dd * 2 + 0x1edc0),sRam304f36,uRam300206._2_2_,
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
  
  if ((uRam3018d8 & 4) == 0) {
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
     (((uRam303c1e & 1) != 0 || ((uRam3018d8 & 4) == 0)))) {
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
    if ((((!bVar3) || (sRam3029c6 != 0)) || (cRam300a02 == '\0')) || (cRam3009fe == '\0'))
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
            ((bRam01263e <= bRam3015d8 || ((uRam303c1e & 1) != 0)))) {
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


// ================= diag_rationality_monitor @ 09a034 =================

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
  if (((bRam30166c & 1) == 0) && ((uRam3018d6 & 0x400) != 0)) {
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
  
  if ((uRam3018d6 & 0x200) == 0) {
    return 0;
  }
  if ((uRam00fd00 & 0x10) == 0) {
    uRam302b5e = func_0x040f32(0x3f16,rl_byte,uRam302b5e);
  }
  else {
    uRam302b5e = func_0x040f32(0x3f1a,rl_byte,uRam302b5e);
  }
  uRam30214c = uRam302b5e >> 8 | uRam302b5e << 8;
  if ((uRam00fd00 & 0x10) == 0) {
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
    if ((uRam00fd00 & 0x10) != 0) {
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
  if ((uRam00fd00 & 0x10) == 0) {
    bVar16 = bRam013f1f;
  }
  uVar14 = (ushort)bVar16;
  bVar16 = bRam013f29;
  if ((uRam00fd00 & 0x10) == 0) {
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
  if ((uRam00fd00 & 0x10) == 0) {
    uVar9 = uRam013f21;
  }
  sVar15 = CONCAT11((char)(uVar10 >> 8),uVar9);
  sVar17 = sVar15 - (sVar15 - (ushort)bVar16 >> 1);
  bRam30213e = (byte)sVar17;
  uVar9 = uRam013f2b;
  if ((uRam00fd00 & 0x10) == 0) {
    uVar9 = uRam013f22;
  }
  sVar13 = CONCAT11((char)((ushort)sVar17 >> 8),uVar9);
  sVar17 = sVar13 - ((ushort)(sVar13 - sVar15) >> 1);
  bRam30213f = (byte)sVar17;
  uVar9 = uRam013f2c;
  if ((uRam00fd00 & 0x10) == 0) {
    uVar9 = uRam013f23;
  }
  sVar15 = CONCAT11((char)((ushort)sVar17 >> 8),uVar9);
  sVar17 = sVar15 - ((ushort)(sVar15 - sVar13) >> 1);
  bRam302140 = (byte)sVar17;
  uVar9 = uRam013f2d;
  if ((uRam00fd00 & 0x10) == 0) {
    uVar9 = uRam013f24;
  }
  sVar13 = CONCAT11((char)((ushort)sVar17 >> 8),uVar9);
  sVar17 = sVar13 - ((ushort)(sVar13 - sVar15) >> 1);
  bRam302141 = (byte)sVar17;
  uVar9 = uRam013f2e;
  if ((uRam00fd00 & 0x10) == 0) {
    uVar9 = uRam013f25;
  }
  sVar15 = CONCAT11((char)((ushort)sVar17 >> 8),uVar9);
  sVar17 = sVar15 - ((ushort)(sVar15 - sVar13) >> 1);
  bRam302142 = (byte)sVar17;
  bVar16 = bRam013f2f;
  if ((uRam00fd00 & 0x10) == 0) {
    bVar16 = bRam013f26;
  }
  bVar19 = (byte)((ushort)(CONCAT11((char)((ushort)sVar17 >> 8),bVar16) - sVar15) >> 1);
  bRam302143 = bVar16 - bVar19;
  bRam302144 = bVar16 + bVar19;
  if ((byte)(bVar16 + bVar19) < bVar16 || (byte)(bVar16 + bVar19) < bVar19) {
    bRam302144 = 0xff;
  }
  bVar16 = bRam013f1b;
  if ((uRam00fd00 & 0x10) == 0) {
    bVar16 = bRam013f17;
  }
  uVar14 = (ushort)bVar16;
  bVar16 = bRam013f1c;
  if ((uRam00fd00 & 0x10) == 0) {
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
  if ((uRam00fd00 & 0x10) == 0) {
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
    if ((uRam00fd00 & 0x10) == 0) {
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
     ((bRam3015d8 <= bRam01a0f0 || ((uRam00fd64 & 0x800) == 0)))) {
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
     (((uRam00fd5c & 2) == 0 && ((bRam3015d8 <= bRam01a0f0 || ((uRam00fd64 & 0x800) == 0)))))) {
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
           (((uRam00fd00 & 0x10) != 0 &&
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
  if ((((uRam00fd1c & 0x2000) == 0) || (bRam3015d8 != 0)) || ((uRam303c1e & 1) != 0)) {
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
  if ((((uRam00fd1c & 0x2000) == 0) || (bRam3015d8 != 0)) || ((uRam303c1e & 1) != 0)) {
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
      if ((uRam00fd00 & 0x10) != 0) {
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


