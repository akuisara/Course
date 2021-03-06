// Java API Documentation: http://docs.oracle.com/javase/7/docs/api/
// Apache Commons: http://commons.apache.org/

// Garbage collection is a part of JVM, the garbage collector runs its own thread, references expire when out of the scope, explicitly expire the persistent objects by setting to null
// Variables: primitives ((data type lowercase / helper class uppercase (e.g., upward numeric conversion, which can also be done by using the casting syntax: add (certainType) before the value)) - int (byte, short, int, long: num_L), char, bool, float (float: num_f, double: num_d)); complex objects (string, date, other objects...). Class variables are fields
// C-style language with similar operators. For/while loop, if/switch statements, overloading functions are the same as C++
// Variables and strings are always pass-by-copy, complex objects like an array pass by reference because copy and original point to the same memory location

// package helpers; write at the top of the helper functions in a helpers folder
// import helpers.*; after created the helper functions
// inside an instance class, namefield "this" is current instance in current class
// getExample/setExample as getter/setter for Example
// public class Subclass extends Superclass {}
// overload a constructor can call super() from inheritance superclass
// add "@Override" before overriding the functions from superclass makes code more readable
// downward casting: Subclass subInstance = (Subclass) parentMethod

// create instance import java.util.Collection
// public interface SomeInterface {method can only be public or abstract, where abstract functions must be implemented in subclasses} 
// public class SomeClass implement SomeInterface { @Override methods} 

// dummynet: network emulation tool

/**
* Generate Javadoc
* @author Sara
* @version 1.0
**/

// package HelloWorld

import java.math.*; // BigDecimal
import java.io.*;   // InputStream, OutputStream, File, FileInputStream, FileOutputStream, FileNotFoundException, IOException, BufferedInputStream
import java.util.*; // Date, GregorianCalendar, ArrayList, HashMap, Set, Iterator, ListIterator
import java.text.*; // DateFormat
import java.net.*;  // URI, URL, MalformedURLEception

import org.apache.commons.io.FileUtils;
// compile: javac -classpath lib/commons-io-2.4.jar HelloWorld.java -d .
// run: java -classpath lib/commons-io-2.4.jar: HelloWorld
// .jar: Java archive file 
// Create: jar cf HelloWorld.jar HelloWorld.java 
// Environment variable for current session: set CLASSPATH=.:{Package jar}

import javax.xml.parsers.*; // DocumentBuilderFactory, DocumentBuilder, ParserConfigurationException
import org.w3c.dom.*; // Element, Document, NodeList
import org.xml.sax.SAXException;

public class HelloWorld {
    // constant variable: final the value cannot be changed
    public static final long RED = 0xff0000;

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

            

        // multidimensional arrays
        // String [][] states = new String[int][int];   
        ArrayList<String> statesList = new ArrayList<String>();
        statesList.add("N/A");
        statesList.add("MA"); statesList.add("CO"); statesList.add("FL"); statesList.add("NH"); statesList.add("RI"); statesList.add("NY");
        statesList.remove(0); // get(), indexOf(), etc
        ListIterator<String> listIterator = statesList.listIterator();
        while (listIterator.hasNext()){
            System.out.println(listIterator.next());
        }

        HashMap<String, String> hashMap = new HashMap<String, String>();
        hashMap.put("Massachusetts", "MA"); // remove(key), get(key), etc
        hashMap.put("New York", "NY"); // remove(key), get(key), etc
        Set<String> keys = hashMap.keySet();
        Iterator<String> iterator = keys.iterator();
        while (iterator.hasNext()){
            String state = iterator.next();
            System.out.println(state + ": " + hashMap.get(state));
        }

        // File
        try {
            File file1 = new File("input.txt");
            File file2 = new File("output.txt");

            // InputStream inputStream = new FileInputStream(file1);
            // OutputStream outputStream = new FileOutputStream(file2);

            // byte[] buffer = new byte[1024];
            // int len;
            // while ((len = inputStream.read(buffer)) > 0){ // while !eof
            //     outputStream.write(buffer, 0, len); // copy file
            // }

            // inputStream.close();
            // outputStream.close();

            // alternative way to copy file by using apache commons library
            FileUtils.copyFile(file1, file2);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }


        try {
            // URI uri = new URI(
            //     "https",
            //     "github.com",
            //     "/akuisara/Course/blob/master/Computer_Communications_And_Networks/learnJava/HelloWorld.java",
            //     null);
            // URL url = uri.toURL();

            URL url = new URL("https://github.com/akuisara/Course/tree/master/Computer_Communications_And_Networks/learnJava");
            InputStream stream = url.openStream();
            BufferedInputStream bufferedStream = new BufferedInputStream(stream);

            StringBuilder stringBuilder = new StringBuilder();
            int webSource = 0;
            while(true){
                webSource = bufferedStream.read();
                if (webSource == -1) {
                    break;
                } else {
                    stringBuilder.append((char) webSource);
                }
            }
            // System.out.println(stringBuilder);

        } catch (Exception e){
            System.out.println(e.getMessage());
        } 

        // Parse XML
        try {
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document document = builder.parse("http://www.w3schools.com/xml/note.xml");
            NodeList list = document.getElementsByTagName("body");

            for (int j=0; j<list.getLength(); j++) {
                Element elt = (Element)list.item(j);
                System.out.println(elt.getFirstChild().getNodeValue());
            }
        } catch (ParserConfigurationException e) {
            e.printStackTrace();
        } catch (SAXException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
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