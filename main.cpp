#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;


float offsetX=0, offsetY=0;


const int H = 17;
const int W = 150;


String TileMap[H] = {
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                                                                                    B                                               0",
"0                                                                                    w               B                                               0",
"0                   w                                  w                   w                         B                                               0",
"0                                      w                                                             B   ееее                                        0",
"0                                                                                                    B   е                                           0",
"0                      c                                                                       w     B   ееее                                        0",
"0                                                                       r                            B   е                                           0",
"0                                                                      rr                     N      B   ееее                                        0",
"0                                                                     rrr                            B                                               0",
"0               c    kckck                                           rrrr                        M   B                                               0",
"0                                      t0                           rrrrr                        M   B                                               0",
"0G                                     00              t0          rrrrrr            G           M   B                                               0",
"0           d    g       d             00              00         rrrrrrr                        M   B                                               0",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};
bool lose;
bool win;
float vor;
int l;
Image health;
Image gameover;
Texture texture; Texture texture1;
Sprite sprite;Sprite sprite1;
class PLAYER
{
public:
float dx,dy;
bool mariored;
FloatRect rect;
bool onGround;
Sprite sprite;
Sprite health;
float currentFrame;
float timer;
float touch;


    PLAYER(Texture &image)
   {
	sprite.setTexture(image);
	rect = FloatRect(100,180,16,16);

	dx=dy=0.1;
	currentFrame = 0;
	mariored=false;
	touch=3;
	timer=0;
   }


   void update(float time)
   {
	 rect.left += dx * time;
     Collision(0);

	 if (!onGround) dy=dy+0.0005*time;
	 rect.top += dy*time;
	 onGround=false;
     Collision(1);


     currentFrame += time * 0.005;
     if (currentFrame > 3) currentFrame -= 3;

    if (dx>0) sprite.setTextureRect(IntRect(112+31*int(currentFrame),144,16,16));
	if (dx<0) sprite.setTextureRect(IntRect(112+31*int(currentFrame)+16,144,-16,16));


	 sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

	 dx=0;
	 if (mariored) {
                timer+=time;
                if (currentFrame > 1.5){sprite.setColor(Color::Red);}
                else {sprite.setColor(Color::White);}
                if (timer>5000) {mariored=false;timer=0;l+=34;sprite.setColor(Color::White);}}
   }

   void Collision(int num)
{

	for (int i = rect.top/16 ; i<(rect.top+rect.height)/16; i++)
		for (int j = rect.left/16; j<(rect.left+rect.width)/16; j++)
			 {
				 if ((TileMap[i][j]=='B') || (TileMap[i][j]=='0') || (TileMap[i][j]=='r') || (TileMap[i][j]=='t') || (TileMap[i][j]=='q'))
				                         {
												   if (dy>0 && num==1)
												   { rect.top =   i*16 -  rect.height;  dy=0;   onGround=true; }
											       if (dy<0 && num==1)
												   { rect.top = i*16 + 16;   dy=0;}
												   if (dx>0 && num==0)
												   { rect.left =  j*16 -  rect.width; }
											       if (dx<0 && num==0)
												   { rect.left =  j*16 +16;}
										 }

				 if (TileMap[i][j]=='c') {

                        if (dy>0 && num==1)
												   { rect.top =   i*16 -  rect.height;  dy=0;   onGround=true; }

                        if (dy<0 && num==1)
                        {                            rect.top = i*16 + 16;   dy=0;
                        TileMap[i][j]='q';
                        }
                        if (dx>0 && num==0)
												   { rect.left =  j*16 -  rect.width; }
												   											       if (dx<0 && num==0)
												   { rect.left =  j*16 +16;}

                        }

                 if (TileMap[i][j]=='k') {

                        if (dy>0 && num==1)
												   { rect.top =   i*16 -  rect.height;  dy=0;   onGround=true; }

                        if (dy<0 && num==1)
                        {                            rect.top = i*16 + 16;   dy=0;

                        TileMap[i][j]='u';
                        }
                        if (dx>0 && num==0)
												   { rect.left =  j*16 -  rect.width; }
												   											       if (dx<0 && num==0)
												   { rect.left =  j*16 +16;}

                        }

                        if (TileMap[i][j]=='M') {

                        if (dy>0 && num==1) win=true;


                        if (dy<0 && num==1)
                        {
                            win=true;
                        }
                        if (dx>0 && num==0) win=true;

						if (dx<0 && num==0) win=true;

                        }



                 if (TileMap[i][j]=='M') {
                                            vor=1;
                                         }

			 }

}
};

class ENEMY
{

public:
	float dx,dy;
FloatRect rect;
bool onGround;
Sprite sprite;
float currentFrame;
bool life;
   void set(Texture &image, int x, int y)
   {
	sprite.setTexture(image);
	rect = FloatRect(x,y,16,16);

    dx=0.05;
	currentFrame = 0;
	life=true;
   }

   void update(float time)
   {
	 rect.left += dx * time;

     Collision();


     currentFrame += time * 0.005;
     if (currentFrame > 2) currentFrame -= 2;

    sprite.setTextureRect(IntRect(18*int(currentFrame),   0, 16,16));
    if (!life) sprite.setTextureRect(IntRect(58, 0, 16,16));


	sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

   }


   void Collision()
  {

	for (int i = rect.top/16 ; i<(rect.top+rect.height)/16; i++)
		for (int j = rect.left/16; j<(rect.left+rect.width)/16; j++)
			 if ((TileMap[i][j]=='B') || (TileMap[i][j]=='0'))
			                           {
                                                    if (dx>0)
												   { rect.left =  j*16 - rect.width; dx*=-1; }
											        else if (dx<0)
												   { rect.left =  j*16 + 16;  dx*=-1; }

										}
  }

};



int main()
{
    l=34;
    RenderWindow window(sf::VideoMode(400, 250, 16), "SFML works!", Style::None);
        window.setPosition(sf::Vector2i(0, 0));
        window.setSize(sf::Vector2u(1600, 900));

	Texture tileSet;
	tileSet.loadFromFile("Mario_Tileset.png");
	health.loadFromFile("OzzEl.png");
	texture.loadFromImage(health);
	sprite.setTexture(texture);
	sprite.setPosition(0,0);
	sprite.setTextureRect(IntRect(0,0,108,55));

	PLAYER Mario(tileSet);
	ENEMY  enemy;
	enemy.set(tileSet,48*16,13*16);
	Sprite tile(tileSet);

	SoundBuffer buffer, high, extra;
	buffer.loadFromFile("Jump.ogg");
	Sound sound(buffer);
	high.loadFromFile("Pain.ogg");
	Sound pain(high);




	Texture menu_texture1,menu_texture2,menu_texture3,menu_texture4,about_texture,over_texture;
	menu_texture1.loadFromFile("111.png");
	menu_texture2.loadFromFile("222.png");
    menu_texture3.loadFromFile("333.png");
    menu_texture4.loadFromFile("instr.png");
	about_texture.loadFromFile("about.png");
    over_texture.loadFromFile("over.png");
	Sprite menu1(menu_texture1),menu2(menu_texture2),menu3(menu_texture3),about(about_texture),over(over_texture),menu4(menu_texture4);
	bool Menu=1;
	int MenuNum=0;
	menu1.setPosition(100,30);
	menu2.setPosition(100,90);
    menu3.setPosition(100,150);
    menu4.setPosition(0,0);
    over.setPosition(100,150);


	while(Menu)
	{
	   menu1.setColor(Color::Red);
	   menu2.setColor(Color::White);
	   menu3.setColor(Color::White);
	   MenuNum=0;
	   window.clear(Color(0,0,0));

	   if (IntRect(300,150,900,100).contains(Mouse::getPosition(window))) {menu1.setColor(Color::Yellow); MenuNum=1;}
       if (IntRect(300,300,900,150).contains(Mouse::getPosition(window))) {menu2.setColor(Color::Yellow); MenuNum=2;}
       if (IntRect(300,550,900,150).contains(Mouse::getPosition(window))) {menu3.setColor(Color::Yellow); MenuNum=3;}

	   if (Mouse::isButtonPressed(Mouse::Left))
	     {
			 if (MenuNum==1) {Menu=false;window.setMouseCursorVisible(false);}
			 if (MenuNum==2) {window.draw(about); window.display(); while(!Keyboard::isKeyPressed(Keyboard::Escape)) ;}
			 if (MenuNum==3)  {window.close();Menu=false;}

	     }


		    window.draw(menu1);
            window.draw(menu2);
			window.draw(menu3);
			window.draw(menu4);

		window.display();
	}

	Music music;
	music.setLoop(true);
    music.openFromFile("Mario_Theme.ogg");
    music.play();

	Clock clock;

    while (window.isOpen())
    {

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time/500;

		if (time > 20) time = 20;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
		}


		if (Keyboard::isKeyPressed(Keyboard::Left))    Mario.dx=-0.1;

	    if (Keyboard::isKeyPressed(Keyboard::Right))    Mario.dx=0.1;

	    if (Keyboard::isKeyPressed(Keyboard::Up))	if (Mario.onGround) { Mario.dy=-0.27; Mario.onGround=false;  sound.play();}




		 Mario.update(time);
		 enemy.update(time);


		 if  (Mario.rect.intersects( enemy.rect ) )
		 {
			 if (enemy.life) {
                if (Mario.dy>0) { enemy.dx=0; Mario.dy=-0.2; enemy.life=false;}
                else if (!Mario.mariored) { Mario.touch-=1; pain.play(); Mario.mariored=true;sprite.setTextureRect(IntRect(0,0,108-l,55));}
		 }
		 }

		 if (Mario.rect.left>200) offsetX = Mario.rect.left-200;

         if (Mario.touch<=0) {lose=true; window.draw(over); over.setPosition(100,30);over.setColor(Color::Red);window.display();window.close();}
         if (vor==1) {window.close();}

		 window.clear(Color(107,140,255));


		 for (int i=0; i<H; i++)
			 for (int j=0; j<W; j++)
			  {
				if (TileMap[i][j]=='B')  tile.setTextureRect( IntRect(143-16*3,112,16,16) );

				if (TileMap[i][j]=='k')  tile.setTextureRect( IntRect(143,112,16,16) );


                if (TileMap[i][j]=='u')  {
                                            tile.setTextureRect( IntRect(239,216,17,16));
                                            float currentFrame;
                                            currentFrame += time * 0.1;
                                            if (currentFrame > 30) {TileMap[i][j]=' ';currentFrame = 0;}



                }
                if (TileMap[i][j]=='c')  {
                                            float pounce;
                                            pounce+=time*0.01;
                                            if (pounce > 60) {pounce = 0;}
                if (pounce > 0 && pounce < 20){

                        tile.setTextureRect( IntRect(143-16,112,17,16) );

                                                    }
           if (pounce > 20 && pounce < 40 ){
                tile.setTextureRect( IntRect(79,112,17,16) );}
                                                  if (pounce > 40 && pounce < 60 ){
                                                      tile.setTextureRect( IntRect(47,31,17,16) );
                                                  }


                }



				if (TileMap[i][j]=='t')  tile.setTextureRect( IntRect(0,47,32,95-47) );

				if (TileMap[i][j]=='N')  tile.setTextureRect( IntRect(96,7,202-96,112) );

				if (TileMap[i][j]=='g')  tile.setTextureRect( IntRect(0,16*9-5,3*16,16*2+5) );

                if (TileMap[i][j]=='G')  tile.setTextureRect( IntRect(145,222,222-145,255-222) );

                if (TileMap[i][j]=='q')  tile.setTextureRect( IntRect(77,16,17,32));

                if (TileMap[i][j]=='l')  tile.setTextureRect( IntRect(77,0,17,16));

                if (TileMap[i][j]=='d')  tile.setTextureRect( IntRect(0,106,74,127-106) );

				if (TileMap[i][j]=='w')  tile.setTextureRect( IntRect(99,224,140-99,255-224) );

				if (TileMap[i][j]=='r')  tile.setTextureRect( IntRect(143-32,112,16,16) );

				if ((TileMap[i][j]==' ') || (TileMap[i][j]=='M') || (TileMap[i][j]=='0')) continue;



  			    tile.setPosition(j*16-offsetX,i*16 - offsetY) ;
		        window.draw(tile);
		     }
		window.draw(Mario.sprite);
	    window.draw(enemy.sprite);
	    window.draw(sprite);

		window.display();
    };

        music.pause();

        if (lose){
        RenderWindow pinus(VideoMode(500, 200, 16), "GAME OVER", Style::None);
        pinus.setMouseCursorVisible(false);
        pinus.setPosition(sf::Vector2i(0, 0));
        pinus.setSize(sf::Vector2u(1600, 900));
        gameover.loadFromFile("GameOver.png");
        texture1.loadFromImage(gameover);
        sprite1.setTexture(texture1);
        sprite1.setPosition(0,0);

         extra.loadFromFile("Lose.ogg");
         Sound Over(extra);
         Over.play();
         while (pinus.isOpen())
    {
        Event event;
        while (pinus.pollEvent(event))
        {
            if (event.type == Event::Closed)
                pinus.close();
        }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                pinus.close();
            }

        pinus.clear();
        pinus.draw(sprite1);
        pinus.display();
    }
        }

        if (win){
        RenderWindow pinus(VideoMode(400, 250, 16), "WIN!!!", Style::None);
        pinus.setMouseCursorVisible(false);
        pinus.setPosition(sf::Vector2i(0, 0));
        pinus.setSize(sf::Vector2u(1600, 900));
        gameover.loadFromFile("Neko.png");
        texture1.loadFromImage(gameover);
        sprite1.setTexture(texture1);
        sprite1.setPosition(0,0);
        extra.loadFromFile("Congratulations.ogg");
        Sound victory(extra);
        victory.play();
         while (pinus.isOpen())
    {
        Event event;
        while (pinus.pollEvent(event))
        {
            if (event.type == Event::Closed)
                pinus.close();
        }
                    if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                pinus.close();
            }
        pinus.clear();
        pinus.draw(sprite1);
        pinus.display();
    }
        }

    return 0;
}



