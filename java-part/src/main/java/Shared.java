import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

import lombok.extern.slf4j.Slf4j;
import org.graalvm.nativeimage.IsolateThread;
import org.graalvm.nativeimage.c.function.CEntryPoint;
import org.graalvm.nativeimage.c.type.CCharPointer;
import org.graalvm.nativeimage.c.type.CTypeConversion;
@Slf4j
public class Shared {

    static Map<String, Function<String,String>> methods;

    @CEntryPoint(name = "JGateway__init", documentation = "Initializes the gateway")
    static void init(IsolateThread thread) {
        log.info("Initializing method map enc={}",System.getProperty("file.encoding"));
        methods = new HashMap<>();
        methods.put("Greeter", s -> "Answer äöü from within java: " + s);
    }


    @CEntryPoint(name = "JGateway__invoke", documentation = "calls a registered method with a string parameter")
    static CCharPointer invoke(IsolateThread thread, CCharPointer methodNamePtr, CCharPointer messagePtr) {
        final String methodName = CTypeConversion.toJavaString(methodNamePtr);
        final String message = CTypeConversion.toJavaString(messagePtr);
        if (methods.containsKey(methodName)) {
            return CTypeConversion.toCString(methods.get(methodName).apply(message)).get();
        } else {
            log.warn("was invoked with " + methodName + ", but this method is not known");
        }
        return CTypeConversion.toCString("").get();
    }
}
