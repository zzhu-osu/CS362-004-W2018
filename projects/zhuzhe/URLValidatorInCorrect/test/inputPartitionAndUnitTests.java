import java.util.ArrayList;
import java.net.URLEncoder;
import java.io.UnsupportedEncodingException;
import java.io.IOException;
import java.io.PrintWriter;

public class inputPartitionAndUnitTests {

    private ArrayList<String> scheme;
    private ArrayList<String> hostWithoutTLD;
    private ArrayList<String> tld;
    private ArrayList<String> port;
    private ArrayList<String> path;
    private ArrayList<String> query;
    //private ArrayList<String> fragment;

    public final String specialchar = " `~!@#$%^&*()-_=+[]{}\\|;:'\",.<>?";
    public final String specialchar_sample = " `~!@#$%^&*(-_=+]{\\|;:'\",.<?";
    public final String upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    public final String upper_sample = "AINUZ";
    public final String lower = upper.toLowerCase();
    public final String lower_sample = upper_sample.toLowerCase();
    public final String digits = "0123456789";
    public final String digits_sample = "0159";
    public final String alphanum = upper + lower + digits;
    public final String alphanum_sample = upper_sample + lower_sample + digits_sample;
    public final String alphanumchar = alphanum + specialchar;
    public final String alphanumchar_sample = alphanum_sample + specialchar_sample;

    

    public void testScheme(PrintWriter printResult) {
        generateScheme();
        //System.out.println("\nNumber of Schemes: " + scheme.size());
        UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
        UrlValidatorCor urlValCor = new UrlValidatorCor(UrlValidatorCor.ALLOW_ALL_SCHEMES);
        int err_counter = 0, test_counter = 0;

        printResult.println("\nTesting Scheme (ALLOW_ALL_SCHEMES)\nOnly incorrect outputs are recorded:");

        for (int i = 0; i < scheme.size(); i++) {
            test_counter++;
            String scheme_entry = scheme.get(i);
            boolean shouldBeValid = urlValCor.isValidScheme(scheme_entry);

            if (urlVal.isValidScheme(scheme_entry) != shouldBeValid) {
                printResult.print("Scheme should be ");
                if (shouldBeValid) {
                    printResult.println("valid: " + scheme_entry);
                } else {
                    printResult.println("invalid: " + scheme_entry);
                }
                err_counter++;
            }
        }

        printResult.println("Scheme (ALLOW_ALL_SCHEMES) Test Result: Errors: " + err_counter + "/" + test_counter);

        urlVal = new UrlValidator();
        urlValCor = new UrlValidatorCor();
        err_counter = 0;
        test_counter = 0;

        printResult.println("\nTesting Scheme (DEFAULT SCHEMES)\nOnly incorrect outputs are recorded:");

        for (int i = 0; i < scheme.size(); i++) {
            test_counter++;
            String scheme_entry = scheme.get(i);
            boolean shouldBeValid = urlValCor.isValidScheme(scheme_entry);

            if (urlVal.isValidScheme(scheme_entry) != shouldBeValid) {
                printResult.print("Scheme should be ");
                if (shouldBeValid) {
                    printResult.println("valid: " + scheme_entry);
                } else {
                    printResult.println("invalid: " + scheme_entry);
                }
                err_counter++;
            }
        }

        printResult.println("Scheme (DEFAULT SCHEMES) Test Result: Errors: " + err_counter + "/" + test_counter);

        scheme = new ArrayList<String>();
    }

    public void testAuthority(PrintWriter printResult) {
        generateHostWithoutTLD();
        generateTLD();
        //System.out.println("\nNumber of hostWithoutTLDs: " + hostWithoutTLD.size());
        //System.out.println("Number of TLDs: " + tld.size());
        long err_counter = 0, test_counter = 0;
        ArrayList<Throwable> testExceptions = new ArrayList<Throwable>();
        UrlValidator urlVal = new UrlValidator();
        UrlValidatorCor urlValCor = new UrlValidatorCor();

        printResult.println("\nTesting Authority\nOnly incorrect outputs are recorded:");

        for (int i = 0; i < hostWithoutTLD.size(); i++) {
            String hostWithoutTLD_entry = hostWithoutTLD.get(i);
            for (int j = 0; j < tld.size(); j++) {

                if (i <= 20 || (i > 20 && j < 30)) {
                    test_counter++;
                    String authority_entry = hostWithoutTLD_entry + tld.get(j);
                    //System.out.println("Testing Authority: " + authority_entry);
                    boolean shouldBeValid = urlValCor.isValidAuthority(authority_entry);

                    try {
                        if (urlVal.isValidAuthority(authority_entry) != shouldBeValid) {
                            printResult.print("Authority should be ");
                            if (shouldBeValid) {
                                printResult.println("valid: " + authority_entry);
                            } else {
                                printResult.println("invalid: " + authority_entry);
                            }
                            err_counter++;
                        }
                    } catch (IllegalArgumentException | ExceptionInInitializerError | NoClassDefFoundError e) {
                        //System.err.println("isValidAuthority(" + authority_entry + ") error: " + e);
                        boolean sameException = false;
                        for (Throwable ee : testExceptions) {

                            if (e.getClass().equals(ee.getClass()) && e.getMessage().equals(ee.getMessage())) {
                                sameException = true;
                                break; //exception matched
                            }
                        }
                        if (sameException == false) {
                            testExceptions.add(e);
                            printResult.println("isValidAuthority() runtime error: " + e);
                            printResult.println("Test string: '" + authority_entry + "'");
                            printResult.println("Future runtime errors of the same type as above will not be recorded.");
                        }
                        err_counter++;
                    }
                } else {
                    break;
                }

            }

        }
        printResult.println("Authority Test Result: Errors: " + err_counter + "/" + test_counter);

        hostWithoutTLD = new ArrayList<String>();
        tld = new ArrayList<String>();
    }

    public void testPath(PrintWriter printResult) {
        generatePath();
        //System.out.println("\nNumber of Paths: " + path.size());
        UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_2_SLASHES);
        UrlValidatorCor urlValCor = new UrlValidatorCor(UrlValidatorCor.ALLOW_2_SLASHES);
        long err_counter = 0, test_counter = 0;

        printResult.println("\nTesting Path (ALLOW_2_SLASHES)\nOnly incorrect outputs are recorded:");

        for (int i = 0; i < path.size(); i++) {
            test_counter++;
            String path_entry = path.get(i);
            boolean shouldBeValid = urlValCor.isValidPath(path_entry);

            if (urlVal.isValidPath(path_entry) != shouldBeValid) {

                printResult.print("Path should be ");
                if (shouldBeValid) {
                    printResult.println("valid: " + path_entry);
                } else {
                    printResult.println("invalid: " + path_entry);
                }

                err_counter++;
            }
        }

        printResult.println("Path (ALLOW_2_SLASHES) Test Result: Errors: " + err_counter + "/" + test_counter);

        urlVal = new UrlValidator();
        urlValCor = new UrlValidatorCor();
        err_counter = 0;
        test_counter = 0;

        printResult.println("\nTesting Path (DEFAULT)\nOnly incorrect outputs are recorded:");

        for (int i = 0; i < path.size(); i++) {
            test_counter++;
            String path_entry = path.get(i);
            boolean shouldBeValid = urlValCor.isValidPath(path_entry);

            if (urlVal.isValidPath(path_entry) != shouldBeValid) {
                printResult.print("Path should be ");
                if (shouldBeValid) {
                    printResult.println("valid: " + path_entry);
                } else {
                    printResult.println("invalid: " + path_entry);
                }
                err_counter++;
            }
        }

        printResult.println("Path (DEFAULT) Test Result: Errors: " + err_counter + "/" + test_counter);

        path = new ArrayList<String>();
    }

    public void testQuery(PrintWriter printResult) {
        generateQuery();
        //System.out.println("\nNumber of Queries: " + query.size());
        UrlValidator urlVal = new UrlValidator();
        UrlValidatorCor urlValCor = new UrlValidatorCor();
        int err_counter = 0, test_counter = 0;

        printResult.println("\nTesting Query\nOnly incorrect outputs are recorded:");

        for (int i = 0; i < query.size(); i++) {
            test_counter++;
            String query_entry = query.get(i);
            boolean shouldBeValid = urlValCor.isValidQuery(query_entry);

            if (urlVal.isValidQuery(query_entry) != shouldBeValid) {
                printResult.print("Query should be ");
                if (shouldBeValid) {
                    printResult.println("valid: " + query_entry);
                } else {
                    printResult.println("invalid: " + query_entry);
                }
                err_counter++;
            }
        }

        printResult.println("Query Test Result: Errors: " + err_counter + "/" + test_counter);

        query = new ArrayList<String>();
    }

    public void testIsValid(PrintWriter printResult) throws IOException {
        //You can use this function for programming based testing
        try {
            generateBasicScheme();
            generateHostWithoutTLD();
            generateBasicTLD();
            generateBasicPort();
            generateBasicPath();
            generateBasicQuery();

            /*
            System.out.println("Number of Schemes: " + scheme.size());
            System.out.println("Number of HostWithoutTLD: " + hostWithoutTLD.size());
            System.out.println("Number of TLDs: " + tld.size());
            System.out.println("Number of Ports: " + port.size());
            System.out.println("Number of Paths: " + path.size());
            System.out.println("Number of Queries: " + query.size());
            */

        } catch (OutOfMemoryError e) {
            System.err.println("testIsValid() error: " + e);
            return;
        }

        UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
        UrlValidatorCor urlValCor = new UrlValidatorCor(UrlValidatorCor.ALLOW_ALL_SCHEMES);

        ArrayList<Throwable> testExceptions = new ArrayList<Throwable>();
        long err_counter = 0, test_counter = 0;

        printResult.println("\nTesting isValid (ALLOW_ALL_SCHEMES)\nOnly incorrect outputs are recorded:\n");

        for (int i = 0; i < scheme.size(); i++) {
            for (int j = 0; j < hostWithoutTLD.size(); j++) {
                for (int k = i % 2; k < tld.size(); k += 2) {
                    for (int m = j % 2; m < port.size(); m += 2) {
                        for (int n = i % 2; n < path.size(); n += 2) {
                            for (int p = j % 2; p < query.size(); p += 2) {
                                String testURLStr = scheme.get(i) + hostWithoutTLD.get(j) + tld.get(k) + port.get(m)
                                        + path.get(n) + query.get(p);

                                test_counter++;
                                boolean shouldBeValid = urlValCor.isValid(testURLStr);
                                try {
                                    if (urlVal.isValid(testURLStr) != shouldBeValid) {

                                        printResult.print("URL should be ");
                                        if (shouldBeValid) {
                                            printResult.println("valid: " + testURLStr);
                                        } else {
                                            printResult.println("invalid: " + testURLStr);
                                        }

                                        err_counter++;
                                    }
                                } catch (IllegalArgumentException | ExceptionInInitializerError
                                        | NoClassDefFoundError e) {
                                    //System.err.println("isValidAuthority(" + authority_entry + ") error: " + e);
                                    boolean sameException = false;
                                    for (Throwable ee : testExceptions) {

                                        if (e.getClass().equals(ee.getClass())
                                                && e.getMessage().equals(ee.getMessage())) {
                                            sameException = true;
                                            break; //exception matched
                                        }
                                    }
                                    if (sameException == false) {
                                        testExceptions.add(e);
                                        printResult.println("isValid() runtime error: " + e);
                                        printResult.println("Test string: '" + testURLStr + "'");
                                        printResult.println("Future runtime errors of the same type as above will not be recorded.");
                                    }
                                    err_counter++;
                                }

                            }

                        }

                    }

                }

                if (j > 15) {
                    j += i + 999;
                }
            }
        }

        printResult.println("\nisValid (ALLOW_ALL_SCHEMES) Test Result: Errors: " + err_counter + "/" + test_counter);

        scheme = new ArrayList<String>();
        hostWithoutTLD = new ArrayList<String>();
        tld = new ArrayList<String>();
        port = new ArrayList<String>();
        path = new ArrayList<String>();
        query = new ArrayList<String>();

    }

    public void generateComponentList(ArrayList<String> someComponentList, int max_sections) {

        // pre-condition: someComponentList initialized and filled with some (10-30) elements
        // max_sections: 1, 2, or 3

        int num_prefilled_someComponentLists = someComponentList.size();
        for (int i = 1; i < num_prefilled_someComponentLists; i++) {
            String someComponentList_entry = someComponentList.get(i);
            try {
                if (someComponentList_entry.length() >= 2) {
                    for (int j = 0; j < alphanum_sample.length(); j++) {
                        String new_someComponentList_entry = alphanum_sample.charAt(j)
                                + someComponentList_entry.substring(1);
                        someComponentList.add(new_someComponentList_entry);

                        new_someComponentList_entry = someComponentList_entry.substring(0,
                                someComponentList_entry.length() - 1) + alphanum_sample.charAt(j);
                        someComponentList.add(new_someComponentList_entry);

                        if (someComponentList_entry.length() >= 3) {
                            new_someComponentList_entry = String.valueOf(someComponentList_entry.charAt(0))
                                    + alphanum_sample.charAt(j) + someComponentList_entry.substring(2);
                            someComponentList.add(new_someComponentList_entry);
                        }
                    }

                    for (int k = 0; k < specialchar_sample.length(); k++) {
                        String new_someComponentList_entry = specialchar_sample.charAt(k)
                                + someComponentList_entry.substring(1);
                        someComponentList.add(new_someComponentList_entry);

                        new_someComponentList_entry = URLEncoder.encode(new_someComponentList_entry, "UTF-8");
                        someComponentList.add(new_someComponentList_entry);

                        new_someComponentList_entry = someComponentList_entry.substring(0,
                                someComponentList_entry.length() - 1) + specialchar_sample.charAt(k);
                        someComponentList.add(new_someComponentList_entry);

                        new_someComponentList_entry = URLEncoder.encode(new_someComponentList_entry, "UTF-8");
                        someComponentList.add(new_someComponentList_entry);

                        if (someComponentList_entry.length() >= 3) {
                            new_someComponentList_entry = someComponentList_entry.charAt(0)
                                    + specialchar_sample.charAt(k) + someComponentList_entry.substring(2);
                            someComponentList.add(new_someComponentList_entry);

                            new_someComponentList_entry = URLEncoder.encode(new_someComponentList_entry, "UTF-8");
                            someComponentList.add(new_someComponentList_entry);
                        }

                        if (someComponentList_entry.length() >= 4) {
                            new_someComponentList_entry = String.valueOf(someComponentList_entry.charAt(0))
                                    + specialchar_sample.charAt(k)
                                    + specialchar_sample.charAt((k + 2) % specialchar_sample.length())
                                    + someComponentList_entry.substring(3);
                        }

                        someComponentList.add(new_someComponentList_entry);

                        new_someComponentList_entry = URLEncoder.encode(new_someComponentList_entry, "UTF-8");
                        someComponentList.add(new_someComponentList_entry);
                    }
                }
            } catch (IndexOutOfBoundsException | UnsupportedEncodingException e) {
                System.err.println("generateComponentList() error: " + e);
            }
        }

        // adding 2-section and 3-section elements
        if (max_sections >= 2) {
            int num_single_section_someComponentLists = someComponentList.size();

            String someComponentLists_multi_section = "";

            try {
                for (int i = 1; i < num_single_section_someComponentLists; i++) {

                    for (int j = 1; j < num_single_section_someComponentLists; j++) {
                        someComponentLists_multi_section = someComponentList.get(i) + someComponentList.get(j);
                        someComponentList.add(someComponentLists_multi_section);
                        if (j > 30) {
                            j += i % 500;
                        }
                    }
                    if (i >= 30) {
                        i += i % 500;
                    }
                }
            } catch (OutOfMemoryError e) {
                System.err.println("generateComponentList() error: " + e);
                System.err.println("Number of entries: " + someComponentList.size());
            }

            if (max_sections >= 3) {
                try {
                    for (int i = 1; i < num_single_section_someComponentLists; i++) {
                        for (int j = 1; j < num_single_section_someComponentLists; j++) {
                            for (int k = 1; k < num_single_section_someComponentLists; k++) {
                                someComponentLists_multi_section = someComponentList.get(i) + someComponentList.get(j)
                                        + someComponentList.get(k);
                                someComponentList.add(someComponentLists_multi_section);

                                if (k > 30) {
                                    k += j % 500;
                                }
                            }
                            if (j > 30) {
                                j += i % 500;
                            }
                        }
                        if (i > 30) {
                            i += i % 500;
                        }
                    }
                } catch (OutOfMemoryError e) {
                    System.err.println("generateComponentList() error: " + e);
                    System.err.println("Number of entries: " + someComponentList.size());
                }
            }
        }

    }

    public void generateBasicScheme() {

        scheme = new ArrayList<String>();

        scheme.add("");
        scheme.add("http://");
        scheme.add("http:///");
        scheme.add("file://");
        scheme.add("file");
        scheme.add("http");
        scheme.add("htp");
        scheme.add("ht");
        scheme.add("ht://");
        scheme.add("ftp://");
        scheme.add("ftp:");
        scheme.add("ftp");
        scheme.add("f3p://");
        scheme.add("h3t://");
        scheme.add("h3t");
        scheme.add("3ht://");
        scheme.add("http:/");
        scheme.add("http:");
        scheme.add("http/");
        scheme.add("://");
        scheme.add(":/");

    }

    public void generateScheme() {
        generateBasicScheme();
        generateComponentList(scheme, 1);
    }

    public void generateBasicHostWithoutTLD() {

        // hostWithoutTLD
        hostWithoutTLD = new ArrayList<String>();

        // adding single-section hostnames
        hostWithoutTLD.add("");
        hostWithoutTLD.add(".");
        hostWithoutTLD.add("..");
        hostWithoutTLD.add("www.");
        hostWithoutTLD.add("www..");
        hostWithoutTLD.add("ww.google.");
        hostWithoutTLD.add("www.google.");
        hostWithoutTLD.add("ww.");
        hostWithoutTLD.add("0.0.0.0");
        hostWithoutTLD.add("0.1.2.3");
        hostWithoutTLD.add("1.2.3.256");
        hostWithoutTLD.add("1.2.3.4.5");
        hostWithoutTLD.add("1..2.");
        hostWithoutTLD.add("01.");
        hostWithoutTLD.add("google.");
        hostWithoutTLD.add("google..");

    }

    public void generateHostWithoutTLD() {
        generateBasicHostWithoutTLD();
        generateComponentList(hostWithoutTLD, 2);
    }

    public void generateBasicTLD() {

        // tld
        tld = new ArrayList<String>();

        // adding single-section tlds
        tld.add("");
        tld.add(".");
        tld.add("c");
        tld.add("co");
        tld.add("com");
        tld.add("com.");
        tld.add("mil");
        tld.add("ac");
        tld.add("cn");
        tld.add("c1");
        tld.add("ca");
        tld.add("11");
        tld.add("256");
        tld.add("cn.");
        tld.add("c1.");
        tld.add("ca.");
        tld.add("aero");
        tld.add("aero.");
        tld.add("academy");
        tld.add("academy.");
        tld.add("academy..");
        tld.add("dog");
        tld.add("dog.");
        tld.add("bcd");
    }

    public void generateTLD() {
        generateBasicTLD();
        generateComponentList(tld, 2);
    }

    public void generateBasicPort() {

        // port
        port = new ArrayList<String>();

        port.add("");
        port.add(":");
        port.add(":.");
        port.add(":80");
        port.add(":80.");
        port.add(":a");
        port.add(":ab");
        port.add(":a80");
        port.add(":0");
        port.add(":0.");
        port.add(":-1");
        port.add(":65535");
        port.add(":65535.");
        port.add(":65536");

    }

    public void generatePort() {
        generateBasicPort();
        generateComponentList(port, 1);
    }

    public void generateBasicPath() {

        // path
        path = new ArrayList<String>();

        path.add("");
        path.add("/");
        path.add("/.");
        path.add("/80");
        path.add("/80.");
        path.add("//ab");
        path.add("/a80");
        path.add("/file1");
        path.add("//file1");
        path.add("/file1/file2");
        path.add("/file1//file2");
        path.add("/..");
        path.add("/../abc");
        path.add("/...");
        path.add("/../");
        path.add("//..");
        path.add("//...");
        path.add("//");
        path.add("///");
        path.add("//.");

    }

    public void generatePath() {
        generateBasicPath();
        generateComponentList(path, 2);
    }

    public void generateBasicQuery() {

        // query
        query = new ArrayList<String>();

        query.add("");
        query.add("?");
        query.add("??");
        query.add("?.");
        query.add("???");
        query.add("?test1");
        query.add("??test1");
        query.add("??.a");
        query.add("?a?");
        query.add("?test=");
        query.add("?test=?");
        query.add("?test=true");
        query.add("?test==t");
        query.add("?test==tr");
        query.add("?t==tr");
        query.add("?t=false&");
        query.add("?tr..");
        query.add("?tr=fa&rt=af");
        query.add("?tr=fa&&rt=af");

    }

    public void generateQuery() {
        generateBasicQuery();
        generateComponentList(query, 2);
    }
}