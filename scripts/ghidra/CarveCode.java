// @category C166
// Aggressive code carving for raw ME7 C166: seed the trap/interrupt vector table at 0x0
// (each entry is a 4-byte JMPS to a handler), then force-disassemble the code segments,
// skipping the dense calibration/map band, and create functions at flow starts.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Function;

public class CarveCode extends GhidraScript {
    // calibration/map data band to skip (maps cluster ~0x13000-0x2D000)
    static final long CAL_LO = 0x10000L, CAL_HI = 0x2D000L;
    static final long ROM_END = 0x100000L;

    @Override
    public void run() throws Exception {
        // 1) vector table 0x0..0x1FF: disassemble each 4-byte slot (JMPS handlers)
        for (long v = 0; v < 0x200; v += 4) {
            Address a = toAddr(v);
            if (getInstructionAt(a) == null) disassemble(a);
        }
        // 2) walk code segments, force disassembly + function creation
        int made = 0, ins = 0;
        long addr = 0;
        while (addr < ROM_END) {
            if (addr >= CAL_LO && addr < CAL_HI) { addr = CAL_HI; continue; }
            Address a = toAddr(addr);
            Instruction in = getInstructionAt(a);
            if (in == null && getDataAt(a) == null) {
                disassemble(a);
                in = getInstructionAt(a);
            }
            if (in != null) {
                ins++;
                if (getFunctionContaining(a) == null) {
                    Function f = createFunction(a, null);
                    if (f != null) made++;
                }
                addr = in.getMaxAddress().getOffset() + 1;
            } else {
                addr += 2; // C166 min instruction size
            }
            if ((addr & 0xFFFF) == 0) monitor.checkCancelled();
        }
        println("CARVE: disassembled~" + ins + " starts, created " + made + " functions");
        println("CARVE: total functions now " + currentProgram.getFunctionManager().getFunctionCount());
    }
}
