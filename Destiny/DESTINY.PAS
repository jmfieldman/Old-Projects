{
DESTINY

BY JASON FIELDMAN

APCSAB PERIOD 7


}
Program Destiny;
uses
    crt,
    vgaunit,     {For Pixel Manipulation}
    mouselib,    {For Mouse Use}
    dos,
    QueueADT;    {Queue ADT}

Const

     BlackC = 0;    {Color of Black}
     DarkGC = 20;   {Pixel Value of Dark Gray}
     LightGC = 26;  {  "     "   "  Light  "}
     WhiteC = 30;   {  "     "   "  White}

     Ship1Score = 60;
     Ship2Score = 120;
     Ship3Score = 195;
     Ship4Score = 350;

	NextBonusValue = 500;  {Score needed to gain bonus}

     Xmin = 0;       {Xmin, Xmax, Ymin, and Ymax for 320x200}
     Xmax = 319;
     Ymin = 0;
     Ymax = 199;

     MaxBullet = 40;  {Max Bullets on screen at one time}
     MaxEnemy = 20;   { "  Enemies "    "     "  "   "}
     MaxExp = 15;     { "  Explosions " "     "  "   "}


     vga = $a000;     {Used in VGA Unit}
     MaxStars = 50;   {Max Stars per Distance level}
     Path = '';
     ShipFilePath = Path + 'ShipPic.Dta';
     Bullet1path = Path + 'Bullet1.dta';
     Bullet2path = Path + 'Bullet2.dta';
     Bullet3path = Path + 'Bullet3.dta';
     Bullet4path = Path + 'Bullet4.dta';
     EnemyShtpath = Path + 'EnemySht.dta';
     Enemy1Path = Path + 'Enemy1.dta';
     Enemy2Path = Path + 'Enemy2.dta';
     Enemy3Path = Path + 'Enemy3.dta';
     Enemy4Path = Path + 'Enemy4.dta';
     Exp1Path = Path + 'Explos1.dta';
     Exp2Path = Path + 'Explos2.dta';
     Exp3Path = Path + 'Explos3.dta';
     Exp4Path = Path + 'Explos4.dta';
     TitlePath = Path + 'Title.Dta';          {Paths for files}
     Opt5000Path = Path + '5000opt.dta';
     scorePath = Path + 'Score.dta';
     zeropath = Path + 'zero.dta';
     onepath = Path + 'one.dta';
     twopath = Path + 'Two.dta';
     ThreePath = Path + 'Three.dta';
     FourPath = Path + 'Four.dta';
     FivePath = Path + 'Five.dta';
     SixPath = Path + 'Six.dta';
     SevenPath = Path + 'Seven.Dta';
     EightPath = Path + 'Eight.dta';
     NinePath = Path + 'Nine.Dta';
     NamePath = Path + 'Name.Dta';
     LevelPath = Path + 'Level.Dta';
     CreditPath = Path + 'credits.dta';
     PausePath = Path + 'pause.dta';







Type


{VGA UNIT STUFF}
    Virtual = Array [1..64000] of byte;  {Virtual screen}
    VirtPtr = ^Virtual;

{STAR TYPE}
    StarRecord = Record
       X,Y: integer;
    end;

    StarArray = array[1..MaxStars] of StarRecord;

    StarType = Array[1..3] of StarArray;
{HIGH SCORE TYPE}
    ScoreType = Record
       Name: string;
       Score: longint;
       Pos: integer;
    end;



{LEVEL TYPE}
    LevelType = QueueType;

{HIT TYPE}
{Hit Type stores all the booleans of whether or not a sprite has been hit}
    HitType = Record
       Ship: boolean;
       Bullet: array[1..MaxBullet] of boolean;
       Enemy: array[1..MaxEnemy] of boolean;
    end;

{SHIP TYPE}
    ShipType = Record
	  X: integer;          {X-Coordinate}
	  Y: integer;		   {Y-Coordinate}
	  Shield: integer;	   {Shield Level}
	  FireRate: integer;   {FireSpeed}
	  LastShot: integer;   {When you took your last shot}
	  Ammo: integer;	   {Your ammo power}
	  Graphics: QueueType; {Graphics for your ship}
	  Dead: Boolean;	   {Are you dead?}
    end;
{SHIP TYPE}

{ENEMY TYPE}
    EnemyRecord = Record
	  X: integer;          {X-Coordinate}
	  Y: integer;		   {Y-Coordinate}
	  LastShot: integer;   {When The enemy last shot...not used now...}
	  Data: integer;	   {The type of enemy it is}
	  Active: Boolean;     {Is is alive?}
    end;

    EnemyArray = array[1..MaxEnemy] of EnemyRecord;

    EnemyGraphics = array[1..4] of QueueType;

    EnemyType = Record
	  Data: EnemyArray;
	  Graphics: EnemyGraphics;  {Enemy Graphics}
    end;
{ENEMY TYPE}

{BULLET TYPE}
    BulletRecord = Record
	 X: integer;         {X-Coordinate}
	 Y: integer;         {Y-Coordinate}
	 Active: Boolean;    {Is it alive?}
	 Data: integer;      {What type of bullet}

    end;

    BulletArray = Array[1..MaxBullet] of BulletRecord;

    BulletGraphics = Array[1..5] of QueueType;

    BulletType = Record
      Data:  BulletArray;
	 Graphics:  BulletGraphics;  {Bullet Graphics}
    End;
{BULLET TYPE}

{EXPLOSION TYPE}
    ExplosionRecord = Record
	  X: integer;           {X-Coordinate}
	  Y: integer;		    {Y-Coordinate}
	  Active: Boolean;	    {Is it alive?}
	  Phase: integer;	    {Which explosion graphic to show}
    end;

    ExplosionArray = Array[1..MaxExp] of ExplosionRecord;

    ExplosionGraphics = Array[1..3] of QueueType;

    ExplosionType = Record
      Data: ExplosionArray;
	 Graphics: ExplosionGraphics; {Graphics}
    end;
{EXPLOSION TYPE}

{MISC TYPE}
    MiscGraphics = Record
      Name,Zero,One,Two,three,four,five,six,seven,eight,
	 credits,nine,opt5000,score,pause: QueueType;

		{These are the miscelaneous pictures that are shown throughout
		 the game.}

    end;

{NECESARY GLOBAL VARS}
{These are used by my VGA unit, and MUST be global...but they are not
accessed like normal variables, so it's an exception}
VAR
   Virscr:       VirtPtr;
   Vaddr:        word;




{==================================================================}
{==================================================================}
{==================================================================}
procedure NOCURSOR; Assembler;
{This Procedure Makes no cursor blink on the screen}
asm
   mov ah, 01
   mov cx, 02000h  {Something in assembly?}
   int 10h
@@1:
end;
{==================================================================}
{==================================================================}
{==================================================================}
Procedure InitVirtual;
{Makes the virtual screen black}
var
   x,y: integer;

begin                                    {Turns every pixel black}
	For x := Xmin to Xmax do begin
	    For y := Ymin to Ymax do begin
             VPP(x,y,0);
         end;
     end;
end;
{==================================================================}
{==================================================================}
{==================================================================}
Procedure DisplayPic(Pic: QueueType; x,y: integer; var Hit: boolean);
{Displays a pic at X,Y, and returns Hit if the pic encounters anything}
var
   TmpPic: QueueType;
   Element: QueueElementType;
begin
	TmpPic := Pic;  {Load a TempQueue}
	Hit := False;	 {Not hit yet...}
     repeat
	   Dequeue(TmpPic, Element);  {Dequeue the Element from the Temp Queue}
        If (Element.X+X>=Xmin) and (Element.X+X<=Xmax) and (Element.y+y>=Ymin) and (Element.Y+y<=Ymax) then begin
		 {Only put pixel if on screen}
		 {Also check for no pixel there already}
		 If (GetPixelVPP(Element.X+X,Element.Y+Y) <> BlackC) AND
		    (GetPixelVPP(Element.X+X,Element.Y+Y) <> DarkGC) AND
		    (GetPixelVPP(Element.X+X,Element.Y+Y) <> LightGC) AND
		    (GetPixelVPP(Element.X+X,Element.Y+Y) <> WhiteC) then Hit := True;
	   VPP(Element.x+x, Element.y+y, ELement.Data);  {Put Pixel on virtual}
	   end;
	until EmptyQueue(TmpPic); {Repeat until Temp Queue is EMPTY}
end;
{==================================================================}
{==================================================================}
{==================================================================}
Procedure InitializePic(var Pic: QueueType; Path: String);
{Reads the file and puts the data in the Queue}
var
   x,y,data: integer;
   done: boolean;
   Element: QueueElementType;
   PicFile: Text;

begin
   CreateQueue(Pic);       {New Queue!}
   Assign(PicFile, Path);  {Assign the file to the correct data file}
   Reset(PicFile);		  {Duh....}
   done := false;		  {Initialize Done}
   repeat

	 read(Picfile, x);
	 read(Picfile, y);           {Read in data from a line in the file}
	 readln(Picfile, data);
	 if x=999 then done := true;  {Until 999 is encountered}
	 if x<>999 then begin
	    Element.x := x;
	    Element.y := y;
	    Element.data := data;
	    EnQueue(Pic, Element);  {Enqueue the data to the queue}
	 end;

   until done;
   Close(PicFile);      {Close the file...}
end;
{==================================================================}
{==================================================================}
{==================================================================}
Procedure Fadeln(Line: String);
{Fade in and out text}
{Self-Explainatory}
begin
    clrscr;
    delay(75);
    textcolor(darkGray);
    gotoxy(39-(Ord(Line[0]) div 2),12);
    writeln(Line);
    delay(75);
    textcolor(lightGray);
    gotoxy(39-(Ord(Line[0]) div 2),12);
    writeln(Line);
    delay(75);
    textcolor(white);
    gotoxy(39-(Ord(Line[0]) div 2),12);
    writeln(Line);
    if Line = 'From an Alien Invasion.' then delay(750);
    delay(2550);
    textcolor(lightGray);
    gotoxy(39-(Ord(Line[0]) div 2),12);
    writeln(Line);
    delay(75);
    textcolor(darkGray);
    gotoxy(39-(Ord(Line[0]) div 2),12);
    writeln(Line);
    delay(575);
    clrscr;


end;
{==================================================================}
{==================================================================}
{==================================================================}
Procedure Intro;
{Simple intro}
{Self-Explainatory}
var
   Line: string;
begin
   Clrscr;
   If not Keypressed then Fadeln('In the Year 2481,');
   If not Keypressed then Fadeln('Mankind will come under great threat,');
   If not Keypressed then Fadeln('From an Alien Invasion.');
   Clrscr;
   If not Keypressed then Delay(1500);
   If not Keypressed then Fadeln('You are its only hope.');
   If not Keypressed then Fadeln('Destiny awaits...');
end;



{==================================================================}
{==================================================================}
{==================================================================}
Procedure Menu(Title: QueueType; var choice: char);
{Opening Menu}
var
   buffer: boolean;
begin

	cls(0);      {Clear the REAL screen}
	InitVirtual; {Clear the VIRTUAL screen}
	DisplayPic(Title,0,0,buffer);  {Display the TITLE picture}
	Flip;     {make the virtual screen the real screen}
     repeat
         choice := readkey;

     until (choice = '1') or (choice = '2') or (choice = '3')
           or (choice = '4') or (choice = '5');

end;

{==================================================================}
{==================================================================}
{==================================================================}
Function getpixelVPP (x,y: integer): integer;
{Get a pixel that is at X,Y on the virtual screen}
begin
     If (x>=Xmin) and (x<Xmax+1) and (Y>=Ymin) and (Y<Ymax+1) then
        getpixelvpp := Mem [Vaddr:X+(Y*320)];
end;
{==================================================================}
{==================================================================}
{==================================================================}
Function getpixel (x,y: integer): integer;
{Get a pixel that is at X,Y on the real screen}
begin
     If (x>=Xmin) and (x<Xmax+1) and (Y>=Ymin) and (Y<Ymax+1) then
	getpixel := Mem [VGA:X+(Y*320)];
end;
{==================================================================}
{==================================================================}
{==================================================================}
Procedure CleanupGame(   var Ship: ShipType;
                         var Bullet: BulletType;
					var Enemy: EnemyType;
					var Explosion: ExplosionType;
					var Title: QueueType;
					Var Misc: MiscGraphics;
					Var Level: LevelType);
begin
	DestroyQueue(Ship.Graphics);
	DestroyQueue(Bullet.Graphics[1]);
	DestroyQueue(Bullet.Graphics[2]);
	DestroyQueue(Bullet.Graphics[3]);
	DestroyQueue(Bullet.Graphics[4]);
	DestroyQueue(Bullet.Graphics[5]);
	DestroyQueue(Enemy.Graphics[1]);
	DestroyQueue(Enemy.Graphics[2]);
	DestroyQueue(Enemy.Graphics[3]);
	DestroyQueue(Enemy.Graphics[4]);
	DestroyQueue(Explosion.Graphics[1]);
	DestroyQueue(Explosion.Graphics[2]);
	DestroyQueue(Explosion.Graphics[3]);
	DestroyQueue(Title);
	DestroyQueue(Misc.one);
	DestroyQueue(Misc.two);              {Initialize the}
	DestroyQueue(Misc.three);          {Graphics}
	DestroyQueue(Misc.four);
	DestroyQueue(Misc.five);
	DestroyQueue(Misc.six);
	DestroyQueue(Misc.seven);
	DestroyQueue(Misc.eight);
	DestroyQueue(Misc.nine);
	DestroyQueue(Misc.score);
	DestroyQueue(Misc.Credits);
	DestroyQueue(Misc.opt5000);
	DestroyQueue(Misc.Zero);
	DestroyQueue(Misc.Name);
	DestroyQueue(Misc.Pause);
	DestroyQueue(Level);


end;
{==================================================================}
{==================================================================}
{==================================================================}

Procedure InitializeGame(var Ship: ShipType;
                         var Bullet: BulletType;
					var Enemy: EnemyType;
                         var Explosion: ExplosionType;
                         var Title: QueueType;
                         Check: integer;
					Var Misc: MiscGraphics;
					Var Level: LevelType);
{Initializes Game Data}
var
   ctr: integer;
begin
     clrscr;
	{writeln('Initializing Game and Loading Graphincs into memory.');
     writeln('Please Hold...');
      }
     If check = 1 then begin
	InitializePic(Ship.Graphics,ShipFilePath);
     InitializePic(Bullet.Graphics[1], Bullet1Path);
     InitializePic(Bullet.Graphics[2], Bullet2Path);
     InitializePic(Bullet.Graphics[3], Bullet3Path);
     InitializePic(Bullet.Graphics[4], Bullet4Path);
     InitializePic(Bullet.Graphics[5], EnemyShtPath);
     InitializePic(Enemy.Graphics[1], Enemy1Path);
     InitializePic(Enemy.Graphics[2], Enemy2Path);
     InitializePic(Enemy.Graphics[3], Enemy3Path);
     InitializePic(Enemy.Graphics[4], Enemy4Path);
     InitializePic(Explosion.Graphics[1], Exp1Path);
     InitializePic(Explosion.Graphics[2], Exp2Path);
     InitializePic(Explosion.Graphics[3], Exp3Path);
     InitializePic(Title, TitlePath);
     InitializePic(Misc.one, onepath);
	InitializePic(Misc.two, twopath);              {Initialize the}
	InitializePic(Misc.three, threepath);          {Graphics}
	InitializePic(Misc.four, fourpath);
	InitializePic(Misc.five, fivepath);
	InitializePic(Misc.six, sixpath);
	InitializePic(Misc.seven, sevenpath);
	InitializePic(Misc.eight, eightpath);
	InitializePic(Misc.nine, ninepath);
	InitializePic(Misc.score, scorepath);
	InitializePic(Misc.Credits, CreditPath);
	InitializePic(Misc.opt5000, opt5000path);
	InitializePic(Misc.Zero, ZeroPath);
	InitializePic(Misc.Name, NamePAth);
	InitializePic(Misc.Pause, PausePath);

	InitializePic(Level, LevelPath);    {Initialize the level}


     end;
	Ship.x := 10;
     Ship.y := 75;
     Ship.Shield := 3;
     Ship.LastShot := 0;
     Ship.FireRate := 20;
     Ship.ammo := 1;
	Ship.Dead := False;
	{Initialize the Guys so they are all NOT ACTIVE}
     for ctr := 1 to MaxBullet do Bullet.Data[ctr].Active := False;
     for ctr := 1 to MaxEnemy do Enemy.Data[ctr].Active := False;
     for ctr := 1 to MaxExp do Explosion.Data[ctr].Active := False;

end;
{==================================================================}
{==================================================================}
{ATTENTION:
	The following are the GetNext functions.  These find the next available
	Guy/Bullet/Explostion to use the commands for.
{==================================================================}
Function GetNextEnemy(Enemy: EnemyType): integer;
var
   counter: integer;
   done: boolean;

begin
     counter := 0;
     done := false;
     repeat
        counter := counter + 1;
        If Enemy.Data[counter].Active = False then done := true;
     until done or (counter = MaxEnemy);
     GetNextEnemy := counter;
end;
{==================================================================}
{==================================================================}
{==================================================================}
Function GetNextBullet(Bullet: BulletType): integer;
var
   counter: integer;


begin
     counter := 0;
     repeat
        counter := counter + 1;
     until (Bullet.Data[counter].Active = False) or (counter = MaxBullet);
     GetNextBullet := counter;
end;
{==================================================================}
{==================================================================}
{==================================================================}
Function GetNextExplosion(Explosion: ExplosionType): integer;
var
   counter: integer;


begin
     counter := 0;
     repeat
        counter := counter + 1;
     until (Explosion.Data[counter].Active = False) or (counter = MaxExp);
     GetNextExplosion := counter;
end;
{==================================================================}
{==================================================================}
{==================================================================}
Procedure Help;
{Self-Explainatory}
begin
     SetText;
     TextMode(C80 + Font8x8);
     Nocursor;
     writeln;
     Textcolor(lightgray);
     writeln('Welcome to your destiny...');
     writeln;
     writeln('MOVEMENT:');
     writeln;
     writeln('To move, use the arrow keys to travel in the direction you wish.  If you have');
     writeln('a mouse, consider using it instead of the keyboard, because your ship is more');
     writeln('manuverable.  When using the mouse, press the left mouse button to fire.');
     writeln;
     writeln('ENEMIES:');
     writeln;
     writeln('While playing, hordes of alien ship will fly in your direction.  You will meet');
     writeln('four different classes of aliens.  The first class is RED.  These ships will');
     writeln('aimlessly fly ahead.  The second class, BLUE, will home in on you slowly and');
     writeln('fire at you.  The third class is GREEN, they manuver faster then the BLUE');
     writeln('ships.  The fourth class is YELLOW, and they are used primarily for ambushes');
     writeln('from the top and bottom of the screen, watch out for them.');
     writeln;
     writeln('PLAYING:');
     writeln;
     writeln('During the game, you will have your Shields, Fire Speed, and Fire Power ');
     writeln('displayed at the bottom of the screen.  Every time you get hit, you lose');
     writeln('shielding.  If you get hit with no shields, you die.  Fire Speed improves the');
     writeln('rate at which your bullets leave your ship.  Fire Power increases the size of');
     writeln('you bullets so you can hit the aliens easier.');
     writeln;
     writeln('BONUSES: ');
     writeln;
     writeln('Every time you reach a score that is a multiple of 5000, you recieve a bonus.');
     writeln('When you start the game, you will see a little "X" to the left of your shields.');
     writeln('This is the bonus selector.  Pressing the "s" key will change what you want to');
     writeln('upgrade when you reach the bonus score.');

     readln;



end;
{==================================================================}
{==================================================================}
{==================================================================}
Procedure RecallPic(Pic: QueueType; x,y: integer; var Hit: boolean);
{Recalls the Picture and turns were it was: black}
var
   TmpPic: QueueType;
   Element: QueueElementType;
begin
     TmpPic := Pic;

     repeat
	   Dequeue(TmpPic, Element);   {Dequeue Element from Queue}
        If (Element.X+X>=Xmin) and (Element.X+X<=Xmax) and (Element.y+y>=Ymin) and (Element.Y+y<=Ymax) then begin
	    {Only is pixel on screen}
	    If GetPixel(Element.X+X, Element.Y+Y) <> Element.Data then
		 {If the pixel is not correct data, THE THING IS HIT!}
		 Hit := True;
	   end;
	   VPP(Element.x+x, Element.y+y,BlackC);  {Put Black Pixel}

     until EmptyQueue(TmpPic);
end;
{==================================================================}
{==================================================================}
{==================================================================}
Procedure InitializeHit(var hit: hittype);
{Initializes the Hit Type to all False}
var
   counter: integer;

begin
     Hit.Ship := False;
     for counter := 1 to MaxEnemy do
         Hit.Enemy[counter] := False;
     for counter := 1 to MaxBullet do
         Hit.Bullet[counter] := False;

end;
{==================================================================}
{==================================================================}
{==================================================================}
Procedure DrawStars(Var Stars: StarType);
var
   counter: integer;

begin
    For counter := 1 to MaxStars do
    begin

	   {Clear the Pixel that the star was originally}
	   VPP(Stars[1][counter].x, Stars[1][counter].y, 0);
	   {Make the star go accross 1 pixel}
	   Stars[1][counter].x := Stars[1][counter].x - 1;
	   {If the star is still on the screen...}
	   if Stars[1][counter].x > -1 then
		{Place a new star at the destination}
		VPP(Stars[1][counter].x, Stars[1][counter].y, DarkGC)
	   {else...}
	   else
		{Make the star go back 319 pixels}
		Stars[1][counter].x := Stars[1][counter].x + Xmax;

	   {AND REPEAT}
	   VPP(Stars[2][counter].x, Stars[2][counter].y, 0);
        Stars[2][counter].x := Stars[2][counter].x - 2;
        if Stars[2][counter].x > -1 then
          VPP(Stars[2][counter].x, Stars[2][counter].y, LightGC)
        else
          Stars[2][counter].x := Stars[1][counter].x + Xmax;

	   {ONCE AGAIN}
        VPP(Stars[3][counter].x, Stars[3][counter].y, 0);
        Stars[3][counter].x := Stars[3][counter].x - 3;
        if Stars[3][counter].x > -1 then
          VPP(Stars[3][counter].x, Stars[3][counter].y, WhiteC)
        else
          Stars[3][counter].x := Stars[1][counter].x + Xmax;
    end;
end;
{==================================================================}
{==================================================================}
{==================================================================}
Function Power(num: integer): longint;
{Does 10 to the NUM power}
var
   counter,total: longint;
begin
    total := 1;
    for counter := 1 to num do
	   total := total * 10;
    Power := total;
    if num = 0 then Power := 1;
end;
{==================================================================}
{==================================================================}
{==================================================================}

Procedure DrawScore(Score: longint;  Misc: MiscGraphics);
{Draws the score on the screen in neat numbers}
var
   counter,subcounter: integer;
   buffer: boolean;
   digit: integer;
   x,y: integer;

begin
     subcounter := 0;
	DisplayPic(Misc.Score,10,181,buffer);  {Put the words "Score"}
     For x := 59 to 130 do begin
        For y := 179 to 195 do begin
		  VPP(x,y,0);  {Clear score area}
	   end;
     end;

     For counter := 6 downto 0 do
     begin
          subcounter := subcounter + 1;
          digit := (Score div Power(counter)) mod 10;
          If Score < Power(counter) then digit := 0;
		case digit of

		  {Display the digit at the proper x,y coordinates}

		  1:  DisplayPic(Misc.one,50+(subcounter*10)+1,180,buffer);
            2:  DisplayPic(Misc.two,50+(subcounter*10)-1,180,buffer);
            3:  DisplayPic(Misc.three,50+(subcounter*10),180,buffer);
            4:  DisplayPic(Misc.four,50+(subcounter*10),180,buffer);
            5:  DisplayPic(Misc.five,50+(subcounter*10),180,buffer);
            6:  DisplayPic(Misc.six,50+(subcounter*10),180,buffer);
            7:  DisplayPic(Misc.seven,50+(subcounter*10),180,buffer);
            8:  DisplayPic(Misc.eight,50+(subcounter*10),180,buffer);
            9:  DisplayPic(Misc.nine,50+(subcounter*10),180,buffer);
            0:  DisplayPic(Misc.zero,50+(subcounter*10),180,buffer);
          end;
     end;

end;
{==================================================================}
{==================================================================}
{==================================================================}
Procedure DispStats(Ship: ShipType; Num: integer);
{Display stats}
var
   counter: integer;
   x,y: integer;
begin

     For x := 229 to Xmax do begin
         For y := 176 to Ymax do begin
             VPP(X,Y,BlackC);
         end;
	end;                                     {Clear stat area}

     For x := 140 to 149 do begin
         For y := 176 to Ymax do begin
             VPP(X,Y,BlackC);
         end;
     end;

     VPP(145,175+(Num*6)-3,100);
     VPP(144,175+(Num*6)-2,100);
	VPP(144,175+(Num*6)-4,100);      {Draw the blue "X"}
     VPP(146,175+(Num*6)-2,100);
     VPP(146,175+(Num*6)-4,100);

     For counter := 1 to Ship.Shield*4 do begin
         VPP(230+counter, 176, 32);
         VPP(230+counter, 177, 32);
	    VPP(230+counter, 178, 32);     {Draw Shield bar}
	    VPP(230+counter, 179, 32);
         VPP(230+counter, 180, 32);
     end;

     For counter := 1 to ((Ship.FireRate-25)*(-1))*2 do begin
         VPP(230+counter, 182, 39);
	    VPP(230+counter, 183, 39);
	    VPP(230+counter, 184, 39);     {Draw Speed bar}
	    VPP(230+counter, 185, 39);
	    VPP(230+counter, 186, 39);

	end;

	For counter := 1 to Ship.Ammo*5 do begin
	    VPP(230+counter, 188, 44);
	    VPP(230+counter, 189, 44);
	    VPP(230+counter, 190, 44);     {Draw Power bar}
	    VPP(230+counter, 191, 44);
	    VPP(230+counter, 192, 44);

     end;

end;
{==================================================================}
{==================================================================}
{==================================================================}
Procedure ChangeSelect(Var Num: integer);
{Stupid procedure that changes the select for the "X"}
begin
     case num of
          1,2,3:  num := num + 1;
          4: num := 1;
     end;
end;
{==================================================================}
{==================================================================}
{==================================================================}
Procedure UpdateLevel(Var Level: LevelType; Var Enemy: EnemyType);
{Advances the level}
var
	counter: integer;
	Element: QueueElementType;


begin
	DeQueue(Level, Element);
	If Element.x <> BlackC then
	begin
	    Enemy.Data[GetNextEnemy(Enemy)].x := Element.X;
	    Enemy.Data[GetNextEnemy(Enemy)].y := Element.Y;
	    Enemy.Data[GetNextEnemy(Enemy)].Data := Element.Data;
	    Enemy.Data[GetNextEnemy(Enemy)].Active := True;
	end;
	If Element.X = 998 then
		InitializePic(Level, LevelPath);


end;
{==================================================================}
{==================================================================}
{==================================================================}
Procedure WarpIn(Var Ship: ShipType; Var Stars: StarType);
var
   Counter: integer;
   Buffer: boolean;

Procedure DrawStar2(var Stars: StarType; Num: integer);
var
      counter2: integer;
      counter: integer;
begin
    For counter := 1 to MaxStars do
    begin
        For counter2 := 1 to ((10 - (Num Div 8))+1) do
        VPP(Stars[1][counter].x + counter2, Stars[1][counter].y, 0);
        Stars[1][counter].x := Stars[1][counter].x - (10 - (Num Div 8));
        if Stars[1][counter].x > -1 then
        For counter2 := 1 to (10 - (Num Div 8)) do
          VPP(Stars[1][counter].x + counter2, Stars[1][counter].y, DarkGC)
        else
          Stars[1][counter].x := Stars[3][counter].x + 319;

        For counter2 := 1 to ((10 - (Num Div 8))+1) do
        VPP(Stars[2][counter].x + counter2, Stars[2][counter].y, 0);
        Stars[2][counter].x := Stars[2][counter].x - 2 * (10 - (Num Div 8));
        if Stars[2][counter].x > -1 then
        For counter2 := 1 to (10 - (Num Div 8)) do
          VPP(Stars[2][counter].x + counter2, Stars[2][counter].y, LightGC)
        else
          Stars[2][counter].x := Stars[3][counter].x + 319;

        For counter2 := 1 to ((10 - (Num Div 8))+1) do
        VPP(Stars[3][counter].x + counter2, Stars[3][counter].y, 0);
        Stars[3][counter].x := Stars[3][counter].x - 3 * (10 - (Num Div 8));
        if Stars[3][counter].x > -1 then
        For counter2 := 1 to (10 - (Num Div 8)) do
          VPP(Stars[3][counter].x + counter2, Stars[3][counter].y, WhiteC)
        else
          Stars[3][counter].x := Stars[3][counter].x + 319;
    end;
end;


begin
    For counter := 0 to 79 do
    begin
         DrawStar2(Stars,counter);
         DisplayPic(Ship.Graphics,Xmax-(counter*4),75,buffer);
         WaitRetrace;
         Delay(20);
         Flip;
         RecallPic(Ship.Graphics,Xmax-(counter*4),75,buffer);

    end;
    InitVirtual;
end;
{==================================================================}
{==================================================================}
{==================================================================}
Procedure Configure(Var Ship: ShipType);
Var
   Choice: Char;
   Input: char;
   MaxPoints: integer;
   TmpShld,TmpAmmo,TmpRate: integer;
   done: boolean;

begin
    SetText;
    Repeat
    TmpShld := 0;
    TmpAmmo := 1;
    TmpRate := 1;
    MaxPoints := 6;
    Clrscr;
    writeln('ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿');
    writeln('³Welcome to the ShipYard³');
    writeln('ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ');
    writeln;
    writeln('Please Distribute your available shippoints: ',MaxPoints);
    writeln('Sorry, we cannot equip you with the best weapons though...');
    writeln;
    repeat
          GotoXY(1,7);
          writeln;
          writeln('1) Current Shield Rating: ',TmpShld,'/20');
          writeln('2) Current Fire Power:    ',TmpAmmo,'/3');
          writeln('3) Current Fire Speed:    ',TmpRate,'/4');
          writeln('Remaining: ',MaxPoints,' ');
          writeln;
          MaxPoints := MaxPoints - 1;
          Repeat
            GotoXy(1,13);
            write('Add to [1..3]:    ');
            writeln('                   ');
            gotoxy(16,13);
            Input := readkey;
            writeln('                    ');
            Done :=  False;
            If (Input='1') or (Input='2') or (Input = '3') then
            begin
                 Done := True;
                 Case Input of
                 '1': TmpShld := TmpShld + 1;
                 '2': If TmpAmmo < 3 then TmpAmmo := TmpAmmo + 1
                    else Done := False;
                 '3': If TmpRate < 4 then TmpRate := TmpRate + 1
                    else Done := False;
                 end;
            end;
          Until done;
    until MaxPoints = 0;
    Clrscr;
    writeln('Current Shield Rating: ',TmpShld,'/20');
    writeln('Current Fire Power:    ',TmpAmmo,'/3');
    writeln('Current Fire Speed:    ',TmpRate,'/4');
    writeln;
    write('Sure? [Y/N]: ');
    repeat
          choice := readkey;
    until (upcase(choice) = 'Y') or (upcase(choice) = 'N');
    Until upcase(choice) = 'Y';
    Ship.Shield := TmpShld;
    Ship.FireRate := 30 - (5*TmpRate);
    Ship.Ammo := TmpAmmo;
    SetMCGA;


end;
{==================================================================}
{==================================================================}
{==================================================================}

Procedure PlayGame(Var Ship: ShipType;
                   Var Bullet: BulletType;
                   Var Enemy: EnemyType;
                   Var Explosion: ExplosionType;
		   Var Misc: MiscGraphics;
		   Var Level: LevelType;
                   Var Score: Longint);
var
   Key:  Char;
   Counter: integer;
   Hit: HitType;
   Buffer: boolean;
   TurnCounter: integer;
   ShotChance: integer;
   DeleteMe: integer;
   Stars: StarType;
   Selected: integer;
   NextBonus: longint;
   CharBuffer: Char;


begin

     Configure(Ship);

     Selected := 1;
     Cls(0);
     InitVirtual;
     Turncounter := 0;

	DestroyQueue(Level);
	InitializePic(Level, LevelPath);

     For counter := 1 to MaxStars do
     begin
	    Stars[1][counter].X := Random(319);
         Stars[1][counter].Y := Random(175);
         Stars[2][counter].X := Random(319);
         Stars[2][counter].Y := Random(175);
         Stars[3][counter].X := Random(319);
         Stars[3][counter].Y := Random(175);
     end;

     WarpIn(Ship, Stars);

     Score := 0;
     NextBonus := NextBonusValue;
     Repeat
        Repeat
           Turncounter := Turncounter + 1;
           DrawStars(Stars);
           DrawScore(Score, Misc);
           DisplayPic(Misc.opt5000,150,176,buffer);
           DispStats(Ship,selected);
           DisplayPic(Misc.Name,260,177,Buffer);
           {ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ}
           {ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ}

           Displaypic(Ship.Graphics,Ship.X,Ship.Y,Hit.Ship);

           For counter := 1 to MaxBullet do
		 begin
                If Bullet.Data[counter].Active then
		     DisplayPic(Bullet.Graphics[Bullet.Data[counter].data],
                     Bullet.Data[counter].x,Bullet.Data[counter].y,Hit.Bullet[counter]);
           end;
           For counter := 1 to MaxEnemy do
           begin
                If Enemy.Data[counter].Active then
                  DisplayPic(Enemy.Graphics[Enemy.Data[counter].data],
                     Enemy.Data[counter].x,Enemy.Data[counter].y,Hit.Enemy[counter]);
           end;
	   For counter := 1 to MaxExp do
           begin
	        If Explosion.Data[counter].Active then
                  DisplayPic(Explosion.Graphics[Explosion.Data[counter].phase],
                     Explosion.Data[counter].x,Explosion.Data[counter].y,buffer);
           end;

           WaitRetrace;
		 Flip;


		 Delay(0);

           {ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ}
           {ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ}

           Recallpic(Ship.Graphics,Ship.X,Ship.Y,Hit.Ship);
           If Hit.Ship then Ship.Shield := Ship.Shield - 1;
           If Ship.Shield = -1 then Ship.Dead := True;
           For counter := 1 to MaxBullet do
           begin
                If Bullet.Data[counter].Active then begin
                  RecallPic(Bullet.Graphics[Bullet.Data[counter].data],
			   Bullet.Data[counter].x,Bullet.Data[counter].y,Hit.Bullet[counter]);
                  If Hit.Bullet[counter] then
                     If Bullet.Data[counter].Data <> 4 then Bullet.Data[counter].Active := False;
                  if Bullet.Data[counter].Data <> 5 then begin
				Bullet.Data[counter].X := Bullet.Data[counter].X + 8;
                    If Bullet.Data[counter].x > 314 then Bullet.Data[counter].active := False;
                  end;
                  if Bullet.Data[counter].Data = 5 then begin
                    Bullet.Data[counter].X := Bullet.Data[counter].X - 6;
                    If Bullet.Data[counter].x < 3 then Bullet.Data[counter].active := False;
			   end;


                end;
		 end;
           For counter := 1 to MaxEnemy do
		 begin
		   If Enemy.Data[counter].Active then begin
			 RecallPic(Enemy.Graphics[Enemy.Data[counter].data],
			   Enemy.Data[counter].x,Enemy.Data[counter].y,Hit.Enemy[counter]);
			 If Hit.Enemy[counter] then begin
			    Enemy.Data[counter].Active := False;
			    case Enemy.Data[counter].Data of
				 1: Score := Score + Ship1Score;
				 2: Score := Score + Ship2Score;
				 3: Score := Score + Ship3Score;
				 4: Score := Score + Ship4Score;
			    end;
			   Explosion.Data[GetNextExplosion(Explosion)].X := Enemy.Data[counter].X-2;
			   Explosion.Data[GetNextExplosion(Explosion)].Y := Enemy.Data[counter].Y-1;
			   Explosion.Data[GetNextExplosion(Explosion)].Phase := 1;
			   Explosion.Data[GetNextExplosion(Explosion)].Active := True;
			   Explosion.Data[GetNextExplosion(Explosion)].X := Enemy.Data[counter].X+4;
			   Explosion.Data[GetNextExplosion(Explosion)].Y := Enemy.Data[counter].Y;
			   Explosion.Data[GetNextExplosion(Explosion)].Phase := 1;
			   Explosion.Data[GetNextExplosion(Explosion)].Active := True;
			   Explosion.Data[GetNextExplosion(Explosion)].X := Enemy.Data[counter].X+2;
			   Explosion.Data[GetNextExplosion(Explosion)].Y := Enemy.Data[counter].Y+2;
			   Explosion.Data[GetNextExplosion(Explosion)].Phase := 1;
			   Explosion.Data[GetNextExplosion(Explosion)].Active := True;
                  end;
                  If Enemy.Data[counter].x < -20 then Enemy.Data[counter].active := False;
                  Enemy.Data[counter].x := Enemy.Data[counter].x - 4;
                  If Enemy.Data[counter].Data = 4 then Enemy.Data[counter].x := Enemy.Data[counter].x - 1;
                  If Enemy.Data[counter].Data > 1 then
                  begin
		      If Enemy.Data[counter].y > Ship.y then
				 Enemy.Data[counter].y := Enemy.Data[counter].y - Enemy.Data[counter].Data + 1;
			 If Enemy.Data[counter].y < Ship.y then
				 Enemy.Data[counter].y := Enemy.Data[counter].y + Enemy.Data[counter].Data - 1;
		      ShotChance := Random(35) + 1;
		      if ShotChance = 3 then begin
			 Bullet.Data[GetNextBullet(Bullet)].X := Enemy.Data[counter].x - 7;
                         Bullet.Data[GetNextBullet(Bullet)].Y := Enemy.Data[counter].y + 3;
			 Bullet.Data[GetNextBullet(Bullet)].Data := 5;
                         Bullet.Data[GetNextBullet(Bullet)].Active := True;
                      end;
                  end;




                end;

           end;
           For counter := 1 to MaxExp do
           begin
                If Explosion.Data[counter].Active then

                  If Explosion.Data[counter].Phase < 4 then
                  RecallPic(Explosion.Graphics[Explosion.Data[counter].phase],
		  Explosion.Data[counter].x,Explosion.Data[counter].y,buffer);
		  Case Explosion.Data[counter].Phase of
		      1: Explosion.Data[counter].Phase := 2;
		      2: Explosion.Data[counter].Phase := 3;
			 3: Explosion.Data[counter].Active := False;
		  end;
	   end;


           {ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ}
           {ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ}

		 {DeleteMe := Random(35) + 1;
           if DeleteMe = 4 then begin
               Enemy.Data[GetNextEnemy(Enemy)].x := 319;
               Enemy.Data[GetNextEnemy(Enemy)].y := Random(125) + 25;
               Enemy.Data[GetNextEnemy(Enemy)].Data := Random(4)+1;
			Enemy.Data[GetNextEnemy(Enemy)].Active := True;
		 end;                      }

		 If turncounter mod 15 = 0 then
		 UpdateLevel(Level, Enemy);

           {ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ}
           {ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ}
		 {
           If mouse.y > 190 then if Ship.y<155 then Ship.y := Ship.y + 6;
           If mouse.x < 10 then if Ship.x>6 then Ship.x := Ship.x - 6;
           if mouse.x > 310 then if Ship.x<265 then Ship.x := Ship.x + 6;
           If mouse.y < 10 then if Ship.y>6 then Ship.y := Ship.y - 6;
           if mouse.left then begin
                  if Ship.LastShot < Turncounter - Ship.FireRate then begin
                     Ship.Lastshot := Turncounter;
                     Bullet.Data[GetNextBullet(Bullet)].X := Ship.x + 47;
                     Bullet.Data[GetNextBullet(Bullet)].Y := Ship.y + 3;
                     Bullet.Data[GetNextBullet(Bullet)].Data := Ship.Ammo;
                     Bullet.Data[GetNextBullet(Bullet)].Active := True;
                  end;
			end;   }



           If Port[$60]=80 then if Ship.y<155 then Ship.y := Ship.y + 6;
           If Port[$60]=75 then if Ship.x>6 then Ship.x := Ship.x - 6;
           If Port[$60]=77 then if Ship.x<265 then Ship.x := Ship.x + 6;
           If Port[$60]=72 then if Ship.y>6 then Ship.y := Ship.y - 6;
           If Port[$60]=57 then
               begin
                  if Ship.LastShot < Turncounter - Ship.FireRate then begin
				 Ship.Lastshot := Turncounter;
                     Bullet.Data[GetNextBullet(Bullet)].X := Ship.x + 47;
                     Bullet.Data[GetNextBullet(Bullet)].Y := Ship.y + 3;
                     Bullet.Data[GetNextBullet(Bullet)].Data := Ship.Ammo;
                     Bullet.Data[GetNextBullet(Bullet)].Active := True;
                  end;
               end;

	{	 If Port[$60]=31 then ChangeSelect(Selected); }
           If Port[$60]=25 then
                    Begin
                       DisplayPic(Misc.Pause,115,75,buffer);
				   Flip;
				   repeat
				   CharBuffer := Readkey;
				   until CharBuffer = #13;
                       RecallPic(Misc.Pause,115,75,buffer);
                    end;



           {ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ}
           {ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ}


           InitializeHit(Hit);
           If NextBonus < Score+1 then begin
		    NextBonus := NextBonus + NextBonusValue;
              case Selected of
                   1:  begin
                          If Ship.Shield < 20 then
                             Ship.Shield := Ship.Shield + 1;
                       end;
                   2:  begin
                          If Ship.FireRate > 6 then
                             Ship.FireRate := Ship.FireRate - 5;
		       end;
                   3:  begin
		             If Ship.Ammo <= 3 then
                             Ship.Ammo := Ship.Ammo + 1;
                       end;
			    4:  begin
					 Score := Score + 3000;
					 NextBonus := NextBonus + 3000;
				   end;

              end;
           end;




        Until Keypressed or Ship.Dead;
        Key := ' ';
        while keypressed do key := Readkey;

        case key of
          #27: Ship.Dead := True;
          {#80: if Ship.y<155 then Ship.y := Ship.y + 6;
          #75: if Ship.x>6 then Ship.x := Ship.x - 6;
          #77: if Ship.x<265 then Ship.x := Ship.x + 6;
          #72: if Ship.y>6 then Ship.y := Ship.y - 6;
          #32: begin
                  if Ship.LastShot < Turncounter - Ship.FireRate then begin
                     Ship.Lastshot := Turncounter;
                     Bullet.Data[GetNextBullet(Bullet)].X := Ship.x + 47;
                     Bullet.Data[GetNextBullet(Bullet)].Y := Ship.y + 3;
                     Bullet.Data[GetNextBullet(Bullet)].Data := Ship.Ammo;
                     Bullet.Data[GetNextBullet(Bullet)].Active := True;
                  end;
			end; }
		's','S':  ChangeSelect(Selected);
{          'p','P':  Begin
                       DisplayPic(Misc.Pause,115,75,buffer);
                       Flip;
                       CharBuffer := Readkey;
                       RecallPic(Misc.Pause,115,75,buffer);
                    end;  }

        end;

        delay(50);

     until Ship.Dead;
     SetText;
     NoCursor;
     Clrscr;
	Fadeln('Ouch...you died...');
	Fadeln('But you did manage a score of:');
     Gotoxy(37,12);
     Textcolor(white);
     writeln(Score);
     Delay(1000);



end;
{==================================================================}
{==================================================================}
{==================================================================}

Procedure MAIN;

var
   Ship: ShipType;
   Bullet: BulletType;
   Enemy: EnemyType;
   Explosion: ExplosionType;
   Title: QueueType;
   HighScore:  ScoreType;
   TurnCounter: integer;
   Choice: char;
   Misc: MiscGraphics;
   buffer: boolean;
   Level: LevelType;
   Score: longint;

begin

     Randomize;
	SetUpVirtual;
     SetText;
     Nocursor;

     Turncounter := 0;

     InitializeGame(Ship,Bullet,Enemy,Explosion,Title,1,Misc,Level);
     InitVirtual;
	Intro;
	TextColor(white);


	Repeat
	InitializeGame(Ship,Bullet,Enemy,Explosion,Title,2,Misc,Level);
        SetMCGA;
        Menu(Title, choice);


        Case choice of

		 '1':  PlayGame(Ship, Bullet, Enemy, Explosion, Misc,Level,score);
           '4':  begin
                      SetMCGA;
                      InitVirtual;
                      DisplayPic(Misc.Credits,0,0,buffer);
                      Flip;
                      readln;
                 end;
           '3':  Help;


        end;
     Until (choice = '5');


     SetText;
     Nocursor;
	Clrscr;
	TextColor(white);
	If not Keypressed then Fadeln('Thank you for playing: Destiny');
	If not Keypressed then Fadeln('By Jason Fieldman');
	If not Keypressed then Fadeln('Mr. Zupp, feel free to give me an A');
	SetText;
	clrscr;
	Textcolor(lightgray);
	CleanUpGame(Ship,Bullet,Enemy,Explosion,Title,Misc,Level);



end;

{==================================================================}
{==================================================================}
{==================================================================}

BEGIN


    MAIN;


END.












































