import java.io.*;
import java.net.*;
import java.awt.image.*;
import javax.imageio.ImageIO;
import java.nio.*;
import java.util.*;

class Sender {
   public static int timer(){
      // get time in milliseconds
      Calendar timer = new GregorianCalendar();
      int millisecond = timer.get(Calendar.MILLISECOND);
      int second = timer.get(Calendar.SECOND);
      int minute = timer.get(Calendar.MINUTE);
      int hour = timer.get(Calendar.HOUR);
      return (millisecond + second * 1000 + minute * 60000 + hour * 3600000);
   }

   public static void main(String args[]) throws Exception {
      // get the IP address of localhost
      InetAddress IPAddress = InetAddress.getByName("localhost");

      // set port, input filename and retry time out from the command line
      int senderPort = Integer.parseInt(args[1]);
      String fileName = args[2];
      int retryTimeOut = Integer.parseInt(args[3]);

      // read image
      BufferedImage img = ImageIO.read(new File(fileName));

      // create sender socket
      DatagramSocket senderSocket = new DatagramSocket();

      // convert the image to the output stream and retrieve data to a byte array
      ByteArrayOutputStream byteArrayOS = new ByteArrayOutputStream();   
      ImageIO.write(img, "jpg", byteArrayOS);
      byteArrayOS.flush();
      byte[] sendData = byteArrayOS.toByteArray();

      
      int leftLen = sendData.length;    // initialize the size of data that has not been sent to the length of sendData
      int srcPos = 0;                   // starting position of the source 
      int length = 1021;                // length of the actual data (1024 - 2 bytes sequence number - 1 byte flag)
      short sequenceNumber = 1;         // sequence number of packets
      byte[] sequenceNum = new byte[2]; // initialize a byte array of size 2 to store the (short) sequence number
      byte eofFlag = 0;                 // Flag 0 - Not the end of the file
      short ackSequenceNumber = 0;      // ACK sequence number
      int retransmission = 0;           // count the number of retransmissions

      int start = timer(); // (ms)
      // while there is still data that has not been sent
      // store sendData to smaller byte arrays of size 1024 and send the data segment packets
      while (leftLen > 0) {
         // convert the short sequence number to a byte array of size 2
         sequenceNum[0] = (byte)(sequenceNumber);
         sequenceNum[1] = (byte)((sequenceNumber >> 8) & 0xff);

         // initialize new dataPacket which will contain 2 bytes sequence number, 1021 bytes actual data, 1 byte flag
         byte[] dataPacket = new byte[1024];

         // First two bytes of header - arraycopy from the byte array sequenceNum to first 2 bytes of dataPacket
         System.arraycopy(sequenceNum, 0, dataPacket, 0, sequenceNum.length);

         // Third byte of header - store the end-of-file flag
         dataPacket[2] = eofFlag;

         // arraycopy from the byte array sendData to dataPacket[3] to dataPacket[length+1]
         System.arraycopy(sendData, srcPos, dataPacket, 3, length);

         // create and send the datagram
         DatagramPacket sendPacket = new DatagramPacket(dataPacket, dataPacket.length, IPAddress, senderPort);
         senderSocket.send(sendPacket);
         System.out.println("Sent Packet: "+sequenceNumber);

         // Resend packet while not received positive ACK
         boolean packetReceived = false, ackReceived = false;
         while (!packetReceived) {

            // initialize a byte array of size 2 to receive ACK
            byte[] ack = new byte[2];
            DatagramPacket ackPacket = new DatagramPacket(ack, ack.length);

            // receiving ACK if not timeout
            try {
               senderSocket.setSoTimeout(retryTimeOut);
               senderSocket.receive(ackPacket);
               ackSequenceNumber = (short)((ack[1] << 8) + (ack[0] & 0xff));
               ackReceived = true;
            } catch (SocketTimeoutException e) {
               System.out.println("Time out, still waiting for the acknowledgment");
               ackReceived = false;
            }

            // Break if ACK is positive, otherwise, resend the packet
            if (ackReceived && (ackSequenceNumber == sequenceNumber)) { 
               packetReceived = true;
               System.out.println("ACK Received Packet: " + ackSequenceNumber);
               break;
            } else {
               senderSocket.send(sendPacket);
               retransmission++;  // increment retransmission number
            }
         }

         // decrement the leftLen, while increment srcPos and sequenceNumber
         leftLen-=length;                 
         srcPos = sequenceNumber * length;
         sequenceNumber++;

         // if leftLen <= 1024, then the next round will be the last round to send dataPacket
         if (leftLen <= length) {
            length = leftLen;
            eofFlag = 1; // Flag 1 - Next round of while loop will reach the end of the file
         }
      }
      
      int end = timer(); // (ms)

      // close sender socket
      senderSocket.close();

      System.out.println("Sending successfully!");

      double fileSize = (sendData.length) / 1024; // File size (KB)
      double transferTime = (double)(end - start) / 1000; // Transfer time (s)
      double throughput = (double) fileSize / transferTime; // Measure average throughput (KB/s)
      
      System.out.println(String.format("Average throughput %.2f KB/s", throughput));  
      System.out.println("Retransmissions: " + retransmission);  
   }
}