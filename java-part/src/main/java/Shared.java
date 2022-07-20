
import java.util.HashMap;
import java.util.Map;
import java.util.function.Consumer;

import lombok.extern.slf4j.Slf4j;
import org.graalvm.nativeimage.IsolateThread;
import org.graalvm.nativeimage.c.function.CEntryPoint;
import org.graalvm.nativeimage.c.type.CCharPointer;
import org.graalvm.nativeimage.c.type.CTypeConversion;

@Slf4j
public class Shared {

    static Map<String, Consumer<String>> methods;

    @CEntryPoint
    static void init(IsolateThread thread) {
        log.info("Initializing method map");
        methods = new HashMap<>();
        methods.put("Greeter", s -> log.info("Answer from within java: " + s));
    }

    @CEntryPoint
    static void invoke(IsolateThread thread, CCharPointer methodNamePtr, CCharPointer messagePtr) {
        final String methodName = CTypeConversion.toJavaString(methodNamePtr);
        final String message = CTypeConversion.toJavaString(messagePtr);
        if (methods.containsKey(methodName)) {
            methods.get(methodName).accept(message);
        } else {
            log.warn("was invoked with "+methodName+", but this method is not known");
        }
    }
}
