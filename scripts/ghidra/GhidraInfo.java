// @category C166
import ghidra.app.script.GhidraScript;
import ghidra.program.model.mem.MemoryBlock;

public class GhidraInfo extends GhidraScript {
    @Override
    public void run() throws Exception {
        println("=== GHIDRA C166 IMPORT INFO ===");
        println("PROGRAM: " + currentProgram.getName());
        println("LANG_ID: " + currentProgram.getLanguageID());
        println("PROCESSOR: " + currentProgram.getLanguage().getProcessor());
        println("IMAGE_BASE: " + currentProgram.getImageBase());
        for (MemoryBlock b : currentProgram.getMemory().getBlocks()) {
            println("BLOCK " + b.getName() + " " + b.getStart() + "-" + b.getEnd() + " init=" + b.isInitialized());
        }
        println("FUNCTION_COUNT: " + currentProgram.getFunctionManager().getFunctionCount());
        println("=== END INFO ===");
    }
}
