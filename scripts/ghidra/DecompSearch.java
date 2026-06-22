// @category C166
// Decompile every function and find which ones' C output references our calibration
// table addresses (the module resolves DPP/EXTP in the decompiler, so refs show as
// DAT_<addr> / 0x<addr> in the C text, not as listing xrefs).
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.Function;
import java.util.*;

public class DecompSearch extends GhidraScript {
    @Override
    public void run() throws Exception {
        long[] eas = {0x27EE2L,0x2C000L,0x2C152L,0x133B1L,0x158A4L,0x156CCL,0x2383EL,0x19B5AL,0x1BC87L,0x1E776L};
        String[] nm = {"KFLDRX","KFLDIMX","KFLDRL","KFZW1","KFMIRL","KFMIOP","LAMFA","KFLBTS","KFLDHBN","KFPED"};
        String[] needle = new String[eas.length];
        for (int i=0;i<eas.length;i++) needle[i] = String.format("%08x", eas[i]); // e.g. 00027ee2
        Map<String,List<String>> hits = new LinkedHashMap<>();
        for (String s : nm) hits.put(s, new ArrayList<String>());

        DecompInterface di = new DecompInterface();
        di.openProgram(currentProgram);
        int done=0, withcode=0;
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            done++;
            if (done % 500 == 0) println("PROGRESS decompiled " + done);
            DecompileResults r = di.decompileFunction(f, 20, monitor);
            if (r == null || !r.decompileCompleted()) continue;
            DecompiledFunction df = r.getDecompiledFunction();
            if (df == null) continue;
            String c = df.getC().toLowerCase();
            withcode++;
            for (int i=0;i<needle.length;i++) {
                if (c.contains(needle[i])) hits.get(nm[i]).add(f.getName()+"@"+f.getEntryPoint());
            }
        }
        println("DONE decompiled=" + done + " ok=" + withcode);
        for (int i=0;i<nm.length;i++) {
            List<String> h = hits.get(nm[i]);
            println("HIT " + nm[i] + " : " + h.size() + " functions" + (h.isEmpty()?"":" -> " + h.subList(0, Math.min(8,h.size()))));
        }
    }
}
