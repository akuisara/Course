// Java API Documentation: http://docs.oracle.com/javase/7/docs/api/
// Garbage collection is a part of JVM, the garbage collector runs its own thread, references expire when out of the scope, explicitly expire the persistent objects by setting to null
// Variables: primitives ((data type lowercase / helper class uppercase (e.g., upward numeric conversion, which can also be done by using the casting syntax: add (certainType) before the value)) - int (byte, short, int, long: num_L), char, bool, float (float: num_f, double: num_d)); complex objects (string, date, other objects...). Class variables are fields
// C-style language with similar operators. For/while loop, if/switch statements, overloading functions are the same as C++
// Variables and strings are always pass-by-copy, complex objects like an array pass by reference because copy and original point to the same memory location
// dummynet: network emulation tool

import java.math.*; // BigDecimal
import java.io.*;
import java.util.*; // Date, GregorianCalendar
import java.text.*; // DateFormat
import java.net.*;  // URI, URL

public class HelloWorld {
    public static void main(String[] args) {
        // public accessible
        // static does not have to create an instance
        // return void

        char[] chars = {'H', 'e', 'l', 'l', 'o'};
        String hello = new String(chars);
        // strings comparison cannot use "==", but s1.equals(s2) instead
        if (hello instanceof java.lang.String) {
            StringBuilder message = new StringBuilder(hello); // avoid creating new instance in memory
            message.append(" World - Java");
            System.out.println(message);

            int pos = message.indexOf("World");
            String subMessage = message.substring(pos);
            // String removeLeadingTrailingWhiteSpaces = subMessage.trim();
        }
        // Java compiler: javac HelloWorld.java
        // (javac HelloWorld.java -verbose)
        // Application launcher: java HelloWorld

        System.out.println("Number of args:" + args.length);
        for(int i=0; i<args.length;i++){
            System.out.print(args[i] + ' ');
        }

        // Another for loop:
        System.out.println("Sum: " + sumLoop(numbers));

        int i = 0;
        // Postfix print 0
        System.out.println(i++);
        // Prefix print 2
        System.out.println(++i);

        // Currency: BigDecimal
        double d = 12.55d;
        String ds = Double.toString(d);
        BigDecimal bd = new BigDecimal(ds);
        char dollar = '\u0024'; // unicode '$'
        System.out.println("\nCost: " + dollar + bd.toString());

        String s1 = getInput("Enter a numeric value: ");
        String s2 = getInput("Enter a numeric value: ");
        double d1 = Double.parseDouble(s1);
        double d2 = Double.parseDouble(s2);
        double result = d1 + d2;
        System.out.println("Sum: " + result);

        GregorianCalendar calendar = new GregorianCalendar(2015, 1, 7); // February
        calendar.add(GregorianCalendar.DATE, 0);
        Date date1 = calendar.getTime();

        DateFormat dateFormatter = DateFormat.getDateInstance(DateFormat.FULL);
        String date2 = dateFormatter.format(date1);
        System.out.println(date2);

        try {
            URI uri = new URI(
                "https",
                "github.com",
                "/akuisara/Course/blob/master/Computer_Communications_And_Networks/learnJava/HelloWorld.java",
                null);
            URL url = uri.toURL();
            System.out.println(url);

        } catch (Exception e){
            System.out.println(e.getMessage());
        }        
    }

    private static String getInput(String prompt){
        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
        System.out.print(prompt);
        System.out.flush(); 

        try {
            return stdin.readLine();
        } catch (Exception e){
            return "Error" + e.getMessage();
        }
    }

    // alternative error handling
    private static void outOfIndex() throws ArrayIndexOutOfBoundsException {
        System.out.println("Eleventh: "+numbers[10]);
    };

    private static double[] numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    private static double sumLoop(double ... num){
        try {
            System.out.println("Eleventh: "+numbers[10]);
        } catch (ArrayIndexOutOfBoundsException e){
            e.printStackTrace();
        }

        try {
            outOfIndex();
        } catch (ArrayIndexOutOfBoundsException e){
            System.out.println("Customized error message: out of index");
        }

        double result = 0d;
        for(double n : num) {
            result += n;
        }
        return result;
    }

}