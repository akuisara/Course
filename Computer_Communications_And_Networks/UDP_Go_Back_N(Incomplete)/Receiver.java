import java.io.*;
import java.net.*;
import java.awt.image.*;
import javax.imageio.ImageIO;
import java.nio.*;

class Receiver {
   public static void main(String args[]) throws Exception {
      // set port, input filename and the window size from the command line
      int receiverPort = Integer.parseInt(args[0]);
      String fileName = args[1];
      int windowSize = Integer.parseInt(args[2]);

      // create receiver socket and initialize a byte array for receiveData
      DatagramSocket serverSocket = new DatagramSocket(receiverPort);
      byte[] receiveData = new byte[1024];

      // initialize an output stream to store received data stream
      ByteArrayOutputStream byteArrarOS = new ByteArrayOutputStream();  
      
      byte[] sequenceNum = new byte[2]; // initialize a byte array of size 2 to store the received sequence number
      short sequenceNumber = 0;         // sequence number of current packet
      short previousSequenceNumber = 0; // sequence number of previous packet
      boolean eof = false;              // Not the end of the file
      byte eofFlag = 0;                 // Flag 0 - Not the end of the file

      // receive data packets while not reach the end of the file
      while(!eof) {     
         // receive the datagram
         DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
         serverSocket.setSoTimeout(0);
         serverSocket.receive(receivePacket);

         // get the IP address and port number
         InetAddress IPAddress = receivePacket.getAddress(); 
         int port = receivePacket.getPort();

         // convert the sequence number to a short from data packet
         System.arraycopy(receiveData, 0, sequenceNum, 0, sequenceNum.length);
         sequenceNumber = (short)((sequenceNum[1] << 8) + (sequenceNum[0] & 0xff));

         // check the flag from the third byte of received data packet, eof is true when flag is 1
         eofFlag = receiveData[2];
         eof = eofFlag!=0;

         // convert the received sequence number to a byte array
         byte[] ack = new byte[2];
         ack[0] = (byte)(sequenceNumber);
         ack[1] = (byte)((sequenceNumber >> 8) & 0xff);

         // send ACK
         DatagramPacket ackPacket = new DatagramPacket(ack, ack.length, IPAddress, port);
         serverSocket.send(ackPacket);
         System.out.println("ACK sent successfully!");

         // check if received correct packet
         if (sequenceNumber == (previousSequenceNumber + 1)) {
            previousSequenceNumber = sequenceNumber;
            System.out.println("Received Packet: " + sequenceNumber +"\tFlag: " + eofFlag);
            // write receiveData[3] to receiveData[1022] to an byte array output stream
            byteArrarOS.write(receiveData, 3, 1021);
         }
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