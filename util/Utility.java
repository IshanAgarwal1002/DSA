package util;
import java.util.Arrays;
import java.util.function.Supplier;

public class Utility {
  // Helper method to format value for printing
  public static <T> String formatValue(T value) {
    if (value == null) return "null";
    if (!value.getClass().isArray()) return String.valueOf(value);
    
    if (value instanceof int[]) return Arrays.toString((int[]) value);
    if (value instanceof long[]) return Arrays.toString((long[]) value);
    if (value instanceof double[]) return Arrays.toString((double[]) value);
    if (value instanceof float[]) return Arrays.toString((float[]) value);
    if (value instanceof boolean[]) return Arrays.toString((boolean[]) value);
    if (value instanceof byte[]) return Arrays.toString((byte[]) value);
    if (value instanceof char[]) return Arrays.toString((char[]) value);
    if (value instanceof short[]) return Arrays.toString((short[]) value);
    
    return Arrays.deepToString((Object[]) value);
  }

  // Generic print utility method
  public static <T> void print(String label, T value) {
    System.out.println(label + ": " + formatValue(value));
  }

  // Helper method to measure execution time
  public static <T> void measureTime(String label, Supplier<T> function) {
    long startTime = System.nanoTime();
    T result = function.get();
    long endTime = System.nanoTime();
    long durationMs = (endTime - startTime) / 1_000_000;
    long durationMicros = ((endTime - startTime) / 1_000) % 1_000;
    print(label, result);
    System.out.println("Time: " + durationMs + "ms " + durationMicros + "µs");
  }
}
