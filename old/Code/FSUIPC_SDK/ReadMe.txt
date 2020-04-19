FSUIPC Developer's Kit           February 2012 revised June 2017
===========================================================================

For FS2004 or before you will need FSUIPC.ZIP as well with FSUIPC3 Version
3.999 or later, and for FSX you need FSUIPC4.ZIP with FSUIPC4 Version 4.80
or later. Many of the facilities described in the
Programmer's Guide need the latest versions.

For FSUIPC5, whgich is 64-bit, you can still interface your 32-bit external 
programs, but internal module users should use the ModuleUser64 library. A
64-bit library is also provided for external 64-bit programs interfacing to
FSUIPC5 (only) and also a 64-bit "Hello" demo for it.

Network users will need WideFS version 6.75 or later, WideClient 6.86
or later. There is no 64-bit version of WideClient.

Changes in this Release are many. Please always peruse the relevant FSUIPC
History document (available in the FSUIPC Zips).


IMPORTANT NOTE FOR FS GAUGE AND MODULE WRITERS
==============================================

If you are wanting to access FSUIPC's facilities from INSIDE FS, rather
than from an external application, please PLEASE note that using the
external users library is most definitely NOT recommended. It is VERY
inefficient. You are inside the FS process, so why use complex
inter-process communications? (IPC == Inter-Process Communication!).

Also, if you do use this slow method, you may get failures on Open which
will recover, eventually, on retries. This is because, following Adam
Szofran's original method, the "unique" ID string, used to identify the
mapped memory, is generated using the Process ID. This ID is unique for
all separate Processes, but obviously it is the same for ALL gauges and
modules running inside FS.

FSUIPC deliberately provides an entry for Gauges and Modules to use.
It is very efficient, it uses a simple message with no memory mapping.
YOU, the user, have to provide the memory for the data, but there are
simple rules for calculating how much. The code is almost identical to
using the external library -- only the Open call is changed to provide
the memory pointer and size!

Please see the "Library for FS Internal Users" ZIP. This has recently
been revised to work from threads other than the main FS thread, and
needs FSUIPC version 3.40 or later. There's also an "internal.pas"
file inlcuded which can be used by those making DLLs in Delphi. (Thanks
due to Michael "Iznogoud" for this contribution).


Contents of SDK
===============

NOTE that not all the parts have been updated for FS2004, FSX or ESP.
The only real change usually is the definition of:

	SIM_FS2K4 as number 7 (FS2K2 was 6).
	SIM_FSX as number 8
	SIM_ESP as number 9
	SIM_P3D (for Prepare3D) as number 10
	SIM_P3D4(64-bit) is number 12.

Number 11 is reserved in case a 64-bit version of FSX is supported.

Readme.txt
	This is it.

FSUIPC for Programmers.pdf
	General information and reference tables
	
FSUIPC4 Offsets Status.pdf
	Specific details of FSUIPC4 offsets, detailing all the
	differences (and additional values) to those for previous
	releases and documented in "FSUIPC for Programmers".
	
Library for FS Internal Users
	A special version of the library for internal FS parts like
	gauges and other modules to read and write FSUIPC
	data. Use with FSUIPC 3.40 and later.
	
	A revised version of the LIB file has been kindly donated
	by PhilippM, who also provided a revised FSUIPC_User.lib.
	
Library for 64-bit P3D4 Internal Users
  see ModuleUser64.zip

UIPCAWI.zip
	Some basic information about the FSUIPC Advanced 
	Weather Interface. This is only applicable to FS2000-4 and
	CFS2. It is not being developed. For FS2004 (and later?)
	see the New Weather Interface Zip.
	
New Weather Interface for FS2004.zip
	This contains a C header file and a description of the New
	Weather Interface provided for FS2004. It allows reading of 
	localised weather by location or station ID, and setting of
	localised weather by station ID. The whole interface is memory
	mapped and so is far easier to understand and use that was
	the "Advanced Weather Interface" (AWI) devised for FS2002.
	
FSUIPC Feedback Control.txt
	This is preliminary documentation for the feedback flight 
	control facilities offered by FSUIPC through offsets 0700 ff.

===========================================================================
Interfacing in different computer languages
	Each of these Zips contains the stuff you need to write your own
	appplication interfacing to FS through FSUIPC. A ready compiled
	example, basically an FSUIPC version of the standard simple
	"Hello World" program, complete  with source, is provided in
	each case.

FSUIPCDotNetClient2.0.zip
	A client DLL for use with Microsoft .NET languages. Supplied
	by Paul Henty.
UIPC_SDK_C.zip
	The Library and source for MSVC/C++ users, by yours truly. This is
	updated to handle FS2004 and also includes its own Access Key
	registration code, writing it to offset 0x8001 (no longer needed).
UIPC64_SDK_C.zip
  is the 64-bit version for C/C++.
UIPC_SDK_CSHARP Revision 1.13.zip
	All the details and examples for C# users, thanks to Scott McCrory
	with later amendments by Bob Scott.
UIPC_SDK_MFC.zip
	Sources and data for C++ MFC users, supplied by Brent Vernon.
UIPC_SDK_Delphi.zip
	Sources and data for Delphi users, supplied by Pelle Liljendal, with
	update work done by Chris Brett.
UIPC_SDK_VisualBasic.zip
	Sources and data for VB users, supplied by Chris Brett, with update
	work done by Enrico Schiratti and notes from Stuart Browne and a
	contribution from Mark Schilberg.
UIPC_SDK VB .NET Shell Revision 2.004.zip
	A revised version of the Visual Basic interface for VB.NET, kindly
	supplied by Bob Scott.
UIPC_SDK_ASM.zip
	Sources and data for ASM users, supplied by Andrea Brunori.
UIPC_SDK_JAVA.zip
	Java sources for Class-based access to FSUIPC, hard work kindly
	contributed by Mark Burton.
UIPC_SDK_BCB5.zip
	This is a version of the C example code revised and compiled
	with Borland C++ Builder 5: supplied by Alan Dyer.
UIPC_RealBasic_SDK.zip
  Kindly donated by Rafael Vallejo (www.goldwaresoft.com).
UIPC_SDK_Python.zip
  Kindly donated by István Váradi (ivaradi@gmail.com)
  
===========================================================================
Other utilities

FSInterrogate2std.exe
FSI2 Manual.pdf
	A very useful program written by and copyright (c) Pelle Liljendal.
	This is completely revised and now includes many useful facilities
	excellent display and conversions options. It will also run on an
	unregistered FSUIPC installation. Thank you Pelle!
FSUIPC.fsi
	A database/project for use with FSInterrogate2 (NOT the previous
	version!) and which includes most if BUT not all of the data in the
	tables in the Programmers and FSUIPC4 Offsets documents. Do NOT use
	this as your prime Offset reference. It is not always correct and is 
	certainly not updated anywhere near as often.
	
===========================================================================
Peter Dowson, 27th February 2012, revised 21st June 2017

with thanks to Paul Henty, Scott McCrory, Bob Scott, Stuart Browne,
Andrea Brunori, Brent Vernon, Pelle Liljendal, Mark Burton,
Enrico Schiratti, Chris Brett, Mark Schilberg, Alan Dyer, Rafael Vallejo
PhilippM, and István Váradi.
===========================================================================
