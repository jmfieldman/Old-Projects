{
        Jason Fieldman
        Advanced Programming
        Period 3

        "Underground Caverns"
}

program HrsQst(input,output);
uses crt;
{----------------------------------------------------------------}
{----------------------------------------------------------------}
procedure scroll(words:string; y:integer);
begin
     delay(00);
     textcolor(black);
     gotoxy(1,y);
     writeln(words);
     delay(25);
     textcolor(darkgray);
     gotoxy(1,y);
     writeln(words);
     textcolor(lightgray);
     delay(25);
     gotoxy(1,y);
     writeln(words);
     textcolor(white);
     gotoxy(1,y);
     delay(25);
     writeln(words);
     delay(00);
end;
{----------------------------------------------------------------}
{----------------------------------------------------------------}
procedure scroll2(words:string; y:integer);
begin
     delay(00);
     textcolor(black);
     gotoxy(1,y);
     writeln(words);
     delay(25);
     textcolor(darkgray);
     gotoxy(1,y);
     writeln(words);
     textcolor(lightgray);
     delay(25);
     gotoxy(1,y);
     writeln(words);
     textcolor(white);
     gotoxy(1,y);
     delay(25);
     write(words);
     delay(00);
end;
{----------------------------------------------------------------}
{----------------------------------------------------------------}
procedure titlescreen;
var
   la:char;
begin
     scroll('                             ÛßßßßßßßßßßßßßßßßßÛ',1);
     scroll('              ÛßßßßßßßßßßßßßßÛ ßßÛßß Û  Û Ûßßß ÛßßßßßßßßßßßßßßßÛ ',2);
     scroll('              Û              Û   Û   ÛßßÛ Ûßß  Û               Û',3);
     scroll('         Ûßßßßßßßßßßßßßßßßßßßß   ß   ß  ß ßßßß ßßßßßßßßßßßßßßßßßßßßßßßßÛ ',4);
     scroll('         Û Û   Û ÛÜ  Û ÛßßÜ Ûßßß ÛßßÜ Üßßß  ÛßßÜ ÜßßÜ Û   Û ÛÜ  Û ÛßßÜ Û',5);
     scroll('         Û Û   Û Û ßÜÛ Û  Û Ûßß  ÛßßÜ Û  ßÜ ÛßßÜ Û  Û Û   Û Û ßÜÛ Û  Û Û',6);
     scroll('         Û  ßßß  ß   ß ßßß  ßßßß Û  ß  ßßß  ß  ß  ßß   ßßß  ß   ß ßßß  Û',7);
     scroll('         ßßßßßÛßßßÛ Üßßß  ÜßßÜ Û Û Û Ûßßß ÛßßÜ ÛÜ  Û Üßßß  ÛßßßÛßßßßßßßß',8);
     scroll('              Û   Û Û     ÛßßÛ ÛÜ ÜÛ Ûßß  ÛßßÜ Û ßÜÛ  ßßßÜ Û   Û',9);
     scroll('              Û   Û  ßßß  ß  ß  Û Û  ßßßß ß  ß ß   ß ßßßß  Û   Û',10);
     scroll('              Û   ßßßßßßßßßßßßß ßÛß ßßßßßßßßßßßßßßßßßßßßßßßß   Û',11);
     scroll('              Û                  Û                             Û',12);
     scroll('              Û    ÜßßßßßÜ                                     Û',13);
     scroll('              Û    Û  Ûßß                                      Û',14);
     scroll('         ÛßÛßÛßÛßÛßÛ  ÛßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßÛÛÛÛÛÛÜÜÜ',15);
     scroll('         Û Û Û Û Û Û  ÛßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßÛÛÛÛÛÛÛßß',16);
     scroll('         ßßßßßÛßßßßÛ  ÛßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßÛßßß   ',17);
     scroll('              Û    Û  ßßßÜ                                     Û    ',18);
     scroll('              Û     ßßßßß     by: Jason Fieldman               Û     Û  ',19);
     scroll('               ßßßÜÜÜ                                    ÜÜÜßßß     ÛÛÛ ',20);
     scroll('                     ßßßÜÜÜ                        ÜÜÜßßß            ß ',21);
     scroll('                           ßßßßßßßßßßßßßßßßßßßßßßßß                 ',22);

     textcolor(black);
     writeln;
     la := readkey;
     clrscr;
     scroll('                      şşşşşşşşşşşşşşşşşşşşşşşşşşşşşşşşşş',9);
     scroll('                             Based on "Hero Quest"        ',10);
     scroll('                      Copywrite 1989,1990 Milton Bradley',11);
     scroll('                      şşşşşşşşşşşşşşşşşşşşşşşşşşşşşşşşşş',12);
     textcolor(black);
     writeln;
     la := readkey;
     clrscr;
     delay(500);
end;
{----------------------------------------------------------------}
{----------------------------------------------------------------}
procedure introfor1;
var
   ctr,ctr2: longint;
begin
     clrscr;
     textcolor(darkgray);
     ctr2 := 0;
     repeat
     for ctr := 1 to 1000 do
         write('ÛÛÛÛÛ');
     clrscr;
     delay(50);
     ctr2 := ctr2 + 1;
     until ctr2 = 3;
     clrscr;
     delay(250);
     scroll('In the peaceful kingdom of Tynsirtin, under the rule of the good Emperor Hyrus',1);
     scroll('Druxinon, a new Orc Warlord has taken power of the old Underground caverns of',2);
     scroll('the First Empire.  Druxinon has called mercinaries from all the land to fight',3);
     scroll('off the threat of this new Warlord, Ulag.  You are a lone warrior, trying to ',4);
     scroll('earn an honest buck.  As you approach the castle of the Emperor, you are in ',5);
     scroll('in shock that you are the only one there.  The Emperor sounds desperate, he ',6);
     scroll('asks you if you know anything about the new underground system of orcs.  After',7);
     scroll('responding no, the Emperor gives you your first quest, to find any documents',8);
     scroll('conserning this new threat to Empire.  If you succeed, the Emperor is planning',9);
     scroll('on paying a large sum of money, 300 gold, for any satisfing evidence where Ulag',10);
     scroll('might be basing his new clan.',11);
     textcolor(black);
     writeln;
     readln;
     clrscr;
     delay(250);
     scroll('                                 ş QUEST ONE ş',11);
     scroll('                           find documents about Ulag',12);
     textcolor(black);
     writeln;
     delay(4000);
end;
{----------------------------------------------------------------}
{----------------------------------------------------------------}
procedure outline(health,armor,weapon: integer; gold:longint);
begin
    textcolor(white);
    writeln('ÚÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄ¿±Hit Pts: ',health);
    writeln('³        ³        ³        ³        ³        ³        ³        ³±Armor: ',armor);
    writeln('³        ³        ³        ³        ³        ³        ³        ³±Weapon: ',weapon);
    writeln('³        ³        ³        ³        ³        ³        ³        ³±Gold: ',gold);
    writeln('ÃÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ´±');
    writeln('³        ³        ³        ³        ³        ³        ³        ³±Items:');
    writeln('³        ³        ³        ³        ³        ³        ³        ³±1)');
    writeln('³        ³        ³        ³        ³        ³        ³        ³±2)');
    writeln('ÃÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ´±3)');
    writeln('³        ³        ³        ³        ³        ³        ³        ³±4)');
    writeln('³        ³        ³        ³        ³        ³        ³        ³±5)');
    writeln('³        ³        ³        ³        ³        ³        ³        ³±6)');
    writeln('ÃÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ´±7)');
    writeln('³        ³        ³        ³        ³        ³        ³        ³±8)');
    writeln('³        ³        ³        ³        ³        ³        ³        ³±9)');
    writeln('³        ³        ³        ³        ³        ³        ³        ³±');
    writeln('ÃÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄ´±');
    writeln('³        ³        ³        ³        ³        ³        ³        ³±');
    writeln('³        ³        ³        ³        ³        ³        ³        ³±');
    writeln('³        ³        ³        ³        ³        ³        ³        ³±');
    writeln('ÀÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÙ±');
    writeln('±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±± ');
                textcolor(darkgray);
                gotoxy(29,10);
                write('   ê ');
                textcolor(lightgray);
                writeln('³');
                gotoxy(29,11);
                textcolor(red);
                write(' Ü');
                textcolor(darkgray);
                write('/³\');
                textcolor(brown);
                writeln('Å');
                gotoxy(29,12);
                textcolor(darkgray);
                writeln('  / \');
                textcolor(white);
end;

{----------------------------------------------------------------}
{----------------------------------------------------------------}
procedure drawpiece(xx,yy:integer; piecetype:longint);
var
   ctr1,ctr2,ffff,check:integer;

begin

     case piecetype of
          1:begin
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('      ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('      ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('     ');
          end;

          2:begin
                textcolor(darkgray);
                gotoxy((xx*9)-7,(yy*4)-2);
                write('   ê ');
                textcolor(lightgray);
                writeln('³');
                gotoxy((xx*9)-7,(yy*4)-1);
                textcolor(red);
                write(' Ü');
                textcolor(darkgray);
                write('/³\');
                textcolor(brown);
                writeln('Å');
                gotoxy((xx*9)-7,(yy*4));
                textcolor(darkgray);
                writeln('  / \');
                textcolor(white);

          end;
          3:begin
                textcolor(brown);
                gotoxy((xx*9)-6,(yy*4)-2);
                writeln('ÚÄÄÄÄÄÄÄ');
                gotoxy((xx*9)-6,(yy*4)-1);
                writeln('³       ');
                gotoxy((xx*9)-6,(yy*4));
                writeln('ÀÄÄÄÄÄÄÄ');

          end;
          4:begin
                textcolor(brown);
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('ÄÄÄÄÄÄÄÄÄ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('         ');
                gotoxy((xx*9)-8,(yy*4));
                writeln('ÄÄÄÄÄÄÄÄÄ');
          end;
          5:begin
                textcolor(brown);
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('ÄÄÄÄÄÄÄ¿');
                gotoxy((xx*9)-8,(yy*4)-1);
                textcolor(yellow);
                write(' ºÛ  ');
                textcolor(brown);
                writeln('  ³');
                gotoxy((xx*9)-8,(yy*4));
                writeln('ÄÄÄÄÄÄÄÙ');
          end;
          6:begin
                textcolor(brown);
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('ÚÄÄÄÄÄÄ¿');
                gotoxy((xx*9)-7,(yy*4)-1);
                write('³  ');
                textcolor(yellow);
                write('ºÛ');
                textcolor(brown);
                writeln('  ³');
                gotoxy((xx*9)-7,(yy*4));
                writeln('³      ³');
          end;
          7:begin
                textcolor(brown);
                gotoxy((xx*9)-7,(yy*4)-3);
                writeln('³      ³');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('³      ³');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('³      ³');
                gotoxy((xx*9)-7,(yy*4));
                writeln('³      ³');
          end;
          8:begin
                textcolor(brown);
                gotoxy((xx*9)-7,(yy*4)-3);
                writeln('³      ³');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('³      ³');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('³      ³');
                gotoxy((xx*9)-7,(yy*4));
                writeln('ÀÄÄÄÄÄÄÙ');
          end;
          9:begin
               { textcolor(lightgray);  }
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('        ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('   ÚÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4)-0);
                writeln('   ³    ');
                gotoxy((xx*9)-7,(yy*4)+1);
                writeln('   ³    ');
          end;
          10:begin
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('         ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄÄÄÄÄ');
                gotoxy((xx*9)-8,(yy*4)-0);
                writeln(' ÚÄÄÂÄÄ¿ ');
                gotoxy((xx*9)-8,(yy*4)+1);
                writeln(' ³@#³$&³');
          end;
          11:begin
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('         ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄ¿   ');
                gotoxy((xx*9)-8,(yy*4));
                writeln('     ³   ');
                gotoxy((xx*9)-8,(yy*4)+1);
                writeln('     ³   ');
          end;
          12:begin
                gotoxy((xx*9)-7,(yy*4)-3);
                writeln('   ³      ');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('   ³    ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('   ÀÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('          ');
          end;
          13:begin
                gotoxy((xx*9)-8,(yy*4)-3);
                writeln(' ³÷÷³÷÷³  ');
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln(' ÀÄÄÁÄÄÙ  ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('         ');
          end;
          14:begin
                gotoxy((xx*9)-8,(yy*4)-3);
                writeln('     ³   ');
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('     ³   ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄÙ   ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('        ');

          end;
          15:begin
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('      ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('  ÚÄÄÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('  ³    ');
          end;
          16:begin
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('      ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄÄÄ¿');
                gotoxy((xx*9)-8,(yy*4));
                writeln('       ³');
          end;
          17:begin
                gotoxy((xx*9)-7,(yy*4)-3);
                writeln('  ³       ');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('  ³   ÚÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('  ³   ÃÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('  ³   ÀÄÄÄÄ');
           end;
           18:begin
                gotoxy((xx*9)-8,(yy*4)-3);
                writeln('       ³ ');
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('ÄÄÄ¿   ³ ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄ´   ³ ');
                gotoxy((xx*9)-8,(yy*4));
                writeln('ÄÄÄÙ   ³ ');
           end;
           19:begin
                gotoxy((xx*9)-7,(yy*4)-3);
                writeln('  ³     ');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('  ³     ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('  ÀÄÄÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('           ');
           end;
           20:begin
                gotoxy((xx*9)-8,(yy*4)-3);
                writeln('       ³ ');
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('       ³ ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄÄÄÙ ');
                gotoxy((xx*9)-8,(yy*4));
                writeln('        ');
           end;
           21:begin
                textcolor(lightgray);
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('ÚÄÄÄÄÄÂÄÄ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('³    ÚÁÄÄ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('³   ÚÁÄÄÄ');
           end;
           22:begin
                textcolor(lightgray);
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('ÄÄÂÄÄÄÄÄ¿');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÁ¿    ³');
                gotoxy((xx*9)-8,(yy*4));
                writeln('ÄÄÄÁ¿   ³');
          end;
          23:begin
                textcolor(lightgray);
                gotoxy((xx*9)-7,(yy*4)-3);
                writeln('³  ÚÁÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('³ ÚÁÄÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('³ÚÁÄÄÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('ÀÁÄÄÄÄÄÄÄ');
          end;
          24:begin
                textcolor(lightgray);
                gotoxy((xx*9)-8,(yy*4)-3);
                writeln('ÄÄÄÄÁ¿  ³');
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('ÄÄÄÄÄÁ¿ ³');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄÄÁ¿³');
                gotoxy((xx*9)-8,(yy*4));
                writeln('ÄÄÄÄÄÄÄÁÙ');
          end;
          25:begin
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('        ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('   ÚÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4)-0);
                writeln('   ÃÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4)+1);
                writeln('   ³    ');
          end;
          26:begin
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('         ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄÄÄÄÄ');
                gotoxy((xx*9)-8,(yy*4)-0);
                writeln('ÄÄÄÄÄÄÄÄÄ');
                gotoxy((xx*9)-8,(yy*4)+1);
                writeln('  ÚÄ¿ Ä®®');
          end;
          27:begin
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('         ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄ¿   ');
                gotoxy((xx*9)-8,(yy*4));
                writeln('ÄÄÄÄÄ´   ');
                gotoxy((xx*9)-8,(yy*4)+1);
                writeln('     ³   ');
          end;
          28:begin
                gotoxy((xx*9)-7,(yy*4)-3);
                writeln('   ³      ');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('   ³    ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('   ÀÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('          ');
          end;
          29:begin
                {gotoxy((xx*9)-8,(yy*4)-3);
                writeln('         ');       }
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('  ÀÄÙ o  ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('         ');
          end;
          30:begin
                gotoxy((xx*9)-8,(yy*4)-3);
                writeln('     ³   ');
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('     ³   ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄÙ   ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('        ');

          end;
          31:begin
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('      ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('  ÚÄÂÄÄÄ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('  ³ ³   ');
          end;
          32:begin
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('      ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄÄÄ¿');
                gotoxy((xx*9)-8,(yy*4));
                writeln('      ³');
          end;
          33:begin
                gotoxy((xx*9)-7,(yy*4)-3);
                writeln('  ³ ³      ');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('  ³ ³      ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('  ³ ³      ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('  ³ ³      ');
           end;
           34:begin
                gotoxy((xx*9)-8,(yy*4)-3);
                writeln(' ³ o   ³ ');
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('ÚÄÄÄ¿  ³ ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÀÄÄÄÙ  ³ ');
                gotoxy((xx*9)-8,(yy*4));
                writeln('       ³ ');
           end;
           35:begin
                gotoxy((xx*9)-7,(yy*4)-3);
                writeln('  ³ ³   ');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('  ³ ³   ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('  ÀÄÁÄÄÄ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('           ');
           end;
           36:begin
                gotoxy((xx*9)-8,(yy*4)-3);
                writeln('       ³ ');
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('       ³ ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄÄÄÙ ');
                gotoxy((xx*9)-8,(yy*4));
                writeln('        ');
           end;
           37:begin
                gotoxy((xx*9)-7,(yy*4)-2);
                textcolor(brown);
                write('Û');
                textcolor(brown);
                write('ÛÛÛÛÛÛ');
                textcolor(brown);
                writeln('Û');
                gotoxy((xx*9)-7,(yy*4)-1);
                textcolor(brown);
                write('Û');
                textcolor(red);
                write('ÛÛÛÛÛÛ');
                textcolor(brown);
                writeln('Û');
                gotoxy((xx*9)-7,(yy*4));
                textcolor(brown);
                write('Û');
                textcolor(red);
                write('ÛÛÛÛÛÛ');
                textcolor(brown);
                writeln('Û');
           end;
           38:begin
                gotoxy((xx*9)-7,(yy*4)-2);
                textcolor(brown);
                write('Û');
                textcolor(red);
                write('ÛÛÛÛÛÛ');
                textcolor(brown);
                writeln('Û');
                gotoxy((xx*9)-7,(yy*4)-1);
                textcolor(brown);
                write('Û');
                textcolor(red);
                write('ÛÛÛÛÛÛ');
                textcolor(brown);
                writeln('Û');
                gotoxy((xx*9)-7,(yy*4));
                textcolor(brown);
                write('Û');
                textcolor(brown);
                write('ÛÛÛÛÛÛ');
                textcolor(brown);
                writeln('Û');
           end;

          39:begin
                textcolor(darkgray);
                gotoxy((xx*9)-6,(yy*4)-2);
                writeln('ÚÄÄÄÄÄÄÄ');
                gotoxy((xx*9)-6,(yy*4)-1);
                writeln('³       ');
                gotoxy((xx*9)-6,(yy*4));
                writeln('ÀÄÄÄÄÄÄÄ');

          end;
          40:begin
                textcolor(darkgray);
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('ÂÄÄÄÄÄÄÄÄ');
                gotoxy((xx*9)-8,(yy*4)-1);
                write('³ ');
                textcolor(brown);
                write('ÜÜÜÜÜÜ');
                textcolor(darkgray);
                writeln(' ');
                gotoxy((xx*9)-8,(yy*4));
                writeln('ÁÄÄßÄÄßÄÄ');
          end;
          41:begin
                textcolor(darkgray);
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('ÂÄÄÄÄÄÄ¿');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('³      ³');
                gotoxy((xx*9)-8,(yy*4));
                writeln('ÁÄÄÄÄÄÄÙ');
          end;
          42:begin
                textcolor(darkgray);
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('ÚÄÄÄÄÄÄ¿');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('³      ³');
                gotoxy((xx*9)-7,(yy*4));
                writeln('³      ³');
          end;
          43:begin
                textcolor(darkgray);
                gotoxy((xx*9)-7,(yy*4)-3);
                writeln('ÃÄÄÄÄÄÄ´');
                gotoxy((xx*9)-7,(yy*4)-2);
                write('³    ');
                textcolor(brown);
                write('Û');
                textcolor(darkgray);
                write('Ä´');
                gotoxy((xx*9)-7,(yy*4)-1);
                write('³    ');
                textcolor(brown);
                write('Û');
                textcolor(darkgray);
                write(' ³');
                gotoxy((xx*9)-7,(yy*4));
                write('³    ');
                textcolor(brown);
                write('Û');
                textcolor(darkgray);
                write('Ä´');
          end;
          44:begin
                textcolor(darkgray);
                gotoxy((xx*9)-7,(yy*4)-3);
                writeln('ÃÄÄÄÄÄÄ´');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('³      ³');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('³      ³');
                gotoxy((xx*9)-7,(yy*4));
                writeln('ÀÄÄÄÄÄÄÙ');
          end;
          45:begin
                textcolor(brown);
                gotoxy((xx*9)-6,(yy*4)-2);
                writeln('ÚÄÄÄÄÄÄÄ');
                gotoxy((xx*9)-6,(yy*4)-1);
                writeln('³  ÄÄ   ');
                gotoxy((xx*9)-6,(yy*4));
                writeln('ÀÄÄÄÄÄÄÄ');

          end;
          46:begin
                textcolor(brown);
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('ÂÄÄÄÄÄÄÄÄÂ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('³   ÄÄ   ³');
                gotoxy((xx*9)-8,(yy*4));
                writeln('ÁÄÄÄÄÄÄÄÄÁ');
          end;
          47:begin
                textcolor(brown);
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('ÄÄÄÄÄÄ¿');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('  ÄÄ  ³');
                gotoxy((xx*9)-7,(yy*4));
                writeln('ÄÄÄÄÄÄÙ');
          end;
          48:begin
                textcolor(brown);
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('ÚÄÄÄÄÄÄ¿');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('³  ³   ³');
                gotoxy((xx*9)-7,(yy*4));
                writeln('³      ³');
          end;
          49:begin
                textcolor(brown);
                gotoxy((xx*9)-7,(yy*4)-3);
                writeln('ÃÄÄÄÄÄÄ´');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('³      ³');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('³  ³   ³');
                gotoxy((xx*9)-7,(yy*4));
                writeln('³      ³');
          end;
          50:begin
                textcolor(brown);
                gotoxy((xx*9)-7,(yy*4)-3);
                writeln('ÃÄÄÄÄÄÄ´');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('³      ³');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('³  ³   ³');
                gotoxy((xx*9)-7,(yy*4));
                writeln('ÀÄÄÄÄÄÄÙ');
          end;
          51:begin
               { textcolor(lightgray);  }
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('        ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('   ÚÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4)-0);
                writeln('   ³    ');
                gotoxy((xx*9)-7,(yy*4)+1);
                writeln('   ³    ');
          end;
          52:begin
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('         ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄÄÄÄÄ');
                gotoxy((xx*9)-8,(yy*4)-0);
                writeln('  R.I.P  ');
                gotoxy((xx*9)-8,(yy*4)+1);
                writeln('    ',chr(15),'     ');
          end;
          53:begin
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('         ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄ¿   ');
                gotoxy((xx*9)-8,(yy*4));
                writeln('     ³   ');
                gotoxy((xx*9)-8,(yy*4)+1);
                writeln('     ³   ');
          end;
          54:begin
                textcolor(white);
                gotoxy((xx*9)-7,(yy*4)-3);
                writeln('   ³      ');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('   ³    ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('   ÀÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('          ');
          end;
          55:begin
                textcolor(white);
                gotoxy((xx*9)-8,(yy*4)-3);
                writeln('   ',chr(15),'',chr(15),'',chr(15),'      ');
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('   ³³³   ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄÄÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('         ');
          end;
          56:begin
                gotoxy((xx*9)-8,(yy*4)-3);
                writeln('     ³   ');
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('     ³   ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄÙ   ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('        ');

          end;
          57:begin
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('      ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('  ÚÄÄÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('  ³   R.');
          end;
          58:begin
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('      ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄÄÄ¿');
                gotoxy((xx*9)-8,(yy*4));
                writeln('I.P    ³');
          end;
          59:begin
                gotoxy((xx*9)-7,(yy*4)-3);
                writeln('  ³    ',#15,'',#15,'',#15,'   ');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('  ³    ³³³    ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('  ³        ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('  ³        ');
           end;
           60:begin
                gotoxy((xx*9)-8,(yy*4)-3);
                writeln(#15,'',#15,'     ³ ');
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('³³     ³ ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('       ³ ');
                gotoxy((xx*9)-8,(yy*4));
                writeln('       ³ ');
           end;
           61:begin
                gotoxy((xx*9)-7,(yy*4)-3);
                writeln('  ³     ');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('  ³     ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('  ÀÄÄÄÄÄÄ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('           ');
           end;
           62:begin
                gotoxy((xx*9)-8,(yy*4)-3);
                writeln('       ³ ');
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('       ³ ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('ÄÄÄÄÄÄÄÙ ');
                gotoxy((xx*9)-8,(yy*4));
                writeln('        ');
           end;
           99:begin
                textcolor(darkgray);
                gotoxy((xx*9)-7,(yy*4)-2);
                write('   ê ');
                textcolor(lightgray);
                writeln('³');
                gotoxy((xx*9)-7,(yy*4)-1);
                textcolor(red);
                write(' Ü');
                textcolor(darkgray);
                write('/³\');
                textcolor(brown);
                writeln('Å');
                gotoxy((xx*9)-7,(yy*4));
                textcolor(darkgray);
                writeln('  / \');
                textcolor(white);

          end;
       end;

end;
{----------------------------------------------------------------}
{----------------------------------------------------------------}
procedure drawtile(xx,yy:integer; walltype:longint; x:integer);
var
   ctr1,ctr2,ffff,check:integer;

begin

     case walltype of
          1:begin


                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('       ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('       ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('       ');
          end;
          2:begin
                textcolor(white);
                gotoxy((xx*9)-7,(yy*4)-3);
                write('ÄÄÄÄÄÄÄÄ');
                textcolor(darkgray);
                writeln('Û');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('        Û');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('        Û');
                gotoxy((xx*9)-7,(yy*4));
                writeln('        Û');
                gotoxy((xx*9)-7,(yy*4)+1);
                textcolor(white);
                write('ÄÄÄÄÄÄÄÄ');
                textcolor(darkgray);
                writeln('Û');
                textcolor(white);
          end;
          3:begin
                textcolor(darkgray);
                gotoxy((xx*9)-8,(yy*4)-3);
                writeln('ÛÛÛÛÛÛÛÛÛÛ');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('       ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('       ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('       ');
                textcolor(white);
          end;
          4:begin
                textcolor(darkgray);
                gotoxy((xx*9)-8,(yy*4)-3);
                writeln('ÛÛÛÛÛÛÛÛÛÛ');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('        Û');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('        Û');
                gotoxy((xx*9)-7,(yy*4));
                writeln('        Û');
                textcolor(white);
                gotoxy((xx*9)-7,(yy*4)+1);
                write('ÄÄÄÄÄÄÄÄ');
                textcolor(darkgray);
                writeln('Û');
                textcolor(white);
          end;
          5:begin
                textcolor(darkgray);
                if x <> 30 then begin
                gotoxy((xx*9)-8,(yy*4)-3);
                writeln('          ');
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('          ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('          ');
                gotoxy((xx*9)-8,(yy*4));
                writeln('          ');
                gotoxy((xx*9)-8,(yy*4)+1);
                writeln('          ');
                end;
                if x = 30 then begin
                gotoxy((xx*9)-7,(yy*4)-3);
                writeln('          ');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('          ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('          ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('          ');
                gotoxy((xx*9)-7,(yy*4)+1);
                writeln('          ');
                textcolor(white);
                end;
          end;
          6:begin
                textcolor(darkgray);
                gotoxy((xx*9)-8,(yy*4)-3);
                writeln('         Û');
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('         Û');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('         Û');
                gotoxy((xx*9)-8,(yy*4));
                writeln('         Û');
                gotoxy((xx*9)-8,(yy*4)+1);
                writeln('         Û');
                textcolor(white);
          end;
          7:begin
                textcolor(darkgray);
                gotoxy((xx*9)-8,(yy*4)-3);
                writeln('ÛÛÛÛÛÛÛÛÛÛ');
                gotoxy((xx*9)-8,(yy*4)-2);
                writeln('          ');
                gotoxy((xx*9)-8,(yy*4)-1);
                writeln('          ');
                gotoxy((xx*9)-8,(yy*4));
                writeln('          ');
                gotoxy((xx*9)-8,(yy*4)+1);
                writeln('          ');
                textcolor(white);
          end;
          8:begin
                textcolor(brown);
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('        Û');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('        Û');
                gotoxy((xx*9)-7,(yy*4));
                writeln('        Û');
                textcolor(white);
          end;
          9:begin
                textcolor(brown);
                gotoxy((xx*9)-7,(yy*4)-3);
                writeln('ßßßßßßßß');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('        ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('       ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('        ');
                textcolor(white);
          end;
          10:begin
                textcolor(white);
                gotoxy((xx*9)-7,(yy*4)-3);
                write('ÄÄÄÄÄÄÄÄ');
                textcolor(darkgray);
                writeln('Û');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('        Û');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('        Û');
                gotoxy((xx*9)-7,(yy*4));
                writeln('        Û');
                gotoxy((xx*9)-7,(yy*4)+1);
                textcolor(white);
                write('ÄÄÄÄÄÄÄÄ');
                textcolor(darkgray);
                writeln('Û');
                textcolor(white);
          end;
          11:begin
                textcolor(darkgray);
                gotoxy((xx*9)-8,(yy*4)-3);
                writeln('ÛÛÛÛÛÛÛÛÛÛ');
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('       ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('       ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('       ');
                textcolor(white);
          end;
       end;

end;
{----------------------------------------------------------------}
{----------------------------------------------------------------}
procedure drawmonster(xx,yy:integer; monstertype:longint);
begin
     case monstertype of
          1:begin
                gotoxy((xx*9)-7,(yy*4)-2);
                writeln('       ');
                gotoxy((xx*9)-7,(yy*4)-1);
                writeln('       ');
                gotoxy((xx*9)-7,(yy*4));
                writeln('       ');
            end;

          2:begin
                textcolor(darkgray);
                gotoxy((xx*9)-7,(yy*4)-2);
                write('   ê ');
                textcolor(lightgray);
                writeln('³');
                gotoxy((xx*9)-7,(yy*4)-1);
                textcolor(red);
                write(' Ü');
                textcolor(darkgray);
                write('/³\');
                textcolor(brown);
                writeln('Å');
                gotoxy((xx*9)-7,(yy*4));
                textcolor(darkgray);
                writeln('  / \');
                textcolor(white);
            end;

end;
end;

{--------------------------------------}
{-------------------------------------}
procedure fight(var health,xxxxx,armor,weapon,c,d: integer; var gold,monster: longint);
var
   hit,defend,damage,
   x,y,didhit,defence,damagetoyou,
   damagetomon,monweapon,monarmor,
   monhitpnts,goldrecieved: integer;
   monsterdead,playerdead:string[10];
begin
     clrscr;
     writeln('The monster approaches...');
     writeln;
     playerdead := 'no';
     delay(2000);
     monarmor:=1;
     monweapon:=2;
     monhitpnts:=5;
     monsterdead := 'no';
     repeat





        defence:=0;
        writeln('You swing your sword at the monster...');
        delay(2000);
        damage := 0;
        for x := 1 to weapon do begin
            didhit:=random(6)+1;
            if (didhit<4) then damage:=damage+1;
        end;
        if damage=0 then begin
           writeln('You wildly swing and miss...');
           writeln;
        end;
        if damage=1 then writeln('You hit 1 time...');
        if damage>1 then writeln('You hit ',damage,' times...');
        delay(1500);
        if damage>0 then begin
           for x := 1 to monarmor do begin
               didhit:=random(6)+1;
               if didhit=1 then begin
                  damage:=damage-1;
                  defence:=defence+1;
               end;
           end;
           if defence=0 then writeln('All of your swings go through the monster''s armor...');
           if defence=1 then writeln('The monster''s armor defends one hit...');
           if defence>1 then writeln('The monster''s armor defends ',defence,' hits...');
           delay(1500);

           if damage=0 then writeln('The monster does not lose any health...');
           if damage=1 then writeln('The monster loses 1 point of health...');
           if damage>1 then writeln('The monster loses ',damage,' points of health...');
           delay(1500);
           monhitpnts:=monhitpnts-damage;
           if monhitpnts<1 then writeln('The monster is dead!');
           if monhitpnts=1 then writeln('The monster has 1 hit point left...');
           if monhitpnts>1 then writeln('The monster has ',monhitpnts,' points left...');
           delay(1500);

           writeln;

           if monhitpnts<1 then
              monsterdead := 'yes';
        end;


     if monsterdead <> 'yes' then begin
        writeln;
        defence:=0;
        damage:=0;
        writeln('The monster strikes you...');
        delay(2000);
        damage := 0;
        for x := 1 to monweapon do begin
            didhit:=random(6)+1;
            if (didhit<4) then damage:=damage+1;
        end;
        if damage=0 then begin
           writeln('The monster wildly swings and misses...');
           writeln;
        end;
        if damage=1 then writeln('The monster hits you 1 time...');
        if damage>1 then writeln('The monster hits you ',damage,' times...');
        delay(1500);
        if damage>0 then begin
           for x := 1 to armor do begin
               didhit:=random(6)+1;
               if didhit<3 then begin
                  damage:=damage-1;
                  defence:=defence+1;
               end;
           end;
           if defence=0 then writeln('All of the monster''s swings go through your armor...');
           if defence=1 then writeln('Your armor defends one hit...');
           if defence>1 then writeln('Your armor defends ',defence,' hits...');
           delay(1500);

           if damage=0 then writeln('You do not lose any health...');
           if damage=1 then writeln('You lose 1 point of health...');
           if damage>1 then writeln('You lose ',damage,' points of health...');
           delay(1500);
           health:=health-damage;
           if health<1 then writeln('You are dead!');
           if health=1 then writeln('You have 1 hit point left...');
           if health>1 then writeln('You have ',health,' hit points left...');
           delay(1500);

           writeln;

           if health<1 then
              playerdead := 'yes';
        end;

       end;


     until (monsterdead = 'yes') or (playerdead='yes');

     if monsterdead = 'yes' then begin
     goldrecieved := random(19)+2;
     writeln('You find ',goldrecieved,' pieces of gold on the monster - Good Job!');
     readln;
     gold := gold + goldrecieved;

     clrscr;
     outline(health,armor,weapon,gold);
     end;

     if playerdead = 'yes' then begin
        writeln;
        writeln('You lose!!!');
        xxxxx := 0;
        readln;
        clrscr;
        outline(health,armor,weapon,gold);
     end;




end;




{------------------------------------------------------------}
{-----------------------------------------------------------}
procedure game(var xxxxx,check,maker,monstercheck: integer; scrol:string);
var
   walltype,piecetype,monstertype,hasmoved: array[1..32,1..23] of longint;
   cansee: array[1..32,1..23] of string[3];
   xaxis,yaxis,der,suby,subx,x,y,xx,yy,xcal,ycal: integer;
   move: char;
   ctr1,ctr2,wherex,wherey,ffff,xfile,yfile,caridge:integer;
   xcounter,ycounter,checkmove: integer;
   f: text;
   health,armor,weapon:integer;
   gold:longint;
   itemname: array[1..9] of string[12];
   itemnumber: array[1..9] of integer;

begin

     if maker = 0 then begin
        health:=10;
        armor:=2;
        weapon:=3;
        gold:=100;
        for ctr1:= 1 to 9 do
            itemnumber[ctr1] := 0;
        itemnumber[1] := 1;
        for ctr1 := 1 to 32 do begin
            for ctr2 := 1 to 23 do begin
                piecetype[ctr1][ctr2] := 1;
                walltype[ctr1][ctr2] := 1;
            end;
        end;
        {declare walls}

            assign(f,'c:\games\hrsqst\walls1.dat');
            reset(f);
            for yfile := 1 to 23 do begin
                for xfile := 1 to 32 do begin
                    read(f,walltype[xfile][yfile]);
                end;
                readln(f,caridge);
            end;
            close(f);
        {declare monsters
            assign(f,'d:monster1.dat');
            reset(f);
            for yfile := 1 to 23 do begin
                for xfile := 1 to 32 do begin
                    read(f,monstertype[xfile][yfile]);
                end;
                readln(f,caridge);
            end;
            close(f);
        {declare pieces}
            assign(f,'c:\games\hrsqst\pieces1.dat');
            reset(f);
            for yfile := 1 to 23 do begin
                for xfile := 1 to 32 do begin
                    read(f,piecetype[xfile][yfile]);
                end;
                readln(f,caridge);
            end;
            close(f);
            for ctr1 := 1 to 32 do begin
                for ctr2 :=  1 to 23 do begin
                   cansee[ctr1][ctr2] := 'no';

                end;
            end;

     maker := 1;
     end;



    textcolor(white);
   { maker:=0;}
    clrscr;
    outline(health,armor,weapon,gold);
    xaxis:=0;
    yaxis:=0;
    if check = 0 then begin
      x:=11;
      y:=15;
      check := 1;
    end;
    if scrol = 'yes' then begin
     {  piecetype[x][y] := 2;}
       wherex:=x;
       wherey:=y;
    end;
    xcal := x-4;
    ycal := y-3;



    {cansee[x][y] := 'yes';}
    {if (walltype[x][y] <> 3) and (walltype[x][y] <> 4) and (walltype[x][y] <> 9) then }


  {can you see the piece in the square?}
  {------------------------------------}
                                                 {----------------}
    if not (walltype[x][y] in [3,4,9]) then
      cansee[x][y-1] := 'yes';
                                                    {XXXXXXX}
    if not (walltype[x-1][y] in [2,4,8]) then       {XXXOXXX}
      cansee[x-1][y] := 'yes';                      {XXOûOXX}
                                                    {XXXOXXX}
    if not (walltype[x][y] in [2,4,8]) then         {XXXXXXX}
      cansee[x+1][y] := 'yes';

    if not (walltype[x][y+1] in [3,4,9]) then
      cansee[x][y+1] := 'yes';                    {--------------}

    if ((not (walltype[x][y] in [3,4,9])) and (not (walltype[x-1][y-1] in [2,4,8])))
     or ((not (walltype[x-1][y] in [8,4,2])) and (not (walltype[x-1][y] in [3,4,9]))) then
      cansee[x-1][y-1] := 'yes';                                                            {--------------}

    if ((not (walltype[x][y+1] in [3,4,9])) and (not (walltype[x-1][y+1] in [2,4,8])))         {XXXXXXX}
     or ((not (walltype[x-1][y] in [2,4,8])) and (not (walltype[x-1][y+1] in [3,4,9]))) then   {XXOûOXX}
      cansee[x-1][y+1] := 'yes';                                                               {XXûûûXX}
                                                                                               {XXOûOXX}
    if ((not (walltype[x][y-1] in [2,4,8])) and (not (walltype[x][y] in [3,4,9])))             {XXXXXXX}
     or ((not (walltype[x][y] in [2,4,8])) and (not (walltype[x+1][y] in [3,4,9]))) then
      cansee[x+1][y-1] := 'yes';
                                                                                            {---------------}
    if ((not (walltype[x][y] in [2,4,8])) and (not (walltype[x+1][y+1] in [3,4,9])))
     or ((not (walltype[x][y+1] in [3,4,9])) and (not (walltype[x][y+1] in [2,4,8]))) then
      cansee[x+1][y+1] := 'yes';

    if ((cansee[x][y-1] = 'yes') and (not (walltype[x][y-1] in [3,4,9]))) then      {---------------}
      cansee[x][y-2] := 'yes';
                                                                                       {XXXOXXX}
    if ((cansee[x][y+1] = 'yes') and (not (walltype[x][y+2] in [3,4,9]))) then         {XXûûûXX}
      cansee[x][y+2] := 'yes';                                                         {XOûûûOX}
                                                                                       {XXûûûXX}
    if ((cansee[x+1][y] = 'yes') and (not (walltype[x+1][y] in [2,4,8]))) then         {XXXOXXX}
      cansee[x+2][y] := 'yes';
                                                                                    {-----------------}
    if ((cansee[x-1][y] = 'yes') and (not (walltype[x-2][y] in [2,4,8]))) then
      cansee[x-2][y] := 'yes';
{----------------}
    if ((cansee[x+2][y] = 'yes') and (not (walltype[x+2][y+1] in [3,4,9])))
     or ((cansee[x+1][y+1] = 'yes') and (not (walltype[x+1][y+1] in [2,4,8]))) then
      cansee[x+2][y+1] := 'yes';

    if ((cansee[x+2][y] = 'yes') and (not (walltype[x+2][y] in [3,4,9])))
     or ((cansee[x+1][y-1] = 'yes') and (not (walltype[x+1][y-1] in [2,4,8]))) then
      cansee[x+2][y-1] := 'yes';

    if ((cansee[x+1][y-1] = 'yes') and (not (walltype[x+1][y-1] in [3,4,9])))
     or ((cansee[x][y-2] = 'yes') and (not (walltype[x][y-2] in [2,4,8]))) then
      cansee[x+1][y-2] := 'yes';

    if ((cansee[x+2][y-1] = 'yes') and (not (walltype[x+2][y-1] in [3,4,9])))
     or ((cansee[x+1][y-2] = 'yes') and (not (walltype[x+1][y-2] in [2,4,8]))) then
      cansee[x+2][y-2] := 'yes';

    if ((cansee[x-1][y+1] = 'yes') and (not (walltype[x-1][y+2] in [3,4,9])))
     or ((cansee[x][y+2] = 'yes') and (not (walltype[x-1][y+2] in [2,4,8]))) then
      cansee[x-1][y+2] := 'yes';

    if ((cansee[x+1][y+1] = 'yes') and (not (walltype[x+1][y+2] in [3,4,9])))
     or ((cansee[x][y+2] = 'yes') and (not (walltype[x][y+2] in [2,4,8]))) then
      cansee[x+1][y+2] := 'yes';
{}
    if ((cansee[x+2][y+1] = 'yes') and (not (walltype[x+2][y+2] in [3,4,9])))
     or ((cansee[x+1][y+2] = 'yes') and (not (walltype[x+1][y+2] in [2,4,8]))) then
      cansee[x+2][y+2] := 'yes';
{}
    if ((cansee[x+2][y] = 'yes') and (not (walltype[x+2][y] in [2,4,8])))
     or ((cansee[x+2][y] = 'yes') and (not (walltype[x+2][y] in [2,4,8]))) then
      cansee[x+3][y] := 'yes';

    if ((cansee[x+3][y] = 'yes') and (not (walltype[x+3][y] in [3,4,9])))
     or ((cansee[x+2][y-1] = 'yes') and (not (walltype[x+2][y-1] in [2,4,8]))) then
      cansee[x+3][y-1] := 'yes';

    if ((cansee[x+3][y-1] = 'yes') and (not (walltype[x+3][y-1] in [3,4,9])))
     or ((cansee[x+2][y-2] = 'yes') and (not (walltype[x+2][y-2] in [2,4,8]))) then
      cansee[x+3][y-2] := 'yes';
{}
    if ((cansee[x+3][y] = 'yes') and (not (walltype[x+3][y+1] in [3,4,9])))
     or ((cansee[x+2][y+1] = 'yes') and (not (walltype[x+2][y+1] in [2,4,8]))) then
      cansee[x+3][y+1] := 'yes';

    if ((cansee[x+3][y+1] = 'yes') and (not (walltype[x+3][y+2] in [3,4,9])))
     or ((cansee[x+2][y+2] = 'yes') and (not (walltype[x+2][y+2] in [2,4,8]))) then
      cansee[x+3][y+2] := 'yes';
{}
    if ((cansee[x-1][y-1] = 'yes') and (not (walltype[x-1][y-1] in [3,4,9])))
     or ((cansee[x][y-2] = 'yes') and (not (walltype[x-1][y-2] in [2,4,8]))) then
      cansee[x-1][y-2] := 'yes';

    if ((cansee[x-2][y] = 'yes') and (not (walltype[x-2][y] in [3,4,9])))
     or ((cansee[x-1][y-1] = 'yes') and (not (walltype[x-2][y-1] in [2,4,8]))) then
      cansee[x-2][y-1] := 'yes';

    if ((cansee[x-2][y-1] = 'yes') and (not (walltype[x-2][y-1] in [3,4,9])))
     or ((cansee[x-1][y-2] = 'yes') and (not (walltype[x-2][y-2] in [2,4,8]))) then     {-XXXXXX}
      cansee[x-2][y-2] := 'yes';                                                         {-XXXXXX}
{}                                                                                       {-XXXXXX}
    if ((cansee[x-2][y] = 'yes') and (not (walltype[x-2][y+1] in [3,4,9])))              {-XXXXXX}
     or ((cansee[x-1][y+1] = 'yes') and (not (walltype[x-2][y+1] in [2,4,8]))) then     {-XXXXXX}
      cansee[x-2][y+1] := 'yes';

    if ((cansee[x-2][y+1] = 'yes') and (not (walltype[x-2][y+2] in [3,4,9])))
     or ((cansee[x-1][y+2] = 'yes') and (not (walltype[x-2][y+2] in [2,4,8]))) then
      cansee[x-2][y+2] := 'yes';
 {everything but left side}
    if ((cansee[x-2][y] = 'yes') and (not (walltype[x-3][y] in [2,4,8])))
     or ((cansee[x-2][y] = 'yes') and (not (walltype[x-3][y] in [2,4,8]))) then
      cansee[x-3][y] := 'yes';

    if ((cansee[x-3][y] = 'yes') and (not (walltype[x-3][y] in [3,4,9])))
     or ((cansee[x-2][y-1] = 'yes') and (not (walltype[x-3][y-1] in [2,4,8]))) then
      cansee[x-3][y-1] := 'yes';

    if ((cansee[x-3][y-1] = 'yes') and (not (walltype[x-3][y-1] in [3,4,9])))
     or ((cansee[x-2][y-2] = 'yes') and (not (walltype[x-3][y-2] in [2,4,8]))) then
      cansee[x-3][y-2] := 'yes';
{}
    if ((cansee[x-3][y] = 'yes') and (not (walltype[x-3][y+1] in [3,4,9])))
     or ((cansee[x-2][y+1] = 'yes') and (not (walltype[x-3][y+1] in [2,4,8]))) then
      cansee[x-3][y+1] := 'yes';

    if ((cansee[x-3][y+1] = 'yes') and (not (walltype[x-3][y+2] in [3,4,9])))
     or ((cansee[x-2][y+2] = 'yes') and (not (walltype[x-3][y+2] in [2,4,8]))) then
      cansee[x-3][y+2] := 'yes';




















  {------------------------------------}




    repeat
    monstercheck := monstercheck + 1;
    cansee[x][y] := 'yes';
    piecetype[x][y] := 2;

 if monstercheck mod 5 = 0 then begin

    for xcounter := 1 to 32 do begin
      for ycounter := 1 to 23 do begin
          hasmoved[xcounter][ycounter] := 0;
      end;
    end;


    for ycounter := 1 to 23 do begin
      for xcounter := 1 to 32 do begin
         if (piecetype[xcounter][ycounter] = 99) and (hasmoved[xcounter][ycounter] = 0)
           and (cansee[xcounter][ycounter] = 'yes') then begin

          if (xcounter-x>0) and (not(walltype[xcounter-1][ycounter] in [2,4]))
           and (piecetype[xcounter-1][ycounter]=1) then begin
             piecetype[xcounter-1][ycounter] := piecetype[xcounter][ycounter];
             piecetype[xcounter][ycounter] := 1;
             hasmoved[xcounter-1][ycounter] := 1;
             cansee[xcounter-1][ycounter] := 'yes';
             cansee[xcounter][ycounter] := 'no';
          end;

          if (xcounter-x<0) and (not(walltype[xcounter][ycounter] in [2,4]))
           and (piecetype[xcounter+1][ycounter]=1) then begin
             piecetype[xcounter+1][ycounter] := piecetype[xcounter][ycounter];
             piecetype[xcounter][ycounter] := 1;
             hasmoved[xcounter+1][ycounter] := 1;
             cansee[xcounter+1][ycounter] := 'yes';
             cansee[xcounter][ycounter] := 'no';
          end;

          if (ycounter-y>0) and (not(walltype[xcounter][ycounter] in [3,4]))
           and (piecetype[xcounter][ycounter-1]=1) then begin
             piecetype[xcounter][ycounter-1] := piecetype[xcounter][ycounter];
             piecetype[xcounter][ycounter] := 1;
             hasmoved[xcounter][ycounter-1] := 1;
             cansee[xcounter][ycounter-1] := 'yes';
             cansee[xcounter][ycounter] := 'no';
          end;

          if (ycounter-y<0) and (not(walltype[xcounter][ycounter+1] in [3,4]))
           and (piecetype[xcounter][ycounter+1]=1) then begin
             piecetype[xcounter][ycounter+1] := piecetype[xcounter][ycounter];
             piecetype[xcounter][ycounter] := 1;
             hasmoved[xcounter][ycounter+1] := 1;
             cansee[xcounter][ycounter+1] := 'yes';
             cansee[xcounter][ycounter] := 'no';
          end;

          if (xcounter-x>0) and (not(walltype[xcounter-1][ycounter] in [2,4]))
           and (piecetype[xcounter-1][ycounter]=2) then begin
             fight(health,xxxxx,armor,weapon,x,y,gold,piecetype[x][y]);
             piecetype[x+1][y] := 1;
          end;

          if (xcounter-x<0) and (not(walltype[xcounter][ycounter] in [2,4]))
           and (piecetype[xcounter+1][ycounter]=2) then begin
             fight(health,xxxxx,armor,weapon,x,y,gold,piecetype[x][y]);
             piecetype[x-1][y]:=1;
          end;

          if (ycounter-y>0) and (not(walltype[xcounter][ycounter] in [3,4]))
           and (piecetype[xcounter][ycounter-1]=2) then begin
             fight(health,xxxxx,armor,weapon,x,y,gold,piecetype[x][y]);
             piecetype[x][y+1]:=1;
          end;

          if (ycounter-y<0) and (not(walltype[xcounter][ycounter+1] in [3,4]))
           and (piecetype[xcounter][ycounter+1]=2) then begin

             fight(health,xxxxx,armor,weapon,x,y,gold,piecetype[x][y]);
             piecetype[x][y-1] := 1;
          end;

        end;
      end;
    end;

 end;


    for suby := (y-2) to (y+2) do begin
        for subx := (x-3) to (x+3) do begin
            xx := subx-xcal;
            yy := suby-ycal;
            cansee[x][y] := 'yes';
            piecetype[x][y] := 2;
            drawtile(xx,yy,walltype[subx][suby],subx);
          { if ((subx<>x) or (suby<>y)) then begin
          { if cansee[subx][suby] = 'yes' then}


            if (cansee[subx][suby] = 'yes') and (piecetype[subx][suby] <> 1) then
               drawpiece(xx,yy,piecetype[subx][suby]);

            cansee[x][y] := 'no';
            piecetype[x][y] := 1;
          { end;}
        end;
    end;






    delay(250);

    xaxis:=0;
    yaxis:=0;
    until keypressed;
    move := readkey;
     if ((move = '4') or (ord(move)=75)) and (x>4) and (piecetype[x-1][y]=1) and
                (walltype[x-1][y]<>2) and (walltype[x-1][y]<>4) then begin
        scrol := 'yes';
        x := x-1;
     end;
     if ((move = '6') or (ord(move)=77)) and (x<29) and (piecetype[x+1][y]=1) and
                (walltype[x][y]<>2) and (walltype[x][y]<>4) then begin
        scrol := 'yes';
        x := x+1;
     end;
     if ((move = '8') or (ord(move)=72)) and (y>3) and (piecetype[x][y-1]=1) and
                (walltype[x][y]<>3) and (walltype[x][y]<>4) then begin
        scrol := 'yes';
        y := y-1;
     end;
     if ((move = '2') or (ord(move)=80)) and (y<21) and (piecetype[x][y+1]=1) and
                (walltype[x][y+1]<>3) and (walltype[x][y+1]<>4) then begin
        scrol := 'yes';
        y := y+1;
     end;



     if (move = 'q') or (ord(move)=27) then
        xxxxx := 0;
    {if (move = '4') and (x<5) and (piecetype[wherex-1][wherey]=1) then begin
        scrol := 'no';
        piecetype[x][y] := 1;
        wherex := wherex-1;
        piecetype[wherex][wherey] := 2;
     end;
     if (move = '6') and (x>22) and (piecetype[wherex+1][wherey]=1) then begin
        scrol := 'no';
        piecetype[x][y] := 1;
        wherex := x+1;
        piecetype[wherex][wherey] := 2;
     end;
     if (move = '8') and (y<4) and (piecetype[wherex][wherey-1]=1) then begin
        scrol := 'no';
        piecetype[x][y] := 1;
        wherey := wherey-1;
        piecetype[wherex][wherey] := 2;
     end;
     if (move = '2') and (y>16) and (piecetype[wherex][wherey+1]=1) then begin
        scrol := 'no';
        piecetype[x][y] := 1;
        wherey := wherey+1;
        piecetype[wherex][wherey] := 2;
     end;                                 }

end;
{----------------------------------------------------------------}
{----------------------------------------------------------------}
procedure instruc;
var
   ch:char;
begin
    clrscr;
    textcolor(white);
    write('Do you need instructions? [Y/N] ');
    repeat
    ch := readkey;
    ch := upcase(ch);
    until (ch = 'Y') or (ch = 'N');
    if ch = 'Y' then begin
       writeln(ch);
       writeln('Sorry, I haven''t done that yet');
       readln;
       instruc;
    end;
end;
{=============================================================}
{=============================================================}
var
   x,check,maker,monstercheck: integer;
   scrol: string;
begin
     x :=1;
     scrol := 'yes';
     monstercheck := 1;
     check := 0;
     maker := 0;
     clrscr;
     titlescreen;
     clrscr;
     randomize;
     instruc;
     {introfor1; }
     repeat
     game(x,check,maker,monstercheck,scrol);
     until x=0;

end.






