/**
 * \file        UARTCommunication.cpp
 * \brief       A brief description one line.
 *
 * \author      Sevval MEHDER
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "UARTCommunication.h"


/*------------------------------< Defines >-----------------------------------*/

/*BAUD Rate = 9600 */

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

UARTCommunication::UARTCommunication()
{
	// Init function
		
		printf("\n +----------------------------------+");
		printf("\n |        Serial Port Comm.         |");
		printf("\n +----------------------------------+");

		/*------------------------------- Opening the Serial Port -------------------------------*/

		/* Change /dev/ttyUSB0 to the one corresponding to your system */

        	serial_port = open("/dev/ttyUSB0", O_RDWR);	/* ttyUSB0 is the FT232 based USB2SERIAL Converter   */
			   					/* O_RDWR   - Read/Write access to serial port       */
								/* Open in blocking mode,read will wait              */
									
									                                        
									
        	if(serial_port == -1)						/* Error Checking */
            	   printf("\n  Error! in Opening ttyUSB0  ");
        	else
            	   printf("\n  ttyUSB0 Opened Successfully ");

	
		/*---------- Setting the Attributes of the serial port using termios structure --------- */
		
		struct termios SerialPortSettings;	/* Create the structure                          	 */
		
		// Read in existing settings, and handle any error
		if(tcgetattr(serial_port, &SerialPortSettings) != 0) {
			printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
		}

		/* 8N1 Mode */
		SerialPortSettings.c_cflag &= ~PARENB;   /* Disables the Parity Enable bit(PARENB),So No Parity   */
		SerialPortSettings.c_cflag &= ~CSTOPB;   /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
		SerialPortSettings.c_cflag &= ~CSIZE;	 /* Clears the mask for setting the data size             */
		SerialPortSettings.c_cflag |=  CS8;      /* Set the data bits = 8                                 */
		
		SerialPortSettings.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
		SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */ 
		
		
		SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);          /* Disable XON/XOFF flow control both i/p and o/p */
		SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ECHONL | ISIG);  /* Non Cannonical mode & echo            */


		SerialPortSettings.c_oflag &= ~OPOST;/*No Output Processing*/
		
		/* Setting Time outs */
		SerialPortSettings.c_cc[VMIN] = 8; /* Read at least 8 characters */
		SerialPortSettings.c_cc[VTIME] = 0; /* Wait indefinetly          */

		/* Setting the Baud rate */
		cfsetispeed(&SerialPortSettings,B115200); /* Set Read  Speed as 115200                       */
		cfsetospeed(&SerialPortSettings,B115200); /* Set Write Speed as 115200                       */

		if((tcsetattr(serial_port,TCSANOW,&SerialPortSettings)) != 0) /* Set the attributes to the termios structure */
		    printf("\n  ERROR ! in Setting attributes");
		else
            printf("\n  BaudRate = 115200 \n  StopBits = 1 \n  Parity   = none");
}

void UARTCommunication::swrite(std::string message){
	// Write operation
	unsigned char msg[] = "sample";		/* Buffer containing characters to write into port	 */	
	int  bytes_written  = 0;  	/* Value for storing the number of bytes written to the port */ 

	bytes_written = write(serial_port,msg,sizeof(msg));/* use write() to send data to port                             */
										/* "serial_port"          - file descriptor pointing to the opened serial port */
										/*	"msg"        - address of the buffer containing data	          */
										/* "sizeof(msg)" - No of bytes to write                               */	
	printf("\n  %s written to ttyUSB0",msg);
	printf("\n  %d Bytes written to ttyUSB0", bytes_written);
	printf("\n +----------------------------------+\n\n");
}

std::string UARTCommunication::sread(){
	// Read operation
	tcflush(serial_port, TCIFLUSH);   /* Discards old data in the rx buffer            */

	char read_buffer[256];   /* Buffer to store the data received              		   */
	int  bytes_read = 0;    /* Number of bytes read by the read() system call          */
	int i = 0;

	bytes_read = read(serial_port,&read_buffer,32); /* Read the data                   */
		
	printf("\n\n  Bytes Rxed -%d", bytes_read); /* Print the number of bytes read      */
	printf("\n\n  ");

	for(i=0;i<bytes_read;i++)	 /* Printing only the received characters              */
		printf("%c",read_buffer[i]);

	printf("\n +----------------------------------+\n\n\n");

}
