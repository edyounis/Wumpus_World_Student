// ======================================================================
// FILE:        Main.java
//
// AUTHOR:      Abdullah Younis
//
// DESCRIPTION: This file is the entry point for the program. The main
//              function serves a couple purposes: (1) It is the
//              interface with the command line. (2) It reads the files,
//              creates the World object, and passes that all the
//              information necessary. (3) It is in charge of outputing
//              information.
//
// NOTES:       - Syntax:
//
//                	Wumpus_World [Options] [InputFile] [OutputFile]
//
//                  Options:
//						-m Use the ManualAI instead of MyAI.
//						-r Use the RandomAI instead of MyAI.
//                      -d Debug mode, which displays the game board
//                         after every mode. Useless with -m.
//                      -h Displays help menu and quits.
//                      -v Verbose mode displays world file names before
//                         loading them.
//                      -f treats the InputFile as a folder containing
//                         worlds. This will trigger the program to
//                         display the average score and standard
//                         deviation instead of a single score. InputFile
//                         must be entered with this option.
//
//                  InputFile: A path to a valid Wumpus World File, or
//                             folder with -f. This is optional unless
//                             used with -f or OutputFile.
//
//                  OutputFile: A path to a file where the results will
//                              be written. This is optional.
//
//              - If -m and -r are turned on, -m will be turned off.
//
//              - Don't make changes to this file.
// ======================================================================

import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;

public class Main
{
    public static void main ( String[] args )
	{
		if ( args.length == 0 )
		{
			// Run on a random world and exit
			try
			{
				World world = new World();
				int score = world.run();
				System.out.println("Your agent scored: " + score);
			}
			catch ( Exception e )
			{
				e.printStackTrace();
			}
			return;
		}

		// Important Variables
		boolean debug        = false;
		boolean verbose      = false;
		boolean randomAI     = false;
		boolean manualAI      = false;
		boolean folder       = false;
		String	worldFile    = "";
		String	outputFile   = "";
		String 	firstToken 	 = args[0];

		// If there are options
		if ( firstToken.charAt(0) == '-' )
		{
			// Parse Options
			for ( int index = 1; index < firstToken.length(); ++index )
			{
				switch ( firstToken.charAt(index) )
				{
					case '-':
						break;
						
					case 'f':
					case 'F':
						folder = true;
						break;
						
					case 'v':
					case 'V':
						verbose = true;
						break;
						
					case 'r':
					case 'R':
						randomAI = true;
						break;
						
					case 'm':
					case 'M':
						manualAI = true;
						break;
						
					case 'd':
					case 'D':
						debug = true;
						break;
						
					case 'h':
					case 'H':
					default:
						System.out.println ( "Wumpus_World [Options] [InputFile] [OutputFile]" );
						System.out.println ( );
						System.out.println ( "Options:" );
						System.out.println ( "\t-m Use the ManualAI instead of MyAI." );
						System.out.println ( "\t-r Use the RandomAI instead of MyAI." );
						System.out.println ( "\t-d Debug mode, which displays the game board" );
						System.out.println ( "\t   after every mode. Useless with -m." );
						System.out.println ( "\t-h Displays help menu and quits." );
						System.out.println ( "\t-f treats the InputFile as a folder containing" );
						System.out.println ( "\t   worlds. This will trigger the program to" );
						System.out.println ( "\t   display the average score and standard" );
						System.out.println ( "\t   deviation instead of a single score. InputFile" );
						System.out.println ( "\t   must be entered with this option." );
						System.out.println ( );
						System.out.println ( "InputFile: A path to a valid Wumpus World File, or" );
						System.out.println ( "           folder with -f. This is optional unless" );
						System.out.println ( "           used with -f." );
						System.out.println ( );
						System.out.println ( "OutputFile: A path to a file where the results will" );
						System.out.println ( "            be written. This is optional." );
						System.out.println ( );
						return;
				}
			}
			
			if ( randomAI && manualAI )
			{
				// If both AI's on, turn one off and let the user know.
				manualAI = false;
				System.out.println ( "[WARNING] Manual AI and Random AI both on; Manual AI was turned off." );
			}
			
			if ( args.length >= 2 )
				worldFile = args[1];
			if ( args.length >= 3 )
				outputFile = args[2];
		}
		else
		{
			if ( args.length >= 1 )
				worldFile = args[0];
			if ( args.length >= 2 )
				outputFile = args[1];
		}
		
		if ( worldFile == "" )
		{
			if ( folder )
				System.out.println( "[WARNING] No folder specified; running on a random world." );
			try
			{
				World world = new World ( debug, randomAI, manualAI );
				int score = world.run();
				System.out.println ( "The agent scored: " + score );
			}
			catch ( Exception e )
			{
				e.printStackTrace();
			}
			return;
		}
		
		if ( folder )
		{
			File worldFolder = new File ( worldFile );
			File[] listOfWorlds = worldFolder.listFiles();
			
			if ( listOfWorlds == null )
			{
				System.out.println ( "[ERROR] Failed to open directory." );
				return;
			}
			
			int		numOfScores        = 0;
			double	sumOfScores        = 0;
			double	sumOfScoresSquared = 0;

			for ( int worldIndex = 0; worldIndex < listOfWorlds.length; worldIndex++ )
			{
				if ( verbose )
					System.out.println ( "Running world: " + listOfWorlds[worldIndex] );
				
				int score = 0;
				try
				{
					World world = new World ( debug, randomAI, manualAI, listOfWorlds[worldIndex] );
					score = world.run();
				}
				catch ( Exception e )
				{
					numOfScores = 0;
					sumOfScores = 0;
					sumOfScoresSquared = 0;
					break;
				}

				numOfScores += 1;
				sumOfScores += score;
				sumOfScoresSquared += score*score;
			}
			double avg = (float)sumOfScores / (float)numOfScores;
			double std_dev = Math.sqrt ( (sumOfScoresSquared - ((sumOfScores*sumOfScores) / (float)numOfScores) ) / (float)numOfScores );
			if ( outputFile == "" )
			{
				System.out.println ( "The agent's average score: " + avg );
				System.out.println ( "The agent's standard deviation: " + std_dev );
			}
			else
			{
				BufferedWriter out = null;
				try
				{
					FileWriter fstream = new FileWriter ( outputFile );
					out = new BufferedWriter ( fstream );
					out.write ( "SCORE: " + avg + '\n' );
					out.write ( "STDEV: " + std_dev );
				}
				catch ( Exception e )
				{
					System.out.println ( "[ERROR] Failure to write to output file." );
				}
				finally
				{
					try
					{
						if ( out != null )
						{
							out.close();
						}
					}
					catch ( IOException ioe )
					{
					}
				}
			}
			return;
		}
		

		if ( verbose )
			System.out.println ( "Running world: " + worldFile );
		
		File worldFileObject = new File ( worldFile );
		
		if ( !worldFileObject.exists() )
		{
			System.out.println ( "[ERROR] Failure to open file." );
			return;
		}
		
		int score = 0;
		try
		{
			World world = new World ( debug, randomAI, manualAI, worldFileObject );
			score = world.run();
		}
		catch ( Exception e )
		{
			System.out.println ( "[ERROR] Failure to open file." );
			return;
		}
		
		if ( outputFile == "" )
		{
			System.out.println ( "The agent scored: " + score );
		}
		else
		{
			BufferedWriter out = null;
			try
			{
				FileWriter fstream = new FileWriter ( outputFile );
				out = new BufferedWriter ( fstream );
				out.write ( "SCORE: " + score );
			}
			catch ( Exception e )
			{
				System.out.println ( "[ERROR] Failure to write to output file." );
			}
			finally
			{
				try
				{
					if ( out != null )
					{
						out.close();
					}
				}
				catch ( IOException ioe )
				{
				}
			}
		}
	}
}