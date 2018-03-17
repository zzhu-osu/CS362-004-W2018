
import junit.framework.TestCase;
import java.security.SecureRandom;
import java.util.Objects;
import java.util.Random;
import java.util.ArrayList;
import java.net.URL;
import java.net.URLEncoder;
import java.net.MalformedURLException;
import java.net.URISyntaxException;

public class UrlValidatorTest extends TestCase {

    public static final String specialchar = " `~!@#$%^&*()-_=+[]{}\\|;:'\",.<>?";
    public static final String upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    public static final String lower = upper.toLowerCase();
    public static final String digits = "0123456789";
    public static final String alphanum = upper + lower + digits;
    public static final String alphanumchar = alphanum + specialchar;

    private ArrayList<String> scheme;
    private ArrayList<String> host;
    private ArrayList<String> port;
    private ArrayList<String> path;
    private ArrayList<String> query;

    private ArrayList<String> randomURL;

    public UrlValidatorTest(String testName) {
        super(testName);

    }

    public void randomTestIsValid() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        assertTrue(urlVal.isValid("http://www.google.com"));

        generate_random_url_components();

        int error_counter = 0;

        for (int i = 0; i < scheme.size(); i++) {
            for (int j = 0; j < host.size(); j++) {
                for (int k = 0; k < port.size(); k++) {
                    for (int m = 0; m < path.size(); m++) {
                        for (int n = 0; n < query.size(); n++) {

                            String testURLStr = scheme.get(i) + host.get(j) +
                                port.get(k) + path.get(m) + query.get(n);
                            try {
                                URL testURL = new URL(testURLStr);

                                testURL.toURI();

                                // should be valid
                                if (!urlVal.isValid(testURLStr)) {
                                    System.err.println("Error: should be valid: " + testURLStr);
                                    error_counter++;
                                }
                            } catch (MalformedURLException e) {
                                // should be invalid
                                if (urlVal.isValid(testURLStr)) {
                                    System.err.println("Error: should be invalid: " + testURLStr);
                                    error_counter++;
                                }
                            } catch (URISyntaxException e) {
                                // should be invalid
                                if (urlVal.isValid(testURLStr)) {
                                    System.err.println("Error: should be invalid: " + testURLStr);
                                    error_counter++;
                                }
                            }
                        }
                    }
                }
            }
        }


        System.out.println("\nTotal number of tests: " + randomURL.size());
        System.out.println("Errors: " + error_counter);

    }

    public void generate_random_url_components() {

        Random rand = new Random();

        scheme = new ArrayList<String>();
        host = new ArrayList<String>();
        port = new ArrayList<String>();
        path = new ArrayList<String>();
        query = new ArrayList<String>();

        RandomStringGenerator alphanumGenerator = new RandomStringGenerator(alphanum);
        RandomStringGenerator alphanumcharGenerator = new RandomStringGenerator(alphanumchar);
        RandomStringGenerator digitsGenerator = new RandomStringGenerator(digits);

        // scheme
        scheme.add("http://");
        scheme.add("ftp://");
        scheme.add("h3t://");
        scheme.add("");

        for (int i = 0; i < 10; i++) {
            // set a random length
            int scheme_length = rand.nextInt(8) + 1;
            String randomStr = alphanumGenerator.nextString(scheme_length);
            scheme.add(randomStr);
            scheme.add(randomStr + "://");
            scheme.add(randomStr + ":/");
            randomStr = alphanumcharGenerator.nextString(scheme_length);
            scheme.add(randomStr);
            scheme.add(randomStr + "://");
            scheme.add(randomStr + ":/");

            String randomStr_encoded = URLEncoder.encode(randomStr);
            if (!randomStr.equals(randomStr_encoded)) {
                scheme.add(randomStr_encoded);
                scheme.add(randomStr_encoded + "://");
                scheme.add(randomStr_encoded + ":/");
            }
        }

        // host
        host.add("");
        for (int i = 0; i < 30; i++) {
            int num_of_dots = rand.nextInt(6); // 0-5
            String host1 = "";
            String host2 = "";
            String host3 = "";
            for (int j = 0; j <= num_of_dots; j++) {
                int host_part_length = rand.nextInt(10) + 1;
                String randomStr = alphanumGenerator.nextString(host_part_length);
                host1 += randomStr + ".";
                randomStr = alphanumcharGenerator.nextString(host_part_length);
                host2 += randomStr + ".";

                String randomStr_encoded = URLEncoder.encode(randomStr);
                if (!randomStr.equals(randomStr_encoded)) {
                    host3 += randomStr_encoded + ".";
                }
            }

            host1 = host1.substring(0, host1.length() - 1);
            host2 = host2.substring(0, host2.length() - 1);

            host.add(host1);
            host.add(host1 + ".com");
            host.add(host1 + ".ca");
            host.add(host1 + ".academy");
            host.add(host2);
            host.add(host2 + ".com");
            host.add(host2 + ".ca");
            host.add(host2 + ".academy");

            if (host3.length() > 0) {
                host3 = host3.substring(0, host3.length() - 1);
                host.add(host3);
                host.add(host3 + ".com");
                host.add(host3 + ".ca");
                host.add(host3 + ".academy");
            }

        }

        // port
        port.add("");
        port.add(":");
        port.add(":65535");
        port.add(":-1");
        port.add(":8e");
        for (int i = 0; i < 10; i++) {

            int port_length = rand.nextInt(6) + 1;
            String randomNumber = ":" + digitsGenerator.nextString(port_length);
            String randomStr = ":" + alphanumcharGenerator.nextString(port_length);

            port.add(randomNumber);
            port.add(randomStr);

            String randomStr_encoded = ":" + URLEncoder.encode(randomStr);
            if (!randomStr.equals(randomStr_encoded)) {
                port.add(randomStr_encoded);
            }

        }

        // path
        path.add("");
        path.add("/");
        for (int i = 0; i < 30; i++) {
            int num_of_slash = rand.nextInt(6); // 0-5
            String path1 = "/";
            String path2 = "/";
            String path3 = "/";
            for (int j = 0; j <= num_of_slash; j++) {
                int path_part_length = rand.nextInt(10) + 1;
                String randomStr = alphanumGenerator.nextString(path_part_length);
                path1 += randomStr + "/";
                randomStr = alphanumcharGenerator.nextString(path_part_length);
                path2 += randomStr + "/";

                String randomStr_encoded = URLEncoder.encode(randomStr);
                if (!randomStr.equals(randomStr_encoded)) {
                    path3 += randomStr_encoded + "/";
                }
            }

            path1 = path1.substring(0, path1.length() - 1);
            path2 = path2.substring(0, path2.length() - 1);

            host.add(path1);
            host.add(path2);

            if (path3.length() > 1) {
                path3 = path3.substring(0, path3.length() - 1);
                host.add(path3);
            }

        }

        // query
        query.add("");
        query.add("?");
        query.add("?a=b");
        for (int i = 0; i < 30; i++) {
            int num_of_queries = rand.nextInt(6); // 0-5
            String query1 = "?";
            String query2 = "?";
            String query3 = "?";
            for (int j = 0; j < num_of_queries; j++) {
                int query_part1_length = rand.nextInt(10) + 1;
                String randomStr1 = alphanumGenerator.nextString(query_part1_length);
                query1 += randomStr1 + "=";
                randomStr1 = alphanumcharGenerator.nextString(query_part1_length);
                query2 += randomStr1 + "=";
                int query_part2_length = rand.nextInt(10) + 1;
                String randomStr2 = alphanumGenerator.nextString(query_part2_length);
                query1 += randomStr2 + "&";
                randomStr2 = alphanumcharGenerator.nextString(query_part2_length);
                query2 += randomStr2 + "&";

                String query2_encoded = URLEncoder.encode(query2);
                if (!query2.equals(query2_encoded)) {
                    query3 = query2_encoded;
                }
            }

            query1 = query1.substring(0, query1.length() - 1);
            query2 = query2.substring(0, query2.length() - 1);

            query.add(query1);
            query.add(query2);

            if (query3.length() > 1) {
                query3 = query3.substring(0, query3.length() - 1);
                query.add(query3);
            }

        }

    }

    public class RandomStringGenerator {

        private final Random random;

        private final char[] symbols_set;

        public String nextString(int length) {
            if (length < 1) {
                throw new IllegalArgumentException();
            }

            char[] generated_str = new char[length];
            for (int i = 0; i < generated_str.length; i++) {
                generated_str[i] = symbols_set[random.nextInt(symbols_set.length)];
            }
            return new String(generated_str);
        }

        public RandomStringGenerator(String symbols) {
            if (symbols.length() < 2)
                throw new IllegalArgumentException();
            this.random = Objects.requireNonNull(new SecureRandom());
            this.symbols_set = symbols.toCharArray();

        }

    }

    public static void main(String[] argv) {

        UrlValidatorTest fct = new UrlValidatorTest("Random URL test");
        fct.randomTestIsValid();

    }
}
