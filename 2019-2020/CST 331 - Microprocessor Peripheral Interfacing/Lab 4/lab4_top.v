module lab4_top(
input EBICS0,		 //CS line from EBI
output CE2			 //Inverted CS line
);

/* Note that the Sidewinder's Seven Segment socket should not be populated
because its pins (with the exception of the SEG5 output), are shared with the
J1 IO header */

/* To use this template, create a new project. Set the device to 5M160ZTC5. 
Copy the contents of this file to your own top level module and CHANGE THE
MODULE'S NAME to match your project name. Then import the Sidewinderfor331new.qsf 
file. When importing (Assignments>Import Assignments) after selecting the qsf
file, click on the Advanced button and then tick the Import Global Assignments
setting. Check that the system messages panel reports that 45 assignments were
written and that 0 non-global assignments were skipped.
If you want to re-import the qsf file, you will either need to uncomment the
TOP_LEVEL_ENTITY assignment and edit to match your top level module's name, or you
will need to clean the project (Project > Clean Project) before importing. 
Importing Sidewinderfor331new.qsf will provide pin assignments for the switches
and LEDs on the sidewinder board. 
Then, add statements describing the additional inputs and outputs your design
will use. Using the assignments editor (Assignments > Assignments Editor) or the
pin planner (Assignments > Pin Planner), you will have to provide pin assignments
for any additional inputs and outputs that you specify, chosing from the 
sidewinder's J1 GPIO header pins (see the Sidewinder documentation for the pin
numbers). The default IO standard for these pins should be 3.3-V LVCMOS.  
Note that the qsf file also contains a global assignment statement that
designates all unused pins a tri-stated inputs. */

assign CE2 = ~EBICS0;

endmodule

