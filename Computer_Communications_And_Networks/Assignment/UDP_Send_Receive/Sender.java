import java.io.*;
import java.net.*;
import java.awt.image.*;
import javax.imageio.ImageIO;
import java.nio.*;

class Sender {
   public static void main(String args[]) throws Exception {
      // get the IP address of localhost
      InetAddress IPAddress = InetAddress.getByName("localhost");

      // set port and the input filename from the command line
      int senderPort = Integer.parseInt(args[1]);
      String fileName = args[2];

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
         System.out.println("Sent Package: "+sequenceNumber);

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

      // close sender socket
      senderSocket.close();
   }
}