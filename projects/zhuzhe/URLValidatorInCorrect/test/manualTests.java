import java.io.PrintWriter;
import javafx.util.Pair;
import java.util.ArrayList;

public class manualTests {

	public static void testManualTest_2_SLASHES(PrintWriter printResult) {

		ArrayList<Pair<String, Boolean>> testURLs = new ArrayList<Pair<String, Boolean>>();
		
		testURLs.add(new Pair("http://www.amazon.com?x", new Boolean(true)));
		testURLs.add(new Pair("http://www.google.com////////pathQuery#Fragment", new Boolean(false)));
		testURLs.add(new Pair("http://www.co:65535//...?test=", new Boolean(false)));
		testURLs.add(new Pair("http:/co:65535//...?", new Boolean(false)));
		testURLs.add(new Pair("https://www.google.co:0//file1/file2?tr=fa&&rt=af", new Boolean(true)));
		testURLs.add(new Pair("http:///ca??test1", new Boolean(false)));
		testURLs.add(new Pair("http://WWW.AMAZON.com", new Boolean(true)));

		UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_2_SLASHES);

		printResult.println("testManualTest_2_SLASHES STARTS\n");

		for (int i=0; i<testURLs.size(); i++) {
			String testURL = testURLs.get(i).getKey();
			printResult.println("\t" + testURL);

			boolean shouldBeValid = testURLs.get(i).getValue().booleanValue();

			try {
				boolean testValid = urlVal.isValid(testURL);
				printResult.println("\t\tShould be " + shouldBeValid
					+ "; Test result: " + testValid);
				if (shouldBeValid != testValid) {
					printResult.println("\t\tError!\n");
				}
				else {
					printResult.println();
				}
			} catch (IllegalArgumentException | ExceptionInInitializerError
			| NoClassDefFoundError e) {
				printResult.println("\t\tRuntime error: " + e + "\n");
			}
			
		}

		printResult.println("testManualTest_2_SLASHES ENDS\n");


	}

	public static void testManualTest_ALL_SCHEMES(PrintWriter printResult) {

		ArrayList<Pair<String, Boolean>> testURLs = new ArrayList<Pair<String, Boolean>>();
		
		testURLs.add(new Pair("http://www.amazon.com?x", new Boolean(true)));
		testURLs.add(new Pair("http://..ca./file1?tr=fa&&rt=af", new Boolean(false)));
		testURLs.add(new Pair("http://ez6TFMO5l.com%3F%7BXO%3F%26S%7D%3DV*lOxKJ%29Q%26n%3Dp-%2", new Boolean(false)));
		testURLs.add(new Pair("https://%%[test].ca,==/test/", new Boolean(false)));
		testURLs.add(new Pair("http://%%[test].ca,==/test/", new Boolean(false)));
		testURLs.add(new Pair("http://.ca.@test,+;==/test/", new Boolean(false)));
		testURLs.add(new Pair("http://.ca.test,+;", new Boolean(false)));
		testURLs.add(new Pair("ftp://ucalgary.ca/", new Boolean(true)));
		testURLs.add(new Pair("http://.ninja.test,=;/", new Boolean(false)));
		testURLs.add(new Pair("h3tp://.ninja.test,=;/", new Boolean(false)));
		testURLs.add(new Pair("://www.rottentomatoes.com", new Boolean(false)));
		testURLs.add(new Pair("http://WWW.AMAZON.com", new Boolean(true)));
		testURLs.add(new Pair("HTTP://www.utoronto.ca", new Boolean(true)));

		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		printResult.println("testManualTest_ALL_SCHEMES STARTS\n");

		for (int i=0; i<testURLs.size(); i++) {
			String testURL = testURLs.get(i).getKey();
			printResult.println("\t" + testURL);

			boolean shouldBeValid = testURLs.get(i).getValue().booleanValue();

			try {
				boolean testValid = urlVal.isValid(testURL);
				printResult.println("\t\tShould be " + shouldBeValid
					+ "; Test result: " + testValid);
				if (shouldBeValid != testValid) {
					printResult.println("\t\tError!\n");
				}
				else {
					printResult.println();
				}
			} catch (IllegalArgumentException | ExceptionInInitializerError
			| NoClassDefFoundError e) {
				printResult.println("\t\tRuntime error: " + e + "\n");
			}
			
		}

		printResult.println("testManualTest_ALL_SCHEMES ENDS\n");

	}

	public static void testManualTest_NO_FRAGMENTS(PrintWriter printResult) {

		ArrayList<Pair<String, Boolean>> testURLs = new ArrayList<Pair<String, Boolean>>();
		
		testURLs.add(new Pair("http://www.rottentomatoes.com", new Boolean(true)));
		testURLs.add(new Pair("http:/www.rottentomatoes.com", new Boolean(false)));
		testURLs.add(new Pair("://www.rottentomatoes.com", new Boolean(false)));
		testURLs.add(new Pair("http://www.rottentomatoes.au", new Boolean(true)));
		testURLs.add(new Pair("http://www.rottentomatoes~.com", new Boolean(false)));
		testURLs.add(new Pair("http://1.2.3.4.5", new Boolean(false)));
		testURLs.add(new Pair("http://www.rottentomatoes.com:-80", new Boolean(false)));
		testURLs.add(new Pair("ftp://ucalgary.ca", new Boolean(true)));
		testURLs.add(new Pair("HTTP://www.utoronto.ca", new Boolean(true)));
		testURLs.add(new Pair("http://www.MCGILL.ca", new Boolean(true)));

		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
		printResult.println("testManualTest_NO_FRAGMENTS STARTS\n");

		for (int i=0; i<testURLs.size(); i++) {
			String testURL = testURLs.get(i).getKey();
			printResult.println("\t" + testURL);

			boolean shouldBeValid = testURLs.get(i).getValue().booleanValue();

			try {
				boolean testValid = urlVal.isValid(testURL);
				printResult.println("\t\tShould be " + shouldBeValid
					+ "; Test result: " + testValid);
				if (shouldBeValid != testValid) {
					printResult.println("\t\tError!\n");
				}
				else {
					printResult.println();
				}
			} catch (IllegalArgumentException | ExceptionInInitializerError
			| NoClassDefFoundError e) {
				printResult.println("\t\tRuntime error: " + e + "\n");
			}
			
		}

		printResult.println("testManualTest_NO_FRAGMENTS ENDS\n");

	}

	public static void testManualTest_LOCAL_URLS(PrintWriter printResult) {

		ArrayList<Pair<String, Boolean>> testURLs = new ArrayList<Pair<String, Boolean>>();
		
		testURLs.add(new Pair("/home/ubuntu/test", new Boolean(false)));
		testURLs.add(new Pair("http:/www.rottentomatoes.com", new Boolean(false)));
		testURLs.add(new Pair("://www.rottentomatoes.com", new Boolean(false)));
		testURLs.add(new Pair("http://www.rottentomatoes.au", new Boolean(true)));
		testURLs.add(new Pair("http://www.rottentomatoes~.com", new Boolean(false)));
		testURLs.add(new Pair("http://1.2.3.4.5", new Boolean(false)));
		testURLs.add(new Pair("http://www.rottentomatoes.com:-80", new Boolean(false)));
		testURLs.add(new Pair("ftp://ucalgary.ca", new Boolean(true)));
		testURLs.add(new Pair("file://home", new Boolean(false)));
		testURLs.add(new Pair("HTTP://www.uWATERloo.ca", new Boolean(true)));

		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
		printResult.println("testManualTest_LOCAL_URLS STARTS\n");

		for (int i=0; i<testURLs.size(); i++) {
			String testURL = testURLs.get(i).getKey();
			printResult.println("\t" + testURL);

			boolean shouldBeValid = testURLs.get(i).getValue().booleanValue();

			try {
				boolean testValid = urlVal.isValid(testURL);
				printResult.println("\t\tShould be " + shouldBeValid
					+ "; Test result: " + testValid);
				if (shouldBeValid != testValid) {
					printResult.println("\t\tError!\n");
				}
				else {
					printResult.println();
				}
			} catch (IllegalArgumentException | ExceptionInInitializerError
			| NoClassDefFoundError e) {
				printResult.println("\t\tRuntime error: " + e + "\n");
			}
			
		}

		printResult.println("testManualTest_LOCAL_URLS ENDS\n");

	}
}