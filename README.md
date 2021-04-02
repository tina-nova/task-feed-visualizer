# task-feed-visualizer
Task Feed Visualizer / Viewer, a simple Qt-based kanban visualizer for daily task items. Licensed mostly as CC-BY-SA due to some borrowed code.

#### Usage: 

		tfv.exe "C:\your-task-directory-here"
    

 - Can also be run from the current directory
 
 - The program uses cross-platform libraries, so it should be compilable in any other platform. This was actually written and compiled from qtcreator inside a WSL setup so it should work in Linux if you have the right dependencies!
 
 - I will eventually update this readme with the dependencies I used, but I think it was just regular QT including C++ filesystem libraries. It also uses a modified version of [the alphanum algorithm](http://www.davekoelle.com/alphanum.html) which is released under the MIT license, a copy of which you will find in alphanum.hpp.
 
 &nbsp;

#### Syntax and Structure

##### Directories

The program follows a very specific way of organizing tasks by directory. The executable's working directory must be at the root of a "month" directory, and subdirectories must be per day. Additionally, each daily task within each subdirectory must be a .txt file that uses "Task Feed - Month Day.txt" as its file name.

An example directory to show how this works will be uploaded at a later date, when I have more time to do so, but for now it should basically go as follows:

    February 2020 \ tfv.exe
	
    February 2020 \ Assigned 10 February 2020 \ Task Feed - 10 February.txt
	
##### Task Feed Files

The tasks inside the text file itself use a very specific format, a sample of which is as follows:

    ----------
   
    FROM:[ROLE]PERSON1
	
    task1 description here
	
    [UPDATE2JANUARY: update]
	
    STATUS:ONHOLD;AWAITINGFEEDBACK
    PRIORITY:LOW

    ----------
	
    FROM:[ROLE]PERSON2
	
    task2 description here
	
    STATUS:NOTSTARTED;MOVEDTOTOMORROW
    PRIORITY:NORMAL/HIGH
	
    ----------
	
    FROM:
	
Dividing lines are needed, but only once between tasks. A minimum of five dashes are required to activate the program's detection code for a new task. 

"FROM" can use any name, but I personally like using brackets to denote position/department/etc and then add the name you would call them by. Note that the third "FROM" in the example above will be ignored by the visualizer as it is empty.

The description can contain anything EXCEPT "STATUS" in all caps, as that is how the program detects when the description section is done. \[UPDATES] as used in the sample above is just how I add updates and is not detected by the program as anything else except as plaintext.

"STATUS" can contain three different statuses: Primary, Secondary, and Moved. They are separated only by semicolons.
 
 - Primary can be any of the following:
 	- NOTSTARTED
	- ONHOLD
	- ONGOING
	- DONE
	- CANCELED
	
	Note that "CANCELED" does not have its own column due to lack of space and is instead placed under "NOTSTARTED"
	
 - Secondary can be any status, but here are my most common:
 
 	- For ONHOLD:
		- AWAITINGFEEDBACK
		- AWAITINGFURTHERINSTRUCTION
		- AWAITINGDEVICE
		- AWAITINGACCESS
		- UPDATING
		- COMPILING
		- AWAITINGDEPENDENCY
		
	- For NOTSTARTED:
		- AWAITINGDEPENDENCIES
		
- "MOVED" is a special status that overrides all the other statuses and places it under the "MOVED" column in the viewer. It can be placed as a primary, secondary, or even third status, and can use any word after "MOVED" to denote when it should be moved to. Just make sure you create a new text file with that specific date!

	 - Some examples:
 		- MOVEDTOTOMORROW
		- MOVEDTOMONDAY
		- MOVEDTOWEDNESDAY
		- MOVEDTO5MARCH2021
		
"PRIORITY" has only six valid statuses, the first three of which are automatically colored with red:

- ASAP
- URGENT
- HIGH
- NORMAL/HIGH
- NORMAL/MEDIUM
- NORMAL/LOW
- LOW
	
	They are sorted automatically in each column.

---------

Planned far-future features:

- Built-in text editor that automatically highlights the cells based on what's being edited : Hopefully before v2.0.0
- ~~Automatic refresh (currently you need to restart it manually to reload the new tasks) : Hopefully before v0.5.0~~ Implemented in v0.1.3
- More flexible directory structures : Hopefully before v2.0.0
- ~~GUI-based directory assignment : Hopefully before v0.6.0~~ Implemented in v0.1.3
- Drag and drop item sorting : Hopefully before v3.0.0

	

