# ME7 (50GPHJ) C166 — map lookup / interpolation machinery

> **ME7-RE docs:** [Algorithm](ALGORITHM.md) · [Boost](boost.md) · [Ignition](ignition.md) · [Fueling](fueling.md) · [Torque](torque.md) · [Load/rl](load-rl.md) · [Charge](charge.md) · [Cam timing](cam-timing.md) · [Lookup](lookup.md) · [Maps](map-inventory.md) · [Warm-up/idle](warmup-idle-thermal.md) · [Idle gov](idle-governor.md) · [Limiters](limiters.md) · [RAM names](ram-names.md) · [Byte-maps](bytemap_callers.md) · [Methodology](methodology.md) · [↑ README](../README.md)

The table-lookup family, decoded from the C166 disassembly of the stock 50GPHJ firmware
(Infineon C167CR). Worked in IDA on `<work>\me7_stock_lookup.i64`.
Code is byte-identical across calibration revisions; only calibration data differs.

Legend: **[C]** = confirmed from the disassembly cited; **[I]** = inferred / structural.
All addresses are physical (`(page<<14)|offset`) unless noted. The map-pointer pair the
caller loads is `(offset=r12, page=r13)`, so the data address = `(r13<<14)|r12`.

---

## 0. TL;DR — the family

There is **not** one universal lookup. There is a small family, selected by data width
(word vs byte), dimensionality (1-D vs 2-D), and signedness of the axis compare:

| Routine | Addr | Dim | Z width | Axis cmp | Interp domain | Purpose |
|---|---|---|---|---|---|---|
| `sub_41A68` | 0x41A68 | 1-D | **word** | unsigned | 16-bit | the common word table (NOT 2-D) |
| `sub_41B5A` | 0x41B5A | 1-D | word | **signed** | 16-bit | word table, signed axis |
| `sub_419F4` | 0x419F4 | 1-D | **byte** | unsigned | 8-bit | byte table (e.g. KFLBTS output map) |
| `sub_41CC0` | 0x41CC0 | **2-D** | word | unsigned | 16-bit | true bilinear word map |
| `sub_421F4` | 0x421F4 | 2-D | word | unsigned | hi-byte frac | 2-D map, caller-supplied frac in regs |
| `sub_42082` | 0x42082 | 1-D | **signed byte** z | unsigned | hi-byte frac | signed-byte 1-D interp |
| `sub_416B0` | 0x416B0 | axis | — | unsigned | — | **byte-axis breakpoint search** (returns frac+idx) |
| `sub_416F0` | 0x416F0 | axis | — | **signed** | — | byte-axis search, signed |
| `sub_41778` | 0x41778 | axis | — | — | — | word-axis breakpoint search (pair of 420A8) |
| `sub_420A8` | 0x420A8 | z | word | — | hi-byte frac | word z-row interp given idx+frac |
| `sub_42464` | 0x42464 | 1-D | word | unsigned | byte frac | wrapper: `416B0`(axis)+`420A8`(z) |
| `sub_42486` | 0x42486 | 1-D | word | — | byte frac | wrapper: `41778`(axis)+`420A8`(z) |

The boost controller's helpers (`sub_43904`, `sub_42F16`, `sub_42DF4`, `sub_42CF4`) are
**integrators / rate-limiters**, not lookups — documented in §5.

---

## 1. `sub_41A68` — common 1-D word table with interpolation  **[C]**

**This is the routine `findings.md` called the "universal 2D map lookup". It is actually a
1-D interpolated word table.** Every caller in `lookup_callers.txt` passes a *single* input:

```
mov   r12, #<offset>     ; table pointer low (14-bit)
mov   r13, #<page>       ; table page   -> data @ (page<<14)|offset
mov   r14, <input>       ; the single axis/input value (word)
calls 4, sub_41A68       ; -> interpolated z in r4
```
e.g. `sub_4E5EC` @ 0x4E5F8: `r12=#2736, r13=#7, r14=word_F410` → result in `r4` (0x4E5FC).

### Binary layout it parses  **[C]**
At the table pointer:
```
+0   : word  LEN      ; only low byte used (0x41A74: and r1,#0FFh)  -> N = LEN & 0xFF
+2   : word  X[0]                 ; N axis breakpoints (monotonic ascending)
...
+2N  : word  Z[0]                 ; N z-values, same count as axis points
...
```
So a 1-D word table = `[len_word][N × x_word][N × z_word]`. The z-block starts at the word
index `1 + N` (the `add r12,r14[`/`](/)add r12,r15` at 0x41AAE/0x41AB0 advances by `2*(N) +
2*idx`).

### Algorithm, instruction by instruction  **[C]**
1. `0x41A68` save input → r10. `0x41A6C mov r14,[r12+]` read LEN, advance r12 to X[0].
2. `0x41A74-7A` `r1 = (LEN & 0xFF) << 1` = byte length of the axis block (2N).
3. **Breakpoint search** (`r2` walks the axis array):
   - `0x41A80` if `input <= X[0]` (unsigned, `cc_ULE`) → jump to end with `idx=0, frac=0`
     (clamp low: result = Z[0], no interpolation).
   - `0x41A84` `r2 = &X[0] + 2N - 2` = `&X[N-1]` (top breakpoint).
   - `0x41A8A` if `input >= X[N-1]` (`cc_NC`) → take top cell (clamp high, frac=0 path via
     `loc_41AA4`: `idx = (r2-base)/2`).
   - else `0x41A90` walk **downward** by 2 until `input >= X[i]` (`cmp; jmpr cc_C` loop).
   - `0x41A98` found bracketing cell `[X[i], X[i+1])`:
     `r4 = input - X[i]`            (numerator delta, 0x41A9C)
     `r5 = X[i+1] - X[i]`           (interval width, 0x41A9E/0x41AA2)
     `r15 = idx = (r2 - base)/2`    (0x41AA4-A8)
4. **Index into Z**: `0x41AAE r14 = LEN<<1` (skip whole axis block = 2N bytes — note it
   re-uses r14 which held LEN, after `shl r14,#1`), `0x41AAC r15 = idx<<1`,
   `r12 = base + 2N + 2*idx` → `&Z[idx]`.
5. **Interpolate** (`0x41AB2-`):
   - `r2 = frac_num = input - X[i]`; `r4 = Z[idx]` (lower z, post-increment to `&Z[idx+1]`).
   - if `frac_num == 0` → return `Z[idx]` exactly (`0x41ABA cc_Z`).
   - `r3 = Z[idx+1]`. If `Z[idx] <= Z[idx+1]` (rising): `r3 = Z[i+1]-Z[i]`;
     `MDL:MDH = r3 * frac_num` (`mulu`); `divlu r5` (÷ interval) → quotient MDL;
     `r4 = Z[i] + quotient`.
   - else (falling): `r1 = Z[i]-Z[i+1]`; `*frac_num /interval`; `r4 = Z[i] - quotient`.
   - **`result = Z[i] + (Z[i+1]-Z[i]) * (input-X[i]) / (X[i+1]-X[i])`**, computed with the
     sign handled by branching so the `mulu/divlu` operands stay unsigned. Truncating
     (floor) division — no rounding. Clamps at both axis ends.

Result in **r4** (16-bit). `0x41AE0 rets`.

> `sub_41B5A` (0x41B5A) is **identical** except the axis comparisons use **signed**
> conditions (`cc_SLE[`/`](/)cc_SGE[`/`](/)cc_SGT` at 0x41B74/0x41B7E/0x41BB4) and the down-walk is a
> separate signed loop. Use it for tables whose **axis** holds signed values (e.g. boost
> control delta tables — `sub_DBB04` calls it at 0xDBC64 / 0xDBD2 for KFLDR* error tables).
> Same `[len][x[]][z[]]` layout. **[C]**

---

## 2. `sub_419F4` — 1-D **byte** table with interpolation  **[C]**

Same calling convention `(offset, page, input)`, result in **r4**. Used for byte-resolution
tables — including the KFLBTS-related output maps in `sub_86318` (called at 0x868B6,
0x86950, 0x869DC, 0x86A68 with table ptrs #1A5B/#1A4E/#1A68/#1A75, page 6).

### Binary layout  **[C]**
```
+0 : byte LEN  (N)          ; 0x419F8 movb rl1,[r12+]
+1 : byte X[0..N-1]         ; N axis breakpoints (byte)
+1+N : byte Z[0..N-1]       ; N z-values (byte)
```
1-D byte table = `[len_byte][N × x_byte][N × z_byte]`.

Algorithm mirrors `sub_41A68` but byte-wide: axis search with `cmpb` (0x41A06/A10/A1A),
clamp-low at X[0] (`cc_ULE`), clamp-high at X[N-1] (`cc_NC`). z indexed at
`base + N + idx` (0x41A30 `add r12,r1` where r1=N, then `add r12,r15` idx). Interp:
`MDL:MDH = (Z-delta) * (input-X[i])`, `divu r5` (8-bit ÷). Result byte zero-extended in r4.
Truncating division, clamps both ends. **[C]**

> `sub_42082` (0x42082) is a related **signed-byte** 1-D interp: z read with `movbs`
> (sign-extend), fraction supplied in the **high byte of the input word** (`shl r14,#8; shr
> r14,#1`), interval implicitly the next cell. Used in `sub_4E5EC` (0x4E622/0x4E63C) for
> sensor scaling. **[C]**

---

## 3. `sub_41CC0` — true **2-D bilinear** word map  **[C]**

This is the real 2-D map lookup. Calling convention:
```
mov   r12, #<offset>     ; map pointer low
mov   r13, #<page>       ; map page
mov   r14, <x_input>     ; first-axis input
mov   r15, <y_input>     ; second-axis input
calls 4, sub_41CC0       ; -> interpolated z in r4
```
(96 callers, e.g. `sub_DBB04` @ 0xDBD22 for a boost map.)

### Binary layout it parses — the canonical ME7 2-D map  **[C]**
```
+0          : word LEN_X        ; low byte = Nx          (0x41CC4/CC6 and #0FFh)
+2          : word X[0..Nx-1]   ; first-axis breakpoints
+2+2Nx      : word LEN_Y        ; low byte = Ny          (0x41D08)
+4+2Nx      : word Y[0..Ny-1]   ; second-axis breakpoints
+4+2Nx+2Ny  : word Z[Nx][Ny]    ; z-matrix, ROW-MAJOR in X: element(ix,iy)=Z[ix*Ny+iy]
```
The z stride between adjacent X rows is `Ny` words (0x41D4E `mulu r1,r14` with r14=2*Ny,
giving the X-row byte offset; 0x41D56 `add r12,r9` adds `2*iy`).

### Algorithm  **[C]**
1. **X-axis search** (0x41CC4-0x41D00): same bracket/clamp logic as `sub_41A68`, producing
   `r11 = xfrac_num = x - X[ix]`, `r5 = xinterval = X[ix+1]-X[ix]` (saved to r10),
   `r1 = ix`.
2. **Y-axis search** (0x41D02-0x41D46): on the Y block, producing `r4(→r15) = yfrac_num =
   y - Y[iy]`, `r5 = yinterval`, `r9 = iy`.
3. **Z base** (0x41D48-0x41D58): `r12 = &Z + 2*(ix*Ny) + 2*iy` = `&Z[ix][iy]`.
4. **Interp along Y at row ix** (0x41D5A-0x41D84): standard
   `z0 = Z[ix][iy] + (Z[ix][iy+1]-Z[ix][iy])*yfrac/yinterval` (rising/falling branch).
   → result in `r4`.
5. **If `xfrac_num != 0`** (0x41D84): interp along Y at **row ix+1** the same way into `r3`
   (re-reads the next X row at `r12-2+2Ny`, 0x41D88), then **interp between rows in X**:
   `result = z0 + (z1 - z0) * xfrac/xinterval` (0x41DB8-0x41DD6).
   This is full **bilinear** interpolation. Clamps on both axes; truncating division.

Result in **r4**. `0x41DDA rets`. **[C]**

---

## 4. Axis-search + z-interp split routines (`sub_42464` family)  **[C]**

Some callers compute the axis fraction once and reuse it. These split the work:

- **`sub_416B0`** (0x416B0) — byte-axis breakpoint search. Inputs `r12=axis ptr, r13=page,
  r14=axislen, r15=input(byte)`. Returns `rl4 = 8-bit fraction` and `rh4 = index`
  (`(r2-base)` in 0x416EC). Frac = `((input-X[i])<<8)/(X[i+1]-X[i])` via `divu` (0x416E4).
  Clamp-low `cc_ULE`, clamp-high `cc_NC`. **[C]**  (`sub_416F0` = signed variant.)
- **`sub_41778`** (0x41778) — word-axis equivalent (pair of `sub_420A8`; not dumped here but
  symmetric, called only via `sub_42486`).
- **`sub_420A8`** (0x420A8) — given a z-row pointer `r12`, page `r13`, and a packed
  `r14 = (index<<8)|frac`, returns `r4 = Z[idx] + (Z[idx+1]-Z[idx])*frac/256` using `mulu`
  and taking **MDH** (the high word = ÷65536-ish, here ÷256 because frac is 8-bit in the hi
  byte). Rising/falling branch. **[C]**
- **`sub_42464`** (0x42464) — 1-D word table wrapper: shuffles args, calls `sub_416B0`
  (byte axis search → frac), pulls the saved z pointer from `[r0]/[r0+2]` (pushed by
  caller), calls `sub_420A8`. So `sub_42464` = "byte-axis-indexed word table".
  Used by `sub_894C0` (LAMFA path) @ 0x89538. **[C]**
- **`sub_42486`** (0x42486) — same but word-axis (`sub_41778`). Used by `sub_86318` (KFLBTS)
  @ 0x86D34, 0x86FCE, 0x87510. **[C]**

`sub_421F4` (0x421F4) is a self-contained **2-D** variant where the caller pre-pushes the
two axis-fraction words on the stack (`[r0+0]`, `[r0+2]`) and passes a byte input pointer in
r14; it does two nested hi-byte interpolations (X inner, Y outer) reading the z-matrix
directly. Used by `sub_4E5EC` (0x4E664 etc.). **[C]**

---

## 5. Boost-controller helpers — integrators / limiters (NOT lookups)

### `sub_43904` — saturating signed integrator / accumulator step  **[C]**
```
sub_43904(r12=gain, r13=target/cur, r14=state_lo, r15=state_hi) -> r4:r5 (new 32-bit state)
```
0x43904 `r5 = r13 - r14`  (error = target − current low word).
- `0x43908 cc_UGT` (error positive, unsigned-ish): `MDL:MDH = gain * error`;
  new_state = state + product (`add r4,MDL; addc r5,MDH` @ 0x4392E). **Integrate up.**
- `0x4390A cc_NZ` false (error == 0): state unchanged, returns `r4=0,r5=current`.
- else (error negative): `neg error`; `product = gain*|error|`;
  new_state = state − product (`sub/subc` @ 0x4391A). **Integrate down.**

So it is a **first-order integrator/PT1 step**: `state += gain * (target − state)` carried
as a 32-bit fixed-point accumulator (`r4`=lo frac, `r5`=hi=usable value). This is exactly
the boost-loop integrator and the KFLBTS slew accumulators in `sub_86318` (called there with
the per-bank error and `byte_19A94` gain, e.g. 0x8686C). **[C]**

### `sub_42F16` — integrator step with **state clamp to [min,max]**  **[C]**
`(r12=gain, r13=delta, r14:r15=state)`, min/max pulled from stack `[r0],[r0+2]`. Same
`state += gain*delta` (signed via `jb r13.15` branch, 0x42F1A) then clamps the 32-bit result
into the caller-pushed `[min,max]` window (0x42F4E-0x42F68). Used as the boost / charge-temp
slew limiter in `sub_86318` (0x86CC6, 0x86D58…). **[C]**

### `sub_42DF4` — integrator step with **saturation to ±0x7FFF/0x8000**  **[C]**
Same integrate, but on overflow (`cc_NV` false) saturates the 32-bit accumulator to
`0x7FFF:FFFF` / `0x8000:0000` (0x42E0C / 0x42E2C). Signed-saturating accumulator. **[C]**

### `sub_42CF4` — fraction blend / linear ramp  **[C]**
`(r12=frac, r13=hi, r14=lo)`: `r13<<=8`; returns `lo + (hi-lo)*frac` (or `lo - ...`),
clamping the unsigned result to `0xFFFF` on carry. A simple 1-D blend between two scalars by
an 8-bit fraction (0x42D02 `mulu r12,r13` → MDH). Not a table lookup. **[C]**

---

## 6. Boost LDR routines (context for the helpers)

### `sub_DBB04` (0xDBB04) — LDR feed-forward + PI arithmetic  **[C]**
Reads gain const `word_2BE38` (page 0xA, KFLDR region) × measured `word_F410`
(0xDBB18 `mulu`), rescales (shift/`or` to a 32-bit fixed value, 0xDBB28-32), clamps to
0xFFFF. Looks up KFLDR map via `sub_41A68` @ 0xDBB60 (ptr #3E92, page 0xA), sums to
`word_302E62`. Computes a **ratio** via `divlu` (0xDBB98: `word_302496<<11 / word_30294A`).
Calls the integrator `sub_43904` @ 0xDBBBA (gain `word_2BF32`, state `word_302E68/6A`) — the
**I-term**. A second `sub_41A68` (#3E3A, 0xDBBD6) feeds a `mul` term (P-term, 0xDBBF6).
Saturates to ±0x7FFF, runs `sub_41B5A` (signed table #3E74 @ 0xDBC64) and `sub_41CC0` (2-D
map #3ECA @ 0xDBD22), and a second integrator `sub_43904` @ 0xDBD7A. Final WGDC-ish output
clamped to `[0xC000,0x3FFF]<<1` then summed. Classic **feed-forward + PI** boost loop.
Map pointers (all page 0xA): #3E92, #3E3A, #3E74, #3E56, #3ECA, #3EAC, #3ECA = the KFLDR*
family. **[C for structure; map identities per `lookup_callers.txt`]**

### `sub_DBF44` (0xDBF44) — LDR enable / limit state machine  **[C]**
Bit-flag machine over `byte_301867/301869/30186F`. Compares `word_302E34` against the
**KFLDIMX threshold `word_2BF4A`** (0xDBF64, 0xDBF84) with a debounce counter `byte_30186B`
(decremented 0xDBFA8) — sets/clears enable bit. Feed-forward add of `word_2BF4C` to setpoint
with under/overflow clamps (0xDC00A-0xDC02A, 0xDC114-0xDC134). Final actuator scaling reads
`byte_2BF34` via `sub_42464` @ 0xDC194 and limits with KFWNW thresholds `word_2BF4E/2BF50`
(0xDC246/0xDC262). This is **why raising KFLDIMX extends controller authority** — the gate is
the `cmp word_2BF4A` here. **[C]**

---

## 7. ME7 map binary layout — summary (implied by the code)

All multi-byte values little-endian. Axis arrays are monotonic ascending. "len" fields use
only the **low byte** → max 255 points per axis.

**1-D word table** (`sub_41A68[`/`](/)sub_41B5A`):
```
[ len:word ][ X[0..N-1]:word ][ Z[0..N-1]:word ]      N = len & 0xFF
```
**1-D byte table** (`sub_419F4`):
```
[ len:byte ][ X[0..N-1]:byte ][ Z[0..N-1]:byte ]
```
**2-D word map** (`sub_41CC0`):
```
[ lenX:word ][ X[0..Nx-1]:word ]
[ lenY:word ][ Y[0..Ny-1]:word ]
[ Z[0..Nx-1][0..Ny-1]:word ]      row-major in X, stride = Ny words
                                   element(ix,iy) = Z[ix*Ny + iy]
```
Interpolation everywhere is **linear / bilinear with truncating (floor) division** and
**clamping at axis ends** (no extrapolation, no rounding). Z width matches the routine.

### Notes on the specific maps in the task
- **KFZW (z @ 0x133B1, odd address)** → byte z-data → read via the **byte** lookups
  (`sub_419F4` for 1-D, or the byte-fraction 2-D `sub_421F4[`/`](/)sub_42082`), not `sub_41A68`.
  Axes at 0x14FEE / 0x1502C are separate axis blocks. **[I — by data width/parity; confirm
  by enumerating callers that load #133B1/page-from-offset]**
- **KFLBTS (z @ 0x19B5A)** → byte-resolution component-protection map, consumed inside
  `sub_86318`, whose output mapping uses `sub_419F4` (byte) and slew via `sub_43904`/
  `sub_42F16`. **[C that 86318 is the consumer; map-pointer identity per findings/A2L]**

---

## 8. Open follow-ups
- Enumerate callers of `sub_419F4` / `sub_421F4` / `sub_42082` the same way
  `ida_lookup_callers.py` did for `sub_41A68`, to get the **byte-map → function** master
  table (the KFZW/KFLBTS linkage). The script just needs the target EA changed.
- Dump `sub_41778` to confirm the word-axis search (symmetric to `sub_416B0`).
- Confirm KFZW pointer/page by reading the ignition-path callers (`sub_8DE10` cluster shows
  many `sub_41A68` calls in `lookup_callers.txt`, but KFZW is byte → look in its byte-lookup
  callers instead).
