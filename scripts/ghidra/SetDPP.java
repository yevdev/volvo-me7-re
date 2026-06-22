// @category C166
// Pre-analysis: seed the known ME7 startup DPP page values so the C166 analyzer
// resolves DPP-relative data references (DPP0=4,DPP1=5,DPP2=0xC0,DPP3=3 from prior IDA work).
import ghidra.app.script.GhidraScript;
import ghidra.program.model.lang.Register;
import ghidra.program.model.lang.RegisterValue;
import ghidra.program.model.address.Address;
import java.math.BigInteger;

public class SetDPP extends GhidraScript {
    @Override
    public void run() throws Exception {
        long[][] dpps = {{0,4},{1,5},{2,0xC0},{3,3}};
        Address min = currentProgram.getMinAddress();
        Address max = currentProgram.getMaxAddress();
        for (long[] d : dpps) {
            String nm = "DPP" + d[0];
            Register r = currentProgram.getRegister(nm);
            if (r == null) { println("MISSING REG " + nm); continue; }
            currentProgram.getProgramContext().setRegisterValue(min, max,
                new RegisterValue(r, BigInteger.valueOf(d[1])));
            println("SET " + nm + "=0x" + Long.toHexString(d[1]));
        }
    }
}
