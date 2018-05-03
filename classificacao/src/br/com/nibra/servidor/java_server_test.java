package br.com.nibra.servidor;

// Simple test of the Java server class

// Keith Vertanen 4/99, updated 10/09

import java.io.*;
import java.net.*;

public class java_server_test 
{

   static int SIZE = 10;		// how many items in each packet
   static int NUM_PACKS = 1;	// how many repetitions to do

   public static void main( String args[] ) throws IOException
   {
	int port = 1995;
	int dataport = -1;
	int rev = 0;

	if (args.length > 1)
	{
		port = (new Integer(args[0])).intValue();
		if (args.length > 2)
			dataport = (new Integer(args[1])).intValue();
	}


	System.out.println("Server, listening on port " + port + ", datagram port " + dataport);
	Server mylink = new Server(port, dataport);

	double C[];
	byte D[];

	C = new double[SIZE];
	D = new byte[SIZE];

	for (int i=0; i<SIZE; i++)
	{
		C[i] = i*i + 0.5;
		D[i] = (byte) i;
	}
while(true){
	try {
	System.out.println("Server, waiting for connection...");
	mylink.Connect();
	
	for (int i=0; i<NUM_PACKS; i++)
	{
		/*
		System.out.println("Server, sending bytes, iteration " + i);
		mylink.SendBytes(D, SIZE);

		System.out.println("Server, receiving doubles, iteration " + i);
		mylink.RecvDoubles(C, SIZE);
		*/
		String texto = mylink.RecvString('\0');
		System.out.println(texto);
	}

	System.out.println("Server, closing connection...");
	mylink.Close();	

	System.out.println("Server, done...");
	}
	catch(Exception e) {
		e.printStackTrace();
	}
   }
   }
}
