# Tetris AI Environment

## Matt Brenman

This is my final project for the class Advanced Machine Learning at Tufts University, Fall 2014. It's a Tetris AI Environment that lets users define agents and easily plug them into the system. 

It's an easy way for ML/AI students to try building game-playing programs without having to worry about creating the game. Try it out!

![gameDesign](http://imgur.com/KGUyNOk)

The design of this system allows users to swap out the Agent module for their own creation and have it automatically work!

## Compiling and Running

Compiling should be really easy and has been tested on Mac and Linux machines. You can use the included compile script with the command `sh compile` in the top level of the repo.

This will make an executable called play, which can be run with `./play`

There is also a part of the compile script that compiles an executable called `train`, which was used for one of the Agents. This can be safely removed if wanted, or it can be totally ignored.

## Creating an Agent
Any user-defined agent needs to do three things:
 
- **Subclass Agent**
	
	This step is necessary because having an abstract superclass allows the game to interact with any Agent, since the public interface will be at least as rich in a subclass. This brings us to the next step:

- **Implement the two virtual functions**
 
	Agents are expected to do two things, which are:

	* Choose actions based on a board. This is declared in Agent.h (as shown below) and needs to be defined in any subclass.  
	```cpp
	virtual Action getAction(Tetris *board);
	```


	* Defining a destructor. This is needed so that the subclass destructor gets called, which may be necessary if any heap elements are created in the Agent that should be kept around as long as the Agent is around. If no destructor is needed, then an empty destructor still needs to be defined (since the superclass makes it a virtual function).  
	```cpp
	virtual ~Agent();
	```

- **Be placed in the `agents` directory**

	Ok, so this isn't actually required, but it keeps everything neat. The compile script includes the agents directory as an additional include path, so if you put it other than in there (or the top level), then you may need to change the compile script. If it's in the agents directory, then no changes need to be made to compile. How neat!

## Letting the Agent Play

Ok, so you've built a super cool Agent, but now you want to see how it does. Luckily, it's really easy to hook the Agent into the game architecture. Here are the steps:

- **Include the file in the Game.cpp file (top level of the repo)**

	The `Agent.h` file will already be included, along with other agent headers. You can remove the other agents if you wish, but there is no harm either way. Simply include your Agent's header with the others.

- **Instantiate the Agent**

	In `main` the Agent needs to be created. This can be done by changing the line 
	```cpp
	Agent *player = new SomeOldAgent();
	```
	to
	```cpp 
	Agent *player = new NewCoolAgent();
	```
	(assuming that your Agent class is called `NewCoolAgent`, which is a wonderful name).

That's it! Then you just need to compile and run the program.

## Actions

Here's where the system is not a perfect model of Tetris. In standard Tetris, a piece can move side to side under other pieces, do t-spins, have hard or soft drops, or not do anything (and the piece will slowly fall). This environment simplifies this so that Agents can be more easily created.

An Action is defined as a combination of a rotation and a drop column: 

- **A rotation**
	
	Any rotation (Clockwise, Counter-Clockwise, Flip, or None) can be applied to any piece.

- **A drop column**

	The column of the leftmost segment of the piece. Not all columns are valid in an action (if any segment of the piece would be off of hte board), but the board can be queried to find the maximum valid column. This is done with the function 
	```cpp 
	int highestValidColWithRot(Rotation rot);
	```

Once an action is sent, it is dropped in that column with that rotation until it hits and sets with the rest of the board. This may make strategy slightly different, but I felt that it was similar enough that the benefit of simpler agents justified the change.

## Simulated Boards (and Board Statistics)

Once an action is played on a board, it cannot be unplayed. To test out multiple actions, however, it's super useful to see what they would do if they were played. This can be done by making an unofficial copy of the board, which is done as follows:

```cpp
Tetris *simulatedBoard = realBoard->gameCopy();
```

This board can have actions sent to it the same way, and then can be queried to see different statistics about it:

```cpp
//How many lines have been cleared on this board
simulatedBoard->getLinesCleared();
//What is the highest row that has a non-empty piece
simulatedBoard->maxBoardHeight();
//Has the game been lost
simulatedBoard->isLost();
```

The simulated board keeps the same information as is known with the real board, which includes the current and next piece, the setup of the board, as well as the number of lines already cleared. Any future pieces, however, will be randomly generated and will not necessarily be the same as will happen on the real board. This means that the Agents cannot get extra information by pinging a simulated board.

## Example Agents

There are multiple agents already defined in the `agents` directory, and they are described more fully in the paper in the repo.

##Troubleshooting
* Open an issue with GitHub's issue reporting system
* Send me an email at mattbrenman@gmail.com

## Author

mbrenman, mattbrenman@gmail.com

## License

This project is available under the MIT license. See the LICENSE file for more info.


