import java.io.*;
import java.net.*;
import java.awt.image.*;
import javax.imageio.ImageIO;
import java.nio.*;

class Receiver {
   public static void main(String args[]) throws Exception {
      // set port and the input filename from the command line
      int receiverPort = Integer.parseInt(args[0]);
      String fileName = args[1];

      // create receiver socket and initialize a byte array for receiveData
      DatagramSocket serverSocket = new DatagramSocket(receiverPort);
      byte[] receiveData = new byte[1024];

      // initialize an output stream to store received data stream
      ByteArrayOutputStream byteArrarOS = new ByteArrayOutputStream();  

      byte[] sequenceNum = new byte[2]; // initialize a byte array of size 2 to store the received sequence number
      short sequenceNumber = 0;         // sequence number of packets
      boolean eof = false;              // Not the end of the file
      byte eofFlag = 0;                 // Flag 0 - Not the end of the file

      // receive data packets while not reach the end of the file
      while(!eof) {     
         // receive the datagram
         DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
         serverSocket.receive(receivePacket);

         // convert the sequence number to a short from data packet
         System.arraycopy(receiveData, 0, sequenceNum, 0, sequenceNum.length);
         sequenceNumber = (short)((sequenceNum[1] << 8) + (sequenceNum[0] & 0xff));

         // write receiveData[3] to receiveData[1022] to an byte array output stream
         byteArrarOS.write(receiveData, 3, 1021);

         // check the flag from the third byte of received data packet, eof is true when flag is 1
         eofFlag = receiveData[2];
         eof = eofFlag!=0;

         System.out.println("Received Package: "+sequenceNumber +"\tFlag: " + eofFlag);
      }

      // after retrieved data to a byte array, convert the output stream to image
      byte[] imageData = byteArrarOS.toByteArray();
      InputStream inputStream = new ByteArrayInputStream(imageData);
      BufferedImage bufferedImage = ImageIO.read(inputStream);

      // write to an output image file
      File outputFile = new File(fileName);
      ImageIO.write(bufferedImage, "jpg", outputFile);

      // close server socket
      serverSocket.close();
   }
}