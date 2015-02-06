// Java API Documentation: http://docs.oracle.com/javase/7/docs/api/
// Garbage collection is a part of JVM, the garbage collector runs its own thread, references expire when out of the scope, explicitly expire the persistent objects by setting to null
// Variables: primitives ((data type lowercase / helper class uppercase (e.g., upward numeric conversion, which can also be done by using the casting syntax: add (certainType) before the value)) - int (byte, short, int, long: num_L), char, bool, float (float: num_f, double: num_d)); complex objects (string, date, other objects...). Class variables are fields
// C-style language with similar operators

import java.math.*;
import java.io.*;

public class HelloWorld {
    public static void main(String[] args) {
    	// public accessible
    	// static do not have to create an instance
    	// return void

    	char[] chars = {'H', 'e', 'l', 'l', 'o'};
    	String hello = new String(chars);
        // strings comparison cannot use "==", but s1.equals(s2) instead
    	if (hello instanceof java.lang.String) {
        	System.out.println(hello + "World!");
    	}
        // javac HelloWorld.java
        // (javac HelloWorld.java -verbose)
        // java HelloWorld

        System.out.println("Number of args:" + args.length);
        for(int i=0; i<args.length;i++){
        	System.out.print(args[i] + ' ');
        }

        // Currency: BigDecimal
        double d = 12.55d;
        String ds = Double.toString(d);
        BigDecimal bd = new BigDecimal(ds);
        char dollar = '\u0024'; // unicode '$'
        System.out.println("\nCost: " + dollar + bd.toString());

        int i = 0;
        // Postfix print 0
        System.out.println(i++);
        // Prefix print 2
        System.out.println(++i);

        String s1 = getInput("Enter a numeric value: ");
        String s2 = getInput("Enter a numeric value: ");
        double d1 = Double.parseDouble(s1);
        double d2 = Double.parseDouble(s2);
        double result = d1 + d2;
        System.out.println("Sum: " + result);

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
}