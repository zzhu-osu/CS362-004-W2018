import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class UrlValidatorTest extends TestCase {

    public static final boolean TEST_MANUAL = true;
    public static final boolean TEST_INPUT_PARTITIONS = true;
    public static final boolean TEST_ISVALID = true;

    public static final boolean DEBUG_HELPER = false;


    public UrlValidatorTest(String testName) {
        super(testName);
    }

    public static void main(String[] args) {

        // For debugging in the 'src' files
        if (DEBUG_HELPER) {
            debuggingHelper("url", UrlValidator.ALLOW_LOCAL_URLS, "http://WWW.amazon.com");
        }
        
        // For manual tests
        if (TEST_MANUAL) {
            long startTime = System.nanoTime();

            try {
                PrintWriter printResult = new PrintWriter(
                    new BufferedWriter(new FileWriter("testResult/manualTests.out")));
                
                manualTests.testManualTest_2_SLASHES(printResult);
                manualTests.testManualTest_ALL_SCHEMES(printResult);
                manualTests.testManualTest_NO_FRAGMENTS(printResult);
                manualTests.testManualTest_LOCAL_URLS(printResult);
                printResult.close();
                System.out.println("Manual Tests result available at testResult/manualTests.out");
            } catch (IOException e) {
                System.err.println("Manual Tests result file writing error: " + e);
            }
            long estimatedTime = System.nanoTime() - startTime;
            System.out.printf("Elapsed time for Manual Tests: %.2f sec\n\n", estimatedTime / Math.pow(10, 9));

        }

        // For input partition tests
        if (TEST_INPUT_PARTITIONS) {
            inputPartitionAndUnitTests inputPartitionTests = new inputPartitionAndUnitTests();
            long startTime = System.nanoTime();
            try {
                PrintWriter printResult = new PrintWriter(
                    new BufferedWriter(new FileWriter("testResult/inputPartitionTests.out")));
                inputPartitionTests.testScheme(printResult);
                inputPartitionTests.testAuthority(printResult);
                inputPartitionTests.testPath(printResult);
                inputPartitionTests.testQuery(printResult);
                printResult.close();
                System.out.println("Input Partition Tests result available at testResult/inputPartitionTests.out");
            } catch (IOException e) {
                System.err.println("Input Partition Tests result file writing error: " + e);
            }
            long estimatedTime = System.nanoTime() - startTime;
            System.out.printf("Elapsed time for Input Partition Tests: %.2f sec\n\n", estimatedTime / Math.pow(10, 9));

        }

        // For programming-based unit test
        if (TEST_ISVALID) {
            inputPartitionAndUnitTests unitTests = new inputPartitionAndUnitTests();
            long startTime = System.nanoTime();
            try {
                PrintWriter printResult = new PrintWriter(
                    new BufferedWriter(new FileWriter("testResult/testIsValid.out")));
                unitTests.testIsValid(printResult);
                printResult.close();
                System.out.println("Unit Test - testIsValid() result available at testResult/testIsValid.out");
            } catch (IOException e) {
                System.err.println("Unit Test - testIsValid() result file writing error: " + e);
            }
            long estimatedTime = System.nanoTime() - startTime;
            System.out.printf("Elapsed time for Unit Test - testIsValid(): %.2f sec\n", estimatedTime / Math.pow(10, 9));
        }

    }

    // debuggingHelper(): Tests a single string
    // component: one of "url", "scheme", "authority", "path", and "query"
    // options: use the constants defined in the UrlValidator class, e.g. UrlValidator.ALLOW_2_SLASHES or 0 for default
    // testString: the URL or URL component that needs to be tested
    public static void debuggingHelper(String component, long options, String testString) {

        UrlValidator urlVal = new UrlValidator(options);
        UrlValidatorCor urlValCor = new UrlValidatorCor(options);

        // COMPLETE URL
        if (component.toLowerCase().equals("url")) {
            System.out.println(urlVal.isValid(testString));
            System.out.println(urlValCor.isValid(testString));
        }

        // SCHEME
        else if (component.toLowerCase().equals("scheme")) {
            System.out.println(urlVal.isValidScheme(testString));
            System.out.println(urlValCor.isValidScheme(testString));
        }

        // AUTHORITY
        else if (component.toLowerCase().equals("authority")) {
            System.out.println(urlVal.isValidAuthority(testString));
            System.out.println(urlValCor.isValidAuthority(testString));
        }

        // PATH
        else if (component.toLowerCase().equals("path")) {
            System.out.println(urlVal.isValidPath(testString));
            System.out.println(urlValCor.isValidPath(testString));
        }

        // QUERY
        else if (component.toLowerCase().equals("query")) {
            System.out.println(urlVal.isValidQuery(testString));
            System.out.println(urlValCor.isValidQuery(testString));
        }
                
    }

}