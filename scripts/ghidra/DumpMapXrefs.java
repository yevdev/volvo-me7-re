// @category C166
// Post-analysis: report function count + which code references our key calibration tables.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.listing.Function;

public class DumpMapXrefs extends GhidraScript {
    @Override
    public void run() throws Exception {
        println("RESULT FUNCTION_COUNT: " + currentProgram.getFunctionManager().getFunctionCount());
        long[] eas = {0x27EE2L,0x2C000L,0x2C152L,0x133B1L,0x158A4L,0x156CCL,0x2383EL,0x19B5AL,0x1BC87L,0x1E776L};
        String[] nm = {"KFLDRX","KFLDIMX","KFLDRL","KFZW1","KFMIRL","KFMIOP","LAMFA","KFLBTS","KFLDHBN","KFPED"};
        for (int i = 0; i < eas.length; i++) {
            Address a = toAddr(eas[i]);
            Reference[] refs = getReferencesTo(a);
            println("RESULT MAP " + nm[i] + " @0x" + Long.toHexString(eas[i]) + " : " + refs.length + " refs");
            int c = 0;
            for (Reference r : refs) {
                if (c++ >= 5) break;
                Function f = getFunctionContaining(r.getFromAddress());
                println("RESULT    <- " + r.getFromAddress() + (f != null ? (" in " + f.getName()) : " (no func)"));
            }
        }
    }
}
