#ifndef MAIN_H_
#define MAIN_H_

#endif

#ifndef _MAIN_DOCUMENTATION_H_
#define _MAIN_DOCUMENTATION_H_
/**
\mainpage CFW10 Interface Firmware
<CENTER>Copyright &copy; 2015 by Arthur Farias
</CENTER>

\section Intro Introdução

Esta é uma implementação mínima de uma interface gráfica baseada em
LCD 16x2 e Keypad para programação de um inversor de freqüência CFW10

\section Building Requirements

\section Building Steps

\note
  The Arduino Print class uses character at a time writes so it was necessary
  to use a \link SdFile::sync() sync() \endlink function to control when data
  is written to the SD card.

\par
An application which writes to a file using \link Print::print() print()\endlink,
\link Print::println() println() \endlink
or \link SdFile::write write() \endlink must call \link SdFile::sync() sync() \endlink
at the appropriate time to force data and directory information to be written
to the SD Card.  Data and directory information are also written to the SD card
when \link SdFile::close() close() \endlink is called.

\par
Applications must use care calling \link SdFile::sync() sync() \endlink
since 2048 bytes of I/O is required to update file and
directory information.  This includes writing the current data block, reading
the block that contains the directory entry for update, writing the directory
block back and reading back the current data block.

It is possible to open a file with two or more instances of SdFile.  A file may
be corrupted if data is written to the file by more than one instance of SdFile.

\section HowTo How to format SD Cards as FAT Volumes

You should use a freshly formatted SD card for best performance.  FAT
file systems become slower if many files have been created and deleted.
This is because the directory entry for a deleted file is marked as deleted,
but is not deleted.  When a new file is created, these entries must be scanned
before creating the file, a flaw in the FAT design.  Also files can become
fragmented which causes reads and writes to be slower.

Microsoft operating systems support removable media formatted with a
Master Boot Record, MBR, or formatted as a super floppy with a FAT Boot Sector
in block zero.

Microsoft operating systems expect MBR formatted removable media
to have only one partition. The first partition should be used.

Microsoft operating systems do not support partitioning SD flash cards.
If you erase an SD card with a program like KillDisk, Most versions of
Windows will format the card as a super floppy.

The best way to restore an SD card's format is to use SDFormatter
which can be downloaded from:

http://www.sdcard.org/consumers/formatter/

SDFormatter aligns flash erase boundaries with file
system structures which reduces write latency and file system overhead.

SDFormatter does not have an option for FAT type so it may format
small cards as FAT12.

After the MBR is restored by SDFormatter you may need to reformat small
cards that have been formatted FAT12 to force the volume type to be FAT16.

If you reformat the SD card with an OS utility, choose a cluster size that
will result in:

4084 < CountOfClusters && CountOfClusters < 65525

The volume will then be FAT16.

If you are formatting an SD card on OS X or Linux, be sure to use the first
partition. Format this partition with a cluster count in above range.

\section  References References

Adafruit Industries:

http://www.adafruit.com/

http://www.ladyada.net/make/waveshield/

The Arduino site:

http://www.arduino.cc/

For more information about FAT file systems see:

http://www.microsoft.com/whdc/system/platform/firmware/fatgen.mspx

For information about using SD cards as SPI devices see:

http://www.sdcard.org/developers/tech/sdcard/pls/Simplified_Physical_Layer_Spec.pdf

The ATmega328 datasheet:

http://www.atmel.com/dyn/resources/prod_documents/doc8161.pdf


 */
#endif
