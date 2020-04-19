==============================================================================
FSUIPC Developer Kit: Library for C#.NET programmers
Version 1.13 (06/02/2006) 
by Scott McCrory <scott@mccrory.us> and Bob Scott <w6kd@yahoo.com>
with improvements by Paul Henty <phenty@offsoft.com>, with thanks.
==============================================================================

To interface to FSUIPC (versions 1.998e or later) in your C#.NET programs:

* Add fsuipc.cs to your Visual Studio.NET project/solution
* Call the appropriate Library routines in your code.

More on this last part (and please feel free to refer to the examples at the
bottom of this README and the UIPC_SDK_CSHARP example solution provided):

BASIC USAGE GOES LIKE THIS:
   0. Instantiate the FsuipcSdk.Fsuipc class (i.e. Fsuipc f = new Fsuipc();).
   1. Call f.FSUIPC_Initialization() at beginning of program (optional).
   2. Call f.FSUIPC_Open() to connect with the running Flight Sim & FSUIPC.
   3. Call f.FSUIPC_Read and/or f.FSUIPC_Write one or more times to build
      the list of actions to be performed by the next step.
   4. Call f.FSUIPC_Process() to actually get/set the data from/to FS.
   5. For reads, call f.FSUIPC_Get to retrieve data read from FSUIPC.
   6. Repeat steps 3, 4, and 5 as necessary.
   7. At program termination, call f.FSUIPC_Close().


Initializing the link
=====================

When the Fsuipc object is freshly instantiated, it will already be
Initialized, however, if you want to reset the object, simply call the
following method: 

	public void FSUIPC_Initialization()
	
You may alternatively wish to destroy and reinstantiate the Fsuipc object
altogether.


Opening the link to FSUIPC
==========================

For this you use the following Library routine:

	public bool FSUIPC_Open(int dwFSReq, ref int dwResult);

where
	dwFSReq specifies which Flight Simulator you want to connect to:
	
		int SIM_ANY		for any supported by FSUIPC or equivalent	
		int SIM_FS98	FS98
		int SIM_FS2K	FS2000
		int SIM_FS2K2	FS2002
		int SIM_CFS2	CFS2
		int SIM_CFS1	CFS
		int SIM_FLY		Fly! (not supported yet, and no promises implied!

and
	dwResult is a reference to an int to receive an error number if the
	operation fails.
	
If the method returns a "FALSE" then the value in the result int will tell
you what went wrong.  The errors currently possible are defined in the Fsuipc
constants (see the list of FSUIPC_ERR_* defs in fsuipc.cs).

If it returns "TRUE" then the link is open and ready for your requests.
Already the Library routine will have obtained some data for you:

	int FSUIPC_Version;		// HIWORD is 1000 x Version Number, minimum 1998
							// LOWORD is build letter, with a = 1 etc.
	int FSUIPC_FS_Version;	// SIM_FS98, SIM_FS2K etc -- see above


Specifying the READ and WRITE requests
======================================

The interface to FSUIPC (and hence the simulator) is simply one of reads and
writes from and to specific memory "offsets". These were originally true
offsets into a specific Global data area within FS, but nowadays, at least
in FS2000+ and CFS they are more likely to be treated as Identifiers to specific
variables, and are translated within FSUIPC. However, you may still address
data with contiguous offsets in blocks, as FSUIPC breaks these down if it
needs to.

READS: The following Library call is used to accumulate Read requests:

		public bool FSUIPC_Read(int dwOffset, int dwSize, ref int Token,
		   ref int dwResult) 
											
	You supply an offset "dwOffset" and size "dwSize" identifying the data
	required as documented in "FSUIPC for Programmers.doc".  The int pointer
	"dwResult" receives the result.  The int pointer "Token" will hold a
	reference token that you'll use during the Get operation further down below.
	This is needed because several Read operations can be performed and
	processed at a time, and the reference tokens are used to uniquely identify
	each value returned to match up with the corresponding memory Read requests.

WRITES: Use the following overloaded Library calls to accumulate Write requests:

		public bool FSUIPC_Write(int dwOffset, byte param, ref int Token,
			ref int dwResult) 
		public bool FSUIPC_Write(int dwOffset, short param, ref int Token,
			ref int dwResult) 
		public bool FSUIPC_Write(int dwOffset, int param, ref int Token,
			ref int dwResult) 
		public bool FSUIPC_Write(int dwOffset, long param, ref int Token,
			ref int dwResult) 
		public bool FSUIPC_Write(int dwOffset, int dwSize, ref byte[] param,
			ref int Token, ref int dwResult) 

	You supply an offset "dwOffset" identifying the data location as
	documented in "FSUIPC for Programmers.doc".  Your byte, short, int or long
	value in "param" will be written to FSUIPC.  The int pointer "dwResult"
	receives the result if the call fails, as indicated by the method's bool
	return value, with "TRUE" indicating success and "FALSE" indicating
	failure.  In the latter case, "dwResult" will identify the reason for
	error, with the only possible errors on these calls being an unopened link
	or a full data area.  You can only accumulate so much data before you need
	to get FSUIPC to "process" it. 	This is next:


Processing the requests
=======================

This one's easy - simply call:

	public bool FSUIPC_Process(ref int dwResult)
	
This routine sends all the requests accumulated using the Read and Write calls
since the last Process call (if any).  It is this call which actually operates
the interface.

As usual, the error number in the Result int needs to be checked if this
call returns FALSE, indicating an error.

Note that if your program is run under WideClient, it is likely that your
first requests for data are met with zeroes for everything. this is because
WideClient sends off the request but meanwhile returns what it already has.
If you depend on seeing correct data from the outset, you will need to wait
some milliseconds (100 or more is good, 500 safer) and read again.

If you are coninually reading the same data over and over in a loop, as when,
for instance, maintaining a moving map position and so on, the initial values
from Wideclient shouldn't be any bother. But remember, in loops, allow some
time for other processes to run, and also process your own Windows messages.


Getting returned values
=======================
If you submitted one or more READ requests before the Process call, you will
need to call one of the following overloaded methods to get the returned
result(s):

		public bool FSUIPC_Get(ref int Token, ref byte Result) 
		public bool FSUIPC_Get(ref int Token, ref short Result) 
		public bool FSUIPC_Get(ref int Token, ref int Result) 
		public bool FSUIPC_Get(ref int Token, ref long Result) 
		public bool FSUIPC_Get(ref int Token, int dwSize, ref byte[] Result) 

Token should reference the "key" returned from the Read request(s) above.
The method will return "TRUE" if successful and Result will contain your value.
If "FALSE" is returned then Result will contain the reason for the error.


Closing the link
================

Before terminating your program, or trying to re-open (e.g. to re-connect
after a lost connection, possibly due to FS crashing or closing), you must
Close the link to free up the resources it uses:

	public void FSUIPC_Close();
	
There is no harm done if you Close a link that is already Closed.

Note that FSUIPC_Initialization() not only closes the connection but also
goes on to re-initialize the Fsuipc instance for continued use, so it
is recommended you use it instead of FSUIPC_Close() for resets.

Example #1: Reading the Indicated Airspeed (IAS)
================================================

	using FsuipcSdk;				// Help Studio.NET find Fsuipc class
	
	Fsuipc fsuipc = new Fsuipc();	// Instantiate our Fsuipc object
	
	bool result = false;			// Return boolean for FSUIPC method calls
	int dwFSReq = 0;				// Any version of FS is OK
	int dwOffset = 0x02BC;			// Indicated airspeed memory offset
	int dwSize = 4;					// Indicated airspeed memory size
	int token = 0;					// Variable to hold returned token index
	int dwResult = 0;				// Variable to hold returned results
	
	// Optional initialization
	fsuipc.FSUIPC_Initialization();
	
	// Open the connection to FSUIPC (and thus the simulator)
	// if result == true then everything worked OK
	result = fsuipc.FSUIPC_Open(dwFSReq, ref dwResult);
	
	// Submit a single read request
	// if result == true then everything worked OK
	result = fsuipc.FSUIPC_Read(dwOffset, dwSize, ref token, ref dwResult);
	
	// Process (actually perform) the request
	// if result == true then everything worked OK
	result = fsuipc.FSUIPC_Process(ref dwResult);
	
	// Get the returned value
	// if result == true then everything worked OK
	result = fsuipc.FSUIPC_Get(ref token, ref dwResult);
	
	// Adjust the IAS value as per "FSUIPC for Programmers.doc"
	int ias = dwResult * 128;
		
	// Close the FSUIPC connection
	fsuipc.FSUIPC_Close();
	

Example #2: Moving the aircraft to Ohio State University Airport (KOSU)
            (Michigan and Miami fans should avert their eyes now)
=======================================================================

	using FsuipcSdk;				// Help Studio.NET find Fsuipc class
	
	Fsuipc fsuipc = new Fsuipc();	// Instantiate our Fsuipc object
	
	bool result = false;			// Return boolean for FSUIPC method calls
	int dwFSReq = 0;				// Any version of FS is OK
	int token = 0;					// Variable to hold returned token index
	int dwResult = 0;				// Variable to hold returned results
	
	// Optional initialization
	fsuipc.FSUIPC_Initialization();
	
	// Open the connection to FSUIPC (and thus the simulator)
	// if result == true then everything worked OK
	result = fsuipc.FSUIPC_Open(dwFSReq, ref dwResult);
	
	// Set slew mode on (required prior to location writes)
	// if result == true then everything worked OK
	result = fsuipc.FSUIPC_Write(0x05DC, 1, ref token, ref dwResult);

	// Set latitude
	// if result == true then everything worked OK
	result = fsuipc.FSUIPC_Write(0x0564, 4454206, ref token, ref dwResult);
	result = fsuipc.FSUIPC_Write(0x0560, 901120000, ref token, ref dwResult);

	// Set longitude
	// if result == true then everything worked OK
	result = fsuipc.FSUIPC_Write(0x056C, -991553537, ref token, ref dwResult);
	result = fsuipc.FSUIPC_Write(0x0568, 219480064, ref token, ref dwResult);

	// Write the data to FS
	// if result == true then everything worked OK
	result = fsuipc.FSUIPC_Process(ref dwResult);
		
	// Close the FSUIPC connection
	fsuipc.FSUIPC_Close();

Future Development
==================

	This version (1.0 - 01/05/2003) should be identical in feature to the
	VB.NET API and should satisfy most C#.NET developer's needs.  However,
	being a Java developer by day, I'm more comfortable with pure Object-
	Oriented (OO) APIs and I'm very interested in writing an OO version of
	this API.  If you have interest in this and/or are willing to help, please
	drop me an email.  I'm also of course interested in hearing about bugs,
	optimizations or about any of the cool things you've created with it!
	
	Thanks, and good luck! - Scott

Version History
===============
1.0   5 Jan 03  Original Release
1.1   9 Jan 04  Bug fix--IPC read buffer wraparound       (Bob Scott)
1.11  5 Mar 04  Bug Fix--FSUIPC_Write byte array function (Bob Scott)
1.13  6 Feb 06  Performance improvement in FSUIPC.CS by Paul Henty
		
==============================================================================
Scott McCrory <scott@mccrory.us> with many thanks to Pete Dowson for FSUIPC,
   Chris Brett for the VB SDK and Bob Scott for the VB.NET SDK rewrite.

