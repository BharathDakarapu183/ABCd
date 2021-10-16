The codes for email client and server are in the client.c and server.c files respectively

For testing the Code the commands are as follows:

	 For compiling server and client files : make/make all

	 For Running the server : ./server <Port No> (use 9999)

	 For Running the client : ./client <ip address> <Port No>

	 To delete output files : make clean


Details of Implementation:

	CONSTRAINTS:
	
		MAXLENGTH:
			
		       The maximum length of string that can be written in a single line. It is set to 255.
                        So in both read and write we considered the buffer length as 255.

			
		MAXUSERS:
		
			The maximum number of users. It is set to 1000.
			
		
		
			
	
		MAIL FORMAT:

			From: ...
			To: ...
			Message
			...
			###
			
		Storing:
			
			After Quit command Server deletes all the users and their mails stored.
