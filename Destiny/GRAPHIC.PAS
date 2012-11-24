PROGRAM GRAPHIC_MAKER;
Uses crt,dos,vgaunit,vgapcx;


const
     Filee = 'credits';
var

   xctr, yctr, color: integer;
   fil: text;
   done: boolean;


Function getpixelVPP (x,y: integer): integer;
begin
     getpixelvpp := Mem [Vaddr:X+(Y*320)];
end;

Function getpixel (x,y: integer): integer;
begin
     getpixel := Mem [VGA:X+(Y*320)];
end;



begin
    clrscr;
    done := false;
    Assign(fil, 'c:\tp\destiny2\'+filee+'.dta');
    Rewrite(fil);
    writeln('Initiating...');

    SetMcga;
    DisplayPCX('c:\tp\destiny2\'+filee+'.pcx');{

    {Repeat
       read(fil, xctr);
       read(fil, yctr);
       readln(fil, color);
       if xctr = 999 then done := true;
       if xctr <> 999 then
       begin
          case color of

           255: PP(xctr, yctr, 31);
           140: PP(xctr, yctr, 31);
           20: PP(xctr, yctr, 31);
          end;
         { PP(xctr, yctr, color);
       end;


    until done;
    readln;  }

    for xctr := 0 to 319 do
    begin

         for yctr := 0 to 199 do
         begin

              color := GetPixel(xctr,yctr);
              if color <> 0 then
              begin
                   write(fil, xctr,' ');
                   write(fil, yctr,' ');
                   writeln(fil, color);
              end;

         end;

    end;
    writeln(fil, '999 999 999');
    close(fil);
    SetText;
    writeln('Yo');






end.