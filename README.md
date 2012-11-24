Old-Projects
============

Old school and hobby projects from over ten years ago.

Updated project descriptions can be found here: http://www.fieldman.org/projects/



Underground Caverns
-------------------

I took my first programming class in eighth grade, 1993. We used Pascal. I was a total newb. I didn’t know what an array was. I didn’t know what a pointer was. By the end of ninth grade I was making some fairly cool stuff. Witness the Underground Caverns, my ninth grade programming project.

This game began my unerring streak of being completely unoriginal and making games that already existed in other media. I owned the board game Hero Quest, which was pretty epic, and I thought it would be a great platform to reproduce. Those familiar with the original board game may recognize the stairs and level layout in the second screenshot.

I had zero knowledge of graphics programming, so the whole thing was done with ASCII characters on the 80×25 terminal. Hilarious. I still have the source and executable; it’s even more hilarious.

To give 14-year-old-me credit, I actually had a working line-of-sight engine, so you couldn’t see past doors or around corners.


F-15 Strike Team
----------------

After The Underground Caverns, I was king of the world. I could make anything. I needed a new challenge, a new program to write over summer vacation.

The divine inspiration for my next masterpiece came at David Frank’s house. Again, having no creativity of my own, I resorted to copying a cool board game that we would play. The basic gameplay of F-15 consists of flying your planes over the “radar” board and shooting down the other player’s planes using dice and missiles. Hey, it was fun back then.

This game was also written in Pascal and the source is pretty crazy/unreadable. Not to mention the fact that I never got around to implementing a quit feature, so execute the program at your own risk.


Destiny
-------

Destiny was my leap from ASCII art to “real” graphics. I wrote this bad boy for a tenth-grade class assignment. Our task was to use a queue data structure any way we wanted. I wrote a bitmap library that used a queue to store picture data – probably the least appropriate way to use a queue or write a bitmap library.

At the time I had a very immature idea of how the VGA card worked and ended up brute-forcing most of the code. Also, it appears that whatever frame timing i used was optimized for the 486 computers we had in our lab; it’s too fast on new machines.

Despite my (relatively) impressive graphics, the gameplay was lacking. It was painfully obvious that Destiny would never be the crowd-pleaser that Albert Kuo’s circle-and-square Bomberman  clone was.

I attempted to expand the Destiny franchise with Destiny 2. I wrote smoother graphics code and the keyboard was more responsive. It never really got off the ground, and i was left with a fly-your-plane-through-empty-space game.


GoGL
----

GoGL has quite a history. When I first started programming with OpenGL I attempted to write a 3D Go game. The first version of GoGL was pretty good. It had a nice board and some cool effects, but i never got around to coding the actual game mechanics.

The game sat idle for a year or so. Our CS184 final project was to make a “3d thing” of our choice, and it was the perfect opportunity to work on GoGL again. The finished product is coded by me, except for sound (sound.cpp, etc.) which was coded by my partner Albert.

Gameplay is fairly intuitive. If you don’t already know how to play Go, search google for some online instructions. The game ends when both players pass in a row.


3D Graphing
-----------

Sometime in 2000 I was sort of challenged to make a cool graphing calculator application. It’s a stupid story, but this program is the end result. I know it’s horribly under-featured (fixed axis, no scaling, poor painting refresh, no options, etc) but i had never intended this for public use.

Probably the hardest part was making the equation parser/interpreter. In retrospect, I did a horribly messy and inefficient job with it, but it works. The graphics were surprisingly easy.

For now, I think it supports abs, sin, cos, tan, asin, acos, atan, log, ln, +, -, *, /, ^ and maybe some others I’m forgetting.


Squared
-------

Back in early 2001 I fell pretty ill. The kind of sickness where you’re too nauseous to walk and you shove a kleenex up each nostril. Stuck in front of the computer, I decided to write a game.

I got the idea for Squared a long long time ago when I played a version of it on AOL. I decided it could use an OpenGL upgrade, and this is what i came up with.

It didn’t turn out quite as nice as i had hoped. This was my first experiment with winsock + opengl, so I was experimenting a lot. I wasn’t really paying attention to coding style; just trying to get it functional. When a given feature would work I was too impatient to go back and clean up what i had done.

So I got a pile of code that did approximately what I wanted it to, but was really a pain in the ass to sort through and modify. When I decided I didn’t like how the game looked it was too late to change it into something cooler, let alone try to add features. Also, I think I violated every rule of network programming.

Whatever. It was done, and it was playable.

To serve, enter your name and press the “begin server” button. The game will wait for someone to connect. To connect, enter your name and the IP of the server and press the connect button. You can talk by typing into the field on the bottom and pressing enter. You can rotate the board by dragging the right mouse button.

Players take turns putting down one peg at a time. When four of your pegs form the vertices of a square, you get (length of side+1)^2 points. For example, a square with vertices on the border of board is worth 64 points, while the smallest square you can make is worth 4 points. Squares can be tilted (see screenshots).

In my version, the first player to reach 150 points wins. To start a new game, press the connect button. The board will reset and the other player will start the next round.

Squared got a mention on the opengl.org blog. For some reason this was a big deal to me.


Mandelbrot
----------

During one of my many Slashdot refreshes (circa 2001) I came across an article about the mandelbrot set. I was intrigued by how simple it was, and decided to make my own viewer.

That evening I wrote the program from 9pm to 2am in one sitting, so it’s really not that high quality or special. I tried to beef it up with some extra options but didn’t really get too far. All I had time to implement was:

* zoom in by drawing a box on the screen
* variable colors
* variable precision
* undo last view change
* reset the view to the beginning
* zoom out
* realign, in case you distort while zooming

That’s it. It’s actually pretty cool what kind of patterns you can find.


Random Art
----------

Colors can be represented by different amounts of red, green and blue. The random art generator graphs each of these three values determined by a randomly generated mathematical function inside of a bounded 2D plane. The equation for each picture is printed above it.

Sometimes math is boring, and sometimes it’s very interesting. This is reflected in the different kinds of pictures you’ll see. Since the equations are generated completely randomly, there is no guarantee that an interesting picture will be created.


Complex Graphing
----------------

I took Math 185 in the fall of 2001. It dealt with complex numbers and a bunch of other stuff like e^πi + 1 = 0.

When you graph a normal function like “f(x) = 2x+1″ you can use a normal cartesian coordinate system because you’re dealing with R->R. Since complex functions are C->C, the graph of a complex equation is really an image from one two-dimensional coordinate system to another.

Drawing these images is a hard because they’re usually very unintuative. you have to calculate a crapload of different points and try figure out what it’s supposed to look like.

It’s pretty easy to use the program. Enter the complex function into the top edit box (look at the sample screenshots to see examples). Remember that the complex function uses “z” as the variable (z = x + iy).

Once the complex function is entered, you can do two things: 1) just click the “Recalculate” button or 2) enter a standard real-valued function of x into the second edit box and press the “Recalculate” button.

If you don’t enter a second function, the program will create a blanket that covers the entire right graph. This blanket is then translated onto the second graph by using the complex equation. If you do enter a second function the program will just translate the function you entered.

After calculating, you can draw on the left graph by dragging the left mouse button and see how the drawing is imaged to the right graph. You can move the graphs by dragging the right mouse button, and zoom with the buttons below.

There’s probably a lot of extra cool things i could have done with this program, but since no one on Earth will ever care about this I didn’t bother.


Galaxy Simulation
-----------------

In 2003, my friend Nick and I had been talking about space games (Master of Orion, Space Empires, etc) and how most of them use a 2D mapping system. Well, if i was ever going to write a 4X space game it would definitely have to be set in a 3D environment.

So to see if this was even plausible I spent a weekend and came up with a model of how a 3D galaxy could look. It’s probably the worst galaxy simulation program ever written. Bite me.