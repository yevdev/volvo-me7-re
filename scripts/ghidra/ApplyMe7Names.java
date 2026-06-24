// @category C166
// Apply the loadkit name DB (function_names.csv, ram_names.csv) to the current Ghidra program,
// so the Ghidra database carries the same companion coverage as the IDA loadkit.
// arg: <loadkit_dir>  (folder holding the two CSVs; addr,name,comment with quoted comments)
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;
import java.nio.file.*;
import java.util.*;

public class ApplyMe7Names extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] a = getScriptArgs();
        String dir = a.length > 0 ? a[0] : ".";
        int fn = applyFunctions(Paths.get(dir, "function_names.csv"));
        int rm = applyRam(Paths.get(dir, "ram_names.csv"));
        println("APPLY_ME7_NAMES_DONE functions=" + fn + " ram=" + rm);
    }

    int applyFunctions(Path p) throws Exception {
        if (!Files.exists(p)) { println("MISSING " + p); return 0; }
        int n = 0; List<String> lines = Files.readAllLines(p);
        for (int i = 1; i < lines.size(); i++) {
            String[] c = splitCsv(lines.get(i));
            if (c.length < 2 || c[0].trim().isEmpty()) continue;
            try {
                Address ad = toAddr(Long.parseLong(c[0].replace("0x", "").trim(), 16));
                Function f = getFunctionContaining(ad);
                if (f == null) { try { disassemble(ad); f = createFunction(ad, null); } catch (Exception e) {} }
                if (f == null) continue;
                f.setName(c[1].trim(), SourceType.USER_DEFINED);
                if (c.length > 2 && !c[2].trim().isEmpty()) setPlateComment(f.getEntryPoint(), c[2].trim());
                n++;
            } catch (Exception e) { /* name clash / bad addr -> skip */ }
        }
        return n;
    }

    int applyRam(Path p) throws Exception {
        if (!Files.exists(p)) { println("MISSING " + p); return 0; }
        int n = 0; List<String> lines = Files.readAllLines(p);
        for (int i = 1; i < lines.size(); i++) {
            String[] c = splitCsv(lines.get(i));
            if (c.length < 2 || c[0].trim().isEmpty()) continue;
            try {
                Address ad = toAddr(Long.parseLong(c[0].replace("0x", "").trim(), 16));
                createLabel(ad, c[1].trim(), true);                 // primary user label
                if (c.length > 2 && !c[2].trim().isEmpty()) setEOLComment(ad, c[2].trim());
                n++;
            } catch (Exception e) { /* addr not in memory map -> skip */ }
        }
        return n;
    }

    // CSV split honoring double-quoted fields (comments may contain commas)
    String[] splitCsv(String line) {
        List<String> out = new ArrayList<>(); StringBuilder sb = new StringBuilder(); boolean q = false;
        for (int i = 0; i < line.length(); i++) {
            char ch = line.charAt(i);
            if (ch == '"') q = !q;
            else if (ch == ',' && !q) { out.add(sb.toString()); sb.setLength(0); }
            else sb.append(ch);
        }
        out.add(sb.toString());
        return out.toArray(new String[0]);
    }
}
