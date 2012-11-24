Program F15StrikeTeam;
Uses
    Crt,
    Dos;

Type

    DataArray =  array [1..4] of integer;
    MovedArray = array [1..2] of integer;
    PlaneType = Record
       Name:        String[10];
       ID:          integer;
       Cannons:     integer;
       LRM:         integer;
       MRM:         integer;
       Wings:       integer;
       Fuselage:    integer;
       CockPit:     integer;
       Engines:     integer;
       Tail:        integer;
       Xloc:        integer;
       Yloc:        integer;
       color:       integer;
       Dead:        boolean;
       chaffs:      integer;
    end;


Function Apple(A,B: PlaneType): integer;
begin
     Apple := 9;
end;

Procedure dood;
var
   g: integer;
   v,h: planetype;
begin
     g := Apple(v,h);
end;






{=========================================================================}

Procedure Instructions;
begin
end;



{=========================================================================}

Procedure Options(var Players: integer);
var
   choice: char;
   done: boolean;
begin
     done := False;
     repeat
     clrscr;
     writeln('Welcome to F-15 Strike Team!');
     writeln('Please choose one of the following: ');
     writeln;
     writeln('1) One-Player game (Not Available yet)');
     writeln('2) Two-Player game (Hotseat play)');
     writeln('3) View Instructions');
     writeln('4) Quit');
     repeat
     choice := readkey;
     until (choice = '1') or (choice = '2') or (choice = '3')
           or (choice = '4');

     if (choice='2') then done := True;
     if choice = '3' then instructions;
     if choice = '4' then begin
        writeln;
        writeln('Bye!');
        halt(1);
     end;
     until done = True;
     if choice = '1' then players := 1
     else players := 2;
end;

{=========================================================================}

procedure NOCURSOR; Assembler;
asm
   mov ah, 01
   mov cx, 02000h
   int 10h
@@1:
end;

{=========================================================================}

Procedure Intro;
var
   choice: char;
begin
     clrscr;
     nocursor;
     gotoxy(33,20);
     writeln('F-15 Strike Team');
     readln;
     clrscr;
     delay(250);
     gotoxy(33,20);
     writeln('By Jason Fieldman');
     readln;
     clrscr;
     repeat
       write('Do you want instructions? [Y/N]: ');
       readln(choice);
     until (upcase(choice)='N') or (upcase(choice)='Y');
     if Upcase(choice) = 'Y' then begin
        clrscr;
        writeln('-------INSTRUCTIONS-------');
        writeln;
        writeln('F15 Strike Team is played on one screen, which is composed of the RADAR, the');
        writeln('PLANE STATUS WINDOW (PSW) and the INTERACTIVE WINDOW (IW).  When you start the');
        writeln('game, you will find the planes resting at the bottom of the RADAR.');
        writeln;
        writeln;
        writeln('THE RADAR SCREEN:');
        writeln;
        writeln('The RADAR SCREEN (RS) displays the position of your planes during the course of');
        writeln('the game.  It is composed of several diamonds arranged in a hexagon formation.');
        writeln('The outer diamonds of the RS have numbers on them, which, as you will see, ');
        writeln('follow a pattern.  The uses of these numbers will be explained in the MOVEMENT');
        writeln('section.');
        writeln;
        writeln;
        writeln('MOVEMENT: ');
        writeln;
        writeln('Movement is simple.  You will be prompted in the IW to enter in two choices for');
        writeln('movement.  The choice is to either (a) break right, (b) break left or (c) break');
        writeln('ahead.  This decision determines if you will go right, left, or ahead (simple).');
        writeln('The second choice is if you will travel (a) Short distance, (b) Medium distance');
        writeln('or (c) Long distance.  Distance is always random, so when you pick Short');
        writeln('distance, you will travel 1-3 spaces.  Medium will send you 2-6 spaces, and');
        writeln('Long will send your plane 4-12 spaces.  Since there are only so many spaces on');
        writeln('the board, we need a wrap-around system.  The numbers on the edges serve that');
        writeln('purpose.  If you go to a square occupied by a number, the next space you');
        writeln('advance will take you to the corresponding number on the bottom of the RS.  The');
        writeln('strategy of this game comes from your ability to use the wrap-around to come in');
        writeln('behind your opponent for a shot.  If your final space is occupied by another');
        writeln('plane, you will be sent forward another space.');
        writeln('REMEMBER:   Movement is always decided before the turn begins, before ANY OTHER');
        writeln('action is taken, so you better choose wisely!');
        writeln;
        writeln;
        writeln;
        writeln('Press RETURN to continue intructions');
        readln;
        clrscr;
        writeln('INSTRUCTIONS CON''T:');
        writeln;
        writeln('ATTACKING:');
        writeln;
        writeln('Attacking is the easy.  Your planes are composed of two weapons: the cannons');
        writeln('and missles.  There are two types of missles, Long Range Missles (LRM) and');
        writeln('Medium Range Missles (MRM).  Using cannons, the targetted plane MUST lay in the');
        writeln('direct diagonal of your plane (right or left), or it must be directly ahead of');
        writeln('your plane.  No matter what, the targetted plane must be in front of your plane');
        writeln('to be targetted.  Missles operate similarly as cannons, but have a wider range.');
        writeln('Missles can fire ANYWHERE within your planes "Cone of Fire" (COF).  The COF is');
        writeln('defined to be the entire area inside your planes two diagonals (including the');
        writeln('diagonals).  Here''s the catch to firing weapons:  Range.  Let us imagine we');
        writeln('have four imaginary dice, all the same.  They contain two 0''s, two 2''s, and two');
        writeln('5''s.  The LRMs roll four dice, the MRMs roll three and the cannons only roll');
        writeln('two.  The total on these dice are the range in which your Missle or cannon has');
        writeln('fired.  If the targetted plane is within this range, you HIT!  But if not, you');
        writeln('MISS!  Here is the other catch: each plane comes equiped with two chaffs.  The');
        writeln('chaffs serve important purposes, because they knock off you highest "Die value"');
        writeln('from your total range, a good defensive utility.');
        writeln;
        writeln;
        writeln('DAMAGE: ');
        writeln;
        writeln('Whenever your plane gets hit by a missle or cannon, you take damage.  Your');
        writeln('plane can only take so much damage before it dies (you have two planes so all');
        writeln('is not lost when one dies).  Your PSW (Plane Status Window) will inform you of');
        writeln('how much damage is in effect, and how much total damage each part can withstand');
        writeln('When one part of your plane reachs maximum damage, your plane dies.');
        writeln;
        writeln;
        writeln('TURNS:');
        writeln;
        writeln('The person who goes first each round alternates, with Player 1 first round 1,');
        writeln('Player 2 first round 2, Player 1 first round 3, etc...  The exception is when');
        writeln('one player has 2 planes and the other has only 1.  The player with more planes');
        writeln('ALWAYS goes first!');

        readln;


     end;
end;

{=========================================================================}

Procedure GetNames(var A,B,C,D: PlaneType);
var
   name: string[10];
   who: integer;
   counter: integer;
   color: integer;
begin
    clrscr;
    writeln('Names should be only 10 characters!');
    writeln;
    write('Enter Name for Player 1''s first plane: ');
    readln(name);
    A.name := Name;
    writeln;
    write('Enter Name for Player 1''s second plane: ');
    readln(name);
    B.name := Name;
    writeln;
    write('Enter Name for Player 2''s first plane: ');
    readln(name);
    C.name := Name;
    writeln;
    write('Enter Name for Player 2''s second plane: ');
    readln(name);
    D.name := Name;
    writeln;
    clrscr;
    writeln('COLORS!');
    writeln('If you pick same colors for planes, it gets VERY confusing!');
    writeln;
    for counter := 0 to 15 do
    begin
         textcolor(counter);
         writeln(counter:2,': This Color');
    end;
    writeln;
    write('Player 1, choose the color for ',A.name,': ');
    readln(color);
    A.Color := Color;
    writeln;
    write('Player 2, choose the color for ',C.name,': ');
    readln(color);
    C.Color := Color;
    writeln;
    write('Player 1, choose the color for ',B.name,': ');
    readln(color);
    B.Color := Color;
    writeln;
    write('Player 2, choose the color for ',D.name,': ');
    readln(color);
    D.Color := Color;
    writeln;



end;

{=========================================================================}

Procedure InitializePlane(var Plane: PlaneType);
begin
   Plane.Cannons := 8;
   Plane.LRM := 2;
   Plane.MRM := 3;
   Plane.Wings := 0;
   Plane.Fuselage := 0;
   Plane.Cockpit := 0;
   Plane.Engines := 0;
   Plane.Tail := 0;
   case Plane.ID of
        1: begin
             Plane.Xloc := 1;
             Plane.Yloc := 5;
           end;
        2: begin
             Plane.Xloc := 2;
             Plane.Yloc := 4;
           end;
        3: begin
             Plane.Xloc := 4;
             Plane.Yloc := 2;
           end;
        4: begin
             Plane.Xloc := 5;
             Plane.Yloc := 1;
           end;
   end;
   Plane.Dead := False;
   Plane.chaffs := 2;
end;

{=========================================================================}

Procedure PrintStats(Plane: PlaneType);
var
   counter: integer;
   base: integer;

begin
   case Plane.ID of
     1: Base := 0;
     2: Base := 12;
     3: Base := 24;
     4: Base := 36;
   end;
   Textcolor(Plane.Color);
   gotoxy(62,Base+1);
   write('Name: ',Plane.Name);
   gotoxy(74,Base+2);
   write('Chfs: ');
   writeln(Plane.Chaffs);
   gotoxy(62,Base+2);
   write('Active: ');
   case Plane.Dead of
     True: writeln('NO');
     False: writeln('YES');
   end;
   gotoxy(62,Base+3);
   writeln('LRM''s Left: ',Plane.LRM,'/2');
   gotoxy(62,Base+4);
   writeln('MRM''s Left: ',Plane.MRM,'/3');
   gotoxy(62,Base+5);
   writeln('Cannon''s Left: ',Plane.cannons,'/8');
   gotoxy(62,Base+6);
   writeln('DAMAGE:');
   gotoxy(62,Base+7);
   writeln('Cockpit: ',Plane.Cockpit,'/1');
   gotoxy(62,Base+8);
   writeln('Fuselage: ',Plane.Fuselage,'/1');
   gotoxy(62,Base+9);
   writeln('Wings: ',Plane.Wings,'/4');
   gotoxy(62,Base+10);
   writeln('Engines: ',Plane.Engines,'/2');
   gotoxy(62,Base+11);
   writeln('Tail: ',Plane.Tail,'/2');
   textcolor(white);
   gotoxy(62,base+12);
   writeln('*******************');
end;

{=========================================================================}

Function CannonRange(Plane1,Plane2: PlaneType): Boolean;
begin
    CannonRange := False;
    If (Plane1.Xloc <= Plane2.Xloc) and (Plane1.Yloc <= Plane2.Yloc) then
    begin
       If (Plane1.Xloc = Plane2.Xloc) or (Plane1.Yloc = Plane2.Yloc)
       or ( (Plane2.Xloc-Plane1.Xloc) = (Plane2.Yloc-Plane1.Yloc) ) then
          CannonRange := True;
    end;
end;

{=========================================================================}

Function MissleRange(Plane1,Plane2: PlaneType): Boolean;
begin
    MissleRange := False;
    If (Plane1.Xloc <= Plane2.Xloc) and (Plane1.Yloc <= Plane2.Yloc) then
       MissleRange := True;
end;

{=========================================================================}

Function SpaceRange(RadarPlane,TargetPlane: PlaneType): integer;
var
   TmpXloc,TmpYloc,counter: integer;
   Done: boolean;
begin
     counter := 0;
     TmpXloc := RadarPlane.Xloc;
     TmpYloc := RadarPlane.Yloc;
     repeat
       Done := False;
       counter := counter + 1;
       If (TmpXloc < TargetPlane.Xloc) AND
          (TmpYloc < TargetPlane.Yloc) then
          begin
             TmpXloc := TmpXloc + 1;
             TmpYloc := TmpYloc + 1;
             Done := True;
          end;
       If (done = False) AND (TmpXloc = TargetPlane.Xloc) AND
          (TmpYloc < TargetPlane.Yloc) then
          begin
             TmpYloc := TmpYloc + 1;
             Done := True;
          end;
       If (done = False) AND (TmpYloc = TargetPlane.Yloc) AND
          (TmpXloc < TargetPlane.Xloc) then
          begin
             TmpXloc := TmpXloc + 1;
             Done := True;
          end;
     until ((TmpXloc = TargetPlane.Xloc) and (TmpYloc = TargetPlane.Yloc))
           OR (counter = 11);
     SpaceRange := counter;
end;

{=========================================================================}

procedure PlacePlane(Plane: PlaneType);
var
   startlocx,startlocy: integer;
   rows:                integer;
   ActualLocx,ActualLocy: integer;
begin
     case Plane.Xloc of
        1: begin
                StartLocx := 3;
                StartLocy := 22;
                rows := 10;
           end;
        2: begin
                StartLocx := 3;
                StartLocy := 16;
                rows := 11;
           end;
        3: begin
                StartLocx := 6;
                StartLocy := 13;
                rows := 11;
           end;
        4: begin
                StartLocx := 9;
                StartLocy := 10;
                rows := 11;
           end;
        5: begin
                StartLocx := 12;
                StartLocy := 7;
                rows := 11;
           end;
        6: begin
                StartLocx := 15;
                StartLocy := 4;
                rows := 11;
           end;
        7: begin
                StartLocx := 18;
                StartLocy := 1;
                rows := 11;
           end;
        8: begin
                StartLocx := 24;
                StartLocy := 1;
                rows := 10;
           end;
        9: begin
                StartLocx := 30;
                StartLocy := 1;
                rows := 9;
           end;
        10: begin
                StartLocx := 36;
                StartLocy := 1;
                rows := 8;
           end;
        11: begin
                StartLocx := 42;
                StartLocy := 1;
                rows := 7;
           end;
       end;
       ActualLocX := StartLocX + (Rows-Plane.Yloc)*3;
       ActualLocY := StartLocY + (Rows-Plane.Yloc)*3;

       if Plane.Dead = False then begin
          Textcolor(Plane.Color);
          gotoxy(ActualLocX,ActualLocY+1);
          writeln('Ú');
          gotoxy(ActualLocX+1,ActualLocY+1);
          writeln('¿');
          gotoxy(ActualLocX,ActualLocY+2);
          writeln('­');
          gotoxy(ActualLocX+1,ActualLocY+2);
          writeln('­');
          gotoxy(ActualLocX,ActualLocY+3);
          writeln('´');
          gotoxy(ActualLocX+1,ActualLocY+3);
          writeln('Ã');
          gotoxy(ActualLocX-1,ActualLocY+3);
          writeln('Ð');
          gotoxy(ActualLocX+2,ActualLocY+3);
          writeln('Ð');
          gotoxy(ActualLocX,ActualLocY+4);
          writeln('Á');
          gotoxy(ActualLocX+1,ActualLocY+4);
          writeln('Á');



       end;



   textcolor(white);
end;

{=========================================================================}

Procedure ClearMap(A,B,C,D: PlaneType);
var
   counter: integer;
begin
   clrscr;
   textcolor(white);
   writeln('                 /\    /\    /\    /\    /\                 *');
   writeln('                /  \  /  \  /  \  /  \  /  \                *');
   writeln('               /    \/    \/    \/    \/    \               *');
   writeln('              /\ 90 /\ 70 /\ 50 /\ 30 /\ 10 /\              *');
   writeln('             /  \  /  \  /  \  /  \  /  \  /  \             *');
   writeln('            /    \/    \/    \/    \/    \/    \            *');
   writeln('           /\100 /\ 80 /\ 60 /\ 40 /\ 20 /\ 0  /\           *');
   writeln('          /  \  /  \  /  \  /  \  /  \  /  \  /  \          *');
   writeln('         /    \/    \/    \/    \/    \/    \/    \         *');
   writeln('        /\110 /\    /\    /\    /\    /\    /\180 /\        *');
   writeln('       /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \       *');
   writeln('      /    \/    \/    \/    \/    \/    \/    \/    \      *');
   writeln('     /\120 /\    /\    /\    /\    /\    /\    /\170 /\     *');
   writeln('    /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \    *');
   writeln('   /    \/    \/    \/    \/    \/    \/    \/    \/    \   *');
   writeln('  /\130 /\    /\    /\    /\    /\    /\    /\    /\160 /\  *');
   writeln(' /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \ *');
   writeln('/    \/    \/    \/    \/    \/    \/    \/    \/    \/    \*');
   writeln('\140 /\    /\    /\    /\    /\    /\    /\    /\    /\150 /*');
   writeln(' \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  / *');
   writeln('  \/    \/    \/    \/    \/    \/    \/    \/    \/    \/  *');
   writeln('  /\    /\    /\    /\    /\    /\    /\    /\    /\    /\  *');
   writeln(' /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \ *');
   writeln('/    \/    \/    \/    \/    \/    \/    \/    \/    \/    \*');
   writeln('\150 /\    /\    /\    /\    /\    /\    /\    /\    /\140 /*');
   writeln(' \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  / *');
   writeln('  \/    \/    \/    \/    \/    \/    \/    \/    \/    \/  *');
   writeln('   \160 /\    /\    /\    /\    /\    /\    /\    /\130 /   *');
   writeln('    \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /    *');
   writeln('     \/    \/    \/    \/    \/    \/    \/    \/    \/     *');
   writeln('      \170 /\    /\    /\    /\    /\    /\    /\120 /      *');
   writeln('       \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /       *');
   writeln('        \/    \/    \/    \/    \/    \/    \/    \/        *');
   writeln('         \180 /\    /\    /\    /\    /\    /\110 /         *');
   writeln('          \  /  \  /  \  /  \  /  \  /  \  /  \  /          *');
   writeln('           \/    \/    \/    \/    \/    \/    \/           *');
   writeln('            \ 0  /\ 20 /\ 40 /\ 60 /\ 80 /\100 /            *');
   writeln('             \  /  \  /  \  /  \  /  \  /  \  /             *');
   writeln('              \/    \/    \/    \/    \/    \/              *');
   writeln('               \ 10 /\ 30 /\ 50 /\ 70 /\ 90 /               *');
   writeln('                \  /  \  /  \  /  \  /  \  /                *');
   writeln('                 \/    \/    \/    \/    \/                 *');
   writeln('*************************************************************');
   writeln('                                                            *');
   writeln('                                                            *');
   writeln('                                                            *');
   writeln('                                                            *');
   writeln('                                                            *');
   writeln('                                                            * By Jason Fieldman');

   Printstats(A);
   Printstats(B);
   Printstats(C);
   Printstats(D);
end;

{=========================================================================}

Function RollRed(Dice: integer; Chaff: boolean): integer;
var
   total: integer;
   counter: integer;
   highest: integer;
   roll: integer;

begin
   total := 0;
   highest := 0;
   for counter := 1 to Dice do
   begin
       roll := random(2)+1;
       case roll of
          2: begin
               total := total + 2;
               if highest < 2 then highest := 2;
             end;
          3: begin
               total := total + 5;
               if highest < 5 then highest := 5;
             end;
       end;
   end;
   if chaff then total := total - 5;
   RollRed := Total;
end;

{=========================================================================}

Function RollBlack(Dice: integer): integer;
var
   counter: integer;
   total: integer;
   roll: integer;

begin
     total := 0;
     for counter := 1 to dice do
         begin
            roll := random(2)+1;
            total := total + roll;
         end;
     RollBlack := total;
end;

{=========================================================================}

Procedure GotoMini;
begin
     gotoxy(1,44);
end;

{=========================================================================}

Procedure ClearMini;
begin
     GotoMini;
   writeln('                                                            ');
   writeln('                                                            ');
   writeln('                                                            ');
   writeln('                                                            ');
   writeln('                                                            ');
   writeln('                                                            ');
end;

{=========================================================================}

Procedure ClearGoto;
begin
     ClearMini;
     GotoMini;
end;

{=========================================================================}

Procedure GetMove(Plane: PlaneType; var direction,range: DataArray);
var
   player: integer;
   otherplayer: integer;
   choice: char;
begin
    ClearGoto;
    if Plane.ID < 3 then Player := 1 else player := 2;
    if Player = 1 then otherplayer := 2 else otherplayer := 1;

    write('Player ',player,', choose one for ');
    textcolor(Plane.Color);
    writeln(Plane.name);
    textcolor(white);
    writeln('Player ',otherplayer,', turn your head please');
    writeln;
    writeln('1) Break Ahead  "³"');
    writeln('2) Break Left   "\"');
    writeln('3) Break Right  "/"');
    repeat
      choice := readkey;
    until (choice='1') or (choice='2') or (choice='3');
    case choice of
         '1': direction[plane.ID] := 1;
         '2': direction[plane.ID] := 2;
         '3': direction[plane.ID] := 3;
    end;
    ClearGoto;
    write('Player ',player,', choose one for ');
    textcolor(Plane.Color);
    writeln(Plane.name);
    textcolor(white);
    writeln('Player ',otherplayer,', turn your head please');
    writeln;
    writeln('1) Short Range   1-3  spaces');
    writeln('2) Medium Range  2-6  spaces');
    writeln('3) Long Range    4-12 spaces');
    repeat
      choice := readkey;
    until (choice='1') or (choice='2') or (choice='3');
    case choice of
         '1': range[plane.ID] := 1;
         '2': range[plane.ID] := 2;
         '3': range[plane.ID] := 3;
    end;

end;

{=========================================================================}

Function HowMany(a,b: PlaneType): integer;
var
   counter: integer;
   Moved: array [1..2] of integer;

begin
   counter := 0;
   if a.dead = False then counter := counter + 1;
   if b.dead = False then counter := counter + 1;
   HowMany := counter;
end;

{=========================================================================}

Procedure Attack(var Plane,Target: PlaneType);
var
   counter: integer;
   weaponchoice: char;
   chaffchoice: char;
   hit: boolean;
   roll: integer;

begin
   ClearGoto;
   writeln('Choose Weapon: ');
   writeln;
   if (CannonRange(Plane,Target)) and (Plane.Cannons > 0) then
   writeln('1) Cannons              | You have ',Plane.cannons,'/8');
   if Plane.LRM > 0 then
   writeln('2) Long Range Missles   | You have ',Plane.LRM,'/2');
   if Plane.MRM > 0 then
   writeln('3) Medium Range Missles | You have ',Plane.MRM,'/3');
   writeln('4) Abort attack run!');
   repeat
     weaponchoice := readkey;
   until ((weaponchoice='1') and (CannonRange(Plane,Target)) and (Plane.Cannons > 0)) OR
         ((Plane.LRM>0) and (weaponchoice='2')) OR
         ((Plane.MRM>0) and (weaponchoice='3')) OR
         (weaponchoice = '4');
   ClearGoto;
 If weaponchoice <> '4' then begin
   If (Target.Chaffs > 0) and (Weaponchoice <> '1') then
   begin
        textcolor(white);
        write('Will ');
        textcolor(Target.color);
        write(Target.Name);
        textcolor(white);
        writeln(' use a chaff?');
        writeln;
        writeln('1) Yes');
        writeln('2) No');
        repeat
            chaffchoice := readkey;
        until (chaffchoice = '1') or (chaffchoice = '2');
   end;

   ClearGoto;
   writeln('Attack being calculated...');

   case weaponchoice of
      '1': begin
             Roll := RollRed(2,False);
           end;
      '2': begin
             If Chaffchoice = '1' then
             begin
                  Target.Chaffs := Target.chaffs - 1;
                  Roll := RollRed(4,True);
             end
             else
             begin
                  Roll := RollRed(4,False);
             end;
           end;
      '3': begin
             If Chaffchoice = '1' then
             begin
                  Target.Chaffs := Target.Chaffs - 1;
                  Roll := RollRed(3,True);
             end
             else
             begin
                  Roll := RollRed(3,False);
             end;
           end;
   end;





 end;
end;


{=========================================================================}

Procedure DoMove(var Plane,B,C,D: PlaneType; Direction: DataArray;
                     Range: DataArray);
var
   counter: integer;
   TotalMoves: integer;
   Choice: char;
   Action: boolean;
   x: integer;
   buffer: char;
   targetchoice: char;
   Thing: integer;

begin
   action := false;
   case range[Plane.ID] of
        1: totalmoves := RollBlack(1);
        2: totalmoves := RollBlack(2);
        3: totalmoves := RollBlack(4);
   end;

   ClearGoto;
   writeln('Please select an option for ',Plane.Name,':');
   writeln;
   writeln('1) Perform Movement');
   writeln('2) Attemp To Attack ');
   writeln('3) Reload One Cannon Round');
   repeat
      choice := readkey;
   until (choice='1') OR
         ((Choice='2')) OR
         ((choice='3') AND (Plane.Cannons < 8));

   If choice = '3' Then
   begin
        Plane.Cannons := Plane.Cannons + 1;
        ClearGoto;
        textcolor(white);
        Writeln('Reloading complete, Press any key to begin movement.');
        buffer := readkey;
        for counter := 1 to TotalMoves do
        begin
             ClearGoto;
             textcolor(white);
             writeln('Now moving ',Plane.Name,' this number of spaces: ',totalmoves);
             Case direction[Plane.ID] of
                  1: begin
                       Plane.Xloc := Plane.Xloc + 1;
                       Plane.Yloc := Plane.Yloc + 1;
                     end;
                  2: Plane.Yloc := Plane.Yloc + 1;
                  3: Plane.Xloc := Plane.Xloc + 1;
             end;
             delay(800);
             Clearmap(Plane,B,C,D);
             PlacePlane(Plane);
             PlacePlane(B);
             PlacePlane(C);
             PlacePlane(D);

        end;
   end;

   If Choice = '2' Then
   begin


        thing := SpaceRange(Plane,B);
        ClearGoto;
        writeln('Who do you want to target?');
        writeln;
        textcolor(B.Color);
        if MissleRange(Plane,B) then writeln('1) ',B.Name,' who is ',Thing,' spaces away');
        textcolor(C.Color);
        thing := Spacerange(plane,C);
        if MissleRange(Plane,C) then writeln('2) ',C.Name,' who is ',thing,' spaces away');
        textcolor(D.Color);
        thing := Spacerange(Plane,D);
        if MissleRange(Plane,D) then writeln('3) ',D.Name,' who is ',thing,' spaces away');
        textcolor(white);
        writeln('4) None');
        repeat
          TargetChoice := readkey;
        until ((Targetchoice='1') AND (Misslerange(Plane,B))) or
              ((targetchoice='2') AND (MissleRange(plane,C))) or
              ((TargetChoice='3') AND (MissleRange(Plane,D))) or
              (Targetchoice = '4');

        if Targetchoice = '4' then
           DoMove(Plane,B,C,D,Direction,Range);
        Case Targetchoice of
             '1': Attack(Plane,B);
             '2': Attack(Plane,C);
             '3': Attack(Plane,D);
        end;

   end;




   If choice = '1' Then
   begin
   for counter := 1 to TotalMoves do
   begin
        ClearGoto;
        writeln('Now moving ',Plane.Name,' this number of spaces: ',totalmoves);
        Case direction[Plane.ID] of
          1: begin
               Plane.Xloc := Plane.Xloc + 1;
               Plane.Yloc := Plane.Yloc + 1;
             end;
          2: Plane.Yloc := Plane.Yloc + 1;
          3: Plane.Xloc := Plane.Xloc + 1;
        end;
        delay(800);
        Clearmap(Plane,B,C,D);
        PlacePlane(Plane);
        PlacePlane(B);
        PlacePlane(C);
        PlacePlane(D);
   end;
   end;


end;

{=========================================================================}

Procedure PerformMove(Player: integer; var A,B,C,D: PlaneType;
                      var Moved: MovedArray; Direction: DataArray;
                      range: dataArray);
var
   choice: char;


begin
     ClearGoto;
     textcolor(white);
     Writeln('Player ',Player,', which plane would you like to move?');
     writeln;

     if (moved[player] <> 1) and (A.Dead = False) then writeln('1) Plane ',A.ID,':  "',A.Name,'"');
     if (moved[player] <> 2) and (B.Dead = False) then writeln('2) Plane ',B.ID,':  "',B.Name,'"');
     repeat
        choice := readkey;
     until ( (Choice='1') and (moved[player] <> 1) and (A.Dead = False)) OR ((Choice='2')
           and (moved[player] <> 2) and (B.Dead = False) );
     if choice = '1' then moved[player] := 1;
     if choice = '2' then moved[player] := 2;


     if choice = '1' then DoMove(A,B,C,D,direction,range);
     if choice = '2' then DoMove(B,A,C,D,direction,range);


end;

{=========================================================================}

Procedure Move(var plane1,plane2,plane3,plane4: planetype;
               var Turn,Teamdead,turnnumber: integer);
var
   counter: integer;
   EnterKey: char;
   First1: boolean;
   direction, range: DataArray;
   moved: MovedArray;

begin
    textcolor(white);
    Moved[1] := 0;
    Moved[2] := 0;
    GotoMini;
    writeln;
    writeln;
    writeln('                       Turn number: ',Turnnumber);
    writeln('                 Press Any Key To Continue!');
    EnterKey := Readkey;
    ClearGoto;
    writeln;
    writeln('               ENTERING CHOOSE MOVEMENT PHASE');

    if (Turn mod 2 = 0) AND (Howmany(Plane1,Plane2)=HowMany(Plane3,Plane4))
       then First1 := False else First1 := True;
    if (Howmany(Plane1,Plane2)>Howmany(Plane3,Plane4)) then
       First1 := True;
    If (Howmany(Plane1,Plane2)<Howmany(Plane3,Plane4)) then
       First1 := False;



    if First1 then
        writeln('          Remember, Player 1 moves first this round.')
    else
        writeln('          Remember, Player 2 moves first this round.');
    writeln('                  Press RETURN to continue');
    readln;
    if not Plane1.Dead then GetMove(Plane1,direction,range);
    if not Plane2.Dead then GetMove(Plane2,direction,range);
    if not Plane3.Dead then GetMove(Plane3,direction,range);
    if not Plane4.Dead then GetMove(Plane4,direction,range);
    ClearGoto;
    writeln;
    writeln('                INITIATING MOVEMENT OF PLANES ');
    writeln('                ----------------------------- ');
    writeln('                   Press RETURN to continue   ');
    readln;
    ClearGoto;
    case first1 of
         True:  begin
                 PerformMove(1,Plane1,Plane2,Plane3,Plane4,Moved,direction,range);
                 PerformMove(2,Plane3,Plane4,Plane1,Plane2,Moved,direction,range);
                 PerformMove(1,Plane1,Plane2,Plane3,Plane4,Moved,direction,range);
                 PerformMove(2,Plane3,Plane4,Plane1,Plane2,Moved,direction,range);
                end;
         False: begin
                 PerformMove(2,Plane3,Plane4,Plane1,Plane2,Moved,direction,range);
                 PerformMove(1,Plane1,Plane2,Plane3,Plane4,Moved,direction,range);
                 PerformMove(2,Plane3,Plane4,Plane1,Plane2,Moved,direction,range);
                 PerformMove(1,Plane1,Plane2,Plane3,Plane4,Moved,direction,range);
                end;
    end;


end;

{=========================================================================}

Procedure Main;
var
   players: integer;
   OrigMode:  integer;
   Plane1,Plane2,Plane3,Plane4: Planetype;
   Turnnumber,teamdead,turn: integer;
begin
     randomize;
     Origmode := Lastmode;
     TextMode(C80 + Font8x8);
     Textcolor(white);
     nocursor;
     Intro;
     turn := 1;
     turnnumber := 1;
     teamdead := 0;
     {Options(Players);}

     GetNames(Plane1,Plane2,Plane3,Plane4);
     Plane1.ID := 1;
     Plane2.ID := 2;
     Plane3.ID := 3;
     Plane4.ID := 4;
     InitializePlane(Plane1);
     InitializePlane(Plane2);
     InitializePlane(Plane3);
     InitializePlane(Plane4);



     repeat

     Clearmap(plane1,plane2,plane3,plane4);
     PlacePlane(plane1);
     PlacePlane(plane2);
     PlacePlane(plane3);
     PlacePlane(plane4);
     Move(plane1,plane2,plane3,plane4,turn,teamdead,turnnumber);
     if teamdead = 0 then begin
        Turn := Turn + 1;
        Turnnumber := Turnnumber + 1;
     end;
     until Teamdead <> 0;

     Textmode(OrigMode);
end;

{=========================================================================}

Begin
     Main;
end.




          {     /\
               /Ú¿\
              / ­­ \
              \Ð´ÃÐ/
               \ÁÁ/
                \/          }









