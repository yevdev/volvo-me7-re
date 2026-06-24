// @category C166
// Decompile the key control functions to pseudo-C (Ghidra C166 module).
// args: <outfile> <hexaddr>...
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.Function;
import java.nio.file.*;

public class DecompKeyFns extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] a = getScriptArgs();
        String out = a[0];
        DecompInterface di = new DecompInterface();
        di.toggleCCode(true);
        di.openProgram(currentProgram);
        StringBuilder sb = new StringBuilder();
        sb.append("// Pseudo-C of key Volvo ME7.0 (50GPHJ) control functions\n");
        sb.append("// Ghidra + keyhana C166 module. C166 has no Hex-Rays decompiler;\n");
        sb.append("// this is Ghidra's SLEIGH-based pseudo-C, best read alongside the IDA disassembly dumps.\n\n");
        for (int i = 1; i < a.length; i++) {
            long ea = Long.parseLong(a[i], 16);
            Function f = getFunctionContaining(toAddr(ea));
            if (f == null) {
                try { disassemble(toAddr(ea)); f = createFunction(toAddr(ea), null); } catch (Exception ex) {}
            }
            if (f == null) { sb.append("// --- no function at 0x" + a[i] + " ---\n\n"); continue; }
            DecompileResults r = di.decompileFunction(f, 90, monitor);
            sb.append("// ================= " + f.getName() + " @ " + f.getEntryPoint() + " =================\n");
            if (r != null && r.decompileCompleted() && r.getDecompiledFunction() != null)
                sb.append(r.getDecompiledFunction().getC()).append("\n");
            else
                sb.append("// (decompile failed)\n\n");
        }
        Files.write(Paths.get(out), sb.toString().getBytes());
        println("DECOMP_KEYFNS_DONE " + out);
    }
}
